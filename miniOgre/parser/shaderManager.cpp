#include "OgreHeader.h"
#include "shaderManager.h"
#include "ScriptParserUtil.h"
#include "myutils.h"
#include "OgreString.h"
#include "OgreResourceManager.h"
#include "OgreMemoryStream.h"
#include "platform_file.h"
namespace Ogre {

	template<> ShaderManager* Ogre::Singleton<ShaderManager>::msSingleton = 0;

	ShaderManager::ShaderManager()
	{

	}

	ShaderManager::~ShaderManager()
	{

	}

	std::vector<String> ShaderManager::getSuffix()
	{
		return { ".shader" };
	}

	void ShaderManager::parseScript(ResourceInfo* res, const String& groupName)
	{
		std::shared_ptr<MemoryDataStream> stream = std::make_shared<MemoryDataStream>(res);
		std::string content = stream->getAsString();
		parseShaderImpl(content);
	}

	void ShaderManager::parseShaderImpl(const String& content)
	{
		std::stringstream ss;
		ss << content;

		std::string linePart;
		ss >> linePart;

		std::string name;

		while (!ss.eof()) {
			// Skip commented lines
			if (linePart == partComment) {
				NextAfterNewLine(ss, linePart);
				continue;
			}

			if (linePart == "shader")
			{
				ss >> name;
				if (name == "basic")
				{
					int kk = 0;
				}
				ShaderConfig* shaderInfo = new ShaderConfig;
				addShader(name, shaderInfo);
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
						readShaderUnit(ss, shaderInfo);
					}
					else if (linePart == "technique") {
						readTechnique(ss, shaderInfo);
					}


					ss >> linePart;
				}
			}
			else
			{
				ss >> linePart;
			}
			
		}
	}

	bool ShaderManager::readShaderUnit(
		std::stringstream& ss,
		ShaderConfig* shaderInfo)
	{
		if (shaderInfo->techniques.empty())
		{
			shaderInfo->techniques.emplace_back();
		}
		ShaderTechnique& technique = shaderInfo->techniques.back();
		ShaderFormat* shaderFormat = &technique.shaderFormat;
		static std::map<String, EngineType> enginetype_map =
		{
			{"directx", EngineType_Dx12},
			{"vulkan", EngineType_Vulkan}
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
			if (isComment(linePart)) 
			{
				SkipLine(ss);
				ss >> linePart;
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
					shaderFormat->shaderInfo[EngineType_Dx12].privateInfo.vertexShaderName = aa[0];
					shaderFormat->shaderInfo[EngineType_Dx12].privateInfo.vertexShaderEntryPoint = aa[1];
				}
			}
			else if (pair.first == "frag_shader")
			{
				shaderFormat->shaderInfo[enginetype].privateInfo.fragShaderName = aa[0];
				shaderFormat->shaderInfo[enginetype].privateInfo.fragShaderEntryPoint = aa[1];
				if (enginetype == EngineType_Dx12)
				{
					shaderFormat->shaderInfo[EngineType_Dx12].privateInfo.fragShaderName = aa[0];
					shaderFormat->shaderInfo[EngineType_Dx12].privateInfo.fragShaderEntryPoint = aa[1];
				}
			}
			else if (pair.first == "compute_shader")
			{
				shaderFormat->shaderInfo[enginetype].privateInfo.computeShaderName = aa[0];
				shaderFormat->shaderInfo[enginetype].privateInfo.computeShaderEntryPoint = aa[1];
				if (enginetype == EngineType_Dx12)
				{
					shaderFormat->shaderInfo[EngineType_Dx12].privateInfo.computeShaderName = aa[0];
					shaderFormat->shaderInfo[EngineType_Dx12].privateInfo.computeShaderEntryPoint = aa[1];
				}
			}
			else if (pair.first == "geometry_shader")
			{
				shaderFormat->shaderInfo[enginetype].privateInfo.geometryShaderName = aa[0];
				shaderFormat->shaderInfo[enginetype].privateInfo.geometryShaderEntryPoint = aa[1];
				if (enginetype == EngineType_Dx12)
				{
					shaderFormat->shaderInfo[EngineType_Dx12].privateInfo.geometryShaderName = aa[0];
					shaderFormat->shaderInfo[EngineType_Dx12].privateInfo.geometryShaderEntryPoint = aa[1];
				}
			}
			else
			{
				assert_invariant(false);
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
		EngineType renderSystem,
		const char* technique)
	{
		auto itor = mShaderTechniqueMap.find(name);

		if (itor != mShaderTechniqueMap.end())
		{
			ShaderConfig* shaderInfo = itor->second;
			if (technique == nullptr)
			{
				return &shaderInfo->techniques[0].shaderFormat.shaderInfo[renderSystem].privateInfo;
			}
			else
			{
				for (auto& obj : shaderInfo->techniques)
				{
					if (obj.name == technique)
					{
						return &obj.shaderFormat.shaderInfo[renderSystem].privateInfo;
					}
				}
			}
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

		auto res = ResourceManager::getSingleton().getResourceInfo(name);

		if (res == nullptr)
		{
			return nullptr;
		}

		CommonUtils::get_file_content(res->_fullname.c_str(), mShaderContentMap[name]);

		itor = mShaderContentMap.find(name);

		return &itor->second;
	}


	bool ShaderManager::readTechnique(std::stringstream& ss, ShaderConfig* shaderInfo)
	{
		shaderInfo->techniques.emplace_back();
		ShaderTechnique& technique = shaderInfo->techniques.back();
		ShaderFormat* shaderFormat = &technique.shaderFormat;
		ss >> technique.name;
		std::string linePart;
		std::map<String, String> keyvalueMap;

		while (linePart != partBlockStart)
		{
			SkipLine(ss);
			ss >> linePart;
		}

		ss >> linePart;
		while (linePart != partBlockEnd) {
			// Skip commented lines
			if (isComment(linePart)) {
				SkipLine(ss);
				ss >> linePart;
				continue;
			}

			
			std::string val = SkipLine(ss);
			Ogre::StringUtil::trim(val);
			if (!linePart.empty() && !val.empty())
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
				shaderFormat->shaderInfo[EngineType_Dx12].privateInfo.vertexShaderName = aa[0];
				shaderFormat->shaderInfo[EngineType_Dx12].privateInfo.vertexShaderEntryPoint = aa[1];
				shaderFormat->shaderInfo[EngineType_Vulkan].privateInfo.vertexShaderName = aa[0];
				shaderFormat->shaderInfo[EngineType_Vulkan].privateInfo.vertexShaderEntryPoint = aa[1];
				
			}
			else if (pair.first == "frag_shader")
			{
			    shaderFormat->shaderInfo[EngineType_Dx12].privateInfo.fragShaderName = aa[0];
			    shaderFormat->shaderInfo[EngineType_Dx12].privateInfo.fragShaderEntryPoint = aa[1];
				shaderFormat->shaderInfo[EngineType_Vulkan].privateInfo.fragShaderName = aa[0];
				shaderFormat->shaderInfo[EngineType_Vulkan].privateInfo.fragShaderEntryPoint = aa[1];
			}
			else if (pair.first == "compute_shader")
			{	
			    shaderFormat->shaderInfo[EngineType_Dx12].privateInfo.computeShaderName = aa[0];
			    shaderFormat->shaderInfo[EngineType_Dx12].privateInfo.computeShaderEntryPoint = aa[1];
				shaderFormat->shaderInfo[EngineType_Vulkan].privateInfo.computeShaderName = aa[0];
				shaderFormat->shaderInfo[EngineType_Vulkan].privateInfo.computeShaderEntryPoint = aa[1];
			}
			else if (pair.first == "geometry_shader")
			{	
				shaderFormat->shaderInfo[EngineType_Dx12].privateInfo.geometryShaderName = aa[0];
				shaderFormat->shaderInfo[EngineType_Dx12].privateInfo.geometryShaderEntryPoint = aa[1];
				shaderFormat->shaderInfo[EngineType_Vulkan].privateInfo.geometryShaderName = aa[0];
				shaderFormat->shaderInfo[EngineType_Vulkan].privateInfo.geometryShaderEntryPoint = aa[1];
			}
			else
			{
				assert_invariant(false);
			}
		}



		return true;
	}

	void ShaderManager::addShader(const String& name, ShaderConfig* shaderInfo)
	{
		auto itor = mShaderTechniqueMap.find(name);
		if (itor != mShaderTechniqueMap.end())
		{
			assert_invariant(false);
		}

		mShaderTechniqueMap[name] = shaderInfo;
	}

	bool ShaderManager::isComment(const String& linePart)
	{
		if (linePart.size() >= 2)
		{
			if (linePart[0] == '/' && linePart[1] == '/')
			{
				return true;
			}
		}
		return false;
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
			assert_invariant(false);
		}

		return itor->second;
	}

}

