#pragma once
#include <shaderc/shaderc.hpp>

#ifdef GLSL_EXPORTS
/* We are building this library */
#      define _GLSLExport __declspec(dllexport)
#    else
/* We are using this library */
#      define _GLSLExport __declspec(dllimport)
#    endif


bool _GLSLExport glslCompileShader(
	std::string& result,
	std::string& shaderName,
	std::string& shaderContent,
	std::string& entryPoint,
	std::vector<std::pair<std::string, std::string>>& shaderMacros,
	shaderc_shader_kind kind
);

struct GlslInputDesc
{
	std::string _name;
	uint32_t _index;
	uint32_t _location;
};

void _GLSLExport parserGlslInputDesc(
	const std::string& code,
	std::vector<GlslInputDesc>& inputDesc);