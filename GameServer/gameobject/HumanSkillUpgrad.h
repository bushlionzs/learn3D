/*$T MapServer/Server/Obj/HumanAssistantClass/HumanSkillUpgrad.h GC 1.140 10/10/07 10:07:31 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef HumanSkillUpgrad_h__
#define HumanSkillUpgrad_h__

#include "TypeDefine.h"

class	Player;

class	PlayerSkillUpgrade
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	PlayerSkillUpgrade();
	virtual ~PlayerSkillUpgrade();

	void	Clear(void);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	void	HumanSkillLevelUp(const Player *pPlayer, SpellID_t iSkillID, int32 iLevel, int32 iType);

	BOOL	HumanSkillLevelUpNoCheck(const Player *pPlayer, SpellID_t iSkillID, int32 iLevel);
	int32	GetHumanSkillLevel(const Player *pPlayer, SpellID_t iSkillID);

	void	StartPassiveSkill(SpellID_t iSkillID, const Player *pPlayer);

	BOOL	IsEnoughMoneyEx(eCURRENCY_UNIT &nPriceType,  int32 nPrice);

	void	SpendMoney(eCURRENCY_UNIT &nPriceType, uint32 nPrice);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	eOPTRESULT		CheckCondition();
	eOPTRESULT		CheckCondition2();
	eOPTRESULT		CheckConditionforInherence();

	void			DepleteHumanAttr();
	void			DepleteHumanAttrforInherence();


	void			UpgradeLevel();

	virtual eOPTRESULT	IsEnoughHumanLevel();

	virtual eOPTRESULT	IsEnoughSkillPoints();

	virtual eOPTRESULT	IsSkillClassSpendEnoughPosints();

	virtual eOPTRESULT	IsOccupationMatch();

	virtual eOPTRESULT	IsEnoughParentSkillLevel();

	virtual eOPTRESULT	IsEnoughMoney();

	virtual eOPTRESULT	IsEnoughExp();

	virtual eOPTRESULT	IsHadEnoughItem1();

	virtual eOPTRESULT	IsHadEnoughItem2();

	virtual eOPTRESULT	IsHadEnoughItem3();

	virtual void		SendSuccessSkillLevelupMsg(int32 iType);

	virtual void		SendFailedSkillLevelupMsg(int32 iType);

	virtual void		DepleteSkillPoints();

	virtual void		DepleteMoney();

	virtual void		DepleteExp();

	virtual void		DepleteItem1();

	virtual void		DepleteItem2();

	virtual void		DepleteItem3();

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
private:
	void		InitAttr(const Player *pPlayer, SpellID_t iSkillID, int32 iLevel);

	eOPTRESULT	CheckSkillStudyCondition();

	void		FindSkillIndex();

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	Player		*m_pHuman;

	SpellID_t	m_iSkillID;

	int32		m_iLevel;

	int32		m_iIndex;
};
#endif
