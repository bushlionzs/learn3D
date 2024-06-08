
/* AICommandDef.h */
#pragma once
enum AI_COMMAND
{
	AI_CMD_UNKOWN,					/* 无效的 */
	AI_CMD_IDLE,					/* 休闲 */
	AI_CMD_MOVE,					/* 移动 */
	AI_CMD_STOP_MOVE,				/* 停止移动 */
	AI_CMD_USE_SKILL,				/* 使用技能 */
	AI_CMD_ACTIVE_TRIPPER,			/* 操作 */
	AI_CMD_DEFAULT_EVENT,			/* 事件 */
	AI_CMD_COMPOSE_ITEM,			/* 合成 */
	AI_CMD_JUMP,					/* 跳 */
	AI_CMD_FOLLOW,					/* 跟随 */
	AI_CMD_DEAD,					/* 死亡 */
	AI_CMD_PICKUP,					/* 拾取 */
	AI_CMD_STALL,					/* 摆摊 */
	AI_CMD_OPEN_BOX,				/* 开宝箱 */
};

/* 移动事件 */
enum PLAYER_MOVE_TO_EVENT
{
	PLAYER_MOVE_TO_SPEAK	= 0,
	PLAYER_ENTER_CHARIOT,
	PLAYER_CHANGE_SCENE,			/* 跨场景寻路 */
	PLAYER_ACTIVE_TRIPPER,
	PLAYER_COMPOSE_ITEM,
};

/* AI状态切换结果 */
enum AI_CHANGE_STATE_RES
{
	AI_CS_FAILD				= 0,	/* 失败 */
	AI_CS_OK_BUT_NO_TICK,			/* 执行成功, 但不是持续状态 */
	AI_CS_OK_AND_TICK,				/* 执行成功, 并且持续 */
};
