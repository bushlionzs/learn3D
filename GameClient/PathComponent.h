#pragma once

class KCharacter;
class PathComponent
{
private:
	KCharacter* mCharacter = nullptr;
	std::vector<Ogre::Vector2> mPathList;
	int32_t mPathIndex = -1;
	
	Ogre::Real mfToRotation = 0.0;
	Ogre::Real mRotationSpeed = 10.0f;
public:
	PathComponent(KCharacter* character);
	~PathComponent();

	bool moveTo(Ogre::Vector2& ownerPos, Ogre::Vector2& targetPos);

	void update(float deltatime);

	void toFaceDir(Ogre::Real targetdir, Ogre::Real facedir);

	void updateToFaceDir(float deltatime);
private:
	Ogre::Real getFaceDir();
	void setFaceDir(Ogre::Real dir);
private:
	void calculateNodePos(const Ogre::Vector2& fvPosition, FLOAT fModifyHeight);
};