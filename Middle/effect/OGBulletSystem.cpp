#include "OgreHeader.h"
#include "OGBulletSystem.h"
#include "OGSpellRibandModule.h"
#include "OGSpellImpactModule.h"
#include "OGSpellSoundModule.h"
#include "OGSpellSceneLightModule.h"
#include "OGMainSceneLight.h"
#include "engine_manager.h"
#include "OGImpact.h"
#include "OGImpactManager.h"
#include "OGBulletFlowSystemManager.h"
#include "OGBulletCallbacks.h"
#include "OGSkeletonMeshComponent.h"
#include "OGBulletSystemEffectElement.h"
#include "OGBulletSystemBeamElement.h"
#include "OGBulletFlowSystem.h"

#include "OgreControllerManager.h"
#include "OgreController.h"
#include "OgreStringConverter.h"
#include "OgreSceneManager.h"

namespace Orphigine
{

	BulletSystem::CmdAttach			BulletSystem::ms_attachCmd;

	BulletSystem::BulletSystem(const String& templateName)
		: m_templateName(templateName)
	{
		initParameters();

		m_userData = NULL;

		mBulletSystemEffectElements.clear();
		mAnimationRibbons.clear();
		mAnimationSounds.clear();
		mAnimationSceneLightInfos.clear();
		mBulletSystemBeamElements.clear();
		m_isAttach = false;
		m_isCreated = false;
		m_age = 0.0f;
		m_eventAge = 0.0f;
		m_sourcePosition = Ogre::Vector3::ZERO;
		m_destPosition = Ogre::Vector3::ZERO;
		m_Priority = 0;
	
	}

	BulletSystem::~BulletSystem()
	{
		removeAllBulletSystemEffectElements();
		removeAllAnimationRibbons();
		removeAllAnimationSounds();
		removeAllAnimationSceneLightInfos();
		removeAllBulletSystemBeamElements();
	}

	void BulletSystem::initParameters()
	{
		if (createParamDictionary("BulletSystem"))
		{
			Ogre::ParamDictionary* tmpDict = getParamDictionary();

			tmpDict->addParameter(Ogre::ParameterDef(
				"IsAttach","Is bullet system attaching to the target",Ogre::PT_BOOL),
				&ms_attachCmd);
		}
	}
 
	BulletSystem& BulletSystem::operator = (const BulletSystem& rhs)
	{
		removeAllBulletSystemEffectElements();
		// Copy effect infos
		unsigned int i;
		for(i = 0; i < rhs.getNumBulletSystemEffectElements(); ++i)
		{
			BulletSystemEffectElement *rhsAEI = rhs.getBulletSystemEffectElement(i);
			BulletSystemEffectElement *newAEI = addBulletSystemEffectElement();

			assert ( rhsAEI && newAEI );

			//	rhsAEI->copyParametersTo(newAEI);
			rhsAEI->copyAttributeTo(*newAEI);
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
		// Copy effect infos
		for(i = 0; i < rhs.getNumAnimationSceneLightInfos(); ++i)
		{
			SpellSceneLightModule *rhsAEI = rhs.getAnimationSceneLightInfo(i);
			SpellSceneLightModule *newAEI = addAnimationSceneLightInfo();

			assert ( rhsAEI && newAEI );

			rhsAEI->copyParameters(*newAEI);
		}

		removeAllBulletSystemBeamElements();
		for(i = 0;i < rhs.getNumBulletSystemBeamElements(); ++i)
		{
			BulletSystemBeamElement* rhsAEI = rhs.getBulletSystemBeamElement(i);
			BulletSystemBeamElement* newAEI = addBulletSystemBeamElement();

			assert (rhsAEI && newAEI && "BulletSystem::operator =");

			rhsAEI->copyAttributesTo(*newAEI);
		}


		// copy skill parameter
		//	rhs.copyParametersTo(this);
		rhs.copyAttributesTo(*this);

		return *this;
	}

	Ogre::String BulletSystem::CmdAttach::doGet( const void* target ) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const BulletSystem*>(target)->getAttach());
	}

	void BulletSystem::CmdAttach::doSet( void* target, const String& val )
	{
		static_cast<BulletSystem*>(target)->setAttach(
			Ogre::StringConverter::parseBool(val));
	}

	BulletSystemEffectElement* BulletSystem::addBulletSystemEffectElement(void)
	{
		BulletSystemEffectElement *effectInfo = new BulletSystemEffectElement();
		assert (effectInfo);

		mBulletSystemEffectElements.push_back(effectInfo);

		return effectInfo;
	}
	//---------------------------------------------------------------------
	BulletSystemEffectElement* BulletSystem::getBulletSystemEffectElement(unsigned short index) const
	{
		assert(index < mBulletSystemEffectElements.size() && "Animation Effect Info index out of bounds!");
		return mBulletSystemEffectElements[index];
	}
	//---------------------------------------------------------------------
	unsigned short BulletSystem::getNumBulletSystemEffectElements(void) const
	{
		return static_cast<unsigned short>( mBulletSystemEffectElements.size() );
	}
	//---------------------------------------------------------------------
	void BulletSystem::removeBulletSystemEffectElement(unsigned short index)
	{
		assert(index < mBulletSystemEffectElements.size() && "Animation Effect Info index out of bounds!");
		BulletSystemEffectElements::iterator ai = mBulletSystemEffectElements.begin() + index;

		if (*ai)
		{
			delete *ai;
			*ai = NULL;
		}

		mBulletSystemEffectElements.erase(ai);
	}
	//---------------------------------------------------------------------
	void BulletSystem::removeAllBulletSystemEffectElements(void)
	{
		for ( BulletSystemEffectElements::iterator i = mBulletSystemEffectElements.begin(); i != mBulletSystemEffectElements.end(); ++i )
		{
			if (*i)
			{
				delete (*i);
				(*i) = NULL;
			}
		}
		mBulletSystemEffectElements.clear();
	}
	//---------------------------------------------------------------------
	SpellRibbonModule* BulletSystem::addAnimationRibbon(void)
	{
		SpellRibbonModule *ribbon = new SpellRibbonModule();
		assert (ribbon);

		mAnimationRibbons.push_back(ribbon);

		return ribbon;
	}
	//---------------------------------------------------------------------
	SpellRibbonModule* BulletSystem::getAnimationRibbon(unsigned short index) const
	{
		assert(index < mAnimationRibbons.size() && "Animation ribbon index out of bounds!");
		return mAnimationRibbons[index];
	}
	//---------------------------------------------------------------------
	unsigned short BulletSystem::getNumAnimationRibbons(void) const
	{
		return static_cast<unsigned short>( mAnimationRibbons.size() );
	}
	//---------------------------------------------------------------------
	void BulletSystem::removeAnimationRibbon(unsigned short index)
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
	void BulletSystem::removeAllAnimationRibbons(void)
	{
		/*for (unsigned short i=0; i<getNumAnimationRibbons(); ++i )
		{
		removeAnimationRibbon(i);
		}*/
		for ( AnimationRibbons::iterator i = mAnimationRibbons.begin(); i != mAnimationRibbons.end(); ++i )
		{
			if (*i)
			{
				delete (*i);
				(*i) = NULL;
			}
		}
		mAnimationRibbons.clear();
	}
	//---------------------------------------------------------------------
	SpellSoundModule* BulletSystem::addAnimationSound(void)
	{
		SpellSoundModule *sound = new SpellSoundModule();
		assert (sound);

		mAnimationSounds.push_back(sound);

		return sound;
	}
	//---------------------------------------------------------------------
	SpellSoundModule* BulletSystem::getAnimationSound(unsigned short index) const
	{
		assert(index < mAnimationSounds.size() && "Animation sound index out of bounds!");
		return mAnimationSounds[index];
	}
	//---------------------------------------------------------------------
	unsigned short BulletSystem::getNumAnimationSounds(void) const
	{
		return static_cast<unsigned short>( mAnimationSounds.size() );
	}
	//---------------------------------------------------------------------
	void BulletSystem::removeAnimationSound(unsigned short index)
	{
		assert(index < mAnimationSounds.size() && "Animation sound index out of bounds!");
		AnimationSounds::iterator ai = mAnimationSounds.begin() + index;

		if (*ai)
		{
			SpellSoundModule* tmpAnimSound = (*ai);

			if(-1 != tmpAnimSound->mSoundHandle)
			{
				SkeletonMeshComponent::GetStopSoundFunction()(tmpAnimSound->mSoundHandle);
				tmpAnimSound->mSoundHandle=-1;
			}

			delete *ai;
			*ai = NULL;
		}

		mAnimationSounds.erase(ai);
	}
	//---------------------------------------------------------------------
	void BulletSystem::removeAllAnimationSounds(void)
	{		
		for ( AnimationSounds::iterator i = mAnimationSounds.begin(); i != mAnimationSounds.end(); ++i )
		{
			if (*i)
			{
				SpellSoundModule* tmpAnimSound = (*i);

				if(-1 != tmpAnimSound->mSoundHandle)
				{
					SkeletonMeshComponent::GetStopSoundFunction()(tmpAnimSound->mSoundHandle);
					tmpAnimSound->mSoundHandle=-1;
				}

				delete *i;
				*i = NULL;
			}
		}
		mAnimationSounds.clear();
	}
	//---------------------------------------------------------------------
	SpellSceneLightModule* BulletSystem::addAnimationSceneLightInfo(void)
	{
		SpellSceneLightModule *effectInfo = new SpellSceneLightModule();
		assert (effectInfo);

		mAnimationSceneLightInfos.push_back(effectInfo);

		return effectInfo;
	}
	//---------------------------------------------------------------------
	SpellSceneLightModule* BulletSystem::getAnimationSceneLightInfo(unsigned short index) const
	{
		assert(index < mAnimationSceneLightInfos.size() && "Animation scene light Info index out of bounds!");
		return mAnimationSceneLightInfos[index];
	}
	//---------------------------------------------------------------------
	unsigned short BulletSystem::getNumAnimationSceneLightInfos(void) const
	{
		return static_cast<unsigned short>( mAnimationSceneLightInfos.size() );
	}
	//---------------------------------------------------------------------
	void BulletSystem::removeAnimationSceneLightInfo(unsigned short index)
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
	void BulletSystem::removeAllAnimationSceneLightInfos(void)
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
	BulletSystemBeamElement* BulletSystem::addBulletSystemBeamElement()
	{	
		BulletSystemBeamElement *tmpBeamElement = new BulletSystemBeamElement();
		assert (tmpBeamElement);

		mBulletSystemBeamElements.push_back(tmpBeamElement);

		return tmpBeamElement;		
	}

	BulletSystemBeamElement* BulletSystem::getBulletSystemBeamElement( unsigned short index ) const
	{
		assert(index < mBulletSystemBeamElements.size() && "BulletSystem beam index out of bounds!");
		return mBulletSystemBeamElements[index];
	}

	unsigned short BulletSystem::getNumBulletSystemBeamElements() const
	{
		return static_cast<unsigned short>( mBulletSystemBeamElements.size() );
	}

	void BulletSystem::removeBulletSystemBeamElement( unsigned short index )
	{
		assert(index < mBulletSystemBeamElements.size() && "Animation Effect Info index out of bounds!");
		BulletSystemBeamElements::iterator ai = mBulletSystemBeamElements.begin() + index;

		if (*ai)
		{
			delete *ai;
			*ai = NULL;
		}

		mBulletSystemBeamElements.erase(ai);
	}

	void BulletSystem::removeAllBulletSystemBeamElements()
	{
		for ( BulletSystemBeamElements::iterator i = mBulletSystemBeamElements.begin(); i != mBulletSystemBeamElements.end(); ++i )
		{
			if (*i)
			{
				delete (*i);
				(*i) = NULL;
			}
		}
		mBulletSystemBeamElements.clear();
	}


	//-------------------------------------------------------------------------
	void BulletSystem::copyAttributesTo( BulletSystem& dest ) const
	{
		dest.m_isAttach = m_isAttach;
	}

	void BulletSystem::createSceneNode()
	{
		m_sceneNode = 
			EngineManager::getSingleton().getBaseSceneNode()->createChildSceneNode(BLANKSTRING);
	}

	void BulletSystem::createSceneNode( Ogre::SceneNode* parentNode )
	{
		assert(NULL != parentNode);

		if (NULL == m_sceneNode)
		{
			m_sceneNode = parentNode->createChildSceneNode(BLANKSTRING);
		} 
		else
		{
			if(m_sceneNode->getParent())
			{
				m_sceneNode->getParent()->removeChild(m_sceneNode);
			}

			parentNode->addChild(m_sceneNode);
		}
	}
	void BulletSystem::setTransformInfo( const TransformInfo& info )
	{
		if(NULL == m_sceneNode)
			return;
		m_sceneNode->setPosition(info.mPosition);
		m_sceneNode->setOrientation(info.mRotation);
		m_sceneNode->setScale(info.mScale);
		m_transWorld= info;
	}

	void BulletSystem::update( Real time )
	{
		if (NULL == m_sceneNode)
			return;
		if (m_isCreated )
		{
			m_age += time;
			m_eventAge += time;
		}

		if (!m_isCreated)
		{
			_createElements();
			m_isCreated = true;
		}
		
		_updateElements(time);
	}

	const String& BulletSystem::getTemplateName() const
	{
		return m_templateName;
	}

	void BulletSystem::removeSceneNode()
	{
		assert(NULL != m_sceneNode && NULL != m_sceneNode->getParent());
		//m_sceneNode->getParent()->removeChild(m_sceneNode);
		m_sceneNode->getCreator()->destroySceneNode(m_sceneNode);
		m_sceneNode = NULL;
	}

	const	TransformInfo& BulletSystem::getTransformInfo() const
	{
		return m_transWorld;
	}

	bool BulletSystem::getAttach() const
	{
		return m_isAttach;
	}

	void BulletSystem::setAttach( bool val )
	{
		m_isAttach = val;
	}

	void BulletSystem::_createElements()
	{
		BulletSystemEffectElements::iterator iter;
		for (iter = mBulletSystemEffectElements.begin();iter != mBulletSystemEffectElements.end();iter ++)
		{
			BulletSystemEffectElement* tmpEffectInfo = (*iter);

			String tmpEffectTemplateName = tmpEffectInfo->getEffectTemplateName();

			Impact* tmpEffect = ImpactManager::getSingleton().createEffect(tmpEffectTemplateName, this->m_Priority);

			tmpEffect->createSceneNode(m_sceneNode);

			tmpEffect->setVisible(true);
			//end

			tmpEffectInfo->setEffect(tmpEffect);
		}

		AnimationRibbons::iterator tmpAnimRibbonIter;
		for (tmpAnimRibbonIter = mAnimationRibbons.begin();tmpAnimRibbonIter != mAnimationRibbons.end();tmpAnimRibbonIter ++)
		{
			SpellRibbonModule* tmpAnimRibbon = (*tmpAnimRibbonIter);

			tmpAnimRibbon->createRenderInstance();
		}

		AnimationSounds::iterator tmpAnimSoundIter;
		for (tmpAnimSoundIter = mAnimationSounds.begin();tmpAnimSoundIter != mAnimationSounds.end();tmpAnimSoundIter ++)
		{
			SpellSoundModule* tmpAnimSound = (*tmpAnimSoundIter);

			String tmpAnimSoundName = tmpAnimSound->getSoundName();

			Ogre::Vector3 tmpPosition = this->getPositionWorld();
			Real pos[3] = { tmpPosition.x, tmpPosition.y, tmpPosition.z };
			tmpAnimSound->mSoundHandle = SkeletonMeshComponent::GetPlaySoundFuncton()(tmpAnimSoundName.c_str(),pos,tmpAnimSound->getLooping());
			tmpAnimSound->mPlayed = true;
		}

		BulletSystemBeamElements::iterator tmpBeamIter;
		for (tmpBeamIter = mBulletSystemBeamElements.begin();tmpBeamIter != mBulletSystemBeamElements.end();tmpBeamIter ++)
		{
			BulletSystemBeamElement* tmpBeamElement = (*tmpBeamIter);

			tmpBeamElement->createElementSceneNode(m_sceneNode);
			tmpBeamElement->createRenderInstance();
		}
	}

	void BulletSystem::_updateElements( Real time )
	{
		TransformInfo tmpTransInfo;

		AnimationRibbons::iterator tmpAnimRibbonIter;
		for (tmpAnimRibbonIter = mAnimationRibbons.begin();tmpAnimRibbonIter != mAnimationRibbons.end();tmpAnimRibbonIter ++)
		{
			SpellRibbonModule* tmpAnimRibbon = (*tmpAnimRibbonIter);

			tmpTransInfo.mPosition = this->getPositionWorld() + tmpAnimRibbon->getOffsetPos();
			tmpTransInfo.mRotation = this->getOrientationWorld() + tmpAnimRibbon->getOffsetRotation();

			tmpAnimRibbon->updateRenderInstance(time,tmpTransInfo);

		}

		BulletSystemBeamElements::iterator tmpBeamIter;
		for (tmpBeamIter = mBulletSystemBeamElements.begin();tmpBeamIter != mBulletSystemBeamElements.end();tmpBeamIter ++)
		{
			BulletSystemBeamElement* tmpBeamElement = (*tmpBeamIter);

			tmpBeamElement->updateRenderInstance(time,m_sourcePosition,m_destPosition);
		}
	}

	const Ogre::Vector3& BulletSystem::getSourcePosition() const
	{
		return m_sourcePosition;
	}

	void BulletSystem::setSourcePosition( const Ogre::Vector3& val )
	{
		m_sourcePosition = val;
	}

	const Ogre::Vector3& BulletSystem::getDestPosition() const
	{
		return m_destPosition;
	}

	void BulletSystem::setDestPosition( const Ogre::Vector3& val )
	{
		m_destPosition = val;
	}

	Ogre::Real BulletSystem::getAge() const
	{
		return m_age;
	}

	void BulletSystem::setAge( Real val )
	{
		m_age = val;
	}

	Real BulletSystem::getEventAge() const
	{
		return m_eventAge;
	}

	void BulletSystem::setEventAge( Real val )
	{
		m_eventAge = val;
	}
}