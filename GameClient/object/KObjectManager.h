#pragma once

#include "GameSingleton.h"
class KObject;
class KPlayer;
class KObjectManager :public GameSingleton<KObjectManager>
{
public:
	KObjectManager();
	~KObjectManager();

	KObject* createPlayer(int64_t id);
	KObject* createNPC(int64_t id);
	KObject* createItem(int64_t id);

	KObject* getObject(int64_t id);
	KPlayer* getMySelf();

	void update(float delta);
private:
	bool addObject(int64_t id, KObject* obj);
private:
	std::unordered_map<int64_t, KObject*> mObjectMap;

	KObject* mPlayer;
};