/*$T MapServer/Server/Base/Config.h GC 1.140 10/10/07 10:07:20 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "TypeDefine.h"


struct SC
{
	char	m_IP[IP_SIZE];
	uint32	m_Port;
	BOOL	m_EnableDB;
};

struct SPECIAL_SETTING
{
	BOOL	m_Enable;
	ID_t	m_MapID;
	uint32	m_ServerCount;
	ID_t	m_WorldID;
	BOOL	m_PWCardEnable;

	char	m_AuServerIP[IP_SIZE];
	char	m_GLServerIP[IP_SIZE];
	char	m_BillingIP[IP_SIZE];
	char	m_DBCenterIP[IP_SIZE];

	uint32	AuServerPort;
	uint32	GLServerPort;
	uint32	BillPort;
	uint32	DBCenterPort;
	BOOL	GLServerEnableDBShare;
	SC	m_SrvInfo[MAX_SERVER];

	SPECIAL_SETTING()
	{
		memset(this, 0, sizeof(*this));
	}
};
struct BASE_SETTING
{
	ID_t	m_ServerID;
	int32	m_SystemMode;
	int32	m_ZoneSize;
	float	m_DropParam;
	float	m_ExpParam;
	int32	m_EquipmentDamagePoint;
	int32	m_DropSearchRange;
	float	m_DropPosDistance;
	int32	m_RecoverTime;
	int32	m_MaxMonster;
	int32	m_PlayerChangeSceneProtectTime;
	int32	m_MergeDBToggle;
	int32	m_TestServerToggle;
	uint32	m_PunchLevel;
	uint32  m_dwOnLineUserCountTimer;
	int32	m_GuildBattleToggle;
	int32	m_KingBattleToggle;
	int32	m_CountryBattleToggle;
	int32	m_ZhuQueBattleToggle;
	int32	m_QingLongBattleToggle;
	int32	m_LairdBattleToggle;
	int32	m_CountryBattleKingissueCount;
	int32	m_WorldCupToggle;
	int32	m_WorldCupVersion;
	int32	m_WorldCupMode;
	int32	m_PVP2v2BattleToggle;
	int32	m_PVP2v2BattleRandGroupNum;
	int32	m_PVP2v2BattleLevelFlag;
	int32	m_PVP6v6BattleToggle;
	int32	m_PVP6v6BattleRandGroupNum;
	int32	m_PVP6v6BattleLevelFlag;
	int32	m_PVP6v6BattleTime;
	int32	m_PVP6v6BattleTeamNumLimit;
	int32	m_GuildBattleRandGroupNum;
	int32	m_GuildBattleGuildMemberNumLessLimit;
	int32	m_CountryBattleLiteWeekFlag;
	int32	m_CountryBattleLiteWeekDay;
	int32	m_CountryBattleLiteWeekFreq;
	int32	m_ZhuQueBattleGuildLevel;
	int32	m_ZhuQueBattleGuildMemberCount;
	int32	m_QingLongBattleGuildLevel;
	int32	m_QingLongBattleGuildMemberCount;
	int32	m_LairdBattleGuildLevel;
	int32	m_LairdBattleGuildMemberCount;
	int32	m_MaxOnlineUser;
	int32	m_MaxPet;
	int32	m_PetHappinessInterval;
	int32	m_PetHappinessPoint;
	int32	m_HorseCallUpHappiness;
	int32	m_PetHappinessDecExp;
	int32	m_nHorseCheckUpSpend;
	int32	m_nHorseMattingSpend;
	int32	m_nHorseComposeSpend;
	int32	m_nHorseComposeLevel;
	uint32	m_uHorseComposeLockPassItem;
	uint32	m_uHorseComposeRepentItem;
	int32	m_MattingPrimaryHorseGeneration;
	int32	m_MattingSecondaryHorseGeneration;
	int32	m_MattingPrimaryHorseLevel;
	int32	m_MattingSecondaryHorseLevel;
	int32	m_MattingHorseLevelPara;
	int32	m_ChildHorseTakeLevelPara;
	int32	m_ChildHorsePerceptionPara;
	int32	m_ChildHorsePerceptionMode;
	int32	m_PerceptionLimit;
	int32	m_PerceptionItemPara;
	int32	m_HorseCallupLevelThanPlayer;
	int32	m_HorseRemainPointPara;
	int32	m_CaptureHorseMinPlayerLevel;
	int32	m_TakeHorseNumIncLevelStep;
	int32	m_DecHorseHappOnMonsterKill;
	int32	m_DecHorseHpaaOnHumanKill;
	int32	m_RestoreHorseHappyMoney;

	int32	m_RemainPointOnLevelup;
	int32	m_HorseReplaceOldSkillRate[12][12];

	int32	m_PetReFollowDistanceB;
	int32	m_PetReFollowDistanceC;
	int32	m_PetStandDistanceToOnwerMIN;
	int32	m_PetStandDistanceToOnwerMAX;
	int32	m_PetBeginMoveRandom;
	int32	m_PetMoveToAPlaceRandom;

	int32	m_DefaultRespawnTime;
	int32	m_ValidAttackTime;
	int32	m_DropBoxRecycleTime;
	int32	m_DropProtectTime;
	int32	m_TimeChangeInterval;
	int32	m_PositionRange;
	int32	m_AIType;
	int32	m_DisconnectTime;
	char	m_UserPath[_MAX_PATH];
	int32	m_MaxPortal;
	int32	m_MaxSkillObj;
	int32	m_DefaultBodyTime;
	int32	m_OutGhostTime;
	float	m_CanGetExpRange;
	int32	m_DefaultMoveSpeed;
	int32	m_DefaultWalkSpeed;
	int32	m_DefaultAttackSpeed;
	int32	m_WallowAge;
	int32	m_WallowStartTime;
	int32	m_WallowStartTime2;
	int32	m_WallowAwokeTime;
	int32	m_HumanVERecoverInterval;
	int32	m_HumanPKValueRecoverInterval;
	int32	m_HumanPKValueRecoverSize;
	int32	m_HumanHGRecoverInterval;
	int32	m_ProfessionRAGERecoverInterval[PROFESSION_NUMBER];
	/*
	int32	m_WUSHIRAGERecoverInterval;
	int32	m_JIANXIARAGERecoverInterval;
	int32	m_QISHERAGERecoverInterval;
	int32	m_HUOQIANGRAGERecoverInterval;
	int32	m_XIANZHIRAGERecoverInterval;
	int32	m_SAMANRAGERecoverInterval;
	*/
	int32	m_MaxCurPlayerLevel;
	float	m_fInherenceFixParam;

	int32	m_WallowInterval_1;
	int32	m_WallowInterval_2;
	int32	m_WallowInterval_3;
	int32	m_WallowTotalTime_1;
	int32	m_WallowTotalTime_2;
	int32	m_WallowTotalTime_3;
	int32	m_WallowTotalTime_5;
	int32	m_WallowTotalTime_3dot5;
	int32	m_ResetWallowTime;

	int32	m_SaveOnlineTimeInterval;
	int32	m_ChatReportCoolTime;
	int32	m_ChatReportMinCount;
	int32	m_WatchKeywordRand;
	int32	m_MailCoolDownTime;

	int32	m_DefaultRefreshRate;
	int32	m_ItemUpdateRate;
	int32	m_ItemUnLockCDTime;
	int32	m_DefaultCheckZoneRate;
	int32	m_DefaultRefuseScanTime;
	int32	m_MaxPlatform;
	int32	m_MaxSpecial;
	int32	m_MaxPlayerShopNum;
	int32	m_MaxTimerCount;
	int32	m_nMaxHumanUseTimer;
	int32	m_nAvailableFollowDist;
	int32	m_nTimeForLoseFollow;
	float	m_nTeamRage;
	int32	m_nTeamFreshTime;
	int32	m_TeamCount1Rate;
	int32	m_TeamCount2Rate;
	int32	m_TeamCount3Rate;
	int32	m_TeamCount4Rate;
	int32	m_TeamCount5Rate;
	int32	m_TeamCount6Rate;
	int32	m_TeamGoodBad;
	int32	m_TeamGoodBadSpecial;
	int32	m_nGoodBadPlayerLevel;
	int32	m_nGoodBadMonsterLevelLow;
	int32	m_nGoodBadMonsterLevelHigh;
	int32	m_nTeamGoodBadImpact;
	float	m_fTeamGoodBadImpactRate;
	float	m_fPrenticeExpRefixWhenMasterHere;
	float	m_fPrenticeExpRefixWhenHaveTitle;

	int32	m_nFoundDurationSec;
	int32	m_nDefaultMaxMemberCount;
	int32	m_nResponseUserCount;
	int32	m_nPasswdPoint;
	int32	m_nPromptPoint;
	int32	m_nDeleteDelayTime;
	int32	m_nProtectDelayTime;
	int32	m_nProtectDefaultTime;
	int32	m_nProtectDefaultError;
	int32	m_nExpPoint;
	int32	m_nHashOnlineUserCount;
	int32	m_nHashMailUserCount;
	int32	m_nMaxOfflineUserCount;
	float	m_fRespawnParam;
	int32	m_KickUserTime;
	int32	m_nDefaultDamageFluctuation;
	int32	m_nCriticalDamageRate;
	int32	m_nToughEffCriticalDamage;

	int32	m_nMinGoodBadValue;
	int32	m_nMaxGoodBadValue;
	int32	m_nLevelNeeded;
	int32	m_nMemberLevel;
	float	m_fGoodBadRadius;
	int32	m_nBonusPerMember;
	int32	m_nMaxBonus;
	int32	m_nPenaltyWhenMemberDie;

	int32	m_nMinPaiScore;
	int32	m_nMinZiPaiScore;
	int32	m_nComMonsterDrop;
	int32	m_nSenMonsterDrop;
	int32	m_nBossDrop;
	int32	m_nEquipDurPer;
	int32	m_MinEquipDurReduce;
	int32	m_nRefreshAttrToWorldInterval;

	int32	m_nSubTrainExp;
	int32	m_nSubTrainMoney;
	int32	m_nDelateNum;
	int32	m_nVoteNum;
	int32	m_nVoteTime;

	int32	m_nCollectInterval;
	int32	m_nRejoinGuildInterval;
	int32	m_ApplyKingMoney;
	int32	m_ApplyKingMoneyType;
	int32	m_ApplyKingGuildLevel;
	int32	m_ApplyKingGuildCount;
	int32	m_ApplyKingWeek;
	int32	m_ApplyKingStartTime;
	int32	m_ApplyKingEndTime;

	int32	m_ApplyCountryBanghuiMoney[COUNTRY_GUILD_COUNT];
	int32	m_ApplyCountryBanghuiMoneyType[COUNTRY_GUILD_COUNT];
	int32	m_ApplyCountryBanghuiLevel[COUNTRY_GUILD_COUNT];
	int32	m_ApplyCountryBanghuiMemberCount[COUNTRY_GUILD_COUNT];
	int32	m_ApplyCountryBanghuiWeek[COUNTRY_GUILD_COUNT];
	int32	m_ApplyCountryBanghuiStartTime[COUNTRY_GUILD_COUNT];
	int32	m_ApplyCountryBanghuiEndTime[COUNTRY_GUILD_COUNT];		

	int32	m_DonateMoneyType;
	int32	m_nForbidChatDuration;
	int32	m_nEnjailDuration;
	int32	m_FortuneDuration;
	int32	m_FortuneDuration_RuoGuo;
	int32	m_FortuneNeedMoney;
	int32	m_FortunePrice1;
	int32	m_FortunePrice2;
	int32	m_FortunePrice3;
	int32	m_FortunePrice4;
	int32	m_FortuneMaxCount;
	int32	m_AssignGeneralMaxCount;
	int32	m_AssignLMinisterMaxCount;
	int32	m_AssignRMinisterMaxCount;
	int32	m_AssignLGuardMaxCount;
	int32	m_AssignRGuardMaxCount;
	int32	m_CancelGeneralMaxCount;
	int32	m_CancelLMinisterMaxCount;
	int32	m_CancelRMinisterMaxCount;
	int32	m_CancelLGuardMaxCount;
	int32	m_CancelRGuardMaxCount;
	int32	m_ModifyNoticeMaxCount;
	int32	m_CollectMaxCount;
	int32	m_ForbidChatMaxCount;
	int32	m_EnjailMaxCount;
	int32	m_AssoilMaxCount;
	int32	m_nLevelOfCreateGuild;
	int32	m_nLevelOfJoinGuild;
	int32	m_arrActivityParam[GUILD_ACTIVITY_PARAM_COUNT];
	
	int32	m_arrActivityParamMaxValue[GUILD_ACTIVITY_PARAM_COUNT];

	int32	m_nMoneyOfCreateGuild;
	int32	m_nMoneyTypeOfCreateGuild;
	int32	m_nMoneyTypeOfLevelupGuild;
	int32	m_nModifyFamilyNameInvertal;
	int32	m_nModifyTitleInvertal;
	int32	m_nModifyDescInvertal;
	int32	m_KingBattlePrise;
	int32	m_nEnableGuildDie;
	char	m_szGuildDieDate[32];

	int32		m_fMoneyRate;
	int32		m_nMoneyExchangeFlag;
	int32		m_nGoldStall;

	int32	m_nBusCreateTime;

	float	m_fDepleteFPTime;
	int32	m_nDepleteFPValue;
	int32	m_nMarryNeedFriendPoint;
	int32	m_nMarryNeedLevel;
	int32	m_nMarryNeedDistance;
	int32	m_nMarryNeedItem;
	int32	m_nMarryNeedGold;
	int32	m_nMarryFreeMonth;
	int32	m_nMarryFreeDay;
	int32	m_nRequireMasterLevel;
	int32	m_nPrenticeLevelLow;
	int32	m_nMasterOrPrenticeLevelConfine;
	int32	m_nMasterOrPrenticeTimeRequire;
	int32	m_nFriendGiftTimeLimit;
	int32	m_nFriendGiftTimes;
	int32	m_nMaxFriendPoint;
	int32	m_nBlackDecFriendPoint;
	int32	m_nEnemyDecFriendPoint;
	int32	m_nToggleDebugBehavior_Template;
	int32	m_nWeddingItem;
	float	m_fWeddingMoneyRate;
	int32	m_nBankDataValidTime;
	int32	m_nBankMailSendTime;

	uint32	m_uPurpleAttRate1;
	uint32	m_uPurpleAttRate2;
	uint32	m_uPurpleAttRate3;
	uint32	m_uBlueAttrRate1; // 打造装备产生3-7条数性的权重
	uint32	m_uBlueAttrRate2;
	uint32	m_uBlueAttrRate3;
	uint32	m_uBlueAttrRate4;
	uint32	m_uBlueAttrRate5;
	int32	m_nGemUninst_NeedItem;
	int32	m_nGemUninst_NeedMoney;
	int32	m_nEquipCopy_NeedItem1;
	int32	m_nEquipCopy_NeedItem2;
	int32	m_nEquipCopy_NeedItem3;
	int32	m_nEquipCopy_NeedItem4;
	int32	m_nEquipCopy_NeedItem5;
	int32	m_nEquipCopy_NeedMoney;
	BOOL	m_PWCardEnable;
	int32	m_nStockCharge;				//股票交易税收百分比
	uint32	m_uStockValidTime;			//股票挂单的有效时间(秒)
	uint32	m_uStockRegisterCharge;		//开户的费用（现银）
	uint32	m_uStockAccCDTime;			//超过此时间不操作(秒)，进入冷却状态，开始扣除账户余额
	uint32	m_uStockAccCDTimeSendMail;	//冷却状态后，邮件通知用户的时间
	uint32	m_uStockAccCDInterval;		//进入冷却状态后，股票扣除MONEY的时间间隔
	uint32	m_uStockAccLateFeeGold;		//滞纳金: StockAccCDTime时间到，扣除现金
	uint32	m_uStockAccLateFeeSiller;	//滞纳金: StockAccCDTime时间到，扣除现银

	int32	m_WorldGoldShopToggle;		//现金寄售开关，1为打开，0为关闭
	int32	m_TestGoldShopToggle;		//供测试用的现金商店页开关，1为打开，0为关闭

	int32	m_nCompressPacket;			//是否启用压缩
	int32	m_nCompressGlobalLog;		//是否记录压缩全局Log
	int32   m_nEquipSwitchNeedLevel;	// 装备转化需要的级别
	int32	m_nMapThreadCount;			//场景最大线程数
	int32	m_nEnableRandEncryptKey;	//是否启用随机密钥
	int32	m_nUpdateDBBefore;			//成1到成2数据库升级前标记，1为打开，0为关闭
	int32	m_nUpdateDBAfter;			//成1到成2数据库升级后标记，1为打开，0为关闭
	int32	m_nQMoneyToggle;			//Q币奖励开关，0为关闭，1为打开
	uchar	m_uEnableCreateNewChar;		//是否允许创建角色，1为允许，0为不允许

	int32	m_nCountryDelateNeedLevel;
	int32	m_nCountryDelateNeedUserCount;
	int32	m_nCountryDelateNeedChieftainPosInTopList;

	int32	m_nToggleDebugInherenceBalance;		//天赋平衡调试信息开关
	int32	m_nToggleDebugInherenceZhuanjing;		//天赋专精调试信息开关
	
	int32	m_nOpenWeakCountryCheck;	// 2010-12-14 by rj 弱国玩法开关

	int32   m_nToggleCountryColleague;	// 系统自动结盟开关,国王申请结盟解盟开关

	BASE_SETTING()
	{
		m_ServerID = INVALID_ID;
		m_SystemMode = 0;
		m_ZoneSize = 10;
		m_EquipmentDamagePoint = 1000;
		m_DropSearchRange = 200;
		m_DropPosDistance = 2.0;
		m_RecoverTime = 1000;
		m_MaxMonster = 1000;
		m_MaxPet = 1000;
		m_PetHappinessInterval = 600000;
		m_HorseCallUpHappiness = 60;
		m_DefaultRespawnTime = 300000;
		m_DropBoxRecycleTime = 300000;
		m_ValidAttackTime = 6000;
		m_DropProtectTime = 100000;
		m_TimeChangeInterval = 300000;
		m_PositionRange = 10;
		m_AIType = 1;
		m_DisconnectTime = 0;
		memset(m_UserPath, 0, _MAX_PATH);
		m_MaxPortal = 0;
		m_MaxPlatform = 0;
		m_MaxSpecial = 1024;
		m_MaxPlayerShopNum = 512;
		m_MaxSkillObj = 1024;
		m_DefaultBodyTime = 0;
		m_OutGhostTime = 0;
		m_CanGetExpRange = 30.0f;
		m_DefaultMoveSpeed = 2800;
		m_DefaultWalkSpeed = 1000;
		m_DefaultAttackSpeed = 2000;
		m_HumanVERecoverInterval = 900000;
		m_HumanPKValueRecoverInterval = 3600000;
		m_HumanPKValueRecoverSize = 1;
		m_HumanHGRecoverInterval = 5000;
		/*
		m_WUSHIRAGERecoverInterval = 5000;
		m_JIANXIARAGERecoverInterval = 5000;
		m_QISHERAGERecoverInterval = 5000;
		m_HUOQIANGRAGERecoverInterval = 5000;
		m_XIANZHIRAGERecoverInterval = 5000;
		m_SAMANRAGERecoverInterval = 5000;
		*/
		for(int32 i=0; i<PROFESSION_NUMBER; i++)
		{
			m_ProfessionRAGERecoverInterval[i] = 5000;
		}
		m_MaxCurPlayerLevel = MAX_PLAYER_EXP_LEVEL;
		m_fInherenceFixParam = 1.0f;
		m_SaveOnlineTimeInterval = 60000;
		m_MergeDBToggle = 0;
		m_TestServerToggle = 0;
		m_ChatReportCoolTime = 0;
		m_nUpdateDBBefore = 0;
		m_nUpdateDBAfter = 0;
		m_nQMoneyToggle = 0;
		m_uEnableCreateNewChar = 1;

		m_DefaultRefreshRate = 60000;
		m_DefaultCheckZoneRate = 1000;
		m_nAvailableFollowDist = 15;
		m_nTimeForLoseFollow = 30;
		m_nTeamRage = 20.0f;
		m_nTeamFreshTime = 1;
		m_TeamCount1Rate = 100;
		m_TeamCount2Rate = 100;
		m_TeamCount3Rate = 100;
		m_TeamCount4Rate = 100;
		m_TeamCount5Rate = 100;
		m_TeamCount6Rate = 100;

		m_TeamGoodBad = 0;
		m_TeamGoodBadSpecial = 0;
		m_nGoodBadPlayerLevel = 0;
		m_nGoodBadMonsterLevelLow = 0;
		m_nGoodBadMonsterLevelHigh = 0;
		m_nTeamGoodBadImpact = 0;
		m_fTeamGoodBadImpactRate = 1.0f;
		m_fPrenticeExpRefixWhenMasterHere = 0.f;
		m_fPrenticeExpRefixWhenHaveTitle = 0.f;

		m_nFoundDurationSec = 864000;
		m_nDefaultMaxMemberCount = 160;
		m_nResponseUserCount = 10;
		m_nPasswdPoint = 0;
		m_nPromptPoint = 0;
		m_nDeleteDelayTime = 0;
		m_nProtectDelayTime = 0;
		m_nProtectDefaultTime = 10;
		m_nProtectDefaultError = 5;
		m_nExpPoint = 0;
		m_nHashOnlineUserCount = 1000;
		m_nHashMailUserCount = 1000;
		m_nMaxOfflineUserCount = 0;
		m_fRespawnParam = 1.0f;
		m_KickUserTime = 300000;
		m_nDefaultDamageFluctuation = 10;
		m_nCriticalDamageRate = 100;
		m_nToughEffCriticalDamage = 100;

		m_nMinGoodBadValue = 0;
		m_nMaxGoodBadValue = 9999;
		m_nLevelNeeded = 31;
		m_nMemberLevel = 19;
		m_fGoodBadRadius = 15.;
		m_nBonusPerMember = 1;
		m_nMaxBonus = 2;
		m_nPenaltyWhenMemberDie = 10;

		m_nMinPaiScore = 100;
		m_nMinZiPaiScore = 300;
		m_nComMonsterDrop = 0;
		m_nSenMonsterDrop = 0;
		m_nBossDrop = 0;
		m_nEquipDurPer = 10;
		m_MinEquipDurReduce = 0;
		m_nHorseCheckUpSpend = 100;
		m_nHorseMattingSpend = 20000;
		m_nHorseComposeSpend = 20000;
		m_nHorseComposeLevel = 40;
		m_uHorseComposeLockPassItem = 0;
		m_uHorseComposeRepentItem = 0;
		m_nRefreshAttrToWorldInterval = 300000;

		m_nDelateNum = 3;
		m_nVoteNum = 100;
		m_nVoteTime = 240;

		m_nCollectInterval = 0;
		m_nRejoinGuildInterval = 0;
		m_PetReFollowDistanceB = 0;
		m_PetReFollowDistanceC = 0;
		m_PetStandDistanceToOnwerMIN = 0;
		m_PetStandDistanceToOnwerMAX = 0;
		m_PetBeginMoveRandom = 0;
		m_PetMoveToAPlaceRandom = 0;
		m_fMoneyRate = 0;

		m_nBusCreateTime = 0;

		m_PlayerChangeSceneProtectTime = 0;

		m_fDepleteFPTime = 0.0;
		m_nDepleteFPValue = 0;
		m_nMarryNeedFriendPoint = 0;
		m_nMarryNeedLevel = 0;
		m_nMarryNeedDistance = 0;
		m_nMarryNeedItem = 0;
		m_nMarryNeedGold = 0;
		m_nMarryFreeMonth = 0;
		m_nMarryFreeDay = 0;
		m_nRequireMasterLevel = 0;
		m_nPrenticeLevelLow = 0;
		m_nMasterOrPrenticeLevelConfine = 0;
		m_nMasterOrPrenticeTimeRequire = 0;
		m_nFriendGiftTimeLimit = 0;
		m_nFriendGiftTimes = 0;
		m_nMaxFriendPoint = 0;
		m_nBlackDecFriendPoint = 0;
		m_nEnemyDecFriendPoint = 0;
		m_nToggleDebugBehavior_Template = 0;
		m_nWeddingItem = 0;
		m_fWeddingMoneyRate = 1.0f;
		m_DonateMoneyType = 0;
		m_ApplyKingMoneyType = 2;
		m_nMoneyTypeOfLevelupGuild = 2;
		m_nMoneyTypeOfCreateGuild = 2;
		m_nBankDataValidTime = 604800;
		m_nBankMailSendTime = 10800;
		m_uPurpleAttRate1 = 0;
		m_uPurpleAttRate2 = 0;
		m_uPurpleAttRate3 = 0;
		m_nGemUninst_NeedItem = 0;
		m_nGemUninst_NeedMoney = 0;
		m_nEquipCopy_NeedItem1 = 0;
		m_nEquipCopy_NeedItem2 = 0;
		m_nEquipCopy_NeedItem3 = 0;
		m_nEquipCopy_NeedItem4 = 0;
		m_nEquipCopy_NeedMoney = 0;
		m_PWCardEnable = 0;
		m_dwOnLineUserCountTimer = 0;
		m_KingBattlePrise = 0;
		m_nEnableGuildDie = 0;
		memset( m_szGuildDieDate, 0, 32 );
		m_nStockCharge=2;				
		m_uStockValidTime=86400;
		m_uStockRegisterCharge = 1000;
		m_uStockAccCDTime = 259200;
		m_uStockAccCDTimeSendMail = 172800;
		m_uStockAccCDInterval = 86400;
		m_uStockAccLateFeeGold = 1000;
		m_uStockAccLateFeeSiller = 30000;
		m_WorldGoldShopToggle = 0;
		m_TestGoldShopToggle  = 0;
		m_nCompressPacket = 0;
		m_nCompressGlobalLog = 0;
		m_nEnableRandEncryptKey = 0;
		m_nCountryDelateNeedLevel = 45;
		m_nCountryDelateNeedUserCount = 150;
		m_nCountryDelateNeedChieftainPosInTopList = 5;
		m_MailCoolDownTime = 0;

		m_nToggleDebugInherenceBalance = 0;
		m_nToggleDebugInherenceZhuanjing = 0;
		m_nOpenWeakCountryCheck = 0;
		m_nToggleCountryColleague = 0;
		};
	~BASE_SETTING()
	{
	};
};

struct LOGIN_SETTING
{
	ID_t	m_LoginID;
	char	m_DBIP[IP_SIZE];
	uint32	m_DBPort;
	char	m_DBName[DATABASE_STR_LEN];
	char	m_DBUser[DB_USE_STR_LEN];
	char	m_DBPassword[DB_PASSWORD_STR_LEN];
	int32	m_MaxClientInSameIP;
	BOOL	m_CheckAnswer;
	BOOL	m_EncryptToggle;
	BOOL	m_RsaToggle;
	BOOL	m_AutoEncryptToggle;
	uchar	m_EncryptArith[VALID_ENCRYPT_ARITH_NUM];
	uint16	m_uLoginCountSameIPPerDay;
	uint16	m_uLoginCountPerDay;

	LOGIN_SETTING()
	{
		m_LoginID = INVALID_ID;
		memset(m_DBIP, 0, IP_SIZE);
		m_DBPort = 0;
		memset(m_DBName, 0, DATABASE_STR_LEN);
		memset(m_DBUser, 0, DB_USE_STR_LEN);
		memset(m_DBPassword, 0, DB_PASSWORD_STR_LEN);
		m_MaxClientInSameIP = 15;
		m_CheckAnswer = FALSE;
		m_EncryptToggle = FALSE;
		m_RsaToggle		= FALSE;
		m_AutoEncryptToggle = FALSE;
		memset(m_EncryptArith, -1, sizeof(m_EncryptArith));
		m_uLoginCountSameIPPerDay = 300;
		m_uLoginCountPerDay = 30;
	}
	~LOGIN_SETTING()
	{
	}
};

struct BILLING_SETTING
{
	ID_t	m_BillingID;
	char	m_IP[IP_SIZE];
	uint32	m_Port;

	// ... (Billing) -->
	char	m_DBIP[IP_SIZE];
	uint32	m_DBPort;
	char	m_DBName[DATABASE_STR_LEN];
	char	m_DBUser[DB_USE_STR_LEN];
	char	m_DBPassword[DB_PASSWORD_STR_LEN];
	// <--

	BILLING_SETTING()
	{
		m_BillingID = INVALID_ID;
		memset(m_IP, 0, IP_SIZE);
		m_Port = 0;
		// ... (Billing) -->
		memset(m_DBIP, 0, IP_SIZE);
		m_DBPort = 0;
		memset(m_DBName, 0, DATABASE_STR_LEN);
		memset(m_DBUser, 0, DB_USE_STR_LEN);
		memset(m_DBPassword, 0, DB_PASSWORD_STR_LEN);
		// <--
	}
	~BILLING_SETTING()
	{
	}
};

struct GL_SETTING
{
	ID_t		m_WorldID;
	MK_VALUE	m_GuildKey;
	MK_VALUE	m_MailKey;
	MK_VALUE	m_CountryKey;
	MK_VALUE	m_SceneVarKey;
	MK_VALUE	m_TopListKey;
	MK_VALUE	m_ShopKey;
	MK_VALUE	m_BankKey;
	MK_VALUE	m_MasterCandidateKey;
	MK_VALUE	m_PrenticeCandidateKey;
	MK_VALUE	m_StockCandidateKey;
	MK_VALUE	m_StockAccCandidateKey;
	MK_VALUE	m_StockRecordCandidateKey;
	MK_VALUE	m_DynamicShopKey;
	BOOL		m_EnableShareMem;
	GL_SETTING()
	{
		m_WorldID = INVALID_ID;
		m_GuildKey = 0;
		m_MailKey = 0;
		m_CountryKey = 0;
		m_SceneVarKey = 0;
		m_TopListKey = 0;
		m_ShopKey = 0;
		m_BankKey = 0;
		m_MasterCandidateKey = 0;
		m_PrenticeCandidateKey = 0;
		m_StockCandidateKey = 0;
		m_StockAccCandidateKey = 0;
		m_StockRecordCandidateKey = 0;
		m_DynamicShopKey = 0;
		m_EnableShareMem = FALSE;
	}
	~GL_SETTING()
	{
	}
};

struct DBCENTER_SETTING
{
	ID_t	m_DBCenterID;
	char	m_IP[IP_SIZE];
	uint32	m_Port;
	char	m_DBIP[IP_SIZE];
	uint32	m_DBPort;
	char	m_DBName[DATABASE_STR_LEN];
	char	m_DBUser[DB_USE_STR_LEN];
	char	m_DBPassword[DB_PASSWORD_STR_LEN];
	uint32	m_DBCenterUserCount;

	DBCENTER_SETTING()
	{
		m_DBCenterID = INVALID_ID;
		memset(m_IP, 0, IP_SIZE);
		m_Port = 0;
		memset(m_DBIP, 0, IP_SIZE);
		m_DBPort = 0;
		memset(m_DBName, 0, DATABASE_STR_LEN);
		memset(m_DBUser, 0, DB_USE_STR_LEN);
		memset(m_DBPassword, 0, DB_PASSWORD_STR_LEN);
		m_DBCenterUserCount = 0;
	}
	~DBCENTER_SETTING()
	{
	}
};

struct SSharememData
{
	MK_VALUE	m_Key;
	eSHM_TYPE	m_Type;

	SSharememData()
	{
		m_Key = 0;
		m_Type = ST_INVAILD;
	}
};
struct DBSHARE_SETTING
{
	uint32		m_MKObjCount;

	SSharememData	*m_pShareData;

	char		m_DBIP[IP_SIZE];
	uint32		m_DBPort;
	char		m_DBName[DATABASE_STR_LEN];
	char		m_DBUser[DB_USE_STR_LEN];
	char		m_DBPassword[DB_PASSWORD_STR_LEN];
	int32		MKInterval;
	int32		DATAInterval;
	DBSHARE_SETTING()
	{
		m_pShareData = NULL;
		m_MKObjCount = 0;
		memset(m_DBIP, 0, IP_SIZE);
		m_DBPort = -1;
		memset(m_DBName, 0, DATABASE_STR_LEN);
		memset(m_DBUser, 0, DB_USE_STR_LEN);
		memset(m_DBPassword, 0, DB_PASSWORD_STR_LEN);
		MKInterval = 60;
		DATAInterval = 300000;
	}
	~DBSHARE_SETTING()
	{
		KSafeDelete_ARRAY(m_pShareData);
	};
};
struct SERVER_DATA
{
	ID_t		m_ServerID;
	ID_t		m_MachineID;
	char		m_IP[IP_SIZE];
	uint32		m_Port;
	int32		m_Type;

	MK_VALUE	m_HumanSMKey;
	MK_VALUE	m_ItemSerialKey;
	BOOL		m_EnableDBShare;

	SERVER_DATA()
	{
		Init();
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Init()
	{
		m_ServerID = INVALID_ID;
		m_MachineID = INVALID_ID;
		memset(m_IP, 0, IP_SIZE);
		m_Port = 0;
		m_Type = -1;
		m_EnableDBShare = FALSE;
	}
};
struct SServerWorld
{
	char	m_IP[IP_SIZE];
	uint32	m_Port;

	SServerWorld()
	{
		Init();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Init()
	{
		memset(m_IP, 0, IP_SIZE);
		m_Port = 0;
	}
};

struct _SERVER_AUTH
{
	char	m_IP[IP_SIZE];
	uint32	m_Port;

	_SERVER_AUTH()
	{
		Init();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Init()
	{
		memset(m_IP, 0, IP_SIZE);
		m_Port = 0;
	}
};

struct MONITOR_CONFIG
{
	char	m_ServerIP[IP_SIZE];
	uint32	m_ServerPort;
	char	m_ClientIP[IP_SIZE];
	char	m_Account[MAX_ACCOUNT];
	char	m_Password[MAX_PASSWORD];

	MONITOR_CONFIG()
	{
		memset(this, 0, sizeof(MONITOR_CONFIG));
	}
};

struct LOGSERVER_CONFIG
{
	uchar	m_bEnable;
	char	m_ServerIP[IP_SIZE];
	uint16	m_ServerPort;
};

#define SERVER_CAPACITY 128

struct SERVER_SETTING
{
	SERVER_DATA	*m_pServer;
	uint32		m_ServerCount;
	int32		m_HashServer[SERVER_CAPACITY];
	SServerWorld	m_World;
	_SERVER_AUTH	m_Auth;

	SERVER_SETTING()
	{
		m_pServer = NULL;
		m_ServerCount = 0;
		for(int32 i = 0; i < SERVER_CAPACITY; i++)
		{
			m_HashServer[i] = -1;
		}
	}
	~SERVER_SETTING()
	{
		KSafeDelete_ARRAY(m_pServer);
		m_ServerCount = 0;
	}
};

struct MAP_CONFIG
{
	MapID_t		m_MapID;
	int32		m_IsActive;
	char		m_szName[_MAX_PATH];
	char		m_szFileName[_MAX_PATH];
	ID_t		m_ServerID;
	ID_t		m_Type;

	ID_t		m_ThreadIndex;
	ID_t		m_ClientRet;
	char		m_cSecurityLevel;
	char		m_cRestrictiveMode;
	BOOL		m_bPunish;
	int32		m_DefaultX;
	int32		m_DefaultZ;
	CampID_t	m_DefaultCamp;
	int32		m_BusParam;

	char        m_szNavFileName[_MAX_PATH];
	char        m_szMonsterFileName[_MAX_PATH];
	char        m_szSceneConfigName[_MAX_PATH];
	char        m_szGrowPointDataName[_MAX_PATH];
	char        m_szGrowPointSetupName[_MAX_PATH];
	char        m_szPatrolPointName[_MAX_PATH];

	MAP_CONFIG()
	{
		Init();
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Init()
	{
		m_MapID = INVALID_ID;
		m_IsActive = 1;
		memset(m_szName, 0, _MAX_PATH);
		memset(m_szFileName, 0, _MAX_PATH);
		m_ServerID = INVALID_ID;
		m_Type = INVALID_ID;
		m_ThreadIndex = INVALID_INDEX;
		m_ClientRet = INVALID_INDEX;
		m_cSecurityLevel = -1;
		m_cRestrictiveMode = -1;
		m_bPunish = TRUE;
		m_DefaultX = 0;
		m_DefaultZ = 0;
		m_DefaultCamp = INVALID_CAMP;
		m_BusParam = -1;
	}
};
struct MAP_INFO
{
	MAP_CONFIG	*m_pMap;
	uint32		m_MapCount;
	int32		m_HashScene[MAX_SCENE];

	MAP_INFO()
	{
		m_pMap = NULL;
		m_MapCount = 0;
		for(int32 i = 0; i < MAX_SCENE; i++)
		{
			m_HashScene[i] = -1;
		}
	};

	~MAP_INFO()
	{
		KSafeDelete_ARRAY(m_pMap);
		m_MapCount = 0;
	};
};

struct MANAGE_LOG_CONFIG
{
	ulong	m_dwOnLineUserCountTimer;
	MANAGE_LOG_CONFIG()
	{
		m_dwOnLineUserCountTimer = 0;
	}
};

struct DBSHARE_CONFIG
{
	uint32 m_uShareType;
	uint32 m_uShareIndex;
	DBSHARE_CONFIG()
	{
		m_uShareType = 0;
		m_uShareIndex = 0;
	}
};


#define MULTI_GROUP_MAX_COUNT	16	// 2010-12-9 by rj GroupCount 上限调整了 16，与 MAX_SERVER_CONNECTOR_POOL_SIZE 保持一致
#define PERGROUP_MAX_MAPCOUNT	16	// 2010-10-19 by rj 单服最大 map 逻辑服务器数量

struct MULTIGROUP_SERVER_INFO
{
	char		m_IP[IP_SIZE];
	uint32		m_Port;
	ID_t		m_WorldID;
	char		m_aBackMapIp[PERGROUP_MAX_MAPCOUNT][IP_SIZE];
	uint32		m_aBackMapPort[PERGROUP_MAX_MAPCOUNT];

	MULTIGROUP_SERVER_INFO()
	{
		m_WorldID = INVALID_ID;
		memset(m_aBackMapIp, 0, PERGROUP_MAX_MAPCOUNT * IP_SIZE);
		memset(m_aBackMapPort, 0, PERGROUP_MAX_MAPCOUNT * sizeof(uint32));
	}
};

struct MULTIGROUP_CONFIG
{
	int32					m_nGroupCount;
	MULTIGROUP_SERVER_INFO	m_DBCenterInfo[MULTI_GROUP_MAX_COUNT];
	MULTIGROUP_SERVER_INFO	m_GLServerInfo[MULTI_GROUP_MAX_COUNT];
	int32					m_nMax2v2SceneCnt; // 跨服 2v2 战场最大场景数量配置 2010-9-23 by rj
	int32					m_nMax6v6SceneCnt; // 跨服 6v6 战场最大场景数量配置 2010-10-14 by rj

	MULTIGROUP_CONFIG()
	{
		m_nGroupCount = 0;
		m_nMax2v2SceneCnt = 0;
		m_nMax6v6SceneCnt = 0;
	}

	MULTIGROUP_SERVER_INFO* GetDBCenterInfo(ID_t WorldID)
	{
		for( int32 i=0; i<m_nGroupCount; i++ )
		{
			if( m_DBCenterInfo[i].m_WorldID == WorldID )
			{
				return &m_DBCenterInfo[i];
			}
		}
		return NULL;
	}

	MULTIGROUP_SERVER_INFO* GetGLServerInfo(ID_t WorldID)
	{
		for( int32 i=0; i<m_nGroupCount; i++ )
		{
			if( m_GLServerInfo[i].m_WorldID == WorldID )
			{
				return &m_GLServerInfo[i];
			}
		}
		return NULL;
	}
};

class	SettingSystem
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	SettingSystem();
	~	SettingSystem();

	BOOL	Init();
	BOOL	InitLog(const char *LogPtr);


	ID_t	MapID2ServerID(MapID_t sID) const;
	ID_t	Key2ServerID(MK_VALUE key) const;
	BOOL	CheckSceneEnable(MapID_t sID) const;

private:

	void	LoadBaseServerConfig();
	void	LoadExtServerConfig();
	void	LoadMultiGroupConfig();
	void	LoadDBConfig();
	void	LoadDBShareConfig();
	void	LoadServerIndexConfig();
	void	LoadWorldIndexConfig();
	void	LoadGameConfig();
	void	LoadGameToggleConfig();
	void	LoadMapData();
	void	LoadMapData_Try();
	void	LoadMapData_ReCache();
	void	LoadFubenSetting();
	void	LoadFubenSetting_Try();
	void	LoadFubenSetting_ReCache();
	void	LoadMonitorInfo();
	void	LoadMonitorInfo_Try();
	void	LoadStockMonitorInfo_Try();
	void	LoadMonitorInfo_Reload();
	void	LoadPetConfigTable();
	void	LoadLogServerConfig();
	
	void	PrintAllConfigInfo();


/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	BASE_SETTING		m_ConfigInfo;
	LOGIN_SETTING		m_LoginInfo;
	DBCENTER_SETTING	m_DBCenterInfo;
	GL_SETTING			m_WorldInfo;
	SERVER_SETTING		m_ServerInfo;
	MAP_INFO			m_MapInfo;
	DBSHARE_SETTING		m_ShareMemInfo;
	BILLING_SETTING		m_BillingInfo;
	MONITOR_CONFIG		m_MonitorInfo;
	MONITOR_CONFIG		m_StockMonitorInfo;
	DBSHARE_CONFIG		m_DBShareConfig;
	MULTIGROUP_CONFIG	m_MultiGroupConfig;
	LOGSERVER_CONFIG	m_LogServerInfo;
	char				m_LogPath[255];
};

extern SettingSystem	g_Config;
#endif
