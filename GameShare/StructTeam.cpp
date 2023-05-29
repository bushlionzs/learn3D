/*$T Common/StructTeam.cpp 2009/10/29 */


/*$6
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*/


#include "stdafx.h"
#include "StructTeam.h"

void CALL_UP_INVITE::Clear()
{
	m_nMapId = INVALID_ID;
	m_nPosX = 0;
	m_nPosZ = 0;
	m_nNeedLevel = 0;
}

uint32 CALL_UP_INVITE::GetSize() const
{
	return sizeof(m_nMapId) + sizeof(m_nPosX) + sizeof(m_nPosZ) + sizeof(m_nNeedLevel);
}




void XG_TEAM::Clear()
{
	m_nOpType	= 0;
	m_GUID		= INVALID_GUID;
}

uint32 XG_TEAM::GetSize() const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	uint32	uSize = sizeof(m_nOpType) + sizeof(m_GUID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	switch(m_nOpType)
	{
	case E_CALL_UP_INVITE:
		uSize += m_Invite.GetSize();
		break;
	case E_CALL_UP_ACCEPT:
		uSize += sizeof(m_nAcceptWho);
		break;
	default:
		break;
	}
	return uSize;
}



void GX_TEAM::Clear()
{
	m_nOpType = 0;
	m_nPlayerID = INVALID_ID;
}

uint32 GX_TEAM::GetSize() const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	uint32	uSize = sizeof(m_nOpType) + sizeof(m_nPlayerID);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	switch(m_nOpType)
	{
	case E_CALL_UP_INVITE:
		uSize += sizeof(m_nInviter);
		break;
	case E_CALL_UP_ACCEPT:
	case E_CALL_UP_ACTIVE_NOW:
		uSize += m_Accept.GetSize();
		break;
	default:
		break;
	}
	return uSize;
}




