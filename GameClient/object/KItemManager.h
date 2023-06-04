#pragma once

#include "GameSingleton.h"
class KItem;
class KObject;
class KItemManager :public GameSingleton<KItemManager>
{
public:
	KItemManager();
	~KItemManager();

	KItem* CreateNewItem(uint32 idTable);
	void DestroyItem(KItem* pItem);
private:
	bool addObject(int64_t id, KObject* obj);
	uint64_t AllotID(void);
private:
	std::unordered_map<int64_t, KObject*> mObjectMap;

	KObject* mPlayer;
};