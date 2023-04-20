#pragma once
#include "OgreSerializer.h"
class GameScene;
class SceneSerializer : public Serializer
{
public:
	enum SceneFileFormatEnum
	{
		SFF_FILEHEADER = 0x1000,// ÎÄ¼þÍ·
		SFF_SCENE = 0x0100,
		SFF_LIQUID_OBJ = 0x0200,
		SFF_ENVIROMENT_OBJ = 0x0300,
		SFF_LIGHT_OBJ = 0x0400,
		SFF_SKYDOME_OBJ = 0x0500,
		SFF_SKYBOX_OBJ = 0x0600,
		SFF_SKYPLANE_OBJ = 0x0700,
		SFF_STATICENTITY_OBJ = 0x0800,
		SFF_EFFECT_OBJ = 0x0900,
		SFF_LOGICMODEL_OBJ = 0x1000,
		SFF_DETAIL_OBJ = 0x1100,
		SFF_ACTOR_OBJ = 0x1200,
		SFF_MODEL_OBJ = 0x1300,
		SFF_PARTICLESYSTEM_OBJ = 0x1400,
		SFF_SKYLAYER_OBJ = 0x1500,
	};
public:
	SceneSerializer();
	~SceneSerializer();

	void import(std::shared_ptr<DataStream>& stream, GameScene* pScene);

private:
	void loadObject(std::shared_ptr<DataStream>& stream, GameScene* pScene);
	void loadStaticEntry(std::shared_ptr<DataStream>& stream, GameScene* pScene);
	String	getObjectTypeFromChunkId(uint32_t chunkId);

private:
	int32_t mSceneVersion;
};