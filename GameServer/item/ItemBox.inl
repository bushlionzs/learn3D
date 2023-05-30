#ifndef _OBJ_ITEM_BOX_INL_
#define _OBJ_ITEM_BOX_INL_


void				ItemBox::SetItemBoxID( ObjID_t id )
{
	m_ItemBoxId = id ; 
} 
ObjID_t				ItemBox::GetItemBoxID( )
{
	return m_ItemBoxId ; 
} 


GUID_t				ItemBox::GetOwner()
{
	return m_OwnerId;
}
void				ItemBox::SetOwner(GUID_t id)
{
	m_OwnerId = id;
}




int32					ItemBox::GetType()	const
{
	return m_ItemBoxType;
};
void				ItemBox::SetType(int32	Type)
{
	m_ItemBoxType = Type;
};

BOOL				ItemBox::GetOpenFlag()
{	
	return m_OpenFlag;
}
void				ItemBox::SetOpenFlag(BOOL bFlag)
{ 
	m_OpenFlag = bFlag;
}

int32					ItemBox::GetRecycleTimes()
{
	return m_RecycleTimes;
}
void				ItemBox::SetRecycleTimes(int32 RecycleTimes)
{
	m_RecycleTimes = RecycleTimes;
}


uint32				ItemBox::GetMaxGrowTime()
{
	return m_MaxGrowTime;
}

inline void			ItemBox::SetPoolPos(uint32	iPos)
{
	m_nPoolPos	= iPos;
}
ItemContainer*		ItemBox::GetContainer()
{
	return	&m_Container;
}



#endif
