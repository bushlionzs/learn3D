/*$T MapServer/Server/Obj/Visitor/InitMonsterVisitor.h GC 1.140 10/10/07 10:07:35 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef InitMonsterVisitor_h__
#define InitMonsterVisitor_h__

#include "CharacterVisitor.h"

class	Character;
class	Monster;
struct _INIT_OBJECT;
struct MonsterProperty;

// 初始怪物访问器
class InitMonsterVisitor :
	public CharacterVisitor
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	InitMonsterVisitor();
	virtual ~InitMonsterVisitor();

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	// 类型
	virtual CharacterVisitor::VisitorType	GetType();

	// 初始化
	virtual void				VisitInitMonster(Character *pChar);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
private:
	// 初始化最小伤血百分比(Hppercent)
	void	InitMinDamagePercent();

	// 初始化基础经验获得(EXP)
	void	InitBaseExp();

	// 初始化近程攻击获得(short range att)
	void	InitAttackNear();

	// 初始化远程攻击获得(long range att)
	void	InitAttackFar();

	// 初始化魔法攻击获得(magic att)
	void	InitAttackMagic();

	// 初始化近程防御(short range recovery)
	void	InitDefenceNear();

	// 初始化远程防御(long range recovery)
	void	InitDefenceFar();

	// 初始化魔法防御(magic recovery)
	void	InitDefenceMagic();

	// 初始化HP上限(hp limit)	
	void	InitMaxHP();

	// 初始化MP上限(mp limit)	
	void	InitMaxMP();

	// 初始化HP回复(hp reversion)
	void	InitRestoreHP();

	// 初始化MP回复(mp reversion)
	void	InitRestoreMP();

	// 初始化命中(hit rate)
	void	InitHitRate();

	// 初始化闪避（volt）	
	void	InitMissRete();

	// 初始化会心率（huixin)
	void	InitCritRate();

	// 初始化属性攻击1(shuxingatt1 )
	void	InitAttrAttack1();

	// 初始化属性攻击2(shuxingatt2 )
	void	InitAttrAttack2();

	// 初始化属性攻击3(shuxingatt3)
	void	InitAttrAttack3();

	// 初始化属性攻击4(shuxingatt4)
	void	InitAttrAttack4();

	// 初始化属性防御1(shuxingrecovery1)
	void	InitAttrDefence1();

	// 初始化属性防御2(shuxingrecovery2)
	void	InitAttrDefence2();

	// 初始化属性防御3(shuxingrecovery3)	
	void	InitAttrDefence3();

	// 初始化属性防御4(shuxingrecovery4)
	void	InitAttrDefence4();

	// 初始化武器调用ID
	void	InitWeaponID();

	// 初始化马调用ID
	void	InitHorseID();

	// 初始化是否能够被攻击
	void	InitUnbreakble();

	// 随机数n%
	int32	MakeRand(int32 iMax);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
private:
	Monster			*m_pChar;

	MonsterProperty*m_pAttr;
};
#endif
