#include "OgreHeader.h"
#include <OgreSceneNode.h>
#include <OgreStringConverter.h>
#include <OgreSceneManager.h>

#include "OgreString.h"
#include "OGImpactModule.h"
#include "OGImpactManager.h"
#include "OGImpactParticleModule.h"


namespace Orphigine	{

	ImpactModule::CmdStartTime ImpactModule::msStartTimeCmd;
	ImpactModule::CmdLifeTime ImpactModule::msLifeTimeCmd;
	ImpactModule::CmdRelPos ImpactModule::msRelPosCmd;
	ImpactModule::CmdRelOrientation ImpactModule::msRelOrientationCmd;

	ImpactModule::ImpactModule(const String &type)	:
	ImpactBasic(),
		mElementType(type),
		mEffectParent(NULL),	
		mIsRenderInstanceCreated(false),
		mLifeTime(0.0f),
		mStartTime(0.0f),
		mCurrentLifeTime(0.0f),
		mCurrentStartTime(0.0f),
		mRelPos(Ogre::Vector3::ZERO),
		mRelOrientation(Ogre::Quaternion::IDENTITY),
		mIsActive(true),
		mIsDestroy(false)
	{
	}

	ImpactModule::~ImpactModule()
	{
	}	

	void ImpactModule::dump(std::ofstream &of) const
	{
				
	}

	void ImpactModule::update( Real time, TransformInfo &info )
	{
		// calculate the born time
		Real currentStartTime = mCurrentStartTime + time;
		if ( currentStartTime < mStartTime )
		{
			mCurrentStartTime = currentStartTime;
			return;
		}

		/*if (mBasicNode)
		mBasicNode->setVisible(mVisible);*/

		if ( false == mIsRenderInstanceCreated )
		{
			if ( createRenderInstance() )
				mIsRenderInstanceCreated = true;
		}

		//　calculate the life time
		Real currentTime = mCurrentLifeTime + time;

		// if the life time is zero ,the element will not be deleted.
		if ( (currentTime > mLifeTime) && (mLifeTime > 0.0f) )
		{
			// destroy
			destroyMe();
		}
		else
		{
			mCurrentLifeTime = currentTime;			

			updateRenderInstance(time,info);			
		}	
	}	
	//---------------------------------------------------------------------
	void ImpactModule::setRelPos( const Ogre::Vector3 &pos )
	{	
		mRelPos = pos;
		if (mBasicNode)
			mBasicNode->setPosition(mRelPos);
	}
	//---------------------------------------------------------------------
	void ImpactModule::setRelOrientation( const Ogre::Quaternion& orientation )
	{	
		mRelOrientation = orientation;
		if (mBasicNode)
			mBasicNode->setOrientation(mRelOrientation);
	}
	//---------------------------------------------------------------------
	bool ImpactModule::initDefaults(const String &mType)
	{		
		if (createParamDictionary(mType + "EffectElement"))
		{
			Ogre::ParamDictionary* dict = getParamDictionary();

			dict->addParameter(Ogre::ParameterDef("StartTime", 
				"the start time of this element.",
				Ogre::PT_REAL),&msStartTimeCmd);

			dict->addParameter(Ogre::ParameterDef("LifeTime", 
				"the life time of this element.",
				Ogre::PT_REAL),&msLifeTimeCmd);

			dict->addParameter(Ogre::ParameterDef("Position", 
				"the relative pos from parent.",
				Ogre::PT_VECTOR3),&msRelPosCmd);

			dict->addParameter(Ogre::ParameterDef("Orientation", 
				"the relative orientation from parent.",
				Ogre::PT_QUATERNION),&msRelOrientationCmd);

			return true;

		}
		return false;
	}
	//---------------------------------------------------------------------
	void ImpactModule::sleep(void)
	{
		mCurrentLifeTime = 0.0f;
		mCurrentStartTime = 0.0f;

		mIsDestroy = false;
		//		mIsVisible = true;
		mIsActive = false;

		setVisible(false);
		//if (mBasicNode)
		//	mBasicNode->setVisible(false);
	}
	//---------------------------------------------------------------------
	void ImpactModule::active(void)
	{
		mIsActive = true;

		/*if (mBasicNode)
		mBasicNode->setVisible(true);	*/
	}
	//---------------------------------------------------------------------
	void ImpactModule::createSceneNode( Ogre::SceneNode *parentNode )
	{
		assert (parentNode);

		assert ( NULL == mBasicNode );

		static uint32_t impactModule_index = 0;
		String name = Ogre::StringUtil::format("ImpactModule:%d", impactModule_index++);
		mBasicNode = parentNode->createChildSceneNode(name);
		mBasicNode->setPosition(mRelPos);
		mBasicNode->setOrientation(mRelOrientation);
		assert (mBasicNode);

		//	dumpSceneNode(mBasicNode);		
	}
	//---------------------------------------------------------------------
	void ImpactModule::destroyMe(void)
	{
		// 设置自己的destroy状态
		mIsDestroy = true;
	}
	//---------------------------------------------------------------------
	void ImpactModule::setTransformInfo( const TransformInfo &info )
	{
		if ( mBasicNode )
		{
			Ogre::Matrix3 mat(Ogre::Matrix3::IDENTITY);
			info.mRotation.ToRotationMatrix(mat);

			//if ( getType() == "Projector" || ( getType() == "Particle" && static_cast<ParticleElement *>(this)->getIsProjector() && gSystemPtr->getTerrain()->isTerrainLoaded() ) )
			if ( getType() == "Projector" || ( getType() == "Particle" && static_cast<ImpactParticleModule *>(this)->getIsProjector() ) )
			{
				Ogre::Vector3 vPos = info.mPosition + mat * mRelPos;
				//这里1000.0f表示Projector的视锥高出地面的值，设置成1000.0f后，会把整个片投影到地面上，不会被地形截掉一部分。
				vPos.y += 1000.0f;
				mBasicNode->setPosition(vPos);
			}
			else
			{
				mBasicNode->setPosition(info.mPosition + mat * mRelPos);
				mBasicNode->setOrientation(info.mRotation * mRelOrientation);
			}

			mBasicNode->setScale(info.mScale);

			//	mBasicNode->_update(true,true);
		}
	}
	///*
	char * ImpactModule::readFromBuffer(char * pCurrent)
	{
		int length = sizeof(Ogre::Real) * 2 + sizeof(Ogre::Vector3) + sizeof(Ogre::Quaternion);
		memcpy(&mStartTime,pCurrent,length);
		pCurrent += length;
		return pCurrent;
	}

	void ImpactModule::saveToFile(std::ofstream & of)
	{
		of.write((const char *)(&mStartTime),sizeof(Ogre::Real) * 2 + sizeof(Ogre::Vector3) + sizeof(Ogre::Quaternion));
	}
	//*/
	///////////////////////////////////////////
	String ImpactModule::CmdStartTime::doGet(const void* target) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const ImpactModule*>(target)->getStartTime() );
	}
	void ImpactModule::CmdStartTime::doSet(void* target, const String& val)
	{
		static_cast<ImpactModule *>(target)->setStartTime(Ogre::StringConverter::parseReal(val));
	}
#if OGRE_STRING_INTERFACE_COPY
	//-----------------------------------------------------------------------
	void ImpactModule::CmdStartTime::doCopy(void* target, const void* source)
	{
		static_cast<ImpactModule *>(target)->setStartTime(
			static_cast<const ImpactModule*>(source)->getStartTime() );
	}
#endif
	//-----------------------------------------------------------------------
	String ImpactModule::CmdLifeTime::doGet(const void* target) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const ImpactModule *>(target)->getLifeTime() );
	}
	void ImpactModule::CmdLifeTime::doSet(void* target, const String& val)
	{
		static_cast<ImpactModule *>(target)->setLifeTime(Ogre::StringConverter::parseReal(val));
	}
#if OGRE_STRING_INTERFACE_COPY
	//-----------------------------------------------------------------------
	void ImpactModule::CmdLifeTime::doCopy(void* target, const void* source)
	{
		static_cast<ImpactModule *>(target)->setLifeTime(
			static_cast<const ImpactModule*>(source)->getLifeTime() );
	}
#endif
	//---------------------------------------------------------------------
	String ImpactModule::CmdRelPos::doGet(const void* target) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const ImpactModule *>(target)->getRelPos() );
	}
	void ImpactModule::CmdRelPos::doSet(void* target, const String& val)
	{
		static_cast<ImpactModule *>(target)->setRelPos(Ogre::StringConverter::parseVector3(val));
	} 
#if OGRE_STRING_INTERFACE_COPY
	//-----------------------------------------------------------------------
	void ImpactModule::CmdRelPos::doCopy(void* target, const void* source)
	{
		static_cast<ImpactModule *>(target)->setRelPos(
			static_cast<const ImpactModule*>(source)->getRelPos() );
	}
#endif
	//---------------------------------------------------------------------
	String ImpactModule::CmdRelOrientation::doGet(const void* target) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const ImpactModule *>(target)->getRelOrientation() );
	}
	void ImpactModule::CmdRelOrientation::doSet(void* target, const String& val)
	{
		static_cast<ImpactModule *>(target)->setRelOrientation(Ogre::StringConverter::parseQuaternion(val));
	}
#if OGRE_STRING_INTERFACE_COPY
	//-----------------------------------------------------------------------
	void ImpactModule::CmdRelOrientation::doCopy(void* target, const void* source)
	{
		static_cast<ImpactModule *>(target)->setRelOrientation(
			static_cast<const ImpactModule*>(source)->getRelOrientation() );
	}
#endif
}