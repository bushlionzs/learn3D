#pragma once
#include <string.h>
#include <stdint.h>
/* Run Command �ķ���ֵ */
enum eRUN_CMD_RESULT_CODE { RC_OK = 0, RC_ERROR, RC_SKIP, RC_WAIT,	   /* �ȴ� */ };

enum GAME_CMD_TYPE 
{ 
	GCT_UNKOWN = -1, 
	GCT_WORLD, 
	GCT_OBJECT, 
	GCT_AI, 
	GCT_DPC, 
	GCT_UI, 
	GCT_MOUSE, };

#define MAX_OBJ_CMD_PARAM_NUM	(64)

/*
 -----------------------------------------------------------------------------------------------------------------------
    ��Ϸ���߼�ָ�����
 -----------------------------------------------------------------------------------------------------------------------
 */
struct Command_Base
{
	/* �������� */
	uint32_t mCommandSize;
	uint32_t	m_wID;
	GAME_CMD_TYPE	m_eType;

	/* ����������� */
	union
	{
		const void			*pConstParam[MAX_OBJ_CMD_PARAM_NUM];
		void				*pParam[MAX_OBJ_CMD_PARAM_NUM];
		uint32_t				uParam[MAX_OBJ_CMD_PARAM_NUM];
		int32_t					nParam[MAX_OBJ_CMD_PARAM_NUM];
		float				fParam[MAX_OBJ_CMD_PARAM_NUM];
		BOOL				bParam[MAX_OBJ_CMD_PARAM_NUM];
		uint64_t	        u64Param[MAX_OBJ_CMD_PARAM_NUM / 2];
		int64_t				n64Param[MAX_OBJ_CMD_PARAM_NUM / 2];
	};
public:
	Command_Base (void)
	{
		m_eType = GCT_UNKOWN;
	}

	/*
	 ===================================================================================================================
	 ===================================================================================================================
	 */
	GAME_CMD_TYPE GetType(void) const
	{
		return m_eType;
	}

	/*
	 ===================================================================================================================
	 ===================================================================================================================
	 */
	void Release(void)
	{
		m_wID = 0xFFFF;
		memset(uParam, 0, sizeof(uParam));
	}
};

/*
 -----------------------------------------------------------------------------------------------------------------------
    Ӧ����object������
 -----------------------------------------------------------------------------------------------------------------------
 */
struct ObjectCmd :
	public Command_Base
{
	ObjectCmd (void)
	{
		m_eType = GCT_OBJECT;
	}
};

/*
 -----------------------------------------------------------------------------------------------------------------------
    Ӧ����AI������
 -----------------------------------------------------------------------------------------------------------------------
 */
struct AICmd :
	public Command_Base
{
	AICmd (void)
	{
		m_eType = GCT_AI;
	}
};

/*
 -----------------------------------------------------------------------------------------------------------------------
    Ӧ����UI������
 -----------------------------------------------------------------------------------------------------------------------
 */
struct DPCCmd :
	public Command_Base
{
	DPCCmd (void)
	{
		m_eType = GCT_DPC;
	}
};

/*
 -----------------------------------------------------------------------------------------------------------------------
    ��������ϵ�����
 -----------------------------------------------------------------------------------------------------------------------
 */
struct MouseCmd :
	public Command_Base
{
	enum MOUSE_CMD_TYPE
	{
		MCT_NULL,
		MCT_PLAYER_MOVETO,			/* �ƶ���Ŀ��� */

		/* fParam[0][1] = The position of target area */
		MCT_PLAYER_SELECT,			/* ѡ������ */

		/* uParam[0] = The ID of target object */
		MCT_SKILL_OBJ,				/* ��ѡĿ��ļ��� */		
		//uParam[0] = The ID of skill ;
		//uParam[1] = The ID of target object ;

		MCT_SKILL_POS,				// ���꼼�� ;
		MCT_SKILL_CANCEL_POS,		// ȡ�����꼼�� ;

		MCT_SKILL_DIR,				//������ ;
		//uParam[0] = The ID of skill ;
		//fParam[1] = The direction
		
		MCT_HIT_TRIPPEROBJ,			/* �����ܹ�������TripperObj��(�������...) */

		/*
		 * uParam[0] = The ID of Tripper obj ;
		 * ...
		 */
		MCT_SPEAK,					/* ��NPC̸�� */

		/* uParam[0] = The ID of NPC */
		MCT_CONTEXMENU,				/* ��ʾ�Ҽ��˵� */

		/* uParam[0] = The ID of NPC */
		MCT_REPAIR,					/* ����ָ�� */
		MCT_CANCLE_REPAIR,			/* ����ָ�� */

		MCT_USE_ITEM,				/* ��Ʒʹ�� */

		/*
		 * pParam[0] = Action Item ;
		 * uParam[1] = The ID of target object ;
		 * fParam[2] = Pos X ;
		 * fParam[3] = Pos Z ;
		 * uParam[4] = Is area
		 */
		MCT_CANCEL_USE_ITEM,		/* ȡ����Ʒʹ�� */

		MCT_ENSNARE_MOUNT,			/* ��׽���� */
		MCT_CANT_ENSNARE_MOUNT,		/* �޷���׽���� ����ڽ����ϵ�����״̬ */

		MCT_UI_USE_IDENTIFY,		/* ʹ�ü������� */
		MCT_UI_USE_CANCEL_IDENTIFY, /* ȡ��ʹ�ü������� */

		MCT_ADD_FRIEND,				/* ��Ӻ��� */
		MCT_CANCEL_ADD_FRIEND,
		MCT_EXCHANGE,				/* ���� */

		MCT_ENTER_CHARIOT,			/* ����ս�� uParam[0] = The ID of NPC */

		/*
		 * MCT_MOOD_ANIM, ��б��� ;
		 * MCT_CANCEL_MOOD_ANIM, ȡ����б�?
		 */
		MCT_ENSNARE_BEASTIE,		/* ��׽���� */
		MCT_CANT_ENSNARE_BEASTIE,	/* ���ɲ�׽���� */
		MCT_SPLIT,					/* ���ָ�� */
		MCT_CANCLE_SPLIT,			/* ���ָ�� */
		MCT_LOCKITEM,				/* ����ָ�� */
		MCT_CANCLE_LOCKITEM,		/* ����ָ�� */
		MCT_UNLOCKITEM,				/* ����ָ�� */
		MCT_CANCLE_UNLOCKITEM,		/* ����ָ�� */

		MCT_AUTO_MOVE,				// �Զ�����
		MCT_CANCEL_AUTO_MOVE,
	};

	MouseCmd (void)
	{
		m_eType = GCT_MOUSE;
	}

	/* ����������� */
	MOUSE_CMD_TYPE	m_typeMouse;
};
