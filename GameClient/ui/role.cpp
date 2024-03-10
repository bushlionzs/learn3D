#include "OgreHeader.h"
#include "role.h"

#include "kplayer.h"

Role::Role(Ogre::SceneManager* sceneMgr)
{
	mSceneManager = sceneMgr;
}

Role::~Role()
{

}


void Role::updateRole()
{
	/*if (mSceneManager)
	{
		GameEntity* main = mPlayer->getMainEntity();
		Orphigine::SkeletonMeshActor* actor = main->getSkeletonMeshActor();
		Ogre::Vector3 pos = Ogre::Vector3(10.0, -100.0f, 0.0f);
		actor->setPosition(pos);
		actor->setSceneManager(mSceneManager);
		
	}*/
}



