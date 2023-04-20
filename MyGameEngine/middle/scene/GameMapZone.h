#pragma once

#include "KDefine.h"

class	KObject;

class	CMapZone
{
public:
	CMapZone();
	virtual				~CMapZone();

	/* Zone��ʼ��������������Map��ʼ��ʱ���� */
	KHAN_RETURN_RESULT	Initialize(void *);

	/* ɾ��ָ�������� */
	bool RemoveRegion(int32 id);
public:
	std::set<int32> *GetRigisterObject()
	{
		return &m_setRegisterObject;
	};

	std::list<int32> *GetListRegion()
	{
		return &m_listRegion;
	};

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
private:
	/* ������Zone��Region */
	std::list<int32>	m_listRegion;

public:
	/* ע�ᵽ��Zone�ϵ�Object */
	std::set<int32>	m_setRegisterObject;

	void			AddRegion(int32 id);

	friend class CMap;
	friend class CMapPath;
	friend class KObject;
	friend class KAI_Player;
};
