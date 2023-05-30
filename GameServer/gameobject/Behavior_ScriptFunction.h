/*$T MapServer/Server/AI/Behavior_ScriptFunction.h GC 1.140 10/10/07 10:07:20 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef _AISCRIPTFUNCTION_H_
#define _AISCRIPTFUNCTION_H_

class	Character;

typedef int32 (*PLAISFunc) (Character * pChar, int32 param0, int32 param1, int32 param2);
#define REGISTERAISFUNC(funcname)	{ #funcname, PLAISFunc(funcname) },

struct BHSFuncMap
{
	const char		*funcname;
	PLAISFunc	Func;
};

struct BHSMacroMap
{
	const char	*Macroname;
	int32	MacroID;
};

const PLAISFunc Name2FuncPtr(const char *funcName);
const char	*Ptr2FuncName(const PLAISFunc FuncPtr);
const int32	Name2Macro(const char *MacroName);

/*
 * function:��ȡ���� ;
 * param0: -- ;
 * param1: -- ;
 * param2: -- ;
 * return: HP of Character
 */
int32		BehaviorStateGetHP(Character *pChar, int32 param0, int32 param1, int32 param2);

/*
 * function:��ȡħ�� ;
 * param0: -- ;
 * param1: -- ;
 * param2: -- ;
 * return: HP of Character
 */
int32		BehaviorStateGetMP(Character *pChar, int32 param0, int32 param1, int32 param2);

/*
 * function:��ȡ�ȼ� ;
 * param0: -- ;
 * param1: -- ;
 * param2: -- ;
 * return: Level of Characte
 */
int32		BehaviorStateGetLevel(Character *pChar, int32 param0, int32 param1, int32 param2);

/*
 * function:��ȡ���˵����� ;
 * param0: -- ;
 * param1: -- ;
 * param2: -- ;
 * return: HP of Enemy Character
 */
int32		BehaviorStateGetEHP(Character *pChar, int32 param0, int32 param1, int32 param2);

/*
 * function:��ȡ���˵�ħ�� ;
 * param0: -- ;
 * param1: -- ;
 * param2: -- ;
 * return: MP of Enemy Character
 */
int32		BehaviorStateGetEMP(Character *pChar, int32 param0, int32 param1, int32 param2);

/*
 * function:��ȡ���˵�ְҵ ;
 * param0: -- ;
 * param1: -- ;
 * param2: -- ;
 * return: Profession of Enemy Character
 */
int32		BehaviorStateGetEProfession(Character *pChar, int32 param0, int32 param1, int32 param2);

/*
 * function:��ȡ���˵ĵȼ� ;
 * param0: -- ;
 * param1: -- ;
 * param2: -- ;
 * return: Level of Enemy Character
 */
int32		BehaviorStateGetELevel(Character *pChar, int32 param0, int32 param1, int32 param2);

/*
 * function:��ȡ���˵��Ա� ;
 * param0: -- ;
 * param1: -- ;
 * param2: -- ;
 * return: Sex of Enemy Character
 */
int32		BehaviorStateGetESex(Character *pChar, int32 param0, int32 param1, int32 param2);

/*
 * function:��ȡ���˵�PKֵ ;
 * param0: -- ;
 * param1: -- ;
 * param2: -- ;
 * return: PKValue of Enemy Character
 */
int32		BehaviorStateGetEPK(Character *pChar, int32 param0, int32 param1, int32 param2);

/*
 * function:��ȡ��ǰ�������� ;
 * param0: -- ;
 * param1: -- ;
 * param2: -- ;
 * return: Count of Enemy Character
 */
int32		BehaviorStateGetEnemyNum(Character *pChar, int32 param0, int32 param1, int32 param2);

/*
 * function:���ܹ��� ;
 * param0: �������� 0-��� 1-����Ķ��� 2-ָ������ ;
 * param1: �������� fX, param0=2ʱ��Ч ;
 * param2: �������� fZ, param0=2ʱ��Ч ;
 * return: 1-�ɹ� -1-ʧ��
 */
int32		BehaviorStateToFlee(Character *pChar, int32 param0, int32 param1, int32 param2);

/*
 * function:ʹ�ü��ܹ��� ;
 * param0: ����ID ;
 * param1: -- ;
 * param2: -- ;
 * return: 1-�ɹ� -1-ʧ��
 */
int32		BehaviorStateToSkill(Character *pChar, int32 param0, int32 param1, int32 param2);

/*
 * function:�ٻ����ѹ��� ;
 * param0: �ٻ����� ;
 * param1: �ٻ����� fX, fX=-1��fZ=-1ʱ�ٻ�������ߵĶ��ѣ������ٻ�ָ���ص�Ķ��� ;
 * param2: �ٻ����� fZ, fX=-1��fZ=-1ʱ�ٻ�������ߵĶ��ѣ������ٻ�ָ���ص�Ķ��� ;
 * return: 1-�ɹ� -1-ʧ��
 */
int32		BehaviorStateToSummon(Character *pChar, int32 param0, int32 param1, int32 param2);

/*
 * function:����˵������ToSpeak(10,5)��ʾ����˵��10��15�Ļ� ;
 * param0: ˵����ʼID ;
 * param1: ˵��IDƫ������ ;
 * param2: -- ;
 * return: 1-�ɹ� -1-ʧ��
 */
int32		BehaviorStateToSpeak(Character *pChar, int32 param0, int32 param1, int32 param2);

/*
 * function:����Ѳ��·�� ;
 * param0: ·��ID ;
 * param1: -- ;
 * param2: -- ;
 * return: 1-�ɹ� -1-ʧ��
 */
int32		BehaviorStateSetPatrolID(Character *pChar, int32 param0, int32 param1, int32 param2);

/*
 * function:��ʼѲ�� ;
 * param0: -- ;
 * param1: -- ;
 * param2: -- ;
 * return: 1-�ɹ� -1-ʧ?
 */
int32		BehaviorStateStartPatrol(Character *pChar, int32 param0, int32 param1, int32 param2);

/*
 * function:��̬�ı�Behavior_TemplateID ;
 * param0: Behavior_TemplateID ;
 * param1: -- ;
 * param2: -- ;
 * return: 1-�ɹ� -1-ʧ?
 */
int32		BehaviorStateChangeTemplate(Character *pChar, int32 param0, int32 param1, int32 param2);

/*
 * function:Ŀ���Ƿ���ָ��Buff ;
 * param0: 0�������Լ� 1������ĵ�ǰ���� ;
 * param1: BuffID ;
 * param2: -- ;
 * return: 1-�ɹ� -1-ʧ��
 */
int32		BehaviorStateHaveBuff(Character *pChar, int32 param0, int32 param1, int32 param2);

/*
 * function:Ŀ���Ƿ���ָ��Buff ;
 * param0: 0�������Լ� 1������ĵ�ǰ���� ;
 * param1: BuffLogicID ;
 * param2: -- ;
 * return: 1-�ɹ� -1-ʧ��
 */
int32		BehaviorStateHaveBuffOfLogic(Character *pChar, int32 param0, int32 param1, int32 param2);

/*
 * function:�������һ������ ;
 * param0: �������ʱ�������ӵĳ��ֵ ;
 * param1: -- ;
 * param2: -- ;
 * return: 1-�ɹ� -1-ʧ��
 */
int32		BehaviorStateRandomAttack(Character *pChar, int32 param0, int32 param1, int32 param2);

/*
 * function:�����ض�ְҵ�ĵ��� ;
 * param0: ְҵID ;
 * param1: �������ʱ�������ӵĳ��ֵ ;
 * param2: -- ;
 * return: 1-�ɹ� -1-ʧ��
 */
int32		AIS_AttackSpecialProfession(Character *pChar, int32 param0, int32 param1, int32 param2);

/*
 * function:�����ض�ְҵ�ĵ��� ;
 * param0: SkillID ;
 * param1: -- ;
 * param2: -- ;
 * return: 1-�ɹ� -1-ʧ��
 */
int32		BehaviorStateUseSkillToSpecialProfession(Character *pChar, int32 param0, int32 param1, int32 param2);
#endif
