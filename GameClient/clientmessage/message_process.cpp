//#include "StructEffect.h"
#include "StructDB.h"
#include "OgreHeader.h"

#include "message_process.h"
#include "game_scene_manager.h"
#include "KObjectManager.h"
#include "kplayer.h"
#include "data/GameDataCharacter.h"
#include "KItem.h"
#include "KItemManager.h"
#include "data/GameDataManager.h"
#include "server_message.pb.h"
#include "Enum.h"
#include "KNpc.h"
#include "command/command.h"


void sc_human_base_attr(NetHandle h, const char* msg, uint32_t msg_size)
{
	GameScene* pScene = GameSceneManager::getSingleton().GetActiveScene();
	
	if (nullptr == pScene)
	{
		return;
	}
	
	servermessage::ServerHumanBaseAttrib dummy;

	bool ret = dummy.ParseFromArray(msg, msg_size);

	if (!ret)
	{
		return;
	}

	auto player_id = dummy.player_id();
	KObject* pObj = KObjectManager::GetSingleton().getObject(player_id);
	if (pObj == nullptr)
	{
		pObj = KObjectManager::GetSingleton().createPlayer(player_id);
	}
	
		
	if (pObj->getObjectType() != ObjectType_PlayerOfMe)
	{
		return;
	}
	
	KCharacter* pCharObj = (KCharacter*)pObj;
	
	KCharatcterBaseData* pCharacterData = pCharObj->GetCharacterData();
	auto & flags = dummy.flags();
	
	SFlag64 mFlags;
	mFlags.m_uHighFlags = flags.high_flags();
	mFlags.m_uLowFlags = flags.low_flags();

	if (mFlags.isSetBit(UPDATE_CHARPLAYER_ATT_JOB))
	{
		pCharacterData->SetProfession(dummy.job());
	}
	
	if (mFlags.isSetBit(UPDATE_CHARPLAYER_ATT_COUNTRY))
	{
		pCharacterData->Set_Country(dummy.country());
	}
	
	if (mFlags.isSetBit(UPDATE_CHARPLAYER_ATT_MODEL_ID))
	{
		//pCharacterData->Set_ModelID(mModelID);
	}
	
	if (mFlags.isSetBit(UPDATE_CHARPLAYER_ATT_NAME))
	{
		pCharacterData->Set_Name(dummy.name().c_str());
	}
	
	if (mFlags.isSetBit(UPDATE_CHARPLAYER_ATT_COUNTRYTITLE))
	{
		pCharacterData->Set_CurTitle(dummy.country_title().c_str(), STitle::GUOJIA_TITLE);
	}
	
		
	bool bSecond = false;
	/* 玩法头衔 */
	
	
	/* 等级 */
	if (mFlags.isSetBit(UPDATE_CHARPLAYER_ATT_LEVEL))
	{
		pCharacterData->Set_Level(dummy.level());
	}
	
	/* HP百分比 */
	if (mFlags.isSetBit(UPDATE_CHARPLAYER_ATT_HP_PERCENT))
	{
		pCharacterData->Set_HPPercent(dummy.hp_percent() / 100.0f);
	
	}
	
	if (mFlags.isSetBit(UPDATE_CHARPLAYER_ATT_HP))
	{
		pCharacterData->Set_HP(dummy.hp());
	
	}
	
	if (mFlags.isSetBit(UPDATE_CHARPLAYER_ATT_HP_MAX))
	{
		pCharacterData->Set_MaxHP(dummy.hp_max());
	
	}
	
	/* 怒气 */
	if (mFlags.isSetBit(UPDATE_CHARPLAYER_ATT_RAGE))
	{
		pCharacterData->Set_Rage(dummy.rage());
	}
	
	/* 怒气上限 */
	if (mFlags.isSetBit(UPDATE_CHARPLAYER_ATT_MAX_RAGE))
	{
		pCharacterData->Set_MaxRage(dummy.max_rage());
	}
	
	/* 隐身级别 */
	if (mFlags.isSetBit(UPDATE_CHARPLAYER_ATT_STEALTH_LEVEL))
	{
		pCharacterData->Set_StealthLevel(dummy.steal_level());
	}
	
	/* 是否为坐下状态 */
	if (mFlags.isSetBit(UPDATE_CHARPLAYER_ATT_SIT))
	{
	}
	
	/* 移动速度 */
	if (mFlags.isSetBit(UPDATE_CHARPLAYER_ATT_MOVE_SPEED))
	{
		pCharacterData->Set_MoveSpeed(dummy.move_speed());
	}
	
	/* 攻击速度 */
	if (mFlags.isSetBit(UPDATE_CHARPLAYER_ATT_ATTACK_SPEED))
	{
		pCharacterData->Set_AttackSpeed(dummy.attack_speed());
	}
	
	/* 阵营ID */
	if (mFlags.isSetBit(UPDATE_CHARPLAYER_ATT_CAMP_ID))
	{
		auto& camp_data = dummy.camp_data();
		SCampData tmp;
		tmp.m_nCampID = camp_data.camp_id();
		tmp.m_uPKMode = camp_data.pk_mode();
		tmp.m_nReserve1 = camp_data.reserve1();
		tmp.m_nReserve2 = camp_data.reserve2();
		pCharacterData->Set_CampData(&tmp);
	}
	
	/* 头像ID */
	if (mFlags.isSetBit(UPDATE_CHARPLAYER_ATT_PORTRAIT_ID))
	{
		pCharacterData->Set_PortraitID(dummy.portrait_id());
	}
	
	/* 脸、头发、头发颜色 */
	if (mFlags.isSetBit(UPDATE_CHARPLAYER_ATT_PLAYER_DATA))
	{
		pCharacterData->Set_FaceMesh(dummy.face_mesh_id());
		pCharacterData->Set_HairMesh(dummy.hair_mesh_id());
	}
	
	/* 选择的目标 */
	if (mFlags.isSetBit(UPDATE_CHARPLAYER_TARGETID))
	{
		pCharacterData->Set_TargetId(dummy.target_id());
	}
	
	/* PK值 */
	if (mFlags.isSetBit(UPDATE_CHARPLAYER_PK_VALUE))
	{
		pCharacterData->Set_PKValue(dummy.pk_value());
	}
	
	
	/* 骑乘代数 */
	if (mFlags.isSetBit(UPDATE_CHARPLAYER_BYGENERATION))
	{
		pCharacterData->Set_MountEra(dummy.generation());
		bSecond = TRUE;
	}
	
	/* 角色种族（更换模型）（数据资源ID）, 要放到其他模型数据之后处理, 以保证一次性创建 */
	if (mFlags.isSetBit(UPDATE_CHARPLAYER_ATT_DATA_ID))
	{
		pCharacterData->Set_RaceID(dummy.data_id());
	}
	
	/* 座骑ID, 要在人物之后创建 */
	if (mFlags.isSetBit(UPDATE_CHARPLAYER_ATT_MOUNT_ID))
	{
		pCharacterData->Set_MountID(dummy.mount_id());
	}
	
	if (mFlags.isSetBit(UPDATE_CHARPLAYER_ATT_CURRENT_HORSE_GUID))
	{
		auto& horseGuid = dummy.current_horse_guid();

		SHorseGuid tmp;
		tmp.m_uHighSection = horseGuid.high_section();
		tmp.m_uLowSection = horseGuid.low_section();
		pCharacterData->Set_CurrentPetGUID(tmp);
	}
	
	// 需要天赋特效是打开
	/* 天赋 */
	if (mFlags.isSetBit(UPDATE_CHARPLAYER_INHERENCE_EXP))
	{
		pCharacterData->Set_InherenceExp(dummy.inherence_exp());
	}
	
	if (mFlags.isSetBit(UPDATE_CHARPLAYER_INHERENCE_LEVEL))
	{
		pCharacterData->Set_InherenceLevel(dummy.inherence_level());
	}
	
	pCharObj->UpdateModel_Visible();
	
}

void sc_detail_equip(NetHandle h, const char* msg, uint32_t msg_size)
{
	servermessage::ServerMsgDetailEquipList dummy;
	dummy.ParseFromArray(msg, msg_size);
	KObject* pObj = KObjectManager::GetSingleton().getObject(dummy.object_id());

	if (nullptr == pObj)
	{
		return;
	}

	KPlayer* pPlayer = dynamic_cast<KPlayer*>(pObj);

	if (nullptr == pPlayer)
	{
		return;
	}
	KCharatcterBaseData* pCharacterData = pPlayer->GetCharacterData();

	auto& items = dummy.items();
	for (auto i = 0; i < items.size(); i++)
	{
		auto& item = items[i];
		KItem* pItemObj = KItemManager::GetSingleton().CreateNewItem(item.item_index());
		pItemObj->SetGUID(
			item.item_guid().world(),
			item.item_guid().server(),
			item.item_guid().serial()
		);

		SItem tmp;
		tmp.m_ItemGUID.m_World = item.item_guid().world();
		tmp.m_ItemGUID.m_Serial = item.item_guid().server();
		tmp.m_ItemGUID.m_Server = item.item_guid().serial();
		tmp.m_ItemIndex = item.item_index();
		tmp.m_nsBind = item.ns_bind();
		tmp.m_TermEndTime = item.term_endtime();
		strncpy(tmp.m_Creator, item.creator().c_str(), sizeof(tmp.m_Creator));

		auto& params = item.params();
		for (auto j = 0; j < params.size(); j++)
		{
			tmp.m_Param[j] = params[j];
		}
		pItemObj->SetExtraInfo(&tmp);

		auto pos = item.item_pos();
		pItemObj->SetPosIndex(pos);

		pCharacterData->Set_Equip((PLAYER_EQUIP)pos, pItemObj->GetIdTable());

		GameDataManager::GetSingleton().UserEquip_SetItem(
			(PLAYER_EQUIP)pos, pItemObj, true);
	}

	//ACTION_SYS_PTR->UserEquip_Update();
	pPlayer->UpdateBodyPartModel();
}

void sc_detail_item(NetHandle h, const char* msg, uint32_t msg_size)
{

}

void sc_detail_skill(NetHandle h, const char* msg, uint32_t msg_size)
{

}

void sc_enter_scene(NetHandle h, const char* msg, uint32_t msg_size)
{
	servermessage::ServerMsgEnterMap dummy;
	dummy.ParseFromArray(msg, msg_size);
	auto scene_id = dummy.scene_id();
	GameSceneManager::getSingletonPtr()->loadScene(scene_id);

	Ogre::Vector3 mPosition;
	mPosition.x = dummy.position_x();
	mPosition.y = 0;
	mPosition.z = dummy.position_y();


	KPlayer* pPlayer = (KPlayer*)KObjectManager::GetSingleton().createPlayer(dummy.object_id());
	pPlayer->setPosition(mPosition);
}

void sc_new_monster(NetHandle h, const char* msg, uint32_t msg_size)
{
	servermessage::ServerMsgNewMonster dummy;
	dummy.ParseFromArray(msg, msg_size);

	KPlayer* pPlayer = KObjectManager::GetSingleton().getMySelf();


	Ogre::Vector3 fvGamePos;
	Ogre::Vector3 fvPlanPos = Ogre::Vector3(dummy.position_x(), 0.0f, dummy.position_z());
	EngineManager::getSingleton().positionAxisTrans(
		GAT_GAME, fvPlanPos, GAT_SCENE, fvGamePos);

	float fFaceDir = 0.0f;

	auto obj_id = dummy.object_id();
	KNpc* pNPC = (KNpc*)(KObjectManager::GetSingleton().getObject(obj_id));


	if (nullptr == pNPC)
	{
		pNPC = (KNpc*)KObjectManager::GetSingleton().createNPC(obj_id);

		pNPC->SetServerGUID(dummy.guid());
	}

	
	


	KCharatcterBaseData* pCharacterData = pNPC->GetCharacterData();


	printf("create monster :%s\n", dummy.name().c_str());

	pCharacterData->Set_MountID(dummy.horse_id());

	pCharacterData->Set_MonstWeapon(dummy.weapon_id());

	pCharacterData->Set_RaceID(dummy.race_id());

	pCharacterData->Set_Name(dummy.name().c_str());

	pCharacterData->Set_MoveSpeed(dummy.move_speed());

	
	pCharacterData->Set_HP(100);
	pCharacterData->Set_HPPercent(100);

	auto camp_id = dummy.camp_id();
	if (camp_id != -1)
	{
		SCampData camp;
		camp.m_nCampID = camp_id;
		pCharacterData->Set_CampData(&camp);
	}

	Ogre::Vector2	mapPos(fvGamePos.x, fvGamePos.z);
	pNPC->calculateNodePos(mapPos, 0.0f);
	pNPC->setDirection(fFaceDir);

	/* 设置休闲状态 */
	ObjectCmd	cmdTemp;
	cmdTemp.m_wID = OBJ_CMD_IDLE;
	cmdTemp.fParam[0] = fvGamePos.x;
	cmdTemp.fParam[1] = fvGamePos.z;
	cmdTemp.bParam[2] = FALSE;
	pNPC->AddCommand(&cmdTemp);
}