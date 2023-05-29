#include "OgreHeader.h"
#include "OGSpellModelModule.h"
#include "OGSkeletonMeshComponent.h"
#include "OGSkeletonMeshComponentManager.h"

#include "OgreStringConverter.h"

namespace Orphigine
{

	SpellModelModule::CmdAttach				SpellModelModule::msAttachCmd;
	SpellModelModule::CmdAttachPoint			SpellModelModule::msAttachPointCmd;
	SpellModelModule::CmdAttachTime			SpellModelModule::msAttachTimeCmd;
	SpellModelModule::CmdModelTemplateName		SpellModelModule::msModelTemplateNameCmd;
	SpellModelModule::CmdOffsetPos				SpellModelModule::msOffsetPosCmd;
	SpellModelModule::CmdOffsetRotation		SpellModelModule::msOffsetRotationCmd;
	SpellModelModule::CmdSubSkillTemplateName	SpellModelModule::msSubSkillTemplateNameCmd;
	SpellModelModule::CmdLifeTime				SpellModelModule::msLifeTimeCmd;

	SpellModelModule::SpellModelModule()
		:mAttachTime(0.0f), 
		mAttachPoint(""), 
		mModelTemplateName(""),
		mModel(NULL),
		mOffsetPos(Ogre::Vector3::ZERO), 
		mOffsetRotation(Ogre::Quaternion::IDENTITY), 
		mAttach(false),
		mSubSkillTemplateName(""),
		mLifeTime(0.0f),
		mIsCreatedInstance(false),
		mCurrentLifeTime(0.0f)
	{
		initParamDictionary();
	}

	SpellModelModule::~SpellModelModule()
	{
		if (NULL != mModel)
		{
			SkeletonMeshComponentManager::getSingleton().destroyLogicModel(mModel);
			mModel = NULL;
		}
	}	

	bool SpellModelModule::initParamDictionary( void )
	{

		if (createParamDictionary("SkillModelElementDict"))
		{
			Ogre::ParamDictionary* dict = getParamDictionary();			

			dict->addParameter(Ogre::ParameterDef("AttachTime", 
				"the time that showing the effect.",
				Ogre::PT_REAL),&msAttachTimeCmd);	  

			dict->addParameter(Ogre::ParameterDef("AttachPoint", 
				"the attached bone or locator.",
				Ogre::PT_STRING),&msAttachPointCmd);	  

			dict->addParameter(Ogre::ParameterDef("ModelTemplateName", 
				"name of model template.",
				Ogre::PT_STRING),&msModelTemplateNameCmd);	  

			dict->addParameter(Ogre::ParameterDef("OffsetPos", 
				"offset position to the attach point.",
				Ogre::PT_VECTOR3),&msOffsetPosCmd);	  

			dict->addParameter(Ogre::ParameterDef("OffsetRotation", 
				"offset orientation to the attach point.",
				Ogre::PT_QUATERNION),&msOffsetRotationCmd);	  

			dict->addParameter(Ogre::ParameterDef("Attach", 
				"whether the effect will move along with the attach point.",
				Ogre::PT_BOOL),&msAttachCmd);	  

			dict->addParameter(Ogre::ParameterDef("SubSkillTemplateName",
				"The sub skill template name.",
				Ogre::PT_STRING),&msSubSkillTemplateNameCmd);

			dict->addParameter(Ogre::ParameterDef("LifeTime",
				"The life time of model.",
				Ogre::PT_REAL),&msLifeTimeCmd);

			return true;
		}

		return false;
	}

	void SpellModelModule::setAttachTime( float time )
	{
		mAttachTime = time;
	}

	float SpellModelModule::getAttachTime( void ) const
	{
		return mAttachTime;
	}

	void SpellModelModule::setAttachPoint( const String &point )
	{
		mAttachPoint = point;
	}

	const String& SpellModelModule::getAttachPoint( void ) const
	{
		return mAttachPoint;
	}

	void SpellModelModule::setModelTemplateName( const String &name )
	{
		mModelTemplateName = name;
	}

	const String& SpellModelModule::getModelTemplateName( void ) const
	{
		return mModelTemplateName;
	}

	void SpellModelModule::setOffsetPos( const Ogre::Vector3 &pos )
	{
		mOffsetPos = pos;
	}

	const Ogre::Vector3& SpellModelModule::getOffsetPos( void ) const
	{
		return mOffsetPos;
	}

	void SpellModelModule::setOffsetRotation( const Ogre::Quaternion &rotation )
	{
		mOffsetRotation = rotation;
	}

	const Ogre::Quaternion& SpellModelModule::getOffsetRotation( void ) const
	{
		return mOffsetRotation;
	}

	void SpellModelModule::setAttach( bool attach )
	{
		mAttach = attach;
	}

	bool SpellModelModule::getAttach( void ) const
	{
		return mAttach;
	}

	SkeletonMeshComponent * SpellModelModule::getModel() const
	{
		return mModel;
	}

	void SpellModelModule::setModel( SkeletonMeshComponent * val )
	{
		mModel = val;
	}

	void SpellModelModule::copyAttributesTo( SpellModelModule& newInfo ) const
	{
		newInfo.mAttachTime = mAttachTime;
		newInfo.mAttachPoint = mAttachPoint;
		newInfo.mModelTemplateName = mModelTemplateName;
		newInfo.mSubSkillTemplateName	= mSubSkillTemplateName;
		newInfo.mOffsetPos = mOffsetPos;
		newInfo.mOffsetRotation = mOffsetRotation;
		newInfo.mAttach = mAttach;
		newInfo.mLifeTime = mLifeTime;
	}

	String SpellModelModule::getSubSkillTemplateName() const
	{
		return mSubSkillTemplateName;
	}

	void SpellModelModule::setSubSkillTemplateName(String val )
	{
		mSubSkillTemplateName = val;
	}

	Real SpellModelModule::getLifeTime() const
	{
		return mLifeTime;
	}

	void SpellModelModule::setLifeTime(Real val )
	{
		mLifeTime = val;
	}

	void SpellModelModule::updateRenderInstance( Real time )
	{
		if(!mIsCreatedInstance)
			return;

		mCurrentLifeTime += time;

		if(mCurrentLifeTime > mLifeTime)
		{
			if (NULL != mModel)
			{
				SkeletonMeshComponentManager::getSingleton().destroyLogicModel(mModel);
				mModel = NULL;
			}
		}

	}

	bool SpellModelModule::getIsCreatedInstance() const
	{
		return mIsCreatedInstance;
	}

	void SpellModelModule::setIsCreatedInstance( bool val )
	{
		mIsCreatedInstance = val;
	}

	Real SpellModelModule::getCurrentLifeTime() const
	{
		return mCurrentLifeTime;
	}

	void SpellModelModule::setCurrentLifeTime(Real val )
	{
		mCurrentLifeTime = val;
	}


	String SpellModelModule::CmdAttachTime::doGet(const void* target) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const SpellModelModule *>(target)->getAttachTime() );
	}
	void SpellModelModule::CmdAttachTime::doSet(void* target, const String& val)
	{
		static_cast<SpellModelModule *>(target)->setAttachTime(Ogre::StringConverter::parseReal(val));
	}
#if OGRE_STRING_INTERFACE_COPY
	void SpellModelModule::CmdAttachTime::doCopy(void* target, const void* source)
	{
		static_cast<SpellModelModule *>(target)->setAttachTime(
			static_cast<const SpellModelModule *>(source)->getAttachTime() );
	}
#endif

	String SpellModelModule::CmdAttachPoint::doGet(const void* target) const
	{
		return static_cast<const SpellModelModule *>(target)->getAttachPoint();
	}
	void SpellModelModule::CmdAttachPoint::doSet(void* target, const String& val)
	{
		static_cast<SpellModelModule *>(target)->setAttachPoint(val);
	}
#if OGRE_STRING_INTERFACE_COPY
	void SpellModelModule::CmdAttachPoint::doCopy(void* target, const void* source)
	{
		static_cast<SpellModelModule *>(target)->setAttachPoint(
			static_cast<const SpellModelModule *>(source)->getAttachPoint() );
	}
#endif

	String SpellModelModule::CmdModelTemplateName::doGet(const void* target) const
	{
		return static_cast<const SpellModelModule *>(target)->getModelTemplateName();
	}
	void SpellModelModule::CmdModelTemplateName::doSet(void* target, const String& val)
	{
		static_cast<SpellModelModule *>(target)->setModelTemplateName(val);
	}
#if OGRE_STRING_INTERFACE_COPY
	void SpellModelModule::CmdModelTemplateName::doCopy(void* target, const void* source)
	{
		static_cast<SpellModelModule *>(target)->setModelTemplateName(
			static_cast<const SpellModelModule *>(source)->getModelTemplateName() );
	}
#endif

	String SpellModelModule::CmdOffsetPos::doGet(const void* target) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const SpellModelModule *>(target)->getOffsetPos() );
	}
	void SpellModelModule::CmdOffsetPos::doSet(void* target, const String& val)
	{
		static_cast<SpellModelModule *>(target)->setOffsetPos(Ogre::StringConverter::parseVector3(val));
	}
#if OGRE_STRING_INTERFACE_COPY
	void SpellModelModule::CmdOffsetPos::doCopy(void* target, const void* source)
	{
		static_cast<SpellModelModule *>(target)->setOffsetPos(
			static_cast<const SpellModelModule *>(source)->getOffsetPos() );
	}
#endif

	String SpellModelModule::CmdOffsetRotation::doGet(const void* target) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const SpellModelModule *>(target)->getOffsetRotation() );
	}
	void SpellModelModule::CmdOffsetRotation::doSet(void* target, const String& val)
	{
		static_cast<SpellModelModule *>(target)->setOffsetRotation(Ogre::StringConverter::parseQuaternion(val));
	}
#if OGRE_STRING_INTERFACE_COPY
	void SpellModelModule::CmdOffsetRotation::doCopy(void* target, const void* source)
	{
		static_cast<SpellModelModule *>(target)->setOffsetRotation(
			static_cast<const SpellModelModule *>(source)->getOffsetRotation() );
	}
#endif

	String SpellModelModule::CmdAttach::doGet(const void* target) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const SpellModelModule *>(target)->getAttach() );
	}
	void SpellModelModule::CmdAttach::doSet(void* target, const String& val)
	{
		static_cast<SpellModelModule *>(target)->setAttach(Ogre::StringConverter::parseBool(val));
	}
#if OGRE_STRING_INTERFACE_COPY
	void SpellModelModule::CmdAttach::doCopy(void* target, const void* source)
	{
		static_cast<SpellModelModule *>(target)->setAttach(
			static_cast<const SpellModelModule *>(source)->getAttach() );
	}
#endif

	String SpellModelModule::CmdSubSkillTemplateName::doGet( const void* target ) const
	{
		return static_cast<const SpellModelModule*>(target)->getSubSkillTemplateName();
	}

	void SpellModelModule::CmdSubSkillTemplateName::doSet( void* target, const String& val )
	{
		static_cast<SpellModelModule*>(target)->setSubSkillTemplateName(val);
	}

#if OGRE_STRING_INTERFACE_COPY
	void SpellModelModule::CmdSubSkillTemplateName::doCopy( void* target, const void* source )
	{
		static_cast<SpellModelModule*>(target)->setSubSkillTemplateName(
			static_cast<const SpellModelModule*>(source)->getSubSkillTemplateName());
	}
#endif


	Ogre::String SpellModelModule::CmdLifeTime::doGet( const void* target ) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const SpellModelModule*>(target)->getLifeTime());
	}

	void SpellModelModule::CmdLifeTime::doSet( void* target, const String& val )
	{
		static_cast<SpellModelModule*>(target)->setLifeTime(
			Ogre::StringConverter::parseReal(val));
	}
#if OGRE_STRING_INTERFACE_COPY
	void SpellModelModule::CmdLifeTime::doCopy( void* target, const void* source )
	{
		static_cast<SpellModelModule*>(target)->setLifeTime(
			static_cast<const SpellModelModule*>(source)->getLifeTime());
	}
#endif

	void SpellModelModule::loadBinary( SpellsSerializer* serializer,Ogre::DataStreamPtr& stream )
	{

	}

	void SpellModelModule::saveBinary( SpellsSerializer* serializer )
	{

	}

	std::size_t SpellModelModule::calcSerializedSize()
	{
		return 0;
	}
}