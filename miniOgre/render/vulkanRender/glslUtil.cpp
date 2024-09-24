#include <OgreHeader.h>
#include "glslUtil.h"
#include <libshaderc_util/file_finder.h>
#include <SPIRV_Cross/spirv_glsl.hpp>
#include <VulkanTools.h>
#include <VulkanHelper.h>
#include <mutex>

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
    MyIncluderInterface(const std::string& rootpath)
    {
        mRootPath = rootpath;
    }
    virtual shaderc_include_result* GetInclude(const char* requested_source,
        shaderc_include_type type,
        const char* requesting_source,
        size_t include_depth)
    {
        mName = mRootPath + requested_source;
        mIncludeResult.source_name = mName.c_str();
        mIncludeResult.source_name_length = mName.size();

        mContent = getContentFromFile(mName.c_str());
        mIncludeResult.content = mContent.c_str();
        mIncludeResult.content_length = mContent.length();
        return &mIncludeResult;
    }

    // Handles shaderc_include_result_release_fn callbacks.
    virtual void ReleaseInclude(shaderc_include_result* data)
    {

    }
private:
    shaderc_include_result mIncludeResult;
    std::string mName;
    std::string mContent;
    std::string mRootPath;
};

std::string getGlslKey(
    std::string& shaderName,
    const std::vector<std::pair<std::string, std::string>>& shaderMacros,
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

    std::string result = shaderName;
    for (auto& key : keys)
    {
        result += key;
    }
    return result;
}

struct ShaderContent
{
    VkShaderModule shaderModule;
    std::vector<GlslInputDesc> inputDesc;
};
static std::unordered_map<std::string, ShaderContent> gVertexShaderCacheMap;

static std::mutex gShaderMutex;

VkShaderModule glslCompileVertexShader(
    std::string& shaderName,
    std::string& shaderContent,
    std::string& entryPoint,
	const std::vector<std::pair<std::string, std::string>>& shaderMacros,
    std::vector<GlslInputDesc>& inputDesc
)
{
    std::string key = getGlslKey(shaderName, shaderMacros, shaderc_glsl_vertex_shader);

    {
        std::unique_lock<std::mutex> lck(gShaderMutex);
        auto itor = gVertexShaderCacheMap.find(key);

        if (itor != gVertexShaderCacheMap.end())
        {
            inputDesc = itor->second.inputDesc;
            return itor->second.shaderModule;
        }
    }
    
    shaderc::Compiler compiler;
    shaderc::CompileOptions options;


    auto pos = shaderName.find_last_of("\\");
    std::string rootpath = shaderName.substr(0, pos+1);


   options.SetIncluder(std::make_unique<MyIncluderInterface>(rootpath));
    // Like -DMY_DEFINE=1
    for (auto& pair : shaderMacros)
    {
        options.AddMacroDefinition(pair.first, pair.second);
    }

  
    options.AddMacroDefinition("VERTEX_SHADER", "1");


    shaderc::SpvCompilationResult module =
        compiler.CompileGlslToSpv(
            shaderContent, 
            shaderc_glsl_vertex_shader,
            shaderName.c_str(), 
            entryPoint.c_str(),
            options);

    if (module.GetCompilationStatus() != shaderc_compilation_status_success) {
        std::string aa  = module.GetErrorMessage();
        assert(false);
        return VK_NULL_HANDLE;
    }


    std::vector<uint32_t> aa = { module.cbegin(), module.cend() };

    std::string result;
    result.resize(aa.size() * sizeof(uint32_t));
    memcpy((void*)result.data(), aa.data(), aa.size() * sizeof(uint32_t));
    auto device = VulkanHelper::getSingleton()._getVkDevice();
    VkShaderModule shader = vks::tools::loadShaderMemory(result, device);
    if (VK_NULL_HANDLE == shader)
    {
        return VK_NULL_HANDLE;
    }

    {
        std::unique_lock<std::mutex> lck(gShaderMutex);
        auto itor = gVertexShaderCacheMap.find(key);
        if (itor == gVertexShaderCacheMap.end())
        {
            gVertexShaderCacheMap[key].shaderModule = shader;
            parserGlslInputDesc(result, inputDesc);
            gVertexShaderCacheMap[key].inputDesc = inputDesc;
        }
    }

    return shader;
}

static std::unordered_map<std::string, VkShaderModule> gFragShaderCacheMap;

VkShaderModule glslCompileFragShader(
    std::string& shaderName,
    std::string& shaderContent,
    std::string& entryPoint,
    const std::vector<std::pair<std::string, std::string>>& shaderMacros
)
{
    std::string key = getGlslKey(shaderName, shaderMacros, shaderc_glsl_fragment_shader);

    {
        std::unique_lock<std::mutex> lck(gShaderMutex);
        auto itor = gFragShaderCacheMap.find(key);

        if (itor != gFragShaderCacheMap.end())
        {
            return itor->second;
        }
    }

    shaderc::Compiler compiler;
    shaderc::CompileOptions options;


    auto pos = shaderName.find_last_of("\\");
    std::string rootpath = shaderName.substr(0, pos + 1);


    options.SetIncluder(std::make_unique<MyIncluderInterface>(rootpath));
    // Like -DMY_DEFINE=1
    for (auto& pair : shaderMacros)
    {
        options.AddMacroDefinition(pair.first, pair.second);
    }


    options.AddMacroDefinition("FRAGMENT_SHADER", "1");
    

    shaderc::SpvCompilationResult module =
        compiler.CompileGlslToSpv(
            shaderContent,
            shaderc_glsl_fragment_shader,
            shaderName.c_str(),
            entryPoint.c_str(),
            options);

    if (module.GetCompilationStatus() != shaderc_compilation_status_success) {
        std::string aa = module.GetErrorMessage();
        assert(false);
        return VK_NULL_HANDLE;
    }


    std::vector<uint32_t> aa = { module.cbegin(), module.cend() };

    std::string result;
    result.resize(aa.size() * sizeof(uint32_t));
    memcpy((void*)result.data(), aa.data(), aa.size() * sizeof(uint32_t));
    auto device = VulkanHelper::getSingleton()._getVkDevice();
    VkShaderModule shader = vks::tools::loadShaderMemory(result, device);
    if (VK_NULL_HANDLE == shader)
    {
        return VK_NULL_HANDLE;
    }

    {
        std::unique_lock<std::mutex> lck(gShaderMutex);
        auto itor = gFragShaderCacheMap.find(key);
        if (itor == gFragShaderCacheMap.end())
        {
            gFragShaderCacheMap[key] = shader;
        }
    }

    return shader;
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