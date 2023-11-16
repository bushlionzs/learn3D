#include "OgreHeader.h"
#include "OGEffectActor.h"
#include "OGActorFactory.h"
#include "OgreDataStream.h"
#include "scene_serializer.h"
#include "OGImpactManager.h"
#include "OGImpact.h"


namespace Orphigine {

	const String EffectActor::msType = "Effect";
	const String EffectActor::msCategory = "StaticObject";

	//////////////////////////////////////////////////////////////////////////
	// Factory
	//////////////////////////////////////////////////////////////////////////

	class EffectActor::Factory : public ActorFactory
	{
	public:
		const String& getType(void) const
		{
			return msType;
		}

		Actor* createInstance(void)
		{
			return new EffectActor;
		}
	};

	EffectActor::EffectActor()
	{
		mEffect = nullptr;
	}

	EffectActor::~EffectActor()
	{

	}

	const String& EffectActor::getType(void) const
	{
		return msType;
	}

	const String& EffectActor::getCategory(void) const
	{
		return msCategory;
	}

	void EffectActor::createRenderInstance()
	{
		return;
		PlacementActor::createRenderInstance();

		
		if (!mEffectName.empty())
		{
			createEffect();
		}
	}

	void EffectActor::destroyRenderInstance(void)
	{

	}

	bool EffectActor::loadFromStream(
		Serializer* pSerializer, 
		std::shared_ptr<DataStream>& stream,
		int32_t version)
	{
		if(stream->eof() == false)
		{
			unsigned short chunkId = pSerializer->readChunk(stream);
			if(chunkId != SceneSerializer::SFF_EFFECT_OBJ)
			{
	
				pSerializer->skipChunk(stream);
				return false;
			}
			//基类成员
			pSerializer->readData(stream,&mTransform,1,sizeof(mTransform));
			pSerializer->readData(stream,&mCreateLevel,1,sizeof(Ogre::Real));
			//自身成员
			String strName=pSerializer->readStringBin(stream);
			setEffectName(strName);
			return true;			
		}
		return false;			

	}
	bool EffectActor::saveToBinaryFile(Serializer* pSerializer)
	{
		
		return false;	
	}
	std::size_t	EffectActor::calcSerializedSize()
	{
		
		return 0;
	}
	//-----------------------------------------------------------------------
	void EffectActor::createEffect(void)
	{
		assert(mEffect == NULL);
		assert(!mEffectName.empty());

		Ogre::SceneNode* parent = getSceneNode();

		if (parent)
		{
			mEffect = ImpactManager::getSingleton().addEffect(mEffectName);
			
			if (!mEffect)
			{
				WARNING_LOG("fail to load effect:%s", mEffectName.c_str());
				return;
			}

			Orphigine::TransformInfos tempTransformInfos;
			Orphigine::TransformInfo tempTransformInfo(Ogre::Vector3::ZERO);
			tempTransformInfos.push_back(tempTransformInfo);
			mEffect->setExtraTransformInfos(tempTransformInfos);

			// the scene node of placement object will be the parent scene node of
			// effect object, so the position of the scene node will be the position of
			// the effect.
			mEffect->createSceneNode(parent);
		}
	}
	//-----------------------------------------------------------------------
	void EffectActor::destroyEffect(void)
	{

	}
	//-----------------------------------------------------------------------
	void EffectActor::setEffectName( const String &name )
	{
		if (mEffectName != name)
		{
			if (mEffect)
			{
				destroyEffect();
			}

			mEffectName = name;

			if (!mEffectName.empty())
			{
				createEffect();
			}
		}
	}
	//-----------------------------------------------------------------------
	ActorFactory* EffectActor::getFactory(void)
	{
		static Factory factory;
		return &factory;
	}
}
