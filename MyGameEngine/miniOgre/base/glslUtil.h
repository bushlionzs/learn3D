#pragma once
#include <shaderc/shaderc.hpp>
bool glslCompileShader(
	String& result,
	String& shaderName,
	String& shaderContent,
	String& entryPoint,
	std::vector<std::pair<std::string, std::string>>& shaderMacros,
	shaderc_shader_kind kind
);

struct GlslInputDesc
{
	String _name;
	uint32_t _index;
	uint32_t _location;
};

void parserGlslInputDesc(
	const String& code,
	std::vector<GlslInputDesc>& inputDesc);