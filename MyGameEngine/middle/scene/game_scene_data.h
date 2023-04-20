#pragma once

#include "OgreAxisAlignedBox.h"

class GameObjectData
{
public:
	GameObjectData();
	~GameObjectData();
public:
	Ogre::Vector3 mPosition;
	Ogre::Vector3 mScale;
	Ogre::Quaternion mOrientation;
};

class StaticEntryData : public GameObjectData
{
public:
	StaticEntryData();
	~StaticEntryData();
public:
	String mMeshName;
	Ogre::Real mAnimationLevel;
	Ogre::Real mTransparency;
	bool mCastShadows;
	bool mReceiveShadows;
	bool mReceiveDecals;
	bool mIsCTMFlag;	//�Ƿ������棬����������ȼ���Ĭ��Ϊfalse
	bool mIsBatchMesh;	//�Ƿ���Batch Mesh
	Real	mTransparentTime;
	bool	mBEnableTransparent;

	Ogre::AxisAlignedBox mAxisAlignedBox;
};