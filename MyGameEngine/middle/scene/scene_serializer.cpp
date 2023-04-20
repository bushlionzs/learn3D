#include "OgreHeader.h"
#include "scene_serializer.h"
#include "OgreDataStream.h"
#include "game_scene.h"
#include "game_scene_data.h"
#include "OGActorFactoryManager.h"

SceneSerializer::SceneSerializer()
{
	mVersion = "[SceneSerializer_v1.00]";
}

SceneSerializer::~SceneSerializer()
{

}

void SceneSerializer::import(std::shared_ptr<DataStream>& stream, GameScene* pScene)
{
	unsigned short headerID = 0;
	readShorts(stream, &headerID, 1);
	if (headerID != HEADER_STREAM_ID)
	{
		OGRE_EXCEPT(Exception::ERR_INTERNAL_ERROR, "scene header error");
	}

	String version = readStringBin(stream);

	mSceneVersion = 100;
	std::set<String> versions = { "[SceneSerializer_v1.00]" , "[SceneSerializer_v1.03]" };
	if (!versions.count(version))
	{
		OGRE_EXCEPT(Exception::ERR_INTERNAL_ERROR, "scene version error");
	}

	if (version == "[SceneSerializer_v1.03]")
	{
		mSceneVersion = 103;
	}
	String FileType = readStringBin(stream);
	String CopyRight = readStringBin(stream);


	auto chunkId = readChunk(stream);
	if (chunkId != SFF_SCENE)
	{
		OGRE_EXCEPT(Exception::ERR_INTERNAL_ERROR, "scene chunk error");
	}

	pScene->mSceneName = readStringBin(stream);
	pScene->mTerrainFilename = readStringBin(stream);

	loadObject(stream, pScene);
}

void SceneSerializer::loadObject(std::shared_ptr<DataStream>& stream, GameScene* pScene)
{
	int32_t index = 0;
	while (!stream->eof())
	{
		//¶ÁÈ¡ÀàÐÍ
		int64_t pos = stream->tell();

		uint32_t size = stream->getStreamLength();

		if (pos >= size)
		{
			break;
		}

		index++;
		if (index == 1190)
		{
			int kk = 0;
		}
		uint32_t chunkId = readChunk(stream);

		String ObjType = getObjectTypeFromChunkId(chunkId);
		Orphigine::ActorPtr object =
			Orphigine::ActorFactoryManager::getSingleton().createInstance(ObjType);
		Ogre::String name;

		if (object)
		{
			stream->seek(pos);
			if (!object->loadFromStream(this, stream, mSceneVersion))
			{
				int kk = 0;
			}

			name = readStringBin(stream);
			
			object->setName(name);

			pScene->addObject(object);
		}
		else
		{
			assert(false);
		}
	}
}


void SceneSerializer::loadStaticEntry(std::shared_ptr<DataStream>& stream, GameScene* pScene)
{
	uint32_t id = readChunk(stream);
	if (id != SFF_STATICENTITY_OBJ)
	{
		OGRE_EXCEPT(Exception::ERR_INTERNAL_ERROR, "static entry type error");
	}

	StaticEntryData* data = new StaticEntryData;

	readObject(stream, data->mPosition);
	readObject(stream, data->mOrientation);
	readObject(stream, data->mScale);
	data->mMeshName = readStringBin(stream);
	readData(stream, &data->mAnimationLevel, 1, sizeof(Ogre::Real));
	readData(stream, &data->mTransparency, 1, sizeof(Ogre::Real));

	readData(stream, &data->mCastShadows, 1, sizeof(bool));
	readData(stream, &data->mReceiveShadows, 1, sizeof(bool));
	readData(stream, &data->mReceiveDecals, 1, sizeof(bool));
	readData(stream, &data->mIsCTMFlag, 1, sizeof(bool));

	Ogre::Vector3 AABBmin;
	Ogre::Vector3 AABBmax;
	bool  isNull = true;
	char temp[3] = { 0 , 0 };
	readData(stream, &AABBmin, 1, sizeof(Ogre::Vector3));
	readData(stream, &AABBmax, 1, sizeof(Ogre::Vector3));
	readData(stream, &isNull, 1, sizeof(bool));
	readData(stream, temp, 3, sizeof(char));
	data->mAxisAlignedBox.setMinimum(AABBmin);
	data->mAxisAlignedBox.setMaximum(AABBmax);
	readData(stream, &data->mTransparentTime, 1, sizeof(Ogre::Real));
	readData(stream, &data->mBEnableTransparent, 1, sizeof(bool));
}

String	SceneSerializer::getObjectTypeFromChunkId(uint32_t chunkId)
{
	switch (chunkId)
	{
	case SFF_LIQUID_OBJ:
		return "TerrainLiquid";
		break;
	case SFF_ENVIROMENT_OBJ:
		return "Enviroment";
		break;
	case SFF_LIGHT_OBJ:
		return "Light";
		break;
	case SFF_SKYDOME_OBJ:
		return "SkyDome";
		break;
	case SFF_SKYBOX_OBJ:
		return "SkyBox";
		break;
	case SFF_SKYPLANE_OBJ:
		return "SkyPlane";
		break;
	case SFF_STATICENTITY_OBJ:
		return "StaticEntity";
		break;
	case SFF_EFFECT_OBJ:
		return "Effect";
		break;
	case SFF_LOGICMODEL_OBJ:
		return "SkeletonMeshComponent";
		break;
	case SFF_DETAIL_OBJ:
		return "DetailObject";
		break;
	case SFF_ACTOR_OBJ:
		return "Actor";
		break;
	case SFF_MODEL_OBJ:
		return "Model";
		break;
	case SFF_PARTICLESYSTEM_OBJ:
		return "ParticleSystem";
		break;
	case SFF_SKYLAYER_OBJ:
		return "SkyLayer";
		break;
	default:
	{
		assert(false);
		static String type("UnknownObjectType");
		return type;
	}
	break;
	}
}