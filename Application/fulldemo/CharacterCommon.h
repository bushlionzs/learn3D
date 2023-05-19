#pragma once

// �Ա�
enum eGENDER
{
	GENDER_INVALID	= -1,
	GENDER_FEMALE,			// Ů
	GENDER_MALE,			// ��	

	GENDER_NUM,
};


// ��������
enum eWEAPON_TYPE
{
	WEAPON_TYPE_INVALID	= -1,

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

/// ���ֻ�������
enum ENUM_WEAPON_LOCATOR_TYPE
{
	WL_DEFAULT,		// Ĭ�ϲ����������������Ͷ����
	WL_LEFT,		// ��
	WL_RIGHT,		// ��
	WL_L_ARM,		// ���ֱۣ������ã�
	WL_BOTH,		// ˫��
};



// ���ﶯ����ʶ
enum ACTION_TYPE
{
	BASE_ACTION_N_STAND		=  0,	// վ��
	BASE_ACTION_N_WALK		=  3,	// ����
	BASE_ACTION_N_RUN		=  4,	// �ܲ�
	BASE_ACTION_F_IDLE		= 14,	// ��Ϣ
	BASE_ACTION_F_BE_HIT0	= 23,	// ����
	BASE_ACTION_F_DIE0		= 25,	// ����
	BASE_ACTION_F_DIEFLYi	= 27,	// ��������
	BASE_ACTION_F_CADAVER0	= 29,	// ʬ��
	BASE_ACTION_N_JUMP		= 30,	// ����
	BASE_ACTION_N_FALLING	= 31,	// ����
	BASE_ACTION_N_TOUCHDOWN = 32,	// ���
	BASE_ACTION_N_IDLE_1	= 41,	// ����1
	BASE_ACTION_N_IDLE_2	= 42,	// ����2
	BASE_ACTION_N_IDLE_3	= 43,	// ����3
	BASE_ACTION_N_IDLE_4	= 44,	// ����4
	BASE_ACTION_N_IDLE_5	= 45,	// ����5

	BASE_ACTION_NUMBERS
};


// ����󶨵�
enum ENUM_CHARACTER_LOCATOR
{
	LOCATOR_CHAR_INVALID	= -1,

	LOCATOR_CHAR_HEAD,			// ����ͷ���󶨵�
	LOCATOR_CHAR_FRONT,			// ��������ǰ�õ�
	LOCATOR_CHAR_ATTACK,		// ���������ܻ���
	LOCATOR_CHAR_CENTER,		// �����������ĵ�
	LOCATOR_CHAR_FOOT,			// ����Ų��󶨵�
	LOCATOR_CHAR_HAND_L,		// �������ְ󶨵�
	LOCATOR_CHAR_HAND_R,		// �������ְ󶨵�
	LOCATOR_CHAR_SHOULDER_L,	// �������󶨵�
	LOCATOR_CHAR_SHOULDER_R,	// �����Ҽ�󶨵�
	LOCATOR_CHAR_SHIELD_L,		// ������۶��ư󶨵�

	LOCATOR_CHAR_NUMBERS
};


// ����󶨵�
enum ENUM_MOUNT_LOCATOR
{
	LOCATOR_MOUNT_INVALID	= -1,

	LOCATOR_MOUNT_LF,		// ��������ǰ��󶨵�
	LOCATOR_MOUNT_RF,		// ��������ǰ��󶨵�
	LOCATOR_MOUNT_LB,		// �����������󶨵�
	LOCATOR_MOUNT_RB,		// �������Һ���󶨵�
	LOCATOR_MOUNT_FOOT,		// ������Ų��󶨵�
	LOCATOR_MOUNT_HEAD,		// ������ͷ���󶨵�
	LOCATOR_MOUNT_BOSOM,	// �������ز��󶨵�
	LOCATOR_MOUNT_BACK,		// ��������NOX��󶨵�

	LOCATOR_MOUNT_NUMBERS,
};

// �����󶨵�
enum ENUM_WEAPON_LOCATOR
{
	LOCATOR_WEAPON_INVALID	= -1,

	LOCATOR_WEAPON_1	= 1,// �����󶨵�1
	LOCATOR_WEAPON_2,		// �����󶨵�2
	LOCATOR_WEAPON_3,		// �����󶨵�3
	LOCATOR_WEAPON_4,		// �����󶨵�3

	LOCATOR_WEAPON_NUMBERS,
};

// ��Ծ״̬
enum ENUM_CHAR_JUMP_STATE
{
	ENUM_CHAR_JUMP_STATE_INVALID = -1,
	ENUM_CHAR_JUMP_STATE_JUMPING,
	ENUM_CHAR_JUMP_STATE_FALLING,
	ENUM_CHAR_JUMP_STATE_TOUCHDOWN,
};


const char* GetCharaLocatorName( ENUM_CHARACTER_LOCATOR eLocator );
const char* GetMountLocatorName( ENUM_MOUNT_LOCATOR eLocator );
const char* GetWeaponLocatorName( ENUM_WEAPON_LOCATOR eLocator );




extern const char *g_szIDSTR_FACE_MESH;
extern const char *g_szIDSTR_FACE_MAT;

extern const char *g_szIDSTR_HAIR_MESH;
extern const char *g_szIDSTR_HAIR_MAT;

extern const char *szIDSTRING_SHOULDER_MESH;
extern const char *szIDSTRING_SHOULDER_MAT;

extern const char *g_szIDSTR_MAINBODY_MESH;
extern const char *g_szIDSTR_MAINBODY_MAT;

extern const char *g_szIDSTR_FOOT_MESH;
extern const char *g_szIDSTR_FOOT_MAT;

extern const char *g_szIDSTR_CAP_MESH;
extern const char *g_szIDSTR_CAP_MAT;

extern const char *g_szIDSTR_ARM_MESH;
extern const char *g_szIDSTR_ARM_MAT;

extern const char *g_szIDSTR_CURRENT_LEFTWEAPON;
extern const char *g_szIDSTR_CURRENT_RIGHTWEAPON;

extern const char *szIDSTRING_SHIELD_RIGHTWEAPON;

extern const char *szIDSTRING_DROPITEM;







