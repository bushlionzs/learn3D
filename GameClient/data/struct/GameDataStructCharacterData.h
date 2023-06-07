#pragma once
#include "StructDB.h"
#include "data/struct/GameDataStructSkill.h"

struct SDataCharacter
{
	int32				m_nRaceID;			/* 数据表中的ID */

	int32				m_nPortraitID;		/* 头像ID */
	String				m_strName;			/* 角色的名字，从服务器传来 */
	String				m_strUtf8Name;		/* 角色的Utf8 名称 */
	String				m_strCountryTitle;	/* 当前国家称号 */
	String				m_strGuildTitle;	/* 当前帮会称号 */
	String				m_strTitle;			/* 当前玩法称号 */
	String				m_strConsortName;	/* 配偶名字 add by QL 081022 */
	BYTE				m_TitleType;		/* 当前称号类型 */
	FLOAT				m_fHPPercent;		/* 生命值百分比 */
	FLOAT				m_fMPPercent;		/* 魔法值百分比 */
	int32				m_nHP;				/* 生命点 */
	int32				m_nMaxHP;			/* 最大生命点 */
	int32				m_nRage;			/* 怒气 */
	int32				m_nMaxRage;			/* 最大怒气 */
	FLOAT				m_fMoveSpeed;		/* 移动的速度 */
	SCampData			m_CampData;			/* 阵营ID */
	int32				m_nOwnerID;			/* 所有者ID */
	int32				m_nRelative;		/* 相对关系，这个人是否可被攻击，是否主动攻击 */
	int32				m_nModelID;			/* 模型ID */
	int32				m_nMountID;			/* 坐骑ID */
	int32				m_nLevel;			/* 等级 */
	BOOL				m_bFightState;		/* 战斗状态 */
	int32				m_nStealthLevel;	/* 隐身级别 */
	BOOL				m_bSit;				/* 坐下状态 */
	int32				m_nAIType;			/* AI类型 */
	int32				m_nCountry;			/* 国家 */
	int32				m_nAttachID;		/* 所绑定的ObjID */
	int32				m_nGuild;			/* 帮派ID */
	int32				m_nGuildPosition;			/* 在帮派中的职位 */
	FLOAT				m_fSpeedRate;		/* 改变角色频率相关 */
	int32				m_nTargetId;		/* 选中的目标 */
	BOOL				m_bVisibleState;	/* 是否可见 */
	FLOAT				m_fDir;				/* 朝向 */
	int32				m_nMoveLogicMode;	/* 移动模式 */
	int32				m_nMoveActionMode;		/* 移动模式 */
	int32				m_nTeamID;			/* 队伍ID */
	BOOL				m_bLimitMove;		/* 是否限制不能移动,定身的 */
	BOOL				m_bLimitMove_2;		/* 限制移动标识，恐惧的 */
	BOOL				m_bCanActionFlag1;	/* 技能受限标记1,用于沉默 */
	BOOL				m_bCanActionFlag2;	/* 技能受限标记2,用于不可攻击 */
	BOOL				m_bAttachSetFlag;	/* 判断是否已经设置过绑定属性 */
	int32				m_nControlState;	/* 控制状态 */
	BOOL				m_bBusState;		/* 进入镖车状态 */
	FLOAT				m_fCharScale;		// 人物缩放比例
	int32				m_nDefaultSkill;	// 默认技能
	SkillDataMap		m_theSkill;			/* 技能数据 */
	/*
	 * 注意: 添删数据需要在 _Init_AsCharacter() 初始化!!! 
	 * 注意: 添删数据需要在 _Init_AsCharacter() 初始化!!! ;
	 * 注意: 添删数据需要在 _Init_AsCharacter() 初始化!!!
	 * Set 和 Get 函数注意自己的数据类型, 需要加 MUST_NOT_CHECK() 检测!!! ;
	 */
};

/*
 -----------------------------------------------------------------------------------------------------------------------
    -->1. Character_NPC 对于NPC ;
 -----------------------------------------------------------------------------------------------------------------------
 */
struct SDataNPC :
	public SDataCharacter
{
	int32 m_nWeaponID;	/* 武器ID */
	int32 m_nAttachMemberID[DEF_BUS_MAX_PASSENGER_COUNT]; /* 乘客ID,车辆专用 */

	/*
	 * 注意: 添删数据需要在 _Init_AsNPC() 初始化!!! 
	 * 注意: 添删数据需要在 _Init_AsNPC() 初始化!!! ;
	 * 注意: 添删数据需要在 _Init_AsNPC() 初始化!!!
	   Set 和 Get 函数注意自己的数据类型, 需要加 MUST_NOT_CHECK() 检测!!! ;
	 */
};

/*
 -----------------------------------------------------------------------------------------------------------------------
    -->2. Character_PlayerOther 对于其他玩家 ;
 -----------------------------------------------------------------------------------------------------------------------
 */
struct SDataPlayerOther :
	public SDataNPC
{
	int32				m_nProfession;						/* 职业 0[武士] 1[剑侠] 2[骑射] 3[火枪] 4[萨满] 5[先知] */
	int32				m_nHairMeshID;						/* 头发外形 -> TABLE_CHARACTER_HAIR_GEO */
	int32				m_nFaceMeshID;						/* 脸部外形 -> TABLE_CHARACTER_HEAD_GEO( char_head.tab ) */
	uint32				m_uHairColor;						/* 头发颜色 */
	int32				m_nEquipVer;						/* 角色的装备状态版本号，用于和服务器同步数据的依据 */
	int32				m_nEquipmentID[HEQUIP_NUMBER];		/* 装备表;
															* 用于外形显示 */
	int32				m_nEquipmentGemID[HEQUIP_NUMBER];	/* 装备宝石表;
															* 用于外形显示 */
	_SUIT_SETTING		m_oChangeSuit[MAX_EQUIP_SUIT_NUM];	/* 一键换装数据 */
	BOOL				m_bShowFashion;						/* 是否显示时装 */
	int32				m_nCurTitleIndex;					/* 当前使用的称号索引 */
	BOOL				m_bIsInStall;						/* 是否摆摊中 */
	String				m_strStallName;						/* 摊位名 */
	uchar				m_StallMoneyType;					/* 摊位金钱模式*/
	int32				m_nFamily;							/* 家族ID */
	int32				m_nPKValue;							/* pkvalue */
	String				m_strProvince;						/* 省份 */
	String				m_strZone;							/* 城市 */
	String				m_strGuildName;						/* 帮会名称 */
	String				m_strFamilyName;					/* 家族名称 */
	BYTE				m_NameColor;						/* 特殊时候名字颜色 */
	int32				m_nMountStrApt;						/* 坐骑力量资质 */
	int32				m_nMountDexApt;						/* 坐骑敏捷资质 */
	int32				m_nMountIntApt;						/* 坐骑智力资质 */
	int32				m_nMountConApt;						/* 坐骑体质资质 */
	int32				m_nMountEra;						/* 坐骑代数 */
	int32				m_nCurSuitId;						/* 当前套装id */
	int32				m_nCurEquipSign;					/* 当前符文的激活 */
	uint32				m_nCurStarSign;						/* 当前星星特效的激活 */
	uint32				m_nCurSuitSign;						/* 当前激活套装 */
	int32				nLeftWeaponVisual;					/* 时装武器标识 */
	int32				nRighttWeaponVisual;
	int32				nShoulderVisual;					/* 时装披风外形标识 */
	int32				nHeadVisual;						/* 时装头发外形标识 */
	int32				nKillCount;							/* 杀人数 */
	BOOL				m_bIsHideName;						/* 是否是蒙面状态 */
	uint32				m_uInherenceExp;			/* 天赋经验 */
	uint32				m_uInherenceNextLevelExp;	/* 天赋经验 */
	uint32				m_uInherenceLevel;			/* 天赋等级 */

	/*
	 * 注意: 添删数据需要在 _Init_AsPlayerOther() 初始化!!! 
	 * 注意: 添删数据需要在 _Init_AsPlayerOther() 初始化!!! ;
	 * 注意: 添删数据需要在 _Init_AsPlayerOther() 初始化!!!
	   Set 和 Get函数注意自己的数据类型, 需要加 MUST_NOT_CHECK() 检测!!! ;
	 */
};

/*
 * -->3. Character_PlayerMySelf 对于玩家自己 ;
 */
#define PLAYER_COIN_NUM 4							/* 玩家背包货币类型总数 */
class	KItem;
struct SDataPlayerMyself :
	public SDataPlayerOther
{
	int32					m_nMP;						/* 魔法点 */
	int64_t					m_nExp;						/* 经验值 */
	int64_t					m_nMoney[PLAYER_COIN_NUM];	/* 玩家金钱 */
	int32					m_nSilverCoin;

	int32					m_nStrikePoint;				/* 连技点 */
	int32					m_nVigor;					/* 活力值 */
	int32					m_nMaxVigor;				/* 活力值上限 */
	int32					m_nRegeneRate;
	int32					m_nEnergy;					/* 精力值 */
	int32					m_nMaxEnergy;				/* 精力值上限 */
	int32					m_nGoodBadValue;			/* 善恶值 */
	SHorseGuid				m_guidCurrentPet;			/* 当前宠物GUID */

	/* 已经分配的系别点数 */
	int32					m_nSeriesPoint_1;			/* 系别 1 */
	int32					m_nSeriesPoint_2;			/* 系别 2 */
	int32					m_nSeriesPoint_3;			/* 系别 3 */
	int32					m_nSkillPoint;

	/* 一级战斗属性 */
	int32					m_nSTR;						/* 外功 */
	int32					m_nCON;						/* 身法 */
	int32					m_nINT;						/* 体魄 */
	int32					m_nDEX;						/* 智慧 */
	int32					m_nPoint_Remain;			/* 剩余待分配点数 */

	/* 二级战斗属性 */
	int32					m_nAtt_Near;				/* 近攻 */
	int32					m_nDef_Near;				/* 近防 */
	int32					m_nAtt_Far;					/* 远攻 */
	int32					m_nDef_Far;					/* 远防 */

	int32					m_nAtt_Magic;				/* 魔法攻击力 */
	int32					m_nDef_Magic;				/* 魔法防御力 */
	int32					m_nMaxMP;					/* 最大魔法点 */
	int32					m_nHP_ReSpeed;				/* HP恢复速度 点/秒 */
	int32					m_nMP_ReSpeed;				/* MP恢复速度 点/秒 */
	int32					m_nRage_Respeed;			/* 怒气恢复 */
	int32					m_nToughness;				/* 韧性 */
	int32					m_nHit;						/* 命中率 */
	int32					m_nMiss;					/* 闪避率 */
	int32					m_nCritRate;				/* 会心率 */
	int32					m_nCritHurt;				/* 爆击伤害 */
	float					m_nAttackSpeed;				/* 攻击速度 */

	int32					m_nAtt_Cold;				/* 冰攻击 */
	int32					m_nDef_Cold;				/* 冰防御 */
	int32					m_nAtt_Fire;				/* 火攻击 */
	int32					m_nDef_Fire;				/* 火防御 */
	int32					m_nAtt_Light;				/* 电攻击 */
	int32					m_nDef_Light;				/* 电防御 */
	int32					m_nAtt_Posion;				/* 毒攻击 */
	int32					m_nDef_Posion;				/* 毒防御 */

	int32					m_nNear_Reduce;				/* 近程减免 */
	int32					m_nFar_Reduce;				/* 远程减免 */
	int32					m_nMagic_Reduce;			/* 魔法减免 */

	int32					m_nDread_Resist;			/* 恐惧抗性 */
	int32					m_nComa_Resist;				/* 昏迷抗性 */
	int32					m_nHush_Resist;				/* 沉默抗性 */
	int32					m_nUnarm_Resist;			/* 缴械抗性 */
	int32					m_nAttackSpeed_Resist;		/* 减攻速抗性 */
	int32					m_nSkillSpeed_Resist;		/* 减施速抗性 */
	int32					m_nMoveReduce_Resist;		/* 减移速抗性 */


	int32					m_nPerCon;					/* 帮贡 */
	int32					m_nHonor;					/* 荣誉值 */
	int32					m_RongYu;					/* 朝廷声望 */
	int32					m_ShengWang;				/* 江湖声望 */
	int32					m_WenCai;					/* 文采 */

	int32					m_nHot;						/* 魅力 */
	uint32					m_uTiredTime;				/* 疲劳时间 */
	
	uint32					m_nBattleHonour;			/* 战场荣誉 */
	USHORT					m_PVP2V2Level;				/* pvp2v2竞技场等级 */
	USHORT					m_PVP2V2Mark;				/* pvp2v2竞技场积分 */
	int32					m_PVP2V2Mark_WeekTotal;		/* pvp2v2竞技场积分本周总计 */
	BYTE					m_byBankPetValidCt;			/* 激活的坐骑个数 */
	int32					m_nMerit;					/* 帮会功德值 */
    uint32                  m_dwFeastScore;             /* 节日积分 */

    //! 专防剩余点数
    uint32                  m_uiDefendRemainPoints;
};
