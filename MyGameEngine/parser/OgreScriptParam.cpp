#include "OgreHeader.h"
#include "OgreScriptParam.h"
#include "OgreMaterial.h"
#include "OgreString.h"
#include "myutils.h"
#include "MaterialScriptParser.h"
#include "MaterialScriptParser.h"
#include "shaderManager.h"
#include "OgreTextureUnit.h"

class  CmdSceneBlend : public ParamCommand
{
public:
    String doGet(const void* target) const
    {
        return String();
    }
    void doSet(void* target, const String& val)
    {
        static_cast<OgreMaterialParam*>(target)->setSceneBlend(
            val);
    }
};

SceneBlendFactor parserBlendFactor(const std::string& val)
{
    static std::map<std::string, SceneBlendFactor> tmpmap =
    {
        {"zero", SBF_ZERO},
        {"one", SBF_ONE},
        {"dest_colour", SBF_DEST_COLOUR},
        {"source_colour", SBF_DEST_COLOUR}
    };
    auto itor = tmpmap.find(val);
    if (itor != tmpmap.end())
    {
        return itor->second;
    }
    assert(false);
    return SBF_ONE;
}
class CmdBlendFallback : public ParamCommand
{
public:
    String doGet(const void* target) const
    {
        return String();
    }
    void doSet(void* target, const String& val)
    {
        std::vector<String> aa = Ogre::StringUtil::split(val);

        SceneBlendFactor sbf0 = parserBlendFactor(aa[0]);
        SceneBlendFactor sbf1 = parserBlendFactor(aa[1]);
        static_cast<OgreMaterialParam*>(target)->setColourOpMultipassFallback(sbf0,
            sbf1);
    }
};

class  CmdDepthWrite : public ParamCommand
{
public:
    String doGet(const void* target) const
    {
        return String();
    }
    void doSet(void* target, const String& val)
    {
        static_cast<OgreMaterialParam*>(target)->setDepthWrite(
            val);
    }
};

class  CmdShader : public ParamCommand
{
public:
    String doGet(const void* target) const
    {
        return String();
    }
    void doSet(void* target, const String& val)
    {
        static_cast<OgreMaterialParam*>(target)->setShader(
            val);
    }
};



class CmdParent : public ParamCommand
{
public:
    String doGet(const void* target) const
    {
        return String();
    }
    void doSet(void* target, const String& val)
    {
        static_cast<OgreMaterialParam*>(target)->setInherit(val);
    }
};

class CmdTexture : public ParamCommand
{
public:
    String doGet(const void* target) const
    {
        return String();
    }
    void doSet(void* target, const String& val)
    {
        static_cast<OgreMaterialParam*>(target)->setTexture(val);
    }
};

class CmdShaderMacro : public ParamCommand
{
public:
    String doGet(const void* target) const
    {
        return String();
    }
    void doSet(void* target, const String& val)
    {
        static_cast<OgreMaterialParam*>(target)->setShaderMacro(val);
    }
};

class CmdAnimTexture: public ParamCommand
{
public:
    String doGet(const void* target) const
    {
        return String();
    }
    void doSet(void* target, const String& val)
    {
        static_cast<OgreMaterialParam*>(target)->setAnimTexture(val);
    }
};

class CmdScrollTexture : public ParamCommand
{
public:
    String doGet(const void* target) const
    {
        return String();
    }
    void doSet(void* target, const String& val)
    {
        static_cast<OgreMaterialParam*>(target)->setScrollTexture(val);
    }
};




OgreMaterialParam::OgreMaterialParam(Material* mat, MaterialScriptParser* parser)
{
    mMaterial = mat;
    mParser = parser;
    mShaderInfo.shaderName = "basic";

    initParameters();
}

OgreMaterialParam::~OgreMaterialParam()
{
    
}

void OgreMaterialParam::replaceVariables(std::string& val)
{
    if (val.find_first_of('$') != String::npos)
    {
        for (auto& pair : mVariablesMap)
        {
            val = Ogre::StringUtil::replaceAll(val, pair.first, pair.second);
        }
    }
}

void OgreMaterialParam::initParameters()
{
	if (createParamDictionary("OgreMaterialParam"))
	{
        ParamDictionary* dict = getParamDictionary();

        static CmdSceneBlend msSceneBlend;

        dict->addParameter(ParameterDef("scene_blend",
            "use blend mode.",
            PT_STRING),
            &msSceneBlend);

        
        static CmdBlendFallback mBlendFallback;

        dict->addParameter(ParameterDef("colour_op_multipass_fallback",
            "use blend mode.",
            PT_STRING),
            &mBlendFallback);

        
        static CmdDepthWrite msDepthWrite;

        dict->addParameter(ParameterDef("depth_write",
            "write depth or not.",
            PT_STRING),
            &msDepthWrite);

        
        static CmdShader msShader;

        dict->addParameter(ParameterDef("shader",
            "vertex shader filename.",
            PT_STRING),
            &msShader);

        
        static CmdParent   mParentConfig;

        dict->addParameter(ParameterDef("material_parent",
            "script parent.",
            PT_STRING),
            &mParentConfig);

        
        static CmdTexture  mTextureConfig;

        dict->addParameter(ParameterDef("texture",
            "texture config.",
            PT_STRING),
            &mTextureConfig);

        
        static CmdShaderMacro mShaderMacro;

        dict->addParameter(ParameterDef("shader_macro",
            "shader macro.",
            PT_STRING),
            &mShaderMacro);

        static CmdAnimTexture mAnimTexture;
        dict->addParameter(ParameterDef("anim_texture",
            "animation texture",
            PT_STRING),
            &mAnimTexture);

        static CmdScrollTexture mScrollTexture;
        dict->addParameter(ParameterDef("scroll_anim",
            "scroll texture",
            PT_STRING),
            &mScrollTexture);
	}
}

void OgreMaterialParam::setSceneBlend(const std::string& val)
{
    if (val == "alpha_blend")
    {
        mBlendState.sourceFactor = Ogre::SBF_SOURCE_ALPHA;
        mBlendState.destFactor = Ogre::SBF_ONE_MINUS_SOURCE_ALPHA;
        mBlendState.sourceFactorAlpha = Ogre::SBF_SOURCE_ALPHA;
        mBlendState.destFactorAlpha = Ogre::SBF_ONE_MINUS_SOURCE_ALPHA;
    }
    else if (val == "add")
    {
        mBlendState.sourceFactor = Ogre::SBF_ONE;
        mBlendState.destFactor = Ogre::SBF_ONE;
        mBlendState.sourceFactorAlpha = SBF_ONE;
        mBlendState.destFactorAlpha = SBF_ONE;
    }
}

void OgreMaterialParam::setColourOpMultipassFallback(SceneBlendFactor sourceFactor,
    SceneBlendFactor destFactor)
{
   // mBlendState.sourceFactorAlpha = sourceFactor;
   // mBlendState.destFactorAlpha = destFactor;
}

void OgreMaterialParam::setColourOperationEx
(
    LayerBlendOperationEx op,
    LayerBlendSource source1,
    LayerBlendSource source2,

    const ColourValue& arg1,
    const ColourValue& arg2,

    Real manualBlend)
{
    /*mBlendState.operation = op;
    mBlendState.source1 = source1;
    mBlendState.source2 = source2;
    mBlendState.colourArg1 = arg1;
    mBlendState.colourArg2 = arg2;
    mBlendState.factor = manualBlend;*/
}

void OgreMaterialParam::setDepthWrite(const std::string& val)
{
    if (val == "off")
    {
        mMaterial->setWriteDepth(false);
    }
}

void OgreMaterialParam::setShader(const std::string& val)
{
    mShaderInfo.shaderName = val;
}


void OgreMaterialParam::setInherit(const std::string& val)
{
    OgreMaterialParam* other = mParser->getMaterialParam(val);

    mParamPairs = other->mParamPairs;
    mUnitParamPairs = other->mUnitParamPairs;
}

void OgreMaterialParam::setTexture(const std::string& val)
{
    TextureProperty tp;
    std::vector<std::string> aa = Ogre::StringUtil::split(val);

    bool video = false;

    aa[0] = UTF8ToGBK(aa[0].c_str());

    if (aa.size() > 1)
    {
        if(aa[1] == "cubic")
            tp._texType = TEX_TYPE_CUBE_MAP;
        else if (aa[1] == "video")
        {
            video = true;
            mMaterial->setVideoName(aa[0]);
        }
    }

    if (!video)
    {
        mMaterial->addTexture(aa[0], &tp);
    }
    
}

void OgreMaterialParam::setAnimTexture(const String& val)
{
    std::vector<std::string> aa = Ogre::StringUtil::split(val);

    if (aa.size() >= 3)
    {
        float duration = Ogre::StringConverter::parseReal(aa.back(), 1.0f);
        aa.pop_back();
        mMaterial->addAnimTexture(aa, duration);
    }
    else
    {
        WARNING_LOG("anim texture param error in material %s", 
            mMaterial->getName().c_str());
    }
}

void OgreMaterialParam::setScrollTexture(const String& val)
{
    std::vector<std::string> aa = Ogre::StringUtil::split(val);

    if (aa.size() != 2)
    {
        WARNING_LOG("scroll texture param error in material %s",
            mMaterial->getName().c_str());
    }
    else
    {
        float u = Ogre::StringConverter::parseReal(aa[0]);
        float v = Ogre::StringConverter::parseReal(aa[1]);

        auto unit = mMaterial->getTextureUnit(0);

        unit->setTextureScroll(u, v);
    }
}

void OgreMaterialParam::setShaderMacro(const std::string& val)
{
    std::vector<std::string> aa = Ogre::StringUtil::split(val);

    for (auto& macro : aa)
    {
        mShaderInfo.shaderMacros.emplace_back();
        mShaderInfo.shaderMacros.back().first = macro;
        mShaderInfo.shaderMacros.back().second = "1";
    }
}

void OgreMaterialParam::addVariable(const std::string& variable)
{
    StringVector aa = Ogre::StringUtil::split(variable);
    assert(aa.size() == 2);
    aa[1] = string_trim(aa[1]);
    mVariablesMap[aa[0]] = aa[1];
}

void OgreMaterialParam::compile()
{
    if (!mVariablesMap.empty())
    {
        for (auto& obj : mParamPairs)
        {
            replaceVariables(obj.second);
        }

        for (auto& unit : mUnitParamPairs)
        {
            for (auto& obj : unit)
            {
                replaceVariables(obj.second);
            }
        }
    }

    for (auto& obj : mParamPairs)
    {
        setParameter(obj.first, obj.second);
    }

    for (auto& unit : mUnitParamPairs)
    {
        for (auto& obj : unit)
        {
            setParameter(obj.first, obj.second);
        }
    }
    mMaterial->setBlendState(mBlendState);

    mMaterial->addShader(mShaderInfo);

    for (auto& pair : mShaderInfo.shaderMacros)
    {
        ShaderManager::getSingleton().addMacro(pair.first);
    }
}

void OgreMaterialParam::addParam(const std::string& key, const std::string& value)
{
    if (key == "set")
    {
        addVariable(value);
        return;
    }

    if (key == "material_parent")
    {
        setInherit(value);
        return;
    }
    mParamPairs.emplace_back();
    mParamPairs.back().first = key;
    mParamPairs.back().second = value;
}

void OgreMaterialParam::addUnitParam(
    const std::string& key, const std::string& value, uint32_t index)
{
    if (key == "set")
    {
        addVariable(value);
        return;
    }
    if (index >= mUnitParamPairs.size())
        mUnitParamPairs.emplace_back();

    ParamPairs& paramPairs = mUnitParamPairs.back();
    paramPairs.emplace_back();
    paramPairs.back().first = key;
    paramPairs.back().second = value;
}
