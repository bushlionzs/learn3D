#pragma once
#include "KDefine.h"

#define BLEND_IN_TIME	(0.25f)
#define BLEND_OUT_TIME	(0.25f)



/* 动作状态 */
enum CHARACTER_ACTION
{
	CA_INVALID = -1,			/* 无效，静止不动 AASMD_NOTHING_DEGREE */
	CA_DIRECTIONAL,					/* 转向 AASMD_DIRECTIONAL_DEGREE */
	CA_MOVING,						/* 移动 AASMD_MOVING_DEGREE */
	CA_RIDING,						/* 是否骑马 AASMD_RIDING_DEGREE */
	CA_ATTACK,						/* 攻击 AASMD_ATTACK_DEGREE */
	CA_LIFE,						/* 生存 AASMD_LIFE_DEGREE */
	CA_WEAPON,						/* 武器 AASMD_WEAPON_DEGREE */
	CA_DAMAGE,						/* 受伤 AASMD_DAMAGCD_DEGREE */
	CA_POSTURE,						/* 姿势（站立或坐下）AASMD_POSTURE_DEGREE, */
	CA_JUMP,					/* 马是否扬蹄|跳跃 AASMD_EQUITATION_DEGREE, 0 0.33 扬蹄 0.66 跳跃 1 */
	CA_GUARD,						/* 警戒或休闲 AASMD_GUARD_DEGREE, */
	CA_MOOD,						/* 表情动画 AASMD_MOOD_DEGREE */
	CA_DANCE,						/* 跳舞 AASMD_DANCE_DEGREE */
	CA_WALK,						/* 跑走切换 AASMD_WALK_DEGREE */
	CA_IDLE,						// 休闲 
};

/* 动作插槽 */
enum CHARACTER_AAS_NODE
{
	AASSLOT_DOWN_IDLE_ATTACK = 0,	/* 马下_站立_攻击 */
	AASSLOT_DOWN_IDLE_MOOD = 1,	/* 马下_站立_表情 */
	AASSLOT_DOWN_IDLE_DACE = 2,	/* 马下_站立_随机跳舞 */
	AASSLOT_DOWN_IDLE_DAMAGE = 3,	/* 马下_站立_受伤 */
	AASSLOT_DOWN_IDLE_STAND = 4,	// 马下_站立_休闲
	AASSLOT_DOWN_IDLE_JUMP = 5,	// 马下_站立_跳跃

	AASSLOT_DOWN_MOVE_ATTACK = 50,	/* 马下_移动_攻击 */
	AASSLOT_DOWN_MOVE_MOOD = 51,	/* 马下_移动_表情 */
	AASSLOT_DOWN_MOVE_DAMAGE = 53,	/* 马下_移动_受伤 */
	AASSLOT_DOWN_MOVE_JUMP = 55,	// 马下_移动_跳跃

	AASSLOT_UP_IDLE_ATTACK = 100,	/* 马上_站立_攻击 */
	AASSLOT_UP_IDLE_MOOD = 101,	/* 马上_站立_表情 */
	AASSLOT_UP_IDLE_DAMAGE = 103,	/* 马上_站立_受伤 */
	AASSLOT_UP_IDLE_STAND = 104,	// 马上_站立_休闲
	AASSLOT_UP_IDLE_JUMP = 105,	// 马上_站立_跳跃

	AASSLOT_UP_MOVE_ATTACK = 150,	/* 马上_移动_攻击 */
	AASSLOT_UP_MOVE_MOOD = 151,	/* 马上_移动_表情 */
	AASSLOT_UP_MOVE_DAMAGE = 153,	/* 马上_移动_受伤 */
	AASSLOT_UP_MOVE_JUMP = 155,	// 马上_移动_跳跃
};


