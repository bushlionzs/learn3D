/*$T MapServer/Object.h GC 1.140 10/10/07 11:01:50 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef __OBJ_H__
#define __OBJ_H__

#include "TypeDefine.h"
#include "Util.h"


class NetPacket;
struct SCampData;
struct _INIT_OBJECT
{
	GLPos	m_Pos;
	float		m_Dir;
	_INIT_OBJECT (void)
	{
		m_Pos.Clear();
		m_Dir = 0.f;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	virtual void Clear(void)
	{
		m_Pos.Clear();
		m_Dir = 0.f;
	}
};

class		Object;
typedef struct _OBJLIST
{
	enum { MAX_OBJ_LIST_SIZE = 255, };
	Object *m_aObj[MAX_OBJ_LIST_SIZE];
	uchar m_Count;

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void Clear(void)
	{
		memset((void *) m_aObj, NULL, sizeof(m_aObj));
		m_Count = 0;
	}

	_OBJLIST()
	{
		Clear();
	};
}
OBJLIST;
typedef BitFlags<OBJLIST::MAX_OBJ_LIST_SIZE>	HitFlagsForOBJLIST_T;

struct _INIT_LIST_NODE;
class GameMap;
class IMessage;
class Object
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	enum ObjectClass:uint16_t
	{
		OBJECT_CLASS_INVALID,							/* ��Чֵ */
		OBJECT_CLASS_PLAYER,							/* ��� */
		OBJECT_CLASS_MONSTER,							/* ���� */
		OBJECT_CLASS_PET,								/* ����,�ٻ��� */
		OBJECT_CLASS_ITEM_BOX,							/* �ɼ��� */
		OBJECT_CLASS_DROP_ITEM,							/* ������Ʒ */
		OBJECT_CLASS_SPECIAL,							/* ����*/
		OBJECT_CLASS_HORSE,								/* ����OBJ */
		OBJECT_CLASS_BUS		= OBJECT_CLASS_HORSE + 2,	/* ö��ֵ�����仯��Ϊ������ű�һ�£����˴��� */
		OBJECT_CLASS_BEASTIE,							/* С���� */
		OBJECT_CLASS_NUMBERS
	};

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	Object();
	virtual ~Object();

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	virtual ObjectClass GetObjType(void) const
	{
		return OBJECT_CLASS_INVALID;
	}

	virtual void	OnEnterMap(void);

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	virtual void OnEnterMapSuccess(void)
	{
	} virtual void	OnLeaveMap(void);

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	virtual void OnRegisterToGrid(void)
	{
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	virtual void OnUnregisterFromGrid(void)
	{
	} 
	
	virtual void	Clear();
	virtual BOOL	Init(const _INIT_OBJECT *pInit);

	virtual bool	HeartBeat(uint32 uTime = 0);

	virtual BOOL	HeartBeat_OutMap(uint32 uTime = 0);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	ObjID_t GetID() const
	{
		return m_ObjID;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetID(ObjID_t id)
	{
		m_ObjID = id;
	}

	virtual uint32	GetUniqueID(void) const;

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	void SetPoolID(uint32 uID)
	{
		m_uPoolID = uID;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 GetPoolID(void) const
	{
		return m_uPoolID;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetSingleMgrIndex(uint32 uIndex)
	{
		m_uSingleMgrIndex = uIndex;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 GetSingleMgrIndex(void) const
	{
		return m_uSingleMgrIndex;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 GetLogicTime() const
	{
		return(m_uNowTime - m_uLastTime);
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 LastTime() const
	{
		return m_uLastTime;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 NowTime() const
	{
		return m_uNowTime;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 GetCreateTime() const
	{
		return m_uCreateTime;
	}

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
private:
	void	UpdateTime(uint32 uTime);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	virtual void OnEvent_KillObject(ObjID_t idObj)
	{
	} Object	*GetSpecificObjInSameSceneByID(ObjID_t nID);
	Object		*GetSpecificHumanInSameSceneByGUID(GUID_t nID);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	_INIT_LIST_NODE *ObjNode()
	{
		return m_pObjNode;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	virtual BOOL IsCanViewMe(const Object *pObj)
	{
		return TRUE;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	virtual BOOL IsCanViewHim(const Object *pObj)
	{
		return TRUE;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	virtual BOOL IsPrevCanViewMe(const Object *pObj)
	{
		return IsCanViewMe(pObj);
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	virtual BOOL IsPrevCanViewHim(const Object *pObj)
	{
		return TRUE;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	virtual BOOL IsStealthCanViewMe(const Object *pObj)
	{
		return TRUE;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	virtual BOOL IsStealthCanViewHim(const Object *pObj)
	{
		return TRUE;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	BOOL IsActiveObj() const
	{
		return(BOOL) m_bActive;
	}

	void	SetActiveFlag(BOOL bFlag);

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	const GLPos *GetGLPos() const
	{
		return &m_Pos;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetGLPos(const GLPos *pos);

	virtual void	Teleport(const GLPos *pos,uchar bShowChangeState = TRUE);

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	void SetDir(float dir);

	virtual void SetObjectDir(float dir);

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	float GetDir() const
	{
		return m_Dir;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetMap(GameMap *pMap)
	{
		m_pMap = pMap;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	GameMap*GetMap()
	{
		return m_pMap;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	void SetGridID(GridID_t zid)
	{
		m_GridID = zid;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	GridID_t GetGridID() const
	{
		return m_GridID;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	virtual void SetScriptID(ScriptID_t idScript)
	{
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	virtual ScriptID_t GetScriptID(void) const
	{
		return INVALID_ID;
	}

	BOOL	IsInValidRadius(float fX1, float fZ1, float fX2, float fZ2, float fRadius);
	BOOL	IsInValidRadius(const Object *pOb, float fRadius);
	BOOL	IsInValidRadius(const GLPos *pPos, float fRadius);

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	virtual BOOL IsInPKArea()
	{
		return FALSE;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	virtual const SCampData *GetCampData(void)
	{
		return NULL;
	}

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	uchar	GetLogicCount(void) const;
	void	AddLogicCount(void);
	int32	GetMoveLogicCount(void);
	void	AddMoveLogicCount(void);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	void	SetMoveLogicCount(int32 nLogicCount);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	virtual NetPacket	*CreateNewObjMsg(void) = 0;
	virtual void		DestroyNewObjMsg(NetPacket*pPacket) = 0;

	virtual NetPacket	*CreateDeleteObjPacket(void);
	virtual void		DestroyDeleteObjPacket(NetPacket*pPacket);

	BOOL			UpdateGrid(void);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
private:
	ObjID_t		m_ObjID;
	uint32		m_uPoolID;
	uint32		m_uSingleMgrIndex;
	_INIT_LIST_NODE	*m_pObjNode = nullptr;
	uchar		m_bActive;

	GLPos	m_Pos;
	float		m_Dir;
	GameMap		*m_pMap;
	GridID_t	m_GridID;
	uint32		m_uLastTime;
	uint32		m_uNowTime;
	uint32		m_uCreateTime;

	uchar		m_nLogicCount;
	int32		m_nMoveLogicCount;

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	virtual const MapID_t		GetMapID_i() const;
	virtual GameMap*GetMap_i();
	virtual void			SetMap_i(GameMap*scene);
	virtual const GridID_t		GetGridID_i() const;
	virtual void			SetGridID_i(const GridID_t zoneid);
	virtual const ScriptID_t	GetScriptID_i() const;
	virtual void			SetScriptID_i(const ScriptID_t scriptid);
	virtual const GLPos		*GetGLPos_i() const;
	virtual void			SetGLPos_i(const GLPos *worldpos);
	virtual const float		GetDir_i() const;
	virtual void			SetDir_i(const float dir);
	virtual const ObjID_t		GetID_i() const;
	virtual void			SetID_i(const ObjID_t id);
};

/*
 =======================================================================================================================
 =======================================================================================================================
 */

inline BOOL IsObjDynamic(Object::ObjectClass eType)
{
	switch(eType)
	{
	case Object::OBJECT_CLASS_PLAYER:
	case Object::OBJECT_CLASS_MONSTER:
	case Object::OBJECT_CLASS_PET:
	case Object::OBJECT_CLASS_HORSE:
	case Object::OBJECT_CLASS_BUS:
	case Object::OBJECT_CLASS_SPECIAL:
	case Object::OBJECT_CLASS_BEASTIE:
		return TRUE;

	case Object::OBJECT_CLASS_ITEM_BOX:
	case Object::OBJECT_CLASS_DROP_ITEM:
	default:
		return FALSE;
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
inline BOOL IsObjStatic(Object::ObjectClass eType)
{
	switch(eType)
	{
	case Object::OBJECT_CLASS_PLAYER:
	case Object::OBJECT_CLASS_MONSTER:
	case Object::OBJECT_CLASS_PET:
	case Object::OBJECT_CLASS_SPECIAL:
	case Object::OBJECT_CLASS_HORSE:
	case Object::OBJECT_CLASS_BUS:
	case Object::OBJECT_CLASS_BEASTIE:
		return FALSE;

	case Object::OBJECT_CLASS_ITEM_BOX:
	case Object::OBJECT_CLASS_DROP_ITEM:
	default:
		return TRUE;
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
inline BOOL IsObjCharacter(Object::ObjectClass eType)
{
	switch(eType)
	{
	case Object::OBJECT_CLASS_PLAYER:
	case Object::OBJECT_CLASS_MONSTER:
	case Object::OBJECT_CLASS_PET:
	case Object::OBJECT_CLASS_HORSE:
	case Object::OBJECT_CLASS_BUS:
	case Object::OBJECT_CLASS_BEASTIE:
		return TRUE;

	case Object::OBJECT_CLASS_SPECIAL:
	case Object::OBJECT_CLASS_ITEM_BOX:
	case Object::OBJECT_CLASS_DROP_ITEM:
	default:
		return FALSE;
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
inline BOOL IsObjSpecial(Object::ObjectClass eType)
{
	switch(eType)
	{
	case Object::OBJECT_CLASS_SPECIAL:
		return TRUE;

	case Object::OBJECT_CLASS_PLAYER:
	case Object::OBJECT_CLASS_MONSTER:
	case Object::OBJECT_CLASS_PET:
	case Object::OBJECT_CLASS_HORSE:
	case Object::OBJECT_CLASS_BUS:
	case Object::OBJECT_CLASS_ITEM_BOX:
	case Object::OBJECT_CLASS_DROP_ITEM:
	case Object::OBJECT_CLASS_BEASTIE:
	default:
		return FALSE;
	}
}
#endif