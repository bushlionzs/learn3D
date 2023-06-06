
#pragma once



/* 客户端预测指令的逻辑计数加值 */
#define DEF_CLIENT_LOGIC_COUNT_ADD_STEP (1)

/* 角色位置校正的距离 */
#define DEF_CHARACTER_POS_ADJUST_DIST	(1.5f)

/* 客户端发角色位置较正消息的距离阀值 */
#define DEF_CLIENT_ADJUST_POS_WARP_DIST (DEF_SERVER_ADJUST_POS_WARP_DIST * 0.8f)

/* 进入战斗状态后要持续的时间 */
#define FIGHT_STATE_DURATION_TIME	(8000)
#define DROP_ITEM_ROTE_ANGLE		2
#define DROP_ITEM_ADD_HEIGHT		1.0

/* 背包整理消息发送间隔时间 */
#define PACKET_RESET_ITEM_TIME	(1)			/* 毫秒 */

/* 仓库整理消息发送间隔时间 */
#define BANK_RESET_ITEM_TIME	(1)			/* 毫秒 */

/* obj逻辑消亡时间 */
#define OBJ_LOGIC_DIEOUT_TIME	(10 * 1000) /* 毫秒 */

/* obj实体消亡时间 */
#define OBJ_ENTITY_DIEOUT_TIME	(750)		/* 毫秒 定义地面类型 */
enum TERRAIN_TYPE
{
	GENERAL_TER = 1,						/* 普通地面 */
	GRASS_TER	= 2,						/* 草地 */
	GROUND_TER	= 4,						/* 土地 */
	SNOW_TER	= 8,						/* 雪地 */
	WATER_TER	= 16,						/* 水 */
	ROCK_TER	= 32,						/* 石头 */
	COLLI_TER	= 64,						/* 行走面 */
};



/* 指令类型 */
enum OBJECT_COMMAND_TYPE
{
	OBJ_CMD_UNKOWN					= -1,
	OBJ_CMD_LOGIC_EVENT,
	OBJ_CMD_IDLE,
	OBJ_CMD_JUMP,
	OBJ_CMD_DEATH,
	OBJ_CMD_IMPACT,
	OBJ_CMD_PLAY_IMPACT,
	OBJ_CMD_ACTION,
	OBJ_CMD_STOP_ACTION,
	OBJ_CMD_MOVE,
	OBJ_CMD_STOP_MOVE,
	OBJ_CMD_SKILL_SEND,
	OBJ_CMD_SKILL_CHARGE,
	OBJ_CMD_GATHER_MODIFY,
	OBJ_CMD_SKILL_CHANNEL,
	OBJ_CMD_LEAD_MODIFY,
	OBJ_CMD_ABILITY,
	OBJ_CMD_ACTION_MODIFY,
	OBJ_CMD_TELEPORT,
	OBJ_CMD_TEAM_FLAG,
	OBJ_CMD_TEAM_FOLLOW_MEMBER,
	OBJ_CMD_UPDATE_TEAM_FOLLOW_FLAG,
	OBJ_CMD_TRAP_TRIGGER,
	OBJ_CMD_TRAP_DIE,
	OBJ_CMD_NUMBERS,
};
class	KObjectCmdDate
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:

	/*
	 ===================================================================================================================
	 ===================================================================================================================
	 */
	KObjectCmdDate(void)
	{
	}

	/*
	 ===================================================================================================================
	 ===================================================================================================================
	 */
	virtual~KObjectCmdDate(void)
	{
	}

	/*
	 ===================================================================================================================
	 ===================================================================================================================
	 */
	virtual void Clear(void)
	{
	}

	/*
	 ===================================================================================================================
	 ===================================================================================================================
	 */
	virtual int32 GetCmdType()
	{
		return OBJ_CMD_UNKOWN;
	}
};
struct ObjectCmd;

void DelObjectCmd(KObjectCmdDate *pCmd);
