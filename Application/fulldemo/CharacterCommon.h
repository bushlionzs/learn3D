#pragma once

// 性别
enum eGENDER
{
	GENDER_INVALID	= -1,
	GENDER_FEMALE,			// 女
	GENDER_MALE,			// 男	

	GENDER_NUM,
};


// 武器类型
enum eWEAPON_TYPE
{
	WEAPON_TYPE_INVALID	= -1,

	WEAPON_TYPE_NONE,		// 徒手
	WEAPON_TYPE_FALCHION,	// 刀
	WEAPON_TYPE_SWORD,		// 剑
	WEAPON_TYPE_BOW,		// 弓箭
	WEAPON_TYPE_GUN,		// 火枪
	WEAPON_TYPE_GAVEL,		// 槌
	WEAPON_TYPE_STAFF,		// 杖
	WEAPON_TYPE_HOLD,		// 双持
	WEAPON_TYPE_DOUBLE,		// 双手
	WEAPON_TYPE_FLAG,		// 旗子
	WEAPON_TYPE_LONG,		// 长柄
	WEAPON_TYPE_NPC,		// NPC
	WEAPON_TYPE_SPEAR,		// 长矛
	WEAPON_TYPE_TOKEN,		// 令
	WEAPON_TYPE_CROSSBOW,	// 弩
	WEAPON_TYPE_FIREGUN,	// 火铳
	WEAPON_TYPE_CROSS,		// 十字架
	WEAPON_TYPE_FAN,		// 帆

	WEAPON_TYPE_NUMBERS,
};

/// 左手还是右手
enum ENUM_WEAPON_LOCATOR_TYPE
{
	WL_DEFAULT,		// 默认参数，以下所有类型都检测
	WL_LEFT,		// 左
	WL_RIGHT,		// 右
	WL_L_ARM,		// 左手臂（盾牌用）
	WL_BOTH,		// 双手
};



// 人物动作标识
enum ACTION_TYPE
{
	BASE_ACTION_N_STAND		=  0,	// 站立
	BASE_ACTION_N_WALK		=  3,	// 行走
	BASE_ACTION_N_RUN		=  4,	// 跑步
	BASE_ACTION_F_IDLE		= 14,	// 休息
	BASE_ACTION_F_BE_HIT0	= 23,	// 受伤
	BASE_ACTION_F_DIE0		= 25,	// 死亡
	BASE_ACTION_F_DIEFLYi	= 27,	// 死亡击飞
	BASE_ACTION_F_CADAVER0	= 29,	// 尸体
	BASE_ACTION_N_JUMP		= 30,	// 起跳
	BASE_ACTION_N_FALLING	= 31,	// 下落
	BASE_ACTION_N_TOUCHDOWN = 32,	// 落地
	BASE_ACTION_N_IDLE_1	= 41,	// 休闲1
	BASE_ACTION_N_IDLE_2	= 42,	// 休闲2
	BASE_ACTION_N_IDLE_3	= 43,	// 休闲3
	BASE_ACTION_N_IDLE_4	= 44,	// 休闲4
	BASE_ACTION_N_IDLE_5	= 45,	// 休闲5

	BASE_ACTION_NUMBERS
};


// 人物绑定点
enum ENUM_CHARACTER_LOCATOR
{
	LOCATOR_CHAR_INVALID	= -1,

	LOCATOR_CHAR_HEAD,			// 人物头部绑定点
	LOCATOR_CHAR_FRONT,			// 人物身体前置点
	LOCATOR_CHAR_ATTACK,		// 人物身体受击点
	LOCATOR_CHAR_CENTER,		// 人物身体中心点
	LOCATOR_CHAR_FOOT,			// 人物脚部绑定点
	LOCATOR_CHAR_HAND_L,		// 人物左手绑定点
	LOCATOR_CHAR_HAND_R,		// 人物右手绑定点
	LOCATOR_CHAR_SHOULDER_L,	// 人物左肩绑定点
	LOCATOR_CHAR_SHOULDER_R,	// 人物右肩绑定点
	LOCATOR_CHAR_SHIELD_L,		// 人物左臂盾牌绑定点

	LOCATOR_CHAR_NUMBERS
};


// 坐骑绑定点
enum ENUM_MOUNT_LOCATOR
{
	LOCATOR_MOUNT_INVALID	= -1,

	LOCATOR_MOUNT_LF,		// 坐骑马左前蹄绑定点
	LOCATOR_MOUNT_RF,		// 坐骑马右前蹄绑定点
	LOCATOR_MOUNT_LB,		// 坐骑马左后蹄绑定点
	LOCATOR_MOUNT_RB,		// 坐骑马右后蹄绑定点
	LOCATOR_MOUNT_FOOT,		// 坐骑马脚部绑定点
	LOCATOR_MOUNT_HEAD,		// 坐骑马头部绑定点
	LOCATOR_MOUNT_BOSOM,	// 坐骑马胸部绑定点
	LOCATOR_MOUNT_BACK,		// 坐骑马背部NOX轴绑定点

	LOCATOR_MOUNT_NUMBERS,
};

// 武器绑定点
enum ENUM_WEAPON_LOCATOR
{
	LOCATOR_WEAPON_INVALID	= -1,

	LOCATOR_WEAPON_1	= 1,// 武器绑定点1
	LOCATOR_WEAPON_2,		// 武器绑定点2
	LOCATOR_WEAPON_3,		// 武器绑定点3
	LOCATOR_WEAPON_4,		// 武器绑定点3

	LOCATOR_WEAPON_NUMBERS,
};

// 跳跃状态
enum ENUM_CHAR_JUMP_STATE
{
	ENUM_CHAR_JUMP_STATE_INVALID = -1,
	ENUM_CHAR_JUMP_STATE_JUMPING,
	ENUM_CHAR_JUMP_STATE_FALLING,
	ENUM_CHAR_JUMP_STATE_TOUCHDOWN,
};


const char* GetCharaLocatorName( ENUM_CHARACTER_LOCATOR eLocator );
const char* GetMountLocatorName( ENUM_MOUNT_LOCATOR eLocator );
const char* GetWeaponLocatorName( ENUM_WEAPON_LOCATOR eLocator );




extern const char *g_szIDSTR_FACE_MESH;
extern const char *g_szIDSTR_FACE_MAT;

extern const char *g_szIDSTR_HAIR_MESH;
extern const char *g_szIDSTR_HAIR_MAT;

extern const char *szIDSTRING_SHOULDER_MESH;
extern const char *szIDSTRING_SHOULDER_MAT;

extern const char *g_szIDSTR_MAINBODY_MESH;
extern const char *g_szIDSTR_MAINBODY_MAT;

extern const char *g_szIDSTR_FOOT_MESH;
extern const char *g_szIDSTR_FOOT_MAT;

extern const char *g_szIDSTR_CAP_MESH;
extern const char *g_szIDSTR_CAP_MAT;

extern const char *g_szIDSTR_ARM_MESH;
extern const char *g_szIDSTR_ARM_MAT;

extern const char *g_szIDSTR_CURRENT_LEFTWEAPON;
extern const char *g_szIDSTR_CURRENT_RIGHTWEAPON;

extern const char *szIDSTRING_SHIELD_RIGHTWEAPON;

extern const char *szIDSTRING_DROPITEM;







