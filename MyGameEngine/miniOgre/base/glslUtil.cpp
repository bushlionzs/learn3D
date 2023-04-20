#include "OgreHeader.h"
#include "glslUtil.h"
#include <libshaderc_util/file_finder.h>
#include "shaderManager.h"
#include <SPIRV_Cross/spirv_glsl.hpp>
#include "OgreString.h"

class MyIncluderInterface : public shaderc::CompileOptions::IncluderInterface
{
public:
    virtual shaderc_include_result* GetInclude(const char* requested_source,
        shaderc_include_type type,
        const char* requesting_source,
        size_t include_depth)
    {
        String name(requested_source);
        mIncludeResult.source_name = requested_source;
        mIncludeResult.source_name_length = name.size();

        String* content = ShaderManager::getSingleton().getShaderContent(name);
        mIncludeResult.content = content->c_str();
        mIncludeResult.content_length = content->length();
        return &mIncludeResult;
    }

    // Handles shaderc_include_result_release_fn callbacks.
    virtual void ReleaseInclude(shaderc_include_result* data)
    {

    }
private:
    shaderc_include_result mIncludeResult;
};

String getGlslKey(String& shaderName, std::vector<std::pair<std::string, std::string>>& shaderMacros)
{
    uint64_t macro_bit = 0;
    for (auto& pair : shaderMacros)
    {
        auto index = ShaderManager::getSingleton().getMacroIndex(pair.first);

        macro_bit |= index;
    }
    return Ogre::StringUtil::format("%s%lld", shaderName, macro_bit);
}

static std::unordered_map<String, String> gGlslCacheMap;

bool glslCompileShader(
	String& result,
	String& shaderName,
    String& shaderContent,
	std::vector<std::pair<std::string, std::string>>& shaderMacros,
    shaderc_shader_kind kind
)
{

    String key = getGlslKey(shaderName, shaderMacros);

    auto itor = gGlslCacheMap.find(key);

    if (itor != gGlslCacheMap.end())
    {
        result = itor->second;
        return true;
    }
    shaderc::Compiler compiler;
    shaderc::CompileOptions options;
   options.SetIncluder(std::make_unique<MyIncluderInterface>());
    // Like -DMY_DEFINE=1
    for (auto& pair : shaderMacros)
    {
        options.AddMacroDefinition(pair.first, pair.second);
    }

    shaderc::SpvCompilationResult module =
        compiler.CompileGlslToSpv(shaderContent, kind, shaderName.c_str(), options);

    if (module.GetCompilationStatus() != shaderc_compilation_status_success) {
        std::string aa  = module.GetErrorMessage();
        OGRE_EXCEPT(Exception::ERR_INVALIDPARAMS, "glsl compile error");
        return false;
    }


    std::vector<uint32_t> aa = { module.cbegin(), module.cend() };

    result.resize(aa.size() * sizeof(uint32_t));
    memcpy(result.data(), aa.data(), aa.size() * sizeof(uint32_t));

    gGlslCacheMap[key] = result;

    return true;
}

void parserGlslInputDesc(
    const String& code,
    std::vector<GlslInputDesc>& inputDesc)
{
    spirv_cross::CompilerGLSL  glsl((const uint32_t*)code.data(), code.size()/4);

    auto inputs = glsl.get_shader_resources().stage_inputs;

    int32_t size = inputs.size();
    inputDesc.resize(size);

    for (int32_t i = 0; i < size; i++) 
    {
        auto& input = inputs[i];
        inputDesc[i]._name = glsl.get_name(input.id);
        inputDesc[i]._index = 0;
        assert(!inputDesc[i]._name.empty());

        if (inputDesc[i]._name.back() >= '0' && inputDesc[i]._name.back() <= '9')
        {
            inputDesc[i]._index = inputDesc[i]._name.back() - '0';
            inputDesc[i]._name.pop_back();
        }

        inputDesc[i]._location = glsl.get_decoration(input.id, spv::DecorationLocation);
    }
}