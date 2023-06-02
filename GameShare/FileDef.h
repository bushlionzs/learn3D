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
#define FILE_BASESERVERCONFIG				"../ServerConfig/BaseServerConfig.ini"
#define FILE_EXTSERVERCONFIG				"../ServerConfig/ExtServerConfig.ini"
#define FILE_MULTIGROUPCONFIG		        "../ServerConfig/MultiGroupConfig.ini"
#define FILE_DBSHARECONFIG					"../ServerConfig/DBShareConfig.ini"
#define FILE_GAMECONFIG						"../ServerConfig/GameConfig.ini"
#define FILE_DBCONFIG 						"../ServerConfig/DBConfig.ini"
#define FILE_SERVERINDEX					"../ServerConfig/ServerIndex.ini"
#define FILE_WORLDINDEX						"../ServerConfig/WorldIndex.ini"
#define FILE_GAMETOGGLE						"../ServerConfig/GameToggleConfig.ini"
#define FILE_LOGSERVERCONFIG				"../ServerConfig/LogServerConfig.ini"

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
#define FILE_PET_CONFIG						"../ServerConfig/HorseConfigTable.ini"
#define FILE_GUILD_MEMBER_ACCESS			"../ServerConfig/GuildMemberAccess.ini"
#define FILE_IPRANGE						"../ServerConfig/IPRange.ini"
#define FILE_BASE_VALUE						"../ServerConfig/BaseValueTable.ini"
#define FILE_ITEM_SERIAL					"../ServerConfig/ItemSerial.ini"
#define FILE_MONITOR_INFO					"../ServerConfig/MonitorInfo.ini"
#define FILE_STOCK_MONITOR_INFO				"../ServerConfig/StockMonitorInfo.ini"

/************************************************************************/
/* 服务器相关内部表格                                                   */
/************************************************************************/
#define FILE_SCENE_INFO						"../ServerConfig/mapdefines.tab"				// 默认的MapServer对应的配置表
#define FILE_SCENE_INFO_6					"../ServerConfig/mapdefines_6.tab"				// 6 MapServer对应的配置表
#define FILE_SCENE_INFO_10					"../ServerConfig/mapdefines_10.tab"			// 10 MapServer对应的配置表
#define FILE_GMLIST							"../ServerConfig/GMList.tab"
#define FILE_NPC_CHAT						"../ServerConfig/npc_speak.tab"
#define FILE_NPCPAOPAOINDEXTBL				"../ServerConfig/npc_pop_index.tab"
#define FILE_PET_ATTRPOINTDISTRIBUTE		"../ServerConfig/horse_sttr_point.tab"
#define FILE_PET_SKILLDISTRIBUTE			"../ServerConfig/horse_skl.tab"
#define FILE_PET_SKILLINDEXTBL				"../ServerConfig/horse_skl_index.tab"
#define FILE_PET_STUDYSKILLTBL				"../ServerConfig/horse_skl_study.tab"
#define FILE_PET_APPERCEIVESKILLTBL			"../ServerConfig/horse_observe_skl.tab"
#define FILE_PET_DOMESTICATION_MONEY		"../ServerConfig/horse_tame_money.tab"
#define FILE_PET_AISTRATEGYTBL				"../ServerConfig/horse_ai.tab"
#define FILE_PET_TRAINCHARGE				"../ServerConfig/HorseTrainCharge.txt"
#define FILE_PET_ATTR						"../ServerConfig/horse_attr.tab"
#define FILE_HORSE_DROP						"../ServerConfig/horse_drop_content.tab"
#define FILE_HORSE_SKILL					"../ServerConfig/horse_skill.tab"
#define FILE_PLANTS							"../ServerConfig/Plants.txt"
#define FILE_ATTR_LEVEL_UP					"../ServerConfig/attr_lvup.tab"
#define FILE_MONSTER_DROP_CONTENT			"../ServerConfig/monsterdrop_content.tab"
#define FILE_DROP_ATTENUATION				"../ServerConfig/drop_fadeout.tab"
#define FILE_DIE_PENALTY					"../ServerConfig/death_penalty.tab"
#define FILE_CHAR_DEFAULT					"../ServerConfig/PlayerTemplte.tab"
#define FILE_MONSTER_SKILL					"../ServerConfig/mon_wqskl.tab"
#define FILE_DROP_POS						"../ServerConfig/dorp_pos.tab"
#define FILE_DUR_SPOIL						"../ServerConfig/DurSpoil.tab"
#define FILE_EQUIP_BLUE_ATTR_SET			"../ServerConfig/equip_blue_attr_set.tab"
#define FILE_EQUIP_BLUE_ATTR_LEVEL			"../ServerConfig/equip_blue_attr_level.tab"
#define FILE_EQUIPEXTRAATT_INFO				"../ServerConfig/EquipExtraAtt_info.tab"
#define FILE_ID_COLLECTION					"../ServerConfig/id_gather.tab"
#define FILE_EQUIPPOINT_INFO				"../ServerConfig/EquipPoint_Value.tab"
#define FILE_FRIEND_GIFT					"../ServerConfig/FriendGift_info.tab"
#define FILE_QUEST_DENGMI_INFO				"../ServerConfig/quest_dengmi.tab"
#define FILE_QUEST_WULONG_INFO				"../ServerConfig/quest_wulong.tab"
#define FILE_STRING_FILTER_TABLE_NAME		"../ServerConfig/str_filter.tab"
#define FILE_TIMER_DOING_LIST				"../ServerConfig/Timer.tab"
#define FILE_TIMER_BATTLE_LIST				"../ServerConfig/GuildBattleTimer.tab"
#define FILE_SCENE_COMMON					"../ServerConfig/map_common.tab"
#define FILE_EQUIP_PURPLEATTR_TB			"../ServerConfig/Equip_PurpleAttr.tab"
#define FILE_ENCRYPT_INFO					"./ServerConfig/encrypt.tab"
#define FILE_LOGIN_ANSWERS_INFO				"../ServerConfig/LoginAnswers.tab"
#define FILE_SCENE_ANSWERS_INFO				"../ServerConfig/SceneAnswers.tab"
#define FILE_MASTER_PRENTICE_TABLE_NAME		"../ServerConfig/master_prentice.tab"
#define FILE_FUBEN_DATA_TABLE_NAME			"../ServerConfig/FubenData.tab"
#define FILE_EQUIP_BLUEATTR					"../ServerConfig/Equip_BlueAttr.tab"			//随机蓝属性
#define FILE_EQUIP_BLUE_INTENSIFY			"../ServerConfig/Equip_BlueIntensify.tab"		//蓝属性强化
#define FILE_CHEAT_ACT_DATA_TABLE_NAME		"../ServerConfig/CheatAct.tab"
#define FILE_WORLD_STOCK_INFO				"../ServerConfig/WorldStock.tab"
#define FILE_PK_POINT						"../ServerConfig/PK_Point.tab"
#define FILE_PK_LEVEL						"../ServerConfig/PK_Level.tab"
#define FILE_PK_PUNISH						"../ServerConfig/PK_Punish.tab"
#define FILE_OPENBOX_ITEM					"../ServerConfig/OpenBoxItem.tab"
#define FILE_ONDIE_MONSTER					"../ServerConfig/OnDie_Monster.tab"
#define FILE_ONDIE_NOPUNISH					"../ServerConfig/OnDie_NoPunish.tab"
#define FILE_ONDIE_DIFFCOUNTRY				"../ServerConfig/OnDie_DiffCountry.tab"
#define FILE_ONDIE_SAMECOUNTRY				"../ServerConfig/OnDie_SameCountry.tab"
#define FILE_ONDIE_SAMECOUNTRY_KILLER		"../ServerConfig/OnDie_Killer.tab"
#define FILE_MENTAL_GAME_ANSWERS			"../ServerConfig/answers.tab"
#define FILE_QUEST_QUIZ_INFO				"../ServerConfig/quest_quiz.tab"
#define FILE_QUEST_SHITU_INFO				"../ServerConfig/quest_shitu.tab"
#define FILE_NEW_EQUIP_BLUEATTR				"../ServerConfig/Equip_BlueAttr_New.tab"    	//橙装随机蓝属性
#define FILE_EQUIP_CONST_ATTR				"../ServerConfig/Equip_Const_Attr.tab"   		//星座装备属性
#define FILE_DYNAMIC_SHOP					"../ServerConfig/dynamic_shop_tab.tab"			// 动态价格商店
#define FILE_RANDOM_MONSTER					"../ServerConfig/random_monster.tab"			// 2010-11-26 by rj 随机怪配置表
/************************************************************************/
/* 客户端服务器端共用内部配置                                           */
/************************************************************************/
#define FILE_MONSTER_BASE_BEHAVIOR			"../Public/Config/monster_base_behavior.ini"

/************************************************************************/
/* 客户端服务器端共用内部表格                                           */
/************************************************************************/
#define FILE_STANDARD_IMPACT_DATA			"../Public/Config/buff_logic.tab"
#define FILE_IMPACT_DIR						"../Public/Config/buff_effect.tab"
#define FILE_PLAYER_EXP_LEVEL				"../Public/Config/pl_explv.tab"
#define FILE_PLAYER_EXP_INHERENCE			"../Public/Config/pl_exp_inherence.tab"
#define FILE_INHERENCE_LEVEL_AVERAGE		"../Public/Config/inherence_level_average.tab"
#define FILE_MONSTER_ATTREX					"../Public/Config/mon_attr_ex.tab"
#define FILE_BUS_ATTREX						"../Public/Config/bus_attr_ex.tab"
#define FILE_HORSE_ATTR						"../Public/Config/horse_jichu.tab"
#define FILE_HORSE_ITEM						"../Public/Config/horse_daoju.tab"
#define FILE_PET_LEVELUP					"../Public/Config/horse_lvup.tab"
#define FILE_HORSE_ZIZHI					"../Public/Config/horse_zizhi.tab"
#define FILE_HORSE_MIX						"../Public/Config/horse_mix.tab"
#define FILE_HORSE_MIX_SPELL				"../Public/Config/horse_mix_spell.tab"
#define FILE_GROWPOINT						"../Public/Config/grow_point.tab"
#define FILE_GAMEOPEN						"../Server/Config/game_open.tab"
#define FILE_SKILL_TEMPLATE					"../Public/Config/spell_logic.tab"
#define FILE_SKILL_STUDY					"../Public/Config/spell_learn.tab"
#define FILE_SPECIAL_OBJ_DATA				"../Public/Config/sp_obj.tab"
#define FILE_IMPACT_SEDATA					"../Public/Config/buff_describe.tab"
#define FILE_CAMP_AND_STAND					"../Public/Config/camp_stand.tab"
#define FILE_ABILITY						"../Public/Config/ability.tab"
#define FILE_HAIRSTYLE						"../Public/Config/char_hair.tab"
#define FILE_PRESCRIPTION					"../Public/Config/item_mix.tab"
#define FILE_ABILITY_EXP					"../Public/Config/ability_exp.tab"
#define FILE_TITLE_INFO						"../Public/Config/title_info.tab"
#define FILE_TITLE_COMBINATION				"../Public/Config/title_combination.tab"
#define FILE_BEASTIE_ATTR					"../Public/Config/beastie_attr.tab"
#define FILE_VIGOR_DATA						"../Public/Config/pl_energy.tab"
#define FILE_EQUIP_BASE						"../Public/Config/equip_base.tab"
#define FILE_GEM_INFO						"../Public/Config/gem_info.tab"
#define FILE_EUIPHOLE_INFO					"../Public/Config/Equip_HoleReqInfo.tab"
#define FILE_EUIPLEVEUP_INFO				"../Public/Config/Equip_levelup.tab"
#define FILE_EUIPBIND_INFO					"../Public/Config/Equip_bind.tab"
#define FILE_SPECIALREPAIR_INFO				"../Public/Config/Equip_SpecialRepair.tab"
#define FILE_EQUIP_PRODUCT_INFO					"../Public/Config/equip_product_info.tab"
#define FILE_MATERIALLEVEL_INFO				"../Public/Config/MaterialLevel_info.tab"
#define FILE_EXTRABAG_INFO					"../Public/Config/Extra_Bag.tab"
#define FILE_CHAIN_INFO						"../Public/Config/chain_info.tab"
#define FILE_SOUL_INFO						"../Public/Config/soul_info.tab"
#define FILE_CHANGEPAI_INFO					"../Public/Config/ChangePai_info.tab"
#define FILE_PAI_INFO						"../Public/Config/pai_info.tab"
#define FILE_MISCELL_ITEM					"../Public/Config/item_miscellaneous.tab"
#define FILE_QUEST_ITEM						"../Public/Config/item _quest.tab"
#define FILE_ITEM_RULE						"../Public/Config/item_formula.tab"
#define FILE_EQUIP_SET_ATTR					"../Public/Config/equipset_attr.tab"
#define FILE_SHOP							"../Public/Config/shop_tab.tab"
#define FILE_DY_SHOP						"../Public/Config/Dyshop_tab.tab"
#define FILE_GUILDSHOP						"../Public/Config/guildshop_tab.tab"
#define FILE_PLAYER_LEVEL_MONEY				"../Public/Config/lv_maxmoney.tab"
#define FILE_CHAT_CONSUME					"../Public/Config/chat_cfg.tab"
#define FILE_EFFECT_MARRY					"../Public/Config/MarryEffect.tab"
#define FILE_EFFECT_FRIEND					"../Public/Config/FriendEffect.tab"
#define FILE_NPC_QUEST						"../Public/Config/obj_quest.tab"
#define FILE_SCENEMAP_NPC					"../Public/Config/scenemap_npc.tab"
#define FILE_QUEST_LIST						"../Public/Config/quest/Quest_List.tab"
#define FILE_QUEST_LOOTITEM					"../Public/Config/quest/Quest_LootItem.tab"
#define FILE_QUEST_KILLMONSTER				"../Public/Config/quest/Quest_KillMonster.tab"
#define FILE_QUEST_ENTERAREA				"../Public/Config/quest/Quest_EnterArea.tab"
#define FILE_QUEST_DELIVERY					"../Public/Config/quest/Quest_Delivery.tab"
#define FILE_QUEST_USEITEM					"../Public/Config/quest/Quest_UseItem.tab"
#define FILE_QUEST_HUSONG					"../Public/Config/quest/Quest_Husong.tab"
#define FILE_ONRELIVE_COST					"../Public/Config/brith_cost.tab"
#define FILE_DEATH_DEAL						"../Public/Config/death_deal.tab"
#define FILE_MENTAL_GAME_QUESTIONS			"../Public/Config/questions.tab"
#define FILE_DAY_TIPS						"../Public/Config/DayTips.tab"
#define FILE_TOP_LIST						"../Public/Config/TopList.tab"
#define FILE_MAP_INFO_LIST					"../Public/Config/WorldPos.tab"
#define FILE_GUILD_LEVEL					"../Public/Config/guild_level_info.tab"
#define FILE_GUILD_MERIT					"../Public/Config/guild_merit_info.tab"
#define FILE_SCRIPT							"../Public/Data/Script.tab"
#define FILE_SCRIPT_GL						"../Public/Data/ScriptGL.tab"
#define FILE_PATH_GUILD_AUTH_RULER			"../Public/Config/auth_ruler_guild.tab"
#define FILE_PATH_COUNTRY_AUTH_RULER		"../Public/Config/auth_ruler_country.tab"
#define FILE_AWARD_INFO						"../Public/Config/trophy.tab"
#define FILE_WORLD_SHOP_INFO				"../Public/Config/WorldShop.tab"
#define FILE_EQUIP_ACTIVATION_TB			"../Public/Config/equip_activation.tab"
#define FILE_EQUIP_COLORCHANGE_TB			"../Public/Config/Equip_ColorChange.tab"
#define FILE_EQUIP_PURPLEREWORK_TB			"../Public/Config/Equip_PurpleRework.tab"
#define FILE_GEM_REWORK_TB					"../Public/Config/GemRework.tab"
#define FILE_EQUIP_COPY_TB					"../Public/Config/EquipCopy.tab"
#define FILE_EQUIP_RECALL_TB				"../Public/Config/EquipRecall.tab"
#define FILE_TRANSITEM_POS					"../Public/Config/TransItemPos.tab"
#define FILE_EQUIP_WANFA_ENERGYBALL			"../Public/Config/EnergyBall.tab"			//蓝属性吸收玩法中能量球的配置
#define FILE_EQUIP_WANFA_AMULET				"../Public/Config/AmuletInfo.tab"			//蓝属性吸收玩法中护身符的配置
#define FILE_EQUIP_WANFA_ENERGYBALLSYN   "../Public/Config/EnergyBallSyn.tab"		// 蓝属性吸收玩法中护身符补色的配置
#define FILE_EQUIP_PRODUCE					"../Public/Config/EquipProduce.tab"			//打造装备配置
#define FILE_EQUIP_SWITCH					"../Public/Config/EquipSwitch.tab"			//装备转化
#define FILE_CHANGE_PROFESSION_TABLE_NAME   "../Public/Config/ChangeProfession.tab"		// 职业转换表
#define FILE_CHANGE_APPEARANCE_TABLE_NAME   "../Public/Config/change_appearance.tab"		// 更换形象表
#define FILE_GUILD_SKILL_INFO				"../Public/Config/gift_learn.tab"		//帮会技能表
#define FILE_EQUIP_PRODUCE_NEW				"../Public/Config/Equip_Produce_New.tab"		//橙装蓝属性打造的配置
#define FILE_GIFT_BALANCE_INFO_1				"../Public/Config/gift_balance_learn_1.tab"		//天赋平衡 控制技能除外
#define FILE_GIFT_BALANCE_INFO_2				"../Public/Config/gift_balance_learn_2.tab"		//天赋平衡 控制技能
#define FILE_EQUIP_CONST_INFO				"../Public/Config/Equip_Const_Info.tab"		        //星座信息
#define FILE_EQUIP_CONST_ACTIVE_POINT		"../Public/Config/Equip_Const_Active_Point.tab"		//星座部件激活信息
#define FILE_EQUIP_CONST_BIND				"../Public/Config/Equip_Const_Bind.tab"		        //星座铭记信息
#define FILE_EQUIP_HONOR_BIND				"../Public/Config/Equip_Honor_Bind.tab"		        //荣誉铭记信息
#define FILE_ITEM_SPECIAL					"../Public/Config/Item_Special.tab"		   //存放一些玩法的用到的特珠道具
#define FILE_GIFT_ZHUANGONG					"../Public/Config/gift_zhuangong.tab"		//天赋专精 专攻
#define FILE_GIFT_ZHUANFANG					"../Public/Config/gift_zhuanfang.tab"		//天赋专精 专防
#define FILE_GUILD_BUS_SKILL_STUDY_CONSUME	"../Public/Config/Bus_Sill_Study_Consume.tab"		// 帮会BUS技能学习消耗



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
	