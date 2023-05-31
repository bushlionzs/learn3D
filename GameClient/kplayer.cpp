#include "OgreHeader.h"
#include "OGActorFactoryManager.h"
#include "OGSKeletonMeshActor.h"
#include "OGImpactManager.h"
#include "kplayer.h"
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
#include "Basics.h"
#include "Enum.h"
#include "data/GameDataCharacter.h"

class	PlayerAASAnimPlayCallback: public Orphigine::SkeletonMeshComponent::AASAnimEndCallback
{
public:
	virtual void	onAnimationEnd(const char* animName, const char* parentNodeType, const char* parentNodeName,
		uint64_t info)
	{

	}
};

KPlayer::KPlayer()
{
	//mousetarget

	mMouseNode = EngineManager::getSingleton().getBaseSceneNode()->createChildSceneNode("mouse");
	Ogre::String effectName = "reachable_projector";
	mProjectorEffect = Orphigine::ImpactManager::getSingleton().createEffect(effectName, 0);
	mProjectorEffect->createSceneNode(mMouseNode);
}

void CalculateNodePos(const Ogre::Vector3& fvPosition, FLOAT fModifyHeight, Ogre::Vector3& outPos)
{
	GameScene* activeScene = GameSceneManager::getSingleton().GetActiveScene();

		//当前位置
	Ogre::Vector3	fvCurObjPos = fvPosition;
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

void KPlayer::injectMousePress(int _absx, int _absy, OIS::MouseButtonID _id)
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

void KPlayer::input(KeyCode _key)
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

void KPlayer::createCharRenderInterface(void)
{
	KCharacter::createCharRenderInterface();

	UpdateFaceMesh();
	UpdateHairMesh();
	UpdateEquip(HEQUIP_MAINHAND);		// 主副 手
	UpdateEquip(HEQUIP_ASSIHAND);		// 主副 手
	UpdateEquip(HEQUIP_BACK);			// 躯干盔甲
	UpdateEquip(HEQUIP_SHOULDER);		// 肩
	UpdateEquip(HEQUIP_HAND);			// 手
	UpdateEquip(HEQUIP_FEET);			// 脚
}

void KPlayer::UpdateFaceMesh(void)
{
	int32 nFaceMeshID = GetFashionHead(BODY_PART_FACE);
	if (INVALID_ID == nFaceMeshID)
	{
		nFaceMeshID = GetCharacterData()->Get_FaceMesh();
	}

	if (INVALID_ID == nFaceMeshID)
	{
		nFaceMeshID = m_pCharRace->nDefHairGeo;
	}
	if (INVALID_ID != nFaceMeshID)
	{
		// 角色头部模型数据库
		const CGameTable* pCharHeadGeoTable = GAME_TABLE_MANAGER_PTR->GetTable(TABLE_CHARACTER_HEAD_GEO);
		if (NULL == pCharHeadGeoTable)
			return;

		// 查找相应记录
		const _TABLE_CHAR_HEAD_GEO* pFaceGeo = (const _TABLE_CHAR_HEAD_GEO*)pCharHeadGeoTable->GetFieldDataByIndex(nFaceMeshID);
		if (pFaceGeo)
		{
			m_ModelPartDateList.SetValue(BODY_PART_FACE, pFaceGeo->pMeshFile);
		}
		else
		{
			m_ModelPartDateList.SetValue(BODY_PART_FACE, "");
		}

	}
}

/*--------------------------------------------------
--------------------------------------------------*/
void KPlayer::UpdateHairMesh(void)
{
	int32 nHairMesh = GetFashionHead(BODY_PART_HAIR);
	if (INVALID_ID == nHairMesh)
	{
		nHairMesh = GetCharacterData()->Get_HairMesh();
	}
	if (INVALID_ID == nHairMesh)
	{
		nHairMesh = m_pCharRace->nDefHeadGeo;
	}
	if (INVALID_ID != nHairMesh)
	{
		// 角色头发模型数据库
		const CGameTable* pCharHairMeshTable = GAME_TABLE_MANAGER_PTR->GetTable(TABLE_CHARACTER_HAIR_GEO);
		if (NULL == pCharHairMeshTable)
			return;

		// 查找相应记录
		const _TABLE_CHAR_HAIR_GEO* pHairMesh = (const _TABLE_CHAR_HAIR_GEO*)pCharHairMeshTable->GetFieldDataByIndex(nHairMesh);
		if (pHairMesh)
		{
			m_ModelPartDateList.SetValue(BODY_PART_HAIR, pHairMesh->pMeshFile);
		}
		else
		{
			m_ModelPartDateList.SetValue(BODY_PART_HAIR, "");
		}
	}
}

int32 KPlayer::GetFashionHead(BODY_PART_MODEL part)
{
	if (BODY_PART_HAIR != part && BODY_PART_FACE != part)
		return INVALID_ID;

	if (FALSE == GetCharacterData()->Get_FashionIsShow())
		return INVALID_ID;

	int32 nEquipID = GetCharacterData()->Get_Equip(HEQUIP_SUIT);
	if (nEquipID < 0)
		return INVALID_ID;

	// 装备物品表
	const CGameTable* pItem_EquipTable = GAME_TABLE_MANAGER_PTR->GetTable(TABLE_ITEM_EQUIP);
	if (NULL == pItem_EquipTable)
		return INVALID_ID;

	const _TABLE_ITEM_EQUIP* pGEquip = (const _TABLE_ITEM_EQUIP*)pItem_EquipTable->GetFieldDataByIndex(nEquipID);
	if (NULL == pGEquip)
		return INVALID_ID;

	// 装备外形表
	const CGameTable* pItem_Visual = GAME_TABLE_MANAGER_PTR->GetTable(TABLE_ITEM_EQUIP_VISUAL);
	if (NULL == pItem_Visual)
		return INVALID_ID;

	const _TABLE_ITEM_EQUIP_VISUAL* pVisual = (const _TABLE_ITEM_EQUIP_VISUAL*)pItem_Visual->GetFieldDataByIndex(pGEquip->nID);
	if (NULL == pVisual)
		return INVALID_ID;

	// 外装表
	const CGameTable* pFashionTable = GAME_TABLE_MANAGER_PTR->GetTable(TABLE_CHAR_FASHION);
	if (NULL == pFashionTable)
		return INVALID_ID;

	const _TABLE_CHAR_FASHION* pFashion = (_TABLE_CHAR_FASHION*)pFashionTable->GetFieldDataByIndex(pVisual->nModelID);
	if (NULL == pFashion)
		return  INVALID_ID;

	int32 nID = INVALID_ID;
	if (BODY_PART_HAIR == part)
		nID = pFashion->nHair;
	else if (BODY_PART_FACE == part)
		nID = pFashion->nFace;

	// 形象配置表
	const CGameTable* pEquipItemTable = GAME_TABLE_MANAGER_PTR->GetTable(TABLE_ITEM_VISUAL_CHAR);
	if (NULL == pEquipItemTable)
		return INVALID_ID;

	const _TABLE_ITEM_VISUAL_CHAR* pEquipVisual = (const _TABLE_ITEM_VISUAL_CHAR*)pEquipItemTable->GetFieldDataByIndex(nID);
	if (NULL == pEquipVisual)
		return INVALID_ID;

	int32 nProfession = GetCharacterData()->GetProfession();
	int32 nGender = GetCharacterData()->Get_RaceID();

	switch (nProfession)
	{
	case PROFESSION_WUSHI:
	case PROFESSION_SHIZIJUN:
		return (nGender == GENDER_FEMALE) ? (pEquipVisual->pVisualEntityIndex[0]) : (pEquipVisual->pVisualEntityIndex[1]);
	case PROFESSION_JIANXIA:
	case PROFESSION_SHENGHUOSHI:
		return (nGender == GENDER_FEMALE) ? (pEquipVisual->pVisualEntityIndex[2]) : (pEquipVisual->pVisualEntityIndex[3]);
	case PROFESSION_QISHE:
	case PROFESSION_CIKE:
		return (nGender == GENDER_FEMALE) ? (pEquipVisual->pVisualEntityIndex[4]) : (pEquipVisual->pVisualEntityIndex[5]);
	case PROFESSION_HUOQIANG:
	case PROFESSION_JINWEIJUN:
		return (nGender == GENDER_FEMALE) ? (pEquipVisual->pVisualEntityIndex[6]) : (pEquipVisual->pVisualEntityIndex[7]);
	case PROFESSION_XIANZHI:
	case PROFESSION_YINXIUSHI:
		return (nGender == GENDER_FEMALE) ? (pEquipVisual->pVisualEntityIndex[8]) : (pEquipVisual->pVisualEntityIndex[9]);
	case PROFESSION_SAMAN:
	case PROFESSION_LAMA:
		return (nGender == GENDER_FEMALE) ? (pEquipVisual->pVisualEntityIndex[10]) : (pEquipVisual->pVisualEntityIndex[11]);
	}
	return INVALID_ID;
}
