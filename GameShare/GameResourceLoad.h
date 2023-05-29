#ifndef _GAME_RESOURCE_LOAD_H_
#define _GAME_RESOURCE_LOAD_H_

#include "OgreSingleton.h"
#include "KDefine.h"

class CResourceLoad :
	public Ogre::Singleton<CResourceLoad>
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	CResourceLoad(void);
	virtual					~CResourceLoad(void);

	static CResourceLoad	&GetSingleton(void);
	static CResourceLoad	*GetSingletonPtr(void);

	/* 初始化 */
	KHAN_RETURN_RESULT		Initialize(void);

	/* 更新 */
	KHAN_RETURN_RESULT		Update(void);

	/* 清除 */
	void					Release(void);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	/* 清除 */
	DWORD	Load(LPCTSTR szFileName, LPSTR &szMem, LPCTSTR szResGroup = NULL);
	BOOL	UnLoad(LPSTR szMem, DWORD dwSize);
};	/* class */
#define RESOURCE_SYS		CResourceLoad::GetSingleton()
#define RESOURCE_SYS_PTR	CResourceLoad::GetSingletonPtr()
#endif /* _GAME_RESOURCE_LOAD_H_ */
