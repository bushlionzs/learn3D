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

	class ShaderManager : public Ogre::Singleton<ShaderManager>, public ScriptLoader
	{
	public:
		ShaderManager();
		~ShaderManager();

        virtual String getSuffix();

        virtual void parseScript(ResourceInfo* res, const String& groupName);

        virtual Real getLoadingOrder(void) const;

		ShaderPrivateInfo* getShader(
			const String& name, 
			EngineType renderSystem);

		String* getShaderContent(const String& name);

		void addMacro(const String& name);
		int32_t getMacroIndex(const String& name);
	private:
		void parseShaderImpl(const String& content);
		bool readShaderUnit(
			std::stringstream& ss,
			ShaderFormat* shaderFormat);
		void addShader(const String& name, ShaderFormat* sf);
	private:
		std::unordered_map<String, ShaderFormat*> mShaderMap;
		std::unordered_map<String, String> mShaderContentMap;

		std::unordered_map<String, uint32_t> mMacroMap;

		uint64_t mMacroValue = 1;
	};
}