#ifndef __GAMEDEFINE_H__
#define __GAMEDEFINE_H__

/************************************************************************/
/* 常量定义                                                             */
/************************************************************************/
const float	WALLOW_INGAME_NORMAL			= 1.0f;																					//
const float	WALLOW_INGAME_HALFINCOME		= 0.5f;																					//
const float	WALLOW_INGAME_NONE				= 0.0f;																					//
const float	TIRED_INGAME_NORMAL				= 1.0f;																					//
const float	TIRED_INGAME_HALF				= 0.5f;																					//
const float	TIRED_INGAME_QUARTER			= 0.25f;																				//

#define MAX_ITEMCONTAINER_SIZE	185

/************************************************************************/															
/* 字符串定义                                                           */
/************************************************************************/
#define COUNTRY_LOULAN_NAME					("(楼兰)")																				//
#define COUNTRY_LAIYIN_NAME					("(天山)")																				//
#define COUNTRY_KUNLUN_NAME					("(昆仑)")																				//
#define COUNTRY_DUNHUANG_NAME				("(敦煌)")																				//
#define SYSTEM_MAIL							("系统邮件")																			//

/************************************************************************/
/* 无效值定义                                                           */
/************************************************************************/
#define INVALID_COUNTRY						(-1)																					//
#define INVALID_JOB							(-1)																					//
#define INVALID_SEX							(-1)																					//
#define INVALID_GUILD_ID					(-1)																					//
#define INVALID_RESOURCE					(-1)																					//
#define INVALID_RULERID						(-1)																					//
#define INVALID_PRICE						(0)																						//
#define INVALID_ITEM_ID						(0)																						//
#define INVALID_ITEM_POS					(-1)																					//
#define INVALID_TIME						(0xFFFFFFFF)																			//
#define INVALID_PAI_TYPE					(0)																						//
#define INVALID_SOUL_TYPE					(0)																						//
#define INVALID_CAMP						(0xFF)																					//
#define INVALID_TITLE_ID					(255)																					//
#define MASTER_TITLE_INVALID				(0)																						//
#define INVALID_CONSTID						(0)

/************************************************************************/
/* 最大值最小值定义                                                     */
/************************************************************************/
#define MAX_TEAMINFOLIST_NUM				(20)																					//
#define MAX_SERVER							(24)																					//
#define MAX_WORLD							(255)																					//
#define MAX_WORLD_PLAYER						(10000)																					//
#define MAX_CHARACTER_INPUTNAME				(24)																					//
#define MAX_CHARACTER_NUM					(3)																						//

#ifdef __WINDOWS__
#define MAX_POOL_SIZE						(100)																					//
#define MAX_PLAYER							(100)																					//
#else
#ifdef __OS64__
#define MAX_POOL_SIZE						(3000)
#define MAX_PLAYER							(2000)
#else
#define MAX_POOL_SIZE						(1500)
#define MAX_PLAYER							(1500)
#endif
#endif

#define MAX_GUILD_SIZE						(1024)																					//
#define MAX_SYSTEM_MSG_SIZE					(512)																					//
#define MAX_MAILNODE_SIZE					(102400)																				//
#define MAX_USERNODE_SIZE					(20480)																					//
#define MAX_COUNTRY_SIZE					(4)																						//
#define MAX_CHARACTER_NAME					(30)																					//
#define MAX_COUNTRY_COLLECT_DESC			(68)																					//
#define MAX_TOP_LIST_NAME					(32)																					//
#define MAX_GROUP_NAME						(12)																					//
#define MAX_CHARACTER_TITLE					(34)																					//
#define MAX_TITLE_COMBINATION				(10)																					//
#define MAX_NICK_NAME						(34)																					//
#define MAX_SHOP_NAME						(34)																					//
#define MAX_STALL_NAME						(34)																					//
#define MAX_BBS_MESSAGE_NUM					(20)																					//
#define MAX_BBS_MESSAGE_LENGTH				(71)																					//
#define MIN_PWD								(8)																						//
#define MAX_PWD								(20)																					//
#define MAX_ACCOUNT							(30)																					//
#define MAX_PASSWORD						(32)																					//
#define MAX_TOKEN_LEN						(255)																					// 会话最大长度
#define MAX_JOBINFO_LENGTH					(50)																					//
#define MAX_SCHOOLINFO_LENGTH				(50)																					//
#define MAX_PROVINCE_LENGTH					(16)																					//
#define MAX_CITY_LENGTH						(16)																					//
#define MAX_EMAIL_LENGTH					(50)																					//
#define MAX_LUCKWORD_LENGTH					(255)																					//
#define MAX_HOME_PAGE_LENGTH				(127)																					//
#define MAX_MSN_LENGTH						(127)																					//
#define MAX_QQ_LENGTH						(16)																					//
#define MAX_CREATE_PLAYER_NUM				(3)																						//
#define MAX_SEND_TIME						(1)																						//
#define MAX_RADIUS							(2)																						//
#define MAX_REFESH_OBJ_GRID_RADIUS			(2)																						//
#define MAX_REFESH_OBJ_ZONE_ARRAY_SIZE		((MAX_REFESH_OBJ_GRID_RADIUS - 1) * (MAX_REFESH_OBJ_GRID_RADIUS - 1) + 1)				//
#define MAX_BOX_OP_DISTANCE					(3.0f)																					//
#define MAX_LOOT_DISTANCE					(8.f)																					//
#define MAX_BAG_SIZE						(184)																					//
#define MAX_EXT_BAG_NUM						(4)																						//
#define MAX_BASE_BAG_SIZE					(MAX_BAG_SIZE)																			//
#define MAX_BASE_BAG_REAL_SIZE				(MAX_BAG_SIZE - MAX_EXT_BAG_NUM)														//
#define MAX_SINGLEBAG_SIZE					(36)																					//
#define MAX_NPC_DISTANCE					(5.0)																					//
#define MAX_BBS_MESSAGE_AUTHORLENGTH		(40)																					//
#define MAX_DROP_ITEM_OP_DISTANCE			(3.0f)																					//
#define MAX_BANK_MONEY						(10000000)																				//
#define MAX_SHOP_NUM_PER_SCENE				(512)																					//
#define MAX_SHOP_NUM_PER_PLAYER				(2)																						//
#define MAX_FAVORITE_SHOPS					(10)																					//
#define MAX_STALL_NUM_PER_SHOP				(10)																					//
#define MAX_PARTNER_PER_SHOP				(6)																						//
#define MAX_EXCHANGE_RECORD					(40)																					//
#define MAX_MANAGER_RECORD					(128)																					//
#define MAX_RECORD_LEN_ENTRY				(128)																					//
#define MAX_RECORD_NUM_ENTRY				(128)																					//
#define MAX_RECORD_NUM_PER_PAGE				(10)																					//
#define MAX_SHOP_NAME_SIZE					(12)																					//
#define MAX_SHOP_DESC_SIZE					(82)																					//
#define MAX_BANK_SIZE						(108)																					//
#define MAX_BANK_MONEY						(10000000)																				//
#define MAX_EXCHANGE_APPLICANTS_NUM			(10)																					//
#define MAX_STRING_TITLE_SIZE				(4)																						//
#define MAX_DYNAMIC_TITLE_SIZE				(256)																					//
#define MAX_TITLE_SIZE						(256)																					//
#define MASTER_LEVEL_ONE_TITLE_ID			(9)																						//
#define MAX_TITLE_ID_SIZE					(16)																					//
#define MAX_ITEM_GEM						(7)																						//
#define MAX_GEM_HOLE						(7)																						//
#define MAX_ITEM_NATUREATTR					(8)																						//
#define MAX_JOB_SUM							(12)																						//
#define MAX_BASE_ITEM_ATTR					(3)																						//
#define MAX_ITEM_ATTR						(8)																						//
#define MAX_EQUIP_EXT_ATTR					(8)																						//
#define MAX_EQUIP_CONST_ATTR				(2)																						//
#define MAX_EQUIP_CONST_ACTIVE_NEED			(2)																						//
#define MAX_EQUIP_HONOR_BIND_COND			(2)																						//
#define MAX_RAND_LEVEL_NUM					(16)																					//
#define MAX_EQUIP_LEVEL						(160)																					//
#define MAX_COMMON_EQUIP_COUNT				(50)																					//
#define MAX_EQUIP_MODEL						(100)																					//
#define MAX_EQUIP_EFFECT_SKILL				(4)																						//
#define MAX_EQUIP_AFFIX_SKILL				(4)																						//
#define MAX_LEVELUP_GEMREQ_NUM				(6)																						//
#define MAX_EQUIP_LEVELUP_NUM				(15)																					// 装备最多15星
#define MAX_EQUIP_SUIT_LEVELUP_NUM			(5)																						// 时装最多5星
#define MAX_EQUIP_BIND_LEVEL				(1)																						//
#define MAX_EQUIP_HONOR_BIND_LEVEL			(9)																						//
#define MAX_BIND_GEMREQ_NUM					(3)																						//
#define MAX_EQUIP_SUIT_NUM					(10)																					//
#define MAX_EQUIPSUIT_POINT_NUMBER			(16)																					//
#define MAX_VALIDMATERIAL_LEVEL				(15)																					//
#define MAX_MATERIAL_LEVEL					(10)																					//
#define MAX_CREATE_MATERIAL_NUM				(4)																						//
#define MAX_REMOULD_MATERIAL_NUM			(3)																						//
#define MAX_EXTRA_BAG_NUM					(MAX_EXT_BAG_NUM)																		//
#define MAX_BAG_NUM							(MAX_EXTRA_BAG_NUM + 1)																	//
#define MAX_SOUL_EFFECTATT					(4)																						//
#define MAX_CHAIN_NUM						(4)																						//
#define MAX_BASE_EQUIP_COUNT				(EQUIP_TYPE_NUM)																		//
#define MAX_GEM_ATT							(4)																						//
#define MAX_GEM_REQ							(3)																						//
#define MAX_GEM_QUALITY						(9)																						//
#define MAX_ABILITY_ITEM					(5)																						//
#define MAX_ITEM_SET_ATTR					(4)																						//
#define MAX_MEDIC_EFFECT_NUM				(3)																						//
#define MAX_GROW_POINT_RATE_NUM				(4)																						//
#define MAX_LOGIC_FUNC_LEN					(128)																					//
#define MAX_MAP_GATHER_POINT_NUM			(128)																					//
#define MAX_SCENE_GP_OWNER					(255)																					//
#define MAX_PET_SKILL_COUNT					(12)																					//
#define MAX_BOXITEM_NUMBER					(10)																					//
#define MAX_DROP_ITEM_NUMBER				(100)																					//
#define MAX_ITEMBOX_PICK_DIST				(20.0f)																					//
#define MAX_BOOTH_NUMBER					(96)																					//
#define MAX_BOOTH_TAB_NUMBER				(144)																					//
#define MAX_BOOTH_SOLD_NUMBER				(10)																					//
#define MAX_SHOP_ELEMENT_NUMBER				(20)																					//
#define MAX_PLAYER_EXP_LEVEL				(160)																					//
#define MAX_EXP_RATE						(10)																					//
#define MAX_PLAYER_INHERENCE_LEVEL			(420)																					//
#define MAX_INHERENCE_LEVEL_AVERAGE			(100)																					//
#define MAX_HAND_LEVEL						(10)																					//
#define MAX_100_PLUS_DELTA_LEVEL			(201)																					//
#define MAXTYPE_NUMBER						(16384)																					//
#define MAXAI_NUMBER						(256)																					//
#define MAXCHATTYPE_NUMBER					(64)																					//
#define MAXCHAT_NUMBER						(64)																					//
#define MAX_RUNTIME_DATA					(64)																					//
#define MAX_NPC_EVENT						(25)																					//
#define MAX_CHAR_SKILL_NUM					(256)																					//
#define MAX_IMPACT_NUM						(64)																					//
#define MAX_CHAR_TALENT_NUM					(16)																					//
#define MAX_CHAR_ABILITY_NUM				(64)																					//
#define MAX_SKILL_PRESCRIPTION_NUM			(4 * 256)																				//
#define MAX_CHAR_PRESCRIPTION_BYTE			(MAX_SKILL_PRESCRIPTION_NUM >> 3)														//
#define MAX_COUNTRY_NUM						(4)																						//
#define MAX_KINDOM_ACTION_POINT				(10000)																					//
#define MAX_PREFESSION_NUM					(PROFESSION_NUMBER)																		//
#define MAX_PROFESSION_NUM					(PROFESSION_NUMBER)																		//
#define MAX_PROFESSION_TALENT_NUM			(16)																					//
#define MAX_ALL_TALENT_NUM					(55)																					//
#define MAX_TALENT_LEVEL_NUM				(120)																					//
#define MAX_ABILITY_LEVEL_NUM				(60)																					//
#define MAX_SKILL_NUMBER					(1024)																					//
#define MAX_QUEST_NUM						(6400)																					//
#define MAX_CHAR_QUEST_FLAG_LEN				((MAX_QUEST_NUM + 31) / 32)																//
#define MAX_CHAR_QUEST_NUM					(20)																					//
#define MAX_CHAR_SCOUT_QUEST_NUM			(10)																					//
#define MAX_QUEST_NOTIFY_NUM				(4)																						//
#define MAX_CHAR_QUEST_DATA_NUM				(320)																					//
#define MAX_CHAR_CAN_PICK_QUEST_ITEM_NUM	(MAX_CHAR_QUEST_NUM * 4)																//
#define MAX_SKILLOBJ_NUMBER					(1024																					//
#define MAX_OPEN_ITEMBOX_DIST				(2.f)																					//
#define MAX_OPEN_ITEMBOX_DIST_SQ			(MAX_OPEN_ITEMBOX_DIST * MAX_OPEN_ITEMBOX_DIST)											//
#define MAX_CLIENT_DEFAULT_EVENT_DIST		(3.f)																					//
#define MAX_SERVER_DEFAULT_EVENT_DIST		(MAX_CLIENT_DEFAULT_EVENT_DIST * 2.f)													//
#define MAX_CLIENT_DEFAULT_EVENT_DIST_SQ	(MAX_CLIENT_DEFAULT_EVENT_DIST * MAX_CLIENT_DEFAULT_EVENT_DIST)							//
#define MAX_SERVER_DEFAULT_EVENT_DIST_SQ	(MAX_SERVER_DEFAULT_EVENT_DIST * MAX_SERVER_DEFAULT_EVENT_DIST)							//
#define MAX_ATOM_OPT_NUM					(8)																						//
#define MAX_CHAR_PATH_NODE_NUMBER			(16)																					//
#define MAX_SCENE							(4096)																					//
#define MAX_AREA_IN_ZONE					(10)																					//
#define MAX_FUBEN							(128)																					//
#define MAX_TEAM_MEMBER						(6)																						//
#define MAX_TEAMS_IN_GROUP					(8)																						//
#define MAX_TEAMS							(3000)																					//
#define MAX_CHATCHANNEL_MEMBER				(11)																					//
#define MAX_CHANNELS						(3000)																					//
#define MAX_MAIL							(31)																					//
#define MAX_MAIL_CONTEX						(257)																					//
#define MAX_MONSTERSPEAK_CONTENT			(64)																					//
#define MIN_DAMAGE_PERCENT					(0.2f)																					//
#define MAX_GUILD_NAME_SIZE					(24)																					//
#define MAX_GUILD_FAMILY_NAME_SIZE			(24)																					//
#define MAX_GUILD_LEVEL						(10)																					//
#define MAX_GUILD_FAMILY_DESC_SIZE			(60)																					//
#define MAX_GUILD_POS_NAME_SIZE				(24)																					//
#define MAX_GUILD_POS_NUM					(8)																						//
#define MAX_FREEPARAM_NUM					(256)																					//
#define MAX_GUILDMERCH_USEINT				(4)																						//
#define MAX_CITY_NAME_SIZE					(24)																					//
#define MAX_CITY_BUILDING_NUM				(20)																					//
#define MAX_GUILD_DESC_SIZE					(256)																					//
#define GUILD_ACTIVITY_PARAM_COUNT			(8)																					//
#define MAX_GUILD_LIST_COUNT				(10)																					//
#define MAX_PROPOSER_IN_GUILD				(10)																					//
#define MAX_USER_IN_GUILD					(160)																					//
#define MAX_TABLE_DEFINE_LEVEL				(160)																					//
#define MAX_TEMP_FRIEND_SIZE				(10)																					//
#define MAX_BLACK_SIZE						(10)																					//
#define MAX_ENEMY_SIZE						(10)																					//
#define MAX_FRIEND_SIZE						(100)																					//
#define MAX_RELATION_SIZE					(MAX_FRIEND_SIZE + MAX_BLACK_SIZE + MAX_ENEMY_SIZE + MAX_TEMP_FRIEND_SIZE)				//
#define MAX_MOOD_SIZE						(25)																					//
#define MAX_PRENTICE_COUNT					(5)																						//
#define MAX_MONEY_COUNT						(999999999)																				//
#define MAX_SHENGWANG_COUNT					(999999)																				//
#define MAX_HOT_VALUE						(999999)																				//
#define MAX_LEVELMONEY_VALUE				(10000)																					//
#define MAX_PVP2V2_LEVEL					(65535)																					//
#define MAX_PVP2V2_MARK						(65535)																					//
#define MAX_FEAST_SCORE						(131072)																				// 节日积分最大值，MD_SEED_SCORE = {63, 0,17 }
#define MAX_CHAT_SIZE						(512)																					//
#define MAX_ANIMATE_SIZE					(10)																					//
#define MAX_REASON_SIZE						(512)																					//
#define MAX_NOTICE_SIZE						(256)																					//
#define MAX_PK_VALUE						(999)																					//
#define MAX_SCENE_VARIABLE					(64)																					//
#define MAX_TOPLIST_POOL_SIZE				(10240)																					//
#define MAX_FIGHT_INFO_SIZE					(128)																					//
#define MAX_TIMER_DOING_NUM					(512)																					//
#define MAX_TIEMR_PARAM_NUM					(8)																						//
#define MAX_MORAL_POINT						(1000000)																				//
#define MAX_INITSKILL_COUNT					(5)																						// 角色初始技能数
#define MAX_INITABILITY_NUM					(5)																						//
#define MAX_INITITEM_NUM					(5)																						//
#define MAX_INIT_EQUIP						(5)																						//
#define MAX_ITEMLOG_ATTLENGTH				(128)																					//
#define MAX_MAC_ADDRESS						(12)																					//
#define MAX_PW_CARD_X_SIZE					(8)																						//
#define MAX_PW_CARD_Y_SIZE					(10)																					//
#define MAX_PW_CARD_COMPAGES				(3)																						//
#define MAX_PW_CARD_CONTEXT_SIZE			(9)																						//
#define MAX_CL_VERIFY_CODE					(64)																					//
#define MAX_CHAR_MOVE_VERIFY_CODE			(10)																					//
#define MAX_LOCK_TARGET_VERIFY_CODE			(16)																					//
#define MAX_LOCK_HEARTBEAT_VERIFY_CODE		(16)																					//
#define MAX_ENCRYPT_ARITH_NUM				(255)																					//
#define MAX_PWCARD_COORD_SIZE				(32)																					//
#define MAX_RSA_ARITH_NUM					(168)																					//
#define MAX_CLIENT_ERROR_STR_LEN			(256)																					//
#define MAX_CRYPTTABLE_NUM					(0x500)																					//
#define MAX_FILE_PATH						(260)																					//
#define MAX_RELATION_DESC_LEN				(32)																					//
#define MAX_CANDIDATE_SIZE					(1024)																					//
#define MAX_GUILDLAIRD_NUM					(10)																					// 据点帮会最大数量
#define MAX_MONSTER_PET_TAKE				(3)																						//
#define MAX_MENTAL_GROUP_MEMBER_NUM			(6)																						// 智力竞赛每组最大玩家数
#define MAX_MENTAL_GROUP_NUM				(MAX_PLAYER/MAX_MENTAL_GROUP_MEMBER_NUM)												// 智力竞赛最大组数量
#define MAX_MENTAL_SCORE_SEND_PERTICK		(MAX_MENTAL_GROUP_NUM/20)																// 智力竞赛一个Tick发送的数量,默认为1秒种假设为20个TICK,这个实际上是要求在1秒钟内同步完一次数据
#define MAX_UINT32_VALUE                    (0xFFFFFFFF)                                                                            // 32位无符号整数最大值
#define MAX_LAIRBATTLE_PLAYER_AID_NUM		(10)																					// 据点战外援最大数量
#define MAX_LAIRDLEVEL						(5)																						// 据点养成最大级别
#define MAX_TEAMTANK_NUM					(100)																					// 最大团队上限
#define MAX_TEAMTANK_TEAM_NUM				(6)																						// 团队所能容纳的最大队伍个数
#define MAX_GUILD_BUS_SKILL_NUM				(10)

/************************************************************************/
/* 杂项                                                                 */
/************************************************************************/
#define BASE_BAG_POS						(185)																					//
#define TEAM_ENOUNCE_LEN					(25)																					//
#define NPC_NAME_LEN						(32)																					//
#define TOP_USDR_MAX_NUM					(20)																					//
#define GUANZHI_TITLE_ID					(0)																						//
#define BANGPAI_TITLE_ID					(1)																						//
#define JIAZU_TITLE_ID						(2)																						//
#define JIEHUN_TITLE_ID						(3)																						//
#define NPC_TITLE_LEN						(32)																					//
#define SHOP_NAME_LENGTH					(9)																						//
#define DEFAULT_OBJ_COUNT					(1024)																					//
#define ZONE_SIZE							(10)																					//
#define ITEM_DROP_DISTANCE					(0.6F)																					//
#define OPENBOX_CONTAINER_SIZE				(2)																						//
#define TMP_OPENBOX_CONTAINER_SIZE			(20)																					//
#define EXTRA_CONTAINER_OFFSET				(MAX_BAG_SIZE - MAX_EXT_BAG_NUM)														//
#define BASE_CONTAINER_OFFSET				(0)																						//
#define EXTRA_BAG1_OFFSET					(BASE_CONTAINER_OFFSET + MAX_SINGLEBAG_SIZE)											//
#define EXTRA_BAG2_OFFSET					(EXTRA_BAG1_OFFSET + MAX_SINGLEBAG_SIZE)												//
#define EXTRA_BAG3_OFFSET					(EXTRA_BAG2_OFFSET + MAX_SINGLEBAG_SIZE)												//
#define EXTRA_BAG4_OFFSET					(EXTRA_BAG3_OFFSET + MAX_SINGLEBAG_SIZE)												//
#define EXTRA_BAG_OFFSET(x)					(EXTRA_BAG1_OFFSET + (x) * MAX_SINGLEBAG_SIZE )											//
#define EQUIP_CONTAINER_OFFSET				(BASE_CONTAINER_OFFSET + MAX_BAG_SIZE)													//
#define BANK_CONTAINER_OFFSET				(EQUIP_CONTAINER_OFFSET + HEQUIP_NUMBER)												//
#define DB_BAG_POS_START					(0)																						//
#define DB_BAG_POS_END						(MAX_BAG_SIZE)																			//
#define DB_EQUIP_POS_START					(DB_BAG_POS_END)																		//
#define DB_EQUIP_POS_END					(DB_EQUIP_POS_START + HEQUIP_NUMBER)													//
#define DB_BANK_POS_START					(DB_EQUIP_POS_END)																		//
#define DB_BANK_POS_END						(MAX_BANK_SIZE + DB_BANK_POS_START - 1)													//
#define INVALID_BAG_INDEX					(-1)																					//
#define SHOP_TAX							(0.03)																					//
#define CUR_BANK_SIZE						(36)																					//
#define RENTBOX1_START_INDEX				(0)																						//
#define RENTBOX2_START_INDEX				(36)																					//
#define RENTBOX3_START_INDEX				(72)																					//
#define QUEST_BOX_SIZE						(4)																						//
#define QUESTLOG_BOX_SIZE					(255)																					//
#define EXCHANGE_BOX_SIZE					(5)																						//
#define EXCHANGE_PET_BOX_SIZE				(1)																						//
#define EXCHANGE_MAX_DISTANCE				(16)																					//
#define BAITAN_BOX_SIZE						(36)																					//
#define BAITAN_HORSE_BOX_SIZE					(20)																					//
#define TITLE_MARRY							(4)																						//
#define TITLE_PRENTICE						(5)																						//
#define WORLDCUP_CHAMPION					(15)																					// 世界杯冠军，数值定义参考title_info.tab
#define WORLDCUP_RUNNERUP					(16)																					// 世界杯亚军
#define WORLDCUP_THIRD						(17)																					// 世界杯季军
#define UPDATE_TITLE_ADD					(1)																						//
#define UPDATE_TITLE_DEL					(2)																						//
#define UPDATE_TITLE_NO_CHANGE				(3)																						//
#define UPDATE_TITLE_TIME					(4)																						//
#define UPDATE_TITLE_SHOW					(5)																						//
#define UPDATE_TITLE_HIDE					(6)																						//
#define CUR_EQUIP_LEVELUP_NUM				(9)																						//
#define ITEM_SERIAL_KEY						(536081)																				//
#define ITEM_LOGIC_FUNC_LEN					(32)																					//
#define BOOTH_BACK_START_INDEX				(200)																					//
#define TODAY_SHOP_START_INDEX				(1024)																					//
#define DEFAULT_WASHPOINT_LEVEL				(60)																					//
#define TIME_TO_TRUE_QUIT					(10000)																					//
#define BUS_MAX_TYPE_NUMBER					(100)																					//
#define BUS_MAX_MEMBER_NUMBER				(10)																					//
#define DEF_BUS_MAX_PASSENGER_COUNT			(8)																						//
#define ABILITY_GAMBLE_NUM					(5)																						//
#define SCENE_NAME_LEN						(16)																					//
#define USER_FAMILY_SIZE					(25)																					//
#define GUILD_FAMILY_SIZE					(5)																						//
#define SENDMAIL_MIN_LEVEL					(15)																					// 发送和接收邮件的最低等级要求
#define CHATDIAG_MIN_LEVEL					(15)																					// 发送和接收私聊与会话消息的最低等级要求
#define USER_ARRAY_SIZE						(MAX_USER_IN_GUILD + MAX_PROPOSER_IN_GUILD)												//
#define ENEMY_NAME_AND_COLOR				("#cFF0000(仇人)")																		//
#define FIND_RELATION_COUNT					(22)																					//
#define RELATION_FRIEND_OFFSET				(0)																						//
#define RELATION_BLACKNAME_OFFSET			(MAX_FRIEND_SIZE)																		//
#define RELATION_ENEMY_OFFSET				(RELATION_BLACKNAME_OFFSET + MAX_BLACK_SIZE)											//
#define RELATION_TEMP_FRIEND_OFFSET			(RELATION_ENEMY_OFFSET + MAX_ENEMY_SIZE)												//
#define MOOD_DATA_SIZE						(32)																					//
#define BASE_FRIEND_COUNT					(MAX_PRENTICE_COUNT+2)																	//
#define DATABASE_STR_LEN					(128)																					//
#define DB_USE_STR_LEN						(32)																					//
#define DB_PASSWORD_STR_LEN					(32)																					//
#define DB_OPERATION_TIME					(1000)																					//
#define DB_CHAR_NUMBER						(5)																						//
#define DB_2_SM_TIME						(60000)																					//
#define DB_CONNECTION_COUNT					(20)																					//
#define DEF_SERVER_ADJUST_POS_WARP_DIST		(5.f)																					//
#define LOCK_A_OBJ_NEED_ENERGY				(10)																					//
#define DAYTIPS_LIST_MAX					(10)																					//
#define DELATE_GOLD							(600000)																				//
#define KINDOM_GOLD							(1000000)																				//
#define SECS_PER_DAY						(86400)																					//
#define TIMER_DOING_MAP_NUM					(10)																					//
#define TIMER_DOING_MAP_LIST				(36)																					//
#define TIMER_PARAMETER_NUM					(5)																						//
#define SHOPPING_PARAMETER_NUM				(5)																						//
#define BILLING_RET_ITEM_NUM				(5)																						//
#define TOP_SCORE_MAX						(20)																					// 
#define STALL_MIN_DISTANCE					(2)																						//
#define PLAYER_EQUIP_STAR_EFFECT			(4)																						//
#define ENCRYPT_OP_PARAM_NUM				(4)																						//
#define ENCRYPT_OP_FUNCTION_NAME_SIZE		(18)																					//
#define ANSWER_TITLE_NUM					(32)																					//
#define VALID_ENCRYPT_ARITH_NUM				(3)																						//
#define ABS(m)								((m) > 0 ? (m) : (m) * (-1))															//
#define LENGTH(x0, z0, x1, z1)				(ABS((x0) - (x1)) + ABS((z0) - (z1)))													//
#define MAKE_COLOR(r, g, b, a)				(((r & 0xFF) << 24) | ((g & 0xFF) << 16) | ((b & 0xFF) << 8) | (a & 0xFF))				//
#define COLOR_R(color)						((color >> 24) & 0x000000FF)															//
#define COLOR_G(color)						((color >> 16) & 0x000000FF)															//
#define COLOR_B(color)						((color >> 8) & 0x000000FF)																//
#define COLOR_A(color)						((color) & 0x000000FF)																	//
#define FUBEN_TYPE_BIWU						(994)																					//
#define FIGHT_INFO_NUM						(10)																					//
#define EPSINON								(0.00001f)																				//
#define ABILITY_SKILL_MAX_LEVEL				(10)																					//
#define STRING_FILTERED_LEN					(257)																					//
#define SUB_SKILL							(-2)																					//
#define RPT_WATCH_MAX_SIZE					(5)																						//
#define TRANS_POS_MAX_NUM					(5)																						// 传送符可设置的最大传送点数
#define CALL_UP_TEAM_MEMBER_VALID_TIME		(180)																					//
#define AWARD_CD_KEY_LEN					(16)																					//
#define PKMODE_SWITCH_INTERVAL				(1)																						//
#define SECOND_PER_MINUTE					(1)																						//
#define MONSTER_PET_MAX_SKILL				(4)																						//
#define MONSTER_PET_MAX_IMPACT				(8)																						//
#define TIRED_TIEM_NORMAL					(480)																					//
#define TIRED_TIEM_EXTREMITY				(720)																					//
#define CAPTCHA_LEN							(4)		// 图形验证码长度
#define CAPTCHA_FULL_LEN					(32)
#define CAPTCHA_CHECK_COUNT					(3)		// 图形验证校验次数
#define CAPTCHA_STR_RANGE					("2345678abdefhknpqrstuvxyABCDEFGHJKLNPQRSTUVXYZ")										// 字符串取值范围
#define RSA_ARITH_OFFSET					(16)	// 定义在RsaDef.h中

#define MAX_ITEM_STRING_BIN_BUFFER					(192)   //物品信息Binary缓存最大
#define MAX_ITEM_STRING_ASCII_BUFFER					(384)	//物品信息ascii缓存最大 = 物品信息Binary缓存最大 * 2
#define SECONDS_PER_MINUTE                  (60)    // 每分钟60秒
#define PROTECT_HUMANLEVEL					(19)
#define PVP2V2_INIT_LEVEL                   (500)   // 战场等级初始值
#define DAYS_PER_WEEK                       (7)
#define MEDIC_MAX_LEVEL                     (5)    //道具最大的星级
#define MAX_GUILDSKILL_COUNT					(50)																					//帮会天赋修行技能最大值
#define MAX_GUILDSKILL_LEVEL					(20)																					//帮会天赋修行技能最大值
#define TYPE_INHERENCE_FOR_PROFESSION_CHECK						(90)																	//技能职业判断中天赋特定类型
#define MAX_GIFT_BALANCE_COUNT					(50)																					//帮会平衡记录条数最大值（控制技除外）
#define MAX_GIFT_BALANCE_LEVEL					(20)																					//帮会平衡最大级别（控制技除外）
#define MAX_GIFT_BALANCE_COUNT_CTRL					(500)																					//帮会平衡记录条数最大值 控制技能
#define MAX_GIFT_BALANCE_LEVEL_CTRL					(420)																					//帮会平衡最大级别 控制技能
#define MAX_GIFT_ZHANJING_COUNT					(50)																					//专精记录条数最大值
#define MAX_GIFT_ZHANJING_LEVEL					(20)																					//专精最大级别
#define MAX_GIFT_ZHANGONG_COEFFICIENT			(4)																						//专攻单一职业分配系数点数最大值
#define MAX_GIFT_ZHANGONG_COEFFICIENT_TOTAL			(12)																						//分配系数点数总值
#define MAX_GUILD_BUSSKILL_COUNT					(200)			// 帮会神兽技能表最大数量

enum
{
	TYPE_SKILL = 0,
	TYPE_INHERENCE,
	TYPE_BALANCE,
};
#define ORANGE_EQUIP_BLUEATTR_MIN_LEVEL (90)    //橙装蓝属性最小等级
#define EQUIP_BLUEATTR_PRODUCE_RATE_ARRAY_NUMBER (3)  //橙装蓝属性随机概率数个数
#define EQUIP_CONST_BIND_NEED_LEVEL (80)			//星座铭刻需求等级
#define EQUIP_CONST_BIND_NEED_START_LEVEL (10)			//星座铭刻需求星级

#define COMMON_COOLDOWN					(1000)			//技能公共cooldown
#endif
