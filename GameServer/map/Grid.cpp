/*********************************************************************************************
created:	10/10/07 10:07:26
filename: 	Grid.cpp
			file path:	F:\khan2\src\MapServer\Server\Map
			file base:
			file ext:	cpp
author:		
modified:	wujianping
purpose:	单个场景的管理方式 由类似矩阵的正方形格子组成的，其中每一个格子都有自己所在的行和列
			Grid就代表一个格子
			每一个Grid都存有处在该Grid中的玩家队列和obj队列
			场景使用这样的组织方式 是能快速的对obj进行查找和定位
			同时这种组织方式也为消息的广播提个了基础 所谓的3*3或者5*5的区域广播 指的都是Grid的阶数
**********************************************************************************************/

#include "stdafx.h"
#include "Grid.h"
#include "gameobject/Object.h"
#include "gameobject/Player.h"
/*
 =======================================================================================================================
 =======================================================================================================================
 */

Grid::Grid()
{
	/*~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	Clear();
	/*~~~~~~~~~~~~~~~~~~~~*/

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
Grid::~Grid()
{
	Clear();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Grid::Clear()
{
	__GUARD__ m_PlayerList.Clear();
	m_ObjList.Clear();
	m_AreaCount = 0;
	m_ZoneID = INVALID_ID;
	memset((void *) m_apArea, 0, sizeof(Region *) * MAX_AREA_IN_ZONE);

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Grid::OnEvent_ObjectEnter(Object *pObj)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ Object::ObjectClass	eObjType = pObj->GetObjType();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	switch(eObjType)
	{
	case Object::OBJECT_CLASS_PLAYER:
	case Object::OBJECT_CLASS_MONSTER:
	case Object::OBJECT_CLASS_PET:
	case Object::OBJECT_CLASS_HORSE:
	case Object::OBJECT_CLASS_BUS:
	case Object::OBJECT_CLASS_ITEM_BOX:
	case Object::OBJECT_CLASS_DROP_ITEM:
	case Object::OBJECT_CLASS_SPECIAL:
	case Object::OBJECT_CLASS_BEASTIE:
		{
			if(Object::OBJECT_CLASS_PLAYER == eObjType)
			{
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
				Player*pPlayer = (Player*) pObj;
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

				m_PlayerList.AddNode(pPlayer->HumanNode());

				int kk = 0;
			}

			_INIT_LIST_NODE* objnode = pObj->ObjNode();
			m_ObjList.AddNode(objnode);
		}
		break;

	default:
		KCheck(FALSE && "Grid::OnObjectEnter Unknow obj type");
		break;
	}

	return TRUE;
	__UNGUARD__
	return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Grid::OnEvent_ObjectLeave(Object *pObj)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ Object::ObjectClass	eObjType = pObj->GetObjType();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	switch(eObjType)
	{
	case Object::OBJECT_CLASS_PLAYER:
	case Object::OBJECT_CLASS_MONSTER:
	case Object::OBJECT_CLASS_PET:
	case Object::OBJECT_CLASS_HORSE:
	case Object::OBJECT_CLASS_BUS:
	case Object::OBJECT_CLASS_ITEM_BOX:
	case Object::OBJECT_CLASS_DROP_ITEM:
	case Object::OBJECT_CLASS_SPECIAL:
	case Object::OBJECT_CLASS_BEASTIE:
		{
			_NET_TRY
			{
				if(Object::OBJECT_CLASS_PLAYER == eObjType)
				{
					/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
					Player*pPlayer = (Player*) pObj;
					/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

					m_PlayerList.DeleteNode(pPlayer->HumanNode());
				}

				m_ObjList.DeleteNode(pObj->ObjNode());
			}
			_NET_CATCH
			{
				return FALSE;
			}
		}
		break;

	default:
		KCheck(FALSE && "Grid::OnObjectLeave Unknow obj type");
		break;
	}

	return TRUE;

	__UNGUARD__
	return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
const Region *Grid::GetCurrentArea(const GLPos *pWorldPos)
{
	/*~~~~~~~~~~~~~~~~~*/
	__GUARD__ float x, z;
	/*~~~~~~~~~~~~~~~~~*/

	x = pWorldPos->m_fX;
	z = pWorldPos->m_fZ;

	for(int32 i = 0; i < m_AreaCount; ++i)
	{
		if(m_apArea[i] != NULL && m_apArea[i]->IsContain(x, z))
		{
			return m_apArea[i];
		}
	}

	__UNGUARD__ return NULL;
}
