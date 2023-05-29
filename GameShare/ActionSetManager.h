#pragma once
#include "KDefine.h"
#include "TAB.h"
struct _TABLE_CHARACTER_ACTION_SET;

namespace TAB
{
	class TABFile;
};

class CDBActionSet
{
protected:
	static CDBActionSet		*m_pManagerActionSet;
public:
	static CDBActionSet *GetActionSetData( void ){
		return m_pManagerActionSet;
	}
public:
	CDBActionSet( void );
	virtual ~CDBActionSet( void );

	KHAN_RETURN_RESULT Initialize( String strResPath );
	void Clear( void );

	const _TABLE_CHARACTER_ACTION_SET *GetActionSet( std::string strFileName, uint32 dwID );
	const TAB::TABFile *GetActionSetFile(std::string strFileName);

protected:

	typedef std::unordered_map< std::string, TAB::TABFile* > CActionSetMap;

	CActionSetMap m_mapActionSet;

	String m_strResPath;
};

inline CDBActionSet *GetActionSetData( void ){
	return CDBActionSet::GetActionSetData();
}
