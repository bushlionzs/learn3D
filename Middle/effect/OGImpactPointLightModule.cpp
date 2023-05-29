#include "OgreHeader.h"
#include "OGImpactPointLightModule.h"
#include <OgreLight.h>
#include <OgreSceneManager.h>
#include <OgreStringConverter.h>
#include <OgreParseCommandHelper.h>
#include <platform_log.h>
#include "OGImpactSerializer.h"
#include "engine_manager.h"
#include "OgreSceneNode.h"

namespace Orphigine	{

	namespace
	{
		typedef MemeberValueChangeParamCommand< ImpactPointLightModule, Ogre::ColourValue, &ImpactPointLightModule::mColourStart >	sPointColourStartCommand;
		typedef MemeberValueChangeParamCommand< ImpactPointLightModule, Ogre::ColourValue, &ImpactPointLightModule::mColourEnd >	sPointColourEndCommand;

		typedef MemeberValueCopyParamCommand< ImpactPointLightModule, Real, &ImpactPointLightModule::mTimeChange >	sPointTimeChangeCommand;

	}

	ImpactPointLightModule::CmdDiffuse ImpactPointLightModule::msDiffuseCmd;
	ImpactPointLightModule::CmdSpecular ImpactPointLightModule::msSpecularCmd;
	ImpactPointLightModule::CmdRange ImpactPointLightModule::msRangeCmd;
	ImpactPointLightModule::CmdAttenuationConstant ImpactPointLightModule::msAttenuationConstantCmd;
	ImpactPointLightModule::CmdAttenuationLinear ImpactPointLightModule::msAttenuationLinearCmd;
	ImpactPointLightModule::CmdAttenuationQuadric ImpactPointLightModule::msAttenuationQuadricCmd;

	//////////////////////////////////////////////////////////////////////////
	ImpactPointLightModule::ImpactPointLightModule(const String &type) :
	ImpactModule(type),
		mLight(NULL),
		mDiffuse(Ogre::ColourValue::White),
		mSpecular(Ogre::ColourValue::Black),
		mRange(1000),
		mAttenuationConstant(1.0f),
		mAttenuationLinear(0.0f),
		mAttenuationQuadric(0.0f),
		mColourStart( Ogre::ColourValue::White ),
		mColourEnd( Ogre::ColourValue::White ),
		mColourDelta1( Ogre::ColourValue::ZERO ),
		mColourDelta2( Ogre::ColourValue::ZERO ),
		mTimePass(0),
		mTimeChange(0)
	{
		if ( initDefaults(mElementType) )
		{
			Ogre::ParamDictionary* dict = getParamDictionary();   

			dict->addParameter(Ogre::ParameterDef("Diffuse", 
				"diffuse colour of point light.",
				Ogre::PT_COLOURVALUE),&msDiffuseCmd);

			dict->addParameter(Ogre::ParameterDef("Specular", 
				"specular colour of point light.",
				Ogre::PT_COLOURVALUE),&msSpecularCmd);

			dict->addParameter(Ogre::ParameterDef("Range", 
				"range of point light.",
				Ogre::PT_REAL),&msRangeCmd);

			dict->addParameter(Ogre::ParameterDef("AttenuationConstant", 
				"attenuation constant of point light.",
				Ogre::PT_REAL),&msAttenuationConstantCmd);

			dict->addParameter(Ogre::ParameterDef("AttenuationLinear", 
				"attenuation linear of point light.",
				Ogre::PT_REAL),&msAttenuationLinearCmd);

			dict->addParameter(Ogre::ParameterDef("AttenuationQuadric", 
				"attenuation quadric of point light.",
				Ogre::PT_REAL),&msAttenuationQuadricCmd);

			static sPointColourStartCommand s_pointColourStartCmd;
			dict->addParameter(Ogre::ParameterDef("clrstart", 
				"change colour start of light.",
				Ogre::PT_COLOURVALUE),&s_pointColourStartCmd);

			static sPointColourEndCommand s_pointColourEndCmd;
			dict->addParameter(Ogre::ParameterDef("clrendt", 
				"change colour end of light.",
				Ogre::PT_COLOURVALUE),&s_pointColourEndCmd);

			static sPointTimeChangeCommand s_pointTimeChangeCmd;
			dict->addParameter(Ogre::ParameterDef("timechange", 
				"time colour loop time.",
				Ogre::PT_REAL),&s_pointTimeChangeCmd);
		}
	}
	//-----------------------------------------------------------------------
	ImpactPointLightModule::~ImpactPointLightModule()
	{
		destroyRenderInstance();
	}
	//-----------------------------------------------------------------------
	bool ImpactPointLightModule::createRenderInstance()
	{
		return _createLight();
	}
	//-----------------------------------------------------------------------
	void ImpactPointLightModule::destroyRenderInstance()
	{
		_destroyLight();

		ImpactModule::destroyRenderInstance();
	}
	//-----------------------------------------------------------------------
	bool ImpactPointLightModule::_createLight(void)
	{
		assert ( NULL == mLight );

		if (mBasicNode)
		{
			//mLight = gSystemPtr->getSceneManager()->createLight( mBasicNode->getName() );
			mLight = EngineManager::getSingletonPtr()->getSceneManager()->createLight( mBasicNode->getName() );
			assert (mLight);

			mColourDelta1 = mColourEnd-mColourStart;
			mColourDelta2 = mColourStart - mColourEnd;
			mTimePass = 0;

			// 初始化光源信息
			mLight->setDiffuseColour(mDiffuse);
			mLight->setSpecularColour(mSpecular);
			if(Ogre::Math::RealEqual(mAttenuationConstant,0.0f)  && Ogre::Math::RealEqual(mAttenuationLinear,0.0f)  && Ogre::Math::RealEqual(mAttenuationQuadric,0.0f))
				mAttenuationConstant=1.0f;
			mLight->setAttenuation(mRange, mAttenuationConstant, mAttenuationLinear, mAttenuationQuadric);

			mLight->setCastShadows(false);

			mLight->setVisible(mVisible);

			mBasicNode->attachObject(mLight);

			mBasicNode->setPosition(mRelPos);
			mBasicNode->setOrientation(mRelOrientation);

			return true;
		}

		return false;
	}
	//-----------------------------------------------------------------------
	void ImpactPointLightModule::_destroyLight(void)
	{
		if (mLight)
		{
			assert(mLight->getParentSceneNode());
			assert(mLight->getParentSceneNode()->getCreator());
			mLight->getParentSceneNode()->getCreator()->destroyLight(mLight->getName());
			mLight = NULL;
		}
	}
	//-----------------------------------------------------------------------
	void ImpactPointLightModule::setDiffuse(const Ogre::ColourValue& diffuse)
	{
		mDiffuse = diffuse;

		if (mLight)
			mLight->setDiffuseColour(mDiffuse);
	}
	//-----------------------------------------------------------------------
	void ImpactPointLightModule::setSpecular(const Ogre::ColourValue& specular)
	{
		mSpecular = specular;

		if (mLight)
			mLight->setSpecularColour(mSpecular);
	}
	//-----------------------------------------------------------------------
	void ImpactPointLightModule::setRange(Real range)
	{
		mRange = range;

		if (mLight)
		{
			if(Ogre::Math::RealEqual(mAttenuationConstant,0.0f)  && Ogre::Math::RealEqual(mAttenuationLinear,0.0f)  && Ogre::Math::RealEqual(mAttenuationQuadric,0.0f))
				mAttenuationConstant=1.0f;
			mLight->setAttenuation(mRange, mAttenuationConstant, mAttenuationLinear, mAttenuationQuadric);
		}
	}
	//-----------------------------------------------------------------------
	void ImpactPointLightModule::setAttenuationConstant(Real constant)
	{
		mAttenuationConstant = constant;

		if (mLight)
		{
			if(Ogre::Math::RealEqual(mAttenuationConstant,0.0f)  && Ogre::Math::RealEqual(mAttenuationLinear,0.0f)  && Ogre::Math::RealEqual(mAttenuationQuadric,0.0f))
				mAttenuationConstant=1.0f;
			mLight->setAttenuation(mRange, mAttenuationConstant, mAttenuationLinear, mAttenuationQuadric);
		}
	}
	//-----------------------------------------------------------------------
	void ImpactPointLightModule::setAttenuationLinear(Real linear)
	{
		mAttenuationLinear = linear;

		if (mLight)
		{
			if(Ogre::Math::RealEqual(mAttenuationConstant,0.0f)  && Ogre::Math::RealEqual(mAttenuationLinear,0.0f)  && Ogre::Math::RealEqual(mAttenuationQuadric,0.0f))
				mAttenuationConstant=1.0f;
			mLight->setAttenuation(mRange, mAttenuationConstant, mAttenuationLinear, mAttenuationQuadric);
		}
	}
	//-----------------------------------------------------------------------
	void ImpactPointLightModule::setAttenuationQuadric(Real quadric)
	{
		mAttenuationQuadric = quadric;

		if (mLight)
		{
			if(Ogre::Math::RealEqual(mAttenuationConstant,0.0f)  && Ogre::Math::RealEqual(mAttenuationLinear,0.0f)  && Ogre::Math::RealEqual(mAttenuationQuadric,0.0f))
				mAttenuationConstant=1.0f;
			mLight->setAttenuation(mRange, mAttenuationConstant, mAttenuationLinear, mAttenuationQuadric);
		}
	}
	//-----------------------------------------------------------------------
	void ImpactPointLightModule::setVisibleFlag(uint32 flags)
	{
		if (mLight)
			mLight->setVisibilityFlags(flags);
	}
	//-----------------------------------------------------------------------
	///*
	char * ImpactPointLightModule::readFromBuffer(char * pCurrent)
	{
		pCurrent = ImpactModule::readFromBuffer(pCurrent);

		int length = sizeof(Ogre::ColourValue) * 4 + sizeof(Real) * 4 + sizeof(float);
		memcpy(&mDiffuse,pCurrent,length);
		pCurrent += length;

		return pCurrent;
	}
	//-----------------------------------------------------------------------
	void ImpactPointLightModule::saveToFile(std::ofstream & of)
	{
		ImpactModule::saveToFile(of);
		of.write((const char *)(&mDiffuse),sizeof(Ogre::ColourValue) * 4 + sizeof(Real) * 4 + sizeof(float));		
	}
	//*/
	bool ImpactPointLightModule::loadFromStream(Ogre::Serializer* pSerializer,Ogre::DataStreamPtr& stream)
	{
		if(pSerializer && stream->eof() == false)
		{
			unsigned short id = pSerializer->readChunk(stream);
			if(id != ImpactSerializer::EFF_POINTLIGHT_ELEMENT)
			{
				WARNING_LOG("Load PointLightElement From Stream Failed. ChunkId Error");
				// 因为不读取，所以直接跳过相应数据段长
				pSerializer->skipChunk(stream);
				return false;
			}
			//基类成员
			pSerializer->readData(stream,&mStartTime,1,sizeof(Ogre::Real));
			pSerializer->readData(stream,&mLifeTime,1,sizeof(Ogre::Real));
			pSerializer->readData(stream,&mRelPos,1,sizeof(Ogre::Vector3));
			pSerializer->readData(stream,&mRelOrientation,1,sizeof(Ogre::Quaternion));
			//自身成员
			pSerializer->readData(stream,&mDiffuse,1,sizeof(Ogre::ColourValue));
			pSerializer->readData(stream,&mSpecular,1,sizeof(Ogre::ColourValue));

			pSerializer->readData(stream,&mRange,1,sizeof(Ogre::Real));
			pSerializer->readData(stream,&mAttenuationConstant,1,sizeof(Ogre::Real));
			pSerializer->readData(stream,&mAttenuationLinear,1,sizeof(Ogre::Real));
			pSerializer->readData(stream,&mAttenuationQuadric,1,sizeof(Ogre::Real));

			pSerializer->readData(stream,&mColourStart,1,sizeof(Ogre::ColourValue));
			pSerializer->readData(stream,&mColourEnd,1,sizeof(Ogre::ColourValue));
			pSerializer->readData(stream,&mTimeChange,1,sizeof(float));						
			return true;	
		}
		return false;
	}
	bool ImpactPointLightModule::saveToBinaryFile(Ogre::Serializer* pSerializer)
	{
		
		return false;
	}
	std::size_t	ImpactPointLightModule::calcSerializedSize()
	{
		size_t tmpSize = Ogre::Serializer::STREAM_OVERHEAD_SIZE;
		//基类成员
		tmpSize += sizeof(mStartTime);
		tmpSize += sizeof(mLifeTime);
		tmpSize += sizeof(mRelPos);
		tmpSize += sizeof(mRelOrientation);
		//自身成员
		tmpSize += sizeof(mDiffuse);
		tmpSize += sizeof(mSpecular);
		tmpSize += sizeof(mRange);
		tmpSize += sizeof(mAttenuationConstant);
		tmpSize += sizeof(mAttenuationLinear);
		tmpSize += sizeof(mAttenuationQuadric);
		tmpSize += sizeof(mColourStart);
		tmpSize += sizeof(mColourEnd);
		tmpSize += sizeof(mTimeChange);
		return tmpSize;
	}

	//////////////////////////////////////////////////////////////////////////
	//-----------------------------------------------------------------------
	String ImpactPointLightModule::CmdDiffuse::doGet(const void* target) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const ImpactPointLightModule*>(target)->getDiffuse() );
	}
	void ImpactPointLightModule::CmdDiffuse::doSet(void* target, const String& val)
	{
		static_cast<ImpactPointLightModule*>(target)->setDiffuse(Ogre::StringConverter::parseColourValue(val));
	}
#if OGRE_STRING_INTERFACE_COPY
	//-----------------------------------------------------------------------
	void ImpactPointLightModule::CmdDiffuse::doCopy(void* target, const void* source)
	{
		static_cast<ImpactPointLightModule*>(target)->setDiffuse(
			static_cast<const ImpactPointLightModule*>(source)->getDiffuse() );
	}
#endif
	//-----------------------------------------------------------------------
	String ImpactPointLightModule::CmdSpecular::doGet(const void* target) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const ImpactPointLightModule*>(target)->getSpecular() );
	}
	void ImpactPointLightModule::CmdSpecular::doSet(void* target, const String& val)
	{
		static_cast<ImpactPointLightModule*>(target)->setSpecular(Ogre::StringConverter::parseColourValue(val));
	}
#if OGRE_STRING_INTERFACE_COPY
	//-----------------------------------------------------------------------
	void ImpactPointLightModule::CmdSpecular::doCopy(void* target, const void* source)
	{
		static_cast<ImpactPointLightModule*>(target)->setSpecular(
			static_cast<const ImpactPointLightModule*>(source)->getSpecular() );
	}
#endif
	//-----------------------------------------------------------------------
	String ImpactPointLightModule::CmdRange::doGet(const void* target) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const ImpactPointLightModule*>(target)->getRange() );
	}
	void ImpactPointLightModule::CmdRange::doSet(void* target, const String& val)
	{
		static_cast<ImpactPointLightModule*>(target)->setRange(Ogre::StringConverter::parseReal(val));
	}
#if OGRE_STRING_INTERFACE_COPY
	//-----------------------------------------------------------------------
	void ImpactPointLightModule::CmdRange::doCopy(void* target, const void* source)
	{
		static_cast<ImpactPointLightModule*>(target)->setRange(
			static_cast<const ImpactPointLightModule*>(source)->getRange() );
	}
#endif

	//-----------------------------------------------------------------------
	String ImpactPointLightModule::CmdAttenuationConstant::doGet(const void* target) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const ImpactPointLightModule*>(target)->getAttenuationConstant() );
	}
	void ImpactPointLightModule::CmdAttenuationConstant::doSet(void* target, const String& val)
	{
		static_cast<ImpactPointLightModule*>(target)->setAttenuationConstant(Ogre::StringConverter::parseReal(val));
	}
#if OGRE_STRING_INTERFACE_COPY
	//-----------------------------------------------------------------------
	void ImpactPointLightModule::CmdAttenuationConstant::doCopy(void* target, const void* source)
	{
		static_cast<ImpactPointLightModule*>(target)->setAttenuationConstant(
			static_cast<const ImpactPointLightModule*>(source)->getAttenuationConstant() );
	}
#endif

	//-----------------------------------------------------------------------
	String ImpactPointLightModule::CmdAttenuationLinear::doGet(const void* target) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const ImpactPointLightModule*>(target)->getAttenuationLinear() );
	}
	void ImpactPointLightModule::CmdAttenuationLinear::doSet(void* target, const String& val)
	{
		static_cast<ImpactPointLightModule*>(target)->setAttenuationLinear(Ogre::StringConverter::parseReal(val));
	}
#if OGRE_STRING_INTERFACE_COPY
	//-----------------------------------------------------------------------
	void ImpactPointLightModule::CmdAttenuationLinear::doCopy(void* target, const void* source)
	{
		static_cast<ImpactPointLightModule*>(target)->setAttenuationLinear(
			static_cast<const ImpactPointLightModule*>(source)->getAttenuationLinear() );
	}
#endif

	//-----------------------------------------------------------------------
	String ImpactPointLightModule::CmdAttenuationQuadric::doGet(const void* target) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const ImpactPointLightModule*>(target)->getAttenuationQuadric() );
	}
	void ImpactPointLightModule::CmdAttenuationQuadric::doSet(void* target, const String& val)
	{
		static_cast<ImpactPointLightModule*>(target)->setAttenuationQuadric(Ogre::StringConverter::parseReal(val));
	}
#if OGRE_STRING_INTERFACE_COPY
	//-----------------------------------------------------------------------
	void ImpactPointLightModule::CmdAttenuationQuadric::doCopy(void* target, const void* source)
	{
		static_cast<ImpactPointLightModule*>(target)->setAttenuationQuadric(
			static_cast<const ImpactPointLightModule*>(source)->getAttenuationQuadric() );
	}
#endif

	Ogre::ColourValue ImpactPointLightModule::__getColourValueByTime( float nTime )
	{
		//int n = nTime/
		nTime = fmod( nTime , (mTimeChange * 2) );
		nTime -= mTimeChange;
		if( nTime < 0 )
		{
			return mColourDelta1 *  ((mTimeChange+nTime) / mTimeChange) + mColourStart;
		}
		else
		{
			return mColourDelta2 *  ((nTime) / mTimeChange) + mColourEnd;
		}
	}

	void ImpactPointLightModule::OnParamChanged()
	{
		mColourDelta1 = mColourEnd-mColourStart;
		mColourDelta2 = mColourStart - mColourEnd;
	}

	void ImpactPointLightModule::update( Real time, TransformInfo &info )
	{
		__super::update( time, info );
		if( mTimeChange == 0 )
			return;
		mTimePass += time;
		Ogre::ColourValue clrCurrent = __getColourValueByTime( mTimePass );

		if (mLight)
			mLight->setDiffuseColour( clrCurrent );
	}
}