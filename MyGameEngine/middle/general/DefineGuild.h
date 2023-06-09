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

#define GUILD_SEND_MAIL_MAX_DAY_COUNT 20 //帮主每日群发邮件的最大次数


enum GUILD_PARAM
{
	GD_GUILD_INDEX_YUNBIAO_SSUE_TIME    = 0,			//帮会运镖发布时间
	GD_GUILD_INDEX_YUNBIAO_STATE        = 1,     		//帮会运镖状态
	GD_GUILD_INDEX_YUNBIAO_ACCEPT_TIME  = 2,  			//帮会运镖接受时间
	GD_GUILD_INDEX_KILL_ISSUE_TIME      = 3,			//帮会杀怪的发布时间
	GD_GUILD_INDEX_GATHER_ISSUE_TIME    = 4,			//帮会采集的发布时间
	GD_GUILD_INDEX_BATTLE_SINGUP 		= 5,			//帮会战报名数据：报名前请求
	GD_GUILD_INDEX_BATTL_STATE			= 6,			//帮会战状态 0：已结束，1：进行中 ,-1未开始
	GD_GUILD_INDEX_BATTLE_WIN_NUM		= 7,			//帮会战获胜场次
	GD_GUILD_INDEX_BATTLE_LOSE_NUM		= 8,			//帮会战失败场次
	GD_GUILD_INDEX_BATTLE_DEUCE_NUM		= 9,			//帮会战平局场次
	GD_GUILD_INDEX_BATTL_SINGUP_RESULT	=10,			//帮会战报名是否成功 ：报名后请求
	GD_GUILD_INDEX_SHOPACTIVE_PARAM0	=11,
	GD_GUILD_INDEX_SHOPACTIVE_PARAM1	=12,
	GD_GUILD_INDEX_SHOPACTIVE_PARAM2	=13,
	GD_GUILD_INDEX_SHOPACTIVE_PARAM3	=14,
	GD_GUILD_INDEX_TURN_NUMBER			=15,			//帮会争霸赛轮次数据
	GD_GUILD_INDEX_WORLDCUP_FLAG		=16,
	GD_GUILD_INDEX_LAST_RESULT			=17,
	GD_GUILD_INDEX_LAST_GB_SCORE		=18,
	GD_GUILD_INDEX_ADDEXP_DATE			=19,			//帮会建设（循环）上次增加帮会经验日期
	GD_GUILD_INDEX_ADDEXP_VALUE			=20,			//帮会建设（循环）当日增加帮会经验计数
	GD_GUILD_INDEX_CONTEND_STATE		=21,			//帮会争霸赛状态
	GD_GUILD_INDEX_CONVOKE_COUNT		=22,			//帮会召集次数，需每小时清零
	GD_GUILD_INDEX_CONVOKE_DAY			=23,			//帮会召集时间（已废弃 by Jianghx 2009.11.26）
	GD_GUILD_INDEX_CONTEND_WIN_COUNT    =24,			//帮会争霸赛取胜计数
	GD_GUILD_INDEX_CONTEND_LOSE_COUNT   =25,			//帮会争霸赛失利计数
	GD_GUILD_INDEX_MINISTER_GUILD_DATE	=26,			//国家大战下台的帮会
	GD_GUILD_INDEX_VIP_COLLECT_COUNT	=27,			//帮会VIP募集次数，需要每日清零
	GD_GUILD_INDEX_GET_MONEY_COUNT		=28,			//帮会跑钱(玩法)次数，需要每日清零
	GD_GUILD_MULTI_MISSION_HUSHOU		=29,			//帮会多倍任务(护兽)，需每周清零
	GD_GUILD_MULTI_MISSION_HEIMU		=30,			//帮会多倍任务(黑木)，需每周清零
	GD_GUILD_MULTI_MISSION_ANZHAN		=31,			//帮会多倍任务(暗战)，需每周清零
	GD_GUILD_MULTI_MISSION_CHUYAO		=32,			//帮会多倍任务(除妖)，需每周清零
	GD_GUILD_MULTI_MISSION_MUJI			=33,			//帮会多倍任务(募集)，需每周清零
	GD_GUILD_MULTI_MISSION_TODAY		=34,			//今日发布的帮会多倍任务，需要每日清零
	GD_GUILD_CHIEF_MULTIMISSION_DAY		=35,			//帮主领取多倍任务奖励日期
	GD_GUILD_ASSCHIEF_MULTIMISSION_DAY	=36,			//副帮主领取多倍任务奖励日期
    GD_GUILD_WORLDCUP_TITLE_TIME        =37,            //世界杯头顶称号保存时间
	GD_GUILD_LAIRDBATTLE_SCENEID		=38,			//据点守护占领的场景
	GD_GUILD_INDEX_YUNBIAO_RING_MIS_TIME=39,  			//帮会运镖环任务接受时间
	GD_GUILD_LAIRDBATTLE_DATE			=40,			//据点守护占领的日期

	GD_GUILD_ACTIVITY_PARAM1			=41,			//帮会活跃度参数1
	GD_GUILD_ACTIVITY_PARAM2			=42,			//帮会活跃度参数2
	GD_GUILD_ACTIVITY_PARAM3			=43,			//帮会活跃度参数3
	GD_GUILD_ACTIVITY_PARAM4			=44,			//帮会活跃度参数4
	GD_GUILD_ACTIVITY_PARAM5			=45,			//帮会活跃度参数5
	GD_GUILD_ACTIVITY_PARAM6			=46,			//帮会活跃度参数6
	GD_GUILD_ACTIVITY_PARAM7			=47,			//帮会活跃度参数7
	GD_GUILD_ACTIVITY_PARAM8			=48,			//帮会活跃度参数8

	GD_GUILD_LAIRDBATTLE_REDEEM_DATE	=49,			//据点守护领取领地金钱时间
	GD_GUILD_LAIRDBATTLE_LEVEL			=50,			//据点守护养成等级

    GD_GUILD_HANDIN_DATE                = 51,           // 帮会捐献日期
    GD_GUILD_HANDIN_MONEY               = 52,           // 帮会每日捐献数

	GD_GUILD_LAIRDBATTLE_CURRENT_EXP	= 53,			//据点帮会当前经验
	
	GD_GUILD_LASTMONTH_GUILD_MEMBER_MONEY 	= 54,		//帮会成员上月的消费金额
	GD_GUILD_CURMONTH_GUILD_MEMBER_MONEY	= 55,		//帮会成员本月的消费金额
	GD_GUILD_LASTMONTH					  	= 56,		//帮会上月的月数
	GD_GUILD_CURMONTH                       = 57,		//帮会本月的月数

	GD_GUILD_SENDMAIL_DATE					= 58,		//帮主群发邮件的日期
	GD_GUILD_SENDMAIL_COUNT				    = 59,		//帮主群发邮件的次数

	GD_GUILD_CASHBOX_SKILL_STATR			= 60,		// 帮会神兽技能开始
	GD_GUILD_CASHBOX_SKILL_END				= 100,		// 帮会神兽技能结束 

	GD_GUILD_MAX_COUNT
};


enum eGuildQuestState { eGuildQuestState_None = -1, eGuildQuestState_Doing, eGuildQuestState_Finished, eGuildQuestState_NUMBER, };

//帮会护送神兽操作
enum GUILD_CONVOY_RESULT
{
	GUILD_CONVOY_RET_MEMBER_OABANDON= 0,				//帮众放弃任务，帮众任务自动结束
	GUILD_CONVOY_RET_KICK,								//帮主踢掉帮众，帮众任务自动结束
	GUILD_CONVOY_RET_LEADER_OABANDON,					//帮主放弃任务，任务自动结束
	GUILD_CONVOY_RET_DEMISE,							//帮会消亡，任务自动结束
	GUILD_CONVOY_RET_DESTORY,							//帮会解散，任务自动结束
	GUILD_CONVOY_RET_DIED,								//镖车死亡，任务自动结束
	GUILD_CONVOY_RET_WAIT_TIMEOUT,						//镖车等待超时，任务自动结束
	GUILD_CONVOY_RET_LIFE_TIMEOUT,						//镖车生命超时，任务自动结束
	GUILD_CONVOY_RET_MEMBER_ENTER,						//接受任务
	GUILD_CONVOY_RET_MEMBER_LEAVE,						//帮众离开帮会，帮众任务自动结束
	GUILD_CONVOY_RET_FAILED,							//任务失败
	GUILD_CONVOY_RET_SUCCEED,							//任务成功
	GUILD_CONVOY_RET_MEMBER_OFFLINE,					//玩家离线
	GUILD_CONVOY_RET_MEMBER_ONLINE,						//玩家上线
	GUILD_CONVOY_RET_QUEST_NONE,						//玩家上线时查询帮会护兽任务：返回没有此任务
	GUILD_CONVOY_RET_NOT_MEMBER,						//玩家不是帮会成员
	GUILD_CONVOY_RET_OUT_RANGE,							//玩家超过有效距离
	GUILD_CONVOY_RET_LEADER_BE_DELATED,					//帮主被弹劾，任务失败
	GUILD_CONVOY_RET_CLEARBUS,							//上线删除镖车
	GUILD_CONVOY_RETNUMBER,
};

enum eGUILD_STATUS_CODE { GUILD_STATUS_INVALID = 0, GUILD_STATUS_NORMAL, };

enum POSITION_DESC
{
	POSITION_Country_King			=0,					//国王
	POSITION_Country_Queen			=1,					//王后
	POSITION_Country_General		=2,					//大将军
	POSITION_Country_LMinister		=3,					//左相
	POSITION_Country_RMinister		=4 ,				//右相
	POSITION_Country_LGuard			=5,					//左守护
	POSITION_Country_RGuard			=6,					//右守护
	POSITION_Country_Guards			=7,					//王者卫队
	POSITION_Guild_CHIEFTAIN		=8,					//帮主
	POSITION_Guild_ASS_CHIEFTAIN	=9,					//副帮主
	POSITION_Guild_FAMILY_BOSS		=10,				//家族长
	POSITION_Guild_ELITE_MEMBER		=11,				//精英帮众
	POSITION_Guild_MEMBER			=12,				//普通帮众
	POSITION_NORMAL					=13,				//普通国民
	POSITION_Country_Qinglong		=14,				//青龙之主
	POSITION_Country_Zhuque			=15,				//朱雀之主
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

	//------- CX消息组1，需通过"XG消息组1"对应的消息进行转发
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
	// End CX消息组1

	GUILD_PACKET_CX_XG_SEPARATOR,
	
	//------- XG消息组1
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
	// End XG消息组1

	//------- XG消息组2，不需要转发
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
    GUILD_PACKET_XG_CHANGEPROFESSION,   // 帮会成员职业发生变化
	// End XG消息组2
	
	GUILD_PACKET_XG_GX_SEPARATOR,
	
	//------- GX消息组1，需通过"XC消息组1"对应的消息进行转发
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
	// End GX消息组1

	//------- GX消息组2，不需要转发
	GUILD_PACKET_GX_CONVOKE_SUCCESS,
	GUILD_PACKET_GX_ADD_GP,
	GUILD_PACKET_GX_SUB_GP,
	GUILD_PACKET_GX_SCRIPT_CALLBACK,
	GUILD_PACKET_GX_SET_MEMBER_GP,
	GUILD_PACKET_GX_REFRESH_MEMBER_INFO, //同步一个GuildMember的信息到Map
	GUILD_PACKET_GX_REFRESH_ALL_MEMBER_INFO, //同步所有GuildMember的信息到Map
	GUILD_PACKET_GX_MEMBER_JOINTIME,
	GUILD_PACKET_GX_SET_MEMBER_MERIT,
	GUILD_PACKET_GX_SKILL,					//同步一个技能数据到Map
	GUILD_PACKET_GX_SKILL_ALL,					//同步所有技能数据到Map
	// End GX消息组2
	
	GUILD_PACKET_GX_XC_SEPARATOR,

	//------- XC消息组1
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
	// End XC消息组1

	//------- XC消息组2
	GUILD_PACKET_XC_FAMILY_DISMISS,
	// End XC消息组2

	GUILD_PACKET_CX_SEND_MAIL,  //帮主群发邮件
	GUILD_PACKET_XG_SEND_MAIL,	//帮主群发邮件
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
