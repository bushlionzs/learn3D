///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//FileName:Spell_Logic_Misc.h
//Author:
//Date:
//Describe:ս�������߼��ľ���ʵ�֣��ղ�����ٻ�������OBJ����׽С����
//History:
//		1.
//		2.
//		3.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __COMMONSPELLLOGIC_H__
#define __COMMONSPELLLOGIC_H__

#include "TypeDefine.h"
#include "Spell_Logic_Base.h"

/*
=======================================================================================================================
add by shangy
CommonSpell001 ;
ս�������߼��ľ���ʵ��:
ʹ�÷�Χ���ղ�
=======================================================================================================================
*/
class CommonSpell001 :
	public BaseSpellLogic
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	enum { ID = COMMON_SPELL_001, };

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	CommonSpell001()
	{
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	~CommonSpell001()
	{
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	BOOL IsPassive(void) const
	{
		return FALSE;
	};
	BOOL	SpecificOperationOnSpellStart(Character &rMe) const;
	BOOL	OnEvent_Interrupt(Character &rMe) const;
	BOOL	OnEvent_Cancel(Character &rMe) const;

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	BOOL	EffectOnUnitOnce(Character &rMe, Character &rTar, BOOL bCriticalFlag = FALSE) const;

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
private:
};

/*
=======================================================================================================================
add by shangy
CommonSpell002 ;
ս�������߼��ľ���ʵ��:
ʹ�÷�Χ���ٻ��༼�ܣ�eg:��ӥ֮��,��Ȯ֮��,���ܻ���,���Ụ��,���ջ���
=======================================================================================================================
*/
class CommonSpell002 :
	public BaseSpellLogic
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	enum { ID = COMMON_SPELL_002, };

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	CommonSpell002()
	{
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	~CommonSpell002()
	{
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	BOOL IsPassive(void) const
	{
		return FALSE;
	};

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	BOOL	EffectOnUnitOnce(Character &rMe, Character &rTar, BOOL bCriticalFlag = FALSE) const;

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
private:
};

/*
=======================================================================================================================
add by shangy
CommonSpell003 ;
ս�������߼��ľ���ʵ��:
�����ﵱǰλ�ô���һ��object
ʹ�÷�Χ��δʹ��
=======================================================================================================================
*/
class CommonSpell003 :
	public BaseSpellLogic
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	enum { ID = COMMON_SPELL_003, };

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	CommonSpell003()
	{
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	~CommonSpell003()
	{
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	BOOL IsPassive(void) const
	{
		return FALSE;
	};

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	BOOL	EffectOnUnitOnce(Character &rMe, Character &rTar, BOOL bCriticalFlag = FALSE) const;

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
private:
};

/*
=======================================================================================================================
add by shangy
CommonSpell004 ;
ս�������߼��ľ���ʵ��:
ʹ�÷�Χ������С���Beastie����δʹ��
=======================================================================================================================
*/
class CommonSpell004 :
	public BaseSpellLogic
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	enum { ID = COMMON_SPELL_004, };

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	CommonSpell004()
	{
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	~CommonSpell004()
	{
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	BOOL IsPassive(void) const
	{
		return FALSE;
	};
	BOOL	SpecificOperationOnSpellStart(Character &rMe) const;
	BOOL	OnEvent_Interrupt(Character &rMe) const;
	BOOL	OnEvent_Cancel(Character &rMe) const;

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	BOOL	EffectOnUnitOnce(Character &rMe, Character &rTar, BOOL bCriticalFlag = FALSE) const;

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
private:
};
#endif