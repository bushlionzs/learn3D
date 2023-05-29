#include "OgreHeader.h"
#include "OGLightActor.h"
#include "OGActorFactory.h"
#include "OgreDataStream.h"
#include "scene_serializer.h"

namespace Orphigine
{
	const String LightActor::msType = "Light";
	const String LightActor::msCategory = "Light";

	//////////////////////////////////////////////////////////////////////////
	// Factory
	//////////////////////////////////////////////////////////////////////////

	class LightActor::Factory : public ActorFactory
	{
	public:
		const String& getType(void) const
		{
			return msType;
		}

		Actor* createInstance(void)
		{
			return new LightActor;
		}
	};

	

	//////////////////////////////////////////////////////////////////////////
	// LightActor class
	//////////////////////////////////////////////////////////////////////////


	LightActor::LightActor(void)
		: Actor()
		, mDiffuse(Ogre::ColourValue::White)
		, mSpecular(Ogre::ColourValue::Black)
		, mPosition(Ogre::Vector3::ZERO)
		, mDirection(Ogre::Vector3::UNIT_Z)
		, mRange(100000.0f)
		, mAttenuationConstant(1.0f)
		, mAttenuationLinear(0.0f)
		, mAttenuationQuadric(0.0f)
		, mSpotOuterAngle(40.0f)
		, mSpotInnerAngle(30.0f)
		, mSpotFalloff(1.0f)
		, mCastShadows(false)
		, mStaticLight(false)
		, mIsAreaLightShadowFlag(true)
	{
		
	}
	//-----------------------------------------------------------------------
	LightActor::~LightActor()
	{
		destroyRenderInstance();
	}
	//-----------------------------------------------------------------------
	const String& LightActor::getType(void) const
	{
		return msType;
	}
	//-----------------------------------------------------------------------
	const String& LightActor::getCategory(void) const
	{
		return msCategory;
	}
	//-----------------------------------------------------------------------
	void LightActor::createRenderInstance()
	{
		
	}
	bool LightActor::loadFromStream(
		Serializer* pSerializer, 
		std::shared_ptr<DataStream>& stream,
		int32_t version)
	{	
		if(stream->eof() == false)
		{
			unsigned short chunkId = readChunk(stream);
			if(chunkId != SceneSerializer::SFF_LIGHT_OBJ)
			{
				skipChunk(stream);
				return false;
			}
			uint32_t lightType;
			pSerializer->readData(stream, &lightType, 1,sizeof(uint32_t));

			pSerializer->readData(stream,&mDiffuse,1,sizeof(Ogre::ColourValue));
			pSerializer->readData(stream,&mSpecular,1,sizeof(Ogre::ColourValue));

			pSerializer->readData(stream,&mPosition,1,sizeof(Ogre::Vector3));
			pSerializer->readData(stream,&mDirection,1,sizeof(Ogre::Vector3));



			pSerializer->readData(stream,&mRange,1,sizeof(Ogre::Real));
			pSerializer->readData(stream,&mAttenuationConstant,1,sizeof(Ogre::Real));
			pSerializer->readData(stream,&mAttenuationLinear,1,sizeof(Ogre::Real));
			pSerializer->readData(stream,&mAttenuationQuadric,1,sizeof(Ogre::Real));
			pSerializer->readData(stream,&mSpotOuterAngle,1,sizeof(Ogre::Real));
			pSerializer->readData(stream,&mSpotInnerAngle,1,sizeof(Ogre::Real));
			pSerializer->readData(stream,&mSpotFalloff,1,sizeof(Ogre::Real));


			pSerializer->readData(stream,&mCastShadows,1,sizeof(bool));
			pSerializer->readData(stream,&mStaticLight,1,sizeof(bool));
			pSerializer->readData(stream,&mIsAreaLightShadowFlag,1,sizeof(bool));
			return true;			
		}
		return false;		
	}
	bool LightActor::saveToBinaryFile(Serializer* pSerializer)
	{
		
		return false;		
	}	
	std::size_t	LightActor::calcSerializedSize()
	{
		/*size_t tmpSize = Ogre::Serializer::STREAM_OVERHEAD_SIZE;

		tmpSize += sizeof(mLightType);
		tmpSize += sizeof(mDiffuse);
		tmpSize += sizeof(mSpecular);
		tmpSize += sizeof(mPosition);
		tmpSize += sizeof(mDirection);

		tmpSize += sizeof(mRange);
		tmpSize += sizeof(mAttenuationConstant);
		tmpSize += sizeof(mAttenuationLinear);
		tmpSize += sizeof(mAttenuationQuadric);
		tmpSize += sizeof(mSpotOuterAngle);
		tmpSize += sizeof(mSpotInnerAngle);
		tmpSize += sizeof(mSpotFalloff);

		tmpSize += sizeof(mCastShadows);
		tmpSize += sizeof(mStaticLight);
		tmpSize += sizeof(mIsAreaLightShadowFlag);*/

		return 0;
	}
	//-----------------------------------------------------------------------
	void LightActor::createLight(void)
	{
		
	}
	//-----------------------------------------------------------------------
	void LightActor::destroyLight(void)
	{
		
	}
	//-----------------------------------------------------------------------
	void LightActor::destroyRenderInstance(void)
	{
		
	}
	//-----------------------------------------------------------------------
	void LightActor::updateRenderInstanceImpl(void)
	{
		
	}
	//-----------------------------------------------------------------------
	void LightActor::updateRenderInstance(void)
	{
		
	}
	//-----------------------------------------------------------------------
	uint32_t LightActor::getPropertyFlags(const String& name) const
	{
		return 0;
	}
	//-----------------------------------------------------------------------
	ActorFactory* LightActor::getFactory(void)
	{
		static Factory factory;
		return &factory;
	}

	Ogre::Quaternion LightActor::getOrientation() const
	{
		return Ogre::Quaternion::IDENTITY;
	}

	void LightActor::setOrientation(const Ogre::Quaternion& ori)
	{
		
	}

	Ogre::Vector3 LightActor::getScale() const
	{
		return Ogre::Vector3::UNIT_SCALE;
	}

	void LightActor::setScale(const Ogre::Vector3& scale)
	{
		
	}
}