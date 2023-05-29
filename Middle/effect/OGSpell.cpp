#include "OgreHeader.h"
#include "OGSpell.h"
#include "OGSpellImpactModule.h"
#include "OGSpellRibandModule.h"
#include "OGSpellSceneLightModule.h"
#include "OGSpellBulletFlowModule.h"
#include "OGSpellModelModule.h"
#include "OGSpellSerializer.h"
#include "OgreString.h"
// ogre header
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>
#include <OgreStringConverter.h>
#include "OgreMaterial.h"

namespace Orphigine	
{

	Spell::CmdAnimationName Spell::msAnimationNameCmd;
	Spell::CmdBreakTime Spell::msBreakTimeCmd;
	Spell::CmdHitTime Spell::msHitTimeCmd;
	Spell::CmdShakeTime Spell::msShakeTimeCmd;
	Spell::CmdRepeatEffect Spell::msRepeatEffectCmd;
	int	Spell::mSkillIdIndex=0;

	//////////////////////////////////////////////////////////////////////////
	Spell::Spell(const String &skillName) :mTemplateSkillName(skillName),mId(++mSkillIdIndex)
		,mRepeatEffect(false)
	{
		mHitTimeArray.push_back(-1.0f);
		mBreakTimeArray.push_back(-1.0f);
		mShakeTimeArray.push_back(-1.0f);

		mAnimationEffectInfos.clear();
		mAnimationRibbons.clear();
		mAnimationSceneLightInfos.clear();
		mAnimationSounds.clear();
		mAnimationBulletFlows.clear();
		mSkillModelElements.clear();

		initParamDictionary();

		m_userData = NULL;
		mPriority = 3;

		mRotation = Ogre::Quaternion::IDENTITY;
	}
	//---------------------------------------------------------------------
	Spell::~Spell()
	{
		removeAllAnimationEffectInfos();
		removeAllAnimationRibbons();
		removeAllAnimationSounds();
		removeAllAnimationSceneLightInfos();
		removeAllAnimationBulletFlows();
		removeAllSkillModelElement();

	}
	//---------------------------------------------------------------------
	bool Spell::initParamDictionary(void)
	{
		if (createParamDictionary("Skill"))
		{
			Ogre::ParamDictionary* dict = getParamDictionary();			

			dict->addParameter(Ogre::ParameterDef("Animation", 
				"name of animation.",
				Ogre::PT_STRING),&msAnimationNameCmd);	  

			dict->addParameter(Ogre::ParameterDef("BreakTime", 
				"the break time of skill.",
				Ogre::PT_STRING),&msBreakTimeCmd);	  

			dict->addParameter(Ogre::ParameterDef("HitTime", 
				"the hit time of skill.",
				Ogre::PT_STRING),&msHitTimeCmd);	  

			dict->addParameter(Ogre::ParameterDef("ShakeTime", 
				"the shake time of skill.",
				Ogre::PT_STRING),&msShakeTimeCmd);	 

			dict->addParameter(Ogre::ParameterDef("RepeatEffect", 
				"whether recreate effect when the animation is loop.",
				Ogre::PT_BOOL),&msRepeatEffectCmd);	  

			return true;
		}

		return false;
	}
	//---------------------------------------------------------------------
	Spell & Spell::operator = (const Spell &rhs)
	{
		removeAllAnimationEffectInfos();

		// Copy effect infos
		unsigned int i;
		for(i = 0; i < rhs.getNumAnimationEffectInfos(); ++i)
		{
			SpellImpactModule *rhsAEI = rhs.getAnimationEffectInfo(i);
			SpellImpactModule *newAEI = addAnimationEffectInfo();

			assert ( rhsAEI && newAEI );

			//	rhsAEI->copyParametersTo(newAEI);
			rhsAEI->copyParameters(*newAEI);
		}

		removeAllAnimationRibbons();

		// copy ribbons
		for(i = 0; i < rhs.getNumAnimationRibbons(); ++i)
		{
			SpellRibbonModule *rhsAEI = rhs.getAnimationRibbon(i);
			SpellRibbonModule *newAEI = addAnimationRibbon();

			assert ( rhsAEI && newAEI );

			//	rhsAEI->copyParametersTo(newAEI);
			rhsAEI->copyParameters(*newAEI);
		}

		removeAllAnimationSounds();

		// copy sounds
		for(i = 0; i < rhs.getNumAnimationSounds(); ++i)
		{
			SpellSoundModule *rhsAEI = rhs.getAnimationSound(i);
			SpellSoundModule *newAEI = addAnimationSound();

			assert ( rhsAEI && newAEI );

			//rhsAEI->copyParametersTo(newAEI);
			rhsAEI->copyParameters(*newAEI);
		}

		removeAllAnimationSceneLightInfos();

		// Copy SceneLight infos
		for(i = 0; i < rhs.getNumAnimationSceneLightInfos(); ++i)
		{
			SpellSceneLightModule *rhsAEI = rhs.getAnimationSceneLightInfo(i);
			SpellSceneLightModule *newAEI = addAnimationSceneLightInfo();

			assert ( rhsAEI && newAEI );

			//  rhsAEI->copyParametersTo(newAEI);
			rhsAEI->copyParameters(*newAEI);
		}

		removeAllAnimationBulletFlows();
		// Copy BulletFlow infos
		for (i = 0;i < rhs.getNumAnimationBulletFlows();i ++)
		{
			SpellBulletFlowModule* rhsABF = rhs.getAnimationBulletFlow(i);
			SpellBulletFlowModule* newABF = addAnimationBulletFlow();

			assert(rhsABF && newABF && "Skill::operator =");

			rhsABF->copyParameters(*newABF);
		}

		removeAllSkillModelElement();
		// Copy SkillModelElement infos
		for (i = 0;i < rhs.getNumSkillModelElement();i ++)
		{
			SpellModelModule* rhsSME = rhs.getSkillModelElement(i);
			SpellModelModule* newSME = addSkillModelElement();

			assert(rhsSME && newSME && "创建失败技能组件 Skill::operator =");
			rhsSME->copyAttributesTo(*newSME);
		}

		// copy skill parameter
		//	rhs.copyParametersTo(this);
		rhs.copyParameters(this);

		return *this;
	}
	Spell* Spell::Clone()
	{
		Spell* pNewSkill = OGRE_NEW Spell(mTemplateSkillName);
		*pNewSkill = *this;
		return pNewSkill;
	}
	//---------------------------------------------------------------------
	SpellImpactModule* Spell::addAnimationEffectInfo(void)
	{
		SpellImpactModule *effectInfo = new SpellImpactModule();
		assert (effectInfo);

		mAnimationEffectInfos.push_back(effectInfo);

		return effectInfo;
	}
	//---------------------------------------------------------------------
	SpellImpactModule* Spell::getAnimationEffectInfo(unsigned short index) const
	{
		assert(index < mAnimationEffectInfos.size() && "Animation Effect Info index out of bounds!");
		return mAnimationEffectInfos[index];
	}
	//---------------------------------------------------------------------
	unsigned short Spell::getNumAnimationEffectInfos(void) const
	{
		return static_cast<unsigned short>( mAnimationEffectInfos.size() );
	}
	//---------------------------------------------------------------------
	void Spell::removeAnimationEffectInfo(unsigned short index)
	{
		assert(index < mAnimationEffectInfos.size() && "Animation Effect Info index out of bounds!");
		AnimationEffectInfos::iterator ai = mAnimationEffectInfos.begin() + index;

		if (*ai)
		{
			delete *ai;
			*ai = NULL;
		}

		mAnimationEffectInfos.erase(ai);
	}
	//---------------------------------------------------------------------
	void Spell::removeAllAnimationEffectInfos(void)
	{
		/*for (unsigned short i=0; i<getNumAnimationEffectInfos(); ++i )
		{
		removeAnimationEffectInfo(i);
		}
		mAnimationEffectInfos.clear();*/
		for ( AnimationEffectInfos::iterator i = mAnimationEffectInfos.begin(); i != mAnimationEffectInfos.end(); ++i )
		{
			if (*i)
			{
				delete *i;
				*i = NULL;
			}
		}
		mAnimationEffectInfos.clear();
	}
	//---------------------------------------------------------------------
	SpellRibbonModule* Spell::addAnimationRibbon(void)
	{
		SpellRibbonModule *ribbon = new SpellRibbonModule();
		assert (ribbon);

		mAnimationRibbons.push_back(ribbon);

		return ribbon;
	}
	//---------------------------------------------------------------------
	SpellRibbonModule* Spell::getAnimationRibbon(unsigned short index) const
	{
		assert(index < mAnimationRibbons.size() && "Animation ribbon index out of bounds!");
		return mAnimationRibbons[index];
	}
	//---------------------------------------------------------------------
	unsigned short Spell::getNumAnimationRibbons(void) const
	{
		return static_cast<unsigned short>( mAnimationRibbons.size() );
	}
	//---------------------------------------------------------------------
	void Spell::removeAnimationRibbon(unsigned short index)
	{
		assert(index < mAnimationRibbons.size() && "Animation ribbon index out of bounds!");
		AnimationRibbons::iterator ai = mAnimationRibbons.begin() + index;

		if (*ai)
		{
			delete *ai;
			*ai = NULL;
		}

		mAnimationRibbons.erase(ai);
	}
	//---------------------------------------------------------------------
	void Spell::removeAllAnimationRibbons(void)
	{
		/*for (unsigned short i=0; i<getNumAnimationRibbons(); ++i )
		{
		removeAnimationRibbon(i);
		}*/
		for ( AnimationRibbons::iterator i = mAnimationRibbons.begin(); i != mAnimationRibbons.end(); ++i )
		{
			if (*i)
			{
				delete *i;
				*i = NULL;
			}
		}
		mAnimationRibbons.clear();
	}
	//---------------------------------------------------------------------
	SpellSoundModule* Spell::addAnimationSound(void)
	{
		SpellSoundModule *sound = new SpellSoundModule();
		assert (sound);

		mAnimationSounds.push_back(sound);

		return sound;
	}
	//---------------------------------------------------------------------
	SpellSoundModule* Spell::getAnimationSound(unsigned short index) const
	{
		assert(index < mAnimationSounds.size() && "Animation sound index out of bounds!");
		return mAnimationSounds[index];
	}
	//---------------------------------------------------------------------
	unsigned short Spell::getNumAnimationSounds(void) const
	{
		return static_cast<unsigned short>( mAnimationSounds.size() );
	}
	//---------------------------------------------------------------------
	void Spell::removeAnimationSound(unsigned short index)
	{
		assert(index < mAnimationSounds.size() && "Animation sound index out of bounds!");
		AnimationSounds::iterator ai = mAnimationSounds.begin() + index;

		if (*ai)
		{
			delete *ai;
			*ai = NULL;
		}

		mAnimationSounds.erase(ai);
	}
	//---------------------------------------------------------------------
	void Spell::removeAllAnimationSounds(void)
	{		
		for ( AnimationSounds::iterator i = mAnimationSounds.begin(); i != mAnimationSounds.end(); ++i )
		{
			if (*i)
			{
				delete *i;
				*i = NULL;
			}
		}
		mAnimationSounds.clear();
	}
	//---------------------------------------------------------------------
	SpellSceneLightModule* Spell::addAnimationSceneLightInfo(void)
	{
		SpellSceneLightModule *effectInfo = new SpellSceneLightModule();
		assert (effectInfo);

		mAnimationSceneLightInfos.push_back(effectInfo);

		return effectInfo;
	}
	//---------------------------------------------------------------------
	SpellSceneLightModule* Spell::getAnimationSceneLightInfo(unsigned short index) const
	{
		assert(index < mAnimationSceneLightInfos.size() && "Animation scene light Info index out of bounds!");
		return mAnimationSceneLightInfos[index];
	}
	//---------------------------------------------------------------------
	unsigned short Spell::getNumAnimationSceneLightInfos(void) const
	{
		return static_cast<unsigned short>( mAnimationSceneLightInfos.size() );
	}
	//---------------------------------------------------------------------
	void Spell::removeAnimationSceneLightInfo(unsigned short index)
	{
		assert(index < mAnimationSceneLightInfos.size() && "Animation scene light Info index out of bounds!");
		AnimationSceneLightInfos::iterator ai = mAnimationSceneLightInfos.begin() + index;

		if (*ai)
		{
			delete *ai;
			*ai = NULL;
		}

		mAnimationSceneLightInfos.erase(ai);
	}
	//---------------------------------------------------------------------
	void Spell::removeAllAnimationSceneLightInfos(void)
	{
		for ( AnimationSceneLightInfos::iterator i = mAnimationSceneLightInfos.begin(); i != mAnimationSceneLightInfos.end(); ++i )
		{
			if (*i)
			{
				delete *i;
				*i = NULL;
			}
		}
		mAnimationSceneLightInfos.clear();
	}

	//----------------------------------------------------------------------
	SpellBulletFlowModule* Spell::addAnimationBulletFlow( void )
	{
		SpellBulletFlowModule* tmpAnimationBulletFlow = new SpellBulletFlowModule();
		mAnimationBulletFlows.push_back(tmpAnimationBulletFlow);

		return tmpAnimationBulletFlow;
	}

	SpellBulletFlowModule* Spell::getAnimationBulletFlow( unsigned short index ) const
	{
		assert(index < mAnimationBulletFlows.size() && "越界 Skill::getAnimationBulletFlow");

		return mAnimationBulletFlows[index];
	}

	unsigned short Spell::getNumAnimationBulletFlows( void ) const
	{
		return mAnimationBulletFlows.size();
	}

	void Spell::removeAnimationBulletFlow( unsigned short index )
	{
		assert(index < mAnimationBulletFlows.size() && "越界 Skill::removeAnimationBulletFlow");

		AnimationBulletFlows::iterator iter = mAnimationBulletFlows.begin() + index;

		delete (*iter);
		(*iter) = NULL;

		mAnimationBulletFlows.erase(iter);
	}

	void Spell::removeAllAnimationBulletFlows( void )
	{
		AnimationBulletFlows::iterator iter;
		for (iter = mAnimationBulletFlows.begin();iter != mAnimationBulletFlows.end(); ++iter)
		{
			delete (*iter);
			(*iter) = NULL;

			//mAnimationBulletFlows.erase(iter);
		}
		mAnimationBulletFlows.clear();
	}

	//---------------------------------------------------------------------
	SpellModelModule* Spell::addSkillModelElement( void )
	{
		SpellModelModule* tmpSkillModelElement = new SpellModelModule();
		mSkillModelElements.push_back(tmpSkillModelElement);

		return tmpSkillModelElement;
	}

	SpellModelModule* Spell::getSkillModelElement( unsigned short index ) const
	{
		assert(index < (unsigned short)mSkillModelElements.size() && "越界 Skill::getSkillModelElement");

		return mSkillModelElements[index];
	}

	unsigned short Spell::getNumSkillModelElement( void ) const
	{
		return (unsigned short)mSkillModelElements.size();
	}

	void Spell::removeSkillModelElement( unsigned short index )
	{
		assert(index < (unsigned short)mSkillModelElements.size() && "越界 Skill::getSkillModelElement");
		SkillModelElements::iterator iter = mSkillModelElements.begin() + index;

		delete (*iter);
		(*iter) = NULL;

		mSkillModelElements.erase(iter);
	}

	void Spell::removeAllSkillModelElement( void )
	{
		SkillModelElements::iterator iter;
		for (iter = mSkillModelElements.begin();iter != mSkillModelElements.end();iter ++)
		{
			delete (*iter);
			(*iter) = NULL;
		}

		mSkillModelElements.clear();
	}

	//---------------------------------------------------------------------
	void Spell::setBreakTimeFromString(const String &breakTimeStr)
	{
		mBreakTimeArray.clear();

		Ogre::StringVector breakTimes = Ogre::StringUtil::split(breakTimeStr);

		for (size_t i=0; i<breakTimes.size(); ++i)
		{
			mBreakTimeArray.push_back( Ogre::StringConverter::parseReal(breakTimes[i]) );
		}
	}
	//---------------------------------------------------------------------
	String Spell::getBreakTimeString(void) const
	{
		String resultStr("");

		for (size_t i=0; i<mBreakTimeArray.size(); ++i)
		{
			resultStr += Ogre::StringConverter::toString(mBreakTimeArray[i]);
			resultStr += " ";
		}

		return resultStr;
	}
	//---------------------------------------------------------------------
	unsigned short Spell::getNumBreakTimes(void)
	{
		return static_cast<unsigned short>(mBreakTimeArray.size());
	}
	//---------------------------------------------------------------------
	void Spell::setHitTimeFromString(const String &hitTimeStr)
	{
		mHitTimeArray.clear();

		Ogre::StringVector hitTimes = Ogre::StringUtil::split(hitTimeStr);

		for (size_t i=0; i<hitTimes.size(); ++i)
		{
			mHitTimeArray.push_back( Ogre::StringConverter::parseReal(hitTimes[i]) );
		}
	}
	//---------------------------------------------------------------------
	String Spell::getHitTimeString(void) const
	{
		String resultStr("");

		for (size_t i=0; i<mHitTimeArray.size(); ++i)
		{
			resultStr += Ogre::StringConverter::toString(mHitTimeArray[i]);
			resultStr += " ";
		}

		return resultStr;
	}
	//---------------------------------------------------------------------
	unsigned short Spell::getNumHitTimes(void)
	{
		return static_cast<unsigned short>(mHitTimeArray.size());
	}
	//---------------------------------------------------------------------
	void Spell::setShakeTimeFromString(const String &shakeTimeStr)
	{
		mShakeTimeArray.clear();

		Ogre::StringVector shakeTimes = Ogre::StringUtil::split(shakeTimeStr);

		for (size_t i=0; i<shakeTimes.size(); ++i)
		{
			mShakeTimeArray.push_back( Ogre::StringConverter::parseReal(shakeTimes[i]) );
		}
	}
	//---------------------------------------------------------------------
	String Spell::getShakeTimeString(void) const
	{
		String resultStr("");

		for (size_t i=0; i<mShakeTimeArray.size(); ++i)
		{
			resultStr += Ogre::StringConverter::toString(mShakeTimeArray[i]);
			resultStr += " ";
		}

		return resultStr;
	}
	//---------------------------------------------------------------------
	unsigned short Spell::getNumShakeTimes(void)
	{
		return static_cast<unsigned short>(mShakeTimeArray.size());
	}
	//---------------------------------------------------------------------
	void Spell::shutdown(void)
	{
		for ( AnimationEffectInfos::iterator i = mAnimationEffectInfos.begin(); i != mAnimationEffectInfos.end(); ++i )
		{
			SpellImpactModule* info = *i;
			Impact* effect = info->getEffect();

			if (effect)
			{
				effect->shutdown();
			}
		}
	}
	//---------------------------------------------------------------------
	void Spell::copyParameters(Spell* newInfo) const
	{
		newInfo->mAnimName = mAnimName;
		newInfo->mBreakTimeArray = mBreakTimeArray;
		newInfo->mHitTimeArray = mHitTimeArray;
		newInfo->mShakeTimeArray = mShakeTimeArray;
		newInfo->mRepeatEffect = mRepeatEffect;
		newInfo->mRotation = this->mRotation;
	}

	//////////////////////////////////////////////////////////////////////////
	String Spell::CmdAnimationName::doGet(const void* target) const
	{
		return static_cast<const Spell *>(target)->getAnimationName();
	}
	void Spell::CmdAnimationName::doSet(void* target, const String& val)
	{
		static_cast<Spell *>(target)->setAnimationName(val);
	}
#if OGRE_STRING_INTERFACE_COPY
	//-----------------------------------------------------------------------
	void Spell::CmdAnimationName::doCopy(void* target, const void* source)
	{
		static_cast<Spell *>(target)->setAnimationName(
			static_cast<const Spell *>(source)->getAnimationName() );
	}
#endif
	//-----------------------------------------------------------------------
	String Spell::CmdBreakTime::doGet(const void* target) const
	{
		return static_cast<const Spell *>(target)->getBreakTimeString();
	}
	void Spell::CmdBreakTime::doSet(void* target, const String& val)
	{
		static_cast<Spell *>(target)->setBreakTimeFromString(val);
	}
#if OGRE_STRING_INTERFACE_COPY
	//-----------------------------------------------------------------------
	void Spell::CmdBreakTime::doCopy(void* target, const void* source)
	{
		static_cast<Spell *>(target)->setBreakTimeFromString(
			static_cast<const Spell *>(source)->getBreakTimeString() );
	}
#endif
	//-----------------------------------------------------------------------
	String Spell::CmdHitTime::doGet(const void* target) const
	{
		return static_cast<const Spell *>(target)->getHitTimeString();
	}
	void Spell::CmdHitTime::doSet(void* target, const String& val)
	{
		static_cast<Spell *>(target)->setHitTimeFromString(val);
	}
#if OGRE_STRING_INTERFACE_COPY
	//-----------------------------------------------------------------------
	void Spell::CmdHitTime::doCopy(void* target, const void* source)
	{
		static_cast<Spell *>(target)->setHitTimeFromString(
			static_cast<const Spell *>(source)->getHitTimeString() );
	}
#endif
	//-----------------------------------------------------------------------
	String Spell::CmdShakeTime::doGet(const void* target) const
	{
		return static_cast<const Spell *>(target)->getShakeTimeString();
	}
	void Spell::CmdShakeTime::doSet(void* target, const String& val)
	{
		static_cast<Spell *>(target)->setShakeTimeFromString(val);
	}
#if OGRE_STRING_INTERFACE_COPY
	//-----------------------------------------------------------------------
	void Spell::CmdShakeTime::doCopy(void* target, const void* source)
	{
		static_cast<Spell *>(target)->setShakeTimeFromString(
			static_cast<const Spell *>(source)->getShakeTimeString() );
	}
#endif
	//-----------------------------------------------------------------------
	String Spell::CmdRepeatEffect::doGet(const void* target) const
	{
		return Ogre::StringConverter::toString( 
			static_cast<const Spell *>(target)->getRepeatEffect() );
	}
	void Spell::CmdRepeatEffect::doSet(void* target, const String& val)
	{
		static_cast<Spell *>(target)->setRepeatEffect( Ogre::StringConverter::parseBool(val) );
	}
#if OGRE_STRING_INTERFACE_COPY
	//-----------------------------------------------------------------------
	void Spell::CmdRepeatEffect::doCopy(void* target, const void* source)
	{
		static_cast<Spell *>(target)->setRepeatEffect(
			static_cast<const Spell *>(source)->getRepeatEffect() );
	}
#endif
	void Spell::loadBinary( SpellsSerializer* serializer ,Ogre::DataStreamPtr& stream)
	{
		mAnimName = serializer->readString(stream);

		if (!stream->eof())
		{
			unsigned short streamID;
			bool isReadDone = false;

			while(!stream->eof() && !isReadDone)
			{
				streamID = serializer->readChunk(stream);
				switch (streamID)
				{
				case SpellsSerializer::SKILL_EFFECT_INFO:
					{
						SpellImpactModule* effectInfo = addAnimationEffectInfo();
						effectInfo->loadBinary(serializer,stream);
						break;
					}
				case SpellsSerializer::SKILL_RIBBON_INFO:
					{
						SpellRibbonModule* ribbonInfo = addAnimationRibbon();
						ribbonInfo->loadBinary(serializer,stream);
						break;
					}
				case SpellsSerializer::SKILL_SOUND_INFO:
					{
						SpellSoundModule* soundInfo = addAnimationSound();
						soundInfo->loadBinary(serializer,stream);
						break;
					}
				case SpellsSerializer::SKILL_LIGHT_INFO:
					{
						SpellSceneLightModule* lightInfo = addAnimationSceneLightInfo();
						lightInfo->loadBinary(serializer,stream);
						break;
					}
				case SpellsSerializer::SKILL_BF_INFO:
					{
						SpellBulletFlowModule* bfInfo = addAnimationBulletFlow();
						bfInfo->loadBinary(serializer,stream);
						break;
					}
				case SpellsSerializer::SKILL_MODEL_INFO:
					{
						assert(false);
						break;
					}
				default:
					isReadDone = true;
					break;
				}

				if(isReadDone)
					stream->skip(-Ogre::Serializer::STREAM_OVERHEAD_SIZE);
			}
		}
	}

	void Spell::saveBinary( SpellsSerializer* serializer )
	{ 
		
	}

	std::size_t Spell::calcSerializedSize()
	{
		return 0;
	}

	void Spell::clear()
	{
		removeAllAnimationEffectInfos();
		removeAllAnimationRibbons();
		removeAllAnimationSounds();
		removeAllAnimationSceneLightInfos();
		removeAllAnimationBulletFlows();
		removeAllSkillModelElement();
	}
}
