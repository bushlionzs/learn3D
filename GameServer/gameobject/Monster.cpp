/*$T MapServer/Server/Obj/Monster.cpp GC 1.140 10/10/07 10:07:31 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include "stdafx.h"
#include "map/game_map.h"
#include "map/map_info.h"
#include "Monster.h"
#include "data/data_manager.h"
#include "server_settting.h"
#include "map/map_manager.h"
#include "Behavior_Monster.h"
#include "net/messages/SCNewMonster.h"
#include "item/Item_Ruler.h"
#include "net/messages/SCMonsterAttribute.h"
#include "net/net_message_manager.h"
#include "net/messages/SCCharImpactListUpdate.h"
#include "gameobject/CharacterVisitor.h"
#include "map/MapDropPosManager.h"
#include "server_manager.h"
#include "script/LuaSystem.h"
#include "ScriptDef.h"
#include "net/messages/SCChat.h"
#include "server_message.pb.h"
using namespace Messages;


extern eREFESH_PROPERTY_TYPE Calc_RefeshAttrType(Character* pSour, Character* pTarget);


Monster::Monster(void)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	m_pShopManager = NULL;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_nOwnerElapsedTick = 0;
	ClearSelf();
	m_pAI_Character = new Behavior_Monster;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
Monster::~Monster(void)
{
	
}


bool Monster::Init(const _INIT_OBJECT* pInit, MapID_t MapID)
{
	if (!Character::Init(pInit)) 
		return false;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	_INIT_MONSTER_OBJECT* pMonsterInit = (_INIT_MONSTER_OBJECT*)pInit;
	mMonsterProperty = DataManager::GetSingletonPtr()->getMonsterProperty(pMonsterInit->m_uDataID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (nullptr == mMonsterProperty)
	{
		char szMsg[128] = { 0 };
		tsnprintf_s(szMsg, 128, 
			"！！策划填表错误或程序使用LuaFunction_CreateMonster时指定的DataID=%d错误！！", 
			pMonsterInit->m_uDataID);
		KCheckEx(mMonsterProperty != nullptr, szMsg);
		return false;
	}
	m_GUID = pMonsterInit->m_GUID;
	m_NPCGUID = pMonsterInit->m_ObjGUID;

	m_uDataID = pMonsterInit->m_uDataID;

	if (pMonsterInit->m_szName[0] == '\0')
		strncpy(m_szName, mMonsterProperty->m_Name, sizeof(m_szName) - 1);
	else
		strncpy(m_szName, pMonsterInit->m_szName, sizeof(m_szName) - 1);

	strncpy(m_szTitle, pMonsterInit->m_szTitle, sizeof(m_szTitle) - 1);

	m_RespawnTime = pMonsterInit->m_RespawnTime;
	if (m_RespawnTime <= 0 && !m_CreateFlag)
	{
		m_RespawnTime = mMonsterProperty->m_RespawnTime;
	}

	m_Level = pMonsterInit->m_nLevel;
	if (m_Level == -1)
	{
		m_Level = mMonsterProperty->m_Level;
	}

	SetRespawnDir(pMonsterInit->m_Dir);

	SetRespawnPos(&pMonsterInit->m_Pos);

	m_RespawnTimer.BeginTimer(m_RespawnTime, 0);

	m_LiveTime = pMonsterInit->m_LiveTime;
	m_LiveTimer.Clear();

	m_nPatrolID = pMonsterInit->m_nPatrolID;
	m_uGroupID = pMonsterInit->m_uGroupID;
	m_uTeamID = pMonsterInit->m_uTeamID;
	m_AIType = pMonsterInit->m_BaseAI;

	m_bPatrolNoBreak = 0;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	tmp = GetMonsterAIType();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_AIScript = pMonsterInit->m_ExtAIScript;
	m_LeaderID = pMonsterInit->m_LeaderID;
	m_idScript = pMonsterInit->m_idScript;

	m_PositionRange = g_Config.m_ConfigInfo.m_PositionRange;
	m_BaseExp = mMonsterProperty->m_BaseExp;
	m_MinDamagePercent = mMonsterProperty->m_MinDamagePercent;

	if (pMonsterInit->m_CampID != INVALID_CAMP)
	{
		m_CampData.m_nCampID = pMonsterInit->m_CampID;
	}
	else
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		MAP_CONFIG* pSceneInfo = MapManager::GetSingletonPtr()->getMapData(MapID);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if (NULL == pSceneInfo)
		{
			m_CampData.m_nCampID = mMonsterProperty->m_Camp;
		}
		else if (pSceneInfo->m_DefaultCamp != INVALID_CAMP)
		{
			m_CampData.m_nCampID = pSceneInfo->m_DefaultCamp;
		}
		else
		{
			m_CampData.m_nCampID = mMonsterProperty->m_Camp;
		}
	}

	m_DropSearchRange = mMonsterProperty->m_DropSearchRange;
	m_DropTeamCount = mMonsterProperty->m_SearchTeamCount;
	m_AttackAnimTime = mMonsterProperty->m_AttackAnimTime;
	m_AttackCooldownTime = mMonsterProperty->m_AttackCooldownTime;
	m_DropRuler = (eBOX_DISTRIBUTE_RULER)mMonsterProperty->m_BossFlag;

	m_nOwnerElapsedTick = 0;

	Behavior_Monster* pMonsterAI = GetMonsterAI();

	if(pMonsterAI)
		pMonsterAI->SetBehavior_TemplateID(m_AIScript);

	Effect_InitList();

	respawn(m_pVisitor);

	return TRUE;
}

bool	Monster::HeartBeat(uint32 uTime)
{
	return Character::HeartBeat(uTime);

}

BOOL	Monster::HeartBeat_OutMap(uint32 uTime)
{
	BOOL	bResult = Character::HeartBeat_OutMap(uTime);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (!bResult) return bResult;

	if (m_RespawnTime < 0)
	{
		return FALSE;
	}

	if (m_RespawnTimer.CountingTimer(uTime))
	{
		m_RespawnTimer.Clear();

		// 老怪流程
		if (m_iRandomGroupID == -1)
		{
			respawn(m_pVisitor);
		}
		//// 2010-11-26 by rj 随机怪重生后必须随机组号是合法的，防止被其他内存破坏
		//else if (GetMap() && m_iRandomGroupID >= 0 && m_iRandomGroupID < RANDOM_PERMAP_MAXGROUP)
		//{
		//	MapID_t iMapID = GetMap()->MapID();

		//	KCheckEx(g_pRandomMonsterConfig[iMapID], "重生检测读取本图为空");
		//	KCheckEx(g_pRandomMonsterConfig[iMapID]->m_paMonsterGroup[m_iRandomGroupID], "重生检测读取本图本组为空");

		//	// 同组随机怪挑选
		//	uint32 uIdx = (uint32)rand() % g_pRandomMonsterConfig[iMapID]->m_paMonsterGroup[m_iRandomGroupID]->m_uMonsterCount;
		//	KCheckEx(g_pRandomMonsterConfig[iMapID]->m_paMonsterGroup[m_iRandomGroupID]->m_paMonster[uIdx], "重生时读取本图配置条目为空");
		//	Init(&g_pRandomMonsterConfig[iMapID]->m_paMonsterGroup[m_iRandomGroupID]->m_paMonster[uIdx]->m_MonsterConfig, iMapID);
		//}
		//else
		//{
		//	KCheckEx(FALSE, "随机怪重生时自身随机组号非法，可能内存被破坏");
		//}
	}

	return TRUE;
}

void	Monster::SendCharBaseDirectForHP()
{
	SCMonsterAttribute* packet = new SCMonsterAttribute;

	uchar					yHPPercent = GetPercentHP();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	packet->setObjId(GetID());
	packet->setHpPercent(yHPPercent);
	if (0 >= GetHP())
	{
		/*~~~~~~~~~~~~~~~~~~~~~~*/
		PLAYERLIST	listHuman;
		/*~~~~~~~~~~~~~~~~~~~~~~*/

		GetMap()->ScanPlayer(GetGridID(), MAX_REFESH_OBJ_GRID_RADIUS, &(listHuman));

		/*~~~~~~*/
		uchar	i;
		/*~~~~~~*/

		for (i = 0; i < listHuman.m_Count; i++)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			Player* pTargetHuman = listHuman.m_aHuman[i];
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if (IsCanViewMe(pTargetHuman))
			{
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
				eREFESH_PROPERTY_TYPE	eType = Calc_RefeshAttrType(this, pTargetHuman);
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

				switch (eType)
				{
				case REFESH_ATTR_TYPE_NONE:
					break;

				case REFESH_ATTR_TYPE_PUBLIC:
				case REFESH_ATTR_TYPE_PUBLIC_AND_LEVEL:
				{
					NetMessageManager::GetSingletonPtr()->sendNetMessage(nullptr);
					packet = nullptr;
				}
				break;

				case REFESH_ATTR_TYPE_PROTECTED:
				{
					NetMessageManager::GetSingletonPtr()->sendNetMessage(nullptr);
					packet = nullptr;
				}
				break;

				default:
					break;
				}
			}
		}

		m_AttrBackUp.m_HP = GetHP();
	}

	if (packet)
	{
		delete packet;
	}
}

void	Monster::Effect_ActiveScript(UNIT_EFFECT& rEffect)
{
	ScriptID_t iScriptID = GetEffectScriptID(rEffect);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (iScriptID <= 0)
	{
		return;
	}

	ServerManager::GetSingletonPtr()->getLuaSystem()->RunScriptFunction
	(
		GetMap()->MapID(),
		iScriptID,
		DEF_PROC_EVENT_ENTRY_FN,
		GetMap()->MapID(),
		(int32)GetID(),
		(int32)rEffect.GetDataIndex(),
		IMPACT_CALL_SCRIPT_ADD
	);
}

void	Monster::Effect_FadeOutScript(UNIT_EFFECT& rEffect)
{
	ScriptID_t iScriptID = GetEffectScriptID(rEffect);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (iScriptID <= 0)
	{
		return;
	}

	ServerManager::GetSingletonPtr()->getLuaSystem()->RunScriptFunction
	(
		GetMap()->MapID(),
		iScriptID,
		DEF_PROC_EVENT_ENTRY_FN,
		GetMap()->MapID(),
		(int32)GetID(),
		(int32)rEffect.GetDataIndex(),
		IMPACT_CALL_SCRIPT_ADD
	);
}

void		Monster::DistributeExpToKiller()
{
	Player* apValidMember[MAX_TEAM_MEMBER];
	uint32			nValidMemberCount = GetValidOwnerList(MAX_TEAM_MEMBER, apValidMember);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	ExpToHuman(nValidMemberCount, apValidMember, FALSE);
}

void		Monster::ExpToHuman(int32 nValidMemberCount, Player** apValidMember, BOOL bTeam)
{
	CaculateMonsterExpRuler	CaculateExp;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (nValidMemberCount < 1)
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~*/
	int32	nExp = m_BaseExp;
	/*~~~~~~~~~~~~~~~~~~~~~*/

	bool bAddTip = nExp > 0;

	if (g_Config.m_ConfigInfo.m_ExpParam > 1.0f)
	{
		nExp = (int32)(m_BaseExp * g_Config.m_ConfigInfo.m_ExpParam);
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	uint32	auExp[MAX_TEAM_MEMBER];
	int32	i;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for (i = 0; i < nValidMemberCount; i++)
	{
		if (NULL == apValidMember[i])
		{
			continue;
		}

		
		auExp[i] = CaculateExp.CaculateBaseExp
		(
			GetLevel(),
			apValidMember[i]->GetLevel(),
			nExp,
			nValidMemberCount
		);

		/*~~~~~~~~~~~~~~~~~~~~*/
		float	nTeamRate = 0.0;
		/*~~~~~~~~~~~~~~~~~~~~*/

		enum
		{
			RATE_TYPE_PRENTTICE_TOPLIST = 1,
			RATE_TYPE_PRENTTICE_TEAM = 2,
		};

		uint32 rateType = 0;

		nTeamRate += (float)apValidMember[i]->GetExpMult();
		nTeamRate += apValidMember[i]->GetWanFaExpMult();
		//装备对经验的加成
		nTeamRate += apValidMember[i]->GetEquipExpMult();

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		float	fExp = nTeamRate * (float)auExp[i];
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		auExp[i] = Float2Int(fExp);

		if (bAddTip && auExp[i] > 0)
		{
			apValidMember[i]->SetAlterPlayerExp
			(
				(uint64)(
					(float)auExp[i] * apValidMember[i]->GetWallow()
					)
			);
		}

		if (bAddTip)
		{
			SCChat* packet = new SCChat;
			packet->setChatType(CHAT_TYPE_SELF);

			packet->setChatShowPos(CHAT_PLUMB_SCROLL);
			NetMessageManager::GetSingletonPtr()->sendNetMessage(packet);
		}

		apValidMember[i]->OnEvent_KillObject(GetID());

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		SHorseGuid	guidPet = apValidMember[i]->GetGUIDOfCallUpHorse();
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if (!guidPet.IsNull())
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			int32	iIndex = apValidMember[i]->GetHorseIndexByGUID(guidPet);
			_HORSE_DB* pPetDB = apValidMember[i]->GetHorseDB(iIndex);
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if (NULL == pPetDB)
			{
				continue;
			}

			/*~~~~~~~~~~~~~~~~*/
			int32	iAddExp = 0;
			/*~~~~~~~~~~~~~~~~*/

			
			iAddExp = CaculateExp.CaculateBaseExp
			(
				pPetDB->m_nLevel,
				pPetDB->m_nLevel,
				nExp,
				nValidMemberCount
			);

			iAddExp = (int32)(iAddExp * nTeamRate);

			if (iAddExp > 0)
			{
				apValidMember[i]->UpdateHorseExp
				(
					(int32)
					(
						(float)iAddExp *
						apValidMember[i]->GetWallow()
						)
				);
			}
		}
	}
}

void		Monster::GoodBadValueToHuman(int32 nValidMemberCount, Player** apValidMember, BOOL bTeam)
{
	
}

void Monster::ClearSelf()
{
	m_AttrBackUp.Clear();

	m_EffectList.Clear();

	m_RespawnTime = -1;
	m_RespawnTimer.Clear();
	m_RespawnDir = -1.f;
	m_RespawnPos = GLPos(-1.f, -1.f);

	m_Own_TeamID = INVALID_ID;
	m_OccupantGUID = INVALID_GUID;
	m_fControlValue = 0;
	m_OccupantLevel = 0;
	m_DamageMemList.Clear();
	m_OwnerList.Clear();
	m_nOwnerElapsedTick = 0;

	m_AIType = -1;
	m_AIScript = -1;
	m_LeaderID = -1;
	m_PositionRange = 0;


	m_nPatrolID = INVALID_ID;
	m_DropSearchRange = 0.f;
	m_DropTeamCount = 0;
	m_CreateFlag = FALSE;
	
	m_bPatrolNoBreak = 0;

	m_nKillCount = 0;

	m_GUID = INVALID_GUID;
	m_NPCGUID = INVALID_GUID;
	m_uDataID = INVALID_ID;
	memset(m_szName, 0, sizeof(m_szName));
	memset(m_szTitle, 0, sizeof(m_szTitle));
	m_HP = 0;
	m_Level = 0;
	m_BaseExp = 0;
	m_idScript = 0;

	m_MinDamagePercent = 0;
	m_uGroupID = INVALID_ID;
	m_uTeamID = INVALID_ID;

	m_iAttackNear = 0;
	m_iAttackFar = 0;
	m_iAttackMagic = 0;
	m_iDefenceNear = 0;
	m_iDefenceFar = 0;
	m_iDefenceMagic = 0;
	m_iHorseID = -1;
	m_iWeaponID = 0;
	m_iMaxHP = 0;
	m_iMaxMP = 0;
	m_iHPRestore = 0;
	m_iMPRestore = 0;
	m_iHitRate = 0;
	m_iMissRate = 0;
	m_iCriticalRate = 0;
	m_iAttackCold = 0;
	m_iAttackFire = 0;
	m_iAttackLight = 0;
	m_iAttackPoison = 0;
	m_iDefenceCold = 0;
	m_iDefenceFire = 0;
	m_iDefenceLight = 0;
	m_iDefencePoison = 0;
	m_iRandomGroupID = -1;
	m_CooldownList.Clear();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Monster::Clear(void)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	ClearSelf();
	/*~~~~~~~~~~~~~~~~~~~~~~~~*/

	Character::Clear();
	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Monster::FadeOutAllEffect()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	_EFFECT_LIST	&rList = Effect_GetEffectList();
	uchar		&rCount = rList.m_Count;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for(int32 i = 0; i < rCount; ++i)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		UNIT_EFFECT	&rImp = rList.m_aImpacts[i];
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	}

	rList.Clear();
}


void	Monster::Effect_InitList(void)
{
	m_EffectList.Clear();
}


bool Monster::respawn(CharacterVisitor* pVisitor)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	KCheck(!IsActiveObj());
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


	/*~~~~~~~~~~~~~~~~~*/
	float		fDir;
	GLPos	Pos;
	/*~~~~~~~~~~~~~~~~~*/

	Pos = *GetRespawnPos();
	fDir = GetRespawnDir();
	SetDir(fDir);
	GetMap()->GetMapInfo()->VerifyPos(&Pos);
	GetMap()->GetMapInfo()->IsCanGo(Pos) ? Pos : Pos = *GetRespawnPos();
	SetGLPos(&Pos);
	m_pVisitor->VisitInitMonster(this);

	UpdateGrid();

	SetHP(GetMaxHP());

	m_nKillCount = 0;
	memset(m_sKillObj, -1, sizeof(m_sKillObj));

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Behavior_Monster* pAI = (Behavior_Monster*)GetAIObj();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (pAI)
	{
		if (isPatrolMonster())
		{
			 pAI->StartPatrol(FALSE, TRUE);
		}
		else
		{
			pAI->ToBHVIdle();
		}
	}

	SetActiveFlag(TRUE);

	return true;
}

enum EPlAYER_BHV_TYPE
{
	PlAYER_BHV_TYPE_INVALID = -1,
	PlAYER_BHV_TYPE_SCANNPC = 0,
	PlAYER_BHV_TYPE_NOTSCANNPC = 1,
	PlAYER_BHV_TYPE_CANNOTATTACK = 2,
};

int32 Monster::GetMonsterAIType(void)
{
	int32	nAIType = GetAIType();
	int32	nRet = PlAYER_BHV_TYPE_INVALID;
	MonsterAIData* aidata = DataManager::GetSingletonPtr()->getMonsterAIData();

	if (aidata->get(nAIType, BHVPARAM_SCANTIME) > 0)
	{
		nRet = PlAYER_BHV_TYPE_SCANNPC;
	}
	else if (IsImmuneAbsForLater())
	{
		nRet = PlAYER_BHV_TYPE_CANNOTATTACK;
	}
	else if (aidata->get(nAIType, BHVPARAM_SCANTIME) <= 0)
	{
		nRet = PlAYER_BHV_TYPE_NOTSCANNPC;
	}

	return nRet;
}

int32_t Monster::Get_Property_Rage(void)
{
	return 0;
}

void	Monster::Set_Property_Rage(int32_t nRage)
{
	
}

void		Monster::SetName(const char* pszName)
{
	strncpy(m_szName, pszName, sizeof(m_szName) - 1);
	m_AttrBackUp.m_bNameModified = TRUE;
}

const char* Monster::GetName(void) const
{
	return m_szName;
}

void		Monster::SetTitle(const char* pszTitle)
{
	strncpy(m_szTitle, pszTitle, sizeof(m_szTitle) - 1);
	m_AttrBackUp.m_bTitleModified = TRUE;
}

const char* Monster::GetTitle(void) const
{
	return m_szTitle;
}

void		Monster::SetHP(int32_t nHP)
{
	m_HP = nHP;
}

int32_t		Monster::GetHP(void)
{
	if (m_HP > GetMaxHP())
	{
		m_HP = GetMaxHP();
	}

	return m_HP;
}

int32_t Monster::GetHPNoClip(void)
{
	return m_HP;
}

void		Monster::SetMP(int32_t nMP)
{

}

int32_t		Monster::GetMP(void)
{
	return 0;
}

void		Monster::SetLevel(int32_t nLevel)
{
	
}

int32_t		Monster::GetLevel(void) const
{
	return 0;
}

NetPacket* Monster::CreateNewObjMsg(void)
{
	const GLPos* pos = this->GetGLPos();
	servermessage::ServerMsgNewMonster dummy;

	dummy.set_object_id(GetID());
	dummy.set_position_x(pos->m_fX);
	dummy.set_position_z(pos->m_fZ);
	dummy.set_dir(GetDir());
	dummy.set_move_speed(Get_Property_MoveSpeed());
	dummy.set_monster_type(MT_MONSTER);
	dummy.set_horse_id(GetHorseID());
	dummy.set_weapon_id(GetWeaponID());
	dummy.set_guid(GetGUID());
	dummy.set_race_id(GetDataID());
	dummy.set_name(mMonsterProperty->m_Name);
	dummy.set_camp_id(mMonsterProperty->m_Camp);
	
	NetPacket* packet = new NetPacket(servermessage::SC_NEWMONSTER, dummy);
	return packet;
}
void		Monster::DestroyNewObjMsg(NetPacket* pPacket)
{
	//delete pPacket;
}


void Monster::SendMsg_RefeshAttrib(void)
{
	BOOL		bSendMsgForBroadcast = FALSE;
	BOOL		bSendMsgForWhoLockMe = FALSE;

	
	servermessage::ServerMsgMonsterAttribute dummy;
	dummy.set_object_id(GetID());
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


	if (m_AttrBackUp.m_HP != GetHP())
	{
		m_AttrBackUp.m_HP = GetHP();
	}

	if (m_AttrBackUp.m_MaxHp != GetMaxHP())
	{
		m_AttrBackUp.m_MaxHp = GetMaxHP();
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	uchar	yHPPercent = GetPercentHP();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (m_AttrBackUp.m_HPPercent != yHPPercent)
	{
		{
			bSendMsgForWhoLockMe = TRUE;

			m_AttrBackUp.m_HPPercent = yHPPercent;

			dummy.set_hp_percent(yHPPercent);
		}
	}

	if (fabs(m_AttrBackUp.m_MoveSpeed - Get_Property_MoveSpeed()) > 0.001f)
	{
		bSendMsgForBroadcast = TRUE;

		m_AttrBackUp.m_MoveSpeed = Get_Property_MoveSpeed();
		dummy.set_move_speed(Get_Property_MoveSpeed());
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	const SCampData* pCampData = GetCampData();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (pCampData != NULL)
	{
		if (m_AttrBackUp.m_CampData != *pCampData)
		{
			bSendMsgForBroadcast = TRUE;

			m_AttrBackUp.m_CampData = *pCampData;

			auto* camp_data = dummy.mutable_camp_data();
			camp_data->set_camp_id(pCampData->m_nCampID);
			camp_data->set_pk_mode(pCampData->m_uPKMode);
			camp_data->set_reserve1(pCampData->m_nReserve1);
			camp_data->set_reserve2(pCampData->m_nReserve2);
		}
	}

	if (m_AttrBackUp.m_OwnerID != GetOwnerID())
	{
		bSendMsgForBroadcast = TRUE;

		m_AttrBackUp.m_OwnerID = GetOwnerID();
		dummy.set_owner_id(GetOwnerID());
	}

	if (m_AttrBackUp.m_OccupantGUID != GetOccupantGUID())
	{
		bSendMsgForBroadcast = TRUE;

		m_AttrBackUp.m_OccupantGUID = GetOccupantGUID();

		dummy.set_occupant_guid(GetOccupantGUID());
	}

	if (m_AttrBackUp.m_nMountID != GetMountID())
	{
		bSendMsgForBroadcast = TRUE;

		m_AttrBackUp.m_nMountID = GetMountID();

		dummy.set_mount_id(GetMountID());
	}

	if (m_AttrBackUp.m_nModelID != GetModelID())
	{
		bSendMsgForBroadcast = TRUE;

		m_AttrBackUp.m_nModelID = GetModelID();

		dummy.set_model_id(GetModelID());
	}

	if (m_AttrBackUp.m_nScale != GetIntAttr_EX(CharIntProperty::PROPERTY_ZOOM_SCALE))
	{
		bSendMsgForBroadcast = TRUE;

		m_AttrBackUp.m_nScale = GetIntAttr_EX(CharIntProperty::PROPERTY_ZOOM_SCALE);

		dummy.set_scale(m_AttrBackUp.m_nScale);
	}

	if (m_AttrBackUp.m_nAIType != GetAIType())
	{
		bSendMsgForBroadcast = TRUE;

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	nRet = GetMonsterAIType();
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		m_AttrBackUp.m_nAIType = nRet;

		dummy.set_ai_type(nRet);
	}

	if (m_AttrBackUp.m_nStealthLevel != GetStealthLevel())
	{
		bSendMsgForBroadcast = TRUE;

		m_AttrBackUp.m_nStealthLevel = GetStealthLevel();

		dummy.set_steal_level(m_AttrBackUp.m_nStealthLevel);
	}

	if (m_AttrBackUp.m_iHorseID != GetHorseID())
	{
		bSendMsgForBroadcast = TRUE;

		m_AttrBackUp.m_iHorseID = GetHorseID();
		dummy.set_mount_id(m_AttrBackUp.m_iHorseID);
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Behavior_Character* pAiObj = GetAIObj();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if (pAiObj)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32		nTargetID = INVALID_ID;
		Character* pObj = ((Behavior_Monster*)pAiObj)->GetNextTarget();
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if (pObj)
		{
			nTargetID = pObj->GetID();
		}

		if (m_AttrBackUp.m_nTargetID != nTargetID)
		{
			bSendMsgForBroadcast = TRUE;

			SetLockedTarget(nTargetID);
			m_AttrBackUp.m_nTargetID = nTargetID;
			dummy.set_target_id(nTargetID);
		}
	}

	if (!bSendMsgForBroadcast && !bSendMsgForWhoLockMe)
	{
		return;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~*/
	PLAYERLIST	listHuman;
	/*~~~~~~~~~~~~~~~~~~~~~~*/

	GetMap()->ScanPlayer(GetGridID(), MAX_REFESH_OBJ_GRID_RADIUS, &(listHuman));

	for(int32_t i = 0; i < listHuman.m_Count; i++)
	{
		Player* player = listHuman.m_aHuman[i];
		NetHandle player_handle = player->GetConnector();
		NetMessageManager::GetSingletonPtr()->sendNetMessage(player_handle, servermessage::SC_MONSTER_ATTRBUTE, &dummy);
	}

}


void Monster::RequestBaseProperty(Player* pTargetHuman, BASEPROPERTY_REFESH_MODE nMode)
{
	if (IsCanViewMe(pTargetHuman))
	{
		
		
		uchar			yHPPercent = GetPercentHP();
		uchar			yMPPercent = (GetMaxMP()) ?
			((uchar)((GetMP() * 100 + GetMaxMP() - 1) / GetMaxMP())) : (0);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


		BOOL bRefesh = TRUE;
		uint64 uCrcCode = GetBaseAttribCrcCode();
		uint64 uSumCode = GetBaseAttribSumCode();

		uint16 uDataId = (uint16)GetDataID();
		uchar uLevel = (uchar)GetLevel();
		float fMoveSpeed = Get_Property_MoveSpeed();
		float fAttackSpeed = (float)Get_Property_AttackSpeed();
		int16 nHorseId = (int16)GetHorseID();
		uchar nAiType = (uchar)GetMonsterAIType();
		int32 nScale = GetIntAttr_EX(CharIntProperty::PROPERTY_ZOOM_SCALE);
		// 
		if (uCrcCode != 0 && uSumCode != 0 && GetGUID() != INVALID_GUILD_ID)
		{
			// 生成CRC
			char szTmp[100] = { 0 };
			int32 nSize = 0;
			memcpy(szTmp + nSize, &uDataId, sizeof(uint16));		nSize += sizeof(uint16);
			memcpy(szTmp + nSize, &uLevel, sizeof(uchar));			nSize += sizeof(uchar);
			memcpy(szTmp + nSize, &fMoveSpeed, sizeof(float));		nSize += sizeof(float);
			memcpy(szTmp + nSize, &fAttackSpeed, sizeof(float));	nSize += sizeof(float);
			memcpy(szTmp + nSize, &nHorseId, sizeof(int16));		nSize += sizeof(int16);
			memcpy(szTmp + nSize, &nAiType, sizeof(uchar));		nSize += sizeof(uchar);
			memcpy(szTmp + nSize, &nScale, sizeof(nScale));		nSize += sizeof(nScale);
			memcpy(szTmp + nSize, GetName(), strlen(GetName()));	nSize += (int32)strlen(GetName());
			memcpy(szTmp + nSize, GetTitle(), strlen(GetTitle()));	nSize += (int32)strlen(GetTitle());

			uint64 uNewCrcCode = CRC(szTmp, nSize);
			uint64 uNewSumCode = CheckSum(szTmp, nSize);

			if (uCrcCode == uNewCrcCode &&
				uSumCode == uNewSumCode)
				bRefesh = FALSE;
		}

		// 说明客户端缓存的数据没有变化，不用重刷
		servermessage::ServerMsgMonsterAttribute dummy;

		auto id = GetID();
		dummy.set_object_id(id);

		if (bRefesh)
		{
			auto name = GetName();
			dummy.set_name(name);
			dummy.set_data_id(uDataId);
			auto scale = GetIntAttr_EX(CharIntProperty::PROPERTY_ZOOM_SCALE);
			dummy.set_scale(scale);
			dummy.set_ai_type(nAiType);
			if (fMoveSpeed > 0)
			{
				dummy.set_move_speed(fMoveSpeed);
			}

			if (fAttackSpeed > 0)
			{
				dummy.set_attack_speed((float)fAttackSpeed);
			}

			if (strlen(GetTitle()) > 0)
			{
				dummy.set_country_title(GetTitle());
			}

			if (nHorseId != INVALID_ID)
			{
				dummy.set_mount_id(nHorseId);
			}

			dummy.set_level(uLevel);
		}

		dummy.set_hp_percent(yHPPercent);
		auto target = GetLockedTarget();
		dummy.set_target_id(GetLockedTarget());

		if (GetStealthLevel() != 0)
		{
			dummy.set_steal_level(GetStealthLevel());
		}

		if (GetCampData() != nullptr)
		{
			const SCampData* source = GetCampData();
			base::SCampData* camp_data = dummy.mutable_camp_data();
			camp_data->set_camp_id(source->m_nCampID);
			camp_data->set_pk_mode(source->m_uPKMode);
			camp_data->set_reserve1(source->m_nReserve1);
			camp_data->set_reserve2(source->m_nReserve2);
		}
		if (GetOccupantGUID() != INVALID_ID)
		{
			dummy.set_occupant_guid(GetOccupantGUID());
		}

		if (GetOwnerID() != INVALID_ID)
		{
			dummy.set_owner_id(GetOwnerID());
		}
		NetHandle handle  = pTargetHuman->GetConnector();
		NetMessageManager::GetSingletonPtr()->sendNetMessage(handle, servermessage::SC_MONSTER_ATTRBUTE, &dummy);
		
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		_EFFECT_LIST& effectlist = Effect_GetEffectList();
		if (effectlist.m_Count > 0)
		{
			SCCharImpactListUpdate* packet = new SCCharImpactListUpdate;
			packet->setImpactList(effectlist);
			packet->setOwnerId(GetID());
			packet->setLastSN(Effect_GetSNSeed());
			NetMessageManager::GetSingletonPtr()->sendNetMessage(packet);
		}
	}
}

bool Monster::IsLimitMove()
{
	return false;
}

void Monster::OnEvent_Die(ObjID_t idKiller)
{
	__GUARD__	
	FadeOutAllEffect();

	OnEvent_Die_Before(idKiller);

	Character::OnEvent_Die(idKiller);

	OnEvent_Die_After(idKiller);

	__UNGUARD__
}

void	Monster::OnEvent_Die_Before(ObjID_t idKiller)
{
	switch (m_DropRuler)
	{
	case BDR_UNKNOW:
	case BDR_BOSS:
	case BDR_COMMON:
	case BDR_BLUE:
	case BDR_GOLD:
	{
		CaculateMonsterDropRuler::CaculateCommOwnerList(this);
	}
	break;

	default:
		break;
	}
}

void	Monster::OnEvent_Die_After(ObjID_t idKiller)
{

	DistributeExpToKiller();
	switch (m_DropRuler)
	{
	case BDR_COMMON:
	{
		if (!CaculateMonsterDropRuler::CaculateCommDropRuler(this, m_DropRuler))
		{
		}
	}
	break;

	case BDR_BOSS:
	{
		if (!CaculateMonsterDropRuler::CaculateBossDropRuler(this, m_DropRuler))
		{
		}
	}
	break;

	case BDR_BLUE:
	case BDR_GOLD:
	{
		if (!CaculateMonsterDropRuler::CaculateHuoDongBossDropRuler(this, m_DropRuler))
		{
		}
	}
	break;

	default:
		KCheck(FALSE);
		break;
	}
}

void Monster::Enter_Respawn(void)
{
	m_Own_TeamID = INVALID_ID;

	m_OccupantGUID = INVALID_ID;
	m_fControlValue = 0;
	m_OccupantLevel = 0;
	m_CooldownList.Clear();
	m_paramLogic_Move.Reset();
	m_RespawnTimer.Clear();
	if (m_RespawnTime >= 0)
	{
		m_RespawnTimer.BeginTimer((uint32)(m_RespawnTime * g_Config.m_ConfigInfo.m_fRespawnParam), NowTime());
	}

	SetActiveFlag(FALSE);
}

void	Monster::UpdateDamageList(int32 nDamage, Character* pAttacker)
{
	if (nDamage >= 1 && pAttacker)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		Player* pPlayer = NULL;
		Object::ObjectClass nType = pAttacker->GetObjType();
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		switch (nType)
		{
		case Object::OBJECT_CLASS_PLAYER:
			pPlayer = (Player*)(pAttacker);
			break;

		case Object::OBJECT_CLASS_PET:
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			Character* pOwner = ((Pet*)(pAttacker))->GetOwner();
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if (pOwner->GetObjType() == Object::OBJECT_CLASS_PLAYER)
			{
				pPlayer = (Player*)pOwner;
			}
		}
		break;

		default:
			break;
		}

		if (pPlayer != NULL)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			ObjID_t nHumanID = pPlayer->GetID();
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if (GetOccupantGUID() == INVALID_ID)
			{

				m_nOwnerElapsedTick = 0;
				SetOccupantGUID(pPlayer->GetGUID());
				SetOccupantLevel(pPlayer->GetLevel());
				SetControlValue(pPlayer->GetWallow());
				if (m_nOwnerElapsedTick == 0)
				{
					m_nOwnerElapsedTick = GET_TIME().TickCount();
				}
			}
			else
			{
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
				int32	nElapsedTick = GET_TIME().TickCount() -
					m_nOwnerElapsedTick -
					g_Config.m_ConfigInfo.m_ValidAttackTime;
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

				if (nElapsedTick > 0)
				{
					m_DamageMemList.Clear();
				
					SetOccupantGUID(pPlayer->GetGUID());
					SetOccupantLevel(pPlayer->GetLevel());
					SetControlValue(pPlayer->GetWallow());
					m_nOwnerElapsedTick = GET_TIME().TickCount();
				}
				else if (GetOccupantGUID() == pPlayer->GetGUID())
				{
					m_nOwnerElapsedTick = GET_TIME().TickCount();;
				}
			}

			if (GetOccupantGUID() == pPlayer->GetGUID())
			{
				m_DamageMemList.Clear();
				
				m_DamageMemList.AddMember
				(
					pPlayer->GetGUID(),
					pPlayer->GetID(),
					-1,
					nDamage
				);
			}
		}
	}
}

SDamageMemList& Monster::GetKillerRec()
{
	return m_DamageMemList;
}

SMonsterOwnerList& Monster::GetOwnerList()
{
	return m_OwnerList;
}

BOOL			Monster::LockOwner(OWNERCHARACTER* poc, uchar count)
{
	if (count == 0) return FALSE;
	KCheck(poc);

	m_OwnerList.Clear();

	count = count > MAX_TEAM_MEMBER ? MAX_TEAM_MEMBER : count;

	/*~~~~~~*/
	uchar	i;
	/*~~~~~~*/

	for (i = 0; i < count; i++)
	{
		m_OwnerList.AddOwner(poc[i].m_Guid, poc[i].m_ObjID);
	}

	m_OwnerList.LockOwner();

	return TRUE;
}

BOOL			Monster::UnLockOwner()
{
	m_OwnerList.UnLockOwner();

	return TRUE;
}

uint32_t Monster::GetValidOwnerList
(
	uint32_t	nMaxSize,
	Player** ppValidOwner,
	ObjID_t* pValidOwnerID,
	GUID_t* pValidOwnerGUID
)
{
	if (ppValidOwner == NULL && pValidOwnerID == NULL && pValidOwnerGUID == NULL) return 0;

	if (nMaxSize == 0) return 0;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	SMonsterOwnerList&	OwnerList = GetOwnerList();
	int32			nOwnerCount = OwnerList.OwnerCount;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(nOwnerCount <= MAX_TEAM_MEMBER);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	float	fSearchLength = g_Config.m_ConfigInfo.m_nTeamRage;
	Player* pPlayer = NULL;
	int32	nValidMemberCount = 0;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for (int32 i = 0; i < nOwnerCount; i++)
	{
		if
			(
				(OwnerList.OwnerDropList[i].m_Guid == INVALID_ID)
				|| (OwnerList.OwnerDropList[i].m_ObjID == INVALID_ID)
				)
		{
			continue;
		}

		/*~~~~~~~~~~~~~~~~~~~~~*/
		GameMap* pMap = GetMap();
		/*~~~~~~~~~~~~~~~~~~~~~*/

		KCheck(pMap);
		pPlayer = (Player*)pMap->GetSpecificObjByID(OwnerList.OwnerDropList[i].m_ObjID);
		if (NULL == pPlayer)
		{
			continue;
		}

		if (pPlayer->GetGUID() != OwnerList.OwnerDropList[i].m_Guid)
		{
			continue;
		}

		if (pPlayer->IsInValidRadius(this, fSearchLength))
		{
			if (ppValidOwner != NULL) ppValidOwner[nValidMemberCount] = pPlayer;
			if (pValidOwnerID != NULL)
				pValidOwnerID[nValidMemberCount] = OwnerList.OwnerDropList[i].m_ObjID;
			if (pValidOwnerGUID != NULL)
				pValidOwnerGUID[nValidMemberCount] = OwnerList.OwnerDropList[i].m_Guid;

			nValidMemberCount++;
			if (nValidMemberCount >= nMaxSize) break;
		}
	}

	return nValidMemberCount;
}

BOOL	Monster::GetNearCanDropPos(GLPos& dropPos)
{
	MapDropPosManager* pDropPosMag = GetMap()->GetMapDropPosManager();
	KCheck(pDropPosMag);

	//当前位置整数化
	GLPos Pos = *GetGLPos();
	uint32 pos_x = (uint32)(Pos.m_fX / g_Config.m_ConfigInfo.m_DropPosDistance);
	uint32 pos_z = (uint32)(Pos.m_fZ / g_Config.m_ConfigInfo.m_DropPosDistance);
	Pos.m_fX = pos_x * g_Config.m_ConfigInfo.m_DropPosDistance;
	Pos.m_fZ = pos_z * g_Config.m_ConfigInfo.m_DropPosDistance;

	int32 nRandPos = 0;

	//根据掉落规则进行相关处理
	switch (m_DropRuler)
	{
	case BDR_BLUE:
	case BDR_GOLD:
	{
		//随机一个索引
		nRandPos = RandGenerator::GetRand(0, 20);

		//取得位置数据
		DROP_POS_TB* pDropPos = g_ItemTab.GetDropPosTB(nRandPos);
		KCheck(pDropPos);

		//之前的整数位置与掉落位置相加，得出新的位置，确保在之前的范围基础上得出新的位置
		dropPos.m_fX = Pos.m_fX + pDropPos->m_DropX;
		dropPos.m_fZ = Pos.m_fZ + pDropPos->m_DropZ;

		//在全局范围内寻找一个可用的掉落位置
		for (int32 i = 0; i < g_Config.m_ConfigInfo.m_DropSearchRange; ++i)
		{
			if (nRandPos >= g_Config.m_ConfigInfo.m_DropSearchRange)
				nRandPos = 0;

			pDropPos = g_ItemTab.GetDropPosTB(nRandPos);
			KCheck(pDropPos);
			dropPos.m_fX = Pos.m_fX + pDropPos->m_DropX;
			dropPos.m_fZ = Pos.m_fZ + pDropPos->m_DropZ;

			//检查是否可以掉落，如果可以掉落，则直接返回本次掉落结果
			if (pDropPosMag->CanDrop(dropPos.m_fX, dropPos.m_fZ))
			{
				return TRUE;
			}

			++nRandPos;
		}
	}

	case BDR_BOSS:
	{
		nRandPos = RandGenerator::GetRand(0, 20);

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		DROP_POS_TB* pDropPos = g_ItemTab.GetDropPosTB(nRandPos);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		KCheck(pDropPos);
		dropPos.m_fX = Pos.m_fX + pDropPos->m_DropX;
		dropPos.m_fZ = Pos.m_fZ + pDropPos->m_DropZ;

		/*~~~~~~~~~~~~~~*/
		int32	count = 0;
		/*~~~~~~~~~~~~~~*/

		for (int32 i = 0; i < g_Config.m_ConfigInfo.m_DropSearchRange; ++i)
		{
			if (nRandPos >= g_Config.m_ConfigInfo.m_DropSearchRange)
			{
				nRandPos = 0;
			}

			pDropPos = g_ItemTab.GetDropPosTB(nRandPos);
			KCheck(pDropPos);
			dropPos.m_fX = Pos.m_fX + pDropPos->m_DropX;
			dropPos.m_fZ = Pos.m_fZ + pDropPos->m_DropZ;

			if (pDropPosMag->CanDrop(dropPos.m_fX, dropPos.m_fZ))
			{
				return TRUE;
			}

			++nRandPos;
		}
	}
	break;

	case BDR_COMMON:
	{
		nRandPos = RandGenerator::GetRand(0, 3);

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		DROP_POS_TB* pDropPos = g_ItemTab.GetDropPosTB(nRandPos);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		KCheck(pDropPos);
		dropPos.m_fX = Pos.m_fX + pDropPos->m_DropX;
		dropPos.m_fZ = Pos.m_fZ + pDropPos->m_DropZ;

		for (int32 i = 0; i < g_Config.m_ConfigInfo.m_DropSearchRange; ++i)
		{
			if (nRandPos >= g_Config.m_ConfigInfo.m_DropSearchRange)
			{
				nRandPos = 0;
			}

			pDropPos = g_ItemTab.GetDropPosTB(nRandPos);
			KCheck(pDropPos);
			dropPos.m_fX = Pos.m_fX + pDropPos->m_DropX;
			dropPos.m_fZ = Pos.m_fZ + pDropPos->m_DropZ;

			if (pDropPosMag->CanDrop(dropPos.m_fX, dropPos.m_fZ))
			{
				return TRUE;
			}

			++nRandPos;
		}
	}
	break;

	default:
		return FALSE;
		break;
	}

	return FALSE;
}