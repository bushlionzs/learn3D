/*$T MapServer/Server/Obj/Beastie/BeastieManager.h GC 1.140 10/10/07 10:07:27 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef _BEASTIE_MANAGER_H_
#define _BEASTIE_MANAGER_H_

#include "TypeDefine.h"
#include "ObjectSingleManager.h"
#include "gameobject/InitBeastieVisitor.h"

class	Beastie;
class BeastieManager :
	public ObjectSingleManager
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	friend class	Beastie;

	BeastieManager(void);
	virtual		~BeastieManager(void);

	void		Clear();

	virtual BOOL	HeartBeat(uint32 uTime = 0);

	Beastie		*GetBeastie(ObjID_t idObj);

	BOOL		LoadBeastie(MapID_t mapId);

	BOOL		RemoveAllBeastie(void);

	BOOL		RemoveBeastie(ObjID_t idObj);

	/*
	 ===============================================================================================================
	 ===============================================================================================================
	 */

	void SetMap(GameMap *pMap)
	{
		m_pMap = pMap;
	}

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	int32	GetRand(int32 iMin, int32 iMax);

	void	ClearRemoveArray(int32 *aNeedRemovePet);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
private:
	GameMap			*m_pMap;
	InitBeastieVisitor	m_BeastieVisitor;
};
#endif
