#pragma once
#include <shaderc/shaderc.hpp>
#include <VulkanCommon.h>

struct GlslInputDesc
{
	std::string _name;
	uint32_t _index;
	uint32_t _location;
	uint32_t _size;
	uint32_t _type;
	uint32_t _offset;

};
VkShaderModule  glslCompileVertexShader(
	std::string& shaderName,
	std::string& shaderContent,
	std::string& entryPoint,
	const std::vector<std::pair<std::string, std::string>>& shaderMacros,
	std::vector<GlslInputDesc>& inputDesc
);

VkShaderModule  glslCompileFragShader(
	std::string& shaderName,
	std::string& shaderContent,
	std::string& entryPoint,
	const std::vector<std::pair<std::string, std::string>>& shaderMacros
);

void  parserGlslInputDesc(
	const std::string& code,
	std::vector<GlslInputDesc>& inputDesc);