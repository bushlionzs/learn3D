/*$T Client/Game/Table/GameTableDefine.h GC 1.140 08/23/09 04:52:43 */


#ifndef _GAME_TABLE_DEFINE_H_
#define _GAME_TABLE_DEFINE_H_

#include "GameTableData.h"
struct TABLE_FILE_LOAD_DEFINE
{
	int32		nTableEnum;
	LPCTSTR szTableFile;
};
static TABLE_FILE_LOAD_DEFINE	g_TableFileLoad[] =
{
	/* ֻ�ڿͻ����� */
	{ TABLE_CHARACTER_RACE, "char_race" },

	/* �������� */
	{ TABLE_CHARACTER_HEAD_GEO, "char_head" },

	/* ��������ģ�� */
	{ TABLE_CHARACTER_MODEL, "char_model" },

	/* ����ID��Ӧģ������ */
	{ TABLE_CHARACTER_MOUNT, "char_mount" },

	/* ����� */
	{ TABLE_CHARACTER_FACE, "char_face" },

	/* ͷ����Ϣ */
	{ TABLE_SYSTEM_COLOR, "sys_color" },

	/* ������Ϣ��ɫ�� */
	{ TABLE_ITEM_VISUAL_CHAR, "item_char" },

	/* װ������Ʒ���������壬�ֱۣ��š��������� */
	{ TABLE_EQUIP_LOC, "equip_loc" },

	/* װ������Ʒ��ʾ���壨���壬�ֱۣ��š��������� */
	{ TABLE_ITEM_VISUAL_LOCATOR, "item_loc" },

	/* �ҽ�����Ʒ��ʾ���壨������ */
	{ TABLE_ITEM_MONSTER_VISUAL_LOCATOR, "item_mon_loc" },

	/* �ֹ������� */
	{ TABLE_SOUND_INFO, "snd_info" },

	/* ���������ļ� */
	{ TABLE_SCENE_DEFINE, "scene_define" },

	/* �������� */
	{ TABLE_SCENE_POS_DEFINE, "scene_position" },

	/* �������͵㶨�� */
	{ TABLE_SCENE_TRANS_DEFINE, "scene_trans_path" },
	{ TABLE_UI_LAYOUTDEFINE, "ui" },

	/* UI�鶨�� */
	{ TABLE_QUEST_KIND, "mission_type" },

	/* �������� */
	{ TABLE_STRING_DICT, "str_dic" },

	/* �������ɫת���ַ����ֵ䣩 */
	{ TABLE_TALK_FILTER, "str_filter" },

	/* ���˴ʻ��ļ� */
	{ TABLE_TALK_ACT, "chat_act" },

	/* ���춯�������ļ� */
	{ TABLE_MONSTER_PAOPAO, "mon_pop" },

	/* ������������ */
	{ TABLE_FULLCMP_FILTER, "cmp_filter" },

	/* ��ȫƥ����˱����ڴ�����ᡢ������֮��ĵط�������ʹ��ϵͳ���飩 */
	{ TABLE_ITEM_GEM_CLIENT_TYPE, "Gem_Type" },

	/* ��ʯ������Ϣ */
	{ TABLE_EQUIP_OPERATOR_SHOW, "equip_show" },

	/* װ���淨������Ч���� */
	{ TABLE_CHAR_FASHION, "char_fashion" },

	/* ʱװ */
	{ TABLE_EQUIP_STAR_EFFECT, "equip_star_effect" },

	/* װ��������Ч�� */
	{ TABLE_HELP_INFO, "help" },

	/* ���ְ��� */
	{ TABLE_EQUIP_SET_EFFECT, "taozhuangtexiao" },

	/* ��װ��Ч��� */
	{ TABLE_IB_SHOP, "IBshop" },

	/*
	 * ����̵� ;
	 * �ͷ���������
	 */
	{ TABLE_ITEM_EQUIP_VISUAL, "equipmodel" },

	/* װ��ģ�ͱ� */
	{ TABLE_ITEM_EQUIP, "equip_base" },

	/* ��Ʒ���� ����װ���� */
	{ TABLE_CHARACTER_HAIR_GEO, "char_hair" },

	/* ����ͷ��ģ�� */
	{ TABLE_CHARACTER_EXPLEVEL, "pl_explv" },

	/* ������������ֵ */
	{ TABLE_CREATURE_ATT, "mon_attr_ex" },

	/* ���ﶨ���ܱ� */
	{ TABLE_PET_LEVELUP, "horse_lvup" },

	/* �����������辭��� */
	{ TABLE_ITEM_MEDIC, "item_miscellaneous" },

	/* ��Ʒ���� ҩƿ */
	{ TABLE_ITEM_TASK, "item _quest" },

	/* ������Ʒ */
	{ TABLE_ITEM_GEM, "gem_info" },

	/* ��Ʒ���� ��ʯ */
	{ TABLE_SPECIAL_OBJ_DATA, "sp_obj" },

	/* ����OBJ���� */
	{ TABLE_LIFEABILITY_GROWPOINT, "grow_point" },

	/* ����� ��Դ������ */
	{ TABLE_LIFEABILITY_DEFINE, "ability" },

	/* ����� */
	{ TABLE_LIFEABILITY_ITEMCOMPOSE, "item_mix" },

	/* ����� ��Ʒ�ϳ� */
	{ TABLE_ITEM_RULE, "item_formula" },

	/* ��Ʒ���� */
	{ TABLE_LV_MAXMONEY, "lv_maxmoney" },

	/* �ȼ���Ǯ��Ӧ�� */
	{ TABLE_TALK_CONFIG, "chat_cfg" },

	/* ���������ļ� */
	{ TABLE_HAIR_STYLE, "hair_sty" },

	/* ���͸ı����ı� */
	{ TABLE_SKILL_DATA, "spell_logic" },

	/* ���� */
	{ TABLE_SKILL_STUDY_DATA, "spell_learn" },

	/* ����ѧϰ */
	{ TABLE_BUFF_IMPACT, "buff_describe" },

	/* BUFF����Ч�� */
	{ TABLE_DIRECTLY_IMPACT, "buff_effect" },

	/* DIRECTLY����Ч�� */
	{ TABLE_CAMP_AND_STAND, "camp_stand" },

	/* ��Ӫ */
	{ TABLE_BULLET_DATA, "blt" },

	/* �ӵ� */
	{ TABLE_QUEST_INFO, "obj_quest" },

	/* ����NPC��Ϣ */
	{ TABLE_EQUIP_HOLE_INFO, "Equip_HoleReqInfo" },

	/* װ�������Ϣ�� */
	{ TABLE_EQUIP_BINDING_INFO, "Equip_bind" },

	/* װ������Ϣ�� */
	{ TABLE_EQUIP_ADD_START, "Equip_levelup" },

	/* װ��������Ϣ�� */
	{ TABLE_EQUIP_SP_REPAIR, "Equip_SpecialRepair" },

	/* װ��������Ϣ�� */
	{ TABLE_EQUIP_PRODUCT_INFO, "equip_product_info" },

	/* װ���ϳɸ���� */
	{ TABLE_EQUIP_MATERIAL_INFO, "MaterialLevel_info" },

	/* ���ϵȼ��� */
	{ TABLE_MOUNT_ITEM_DATA, "horse_daoju" },
	{ TABLE_EQUIP_CARD_INFO, "pai_info" },

	/* ÿ������Ϣ�� */
	{ TABLE_EQUIP_CARD_GROUP_INFO, "chain_info" },

	/* װ�����С������Ϣ�� */
	{ TABLE_EQUIP_CARD_ALL, "soul_info" },

	/* װ�����󼤻���Ϣ�� */
	{ TABLE_EQUIP_SET_INFO, "equipset_attr" },

	/* ��װ��Ϣ�� */
	{ TABLE_EQUIP_CARD_TARGET, "ChangePai_info" },

	/* ���Ʊ�� */
	{ TABLE_MOUNT_BASE_DATA, "horse_jichu" },

	/* ��������� */
	{ TABLE_TITLE, "title_info" },

	/* �ƺ� */
	{ TABLE_DAY_TIPS, "DayTips" },

	/* ÿ�����ѹ��ܱ� */
	{ TABLE_TOP_LIST, "TopList" },

	/* ���а��ܱ� */
	{ TABLE_QUEST_LOG, "questlog" },

	/* ��������ܱ� */
	{ TABLE_EQUIP_IMPACT, "buff_logic" },

	/* impact��� */
	{ TABLE_WORLD_POS, "WorldPos" },

	/* �����ͼ��ת�� */
	{ TABLE_SCENEMAP_NPC, "scenemap_npc" },

	/* ��ǰ����NPC�� */
	{ TABLE_ITEM_EXTBAG, "Extra_Bag" },

	/* ��չ���� //by soongxl */
	{ TABLE_PROVINCE_ZONE, "Province_Zone" },

	/* ʡ������� */
	{ TABLE_DEATH_DEAL, "death_deal" },

	/* ��������� */
	{ TABLE_BRITH_COST, "brith_cost" },

	/* �������ñ� */
	{ TABLE_BUS_ATTR, "bus_attr_ex" },

	/* BUS���Ա� */
	{ TABLE_LOGIN_SCENE, "login_scene" },

	/* ��½��صĳ������� */
	{ TABLE_CAMERA_TRACK, "camera_track" },

	/* ������켣�� */
	{ TABLE_QUEST_SCRIPT, "script" },

	/* ����ű� */
	{ TABLE_QUEST_DELIVERY, "Quest_Delivery" },

	/* �������� */
	{ TABLE_QUEST_ENTERAREA, "Quest_EnterArea" },

	/* ̽������ */
	{ TABLE_QUEST_KILLMONSTER, "Quest_KillMonster" },

	/* ɱ������ */
	{ TABLE_QUEST_LIST, "Quest_List" },
	{ TABLE_QUEST_USEITEM, "Quest_UseItem" },
	{ TABLE_QUEST_LOOTITEM, "Quest_LootItem" },

	/* �ռ����� */
	{ TABLE_QUESTIONS, "questions" },

	/* ����� */
	{ TABLE_AUTHORITY_GUILD, "auth_ruler_guild" },

	/* ��ᣬְλ��ְ������Ӧ��Ȩ�ޱ� */
	{ TABLE_AUTHORITY_COUNTRY, "auth_ruler_country" },

	/* ���ң�ְλ��ְ������Ӧ��Ȩ�ޱ� */
	{ TABLE_MOODANIM, "char_moodanim" },

	/* ���鶯������ */
	{ TABLE_BEASTIE_ATTR, "beastie_attr" },

	/* ���ȼ����Ա� */
	{ TABLE_GUILD_LEVEL_INFO, "guild_level_info" },

	/* ��Ṧ�±� */
	{ TABLE_GUILD_MERIT_INFO, "guild_merit_info" },

	/* ���ȼ���Ϣ ����ʱ��Ҫ�õ� */
	{ TABLE_SCENEOB_SOUNE, "sceneobj_sound" },

	/* �����ж��� */
	{ TABLE_SCENEOB_LIGHT, "sceneobj_light" },

	/* �����ж��� */
	{ TABLE_SCENEOB_EFFECT, "sceneobj_effect" },

	/* �����ж��� */
	{ TABLE_GLOBAL_CONFIG, "config" },

	/* ȫ�������ļ� */
	{ TABLE_MOUNT_APTITUDE, "horse_zizhi" },

	/* �������ʱ� */
	{ TABLE_CHANGCD_MAP_TIPS_INFO, "changemap_tips_info" },

	/* ��ͼ����ʱ����Ϣ��ʾ */
	{ TABLE_SYSTEMINFO, "SystemInfo" },

	/* ϵͳ��ʾ��Ϣ */
	{ TABLE_COMBIN_TITLE, "title_combination" },

	/* ��ϳƺű� */
	{ TABLE_FRIEND, "FriendEffect" },

	/* ���� */
	{ TABLE_SPOUSE, "MarryEffect" },

	/* ��ż */
	{ TABLE_AAS_NODE_INFO, "char_AASNode" },

	/* ���ﶯ���ڵ� */
	{ TABLE_WORLD_SHOP_ATTR, "WorldShop" },

	/* ȫ���ֽ��̵� */
	{ TABLE_EQUIP_ACTIVATION_TABLE, "equip_activation" },

	/* �������ļ���� */
	{ TABLE_EQUIP_COLORCHANGCD_TABLE, "Equip_ColorChange" },

	/* ��װ����װ�� */
	{ TABLE_EQUIP_PURPLEREWORK_TABLE, "Equip_PurpleRework" },

	/* �������� */
	{ TABLE_SCENE_ANSWER, "scene_answer" },

	/* ��¼���� */
	{ TABLE_LOGIN_ANSWER, "login_answer" },

	/* �������� */
	{ TABLE_GEM_REWORK_TABLE, "GemRework" },

	/* ��ʯ�����ͺϳ� */
	{ TABLE_EQUIP_COPY_TABLE, "EquipCopy" },
	/*װ������*/
	{ TABLE_EQUIP_RECALL_TABLE, "EquipRecall" },
	/*���ͷ�������Ĵ��ͳ���*/
	{ TABLE_TRANSITEM_POS_TABLE, "TransItemPos" },
	/*���������գ��������*/
	{ TABLE_ENERGYBALL_TABLE, "EnergyBall" },
	/*���������գ��������*/
	{ TABLE_AMULET_TABLE, "AmuletInfo" },
	/* ����װ�� */
	{ TABLE_EQUIP_PRODUCE, "EquipProduce" },

	/* װ��ת�� */
	{ TABLE_EQUIP_SWITCH, "EquipSwitch" },

	// �츳��Ч
	{ TABLE_INHERENCE_IMPACT, "pl_exp_inherence" },

	// ��������
	{ TABLE_SCENE_AREA, "scene_area" },

	// �����������
	{ TABLE_SCENE_ACTOR_MESH, "sceneActorMesh" },

	// ������ɫ
	{ TABLE_SCENE_COLOR, "sceneColor" },
	
	//����ָ��
	{ TABLE_WORLD_DIRECTORY,"WorldDirectory"},

	//��������
	{ TABLE_CHANGE_APPEARANCE,"change_appearance"},

	// ��������
	{ TABLE_CHAR_SOUND, "char_sound"},

	{ TABLE_GIFT_LEARN, "gift_learn" },
	
	/* �츳ƽ���ȼ��� */
	{ TABLE_AVG_INHERENCE, "inherence_level_average" },

	/*���������գ��������*/
	{ TABLE_ENERGYBALLSYN, "EnergyBallSyn" },

	// ƽ���츳ѧϰ
	{ TABLE_BALANCE_LEARN_1, "gift_balance_learn_1" },
	{ TABLE_BALANCE_LEARN_2, "gift_balance_learn_2" },

	// ����һЩ����npcͷ�ϵ�������
	{ TABLE_NPC_SPECIAL_TITLE, "NpcSpecialTitle" },

	/* ��װ����� */
	{ TABLE_NEW_EQUIP_PRODUCE, "Equip_Produce_New" },

	/*��������*/
	{TABLE_EQUIP_CONST_BIND, "Equip_Const_Bind"},

	{TABLE_EQUIP_CONST_INFO, "Equip_Const_Info"},

	{TABLE_EQUIP_CONST_ACTIVE_POINT, "Equip_Const_Active_Point"},	

	/* 2010-10-19 by rj �����ҷ�������ʾ */
	{TABLE_WORLD_NAME, "worldname"},

	/*�ض��淨��Ʒ��*/
	{TABLE_ITEM_SPECIAL, "Item_Special"},

    // 2010-11-03 add by ql ר����ר����
    {TABLE_GIFT_ZHUANGONG, "gift_zhuangong" },
    {TABLE_GIFT_ZHUANFANG, "gift_zhuanfang" },

	//��������
    {TABLE_EQUIP_HONOR_BIND, "Equip_Honor_Bind" },	
	
	// ������޼���ѧϰ���ı�
	{TABLE_GUILD_BUS_SKILL_STUDY_CONSUME, "Bus_Sill_Study_Consume"},

};
#endif /* _GAME_TABLE_DEFINE_H_ */
