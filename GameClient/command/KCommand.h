#pragma once
#include <string.h>
#include <stdint.h>
/* Run Command 的返回值 */
enum eRUN_CMD_RESULT_CODE { RC_OK = 0, RC_ERROR, RC_SKIP, RC_WAIT,	   /* 等待 */ };

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
    游戏中逻辑指令基类
 -----------------------------------------------------------------------------------------------------------------------
 */
struct Command_Base
{
	/* 命令类型 */
	uint32_t mCommandSize;
	uint32_t	m_wID;
	GAME_CMD_TYPE	m_eType;

	/* 命令参数集合 */
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
    应用于object的命令
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
    应用于AI的命令
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
    应用于UI的命令
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
    挂在鼠标上的命令
 -----------------------------------------------------------------------------------------------------------------------
 */
struct MouseCmd :
	public Command_Base
{
	enum MOUSE_CMD_TYPE
	{
		MCT_NULL,
		MCT_PLAYER_MOVETO,			/* 移动到目标点 */

		/* fParam[0][1] = The position of target area */
		MCT_PLAYER_SELECT,			/* 选中物体 */

		/* uParam[0] = The ID of target object */
		MCT_SKILL_OBJ,				/* 点选目标的技能 */		
		//uParam[0] = The ID of skill ;
		//uParam[1] = The ID of target object ;

		MCT_SKILL_POS,				// 坐标技能 ;
		MCT_SKILL_CANCEL_POS,		// 取消坐标技能 ;

		MCT_SKILL_DIR,				//方向技能 ;
		//uParam[0] = The ID of skill ;
		//fParam[1] = The direction
		
		MCT_HIT_TRIPPEROBJ,			/* 放在能够操作的TripperObj上(矿物，箱子...) */

		/*
		 * uParam[0] = The ID of Tripper obj ;
		 * ...
		 */
		MCT_SPEAK,					/* 和NPC谈话 */

		/* uParam[0] = The ID of NPC */
		MCT_CONTEXMENU,				/* 显示右键菜单 */

		/* uParam[0] = The ID of NPC */
		MCT_REPAIR,					/* 修理指针 */
		MCT_CANCLE_REPAIR,			/* 修理指针 */

		MCT_USE_ITEM,				/* 物品使用 */

		/*
		 * pParam[0] = Action Item ;
		 * uParam[1] = The ID of target object ;
		 * fParam[2] = Pos X ;
		 * fParam[3] = Pos Z ;
		 * uParam[4] = Is area
		 */
		MCT_CANCEL_USE_ITEM,		/* 取消物品使用 */

		MCT_ENSNARE_MOUNT,			/* 捕捉坐骑 */
		MCT_CANT_ENSNARE_MOUNT,		/* 无法捕捉坐骑 鼠标在界面上的命令状态 */

		MCT_UI_USE_IDENTIFY,		/* 使用鉴定卷轴 */
		MCT_UI_USE_CANCEL_IDENTIFY, /* 取消使用鉴定卷轴 */

		MCT_ADD_FRIEND,				/* 添加好友 */
		MCT_CANCEL_ADD_FRIEND,
		MCT_EXCHANGE,				/* 交易 */

		MCT_ENTER_CHARIOT,			/* 进入战车 uParam[0] = The ID of NPC */

		/*
		 * MCT_MOOD_ANIM, 情感表情 ;
		 * MCT_CANCEL_MOOD_ANIM, 取消情感表?
		 */
		MCT_ENSNARE_BEASTIE,		/* 捕捉动物 */
		MCT_CANT_ENSNARE_BEASTIE,	/* 不可捕捉动物 */
		MCT_SPLIT,					/* 拆分指针 */
		MCT_CANCLE_SPLIT,			/* 拆分指针 */
		MCT_LOCKITEM,				/* 加锁指针 */
		MCT_CANCLE_LOCKITEM,		/* 加锁指针 */
		MCT_UNLOCKITEM,				/* 解锁指针 */
		MCT_CANCLE_UNLOCKITEM,		/* 解锁指针 */

		MCT_AUTO_MOVE,				// 自动行走
		MCT_CANCEL_AUTO_MOVE,
	};

	MouseCmd (void)
	{
		m_eType = GCT_MOUSE;
	}

	/* 鼠标命令类型 */
	MOUSE_CMD_TYPE	m_typeMouse;
};
