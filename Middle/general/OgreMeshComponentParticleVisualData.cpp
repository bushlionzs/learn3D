#include "OgreHeader.h"
#include "OgreMeshComponentParticleVisualData.h"
#include "OgreMaterialManager.h"
#include "OgreSceneManager.h"
#include "OgreRoot.h"
#include "OgreEntity.h"
#include "OgreSubEntity.h"
#include "OgreSubMesh.h"
#include "OgreHardwareBuffer.h"
#include "platform_log.h"
#include "engine_manager.h"
#include "OgreSceneNode.h"
#include "OgreAnimationState.h"

namespace Ogre	
{
	MeshComponentParticleVisualData::MeshComponentParticleVisualData() :
mSceneNode(NULL),
mEntity(NULL),
mInit(false),
mVisible(false),
mAnimtionState(NULL),
mPoolIndex(0),
mYawRotationSpeed(0),
mPitchRotationSpeed(0),
mRollRotationSpeed(0),
mYawRotation(0),
mPitchRotation(0),
mRollRotation(0),
mOrientation(Quaternion::IDENTITY),
mAnimationLoop(false),
mAnimationName(""),
mDeltaTime(0.0f),
mAnimSpeedFactor(1.0f), 
mAnimationUpdated(false)
{
}
//-----------------------------------------------------------------------
MeshComponentParticleVisualData::~MeshComponentParticleVisualData()
{
	destroyVisualData();		
}
//-----------------------------------------------------------------------
void MeshComponentParticleVisualData::createVisualData(const String &meshName, const String &matName, Node* parentNode)
{
	SceneManager* sceneMgr = EngineManager::getSingleton().getSceneManager();
	mSceneNode = sceneMgr->createSceneNode();

	parentNode->addChild(mSceneNode);

	if (!meshName.empty())
	{
		assert(false);
	}
	
	mEntity = sceneMgr->createEntity( mSceneNode->getName(), meshName );

	assert (mEntity);

	mSceneNode->attachObject(mEntity);

	cloneMaterial(matName);

	mEntity->setCastShadows(false);

	if(matName!="BaseWhite")
		mEntity->setMaterialName(mMaterial->getName());

	///fs在修改材质的时候改成material
	///mEntity->setMaterialName(mMaterial->getName());
	/*
	size_t numSubEntities=mEntity->getNumSubEntities();
	for(size_t i=0;i<numSubEntities;++i){
	Ogre::SubEntity* subEntity=mEntity->getSubEntity(i);
	const Ogre::MaterialPtr& material=subEntity->getMaterial();
	}*/

	mInit = true;
}
//-----------------------------------------------------------------------
void MeshComponentParticleVisualData::destroyVisualData(void)
{
	if (mInit)
	{
		assert(mEntity);
		assert (mSceneNode);
		mSceneNode->getCreator()->destroyMovableObject(mEntity);
		mEntity = NULL;
		mSceneNode->getCreator()->destroySceneNode(mSceneNode);

		mSceneNode = NULL;

		if (mMaterial)
			MaterialManager::getSingleton().remove(mMaterial->getHandle());

		mInit = false;
	}		
}
//-----------------------------------------------------------------------
void MeshComponentParticleVisualData::setPosition( const Vector3 &pos )
{
	mSceneNode->setPosition(pos);
}
//-----------------------------------------------------------------------
void MeshComponentParticleVisualData::setDirection( const Vector3 &dir, const Quaternion& parentOrientation )
{
	Vector3 yAdjustVec = dir;
	yAdjustVec.normalise();
	Vector3 xVec = mSceneNode->getQuaternion().zAxis().crossProduct( yAdjustVec );
	xVec.normalise();
	Vector3 zVec = xVec.crossProduct( yAdjustVec );
	zVec.normalise();   

	mOrientation = parentOrientation * Quaternion( xVec, yAdjustVec, zVec );
}
//-----------------------------------------------------------------------
void MeshComponentParticleVisualData::setScale( Real xzSize, Real ySize )
{
	mSceneNode->setScale(xzSize, ySize, xzSize);
}
//-----------------------------------------------------------------------
void MeshComponentParticleVisualData::setOrientation( const Radian &yaw, const Radian &pitch, const Radian &roll )
{
	Quaternion yawQuaternion(Degree(yaw.valueDegrees()), Vector3::UNIT_Y);
	Quaternion pitchQuaternion(Degree(pitch.valueDegrees()), Vector3::UNIT_X);
	Quaternion rollQuaternion(Degree(roll.valueDegrees()), Vector3::UNIT_Z);

	mSceneNode->setOrientation(yawQuaternion * pitchQuaternion * rollQuaternion);
}
//-----------------------------------------------------------------------
void MeshComponentParticleVisualData::setOrientation( const Quaternion& q )
{
	mOrientation = q;
}
//-----------------------------------------------------------------------
void MeshComponentParticleVisualData::setOrientation(bool rotate, const Quaternion& parentOrientation)
{
	if (rotate)
	{
		Quaternion yaw(Degree(mYawRotation.valueDegrees()), Vector3::UNIT_Y);
		Quaternion pitch(Degree(mPitchRotation.valueDegrees()), Vector3::UNIT_X);
		Quaternion roll(Degree(mRollRotation.valueDegrees()), Vector3::UNIT_Z);
		mSceneNode->setOrientation(yaw * pitch * roll * mOrientation);
	}
	else
		mSceneNode->setOrientation(mOrientation);
}
//-----------------------------------------------------------------------
void MeshComponentParticleVisualData::setVisible(bool visible)
{
	mVisible = visible;
	mSceneNode->setVisible(visible);
}

bool MeshComponentParticleVisualData::getVisible( void )
{
	return mVisible;
}

//-----------------------------------------------------------------------
void MeshComponentParticleVisualData::setColour( const ColourValue &colour )
{
}
//-----------------------------------------------------------------------
void MeshComponentParticleVisualData::modifyMesh(const String &meshName)
{
	assert(mEntity);
	Ogre::SceneNode* parent = mEntity->getParentSceneNode();
	assert(parent);
	Ogre::SceneManager* creator = parent->getCreator();
	assert(creator);
	parent->detachObject(mEntity->getName());
	creator->destroyMovableObject(mEntity);
	mEntity = NULL;

	mEntity = creator->createEntity( mSceneNode->getName(), meshName );

	assert (mEntity);
	mSceneNode->attachObject(mEntity);
}
//-----------------------------------------------------------------------
void MeshComponentParticleVisualData::modifyMaterial(const String &matName)
{
	assert(mEntity);

	if (mMaterial)
		MaterialManager::getSingleton().remove(mMaterial->getHandle());

	cloneMaterial(matName);
	mEntity->setMaterialName(mMaterial->getName());
}
//-----------------------------------------------------------------------
void MeshComponentParticleVisualData::updateAnimation(void)
{
	if (!mAnimtionState && mEntity)
	{            
		
		mAnimtionState = mEntity->getAnimationState(mAnimationName);

	}

	if (mAnimtionState)
	{
		mAnimtionState->setLoop(mAnimationLoop);
		if (false == mAnimtionState->getEnabled())
			mAnimtionState->setEnabled(true);
		mAnimtionState->addTime(mDeltaTime * mAnimSpeedFactor);
	}
}
//-----------------------------------------------------------------------
void MeshComponentParticleVisualData::resetAnimation(void)
{
	if (mAnimtionState)
	{
		mAnimationName = "";
		mAnimationLoop = false;
		mAnimationUpdated = false;

		mAnimtionState->setTimePosition(0.0f);
		mAnimtionState->setLoop(mAnimationLoop);
		mAnimtionState->setEnabled(false);
		mAnimtionState = NULL;
		mDeltaTime = 0.0f;
	}
}
//-----------------------------------------------------------------------
void MeshComponentParticleVisualData::cloneMaterial(const String& matName)
{
	MaterialPtr material;
	String materialName;

	if ( matName.empty() && (mEntity->getNumSubEntities() > 0) )
		materialName = mEntity->getSubEntity(0)->getMaterial()->getName();
	else
		materialName = matName;

	material = MaterialManager::getSingleton().getByName(materialName);			

	if (!material)
	{
		OGRE_EXCEPT(Exception::ERR_ITEM_NOT_FOUND,"Could not find material " + materialName,
			"MeshComponentParticleVisualData::cloneMaterial");
	}

	material = material->clone(mSceneNode->getName());
	mMaterial = material;
}
//-----------------------------------------------------------------------
void MeshComponentParticleVisualData::setRenderQueueGroup(uint8 queueID)
{
}

void MeshComponentParticleVisualData::setAnimationSpeedFactor( Real factor )
{
	mAnimSpeedFactor = factor;
}

bool MeshComponentParticleVisualData::isInit( void )
{
	return mInit;
}

void MeshComponentParticleVisualData::setPoolIndex( size_t index )
{
	mPoolIndex = index;
}

size_t MeshComponentParticleVisualData::getPoolIndex( void ) const
{
	return mPoolIndex;
}
}