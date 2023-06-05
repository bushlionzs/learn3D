#include "OgreHeader.h"
#include "KObjectManager.h"
#include "kplayer.h"

template<>
KObjectManager* GameSingleton<KObjectManager>::m_sSingleton = NULL;

KObjectManager::KObjectManager()
{
	mPlayer = nullptr;
}

KObjectManager::~KObjectManager()
{

}

KObject* KObjectManager::createPlayer(int64_t id)
{
	auto player = new KPlayer();
	addObject(id, player);
	player->initialize();
	mPlayer = player;
	mPlayer->setId(id);
	
	return player;
}

KObject* KObjectManager::createNPC(int64_t id)
{
	return nullptr;
}

KObject* KObjectManager::createItem(int64_t id)
{
	return nullptr;
}

KObject* KObjectManager::getObject(int64_t id)
{
	auto itor = mObjectMap.find(id);
	if (itor != mObjectMap.end())
	{
		return itor->second;
	}

	return nullptr;
}

KPlayer* KObjectManager::getMySelf()
{
	return (KPlayer*)mPlayer;
}

void KObjectManager::update(float delta)
{
	for (auto& pair : mObjectMap)
	{
		pair.second->update(delta);
	}
}

bool KObjectManager::addObject(int64_t id, KObject* obj)
{
	auto itor = mObjectMap.insert(std::pair<int64_t, KObject*>(id, obj));
	assert(itor.second);
	return itor.second;
}