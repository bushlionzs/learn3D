#pragma once
#include "KDefine.h"

#define BLEND_IN_TIME	(0.25f)
#define BLEND_OUT_TIME	(0.25f)

// ��������
enum eWEAPON_TYPE
{
	WEAPON_TYPE_INVALID = -1,

	WEAPON_TYPE_NONE,		// ͽ��
	WEAPON_TYPE_FALCHION,	// ��
	WEAPON_TYPE_SWORD,		// ��
	WEAPON_TYPE_BOW,		// ����
	WEAPON_TYPE_GUN,		// ��ǹ
	WEAPON_TYPE_GAVEL,		// �
	WEAPON_TYPE_STAFF,		// ��
	WEAPON_TYPE_HOLD,		// ˫��
	WEAPON_TYPE_DOUBLE,		// ˫��
	WEAPON_TYPE_FLAG,		// ����
	WEAPON_TYPE_LONG,		// ����
	WEAPON_TYPE_NPC,		// NPC
	WEAPON_TYPE_SPEAR,		// ��ì
	WEAPON_TYPE_TOKEN,		// ��
	WEAPON_TYPE_CROSSBOW,	// ��
	WEAPON_TYPE_FIREGUN,	// ���
	WEAPON_TYPE_CROSS,		// ʮ�ּ�
	WEAPON_TYPE_FAN,		// ��

	WEAPON_TYPE_NUMBERS,
};

/* ����״̬ */
enum CHARACTER_ACTION
{
	CA_INVALID = -1,			/* ��Ч����ֹ���� AASMD_NOTHING_DEGREE */
	CA_DIRECTIONAL,					/* ת�� AASMD_DIRECTIONAL_DEGREE */
	CA_MOVING,						/* �ƶ� AASMD_MOVING_DEGREE */
	CA_RIDING,						/* �Ƿ����� AASMD_RIDING_DEGREE */
	CA_ATTACK,						/* ���� AASMD_ATTACK_DEGREE */
	CA_LIFE,						/* ���� AASMD_LIFE_DEGREE */
	CA_WEAPON,						/* ���� AASMD_WEAPON_DEGREE */
	CA_DAMAGE,						/* ���� AASMD_DAMAGCD_DEGREE */
	CA_POSTURE,						/* ���ƣ�վ�������£�AASMD_POSTURE_DEGREE, */
	CA_JUMP,					/* ���Ƿ�����|��Ծ AASMD_EQUITATION_DEGREE, 0 0.33 ���� 0.66 ��Ծ 1 */
	CA_GUARD,						/* ��������� AASMD_GUARD_DEGREE, */
	CA_MOOD,						/* ���鶯�� AASMD_MOOD_DEGREE */
	CA_DANCE,						/* ���� AASMD_DANCE_DEGREE */
	CA_WALK,						/* �����л� AASMD_WALK_DEGREE */
	CA_IDLE,						// ���� 
};

/* ������� */
enum CHARACTER_AAS_NODE
{
	AASSLOT_DOWN_IDLE_ATTACK = 0,	/* ����_վ��_���� */
	AASSLOT_DOWN_IDLE_MOOD = 1,	/* ����_վ��_���� */
	AASSLOT_DOWN_IDLE_DACE = 2,	/* ����_վ��_������� */
	AASSLOT_DOWN_IDLE_DAMAGE = 3,	/* ����_վ��_���� */
	AASSLOT_DOWN_IDLE_STAND = 4,	// ����_վ��_����
	AASSLOT_DOWN_IDLE_JUMP = 5,	// ����_վ��_��Ծ

	AASSLOT_DOWN_MOVE_ATTACK = 50,	/* ����_�ƶ�_���� */
	AASSLOT_DOWN_MOVE_MOOD = 51,	/* ����_�ƶ�_���� */
	AASSLOT_DOWN_MOVE_DAMAGE = 53,	/* ����_�ƶ�_���� */
	AASSLOT_DOWN_MOVE_JUMP = 55,	// ����_�ƶ�_��Ծ

	AASSLOT_UP_IDLE_ATTACK = 100,	/* ����_վ��_���� */
	AASSLOT_UP_IDLE_MOOD = 101,	/* ����_վ��_���� */
	AASSLOT_UP_IDLE_DAMAGE = 103,	/* ����_վ��_���� */
	AASSLOT_UP_IDLE_STAND = 104,	// ����_վ��_����
	AASSLOT_UP_IDLE_JUMP = 105,	// ����_վ��_��Ծ

	AASSLOT_UP_MOVE_ATTACK = 150,	/* ����_�ƶ�_���� */
	AASSLOT_UP_MOVE_MOOD = 151,	/* ����_�ƶ�_���� */
	AASSLOT_UP_MOVE_DAMAGE = 153,	/* ����_�ƶ�_���� */
	AASSLOT_UP_MOVE_JUMP = 155,	// ����_�ƶ�_��Ծ
};


// ���ﶯ����ʶ
enum ACTION_TYPE
{
	BASE_ACTION_N_STAND = 0,	// վ��
	BASE_ACTION_N_WALK = 3,	// ����
	BASE_ACTION_N_RUN = 4,	// �ܲ�
	BASE_ACTION_F_IDLE = 14,	// ��Ϣ
	BASE_ACTION_F_BE_HIT0 = 23,	// ����
	BASE_ACTION_F_DIE0 = 25,	// ����
	BASE_ACTION_F_DIEFLYi = 27,	// ��������
	BASE_ACTION_F_CADAVER0 = 29,	// ʬ��
	BASE_ACTION_N_JUMP = 30,	// ����
	BASE_ACTION_N_FALLING = 31,	// ����
	BASE_ACTION_N_TOUCHDOWN = 32,	// ���
	BASE_ACTION_N_IDLE_1 = 41,	// ����1
	BASE_ACTION_N_IDLE_2 = 42,	// ����2
	BASE_ACTION_N_IDLE_3 = 43,	// ����3
	BASE_ACTION_N_IDLE_4 = 44,	// ����4
	BASE_ACTION_N_IDLE_5 = 45,	// ����5

	BASE_ACTION_NUMBERS
};
