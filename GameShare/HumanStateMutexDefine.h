/*$T Common/HumanStateMutexDefine.h GC 1.140 10/10/07 10:06:30 */

/*
 * created: 2008/10/10 created: 10:10:2008 11:29 filename:
 * Common\HumanStateMutexDefine.h file path: Common file base:
 * HumanStateMutexDefine file ext: h author: Richard purpose:
 * 玩家状态互斥管理器相关数据结构和枚举的声明
 */
#ifndef HumanStateMutexDefine_h__10_10_2008_11_34
#define HumanStateMutexDefine_h__10_10_2008_11_34

const int32	Max_Mutex_State = 64;
const int32	Max_Input_Event = 128;

#define FILE_HUMAN_MUTEX	"./../Public/Config/PlayerStateMutex.tab"

enum _MutexState
{
	MS_FreeState		= -1,
	MS_Stall		= 0,	/* 摆摊 */
	MS_Fuben,			/* 副本 */
	MS_BattleFieldMap,		/* 战场 */
	MS_ArenaMap,			/* 擂台 */
	MS_CityMap,			/* 城市 */
	MS_PrisonMap,			/* 监狱 */
	MS_Die,			/* 死亡 */
	MS_Bus,			/* Bus */
	MS_Cashbox,		/* 运镖 */
	MS_Exchange,		/* 交易 */
	MS_MentalGame,		/* 答题 */
	MS_TeamFollow,		/* 组队跟随 */
	MS_AutoPlay,		/* 挂机Client */
	MS_SubTrain,		/* 代练 */
	MS_Prison,		/* 监狱 */
	MS_OpenBox,		/* 开箱 */
	MS_ProtectTime,		/* 场景生命保护时间 */
	MS_KeyboardMove,	/* 键盘移动Client */
	MS_Quest_TieSan,	/* 在做任务铁人三项 */
	MS_ReadyFuben,		/* 已经接受副本任务，等待 */
	MS_Quest_DuoQiBuff,	/* 夺旗任务有buff时的状态 */
	MS_Quest_TongQuBuff,	/* 童趣任务有buff时的状态 */
	MS_PKMode,		/* 处于PK模式状态 */
	MS_ForbidRide,		/* 081226（齐亮）禁骑状态，用来限制在特定场景（如舞厅）上马 */
	MS_Wedding,		/* 处于婚礼状态 */
	MS_Enjail,		/* 囚禁状态 */
	MS_Award,		/* 领奖状态 */
	MS_TransGold,		/* 领取现金状态 */
	MS_InDancery,		/* 在舞厅 */
	MS_BlackGold,		/* 黑金答题状态 */
	MS_NumOfMutexState
};

enum _MutexStateEvent
{
	ME_CXAskQuestList	= 0,	/* 调用 */
	ME_CXEventRequest,		/* 请求事件 */
	ME_CXQuestAccept,		/* 接受任务 */
	ME_CXQuestAbandon,		/* 放弃任务 */
	ME_CXQuestRefuse,		/* 拒绝任务 */
	ME_CXQuestSubmit,		/* 完成任务 */
	ME_CXQuestContinue,		/* 继续任务 */
	ME_CXCharJump,			/* 玩家跳跃 */
	ME_CXCharMoodState,		/* 玩家表情动作 */
	ME_CXCharMove,			/* 玩家移动 */
	ME_CXPlayerDieResult,		/* 玩家死亡 */
	ME_CXChat,			/* 聊天 */
	ME_CXUseItem,			/* 使用物品 */
	ME_CXShopBuy,			/* 商店购买 */
	ME_CXShopSell,			/* 商店卖 */
	ME_CXShopRepair,		/* 商店修 */
	ME_CXCountryAppoint,		/* 国家委任 */
	ME_CXExchangeSynchLock,		/* 交易锁 */
	ME_CXStallEstablish,		/* 建立摆摊 */
	ME_CXStallOpen,			/* 开始摊位 */
	ME_CXSplitItem,			/* 物品拆分 */
	ME_CXAskSubTrainMode,		/* 代练模式 */
	ME_CXSetShowSuitMode,		/* 设置显示外装模式 */
	ME_CXOpenBox,			/* 开箱子 */
	ME_CXOpenBoxManipulate,		/* 操作开箱子 */
	ME_CXRegisterTeamRecruit,	/* 注册队伍招募 */
	ME_CXCountryCollect,		/* 国家采集 */
	ME_CXCountryDonative,		/* 国家捐赠 */
	ME_CXBusApplyInto,		/* 进入 */
	ME_CXBusLeave,			/* 离开 */
	ME_CXBusRetInto,		/* 返回进入 */
	ME_CXGuildBattle,		/* 帮战 */
	ME_CXMentalGame,		/* 答题 */
	ME_ChangeScene,			/* 切场景 */
	ME_CountryCallOfMan,		/* 国家拉人 */
	ME_TeamFollow,			/* 组队跟随 */
	ME_UseSkill,			/* 使用技能 */
	ME_GuildCallOfMan,		/* 帮会拉人 */
	ME_AcceptBuff,			/* 接受buff */
	ME_GetRide,			/* 骑乘 */
	ME_SwitchPKMode,		/* 切换PK模式 */
	ME_JoinWedding,			/* 参加婚礼 */
	ME_Enjail,			/* 被囚禁 */
	ME_Award,			/* 领奖中 */
	ME_TransGold,			/* 领取现金中 */
	ME_GotoFightPos,		/* 传送到异国发生战斗的位置 */
	ME_Wedding,			/* 举办婚礼 */
	ME_Dress,			/* 使用外装 */
	ME_GuildConvoke,		/* 帮会召集 */
	ME_Duel,			/* 决斗 */
	ME_NumOfStateEvent
};

struct _HumanStateMutexTBL
{
	BOOL	aMutexState[MS_NumOfMutexState][ME_NumOfStateEvent];
};
#endif /* HumanStateMutexDefine_h__10_10_2008_11_34 */
