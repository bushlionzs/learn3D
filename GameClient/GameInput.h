#pragma once

#include "GameSingleton.h"
#include "InputManager.h"
#include "Camp.h"

class KObject;
class GameInput :public InputListener
{
public:
	GameInput();
	~GameInput();
	void init();
	

	virtual void injectMouseMove(int _absx, int _absy, int _absz);
	virtual void injectMousePress(int _absx, int _absy, OIS::MouseButtonID _id);
	virtual void injectMouseRelease(int _absx, int _absy, OIS::MouseButtonID _id);
	virtual void injectKeyPress(KeyCode _key, uint32_t _text);
	virtual void injectKeyRelease(KeyCode _key);

	virtual void injectMouseWheel(int _absz);

	virtual void injectMouseCursor();
private:
	void input(KeyCode _key);
private:
	KObject* mLastSelectObj = nullptr;
	bool mSelectObjAttack = false;
	CampAndStandDataMgr* mCampAndStandDataMgr = nullptr;
};