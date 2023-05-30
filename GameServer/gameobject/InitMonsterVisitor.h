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

// ��ʼ���������
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
	// ����
	virtual CharacterVisitor::VisitorType	GetType();

	// ��ʼ��
	virtual void				VisitInitMonster(Character *pChar);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
private:
	// ��ʼ����С��Ѫ�ٷֱ�(Hppercent)
	void	InitMinDamagePercent();

	// ��ʼ������������(EXP)
	void	InitBaseExp();

	// ��ʼ�����̹������(short range att)
	void	InitAttackNear();

	// ��ʼ��Զ�̹������(long range att)
	void	InitAttackFar();

	// ��ʼ��ħ���������(magic att)
	void	InitAttackMagic();

	// ��ʼ�����̷���(short range recovery)
	void	InitDefenceNear();

	// ��ʼ��Զ�̷���(long range recovery)
	void	InitDefenceFar();

	// ��ʼ��ħ������(magic recovery)
	void	InitDefenceMagic();

	// ��ʼ��HP����(hp limit)	
	void	InitMaxHP();

	// ��ʼ��MP����(mp limit)	
	void	InitMaxMP();

	// ��ʼ��HP�ظ�(hp reversion)
	void	InitRestoreHP();

	// ��ʼ��MP�ظ�(mp reversion)
	void	InitRestoreMP();

	// ��ʼ������(hit rate)
	void	InitHitRate();

	// ��ʼ�����ܣ�volt��	
	void	InitMissRete();

	// ��ʼ�������ʣ�huixin)
	void	InitCritRate();

	// ��ʼ�����Թ���1(shuxingatt1 )
	void	InitAttrAttack1();

	// ��ʼ�����Թ���2(shuxingatt2 )
	void	InitAttrAttack2();

	// ��ʼ�����Թ���3(shuxingatt3)
	void	InitAttrAttack3();

	// ��ʼ�����Թ���4(shuxingatt4)
	void	InitAttrAttack4();

	// ��ʼ�����Է���1(shuxingrecovery1)
	void	InitAttrDefence1();

	// ��ʼ�����Է���2(shuxingrecovery2)
	void	InitAttrDefence2();

	// ��ʼ�����Է���3(shuxingrecovery3)	
	void	InitAttrDefence3();

	// ��ʼ�����Է���4(shuxingrecovery4)
	void	InitAttrDefence4();

	// ��ʼ����������ID
	void	InitWeaponID();

	// ��ʼ�������ID
	void	InitHorseID();

	// ��ʼ���Ƿ��ܹ�������
	void	InitUnbreakble();

	// �����n%
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
