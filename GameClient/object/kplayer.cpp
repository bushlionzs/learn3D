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
#include "GameEntity.h"
#include "KItemEquip.h"
#include "KItemManager.h"

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

	mObjectType = ObjectType_PlayerOfMe;
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
	if (!mMainEntity)
	{
		mMainEntity = std::make_shared<GameEntity>();
	}
	const CGameTable* pCharModelTable = GAME_TABLE_MANAGER_PTR->GetTable(TABLE_CHARACTER_MODEL);
	if (NULL == pCharModelTable)
	{
		return;
	}

	LPCSTR lpszModelFileName = NULL;
	int32 nModelID = GetCurrCharModelID();

	// char_model.tab
	const _TABLE_CHARACTER_MODEL* pCharModel = (const _TABLE_CHARACTER_MODEL*)(pCharModelTable->GetFieldDataByIndex(nModelID));
	if (pCharModel != NULL)
	{
		lpszModelFileName = pCharModel->m_pszModelName;
	}

	if (lpszModelFileName)
	{
		auto position = EngineManager::getSingleton().getMyPosition();
		// 设置ActorFile
		mMainEntity->setModelName(lpszModelFileName);
		setPosition(position);
	
		m_ModelPartDateList.Clear();


		UpdateFaceMesh();
		UpdateHairMesh();
		UpdateEquip(HEQUIP_MAINHAND);		// 主副 手
		UpdateEquip(HEQUIP_ASSIHAND);		// 主副 手
		UpdateEquip(HEQUIP_BACK);			// 躯干盔甲
		UpdateEquip(HEQUIP_SHOULDER);		// 肩
		UpdateEquip(HEQUIP_HAND);			// 手
		UpdateEquip(HEQUIP_FEET);			// 脚

		
		UpdateBodyPartModel();

	}
	KCharacter::createCharRenderInterface();
}

void KPlayer::UpdateEquip(PLAYER_EQUIP point)
{
	KCharatcterBaseData* pCharacterData = GetCharacterData();
	if (pCharacterData == nullptr)
		return;

	if (point < 0 || point >= HEQUIP_NUMBER)
		return;

	int32 nVisualID = INVALID_ID;
	int32 nEquipID = INVALID_ID;
	KItemEquip* pTempEquip = nullptr;


	// 变身时可换的部件
	if (INVALID_ID != GetCharacterData()->Get_ModelID())
	{
		if (FALSE == isCanUpdateEquipByModelID(point))
			return;

		nVisualID = GetWeaponIDByModelID(point);
	}
	// 外装的部件
	if (INVALID_ID == nVisualID)
	{
		nVisualID = GetFashionEquipParth(point);
	}
	// 当前的装备部件
	if (0 > nVisualID)
	{
		nEquipID = pCharacterData->Get_Equip(point);
		if (INVALID_ID != nEquipID)
		{
			pTempEquip = (KItemEquip*)KItemManager::GetSingleton().CreateNewItem(nEquipID);
			if (pTempEquip  && pTempEquip->GetTermTime() != 1)
			{
				nVisualID = pTempEquip->GetVisualID();
			}
		}
	}


	// 如果是装备根据装配点装备物品
	if (nVisualID > 0)
	{
		switch (point)
		{
			//主手
		case HEQUIP_MAINHAND:
		{
			ENUM_WEAPON_LOCATOR_TYPE eWeaponType = WL_RIGHT;
			if (FALSE == isRightHandHabit())
				eWeaponType = WL_LEFT;

			EquipItem_BodyLocator(nEquipID, nVisualID, eWeaponType);
		}
		break;
		// 副手武器, 盾
		case HEQUIP_ASSIHAND:
		{
			ENUM_WEAPON_LOCATOR_TYPE eWeaponType = WL_LEFT;

			if (pTempEquip && pTempEquip->IsDefence())
				eWeaponType = WL_L_ARM;
			else if (FALSE == isRightHandHabit())
				eWeaponType = WL_RIGHT;

			EquipItem_BodyLocator(nEquipID, nVisualID, eWeaponType);
		}
		break;
		// 身体, 手臂, 鞋, 装备类物品
		case HEQUIP_BACK:
		case HEQUIP_HAND:
		case HEQUIP_FEET:
		case HEQUIP_SHOULDER:
		{
			EquipItem_BodyPart(point, nVisualID);
			DelEquipEffect(point);
			SetBodyEquipEffect(nEquipID, point);
		}
		break;
		default:
			break;
		}
	}
	else if (0 == nVisualID)
	{
		DelEquipEffect(point);
		// 卸载装备
		UnEquipItem(point, FALSE);

	}
	else
	{
		DelEquipEffect(point);
		UnEquipItem(point);
	}

	mMainEntity->Weapon_SetAasAnim(GetMainWeaponType());

	KItemManager::GetSingleton().DestroyItem(pTempEquip);

	// 刷新可见
	if (IsModelCreateAllCompleted())
	{
		UpdateModel_Visible();
	}
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

bool KPlayer::isRightHandHabit()
{
	//骑射的特例
	int32 nProfession = GetCharacterData()->GetProfession();
	if (PROFESSION_QISHE == (PROFESSION_TYPE)nProfession)
	{
		return false;
	}
	return true;
}

int32 KPlayer::GetWeaponIDByModelID(PLAYER_EQUIP point)
{
	int32 nModelID = GetCharacterData()->Get_ModelID();
	if (INVALID_ID == nModelID)
		return INVALID_ID;

	const CGameTable* pCharModelTable = GAME_TABLE_MANAGER_PTR->GetTable(TABLE_CHARACTER_MODEL);
	if (NULL == pCharModelTable)
		return INVALID_ID;

	const _TABLE_CHARACTER_MODEL* pCharModel = (const _TABLE_CHARACTER_MODEL*)(pCharModelTable->GetFieldDataByIndex(nModelID));
	if (NULL == pCharModel)
		return INVALID_ID;

	// 变身是否指定了武器
	if (0 >= pCharModel->m_nCheckWeapon)
		return INVALID_ID;

	if (HEQUIP_MAINHAND == point)
	{
		// 有主手武器时，有效
		int32 nEquipID = GetCharacterData()->Get_Equip(HEQUIP_MAINHAND);
		if (INVALID_ID != nEquipID)
		{
			return pCharModel->m_nCheckWeapon;
		}

	}
	else if (HEQUIP_ASSIHAND == point)
	{
		// 有副手武器时，有效
		int32 nEquipID = GetCharacterData()->Get_Equip(HEQUIP_ASSIHAND);
		if (INVALID_ID != nEquipID)
		{
			return pCharModel->m_nCheckWeapon;
		}
	}
	return INVALID_ID;
}

bool KPlayer::isCanUpdateEquipByModelID(PLAYER_EQUIP point)
{
	// 变身时，检测是否能挂接武器
	int32 nModelID = GetCharacterData()->Get_ModelID();
	if (INVALID_ID == nModelID)
		return true;

	const CGameTable* pCharModelTable = GAME_TABLE_MANAGER_PTR->GetTable(TABLE_CHARACTER_MODEL);
	if (NULL == pCharModelTable)
		return true;

	const _TABLE_CHARACTER_MODEL* pCharModel = (const _TABLE_CHARACTER_MODEL*)(pCharModelTable->GetFieldDataByIndex(nModelID));
	if (NULL == pCharModel)
		return true;

	// 详情见 m_nCheckWeapon 规程
	if (0 > pCharModel->m_nCheckWeapon)
	{
		return false;
	}
	else
	{
		if (HEQUIP_MAINHAND == point || HEQUIP_ASSIHAND == point)
			return true;
	}
	return false;
}

bool KPlayer::isCanUpdatePartModelByModelID(BODY_PART_MODEL part)
{
	// 变身时，检测是否能挂接武器
	int32 nModelID = GetCharacterData()->Get_ModelID();
	if (INVALID_ID == nModelID)
		return true;

	const CGameTable* pCharModelTable = GAME_TABLE_MANAGER_PTR->GetTable(TABLE_CHARACTER_MODEL);
	if (NULL == pCharModelTable)
		return true;

	const _TABLE_CHARACTER_MODEL* pCharModel = (const _TABLE_CHARACTER_MODEL*)(pCharModelTable->GetFieldDataByIndex(nModelID));
	if (NULL == pCharModel)
		return true;

	if (0 > pCharModel->m_nCheckWeapon)
		return false;

	if (BODY_PART_RIGHTHAND == part ||
		BODY_PART_LEFTHAND == part ||
		BODY_PART_SHIELD == part)
	{
		return true;
	}
	return false;
}

void KPlayer::UpdateBodyPartModel()
{
	std::vector<String> vName;
	std::vector<String> vValue;

	// 更新模型
	for (int32 i = 0; i < BODY_PART_NUMBER; ++i)
	{
		if (m_ModelPartDateList.m_ModelPartData[i].IsFlag() && isCanUpdatePartModelByModelID((BODY_PART_MODEL)i))
		{
			vName.push_back(m_ModelPartDateList.m_strPartName[i]);
			vValue.push_back(m_ModelPartDateList.m_ModelPartData[i].m_strValue);
		}
	}

	if (vName.empty() || vValue.empty())
	{
		m_ModelPartDateList.Update();
		return;
	}
	mMainEntity->changeAttributes(vName, vValue);
	m_ModelPartDateList.Update();
}

int32 KPlayer::GetFashionEquipParth(PLAYER_EQUIP point)
{
	KCharatcterBaseData* pCharacterData = GetCharacterData();
	if (NULL == pCharacterData)
		return INVALID_ID;

	if (FALSE == pCharacterData->Get_FashionIsShow())
		return INVALID_ID;

	int32 nEquipID = pCharacterData->Get_Equip(HEQUIP_SUIT);
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

	int32 nVisual = INVALID_ID;

	switch (PLAYER_EQUIP(point))
	{
	case HEQUIP_BACK:
		nVisual = pFashion->nBody;
		break;
	case HEQUIP_HAND:
		nVisual = pFashion->nHand;
		break;
	case HEQUIP_FEET:
		nVisual = pFashion->nFoot;
		break;
	case HEQUIP_SHOULDER:
		nVisual = pFashion->nShoulder;
		break;
	case HEQUIP_MAINHAND:
	{
		// 有主手武器时，更换为外装武器
		nEquipID = pCharacterData->Get_Equip(HEQUIP_MAINHAND);
		if (INVALID_ID == nEquipID)
			break;

		// 根据职业读取不同的列
		int32 nProfession = pCharacterData->GetProfession();
		if (nProfession < 0 || nProfession >= PROFESSION_NUMBER)
			return INVALID_ID;

		switch (nProfession)
		{
		case PROFESSION_WUSHI:
			nVisual = pFashion->nWuShi_RightWeapon;
			break;
		case PROFESSION_JIANXIA:
			nVisual = pFashion->nJianXia_RightWeapon;
			break;
		case PROFESSION_QISHE:
			nVisual = pFashion->nQiShe_LeftWeapon;
			break;
		case PROFESSION_HUOQIANG:
			nVisual = pFashion->nHuoQiang_RightWeapon;
			break;
		case PROFESSION_XIANZHI:
			nVisual = pFashion->nXianZhi_RightWeapon;
			break;
		case PROFESSION_SAMAN:
			nVisual = pFashion->nSheMan_RightWeapon;
			break;
		case PROFESSION_SHIZIJUN:
			nVisual = pFashion->nShiZiJun_RightWeapon;
			break;
		case PROFESSION_SHENGHUOSHI:
			nVisual = pFashion->nShengHuoShi_RightWeapon;
			break;
		case PROFESSION_CIKE:
			nVisual = pFashion->nCiKe_RightWeapon;
			break;
		case PROFESSION_JINWEIJUN:
			nVisual = pFashion->nJinWeiJun_RightWeapon;
			break;
		case PROFESSION_YINXIUSHI:
			nVisual = pFashion->nYinXiuShi_RightWeapon;
			break;
		case PROFESSION_LAMA:
			nVisual = pFashion->nLaMa_RightWeapon;
			break;
		}
	}
	break;
	case HEQUIP_ASSIHAND:
	{
		// 有副手武器时，更换为外装武器
		nEquipID = pCharacterData->Get_Equip(HEQUIP_ASSIHAND);
		if (INVALID_ID == nEquipID)
			break;

		// 根据职业读取不同的列
		int32 nProfession = pCharacterData->GetProfession();
		if (nProfession < 0 || nProfession >= PROFESSION_NUMBER)
			return INVALID_ID;

		switch (nProfession)
		{
		case PROFESSION_WUSHI:
			nVisual = pFashion->nWuShi_Shield;
			break;
		case PROFESSION_JIANXIA:
			nVisual = pFashion->nJianXia_LeftWeapon;
			break;
		case PROFESSION_QISHE:
			nVisual = INVALID_ID;
			break;
		case PROFESSION_HUOQIANG:
			nVisual = INVALID_ID;
			break;
		case PROFESSION_XIANZHI:
			nVisual = pFashion->nXianZhi_LeftWeapon;
			break;
		case PROFESSION_SAMAN:
			nVisual = pFashion->nShaMan_LeftWeapon;
			break;
		case PROFESSION_SHIZIJUN:
			nVisual = pFashion->nWuShi_Shield;
			break;
		case PROFESSION_SHENGHUOSHI:
			nVisual = pFashion->nShengHuoShi_LeftWeapon;
			break;
		case PROFESSION_CIKE:
			nVisual = pFashion->nCiKe_LeftWeapon;
			break;
		case PROFESSION_JINWEIJUN:
			nVisual = pFashion->nJinWeiJun_LeftWeapon;
			break;
		case PROFESSION_YINXIUSHI:
			nVisual = pFashion->nYinXiuShi_LeftWeapon;
			break;
		case PROFESSION_LAMA:
			nVisual = pFashion->nLaMa_LeftWeapon;
			break;
		}
	}
	break;
	default:
		break;
	}
	return nVisual;
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

void KPlayer::EquipItem_BodyLocator(
	int32_t nEquipId,
	int32_t nWeaponId,
	ENUM_WEAPON_LOCATOR_TYPE loc, 
	bool bUpdateWeaponAnimType)
{
	if (nullptr == mMainEntity)
		return;

	const CGameTable* pWeaponItemTable = GAME_TABLE_MANAGER_PTR->GetTable(TABLE_ITEM_VISUAL_LOCATOR);
	if (NULL == pWeaponItemTable)
		return;

	const _TABLE_ITEM_VISUAL_LOCATOR* pEquipVisual = (_TABLE_ITEM_VISUAL_LOCATOR*)pWeaponItemTable->GetFieldDataByIndex(nWeaponId);
	if (NULL == pEquipVisual)
		return;

	BOOL bHaveRightWeapon = FALSE;
	BOOL bHaveLeftWeapon = FALSE;

	LPCSTR pObjFile_Right = NULL;
	if (GENDER_MALE == GetCharacterData()->Get_RaceID())
		pObjFile_Right = pEquipVisual->pObjFile_Right_Man;
	else
		pObjFile_Right = pEquipVisual->pObjFile_Right_Woman;

	LPCSTR pObjFile_Left = NULL;
	if (GENDER_MALE == GetCharacterData()->Get_RaceID())
		pObjFile_Left = pEquipVisual->pObjFile_Left_Man;
	else
		pObjFile_Left = pEquipVisual->pObjFile_Left_Woman;

	switch (pEquipVisual->nWeaponPointType)
	{
		// 右手武器
	case WL_RIGHT:
	{
		if (pObjFile_Right && pObjFile_Right[0] != '\0')
		{
			m_ModelPartDateList.SetValue(BODY_PART_RIGHTHAND, pObjFile_Right);
			m_ModelPartDateList.SetValue(BODY_PART_RIGHTHAND, nEquipId);

			bHaveRightWeapon = TRUE;
		}
		else
		{
			m_ModelPartDateList.SetValue(BODY_PART_RIGHTHAND, "");
			m_ModelPartDateList.SetValue(BODY_PART_RIGHTHAND, INVALID_ID);
		}
	}
	break;
	// 左手武器
	case WL_LEFT:
	{
		if (pObjFile_Left && pObjFile_Left[0] != '\0')
		{
			m_ModelPartDateList.SetValue(BODY_PART_LEFTHAND, pObjFile_Left);
			m_ModelPartDateList.SetValue(BODY_PART_LEFTHAND, nEquipId);

			bHaveLeftWeapon = TRUE;
		}
		else
		{
			m_ModelPartDateList.SetValue(BODY_PART_LEFTHAND, "");
			m_ModelPartDateList.SetValue(BODY_PART_LEFTHAND, INVALID_ID);
		}
	}
	break;
	// 左手盾
	case WL_L_ARM:
	{
		if (pEquipVisual->pObjShieldFile && pEquipVisual->pObjShieldFile[0] != '\0')
		{
			m_ModelPartDateList.SetValue(BODY_PART_SHIELD, pEquipVisual->pObjShieldFile);
			m_ModelPartDateList.SetValue(BODY_PART_SHIELD, nEquipId);
		}
		else
		{
			m_ModelPartDateList.SetValue(BODY_PART_SHIELD, "");
			m_ModelPartDateList.SetValue(BODY_PART_SHIELD, INVALID_ID);
		}
	}
	break;
	// 遍历, 自动匹配
	case WL_DEFAULT:
	{
		// 右手武器
		if (pObjFile_Right && pObjFile_Right[0] != '\0')
		{
			m_ModelPartDateList.SetValue(BODY_PART_RIGHTHAND, pObjFile_Right);
			m_ModelPartDateList.SetValue(BODY_PART_RIGHTHAND, nEquipId);

			bHaveRightWeapon = TRUE;
		}
		// 左手武器
		if (pObjFile_Left && pObjFile_Left[0] != '\0')
		{
			m_ModelPartDateList.SetValue(BODY_PART_LEFTHAND, pObjFile_Left);
			m_ModelPartDateList.SetValue(BODY_PART_LEFTHAND, nEquipId);

			bHaveLeftWeapon = TRUE;
		}
		// 左手盾
		if (pEquipVisual->pObjShieldFile && pEquipVisual->pObjShieldFile[0] != '\0')
		{
			m_ModelPartDateList.SetValue(BODY_PART_SHIELD, pEquipVisual->pObjShieldFile);
			m_ModelPartDateList.SetValue(BODY_PART_SHIELD, nEquipId);
		}
	}
	break;
	default:
		break;
	}


	// 更新主手武器动作
	if (0 < pEquipVisual->nWeaponActor)
	{
		if (bHaveRightWeapon && IsRightHandHabit() || bHaveLeftWeapon && FALSE == IsRightHandHabit())
		{
			if (GENDER_MALE == GetCharacterData()->Get_RaceID())
				SetWeaponActionName(pEquipVisual->pWeaponActorFile_Man_Down, pEquipVisual->pWeaponActorFile_Man_Up);
			else
				SetWeaponActionName(pEquipVisual->pWeaponActorFile_Woman_Down, pEquipVisual->pWeaponActorFile_Woman_Up);

			UpdateModel_WeaponActionSet();
		}
	}

	// 设置主手或副手的武器类型
	if (pEquipVisual->pWeaponType >= 0 && pEquipVisual->pWeaponType < WEAPON_TYPE_NUMBERS)
	{
		if (bHaveRightWeapon || bHaveLeftWeapon)
		{
			if (IsRightHandHabit())
				SetWeaponType((eWEAPON_TYPE)pEquipVisual->pWeaponType, WL_RIGHT);
			else
				SetWeaponType((eWEAPON_TYPE)pEquipVisual->pWeaponType, WL_LEFT);
		}
	}

	// 更新人物手持武器的动作
	if (bUpdateWeaponAnimType)
	{
		if (bHaveRightWeapon && IsRightHandHabit() ||
			bHaveLeftWeapon && FALSE == IsRightHandHabit())
		{
			mMainEntity->Weapon_SetAasAnim(GetMainWeaponType());
		}
	}
}

void KPlayer::EquipItem_BodyPart(PLAYER_EQUIP nPart, int32 nID)
{
	if (NULL == mMainEntity)
		return;

	KCharatcterBaseData* pCharacterData = GetCharacterData();
	if (NULL == pCharacterData)
		return;

	const _TABLE_EQUIP_LOC* pEquipLoc = NULL;

	const CGameTable* pEquipItemTable = GAME_TABLE_MANAGER_PTR->GetTable(TABLE_ITEM_VISUAL_CHAR);
	if (NULL == pEquipItemTable)
		return;

	const _TABLE_ITEM_VISUAL_CHAR* pEquipVisual = (const _TABLE_ITEM_VISUAL_CHAR*)pEquipItemTable->GetFieldDataByIndex(nID);
	if (NULL == pEquipVisual)
		return;

	// 根据性别和职业来确定模型

	// 种族(男，女)
	int32 nRaceID = GetCharacterData()->Get_RaceID();
	if (nRaceID < 0 || nRaceID >= CHAR_RACE_NUM)
		return;

	// 职业
	int32 nProfession = GetCharacterData()->GetProfession();
	if (nProfession < 0 || nProfession >= PROFESSION_NUMBER)
		return;

	// 职业的模型索引
	int32 nVisualIndex = nRaceID + nProfession * CHAR_RACE_NUM;// 2表示的是各职业间隔的列数
	if (nVisualIndex < 0 || nVisualIndex >= PROFESSION_NUMBER * CHAR_RACE_NUM)
		return;

	// 取得装备索引
	int32 nEquipIndex = pEquipVisual->pVisualEntityIndex[nVisualIndex];

	// 角色装备类数据库
	const CGameTable* pEquipLocTable = GAME_TABLE_MANAGER_PTR->GetTable(TABLE_EQUIP_LOC);
	if (NULL == pEquipLocTable)
		return;

	pEquipLoc = (const _TABLE_EQUIP_LOC*)pEquipLocTable->GetFieldDataByIndex(nEquipIndex);
	if (NULL == pEquipLoc)
		return;


	switch (nPart)
	{
		// 披风
	case HEQUIP_SHOULDER:
		m_ModelPartDateList.SetValue(BODY_PART_MANTLE, pEquipLoc->pMeshFile);
		break;
		// 身体
	case HEQUIP_BACK:
		m_ModelPartDateList.SetValue(BODY_PART_BODY, pEquipLoc->pMeshFile);
		break;
		// 手臂
	case HEQUIP_HAND:
		m_ModelPartDateList.SetValue(BODY_PART_HAND, pEquipLoc->pMeshFile);
		break;
		// 鞋
	case HEQUIP_FEET:
		m_ModelPartDateList.SetValue(BODY_PART_FEET, pEquipLoc->pMeshFile);
		break;
	};


	for (int32 i = 0; i < EQUIP_LOC_EFFECT_MAX_NUM; ++i)
	{
		if (0 == strcmp(pEquipLoc->szREffect[i].szEffect, "") ||
			0 == strcmp(pEquipLoc->szREffect[i].szBindPoint, ""))
			continue;

		SetBodyEquipEffect(nPart, pEquipLoc->szREffect[i].szEffect, pEquipLoc->szREffect[i].szBindPoint);
	}
}

void KPlayer::SetBodyEquipEffect(int32 nEquipId, PLAYER_EQUIP nPart)
{
	if (NULL == mMainEntity)
		return;

	const CGameTable* ppItem_EquipVisualTable = GAME_TABLE_MANAGER_PTR->GetTable(TABLE_ITEM_EQUIP_VISUAL);
	if (NULL == ppItem_EquipVisualTable)
		return;

	const _TABLE_ITEM_EQUIP_VISUAL* pEquipVisual =
		(const _TABLE_ITEM_EQUIP_VISUAL*)ppItem_EquipVisualTable->GetFieldDataByIndex((uint32)nEquipId);

	if (NULL == pEquipVisual)
		return;

	// 加载装备上的特效
	for (int32 i = 0; i < EQUIP_EFFECT_MAX_NUM; ++i)
	{
		// 特效名称不为空
		if (('\0' != pEquipVisual->szEffect[i].szEffect[0]) &&
			('\0' != pEquipVisual->szEffect[i].szBindPoint[0]))
		{
			// 绑特效
			String strEffect = mMainEntity->AddEffect(
				pEquipVisual->szEffect[i].szEffect, 
				pEquipVisual->szEffect[i].szBindPoint, 
				0, "", getEffectPriority());

			// 保存特效到列表
			auto it = m_EquipEffectMap.find(nPart);
			if (it == m_EquipEffectMap.end())
			{
				std::vector<String> effectList;

				effectList.push_back(strEffect);

				m_EquipEffectMap.insert(std::make_pair(nPart, effectList));
			}
			else
			{
				it->second.push_back(strEffect);
			}
		}
	}

}
void KPlayer::SetBodyEquipEffect(
	PLAYER_EQUIP nPart, 
	LPCTSTR szBindPoint, 
	LPCTSTR szEffect)
{
	if (nullptr == mMainEntity)
		return;

	if (0 == strcmp(szBindPoint, "") || 0 == strcmp(szEffect, ""))
		return;

	String strEffectID = mMainEntity->AddEffect(szEffect, szBindPoint, 0, "", this->getEffectPriority());
	auto it = m_EquipEffectMap.find(nPart);

	if (it == m_EquipEffectMap.end())
	{
		std::vector<String> effectList;
		effectList.push_back(strEffectID);
		m_EquipEffectMap.insert(std::make_pair(nPart, effectList));
	}
	else
	{
		it->second.push_back(strEffectID);
	}
}


void KPlayer::AddEquipEffect(int32 nEquipId, PLAYER_EQUIP eEquipType)
{
	if (NULL == mMainEntity)
		return;

	const CGameTable* pItem_EquipVisualTable = GAME_TABLE_MANAGER_PTR->GetTable(TABLE_ITEM_EQUIP_VISUAL);
	if (NULL == pItem_EquipVisualTable)
		return;

	// 搜索纪录
	const _TABLE_ITEM_EQUIP_VISUAL* pEquipVisual = \
		(const _TABLE_ITEM_EQUIP_VISUAL*)pItem_EquipVisualTable->GetFieldDataByIndex((uint32)nEquipId);

	if (NULL == pEquipVisual)
		return;

	switch (eEquipType)
	{
		// 主手
	case HEQUIP_MAINHAND:
	{
		GameEntity::eWEAPATTR eType = GameEntity::WEAP_RIGHT;

		mMainEntity->Weapon_RemoveEffect(eType);

		// 加载武器默认的特效			
		for (int32 i = 0; i < EQUIP_EFFECT_MAX_NUM; ++i)
		{
			KCharacter::ChangeWeaponEffect(eType,
				pEquipVisual->szEffect[i].szEffect,
				pEquipVisual->szEffect[i].szBindPoint, 1);
		}
	}
	break;
	// 副手
	case HEQUIP_ASSIHAND:
	{
		GameEntity::eWEAPATTR eWeapAttr = GameEntity::WEAP_LEFT;

		if (EQUIP_SDUN == pEquipVisual->nType ||
			EQUIP_CRUSADE_ASSIST_HAND == pEquipVisual->nType)
		{
			eWeapAttr = GameEntity::WEAP_LEFT_SHIELD;
		}

		mMainEntity->Weapon_RemoveEffect(eWeapAttr);

		// 加载武器默认的特效
		for (int32 i = 0; i < EQUIP_EFFECT_MAX_NUM; ++i)
		{
			KCharacter::ChangeWeaponEffect(eWeapAttr,
				pEquipVisual->szEffect[i].szEffect,
				pEquipVisual->szEffect[i].szBindPoint, 1);
		}
	}
	break;
	default:
		break;
	}
}

bool KPlayer::IsRightHandHabit()
{
	//骑射的特例
	int32 nProfession = GetCharacterData()->GetProfession();
	if (PROFESSION_QISHE == (PROFESSION_TYPE)nProfession)
	{
		return false;
	}
	return true;
}

void KPlayer::SetWeaponActionName(LPCSTR szDown, LPCSTR szUp)
{
	if (szDown && szUp)
	{
		m_strWeaponActorFile_Down = szDown;
		m_strWeaponActorFile_Up = szUp;
	}
}

void KPlayer::UpdateModel_WeaponActionSet()
{
	
	SetWeaponAction(m_strWeaponActorFile_Down.c_str());
	
}

void KPlayer::DelEquipEffect(PLAYER_EQUIP nPart)
{

	// 查找该部位拥有的特效
	auto it = m_EquipEffectMap.find(nPart);
	if (it != m_EquipEffectMap.end())
	{
		// 删除该部位所有特效
		auto effectID = it->second.begin();
		for (; effectID != it->second.end(); ++effectID)
		{
			mMainEntity->DeleteEffect((*effectID).c_str());
		}
		it->second.clear();
	}
}

void KPlayer::UnEquipItem(PLAYER_EQUIP nPart, bool bUseDefaultEquip)
{
	switch (nPart)
	{
		// 主手 == 右手
	case HEQUIP_MAINHAND:
	{
		if (FALSE == IsRightHandHabit())
		{
			// 设为空手状态
			SetWeaponType(WEAPON_TYPE_NONE, WL_LEFT);

			m_ModelPartDateList.SetValue(BODY_PART_LEFTHAND, "");
			m_ModelPartDateList.SetValue(BODY_PART_LEFTHAND, INVALID_ID);
		}
		else
		{
			// 设为空手状态
			SetWeaponType(WEAPON_TYPE_NONE, WL_RIGHT);

			m_ModelPartDateList.SetValue(BODY_PART_RIGHTHAND, "");
			m_ModelPartDateList.SetValue(BODY_PART_RIGHTHAND, INVALID_ID);
		}
	}
	break;
	// 副手 == 左手
	case HEQUIP_ASSIHAND:
	{
		if (FALSE == IsRightHandHabit())
		{
			SetWeaponType(WEAPON_TYPE_NONE, WL_RIGHT);
			m_ModelPartDateList.SetValue(BODY_PART_RIGHTHAND, "");
			m_ModelPartDateList.SetValue(BODY_PART_RIGHTHAND, INVALID_ID);
		}
		else
		{
			SetWeaponType(WEAPON_TYPE_NONE, WL_LEFT);
			m_ModelPartDateList.SetValue(BODY_PART_LEFTHAND, "");
			m_ModelPartDateList.SetValue(BODY_PART_LEFTHAND, INVALID_ID);
		}

		SetWeaponType(WEAPON_TYPE_NONE, WL_L_ARM);
		m_ModelPartDateList.SetValue(BODY_PART_SHIELD, "");
		m_ModelPartDateList.SetValue(BODY_PART_SHIELD, INVALID_ID);
	}
	break;
	// 头
	case HEQUIP_HEAD:
	{
		// 设置缺省装备
		if (m_pCharRace)
			EquipItem_BodyPart(HEQUIP_HEAD, m_pCharRace->nDefHeadGeo);
	}
	break;
	// 衣服
	case HEQUIP_BACK:
	{
		if (bUseDefaultEquip)
		{
			// 设置缺省装备
			if (m_pCharRace)
				EquipItem_BodyPart(HEQUIP_BACK, m_pCharRace->nDefBody);
		}
		else
		{
			m_ModelPartDateList.SetValue(BODY_PART_BODY, "");
			m_ModelPartDateList.SetValue(BODY_PART_BODY, INVALID_ID);
		}
	}
	break;
	// 肩/披风
	case HEQUIP_SHOULDER:
	{
		if (bUseDefaultEquip)
		{
			// 设置缺省装备
			if (m_pCharRace)
				EquipItem_BodyPart(HEQUIP_SHOULDER, m_pCharRace->nDefShoulder);
		}
		else
		{
			m_ModelPartDateList.SetValue(BODY_PART_MANTLE, "");
			m_ModelPartDateList.SetValue(BODY_PART_MANTLE, INVALID_ID);
		}
	}
	break;
	// 手
	case HEQUIP_HAND:
	{
		if (bUseDefaultEquip)
		{
			// 设置缺省装备
			if (m_pCharRace)
				EquipItem_BodyPart(HEQUIP_HAND, m_pCharRace->nDefArm);
		}
		else
		{
			m_ModelPartDateList.SetValue(BODY_PART_HAND, "");
			m_ModelPartDateList.SetValue(BODY_PART_HAND, INVALID_ID);
		}
	}
	break;
	// 脚
	case HEQUIP_FEET:
	{
		if (bUseDefaultEquip)
		{
			// 设置缺省装备
			if (m_pCharRace)
				EquipItem_BodyPart(HEQUIP_FEET, m_pCharRace->nDefFoot);
		}
		else
		{
			m_ModelPartDateList.SetValue(BODY_PART_FEET, "");
			m_ModelPartDateList.SetValue(BODY_PART_FEET, INVALID_ID);
		}
	}
	break;
	default:
		break;
	};
}

void KPlayer::UpdateCharBaseData(void) 
{
	KCharatcterBaseData* pCharacterData = GetCharacterData();

	if (pCharacterData != NULL && pCharacterData->Get_RaceID() != INVALID_ID)
	{
		m_pCharRace = NULL;

		int32 nProfession = pCharacterData->GetProfession();
		int32 nRaceId = pCharacterData->Get_RaceID();
		int32 nIndex = nRaceId * PROFESSION_NUMBER + nProfession + 100;

		const CGameTable* pCharacterRaceTable = GAME_TABLE_MANAGER_PTR->GetTable(TABLE_CHARACTER_RACE);
		if (NULL == pCharacterRaceTable)
		{
			return;
		}

		m_pCharRace = (const _TABLE_CHAR_RACE*)(pCharacterRaceTable->GetFieldDataByIndex(nRaceId));
	}
}

void KPlayer::UpdateModel_Visible()
{
	KCharacter::UpdateModel_Visible();
}

int32 KPlayer::AnalyseCharModel(void)const
{
	// 经过变身
	if (INVALID_ID != m_pCharacterData->Get_ModelID())
	{
		// 直接从模型定义表中读取模型名
		return m_pCharacterData->Get_ModelID();
	}
	else
	{
		if (m_pCharRace != NULL)
		{
			// 通过性别和职业获取相应的模型
			int32 nMenpai = m_pCharacterData->GetProfession();
			if (INVALID_ID != nMenpai)
				return m_pCharRace->nModelID + nMenpai;
			else
				return m_pCharRace->nModelID;
		}
	}

	return INVALID_ID;
}

