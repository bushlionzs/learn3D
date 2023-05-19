#pragma once

class GameEntity;
class GameObject
{
public:
	GameObject();
	~GameObject();

	void setPosition(const Ogre::Vector3& pos);
	const Ogre::Vector3& getPosition();
	void setOrientation(const Ogre::Vector3& dir);
	const Ogre::Vector3& getOrientation();
private:
	GameEntity* mGameEntity;

	int64_t mServerId;
	int64_t mLocalId;


	Ogre::Vector3 mPosition;
	Ogre::Vector3 mOrientation;
};