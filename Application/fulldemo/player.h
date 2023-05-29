#pragma once

#include "OGActor.h"
#include "OGSkeletonMeshComponent.h"
#include "engine_manager.h"
#include "InputManager.h"
#include "PathComponent.h"
#include "demoHeader.h"
#include "TAB.h"
#include "demoHeader.h"
#include "CharacterCommon.h"
#include "InputManager.h"
#include "character.h"
#include "GameTableData.h"


class PathComponent;
class PlayerLogicModelHaveCreateCallback;

class GameEntity;

class Player: public Character
{

public:
	Player();
	~Player();

	void injectMousePress(int _absx, int _absy, OIS::MouseButtonID _id);
	void input(KeyCode _key);
private:
	void createCharRenderInterface(void);

	void UpdateFaceMesh(void);
	void UpdateHairMesh(void);

	int32 GetFashionHead(BODY_PART_MODEL part);
private:
	// 模型更新
	ModelPartDataList m_ModelPartDateList;

	/// CharRace表中的定义
	const _TABLE_CHAR_RACE* m_pCharRace;
};