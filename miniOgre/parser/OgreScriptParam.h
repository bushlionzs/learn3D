#pragma once
#include "OgreStringInterface.h"
#include "shader.h"
#include "texture.h"
#include "OgreBlendMode.h"

class MaterialScriptParser;

class OgreMaterialParam: public StringInterface
{
public:
	OgreMaterialParam(Material* mat, MaterialScriptParser* parser);
	~OgreMaterialParam();

	void setSceneBlend(const std::string& val);
	void setColourOpMultipassFallback(SceneBlendFactor sourceFactor, 
		SceneBlendFactor destFactor);
	void setColourOperationEx(
		LayerBlendOperationEx op,
		LayerBlendSource source1 = LBS_TEXTURE,
		LayerBlendSource source2 = LBS_CURRENT,

		const ColourValue& arg1 = ColourValue::White,
		const ColourValue& arg2 = ColourValue::White,

		Real manualBlend = 0.0);
	void setDepthWrite(const std::string& val);
	void setShader(const std::string& val);
	void setInherit(const std::string& val);
	void setTexture(const std::string& val);
	void setTextureAddrMode(const std::string& val);
	void setPbrTexture(TextureTypePbr pbrtype, const std::string& val);
	void setAnimTexture(const String& val);
	void setRotateTexture(const String& val);
	void setScrollTexture(const String& val);
	void setCullMode(const String& val);
	void setShaderMacro(const std::string& val);
	void addParam(const std::string& key, const std::string& value);
	void addUnitParam(const std::string& key, const std::string& value, uint32_t index);
	void addVariable(const std::string& variable);

	void compile();
private:
	void initParameters();
	void replaceVariables(std::string& val);
public:
	typedef std::vector<std::pair<std::string, std::string>> ParamPairs;
	Material* mMaterial;

	ShaderInfo mShaderInfo;

	Ogre::ColourBlendState mBlendState;

	ParamPairs mParamPairs;
	std::vector<ParamPairs> mUnitParamPairs;
	std::map<std::string, std::string> mVariablesMap;

	MaterialScriptParser* mParser;

	uint32_t mTexIndex = 0;
};