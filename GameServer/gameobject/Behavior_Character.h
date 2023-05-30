#ifndef __AI_CHARACTER_H__
#define __AI_CHARACTER_H__

#include "TypeDefine.h"
#include "Behavior_State.h"

class	Object;
class	Character;

class	Behavior_Character
{
	friend class	BHVState;
public:
	enum { MAX_THREAT_COUNT = 20 };

	Behavior_Character(void);
	virtual~Behavior_Character(void);

	virtual BOOL Init(Character *pCharacter);
	virtual void Clear(void);

public:
	BOOL Logic(uint32 uTime);

	void SetBehavior_State(BHVState* s);
	BHVState *GetBehavior_State(void) const{return m_pBHVState;}
	ObjID_t GetCurrentUseSpellID(){return m_currUseSpellID;}

	BOOL BHV_CanUseSpell(void) const{return m_pBHVState->CanUseSpell(this);}
	BOOL BHV_CanUseItem(void) const{return m_pBHVState->CanUseItem(this);}

	virtual void ChangeState(eSTATE eState);
	virtual void ForceInterruptAllSpell(void){}
	virtual void ForceInterruptAutoSpell(void){}
	virtual void Relive(int32 nResultCode){};

	void	OnEvent_Die(Object *pKiller = NULL);
	void	OnEvent_Relive(Object *pKiller = NULL);
	void	OnEvent_Damage(int32 nDamage, Character *pAttacker);
	void	OnEvent_BeHeal(Character *pCharacter, int32 nHeal);
	void	OnEvent_BeSpell(Character *pCharacter, int32 nGoodEffect);

	OPT_RESULT BHV_Jump(void);
	OPT_RESULT BHV_Stop(void);
	OPT_RESULT BHV_Stall(void);
	OPT_RESULT BHV_StopSpell();
	OPT_RESULT BHV_StopMove();
	OPT_RESULT BHV_UseSkill(void);
	OPT_RESULT BHV_Move(const GLPos *pTar);
	OPT_RESULT BHV_UseItem(ID_t	nBagIndex,ObjID_t nTargetObj,GLPos const &posTarget, SHorseGuid const &guidTargetPet,ID_t nTargetItem);
	OPT_RESULT BHV_UseSpell(ObjID_t idSpell,ObjID_t idTarget,float fTargetX,float fTargetZ,int32	iHurtDelayTime,float fDir = -1.f,GUID_t	guidTarget = INVALID_ID);
	OPT_RESULT BHV_Move(int32 nHandleID,uint16 wNumTargetPos,const GLPos *paTargetPos,int32 nStopLogicCount = INVALID_ID,const GLPos *paCurPos = NULL,ObjID_t nSenderID = INVALID_ID);


protected:
	void	Terror_Logic(uint32 uTime);
	Character* GetCharacter() const;
	GLPos	GetRandPosOfCircle(const GLPos *pPos, float fRadio);

	OPT_RESULT BHV_Move_i(const GLPos *pTar);
	OPT_RESULT BHV_UseSpell_i(ObjID_t idSpell,ObjID_t idTarget,float fTargetX,float	fTargetZ,int32 iHurtDelayTime,float fDir = -1.f,GUID_t	guidTarget = INVALID_ID);
	OPT_RESULT BHV_UseItem_i(ID_t nBagIndex,ObjID_t	nTargetObj,	GLPos const	&posTarget, SHorseGuid const &guidTargetPet,ID_t nTargetItem);

	virtual void	State_OnActive(int32 nStateID);
	virtual void	State_OnShutdwon(int32 nStateID);

	virtual void Idle_Logic(uint32 uTime){};
	virtual void Dead_Logic(uint32 uTime){};
	virtual void Combat_Logic(uint32 uTime){};
	virtual void Flee_Logic(uint32 uTime){};
	virtual void Patrol_Logic(uint32 uTime){};
	virtual void Gohome_Logic(uint32 uTime){};
	virtual void Service_Logic(uint32 uTime){};
	virtual void Approach_Logic(uint32 uTime){};
	virtual void Sit_Logic(uint32 uTime){};
	virtual void TeamFollow_Logic(uint32 uTime){};

	virtual void Event_OnDie(Object *pKiller = NULL){};
	virtual void Event_OnDamage(int32 nDamage, Character *pAttacker){};
	virtual void Event_OnBeSpell(Character *pCharacter, int32 nGoodEffect){};
	virtual void Event_OnBeHeal(Character *pCharacter, int32 nHeal){};
	virtual void Event_OnMove(const GLPos *pTar){}


protected:
	BHVState	*m_pBHVState;
	Character	*m_pCharacter;
	ObjID_t		m_currUseSpellID;

private:
	int32	m_nIntervalTime;
};

#endif
