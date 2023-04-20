#include "OgreHeader.h"
#include "OGParticleSystemActor.h"
#include "OGActorFactory.h"
#include "OgreDataStream.h"
#include "scene_serializer.h"


namespace Orphigine {

	const String ParticleSystemActor::msType = "ParticleSystem";
	const String ParticleSystemActor::msCategory = "StaticObject";

	//////////////////////////////////////////////////////////////////////////
	// Factory
	//////////////////////////////////////////////////////////////////////////

	class ParticleSystemActor::Factory : public ActorFactory
	{
	public:
		const String& getType(void) const
		{
			return msType;
		}

		Actor* createInstance(void)
		{
			return new ParticleSystemActor;
		}
	};

	


	//////////////////////////////////////////////////////////////////////////
	// ParticleSystemActor class
	//////////////////////////////////////////////////////////////////////////
	ParticleSystemActor::ParticleSystemActor(void)
		: PlacementActor(),
		mParticleSystem(NULL)
	{
		
	}
	//-----------------------------------------------------------------------
	ParticleSystemActor::~ParticleSystemActor()
	{
		destroyRenderInstance();
	}
	//-----------------------------------------------------------------------
	const String& ParticleSystemActor::getType(void) const
	{
		return msType;
	}
	//-----------------------------------------------------------------------
	const String& ParticleSystemActor::getCategory(void) const
	{
		return msCategory;
	}
	//-----------------------------------------------------------------------
	void ParticleSystemActor::createRenderInstance()
	{
		
	}
	//-----------------------------------------------------------------------
	void ParticleSystemActor::destroyRenderInstance(void)
	{
		if (mParticleSystem)
		{
			destroyParticleSystem();
		}

		PlacementActor::destroyRenderInstance();
	}
	bool ParticleSystemActor::loadFromStream(
		Serializer* pSerializer, 
		std::shared_ptr<DataStream>& stream,
		int32_t version)
	{		
		if(stream->eof() == false)
		{
			unsigned short id = pSerializer->readChunk(stream);
			if(id != SceneSerializer::SFF_PARTICLESYSTEM_OBJ)
			{
				pSerializer->skipChunk(stream);
				return false;
			}
			//基类成员
			pSerializer->readData(stream,&mTransform,1,sizeof(mTransform));
			pSerializer->readData(stream,&mCreateLevel,1,sizeof(Ogre::Real));
			//自身成员
			String strParticleSystemName = pSerializer->readStringBin(stream);
			setParticleSystemName(strParticleSystemName);
			return true;			
		}
		return false;			
	}
	bool ParticleSystemActor::saveToBinaryFile(Serializer* pSerializer)
	{
		
		return false;		
	}	
	std::size_t	ParticleSystemActor::calcSerializedSize()
	{
		return 0;
	}
	//-----------------------------------------------------------------------
	void ParticleSystemActor::createParticleSystem(void)
	{
		
	}
	//-----------------------------------------------------------------------
	void ParticleSystemActor::destroyParticleSystem(void)
	{
		
	}
	//-----------------------------------------------------------------------
	void ParticleSystemActor::setParticleSystemName( const String &name )
	{
		
	}
	//-----------------------------------------------------------------------
	ActorFactory* ParticleSystemActor::getFactory(void)
	{
		static Factory factory;
		return &factory;
	}
}
