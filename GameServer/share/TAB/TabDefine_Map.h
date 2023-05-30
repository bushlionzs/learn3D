/*$T MapServer/TabDefine_Map.h GC 1.140 10/10/07 11:01:50 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef __TAB_DEFINE_MAP_H__
#define __TAB_DEFINE_MAP_H__

#include "TypeDefine.h"
#include "ScriptCacheMgr.h"


/*
 =======================================================================================================================
 =======================================================================================================================
 */
class TableInit_Map
{
public:
	TableInit_Map() {}
	~TableInit_Map() {}

	// º”‘ÿ±Ì
	BOOL	Init();

private:
	void	LoadBehavior_StateList();
	void	CleanUpBehavior_StateList();
	void	LoadBehavior_TemplateTable();

};

extern TableInit_Map g_TabInit_Map;

ScriptCache *GetScriptFileData(ScriptID_t idScript);

#endif
