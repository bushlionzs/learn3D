#pragma once

#include "OgreSingleton.h"
#include "OgreScriptLoader.h"
#include "engine_struct.h"

namespace Ogre {

	class ShaderPrivateInfo
	{
	public:
		std::string vertexShaderName;
		std::string vertexShaderEntryPoint;

		std::string fragShaderName;
		std::string fragShaderEntryPoint;

		std::string geometryShaderName;
		std::string geometryShaderEntryPoint;

		std::string computeShaderName;
		std::string computeShaderEntryPoint;
	};
	class ShaderTypeInfo
	{
	public:
		ShaderPrivateInfo privateInfo;
	};

	class ShaderFormat
	{
	public:
		ShaderTypeInfo shaderInfo[EngineType_Count];
	};

	struct ShaderTechnique
	{
		std::string name;
		ShaderFormat shaderFormat;
	};

	struct ShaderConfig
	{
		std::vector<ShaderTechnique> techniques;
	};

	class ShaderManager : public Ogre::Singleton<ShaderManager>, public ScriptLoader
	{
	public:
		ShaderManager();
		~ShaderManager();

        virtual std::vector<String> getSuffix();

        virtual void parseScript(ResourceInfo* res, const String& groupName);

        virtual Real getLoadingOrder(void) const;

		ShaderPrivateInfo* getShader(
			const String& name, 
			EngineType renderSystem,
			const char* technique = nullptr);

		String* getShaderContent(const String& name);

		void addMacro(const String& name);
		int32_t getMacroIndex(const String& name);

	private:
		void parseShaderImpl(const String& content);
		bool readShaderUnit(
			std::stringstream& ss,
			ShaderConfig* shaderInfo);
		bool readTechnique(std::stringstream& ss, ShaderConfig* shaderInfo);

		void addShader(const String& name, ShaderConfig* shaderInfo);

		bool isComment(const String& linePart);
	private:
		std::unordered_map<String, String> mShaderContentMap;

		std::unordered_map<String, uint32_t> mMacroMap;
		std::unordered_map<String, ShaderConfig*> mShaderTechniqueMap;
		uint64_t mMacroValue = 1;
	};
}