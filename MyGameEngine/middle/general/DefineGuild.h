#ifndef __GAMEDEFINE_GUILD_H__
#define __GAMEDEFINE_GUILD_H__

#define MAX_NUM_PER_POSITION			20
#define GUILD_CREATE_LEVEL_LIMIT		20
#define GUILD_CREATE_MONEY_LIMIT		500000
#define GUILD_CREATE_ITEM_INDEX			11990001
#define GUILD_REJOIN_TIME_LIMIT			24 * 3600
#define GUILD_FAMILY_USER_MAX			20
#define GUILD_NORMAL_FAMILY_SIZE		12
#define MAX_GUILD_USER_POINT			99999
#define MAX_GUILD_TOTAL_POINT			9999999

#define MAX_RECRUIT_WAIT_TIME			30 * 1000

#define MAX_CONVOY_WAIT_TIME			30 * 1000

#define MAX_GUILD_QUEST_NUM			256

#define TRIATHLON_BUF1				7501
#define TRIATHLON_BUF2				7502
#define TRIATHLON_BUF3				7503

#define GUILD_SEND_MAIL_MAX_DAY_COUNT 20 //����ÿ��Ⱥ���ʼ���������


enum GUILD_PARAM
{
	GD_GUILD_INDEX_YUNBIAO_SSUE_TIME    = 0,			//������ڷ���ʱ��
	GD_GUILD_INDEX_YUNBIAO_STATE        = 1,     		//�������״̬
	GD_GUILD_INDEX_YUNBIAO_ACCEPT_TIME  = 2,  			//������ڽ���ʱ��
	GD_GUILD_INDEX_KILL_ISSUE_TIME      = 3,			//���ɱ�ֵķ���ʱ��
	GD_GUILD_INDEX_GATHER_ISSUE_TIME    = 4,			//���ɼ��ķ���ʱ��
	GD_GUILD_INDEX_BATTLE_SINGUP 		= 5,			//���ս�������ݣ�����ǰ����
	GD_GUILD_INDEX_BATTL_STATE			= 6,			//���ս״̬ 0���ѽ�����1�������� ,-1δ��ʼ
	GD_GUILD_INDEX_BATTLE_WIN_NUM		= 7,			//���ս��ʤ����
	GD_GUILD_INDEX_BATTLE_LOSE_NUM		= 8,			//���սʧ�ܳ���
	GD_GUILD_INDEX_BATTLE_DEUCE_NUM		= 9,			//���սƽ�ֳ���
	GD_GUILD_INDEX_BATTL_SINGUP_RESULT	=10,			//���ս�����Ƿ�ɹ� ������������
	GD_GUILD_INDEX_SHOPACTIVE_PARAM0	=11,
	GD_GUILD_INDEX_SHOPACTIVE_PARAM1	=12,
	GD_GUILD_INDEX_SHOPACTIVE_PARAM2	=13,
	GD_GUILD_INDEX_SHOPACTIVE_PARAM3	=14,
	GD_GUILD_INDEX_TURN_NUMBER			=15,			//����������ִ�����
	GD_GUILD_INDEX_WORLDCUP_FLAG		=16,
	GD_GUILD_INDEX_LAST_RESULT			=17,
	GD_GUILD_INDEX_LAST_GB_SCORE		=18,
	GD_GUILD_INDEX_ADDEXP_DATE			=19,			//��Ὠ�裨ѭ�����ϴ����Ӱ�ᾭ������
	GD_GUILD_INDEX_ADDEXP_VALUE			=20,			//��Ὠ�裨ѭ�����������Ӱ�ᾭ�����
	GD_GUILD_INDEX_CONTEND_STATE		=21,			//���������״̬
	GD_GUILD_INDEX_CONVOKE_COUNT		=22,			//����ټ���������ÿСʱ����
	GD_GUILD_INDEX_CONVOKE_DAY			=23,			//����ټ�ʱ�䣨�ѷ��� by Jianghx 2009.11.26��
	GD_GUILD_INDEX_CONTEND_WIN_COUNT    =24,			//���������ȡʤ����
	GD_GUILD_INDEX_CONTEND_LOSE_COUNT   =25,			//���������ʧ������
	GD_GUILD_INDEX_MINISTER_GUILD_DATE	=26,			//���Ҵ�ս��̨�İ��
	GD_GUILD_INDEX_VIP_COLLECT_COUNT	=27,			//���VIPļ����������Ҫÿ������
	GD_GUILD_INDEX_GET_MONEY_COUNT		=28,			//�����Ǯ(�淨)��������Ҫÿ������
	GD_GUILD_MULTI_MISSION_HUSHOU		=29,			//���౶����(����)����ÿ������
	GD_GUILD_MULTI_MISSION_HEIMU		=30,			//���౶����(��ľ)����ÿ������
	GD_GUILD_MULTI_MISSION_ANZHAN		=31,			//���౶����(��ս)����ÿ������
	GD_GUILD_MULTI_MISSION_CHUYAO		=32,			//���౶����(����)����ÿ������
	GD_GUILD_MULTI_MISSION_MUJI			=33,			//���౶����(ļ��)����ÿ������
	GD_GUILD_MULTI_MISSION_TODAY		=34,			//���շ����İ��౶������Ҫÿ������
	GD_GUILD_CHIEF_MULTIMISSION_DAY		=35,			//������ȡ�౶����������
	GD_GUILD_ASSCHIEF_MULTIMISSION_DAY	=36,			//��������ȡ�౶����������
    GD_GUILD_WORLDCUP_TITLE_TIME        =37,            //���籭ͷ���ƺű���ʱ��
	GD_GUILD_LAIRDBATTLE_SCENEID		=38,			//�ݵ��ػ�ռ��ĳ���
	GD_GUILD_INDEX_YUNBIAO_RING_MIS_TIME=39,  			//������ڻ��������ʱ��
	GD_GUILD_LAIRDBATTLE_DATE			=40,			//�ݵ��ػ�ռ�������

	GD_GUILD_ACTIVITY_PARAM1			=41,			//����Ծ�Ȳ���1
	GD_GUILD_ACTIVITY_PARAM2			=42,			//����Ծ�Ȳ���2
	GD_GUILD_ACTIVITY_PARAM3			=43,			//����Ծ�Ȳ���3
	GD_GUILD_ACTIVITY_PARAM4			=44,			//����Ծ�Ȳ���4
	GD_GUILD_ACTIVITY_PARAM5			=45,			//����Ծ�Ȳ���5
	GD_GUILD_ACTIVITY_PARAM6			=46,			//����Ծ�Ȳ���6
	GD_GUILD_ACTIVITY_PARAM7			=47,			//����Ծ�Ȳ���7
	GD_GUILD_ACTIVITY_PARAM8			=48,			//����Ծ�Ȳ���8

	GD_GUILD_LAIRDBATTLE_REDEEM_DATE	=49,			//�ݵ��ػ���ȡ��ؽ�Ǯʱ��
	GD_GUILD_LAIRDBATTLE_LEVEL			=50,			//�ݵ��ػ����ɵȼ�

    GD_GUILD_HANDIN_DATE                = 51,           // ����������
    GD_GUILD_HANDIN_MONEY               = 52,           // ���ÿ�վ�����

	GD_GUILD_LAIRDBATTLE_CURRENT_EXP	= 53,			//�ݵ��ᵱǰ����
	
	GD_GUILD_LASTMONTH_GUILD_MEMBER_MONEY 	= 54,		//����Ա���µ����ѽ��
	GD_GUILD_CURMONTH_GUILD_MEMBER_MONEY	= 55,		//����Ա���µ����ѽ��
	GD_GUILD_LASTMONTH					  	= 56,		//������µ�����
	GD_GUILD_CURMONTH                       = 57,		//��᱾�µ�����

	GD_GUILD_SENDMAIL_DATE					= 58,		//����Ⱥ���ʼ�������
	GD_GUILD_SENDMAIL_COUNT				    = 59,		//����Ⱥ���ʼ��Ĵ���

	GD_GUILD_CASHBOX_SKILL_STATR			= 60,		// ������޼��ܿ�ʼ
	GD_GUILD_CASHBOX_SKILL_END				= 100,		// ������޼��ܽ��� 

	GD_GUILD_MAX_COUNT
};


enum eGuildQuestState { eGuildQuestState_None = -1, eGuildQuestState_Doing, eGuildQuestState_Finished, eGuildQuestState_NUMBER, };

//��Ụ�����޲���
enum GUILD_CONVOY_RESULT
{
	GUILD_CONVOY_RET_MEMBER_OABANDON= 0,				//���ڷ������񣬰��������Զ�����
	GUILD_CONVOY_RET_KICK,								//�����ߵ����ڣ����������Զ�����
	GUILD_CONVOY_RET_LEADER_OABANDON,					//�����������������Զ�����
	GUILD_CONVOY_RET_DEMISE,							//��������������Զ�����
	GUILD_CONVOY_RET_DESTORY,							//����ɢ�������Զ�����
	GUILD_CONVOY_RET_DIED,								//�ڳ������������Զ�����
	GUILD_CONVOY_RET_WAIT_TIMEOUT,						//�ڳ��ȴ���ʱ�������Զ�����
	GUILD_CONVOY_RET_LIFE_TIMEOUT,						//�ڳ�������ʱ�������Զ�����
	GUILD_CONVOY_RET_MEMBER_ENTER,						//��������
	GUILD_CONVOY_RET_MEMBER_LEAVE,						//�����뿪��ᣬ���������Զ�����
	GUILD_CONVOY_RET_FAILED,							//����ʧ��
	GUILD_CONVOY_RET_SUCCEED,							//����ɹ�
	GUILD_CONVOY_RET_MEMBER_OFFLINE,					//�������
	GUILD_CONVOY_RET_MEMBER_ONLINE,						//�������
	GUILD_CONVOY_RET_QUEST_NONE,						//�������ʱ��ѯ��Ụ�����񣺷���û�д�����
	GUILD_CONVOY_RET_NOT_MEMBER,						//��Ҳ��ǰ���Ա
	GUILD_CONVOY_RET_OUT_RANGE,							//��ҳ�����Ч����
	GUILD_CONVOY_RET_LEADER_BE_DELATED,					//����������������ʧ��
	GUILD_CONVOY_RET_CLEARBUS,							//����ɾ���ڳ�
	GUILD_CONVOY_RETNUMBER,
};

enum eGUILD_STATUS_CODE { GUILD_STATUS_INVALID = 0, GUILD_STATUS_NORMAL, };

enum POSITION_DESC
{
	POSITION_Country_King			=0,					//����
	POSITION_Country_Queen			=1,					//����
	POSITION_Country_General		=2,					//�󽫾�
	POSITION_Country_LMinister		=3,					//����
	POSITION_Country_RMinister		=4 ,				//����
	POSITION_Country_LGuard			=5,					//���ػ�
	POSITION_Country_RGuard			=6,					//���ػ�
	POSITION_Country_Guards			=7,					//��������
	POSITION_Guild_CHIEFTAIN		=8,					//����
	POSITION_Guild_ASS_CHIEFTAIN	=9,					//������
	POSITION_Guild_FAMILY_BOSS		=10,				//���峤
	POSITION_Guild_ELITE_MEMBER		=11,				//��Ӣ����
	POSITION_Guild_MEMBER			=12,				//��ͨ����
	POSITION_NORMAL					=13,				//��ͨ����
	POSITION_Country_Qinglong		=14,				//����֮��
	POSITION_Country_Zhuque			=15,				//��ȸ֮��
};

enum eGUILD_POSITION_TYPE
{
	GUILD_POSITION_INVALID		= -1,
	GUILD_POSITION_TRAINEE		= 0,
	GUILD_POSITION_MEMBER		= 1,
	GUILD_POSITION_ELITE_MEMBER	= 2,
	GUILD_POSITION_FAMILY_BOSS	= 3,
	GUILD_POSITION_ASS_CHIEFTAIN	= 4,
	GUILD_POSITION_CHIEFTAIN	= 5,
	GUILD_POSITION_SIZE,
};

enum eGUILD_AUTHORITY_DEFINE
{
	GUILD_AUTHORITY_INVALID		= -1,
	GUILD_AUTHORITY_ASSIGN		= 0,
	GUILD_AUTHORITY_AUTHORIZE	= 1,
	GUILD_AUTHORITY_RECRUIT		= 2,
	GUILD_AUTHORITY_EXPEL		= 3,
	GUILD_AUTHORITY_DEMISE		= 4,
	GUILD_AUTHORITY_WITHDRAW	= 5,
	GUILD_AUTHORITY_DEPOSIT		= 6,
	GUILD_AUTHORITY_LEAVE		= 7,
	GUILD_AUTHORITY_DIMISS		= 8,
	GUILD_AUTHORITY_ADDFAMILYUSER	= 9,
	GUILD_AUTHORITY_DELFAMILYUSER	= 10,
	GUILD_AUTHORITY_LEVELUP		= 11,
	GUILD_AUTHORITY_CREATEFAMILY	= 12,
	GUILD_AUTHORITY_MODIFY_TITLE	= 13,
	GUILD_AUTHORITY_DIMISS_FAMILY	= 14,
	GUILD_AUTHORITY_MODIFY_DESC	= 15,
	GUILD_AUTHORITY_INVITE		= 16,
	GUILD_AUTHORITY_MOVE_MEMBER	= 17,
	GUILD_AUTHORITY_APPOINTPOS	= 18,
	GUILD_AUTHORITY_CANCELPOS	= 19,
	GUILD_AUTHORITY_ABDICATE	= 20,
	GUILD_AUTHORITY_MODIFYFAMILYNAME= 21,
	GUILD_AUTHORITY_PROPERTY = 22,
	GUILD_AUTHORITY_ACTIVITYPARAM = 23,
	GUILD_AUTHORITY_NUMBER,
};

enum eGUILD_RETURN_CODE
{
	GUILD_RETURN_INVALID		= -1,
	GUILD_RETURN_CREATE,
	GUILD_RETURN_RESPONSE,
	GUILD_RETURN_JOIN,
	GUILD_RETURN_INVIT,
	GUILD_RETURN_PROMOTE,
	GUILD_RETURN_DEMOTE,
	GUILD_RETURN_AUTHORIZE,
	GUILD_RETURN_DEPRIVE_AUTHORITY,
	GUILD_RETURN_RECRUIT,
	GUILD_RETURN_EXPEL,
	GUILD_RETURN_DEMISE,
	GUILD_RETURN_WITHDRAW,
	GUILD_RETURN_DEPOSIT,
	GUILD_RETURN_LEAVE,
	GUILD_RETURN_REJECT,
	GUILD_RETURN_FOUND,
	GUILD_RETURN_DISMISS,
	GUILD_RETURN_CHANGEDESC,
	GUILD_RETURN_NAME,
	GUILD_RETURN_CREATE_FAILED,
	GUILD_RETURN_CREATE_FAMILY,
	GUILD_RETURN_ADD_FAMILY_USER,
	GUILD_RETURN_REMOVE_FAMILY_USER,
	GUILD_RETURN_MODIFY_DESC,
	GUILD_RETURN_FAMILY_DISMISS,
	GUILD_RETURN_BEADD_FAMILY,
	GUILD_RETURN_LEVEL_UP,
	GUILD_RETURN_ALREADY_IN,
	GUILD_RETURN_ERASE_ITEM_FAIL,
	GUILD_RETURN_POSITION_CHANGED,
	GUILD_RETURN_SIZE,
	GUILD_RETURN_SKILL_LEVEL_UP,
	GUILD_RETURN_BUS_SKILL_LEVEL_UP,
};

enum eGUILD_ERROR_CODE
{
	GUILD_ERROR_NOTHING		= 0,
	GUILD_ERROR_WANTING		= -1,
	GUILD_ERROR_INVALID_NAME	= -2,
	GUILD_ERROR_DUPLICATED_NAME	= -3,
	GUILD_ERROR_GUILD_FULL		= -4,
	GUILD_ERROR_MEMBER_FULL		= -5,
	GUILD_ERROR_PROPOSER_FULL	= -6,
	GUILD_ERROR_IN_GUILD		= -7,
	GUILD_ERROR_NOT_EXIST		= -8,
	GUILD_ERROR_UNAUTHORIZED	= -9,
	GUILD_ERROR_NO_VACANCY		= -10,
	GUILD_ERROR_NO_QUALIFICATION	= -11,
	GUILD_ERROR_CASHBOX_FULL	= -12,
	GUILD_ERROR_ALREADY_MEMBER	= -13,
	GUILD_ERROR_MEMBER_NOT_EXIST	= -14,
	GUILD_ERROR_NO_ASS_CHIEF	= -15,
	GUILD_ERROR_GUILD_ALREADY_EXIST = -16,
	GUILD_ERROR_POS_FULL		= -17,
	GUILD_ERROR_LEVEL_TOO_LOW	= -18,
	GUILD_ERROR_LEVEL_TO_JOIN	= -19,
	GUILD_ERROR_PASSWORD		= -20,
	GUILD_ERROR_WAITTING		= -21,
	GUILD_ERROR_FAMILY_DIMISS	= -22,
	GUILD_ERROR_CANNOT_LEAVE	= -23,
	GUILD_ERROR_FAIL		= -24,
	GUILD_ERROR			= -64,
};

enum eGUILD_PACKET_TYPE
{
	GUILD_PACKET_INVALID			= -1,

	//------- CX��Ϣ��1����ͨ��"XG��Ϣ��1"��Ӧ����Ϣ����ת��
	GUILD_PACKET_CX_ASKLIST,
	GUILD_PACKET_CX_CREATE,
	GUILD_PACKET_CX_JOIN,
	GUILD_PACKET_CX_ASKINFO,
	GUILD_PACKET_CX_APPOINT,
	GUILD_PACKET_CX_ADJUSTAUTHORITY,
	GUILD_PACKET_CX_RECRUIT,
	GUILD_PACKET_CX_EXPEL,
	GUILD_PACKET_CX_WITHDRAW,
	GUILD_PACKET_CX_DEPOSIT,
	GUILD_PACKET_CX_LEAVE,
	GUILD_PACKET_CX_DISMISS,
	GUILD_PACKET_CX_DEMISE,
	GUILD_PACKET_CX_CHANGEDESC,
	GUILD_PACKET_CX_INVITE,
	GUILD_PACKET_CX_INVITE_CONFIRM,
	GUILD_PACKET_CX_CREATE_FAMILY,
	GUILD_PACKET_CX_ADD_FAMILY_USER,
	GUILD_PACKET_CX_REMOVE_FAMILY_USER,
	GUILD_PACKET_CX_MODIFY_DESC,
	GUILD_PACKET_CX_MODIFY_ACTIVITY_PARAM,
	GUILD_PACKET_CX_MODIFY_TITLE_NAME,
	GUILD_PACKET_CX_FAMILY_DISMISS,
	GUILD_PACKET_CX_LEVELUP,
	GUILD_PACKET_CX_MOVE_MEMBER,
	GUILD_PACKET_CX_ABDICATE,
	GUILD_PACKET_CX_APPOINT_POS,
	GUILD_PACKET_CX_CANCEL_POS,
	GUILD_PACKET_CX_ASKMEMBERLIST,
	GUILD_PACKET_CX_ADD_GEXP,
	GUILD_PACKET_CX_SUB_GEXP,
	GUILD_PACKET_CX_LEVEL_INFO,
	GUILD_PACKET_CX_SET_GP,
	GUILD_PACKET_CX_MODIFYFAMILYNAME,
	GUILD_PACKET_CX_GUILDSTRENGTH,
	GUILD_PACKET_CX_CONVOKE_CONFIRM,
	GUILD_PACKET_CX_DELATE_VOTE,
	GUILD_PACKET_CX_UPDATESKILLLEVEL,
	GUILD_PACKET_CX_BUS_SKILLUP,
	GUILD_PACKET_CX_ASKLAIRDDATA,
	// End CX��Ϣ��1

	GUILD_PACKET_CX_XG_SEPARATOR,
	
	//------- XG��Ϣ��1
	GUILD_PACKET_XG_ASKLIST,
	GUILD_PACKET_XG_CREATE,
	GUILD_PACKET_XG_JOIN,
	GUILD_PACKET_XG_ASKINFO,
	GUILD_PACKET_XG_APPOINT,
	GUILD_PACKET_XG_ADJUSTAUTHORITY,
	GUILD_PACKET_XG_RECRUIT,
	GUILD_PACKET_XG_EXPEL,
	GUILD_PACKET_XG_WITHDRAW,
	GUILD_PACKET_XG_DEPOSIT,
	GUILD_PACKET_XG_LEAVE,
	GUILD_PACKET_XG_DISMISS,
	GUILD_PACKET_XG_DEMISE,
	GUILD_PACKET_XG_CHANGEDESC,
	GUILD_PACKET_XG_INVITE,
	GUILD_PACKET_XG_INVITE_CONFIRM,
	GUILD_PACKET_XG_CREATE_FAMILY,
	GUILD_PACKET_XG_ADD_FAMILY_USER,
	GUILD_PACKET_XG_REMOVE_FAMILY_USER,
	GUILD_PACKET_XG_MODIFY_DESC,
	GUILD_PACKET_XG_MODIFY_ACTIVITY_PARAM,
	GUILD_PACKET_XG_MODIFY_TITLE_NAME,
	GUILD_PACKET_XG_FAMILY_DISMISS,
	GUILD_PACKET_XG_LEVELUP,
	GUILD_PACKET_XG_MOVE_MEMBER,
	GUILD_PACKET_XG_ABDICATE,
	GUILD_PACKET_XG_APPOINT_POS,
	GUILD_PACKET_XG_CANCEL_POS,
	GUILD_PACKET_XG_ASKMEMBERLIST,
	GUILD_PACKET_XG_ADD_GEXP,
	GUILD_PACKET_XG_SUB_GEXP,
	GUILD_PACKET_XG_LEVEL_INFO,
	GUILD_PACKET_XG_SET_GP,
	GUILD_PACKET_XG_MODIFYFAMILYNAME,
	GUILD_PACKET_XG_GUILDSTRENGTH,
	GUILD_PACKET_XG_CONVOKE_CONFIRM,
	GUILD_PACKET_XG_DELATE_VOTE,
	GUILD_PACKET_XG_UPDATESKILLLEVEL,
	GUILD_PACKET_XG_BUS_UPDATESKILL,
	// End XG��Ϣ��1

	//------- XG��Ϣ��2������Ҫת��
	GUILD_PACKET_XG_SCRIPT_CALLBACK,
	GUILD_PACKET_XG_SETFREEPARAM,
	GUILD_PACKET_XG_CONVOKE,
	GUILD_PACKET_XG_MEMBER_JOINTIME,
	GUILD_PACKET_XG_LEVELDOWN,
	GUILD_PACKET_XG_SET_SHIMING,
	GUILD_PACKET_XG_ADD_MERIT,
	GUILD_PACKET_XG_ADD_MEMBER_VALUE,
	GUILD_PACKET_XG_ADD_MONEY,
	GUILD_PACKET_XG_SET_MULTIMISSION,
    GUILD_PACKET_XG_CHANGEPROFESSION,   // ����Աְҵ�����仯
	// End XG��Ϣ��2
	
	GUILD_PACKET_XG_GX_SEPARATOR,
	
	//------- GX��Ϣ��1����ͨ��"XC��Ϣ��1"��Ӧ����Ϣ����ת��
	GUILD_PACKET_GX_LIST,
	GUILD_PACKET_GX_MEMBER_LIST,
	GUILD_PACKET_GX_GUILD_INFO,
	GUILD_PACKET_GX_APPOINT_INFO,
	GUILD_PACKET_GX_SELF_GUILD_INFO,
	GUILD_PACKET_GX_CONFIRM_GUILD_INVITE,
	GUILD_PACKET_GX_MODIFY_TITLE_NAME,
	GUILD_PACKET_GX_GUILDSTRENGTH,
	GUILD_PACKET_GX_CONVOKE,
	GUILD_PACKET_GX_DELATE_BROADCAST,
	GUILD_PACKET_GX_SET_MULTIMISSION,
	GUILD_PACKET_GX_SYNC_LAIRDINFO,
	GUILD_PACKET_GX_SYNC_SKILL_INFO,
	// End GX��Ϣ��1

	//------- GX��Ϣ��2������Ҫת��
	GUILD_PACKET_GX_CONVOKE_SUCCESS,
	GUILD_PACKET_GX_ADD_GP,
	GUILD_PACKET_GX_SUB_GP,
	GUILD_PACKET_GX_SCRIPT_CALLBACK,
	GUILD_PACKET_GX_SET_MEMBER_GP,
	GUILD_PACKET_GX_REFRESH_MEMBER_INFO, //ͬ��һ��GuildMember����Ϣ��Map
	GUILD_PACKET_GX_REFRESH_ALL_MEMBER_INFO, //ͬ������GuildMember����Ϣ��Map
	GUILD_PACKET_GX_MEMBER_JOINTIME,
	GUILD_PACKET_GX_SET_MEMBER_MERIT,
	GUILD_PACKET_GX_SKILL,					//ͬ��һ���������ݵ�Map
	GUILD_PACKET_GX_SKILL_ALL,					//ͬ�����м������ݵ�Map
	// End GX��Ϣ��2
	
	GUILD_PACKET_GX_XC_SEPARATOR,

	//------- XC��Ϣ��1
	GUILD_PACKET_XC_LIST,
	GUILD_PACKET_XC_MEMBER_LIST,
	GUILD_PACKET_XC_GUILD_INFO,
	GUILD_PACKET_XC_APPOINT_INFO,
	GUILD_PACKET_XC_SELF_GUILD_INFO,
	GUILD_PACKET_XC_CONFIRM_GUILD_INVITE,
	GUILD_PACKET_XC_MODIFY_TITLE_NAME,
	GUILD_PACKET_XC_GUILDSTRENGTH,
	GUILD_PACKET_XC_CONVOKE,
	GUILD_PACKET_XC_DELATE_BROADCAST,
	GUILD_PACKET_XC_SET_MULTIMISSION,
	GUILD_PACKET_XC_SYNC_LAIRDINFO,
	GUILD_PACKET_XC_SYNC_SKILL_INFO,
	// End XC��Ϣ��1

	//------- XC��Ϣ��2
	GUILD_PACKET_XC_FAMILY_DISMISS,
	// End XC��Ϣ��2

	GUILD_PACKET_CX_SEND_MAIL,  //����Ⱥ���ʼ�
	GUILD_PACKET_XG_SEND_MAIL,	//����Ⱥ���ʼ�
};

enum E_GUILD_DELATE_RET
{
	GDR_SUCCESS				= 0,
	GDR_CANNOT_DELATE_YOURSELF,
	GDR_ALREADY_DELATING,
	GDR_CANNOT_DELATE_KING,
	GDR_NEED_MORE_ONLINE_MEMBER,
	GDR_CANNOT_DELATE_QINGLONG,
	GDR_CANNOT_DELATE_ZHUQUE,
	GDR_UNKNOW
};

enum E_GUILD_DELATE_VOTE_RET { GDVR_SUCCESS = 0, GDVR_DELATING_OVER, GDVR_CANNOT_DELATE_OTHER_PERSON, GDVR_UNKNOW };
#endif