#ifndef _GAME_TABLE_MANAGER_H_
#define _GAME_TABLE_MANAGER_H_

#include "GameSingleton.h"
#include "KDefine.h"

class CGameTable;

class CGameTableManager :
	public GameSingleton<CGameTableManager>
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	CGameTableManager(void);
	virtual ~CGameTableManager(void);

	KHAN_RETURN_RESULT			Initialize(void);
	void						Release(void);

	/* �õ�һ���ѽ��򿪵����ݿ⣬�������ݿ�ָ�� */
	const CGameTable			*GetTable(int32_t nTable) const;

	/* �������ݱ� */
	void						OpenAllTable(void);
	void						CloseAllTable(void);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	/* ���ݿ� */
	std::map<int32, CGameTable *> m_TableMap;
};	/* class */
#define GAME_TABLE_MANAGER		CGameTableManager::GetSingleton()
#define GAME_TABLE_MANAGER_PTR	CGameTableManager::GetSingletonPtr()
#endif /* _GAME_TABLE_MANAGER_H_ */
