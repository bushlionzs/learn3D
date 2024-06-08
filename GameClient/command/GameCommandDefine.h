/*$T Client/Game/Command/GameCommandDefine.h GC 1.140 08/23/09 04:52:40 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


/*
 * ;
 * ��Ϸ����ϵͳ ;
 * ;
 * ;
 * ������ Nick 080314 ��lua�ű����͵���Ϣ��ö�ٶ��壬
 * lua�ű�ʹ������ö��ֵ��Ӧ��������
 * ���������ö��ֵһ��Ҫ�ӵ�����Ա���lua�ű���Ϣ���� Nick 080327
 * �����ڽű���AddCommand����GAME_COMMAND_ID��Ӧ���ַ����Ĺ��ܡ�
 * ���Ը�ö�ٿ���������ˡ�
 */
#ifndef _GAME_COMMAND_DEFINE_H_
#define _GAME_COMMAND_DEFINE_H_
enum GAME_COMMAND_ID
{
	/* ��Ϸͨ�ò��� */
	GCD_APPLICATION_INITED,						/* ��Ϸ�����ʼ�� */

	/* ���� */
	GCD_ON_SCENE_TRANS,							/* ����ת�� */
	GCD_SCENE_TRANSED,							/* ����ת�ƺ� */

	/* arg0- С��ͼ������ */
	GCD_SCENE_TELEPORT,							/* ͬ�����ڵ��л� */

	/*
	 * GCD_ON_SCENE_UPDATED, // ��������(һ��������ҳ���) ;
	 * // arg0- С��ͼ������
	 */
	GCD_SCENE_NAME_TIP,							/* �任��������ʾ������ */

	GCD_ON_SERVER_TRANS,						/* ������ת�� */

	GCD_PLAYER_ENTER_WORLD,						/* �������� */
	GCD_PLAYER_LEAVE_WORLD,						/* �˳����� */

	GCD_TEAM_CHANG_WORLD,						/* ���Ѹı䳡���� */
	GCD_SKILL_CHANGED,							/* ��ҵ�ĳ��ܷ����ı�, */

	/* arg0 - ����id */
	GCD_PACKAGE_ITEM_CHANGED,					/* �����е�ĳ����Ʒ�����ı� */

	/* arg0 - ��Ʒ�ڰ����еı�� */
	GCD_MAINTARGET_CHANGED,						/* ��ѡ�������� */

	/* arg0 - ����ServerId */
	GCD_MAINTARGET_OPEND,						/* ��target ����ѡ���Ƕ��ѵ������ �򿪴��� */
	GCD_MAINTARGET_BUFF_REFRESH,				/* ˢ����Ŀ��buff */
	GCD_UPDATE_TARGET2,							/* ˢ����Ŀ���Ŀ�� */

	GCD_TOGLE_SKILL_BOOK,						/* ��/�رռ����� */
	GCD_CLOSE_SKILL_BOOK,						/* �رռ����� */

	GCD_TOGLE_PET_PAGE,							/* �򿪳������ */
	GCD_TOGLE_LIFE_PAGE,						/* ������ܽ��� */
	GCD_TOGLE_COMMONSKILL_PAGE,					/* ����ͨ���ܽ��� */
	GCD_SKILL_UPDATE,							/* ��Ҽ������ݷ����ı� */

	GCD_TOGLE_CONTAINER,						/* ��/�رհ��� */

	/* ��ö�ٵ�λ�ò��ܱ任���ű���ʹ�� 22 */
	GCD_TIME_ENENT,								/* ʱ���¼� */

	/* ��ɫ���� */
	GCD_UNIT_HP,								/* ĳ����Ԫ��HP�����仯 */

	/*
	 * arg0 - ��Ԫ���� ;
	 * "player" - ����Լ� ;
	 * "target" - ��Ŀ�� ;
	 * "pet" - �Լ��ĳ��� ;
	 * "party*" - ����(1-4) ;
	 * "partypet*" - ���ѵĳ���(1-4) ;
	 * ..
	 */
	GCD_UNIT_MP,								/* ĳ����Ԫ��MANA�����仯 */

	/* arg0 - ��Ԫ����(ͬ��) */
	GCD_UNIT_RAGE,								/* ĳ����Ԫ��ŭ�������仯 */

	/* arg0 - ��Ԫ����(ͬ��) */
	GCD_UNIT_MAX_RAGE,							/* ���ŭ�� */

	GCD_UNIT_RAGE_RESPEED,						/* ŭ���ָ��ٶ� */

	/*
	 * GCD_UNIT_TALENT, //ĳ����Ԫ���츳�ȼ������仯 ;
	 * arg0 - ��Ԫ����(ͬ��) ;
	 * arg1 - �츳����
	 */
	GCD_UNIT_EXP,								/* ĳ����Ԫ�ľ���ֵ�����仯 */

	/* arg0 - ��Ԫ����(ͬ��) */
	GCD_UNIT_MONEY,								/* ĳ����Ԫ��Ǯ�����仯 */

	/* arg0 - ��Ԫ����(ͬ��) */
	GCD_UNIT_RACE_ID,							/* ���ݱ��е�ID */
	GCD_UNIT_NAME,								/* ��ɫ�����֣��ӷ��������� */
	GCD_UNIT_CAMP_ID,							/* ��ӪID */
	GCD_UNIT_LEVEL,								/* �ȼ� */
	GCD_UNIT_MOVE_SPEED,						/* �ƶ����ٶ� */
	GCD_UNIT_FIGHT_STATE,						/* ս��״̬ */
	GCD_UNIT_MAX_EXP,							/* ���EXP */
	GCD_UNIT_TITLE,								/* �ƺ� */
	GCD_UNIT_STRIKEPOINT,						/* ������ */
	GCD_UNIT_RELATIVE,							/* �������� */

	/* һ��ս������ */
	GCD_UNIT_STR,								/* �⹦ */
	GCD_UNIT_SPR,								/* �ڹ� */
	GCD_UNIT_CON,								/* �� */
	GCD_UNIT_INT,								/* ���� */
	GCD_UNIT_DEX,								/* �ǻ� */
	GCD_UNIT_POINT_REMAIN,						/* ʣ���������� */

	/* ����ս������ */
	GCD_UNIT_ATT_NEAR,							/* ���� */
	GCD_UNIT_DEF_NEAR,							/* ���� */
	GCD_UNIT_ATT_FAR,							/* Զ�� */
	GCD_UNIT_DEF_FAR,							/* Զ�� */

	/* GCD_UNIT_ATT_PHYSICS, // �������� */
	GCD_UNIT_ATT_MAGIC,							/* ħ�������� */

	/* GCD_UNIT_DEF_PHYSICS, // ��������� */
	GCD_UNIT_DEF_MAGIC,							/* ħ�������� */
	GCD_UNIT_MAX_HP,							/* ��������� */
	GCD_UNIT_MAX_MP,							/* ���ħ���� */
	GCD_UNIT_HP_RE_SPEED,						/* HP�ָ��ٶ� ��/�� */
	GCD_UNIT_MP_RE_SPEED,						/* MP�ָ��ٶ� ��/�� */
	GCD_UNIT_TOUGHNESS,							/* ���� */
	GCD_UNIT_HIT,								/* ������ */
	GCD_UNIT_MISS,								/* ������ */
	GCD_UNIT_CRIT_RATE,							/* ������ */
	GCD_UNIT_CRIT_HURT,							/* �����˺� */
	GCD_UNIT_ATT_SPEED,							/* �����ٶ� */
	GCD_UNIT_ATT_COLD,							/* ������ */
	GCD_UNIT_DEF_COLD,							/* ������ */
	GCD_UNIT_ATT_FIRE,							/* �𹥻� */
	GCD_UNIT_DEF_FIRE,							/* ����� */
	GCD_UNIT_ATT_LIGHT,							/* �繥�� */
	GCD_UNIT_DEF_LIGHT,							/* ����� */
	GCD_UNIT_ATT_POSION,						/* ������ */
	GCD_UNIT_DEF_POSION,						/* ������ */
	GCD_UNIT_VIGOR,								/* ����ֵ */
	GCD_UNIT_MAX_VIGOR,							/* ����ֵ���� */
	GCD_UNIT_REGENE_VIGOR,						/* �����ظ��ٶ� */
	GCD_UNIT_ENERGY,							/* ����ֵ */
	GCD_UNIT_MAX_ENERGY,						/* ����ֵ���� */
	GCD_UNIT_HOT,								/* ���� */
	GCD_UNIT_INHERENCE,							/* �츳 */
	GCD_UNIT_PVP2V2_LEVEL,						/* ���������� */
	GCD_UNIT_PVP2V2_MARK,						/* ���������� */
    GCD_UNIT_FEAST_SCORE,                       /* ���ջ��� */

	GCD_UNIT_NEARATT_REDUCE,					/* ���̼��� */
	GCD_UNIT_FARATT_REDUCE,						/* Զ�̼��� */
	GCD_UNIT_MAGICATT_REDUCE,					/* ħ������ */

	GCD_UNIT_DREAD_RESIST,						/* �־忹�� */
	GCD_UNIT_COMA_RESIST,						/* ���Կ��� */
	GCD_UNIT_HUSH_RESIST,						/* ��Ĭ���� */
	GCD_UNIT_UNARM_RESIST,						/* ��е���� */
	GCD_UNIT_ATTACKSPEED_RESIST,				/* �����ٿ��� */
	GCD_UNIT_SKILLSPEED_RESIST,					/* ��ʩ�ٿ��� */
	GCD_UNIT_MOVEREDUCE_RESIST,					/* �����ٿ��� */

	GCD_UNIT_MENPAI,							/* ְҵ�� */
	GCD_UNIT_HAIR_MESH,							/* -> TABLE_CHARACTER_HAIR_GEO */
	GCD_UNIT_HAIR_COLOR,						/* ͷ����ɫ */
	GCD_UNIT_FACE_MESH,							/* -> TABLE_CHARACTER_HEAD_GEO char_head.tab */
	GCD_UNIT_FACE_IMAGE,						/* ͷ����Ϣ�ı� */
	GCD_UNIT_EQUIP_VER,							/* ��ɫ��װ��״̬�汾�ţ����ںͷ�����ͬ�����ݵ����� */
	GCD_UNIT_EQUIP,								/* װ����(������) */
	GCD_UNIT_EQUIP_WEAPON,						/* ���� */
	GCD_UNIT_Honor_FIRE,
	GCD_UNIT_CTShengWang_FIRE,
	GCD_UNIT_JHShengWang_FIRE,
	GCD_SHOW_CONTEXMENU,						/* ��ʾ�Ҽ��˵� */

	/*
	 * arg0 - �˵��� ;
	 * "player" - ����Լ� ;
	 * "other_player" - ������� ;
	 * "npc" - npc ;
	 * arg1 - ���λ��_x ;
	 * arg2 - ���λ��_y
	 */
	GCD_TOGLE_COMPOSE_WINDOW,					/* �򿪹رպϳɽ��� */

	GCD_TOGLE_CONSOLE,							/* ��ʾ����̨ */

	GCD_ON_SKILL_ACTIVE,						/* ĳ�����ܿ�ʼʹ�� */

	/* arg0 - ����ID */
	GCD_POSITION_MODIFY,						/* �����λ�øı��� */

	GCD_CHAT_MESSAGE,							/* �õ�������Ϣ */

	/*
	 * | arg0 - �������� | "here" - ������� | "scene" - ���� | "sys" - ϵͳ | "team"
	 * - ���� | "guild" - ��� | "user" - �Խ� | "private" - ˽�� | | arg1
	 * ˵���ߵ����� | | arg2 - ˵������ |
	 */
	GCD_CHAT_MESSAGE2,							/* ��Ϣ���� [ ZG 2008-6-6 ] */
	GCD_CHAT_CHANNEL_CHANGED,					/* ����Ƶ�������ı� */
	GCD_CHAT_CHANGE_PRIVATENAME,				/* �޸������е�������� */
	GCD_CHAT_ITEMLINK,							/* ��������Ʒ���� */
	GCD_CHAT_QUESTLINK,						/* �������������� */
	GCD_CHAT_HORSELINK,							/* �������������� */
	GCD_CHAT_SKILLLINK,							/* �������������� */
	GCD_CHAT_TAB_CREATE,						/* ��������ҳ�� */
	GCD_CHAT_TAB_CREATE_FINISH,					/* ��������ҳ����� */
	GCD_CHAT_TAB_CONFIG,						/* ��������ҳ�� */
	GCD_CHAT_TAB_CONFIG_FINISH,					/* ��������ҳ����� */
	GCD_CHAT_FACEMOTION_SELECT,					/* �������ѡ�� */
	GCD_CHAT_TEXTCOLOR_SELECT,					/* ����������ɫѡ�� */
	GCD_SHOW_CHATCOLOR_SELECT,					/* ����������ɫѡ����� */
	GCD_CHAT_CONTEX_MENU,						/* ������صĿ�ݲ˵� */
	GCD_CHAT_ACTSET,							/* ���춯������ */
	GCD_CHAT_ACTSETNEW,							/* ���춯�������� */
	GCD_CHAT_ACT_SELECT,						/* ���춯�����������ʾ */
	GCD_CHAT_ACT_HIDE,							/* ���춯���������رգ���Ϊ�����������Ƚ����⣬��Ҫ֧����ק�� */
	GCD_CHAT_PINGBI_LIST,						/* �������ν��� */
	GCD_CHAT_PINGBI_UPDATE,						/* �����б���� */
	GCD_CHAT_ADJUST_MOVE_CTL,					/* ֪ͨ���촰�ڵ�����С */
	GCD_CHAT_INPUTLANGUAGE_CHANGE,				/* ���뷨��� */
	GCD_CHAT_SHOWUSERINFO,						/* ����鿴�����Ϣ���� */
	GCD_CHAT_LOAD_TAB_CONFIG,					/* ����ҳ��������Ϣ */
	GCD_CHAT_INPUT_STATE,						/* ��������״̬ */
	GCD_CHAT_SHOW_CHATFILTERUI,					/* ���˽��� */
	GCD_CHAT_PopChatEditBox,					/* ������������� */
	GCD_CHAT_COPYTEXT,
	GCD_CHAT_PASTETXT,
	GCD_CHAT_RAPID_REPLY,						/* !< ���ٻظ��¼� */
	GCD_CHAT_RAPID_PERSONAL,					/* !< ����˽�ġ� */
	GCD_CHAT_CLEAR,								/* !< ��������¼�� */

	GCD_ACCELERATE_KEYSEND,						/* ���̿�ݼ����� */

	GCD_UI_SHOWHIDE,							/* ��ʾ/���������� */

	GCD_LOOT_OPENED,							/* ���Ӵ� */
	GCD_LOOT_SLOT_CLEARED,						/* �����е�ĳ��λ����� */

	/* arg0 - �����е�λ�� */
	GCD_LOOT_CLOSED,							/* ���ӹر� */

	GCD_PROGRESSBAR_SHOW,						/* ��������ʾ */
	GCD_PROGRESSBAR_HIDE,						/* ���������� */
	GCD_PROGRESSBAR_WIDTH,						/* ��������ȵ��� */

	/* arg0 - �������İٷֱ� 1 < x < 100 */
	GCD_CHANGE_BAR,								/* �ı乤�����ϵ�Action */

	/*
	 * arg0 - Bar���� ;
	 * arg1 - Index ;
	 * arg2 - ActionItem ID
	 */
	GCD_UPDATE_BAR,								/* ˢ�¿�����ϵ�Action״̬ */

	GCD_TOGLE_QUEST,							/* ����������� */
	GCD_UPDATE_QUEST,							/* ˢ�������б� */
	GCD_REPLY_QUEST,							/* �ύ������� */
	GCD_UPDATE_REPLY_QUEST,					/* ˢ���ύ������� */
	GCD_UPDATE_TIME_QUEST,					/* ˢ�������е�ʱ�䵹��ʱ */
	GCD_UPDATE_TIME_QUEST_SET_QUEST_NAME,	/* ���õ���ʱ��������� */
	GCD_UPDATE_TIME_QUEST_SET_TOTAL_TIME,		/* ���õ���ʱ�������ʱ�䳤�� */
	GCD_UPDATE_TIME_QUEST_SET_EVENT_TIME,		/* ���õ���ʱ�����¼�����ʱ�� */

	GCD_TOGLE_LARGEMAP,								/* �رմ򿪴��ͼ */
	GCD_TOGLE_SCENEMAP,								/* �رմ򿪴��ͼ */
	GCD_OPEN_MINIMAP,								/* ��С��ͼ */
	GCD_OPEN_MINIMAPEXP,							/* ����չС��ͼ */
	GCD_AUTO_FIND_PATH,
	GCD_SHOW_MINIMAP_BUTTON,						/* ��ʾ/����С��ͼ */

	GCD_QUEST_EVENTLIST,							/* �򿪺�npc��һ�ζԻ�ʱ�Ŀ�ִ�нű��б� */
	GCD_QUEST_INFO,									/* �򿪺�npc�ڶ��ζԻ�(�ڽ�����ʱ��������������Ϣ���ȴ�����) */
	GCD_QUEST_REGIE,								/* �������� */
	GCD_QUEST_CONTINUE_DONE,						/* ����������ٴκ�npc�Ի������õ�������������Ϣ��(�������) */
	GCD_QUEST_CONTINUE_NOTDONE,						/* ����������ٴκ�npc�Ի������õ�������������Ϣ��(����δ���) */
	GCD_QUEST_AFTER_CONTINUE,						/* ���������֮�󡱣���Ʒѡ����� */
	GCD_QUEST_TIPS,									/* ��Ϸ�����е������չ��ʾ��Ϣ */
	GCD_QUEST_INPUT_PASSWD_COMMAND,					/* ͨ�������������Ʒ���� */
	GCD_QUESTLOG_AUTO_FIND_PATH,					/* �Զ�Ѱ·����NPC�Ի� */
	GCD_EVENTLIST_HIDE,								/* �뿪̽�������ر�EventList */

	GCD_TOGLE_COMPOSEITEM,							/* ��/�ر� �ϳɽ��� */

	/* arg0 - ����ܵ����� */
	GCD_TOGLE_COMPOSEGEM,							/* ��/�ر� ��ʯ�ϳɽ��� */
	GCD_ON_LIFEABILITY_ACTIVE,						/* ĳ������ܿ�ʼʹ�� */

	/*
	 * arg0 - ����ID ;
	 * arg1 - �䷽ ;
	 * arg2 - ƽ?
	 */
	GCD_NEW_DEBUGMESSAGE,							/* �µ�debug string����������Ļ����listbox��ʾ�� */
	GCD_QUICK_CHANGE_EQUIP,						/* �򿪹ر�һ����װ���� */
	GCD_UPDATE_QUICK_CHANGE,						/* ����һ����װ���� */
	GCD_QUICK_CHANGE_SUCCESS,						/* һ����װ�ɹ� */
	GCD_QUICK_UPDATE_FRAME,							/* ������Ʒʱ���������һ����װ���棬���´˽��� */

	/* �������Խ��� */
	GCD_UPDATE_EQUIP,								/* ����װ�� */
	GCD_OPEN_BOOTH,									/* �򿪻����� */
	GCD_CLOSE_BOOTH,								/* �رջ����� */
	GCD_MANUAL_ATTR_SUCCESS_EQUIP,					/* �ֶ��������Գɹ�. */
	GCD_CUR_TITLE_CHANGEED,							/* ��ǰ����ĳƺŸı���. */

	GCD_UPDATE_BOOTH,								/* ���ܸ��� */

	GCD_OPEN_CHARACTOR,								/* ������������ */
	GCD_OPEN_EQUIP,									/* ��װ���� */
	GCD_TOGLE_JOINSCHOOL,							/* �򿪼���ְҵ�ĶԻ��� */

	/* Nick 2007.11.22 */
	GCD_OPEN_MAIN_FUNC_BTN,							/* �����ܰ�ť�����ڴ�8�������ܰ�ť */

	GCD_OPEN_ADD_HOLE,								/* �򿪴�׽��� */
	GCD_UPDATE_ADD_HOLE,							/* ���´�׽��� */
	GCD_ADD_HOLE_SUCCESS,							/* �ɹ���� */

	GCD_OPEN_BANG_DING,								/* �򿪰󶨽��� */
	GCD_UPDATE_BANG_DING,							/* ���°󶨽��� */
	GCD_ADD_BANG_DING_SUCCESS,						/* �󶨳ɹ� */

	GCD_OPEN_DA_XING,								/* �򿪴��ǽ��� */
	GCD_UPDATE_DA_XING,								/* ���´��ǽ��� */
	GCD_OPEN_DA_XING_SUCCESS,						/* ���ǳɹ� */

	GCD_OPEN_RING_FUSION,							/* �򿪽�ָ�������� */
	GCD_UPDATE_RING_FUSION,							/* ���½�ָ�������� */
	GCD_OPEN_STARS_FUSION,							/* ���ǳ���������*/

	GCD_OPEN_SP_REPAIR,								/* �����޽��� */
	GCD_UPDATE_SP_REPAIR,							/* �������޽��� */
	GCD_OPEN_SP_REPAIR_SUCCESS,						/* ���޳ɹ� */
	GCD_OPEN_REPAIR_SURE,							/* ��������������ʾ�Ի��� */

	GCD_OPEN_SYNTHESIZE,							/* �򿪺ϳ������Ի��� */
	GCD_CLOSE_SYNTHESIZE,							/* �رպϳ������Ի��� */

	GCD_OPEN_EQUIP_REWORK,							/* �򿪸���Ի��� */

	GCD_CLOSE_EQUIP_REWORK,							/* �رո���Ի��� */

	GCD_OPEN_EQUIP_DISASS,							/* �򿪲��װ���Ի��� */
	GCD_UPDATE_EQUIP_DISASS,						/* ���� */
	GCD_CLOSE_EQUIP_DISASS,							/* �رղ��װ���Ի��� */

	GCD_UPDATE_CONTAINER,							/* ����״̬���� */
	GCD_IMPACT_SELF_UPDATE,							/* �Լ�����Ч���� */
	GCD_IMPACT_SELF_UPDATE_TIME,					/* �Լ�����Чʱ��ĸ��� */
	GCD_IMPACT_SELF_CLEANUP,						/* ��� */

	GCD_TOGLE_SKILLSTUDY,							/* �����츳��ѧϰ������ */
	GCD_SKILLSTUDY_SUCCEED,							/* �����츳ѧϰ�ɹ� */

	GCD_TOGLE_ABILITY_STUDY,						/* �����ѧϰ���� */
	GCD_TOGLE_ABILITY_STUDY_CLOSE,					/* �ر������ѧϰ���� */
	GCD_OPEN_AGNAME,								/* ��ѡ��ƺŽ��� */
	GCD_CLOSE_AGNAME,								/* �ر�ѡ��ƺŽ��� */

	GCD_TOGLE_BANK,									/* �����н��� */
	GCD_UPDATE_BANK,								/* �������н��� */
	GCD_TOGLE_BANKPET,								/* ������������� */
	GCD_UPDATE_BANKPET,								/* ��������������� */
	GCD_TOGLE_INPUT_MONEY,							/* ������Ǯ�Ľ��� */
	GCD_CLOSE_INPUT_MONEY,							/* �ر������Ǯ���� */
	GCD_OPEN_BANK_EVENT,							/* �ж��������뱣�� */

	GCD_RECEIVE_EXCHANGE_APPLY,					/* �յ��������� */
	GCD_STOP_EXCHANGE_TIP,							/* ֹͣ����������ʾ */
	GCD_OPEN_EXCHANGE_FRAME,						/* �򿪽��׶Ի��� */
	GCD_UPDATE_EXCHANGE,							/* ���½��׽��� */
	GCD_CANCEL_EXCHANGE,							/* ȡ������ */
	GCD_SUCCEED_EXCHANGE_CLOSE,					/* ���׳ɹ���֪ͨ�رս��׽��棨���ܻ���ر���ؽ��棩 */
	GCD_EXCHANGE_INPUT_MONEY,						/* ���׿������money */
	GCD_PACKET_OPEN_SALE,							/* ���뱣����̯���� */
	GCD_EQUIP_LEVELUP_CANCEL_BIND,					

	GCD_UPDATE_PET_PAGE,							/* ˢ�³������ */
	GCD_UPDATE_LIFESKILL_PAGE,						/* ˢ������ܽ��� */
	GCD_OPEN_COMPOSE_ITEM,							/* ��������Ʒ���� */
	GCD_UPDATE_COMPOSE_ITEM,						/* ˢ��������Ʒ���� */
	GCD_OPEN_COMPOSE_GEM,							/* ����Ƕ���� */
	GCD_OPEN_REPLACE_GEM,							/* �滻���� */
	GCD_UPDATE_COMPOSE_EQUIP,						/* ˢ����Ƕ���� */
	GCD_UPDATE_COMPOSE_GEM,							/* ˢ����Ƕ���� */
	GCD_COMPOSE_GEM_SUCCESS,						/* ˢ����Ƕ���� */
	GCD_ENCHASE_CONFIRM_DLG,						/* ��Ƕȷ�Ͻ��� */

	GCD_AFFIRM_SHOW,								/* �򿪷�������ȷ�Ͻ��� */

	GCD_OPEN_STALL_SALE,							/* ��̯(��) */
	GCD_OPEN_STALL_BUY,								/* ��̯(��) */
	GCD_OPEN_STALL_BUY_GOLDSURE,					/* ���̯λȷ���� */
	GCD_UPDATE_STALL_BUY,							/* ����(��) */
	GCD_UPDATE_STALL_SALE,							/* ����(��) */
	GCD_OPEN_STALL_RENT_FRAME,						/* ��̯(���˰����ʾ) */
	GCD_STALL_SALE_SELECT,							/* ��̯(��)ʱ��ѡ��̯λ�ϵ���Ʒ */
	GCD_STALL_BUY_SELECT,							/* ��̯(��)ʱ��ѡ��̯λ�ϵ���Ʒ */
	GCD_OPEN_STALL_MESSAGE,							/* ��̯(��Ϣ��������) */
	GCD_CLOSE_STALL_MESSAGE,						/* ��̯(��ϵ��Ϣ����) */

	GCD_OPEN_DISCARD_ITEM_FRAME,					/* ������Ʒ */
	GCD_OPEN_CANNT_DISCARD_ITEM,					/* ����������Ʒ */

	GCD_SHOW_SPLIT_ITEM,							/* �򿪲����ƽ�Ի��� */
	GCD_HIDE_SPLIT_ITEM,							/* �رղ����ƽ�Ի��� */

	GCD_TOGLE_FRIEND_INFO,							/* �򿪹رպ����б�Ի��� */
	GCD_TOGLE_FRIEND,								/* �򿪹رպ��ѶԻ��� */
	GCD_UPDATE_FRIEND,								/* ���º��������� */
	GCD_UPDATE_FRIEND_INFO,							/* �������ݽ���� */
	GCD_MENU_UPDATE_FRIENDCUSTOMGROUP,				/* ���º����Զ�����˵�(�Զ���1--�Զ���5) */
	GCD_OPEN_EMAIL,									/* ���ż����� */
	GCD_OPEN_EMAIL_WRITE,							/* ���ż����� */
	GCD_CLOSE_EMAIL_WRITE,							/* �ر��ż����� */
	GCD_HAVE_MAIL,									/* ���ʼ� */
	GCD_SEND_MAIL,									/* �����ʼ� */
	GCD_UPDATE_EMAIL,								/* ˢ�µ�ǰ�ʼ� */
	GCD_FRIEND_SET,									/* ���� */
	GCD_MOOD_CHANGE,								/* ����ı��� */
	GCD_OPEN_HISTROY,								/* �����ʷ��Ϣ */

	GCD_OPEN_XIAOLABA,								/* С���ȹ㲥��̨ */

	/* �������� */
	GCD_OPEN_FRIEND_SEARCH,							/* �������ѽ��� */

	/* ϵͳ������� */
	GCD_TOGLE_SYSTEMFRAME,							/* ��ϵͳ������ */
	GCD_TOGLE_VIEWSETUP,							/* ����Ƶ���ý��� */
	GCD_TOGLE_SOUNDSETUP,							/* ���������ý��� */
	GCD_TOGLE_UISETUP,								/* �򿪽������� */
	GCD_TOGLE_INPUTSETUP,							/* �򿪰������� */
	GCD_TOGLE_GAMESETUP,							/* ��Ϸ������ */
	GCD_UPDATE_VIEWSETUP,							// ������Ƶ���ý���

	/* �����Զ������ */
	GCD_KEYBOARD_SET_KEY,							/* ���ü�ֵ */
	GCD_KEYBOARD_SWAP_KEY,							/* ������ֵ */
	GCD_KEYBOARD_SET_REPEAT,						/* �����ظ����� */
	GCD_KEYBOARD_CANCEL,							/* ȡ���ض���ÿ�ݼ� */
	GCD_KEYBOARD_OVERWRITE,							/* �����ǿ�ݼ� */

	/* ����̵� */
	GCD_PS_OPEN_OTHER_SHOP,							/* �򿪱��˵��̵� */
	GCD_PS_OPEN_MY_SHOP,							/* ���Լ����̵� */
	GCD_PS_OPEN_CREATESHOP,							/* �򿪴����̵���� */
	GCD_PS_CLOSE_CREATESHOP,						/* �رմ����̵���� */
	GCD_PS_OPEN_SHOPLIST,							/* ���̵��б���� */
	GCD_PS_SELF_ITEM_CHANGED,						/* �Լ��̵�����Ʒ�����ı� */
	GCD_PS_OTHER_SELECT,							/* ѡ��һ����Ʒ */
	GCD_PS_SELF_SELECT,								/* ѡ��һ����Ʒ */

	GCD_PS_UPDATE_MY_SHOP,							/* �����Լ��̵������ */
	GCD_PS_UPDATE_OTHER_SHOP,						/* �����̵������ */

	GCD_PS_OPEN_OTHER_TRANS,						/* ���Լ����̳�״̬�е��̵� */
	GCD_PS_UPDATE_OTHER_TRANS,						/* ���� */
	GCD_PS_OTHER_TRANS_SELECT,						/* ѡ�� */

	GCD_OPEN_PS_MESSAGE_FRAME,						/* ����̵��������Ҫ������ȷ�϶Ի��� */

	GCD_PS_OPEN_MESSAGE,							/* ������̵����Ϣ�� */
	GCD_PS_UPDATE_MESSAGE,							/* ��������̵����Ϣ�� */

	GCD_OPEN_PET_LIST,								/* ���׵ȹ���ʹ�õĳ����б� */
	GCD_VIEW_EXCHANGE_PET,							/* ���׵ȹ�������ʾ���� */
	GCD_CLOSE_PET_LIST,								/* ���׵ȹ��̽�����ʱ��رճ����б���� */
	GCD_UPDATE_PET_LIST,							/* ���³����б���� */
	GCD_HORSE_IS_DELETED,							/* ��˱��������ջ� */
    GCD_OPEN_ITEM_LIST,                             /* �������ύ��Ʒ���� */
    GCD_CLOSE_ITEM_LIST,                            /* �ر������ύ��Ʒ���� */

	GCD_OPEN_PRIVATE_INFO,							/* �������Ϣ�Ի��� */
	GCD_OPEN_OTHER_INFO,							/* ��������Ͻ��� */
	GCD_UPDATE_PRIVATE_INFO,						/* ����������� */
	GCD_PRIVATE_INFO_MODIFY,						/* ����������޸� */

	GCD_OPEN_CALLOF_PLAYER,							/* ������Ҫ����ĶԻ��� */
	GCD_NET_CLOSE,									/* �Ͽ����� */

	GCD_OPEN_ITEM_COFFER,							/* ��������Ʒ���� */

	GCD_PS_INPUT_MONEY,								/* ��������̵������Ǯ�Ŀ� */

	/* �������¼� */
	GCD_TEAM_OPEN_TEAMINFO_DLG,						/* �򿪶�����Ϣ�Ի���. */

	/*
	 * ;
	 * arg0 - ������, ��0��ʼ ;
	 * 0 : ���������������� ;
	 * 1 : �������������� ;
	 * 2 : �򿪶�����Ϣ ;
	 * -1: �رնԻ�?
	 */
	GCD_TEAM_NOTIFY_APPLY,							/* ֪ͨ�ӳ�, ��������������. */

	/*
	 * ;
	 * arg0 - ������, ��0��ʼ ;
	 * 0 : ���������������� ;
	 * 1 : �������������� ;
	 * ������˵ľ�����Ϣ���������Ϣ�����л�?
	 */
	GCD_TEAM_APPLY,									/* ����������������. */

	/*
	 * ;
	 * arg0 - �ַ��� ;
	 * �������.
	 */
	GCD_TEAM_INVITE,								/* ����������������. */

	/*
	 * ;
	 * arg0 - �ַ��� ;
	 * ���������.
	 */
	GCD_TEAM_CLEAR_UI,								/* ��ս��� */

	/*
	 * ;
	 * �޲�?
	 */
	GCD_TEAM_REFRESH_UI,							/* ˢ�½��� */

	/*
	 * ;
	 * �޲���
	 */
	GCD_TEAM_MEMBER_ENTER,							/* ���µĶ�Ա���� */

	/*
	 * ;
	 * arg0 - ������, ��1 ��ʼ ;
	 * ��ui�����е���ʾλ��
	 */
	GCD_TEAM_UPTEDATA_MEMBER_INFO,					/* ���¶�Ա��Ϣ */

	/*
	 * arg0 - ������, ��1 ��ʼ ;
	 * ��ui�����е���ʾλ?
	 */
	GCD_TEAM_MESSAGE,								/* ������Ϣ��ʾ��Ϣ */

	/*
	 * arg0 - �ַ��� ;
	 * ��Ҫ��ʾ����Ϣ. ;
	 * ע��, ������Ϣ��������ʾ���������Ϣ ;
	 * ��: xxx�뿪���� ;
	 * xxx�Ѿ���һ��������
	 */
	GCD_TEAM_MEMBER_INVITE,							/* ��Ա����ĳһ���˼����������ӳ�ͬ�� */

	/*
	 * ;
	 * arg0 - ��Ա���� ;
	 * arg1 - �������˵���?
	 */
	GCD_TEAM_FOLLOW_INVITE,							/* �ӳ������Ա������Ӹ���ģʽ */

	/*
	 * ;
	 * arg0 - �ӳ���?
	 */
	GCD_TEAM_REFRESH_MEMBER,						/* ˢ�¶�Ա��Ϣ */

	/*
	 * ;
	 * arg0 - ��Ա��λ������
	 */
	GCD_CHANGE_TEAM_ITEM_DISTRIB_MODE,				/* �ı����ģʽ */

	/* �����Ժ���Ҫɾ�� */
	GCD_ON_TEAM_ENTER_MEMBER,						/* ���¶�Ա��� */

	GCD_SHOW_TEAM_YES_NO,							/* ��ͬ����Ӵ���. */

	GCD_SHOW_TEAM_MEMBER_INFO,						/* ��ʾ��Ա����ϸ��Ϣ. */

	GCD_SHOW_TEAM_MEMBER_NAME,						/* ����ߵĶ����б������ʾ���ѵ����� */

	GCD_HIDE_ALL_PLAYER,							/* �Լ��뿪�����, �������еĶ��ѽ��� */

	/* ��Ա����ϸ��Ϣ */
	GCD_SHOW_TEAM_MEMBER_NICK,						/* ���� */

	GCD_SHOW_TEAM_MEMBER_FAMILY,					/* ְҵ */
	GCD_SHOW_TEAM_MEMBER_LEVEL,						/* �ȼ� */
	GCD_SHOW_TEAM_MEMBER_POS,						/* λ�� */
	GCD_SHOW_TEAM_MEMBER_HP,						/* hp */
	GCD_SHOW_TEAM_MEMBER_MP,						/* mp */
	GCD_SHOW_TEAM_MEMBER_ANGER,						/* ŭ�� */
	GCD_SHOW_TEAM_MEMBER_DEAD_LINK,					/* ������Ϣ */
	GCD_SHOW_TEAM_MEMBER_DEAD,						/* ������Ϣ. */

	GCD_UPDATE_TEAM_MEMBER,							/* ���¶�Ա��Ϣ */

	/*
	 * arg0 - ��Ա��ţ������У��Լ���ռ����ţ� ;
	 * arg1 - ��Ա guid������ȡ�øö�Ա��Ϣ��
	 */
	GCD_SHOW_TEAM_FUNC_MENU_MEMBER,					/* ��ʾ��Ա�Ĺ��ܲ˵� */
	GCD_SHOW_TEAM_FUNC_MENU_LEADER,					/* ��ʾ�ӳ��Ĺ��ܲ˵� */

	/*
	 * ;
	 * �������¼� ;
	 * ;
	 * ��¼��� ;
	 */
	GCD_GAMELOGIN_SHOW_SYSTEM_INFO_CLOSE_NET,		/* ��ʾϵͳ��Ϣ */

	/*
	 * ;
	 * arg0 - �ַ��� : ��Ҫ��ʾ��ϵͳ��Ϣ. ;
	 * ���ȷ�ϰ�ť��Ͽ����硣
	 */
	GCD_GAMELOGIN_SHOW_SYSTEM_INFO,					/* ��ʾϵͳ��Ϣ */

	/*
	 * ;
	 * arg0 - �ַ��� : ��Ҫ��ʾ��ϵͳ��Ϣ.
	 */
	GCD_GAMELOGIN_CLOSE_SYSTEM_INFO,				/* ��ʾ�ӳ��Ĺ��ܲ˵� */

	GCD_GAMELOGIN_OPEN_SELECT_SERVER,				/* �ر�ѡ����������� */

	GCD_GAMELOGIN_CLOSE_SELECT_SERVER,				/* �ر�ѡ����������� */

	GCD_GAMELOGIN_OPEN_COUNT_INPUT,					/* ���ʺ�������� */
	GCD_GAMELOGIN_CLOSE_COUNT_INPUT,				/* �ر��ʺ�������� */
	GCD_GAMELOGIN_NOTIFY_COUNT_INPUT,				/* ֪ͨ�˺�Ϊ����״̬ */

	GCD_GAMELOGIN_SHOW_SYSTEM_INFO_NO_BUTTON,		/* ��ʾϵͳ��Ϣ, ����ʾ��ť */

	/*
	 * ;
	 * arg0 - �ַ��� : ��Ҫ��ʾ��ϵͳ��Ϣ
	 */
	GCD_GAMELOGIN_OPEN_SELECT_CHARACTOR,			/* ��ʾ����ѡ����� */

	GCD_GAMELOGIN_CLOSE_SELECT_CHARACTOR,			/* �ر�����ѡ����� */

	GCD_GAMELOGIN_OPEN_CREATE_CHARACTOR,			/* ��ʾ���ﴴ������ */

	GCD_GAMELOGIN_CLOSE_CREATE_CHARACTOR,			/* �ر����ﴴ������ */

	GCD_GAMELOGIN_REFRESH_ROLE_SELECT_CHARACTOR,	/* ˢ��������Ϣ */

	GCD_GAMELOGIN_CLOSE_BACK_GROUND,				/* �رձ������� */

	GCD_GAMELOGIN_SYSTEM_INFO_YESNO,				/* ϵͳ��Ϣ��ʾ yes_no ����. */

	/*
	 * ;
	 * ����0, ��ʾ���ַ��� ;
	 * ����1, �Ի�������� ;
	 * 0 -- �Ƿ��˳���Ϸ ;
	 * 1 -- �Ƿ�ɾ����ɫ ;
	 * 2 -- �Ƿ������?
	 */
	GCD_GAMELOGIN_SELECT_LOGIN_SERVER,				/* ѡ��һ��login server */

	/*
	 * ;
	 * ����0, iAreaIndex �������� ;
	 * ����1, iLoginServer ��������
	 */
	GCD_GAMELOGIN_CLEAR_ACCOUNT,					/* ����ʺ���ʾ. */
	GCD_GAMELOGIN_SELECT_AREA,						/* ����ʺ���ʾ. */
	GCD_GAMELOGIN_SELECT_LOGINSERVER,				/* ����ʺ���ʾ. */
	GCD_GAMELOGIN_CREATE_CLEAR_NAME,				/* ��մ�����ɫ�����֡� */
	GCD_GAMELOGIN_CREATE_ROLE_OK,					/* ������ɫ�ɹ��� */

	/*
	 * ;
	 * ��¼��� ;
	 */
	GCD_SUPERTOOLTIP,							/* Tooltips */

	/*
	 * | arg0 - ��ʾ/���� 1,0 | arg1 - ���� "skill", "lifeability", "item", "talent",
	 * "pet_skill" | arg2, arg3 - ���λ�� | ;
	 * ���������
	 */
	GCD_RELIVE_SHOW,							/* ��ʾ������� */

	/*
	 * arg0 - �Ƿ��и���İ�ť ;
	 * arg1 - ʣ��ʱ��
	 */
	GCD_RELIVE_HIDE,							/* ���ظ������ */

	GCD_RELIVE_REFESH_TIME,						/* ˢ�������ϵ�ʱ�� */

	/* ��ʾʱ�� */
	GCD_RELIVE_ACTIVE,							/* ���¼�������İ�ť */

	GCD_OBJECT_CARED_EVENT,						/* ĳ�߼������ĳЩ�����ı� */

	/*
	 * | arg0 - Object��ID | arg1 - ���� | distance: ���뷢���ı� (arg2����) |
	 * destroy: ������ |
	 */
	GCD_UPDATE_MAP,								/* ���µ�ͼ */
	GCD_UPDATE_NPC_MAP,							/* ����NPC��ͼ�б� */
	GCD_UPDATE_TRANSFER_MAP,					/* ���´��͵�ͼ�б� */

	GCD_UPDATE_SUPERTOOLTIP,
	GCD_UI_COMMAND,
	GCD_OTHERPLAYER_UPDATE_EQUIP,
	GCD_TOGLE_ONLINEUSER_EQUIP_ALL,
	GCD_VARIABLE_CHANGED,						/* ĳ��ȫ�ֱ��������ı䣬 */

	/* | arg0 - ������ | arg1 - �µı���ֵ */
	GCD_TIME_UPDATE,							/* ��ʱ��ϵͳ��ʱ�������¼� */
	GCD_FRIEND_INFO,							/* �򿪺�����ϸ��Ϣ */

	GCD_UPDATE_TARGETPET_PAGE,					/* ��targetpet ui */
	GCD_UPDATE_PETSKILLSTUDY,					/* ���³��＼��ѧϰ���� */

	GCD_UPDATE_PETINVITEFRIEND,					/* ���³������Ѱ���� */
	GCD_REPLY_QUEST_PET,						/* ����ˢ�� */

	GCD_GUILD_CREATE,							/* ��ᴴ���¼� */
	GCD_GUILD_CREATE_CONFIRM,					/* ��ᴴ��ȷ���¼� */
	GCD_GUILD_SHOW_LIST,						/* ��ʾ����б��¼� */
	GCD_GUILD_SHOW_MEMBERINFO,					/* ��ʾ�Լ�����Ա������� */
	GCD_GUILD_TOGGLE,							/* ��Ұ��°���ݼ��¼� */
	GCD_GUILD_UPDATE_MEMBERINFO,				/* ���°���Ա����Ϣ */
	GCD_GUILD_SHOW_DETAILINFO,					/* ��ʾ�Լ������ϸ��Ϣ���� */
	GCD_GUILD_SHOW_APPOINTPOS,					/* ��ʾ�Լ�������ְλ���� */
	GCD_GUILD_DESTORY_CONFIRM,					/* ɾ�����ȷ���¼� */
	GCD_GUILD_QUIT_CONFIRM,						/* �˳����ȷ���¼� */
	GCD_GUILD_FORCE_CLOSE,						/* ǿ�ư����ؽ���ر��¼� */
	GCD_GUILD_INVITE_OBJECT,					/* ����Ի��� */
	GCD_GUILD_NOTIFY_INTIVE,					/* ֪ͨ�յ�������� */
	GCD_GUILD_INTIVE_CONFIRM,					/* ����ȷ�� */
	GCD_GUILD_EVENT,							/* �����Ψһ���¼����¼�����type�����־�����¼������������е��¼���ͳһ����
												 * add by wujianping */
	GCD_GUILD_MODIFY_TITLE,						/* �޸ĳ�Ա�ƺ� */
	GCD_GUILD_MOVE_USER_TO_FAMILY,				/* ת�Ƴ�Ա��һ�����壬֪ͨUI���浯��һ����������������ֵ�ui */
	GCD_GUILD_CREATE_FAMILY,					/* �������� */
	GCD_GUILD_CREATE_FAMILY_CONFIRM,			/* ��������ȷ�� */
	GCD_GUILD_DESTORY_FAMILY_CONFIRM,			/* ɾ������ȷ�� */
	GCD_GUILD_LEVEL_UP,							/* ��������¼� */
	GCD_GUILD_SHOW_LIST_CARENPC,				/* �򿪰���б�ʱ��ϵNPC */
	GCD_INPUT_PASSWD_COMMAND,					/* ͨ����������򿪰����� */

	GCD_CLOSE_QUEST_REPLY,						/* �ر������ύUI */
	GCD_TOGLE_TARGET_EQUIP_PAGE,				/* �����鿴�Է���ɫװ������ */
	GCD_CLOSE_TARGET_EQUIP,						/* �رա������������������� */
	GCD_TOGLE_TARGET_EQUIP_ALL,					/* �����鿴�Է���ɫ���� */
	GCD_TOGLE_TARGET_EQUIP_ALL_FOR_AROUNDPLAYER,
	GCD_CLOSE_TARGET_EQUIP_ALL,					/* �رա��������������� */
	GCD_CHANGE_TARGET_EQUIP_ALL_PAGE,			/* �л����������������� */
	GCD_VIEW_RESOLUTION_CHANGED,				/* ��Ļ�ֱ��ʱ仯ʱ��֪ͨ��Ϣ */
	GCD_CLOSE_SYNTHESIZE_ENCHASE,				/* �رպϳ�UI����ǶUI */
	GCD_TOGGLE_PETLIST,							/* �򿪺͹رճ����б� */
	GCD_PET_FREE_CONFIRM,						/* ��������ȷ�� */

	/* ������� */
	GCD_TOGLE_MOUNT_PAGE,						/* ��/�ر������� */
	GCD_OPEN_MOUNT_PAGE,						/* �������� */
	GCD_CLOSE_MOUNT_PAGE,						/* �ر������� */
	GCD_MOUNT_ATTR_UPDATE,						/* ����������� */
	GCD_MOUNT_MATING_SUCCESS,					/* ����ɹ��¼� */
	GCD_MOUNT_COMPOSE_SUCCESS,					/* �ϳɳɹ��¼� */
	GCD_MOUNT_COMPOSE_LOCKPASS_ITEM_UPDATE,		/* ���ºϳ���Ʒ */
	GCD_MOUNT_COMPOSE_REPENT_ITEM_UPDATE,		/* ���ºϳ���Ʒ */
	GCD_MOUNT_ATTR_LINK,						/* ����������ʾ */
	GCD_MOUNT_HAPPINESS_UPDATE,					/* ��˿��ֶȸ��� */
	GCD_MOUNT_TIMER_UPDATE,						/* ��˺ϳɶ�ʱ������ */
	GCD_MOUNT_TIMER_STOP,						/* ��˺ϳɶ�ʱ��ֹͣ */
	GCD_MOUNT_SKILL_SLOT_NOT_ENOUGH,			/* ��˺ϳ�ʱ�����㲻�� */

	GCD_TOGLE_TARGET_MOUNT_PAGE,				/* �򿪻�ر�Ŀ��������� */
	GCD_TARGET_MOUNT_ATTR_UPDATE,				/* ����Ŀ���������� */

	GCD_TOGLE_MOUNT_STUDY_PAGE,					/* �򿪻�ر����ѧϰ���� */
	GCD_MOUNT_STUDY_ITEM_UPDATE,				/* �������ѧϰ��Ʒ */

	GCD_TOGLE_MOUNT_FEED_PAGE,					/* �򿪻�ر�����ι������ */
	GCD_MOUNT_FEED_ITEM_UPDATE,					/* �������ι����Ʒ */

	GCD_TOGLE_MOUNT_TRAIN_PAGE,					/* �򿪻�ر����ѱ������ */
	GCD_MOUNT_TRAIN_ITEM_UPDATE,				/* ����ѱ����Ʒ */

	GCD_TOGLE_MOUNT_IDENTIFY_PAGE,				/* �򿪻�ر����������� */

	GCD_TOGLE_MOUNT_MATING_PAGE,				/* ����跱ֳ���� */
	GCD_CLOSE_MOUNT_MATING_PAGE,				/* �ر���跱ֳ���� */
	GCD_MY_MOUNT_MATING_LOCKED,					/* �Լ��Ľ���������� */
	GCD_OTHER_MOUNT_MATING_LOCKED,				/* ���˵Ľ���������� */
	GCD_REQUEST_TOGLE_MOUNT_MATING_PAGE,		/* ���뿪����ֳ���� */
	GCD_GAIN_MATING_MOUNT,						/* ��ȡ��ֳ���� */
	GCD_TOGLE_MOUNT_COMPOSE_PAGE,				/* �����ϳɽ��� */
	GCD_TOGLE_MOUNT_COMPOSE_PAGE2,				/* �����ϳɵڶ������� */
	GCD_TOGLE_MOUNT_COMPOSE_START,				/* �����ϳ�,�ر�������˽��� */
	GCD_CLOSE_MOUNT_COMPOSE_PAGE,				/* �ر����ϳɽ��� */
	GCD_HORSE_PASSIVITY_SKILL_REPLACE_CONFIRM,	/* ��˱��������滻 */
	GCD_HORSE_SKILL_UP_CONFIRM,					/* ��˼������� */
	GCD_HORSE_SKILL_REPLACE_CONFIRM,			/* ��˼��� */
	GCD_HORSE_SKILL_REPLACE_MULTI_CONFIRM,		/* ��˼��� */
	GCD_HORSE_TOCHILD_CONFIRM,					/* ��˻�ͯ */

	GCD_OPEN_BUY_CONFIRM,						/* ���̵�����ȷ�Ͻ��� */
	GCD_OPEN_SALE_CONFIRM,						/* ���̵�����ȷ�Ͻ��� */

	GCD_SEARCH_MASTER,						/* ��ʦ�� */
	GCD_SEARCH_PRENTICE,					/* ��ͽ�� */
	GCD_REQUEST_MARRY,						/* ��� */

	/* �û����������������Ƶ��¼� */
	GCD_FRIEND_CREATE_GROUP,

	/* ����������� */
	GCD_OPEN_FRIEND_SEARCH_REASON,

	/* ��Ӻ������� */
	GCD_ADD_GROUP,
	GCD_QUICK_CHANGCD_NAME,					/* һ����װ���� */

	GCD_ITEM_LINK,							/* ��Ʒ���� arg0����Ʒ���� */
	GCD_QUEST_LINK,							/* �������� */
	GCD_HORSE_LINK,							/* �������� */
	GCD_SKILL_LINK,							/* �������� */
	GCD_QUEST_SUPER_TOOLTIP_SHOW,			/* ����������ʾ���� */
	GCD_SKILL_SUPER_TOOLTIP_SHOW,			/* ����������ʾ���� */

	GCD_TOGLE_MOUNT_CHILD_PAGE,				/* �򿪻�ر���軹ͯ���� */
	GCD_MOUNT_CHILD_ITEM_UPDATE,			/* ������軹ͯ��Ʒ */

	/* ��ʾ���ѵ���ϸ��Ϣ */
	GCD_SHOW_FRIEND_INFO,
	GCD_EQUIP_SWAPCARD_OPEN,				/* ��װ�����ͽ������� */
	GCD_EQUIP_SWAPCARD_UPDATA,				/* ����װ�����ͽ������� */
	GCD_EQUIP_SWAPCARD_SUCESS,				/* װ�����ͽ����ɹ� */

	GCD_EQUIP_CHANGECARD_OPEN,				/* ��װ�����͸������ */
	GCD_EQUIP_CHANGECARD_UPDATA,			/* ����װ�����͸������ */
	GCD_EQUIP_CHANGECARD_SUCESS,			/* װ�����͸���ɹ� */

	GCD_EQUIP_ALL_OPEN,						/* �򿪸���װ�� �������� ���˳ƺ� һ����װ ������� �������� */

	GCD_SHOW_TITLE,							/* ��ʾ�ƺŽ��� */
	GCD_UPDATE_TITLE,						/* ���³ƺŽ��� */

	GCD_PERSONAL_MESSAGE,					/* ������Ϣ */
	GCD_SYSTEM_MESSAGE,						/* ϵͳ��Ϣ */
	GCD_PARALLEL_MESSAGE,					/* ˮƽ��Ϣ */

	GCD_SHOW_SYSTEM_PROMPT,					/* ϵͳ��Ϣ��ʾͼ�� */

	/* GCD_SYSTEM_PROMPT_UPDATE, // ����ϵͳ��Ϣ��ʾͼ�� */
	GCD_OPERATE_SYSTEM_PROMPT,
	GCD_SHOW_SUPERTOOLTIP_TITLE,			/* ��ʾ�ƺ���ʾ */
	GCD_SHOW_COMPARETOOLTIP,				/* ��Ʒ���� // */
	GCD_SHOW_COMPARETOOLTIP_REPOS,			/* ��Ʒ�������¶�λ */
	GCD_UNITE_GF_SHOW,						/* ���ѺͰ������� */
	GCD_MASTER_OR_PRENTICE,					/* ʦͽ */

	/*
	 * �Ƿ����ö����������� ;
	 * ;
	 * GCD_MINORPASSWORD_OPEN_SET_PASSWORD_DLG, // �����ö���������� ;
	 * GCD_MINORPASSWORD_OPEN_UNLOCK_PASSWORD_DLG, // ��unlock������档 ;
	 * GCD_MINORPASSWORD_OPEN_CHANGCD_PASSWORD_DLG, // �����������
	 */
	GCD_OPEN_SYSTEM_TIP_INFO_DLG,			/* ��ʾϵͳ��Ϣ�Ի��� */

	GCD_INPUT_PASSWORD_DLG,					/* �������������� */

	GCD_INPUT_SUPER_PW_DLG,					/* ���볬��������� */

	GCD_INPUT_FIND_PLAYER_ITEM_DLG,				// ׷�ٷ�����


	/*
	 * ;
	 * �Ƿ����ö����������� ;
	 */
	GCD_RICH_SAFE_GUARD,					/* ������Χ���� */
	GCD_RICH_SAFE_TIME,						/* ��ȫʱ�޵������� */
	GCD_UPDATE_RICH_SAFE_TIME,				/* ���°�ȫʱ�� */
	GCD_RICH_SET_PASSWORD,					/* �������롢�޸�������� */
	GCD_RICH_MODIFY_PASSWORD,
	GCD_RICH_SETUP,							/* �Ʋ������������ý��� */
	GCD_OPEN_RICHES_PROTECT_FRAME,			/* �Ʋ�������ʾ���� */
	GCD_RICH_TEMP_CANCEL_PASSWORD,			/* ��ʱȡ������ */
	GCD_RICH_CANCEL_PASSWORD,				/* ȡ������ */
	GCD_RICH_CHECK_PASSWORD,				/* ����������� */
	GCD_RICH_SAFE_TIME_TIP,					/* ��ȫʱ����ʾ */
	GCD_RICH_DELETE_PWD_TIME_TIP,			/* ɾ�����뱣����ʣ��ʱ��������ʾ */

	/* temp ���ͽ����ã� �Ⱥϵ�һ��������Ͳ����� */
	GCD_TEMP_CLOSE_FRIEND,
	GCD_TEMP_CLOSE_GUILD,
	GCD_ADD_FRIEND,
	GCD_FRIEND_EVENT,
	GCD_FRIEND_CONFIRM_EVENT,
	GCD_EQUIP_ALL_CLOSE,					/* �رո���װ�� �������� ���˳ƺ� һ����װ ������� �������� */
	GCD_AUTOREPLY_RECV_MSG,					/* �յ�������ҷ�������������Ϣ */

	GCD_TOGLE_PLAYER_ATTR_PAGE,				/* ��������ϸ���Խ��� */
	GCD_CLOSE_PLAYER_ATTR_PAGE,				/* �ر�������ϸ���Խ��� */
	GCD_TOGLE_PLAYER_ATTR2_PAGE,
	GCD_CLOSE_PLAYER_ATTR2_PAGE,
	GCD_OPEN_DAY_TIPS,						/* ��ÿ�����ѹ��ܽ��� */
	GCD_UPDATE_DATE_TIME,					/* ����ÿ���������ں�ʱ�� */
	GCD_UPDATE_DAY_TIPS,					/* ����ÿ���������� */
	GCD_UPDATE_DAY_TIPS_DISPLAYLIST,		/* ����ÿ�����ѿ���ʾ�б� */
	GCD_UPDATE_CALENDAR,					/* ������������ */
	GCD_QUIT_UPDATE_CALENDAR,				/* �����˳��������� */

	GCD_OPEN_TOP_LIST,						/* �����а���� */
	GCD_UPDATE_TOP_LIST,					/* �������а���� */

	/* arg0��Ϊ0��ʾ������а�����Ϊ1��ʾ������а����� */
	GCD_LEVEL_TOP_LIST,						/* �ȼ����а� */
	GCD_MONEY_TOP_LIST,						/* �Ƹ����а� */
	GCD_NO_TOPLIST_INFO,					/* û�����а���Ϣ */
	GCD_UPDATE_TOPLIST_PERSONINFO,			/* �������а������Ϣ */

	GCD_OPEN_QUEST_SCOUT,					/* ��������ٽ��� */
	GCD_UPDATE_QUEST_SCOUT,					/* ����������ٽ��� */
	GCD_UPDATA_EQUIP_ALL_POS,				/* ����6������λ�� ������װ�� �������� ���˳ƺ� һ����װ ������� �������ϡ� */

	GCD_COUNTRY_EVENT,						/* ������Ψһ���¼����¼�����type�����־�����¼������������е��¼���ͳһ����
											 * add by wujianping */
	GCD_COUNTRY_MANAGER_REQUEST_INFO,		/* ���������Ϣ */
	GCD_COUNTRY_MANAGER_INFO,				/* ������Ϣ */
	GCD_COUNTRY_MANAGER_ADJUST_AUTH,		/* ���ҹ�ְ���� */
	GCD_INPUT_COUNTRY_DLG,					/* ������ҹ�ְ */
	GCD_COUNTRY_MANAGER_CREATE_KING,		/* �������� */
	GCD_COUNTRY_KING_CREATE_CONFIRM,		/* ȷ�ϲ������� */
	GCD_COUNTRY_MANAGER_KING_COLLECT,		/* ļ�� */

	GCD_SHOW_EQUIP_CONTEXMENU,				/* ��ʾװ���Ҽ��˵� */

	/*
	 * arg0 - �˵��� ;
	 * arg1 - ���λ��_x ;
	 * arg2 - ���λ��_
	 */
	GCD_CLOSE_EQUIP_CONTEXMENU,
	GCD_FILL_TEAM_MEMBER,					/* ����Ա��Ϣ */
	GCD_FILL_TEAM_INFO,						/* ��������Ϣ */
	GCD_FILL_TEAMSEARCH_INFO,				/* ���Ѱ�������Ϣ */

	GCD_GUILD_KICK_CONFIRM,					/* �������ȷ�� */

	GCD_MOUNT_FRIEND_SETUI_SHOW,			/* ��������趨���� */
	GCD_MOUNT_FRIEND_SEARCHUI_SHOW,			/* ������Ѳ�ѯ���� */
	GCD_MOUNT_FRIEND_VIEWUI_SHOW,			/* ��˲鿴���� */
	GCD_MOUNT_FRIEND_INITINFO,				/* �鿴������Ϣ��ʾ */
	GCD_SAMECITY_PLAYER_UPDATEUI,			/* ͬ����ҽ������ */

	GCD_TOGLE_CHATQUERY,					/* [ ZG ] ������ʷ��¼ */

	GCD_TOGLE_SUBTRAIN_PAGE,				/* �������� */
	GCD_UPDATE_SUBTRAIN_PAGE,
	GCD_PK_MODE_CHANGED,					/* by soongxl */

	GCD_SUB_TRAIN_EXP_DLG,					/* ��ȡ����ȷ�Ͻ��� */
	GCD_SUB_TRAIN_GETEXP_DLG,				/* �о���δ��ȡ��ʾ */
	GCD_CLOSE_STALL_SALE,					/* ��̯(��) */
	GCD_STALL_SAVE_DLG,						/* ��̯���� */

	GCD_SHORTCUT_KEYDOWN,					/* !< ��ݼ������¼� */
	GCD_SHORTCUT_KEYUP,						/* !< ��ݼ��ɿ��¼� */

	GCD_EXTENT_SHORTCUT,					/* !< 081103����������չ��ݼ��¼� */
	GCD_SHORTCUT_RIGHTBAR,					/* !< �Ҳ�������ݼ���Ϣ */
	GCD_RIDE_EXTENT_SHORTCUT,				/* !< ��˿������ݼ��¼� */

	GCD_EXTEND_SHORTCUT_SHOW,				/* ��չ����� */

	GCD_GUAJI_SHOW,							/* �һ����� */
	GCD_GUAJI_UPDATE,
	GCD_TOGGLE_GUAJI,						/* 081105���������л��һ����� */

	GCD_DOUBLEACTION_REQUEST,				/* ˫�˶������� */

	GCD_OPEN_DONATEPUTOUT,					/* ����ļ�� [ ZG ] */
	GCD_OPEN_DONATE,						/* �ύļ����� [ ZG ] */
	GCD_COUNTRY_DELATE,						/* �������� [ ZG ] */
	GCD_COUNTRY_VOTEON,						/* ����ͶƱ [ ZG ] */
	GCD_OTHER_TEAM_INFO,					/* �Է�������Ϣ���� [ ZG ] */
	GCD_OTHER_TEAM_INFO_HIDE,				/* �������ر� */

	GCD_EXT_PACKAGE_OPEN,					/* by soongxl ��չ���� */
	GCD_DOUBLEACTION_CANCEL,				/* ȡ��˫�˶��� */

	GCD_SEND_MOOD_ANIM,						/* ���ͱ��鶯�� */

	GCD_TOGLE_TREASUREBOX_PAGE,				/* �򿪱������ */
	GCD_CLOSE_TREASUREBOX_PAGE,				/* �رձ������ */
	GCD_TREASUREBOX_UPDATE,					/* ���±������ */
	GCD_TREASUREBOX_GETITEM_RESULT,			/* �����Ʒ�Ľ�� */

	GCD_CREATE_BUS,							/* ����bus */
	GCD_OPEN_BUS,							/* ��bus */
	GCD_UPDATE_BUS,							/* ����bus��Ϣ */
	GCD_OPEN_CASHBUS,						/* ���ڳ� */

	GCD_OPEN_REGISTRATION,					/* ��ע���ʺŽ��� */
	GCD_UPDATA_EQUIP_REWORK,
	GCD_HIDE_TOOLTIP,
	GCD_UNLOCK_ITEM_ONLEAVE,				/* ������Ʒ */

	GCD_NAME_INPUT_ERROR,					/* ��������ֲ��Ϸ� */
	GCD_NAME_INPUT_EMPTY,					/* ���������Ϊ�� */

	GCD_UPDATA_SELF_ATTR,					/* �������� */
	GCD_LOGIN_KEYPRESS,						/* ��½ʱ���̿�ݼ����� */

	GCD_EFFECT_UI_OPEN,						/* ������Чui */
	GCD_EFFECT_UI_CLOSE,
	GCD_MENTAL_GAME_ASK_SIGNUP,				/* ���� */
	GCD_MENTAL_GAME_INTERFACE,
	GCD_MENTAL_GAME_THINK,
	GCD_MENTAL_GAME_QUIZ,
	GCD_MENTAL_GAME_SCORE,					/* ˢ�·��� */
	GCD_MENTAL_GAME_WENCAI,					/* ˢ���Ĳ� */
	GCD_MENTAL_GAME_SORTID,					/* �õ����� */
	GCD_MENTAL_GAME_FINISHED,				/* ������� */
	GCD_MENTAL_GAME_ANSWER_RESULT,			/* ������ */
	GCD_MENTAL_GAME_CLOSE_INTERFACE,		/* ����رս��� */
	GCD_MENTAL_GAME_BUY_ITEM,				/* ���⹺�����*/

	GCD_TOGLE_VALIDATE,						/* ��|�رշ������֤���� */
	GCD_UPDATE_VALIDATE,					/* ���·������֤���� */

	GCD_OPEN_CONVOYBUS,						/* �򿪰�����ڽ��� */
	GCD_ASK_GUILDCONVOY,					/* ѯ�ʰ������ */
	GCD_ASK_GUILDCONVOY_QUEST,				/* ѯ���Ƿ���ܰ���������� */

	GCD_TOGLE_GUILDCONVOY_INFOLIST,			/* ��/�رհ�����ڽ��� */
	GCD_GUILDCONVOY_INFO_UPDATE,			/* ���� */

	GCD_QUIT_GAME_CONFIRM,					/* �˳���Ϸȷ�� */
	GCD_RETURN_LOGIN_CONFIRM,
	GCD_QUIT_GAME_TIME_UPDATA,				/* �˳��򷵻ص�½��ʱ����� */

	GCD_RECONNECT_SERVER,					/* �������ӷ����� */
	GCD_RECONNECT_SERVER_UPDATA,			/* �������ӷ�������ʱ����� */

	GCD_UPDATE_PING,						/* ������Ϸ���pingֵ */
	GCD_THIRD_SHORTCUT_SHOW,				/* ������ݼ� */
	GCD_UNIT_MONEYMODE,
	GCD_TOGLE_MOUNT_CLEARPOINT,				/* ��/�ر����ϴ����� */
	GCD_MOUNT_CLEARPOINT_ITEM_UPDATE,		/* ˢ����Ʒ */

	GCD_ASK_INTO_BUS,						/* �������ս�� */
	GCD_INVITE_TO_BUS,						/* �������ս�� */
	GCD_UPDATE_BUS_STATE,					/* ����bus��ť״̬ */

	GCD_OPEN_NPC_FINDPATH,					/* NPC�Զ�Ѱ· */
	GCD_OPEN_WORLDMAP,						/* �����ͼ */
	GCD_OPEN_TRIP_MAP,						/* �����ţ������ͣ� */

	GCD_WINDOW_SHOW,
	GCD_ESCAPE_HIDE_MESSAGE,				/* ESCͳһ������Ϣ */

	GCD_OPEN_GOLD_EXCHANGE,					/* ���Ӷһ� */
	GCD_CLOSE_GOLD_EXCHANGE,				/* ���Ӷһ� */
	GCD_OPEN_GOLDCARD_EXCHANGE,				/* �𿨶һ� */
	GCD_CLOSE_GOLDCARD_EXCHANGE,			/* �𿨶һ� */

	GCD_OPEN_QUIZQUEST_INTERFACE,			/* �����ƾٴ��̽��� */
	GCD_CLOSE_QUIZQUEST_INTERFACE,			/* �رտƾٴ��̽��� */
	GCD_FLASH_QUIZQUEST_TIME,				/* ˢ�¿ƾٴ���ʱ�� */

	GCD_UPDATE_MIXTURE,						/* ���µ��ߺϳ���壨�ϳɺ����ȣ� */
	GCD_UPDATE_MIXTURE_SUCC,				/* ������ߺϳɳɹ�ʱ */
	GCD_UPDATE_MIXTURE_FAIL,				/* ������ߺϳ���ɵ���δ�ɹ� */

	GCD_UNIT_FASHIONMODE,
	GCD_WINDOW_INPUT_KEY,					/* �������ڴ�������¼� */
	GCD_WINDOW_INPUT_MOUSE,					/* �������ڴ�������¼� */

	GCD_ASK_COUNTRY_DESTROY_ISSUE,			/* �������� */

	GCD_ASK_GUILD_BATTLE,					/* ���ս */
	GCD_OPEN_BATTLE_INTERFACE,				/* ����ս����Ϣ��� */
	GCD_REFRESH_BATTLE_INFO,				/* ����ս����Ϣ��� */

	GCD_TOGLE_MOUNT_TF_PAGE,				/* �������������� */
	GCD_MOUNT_TF_ITEM_UPDATE,				/* �������������� */

	GCD_PLAY_IMPACT,						/* ����һ����Ч */
	GCD_RICH_MODIFY_PASSWORD_CLOSE,
	GCD_UNLOAD_OPERATOR_ITEM,
	GCD_TOGLE_VIEWSKILL_PAGE,				/* ����/�رռ��ܲ鿴���� */
	GCD_VIEWSKILL_UPDATE,					/* ���� */
	GCD_OPEN_VIEWSKILL_PAGE,
	GCD_SCENEMAP_FLASH_POINT,				/* ����ͼ��˸ĳ�� */
	GCD_SCENEMAP_COUNTRYFIGHTALARM,			/* ������Ա��ɱ��ͼ��ʾ��Ϣ */
	GCD_SCENEMAP_COUNTRYFIGHTCLICK,			/* ������Ա��ɱ��ʾ��Ϣ����¼� */

	GCD_SUPERTOOLTIPCMPF,
	GCD_UPDATE_SUPERTOOLTIPCMPF,
	GCD_HIDE_TOOLTIPCMPF,
	GCD_SUPERTOOLTIPCMPS,
	GCD_UPDATE_SUPERTOOLTIPCMPS,
	GCD_HIDE_TOOLTIPCMPS,
	GCD_MIDDLE_BOTTOM_SCROLL_MESSAGE,		/* �м��²��Ĺ����� */
	GCD_MIDDLE_BOTTOM_TEXT_MESSAGE,			/* �м��²����ı��� */
	GCD_MIDDLE_ANIM_MESSAGE,				/* �м�Ķ����� */

	GCD_LOCKKEYBOARD_INPUT,					/* ����������������ĸ������ĸ���¼� */

	GCD_GUARD_INFO,							/* �ٻ�����Ϣ */
	GCD_GUARDER_CHANGED,
	GCD_OPEN_GUILD_BATTLE_STATISTIC,		/* �򿪰�սͳ�ƽ��� */
	GCD_CLOSE_GUILD_BATTLE_STATISTIC,		/* �رհ�սͳ�ƽ��� */
	GCD_UPDATE_GUILD_BATTLE_STATISTIC,		/* ���°�ս������� */

	GCD_OPEN_EXERCISESCOUT,					/* ��ÿ����ʾ�׷�� */
	GCD_CLOSE_EXERCISESCOUT,				/* �ر�ÿ����ʾ�׷�� */
	GCD_UPDATE_EXERCISESCOUT,				/* ����ÿ����ʾ�׷�� */
	GCD_OPEN_DISMANTLE_EQUIP_FRAME,			/* ���ȷ�� */
	GCD_OPEN_BIND_EQUIP_FRAME,				/* ��ȷ�� */
	GCD_UNIT_Updata_BangGong,
	GCD_UNIT_Updata_ShengWang,
	GCD_OPEN_ACTIVE_SHOP_ITEM_FRAME,
	GCD_ASK_KING_BATTLE,					/* ��������ս -CZG */
	GCD_DAMAGE_TIP,							/* �˺���ʾ */
	GCD_ADVANCED_ROSE,						/* �߼�õ�廨��Ч��QL�� */

	GCD_OPEN_CHECKOUT,						// ��У�������
	GCD_OPEN_SCENE_ANSWER,					/* ���������ʴ� */
	GCD_SET_CHECKOUT,						// ���ò���
	GCD_REFURBISH_CHECKOUT,					/* ��ˢУ������� */
	
	GCD_CAPTCHA_OPEN,						// ͼ����֤����
	GCD_CAPTCHA_TIME_EVENT,					// 

	GCD_OPEN_HELP,							/* �����ְ������� */
	GCD_OPEN_GOLD_BUTTON,
	GCD_CLOSE_GOLD_BUTTON,
	GCD_ENABLE_IB_SHOP_BUTTON,
	GCD_RICH_SAFE_GUARD_CLEAR,				/* �����ܱ� */
	GCD_LEVEL_UP,							/* �������� */

	GCD_POS_CARED_EVENT,					/* ��λ����صľ������ */
	GCD_ENABLE_IB_SHOP_BUTTON_ANI,			/* ���ֽ��̵갴臨���Ч����Ч */

	GCD_MOREKEY_VIEW_RESET,					/* ������չ�����ͼ�� */
	GCD_CHAR_RENAME,						/* ��ɫ������ */
	GCD_UPDATE_RENAME_FLAG,					/* ������������� */
	GCD_START_OPEN_BOX_STATE,				/* ���뿪������״̬ */

	GCD_ASK_COUNTRY_BATTLE_LITE,			/* ����С��ս */
	GCD_ASK_COUNTRY_BATTLE_LITE_KINGISSUE,	/* С��ս���� */
	GCD_ASK_WORLDCUP_JOIN,					/* ������籭���� */

	GCD_UPDATE_SHORTCUT_KEY,				/* ���¿�ݼ� */

	/* �ֽ������� */
	GCD_OPEN_WORLD_IB_SHOP_SELL,			/* �򿪼��۽��� */
	GCD_CLOSE_WORLD_IB_SHOP_SELL,			/* �رռ��۽��� */
	GCD_OPEN_WORLD_IB_SHOP_BUY,				/* �򿪹������ */
	GCD_OPEN_GOLD_SALE_MESSAGE,				/* ����ȷ�϶Ի��� */

	GCD_TIRED_SCENE_INFO,					/* ƣ�ͳ�����ʾ��Ϣ */
	GCD_OPEN_STALL_BUY_CONFIRM,				/* ��̯����ȷ�� */
	GCD_OPEN_SUPERTOOLTIPABILITY,			/* ����ʾ */
	GCD_CLOSE_SUPERTOOLTIPABILITY,			/* �ر���ʾ */
	GCD_UNIT_UPDATA_GOODBADVALUE,			/* ˢ���ƶ�ֵ */

	GCD_LOCKED_SHORTCUT,					/* ��������� */

	GCD_PASSWORD_CARD_OPEN,					/* �ܱ��� */
	GCD_PASSWORD_CARD_CLOSE,
	GCD_PASSPOD,							/* ��̬�ܱ� */
	GCD_OPEN_DESTROY_TASK_ITEM,
	GCD_UPDATA_DESTROY_TASK_ITEM,
	GCD_DESTROY_TASK_ITEM,					/* ɾ��������� */

	GCD_DIALOG_SHOW,						/* �����Ի� */
	GCD_DIALOG_UPDATE,						/* ���¶Ի� */
	GCD_DIALOG_SEND,						/* ���ͶԻ� */
	GCD_DIALOG_OPEN_HISTORY,				/* �Ի���ʷ */
	GCD_DIALOG_ITEM_LINK,					/* ��Ʒ������ */
	GCD_DIALOG_QUEST_LINK,					/* �������� */
	GCD_DIALOG_HORSE_LINK,					/* ������ */
	GCD_DIALOG_SKILL_LINK,					/* ���ܳ����� */
	GCD_OPEN_EQUIP_COLOR_CHANGE,			/* �򿪻�װ����װ���� */
	GCD_UPDATE_EQUIP_COLOR_CHANGE,			/* ���»�װ����װ���� */
	GCD_OPEN_EQUIP_PURPLE_REWORK,			/* ����װϴ���Խ��� */
	GCD_UPDATE_EQUIP_PURPLE_REWORK,			/* ������װϴ���Խ��� */
	GCD_UPDATE_EQUIP_COLOR_CHANGE_RESULT,	/* ��װ����װ��� */
	GCD_UPDATE_EQUIP_PURPLE_REWORK_RESULT,	/* ��װϴ���Խ�� */

	GCD_DUEL_INVITE,						/* �������� */

	GCD_OPEN_DELQUESTITEM,				/* ɾ��������� */
	GCD_LOCKITEM,						/* ���� */
	GCD_UNLOCKITEM,						/* ���� */

	GCD_SHOW_SUPERTOOLTIP_ACTIVATION,	/* ��������tip���� */

	GCD_TOGLE_AUTO_USE_DRUG,			/* ����/�ر� �Զ���ҩ */
	GCD_UPDATE_AUTO_USE_DRUG,			/* ���� */

	GCD_OPEN_PAY_MESSAGEBOX,			/* ������ֵ��Ϣ�� */

	GCD_UNIT_UPDATA_PVP2V2MARK,			/* ˢ��Ӣ�ۻ���� */

	/* ��ʯ�ϳɺ�������� */
	GCD_OPEN_GEM_LEVELUP,
	GCD_UPDATE_GEM_LEVELUP,
	GCD_GEM_LEVELUP_RESULT,
	GCD_OPEN_GEM_SYN,
	GCD_UPDATE_GEM_SYN,
	GCD_GEM_SYN_RESULT,

	/* ��ʯ��ж */
	GCD_OPEN_GEM_UNINST,
	GCD_GEM_UNINST_RESULT,

	/* װ���������� */
	GCD_OPEN_EQUIP_COPY,
	GCD_UPDATE_EQUIP_COPY,
	GCD_EQUIP_COPY_RESULT,
	GCD_IBSHOP_OPEN,					/* �򿪽���̵� */
	GCD_IBSHOP_CLOSE,					/* �رս���̵� */
	GCD_IBSHOP_UPDATE,					/* ���½���̵� */
	GCD_OPEN_EQUIP_COPY_OTHER,

	GCD_OEQUIP_COPY_FRAME, //װ������ȷ��
	GCD_STUDY_SKILL_MSG ,	//ѧϰ9������ȷ��

	GCD_ASK_IF_REGISTER_MIBAOKA,		/* �ܱ�����*/
	GCD_EQUIP_WANFA_FRAME,		
	GCD_EQUIP_WANFA_FRAME_OK,
	GCD_OPEN_EQUIP_RECALL,
	GCD_EQUIP_RECALL_RESULT,
	GCD_UPDATE_EQUIP_RECALL,
	GCD_OPEN_ITEM_RECALL,
	GCD_UPDATE_ITEM_RECALL,
	GCD_TEAMMEMBER_CALL_UP,			//��Ա�ټ�
	GCD_TRANSPOS_UPDATE,			//ʹ�ô��ͷ�����

	GCD_SHOW_EQUIP_CHANGE_EFFECT,	// ��ʾ��װʱ����Ч

    GCD_SHOW_TOP_MESSAGEBOX,        // ��ʾ����ģ̬�Ի���
    GCD_EXIT_TIMER_UPDATE,          // ǿ���˻ص�¼���涨ʱ�������¼�

	GCD_OPEN_STOCK_FRAME,						/* �򿪹�Ʊ������ */
	GCD_UPDATE_STOCK_TOP_LIST,					/* ���´�����Ϣ */
	GCD_UPDATE_ACC_MONEY,						/* ���¹�Ʊ�˻���� */
	GCD_UPDATE_STOCK_RECPRD,					/* ���¹�Ʊ������ʷ��¼ */
	GCD_UPDATE_STOCK_MARKET,					/* ���¹�Ʊ�ϼ��б� */
	GCD_OPEN_STOCK_BUY_SURE_FRAME,				/* �򿪹�Ʊ����ȷ�Ͽ�"*/
	GCD_NEW_PLAYER_UI_TIPS,						/* ����UI������ʾ*/
	GCD_OPEN_1LEVEL_REMIND_FRAME,				/*��һ�����ѿ�*/
	GCD_TRANSPOS_SET_FRAME,							/*���ͷ���λȷ��*/
	
	//����������
	GCD_OPEN_BULL_IN,					
	GCD_UPDATE_BULL_IN,
	GCD_BULL_IN_RESULT,
	//�����Ը���
	GCD_OPEN_BULL_ADD,					
	GCD_UPDATE_BULL_ADD,
	GCD_BULL_ADD_RESULT,

	GCD_UPDATE_LOGIN_SAFE_INFO,		// ��ʾ��¼�ܱ���Ϣ
	GCD_TOGLE_SAFE_SET,				// ��Ϸ�ڵ��ܱ�����
	GCD_SHOW_SAFE_DETAIL_INFO,		// ��ʾ�ܱ���ϸ��Ϣ

	GCD_OPEN_AWARD_FRAME,			// ���콱�Ի���

	GCD_OPEN_EQUIPPRODUCE,		// �򿪴���װ���Ի���
	GCD_CLOSE_EQUIPPRODUCE,		// �رմ���װ���Ի���
	GCD_ABILITY_COOLDOWN_TIME_ENENT,	//�������ȴ
	GCD_ABILITY_COOLDOWN_ADD_TIMER,		//�������ȴ
	GCD_RETURN_SELECT_ROLE,				//���ص�½����

    GCD_OPEN_PROFESSION_SWITCH_UI,      // ��2010-03-24��ql����ְҵת������
    GCD_ADD_PROFESSION_SWITCH_ITEM,     // ��2010-03-26��ql�����ְҵת����Ʒ��ת������

	GCD_OPEN_EQUIPSWITCH,		// ��ת��װ������
	GCD_UPDATE_EQUIPSWITCH,		// ����ת��װ������
	GCD_CLOSE_EQUIPSWITCH,		// �ر�ת��װ������

	GCD_OPEN_BLUE_INTENSIFY,	//��������ǿ������
	GCD_UPDATE_BLUE_INTENSIFY,	//����������ǿ������
	GCD_UPDATE_BLUE_INTENSIFY_ATTR,	//����������ǿ�������е�������ֵ
	GCD_CLOSE_BLUE_INTENSIFY,	//�ر�������ǿ������

	GCD_OPEN_BLUE_RESET,		//�������Ի�ͯ����
	GCD_UPDATE_BLUE_RESET,		//���������Ի�ͯ����
	GCD_UPDATE_BLUE_RESET_ATTR,	//���������Ի�ͯ�����е�������ֵ
	GCD_CLOSE_BLUE_RESET,		//�ر������Ի�ͯ����

	GCD_KING_ZHAOJI, //���������ټ���
	GCD_UPDATE_GUILD_LAIRD_INFO,//���°��ݵ���Ϣ

	GCD_STALL_ITEM_BUY,			// ��̯��Ʒ����
	GCD_IB_STALL_ITEM_BUY,

	GCD_STALL_PET_BUY,			// ��̯��˹���
	GCD_IB_STALL_PET_BUY,

	GCD_SHOW_LOAD_BACKDROP,		// ��ʾ������
	GCD_UPDATE_LOAD_PROGRESS,	// ���½�����

	GCD_UPDATE_BATTLE_MAP,		// ����ս����ͼ

	GCD_CAPSLOCK_KEYDOWN,		//  CapsLock�������¼�

	GCD_UNIT_MOVE_MOVE,			// �ƶ�ģʽ

    GCD_COUNTRY_PRECONTRACT_OPEN,   // �򿪹���ԤԼ����

	GCD_GAMELOGIN_OPEN_VIEW_SETUP,	// �򿪵�¼�������ʾ���ý���
	GCD_GAMELOGIN_CLOSE_VIEW_SETUP,	// �رյ�¼�������ʾ���ý���
	
	GCD_OPEN_WORLD_DIRECTORY,		// �򿪽���ָ��
	GCD_UPDATE_WORLD_DIRECTORY,		// ���½���ָ��

	GCD_OPEN_CHANGE_APPEARANCE,		//�򿪸�������
	GCD_UPDATE_CHAR_CHANGE_APPEARACE_RESULT,  //����������

	GCD_TO_OPEN_SHOP,//��NPC�̵�

	GCD_OPEN_SELFGIFT,	//���츳����
	GCD_CLOSE_SELFGIFT,	//�ر��츳����

	GCD_CLOSE_SCENE_TRANS,	// �رճ�������Ļ��

	GCD_OPEN_SELF_GIFT,		// ���������츳����
	GCD_UPDATE_SELF_GIFT,	// ���¸����츳����

	GCD_OPEN_GUILD_GIFT,	// ��������츳����
	GCD_UPDATE_GUILD_GIFT,	// ���°���츳����

	GCD_OPEN_BLUE_SYN,	 // �򿪻������ɫ
	GCD_UPDATE_BLUE_SYN, // ���»������ɫ
	GCD_CLOSE_BLUE_SYN,	 // �رջ������ɫ
	GCD_BLUE_SYN_RESULT, //�������ɫ���

	GCD_GUILD_SKILL_GUILD_LEVEL_UP,
	GCD_GUILD_SKILL_GUILD_EXP,
	GCD_GUILD_SKILL_GUILD_MONEY,
	GCD_GUILD_SKILL_CHAR_INHERENCE_LEVEL,
	GCD_GUILD_SKILL_CHAR_MONEY,
	GCD_GUILD_SKILL_CHAR_BANGGONG,
	GCD_GUILD_SKILL_CHAR_SHENGWANG,
	GCD_GUILD_SKILL_CHAR_WEIWANG,
	GCD_GUILD_SKILL_CHAR_ITEM,

	GCD_OPEN_SUIT_DA_XING,//��ʱװ����

	GCD_GAMELOGIN_ENTER_SUCCEED,	// ��¼����ɹ�

	GCD_TO_OPEN_QINGJIAN,	// ���ӳ�͢����뽭�����Ļ����뻥����ʾ

	GCD_OPEN_BALANCE_GIFT,	// ƽ���츳
	GCD_UPDATE_BALANCE_GIFT,

	GCD_OPEN_NEW_EQUIPPRODUCE,   //�򿪳�װ����
	GCD_UPDATE_NEW_EQUIPPRODUCE, //���³�װ����
	GCD_CLOSE_NEW_EQUIPPRODUCE,  //�رճ�װ����
	GCD_NEW_EQUIPPRODUCE_RESULT, //��װ������
	
	GCD_OPEN_EQUIP_CONST_BIND,          //������װ������
	GCD_UPDATE_EQUIP_CONST_BIND,        //������װ���̽���
	GCD_UPDATE_EQUIP_CONST_BIND_RESULT, //�����������̽��

    GCD_OPEN_INH_ATTACK,                // ���츳ר������
    GCD_OPEN_INH_DEFEND,                // ���츳ר������

    GCD_UPDATE_INH_ATTACK,              // ����ר����Ϣ
    GCD_UPDATE_INH_DEFEND,              // ����ר����Ϣ
    GCD_INH_ATTACK_RESET,               // ר������ȷ��
    
    GCD_UNIT_BATTLEHONOUR,	// ս������

    GCD_INH_ATTACK_CONFIRM,             // ר���츳��������ȷ��

	GCD_OPEN_HONOR_BIND,		//��������
	GCD_GUILD_SEND_MAIL,		//Ⱥ���ʼ�

	GCD_DRAG_SHOP_ITEM_TO_BAG,	/* ���̵����Ʒ�ᶯ������ */

	GCD_OPEN_XINNIAN,			// �������ַ��ύ

	GCD_AGREE_COUNTRY_COLLEAGUE_YES_NO_TO_ACQUIRE, //��Ҫ����ȷ���Ƿ���Ҫ����
	GCD_AGREE_COUNTRY_COLLEAGUE_YES_NO,			   //����ͬ�����
	

	GCD_OPEN_GUILD_BUSSKILL_STUDY,		/* �򿪰�����޼����о����� */
	GCD_UPDATE_GUILD_BUSKILL,			/* ���°�����޼����о����� */
	GCD_UPDATE_GUILD_BUSSKILL_TOOLBAR,	/* ���°�����޼��ܿ���� */

    GCD_DAILIAN_CONFIRM,                // �򿪴���ȷ����Ϣ��
    GCD_WUTING_MANAGEMENT,              // �����й�
    GCD_WUTING_PRECONTRACT,             // ����ԤԼ

};	/* define */

struct sCommand;
typedef void (__stdcall *HANDLE_COMMAND_FUNC) (const sCommand *pCommand, uint32 dwOwnerData);

struct sCommandData
{
	GAME_COMMAND_ID										idCommand;		/* �¼�����ö�� */
	LPCTSTR												szCommand;		/* �ַ����¼����� */
	BOOL												bDelayProcess;	/* �ӻ������������ٶ��� */
	std::list<std::pair<HANDLE_COMMAND_FUNC, uint32> >	FuncNotifyList;
};

struct sCommand
{
	sCommandData		*m_pCommandData;
	std::vector<STRING> m_ValueVector;

	bool operator == (const sCommand &other) const
	{
		if(other.m_pCommandData != m_pCommandData) return false;
		if(other.m_ValueVector.size() != m_ValueVector.size()) return false;

		for(auto i = 0; i < m_ValueVector.size(); i++)
		{
			if(m_ValueVector[i] != other.m_ValueVector[i]) return false;
		}
		return true;
	}
};
#endif /* _GAME_COMMAND_DEFINE_H_ */

/*
 * �޸ļ�¼�� 080305 GCD_GUILD_INVITE_OBJECT 080306 GCD_GUILD_NOTIFY_INTIVE
 * GCD_GUILD_INTIVE_CONFIRM GCD_GUILD_MODIFY_TITLE 080308 GCD_GUILD_CREATE_FAMILY
 * GCD_GUILD_CREATE_FAMILY_CONFIRM GCD_GUILD_DESTORY_FAMILY_CONFIRM 080314
 * GCD_OPEN_FRIEND_SEARCH 080318 GCD_FRIEND_CREATE_GROUP 080319
 * GCD_OPEN_FRIEND_SEARCH_REASON 080320 GCD_OPEN_BUY_CONFIRM 080320
 * GCD_OPEN_SALE_CONFIRM 080324 GCD_QUICK_CHANGCD_NAME 080325 GCD_ADD_GROUP 080327
 * GCD_ITEM_LINK 080331 GCD_SHOW_TITLE GCD_UPDATE_TITLE 080402
 * GCD_SHOW_FRIEND_INFO 080407 GCD_PERSONAL_MESSAGE // ������Ϣ GCD_SYSTEM_MESSAGE
 * // ϵͳ��Ϣ GCD_SHOW_SYSTEM_PROMPT 080410 GCD_SHOW_SUPERTOOLTIP_TITLE, //
 * ��ʾ�ƺ���ʾ GCD_RICH_SAFE_GUARD, // ������Χ���� GCD_RICH_SAFE_TIME, //
 * ��ȫʱ�޵������� GCD_RICH_SET_PASSWORD, // �������롢�޸��������
 * GCD_RICH_SETUP, // �Ʋ������������ý��� GCD_UNITE_GF_SHOW 080418
 * GCD_INPUT_PASSWD_COMMAND 080331 GCD_OPEN_DAY_TIPS GCD_UPDATE_DAYTIPS_TIME
 * GCD_UPDATE_DAY_TIPS GCD_UPDATE_CALENDAR GCD_OPEN_TOP_LIST 080410
 * GCD_UPDATE_TOP_LIST 080417 GCD_OPEN_QUEST_SCOUT GCD_UPDATE_QUEST_SCOUT
 * 080331 GCD_OPEN_DAY_TIPS GCD_UPDATE_DAYTIPS_TIME GCD_UPDATE_DAY_TIPS
 * GCD_UPDATE_CALENDAR GCD_OPEN_TOP_LIST 080410 GCD_UPDATE_TOP_LIST 080417
 * GCD_OPEN_QUEST_SCOUT GCD_UPDATE_QUEST_SCOUT 080421 GCD_OPEN_BANK_EVENT
 * GCD_QUEST_INPUT_PASSWD_COMMAND GCD_PACKET_OPEN_SALE GCD_COUNTRY_MANAGER_INFO,
 * // ������Ϣ GCD_COUNTRY_MANAGER_ADJUST_AUTH, // ���ҹ�ְ���� 080422
 * GCD_INPUT_COUNTRY_DLG GCD_COUNTRY_KING_CREATE_CONFIRM 080425
 * GCD_COUNTRY_MANAGER_CREATE_KING GCD_COUNTRY_MANAGER_REQUEST_INFO 080516
 * GCD_FILL_TEAM_MEMBER, // ����Ա��Ϣ GCD_FILL_TEAM_INFO, // ��������Ϣ
 * 080519 GCD_GUILD_KICK_CONFIRM, // �������ȷ�� 080521 GCD_KEYBOARD_SET_KEY, //
 * ���ü�ֵ 080522 GCD_KEYBOARD_SET_REPEAT GCD_KEYBOARD_SWAP_KEY
 * GCD_EXTEND_SHORTCUT_SHOW, // ��չ����� GCD_GUAJI_SHOW, // �һ����� 080520
 * GCD_MOUNT_FRIEND_SETUI_SHOW //��������趨�����¼� 080521
 * GCD_QUESTLOG_AUTO_FIND_PATH, // �Զ�Ѱ·����NPC�Ի� 080603 GCD_CHAT_INPUT_STATE
 * // ���������״̬ 080606 GCD_SCENE_NAME_TIP 080711 GCD_NAME_INPUT_ERROR, //
 * ��������ֲ��Ϸ� GCD_NAME_INPUT_EMPTY, // ���������Ϊ�� 080721
 * GCD_RICH_SAFE_TIME_TIP, // ��ȫʱ����ʾ 080801 GCD_TOGLE_VALIDATE //
 * ��|�رշ������֤���� GCD_UPDATE_VALIDATE // ���·������֤���� 080805
 * GCD_QUIT_GAME_CONFIRM // �˳���Ϸȷ�� 080812 GCD_SEND_MOOD_ANIM, //
 * ���ͱ��鶯�� GCD_PARALLEL_MESSAGE, // ˮƽ��Ϣ 081010 GCD_QUICK_UPDATE_FRAME //
 * �ػ�һ����װ���� GCD_RICH_SAFE_GUARD_CLEAR //�����ܱ�
 */
