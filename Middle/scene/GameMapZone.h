#pragma once

class	KObject;

class	CMapZone
{
public:
	CMapZone();
	virtual				~CMapZone();

	/* Zone初始化，用于所属的Map初始化时调用 */
	bool	Initialize(void *);

	/* 删除指定的区域 */
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
	/* 经过该Zone的Region */
	std::list<int32>	m_listRegion;

public:
	/* 注册到该Zone上的Object */
	std::set<int32>	m_setRegisterObject;

	void			AddRegion(int32 id);

	friend class CMap;
	friend class CMapPath;
	friend class KObject;
	friend class KAI_Player;
};
