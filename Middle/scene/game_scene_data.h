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
	bool mIsCTMFlag;	//是否行走面，用于提高优先级，默认为false
	bool mIsBatchMesh;	//是否是Batch Mesh
	Real	mTransparentTime;
	bool	mBEnableTransparent;

	Ogre::AxisAlignedBox mAxisAlignedBox;
};