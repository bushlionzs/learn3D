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
};