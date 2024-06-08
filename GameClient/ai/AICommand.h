
/* AICommandDef.h */
#pragma once
enum AI_COMMAND
{
	AI_CMD_UNKOWN,					/* ��Ч�� */
	AI_CMD_IDLE,					/* ���� */
	AI_CMD_MOVE,					/* �ƶ� */
	AI_CMD_STOP_MOVE,				/* ֹͣ�ƶ� */
	AI_CMD_USE_SKILL,				/* ʹ�ü��� */
	AI_CMD_ACTIVE_TRIPPER,			/* ���� */
	AI_CMD_DEFAULT_EVENT,			/* �¼� */
	AI_CMD_COMPOSE_ITEM,			/* �ϳ� */
	AI_CMD_JUMP,					/* �� */
	AI_CMD_FOLLOW,					/* ���� */
	AI_CMD_DEAD,					/* ���� */
	AI_CMD_PICKUP,					/* ʰȡ */
	AI_CMD_STALL,					/* ��̯ */
	AI_CMD_OPEN_BOX,				/* ������ */
};

/* �ƶ��¼� */
enum PLAYER_MOVE_TO_EVENT
{
	PLAYER_MOVE_TO_SPEAK	= 0,
	PLAYER_ENTER_CHARIOT,
	PLAYER_CHANGE_SCENE,			/* �糡��Ѱ· */
	PLAYER_ACTIVE_TRIPPER,
	PLAYER_COMPOSE_ITEM,
};

/* AI״̬�л���� */
enum AI_CHANGE_STATE_RES
{
	AI_CS_FAILD				= 0,	/* ʧ�� */
	AI_CS_OK_BUT_NO_TICK,			/* ִ�гɹ�, �����ǳ���״̬ */
	AI_CS_OK_AND_TICK,				/* ִ�гɹ�, ���ҳ��� */
};
