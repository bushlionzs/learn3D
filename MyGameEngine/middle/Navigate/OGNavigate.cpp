/********************************************************************
	created:	2008/03/05
	created:	5:3:2008   16:47
	file base:	Ne
	file ext:	cpp
	author:		½ªÍþ
	email:		jiang628@hotmail.com
	purpose:	
*********************************************************************/
#include "OgreHeader.h"
#include "OGNavigate.h"
#include "OGNavigateSpaceImp.h"
#include "OGNavigateImp.h"

namespace Orphigine 
{

NeSDK* NeCreateSDK()
{
	NeSDK* tmpSDK = new NeSDKImp();

	return tmpSDK;
}

bool NeRemoveSDK( NeSDK* pNesdk )
{
	if(pNesdk)
	{
		delete (NeSDKImp*)pNesdk;
		pNesdk = NULL;
		return true;
	}
	return false;
}
} // namespace Orphigine