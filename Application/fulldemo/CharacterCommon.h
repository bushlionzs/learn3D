#pragma once

// ----------------------------------------------------------------

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

/// NPC 类型
enum eNPC_TYPE
{
	NPC_TYPE_INVALID = -1,
	NPC_TYPE_MONSTER,			// 怪物
	//NPC_TYPE_PET,				// 宠物
	NPC_TYPE_HORSE,				// 马
	NPC_TYPE_BUS,				// BUS
	NPC_TYPE_BEASTIE,			// 动物
	NPC_TYPE_GUARDER,			// 召唤兽

	NPC_TYPE_NUMBERS
};

/// 任务状态（对应到NPC）
enum QUEST_STATE
{
	MS_INVALID = -1,

	MS_HAVE_MISS_NOT_ACCEPT,		// 有任务，不满足接受条件

	MS_DRUGSTORE,					// 药店	-》 药罐子
	MS_FORGER,						// 铁匠 -》 铁锤
	MS_HOSTLER,						// 马夫 -》 马
	MS_SULUDING,					// 苏鲁定
	MS_COACHMAN,					// 马车夫传送
	MS_COUNTRY,						// 国家管理
	MS_GUILD,						// 帮会管理

	MS_CHAPMAN,						// 商人	“商”字图标
	MS_FUBEN,						// 副本入口	城堡图标
	MS_TRAN,						// 钥匙老人传送	传送门图标
	MS_BIND,						// 绑定	
	MS_DECOMPOSE,					// 拆解	分解
	MS_BESET,						// 镶嵌	
	MS_CHECKUP,						// 鉴定	
	MS_COMPOSE,						// 合成
	MS_CHANGE,						// 改造
	MS_REPAIR,						// 修理

	MS_BLUESIGN,					// 蓝色叹号

//	MS_HAVE_CIRECLEMISS_NO_DONE,	// 循环任务未完成
MS_HAVE_MISS_NO_DONE,			// 已接任务， 未完成
MS_TRANSMISS,					// 有传送点没有开启
MS_CIRCLEMISS,					// 有循环任务，可接
MS_MISS,						// 有可接任务
MS_HAVE_MISS_DONE,				// 已接任务， 已完成

};

/// 角色obj的类型
enum CHARACTER_BASE_TYPE
{
	CHAR_BASE_TYPE_INVALID = -1,

	CHAR_BASE_TYPE_NPC,			// NPC
	CHAR_BASE_TYPE_OHTER,		// 其他玩家
	CHAR_BASE_TYPE_ME			// 自己
};

/// 当前角色类Object的逻辑状态
enum CHARATER_STATE_TYPE
{
	CAHR_STATE_INVAILD = -1,	// 无效

	// 基础逻辑
	CAHR_STATE_IDLE,			// 休闲
	CAHR_STATE_MOVE,			// 移动
	CAHR_STATE_DEAD,			// 死亡
	CAHR_STATE_STALL,			// 摆摊

	// 行为逻辑
	CAHR_STATE_ACTION,			// 动作
	CAHR_STATE_GATHER,			// 聚集技能
	CAHR_STATE_LEAD,			// 引导技能
	CAHR_STATE_SEND,			// 发送技能
	CAHR_STATE_ABILITY,			// 生活动作

	CAHR_STATE_NUMBERS
};

/// 逻辑的类型
enum CHARATER_LOGIC_TYPE
{
	CHAR_LOGIC_BASE,					// 基础逻辑
	CHAR_LOGIC_ACTION,					// 行为逻辑
};

// 模型标识
enum CHARATER_MODEL_TYPE
{
	CHAR_MODEL_INVAILD = 0,
	CHAR_MODEL_CHAR,					// 人物
	CHAR_MODEL_MOUNT,					// 坐骑
	CHAR_MODEL_ADJUNCT_1,				// 挂接物1
	CHAR_MODEL_ADJUNCT_2,				// 挂接物2

	CHAR_MODEL_TYPE_NUM,
};

enum CHARIOT_TYPE
{
	CT_NONE = 0,
	CT_BUS,
	CT_CASHBOX,
	CT_GUILD_CASHBOX,
};



// 人物身体模型部件
enum BODY_PART_MODEL
{
	BODY_PART_HAIR = 0,// 头发
	BODY_PART_FACE,			// 脸
	BODY_PART_RIGHTHAND,	// 主手
	BODY_PART_LEFTHAND,		// 副手
	BODY_PART_SHIELD,		// 盾
	BODY_PART_MANTLE,		// 披风
	BODY_PART_BODY,			// 躯干
	BODY_PART_HAND,			// 手
	BODY_PART_FEET,			// 脚

	BODY_PART_NUMBER,
};

struct ModelPartData
{
	BOOL	m_bUpdateFlag;	// 更新标识
	String	m_strBackUp;
	String	m_strValue;
	int32		m_nBackUp;
	int32		m_nValue;

	ModelPartData();

	void Clear();
	void Update();
	BOOL IsFlag();

	void SetValue(LPCSTR szValue);
	void SetValue(int32 nValue);
};

struct ModelPartDataList
{
	BOOL			m_bUpdateFlag;
	ModelPartData	m_ModelPartData[BODY_PART_NUMBER];
	String			m_strPartName[BODY_PART_NUMBER];

	ModelPartDataList();

	void Clear();
	void Update();
	BOOL IsFlag() { return m_bUpdateFlag; }

	void SetValue(int32 nPart, LPCSTR szValue);
	void SetValue(int32 nPart, int32 nValue);
};

LPCSTR GetCharaLocatorName( ENUM_CHARACTER_LOCATOR eLocator );
LPCSTR GetMountLocatorName( ENUM_MOUNT_LOCATOR eLocator );
LPCSTR GetWeaponLocatorName( ENUM_WEAPON_LOCATOR eLocator );




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







