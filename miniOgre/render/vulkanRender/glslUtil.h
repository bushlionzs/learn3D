#pragma once
#include <shaderc/shaderc.hpp>
#include <OgreCommon.h>
#include <VulkanCommon.h>



bool glslCompileShader
(
	std::string& shaderName,
	std::string& shaderContent,
	std::string& entryPoint,
	const std::vector<std::pair<std::string, std::string>>& shaderMacros,
	VkShaderModuleInfo& shaderModuleInfo
);


void  parserGlslInputDesc(
	const std::string& code,
	std::vector<GlslInputDesc>& inputDesc);