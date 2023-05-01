#include "glslUtil.h"
#include <libshaderc_util/file_finder.h>
#include <SPIRV_Cross/spirv_glsl.hpp>

static std::string getContentFromFile(const char* name)
{
    FILE* fp = fopen(name, "rb");
    fseek(fp, 0, SEEK_END);

    int32_t size = ftell(fp);

    fseek(fp, 0, SEEK_SET);

    std::string content;
    content.resize(size);
    fread((void*)content.data(), 1, size, fp);
    fclose(fp);
    return content;
}

class MyIncluderInterface : public shaderc::CompileOptions::IncluderInterface
{
public:
    virtual shaderc_include_result* GetInclude(const char* requested_source,
        shaderc_include_type type,
        const char* requesting_source,
        size_t include_depth)
    {
        std::string name(requested_source);
        mIncludeResult.source_name = requested_source;
        mIncludeResult.source_name_length = name.size();

        std::string content = getContentFromFile(name.c_str());
        mIncludeResult.content = content.c_str();
        mIncludeResult.content_length = content.length();
        return &mIncludeResult;
    }

    // Handles shaderc_include_result_release_fn callbacks.
    virtual void ReleaseInclude(shaderc_include_result* data)
    {

    }
private:
    shaderc_include_result mIncludeResult;
};

std::string getGlslKey(
    std::string& shaderName,
    std::vector<std::pair<std::string, std::string>>& shaderMacros,
    shaderc_shader_kind kind)
{
    uint64_t macro_bit = 0;
    std::vector<std::string> keys;
    for (auto& pair : shaderMacros)
    {
        keys.push_back(pair.first);
        keys.push_back(pair.second);
    }
    keys.push_back(std::to_string(kind));

    std::sort(keys.begin(), keys.end());

    std::string result;
    for (auto& key : keys)
    {
        result += key;
    }
    return result;
}

static std::unordered_map<std::string, std::string> gGlslCacheMap;

bool glslCompileShader(
    std::string& result,
    std::string& shaderName,
    std::string& shaderContent,
    std::string& entryPoint,
	std::vector<std::pair<std::string, std::string>>& shaderMacros,
    shaderc_shader_kind kind
)
{

    std::string key = getGlslKey(shaderName, shaderMacros, kind);

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

    if (kind == shaderc_glsl_vertex_shader)
    {
        options.AddMacroDefinition("VERTEX_SHADER", "1");
    }
    else if (kind == shaderc_glsl_fragment_shader)
    {
        options.AddMacroDefinition("FRAGMENT_SHADER", "1");
    }

    shaderc::SpvCompilationResult module =
        compiler.CompileGlslToSpv(
            shaderContent, 
            kind, 
            shaderName.c_str(), 
            entryPoint.c_str(),
            options);

    if (module.GetCompilationStatus() != shaderc_compilation_status_success) {
        std::string aa  = module.GetErrorMessage();
        return false;
    }


    std::vector<uint32_t> aa = { module.cbegin(), module.cend() };

    result.resize(aa.size() * sizeof(uint32_t));
    memcpy((void*)result.data(), aa.data(), aa.size() * sizeof(uint32_t));

    gGlslCacheMap[key] = result;

    return true;
}

void parserGlslInputDesc(
    const std::string& code,
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