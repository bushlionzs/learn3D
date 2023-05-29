#pragma once
#include "DefineItem.h"
#include "DefineGuild.h"
#include "Define.h"
#include "TAB.h"

#define EQUIP_CHIEFTAIN_TAG 11990001

/* 装备上的特效 */
#define EQUIP_EFFECT_MAX_NUM	16
struct EQUIP_EFFECT
{
	LPCTSTR szEffect;					/* 特效id */
	LPCTSTR szBindPoint;				/* 特效绑点 */
};

/* 怪身上的特效 */
#define MONSTER_EFFECT_MAX_NUM	4
struct MONSTER_EFFECT
{
	LPCTSTR szEffect;
	LPCTSTR szBind;

	MONSTER_EFFECT()
	{
		szEffect = NULL;
		szBind = NULL;
	};
};

enum CHAR_RACE_LOGICTYPE
{
	CHAR_RACE_LOGICTYPE_DEFAULT = 0,
	CHAR_RACE_LOGICTYPE_CREATE_ROLE,
	CHAR_RACE_LOGICTYPE_SELECT_ROLE,
};

/* 主角种族 (CHAR_01) */
#define TABLE_CHARACTER_RACE	(101)		/* 主角种族(男，女) */
struct _TABLE_CHAR_RACE					/* bc */
{
	table_int_t 	nID;
	table_int_t 	nModelID;						/* 模型 */
	table_int_t 	nDefHeadGeo;					/* 头 */
	table_int_t 	nDefHairGeo;					/* 脸 */
	table_int_t 	nDefShoulder;					/* 肩 */
	table_int_t 	nDefBody;						/* 身体 */
	table_int_t 	nDefArm;						/* 手 */
	table_int_t 	nDefFoot;						/* 脚 */
	table_int_t 	nIdleInterval;					/* 休闲时间 */
	table_int_t 	nWeaponId;						/* 武器ID */
	table_int_t 	nSex;
	table_int_t 	nProfession;
	table_int_t 	nLogicType;					// CHAR_RACE_LOGICTYPE
	table_float_t  	fAddDownHeight;
	table_float_t 	fAddUpHeight;
};

/* 主角头发模型 (CHAR_02) */
#define TABLE_CHARACTER_HAIR_GEO	(102)	/* 主角头发模型 */
struct _TABLE_CHAR_HAIR_GEO
{
	table_int_t		nID;
	table_int_t		nRace;						/* RaceID */
	LPCSTR	pMeshFile;
	LPCSTR	pShowName;
	table_int_t		n1;			/* 消耗物品ID */
	LPCSTR	n2;			/* MaterialName */
	table_int_t		n3;			/* 消耗物品数量 */
	table_int_t		n4;			/* 是否在初始时可选 */
	table_int_t		nHairType;	/* 头型类型 */
	table_int_t		nColorType; /* 颜色类型 */
	LPCSTR	pColorName; /* 颜色显示名称 */
	table_int_t	bIsShowInCreateRole;
};

/* 主角脸部模型 (CHAR_04) */
#define TABLE_CHARACTER_HEAD_GEO	(104)				/* 主角脸部模型 */
struct _TABLE_CHAR_HEAD_GEO							/* bc */
{
	table_int_t		nID;
	LPCSTR		pMeshFile;
	table_int_t		nRace;
	LPCSTR		pShowName;
	table_int_t		nFaceType;								/* 发型类型 */
	table_int_t		nColorType;								/* 类别，和发型相对应 */
	table_int_t		bIsShowInCreateRole;
};

/* 主角动作组 (CHAR_06) */
#define TABLE_CHARACTER_ACTION_SET	(106)
#define MAX_WEAPON_TYPE_NUMBER		(18)			/* 武器类型数量 */
struct _TABLE_CHARACTER_ACTION_SET
{
	table_int_t		nID;
	LPCSTR	pWeapon_Set[MAX_WEAPON_TYPE_NUMBER];	/* 对应武器类型 eWEAPON_TYPE */
	table_int_t 	bHideWeapon;					/* 隐藏武器 */
	table_int_t	nAppointedWeaponID;				/* 指定的武器ID */
	LPCSTR	pszDesc;						/* 描述 */
	table_float_t 	nMonitoringDegree;				/* 动作融合度 */
	table_int_t	nIsSkill;						/* 是否是技能 */
};

/* 主角特效 (CHAR_07) */
#define TABLE_CHARACTER_EFFECT	(107)
struct _TABLE_CHARACTER_EFFECT
{
	table_int_t 		nID;
	table_int_t 		nEffect1;
	table_int_t 		nEffect2;
	LPCSTR	pLocator;
	table_int_t 		nSoundID;
	LPCSTR	pWeaponLocator;
};

/* 主角升级经验值 (CHAR_08) */
#define TABLE_CHARACTER_EXPLEVEL	(108)
struct _TABLE_CHARACTER_EXPLEVEL
{
	table_int_t nID;
	LPCSTR pNeedExp;
};

/* 外形ID对应模型名称 (CHAR_09) */
#define TABLE_CHARACTER_MODEL (109)
#define MAX_MOUNT_NUMBER	(20)
#define MAX_SOUND_NUMBER	(3)				/* 此数值根据地面的类型得出 分为：地表、水、行走面 */
struct _TABLE_CHARACTER_MODEL					/* bc */
{
	table_int_t 	m_nID;
	table_float_t 	m_fFuseTime;					/* 动作熔合时间 */
	LPCSTR	m_pszModelName;					/* 模型文件 */
	table_int_t 	m_nSoundId[MAX_SOUND_NUMBER];	/* 不同地面跑步的声音 */
	LPCSTR	m_pszActionSetName_None;		/* 不使用坐骑的动作文件 */
	LPCSTR	m_apszActionSetName_Mount[MAX_MOUNT_NUMBER];	/* 使用坐骑后的动作文件 */

	table_int_t 	m_nCheckMount;					// 变身后是否能骑坐骑
											// <0，不能
											// =0，能，可骑拥有的坐骑
											// >0，能，只能骑指定坐骑 char_mount.tab

	table_int_t 	m_nCheckWeapon;					// 是否能挂接武器
											// <0，不能
											// =0，能，挂接自身的武器
											// >0，能，挂接指定武器 item_loc.tab

	table_int_t 	m_nCanJump;						// 是否可跳跃
};

/* 主角头像 */
#define TABLE_CHARACTER_FACE	(110)			/* 主角头像 */
struct _TABLE_CHAR_FACE						/* bc */
{
	table_int_t 		nID;
	LPCSTR	pImageSetName;
	table_int_t 		nRace;
	LPCSTR	pImageSetNameGray;
};

/* 坐骑表 */
#define MOUNT_EFFECT_MAX_NUM	8
struct MOUNT_EFFECT
{
	const char	*pszEffectLocator;			/* 特效帮定点 */
	const char	*pszEffectName;				/* 特效名称 */
};

struct MOUNT_ATTR_EFFECT
{
	table_int_t 			nType;						/* 影响类别,MountAttrEffect_Type */
	table_int_t 			nVal;						/* 影响数值 */
	const char	*pszEffectLocator;			/* 特效帮定点 */
	const char	*pszEffectName;				/* 特效名称 */
};

enum MountAttrEffect_Type
{
	MAE_INVALID		= -1,
	MAE_APT_ALL_MAX = 0,					/* 所有资质全满 */

	MAE_APT_STR_MAX,						/* 力量资质满 */
	MAE_APT_DEX_MAX,						/* 敏捷资质满 */
	MAE_APT_INT_MAX,						/* 智力资质满 */
	MAE_APT_CON_MAX,						/* 体质资质满 */

	MAE_APT_STR_VAL,						/* 力量资质数值 */
	MAE_APT_DEX_VAL,						/* 敏捷资质数值 */
	MAE_APT_INT_VAL,						/* 智力资质数值 */
	MAE_APT_CON_VAL,						/* 体质资质数值 */

	MAE_APT_ONE_MAX,						/* 任意一种资质满 */

	MAE_NUMBER,
};

#define TABLE_CHARACTER_MOUNT (111)
struct _TABLE_CHARACTER_MOUNT
{
	table_int_t 					m_nID;									/* 骑乘ID */
	table_float_t 					m_fBoardAddHeight;						/* 头顶信息版高度修正 */	
	table_int_t 					m_nModelID;								/* 模型ID */
	table_int_t 					m_nCharActionIndex;						/* 人物骑乘时的动作组,对应char_model.tab的mount0~19 */
	MOUNT_EFFECT			m_EffectInfo[MOUNT_EFFECT_MAX_NUM];		/* 特效信息 */
	LPCSTR					m_szIcoName;							/* 头像名 */
	MOUNT_ATTR_EFFECT		m_AttrEffectInfo[MOUNT_EFFECT_MAX_NUM]; /* 坐骑属性特效 */
	table_float_t 					fCameraHeight;							// UI摄像机高度
	table_float_t 					fCameraDistance;						// UI摄像机距离
	table_float_t 					fCameraPitch;							// UI摄像机角度
	table_float_t 					m_fCameraAddHeight;						// 游戏摄象机高度修正
	
};

/*
 * 生物相关 // ;
 * -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//
 * 生物定义总表 (CREATURE_01) #define TABLE_BUS_ATTR (201) ;
 * struct _TABLE_CREATURE_ATT_BASE ;
 * { ;
 * table_int_t nMonsterID1;
 * // 怪物编号 ;
 * table_int_t nCannotBeAttack;
 * // 不可被攻击 ;
 * table_int_t nID;
 * // 怪物编号 ;
 * table_int_t nLevel;
 * // 等级 ;
 * table_int_t NOTCARE1[3];
 * //* 刷新周期 ;
 * // 最小伤血百分比(Hppercent) ;
 * // 基础经验获得(EXP) ;
 * table_int_t nAttackRate_N;
 * // 近程攻击获得(table_int_t  range att) ;
 * table_int_t nAttackRate_F;
 * // 远程攻击获得(long range att) ;
 * table_int_t nAttackRate_M;
 * // 魔法攻击获得(magic att) ;
 * table_int_t nDefence_N;
 * // 近程防御(table_int_t  range recovery) ;
 * table_int_t nDefence_F;
 * // 远程防御(long range recovery) ;
 * table_int_t nDefence_M;
 * // 魔法防御(magic recovery) ;
 * table_int_t nMaxHP;
 * // HP上限(hp limit) ;
 * table_int_t nMaxMP;
 * // MP上限(mp limit) ;
 * table_int_t nRestoreHP;
 * // HP回复(hp reversion) ;
 * table_int_t nRestoreMP;
 * // MP回复(mp reversion) ;
 * table_int_t nHit;
 * // 命中(hit rate) ;
 * table_int_t nMiss;
 * // 闪避（volt） ;
 * table_int_t nCritrate;
 * // 会心率（huixin) ;
 * table_int_t nTenacity;
 * //韧性 ;
 * table_int_t nAttackCold;
 * // 属性攻击１(shuxingatt1 ) 冰 ;
 * table_int_t nAttackFire;
 * // 属性攻击２(shuxingatt2 ) 火 ;
 * table_int_t nAttackLight;
 * // 属性攻击３(shuxingatt3) 光 ;
 * table_int_t nAttackPoison;
 * // 属性攻击４(shuxingatt4) 毒 ;
 * table_int_t nDefenceCold;
 * // 属性防御１(shuxingrecovery1) ;
 * table_int_t nDefenceFire;
 * // 属性防御２(shuxingrecovery2) ;
 * table_int_t nDefenceLight;
 * // 属性防御３(shuxingrecovery3) ;
 * table_int_t nDefencePoison;
 * // 属性防御４(shuxingrecovery4) ;
 * table_int_t NOTCARE2;
 * //* 调用脚本ID ;
 * table_int_t nModelID;
 * // 外型ID ;
 * LPCSTR szIconName;
 * // 人物头像 ;
 * table_int_t nIsDisplayerName;
 * // 是否显示头顶信息板 ;
 * table_float_t  fBoardHeight;
 * // 名字板高度 ;
 * table_float_t  fProjTexRange;
 * // 选中环大小 ;
 * table_float_t  fShadowRange;
 * // 阴影大小 ;
 * table_int_t NOTCARE3[2];
 * // 攻击动作时间 ;
 * // 攻击冷却时间 ;
 * table_int_t nIdleInterval;
 * // 休闲间隔时间 ;
 * table_int_t nSpeed;
 * // 移动速度 ;
 * table_int_t nMonsterWalkSpeed;
 * // 步行速度 ;
 * table_int_t nAttackSpeed;
 * // 攻击速度 ;
 * table_int_t nMArmID;
 * // 武器调用ID ;
 * table_int_t NOTCARE4[4];
 * //* 马调用ID ;
 * // 基础AI ;
 * // 扩展AI ;
 * // 阵营 ;
 * table_int_t nCannotBeAttack;
 * // 不可被攻击 ;
 * table_int_t nCanHandle;
 * // 是否可以交互 ;
 * table_int_t NOTCARE5;
 * // 友好值 ;
 * table_int_t nMonsterBossFlag;
 * // BOSS标记 ;
 * table_int_t nMonsterBossSnapImmID;
 * // 瞬时效果免疫ID ;
 * table_int_t nMonsterBossDurationImmID;
 * // 持续效果免疫ID ;
 * table_int_t NOTCARE6[2];
 * // 掉落分配半径(米) ;
 * // 掉落最大有效组 ;
 * table_int_t nDropItemSet;
 * //掉落物品组 ;
 * table_int_t nDropItemRate;
 * //掉落概率 ;
 * MONSTER_EFFECT sMonsterEffect[MONSTER_EFFECT_MAX_NUM];
 * // 绑在怪身上的特效 ;
 * LPCSTR pHorseDropID;
 * // 马掉落ID ;
 * table_int_t nDropID;
 * // 掉落ID ;
 * };
 */
#define TABLE_BUS_ATTR	(201)
struct _TABLE_BUS_ATTR
{
	table_int_t 				nID;					/* 怪物编号 */
	table_int_t 				nCannotBeAttack;		/* 不可被攻击 */
	LPCSTR			pName;					/* 名称 */
	table_int_t 				nIsCanSwerve;			/* 是否随玩家转向 */
	table_int_t 				nIsDisplayerName;		/* 是否显示头顶信息板 */
	table_float_t 			fBoardHeight;			/* 名字板高度 */
	table_float_t 			fProjTexRange;			/* 选中环大小 */
	table_float_t 			fShadowRange;			/* 阴影大小 */
	LPCSTR			szIconName;				/* 人物头像 */
	table_int_t 				nModelID;				/* 外型ID */
	table_int_t 				nBusType;				/* Bus的类型 */
	table_int_t 				nBusMountModelID[2];	/* 拉车的马模型 */
	LPCSTR			szMountModelLocator[2]; /* 挂接拉车的马绑定点名称 */
	table_int_t 				nIdleInterval;			/* 休闲间隔时间 */
	table_int_t 				nCanHandle;				/* 是否可以交互 */
	table_int_t 				nMonsterBossFlag;		/* BOSS标记 */
	MONSTER_EFFECT	sMonsterEffect[MONSTER_EFFECT_MAX_NUM]; /* 绑在怪身上的特效 */
	LPCSTR			szPassengerLocator[8];					/* 乘客座位的绑定点 */
};

#define TABLE_CREATURE_ATT	(202)
struct _TABLE_CREATURE_ATT				/* : public _TABLE_CREATURE_ATT_BASE */
{
	table_int_t 				nID;				/* 怪物编号 */
	table_int_t 				nCannotBeAttack;	/* 不可被攻击 */
	LPCSTR			pName;				/* 名称 */
	table_int_t 				nIsCanSwerve;		/* 是否随玩家转向 */
	table_int_t 				nIsDisplayerName;	/* 是否显示头顶信息板 */
	table_float_t 			fBoardHeight;		/* 名字板高度 */
	table_float_t 			fProjTexRange;		/* 选中环大小 */
	table_float_t 			fShadowRange;		/* 阴影大小 */
	LPCSTR			szIconName;			/* 人物头像 */
	table_int_t 				nModelID;			/* 外型ID */
	table_int_t 				nIdleInterval;		/* 休闲间隔时间 */
	table_int_t 				nCanHandle;			/* 是否可以交互 */
	table_int_t 				nMonsterBossFlag;	/* BOSS标记 */
	table_int_t 				nRunSpeed;			/* 跑步速度 */
	table_int_t 				nWalkSpeed;			/* 步行速度 */
	MONSTER_EFFECT	sMonsterEffect[MONSTER_EFFECT_MAX_NUM]; /* 绑在怪身上的特效 */
	table_int_t 				nNPCType;	/* NPC类型 */
};

/*
 * 宠物附加属性 (TABLE_PET_EX_ATT) #define TABLE_PET_EX_ATT (202) ;
 * struct _TABLE_PET_EX_ATT // bc ;
 * { ;
 * table_int_t m_Type;
 * // 宠物编号 ;
 * table_int_t m_TakeLevel;
 * // 可携带等级 ;
 * LPTSTR m_Name;
 * // 名称 ;
 * table_int_t m_Camp;
 * // 阵营 ;
 * table_int_t m_Reserve1;
 * // 保留 ;
 * table_int_t m_Reserve2;
 * // 保留 ;
 * table_int_t m_FoodType;
 * // 食物类 ;
 * table_int_t m_SkillLearnNum;
 * // 所能学的技能数 ;
 * table_int_t m_PositiveSkill;
 * // 主动技能 ;
 * table_int_t m_PassiveSkill1;
 * // 被动技能1 ;
 * table_int_t m_PassiveSkill2;
 * // 被动技能2 ;
 * table_int_t m_PassiveSkill3;
 * // 被动技能3 ;
 * table_int_t m_PassiveSkill4;
 * // 被动技能4 ;
 * table_int_t m_Life;
 * // 标准寿命 ;
 * table_int_t m_StrPerception;
 * // 标准力量资质 ;
 * table_int_t m_ConPerception;
 * // 标准体质资质 ;
 * table_int_t m_DexPerception;
 * // 标准灵气资质 table_int_t m_SprPerception;
 * // 标准身法资质 ;
 * table_int_t m_IntPerception;
 * // 标准定力资质 ;
 * table_int_t m_GrowRate0;
 * // 成长率1 ;
 * table_int_t m_GrowRate1;
 * // 成长率2 ;
 * table_int_t m_GrowRate2;
 * // 成长率3 ;
 * table_int_t m_GrowRate3;
 * // 成长率4 ;
 * table_int_t m_GrowRate4;
 * // 成长率5 ;
 * table_int_t m_CowardiceRate;
 * // 胆小几率 ;
 * table_int_t m_WarinessRate;
 * // 谨慎几率 ;
 * table_int_t m_LoyalismRate;
 * // 忠诚几率 ;
 * table_int_t m_CanninessRate;
 * // 精明几率 ;
 * table_int_t m_ValourRate;
 * // 勇猛几率 ;
 * };
 * 生物声音定义表 (CREATURE_03) #define TABLE_CREATURE_SOUND (203) ;
 * struct _TABLE_CREATURE_SOUND // bc ;
 * { ;
 * table_int_t nID;
 * table_int_t nUnderAttack;
 * table_int_t nAttack;
 * table_int_t nDeath;
 * };
 * BUS属性表定义 #define TABLE_BUS_ATTR (204) ;
 * const table_int_t BUS_SKILL_SIZE = 5;
 * ;
 * struct _TABLE_BUS_ATTR ;
 * { ;
 * _TABLE_CREATURE_ATT nMonsterBaseAttr;
 * table_int_t nChariotSkill[BUS_SKILL_SIZE];
 * // 战车技能1-5 ;
 * LPTSTR szTitle;
 * // title名称 ;
 * table_int_t nControl;
 * // 控制权 ;
 * table_int_t nSpace;
 * // 战车空间 ;
 * table_int_t nShowPlayer;
 * // 人物显示 ;
 * };
 * ;
 * 物品相关 // ;
 * -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//
 * 装备类物品显示定义 (ITEM_01)
 */
#define TABLE_ITEM_VISUAL_CHAR	(301)
struct _TABLE_ITEM_VISUAL_CHAR	/* bc */
{
#define CHAR_RACE_NUM	(2)
	table_int_t nID;

	/*
	 * LPCSTR pVisualEntity[ 6 * 2 * CHAR_RACE_NUM ];
	 */
	table_int_t pVisualEntityIndex[12];
};

#define EQUIP_LOC_EFFECT_MAX_NUM	8
#define TABLE_EQUIP_LOC				(303)
struct _TABLE_EQUIP_LOC
{
	table_int_t 				nID;
	LPCSTR			szDesc;
	LPCSTR			pMeshFile;
	LPCSTR			pMatFile;
	EQUIP_EFFECT	szREffect[EQUIP_LOC_EFFECT_MAX_NUM];	/* 绑点和特效 */
};

#define  ITEM_VISUAL_EFFECT_MAX_NUM		(30)
/* 挂接类物品显示定义 (ITEM_02) */
#define TABLE_ITEM_VISUAL_LOCATOR (302)
struct _TABLE_ITEM_VISUAL_LOCATOR
{
	table_int_t 		nID;

	LPCSTR	pObjFile_Right_Man;			/* 男右手武器名 */
	LPCSTR	pMatName_Right_Man;			/* 男右手武器材质名 */

	LPCSTR	pObjFile_Right_Woman;		/* 女右手武器名 */
	LPCSTR	pMatName_Right_Woman;		/* 女右手武器材质名 */

	LPCSTR	pObjFile_Left_Man;			/* 左手武器名 */
	LPCSTR	pMatName_Left_Man;			/* 左手武器材质名 */

	LPCSTR	pObjFile_Left_Woman;			/* 左手武器名 */
	LPCSTR	pMatName_Left_Woman;			/* 左手武器材质名 */

	LPCSTR	pObjShieldFile;			/* 左手盾名 */
	LPCSTR	pMatName_Shield;		/* 左手盾材质名 */

	table_int_t 	nWeaponPointType;		// 武器绑定类型 ENUM_WEAPON_LOCATOR_TYPE
	table_int_t 	pWeaponType;			/* 武器类型 */
	table_int_t 	nWeaponActor;			/* 表示该武器是否有动作 */

	LPCSTR	pWeaponActorFile_Man_Down;		/* 男马下武器动作文件 */
	LPCSTR	pWeaponActorFile_Woman_Down;	/* 女马下武器动作文件 */

	LPCSTR	pWeaponActorFile_Man_Up;		/* 男马上武器动作文件 */
	LPCSTR	pWeaponActorFile_Woman_Up;		/* 女马上武器动作文件 */

	LPCSTR	pEffectName[ITEM_VISUAL_EFFECT_MAX_NUM];		/* 增加30列各种宝石的特效 */
};

/* 怪武器 */
#define TABLE_ITEM_MONSTER_VISUAL_LOCATOR (320)
struct _TABLE_ITEM_MONSTER_VISUAL_LOCATOR
{
	table_int_t 				nID;			/* id */

	LPCSTR			pObjFile_Right; /* 右手武器名 */
	LPCSTR			pMatName_Right; /* 右手武器材质名 */
	EQUIP_EFFECT	szREffect[MONSTER_EFFECT_MAX_NUM];	/* 右手武器特效 */

	LPCSTR			pObjFile_Left;						/* 左手武器名 */
	LPCSTR			pMatName_Left;						/* 左手武器材质名 */
	EQUIP_EFFECT	szLEffect[MONSTER_EFFECT_MAX_NUM];	/* 左手武器特效 */

	LPCSTR			pObjShieldFile;						/* 左手盾名 */
	LPCSTR			pMatName_Shield;					/* 左手盾材质名 */
	EQUIP_EFFECT	szLSEffect[MONSTER_EFFECT_MAX_NUM]; /* 左手盾材特效 */

	table_int_t 				pWeaponType;						/* 武器类型 */
	table_int_t 				nWeaponActor;						/* 表示该武器是否有动作 */
	LPCSTR			pActorFile; /* 武器动作文件 */
};

#define EQUIP_EFFECT_ATTR_MAXNUM	16

/*
 -----------------------------------------------------------------------------------------------------------------------
    装备对人物属性的影响
 -----------------------------------------------------------------------------------------------------------------------
 */
struct EQUIP_EFFECT_ATTR
{
	table_int_t nAttrID;						/* 影响属性Id */
	table_int_t nEffectNum;						/* 影响属性数值 */
};

/* 附加技能最大个数 */
#define EQUIP_ADDEFFECT_SKILL_MAXNUM	4

/* 影响技能最大个数 */
#define EQUIP_EFFECT_SKILL_MAXNUM	4

struct EQUIP_EFFECT_SKILL
{
	table_int_t nSkillID;						/* 影响技能id */
	table_int_t nEffectLevel;					/* 影响技能等级 */
};

/* 物品定义表_装备 */
#define TABLE_ITEM_EQUIP	(318)
struct _TABLE_ITEM_EQUIP
{
	table_int_t 					nID;				/* 装备序列号 */
	table_int_t 					nClass;				/* 基本类型class */
	table_int_t 					nType;				/* 类别 type */
	table_int_t 					nIndex;				/* 物品号 */
	table_int_t 					nColorType;			/* 物品颜色属性 */
	table_int_t 					nEquipPoint;		/* 装备点 */
	table_int_t 					nRule;				/* 适应规则 */
	table_int_t 					nSetID;				/* 装备套装编号 */
	LPCSTR					nLevelRequire;		/* 等级需求 */
	table_int_t 					iReqInherenceLevel;	/* rj 2010-8-23 天赋等级 */
	table_int_t 					iReqPersonLevel;	/* rj 2010-8-23 个人等级 */
	table_int_t 					nBasePrice;			/* 基本价格 */
	table_int_t 					nBMaxDur;			/* max耐久 */
	table_int_t 					nTermHour;			/* 到期时限，单位：小时 */
	LPCSTR					nStarLeveL;			/* 星级 */
	table_int_t 					nNatureHoleNum;		/* 天然孔数目 */
	table_int_t 					nMaxHoleNum;		/* 最大孔数目 */
	table_int_t 					nProfessionalReq;	/* 职业要求 */
	table_int_t 					nPaixing;			/* 装备牌型 */
	table_int_t 					nEquipScore;		/* 装备分数 */
	table_int_t 					nBaseAttackNear;	/* 基础近程攻击 */
	table_int_t 					nBaseAttackFar;		/* 基础远程攻击 */
	table_int_t 					nBaseAttackMagic;	/* 基础魔法攻击 */
	table_int_t 					nBaseDEefNear;		/* 基础近程防御 */
	table_int_t 					nBaseDefFar;		/* 基础远程防御 */
	table_int_t 					nBaseDefMagic;		/* 基础魔法防御 */

	/* 装备对人物属性的影响 */
	EQUIP_EFFECT_ATTR	stEffectAttr[EQUIP_EFFECT_ATTR_MAXNUM];

	/* 装备对技能的影响 */
	EQUIP_EFFECT_SKILL	stADDEffectSkill[EQUIP_ADDEFFECT_SKILL_MAXNUM]; /* 附加技能 */
	EQUIP_EFFECT_SKILL	stEffectSkill[EQUIP_EFFECT_SKILL_MAXNUM];		/* 影响技能 */
	table_int_t 					nEventScript;
	table_int_t 					nAddParam1;						/* 预留 */
	table_int_t 					nAddParam2;						/* 预留 */
	table_int_t 					nAddParam3;						/* 预留 */
	/*
	 * // 装备对人物属性的影响 table_int_t stEffectAttr[ EQUIP_EFFECT_ATTR_MAXNUM * 2] ;
	 * // 装备对技能的影响 table_int_t ADDEffectSkill[EQUIP_ADDEFFECT_SKILL_MAXNUM * 2];
	 * // 附加技能 table_int_t EffectSkill[EQUIP_EFFECT_SKILL_MAXNUM * 2];
	 * // 影响技能
	 */
};

/* by soongxl 扩展包 */
#define TABLE_ITEM_EXTBAG (350)
struct _TABLE_ITEM_EXTBAG
{
	table_int_t 		nID;										/* id */
	table_int_t 		nClass;										/* class */
	table_int_t 		nType;										/* 类型 */
	table_int_t 		nIndex;
	LPCSTR	szIcon;										/* icon */
	LPCSTR	szName;										/* 名字 */
	LPCSTR	szDesc;										/* 描述 */
	table_int_t 		nRule;										/* 适应规则 */
	table_int_t 		nBasePrice;									/* 基本价格 */
	table_int_t 		nSalePrice;									/* 出售价格 */
	table_int_t 		nValidTime;									/* 有效时间 */
	table_int_t 		nSize;										/* 有效格子数 */
	table_int_t 		nAddParam1;									/* 预留 */
	table_int_t 		nAddParam2;									/* 预留 */
	table_int_t 		nAddParam3;									/* 预留 */
	LPCTSTR szTypeDesc;									/* 物品的类型描述 */
	LPCTSTR nDropModelId;								/* 掉落时的外形 */
	LPCTSTR szDropEffect;								/* 掉落模型附属特效 */
	table_int_t 		szDropSound;								/* 掉落声音 */
	LPCTSTR szDropVisColor;								/* 显示名称颜色 */
	LPCTSTR szAnimateFrame;								/* 动画帧 */
};

/* 物品定义表_药瓶 (ITEM_06) */
#define TABLE_ITEM_MEDIC	(306)
struct _TABLE_ITEM_MEDIC									/* ef */
{
	table_int_t 		nID;										/* id */
	table_int_t 		nClass;										/* class */
	table_int_t 		nType;										/* 类型 */
	table_int_t 		nIndex;
	LPCSTR		szIcon;										/* icon */
	LPCSTR		szName;										/* 名字 */
	LPCSTR		szDesc;										/* 描述 */
	table_int_t 		nLevel;										/* 等级 */
	table_int_t 		iReqInherenceLevel;							/* rj 2010-8-23 天赋等级 */
	table_int_t 		iReqPersonLevel;							/* rj 2010-8-23 个人等级 */
	LPCSTR		nProfessionalReq;							/* 职业需求 */
	table_int_t 		nBasePrice;									/* 基本价格 */
	table_int_t 		nSalePrice;									/* 出售价格 */
	table_int_t 		nRule;										/* 适应规则 */
	table_int_t 		nPileCount;									/* 叠放数量 */
	table_int_t 		nScriptID;									/* 脚本编号 */
	table_int_t 		nSkillID;									/* 技能编号 */
	table_int_t 		NOTCARE[2];									/* 需求技能等级 */
	table_int_t 		nMaxHold;									/* 最大持有数量 */
	table_int_t 		nTargetType;								/* 针对对象类型 eITEM_TARGET_TYPE */
	table_int_t 		nBroadcast;									/* 是否广播 */
	table_int_t 		nAddParam1;									/* 预留 */
	table_int_t 		nAddParam2;									/* 预留 */
	table_int_t 		nAddParam3;									/* 预留 */
	LPCTSTR		szTypeDesc;									/* 物品的类型描述 */
	LPCTSTR		nDropModelId;								/* 掉落时的外形 */
	LPCTSTR		szDropEffect;								/* 掉落模型附属特效 */
	table_int_t 		szDropSound;								/* 掉落声音 */
	LPCTSTR		szDropVisColor;								/* 显示名称颜色 */
	LPCTSTR		szAnimateFrame;								/* 动画帧 */
	table_int_t 		nQualityLevel;								/* 品质等级 */
	table_int_t 		nEffectId;									/* 效果ID */
	table_int_t 		nbRecord;									/* 是否计数道具 */
	table_int_t 		nRecordNum;									/* 次数 */
	table_int_t 		nPrescrId;									/* 对应的配方ID */
	table_int_t 		nReworkIndex;								/*洗石剂合成对应索引*/
	/* ... NOT CARE */
};

/* 物品定义表 任务物品表 */
#define TABLE_ITEM_TASK	(323)
struct _TABLE_ITEM_TASK									/* ef */
{
	table_int_t 		nID;										/* id */
	table_int_t 		nClass;										/* class */
	table_int_t 		nType;										/* 类型 */
	table_int_t 		nIndex;
	LPCSTR	szIcon;										/* icon */
	LPCSTR	szName;										/* 名字 */
	LPCSTR	szDesc;										/* 描述 */
	table_int_t 		nLevelRequire;								/* 等级 */
	table_int_t 		nBasePrice;									/* 基本价格 */
	table_int_t 		nSalePrice;									/* 出售价格 */
	table_int_t 		nRule;										/* 适应规则 */
	table_int_t 		nPileCount;									/* 叠放数量 */
	table_int_t 		nScriptID;									/* 脚本编号 */
	table_int_t 		nSkillID;									/* 技能编号 */
	table_int_t 		NOTCARE[2];									/* 需求技能等级 */
	table_int_t 		nMaxHold;									/* 最大持有数量 */
	table_int_t 		nTargetType;								/* 针对对象类型 eITEM_TARGET_TYPE */
	table_int_t 		nBroadcast;									/* 是否广播 */
	table_int_t 		nAddParam1;									/* 预留 */
	table_int_t 		nAddParam2;									/* 预留 */
	table_int_t 		nAddParam3;									/* 预留 */
	LPCTSTR szTypeDesc;									/* 物品的类型描述 */
	LPCTSTR szAnimateFrame;								/* 动画帧 */
	LPCTSTR szDropVisColor;								/* 显示名称颜色 */
	/* ... NOT CARE */
};

/* 宝石属性最大个数 */
#define EQUIP_GEMATTR_MAXNUM	4

/* 需求宝石最大数量 */
#define EQUIP_GEMNEED_MAXNUM	3

struct EQUIP_GEM_ATTR
{
	table_int_t nAttr;											/* 强化属性 */
	table_int_t nNum;											/* 强化数值 */
};

struct EQUIP_GEM_NEED
{
	table_int_t nGem;											/* 需求宝石 */
	table_int_t nGemNum;										/* 需求宝石NUM */
};

/* 物品定义表_宝石 (ITEM_07) */
#define TABLE_ITEM_GEM	(307)
struct _TABLE_ITEM_GEM									/* ef */
{
	table_int_t 				nID;
	table_int_t 				nClass;								/* 物品类型 */
	table_int_t 				nType;								/* 物品种类 */
	table_int_t 				nGemIndex;							/* 物品编号 */
	LPCTSTR			szIcon;								/* 图标 */
	table_int_t 				nRule;								/* 适应规则 */
	LPCTSTR			szWhere;							/* 镶嵌位置 */
	LPCTSTR			szName;
	LPCTSTR			szDesc;
	table_int_t 				nPrice;								/* 宝石基本的价格 */
	table_int_t 				nSalePrice;							/* 宝石出售的价格 */
	table_int_t 				nNeedMoney;							/* 所需金钱 */
	table_int_t 				nNeedEquipLevel;					/* 所需装备等级 */
	table_int_t 				nBroadcast;							/* 是否广播 */

	/*
	 * table_int_t nAttr[66];
	 * // 宝石的附加属性 // 5
	 */
	EQUIP_GEM_ATTR	stGemAttr[EQUIP_GEMATTR_MAXNUM];	/* 宝石的附加属性 */
	EQUIP_GEM_NEED	stGemNeed[EQUIP_GEMNEED_MAXNUM];	/* 需求其他宝石的信息 */
	table_int_t 				nShowLevel;						/* 显示等级 */
	table_int_t 				nAddParam1;						/* 预留 */
	table_int_t 				nAddParam2;						/* 预留 */
	table_int_t 				nAddParam3;						/* 预留 */
	LPCTSTR			szColor;						/* 附加属性的颜色 */
	LPCTSTR			szTypeDesc;						/* 类型描述 */
	LPCTSTR			szEffectColor;					/* 特效颜色值 */
	table_int_t 				nEffectIndex;					/* 特效索引 */
	LPCTSTR			nDropModelId;					/* 掉落时的外形 */
	LPCTSTR			szDropEffect;					/* 掉落模型附属特效 */
	table_int_t 				szDropSound;					/* 掉落声音 */
	LPCTSTR			szDropVisColor;					/* 显示名称颜色 */
	LPCTSTR			szAnimateFrame;					/* 动画帧 */
	table_int_t 				nReworkIndex;

	/* ... NOT CARE */
};

/* Gem_Type.tab client 使用 for 宝石需求信息 */
#define TABLE_ITEM_GEM_CLIENT_TYPE	(314)
struct _TABLE_ITEM_GEM_CLIENT_TYPE					/* ef */
{
	table_int_t 		nID;
	LPCTSTR szTypeDesc;								/* 类型描述 */
};

/*
 * 物品定义表_地图 (ITEM_08) #define TABLE_ITEM_STOREMAP (308) ;
 * struct _TABLE_ITEM_STOREMAP // ef ;
 * { ;
 * table_int_t nID;
 * table_int_t nClass;
 * table_int_t nQuality;
 * //remove ;
 * table_int_t nType;
 * LPCSTR szIcon;
 * table_int_t nIndex;
 * LPCSTR szName;
 * LPCSTR szDesc;
 * table_int_t nLevelRequire;
 * table_int_t nRule;
 * //....................... ;
 * //... NOT CARE ;
 * };
 * 套装组合后附加属性 (ITEM_15)
 */
#define TABLE_ITEM_SETATT (315)
struct _TABLE_ITEM_SETATT
{
	table_int_t nID;
	table_int_t nAtt[66];									/* 59 */
};

/*
 * // 普通装备外形表 #define TABLE_ITEM_COMMON_EQUIP_VISUAL (316) struct
 * _TABLE_ITEM_COMMON_EQUIP_VISUAL { table_int_t nIndex;
 * // 编号 区分同一id的装备 table_int_t nID;
 * // 例如 10010000 普通装备末4位为0000 table_int_t level;
 * // client不使用 table_int_t nModelID;
 * // 模型id，可以在模型表里找到对应的具体模型 LPCTSTR szName;
 * // 装备名称 例如 xx刀 LPCTSTR szDes;
 * // 说明 描述信息 LPCTSTR szIcon;
 * // 图标 ui显示用 LPCTSTR szType;
 * // 刀, 类型描述 LPCTSTR nDropModelId;
 * //掉落时的外形 // LPCTSTR szDropEffect;
 * //掉落模型附属特效 table_int_t szDropSound;
 * //掉落声音 LPCTSTR szDropVisColor;
 * //显示名称颜色 //LPCTSTR szEffect[EQUIP_EFFECT_MAX_NUM*2];
 * //特效 EQUIP_EFFECT szEffect[EQUIP_EFFECT_MAX_NUM];
 * //特效 };
 */
#define TABLE_ITEM__EQUIP_VISUAl_MAXNUM	99
#define TABLE_ITEM__EQUIP_GEM_MAXNUM		7

/*
 * //高级装备外形表 #define TABLE_ITEM_ADVANCED_EQUIP_VISUAL (317) struct
 * _TABLE_ITEM_ADVANCED_EQUIP_VISUAL { table_int_t nIndex;
 * // 编号 对高级装备来说 没用的列 table_int_t nID;
 * // 例如 10010001 table_int_t nModelID;
 * // 模型id，可以在模型表里找到对应的具体模型 LPCTSTR szName;
 * // 装备名称 例如 xx刀 LPCTSTR szDes;
 * // 说明 描述信息 LPCTSTR szIcon;
 * // 图标 ui显示用 LPCTSTR szType;
 * // 刀 LPCTSTR nDropModelId;
 * //掉落时的外形 // LPCTSTR szDropEffect;
 * //掉落模型附属特效 table_int_t szDropSound;
 * //掉落声音 LPCTSTR szDropVisColor;
 * //显示名称颜色 // LPCTSTR szEffect[EQUIP_EFFECT_MAX_NUM*2];
 * //特效 EQUIP_EFFECT szEffect[EQUIP_EFFECT_MAX_NUM];
 * //特效 };
 * ;
 * 高级装备外形表
 */
#define TABLE_ITEM_EQUIP_VISUAL	(316)
struct _TABLE_ITEM_EQUIP_VISUAL
{
	table_int_t 				nID;							/* 例如 10010001 */
	table_int_t 				nModelID;						/* 模型id，可以在模型表里找到对应的具体模型 */
	LPCTSTR			szName;							/* 装备名称 例如 xx刀 */
	LPCTSTR			szDes;							/* 说明 描述信息 */
	LPCTSTR			szIcon;							/* 图标 ui显示用 */
	LPCTSTR			szType;							/* 刀 */

	LPCTSTR			nDropModelId;					/* 掉落时的外形 */
	LPCTSTR			szDropEffect;					/* 掉落模型附属特效 */
	table_int_t 				szDropSound;					/* 掉落声音 */
	LPCTSTR			szDropVisColor;					/* 显示名称颜色 */

	EQUIP_EFFECT	szEffect[EQUIP_EFFECT_MAX_NUM]; /* 特效 */
	LPCTSTR			szAnimateFrame;					/* 动画帧 */

	table_int_t 			nType;							// 装备类型
};

/*
 * 装备属性组表 〈 普通装备才会用到〉对应的装备表的普通装备的属性会填充-1 ;
 * #define TABLE_ITEM_ATTR_GROUP 322 struct _TABLE_ITEM_ATTR_GROUP { table_int_t nGroupId;
 * // 属性组Id LPCTSTR szGroupName;
 * // 属性组名字 table_int_t nProbability;
 * // 属性组几率 table_int_t nAttrId[EQUIP_EFFECT_ATTR_MAXNUM];
 * // 影响属性id 共16项 对应到装备表的16项 };
 */
#define EQUIP_LEVEL_MAXNUM	100

/*
 * 装备属性等级表〈 普通装备才会用到〉 ;
 * #define TABLE_ITEM_ATTR_LEVEL 321 struct _TABLE_ITEM_ATTR_LEVEL { table_int_t nAttrID;
 * //属性id LPCSTR szName;
 * //属性名 table_int_t nLevel[EQUIP_LEVEL_MAXNUM];
 * //装备影响属性 };
 * ;
 * 装备玩法 装备打孔 ;
 * Equip_HoleReqInfo.ta
 */
#define TABLE_EQUIP_HOLE_INFO 330
#define EQUIP_PART_ON_HOLE	(EQUIP_TYPE_NUM-1)
struct _TABLE_EQUIP_HOLE_INFO
{
	table_int_t nHoleNum;						/* 孔的数目 */
	table_int_t nItemNeed[EQUIP_PART_ON_HOLE];	/* 需要的打孔道具 */
	table_int_t nItemNeedNum;					/* 需要的道具数量 */
	table_int_t nMoneyNeed;						/* 需要的金钱数量 */
	table_int_t nSuccessRatio;					/* 成功率 */
	/*
	 * LPCTSTR szName;
	 * //道具名称
	 */
};

/*
 * 装备绑定 ;
 * Equip_bind.tab
 */
#define TABLE_EQUIP_BINDING_INFO	331

struct _TABLE_EQUIP_BINDING_INFO
{
	table_int_t nBindingLevel;					/* 绑定级别 */
	table_int_t nIntensifyInfo;					/* 强化比例 */
	table_int_t nGemNeed[MAX_BIND_GEMREQ_NUM];	/* 需求宝石 */
	table_int_t nNeedMoney[MAX_BIND_GEMREQ_NUM];	/* 所需金钱 */
	table_int_t nNeedEquipLevel[MAX_BIND_GEMREQ_NUM];	/* 所需金钱装备等级,先消耗此等级对应道具，其次消耗高级灵魂印道具*/
};

/*
 * 装备打星 ;
 * Equip_levelup.tab
 */
#define TABLE_EQUIP_ADD_START		332
#define ADD_STAR_GEM_TYPE		5
#define EQUIP_STAR_NUM_LIMIT	15
struct EQUIP_ADD_STAR_INFO
{
	table_int_t nEquipLevelReqGemID[MAX_LEVELUP_GEMREQ_NUM];		//装备等级需求宝石
	/*
	 * table_int_t nGemIdSave;
	 * //其他需求 预留的需求
	 */
	table_int_t nSuccessRate[MAX_LEVELUP_GEMREQ_NUM];				//成功概率
	table_int_t nPunishment;					/* 失败惩罚 */
	table_int_t nNeedMoney[MAX_LEVELUP_GEMREQ_NUM];/* 所需金钱 */
	table_int_t nIntensifyInfo;					/* 强化比例 */
	table_int_t nIntensifyType;					/* 强化属性类别 */
	table_int_t nNeedPlayerLevel;				/* 需要的人物等级 */
	table_int_t nStartStepLevel;				/* 星级对应位 */
	table_int_t 	nLevelNeed[MAX_LEVELUP_GEMREQ_NUM];/* 等级段 */
};

struct _TABLE_EQUIP_ADD_START
{
	table_int_t 					nIndex;			/* 编号 */
	table_int_t 					nStarLevel;		/* 星级 */
	table_int_t 					nEquipPoint;	/* 装备点 */
	EQUIP_ADD_STAR_INFO Add_Star_Info[ADD_STAR_GEM_TYPE];
};

/*
 * 装备特修表 ;
 * Equip_SpecialRepair.tab
 */
#define TABLE_EQUIP_SP_REPAIR 333

struct _TABLE_EQUIP_SP_REPAIR
{
	table_int_t nDestItemID;					/* 欲修理物品ID */
	table_int_t nUseItemID;						/* 消耗物品ID */
	table_int_t nUseItemCount;					/* 恢复耐久点 */
	table_int_t nNeedMoney;						/* 所需金钱 */
};

#define MAX_EQUIP_PROMATL_NUM	4
struct _TABLE_EQUIP_PRO_MAT
{
	table_int_t nMaterial;						/* 材料类 */
	table_int_t nMaterialNum;					/* 材料数量 */
	table_int_t nMatLowestLv;					/* 材料最低等1 */
	table_int_t nMaterialLoss;					/* 拆解损耗比例4 */
};

#define MAX_EQUIP_RWMATL_NUM	3		/* 改造材料数量 */

struct _TABLE_EQUIP_REWORK_MAT
{
	table_int_t nReWorkMaterial;				/* 改造1材料类 */
	table_int_t nReWorkMatNum;					/* 改造1材料数量 */
	table_int_t nReWorkMatLowestLv;				/* 改造1材料最低等级 */
};

#define MAX_EQUIP_SPIRIT_RWMATL_NUM 3	/* 灵魂改造材料数量 */

#define TABLE_EQUIP_PRODUCT_INFO		334

struct _TABLE_EQUIP_PRODUCT_INFO
{
	table_int_t 						nFormulaId; /* 配方号 */
	table_int_t 						nProductId; /* 产品ID */
	LPCSTR						szFormulaName;		/* 配方名称 */
	table_int_t 						nProductNum;		/* 产品数量 */

	/*
	 * table_int_t nMaterial1;
	 * //材料类1 ;
	 * table_int_t nMaterial1Num;
	 * //材料数量1 ;
	 * table_int_t nMat1LowestLv;
	 * //材料最低等级1 ;
	 * table_int_t nMaterial1Loss;
	 * //拆解损耗比例1 ;
	 * table_int_t nMaterial2;
	 * //材料类2 ;
	 * table_int_t nMaterial2Num;
	 * //材料数量2 ;
	 * table_int_t nMat2LowestLv;
	 * //材料最低等级2 ;
	 * table_int_t nMaterial2Loss;
	 * //拆解损耗比例2 ;
	 * table_int_t nMaterial3;
	 * //材料类3 ;
	 * table_int_t nMaterial3Num;
	 * //材料数量3 ;
	 * table_int_t nMat3LowestLv;
	 * //材料最低等级3 ;
	 * table_int_t nMaterial3Loss;
	 * //拆解损耗比例3 ;
	 * table_int_t nMaterial4;
	 * //材料类4 ;
	 * table_int_t nMaterial4Num;
	 * //材料数量4 ;
	 * table_int_t nMat4LowestLv;
	 * //材料最低等级4 ;
	 * table_int_t nMaterial4Loss;
	 * //拆解损耗比例4
	 */
	_TABLE_EQUIP_PRO_MAT		szMat[MAX_EQUIP_PROMATL_NUM];

	/*
	 * table_int_t nReWorkMaterial1;
	 * //改造1材料类 ;
	 * table_int_t nReWorkMat1Num;
	 * //改造1材料数量 ;
	 * table_int_t nReWorkMat1LowestLv;
	 * //改造1材料最低等级 ;
	 * table_int_t nReWorkMaterial2;
	 * //改造2材料类 ;
	 * table_int_t nReWorkMat2Num;
	 * //改造2材料数量 ;
	 * table_int_t nReWorkMat2LowestLv;
	 * //改造2材料最低等级 ;
	 * table_int_t nReWorkMaterial3;
	 * //改造3材料类 ;
	 * table_int_t nReWorkMat3Num;
	 * //改造3材料数量 ;
	 * table_int_t nReWorkMat3LowestLv;
	 * //改造3材料最低等级
	 */
	_TABLE_EQUIP_REWORK_MAT	szRwMat[MAX_EQUIP_RWMATL_NUM];

	table_int_t 						nOperateTime;		/* 操作时间 */
	table_int_t 						nScriptId;			/* 脚本ID */
	table_int_t 						nProNeedMoney;		/* 打造金钱 */
	table_int_t 						nReNeedMoney;		/* 改造金钱 */
	table_int_t 						nProLevel;			/* 产品等级 */
	table_int_t 						nProBodyBelong;		/* 所属部件 */
	table_int_t 						nProAttrBelong;		/* 属性归属 */

	/*
	 * table_int_t nNpcId;
	 * //npcid
	 */
	LPCSTR						szNpcIdList;
	table_int_t 						nCanSelMatLevel;	/* 是否可以选择材料等级 */
};

/* MaterialLevel_info.tab */
#define TABLE_EQUIP_MATERIAL_INFO 335

struct _TABLE_EQUIP_MATERIAL_INFO
{
	table_int_t nMaterialGrade;					/* 材料等级 */
	table_int_t nMaterialValues;				/* 材料分值 */
};

/*
 * pai_info.tab ;
 * 每张牌
 */
#define TABLE_EQUIP_CARD_INFO 336

struct _TABLE_EQUIP_CARD_INFO
{
	table_int_t 		nCardId;					/* 牌id 对应于枚举 例如 EQUIPPAI_ANY 任意牌 */
	LPCTSTR		szCardName;					/* 牌名 */
	table_int_t 		nAttrId;					/* 属性id */
	table_int_t 		nAttrNum;					/* 属性值 */
	table_int_t 		nRata;						/* 概率 */
	table_int_t 		nPaiItemId;					/* 牌对应的item id */
};

/*
 * chain_info.tab ;
 * 3张牌组
 */
#define TABLE_EQUIP_CARD_GROUP_INFO	337

struct _TABLE_EQUIP_CARD_GROUP_INFO
{
	table_int_t 		nGroupId;					/* 组id */
	LPCTSTR		sznGroupName;				/* 组合名字 */
	table_int_t 		nNeedCardId1;				/* 需求牌型id */
	table_int_t 		nNeedCardId2;				/* 需求牌型id */
	table_int_t 		nNeedCardId3;				/* 需求牌型id */
	table_int_t 		nAttrId;					/* 强化属性 */
	table_int_t 		nAttrNum;					/* 强化数值 */
	LPCTSTR		szEffect;					/* 特效 */
};

/*
 * soul_info.tab ;
 * 整套牌 用于激活
 */
#define EQUIP_CARD_ACTIVE_ATTR_NUM	4

struct EQUIP_CARD_ATTR
{
	table_int_t nAttrId;						/* 强化属性 */
	table_int_t nAttrNum;						/* 强化数值 */
};

#define EQUIP_CARD_ACTIVE_EFFECT_NUM	2

struct EQUIP_CARD_EFFECT
{
	LPCTSTR szEffect;					/* 特效 */
	LPCTSTR szEffectBindPoint;			/* 特效绑定点 */
};

#define TABLE_EQUIP_CARD_ALL	338

struct _TABLE_EQUIP_CARD_ALL
{
	static const table_int_t 	EQUIP_CARD_ALL_Sign_COLUMN = 16;
	table_int_t 					nGroupId;		/* 组id */
	LPCTSTR				sznGroupName;	/* 组合名字 */
	table_int_t 					nSoulType;   /*胡牌类别*/
	table_int_t 					nNeedGropId1;	/* 需求组合id */
	table_int_t 					nNeedGropId2;	/* 需求组合id */
	table_int_t 					nNeedGropId3;	/* 需求组合id */
	table_int_t 					nNeedGropId4;	/* 需求组合id */
	table_int_t 					nNeedGropId5;	/* 需求组合id */

	EQUIP_CARD_ATTR		stAttr[EQUIP_CARD_ACTIVE_ATTR_NUM]; /* 强化属性 */
	table_int_t 					nNeedSignEquip;						/* 需要的符文 */
	EQUIP_CARD_EFFECT	stEffect[EQUIP_CARD_ACTIVE_EFFECT_NUM];
};

/*
 * 换牌表格 ;
 * ChangePai_info.tab
 */
#define TABLE_EQUIP_CARD_TARGET	339

struct _TABLE_EQUIP_CARD_TARGET
{
	table_int_t 		nId;					/* 道具i */
	LPCTSTR szName;					/* 说明 */
	table_int_t 		nTargetId;				/* 目标id */
	table_int_t 		nNeedMoney;				/* 所需金钱 */
};

/*
 * equipset_attr.tab ;
 * 装备套装表
 */
#define TABLE_EQUIP_SET_INFO	340
#define EQUIP_SET_ATTR_NUM	4

struct EQUIP_SET_ATTR
{
	table_int_t nNeedNum;					/* 激活该属性的数量 */
	table_int_t nAttrId;					/* 属性id */
	table_int_t nAttrNum;					/* 属性数值 */
};
#define EQUIP_SET_EFFECT_NUM	4
struct EQUIP_SET_EFFECT
{
	LPCTSTR szEffectName;			/* 特效 */
	LPCTSTR szBindPointName;		/* 绑定点 */
};

struct _TABLE_EQUIP_SET_INFO
{
	table_int_t 					nSetId;		/* 套装id */
	LPCTSTR				szSetName;	/* 套装名字 */
	table_int_t 					nSetNum;	/* 套装件数 */
	LPCTSTR				szId;		/* 套装包含的系列id */
	EQUIP_SET_ATTR		stAttr[EQUIP_SET_ATTR_NUM]; /* 套装属性 */
	EQUIP_SET_EFFECT	stEffect[EQUIP_SET_EFFECT_NUM];
};
#define TABLE_EQUIP_IMPACT		341					/* buff_logic.tab */
#define IMPACT_PARAM_MAX_NUM	16
struct _TABLE_EQUIP_IMPACT
{
	/* 在表格中对应的纪录的索引 */
	table_int_t 		m_nDataIndex;

	/* 名字 */
	LPCTSTR m_szName;
	LPCTSTR m_szParamDes[IMPACT_PARAM_MAX_NUM * 2];

	/*
	 * 在表格中对应的纪录的索引 ;
	 * table_int_t m_nDataIndex;
	 * 对应的技能ID ;
	 * table_int_t m_nLogicID;
	 * 没用 名字 ;
	 * LPCTSTR m_szName;
	 * 描述 ;
	 * LPCTSTR m_szLogicDesc;
	 * 没用 是否为持续性效果 ;
	 * table_int_t m_bIsOverTimed;
	 * 没用 瞬发或驻留效果ID ;
	 * table_int_t m_nImpactID;
	 * 没用 互斥组ID ;
	 * table_int_t m_nMutexID;
	 * 没用 互斥优先级 ;
	 * table_int_t m_nLevel;
	 * 没用 影响性质 ;
	 * table_int_t m_nStandFlag;
	 * 没用 死后是否保留 ;
	 * table_int_t m_bRemainOnCorpse;
	 * 没用 是否可以被技能驱散 ;
	 * table_int_t m_bCanBeDispeled;
	 * 没用 是否可以被手动取消 ;
	 * table_int_t m_bCanBeCanceled;
	 * 没用 是否需要引导支持 ;
	 * table_int_t m_bNeedChannelSupport;
	 * 没用 是否是直通效果,即忽略所有影响 ;
	 * table_int_t m_bIgnoreFliter;
	 * 没用 受到伤害时是否消失 ;
	 * table_int_t m_bFadeOutWhenUnitOnDamage;
	 * 没用 开始动作时是否消失 ;
	 * table_int_t m_bFadeOutWhenUnitStartActions;
	 * 没用 下线就消失否 ;
	 * table_int_t m_bFadeOutWhenUnitOffline;
	 * 没用 下线是否仍然计时 ;
	 * table_int_t m_bStillTimingWhenUnitOffline;
	 * 没用 总持续时间(毫秒) ;
	 * table_int_t m_nContinuance;
	 * 没用 发作时间间隔(毫秒) ;
	 * table_int_t m_nInterval;
	 * 没用 互斥规则是否参考制造者ID ;
	 * table_int_t m_bMutexByCaster;
	 * 没用 预留 2 3 4 5 ;
	 * table_int_t m_nSaved[4];
	 * 没用 LPCTSTR m_szParamDes[IMPACT_PARAM_MAX_NUM *2];
	 * 参数值 ;
	 * LPCTSTR m_szParaValue;
	 * 没用 效果描述 ;
	 * LPCTSTR m_szDescription;
	 * 没用 先知或同类技能需要的子弹数量 ;
	 * table_int_t m_uBallCount;
	 * 没用 子弹的生命周期 ;
	 * table_int_t m_uBallLife;
	 * 没用
	 */
};

/*
 * -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-// ;
 * 声音相关 // ;
 * -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//
 * 声音文件定义 (SOUND_0
 */
#define TABLE_SOUND_INFO	(401)
struct _TABLE_SOUND_INFO
{
	table_int_t 		nID;
	LPCSTR	pSoundFile;
};

/*
 * 特效相关 // ;
 * -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//
 * 特效定义 (EFFECT_01) #define TABLE_EFFECT_DEFINE (501) ;
 * struct _TABLE_EFFECT_DEFINE // bc ;
 * { ;
 * table_int_t nID;
 * LPCSTR pEffectType;
 * LPCSTR pParam1;
 * LPCSTR pParam2;
 * LPCSTR pParam3;
 * LPCSTR pParam4;
 * LPCSTR pParam5;
 * LPCSTR pParam6;
 * };
 * ;
 * 技能相关 // ;
 * -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//
 * 天赋定义表 (SKILL_01) #define TABLE_SKILL_TALENT (601) ;
 * struct _TABLE_SKILL_TALENT // bc ;
 * { ;
 * table_int_t nID;
 * LPCSTR pszName;
 * table_int_t nMenpaiID;
 * LPCSTR pszDesc;
 * LPCSTR pszIconName;
 * };
 * 附加效果 (SKILL_02) #define TABLE_SKILL_ADDIMPACT (602) ;
 * struct _TABLE_SKILL_ADDIMPACT // bc ;
 * { ;
 * table_int_t nID;
 * table_int_t nParamNum;
 * LPCSTR pDesc;
 * table_int_t nAddAttributeNum;
 * LPCSTR pAddAttribute1;
 * LPCSTR pAddAttribute2;
 * LPCSTR pAddAttribute3;
 * LPCSTR pAddAttribute4;
 * table_int_t nSpliceID;
 * LPCSTR pIcon;
 * };
 * ;
 * 子弹效果定义 (SKILL_03) #define TABLE_SKILL_BULLET (603) ;
 * struct _TABLE_SKILL_BULLET ;
 * { ;
 * table_int_t nID;
 * //子弹类型 ;
 * table_int_t nType;
 * /* ;
 * | 0 - 瞬间到达 ;
 * | 1 - 移动到达 ;
 */
#define TABLE_BUFF_IMPACT (604)

/* TABLE_BUFF_IMPACT DIRECTLY附加效果 (DIRECTLY_IMPACT) */
#define TABLE_DIRECTLY_IMPACT (605)

/* TABLE_DIRECTLY_IMPACT 子弹 (BULLET) */
#define TABLE_BULLET_DATA (606)

/* TABLE_BULLET_DATA 技能 (SKILL) */
#define TABLE_SKILL_DATA	(607)

#define TABLE_SPECIAL_OBJ_DATA	(610)
struct _TABLE_SPECIAL_OBJ_DATA						/* cd */
{
	table_int_t 		m_nID;						/* ID */
	LPCSTR		m_lpszName;					/* 名称 */
	table_int_t 		m_nType;					/* 类别（服务器专用） */
	LPCSTR		m_lpszToolTips;				/* ToolTips */
	table_int_t 		m_nLogicID;					/* 逻辑ID（服务器专用） */
	table_int_t 		m_nStealthLevel;			/* 隐形级别（服务器专用，陷阱专用） */
	table_int_t 		m_nTrapFlags;				/* 陷阱标记位集合（服务器专用，陷阱专用） */
	table_int_t 		m_nActiveTimes;				/* 可以激发的次数（服务器专用） */
	LPCSTR		m_lpszEffect_Normal;		/* 生存期持续特效 */
	LPCSTR		m_lpszSound_Normal;			/* 生存期持续音效 */
	LPCSTR		m_lpszEffect_Active;		/* 激发特效 */
	LPCSTR		m_lpszSound_Active;			/* 激发音效 */
	LPCSTR		m_lpszEffect_Die;			/* 死亡特效 */
	LPCSTR		m_lpszSound_Die;			/* 死亡音效 */
	table_int_t 		m_nReserve1;				/* 预留 */
	table_int_t 		m_nReserve2;				/* 预留 */
	table_int_t 		m_nReserve3;				/* 预留 */
	table_int_t 		m_nBulletID;				/* 子弹ID */
	table_int_t 		m_nDuration;				/* 持续时间（服务器专用） */
	table_int_t 		m_nInterval;				/* 激活或触发时间间隔（服务器专用） */
	table_float_t 		m_nTriggerRadius;			/* 触发半径（服务器专用，陷阱专用） */
	table_float_t 		m_nEffectRadius;			/* 影响半径（服务器专用，陷阱专用） */
	table_int_t 		m_nEffectUnitNum;			/* 影响个体数目（服务器专用，陷阱专用） */
	table_int_t 		m_nReserve4;				/* 预留 */
	table_int_t 		m_nReserve5;				/* 预留 */
	table_int_t 		m_nReserve6;				/* 预留 */
	table_int_t 		m_nReserve7;				/* 预留 */
	table_int_t 		m_nReserve8;				/* 预留 */
	LPCSTR		m_lpszParamDesc0;			/* 参数说明（服务器专用） */
	table_int_t 		m_nParam0;					/* 参数值（服务器专用） */
	LPCSTR		m_lpszParamDesc1;			/* 参数说明（服务器专用） */
	table_int_t 		m_nParam1;					/* 参数值（服务器专用） */
	LPCSTR		m_lpszParamDesc2;			/* 参数说明（服务器专用） */
	table_int_t 		m_nParam2;					/* 参数值（服务器专用） */
	LPCSTR		m_lpszParamDesc3;			/* 参数说明（服务器专用） */
	table_int_t 		m_nParam3;					/* 参数值（服务器专用） */
	LPCSTR		m_lpszParamDesc4;			/* 参数说明（服务器专用） */
	table_int_t 		m_nParam4;					/* 参数值（服务器专用） */
	LPCSTR		m_lpszParamDesc5;			/* 参数说明（服务器专用） */
	table_int_t 		m_nParam5;					/* 参数值（服务器专用） */
	LPCSTR		m_lpszParamDesc6;			/* 参数说明（服务器专用） */
	table_int_t 		m_nParam6;					/* 参数值（服务器专用） */
	LPCSTR		m_lpszParamDesc7;			/* 参数说明（服务器专用） */
	table_int_t 		m_nParam7;					/* 参数值（服务器专用） */
	LPCSTR		m_lpszParamDesc8;			/* 参数说明（服务器专用） */
	table_int_t 		m_nParam8;					/* 参数值（服务器专用） */
	LPCSTR		m_lpszParamDesc9;			/* 参数说明（服务器专用） */
	table_int_t 		m_nParam9;					/* 参数值（服务器专用） */
	LPCSTR		m_lpszParamDesc10;			/* 参数说明（服务器专用） */
	table_int_t 		m_nParam10;					/* 参数值（服务器专用） */
	LPCSTR		m_lpszParamDesc11;			/* 参数说明（服务器专用） */
	table_int_t 		m_nParam11;					/* 参数值（服务器专用） */
	LPCSTR		m_lpszParamDesc12;			/* 参数说明（服务器专用） */
	table_int_t 		m_nParam12;					/* 参数值（服务器专用） */
	LPCSTR		m_lpszParamDesc13;			/* 参数说明（服务器专用） */
	table_int_t 		m_nParam13;					/* 参数值（服务器专用） */
	LPCSTR		m_lpszParamDesc14;			/* 参数说明（服务器专用） */
	table_int_t 		m_nParam14;					/* 参数值（服务器专用） */
	LPCSTR		m_lpszParamDesc15;			/* 参数说明（服务器专用） */
	table_int_t 		m_nParam15;					/* 参数值（服务器专用） */
	LPCSTR		m_lpszInfo;					/* 详细说明(内部使用) */
};

/* 任务 (QUEST) */
#define TABLE_QUEST_DELIVERY	(620)
struct _TABLE_QUEST_DELIVERY
{
	table_int_t nQuestIndex;
	table_int_t nDeliveryItemID1;
	table_int_t nDeliveryItemNum1;
	table_int_t nDeliveryItemID2;
	table_int_t nDeliveryItemNum2;
	table_int_t nDeliveryItemID3;
	table_int_t nDeliveryItemNum3;
};

#define TABLE_QUEST_ENTERAREA	(621)
struct _TABLE_QUEST_ENTERAREA
{
	table_int_t 		nQuestIndex;
	LPCSTR		szAreaName;
	table_int_t 		nAreaSceneID;
	table_int_t 		nAreaID;
	table_int_t 		nAreaIndex;
	LPCSTR		szEnterArea;
	table_int_t 		nIfHaveDialog;
	LPCSTR		szEnterAreaDialog;
};

#define TABLE_QUEST_KILLMONSTER (622)
struct _TABLE_QUEST_KILLMONSTER
{
	table_int_t 		nQuestIndex;
	table_int_t 		nMonsterSceneID;
	LPCSTR		szMonsterName;
	LPCSTR		szMonsterTitle;
	table_int_t 		nMonsterType;
	table_int_t 		nMonsterLevelMin;
	table_int_t 		nMonsterLevelMax;
	table_int_t 		nCourseIndex;
	table_int_t 		nKillNum;
};

#define TABLE_QUEST_LOOTITEM	(623)
struct _TABLE_QUEST_LOOTITEM
{
	table_int_t 		nQuestIndex;
	table_int_t 		nLookItemType;
	table_int_t 		nItemID1;
	table_int_t 		nItemNum1;
	table_int_t 		nGrowPointType;
	table_int_t 		nCollectNum;
	table_int_t 		nMonsterSceneID;
	LPCSTR		szMonsterName;
	LPCSTR		szMonsterTitle;
	table_int_t 		nMonsterType;
	table_int_t 		nMonsterLevelMin;
	table_int_t 		nMonsterLevelMax;
	table_int_t 		nCourseIndex;
	table_int_t 		nDropRand;
	table_int_t 		nMaxDropNum;
};

#define TABLE_QUEST_USEITEM (624)
struct _TABLE_QUEST_USEITEM
{
	table_int_t 		nQuestIndex;
	table_int_t 		nUseItemType;
	table_int_t 		nItemID1;
	LPCSTR		szSceneID;
	table_int_t 		nPosX;
	table_int_t 		nPosZ;
	table_int_t 		nRadius;
	table_int_t 		nSkillID;
	LPCSTR		szUseItemDesc;
	table_int_t 		nUseDialog;
	LPCSTR		szUseItemDialog;
};

#define TABLE_QUEST_LIST	(625)
struct _TABLE_QUEST_LIST
{
	table_int_t 		nQuestID;					/* QuestID */
	table_int_t 		nScriptID;					/* ScriptID */
	table_int_t 		nQuestType;					/* 任务类型 0:普通表格任务 1:副本任务 2:循环任务 Add CZG */
	LPCSTR		szQuestName;				/* 任务名称 */
	LPCSTR		szQuestDisp;				/* 任务名称 */
	table_int_t 		nPreQuestID1;				/* 前续任务 */
	table_int_t 		nPreQuestID2;				/* 前续任务 */
	table_int_t 		nPreQuestID3;				/* 前续任务*/
	table_int_t 		nMinLevel;					/* Min等级 */
	table_int_t 		nMaxLevel;					/* Max等级 */
	table_int_t 		nNeedMoneyType;				/* 接任务金钱花费类型 */
	table_int_t 		nNeedMoney;					/* 接任务金钱花费 */
	table_int_t 		nCountry;					/* 国家:0-3,对应国家; -1无国家限制; */
	table_int_t 		nProfession;				/* 职业:0-5,对应职业;-1无职业限制;*/
	table_int_t 		nCamp;						/* 阵营 */
	table_int_t 		nQuestDest1;				/* 目标索引 */
	table_int_t 		nQuestDest2;				/* 目标索引 */
	table_int_t 		nQuestDest3;				/* 目标索引 */
	table_int_t 		nQuestDest4;				/* 目标索引 */
	table_int_t 		nQuestDest5;				/* 目标索引 */
	table_int_t 		nMoneyRewardType;			/* 固定金钱奖励类型 */
	table_int_t 		nMoneyRewardP1;				/* 固定金钱奖励 */
	table_int_t 		nMoneyRewardP2;				/* 固定金钱奖励 */
	table_int_t 		nMoneyRewardP3;				/* 固定金钱奖励 */
	table_int_t 		nExpRewardP1;				/* 固定经验奖励 */
	table_int_t 		nExpRewardP2;				/* 固定经验奖励 */
	table_int_t 		nExpRewardP3;				/* 固定经验奖励 */
	table_int_t 		nShengWangType;				/* 声望奖励 0朝廷声望 1江湖声望 2PK值 3荣誉（功勋） 4帮贡 5文采 6 威望 7 天赋经验 */
	table_int_t 		nShengWangRewartP1;
	table_int_t 		nShengWangRewartP2;
	table_int_t 		nShengWangRewartP3;
	table_int_t 		nEnergyRewardType;
	table_int_t 		nEnergyReward;
	table_int_t 		nGuildRewardType;
	table_int_t 		nGuildReward;
	table_int_t 		nFixItemID1;				/* 固定物品奖励ID */
	table_int_t 		nFixItemNum1;				/* 奖励个数 */
	table_int_t 		nFixItemID2;
	table_int_t 		nFixItemNum2;
	table_int_t 		nFixItemID3;
	table_int_t 		nFixItemNum3;
	table_int_t 		nFixItemID4;
	table_int_t 		nFixItemNum4;
	LPCSTR		szSelItemID1;				/* 随机物品奖励ID */
	table_int_t 		nSelItemNum1;				/* 奖励个数 */
	table_int_t 		nSelItemID2;
	table_int_t 		nSelItemNum2;
	table_int_t 		nSelItemID3;
	table_int_t 		nSelItemNum3;
	table_int_t 		nSelItemID4;
	table_int_t 		nSelItemNum4;
	table_int_t 		nSelItemID5;
	table_int_t 		nSelItemNum5;
	table_int_t 		nSelItemID6;
	table_int_t 		nSelItemNum6;
	table_int_t 		nRewardScript;				/* 是否还调用脚本奖励：0，不；1，调用对应scriptid脚本 */
	LPCSTR		szQuestDesc;				/* 任务描述 */
	LPCSTR		szQuestManual;				/* 任务攻略 */
	LPCSTR		szQuestContinue;			/* 继续任务 */
	LPCSTR		szQuestAbandon;				/* 放弃任务 */
	LPCSTR		szQuestSuccess;				/* 完成任务 */
	table_int_t 		nSubmitNPCGUID;				/* 交任务NPC的GUID */
	LPCSTR		szSubmitNPCName;			/* 交任务NPC名称 */
	table_int_t 		nSubmitNPCSceneID;			/* 交任务NPC所在地图ID */
	table_int_t 		nPathIndex;					/* 自动寻路索引(scenemap_npc.tab中对应的index),-1为无 */
	table_int_t 		nAfterQuestType;			/* 后续自动任务类型 */
	table_int_t 		nAfterQuestScriptID;		/* 后续自动接任务的ScriptID */

	LPCSTR		szQuestTarget1;				/* 任务目标1 */
	LPCSTR		szQuestTarget2;				/* 任务目标2 */
	LPCSTR		szQuestTarget3;				/* 任务目标3 */
	LPCSTR		szQuestTarget4;				/* 任务目标4 */
	LPCSTR		szQuestTarget5;				/* 任务目标5 */

	LPCSTR		szQuestHelp;				/* 任务帮助 */

	table_int_t 		nSyncServerFlag;			/* 服务器端同步标记，如果为1表示要从服务器端同步数据。否则使用客户端数据 */
	table_int_t 		nTechuFlag;					/* 任务特殊处理标记*/
	table_int_t 		nAcceptIconFlag;			/* 接任务图标标记 */
};

/*
 * 场景相关相关 // ;
 * -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//
 * 场景定义 (SCENE_01)
 */


#define TABLE_SCENE_DEFINE	(701)
struct _TABLE_SCENE_DEFINE				/* cd */
{
	static const table_int_t 	SCENE_SERVER_ID_COLUMN = 1;

	table_int_t					nLocalID;
	table_int_t					nServerID;
	LPCSTR					szName;
	table_int_t					nXSize;
	table_int_t					nZSize;
	LPCSTR					szSceneName;
	table_int_t					nBackSound;
	LPCSTR					szSceneMap;
	table_int_t					nWroldMapPosX;
	table_int_t					nWroldMapPosY;				/* 场景图标所在得位置 */
	table_int_t					nNameWroldMapPosX;
	table_int_t					nNameWroldMapPosY;			/* 场景名字所在得位置 */
	LPCSTR					szSceneType;				/* 场景得图标等级 */
	LPCSTR					szCityNameNormalImageSet;	/* 场景正常名字所用得图片资源 */
	LPCSTR					szCityNameNormalImage;		/* 场景正常名字所用得图片资源 */
	LPCSTR					szCityNameHoverImageSet;	/* 场景高亮名字所用得图片资源 */
	LPCSTR					szCityNameHoverImage;		/* 场景高亮名字所用得图片资源 */
	LPCSTR					szTransImg;					/* 场景切换图 */
	table_int_t					nSceneType;					/* 场景类型：无(0)、征战(1)、国家(2) */
	table_int_t					nCountryID;					/* 所属国家ID */
	table_int_t					nNameColorType;				/* 判断该场景的名称显示规则 */
	LPCSTR					szSceneOriginColorIDList;	// 场景原色标识 sceneColor.tab
	table_int_t					nPKType;					// PK类型
};

/*
 * 场景建筑物定义 (SCENE_02) #define TABLE_BUILDING_DEINFE (702) ;
 * struct _TABLE_BUILDING_DEFINE // bc ;
 * { ;
 * static const table_int_t MAX_LEVEL = 5;
 * ;
 * table_int_t nID;
 * // 资源id ;
 * LPCSTR szResType;
 * // 资源类型 ;
 * LPCSTR szLevel[MAX_LEVEL];
 * // 等级1-5资源 ;
 * };
 * 城市建筑物定义 (SCENE_03) #define TABLE_CITY_BUILDING (703) ;
 * struct _TABLE_CITY_BUILDING // de ;
 * { ;
 * table_int_t nID;
 * // id ;
 * table_int_t nCityID;
 * // 城市id(TABLE_CITY_DEINFE) ;
 * table_int_t nBuildingID;
 * // 建筑物id(TABLE_BUILDING_DEINFE) ;
 * LPCSTR szGfxPosition;
 * // 位置(gfx) ;
 * table_int_t nInitLevel;
 * // 初始等级 ;
 * LPCSTR szGfxOrientation;
 * // 旋转四元数(gfx) ;
 * };
 * 场景传送点定义 (SCENE_02
 */
#define TABLE_SCENE_POS_DEFINE	(917)
struct _TABLE_SCENE_POS_DEFINE
{
	table_int_t 		nID;					/* id */
	table_int_t 		nSceneID;				/* 场景的id */
	LPCSTR		szSceneName;			/* 场景的名字 */
	table_int_t 		nXPos;					/* 传送点的位置 */
	table_int_t 		nZPos;					/* 传送点的位置 */
	table_int_t 		nTargetSceneID;			/* 目标场景的id */
	LPCSTR		szTargetSceneName;		/* 目标场景的名字 */
	table_int_t 		nTargetXPos;			/* 目标传送点的位置 */
	table_int_t 		nTargetZPos;			/* 目标传送点的位置 */
	table_int_t 		nType;					/* 传送点类型 */
};

/* 传送点路径 */
#define TABLE_SCENE_TRANS_DEFINE	(802)
struct _TABLE_SCENE_TRANS_DEFINE		/* scene_trans_path.tab */
{
	table_int_t 		nID;					/* id */
	table_int_t 		nSrcSceneID;			/* 源场景 */
	table_int_t 		nTarSceneID;			/* 目标场景 */
	LPCSTR	szTransPath;			/* 路径点， 对应到传送点表 */
};

/*
 * UI相关 // ;
 * -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//
 * UI组定义 (UI_0
 */
#define TABLE_UI_LAYOUTDEFINE (801)
struct _TABLE_UI_LAYOUTDEFINE			/* de */
{
	table_int_t 		nID;
	LPCSTR	szName;
	LPCSTR	szLayout;
	table_int_t 		nDemise;
	LPCSTR	szScript;
	table_int_t 		nEscPriority;			/* ESC优先级 */

	/* 互斥规则 */
	table_int_t 		nOverlay;				/* 能否覆盖 */
	table_int_t 		nBeOverlay;				/* 能否被覆盖 */
	table_int_t 		nMouseLock;				/* 鼠标锁 */
	table_int_t 		nKeyLock;				/* 键盘锁 */
	table_int_t 		nChatLock;				/* 聊天锁 */

	LPCSTR	szDefaultPos;			/* 默认打开窗口的位置。 */
	table_int_t 		nCloseDistance;			/* 自动关闭距离 */

	/* 音效 */
	table_int_t 		nOpenWindowSound;		/* 打开窗口音效 */
	table_int_t 		nCloseWindowSound;		/* 关闭窗口音效 */
};

/*
 * 生活技能相关 // ;
 * -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-//
 * 资源生长点 (LIFE_01
 */
#define TABLE_LIFEABILITY_GROWPOINT	(901)
struct _TABLE_LIFEABILITY_GROWPOINT	/* cd */
{
	table_int_t 		nID;					/* 编号 */
	LPCSTR	szName;					/* 名称 */
	table_int_t 		nLifeAbility;			/* 技能编号 */
	LPCSTR	szMeshFile;				/* 模型文件 */
	table_int_t 		nQuestID;				/* 对应任务ID CZG */
	LPCSTR	szTips;					/* 默认提示 */
	table_int_t 		nTimeNeed;				/* 采集时间 */

	/*
	 * LPCSTR szNotcare[4];
	 */
	table_int_t 		nScriptID;				/* 脚本ID CZG */
	table_int_t 		nAnimOpen;				/* 打开动画 */
	LPCSTR	szEffect;				/* 特效 CZG */
	LPCSTR	szQuestId;			/* 任务ID */
};

/* 生活技能 (LIFE_02) */
#define TABLE_LIFEABILITY_DEFINE	(902)
struct _TABLE_LIFEABILITY_DEFINE		/* bc */
{
	table_int_t 		nID;
	table_int_t 		nLevelNeed;
	LPCSTR	szName;
	table_int_t 		nLevelMax;
	table_int_t 		nTimeOperation;			/* 采集读条时间 */
	table_int_t 		nToolNeed;				/* 采集所需工具 */
	table_float_t 	fPlatformDist;			/* 操作距离 */
	table_int_t 		nPlatformID;			/* 操作平台 */
	table_int_t 		nAnimOperation;			/* 人物动作 */
	LPCSTR	szExpTableName;			/* 技能升级对应的表，client不处理 */
	LPCSTR	szIconName;				/* 图标 */
	table_int_t 		nItemVisualLocator;		/* 动作挂接 */
	LPCSTR	szExplain;				/* 详细解释 */
	table_int_t 		nPopup;					/* 是否弹出下级界面 */
	LPCSTR	szProgressbarName;		/* 进度条名称 */
};

/* 生活技能 物品合成 (LIFE_03) */
#define TABLE_LIFEABILITY_ITEMCOMPOSE (903)
struct _TABLE_LIFEABILITY_ITEMCOMPOSE /* bc */
{
	table_int_t 		nID;
	LPCSTR	szName;
	table_int_t 		nResultID;
	table_int_t 		nResultNum;
	table_int_t 		nLifeAbility;
	table_int_t 		nLifeAbility_Level;
	table_int_t 		nStuff1ID;
	table_int_t 		nStuff1num;
	table_int_t 		nStuff2ID;
	table_int_t 		nStuff2num;
	table_int_t 		nStuff3ID;
	table_int_t 		nStuff3num;
	table_int_t 		nStuff4ID;
	table_int_t 		nStuff4num;

	/*
	 * table_int_t nStuff5ID;
	 * table_int_t nStuff5num;
	 */
	table_int_t 		nCostVigor;

	/*
	 * table_int_t nAttribute_ID1;
	 * table_int_t nAttribute_Level1;
	 * table_int_t nAttribute_ID2;
	 * table_int_t nAttribute_Level2;
	 */
	table_int_t 		nCoolDown_Time;
	table_int_t 		nFacility;				/* 需要的工具 */
	table_int_t 		nCoolDoon_Troop;		/* 冷却组 */

	/*
	 * table_int_t nProficiencyRequire;
	 * // 熟练度需求
	 */
	table_int_t 		nProficiencyIncrease;	/* 熟练度增加 */

	/*
	 * table_int_t NOTCARE;
	 * // 不关心的1列
	 */
	table_int_t 		nProficiencyTime;		/* 配方时间 */
	table_int_t 		nScriptID;				/* 脚本ID */

	/*
	 * table_int_t nFailItem;
	 * // 失败后的替代品
	 */
	LPCSTR	szExplain;				/* 详细描述 */
	LPCTSTR szTypeName;				/* 配方所在树结构中的分类名称 */

	/*
	 * 功能分组 ;
	 * NOT CARE...
	 */
};

/*
 -----------------------------------------------------------------------------------------------------------------------
    生活技能 操作平台 (LIFE_04) #define TABLE_LIFEABILITY_PLATFORM (904) ;
    struct _TABLE_LIFEABILITY_PLATFORM // bc ;
    { ;
    table_int_t nID;
    LPCSTR szName;
    table_int_t nType;
    LPCSTR szMeshFile;
    table_int_t nClickType;
    };
    表情和颜色转换字符 #define TABLE_CODE_CONVERT ( 905 ) ;
    struct _TABLE_CODE_CONVERT // bc ;
    { ;
    table_int_t nID;
    // ID ;
    LPCSTR szCode;
    // 字符串形式的十六进制数字 ;
    LPCSTR szName;
    // 介绍 ;
    };
    天赋技能 (XINFA_02) #define TABLE_TALENT_TALENTDEFINE (902) ;
    struct _TABLE_TALENT_TALENTDEFINE ;
    { ;
    table_int_t nID;
    // 天赋ID ;
    table_int_t nIDMenpai;
    // 职业ID ;
    LPCSTR szName;
    // 天赋名称 ;
    LPCSTR szTips;
    // 天赋描述 ;
    LPCSTR szIconName;
    // 图标名称 ;
    };
    天赋升级花费 (XINFA_02)
 -----------------------------------------------------------------------------------------------------------------------
 */
struct Spend
{
	table_int_t dwSpendMoney;									/* 需要花费的金钱数 */
	table_int_t dwSpendExperience;								/* 需要花费的经验值 */
};

/*
 * define TABLE_TALENT_STUDYSPEND (907) ;
 * struct _TABLE_TALENT_STUDYSPEND ;
 * { ;
 * table_int_t nStudyLevel;
 * // 要学习的等级 ;
 * Spend StudySpend[54];
 * };
 * 称号列表 (TITLE) ;
 * #define TABLE_TITLE_NAME (908) struct _TABLE_TITLE_NAME // bc { table_int_t nTitleIndex;
 * // 称号的索引 LPCSTR szTitle;
 * // 称号的名字 utable_int_t nReserve;
 * // 类型保留 LPCSTR szTitleDesc;
 * // 称号的描述 };
 */
#define TABLE_TITLE	(908)								/* title_info.tab */
struct _TABLE_TITLE
{
	enum _TITLE_KIND
	{
		KIND_QUEST= 1,								/* 任务称号 */
		KIND_GUT,										/* 剧情称号 */
		KIND_SPECIAL,									/* 特殊称号 */
	};

	table_int_t 		nId;										/* 称号ID */
	table_int_t 		nType;										/* TYPE */
	LPCSTR	szColor;									/* 显示颜色 */
	table_int_t 		bShow;										/* 默认是否显示 */
	LPCSTR	szManTitle;									/* 男性称号 */
	LPCSTR	szWomanTitle;								/* 女性称号 */
	LPCSTR	szTitleDesc;								/* 称号描述 */
	table_int_t 		nTimeLimit;									/* 称号时限 */
	LPCSTR	szAcquireDesc;								/* 获取途径 */
	table_int_t 		nEffectId;									/* 效果ID */
	LPCSTR	szReclaimCause;								/* 回收原因 */
	table_int_t 		nCombinationId;								/* 组合称号ID */
	table_int_t 		nKind;										/* 分类：任务，剧情，特殊 */
};

#define TABLE_COMBIN_TITLE	(977)
struct _TABLE_COMBIN_TITLE								/* title_combination.tab */
{
	table_int_t 					nGroupId;						/* title_inof.tab中组合称号id */
	table_int_t 					nCombinId;						/* 组合称号id */
	table_int_t 					nId1;							/* 所需要的10个称号id */
	table_int_t 					nId2;
	table_int_t 					nId3;
	table_int_t 					nId4;
	table_int_t 					nId5;
	table_int_t 					nId6;
	table_int_t 					nId7;
	table_int_t 					nId8;
	table_int_t 					nId9;
	table_int_t 					nId10;
	const static table_int_t 	COMBIN_TITLE_NUMBER = 10;
};

/* 阵营数据 */
#define TABLE_CAMP_DATA	(909)

/*
 * 技能 skillData_v1.txt(读取表) #define TABLE_SKILLDATA_V1_DEPLETE (910) ;
 * struct _TABLE_SKILLDATA_V1_DATA_PAIR ;
 * { ;
 * table_int_t nData;
 * LPCSTR szDesc;
 * ;
 * };
 * struct _TABLE_SKILLDATA_V1_DEPLETE // cd ;
 * { ;
 * table_int_t nId;
 * // ID ;
 * table_int_t nCeHuaId;
 * // 策划专用ID ;
 * table_int_t nSkillLogicid;
 * // 技能逻辑ID ;
 * LPCSTR szEffectDesc;
 * // 效果的简要逻辑说明 ;
 * table_int_t nCooldownTime;
 * // 冷却时间 ;
 * table_int_t nJuqiTime;
 * // 聚气时间(ms) ;
 * table_int_t nDirectTime;
 * // 引导时间(ms) ;
 * LPCSTR szCondition1Desc;
 * // 条件或消耗参数说明 ;
 * table_int_t nCondition11;
 * // 条件或消耗参数值 ;
 * table_int_t nCondition12;
 * // 条件或消耗参数值 ;
 * LPCSTR szCondition2Desc;
 * // 条件或消耗参数说明 ;
 * table_int_t nCondition21;
 * // 条件或消耗参数值 ;
 * table_int_t nCondition22;
 * // 条件或消耗参数值 ;
 * LPCSTR szCondition3Desc;
 * // 条件或消耗参数说明 ;
 * table_int_t nCondition31;
 * // 条件或消耗参数值 ;
 * table_int_t nCondition32;
 * // 条件或消耗参数值 ;
 * LPCSTR szCondition4Desc;
 * // 条件或消耗参数说明 ;
 * table_int_t nCondition41;
 * // 条件或消耗参数值 ;
 * table_int_t nCondition42;
 * // 条件或消耗参数值 ;
 * LPCSTR szCondition5Desc;
 * // 条件或消耗参数说明 ;
 * table_int_t nCondition51;
 * // 条件或消耗参数值 ;
 * table_int_t nCondition52;
 * // 条件或消耗参数值 ;
 * LPCSTR szCondition6Desc;
 * // 参数说明 ;
 * ;
 * // 参数对 ;
 * _TABLE_SKILLDATA_V1_DATA_PAIR paraPair[12];
 * ;
 * LPCSTR Skill_Desc_Interface;
 * ;
 * };
 */
#define TABLE_QUEST_KIND	(911)
struct _TABLE_QUEST_KIND
{
	table_int_t 	nIndex;										/* 任务种类的索引 */
	LPCSTR	szKindName;									/* 任务种类的名字 */
};

/* 任务NPC信息 */
#define TABLE_QUEST_INFO	(930)
struct _TABLE_QUEST_INFO
{
	table_int_t 		nIndex;
	LPCSTR	nNpcName;
	LPCSTR	szDefault;
	table_int_t 		nScript;
	LPCSTR	szEventList;
	LPCSTR	szEventList1;
	LPCSTR	szEventList2;
	LPCSTR	szEventList3;
	LPCSTR	szEventList4;
	table_int_t 		nFunctionType;
	LPCSTR	szSpeakSoundId;
};

/* 表情和颜色转换字符 */
#define TABLE_STRING_DICT (912)
struct _TABLE_STRING_DICT									/* bc */
{
	table_int_t 		nID;										/* ID */
	LPCSTR	szString;									/* 字符串 */
	LPCSTR	szKey;										/* 关键字 */
};

/* 环境音效列表 */
#define TABLE_ENV_SOUND	(913)
struct _TABLE_ENV_SOUND
{
	table_int_t 		nID;										/* ID */
	table_int_t 	nSoundID;									/* 音效ID */
	table_int_t 	nXPos;										/* 声源的X坐标 */
	table_int_t 	nZPos;										/* 声源的Z坐标 */
	table_int_t 	nDistance;									/* 能听到声音的最大距离 */
	table_int_t 		n1;											/* 连播次数 nRepeatTimes */
	table_int_t 		n2;											/* 间隔时间(ms) nRepeatIntervalTime */
	table_int_t 		n3;											/* 下一次连播间隔时间(ms) nNextRepeatTime */
};

/* 物品规则表 */
#define TABLE_ITEM_RULE	(914)
struct _TABLE_ITEM_RULE									/* bc */
{
	table_int_t 		nID;										/* ID */
	LPCSTR	szName;										/* 规则名字 程序不适用 策划用 */
	table_int_t 		bCanOverLay;								/* 是否可重叠 */
	table_int_t 		bCanDrop;									/* 是否可丢弃 */
	table_int_t 		bCanQuick;									/* 是否可放入快捷栏 */
	table_int_t 		bCanSale;									/* 是否可以出售给NPC商店 */
	table_int_t 		bCanExchange;								/* 是否可以交易 */
	table_int_t 		bCanUse;									/* 是否可以使用 */
	table_int_t 		bPickBind;									/* 是否是拾取邦定 */
	table_int_t 		bEquipBind;									/* 是否是装备邦定 */
	table_int_t 		bUnique;									/* 是否是唯一 */
	table_int_t 		bCheck;										/* 是否需要鉴定 */
	table_int_t 		bUnRealItem;								/* 是否是虚拟道具 */
	table_int_t 		bAccessInBack;								/* 是否可存入银行 */
	table_int_t 		bWearOut;									/* 是否消耗 */
};

/* 过滤词词汇表 */
#define TABLE_TALK_FILTER (915)
struct _TABLE_TALK_FILTER
{
	table_int_t 		nID;										/* ID */
	LPCSTR	szString;									/* 过滤词汇（即：不能说的词汇） */

	/*
	 * 过滤规则 ;
	 * 0表示忽略，1表示含有就过滤，2表示完全匹配过?
	 */
	table_int_t 		chatFilter;									/* 聊天时规则 */
	table_int_t 		roleFilter;									/* 创建人物时规则 */
	table_int_t 		nameFilter;									/* 命名时规则 */
	table_int_t 		stallFilter;								/* 摆摊时规则 */
	table_int_t 		otherFilter;								/* 供人物资料使用 */
	table_int_t 		darkFilter;									/* 模糊过滤该词语 */
	table_int_t 		findPlayerItemFilter;						/* 追踪符规则 */
};

/* 等级金钱对应表 */
#define TABLE_LV_MAXMONEY (916)
struct _TABLE_LV_MAXMONEY									/* bc */
{
	table_int_t nID;											/* ID */
	table_int_t nMaxMoney;										/* 最大金钱 */
	table_int_t nLv;											/* 等级 */
};

/* 聊天动作命令表 */
#define TABLE_TALK_ACT	(918)
struct _TABLE_TALK_ACT									/* ef */
{
	table_int_t 		nID;										/* ID */
	LPCSTR	szCmd;										/* 命令 */
	LPCSTR	szNobody;									/* 没有目标时的字串 */
	LPCSTR	szMyself;									/* 目标自己时的字串 */
	table_int_t 		n0;											/* 维持状态标 */
	LPCSTR	szOther;									/* 目标是其他玩家时的字串 */
	LPCSTR	szAct;										/* （起始）收到聊天信息时需要做的动作命令串 */
	LPCSTR	szActPersist;								/* （持续） */
	LPCSTR	szActEnd;									/* （结束） */

	LPCSTR	szIconName;									/* 图标 */
	LPCSTR	szToolTip;									/* 提示信息 */
	table_int_t 		isForce;									/* 是否强制 */
	table_int_t 		isDouble;									/* 是否双人 */
};

/* 聊天限制配置表 */
#define TABLE_TALK_CONFIG (919)
struct _TABLE_TALK_CONFIG									/* cd */
{
	table_int_t 		nID;										/* ID 依据eCHAT_TYPE */
	LPCSTR	szChannelName;								/* 频道名称 */
	table_int_t 		nTimeSlice;									/* 时间间隔（单位：秒） */
	LPCSTR	szChannelHeader;							/* 频道前导字符 */
	table_int_t 		nNeedType1;									/* 消耗类型1 依据eCHAT_NEED_TYPE */
	table_int_t 		nNeedValue1;								/* 消耗数值1 */
	table_int_t 		nNeedType2;									/* 消耗类型2 依据eCHAT_NEED_TYPE */
	table_int_t 		nNeedValue2;								/* 消耗数值2 */
	table_int_t 		nNeedType3;									/* 消耗类型3 依据eCHAT_NEED_TYPE */
	table_int_t 		nNeedValue3;								/* 消耗数值3 */
	table_int_t 		nNeedLv;									/* 等级限制，这里标称的是最低多少级才能在此频道发言 */
};

/* 发型改变消耗表 */
#define TABLE_HAIR_STYLE	(920)
struct _TABLE_HAIR_STYLE									/* bc */
{
	table_int_t nID;											/* ID索引 */
	table_int_t nItemTableID;									/* 消耗物品ID */
	table_int_t nRaceID;										/* 性别区分 */
	table_int_t nItemCount;										/* 消耗物品数量 */
};

/* 怪物头顶泡泡表 */
#define TABLE_MONSTER_PAOPAO	(921)
struct _TABLE_MONSTER_PAOPAO
{
	table_int_t 		nID;										/* ID索引 */
	LPCSTR	szPaoPaoTxt;								/* 怪物要说的头顶文字 */
};

#define TABLE_CAMP_AND_STAND	(922)						/* 阵营 */

/* 字体信息颜色表 */
#define TABLE_SYSTEM_COLOR	(923)
struct _TABLE_SYSTEM_COLOR								/* bc */
{
	const static table_int_t 	NAME_PLAYER_MYSELF_NEWGUY = 1;	/* 名字_主角_新手 */
	const static table_int_t 	NAME_PLAYER_MYSELF_PK_PUTONG = 2;				/* 名字_主角_PK关 */
	const static table_int_t 	NAME_PLAYER_MYSELF_PK_PK = 3;					/* 名字_主角_PK开 */
	const static table_int_t 	NAME_PLAYER_MYSELF_PK_HUNZHAN = 4;				/* 名字_主角_PK狂暴 */
	const static table_int_t 	NAME_PLAYER_MYSELF_GUARDER = 5;					/* 名字_主角_宠物 */
	const static table_int_t 	NAME_PLAYER_OTHER_SAMECOUNTRY_NEWGUY = 6;		/* 名字_其他玩家_同国_新手 */
	const static table_int_t 	NAME_PLAYER_OTHER_SAMECOUNTRY_PK_PUTONG = 7;	/* 名字_其他玩家_同国_PK关 */
	const static table_int_t 	NAME_PLAYER_OTHER_SAMECOUNTRY_PK_PK = 8;		/* 名字_其他玩家_同国_PK开 */
	const static table_int_t 	NAME_PLAYER_OTHER_SAMECOUNTRY_PK_HUNZHAN = 9;	/* 名字_其他玩家_同国_PK狂暴 */
	const static table_int_t 	NAME_PLAYER_OTHER_SAMECOUNTRY_PK_GUARDER = 10;	/* 名字_其他玩家_同国_宠物 */
	const static table_int_t 	NAME_PLAYER_OTHER_ENEMYCOUNTRY_NEWGUY = 11;		/* 名字_其他玩家_异国_新手 */
	const static table_int_t 	NAME_PLAYER_OTHER_ENEMYCOUNTRY_NOTNEWGUY = 12;	/* 名字_其他玩家_异国_非新手 */
	const static table_int_t 	NAME_PLAYER_OTHER_ENEMYCOUNTRY_GUARDER = 13;	/* 名字_其他玩家_异国_宠物 */
	const static table_int_t 	NAME_NPC_HORSE = 14;						/* 名字_NPC_可捕捉马 */
	const static table_int_t 	NAME_NPC_SAMECOUNTRY = 15;					/* 名字_NPC_同国 */
	const static table_int_t 	NAME_NPC_ENEMYCOUNTRY_NOTATTACK = 16;		/* 名字_NPC_异国_和平 */
	const static table_int_t 	NAME_NPC_ENEMYCOUNTRY_ATTACK_SCANNPC = 17;	/* 名字_NPC_异国_主动攻击 */
	const static table_int_t 	NAME_NPC_ENEMYCOUNTRY_ATTACK_NOTSCANNPC = 18;	/* 名字_NPC_异国_被动攻击 */
	const static table_int_t 	NAME_MONSTER_SCANNPC = 19;						/* 名字_NPC_异国_主动攻击 */
	const static table_int_t 	NAME_MONSTER_NOTSCANNPC = 20;					/* 名字_NPC_异国_被动攻击 */

	const static table_int_t 	NANE_GUILDBATTLE_SAME_GUILD_A = 21;		/* 帮会战中同帮玩家名字（A阵营玩家） */
	const static table_int_t 	NANE_GUILDBATTLE_SAME_GUILD_B = 22;		/* 帮会战中同帮玩家名字（B阵营玩家） */
	const static table_int_t 	NANE_WORLDCUP_SAME_GUILD_A = 23;		/* 世界杯中同帮玩家名字（A阵营玩家） */
	const static table_int_t 	NANE_WORLDCUP_SAME_GUILD_B = 24;		/* 世界杯中同帮玩家名字（B阵营玩家） */
	const static table_int_t 	NANE_KINGBATTLE_SAME_GUILD_A = 25;		/* 国王争夺战中同帮玩家名字（A阵营玩家） */
	const static table_int_t 	NANE_KINGBATTLE_SAME_GUILD_B = 26;		/* 国王争夺战中同帮玩家名字（B阵营玩家） */
	const static table_int_t 	NANE_PVP2V2_SAME_GUILD_A = 27;		/* PVP2V2中同帮玩家名字（A阵营玩家） */
	const static table_int_t 	NANE_PVP2V2_SAME_GUILD_B = 28;		/* PVP2V2中同帮玩家名字（B阵营玩家） */
	const static table_int_t 	NANE_PVP6V6_SAME_GUILD_A = 29;		/* PVP6V6中同帮玩家名字（A阵营玩家） */
	const static table_int_t 	NANE_PVP6V6_SAME_GUILD_B = 30;		/* PVP6V6中同帮玩家名字（B阵营玩家） */
	const static table_int_t 	NANE_ZHUQUE_SAME_GUILD_A = 31;		/* 朱雀守护中同帮玩家名字（A阵营玩家） */
	const static table_int_t 	NANE_ZHUQUE_SAME_GUILD_B = 32;		/* 朱雀守护中同帮玩家名字（B阵营玩家） */
	const static table_int_t 	NANE_QINGLONG_SAME_GUILD_A = 33;	/* 青龙守护中同帮玩家名字（A阵营玩家） */
	const static table_int_t 	NANE_QINGLONG_SAME_GUILD_B = 34;	/* 青龙守护中同帮玩家名字（B阵营玩家） */

	const static table_int_t 	TITLE_NORMAL = 100;			/* 称号_普通 */
	const static table_int_t 	TITLE_BANGPAI = 101;		/* 称号_帮派职称 */
	const static table_int_t 	TITLE_MOOD = 102;			/* 称号_玩家自定义心情 */
	const static table_int_t 	TITLE_PLAYER_SHOP = 103;	/* 称号_玩家商店 */
	const static table_int_t 	TITLE_COUNTRY = 104;		/* 称号_国家称号 */

	const static table_int_t 	UI_DEBUGLISTBOX = 1000;		/* debuglistbox的颜色 */

	table_int_t 					m_nID;
	LPCSTR				strFontColor;
	LPCSTR				strDesc;
	LPCSTR				strExtenColor;
};

/* 完全匹配过滤表，用在创建帮会、起名字之类的地方，避免使用系统词组 */
#define TABLE_FULLCMP_FILTER	(924)
struct _TABLE_FULLCMP_FILTER		/* bc */
{
	table_int_t 		nID;				/* ID索引 */
	LPCSTR	szFullTxt;			/* 完全屏蔽词 */
	LPCSTR	szFilterType;		/* 用在什么地方，例如：all,guild,team,.....表示用在所有地方，仅帮会，仅组队等等。 */
};

/* 宠物升级需要的经验表 */
#define TABLE_PET_LEVELUP (925)
struct _TABLE_PET_LEVELUP
{
	table_int_t nID;					/* ID索引 */
	table_int_t nExp;					/* 所需要经验 */
};

/* 技能学习条件表 */
#define TABLE_SKILL_STUDY_DATA	(926)

/* 骑宠物品表 */
#define TABLE_MOUNT_ITEM_DATA (927)
struct _TABLE_MOUNT_ITEM_DATA
{
	table_int_t 	nItemID;			/* 物品ID */
	LPCSTR	szItemDec;			/* 物品说明,策划用 */
	table_int_t 		nType;				/* 物品类型 */
	table_int_t 		nRate;				/* 属性比例 */
	table_int_t 		nNum;				/* 属性值 */
	table_int_t 		nSkillID;			/* 技能ID */
	table_int_t 		nSucceedRate;		/* 成功率 */
	table_int_t 		nUseLevel;			/* 使用等级 */
	table_int_t 		nTakeLevel;			/* 携带等级 */
	table_int_t 		nOnlyAberrance;		/* 是否变异骑乘专用 */
};

/* 坐骑基础表 */
#define TABLE_MOUNT_BASE_DATA (928)
struct _TABLE_MOUNT_BASE_DATA
{
	table_int_t 		nMountID;			/* 骑乘的ID */
	table_int_t 		nLevel;				/* 骑乘等级 */
	table_int_t 		bMating;			/* 是否可以交配 */
	table_int_t 		bCompose;			/* 是否可以炼化 */
	LPCSTR		szName;				/* 初始名 */
	table_int_t 		iKindType;			/* 物种类型 */
	LPCSTR		szKindName;			/* 物种名称 */
	table_int_t 		nRequirementLevel;	/* 骑乘携带等级 */
	table_int_t 		iReqInherenceLevel;	/* rj 2010-8-23 天赋等级 */
	table_int_t 		iReqPersonLevel;	/* rj 2010-8-23 个人等级 */
	table_int_t 		bIsAberrance;		/* 是否变异 */
	table_int_t 		IsFixedHold;		/* 是否可交易 */
	/*
	 * LPCSTR szTemp;
	 * // CNC ;
	 * table_int_t nChildPer1;
	 * LPCSTR szChildID;
	 * LPCSTR szChildPer2;
	 * LPCSTR szMatingID;
	 * ;
	 * table_int_t nMountID;
	 * // 骑乘的ID ;
	 * const char * szMountName;
	 * // 骑乘名称 没用 table_int_t nLevel;
	 * // 骑乘等级 ;
	 * table_int_t nRequirementLevel;
	 * // 骑乘携带等级 没用 const char * szChildID;
	 * // 还童ID 没用 const char * szMatingID;
	 * // 交配ID 没用 table_int_t bMating;
	 * // 是否可以交配 ;
	 * table_int_t bAberrance;
	 * // 是否变异 没用 table_int_t nDaiShu;
	 * // 繁殖代数 没用 table_int_t nAttach;
	 * // 骑乘的归属 没用 table_int_t nSurvivalTime;
	 * // 无主骑乘存活时间 没用 table_int_t nMinStr;
	 * // 初始最小力量 没用 table_int_t nMaxStr;
	 * // 初始最大力量 没用 table_int_t nMinDex;
	 * // 初始最小敏捷 没用 table_int_t nMaxDex;
	 * // 初始最大敏捷 没用 table_int_t nMinInt;
	 * // 初始最小智力 没用 table_int_t nMaxInt;
	 * // 初始最大智力 没用 table_int_t nMinCon;
	 * // 初始最小体质 没用 table_int_t nMaxCon;
	 * // 初始最大体质 没用 table_int_t nMinStrApt;
	 * // 初始最小力量资质 没用 table_int_t nMaxStrApt;
	 * // 初始最大力量资质 没用 table_int_t nMinDexApt;
	 * // 初始最小敏捷资质 没用 table_int_t nMaxDexApt;
	 * // 初始最大敏捷资质 没用 table_int_t nMinIntApt;
	 * // 初始最小智力资质 没用 table_int_t nMaxIntApt;
	 * // 初始最大智力资质 没用 table_int_t nMinConApt;
	 * // 初始最小体质资质 没用 table_int_t nMaxConApt;
	 * // 初始最大体质资质 没用 table_int_t nMinSavvy;
	 * // 初始最小悟性 没用 table_int_t nMaxSavvy;
	 * // 初始最大悟性 没用 table_int_t nMinBasic;
	 * // 初始最小根骨 没用 table_int_t nMaxBasic;
	 * // 初始最大根骨 没用 table_int_t nMinGrowRate;
	 * // 初始最小成长率 没用 table_int_t nMaxGrowRate;
	 * // 初始最大成长率 没用 table_int_t nMoveSpeed;
	 * // 移动速度 没用 table_int_t nModelID;
	 * // 对应表现ＩＤ 没用 table_int_t nModelID_A;
	 * // 对应表现ID 没用 table_int_t nSkillNum;
	 * // 骑乘技能数 没用 const char * szSkill_1;
	 * // 骑乘技能1 没用 const char * szSkill_2;
	 * // 骑乘技能2 没用 const char * szSkill_3;
	 * // 骑乘技能3 没用 const char * szSkill_4;
	 * // 骑乘技能4 没用 const char * szSkill_5;
	 * // 骑乘技能5 没用 const char * szSkill_6;
	 * // 骑乘技能6 没用 table_int_t nSavvySklll;
	 * // 骑乘领悟技能ＩＤ 没用
	 */
};

/* 每日提醒相关 */
#define MAX_NPC_DIALOG_LEN	70
#define MAX_SCENE_LEN		10
#define MAX_MIS_NAME_LEN	24
#define MAX_MIS_TEXT_LEN	24	/* 任务描述 */
#define MAX_MIS_IMAGCD_LEN	(128)

const table_int_t 	MAX_LEVEL_NUM = 161;
const table_int_t 	MAX_DAY_TIPS_NUM = 512;
const table_int_t MONTH_WEEK_NUM = 6; /* 每月最多6周 */
const table_int_t WEEK_DAY_NUM = 8;	/* 每周最多7天 */

/*
 -----------------------------------------------------------------------------------------------------------------------
    任务的有效时间片
 -----------------------------------------------------------------------------------------------------------------------
 */
struct VALID_TIME_SLICE
{
	tm		m_Begin;	/* 开始时间 */
	tm		m_End;		/* 结束时间 */

	table_int_t 	m_bShow;	/* 是否显示 */
};

/*
 -----------------------------------------------------------------------------------------------------------------------
    任务参数相关
 -----------------------------------------------------------------------------------------------------------------------
 */
struct MIS_PARAM_INFO
{
	table_int_t 	m_DayIdx;						/* 日期索引 */
	table_int_t 	m_DayFrom;						/* 从第几位 */
	table_int_t 	m_DayTo;						/* 到第几位 */

	table_int_t 	m_DataIdx;						/* 数据索引 */
	table_int_t 	m_DataFrom;						/* 从第几位 */
	table_int_t 	m_DataTo;						/* 到第几位 */
};

/* 每日提醒功能属性 */
#include "Define.h"
#define TABLE_DAY_TIPS	(929)
struct _TABLE_DAY_TIPS
{
	table_int_t 					m_Index;			/* index */
	table_int_t 					m_Used;				/* 是否已初始化 */
	table_int_t 					m_DayNominate;		/* 日推荐 */
	table_int_t 					m_MonthNominate;	/* 月推荐 */
	table_int_t 					m_ShowAll;			/* 是否全部可见，0为否，1为所有人可见 */

	table_int_t 					m_ShowLevel[MAX_LEVEL_NUM];						/* 可见等级，0表示所有等级段。 */
	table_int_t 					m_ShowCountry[MAX_COUNTRY_NUM];					/* 可见国家，0表示所有国家。 */

	table_int_t 					m_CheckGuild;									/* 是否检查帮会等级 */
	table_int_t 					m_ShowGuild[MAX_GUILD_LEVEL];					/* 可见帮会等级，0表示所有等级帮会 */

	table_int_t 					m_CheckFamily;									/* 检查家族 */

	table_int_t 					m_MisType;										/* 任务类型，0表示循环任务，1表示定时玩法。 */
	char					m_MisName[MAX_MIS_NAME_LEN];					/* 任务名称 */

	table_int_t 					m_MisValidMonth[13];							/* 任务有效月份，0表示不限月，否则表示可做该任务的月份*/
	table_int_t 					m_WeekOrDay;									/* 任务以星期或日期来做，0表示星期 */

	table_int_t 					m_MisValidDate[32];								/* m_WeekOrDay=1时的任务有效日期,0表示不限时。要注意每个月不是都在31天*/

	table_int_t 					m_MisValidWeek[MONTH_WEEK_NUM][WEEK_DAY_NUM];	/* 任务以周为单位来做 */

	/*
	 * 第一个字段表示第几周，为0表示不限周 ;
	 * 第二个字段表示周几，为0表示不限
	 */
	VALID_TIME_SLICE		m_VailidTimeSlice;					/* 任务开始到结束的时间,为0表示不限时 */

	table_int_t 					m_MisTimeFlag;						/* 全人全局变量时间标记 */
	MIS_PARAM_INFO			m_MisParamInfo;						/* 任务参数信息 */

	table_int_t 					m_MisCount;							/* 每日可做次数 */
	char					m_MisText[MAX_MIS_TEXT_LEN];		/* 任务描述 */

	table_int_t 					m_NPCId;							/* NPCID */
	char					m_QuestImage[MAX_MIS_IMAGCD_LEN];	/* 任务图标 */
};

/* 排行榜表 */
#define TABLE_TOP_LIST	(931)
struct _TABLE_TOP_LIST
{
	table_int_t 			nID;			/* ID */
	const char	*	szName;			/* 排行榜名 */
	table_int_t 			nListNum;		/* 排行榜最大数量 */
	table_int_t 			nMaxLevel;		/* 进入排行榜的最小级别 */
	table_int_t 			bSaveDB;		/* 是否存数据库 */
	table_int_t 			nType;			/* 排行榜类型 */
	table_int_t 			nID_bk;			/* 备份榜ID */
	const char	*	szExplain;		/* 排行榜说明 */
	table_int_t 			nAwardType;		/* 奖励类型 */
	table_int_t 			nAwardNum;		/* 奖励数量 */
	const char	*	szTempDec;
	const char	*	szAwardDec;		/* 奖励说明 */
};

/* 任务管理表 */
#define TABLE_QUEST_LOG	(932)
struct _TABLE_QUEST_LOG
{
	table_int_t 			nIndexID;		/* 索引ID */
	table_int_t 			nQuestID;		/* 任务 QuestID */
	table_int_t 			nScriptID;		/* 脚本 ScriptID */
	table_int_t 			nQuestType;		/* 任务类型，用于排序 */
	const char	*	szName;			/* 任务名称 */
	table_int_t 			nNPCId;			/* 接任务NPCID */

	table_int_t 			nMinLevel;		/* 接任务最低等级 */
	table_int_t 			nMaxLevel;		/* 接任务最高等级 */

	/* 前置任务 QuestID */
	table_int_t 			nPrevQuest1;	/* 前置任务1 */
	table_int_t 			nPrevQuest2;	/* 前置任务2 */
	table_int_t 			nPrevQuest3;	/* 前置任务3 */

	table_int_t 			nNeedMoneyType;
	table_int_t 			nNeedMoney;
	table_int_t 			nCountry;
	table_int_t 			nProfession;
	table_int_t 			nCamp;
};

#define TABLE_DEATH_DEAL	(944)
struct _TABLE_DEATH_DEAL
{
	table_int_t 		nDieSceneID;
	char	*szSceneName;		/* 地图名 */
	table_int_t 		nRebirthSceneID;
	table_int_t 		nRebirthWay1;
	table_int_t 		nRebirthWay2;
};

#define TABLE_BRITH_COST	(945)
struct _TABLE_BRITH_COST
{
	table_int_t nMinLv;
	table_int_t nOrgeCost;
	table_int_t nSafeCost;
};

/* 世界地图跳转表 */
#define TABLE_WORLD_POS	(934)
struct _TABLE_WORLD_POS
{
	table_int_t 		nIndex;				/* index */
	table_int_t 		nSceneId;			/* 地图SceneId */
	char	*szSceneName;		/* 地图名 */
	table_int_t 		nPosX;				/* X坐标 */
	table_int_t 		nPosZ;				/* Z坐标 */
	table_int_t 		nSceneType;			/* SceneType */
	table_int_t 		nMapLevel;			/* MapLevel */
	table_int_t 		nEnterLevel;		/* EnterLevel */
	char	*szIndexName;		/* 拼音索引 */
};

enum SCENEMAP_NPC_LOGIC_TYPE
{
	SNLT_DEFAULT = 0,
	SNLT_ONLY_PIC,
};

/* 当前场景NPC表 scenemap_npc.tab */
#define TABLE_SCENEMAP_NPC	(935)
struct _TABLE_SCENEMAP_NPC
{
	table_int_t 	nIndex;				/* index */
	LPCSTR	szSceneId;			/* 地图SceneId */
	LPCSTR	szNpcName;			/* 游戏中角色头顶名称 */
	LPCSTR	szNpcUIName;		/* 在NPC列表中显示的名称 */
	table_float_t 	nPosX;				/* X坐标 */
	table_float_t 	nPosZ;				/* Z坐标 */
	table_int_t 	nTalkToNpc;			/* SceneType */
	table_int_t 	nNPCType;			/* NPC类型 */
	LPCSTR	pNPCTypeName;		/* NPC类型名 */
	LPCSTR	pFilterName;		/* NPC名称拼音索引 */
	LPCSTR	pImageName;			/* NPC图片名 */
	INT		nLogicType;
};

#define TABLE_PROVINCE_ZONE	(936)
struct _TABLE_PROVINCE_ZONE
{
	table_int_t 		m_iPostCode;
	char	*m_strProvince;
	char	*m_strZone;
};

// 和摄像机互动的物件
struct CAMERA_INTERACT_STATICMESH
{
	LPCSTR	szStaticMeshName;
	LPCSTR	szSoundName;
	table_int_t 	nBeginTime;
	table_int_t 	bIsLoop;
};
#define CAMERA_INTERACT_STATICMESH_MAX_NUM  (3)


/* 登陆相关的场景数据 login_scene.tab */
#define TABLE_LOGIN_SCENE				(937)
struct _TABLE_LOGIN_SCENE
{
	table_int_t 			nID;					/* month */
	table_int_t 			nSceneId;				/* login scene id */
	table_int_t 			nBackSound;				/* 背景音乐 */
	LPCSTR			szCameraTrack;			/* camera track name */
	table_float_t 			fCameraStartPosX;
	table_float_t 			fCameraStartPosY;
	table_float_t 			fCameraStartPosZ;
	table_float_t 			fCameraStartLookAtX;
	table_float_t 			fCameraStartLookAtY;
	table_float_t 			fCameraStartLookAtZ;	
	table_float_t 			fCameraEndPosX;
	table_float_t 			fCameraEndPosY;
	table_float_t 			fCameraEndPosZ;
	table_float_t 			fCameraEndLookAtX;
	table_float_t 			fCameraEndLookAtY;
	table_float_t 			fCameraEndLookAtZ;
	table_float_t 			fCharPosX;
	table_float_t 			fCharPosZ;
	table_float_t 			fCharDir;
	table_float_t 			fCharScale;
	table_float_t 			fMountPosX;
	table_float_t 			fMountPosZ;
	table_float_t 			fMountDir;
	table_float_t 			fMountScale;
	CAMERA_INTERACT_STATICMESH	staticMesh[CAMERA_INTERACT_STATICMESH_MAX_NUM];	
};

/* 摄像机轨迹表 camera_track.tab */
#define TABLE_CAMERA_TRACK	(938)
struct _TABLE_CAMERA_TRACK
{
	table_int_t 		nIndex;									/* index */
	char	*szTrackName;							/* Track Name */
	char	*szIndexTrackName;						/* Index Track Name */
};

/* 服务器列表 serverlist.tab */
#define TABLE_SERVER_LIST			(939)
#define SERVER_LIST_FIELDS_NUM	10
struct _TABLE_SERVER_LIST
{
	table_int_t 		nIndex;									/* id */
	String	szAreaName;								/* 所属大区 */
	String	szServerName;							/* 服务器名 */
	String	szTooltip;								/* Tip说明 */
	table_int_t 		nProvider;								/* 0网通，1电信 */
	table_int_t 		nServerNo;								/* 服务器编号 */
	table_int_t 		nServerPower;							/* 服务器荷载：0为爆满，1为繁忙，2为良好，3为极佳，4为维护，10为备用服务器
													 * */
	table_int_t 		nIsRecommender;							/* 是否为推荐服务器 */
	table_int_t 		nIsNewServer;							/* 是否为新开服务器 */
	String	szServer1;								/* 网关IP及端口 */
	String	szServer2;								/* 服务器1IP及端口 */
	String	szServer3;								/* 服务器2IP及端口 */
	String	szServer4;								/* 服务器3IP及端口 */
};

/* 任务脚本 public\Script.tab */
#define TABLE_QUEST_SCRIPT	(950)
struct _TABLE_QUEST_SCRIPT
{
	table_int_t 		nIndex;									/* 编号 */
	LPCSTR	szQuestLua;							/* 对应的任务脚本 */
};

/* client equip_show.tab */
#define TABLE_EQUIP_OPERATOR_SHOW (951)
struct _TABLE_EQUIP_OPERATOR_SHOW
{
	table_int_t 		nIndex;									/* 玩法编号 */

	table_int_t 		nSucSound;								/* 成功对应的sound */
	table_int_t 		nFailSound;								/* 失败对应的sound */

	LPCSTR		szSucEff;								/* 成功对应的特效 */
	LPCSTR		szFailEff;								/* 失败对应的特效 */
	table_int_t 		nAnimateTime;							/* 动画时间 */
};

/* 题库 */
#define TABLE_QUESTIONS	(960)
struct _TABLE_QUESTIONS
{
	table_int_t 		nIndex;
	table_int_t 		nType;
	LPCTSTR szQuiz;
	LPCTSTR szAnswer1;
	LPCTSTR szAnswer2;
	LPCTSTR szAnswer3;
	LPCTSTR szAnswer4;
};

/* 帮会，职位与职能所对应的权限表 */
#define TABLE_AUTHORITY_GUILD (961)

struct _TABLE_AUTHORITY_GUILD
{
	_TABLE_AUTHORITY_GUILD()
	{
		nIndex = 0;
		szAuthorityName = NULL;
		memset(anPosAuthority, 0, sizeof(anPosAuthority));
	}
	table_int_t 		nIndex;
	LPCTSTR szAuthorityName;
	table_int_t 		anPosAuthority[GUILD_POSITION_SIZE];	/* 职位对应的权限 */
};

/* 表情动画表 */
#define TABLE_MOODANIM	(962)
struct _TABLE_MOODANIM
{
	table_int_t 		nID;
	LPCTSTR sKey;				/* 关键字 */
	LPCTSTR sDesc;				/* 描述, 用于tip显示和索引字符串用 */
	LPCTSTR sStr;				/* 如果是自己对自己的表情，字符串 */
	LPCTSTR sIcon;				/* 显示在界面的图标 */
	table_int_t 		nType;				/* 类型（0 == 2D，1 == 3D） */
	LPCTSTR sMoodRes;			/* 表情符号资源（图片或模型） */
};

#define TABLE_BEASTIE_ATTR	(963)
struct _TABLE_BEASTIE_ATTR
{
	table_int_t 				nID;		/* ID */
	table_int_t 				nModelID;	/* 模型ID */
	LPCTSTR			szPortrait; /* 头像 */
	table_int_t 				nSceneID;	/* 生成场景 */
	MONSTER_EFFECT	effect[MONSTER_EFFECT_MAX_NUM]; /* 特效 */

	/*
	 * LPCTSTR nName_NoUse;
	 * // 名字 ;
	 * table_float_t  fPosX_NoUse;
	 * // 初始位置X ;
	 * table_float_t  fPosZ_NoUse;
	 * // 初始位置Z ;
	 * table_int_t nItemID_NoUse;
	 * // 生成物品 ;
	 * table_float_t  fSpeed_NoUse;
	 * // 移动速度
	 */
};

/* char_fashion.tab */
#define TABLE_CHAR_FASHION	(964)
struct _TABLE_CHAR_FASHION
{
	/* 时装编号 身体 手 脚 头 脸 左手 右手 */
	table_int_t nFashionID;
	table_int_t nBody;
	table_int_t nHand;
	table_int_t nFoot;
	table_int_t nHair;
	table_int_t nShoulder;
	table_int_t nFace;
	table_int_t nWuShi_RightWeapon;
	table_int_t nWuShi_Shield;
	table_int_t nJianXia_LeftWeapon;
	table_int_t nJianXia_RightWeapon;
	table_int_t nQiShe_LeftWeapon;
	table_int_t nHuoQiang_RightWeapon;
	table_int_t nXianZhi_LeftWeapon;
	table_int_t nXianZhi_RightWeapon;
	table_int_t nShaMan_LeftWeapon;
	table_int_t nSheMan_RightWeapon;

	table_int_t nShiZiJun_LeftWeapon;
	table_int_t nShiZiJun_RightWeapon;
	table_int_t nShengHuoShi_LeftWeapon;
	table_int_t nShengHuoShi_RightWeapon;
	table_int_t nCiKe_LeftWeapon;
	table_int_t nCiKe_RightWeapon;
	table_int_t nJinWeiJun_LeftWeapon;
	table_int_t nJinWeiJun_RightWeapon;
	table_int_t nYinXiuShi_LeftWeapon;
	table_int_t nYinXiuShi_RightWeapon;
	table_int_t nLaMa_LeftWeapon;
	table_int_t nLaMa_RightWeapon;
};

/* guild_level_info.tab */
#define TABLE_GUILD_LEVEL_INFO	(965)
struct _TABLE_GUILD_LEVEL_INFO
{
	table_int_t m_Level;									/* 帮会等级 */
	table_int_t m_MaxFamily;								/* 家族个数上限 */
	table_int_t m_Gold;										/* 该级所需金钱 */
	table_int_t m_Contribute;								/* 该级所需贡献 */
	table_int_t m_MaxGuildUser;								/* 帮会最大成员上限 */
	table_int_t m_MaxFamilyUser;							/* 家族人数上限 */
	table_int_t m_MaxGoldFamilyUser;						/* 黄金家族人数上限 */
	table_int_t m_GuildItemNum;								/* 该级所需帮会信物数量 */
	table_int_t m_GuildMaxExp;								/* 帮会等级经验 */
	table_int_t m_nMaxMemberGP;								/* 帮贡最大值 */
	table_int_t m_nShiMing;									/* 使命点 */
	table_int_t m_nPriseShiMing;							// 奖励使命点基数
	table_int_t m_nShiMingPriseExp;							/* 使命点经验奖励 */
	table_int_t m_nMoneyLimit;								/* 帮会金钱上限 */

	_TABLE_GUILD_LEVEL_INFO()
	{
		m_Level = 0;
		m_MaxFamily = 0;
		m_Gold = 0;
		m_Contribute = 0;
		m_MaxGuildUser = 0;
		m_MaxFamilyUser = 0;
		m_MaxGoldFamilyUser = 0;
		m_GuildItemNum = 0;
		m_GuildMaxExp = 0;
		m_nMaxMemberGP = 0;
		m_nShiMing = 0;
		m_nPriseShiMing = 0;
		m_nShiMingPriseExp = 0;
		m_nMoneyLimit = 0;
	}
};

/* guild_merit_info.tab */
#define TABLE_GUILD_MERIT_INFO	(966)
struct _TABLE_GUILD_MERIT_INFO
{
	table_int_t 	m_nLevel;
	table_int_t 	m_nMerit;
	LPCTSTR	m_pTitle;
	table_float_t 	m_fMultiple;

	_TABLE_GUILD_MERIT_INFO()
	{
		m_nLevel = 0;
		m_nMerit = 0;
		m_pTitle = NULL;
		m_fMultiple = 1.0;
	}
};

#define TABLE_SCENEOB_SOUNE	(970)
struct _TABLE_SCENEOB_SOUNE
{
	table_int_t 		m_nID;
	LPCTSTR m_lpName;
	table_int_t 		m_nIndex;
	LPCTSTR m_lpFileName;
	LPCTSTR m_lpPosition;
	LPCTSTR m_lpLoop;
};

#define TABLE_SCENEOB_LIGHT	(971)
struct _TABLE_SCENEOB_LIGHT
{
	table_int_t 		m_nID;
	LPCTSTR m_lpName;
	LPCTSTR m_lpType;
	LPCTSTR m_lpDiffuse;
	LPCTSTR m_lpSpecular;
	LPCTSTR m_lpPosition;
	LPCTSTR m_lpDirection;
	LPCTSTR m_lpRange;
	LPCTSTR m_lpAttenuationConstant;
	LPCTSTR m_lpAttenuationLinear;
	LPCTSTR m_lpAttenuationQuadric;
	LPCTSTR m_lpSpotlightOuter;
	LPCTSTR m_lpSpotlightInner;
	LPCTSTR m_lpSpotlightFalloff;
	LPCTSTR m_lpCastShadows;
	LPCTSTR m_lpStaticLight;
};

#define TABLE_SCENEOB_EFFECT	(972)
struct _TABLE_SCENEOB_EFFECT
{
	table_int_t 		m_nID;
	LPCTSTR m_lpName;
	LPCTSTR m_lpEffectName;

	/*
	 * LPCTSTR m_lpPosition;
	 */
	table_float_t 	m_fPositionX;
	table_float_t 	m_fPositionY;
	table_float_t 	m_fPositionZ;
};

#define TABLE_GLOBAL_CONFIG	(973)
struct _TABLE_GLOBAL_CONFIG
{
	LPCTSTR m_lpName;
	table_int_t 		m_nValue;
	LPCTSTR m_lpDesc;
};

#define TABLE_MOUNT_APTITUDE	(974)
struct _TABLE_MOUNT_APTITUDE
{
	table_int_t nApt;										/* 资质 */
};

#define TABLE_CHANGCD_MAP_TIPS_INFO	(975)
struct _TABLE_CHANGCD_MAP_TIPS_INFO
{
	table_int_t 		m_Index;
	LPCTSTR m_lpTipContext;
};

/* 系统提示信息 */
#define TABLE_SYSTEMINFO	(976)
struct _TABLE_SYSTEMINFO
{
	table_int_t 		nID;
	table_int_t 		nMinLevel;
	table_int_t 		nMaxLevel;
	LPCTSTR szCounty;
	table_int_t 		nPlayCount;
	LPCTSTR szDesc;
};

/* 好友信息 */
#define TABLE_FRIEND	(978)
struct _TABLE_FRIEND
{
	table_int_t 		nID;
	table_int_t 		nEffect;
	table_int_t 		nFriendPoint;
	table_int_t 		nDayCount;
	LPCTSTR szDesc;
};

/* 配偶信息 */
#define TABLE_SPOUSE	(979)
struct _TABLE_SPOUSE
{
	table_int_t 		nID;
	table_int_t 		nEffect[9];
	table_int_t 		nDayCount;
	LPCTSTR szDesc;
};

/* 国家，职位与职能所对应的权限表 */
#define TABLE_AUTHORITY_COUNTRY	(980)
#include "DefineCountry.h"
struct _TABLE_AUTHORITY_COUNTRY
{
	_TABLE_AUTHORITY_COUNTRY()
	{
		nIndex = 0;
		szAuthorityName = NULL;
		memset(anPosAuthority, 0, sizeof(anPosAuthority));
	}
	table_int_t 		nIndex;
	LPCTSTR szAuthorityName;
	table_int_t 		anPosAuthority[COUNTRY_POSITION_SIZE];	/* 职位对应的权限 */
};

/* equip_star_effect.tab */
#define TABLE_EQUIP_STAR_EFFECT	(981)

struct _TABLE_EQUIP_STAR_EFFECT
{
	table_int_t 		nEffectId;						/* 对应 */
	LPCTSTR szEffectName;					/* 特效 */
	LPCTSTR szBindPointName;				/* 绑定点 */
};

#define TABLE_AAS_NODE_INFO	(982)
struct _TABLE_AAS_NODE_INFO
{
	table_int_t 		nID;							/* 标示 CHARACTER_AAS_NODE */
	LPCTSTR szDesc;							/* 说明 */
	LPCTSTR szNodeName;						/* 节点名 */
};

/* 新手帮助 */
#define TABLE_HELP_INFO	(969)
struct _TABLE_HELP_INFO
{
	table_int_t 		nID;							/* 相当于步骤 */
	LPCTSTR szImage;						/* 图片帮助 */
	LPCTSTR szDesc;							/* 文字帮助 */
};

#define EQUIP_SET_EFFECT_MAX_NUM	4
struct EQUIP_SET_EFFECT_INFO
{
	LPCTSTR szEffectName;					/* 特效 */
	LPCTSTR szBindPointName;				/* 绑定点 */
};

/* taozhuangtexiao.tab */
#define TABLE_EQUIP_SET_EFFECT	(983)
struct _TABLE_EQUIP_SET_EFFECT
{
	table_int_t 						nSetNum;		/* 套装件数 */
	EQUIP_SET_EFFECT_INFO	stEffect[EQUIP_SET_EFFECT_MAX_NUM];
};

/* 世界现金商店 */
#define TABLE_WORLD_SHOP_ATTR (984)
struct _TABLE_WORLD_SHOP_ATTR
{
	table_int_t 	m_ShopId;						/* 商店ID */
	table_int_t 		m_GoldCash;						/* 寄售现金 */
	table_int_t 		m_Charge;						/* 收费 */
	table_int_t 	m_ConcentNum;					/* 该玩家被允许在一个商店中的寄售次数 */
	table_int_t 	m_RemainTime;					/* 剩余有效时间 */
	table_int_t 	m_PageNum;						/* 商店分页上限 */
	LPCSTR	m_strIconName;
};

/* 打星,铭文激活表 */
#define TABLE_EQUIP_ACTIVATION_TABLE	(985)
struct _TABLE_EQUIP_ACTIVATION_TABLE
{
	table_int_t 		m_Index;
	LPCTSTR m_strActivationName;
	table_int_t 		m_Type;
	table_int_t 		m_NeedCountMin;
	table_int_t 		m_NeedCountMax;
	table_int_t 		m_NeedLevel;
	table_int_t 		m_PRI;
	table_int_t 		m_AttId0;
	table_int_t 		m_AttValue0;
	table_int_t 		m_AttId1;
	table_int_t 		m_AttValue1;
};

#define TABLE_EQUIP_COLORCHANGCD_TABLE	(986)
struct _TABLE_EQUIP_COLORCHANGCD_TABLE
{
	table_int_t m_Index;
	table_int_t m_ItemId;
	table_int_t m_Money;
	table_int_t m_NeedLevel;
};

#define TABLE_EQUIP_PURPLEREWORK_TABLE	(987)
struct _TABLE_EQUIP_PURPLEREWORK_TABLE
{
	table_int_t m_Index;
	table_int_t m_ItemId;
	table_int_t m_Money;
};

/* 副本答题 */
#define TABLE_SCENE_ANSWER	(988)
struct _TABLE_SCENE_ANSWER
{
	table_int_t 		nID;

	/*
	 * LPCSTR szQuestion;
	 * // 题目 ;
	 * LPCSTR szAnswer;
	 * // 答案
	 */
	LPCSTR	szFalsity[6];					/* 备选 */
};

/* 金币商店 */
#define TABLE_IB_SHOP		(989)
#define IB_SHOP_SUB_NUM 12
struct IB_SHOP_SUB							/* 子类数据 */
{
	table_int_t 		nShopId;						/* 对应到shop.tab中 */
	LPCTSTR szShopName;						/* 商店名称 */
};
struct _TABLE_IB_SHOP
{
	table_int_t 			nIndex;						/* 索引 */
	LPCSTR		szPageName;					/* 页名，代表商品的大类 */
	IB_SHOP_SUB subShop[IB_SHOP_SUB_NUM];	/* 商店数据 */
};

#define TABLE_GEM_REWORK_TABLE	(990)
struct _TABLE_GEM_REWORK_TABLE
{
	table_int_t m_Index;
	table_int_t m_NeedNum;
	table_int_t m_OtherNeedItem;
	table_int_t m_OtherNeedNum;
	table_int_t m_NeedMoney;
	table_int_t m_NewItem;
	table_int_t m_NewItemNum;
	_TABLE_GEM_REWORK_TABLE()
	{
		memset(this, 0, sizeof(_TABLE_GEM_REWORK_TABLE));
	}
};

/* 登录答题 */
#define TABLE_LOGIN_ANSWER	(991)
struct _TABLE_LOGIN_ANSWER
{
	table_int_t 		nID;

	/*
	* LPCSTR szQuestion;
	* // 题目 ;
	* LPCSTR szAnswer;
	* // 答案
	*/
	LPCSTR	szFalsity[6];					/* 备选 */
};

#define TABLE_EQUIP_COPY_TABLE (992)
struct _TABLE_EQUIP_COPY_TABLE
{
	table_int_t m_ItemId;
	table_int_t m_Type;
	_TABLE_EQUIP_COPY_TABLE()
		:m_ItemId(0), m_Type(0)
	{

	}
};

#define TABLE_EQUIP_RECALL_TABLE (993)
struct _TABLE_EQUIP_RECALL_TABLE
{
	table_int_t m_ItemId;
	table_int_t m_RecallType;
	table_int_t m_RecallValue;
	_TABLE_EQUIP_RECALL_TABLE()
		:m_ItemId(0), m_RecallType(0), m_RecallValue(0)
	{

	}
};

#define TABLE_TRANSITEM_POS_TABLE (994)
struct _TABLE_TRANSITEM_POS_TABLE
{
	table_int_t 	m_MapId;
	table_int_t 	m_CoutryLimit;
	LPCTSTR m_MapName;	
	_TABLE_TRANSITEM_POS_TABLE()
	{
		memset(this, 0, sizeof(_TABLE_TRANSITEM_POS_TABLE));
	}
};

#define TABLE_ENERGYBALL_TABLE (995)
struct _TABLE_ENERGYBALL_TABLE
{
	table_int_t 	m_BallId;
	table_int_t 	m_Rate;
	LPCTSTR m_NewItemId;
	
	_TABLE_ENERGYBALL_TABLE()
	{
		memset(this, 0, sizeof(_TABLE_ENERGYBALL_TABLE));
	}
};

#define TABLE_AMULET_TABLE (996)
struct _TABLE_AMULET_TABLE
{
	table_int_t 	m_ItemId;
	table_int_t 	m_Cost;
	table_int_t 	m_bHole1;
	LPCTSTR m_szPartId1;
	table_int_t 	m_bHole2;
	LPCTSTR m_szPartId2;
	table_int_t 	m_bHole3;
	LPCTSTR m_szPartId3;
	table_int_t 	m_bHole4;
	LPCTSTR m_szPartId4;
	table_int_t 	m_bHole5;
	LPCTSTR m_szPartId5;
	table_int_t 	m_bHole6;
	LPCTSTR m_szPartId6;
	_TABLE_AMULET_TABLE()
	{
		memset(this, 0, sizeof(_TABLE_AMULET_TABLE));
	}
};

#define TABLE_EQUIP_PRODUCE (997)
struct _TABLE_EQUIP_PRODUCE
{
	table_int_t m_EquipId;
	table_int_t m_EquipSetId;
	table_int_t m_MatId1;
	table_int_t m_MatCount1;
	table_int_t m_MatId2;
	table_int_t m_MatCount2;
	table_int_t m_MatId3;
	table_int_t m_MatCount3;
	table_int_t m_MatId4;
	table_int_t m_MatCount4;

	_TABLE_EQUIP_PRODUCE()
	{
		memset(this, 0, sizeof(_TABLE_EQUIP_PRODUCE));
	}
};

#define TABLE_EQUIP_SWITCH (998)
struct _TABLE_EQUIP_SWITCH
{
	table_int_t m_EquipSourceId;
	table_int_t m_EquipDestId;
	table_int_t m_Cost;
	table_int_t m_MaterialId;

	_TABLE_EQUIP_SWITCH()
	{
		memset(this, 0, sizeof(_TABLE_EQUIP_SWITCH));
	}
};

// 天赋特效
#define TABLE_INHERENCE_IMPACT	(999)
struct _TABLE_INHERENCE_IMPACT
{
	table_int_t 		m_iInherenceLevel;
	table_int_t 		m_iNextLevelExp;
	table_int_t 		m_iNextLevelMoney;
	table_int_t 		m_iNextLevelItem;
	LPCSTR		m_lpszEffect_Continuous;
	LPCSTR		m_lpszBind_Continuous;

	_TABLE_INHERENCE_IMPACT()
	{
		memset(this, 0, sizeof(_TABLE_INHERENCE_IMPACT));
	}
};

// 资源预加载
#define TABLE_RES_PRO_LOAD			(1000)
struct _TABLE_RES_PRO_LOAD
{
	table_int_t 	nID;		// id
	LPCSTR	szResName;	// 资源名
};

// 场景区域
#define  TABLE_SCENE_AREA			(1001)
struct _TABLE_SCENE_AREA
{
	table_int_t 	nID;			// ID
	table_int_t 	nSceneID;		// 场景ID
	LPCSTR	szExplain;		// 说明
	table_float_t 	fTopLeftX;		// 左上X
	table_float_t 	fTopLeftZ;		// 左上Z
	table_float_t 	fBottomRightX;	// 右下X
	table_float_t 	fBottomRightZ;	// 右下Z
	table_float_t 	fCharDir;		// 人物朝向
	table_float_t 	fCameraDir;		// 摄像机朝向
};

// 场景互动物件
#define TABLE_SCENE_ACTOR_MESH		(1002)
struct _TABLE_SCENE_ACTOR_MESH
{
	table_int_t 	nID;				// ID
	table_int_t 	nSceneID;			// 场景ID
	LPCSTR	szMeshName;			// Mesh名字
	table_int_t 	bIsActLoop;			// 是否动作循环
	table_int_t 	bInitActivation;	// 初始激活
};

// 场景颜色
#define TABLE_SCENE_COLOR		(1003)
struct _TABLE_SCENE_COLOR
{
	table_int_t 	nID;
	table_float_t 	fAddColorR;					// 添加红色值
	table_float_t 	fAddColorG;					// 添加绿色值
	table_float_t 	fAddColorB;					// 添加蓝色值
	table_float_t 	fScaleColorR;				// 缩放红色值 
	table_float_t 	fScaleColorG;				// 缩放绿色值
	table_float_t 	fScaleColorB;				// 缩放蓝色值
	table_float_t 	fGrayScale;					// 缩放灰度
};

//江湖指南
#define TABLE_WORLD_DIRECTORY	(1004)
struct _TABLE_WORLD_DIRECTORY
{
	table_int_t 	nID;						//索引
	LPCSTR	szMenu;						//主菜单
	LPCSTR	szSubMenu0;					//子菜单1
	LPCSTR	szSubMenu1;					//子菜单2
	LPCSTR	szContext;					//内容
	LPCSTR	szMinLevel;					//最小等级
	LPCSTR	szMaxLevel;					//最大等级
	LPCSTR	szTime;						//时间
	LPCSTR	szMap;						//发布场景
	LPCSTR	szNPC0;						//发布人（楼兰）
	LPCSTR	szNPC1;						//发布人（天山）
	LPCSTR	szNPC2;						//发布人（昆仑）
	LPCSTR	szNPC3;						//发布人（敦煌）
	LPCSTR	szEvent;					//事件字符串
};

//更换形象
#define TABLE_CHANGE_APPEARANCE	(1005)
struct _TABLE_CHANGE_APPEARANCE
{
	table_int_t 	m_ItemId;//道具物品id
};

enum ENUM_CHAR_SOUND_TYPE
{
	ENUM_CHAR_SOUND_TYPE_BATTLE = 0,
	ENUM_CHAR_SOUND_TYPE_DAMAGE,
	ENUM_CHAR_SOUND_TYPE_DEATH,

	ENUM_CHAR_SOUND_TYPE_NUM,
};

// 人物声音
#define TABLE_CHAR_SOUND		(1006)
struct _TABLE_CHAR_SOUND
{
	table_int_t 		nID;
	LPCSTR		szSound[ENUM_CHAR_SOUND_TYPE_NUM];
};

// 天赋学习
#define TABLE_GIFT_LEARN		(1007)
struct _TABLE_GIFT_LEARN
{
	table_int_t 		nID;
	LPCSTR		szNeedLevel_Guild;			// 帮会升级所需等级
	LPCSTR		szNeeddMoney_Guild;			// 帮会升级所需金钱
	LPCSTR		szNeedExp_Guild;			// 帮会升级所需经验
	LPCSTR		szNeedItem_Guild;			// 帮会升级所需道具id
	LPCSTR		szNeedItemCount_Guild;		// 帮会道具个数
	table_int_t 		nGuildLevelLargess;			// 开启默认等级

	LPCSTR		szNeedGiftLevel_Self;		// 个人所需天赋等级
	LPCSTR		szNeedGiftTotalPoint_Self;	// 个人所需天赋总等级
	LPCSTR		szNeedMoney_Self;			// 个人所需银卡
	LPCSTR		szNeedBangGong_Self;		// 个人所需帮贡
	LPCSTR		szNeedShengWang_Self;		// 个人所需声望
	LPCSTR		szNeedWeiWang_Self;			// 个人所需威望
	LPCSTR		szNeedItem_Self;			// 个人所需道具id
	LPCSTR		szNeedItemCount_Self;		// 个人道具个数
};

//
#define TABLE_AVG_INHERENCE	(1008)
struct _TABLE_AVG_INHERENCE
{
	table_int_t 	nIndex;
	table_int_t 	nPlayerlevel;
	table_int_t 	nInherencelevel;
};

//
#define TABLE_ENERGYBALLSYN (1009)
struct _TABLE_ENERGYBALLSYN
{
	table_int_t  m_Level; //能量球补色次数
	table_int_t m_Rate;  //吸收比率
	table_int_t m_ItemId;//需要的道具
	table_int_t m_ItemCount;//需要的道具数量
};

// 平衡天赋学习
#define TABLE_BALANCE_LEARN_1	(1010)
struct _TABLE_BALANCE_LEARN_1
{
	table_int_t 	nID;
	table_int_t 	nLogicID;
	table_int_t 	nMaxLevel;
	LPCSTR	szNeedSelfGiftLevel;
	LPCSTR	szNeedItemID;
	LPCSTR	szNeedItemNum;
	LPCSTR	szName;
	LPCSTR	szIconName;
	LPCSTR	szExplain;
	LPCSTR	szDesc;
};

#define SPECIAL_BALANCE_NUM (2)
struct BalanceLearnInfo
{
	table_int_t 	nLogicID;
	table_int_t 	nMaxLevel;
	table_int_t 	nNeedItemID;
	table_int_t 	nNeedItemNum;
	LPCSTR	szName;
	LPCSTR	szIconName;
	LPCSTR	szExplain;
	LPCSTR	szDesc;
};

#define TABLE_BALANCE_LEARN_2	(1011)
struct _TABLE_BALANCE_LEARN_2
{
	table_int_t 	nID;
	BalanceLearnInfo learnInfo[SPECIAL_BALANCE_NUM];
};

#define TABLE_NPC_SPECIAL_TITLE	(1012)
struct _TABLE_NPC_SPECIAL_TITLE
{
	table_int_t 	m_guid;
	table_int_t 	m_country;
	table_int_t 	m_index;
	table_int_t 	m_optType;  //按那种规则处理	
};

//
#define TABLE_NEW_EQUIP_PRODUCE (1013)
struct _TABLE_NEW_EQUIP_PRODUCE
{
	static const table_int_t 	ATLAS_COL = 2;
	static const table_int_t 	ADDITIVE_COL = 11;
	table_int_t m_nEquipItemId;     //装备ID	
	table_int_t m_nNeedMoney;       //需求金钱	
	table_int_t m_nAtlasItemId;     //图谱	
	table_int_t m_nAtlasCount;      //个数	
	table_int_t m_nLifeMetItemId;   //生活材料	
	table_int_t m_nLifeMetCount;    //个数	
	table_int_t m_nSpeMetItemId;    //特殊材料	
	table_int_t m_nSpeMetCout;      //个数	
	table_int_t m_nRate1[EQUIP_BLUEATTR_PRODUCE_RATE_ARRAY_NUMBER]; //3条,4条,5条属性几率		
	table_int_t m_nAdditiveItemId;  //添加剂	
	table_int_t m_nAdditiveCount;   //个数	
	table_int_t m_nRate2[EQUIP_BLUEATTR_PRODUCE_RATE_ARRAY_NUMBER]; //3条,4条,5条属性几率
};

//
#define TABLE_EQUIP_CONST_BIND (1014)
struct _TABLE_EQUIP_CONST_BIND
{
	table_int_t m_nNeedItemId;	  //需要道具ID
	table_int_t m_nNeedMoney;       //需求金钱
	table_int_t m_nAddConstCount[MAX_EQUIP_CONST_ATTR];   //附加星座数量
	table_int_t m_nRate[MAX_EQUIP_CONST_ATTR]; //附加星座数量的概率		
};
#define TABLE_EQUIP_CONST_INFO (1015)
struct _TABLE_EQUIP_CONST_INFO
{
	table_int_t m_nConstId;	      //星座ID
	LPCSTR m_szConstName;       //星座名称
	table_int_t m_nActiveConstId1;   //激活的星座ID
	LPCSTR m_szActiveConstName1; //激活的星座名称
	table_int_t m_nActiveConstId2;   //激活的星座ID
	LPCSTR m_szActiveConstName2; //激活的星座名称
	table_int_t m_nRate;            //附加星座数量的概率		
};

#define TABLE_EQUIP_CONST_ACTIVE_POINT (1016)
struct _TABLE_EQUIP_CONST_ACTIVE_POINT
{
	table_int_t m_nPoint;	      //星座ID
	table_int_t m_nActivePoint;       //星座名称	
};

/* 2010-10-19 by rj 跨服玩家服名称显示 */
#define TABLE_WORLD_NAME	(1017)
struct _TABLE_WORLD_NAME
{
	int16	nWorldID;				/* 世界服务器 ID */
	LPCSTR	szWorldName;			/* 世界服务器名字 */
};

#define TABLE_ITEM_SPECIAL (1018)
struct _TABLE_ITEM_SPECIAL
{
	table_int_t m_nIndex;			  //索引
	table_int_t m_nItemId;	      //特殊道具id
	table_int_t m_nUseType;         //特殊道具使用类型	
};

//! 专攻
#define TABLE_GIFT_ZHUANGONG    1019
struct _TABLE_GIFT_ZHUANGONG
{
    table_int_t m_iLevel;             // 技能等级
    table_int_t m_iNeedXP;            // 所需专攻经验
    table_int_t m_iEffect;            // 攻击提高效果
};

//! 专防
#define TABLE_GIFT_ZHUANFANG    1020
struct _TABLE_GIFT_ZHUANFANG
{
    table_int_t m_iLevel;             // 技能等级
    table_int_t m_iNeedPoint;         // 所需专防点数
    table_int_t m_iEffect;            // 防御提高效果
};

//荣誉铭刻
#define TABLE_EQUIP_HONOR_BIND    1021
struct _TABLE_EQUIP_HONOR_BIND
{
	table_int_t m_nBindLevel;                                     // 铭刻级别
	table_int_t m_NeedGem[MAX_EQUIP_HONOR_BIND_COND];             // 需求宝石
	table_int_t m_SuccRate[MAX_EQUIP_HONOR_BIND_COND];            // 成功几率
	table_int_t m_FailPunish[MAX_EQUIP_HONOR_BIND_COND];          // 失败惩罚
	table_int_t m_nNeedMoney;									    //需要金钱
	table_int_t m_nIntensify;									    //强化比率
};

// 帮会神兽技能学习条件表
#define TABLE_GUILD_BUS_SKILL_STUDY_CONSUME	(1022)
struct _TABLE_GUILD_BUS_SKILL_STUDY_CONSUME
{
	table_int_t m_nSkillID;										// 当前等级的技能ID
	table_int_t m_NextLevelSKillID;								// 下一级的技能ID
	table_int_t m_nSkillLevel;									// 等级
	table_int_t m_nNeedGuildLevel;								// 需求帮会等级
	table_int_t m_ConsumeMoney;									// 消耗金钱
	table_int_t m_ConsumeGuildExp;								// 消耗帮会经验
};