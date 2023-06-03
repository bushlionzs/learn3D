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
		if (NULL == mGameEntity)
		{
			mGameEntity = createGameEntity(0);
		}

		auto position = EngineManager::getSingleton().getMyPosition();
		// 设置ActorFile
		setPosition(position);
	
		mGameEntity->setModelName(lpszModelFileName);
	

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
			pTempEquip = (KItemEquip*)ITEM_MANAGER_PTR->CreateNewItem(nEquipID);
			if (pTempEquip && ICLASS_EQUIP == pTempEquip->GetItemClass() && pTempEquip->GetTermTime() != 1)
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

	UpdateAnimWeaponType();

	ITEM_MANAGER_PTR->DestroyItem(pTempEquip);

	// 刷新可见
	if (IsModelCreateAllCompleted())
	{
		UpdateModel_Visiable();
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
	mGameEntity->changeAttributes(vName, vValue);
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
