/*$T MapServer/Server/Obj/ObjectManager.cpp GC 1.140 10/10/07 10:07:32 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include "stdafx.h"
#include "gameobject/Object.h"
#include "ObjectManager.h"

/*
 =======================================================================================================================
 =======================================================================================================================
 */

ObjectManager::ObjectManager(void)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	memset(m_pObj, 0, MAX_OBJID_SIZE * sizeof(Object *));
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_NormalPos = 0;
	m_HumanPos = HUMAN_OBJ_START;

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
ObjectManager::~ObjectManager(void)
{
	/*~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ uint32	i;
	/*~~~~~~~~~~~~~~~~~~~~~~*/

	for(i = 0; i < MAX_OBJID_SIZE; i++)
	{
		KCheck(m_pObj[i] == NULL && "ObjManager::~ObjectManager obj list not free");
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ObjectManager::Init(const _INIT_OBJECT_MAGAGER *pInit)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	memset(m_pObj, 0, MAX_OBJID_SIZE * sizeof(Object *));
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_NormalPos = 0;
	m_HumanPos = HUMAN_OBJ_START;

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void ObjectManager::Term(void)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	memset(m_pObj, 0, MAX_OBJID_SIZE * sizeof(Object *));
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	m_NormalPos = 0;
	m_HumanPos = HUMAN_OBJ_START;

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ObjectManager::AddObj(Object *pObj, eOBJ_ID_TYPE eIDType)
{
	__GUARD__ if(pObj == NULL) return FALSE;

	if(eIDType == OBJ_ID_TYPE_NORMAL)
	{
		m_pObj[m_NormalPos] = pObj;
		pObj->SetID(m_NormalPos);

		for(int32 i = 0; i < HUMAN_OBJ_START; i++)
		{
			m_NormalPos++;
			if(m_NormalPos >= HUMAN_OBJ_START) m_NormalPos = 0;
			if(m_pObj[m_NormalPos] == NULL) break;
		}
	}
	else if(eIDType == OBJ_ID_TYPE_HUMAN)
	{
		m_pObj[m_HumanPos] = pObj;
		pObj->SetID(m_HumanPos);

		for(int32 i = HUMAN_OBJ_START; i < MAX_OBJID_SIZE; i++)
		{
			m_HumanPos++;
			if(m_HumanPos >= MAX_OBJID_SIZE) m_HumanPos = HUMAN_OBJ_START;
			if(m_pObj[m_HumanPos] == NULL) break;
		}
	}
	else
	{
		return FALSE;
	}

	return TRUE;

	return FALSE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL ObjectManager::RemoveObj(ObjID_t idObj)
{
	__GUARD__ if(idObj == INVALID_ID || idObj >= MAX_OBJID_SIZE) return FALSE;

	if(m_pObj[idObj] == NULL) return FALSE;

	m_pObj[idObj]->SetID(INVALID_ID);
	m_pObj[idObj] = NULL;

	return TRUE;

	__UNGUARD__ return FALSE;
}
