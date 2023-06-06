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
	/* 只在客户端用 */
	{ TABLE_CHARACTER_RACE, "char_race" },

	/* 主角种族 */
	{ TABLE_CHARACTER_HEAD_GEO, "char_head" },

	/* 主角脸部模型 */
	{ TABLE_CHARACTER_MODEL, "char_model" },

	/* 外形ID对应模型名称 */
	{ TABLE_CHARACTER_MOUNT, "char_mount" },

	/* 坐骑表 */
	{ TABLE_CHARACTER_FACE, "char_face" },

	/* 头像信息 */
	{ TABLE_SYSTEM_COLOR, "sys_color" },

	/* 字体信息颜色表 */
	{ TABLE_ITEM_VISUAL_CHAR, "item_char" },

	/* 装备类物品索引（身体，手臂，脚。。。。） */
	{ TABLE_EQUIP_LOC, "equip_loc" },

	/* 装备类物品显示定义（身体，手臂，脚。。。。） */
	{ TABLE_ITEM_VISUAL_LOCATOR, "item_loc" },

	/* 挂接类物品显示定义（武器） */
	{ TABLE_ITEM_MONSTER_VISUAL_LOCATOR, "item_mon_loc" },

	/* 怪挂武器表 */
	{ TABLE_SOUND_INFO, "snd_info" },

	/* 场景定义文件 */
	{ TABLE_SCENE_DEFINE, "scene_define" },

	/* 场景定义 */
	{ TABLE_SCENE_POS_DEFINE, "scene_position" },

	/* 场景传送点定义 */
	{ TABLE_SCENE_TRANS_DEFINE, "scene_trans_path" },
	{ TABLE_UI_LAYOUTDEFINE, "ui" },

	/* UI组定义 */
	{ TABLE_QUEST_KIND, "mission_type" },

	/* 任务种类 */
	{ TABLE_STRING_DICT, "str_dic" },

	/* 表情和颜色转换字符（字典） */
	{ TABLE_TALK_FILTER, "str_filter" },

	/* 过滤词汇文件 */
	{ TABLE_TALK_ACT, "chat_act" },

	/* 聊天动作命令文件 */
	{ TABLE_MONSTER_PAOPAO, "mon_pop" },

	/* 怪物聊天泡泡 */
	{ TABLE_FULLCMP_FILTER, "cmp_filter" },

	/* 完全匹配过滤表（用在创建帮会、起名字之类的地方，避免使用系统词组） */
	{ TABLE_ITEM_GEM_CLIENT_TYPE, "Gem_Type" },

	/* 宝石需求信息 */
	{ TABLE_EQUIP_OPERATOR_SHOW, "equip_show" },

	/* 装备玩法声音特效配置 */
	{ TABLE_CHAR_FASHION, "char_fashion" },

	/* 时装 */
	{ TABLE_EQUIP_STAR_EFFECT, "equip_star_effect" },

	/* 装备星星特效表 */
	{ TABLE_HELP_INFO, "help" },

	/* 新手帮助 */
	{ TABLE_EQUIP_SET_EFFECT, "taozhuangtexiao" },

	/* 套装特效表格 */
	{ TABLE_IB_SHOP, "IBshop" },

	/*
	 * 金币商店 ;
	 * 和服务器共用
	 */
	{ TABLE_ITEM_EQUIP_VISUAL, "equipmodel" },

	/* 装备模型表 */
	{ TABLE_ITEM_EQUIP, "equip_base" },

	/* 物品定义 人物装备表 */
	{ TABLE_CHARACTER_HAIR_GEO, "char_hair" },

	/* 主角头发模型 */
	{ TABLE_CHARACTER_EXPLEVEL, "pl_explv" },

	/* 主角升级经验值 */
	{ TABLE_CREATURE_ATT, "mon_attr_ex" },

	/* 生物定义总表 */
	{ TABLE_PET_LEVELUP, "horse_lvup" },

	/* 宠物升级所需经验表 */
	{ TABLE_ITEM_MEDIC, "item_miscellaneous" },

	/* 物品定义 药瓶 */
	{ TABLE_ITEM_TASK, "item _quest" },

	/* 任务物品 */
	{ TABLE_ITEM_GEM, "gem_info" },

	/* 物品定义 宝石 */
	{ TABLE_SPECIAL_OBJ_DATA, "sp_obj" },

	/* 法术OBJ数据 */
	{ TABLE_LIFEABILITY_GROWPOINT, "grow_point" },

	/* 生活技能 资源生长点 */
	{ TABLE_LIFEABILITY_DEFINE, "ability" },

	/* 生活技能 */
	{ TABLE_LIFEABILITY_ITEMCOMPOSE, "item_mix" },

	/* 生活技能 物品合成 */
	{ TABLE_ITEM_RULE, "item_formula" },

	/* 物品规则 */
	{ TABLE_LV_MAXMONEY, "lv_maxmoney" },

	/* 等级金钱对应表 */
	{ TABLE_TALK_CONFIG, "chat_cfg" },

	/* 聊天配置文件 */
	{ TABLE_HAIR_STYLE, "hair_sty" },

	/* 发型改变消耗表 */
	{ TABLE_SKILL_DATA, "spell_logic" },

	/* 技能 */
	{ TABLE_SKILL_STUDY_DATA, "spell_learn" },

	/* 技能学习 */
	{ TABLE_BUFF_IMPACT, "buff_describe" },

	/* BUFF附加效果 */
	{ TABLE_DIRECTLY_IMPACT, "buff_effect" },

	/* DIRECTLY附加效果 */
	{ TABLE_CAMP_AND_STAND, "camp_stand" },

	/* 阵营 */
	{ TABLE_BULLET_DATA, "blt" },

	/* 子弹 */
	{ TABLE_QUEST_INFO, "obj_quest" },

	/* 任务NPC信息 */
	{ TABLE_EQUIP_HOLE_INFO, "Equip_HoleReqInfo" },

	/* 装备打孔信息表 */
	{ TABLE_EQUIP_BINDING_INFO, "Equip_bind" },

	/* 装备绑定信息表 */
	{ TABLE_EQUIP_ADD_START, "Equip_levelup" },

	/* 装备打星信息表 */
	{ TABLE_EQUIP_SP_REPAIR, "Equip_SpecialRepair" },

	/* 装备打星信息表 */
	{ TABLE_EQUIP_PRODUCT_INFO, "equip_product_info" },

	/* 装备合成改造表 */
	{ TABLE_EQUIP_MATERIAL_INFO, "MaterialLevel_info" },

	/* 材料等级表 */
	{ TABLE_MOUNT_ITEM_DATA, "horse_daoju" },
	{ TABLE_EQUIP_CARD_INFO, "pai_info" },

	/* 每张牌信息表 */
	{ TABLE_EQUIP_CARD_GROUP_INFO, "chain_info" },

	/* 装备灵魂小激活信息表 */
	{ TABLE_EQUIP_CARD_ALL, "soul_info" },

	/* 装备灵魂大激活信息表 */
	{ TABLE_EQUIP_SET_INFO, "equipset_attr" },

	/* 套装信息表 */
	{ TABLE_EQUIP_CARD_TARGET, "ChangePai_info" },

	/* 换牌表格 */
	{ TABLE_MOUNT_BASE_DATA, "horse_jichu" },

	/* 坐骑基础表 */
	{ TABLE_TITLE, "title_info" },

	/* 称号 */
	{ TABLE_DAY_TIPS, "DayTips" },

	/* 每日提醒功能表 */
	{ TABLE_TOP_LIST, "TopList" },

	/* 排行榜功能表 */
	{ TABLE_QUEST_LOG, "questlog" },

	/* 任务管理功能表 */
	{ TABLE_EQUIP_IMPACT, "buff_logic" },

	/* impact表格 */
	{ TABLE_WORLD_POS, "WorldPos" },

	/* 世界地图跳转表 */
	{ TABLE_SCENEMAP_NPC, "scenemap_npc" },

	/* 当前场景NPC表 */
	{ TABLE_ITEM_EXTBAG, "Extra_Bag" },

	/* 扩展背包 //by soongxl */
	{ TABLE_PROVINCE_ZONE, "Province_Zone" },

	/* 省份区域表 */
	{ TABLE_DEATH_DEAL, "death_deal" },

	/* 死亡处理表 */
	{ TABLE_BRITH_COST, "brith_cost" },

	/* 重生费用表 */
	{ TABLE_BUS_ATTR, "bus_attr_ex" },

	/* BUS属性表 */
	{ TABLE_LOGIN_SCENE, "login_scene" },

	/* 登陆相关的场景数据 */
	{ TABLE_CAMERA_TRACK, "camera_track" },

	/* 摄像机轨迹表 */
	{ TABLE_QUEST_SCRIPT, "script" },

	/* 任务脚本 */
	{ TABLE_QUEST_DELIVERY, "Quest_Delivery" },

	/* 送信任务 */
	{ TABLE_QUEST_ENTERAREA, "Quest_EnterArea" },

	/* 探索任务 */
	{ TABLE_QUEST_KILLMONSTER, "Quest_KillMonster" },

	/* 杀怪任务 */
	{ TABLE_QUEST_LIST, "Quest_List" },
	{ TABLE_QUEST_USEITEM, "Quest_UseItem" },
	{ TABLE_QUEST_LOOTITEM, "Quest_LootItem" },

	/* 收集任务 */
	{ TABLE_QUESTIONS, "questions" },

	/* 问题库 */
	{ TABLE_AUTHORITY_GUILD, "auth_ruler_guild" },

	/* 帮会，职位与职能所对应的权限表 */
	{ TABLE_AUTHORITY_COUNTRY, "auth_ruler_country" },

	/* 国家，职位与职能所对应的权限表 */
	{ TABLE_MOODANIM, "char_moodanim" },

	/* 表情动画数据 */
	{ TABLE_BEASTIE_ATTR, "beastie_attr" },

	/* 帮会等级属性表 */
	{ TABLE_GUILD_LEVEL_INFO, "guild_level_info" },

	/* 帮会功德表 */
	{ TABLE_GUILD_MERIT_INFO, "guild_merit_info" },

	/* 帮会等级信息 升级时需要用到 */
	{ TABLE_SCENEOB_SOUNE, "sceneobj_sound" },

	/* 场景中对象 */
	{ TABLE_SCENEOB_LIGHT, "sceneobj_light" },

	/* 场景中对象 */
	{ TABLE_SCENEOB_EFFECT, "sceneobj_effect" },

	/* 场景中对象 */
	{ TABLE_GLOBAL_CONFIG, "config" },

	/* 全局配置文件 */
	{ TABLE_MOUNT_APTITUDE, "horse_zizhi" },

	/* 坐骑资质表 */
	{ TABLE_CHANGCD_MAP_TIPS_INFO, "changemap_tips_info" },

	/* 地图传送时的信息提示 */
	{ TABLE_SYSTEMINFO, "SystemInfo" },

	/* 系统提示信息 */
	{ TABLE_COMBIN_TITLE, "title_combination" },

	/* 组合称号表 */
	{ TABLE_FRIEND, "FriendEffect" },

	/* 好友 */
	{ TABLE_SPOUSE, "MarryEffect" },

	/* 配偶 */
	{ TABLE_AAS_NODE_INFO, "char_AASNode" },

	/* 人物动作节点 */
	{ TABLE_WORLD_SHOP_ATTR, "WorldShop" },

	/* 全局现金商店 */
	{ TABLE_EQUIP_ACTIVATION_TABLE, "equip_activation" },

	/* 打星铭文激活表 */
	{ TABLE_EQUIP_COLORCHANGCD_TABLE, "Equip_ColorChange" },

	/* 黄装升紫装表 */
	{ TABLE_EQUIP_PURPLEREWORK_TABLE, "Equip_PurpleRework" },

	/* 场景答题 */
	{ TABLE_SCENE_ANSWER, "scene_answer" },

	/* 登录答题 */
	{ TABLE_LOGIN_ANSWER, "login_answer" },

	/* 副本答题 */
	{ TABLE_GEM_REWORK_TABLE, "GemRework" },

	/* 宝石升级和合成 */
	{ TABLE_EQUIP_COPY_TABLE, "EquipCopy" },
	/*装备返还*/
	{ TABLE_EQUIP_RECALL_TABLE, "EquipRecall" },
	/*传送符所允许的传送场景*/
	{ TABLE_TRANSITEM_POS_TABLE, "TransItemPos" },
	/*蓝属性吸收，能量球表*/
	{ TABLE_ENERGYBALL_TABLE, "EnergyBall" },
	/*蓝属性吸收，护身符表*/
	{ TABLE_AMULET_TABLE, "AmuletInfo" },
	/* 打造装备 */
	{ TABLE_EQUIP_PRODUCE, "EquipProduce" },

	/* 装备转化 */
	{ TABLE_EQUIP_SWITCH, "EquipSwitch" },

	// 天赋特效
	{ TABLE_INHERENCE_IMPACT, "pl_exp_inherence" },

	// 场景区域
	{ TABLE_SCENE_AREA, "scene_area" },

	// 场景互动物件
	{ TABLE_SCENE_ACTOR_MESH, "sceneActorMesh" },

	// 场景颜色
	{ TABLE_SCENE_COLOR, "sceneColor" },
	
	//江湖指南
	{ TABLE_WORLD_DIRECTORY,"WorldDirectory"},

	//更换形象
	{ TABLE_CHANGE_APPEARANCE,"change_appearance"},

	// 人物声音
	{ TABLE_CHAR_SOUND, "char_sound"},

	{ TABLE_GIFT_LEARN, "gift_learn" },
	
	/* 天赋平均等级表 */
	{ TABLE_AVG_INHERENCE, "inherence_level_average" },

	/*蓝属性吸收，能量球表*/
	{ TABLE_ENERGYBALLSYN, "EnergyBallSyn" },

	// 平衡天赋学习
	{ TABLE_BALANCE_LEARN_1, "gift_balance_learn_1" },
	{ TABLE_BALANCE_LEARN_2, "gift_balance_learn_2" },

	// 更改一些特殊npc头上的名字用
	{ TABLE_NPC_SPECIAL_TITLE, "NpcSpecialTitle" },

	/* 橙装打造表 */
	{ TABLE_NEW_EQUIP_PRODUCE, "Equip_Produce_New" },

	/*星座铭刻*/
	{TABLE_EQUIP_CONST_BIND, "Equip_Const_Bind"},

	{TABLE_EQUIP_CONST_INFO, "Equip_Const_Info"},

	{TABLE_EQUIP_CONST_ACTIVE_POINT, "Equip_Const_Active_Point"},	

	/* 2010-10-19 by rj 跨服玩家服名称显示 */
	{TABLE_WORLD_NAME, "worldname"},

	/*特定玩法物品表*/
	{TABLE_ITEM_SPECIAL, "Item_Special"},

    // 2010-11-03 add by ql 专攻、专防表
    {TABLE_GIFT_ZHUANGONG, "gift_zhuangong" },
    {TABLE_GIFT_ZHUANFANG, "gift_zhuanfang" },

	//荣誉铭刻
    {TABLE_EQUIP_HONOR_BIND, "Equip_Honor_Bind" },	
	
	// 帮会神兽技能学习消耗表
	{TABLE_GUILD_BUS_SKILL_STUDY_CONSUME, "Bus_Sill_Study_Consume"},

};
#endif /* _GAME_TABLE_DEFINE_H_ */
