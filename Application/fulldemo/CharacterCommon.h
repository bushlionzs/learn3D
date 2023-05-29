#pragma once

// ----------------------------------------------------------------

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

/// NPC ����
enum eNPC_TYPE
{
	NPC_TYPE_INVALID = -1,
	NPC_TYPE_MONSTER,			// ����
	//NPC_TYPE_PET,				// ����
	NPC_TYPE_HORSE,				// ��
	NPC_TYPE_BUS,				// BUS
	NPC_TYPE_BEASTIE,			// ����
	NPC_TYPE_GUARDER,			// �ٻ���

	NPC_TYPE_NUMBERS
};

/// ����״̬����Ӧ��NPC��
enum QUEST_STATE
{
	MS_INVALID = -1,

	MS_HAVE_MISS_NOT_ACCEPT,		// �����񣬲������������

	MS_DRUGSTORE,					// ҩ��	-�� ҩ����
	MS_FORGER,						// ���� -�� ����
	MS_HOSTLER,						// ��� -�� ��
	MS_SULUDING,					// ��³��
	MS_COACHMAN,					// ������
	MS_COUNTRY,						// ���ҹ���
	MS_GUILD,						// ������

	MS_CHAPMAN,						// ����	���̡���ͼ��
	MS_FUBEN,						// �������	�Ǳ�ͼ��
	MS_TRAN,						// Կ�����˴���	������ͼ��
	MS_BIND,						// ��	
	MS_DECOMPOSE,					// ���	�ֽ�
	MS_BESET,						// ��Ƕ	
	MS_CHECKUP,						// ����	
	MS_COMPOSE,						// �ϳ�
	MS_CHANGE,						// ����
	MS_REPAIR,						// ����

	MS_BLUESIGN,					// ��ɫ̾��

//	MS_HAVE_CIRECLEMISS_NO_DONE,	// ѭ������δ���
MS_HAVE_MISS_NO_DONE,			// �ѽ����� δ���
MS_TRANSMISS,					// �д��͵�û�п���
MS_CIRCLEMISS,					// ��ѭ�����񣬿ɽ�
MS_MISS,						// �пɽ�����
MS_HAVE_MISS_DONE,				// �ѽ����� �����

};

/// ��ɫobj������
enum CHARACTER_BASE_TYPE
{
	CHAR_BASE_TYPE_INVALID = -1,

	CHAR_BASE_TYPE_NPC,			// NPC
	CHAR_BASE_TYPE_OHTER,		// �������
	CHAR_BASE_TYPE_ME			// �Լ�
};

/// ��ǰ��ɫ��Object���߼�״̬
enum CHARATER_STATE_TYPE
{
	CAHR_STATE_INVAILD = -1,	// ��Ч

	// �����߼�
	CAHR_STATE_IDLE,			// ����
	CAHR_STATE_MOVE,			// �ƶ�
	CAHR_STATE_DEAD,			// ����
	CAHR_STATE_STALL,			// ��̯

	// ��Ϊ�߼�
	CAHR_STATE_ACTION,			// ����
	CAHR_STATE_GATHER,			// �ۼ�����
	CAHR_STATE_LEAD,			// ��������
	CAHR_STATE_SEND,			// ���ͼ���
	CAHR_STATE_ABILITY,			// �����

	CAHR_STATE_NUMBERS
};

/// �߼�������
enum CHARATER_LOGIC_TYPE
{
	CHAR_LOGIC_BASE,					// �����߼�
	CHAR_LOGIC_ACTION,					// ��Ϊ�߼�
};

// ģ�ͱ�ʶ
enum CHARATER_MODEL_TYPE
{
	CHAR_MODEL_INVAILD = 0,
	CHAR_MODEL_CHAR,					// ����
	CHAR_MODEL_MOUNT,					// ����
	CHAR_MODEL_ADJUNCT_1,				// �ҽ���1
	CHAR_MODEL_ADJUNCT_2,				// �ҽ���2

	CHAR_MODEL_TYPE_NUM,
};

enum CHARIOT_TYPE
{
	CT_NONE = 0,
	CT_BUS,
	CT_CASHBOX,
	CT_GUILD_CASHBOX,
};



// ��������ģ�Ͳ���
enum BODY_PART_MODEL
{
	BODY_PART_HAIR = 0,// ͷ��
	BODY_PART_FACE,			// ��
	BODY_PART_RIGHTHAND,	// ����
	BODY_PART_LEFTHAND,		// ����
	BODY_PART_SHIELD,		// ��
	BODY_PART_MANTLE,		// ����
	BODY_PART_BODY,			// ����
	BODY_PART_HAND,			// ��
	BODY_PART_FEET,			// ��

	BODY_PART_NUMBER,
};

struct ModelPartData
{
	BOOL	m_bUpdateFlag;	// ���±�ʶ
	String	m_strBackUp;
	String	m_strValue;
	int32		m_nBackUp;
	int32		m_nValue;

	ModelPartData();

	void Clear();
	void Update();
	BOOL IsFlag();

	void SetValue(LPCSTR szValue);
	void SetValue(int32 nValue);
};

struct ModelPartDataList
{
	BOOL			m_bUpdateFlag;
	ModelPartData	m_ModelPartData[BODY_PART_NUMBER];
	String			m_strPartName[BODY_PART_NUMBER];

	ModelPartDataList();

	void Clear();
	void Update();
	BOOL IsFlag() { return m_bUpdateFlag; }

	void SetValue(int32 nPart, LPCSTR szValue);
	void SetValue(int32 nPart, int32 nValue);
};

LPCSTR GetCharaLocatorName( ENUM_CHARACTER_LOCATOR eLocator );
LPCSTR GetMountLocatorName( ENUM_MOUNT_LOCATOR eLocator );
LPCSTR GetWeaponLocatorName( ENUM_WEAPON_LOCATOR eLocator );




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







