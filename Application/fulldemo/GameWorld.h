#pragma once

#include "InputManager.h"

class GameCamera;
class Player;

class GameWorld: public InputListener
{
public:
	GameWorld(GameCamera* gameCamera);
	~GameWorld();

	bool gameWorldInit();

	void update(float delta);

private:
	virtual void injectMouseMove(int _absx, int _absy, int _absz);
	virtual void injectMousePress(int _absx, int _absy, OIS::MouseButtonID _id);
	virtual void injectMouseRelease(int _absx, int _absy, OIS::MouseButtonID _id);
	virtual void injectKeyPress(KeyCode _key, uint32_t _text);
	virtual void injectKeyRelease(KeyCode _key);

	virtual void injectMouseWheel(int _absz);
private:
	GameCamera* mGameCamera;
	Player* mPlayer;
};