#include "OgreHeader.h"
#include "OGActorFactoryManager.h"
#include "OGSKeletonMeshActor.h"
#include "OGImpactManager.h"
#include "player.h"
#include "OGAASCrossFadeByTimeListNode.h"
#include "OGAASCrossFadeByTimeSlotNode.h"
#include "OGSpell.h"
#include "engine_manager.h"
#include "GameTableData.h"
#include "ActionSetManager.h"
#include "GameTableManager.h"
#include "KTable.h"
#include "KDefine.h"
#include "OgreMeshManager.h"
#include "OgreEntity.h"
#include "game_scene_manager.h"
#include "game_scene.h"
#include "CharacterCommon.h"
#include "GameEntity.h"


class	PlayerAASAnimPlayCallback: public Orphigine::SkeletonMeshComponent::AASAnimEndCallback
{
public:
	virtual void	onAnimationEnd(const char* animName, const char* parentNodeType, const char* parentNodeName,
		uint64_t info)
	{

	}
};

Player::Player()
{
	//mousetarget

	mMouseNode = EngineManager::getSingleton().getBaseSceneNode()->createChildSceneNode("mouse");
	Ogre::String effectName = "reachable_projector";
	mProjectorEffect = Orphigine::ImpactManager::getSingleton().createEffect(effectName, 0);
	mProjectorEffect->createSceneNode(mMouseNode);
}

void CalculateNodePos(const vector3& fvPosition, FLOAT fModifyHeight, vector3& outPos)
{
	GameScene* activeScene = GameSceneManager::getSingleton().GetActiveScene();

		//当前位置
	vector3	fvCurObjPos = fvPosition;
	FLOAT	fInAirHeight = fvCurObjPos.y;

	//---------------------------------------------------
	//首先取得在地形上的高度

	FLOAT fHeight = -FLT_MAX;


	if (FALSE == activeScene->getCollision().Get3DMapHeight(fvPosition.x, fvCurObjPos.y, fvPosition.z, fHeight))
	{
		fHeight = fvPosition.y;
	}
	else
	{
		int kk = 0;
	}


	// 设置最终高度， 并且设置是否在行走面上的状态
	FLOAT fRealHeight = 0.0f;


	if (fHeight > fvPosition.y)
	{
		fRealHeight = fHeight;
	}
	else
	{
		fRealHeight = fvPosition.y;
	}

	outPos.x = fvPosition.x;
	outPos.y = fRealHeight + fModifyHeight;
	outPos.z = fvPosition.z;
}

void Player::injectMousePress(int _absx, int _absy, OIS::MouseButtonID _id)
{
	if (_id == OIS::MB_Left)
	{
		Ogre::Vector3 fvTarget;
		Ogre::Vector3 fvSource(_absx, _absy, 0);
		EngineManager::getSingleton().positionAxisTrans(GAT_SCREEN,
			fvSource, GAT_GAME, fvTarget);

		

		Ogre::Vector2 fvMyPos(mGamePosition.x, mGamePosition.z);
		Ogre::Vector2 fvTargetPos(fvTarget.x, fvTarget.z);

		mPathComponent->moveTo(fvMyPos, fvTargetPos);

		Ogre::Vector3 fvEnginePosition;
		EngineManager::getSingleton().positionAxisTrans(GAT_GAME,
			fvTarget, GAT_ENGINE, fvEnginePosition);
		Ogre::Vector3 modifyPosition;
		CalculateNodePos(fvEnginePosition, 0.0f, modifyPosition);


		mMouseNode->setPosition(fvEnginePosition);
		mMouseNode->updatechildren();
		ChangeAction(CA_MOVING, 0.0f);
		ChangeAction(CA_JUMP, 0.0f);
		ChangeAction(CA_MOVING, 1.0f);
		ChangeAction(CA_WALK, 0.0f, BASE_ACTION_N_RUN);
	}

}

void Player::input(KeyCode _key)
{
	if (_key == KeyCode::M)
	{
		startSkill();
	}
	else if (_key == KeyCode::N)
	{
		startMood();
	}
}

