#include "OgreHeader.h"
#include "shaderManager.h"
#include "ScriptParserUtil.h"
#include "myutils.h"
#include "OgreString.h"
#include "OgreResourceManager.h"

namespace Ogre {

	template<> ShaderManager* Ogre::Singleton<ShaderManager>::msSingleton = 0;

	ShaderManager::ShaderManager()
	{

	}

	ShaderManager::~ShaderManager()
	{

	}

	String ShaderManager::getSuffix()
	{
		return ".shader";
	}

	void ShaderManager::parseScript(DataStreamPtr& stream, const String& groupName)
	{
		std::string content = stream->getAsString();
		parseShaderImpl(content);
	}

	void ShaderManager::parseShaderImpl(const String& content)
	{
		std::stringstream ss;
		ss << content;

		std::string linePart;
		ss >> linePart;

		std::string shadername;


		

		while (!ss.eof()) {
			// Skip commented lines
			if (linePart == partComment) {
				NextAfterNewLine(ss, linePart);
				continue;
			}
			if (linePart != "shader") {
				ss >> linePart;
				continue;
			}

			ss >> shadername;

			ShaderFormat* shaderFormat = new ShaderFormat;
			addShader(shadername, shaderFormat);
			do
			{
				ss >> linePart;
			} while (linePart != partBlockStart);

			ss >> linePart;

			while (linePart != partBlockEnd) {
				// Skip commented lines
				if (linePart == partComment) {
					SkipLine(ss);
					continue;
				}

				if (linePart == "shader_unit") {
					readShaderUnit(ss, shaderFormat);
				}
				

				ss >> linePart;
			}
		}
	}

	bool ShaderManager::readShaderUnit(
		std::stringstream& ss,
		ShaderFormat* shaderFormat)
	{
		static std::map<String, EngineType> enginetype_map =
		{
			{"directx", EngineType_Dx12},
			{"vulkan", EngineType_Vulkan}
		};

		static std::map<String, Ogre::ShaderType> shadertype_map =
		{
			{"vertex_shader", VertexShader},
			{"frag_shader", PixelShader}
		};

		std::string linePart;
		ss >> linePart;

		if (linePart != partBlockStart) {
			OGRE_EXCEPT(Exception::ERR_INVALIDPARAMS, "shader unit error");
		}

		ss >> linePart;

		EngineType enginetype = EngineType_Dx12;
		std::map<String, String> keyvalueMap;
		while (linePart != partBlockEnd) {
			// Skip commented lines
			if (linePart == partComment) {
				SkipLine(ss);
				continue;
			}

			std::string val = SkipLine(ss);
			Ogre::StringUtil::trim(val);

			if (linePart == "shader_type")
			{
				enginetype = enginetype_map[val];
			}
			else
			{
				keyvalueMap[linePart] = val;
			}
			
			ss >> linePart;
		}

		for (auto& pair : keyvalueMap)
		{
			std::vector<String> aa = Ogre::StringUtil::split(pair.second);
			if (pair.first == "vertex_shader")
			{
				shaderFormat->shaderInfo[enginetype].privateInfo.vertexShaderName = aa[0];
				shaderFormat->shaderInfo[enginetype].privateInfo.vertexShaderEntryPoint = aa[1];

				if (enginetype == EngineType_Dx12)
				{
					shaderFormat->shaderInfo[EngineType_Dx11].privateInfo.vertexShaderName = aa[0];
					shaderFormat->shaderInfo[EngineType_Dx11].privateInfo.vertexShaderEntryPoint = aa[1];
				}
			}
			else if (pair.first == "frag_shader")
			{
				shaderFormat->shaderInfo[enginetype].privateInfo.fragShaderName = aa[0];
				shaderFormat->shaderInfo[enginetype].privateInfo.fragShaderEntryPoint = aa[1];
				if (enginetype == EngineType_Dx12)
				{
					shaderFormat->shaderInfo[EngineType_Dx11].privateInfo.fragShaderName = aa[0];
					shaderFormat->shaderInfo[EngineType_Dx11].privateInfo.fragShaderEntryPoint = aa[1];
				}
			}
			
		}
		return true;
	}

	Real ShaderManager::getLoadingOrder(void) const
	{
		return 2.0f;
	}

	ShaderPrivateInfo* ShaderManager::getShader(
		const String& name,
		EngineType renderSystem)
	{
		auto itor = mShaderMap.find(name);

		if (itor != mShaderMap.end())
		{
			return &itor->second->shaderInfo[renderSystem].privateInfo;
		}

		return nullptr;
	}

	String* ShaderManager::getShaderContent(const String& name)
	{
		auto itor = mShaderContentMap.find(name);

		if (itor != mShaderContentMap.end())
		{
			return &itor->second;
		}

		auto res = ResourceManager::getSingleton().getResource(name);

		if (res == nullptr)
		{
			return nullptr;
		}

		mShaderContentMap[name] = getContentFromFile(res->_fullname.c_str());

		itor = mShaderContentMap.find(name);

		return &itor->second;
	}

	void ShaderManager::addShader(const String& name, ShaderFormat* sf)
	{
		auto itor = mShaderMap.find(name);
		if (itor != mShaderMap.end())
		{
			assert(false);
		}

		mShaderMap[name] = sf;
	}

	void ShaderManager::addMacro(const String& name)
	{
		auto itor = mMacroMap.find(name);

		if (itor == mMacroMap.end())
		{
			mMacroMap[name] = mMacroValue;

			mMacroValue <<= 1;
		}
	}

	int32_t ShaderManager::getMacroIndex(const String& name)
	{
		auto itor = mMacroMap.find(name);

		if (itor == mMacroMap.end())
		{
			assert(false);
		}

		return itor->second;
	}
}

