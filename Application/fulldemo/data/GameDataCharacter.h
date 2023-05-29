#ifndef __CHARACTERDATA_H__
#define __CHARACTERDATA_H__


#include "data/struct/GameDataStructCharacterData.h"

struct SCampData;
class Character;
struct SDataCharacter;

class KCharatcterBaseData
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	/*
	 ===================================================================================================================
	    Character 基本属性 ;
	    国家
	 ===================================================================================================================
	 */
	int32 Get_Country(void) const
	{
		return m_pData->m_nCountry;
	}

	void	Set_Country(int32 country);

	/*
	 ===================================================================================================================
	    种族(性别)
	 ===================================================================================================================
	 */
	int32 Get_RaceID(void) const
	{
		return m_pData->m_nRaceID;
	}

	void	Set_RaceID(int32 nRaceID);

	/*
	 ===================================================================================================================
	    头像
	 ===================================================================================================================
	 */
	int32 Get_PortraitID(void) const
	{
		return m_pData->m_nPortraitID;
	}

	void	Set_PortraitID(int32 nPortraitID);

	/*
	 ===================================================================================================================
	    名称
	 ===================================================================================================================
	 */
	LPCTSTR Get_Name(void) const
	{
		return m_pData->m_strName.c_str();
	}

	const String& Get_NameStr(void) const
	{
		return m_pData->m_strName;
	}

	/*
	 ===================================================================================================================
	 ===================================================================================================================
	 */
	LPCTSTR Get_Utf8Name(void) const
	{
		return m_pData->m_strUtf8Name.c_str();
	}

	void	Set_Name(LPCTSTR szName);

	/* 称号(国家\帮会\玩法) */
	LPCTSTR Get_CurTitle(int32 nType) const;
	void	Set_CurTitle(LPCTSTR szTitle, int32 nType);

	/*
	 ===================================================================================================================
	    称号类型
	 ===================================================================================================================
	 */
	BYTE Get_CurTitleType(void) const
	{
		return m_pData->m_TitleType;
	}

	void	Set_CurTitleType(BYTE bTitleType);

	/*
	 ===================================================================================================================
	    生命值百分比
	 ===================================================================================================================
	 */
	FLOAT Get_HPPercent(void) const
	{
		return m_pData->m_fHPPercent;
	}

	void	Set_HPPercent(FLOAT fPercent);

	/* 通过生命值是否死亡 */
	BOOL	IsDie(void) const;

	/*
	 ===================================================================================================================
	    魔法百分比
	 ===================================================================================================================
	 */
	FLOAT Get_MPPercent(void) const
	{
		return m_pData->m_fMPPercent;
	}

	void	Set_MPPercent(FLOAT fPercent);

	/*
	 ===================================================================================================================
	    移动速度
	 ===================================================================================================================
	 */
	FLOAT Get_MoveSpeed(void) const
	{
		return m_pData->m_fMoveSpeed;
	}

	void	Set_MoveSpeed(FLOAT fSpeed);

	/*
	 ===================================================================================================================
	 ===================================================================================================================
	 */

	int32	Get_MoveLogicMode(void) const { return m_pData->m_nMoveLogicMode; }
	void	Set_MoveLogicMode(int32 nMoveMode);

	int32	Get_MoveActionMode(void) const { return m_pData->m_nMoveActionMode; }
	void	Set_MoveActionMode(int32 nMoveMode);

	

	/*
	 ===================================================================================================================
	    所有者
	 ===================================================================================================================
	 */
	ObjID_t Get_OwnerID(void) const
	{
		return m_pData->m_nOwnerID;
	}

	void	Set_OwnerID(ObjID_t nOwnerID);

	

	void	Set_OwnerGUID(GUID_t nOwnerGUID);

	/*
	 ===================================================================================================================
	 ===================================================================================================================
	 */
	int32 Get_AIType(void) const
	{
		return m_pData->m_nAIType;
	}

	void	Set_AIType(int32 nAIType);


	/*
	 ===================================================================================================================
	 ===================================================================================================================
	 */
	int32 Get_Relative(void) const
	{
		return m_pData->m_nRelative;
	}

	void	Set_Relative(int32 nRelative);

	/*
	 ===================================================================================================================
	    数据内部保存的模型id， 变身用
	 ===================================================================================================================
	 */
	int32 Get_ModelID(void) const
	{
		return m_pData->m_nModelID;
	}

	void	Set_ModelID(int32 nModelID);

	/*
	 ===================================================================================================================
	    坐骑ID
	 ===================================================================================================================
	 */
	int32 Get_MountID(void) const
	{
		return m_pData->m_nMountID;
	}

	void	Set_MountID(int32 nMountID);

	/*
	 ===================================================================================================================
	    等级
	 ===================================================================================================================
	 */
	int32 Get_Level(void) const
	{
		return m_pData->m_nLevel;
	}

	void	Set_Level(int32 nLevel);

	/*
	 ===================================================================================================================
	    隐身级别
	 ===================================================================================================================
	 */
	int32 Get_StealthLevel(void) const
	{
		return m_pData->m_nStealthLevel;
	}

	void	Set_StealthLevel(int32 nStealthLevel);

	/*
	 ===================================================================================================================
	    是否坐下
	 ===================================================================================================================
	 */
	BOOL IsSit(void) const
	{
		return m_pData->m_bSit;
	}

	void		Set_Sit(BOOL bSit);

	/* [ ZG 2008-6-10 ] */
	void		Set_PerGuildCon(int32 nPerCon);
	int32			Get_PerGuildCon();

	/* [ ZG 2008-6-23 ] */
	void		Set_Honor(int32 nHonor);
	int32			Get_Honor();

	void		Set_RongYu(int32 chaotingShengWang);
	int32			Get_RongYu();

	void		Set_ShengWang(int32 jiangHuShengWang);
	int32			Get_ShengWang();

	void		Set_WenCai(int32 WenCai);
	int32			Get_WenCai();

	/* [ ZG 2008-6-30 ] */
	void		Set_PreTimeAt(uint32 nAt);
	uint32		Get_PreTimeAt();

	void		Set_VoteTime(uint32 nTime);
	uint32		Get_VoteTime();

	void		Set_KingName(const char *pStr);
	const char	*Get_KingName();

	void		Set_CurVotes(uint32 nVotes);
	uint32		Get_CurVotes();
	void		Set_VoteCel(int32 nCel);

	/*
	 ===================================================================================================================
	    目标id
	 ===================================================================================================================
	 */
	int32 Get_TargetId(void)
	{
		return m_pData->m_nTargetId;
	};
	void						Set_TargetId(int32 id);

	/*
	 * END ;
	 * by soongxl
	 */
	void						Set_PKValue(int32 value);
	int32							Get_PKValue();

	void						Set_AttachMemberID(int32 nIndex, int32 nObjID);
	int32							Get_AttachMemberID(int32 nIndex);

	void						Set_AttachID(int32 nID);
	int32							Get_AttachID();

	void						Set_VisibleState(BOOL bVisible);
	BOOL						Get_VisibleState();

	void						Set_Dir(FLOAT fDir);
	FLOAT						Get_Dir();

	void						Set_ControlState(int32 nState);
	int32							Get_ControlState();

	/*
	 * Character_PlayerOther 对于其他玩家 ;
	 * 职业
	 */
	int32							GetProfession(void) const;
	void						SetProfession(int32 nProfession);

	/* 帮会 */
	int32							Get_Guild(void) const;
	void						Set_Guild(int32 nGuild, BOOL bMySelf);
	const char					*Get_GuildName() const;
	void						Set_GuildName(const char *pName);

	/* 帮会职位 */
	int32							Get_GuildPosition(void) const;
	void						Set_GuildPosition(int32 nGuildPosition);

	/* 帮会家族 */
	int32							Get_Family(void) const;
	void						Set_Family(int32 nFamily, BOOL bMySelf = FALSE);
	const char					*Get_FamilyName() const;
	void						Set_FamilyName(const char *pName);

	/* ! 获得该玩家配偶名字 add by QL */
	const char					*Get_ConsortName() const;

	/* ! 设置该玩家配偶名字 add by QL */
	void						Set_ConsortName(const char *pName);

	/* 队伍ID */
	int32							Get_TeamID(void) const;
	void						Set_TeamID(int32 nTeamID);

	/* 头发模型 */
	int32							Get_HairMesh(void) const;
	void						Set_HairMesh(int32 nHairMesh);

	/* 头发颜色 */
	uint32						Get_HairColor(void) const;
	void						Set_HairColor(uint32 uHairColor);

	/* 脸模型 */
	int32							Get_FaceMesh(void) const;
	void						Set_FaceMesh(int32 nFaceMesh);

	/* 装备状态版本号，用于和服务器同步数据 */
	int32							Get_EquipVer(void) const;
	void						Set_EquipVer(int32 nEquipVer);

	/* 装备 */
	int32							Get_Equip(PLAYER_EQUIP point) const;
	void						Set_Equip(PLAYER_EQUIP point, int32 nID, BOOL bUpdateShow = FALSE);
	void						Set_Fashion();

	/* 装备宝石 */
	int32							Get_EquipGem(PLAYER_EQUIP point) const;
	void						Set_EquipGem(PLAYER_EQUIP point, int32 nID, BOOL bUpdateShow = FALSE);

	/* 套装 */
	_SUIT_SETTING				&Get_EquipSuit(int32 suitIdx) const;
	void						Set_EquipSuit(int32 suitIdx, _SUIT_SETTING &pSuit);

	/* 套装id */
	int32							Get_EquipSuitId() const;
	void						Set_EquipSuitId(int32 suitIdx);

	/* 符文 */
	int32							Get_EquipSignId() const;
	void						Set_EquipSignId(int32 signId, BOOL bUpdate = FALSE);

	/* 星星 */
	int32							Get_EquipStarId() const;
	void						Set_EquipStarId(int32 signId, BOOL bUpdate = FALSE);

	/* 套装特效 */
	int32							Get_EquipSuitEffect() const;
	void						Set_EquipSuitEffect(int32 signId, BOOL bUpdate = FALSE);

	/* 时装外形表示 */
	int32							Get_LeftWeaponVisual() const;
	void						Set_LeftWeaponVisual(int32 nVisual);

	int32							Get_RightWeaponVisual() const;
	void						Set_RightWeaponVisual(int32 nVisual);

	int32							Get_ShouderVisual() const;
	void						Set_ShouderVisual(int32 nVisual);

	int32							Get_HeadVisual() const;
	void						Set_HeadVisual(int32 nVisual);

	/* 怪的武器 */
	int32							Get_MonstWeapon(void) const;
	void						Set_MonstWeapon(int32 nID);

	/* 是否组队标记 */
	BOOL						Get_HaveTeamFlag(void) const;
	void						Set_HaveTeamFlag(BOOL flag);

	/* 是否队长标记 */
	BOOL						Get_TeamLeaderFlag(void) const;
	void						Set_TeamLeaderFlag(BOOL flag);

	/* 是否满队标记 */
	BOOL						Get_TeamFullFlag(void) const;
	void						Set_TeamFullFlag(BOOL flag);

	/* 是否组队跟随状态 */
	BOOL						Get_TeamFollowFlag(void) const;
	void						Set_TeamFollowFlag(BOOL flag);

	/* 跟随列表里的人数 */
	int32							Get_TeamFollowListCount(void) const;
	void						Set_TeamFollowListCount(int32 count);

	/* 跟随列表里的成员 */
	GUID_t						Get_TeamFollowedMember(int32 index) const;
	void						Set_TeamFollowedMember(int32 index, GUID_t guid);


	/* 当前称号索引 */
	int32							Get_CurTitleIndex() const;
	void						Set_CurTitleIndex(int32 index);

	/* 清空称号 */
	void						Clear_AllTitles();

	/* 时装 */
	BOOL						Get_FashionIsShow() const;
	void						Set_FashionShow(BOOL bShow, BOOL bUIUpdate=TRUE);

	/* 得到名字特殊时候的颜色 */
	BYTE						GetNameColor() const;
	void						SetNameColor(BYTE color);

	/* 坐骑力量资质 */
	int32							Get_MountStrApt();
	void						Set_MountStrApt(int32 val);

	/* 坐骑敏捷资质 */
	int32							Get_MountDexApt();
	void						Set_MountDexApt(int32 val);

	/* 坐骑智力资质 */
	int32							Get_MountIntApt();
	void						Set_MountIntApt(int32 val);

	/* 坐骑体质资质 */
	int32							Get_MountConApt();
	void						Set_MountConApt(int32 val);

	/* 坐骑代数 */
	int32							Get_MountEra();
	void						Set_MountEra(int32 val);

	int32							Get_KillCount();
	void						Set_KillCount(int32 val);

	BOOL						Get_BusState();
	void						Set_BusState(BOOL bEnable);

	/* Character_PlayerMySelf 对于玩家自己 */
	int32							Get_HP(void) const;
	void						Set_HP(int32 nHP);

	int32							Get_MP(void) const;
	void						Set_MP(int32 nMP);

	int64_t						Get_Exp(void) const;
	void						Set_Exp(int64_t nExp);

	int64_t							Get_MaxExp(void) const;
	int64_t							Get_MaxExp(int32 nLevel) const;

	/*
	 * void Set_MaxExp(int32 nMaxExp);
	 * //通过查表获得 ;
	 * int32 Get_Money(void) const;
	 * ;
	 * void Set_Money(int32 nMoney);
	 */
	int64_t						Get_Money(int32 T = CU_SILLER) const;
	void						Set_Money(int64_t nMoney, int32 T = CU_SILLER);

	int64_t							Get_SliverMoney() const;
	int64_t							Get_GoldMoney() const;

	void						Set_Silver_Model(SILLER_MODE m);
	void						Set_Gold_Model(GOLD_MODE m);

	SILLER_MODE					Get_Silver_Model();
	GOLD_MODE					Get_Gold_Model();

	const SHorseGuid&Get_CurrentPetGUID(void) const;
	void						Set_CurrentPetGUID(SHorseGuid guid);

	int32							Get_Rage(void) const;
	void						Set_Rage(int32 nRage);

	int32							Get_MaxRage(void) const;
	void						Set_MaxRage(int32 nMaxRage);

	int32							Get_RageRespeed(void) const;
	void						Set_RageRespeed(int32 nRageRespeed);

	int32							Get_StrikePoint(void) const;
	void						Set_StrikePoint(int32 nStrikePoint);

	/* 活力值 */
	int32							Get_Vigor(void) const;
	void						Set_Vigor(int32 nVigor);

	int32							Get_MaxVigor(void) const;
	void						Set_MaxVigor(int32 nVigor);

	int32							Get_RegeneRate(void) const;
	void						Set_RegeneRate(int32 regeneRate);

	int32							Get_Energy(void) const;
	void						Set_Energy(int32 nEnergy);

	int32							Get_MaxEnergy(void) const;
	void						Set_MaxEnergy(int32 nEnergy);

	int32							Get_GoodBadValue(void) const;
	void						Set_GoodBadValue(int32 nValue);
	int32							Get_STR(void) const;
	void						Set_STR(int32 nSTR);

	int32							Get_CON(void) const;
	void						Set_CON(int32 nCON);

	int32							Get_INT(void) const;
	void						Set_INT(int32 nINT);

	int32							Get_DEX(void) const;
	void						Set_DEX(int32 nDEX);

	int32							Get_PointRemain(void) const;
	void						Set_PointRemain(int32 nPoint);

	int32							Get_AttMagic(void) const;
	void						Set_AttMagic(int32 nAttMagic);
	int32							Get_AttNear(void) const;
	void						Set_AttNear(int32 nAtt);
	int32							Get_DefNear(void) const;
	void						Set_DefNear(int32 nDef);

	int32							Get_AttFar(void) const;
	void						Set_AttFar(int32 nAtt);
	int32							Get_DefFar(void) const;
	void						Set_DefFar(int32 nDef);

	int32							Get_DefMagic(void) const;
	void						Set_DefMagic(int32 nDefMagic);
	int32							Get_MaxHP(void) const;
	void						Set_MaxHP(int32 nMaxHP);

	int32							Get_MaxMP(void) const;
	void						Set_MaxMP(int32 nMaxMP);

	int32							Get_HPRespeed(void) const;
	void						Set_HPRespeed(int32 nHPRespeed);

	int32							Get_MPRespeed(void) const;
	void						Set_MPRespeed(int32 nMPRespeed);

	int32							Get_Toughness(void) const;
	void						Set_Toughness(int32 nToughness);

	int32							Get_Hit(void) const;
	void						Set_Hit(int32 nHit);

	int32							Get_Miss(void) const;
	void						Set_Miss(int32 nMiss);

	int32							Get_CritRate(void) const;
	void						Set_CritRate(int32 nCritRate);

	int32							Get_CritHurt(void) const;
	void						Set_CritHurt(int32 nCritHurt);

	int32							Get_AttackSpeed(void) const;
	void						Set_AttackSpeed(int32 fSpeed);

	int32							Get_AttCold(void) const;
	void						Set_AttCold(int32 nAttCold);

	int32							Get_DefCold(void) const;
	void						Set_DefCold(int32 nDefCold);

	int32							Get_AttFire(void) const;
	void						Set_AttFire(int32 nAttFire);

	int32							Get_DefFire(void) const;
	void						Set_DefFire(int32 nDefFire);

	int32							Get_AttLight(void) const;
	void						Set_AttLight(int32 nAttLight);

	int32							Get_DefLight(void) const;
	void						Set_DefLight(int32 nDefLight);

	int32							Get_AttPosion(void) const;
	void						Set_AttPosion(int32 nAttPosion);

	int32							Get_DefPosion(void) const;
	void						Set_DefPosion(int32 nDefPosion);

	BOOL						IsLimitMove(void) const;
	void						SetLimitMove(BOOL bSet);

	void						SetLimitMove2(BOOL bSet);

	int32							Get_NearReduce(void) const;
	void						Set_NearReduce(int32 nNearReduce);

	int32							Get_FarReduce(void) const;
	void						Set_FarReduce(int32 nFarReduce);

	int32							Get_MagicReduce(void) const;
	void						Set_MagicReduce(int32 nMagicReduce);

	int32							Get_DreadResist(void) const;
	void						Set_DreadResist(int32 nDreadResist);

	int32							Get_ComaResist(void) const;
	void						Set_ComaResist(int32 nComaResist);

	int32							Get_HushResist(void) const;
	void						Set_HushResist(int32 nHushResist);

	int32							Get_UnarmResist(void) const;
	void						Set_UnarmResist(int32 nUnarmResist);

	int32							Get_AttackSpeedResist(void) const;
	void						Set_AttackSpeedResist(int32 nAttackSpeedResist);

	int32							Get_SkillSpeedResist(void) const;
	void						Set_SkillSpeedResist(int32 nSkillSpeedResist);

	int32							Get_MoveReduceResist(void) const;
	void						Set_MoveReduceResist(int32 nMoveReduceResist);

	/* 魅力 */
	int32							Get_Hot(void) const;
	void						Set_Hot(int32 nHot);

	/*
	 * BOOL IsLimitUseSkill(void) const;
	 * void SetLimitUseSkill(BOOL bSet);
	 * ;
	 * BOOL IsLimitHandle(void) const;
	 * void SetLimitHandle(BOOL bSet);
	 */
	BOOL						IsHaveCanActionFlag1(void) const;
	void						SetCanActionFlag1(BOOL bSet);

	BOOL						IsHaveCanActionFlag2(void) const;
	void						SetCanActionFlag2(BOOL bSet);

	/* 设置二级保护密码 */
	BOOL						Get_IsMinorPwdSetup(BOOL bOpenDlg = TRUE) const;
	void						Set_SetMinorPwdSetup(BOOL bSet);

	/* 是否验证过二级保护密码 */
	BOOL						Get_IsMinorPwdUnlocked(BOOL bOpenDlg = TRUE) const;
	void						Set_SetMinorPwdUnlocked(BOOL bSet);

	BOOL						Get_IsMaxErrorCount(BOOL bOpenDlg = TRUE) const;
	void						Set_SetMaxErrorCount(BOOL bSet);


	/*
	 * void Update_SkillByTalentID( int32 nTalentID );
	 */
	int32						Get_SeriesPoint(int32 nSeriesID);						/* 获取 某系别的总共花费的点数 */
	void						Set_SeriesPoint(int32 nSeriesID, int32 nSeriesPoint);	/* 设置 ...................... */

	int32						Get_CurrentSkillPoint();			/* 获得 拥有的技能点数 */
	void						Set_CurrentSkillPoint(int32 nPoint);	/* 设置 .............. */

	void						Set_SkillLevel(int32 nSkillID, int32 nSkillLevel);

	
	void						Set_Prescr(int32 nID, BOOL bLean);

	/* 摆摊状态 */
	BOOL						Get_IsInStall(void) const;
	void						Set_IsInStall(BOOL bIsInStall);

	LPCTSTR						Get_StallName(void) const;
	void						Set_StallName(LPCTSTR szName);

	void						Set_StallMoneyType(uchar nType);
	uchar						Get_StallMoneyType() const;

	FLOAT						Get_SpeedRate(void) const;

	String						Get_Province();
	String						Get_Zone();

	void						Set_Province(String province);
	void						Set_Zone(String Zone);

	void						Set_TiredTime(uint32 value);
	uint32						Get_TiredTime();

	/* 天赋 */
	void						Set_InherenceExp(uint32 value);
	uint32						Get_InherenceExp(void);

	void						Set_InherenceNextLevelExp(uint32 value);
	uint32						Get_InherenceNextLevelExp(void);

	void						Set_InherenceLevel(uint32 value);
	uint32						Get_InherenceLevel(void);

	void						Set_BattleHonour(uint32 nHonour);
	uint32						Get_BattleHonour();

	void						Set_PVP2V2Level(USHORT nLevel);
	USHORT						Get_PVP2V2Level();

	void						Set_PVP2V2Mark(USHORT nMark);
	USHORT						Get_PVP2V2Mark();

    void						Set_FeastScore(uint32 dwScore);
    uint32						Get_FeastScore();

	void						Set_PVP2V2Mark_WeekTotal(int32 nMarkTotal);
	int32						Get_PVP2V2Mark_WeekTotal();

	void						Set_BankPetValidCt(BYTE val);
	BYTE						Get_BankPetValidCt();

	void						SetHideName(BOOL isHide);
	BOOL						IsHideName() const;

	void						SetMerit(int32 nMerit);
	int32						GetMerit();

	void						Set_CharScale(FLOAT fValue);
	FLOAT						Get_CharScale();

	void						Set_DefaultSkill(int32 nId);
	int32						Get_GetDefaultSkill();

	void						Set_AttrGift(int32 nGiftId, int32 nlevel);


	void						Set_BalanceGift(int32 nGift, int32 nLevel);


	void						Set_SpecialBalanceGift(int32 nGift, int32 nLevel);


    void                        Set_InhDefend( int32 iIndex, uint16 usValue);
    const uint16*               Get_InhDefend();

    void                        Set_DefendRemainPoints( uint32 uiPoints);
    uint32                      Get_DefendRemainPoints();
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	KCharatcterBaseData(Character *pCharObj);
	virtual ~KCharatcterBaseData();

	void	ResetData();

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	/* 初始化操作 */
	void	_Init_AsCharacter(void);
	void	_Init_AsNPC(void);
	void	_Init_AsPlayerOther(void);
	void	_Init_AsPlayerMySelf(void);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	/* 判断该级升级经验 */
	void	CheckLevelUpExp(int64_t nExp, int32 nLevel);

public:

	/* */
	int32			m_nType;

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:

	/* 角色逻辑指针 */
	Character*m_pObjRef;

	/* 角色数据结构 */
	SDataCharacter *m_pData;
};	/* class */

/* 得到 国家名字 */
String	getCountryName(int32 nCountry);

/* 得到 职业名字 */
String	getProfessionName(int32 nProfession);
#endif /* __CHARACTERDATA_H__ */
