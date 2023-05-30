/*$T MapServer/Server/DB/PlayerDB.h GC 1.140 10/10/07 10:07:21 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef __HUMANDB_H__
#define __HUMANDB_H__

#include "TypeDefine.h"
#include "StructDB.h"
#include "BaseTool.h"
#include "TabDefine.h"

#define GetPlayerArchiveStr(db)	(db)->GetArchiveAttrLvl1(CPROPERTY_LEVEL1_STR)
#define GetPlayerArchiveCon(db)	(db)->GetArchiveAttrLvl1(CPROPERTY_LEVEL1_CON)
#define GetPlayerArchiveInt(db)	(db)->GetArchiveAttrLvl1(CPROPERTY_LEVEL1_INT)
#define GetPlayerArchiveDex(db)	(db)->GetArchiveAttrLvl1(CPROPERTY_LEVEL1_DEX)
#define SetPlayerArchiveStr(db, v) (db)->SetArchiveAttrLvl1(CPROPERTY_LEVEL1_STR, v)
#define SetPlayerArchiveCon(db, v) (db)->SetArchiveAttrLvl1(CPROPERTY_LEVEL1_CON, v)
#define SetPlayerArchiveInt(db, v) (db)->SetArchiveAttrLvl1(CPROPERTY_LEVEL1_INT, v)
#define SetPlayerArchiveDex(db, v) (db)->SetArchiveAttrLvl1(CPROPERTY_LEVEL1_DEX, v)

class	PlayerArchive
{
#define N_SM_LOCK(type) \
	if(m_PlayerSHM) \
	{ \
		SHM_LOCK(&m_PlayerSHM->m_MKHead.flag, type) \
	};
#define N_SM_UNLOCK(type) \
	if(m_PlayerSHM) \
	{ \
		SHM_UNLOCK(&m_PlayerSHM->m_MKHead.flag, type) \
	};

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	PlayerArchive();
	~				PlayerArchive();

	void				Clear();
	void				RefreshArchiveToDBShare(BOOL bForceAll, BOOL &bUpdateAttr);
	BOOL				IsNoDirectAttr(PLAYER_PROPERTY_ARCHIVE attrType);
	void				ValidatePlayerID(ConnectorID_t PID);
	inline void			Lock();
	inline void			UnLock();

	inline GUID_t			GetGUID() const;
	inline BOOL			IsFirstEnterGame();
	inline void			ClearFirstEnterGame();
	inline void			SetGUID(GUID_t guid);
	inline int32			GetPortraitID() const;
	inline void			SetPortraitID(int32 nID);
	inline const char		*GetName() const;
	inline uchar			GetSex();
	inline int32			GetHP();
	inline void			SetHP(int32 hp);
	inline int32			GetMP();
	inline void			SetMP(int32 mp);
	inline int32			Get_Property_StrikePoint(void);
	inline void			Set_Property_StrikePoint(int32 nStrikePoint);
	inline int32			Get_Property_Vigor(void);
	inline void			Set_Property_Vigor(int32 nVigor);
	inline int32			Get_Property_MaxVigor(void);
	inline void			Set_Property_MaxVigor(int32 nMaxVigor);
	inline int32			Get_Property_VigorRegeneRate(void);
	inline void			Set_Property_VigorRegeneRate(int32 nRate);
	inline int32			Get_Property_Energy(void);
	inline void			Set_Property_Energy(int32 nEnergy);
	inline int32			Get_Property_MaxEnergy(void);
	inline void			Set_Property_MaxEnergy(int32 nMaxEnergy);
	inline int32			Get_Property_EnergyRegeneRate(void);
	inline void			Set_Property_EnergyRegeneRate(int32 nRate);
	inline int32			Get_Property_Rage(void);
	inline void			Set_Property_Rage(int32 nRage);
	inline uchar			GetLevel();
	inline void			SetLevel(uchar level);
	inline int32			GetPKValue(void) const;
	inline void			SetPKValue(int32 nValue);
	inline int32			GetLastChgPKModeTime(void) const;
	inline void			SetLastChgPKModeTime(int32 nValue);
	inline SHorseGuid		GetCurrentPetGUID(void) const;
	inline void			SetCurrentPetGUID(SHorseGuid guid);
	inline uint64			GetExp();
	inline void			SetExp(uint64 exp);

	inline int32			GetCountry();
	inline void			SetCountry(int32 nCountry);
	inline int32			GetProfession();
	inline void			SetProfession(int32 Profession);
	inline int32			GetSiller();
	inline void			SetSiller(int32 siller);
	inline int32			GetCharGold();
	inline void			SetCharGold(int32 gold);
	inline int32			GetBindSiller();
	inline void			SetBindSiller(int32 bindsiller);
	inline int32			GetBindGold();
	inline void			SetBindGold(int32 bindgold);
	inline uchar			GetSillerMode();
	inline void			SetSillerMode(uchar sillermode);
	inline uchar			GetGoldMode();
	inline void			SetGoldMode(uchar goldMode);

	inline uint16			GetWenCai();
	inline void			SetWenCai(uint16 nWenCai);

	inline int32			GetRongYu();
	inline void			SetRongYu(int32 nRongYu);

	inline int32			GetShengWang();
	inline void			SetShengWang(int32 nShengWang);

	inline int32			GetHotValue();
	inline void			SetHotValue(int32 nHotValue);

	inline int32			Get_Property_GoodBadValue();
	inline int32			Set_Property_GoodBadValue(int32 nValue);
	inline BOOL			IsChangeScence();
	inline const char		*GetPasswd();
	inline void			SetPasswd(const char *szPasswd);
	inline const uchar		GetPwdType();
	inline void			SetPwdType(uchar pwdType);
	inline void			DelPasswd();
	inline uint32			GetPasswdDeleteTime();
	inline void			SetPasswdDeleteTime(uint32 uTime);
	inline uchar			GetLastProtectTime();
	inline void			SetLastProtectTime(uchar uTime);
	inline uchar			GetProtectTime();
	inline void			SetProtectTime(uchar uTime);
	inline uint32			GetProtectDeleteTime();
	inline void			SetProtectDeleteTime(uint32 uTime);
	inline uint32			Get_Property_HairColor(void) const;
	inline void			SetHairColor(uint32 uColor);
	inline uchar			GetFaceColor(void) const;
	inline void			SetFaceColor(uchar byColor);
	inline uchar			Get_Property_HairModel(void) const;
	inline void			SetHairModel(uchar byModel);
	inline uchar			Get_Property_FaceModel(void) const;
	inline void			SetFaceModel(uchar byModel);

	inline void			SetSoulID(int32 nSoulID);
	inline int32			GetSoulID();
	inline void			SetGemAff(uint32 nGemAff);
	inline uint32			GetGemAff();
	inline void			SetSetSuit(uint32 nSetSuit);
	inline uint32			GetSetSuit();
	inline uint32			GetLevelAff();
	inline void			SetLevelAff(uint32 nLevelAff);

	inline uint32			GetEquipID(PLAYER_EQUIP equipPoint);
	inline uint32			GetEquipLevel(PLAYER_EQUIP equipPoint);
	inline int32			GetArchiveAttrLvl1(PLAYER_PROPERTY_LEVEL1 enAttrType);
	inline void			SetArchiveAttrLvl1(PLAYER_PROPERTY_LEVEL1 enAttrType, int32 iValue);

	inline int32			GetNeiShang();

	inline const SCampData		*GetDBCampData(void) const;
	inline void			SetDBCampData(const SCampData *pCampData);
	inline MapID_t			GetDBStartScene();
	inline void			SetDBStartScene(MapID_t sceneID);
	inline MapID_t			GetDBBakScene();
	inline void			SetDBBakScene(MapID_t sceneID);
	inline void			SetDBNextScene(MapID_t sceneID);
	inline MapID_t			GetDBNextScene();
	inline void			SetDBPosition(const GLPos &pos);
	inline const GLPos		*GetDBPosition();
	inline void			SetDBBakPosition(const GLPos &pos);
	inline const GLPos		*GetDBBakPosition();
	inline void			SetDBNextPosition(const GLPos &pos);
	inline const GLPos		*GetDBNextPosition();
	inline void			WriteDBPosition(GLPos &pos);

	inline void			SetOnlineTime(uint32 uTime);
	inline uint32			GetOnlineTime();
	inline void			SetLoginTime(uint32 uTime);
	inline uint32			GetLoginTime();
	inline void			SetLogoutTime(uint32 uTime);
	inline uint32			GetLogoutTime();
	inline void			SetLeaveGuildTime(uint32 uTime);
	inline uint32			GetLeaveGuildTime() const;
	inline void			SetLoginIP(IP_t lastLoginIP);
	inline IP_t			GetLoginIP();
	inline void			SetDBVersion(uint32 Ver);
	inline uint32			GetDBVersion();

	inline int32			GetWallowOnlineTime();
	inline void			SetWallowOnlineTime(int32 nTime);
	inline int32			GetWallowOfflineTime();
	inline void			SetWallowOfflineTime(int32 nTime);
	inline int32			GetTotalOnlineTime();
	inline void			SetTotalOnlineTime(int32 nTime);
	inline uint32			GetTiredTime();
	inline void			SetTiredTime(uint32 uTime);

	inline void			SetDBGuid(GUID_t guid);
	inline GuildID_t		GetDBGuildID();
	inline void			SetDBGuildID(GuildID_t guildID);
	inline int32			GetDBFamilyID();
	inline void			SetDBFamilyID(int32 nFamilyID);
	inline int32			GetDBGuildOfficial();
	inline void			SetDBGuildOfficial(int32 nOfficial);
	inline int32			GetDBGuildPoint();
	inline void			SetDBGuildPoint(int32 nGP);
	inline int32		GetDBGuildMerit();
	inline void			SetDBGuildMerit(int32 nMerit);		
	inline int32			GetDBHonor();
	inline void			SetDBHonor(int32 nHonor);
	inline void			SetKillCountToday(uint16 nKillCount);
	inline uint16			GetKillCountToday();
	inline void			SetBattleHonour(uint32 nHonour);
	inline uint32			GetBattleHonour();
	inline void			SetPVP2V2Level(uint16 nLevel);
	inline uint16			GetPVP2V2Level();
	inline void			SetPVP2V2Mark(uint16 nMark);
	inline uint16			GetPVP2V2Mark();
	inline void			SetPVP2V2Day(int32 nDay);
	inline int32			GetPVP2V2Day();
	inline int32			GetPVP2v2Mark_WeekTotal();
	inline void			SetPVP2v2Mark_WeekTotal(int32 nTotal);
	inline uint32			GetDBInherenceExp();
	inline void			SetDBInherenceExp(uint32 nInherenceExp);
	inline uint16			GetDBInherenceLevel();
	inline void			SetDBInherenceLevel(uint16 nLevel);
	inline int32			GetDuelMark();
	inline void			SetDuelMark(int32 nMark);

	inline TeamID_t			GetDBTeamID();
	inline void			SetDBTeamID(TeamID_t teamID);

	inline BusID_t			GetDBBusID();
	inline void			SetDBBusID(BusID_t BusID);

	inline BOOL			GetDelCharFlag();
	inline void			SetDelCharFlag(BOOL flag);

	inline int32			GetLastForbidChatTime() const;
	inline void			SetLastForbidChatTime(int32 iTime);

	inline int32			GetLastEnjailTime() const;
	inline void			SetLastEnjailTime(int32 iTime);

	inline BOOL			GetKing() const;
	inline void			SetKing(BOOL bValue);
	inline int32			GetCountryOfficial();
	inline void			SetCountryOfficial(int32 pos);
	inline BOOL			IsNeedRename() const;
	inline void			SetNewName(const char *pName);

	inline const STitle		*GetTitleInfo() const;
	inline void			SetCurCountryTitle(int32 iTitleID);
	inline void			SetCurGuildTitle(int32 iTitleID);
	inline void			SetCurNormalTitle(int32 iTitleID);
	inline int32			SetCurCountryTitle
					(
						int32	iTitleID,
						int32	&BuffID1,
						int32	&BuffID2,
						uchar	&ComId
					);
	inline int32			SetCurGuildTitle(int32 iTitleID, int32 &BuffID1, int32 &BuffID2, uchar &ComId);
	inline int32			SetCurNormalTitle
					(
						int32	iTitleID,
						int32	&BuffID1,
						int32	&BuffID2,
						uchar	&ComId,
						int32	nCommand
					);
	inline uchar			GetCurCountryTitle();
	inline uchar			GetCurGuildTitle();
	inline uchar			GetCurNormalTitle();

	inline void			AddTitle(int32 iTitleID, int32 &BuffID1, int32 &BuffID2, uchar &ComId);
	inline int32			RemoveTitle(int32 iTitleID, uchar &comId, int32 &buffId1, int32 &buffId2);
	inline int32			IsHaveTitle(int32 iTitleID);

	inline void			SetGuildTitleName(const char *pszTitle, int32 iSize);
	inline const char		*GetGuildTitleName() const;
	inline void			SetCountryTitleName(const char *pszTitle, int32 iSize);
	inline const char		*GetCountryTitleName() const;
	inline void			SetNormalTitleName(const char *pszTitle, int32 iSize);
	inline const char		*GetNormalTitleName() const;
	inline void			SetOfficalTitleName(const char *pszTitle, int32 iSize);
	inline const char		*GetOfficalTitleName() const;

	inline const char		*GetTitleNameByID(int32 iTitleID, int32 iSex);
	inline BOOL			UpdateTitleTime(uchar &titleId, uchar &comId, int32 &buffId1, int32 &buffId2);

	inline const int32		GetBankItemCount() const;
	inline const SItem		*GetBankItem(const int32 bankindex) const;
	inline const int32		GetBankEndIndex() const;
	inline void			SetBankEndIndex(const int32 bankindex);
	inline const int32		GetBankMoney() const;
	inline void			SetBankMoney(const int32 money);
	inline const int32		GetBankSize() const;
	inline void			ExpandBankSize(uint32 uBanksize);

	void				SetFreeOwnFlag(int32 Flag);
	int32				GetFreeOwnFlag();

	inline const SItem		*GetBagItem(uint32 iBagIndex) const;
	inline const SItem		*GetEquipItem(PLAYER_EQUIP equipPoint);
	inline void			RandSet();
	inline uint32			GetBaseBagSize();
	inline uint32			GetExtraContainerSize();
	inline uint32			GetExtraBagSize(uint32 nIndex);

	inline uint32			GetTaskBagSize();
	inline uint32			GetMatBagSize();

	inline void			SetCooldown(CooldownID_t nID, Time_t nTime);
	inline BOOL			IsCooldowned(CooldownID_t nID) const;
	inline void			HeartBeat_Cooldown(Time_t nDeltaTime);
	inline Time_t			GetCooldownRemain(CooldownID_t nID) const;
	inline void			ClearCooldown();

	inline uchar			GetSkillCount();
	inline void			SetSkillCount(uchar Count);
	inline _PLAYER_SPELL		&GetSkillID(uchar Index);
	inline void			SetSkillID(const _PLAYER_SPELL &oSkill, uchar Index);
	inline void			SetSkillLevel(const int32 nID, uchar Index, const int32 nLevel);
	inline int32			GetRemainPoints();
	inline int32			GetRemainSkillPoints();
	inline int32			Get_S_SkillPoints(int32 nS);
	inline void			SetDBRemainPoints(int32 Point);
	inline void			SetDBRemainSkillPoints(int32 Point);
	inline void			SetDB_S_SkillPoints(int32 nS, int32 Point);
	inline void			SetMonsterPetAttr(int32 iIndex, _Monster_Pet_DB_Struct *pMonsterPet);

	inline void			SetQuestDone(QuestID_t idQuest, QuestID_t idIndex);
	inline void			SetQuestUnDone(QuestID_t idQuest, QuestID_t idIndex);
	inline void			SetQuestParam(uint32 uIndexQuest, uint32 uIndexParam, int32 nValue);
	inline void			SetQuestParam_Unsigned(uint32 uIndexQuest, uint32 uIndexParam, uint32 nValue);
	inline void			SetQuestData(int32 nIndex, int32 nData);
	inline void			SetQuest(uint32 uIndex, QuestID_t idQuest, ScriptID_t idScript);
	inline void			SetQuestCount(uint32 uCount);
	inline void			SetFlags_KillObject(uint32 uIndex, BOOL bSet);
	inline void			SetFlags_EnterArea(uint32 uIndex, BOOL bSet);
	inline void			SetFlags_ItemChanged(uint32 uIndex, BOOL bSet);
	inline void			SetFlags_PetChanged(uint32 uIndex, BOOL bSet);
	inline void			SetFlags_ClickNPC(uint32 uIndex, BOOL bSet);
	inline void			ClearQuest(uint32 uIndex);

	inline void				ChangeTitleForPrenticeCount(uint16 uTitleID);
	inline int32			GetTitleForPrenticeCount();
	inline int32			GetCurPrenticeCount();
	inline BOOL				IsHaveFriend_FriendPointMoreThenPara(int32 nValue);

	inline void			ModifyFriendType(int32 nIndex, eRELATIONSHIP_TYPE RelationType);
	inline Time_t			GetSendGiftTime();
	inline uchar			GetSendGiftTimes();
	inline void			SetSendGiftTime(Time_t time);
	inline void			SetSendGiftTimes(uchar times);
	inline void			SetRelationGroupName(const int32 index, const char *szName);
	inline void			ModifyFriendPoint(int32 Index, int32 nFriendPoint);
	inline void			AdjustRelationType(int32 Index, uchar uType);
	inline void			AdjustRelationGroup(int32 Index, uchar uGroup);
	inline void			DeleteRelation(int32 Index);
	inline void			TrimRelation(eRELATIONSHIP_TYPE rt);
	inline void			IncRelationCount(int32 Index);
	inline void			DecRelationCount(int32 Index);
	inline void			SetSpouse(const SMarriageInfo *pMarriageInfo);
	inline void			AddPrentice(GUID_t guid);
	inline void			DelPrentice(GUID_t guid, BOOL bIsForce = FALSE);
	inline void			Set_Property_MoralPoint(uint32 uPoint);
	inline void			DelMaster();
	inline void			AddMaster(GUID_t guid);
	inline void			DoWedding();
	inline int32			GetPatrolID() const;
	inline void			SetPatrolID(int32 nIndex);
	inline int32			GetCurrentPathNode() const;
	inline void			SetCurrentPathNode(int32 nIndex);
	inline int32			GetRelationMemberNum(eRELATIONSHIP_TYPE eType);

	inline void			SetHonorRecord(const SArchiveLoader_Honor *pRecord);

	inline void			SetAbilityLevel(SpellID_t abilityid, int32 lvl);
	inline void			SetAbilityExp(SpellID_t abilityid, int32 exp);
	inline void			SetPrescrLearnedFlag(const PrescriptionID_t prescrid, BOOL flag);

	inline const _HORSE_DB_LOAD	*GetPet(uint32 iIndex) const;
	inline const _HORSE_DB_LOAD	*GetBankPet(uint32 iIndex) const;

	inline void			SetSettingData(int32 nType, _PLAYER_SETTING *Value);
	inline const _PLAYER_SETTING	*GetSetting(int32 nType) const;

	inline void			SetGameSetting(int32 gameSettingMode, BOOL bShow);
	inline const uchar		GetGameSettingMode(int32 gameSettingMode) const;

	inline void			SetPrivateInfo(SArchiveLoader_PrivateInfo *pPrivateInfo);

	inline int32			GetReserve(int32 index);
	inline void			SetReserve(int32 index, int32 value);

	inline uchar			GetGuildBuildCount();
	inline void			SetGuildBuildCount(uchar count);
	inline int32			GetGuildBuildDay();
	inline void			SetGuildBuildDay(int32 nDay);

	inline void			SetSoldItemValue(int32 idx, SItem *pItem);
	inline void			SetSoldItemPrice(int32 idx, int32 iPrice);
	inline void			SetSoldItemPriceType(int32 idx, int32 iPriceType);

	inline SItem			*GetSoldItemValue(int32 idx) const;
	inline int32			GetSoldItemPrice(int32 idx) const;
	inline int32			GetSoldItemPriceType(int32 idx) const;

	inline void			SetDBFlag(CHAR_ATTR_DBFLAG uIndex, BOOL bFlag);
	inline BOOL			GetDBFlag(CHAR_ATTR_DBFLAG uIndex);

	inline void			SetExploit(int32 nExploit);
	inline int32		GetExploit();

	inline void			SetExploitDay(int16 nDay);
	inline int16		GetExploitDay();
	
	inline ID_t			GetWorldID();

	inline void			SetMountModelID(int32 nModelID);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
private:
	inline SItem	*_GetBagItem(uint32 uBagIndex);
	inline SItem	*_GetBankItem(uint32 uBankIndex);
	inline void	_RegArchiveAttr(PLAYER_PROPERTY_ARCHIVE eOffSet, void *pArg, int32 iSize);
	inline void	_RegSHMAttr(PLAYER_PROPERTY_ARCHIVE eOffSet, void *pArg, int32 iSize);
	void		_RegisterArchiveAttributes();
	void		_RegisterSHMAttributes();

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	_HORSE_DB_LIST_LOAD	*m_dbPetList;
	_BANKPET_DB_LIST_LOAD	*m_dbBankPetList;

	inline void		SetBankPetValidSlot(int32 val);
	inline int32		GetBankPetValidSlot();

	void			SetArchiveEnumPropertyDirty(PLAYER_PROPERTY_ARCHIVE eOffSet, BOOL bFlag = TRUE);
	BOOL			GetArchiveEnumPropertyDirty(PLAYER_PROPERTY_ARCHIVE eOffSet);

	void			SetToGLEnumPropertyDirty(PLAYER_PROPERTY_ARCHIVE eOffSet, BOOL bFlag = TRUE);
	BOOL			GetToGLEnumPropertyDirty(PLAYER_PROPERTY_ARCHIVE eOffSet);

public:
	inline const SArchiveLoader_Player_ExtendInfo* GetPlayerExtendInfoArchive();

	inline const SPlayerShopFolder& GetShopItemFavorite();
	BOOL AddShopItemFavorite(const SPlayerShopElement& element);
	BOOL DelShopItemFavorite(const SPlayerShopElement& element);
	BOOL UpdateShopItemFavorite(const SPlayerShopElement& element);

	inline const SPlayerShopFolder& GetShopItemBuyHistory();
	BOOL AddShopItemBuyHistory(const SPlayerShopElement& element);
	BOOL DelShopItemBuyHistory(const SPlayerShopElement& element);
	BOOL UpdateShopItemBuyHistory(const SPlayerShopElement& element);	

public:
	int32 GetInherenceBalanceLevel(PLAYER_PROPERTY_LEVEL4_BALANCE iBalanceIndex);
	void SetInherenceBalanceLevel(PLAYER_PROPERTY_LEVEL4_BALANCE iBalanceIndex, int32 iValue);
	SPlayerInherenceBalance* GetInherenceBalance();

public:
	inline SPlayerInherenceZhanJing& GetInherenceZhanJing();

	inline int32 GetInherenceZhuanGongLevel(PROFESSION_TYPE eProfession);
	inline void SetInherenceZhuanGongLevel(PROFESSION_TYPE eProfession, int32 value);

	inline int32 GetInherenceZhuanGongPoint(PROFESSION_TYPE eProfession);
	inline void SetInherenceZhuanGongPoint(PROFESSION_TYPE eProfession, int32 value);

	inline int32 GetInherenceZhuanGongTotalCoefficient();
	inline void SetInherenceZhuanGongTotalCoefficient(int32 value);
	
	inline int32 GetInherenceZhuanGongCoefficient(PROFESSION_TYPE eProfession);
	inline void SetInherenceZhuanGongCoefficient(PROFESSION_TYPE eProfession, int32 value);

	inline int32 GetInherenceZhuanFangTotalPoint();
	inline void SetInherenceZhuanFangTotalPoint(int32 value);

	inline int32 GetInherenceZhuanFangLevel(PROFESSION_TYPE eProfession);
	inline void SetInherenceZhuanFangLevel(PROFESSION_TYPE eProfession, int32 value);


/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
private:
	SArchiveLoader_Player			*m_dbPlayer;
	SArchiveLoader_Bag			*m_dbBag;
	SArchiveLoader_Equip			*m_dbEquip;
	SArchiveLoader_Bank			*m_dbBank;
	SArchiveLoader_Spell			*m_dbSpell;
	SArchiveLoader_CoolDown	*m_dbCooldown;
	SArchiveLoader_Relationship		*m_dbRelation;
	SArchiveLoader_Honor		*m_dbHonorRecord;
	SArchiveLoader_Skill			*m_dbSkill;
	SArchiveLoader_Effect			*m_dbEffect;
	SArchiveLoader_Quest			*m_DBQuest;
	SArchiveLoader_Setting		*m_dbSetting;
	SArchiveLoader_PrivateInfo		*m_dbPrivateInfo;
	SArchiveLoader_MonsterPet			*m_dbMonsterPet;
	SArchiveLoader_SoldList		*m_dbSoldList;
	SArchiveLoader_Player_ExtendInfo   *m_dbPlayerExtendInfo;
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
private:
	PlayerMK		*m_PlayerSHM;
	PLAYER_DB_ATTR_FLAG	*m_AttrFlag;
	PLAYER_DB_ATTR_FLAG	*m_AttrFlag_ToWorld;
	PLAYER_DB_ATTR_REG	*m_AttrReg;
	PLAYER_DB_ATTR_REG	*m_AttrRegSM;

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	inline const SArchiveLoader_Bag			*GetBagArchive();
	inline const SArchiveLoader_Player			*GetPlayerArchive() const;
	inline const SArchiveLoader_Equip			*GetEquipArchive();
	inline const SArchiveLoader_Bank			*GetBankArchive();
	inline const SArchiveLoader_Spell			*GetSpellArchive();
	inline const SArchiveLoader_CoolDown	*GetCooldownArchive() const;
	inline const SArchiveLoader_Relationship			*GetRelationArchive() const;
	inline const SArchiveLoader_Honor			*GetHonorRecordArchive() const;
	inline const SArchiveLoader_Skill			*GetSkillArchive() const;
	inline const SArchiveLoader_Effect			*GetEffectArchive() const;
	inline const SArchiveLoader_Quest			*GetQuestArchive() const;
	inline const SArchiveLoader_Setting			*GetSettingArchive() const;
	inline const SArchiveLoader_PrivateInfo		*GetPrivateInfoArchive() const;
	inline const SArchiveLoader_MonsterPet			*GetMonsterPetArchive() const;
	inline const SArchiveLoader_SoldList			*GetSoldListArchive() const;
	inline const void				MarkImpactDirty();

	inline void					WritePlayerArchive(const SArchiveLoader_Player *pHumanDB);
	inline void					WriteBagArchive(const SArchiveLoader_Bag *pBagDB);
	inline void					WriteEquipArchive(const SArchiveLoader_Equip *pEquipDB);
	inline void					WriteBankArchive(const SArchiveLoader_Bank *pBankDB);
	inline void					WriteSpellArchive(const SArchiveLoader_Spell *pSkillDB);
	inline void					WriteCooldownArchive(const SArchiveLoader_CoolDown	 *pCooldownDB);
	inline void					WriteRelationArchive(const SArchiveLoader_Relationship *pRelationDB);
	inline void					WriteHonorRecordArchive(const SArchiveLoader_Honor *pHonorRecordDB);
	inline void					WriteAbilityArchive(const SArchiveLoader_Skill *pAbilityDB);
	inline void					WriteImpactArchive(const SArchiveLoader_Effect *pImpactDB);
	inline void					WriteQuestArchive(const SArchiveLoader_Quest *pQuestDB);
	inline void					WriteSettingArchive(const SArchiveLoader_Setting *pSettingDB);
	inline void					WritePrivateInfoArchive(const SArchiveLoader_PrivateInfo *pPrivateDB);
	inline void					WriteMonsterPetArchive(const SArchiveLoader_MonsterPet *pMonsterPetDB);
	inline void					WritePetArchive(const _HORSE_DB_LIST_LOAD *pPetData);
	inline void					WriteBankPetArchive(const _BANKPET_DB_LIST_LOAD *pPetData);
	inline void					WriteSoldListArchive(const SArchiveLoader_SoldList *pSoldList);
	inline void					WritePlayerExtendInfoArchive(const SArchiveLoader_Player_ExtendInfo *pPlayerExtendInfo);
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
private:
	void	*GetArchiveEnumProperty(PLAYER_PROPERTY_ARCHIVE eOffSet);
	void	*GetSMEnumProperty(PLAYER_PROPERTY_ARCHIVE eOffSet);
	int32	GetArchiveEnumPropertySize(PLAYER_PROPERTY_ARCHIVE eOffSet);
	int32	GetSMEnumPropertySize(PLAYER_PROPERTY_ARCHIVE eOffSet);
};

#include "PlayerDB.inl"
#endif
