
#pragma once



/* �ͻ���Ԥ��ָ����߼�������ֵ */
#define DEF_CLIENT_LOGIC_COUNT_ADD_STEP (1)

/* ��ɫλ��У���ľ��� */
#define DEF_CHARACTER_POS_ADJUST_DIST	(1.5f)

/* �ͻ��˷���ɫλ�ý�����Ϣ�ľ��뷧ֵ */
#define DEF_CLIENT_ADJUST_POS_WARP_DIST (DEF_SERVER_ADJUST_POS_WARP_DIST * 0.8f)

/* ����ս��״̬��Ҫ������ʱ�� */
#define FIGHT_STATE_DURATION_TIME	(8000)
#define DROP_ITEM_ROTE_ANGLE		2
#define DROP_ITEM_ADD_HEIGHT		1.0

/* ����������Ϣ���ͼ��ʱ�� */
#define PACKET_RESET_ITEM_TIME	(1)			/* ���� */

/* �ֿ�������Ϣ���ͼ��ʱ�� */
#define BANK_RESET_ITEM_TIME	(1)			/* ���� */

/* obj�߼�����ʱ�� */
#define OBJ_LOGIC_DIEOUT_TIME	(10 * 1000) /* ���� */

/* objʵ������ʱ�� */
#define OBJ_ENTITY_DIEOUT_TIME	(750)		/* ���� ����������� */
enum TERRAIN_TYPE
{
	GENERAL_TER = 1,						/* ��ͨ���� */
	GRASS_TER	= 2,						/* �ݵ� */
	GROUND_TER	= 4,						/* ���� */
	SNOW_TER	= 8,						/* ѩ�� */
	WATER_TER	= 16,						/* ˮ */
	ROCK_TER	= 32,						/* ʯͷ */
	COLLI_TER	= 64,						/* ������ */
};



/* ָ������ */
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
