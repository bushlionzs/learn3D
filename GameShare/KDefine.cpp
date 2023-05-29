
#include "OgreHeader.h"
#include "KDefine.h"



ku::CKU					gUtil;
const char				GAME_TAG[] = "-khantag-adebug";
String					g_strCmdLine = "";				
														
BOOL					g_bDebug		= FALSE;
BOOL					g_bDebugPackRes = FALSE;		/* 是否调试打包资源 */
BOOL					g_bGM			= FALSE;

/*
 * BOOL g_bLawless = FALSE;
 */
FLOAT					g_fVideoMem = 0.0f;
const FLOAT				g_fRequiredVideoMemory = 50.0f;


const char				DEBUG_FILE_NAME[] = ".\\Debug.cfg";
const char				LOGIN_FILE_NAME[] = "..\\User\\Login.cfg";
char*					SERVER_LIST_FILE_NAME = NULL;	// [] = "..\\Download\\Entrance.cfg"; /* "..\\Patch\\ServerList.cfg" */
int						g_nProcess = 1;

// 在线客服
const char				ONLINE_SERVICE_PATH[]	= ".\\IM800";
const char				ONLINE_SERVICE_EXE[]	= "DialogWindow.exe";
const char				ONLINE_SERVICE_INI[]	= "param.ini";

String					g_strKhanInfo;
