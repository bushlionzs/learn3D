#pragma once

#include "InputManager.h"

class GameCamera;
class KPlayer;
class KObject;
class GameInput;
class GameWorld
{
public:
	GameWorld(GameCamera* gameCamera);
	~GameWorld();

	bool gameWorldInit();

	void update(float delta);
private:
	GameCamera* mGameCamera;
	KPlayer* mPlayer;
	KObject* mLastSelectObj = nullptr;
	GameInput* mGameInput;
};