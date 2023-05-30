
#ifndef _GROWPOINT_MANAGER_INL_
#define _GROWPOINT_MANAGER_INL_

inline	void		TypeGatherPointManager::DecCurrentCount()
{
	m_CurrentCount--;
	KCheck(m_CurrentCount>=0);
}

inline	void		TypeGatherPointManager::SetIntervalSeed(uint32 time)
{
	for(int32 i=0;i<m_TypeCount;i++)
	{
		m_pData[i].SeedInterval = time;
	}	
}

inline	void		TypeGatherPointManager::SetCurrentSeedCount(int32 num)
{
	for(int32 i=0;i<m_TypeCount;i++)
	{
		m_pData[i].CurrSeedCount = num;
	}	
}

inline int32			TypeGatherPointManager::GetCurrentSeedCount(void)
{
	return m_pData[0].CurrSeedCount;
}

inline	void		TypeGatherPointManager::SetCurrentSeedElapse(uint32 time)
{
	for(int32 i=0;i<m_TypeCount;i++)
	{
		m_pData[i].CurrentElapse = time;
	}	
}

inline	void		TypeGatherPointManager::IncCurrentSeedCount(int32 index)
{
	m_pData[index].CurrSeedCount++;
}

inline	void		TypeGatherPointManager::DecCurrentSeedCount(int32 index)
{
	m_pData[index].CurrSeedCount--;
}


inline	uint16		TypeGatherPointManager::GetGatherPointType()
{
	return		m_GatherPointType;
}

inline	void	TypeGatherPointManager::AddData(GATHER_POINT_GROUPMAP_SETTING& RefData)
{
	if(!m_pData)
	{
		m_pData = new GATHER_POINT_GROUPMAP_SETTING[m_TypeCount];
		m_pObjID = new ObjID_t[m_TypeCount];
		memset( m_pObjID,INVALID_ID,sizeof(ObjID_t)*m_TypeCount );
	}

	KCheck(m_AddOffSet<m_TypeCount);

	m_pData[m_AddOffSet] = RefData;
	m_AddOffSet++;
}

inline	void			TypeGatherPointManager::SetCount(int32 count) 
{
		m_TypeCount = count;
}
inline	int32				TypeGatherPointManager::GetCount()
{
		return	m_TypeCount;
}

inline	void		TypeGatherPointManager::IncCount()
{
		m_TypeCount++;
}

inline	void		TypeGatherPointManager::IncCurrentCount()
{
		m_CurrentCount++;
		KCheck(m_CurrentCount<=m_MaxApperaCount);
}

inline	void		TypeGatherPointManager::SetGatherPointType(uint16 gpType)
{
	m_GatherPointType = gpType;
}

inline	void		TypeGatherPointManager::SetIntervalTime(uint32 iInterval)
{
	m_IntervalPerSeed = iInterval;
}

inline	void		TypeGatherPointManager::SetCurrentElapse(uint32 time)
{
	m_CurrentElapse = time;
}

inline	void		TypeGatherPointManager::SetEnable(BOOL flag)
{
	m_bEnable = flag;
}
inline	BOOL		TypeGatherPointManager::GetEnable()
{
	return m_bEnable;
}


#endif
