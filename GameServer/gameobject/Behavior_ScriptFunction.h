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
 * function:获取生命 ;
 * param0: -- ;
 * param1: -- ;
 * param2: -- ;
 * return: HP of Character
 */
int32		BehaviorStateGetHP(Character *pChar, int32 param0, int32 param1, int32 param2);

/*
 * function:获取魔法 ;
 * param0: -- ;
 * param1: -- ;
 * param2: -- ;
 * return: HP of Character
 */
int32		BehaviorStateGetMP(Character *pChar, int32 param0, int32 param1, int32 param2);

/*
 * function:获取等级 ;
 * param0: -- ;
 * param1: -- ;
 * param2: -- ;
 * return: Level of Characte
 */
int32		BehaviorStateGetLevel(Character *pChar, int32 param0, int32 param1, int32 param2);

/*
 * function:获取敌人的生命 ;
 * param0: -- ;
 * param1: -- ;
 * param2: -- ;
 * return: HP of Enemy Character
 */
int32		BehaviorStateGetEHP(Character *pChar, int32 param0, int32 param1, int32 param2);

/*
 * function:获取敌人的魔法 ;
 * param0: -- ;
 * param1: -- ;
 * param2: -- ;
 * return: MP of Enemy Character
 */
int32		BehaviorStateGetEMP(Character *pChar, int32 param0, int32 param1, int32 param2);

/*
 * function:获取敌人的职业 ;
 * param0: -- ;
 * param1: -- ;
 * param2: -- ;
 * return: Profession of Enemy Character
 */
int32		BehaviorStateGetEProfession(Character *pChar, int32 param0, int32 param1, int32 param2);

/*
 * function:获取敌人的等级 ;
 * param0: -- ;
 * param1: -- ;
 * param2: -- ;
 * return: Level of Enemy Character
 */
int32		BehaviorStateGetELevel(Character *pChar, int32 param0, int32 param1, int32 param2);

/*
 * function:获取敌人的性别 ;
 * param0: -- ;
 * param1: -- ;
 * param2: -- ;
 * return: Sex of Enemy Character
 */
int32		BehaviorStateGetESex(Character *pChar, int32 param0, int32 param1, int32 param2);

/*
 * function:获取敌人的PK值 ;
 * param0: -- ;
 * param1: -- ;
 * param2: -- ;
 * return: PKValue of Enemy Character
 */
int32		BehaviorStateGetEPK(Character *pChar, int32 param0, int32 param1, int32 param2);

/*
 * function:获取当前敌人数量 ;
 * param0: -- ;
 * param1: -- ;
 * param2: -- ;
 * return: Count of Enemy Character
 */
int32		BehaviorStateGetEnemyNum(Character *pChar, int32 param0, int32 param1, int32 param2);

/*
 * function:逃跑功能 ;
 * param0: 逃跑类型 0-随机 1-最近的队友 2-指定坐标 ;
 * param1: 逃跑坐标 fX, param0=2时有效 ;
 * param2: 逃跑坐标 fZ, param0=2时有效 ;
 * return: 1-成功 -1-失败
 */
int32		BehaviorStateToFlee(Character *pChar, int32 param0, int32 param1, int32 param2);

/*
 * function:使用技能功能 ;
 * param0: 技能ID ;
 * param1: -- ;
 * param2: -- ;
 * return: 1-成功 -1-失败
 */
int32		BehaviorStateToSkill(Character *pChar, int32 param0, int32 param1, int32 param2);

/*
 * function:召唤队友功能 ;
 * param0: 召唤个数 ;
 * param1: 召唤坐标 fX, fX=-1或fZ=-1时召唤怪物身边的队友，否则召唤指定地点的队友 ;
 * param2: 召唤坐标 fZ, fX=-1或fZ=-1时召唤怪物身边的队友，否则召唤指定地点的队友 ;
 * return: 1-成功 -1-失败
 */
int32		BehaviorStateToSummon(Character *pChar, int32 param0, int32 param1, int32 param2);

/*
 * function:怪物说话，如ToSpeak(10,5)表示可能说第10到15的话 ;
 * param0: 说话起始ID ;
 * param1: 说话ID偏移数量 ;
 * param2: -- ;
 * return: 1-成功 -1-失败
 */
int32		BehaviorStateToSpeak(Character *pChar, int32 param0, int32 param1, int32 param2);

/*
 * function:设置巡逻路径 ;
 * param0: 路径ID ;
 * param1: -- ;
 * param2: -- ;
 * return: 1-成功 -1-失败
 */
int32		BehaviorStateSetPatrolID(Character *pChar, int32 param0, int32 param1, int32 param2);

/*
 * function:开始巡逻 ;
 * param0: -- ;
 * param1: -- ;
 * param2: -- ;
 * return: 1-成功 -1-失?
 */
int32		BehaviorStateStartPatrol(Character *pChar, int32 param0, int32 param1, int32 param2);

/*
 * function:动态改变Behavior_TemplateID ;
 * param0: Behavior_TemplateID ;
 * param1: -- ;
 * param2: -- ;
 * return: 1-成功 -1-失?
 */
int32		BehaviorStateChangeTemplate(Character *pChar, int32 param0, int32 param1, int32 param2);

/*
 * function:目标是否有指定Buff ;
 * param0: 0：怪物自己 1：怪物的当前敌人 ;
 * param1: BuffID ;
 * param2: -- ;
 * return: 1-成功 -1-失败
 */
int32		BehaviorStateHaveBuff(Character *pChar, int32 param0, int32 param1, int32 param2);

/*
 * function:目标是否有指定Buff ;
 * param0: 0：怪物自己 1：怪物的当前敌人 ;
 * param1: BuffLogicID ;
 * param2: -- ;
 * return: 1-成功 -1-失败
 */
int32		BehaviorStateHaveBuffOfLogic(Character *pChar, int32 param0, int32 param1, int32 param2);

/*
 * function:随机攻击一个敌人 ;
 * param0: 随机攻击时额外增加的仇恨值 ;
 * param1: -- ;
 * param2: -- ;
 * return: 1-成功 -1-失败
 */
int32		BehaviorStateRandomAttack(Character *pChar, int32 param0, int32 param1, int32 param2);

/*
 * function:攻击特定职业的敌人 ;
 * param0: 职业ID ;
 * param1: 随机攻击时额外增加的仇恨值 ;
 * param2: -- ;
 * return: 1-成功 -1-失败
 */
int32		AIS_AttackSpecialProfession(Character *pChar, int32 param0, int32 param1, int32 param2);

/*
 * function:攻击特定职业的敌人 ;
 * param0: SkillID ;
 * param1: -- ;
 * param2: -- ;
 * return: 1-成功 -1-失败
 */
int32		BehaviorStateUseSkillToSpecialProfession(Character *pChar, int32 param0, int32 param1, int32 param2);
#endif
