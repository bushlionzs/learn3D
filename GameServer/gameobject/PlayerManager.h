/*$T MapServer/Server/Obj/HumanManager.h GC 1.140 10/10/07 10:07:31 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef __HUMANMANAGER_H__
#define __HUMANMANAGER_H__

#include "TypeDefine.h"
#include "map/ObjectSingleManager.h"

class	Player;
class PlayerManager :
	public ObjectSingleManager
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	PlayerManager(void);
	virtual ~PlayerManager(void);

	Player	*GetPlayer(ObjID_t idObj);
};
#endif
