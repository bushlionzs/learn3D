#pragma once

#include "kcharacter.h"
#include "GameTableData.h"
class KNpc : public KCharacter
{
public:
	KNpc();
	~KNpc();

	virtual void	SetServerGUID(GUID_t guid) 
	{ 
		m_GUIDServer = guid; 
	}
	virtual GUID_t	GetServerGUID(void) const
	{
		return m_GUIDServer;
	}

	virtual int32 AnalyseCharModel(void)const;
	virtual void UpdateCharBaseData(void);

	virtual void   OnQueryRay(GameEntity* entity);
private:
	GUID_t m_GUIDServer;
};