/*$T MapServer/FileDef.h GC 1.140 10/10/07 11:01:49 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef __FILEDEF_H__
#define __FILEDEF_H__

/************************************************************************/
/* 场景目录声明                                                         */
/************************************************************************/
#define PATH_SCENE							"./map/"

/************************************************************************/
/* 服务器配置相关                                                       */
/************************************************************************/
#define FILE_BASESERVERCONFIG				"../../server_resources/ServerConfig/BaseServerConfig.ini"
#define FILE_EXTSERVERCONFIG				"../../server_resources/ServerConfig/ExtServerConfig.ini"
#define FILE_MULTIGROUPCONFIG		        "../../server_resources/ServerConfig/MultiGroupConfig.ini"
#define FILE_DBSHARECONFIG					"../../server_resources/ServerConfig/DBShareConfig.ini"
#define FILE_GAMECONFIG						"../../server_resources/ServerConfig/GameConfig.ini"
#define FILE_DBCONFIG 						"../../server_resources/ServerConfig/DBConfig.ini"
#define FILE_SERVERINDEX					"../../server_resources/ServerConfig/ServerIndex.ini"
#define FILE_WORLDINDEX						"../../server_resources/ServerConfig/WorldIndex.ini"
#define FILE_GAMETOGGLE						"../../server_resources/ServerConfig/GameToggleConfig.ini"
#define FILE_LOGSERVERCONFIG				"../../server_resources/ServerConfig/LogServerConfig.ini"

//////////////////////////////////////////////////////////////////////////
//#define FILE_SPECIAL_INFO					"./Config/Special.ini"
//#define FILE_CONFIG_INFO					"./Config/ConfigInfo.ini"
//#define FILE_LOGIN_INFO					"./Config/LoginCenterInfo.ini"
//#define FILE_WORLD_INFO					"./Config/GLServerInfo.ini"
//#define FILE_SHARE_MEM_INFO				"./Config/DBShareInfo.ini"
//#define FILE_MACHINE_INFO					"./Config/MachineInfo.ini"
//#define FILE_SERVER_INFO					"./Config/MapServerInfo.ini"
//#define FILE_DBCENTER_INFO				"./Config/DBCenterInfo.ini"

/************************************************************************/
/* 服务器玩法配置                                                       */
/************************************************************************/
#define FILE_PET_CONFIG						"../../server_resources/ServerConfig/HorseConfigTable.ini"
#define FILE_GUILD_MEMBER_ACCESS			"../../server_resources/ServerConfig/GuildMemberAccess.ini"
#define FILE_IPRANGE						"../../server_resources/ServerConfig/IPRange.ini"
#define FILE_BASE_VALUE						"../../server_resources/ServerConfig/BaseValueTable.ini"
#define FILE_ITEM_SERIAL					"../../server_resources/ServerConfig/ItemSerial.ini"
#define FILE_MONITOR_INFO					"../../server_resources/ServerConfig/MonitorInfo.ini"
#define FILE_STOCK_MONITOR_INFO				"../../server_resources/ServerConfig/StockMonitorInfo.ini"

/************************************************************************/
/* 服务器相关内部表格                                                   */
/************************************************************************/
#define FILE_SCENE_INFO						"../../server_resources/ServerConfig/mapdefines.tab"				// 默认的MapServer对应的配置表
#define FILE_SCENE_INFO_6					"../../server_resources/ServerConfig/mapdefines_6.tab"				// 6 MapServer对应的配置表
#define FILE_SCENE_INFO_10					"../../server_resources/ServerConfig/mapdefines_10.tab"			// 10 MapServer对应的配置表
#define FILE_GMLIST							"../../server_resources/ServerConfig/GMList.tab"
#define FILE_NPC_CHAT						"../../server_resources/ServerConfig/npc_speak.tab"
#define FILE_NPCPAOPAOINDEXTBL				"../../server_resources/ServerConfig/npc_pop_index.tab"
#define FILE_PET_ATTRPOINTDISTRIBUTE		"../../server_resources/ServerConfig/horse_sttr_point.tab"
#define FILE_PET_SKILLDISTRIBUTE			"../../server_resources/ServerConfig/horse_skl.tab"
#define FILE_PET_SKILLINDEXTBL				"../../server_resources/ServerConfig/horse_skl_index.tab"
#define FILE_PET_STUDYSKILLTBL				"../../server_resources/ServerConfig/horse_skl_study.tab"
#define FILE_PET_APPERCEIVESKILLTBL			"../../server_resources/ServerConfig/horse_observe_skl.tab"
#define FILE_PET_DOMESTICATION_MONEY		"../../server_resources/ServerConfig/horse_tame_money.tab"
#define FILE_PET_AISTRATEGYTBL				"../../server_resources/ServerConfig/horse_ai.tab"
#define FILE_PET_TRAINCHARGE				"../../server_resources/ServerConfig/HorseTrainCharge.txt"
#define FILE_PET_ATTR						"../../server_resources/ServerConfig/horse_attr.tab"
#define FILE_HORSE_DROP						"../../server_resources/ServerConfig/horse_drop_content.tab"
#define FILE_HORSE_SKILL					"../../server_resources/ServerConfig/horse_skill.tab"
#define FILE_PLANTS							"../../server_resources/ServerConfig/Plants.txt"
#define FILE_ATTR_LEVEL_UP					"../../server_resources/ServerConfig/attr_lvup.tab"
#define FILE_MONSTER_DROP_CONTENT			"../../server_resources/ServerConfig/monsterdrop_content.tab"
#define FILE_DROP_ATTENUATION				"../../server_resources/ServerConfig/drop_fadeout.tab"
#define FILE_DIE_PENALTY					"../../server_resources/ServerConfig/death_penalty.tab"
#define FILE_CHAR_DEFAULT					"../../server_resources/ServerConfig/PlayerTemplte.tab"
#define FILE_MONSTER_SKILL					"../../server_resources/ServerConfig/mon_wqskl.tab"
#define FILE_DROP_POS						"../../server_resources/ServerConfig/dorp_pos.tab"
#define FILE_DUR_SPOIL						"../../server_resources/ServerConfig/DurSpoil.tab"
#define FILE_EQUIP_BLUE_ATTR_SET			"../../server_resources/ServerConfig/equip_blue_attr_set.tab"
#define FILE_EQUIP_BLUE_ATTR_LEVEL			"../../server_resources/ServerConfig/equip_blue_attr_level.tab"
#define FILE_EQUIPEXTRAATT_INFO				"../../server_resources/ServerConfig/EquipExtraAtt_info.tab"
#define FILE_ID_COLLECTION					"../../server_resources/ServerConfig/id_gather.tab"
#define FILE_EQUIPPOINT_INFO				"../../server_resources/ServerConfig/EquipPoint_Value.tab"
#define FILE_FRIEND_GIFT					"../../server_resources/ServerConfig/FriendGift_info.tab"
#define FILE_QUEST_DENGMI_INFO				"../../server_resources/ServerConfig/quest_dengmi.tab"
#define FILE_QUEST_WULONG_INFO				"../../server_resources/ServerConfig/quest_wulong.tab"
#define FILE_STRING_FILTER_TABLE_NAME		"../../server_resources/ServerConfig/str_filter.tab"
#define FILE_TIMER_DOING_LIST				"../../server_resources/ServerConfig/Timer.tab"
#define FILE_TIMER_BATTLE_LIST				"../../server_resources/ServerConfig/GuildBattleTimer.tab"
#define FILE_SCENE_COMMON					"../../server_resources/ServerConfig/map_common.tab"
#define FILE_EQUIP_PURPLEATTR_TB			"../../server_resources/ServerConfig/Equip_PurpleAttr.tab"
#define FILE_ENCRYPT_INFO					"../../server_resources/ServerConfig/encrypt.tab"
#define FILE_LOGIN_ANSWERS_INFO				"../../server_resources/ServerConfig/LoginAnswers.tab"
#define FILE_SCENE_ANSWERS_INFO				"../../server_resources/ServerConfig/SceneAnswers.tab"
#define FILE_MASTER_PRENTICE_TABLE_NAME		"../../server_resources/ServerConfig/master_prentice.tab"
#define FILE_FUBEN_DATA_TABLE_NAME			"../../server_resources/ServerConfig/FubenData.tab"
#define FILE_EQUIP_BLUEATTR					"../../server_resources/ServerConfig/Equip_BlueAttr.tab"			//随机蓝属性
#define FILE_EQUIP_BLUE_INTENSIFY			"../../server_resources/ServerConfig/Equip_BlueIntensify.tab"		//蓝属性强化
#define FILE_CHEAT_ACT_DATA_TABLE_NAME		"../../server_resources/ServerConfig/CheatAct.tab"
#define FILE_WORLD_STOCK_INFO				"../../server_resources/ServerConfig/WorldStock.tab"
#define FILE_PK_POINT						"../../server_resources/ServerConfig/PK_Point.tab"
#define FILE_PK_LEVEL						"../../server_resources/ServerConfig/PK_Level.tab"
#define FILE_PK_PUNISH						"../../server_resources/ServerConfig/PK_Punish.tab"
#define FILE_OPENBOX_ITEM					"../../server_resources/ServerConfig/OpenBoxItem.tab"
#define FILE_ONDIE_MONSTER					"../../server_resources/ServerConfig/OnDie_Monster.tab"
#define FILE_ONDIE_NOPUNISH					"../../server_resources/ServerConfig/OnDie_NoPunish.tab"
#define FILE_ONDIE_DIFFCOUNTRY				"../../server_resources/ServerConfig/OnDie_DiffCountry.tab"
#define FILE_ONDIE_SAMECOUNTRY				"../../server_resources/ServerConfig/OnDie_SameCountry.tab"
#define FILE_ONDIE_SAMECOUNTRY_KILLER		"../../server_resources/ServerConfig/OnDie_Killer.tab"
#define FILE_MENTAL_GAME_ANSWERS			"../../server_resources/ServerConfig/answers.tab"
#define FILE_QUEST_QUIZ_INFO				"../../server_resources/ServerConfig/quest_quiz.tab"
#define FILE_QUEST_SHITU_INFO				"../../server_resources/ServerConfig/quest_shitu.tab"
#define FILE_NEW_EQUIP_BLUEATTR				"../../server_resources/ServerConfig/Equip_BlueAttr_New.tab"    	//橙装随机蓝属性
#define FILE_EQUIP_CONST_ATTR				"../../server_resources/ServerConfig/Equip_Const_Attr.tab"   		//星座装备属性
#define FILE_DYNAMIC_SHOP					"../../server_resources/ServerConfig/dynamic_shop_tab.tab"			// 动态价格商店
#define FILE_RANDOM_MONSTER					"../../server_resources/ServerConfig/random_monster.tab"			// 2010-11-26 by rj 随机怪配置表
/************************************************************************/
/* 客户端服务器端共用内部配置                                           */
/************************************************************************/
#define FILE_MONSTER_BASE_BEHAVIOR			"../../server_resources/Public/Config/monster_base_behavior.ini"

/************************************************************************/
/* 客户端服务器端共用内部表格                                           */
/************************************************************************/
#define FILE_STANDARD_IMPACT_DATA			"../../server_resources/Public/Config/buff_logic.tab"
#define FILE_IMPACT_DIR						"../../server_resources/Public/Config/buff_effect.tab"
#define FILE_PLAYER_EXP_LEVEL				"../../server_resources/Public/Config/pl_explv.tab"
#define FILE_PLAYER_EXP_INHERENCE			"../../server_resources/Public/Config/pl_exp_inherence.tab"
#define FILE_INHERENCE_LEVEL_AVERAGE		"../../server_resources/Public/Config/inherence_level_average.tab"
#define FILE_MONSTER_ATTREX					"../../server_resources/Public/Config/mon_attr_ex.tab"
#define FILE_BUS_ATTREX						"../../server_resources/Public/Config/bus_attr_ex.tab"
#define FILE_HORSE_ATTR						"../../server_resources/Public/Config/horse_jichu.tab"
#define FILE_HORSE_ITEM						"../../server_resources/Public/Config/horse_daoju.tab"
#define FILE_PET_LEVELUP					"../../server_resources/Public/Config/horse_lvup.tab"
#define FILE_HORSE_ZIZHI					"../../server_resources/Public/Config/horse_zizhi.tab"
#define FILE_HORSE_MIX						"../../server_resources/Public/Config/horse_mix.tab"
#define FILE_HORSE_MIX_SPELL				"../../server_resources/Public/Config/horse_mix_spell.tab"
#define FILE_GROWPOINT						"../../server_resources/Public/Config/grow_point.tab"
#define FILE_GAMEOPEN						"../../server_resources/Config/game_open.tab"
#define FILE_SKILL_TEMPLATE					"../../server_resources/Public/Config/spell_logic.tab"
#define FILE_SKILL_STUDY					"../../server_resources/Public/Config/spell_learn.tab"
#define FILE_SPECIAL_OBJ_DATA				"../../server_resources/Public/Config/sp_obj.tab"
#define FILE_IMPACT_SEDATA					"../../server_resources/Public/Config/buff_describe.tab"
#define FILE_CAMP_AND_STAND					"../../server_resources/Public/Config/camp_stand.tab"
#define FILE_ABILITY						"../../server_resources/Public/Config/ability.tab"
#define FILE_HAIRSTYLE						"../../server_resources/Public/Config/char_hair.tab"
#define FILE_PRESCRIPTION					"../../server_resources/Public/Config/item_mix.tab"
#define FILE_ABILITY_EXP					"../../server_resources/Public/Config/ability_exp.tab"
#define FILE_TITLE_INFO						"../../server_resources/Public/Config/title_info.tab"
#define FILE_TITLE_COMBINATION				"../../server_resources/Public/Config/title_combination.tab"
#define FILE_BEASTIE_ATTR					"../../server_resources/Public/Config/beastie_attr.tab"
#define FILE_VIGOR_DATA						"../../server_resources/Public/Config/pl_energy.tab"
#define FILE_EQUIP_BASE						"../../server_resources/Public/Config/equip_base.tab"
#define FILE_GEM_INFO						"../../server_resources/Public/Config/gem_info.tab"
#define FILE_EUIPHOLE_INFO					"../../server_resources/Public/Config/Equip_HoleReqInfo.tab"
#define FILE_EUIPLEVEUP_INFO				"../../server_resources/Public/Config/Equip_levelup.tab"
#define FILE_EUIPBIND_INFO					"../../server_resources/Public/Config/Equip_bind.tab"
#define FILE_SPECIALREPAIR_INFO				"../../server_resources/Public/Config/Equip_SpecialRepair.tab"
#define FILE_EQUIP_PRODUCT_INFO				"../../server_resources/Public/Config/equip_product_info.tab"
#define FILE_MATERIALLEVEL_INFO				"../../server_resources/Public/Config/MaterialLevel_info.tab"
#define FILE_EXTRABAG_INFO					"../../server_resources/Public/Config/Extra_Bag.tab"
#define FILE_CHAIN_INFO						"../../server_resources/Public/Config/chain_info.tab"
#define FILE_SOUL_INFO						"../../server_resources/Public/Config/soul_info.tab"
#define FILE_CHANGEPAI_INFO					"../../server_resources/Public/Config/ChangePai_info.tab"
#define FILE_PAI_INFO						"../../server_resources/Public/Config/pai_info.tab"
#define FILE_MISCELL_ITEM					"../../server_resources/Public/Config/item_miscellaneous.tab"
#define FILE_QUEST_ITEM						"../../server_resources/Public/Config/item _quest.tab"
#define FILE_ITEM_RULE						"../../server_resources/Public/Config/item_formula.tab"
#define FILE_EQUIP_SET_ATTR					"../../server_resources/Public/Config/equipset_attr.tab"
#define FILE_SHOP							"../../server_resources/Public/Config/shop_tab.tab"
#define FILE_DY_SHOP						"../../server_resources/Public/Config/Dyshop_tab.tab"
#define FILE_GUILDSHOP						"../../server_resources/Public/Config/guildshop_tab.tab"
#define FILE_PLAYER_LEVEL_MONEY				"../../server_resources/Public/Config/lv_maxmoney.tab"
#define FILE_CHAT_CONSUME					"../../server_resources/Public/Config/chat_cfg.tab"
#define FILE_EFFECT_MARRY					"../../server_resources/Public/Config/MarryEffect.tab"
#define FILE_EFFECT_FRIEND					"../../server_resources/Public/Config/FriendEffect.tab"
#define FILE_NPC_QUEST						"../../server_resources/Public/Config/obj_quest.tab"
#define FILE_SCENEMAP_NPC					"../../server_resources/Public/Config/scenemap_npc.tab"
#define FILE_QUEST_LIST						"../../server_resources/Public/Config/quest/Quest_List.tab"
#define FILE_QUEST_LOOTITEM					"../../server_resources/Public/Config/quest/Quest_LootItem.tab"
#define FILE_QUEST_KILLMONSTER				"../../server_resources/Public/Config/quest/Quest_KillMonster.tab"
#define FILE_QUEST_ENTERAREA				"../../server_resources/Public/Config/quest/Quest_EnterArea.tab"
#define FILE_QUEST_DELIVERY					"../../server_resources/Public/Config/quest/Quest_Delivery.tab"
#define FILE_QUEST_USEITEM					"../../server_resources/Public/Config/quest/Quest_UseItem.tab"
#define FILE_QUEST_HUSONG					"../../server_resources/Public/Config/quest/Quest_Husong.tab"
#define FILE_ONRELIVE_COST					"../../server_resources/Public/Config/brith_cost.tab"
#define FILE_DEATH_DEAL						"../../server_resources/Public/Config/death_deal.tab"
#define FILE_MENTAL_GAME_QUESTIONS			"../../server_resources/Public/Config/questions.tab"
#define FILE_DAY_TIPS						"../../server_resources/Public/Config/DayTips.tab"
#define FILE_TOP_LIST						"../../server_resources/Public/Config/TopList.tab"
#define FILE_MAP_INFO_LIST					"../../server_resources/Public/Config/WorldPos.tab"
#define FILE_GUILD_LEVEL					"../../server_resources/Public/Config/guild_level_info.tab"
#define FILE_GUILD_MERIT					"../../server_resources/Public/Config/guild_merit_info.tab"
#define FILE_SCRIPT							"../../server_resources/Public/Data/Script.tab"
#define FILE_SCRIPT_GL						"../../server_resources/Public/Data/ScriptGL.tab"
#define FILE_PATH_GUILD_AUTH_RULER			"../../server_resources/Public/Config/auth_ruler_guild.tab"
#define FILE_PATH_COUNTRY_AUTH_RULER		"../../server_resources/Public/Config/auth_ruler_country.tab"
#define FILE_AWARD_INFO						"../../server_resources/Public/Config/trophy.tab"
#define FILE_WORLD_SHOP_INFO				"../../server_resources/Public/Config/WorldShop.tab"
#define FILE_EQUIP_ACTIVATION_TB			"../../server_resources/Public/Config/equip_activation.tab"
#define FILE_EQUIP_COLORCHANGE_TB			"../../server_resources/Public/Config/Equip_ColorChange.tab"
#define FILE_EQUIP_PURPLEREWORK_TB			"../../server_resources/Public/Config/Equip_PurpleRework.tab"
#define FILE_GEM_REWORK_TB					"../../server_resources/Public/Config/GemRework.tab"
#define FILE_EQUIP_COPY_TB					"../../server_resources/Public/Config/EquipCopy.tab"
#define FILE_EQUIP_RECALL_TB				"../../server_resources/Public/Config/EquipRecall.tab"
#define FILE_TRANSITEM_POS					"../../server_resources/Public/Config/TransItemPos.tab"
#define FILE_EQUIP_WANFA_ENERGYBALL			"../../server_resources/Public/Config/EnergyBall.tab"			//蓝属性吸收玩法中能量球的配置
#define FILE_EQUIP_WANFA_AMULET				"../../server_resources/Public/Config/AmuletInfo.tab"			//蓝属性吸收玩法中护身符的配置
#define FILE_EQUIP_WANFA_ENERGYBALLSYN   "../../server_resources/Public/Config/EnergyBallSyn.tab"		// 蓝属性吸收玩法中护身符补色的配置
#define FILE_EQUIP_PRODUCE					"../../server_resources/Public/Config/EquipProduce.tab"			//打造装备配置
#define FILE_EQUIP_SWITCH					"../../server_resources/Public/Config/EquipSwitch.tab"			//装备转化
#define FILE_CHANGE_PROFESSION_TABLE_NAME   "../../server_resources/Public/Config/ChangeProfession.tab"		// 职业转换表
#define FILE_CHANGE_APPEARANCE_TABLE_NAME   "../../server_resources/Public/Config/change_appearance.tab"		// 更换形象表
#define FILE_GUILD_SKILL_INFO				"../../server_resources/Public/Config/gift_learn.tab"		//帮会技能表
#define FILE_EQUIP_PRODUCE_NEW				"../../server_resources/Public/Config/Equip_Produce_New.tab"		//橙装蓝属性打造的配置
#define FILE_GIFT_BALANCE_INFO_1				"../../server_resources/Public/Config/gift_balance_learn_1.tab"		//天赋平衡 控制技能除外
#define FILE_GIFT_BALANCE_INFO_2				"../../server_resources/Public/Config/gift_balance_learn_2.tab"		//天赋平衡 控制技能
#define FILE_EQUIP_CONST_INFO				"../../server_resources/Public/Config/Equip_Const_Info.tab"		        //星座信息
#define FILE_EQUIP_CONST_ACTIVE_POINT		"../../server_resources/Public/Config/Equip_Const_Active_Point.tab"		//星座部件激活信息
#define FILE_EQUIP_CONST_BIND				"../../server_resources/Public/Config/Equip_Const_Bind.tab"		        //星座铭记信息
#define FILE_EQUIP_HONOR_BIND				"../../server_resources/Public/Config/Equip_Honor_Bind.tab"		        //荣誉铭记信息
#define FILE_ITEM_SPECIAL					"../../server_resources/Public/Config/Item_Special.tab"		   //存放一些玩法的用到的特珠道具
#define FILE_GIFT_ZHUANGONG					"../../server_resources/Public/Config/gift_zhuangong.tab"		//天赋专精 专攻
#define FILE_GIFT_ZHUANFANG					"../../server_resources/Public/Config/gift_zhuanfang.tab"		//天赋专精 专防
#define FILE_GUILD_BUS_SKILL_STUDY_CONSUME	"../../server_resources/Public/Config/Bus_Sill_Study_Consume.tab"		// 帮会BUS技能学习消耗



/************************************************************************/
/* 相关函数宏定义                                                       */
/************************************************************************/
#define _GetFullPath(fullpath, filepath, filename) \
	do \
	{ \
		sprintf(fullpath, "%s%s", (filepath), (filename)); \
	} while(0)
#define GetAIScriptFullPath(fullpath, filename)	_GetFullPath(fullpath, PATH_AI_SCRIPT, (filename))
#define GetMapFullPath(fullpath, filename)		_GetFullPath(fullpath, PATH_SCENE, (filename))
#endif
	