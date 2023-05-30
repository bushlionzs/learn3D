#ifndef _CAMP_AND_STAND_H_
#define _CAMP_AND_STAND_H_

#include "TypeDefine.h"
#include "TabTemplateLoader.h"

namespace	TAB
{
class	TABFile;
} using namespace	TAB;
class		CampStandRecord
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	enum { MAX_ID = 31, MAX_SIZE = MAX_ID +1, };

	CampStandRecord();

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	~CampStandRecord()
	{
	};

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */
	BOOL IsInited(void) const
	{
		return m_bInited;
	};
	BOOL	InitFromDB(const TABFile *pDB, int32 const nRow);
	BOOL	StandByCampID(CampID_t const nCampID) const;

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
private:
	BOOL	m_bInited;
	BOOL	m_aStands[MAX_SIZE];
};


typedef class TemplateManager<CampStandRecord>	CampAndStandDataMgr;

struct _HUMAN_CAMP_DATA;
eRELATION Calc_RelationType
	(
		const _HUMAN_CAMP_DATA		*pCamp_A,
		const _HUMAN_CAMP_DATA		*pCamp_B,
		BOOL				bUsePKMode,
		const CampAndStandDataMgr	*pCampMgr
	);
eRELATION Calc_RelationType(CampID_t CampA, CampID_t CampB, const CampAndStandDataMgr *pCampMgr);	/* CZG Add */
#endif /* _CAMP_AND_STAND_H_ */
