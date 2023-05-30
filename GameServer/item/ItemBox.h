/*$T MapServer/Server/Obj/ItemBox.h GC 1.140 10/10/07 10:07:31 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef _OBJ_ITEM_BOX_H_
#define _OBJ_ITEM_BOX_H_

#include "Item_Container.h"

struct ItemLogRecordInfo;

struct _INIT_ITEMBOX_OBJECT :
	public _INIT_OBJECT
{
	uint32	m_uCreateTime;
	uint32	m_uRecycleTime;
	BOOL	m_bRecycle;
	int32	m_ItemBoxType;

	_INIT_ITEMBOX_OBJECT (void)
	{
		Clear();
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	virtual void Clear(void)
	{
		_INIT_OBJECT::Clear();
		m_uCreateTime = 0;
		m_uRecycleTime = 0;
		m_ItemBoxType = 0;
		m_bRecycle = TRUE;
	}
};

class	Map;

class ItemBox :
	public Object
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	ItemBox();
	~	ItemBox();

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	friend class	GatherBoxPool;

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	virtual ObjectClass GetObjType(void) const
	{
		return OBJECT_CLASS_ITEM_BOX;
	}

	virtual void	Clear();
	virtual BOOL	Init(const _INIT_OBJECT *pInit);

	virtual bool	HeartBeat(uint32 uTime = 0);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	virtual NetPacket* CreateNewObjMsg(void);
	virtual void		DestroyNewObjMsg(NetPacket* pPacket);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	void	Recycle();

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	uint32 GetPoolPos()
	{
		return m_nPoolPos;
	};

	SItem		*GetItem(uchar itemIndex);
	void		EraseItem(uchar itemIndex);
	void		SetItemCount(uchar itemCount);
	uchar		GetItemCount();
	void		SetItemBoxData(SItem *pData);
	const SItem	*GetItemBoxData();

	int32		AddItem(SItemBoxContaner *pContain, int32 nDestIndex);
	BOOL		CreateItem(ItemLogRecordInfo *pLogParam, uint32 uItemType, uint32 uQuality);

	inline void	SetItemBoxID(ObjID_t id);
	inline ObjID_t	GetItemBoxID();

	inline GUID_t	GetOwner();
	inline void	SetOwner(GUID_t id);

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	inline void SetDropMonsterID(ObjID_t nID)
	{
		m_MonsterID = nID;
	}

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	ObjID_t GetDropMonsterID()
	{
		return m_MonsterID;
	}

	inline int32		GetType() const;
	inline void		SetType(int32 Type);
	inline BOOL		GetOpenFlag();
	inline void		SetOpenFlag(BOOL bFlag);
	inline int32		GetRecycleTimes();
	inline void		SetRecycleTimes(int32 RecycleTimes);
	void			Set_Property_MaxGrowTime(uint32 uGrowTime);
	inline uint32		GetMaxGrowTime();
	BOOL			CanPickBox(GUID_t PickerID, ObjID_t HumanID);
	virtual BOOL		IsCanViewMe(const Object *pObj);
	void			EnablePickOwnerTime();
	void			SetPickOwnerTime(uint32 uPickTime);

	inline ItemContainer	*GetContainer();

	virtual ScriptID_t	GetScriptID() const;

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
private:
	inline void	SetPoolPos(uint32 iPos);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
private:
	uint32		m_nPoolPos;
	GUID_t		m_OwnerId;
	ObjID_t		m_MonsterID;
	TeamID_t	m_OwnerTeam;
	ObjID_t		m_ItemBoxId;
	uchar		m_ItemCount;
	SItem		m_ItemList[MAX_BOXITEM_NUMBER];
	IPC		m_IPCList[MAX_BOXITEM_NUMBER];
	int32		m_ItemBoxType;
	int32		m_RecycleTimes;

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
private:
	BOOL		m_OpenFlag;
	int32		m_MaxGrowTime;
	CTinyTimer	m_LifeTimer;
	int32		m_PickOwnerTime;
	int32		m_FinalPickTime;

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
private:
	CTinyTimer	m_RecycleTimer;
	uint32		m_CreateTime;
	uint32		m_RecycleTime;

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
private:
	ItemContainer	m_Container;
};

#include "ItemBox.inl"
#endif
