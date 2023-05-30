#ifndef _OBJ_ITEM_INL_
#define _OBJ_ITEM_INL_


void				ItemInstance::SetObj_ItemID( ObjID_t id )
{
	m_Obj_ItemId = id ; 
} 
ObjID_t				ItemInstance::GetObj_ItemID( )
{
	return m_Obj_ItemId ; 
} 

GUID_t		ItemInstance::GetOwner(int32 nPos)
{
	KCheck(nPos<=MAX_TEAM_MEMBER);
	return m_OwnerId[nPos];
}

void				ItemInstance::SetOwner(GUID_t owner)
{
	KCheck(m_OwnerCount<MAX_TEAM_MEMBER);

	m_OwnerId[m_OwnerCount]  = owner; 
	++m_OwnerCount;							
}

int32					ItemInstance::GetType()	const
{
	return m_Obj_ItemType;
};
void				ItemInstance::SetType(int32	Type)
{
	m_Obj_ItemType = Type;
};

int32					ItemInstance::GetRecycleTimes()
{
	return m_RecycleTimes;
}
void				ItemInstance::SetRecycleTimes(int32 RecycleTimes)
{
	m_RecycleTimes = RecycleTimes;
}

inline void			ItemInstance::SetPoolPos(uint32	iPos)
{
	m_nPoolPos	= iPos;
}
#endif
