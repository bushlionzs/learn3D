/*$T MapServer/Server/Spell/SpecialObjLogic/Spell_TrapObjLogic.h GC 1.140 10/10/07 10:07:56 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef SPECIALOBJLOGIC_H
#define SPECIALOBJLOGIC_H
#include "TypeDefine.h"
#include "StructEffect.h"
#include "gameobject/Character.h"
#include "gameobject/Trap.h"

enum 
{ 
	SPECIAL_OBJ_TYPE = INVALID_ID, 
	TRAP_OBJ, 
	TOTEM_OBJ, 
};

//����OBJ���߼����� ����������Ի��� �Ի����������������OBJ add by wujianping
class	SpecialObjectLogic
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	enum { TYPE = SPECIAL_OBJ_TYPE, ID = INVALID_ID, };
	enum { DESCRIPTOR_NUMBER = 16, };
	enum { INVALID_LOGIC_ID = INVALID_ID, TRAP_LOGIC_ID = 0, MAX_ID, } SpecialObjLogicID_T;

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	SpecialObjectLogic()
	{
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	~SpecialObjectLogic()
	{
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	virtual int32 GetType(void) const
	{
		return TYPE;
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	virtual void OnEvent_Tick(SpecialCreature &rThisObj) const
	{
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	virtual void OnEvent_TimeOver(SpecialCreature &rThis) const
	{
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	virtual BOOL IsScanedTargetValid(SpecialCreature &rThis, Character &rScaned) const
	{
		return FALSE;
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	virtual BOOL IsScanedTargetValid(SpecialCreature &rThis, SpecialCreature &rScaned) const
	{
		return FALSE;
	};

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	int32	GetDescriptorValueByIndex(SpecialCreature &rThis, int32 nIdx) const;

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
private:
};
SpecialObjectLogic const *ObjSpecial_GetLogic(SpecialCreature &rObj);
#endif