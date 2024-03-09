#pragma once

class KPlayer;

class Role
{
public:
	Role(Ogre::SceneManager* sceneMgr);
	~Role();

	void createRoleData();

	void updateRole();

	KPlayer* getPlayer()
	{
		return mPlayer;
	}
private:
	KPlayer* mPlayer;
	Ogre::SceneManager* mSceneManager;
};