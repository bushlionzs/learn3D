#pragma once
#include "shader.h"
#include "VulkanCommon.h"
#include "glslUtil.h"
class VulkanRenderSystem;
class VertexDeclaration;

class VulkanShader :public Shader
{
public:
public:
    VulkanShader(ShaderInfo& info, VulkanRenderSystem* engine);

    ~VulkanShader();

    bool load();
    void updateInputDesc(VertexDeclaration* vDeclaration);

    VkPipeline getVKPipeline(VulkanPass* pass);

    VkShaderModule getVertexModule()
    {
        return mVertexShader;
    }

    VkShaderModule getFlagModule()
    {
        return mFragShader;
    }

private:
    void createGraphicsPipeline(VulkanPass* pass);
    std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions(VertexDeclaration* vd);
    VkShaderModule VulkanShader::createShaderModule(const std::string& code);
private:
    VulkanRenderSystem* mEngine = nullptr;
    ShaderInfo mShaderInfo;

    VkShaderModule mVertexShader;
    VkShaderModule mFragShader;

    VkPipeline mGraphicsPipeline = VK_NULL_HANDLE;

    std::vector<GlslInputDesc> mInputDesc;
};