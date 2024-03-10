#pragma once

class KPlayer;

class Role
{
public:
	Role(Ogre::SceneManager* sceneMgr);
	~Role();

	void createRoleData();

	void updateRole();

private:
	Ogre::SceneManager* mSceneManager;
};