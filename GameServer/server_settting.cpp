/*$T MapServer/Server/Base/Config.cpp GC 1.140 10/10/07 10:07:20 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#include "stdafx.h"
#include "server_settting.h"
#include "BaseTool.h"
#include "FileDef.h"
#include "TAB.h"
#include "SplitStringLevelOne.h"


using namespace TAB;
SettingSystem	g_Config;

#if ( defined(__LINUX__) && (defined(__MAPSERVER__) || defined(__GLSERVER__)) )
#include "udpsender.h"
CUdpSender g_UdpSender;
#endif

BOOL DecodeDBPassword( const char* pIn, char* pOut )
{
	char pOut_Binary[DB_USE_STR_LEN*2+2] = {0};
	int32 idx = 0;
	uint32 OutLenTmp = 0;
	
	int32 nStartIndex = pIn[0] % (DB_USE_STR_LEN*2+2);
	if( nStartIndex == 0 )
		nStartIndex = 1;
	
	char szLen_Binary[3] = {0};
	szLen_Binary[0] = pIn[DB_USE_STR_LEN*2];
	szLen_Binary[1] = pIn[DB_USE_STR_LEN*2+1];
	char PassLen;
	
	Str2Binary( szLen_Binary, 2, (char*)&PassLen, 2, OutLenTmp );
	
	memset( pOut_Binary, 0, DB_USE_STR_LEN*2+2 );
	for( int i=nStartIndex; idx<PassLen*2; i++ )
	{
		if( i>=DB_USE_STR_LEN*2 )
			i = 1;
		pOut_Binary[idx] = pIn[i];
		idx++;
	}

	Str2Binary( pOut_Binary, strlen(pOut_Binary), pOut, DB_USE_STR_LEN*2+2, OutLenTmp );

	return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
SettingSystem::SettingSystem()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	memset(m_LogPath, 0, sizeof(m_LogPath));
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
SettingSystem::~SettingSystem()
{
	__GUARD__ __UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SettingSystem::Init()
{
	__GUARD__	

	LoadWorldIndexConfig();
	LoadServerIndexConfig();
	LoadBaseServerConfig();
	LoadDBShareConfig();
	LoadExtServerConfig();
	LoadMultiGroupConfig();
	LoadDBConfig();
	LoadGameConfig();
	LoadGameToggleConfig();
	LoadLogServerConfig();

	PrintAllConfigInfo();

	LoadMapData();
	LoadMonitorInfo();

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SettingSystem::InitLog(const char *LogPtr)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(LogPtr);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	strncpy(m_LogPath, LogPtr, 255 - 1);
	return TRUE;
	__UNGUARD__ return FALSE;
}

/*
=======================================================================================================================
 加载GLServer索引信息
=======================================================================================================================
*/
void SettingSystem::LoadWorldIndexConfig()
{
	__GUARD__ 

	Configer ini(FILE_WORLDINDEX);
	m_WorldInfo.m_WorldID = ini.Get_Property_Int("System", "GLServerID");

	__UNGUARD__
}

/*
=======================================================================================================================
 加载服务器基本配置信息，主要是IP，Port
=======================================================================================================================
*/
void SettingSystem::LoadBaseServerConfig()
{
	__GUARD__ 

	Configer	ini(FILE_BASESERVERCONFIG);

	// GLServer
	ini.GetText("GLServer", "IP", m_ServerInfo.m_World.m_IP, IP_SIZE);
	m_ServerInfo.m_World.m_Port = (uint32) (ini.Get_Property_Int("GLServer", "Port"));
	// AUServer
	ini.GetText("AUServer", "IP", m_ServerInfo.m_Auth.m_IP, IP_SIZE);
	m_ServerInfo.m_Auth.m_Port = (uint32) (ini.Get_Property_Int("AUServer", "Port"));
	// DBCenter
	ini.GetText("DBCenter", "IP", m_DBCenterInfo.m_IP, IP_SIZE);
	m_DBCenterInfo.m_Port = (uint32) (ini.Get_Property_Int("DBCenter", "Port"));
	// Billing
	ini.GetText("Billing", "IP", m_BillingInfo.m_IP, IP_SIZE);
	m_BillingInfo.m_Port = (uint32) (ini.Get_Property_Int("Billing", "Port"));

	m_ServerInfo.m_ServerCount = ini.Get_Property_Int("System", "ServerNumber");
	m_ServerInfo.m_pServer = new SERVER_DATA[m_ServerInfo.m_ServerCount];
	memset(m_ServerInfo.m_pServer, 0, sizeof(SERVER_DATA) * m_ServerInfo.m_ServerCount);

	uint32 i;
	for(i = 0; i < m_ServerInfo.m_ServerCount; i++)
	{
		char	szSection[256];
		memset(szSection, 0, 256);
		m_ServerInfo.m_pServer[i].Init();
		sprintf(szSection, "Server%d", i);
		m_ServerInfo.m_pServer[i].m_ServerID = (ID_t) (ini.Get_Property_Int(szSection, "ServerID"));
		m_ServerInfo.m_pServer[i].m_MachineID = (ID_t) (ini.Get_Property_Int(szSection, "MachineID"));
		ini.GetText(szSection, "IP", m_ServerInfo.m_pServer[i].m_IP, IP_SIZE);
		m_ServerInfo.m_pServer[i].m_Port = (uint32) (ini.Get_Property_Int(szSection, "Port"));
		m_ServerInfo.m_pServer[i].m_Type = (uint32) (ini.Get_Property_Int(szSection, "Type"));
	}

	for(i = 0; i < m_ServerInfo.m_ServerCount; i++)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		ID_t	ServerID = m_ServerInfo.m_pServer[i].m_ServerID;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		KCheck(ServerID != INVALID_ID && ServerID < SERVER_CAPACITY);

		KCheck(m_ServerInfo.m_HashServer[ServerID] == -1);

		m_ServerInfo.m_HashServer[ServerID] = i;
	}

	__UNGUARD__
}

/*
=======================================================================================================================
 加载服务器扩展配置信息，主要时SMU Key
=======================================================================================================================
*/
void SettingSystem::LoadExtServerConfig()
{
	__GUARD__ 

	Configer	ini(FILE_EXTSERVERCONFIG);
	uint32 i;

	// DBCenter
	m_DBCenterInfo.m_DBCenterID = (ID_t) (ini.Get_Property_Int("DBCenter", "DBCenterID"));
	m_DBCenterInfo.m_DBCenterUserCount = (uint32) (ini.Get_Property_Int("DBCenter", "DBUserCount"));

	// Login
	m_LoginInfo.m_LoginID = (ID_t) (ini.Get_Property_Int("Login", "LoginID"));
	m_LoginInfo.m_MaxClientInSameIP = ini.Get_Property_Int("Login", "MaxClientInSameIP");
	m_LoginInfo.m_CheckAnswer = ini.Get_Property_Int("Login", "CheckAnswer");
	m_LoginInfo.m_EncryptToggle = ini.Get_Property_Int("Login", "EncryptToggle");
	m_LoginInfo.m_RsaToggle = ini.Get_Property_Int("Login", "RsaToggle");
	m_LoginInfo.m_AutoEncryptToggle = ini.Get_Property_Int("Login", "AutoEncryptToggle");
	m_LoginInfo.m_uLoginCountSameIPPerDay = ini.Get_Property_Int("Login", "LoginCountSameIPPerDay");
	m_LoginInfo.m_uLoginCountPerDay = ini.Get_Property_Int("Login", "LoginCountPerDay");
	for(i = 0; i < VALID_ENCRYPT_ARITH_NUM; i++)
	{
		char	arithId[32] = { 0 };
		sprintf(arithId, "EncryptAriths%d", i + 1);
		m_LoginInfo.m_EncryptArith[i] = ini.Get_Property_Int("Login", arithId);
	}

	// DBShare
	m_ShareMemInfo.MKInterval = ini.Get_Property_Int("DBShare", "SMUInterval");
	m_ShareMemInfo.DATAInterval = ini.Get_Property_Int("DBShare", "DATAInterval");

	// GLServerSMU Common
	m_WorldInfo.m_EnableShareMem = (BOOL) ini.Get_Property_Int("GLServerSMU", "EnableShareMem");
	m_WorldInfo.m_GuildKey = (MK_VALUE) ini.Get_Property_Int("GLServerSMU", "GuildSMKey");
	m_WorldInfo.m_MailKey = (MK_VALUE) ini.Get_Property_Int("GLServerSMU", "MailSMKey");
	m_WorldInfo.m_CountryKey = (MK_VALUE) ini.Get_Property_Int("GLServerSMU", "CountrySMKey");
	m_WorldInfo.m_SceneVarKey = (MK_VALUE) ini.Get_Property_Int("GLServerSMU", "SceneVarSMKey");
	m_WorldInfo.m_TopListKey = (MK_VALUE) ini.Get_Property_Int("GLServerSMU", "TopListSMKey");
	m_WorldInfo.m_ShopKey = (MK_VALUE) ini.Get_Property_Int("GLServerSMU", "ShopSMKey");
	m_WorldInfo.m_BankKey = (MK_VALUE) ini.Get_Property_Int("GLServerSMU", "BankSMKey");
	m_WorldInfo.m_MasterCandidateKey = (MK_VALUE) ini.Get_Property_Int("GLServerSMU", "MasterCandidateSMKey");
	m_WorldInfo.m_PrenticeCandidateKey = (MK_VALUE) ini.Get_Property_Int("GLServerSMU", "PrenticeCandidateSMKey");

	m_WorldInfo.m_StockCandidateKey = (MK_VALUE) ini.Get_Property_Int("GLServerSMU", "StockCandidateSMKey");
	m_WorldInfo.m_StockAccCandidateKey = (MK_VALUE) ini.Get_Property_Int("GLServerSMU", "StockAccCandidateSMKey");
	m_WorldInfo.m_StockRecordCandidateKey = (MK_VALUE) ini.Get_Property_Int("GLServerSMU", "StockRecordCandidateSMKey");
	m_WorldInfo.m_DynamicShopKey = (MK_VALUE) ini.Get_Property_Int("GLServerSMU", "DynamicShopSMKey");

	// MapServerSMU Common
	for(i = 0; i < m_ServerInfo.m_ServerCount; i++)
	{
		char	szSection[256];
		memset(szSection, 0, 256);
		sprintf(szSection, "MapServerSMU%d", i);

		m_ServerInfo.m_pServer[i].m_EnableDBShare = (BOOL) (ini.Get_Property_Int(szSection, "EnableShareMem"));
		m_ServerInfo.m_pServer[i].m_HumanSMKey = (MK_VALUE) (ini.Get_Property_Int(szSection, "HumanSMKey"));
		m_ServerInfo.m_pServer[i].m_ItemSerialKey = (MK_VALUE) (ini.Get_Property_Int(szSection, "ItemSerialKey"));
	}

	// SMU Key and Type of GLServer or MapServer
	char	szSection[256] = {0};
	if(0 == m_DBShareConfig.m_uShareType) // 0--MapServer，1--GLServer
		tsnprintf_s(szSection, 256, "MapServerSMU%d", m_ConfigInfo.m_ServerID);
	else if(1 == m_DBShareConfig.m_uShareType)
		tsnprintf_s(szSection, 256, "%s", "GLServerSMU");

	m_ShareMemInfo.m_MKObjCount = (uint32) ini.Get_Property_Int(szSection, "KeyCount");
	m_ShareMemInfo.m_pShareData = new SSharememData[m_ShareMemInfo.m_MKObjCount];
	for(i = 0; i < m_ShareMemInfo.m_MKObjCount; i++)
	{
		char	szKeyID[256];
		char	szTypeID[256];
		memset(szKeyID, 0, 256);
		memset(szTypeID, 0, 256);
		sprintf(szKeyID, "Key%d", i);
		sprintf(szTypeID, "Type%d", i);
		m_ShareMemInfo.m_pShareData[i].m_Key = (MK_VALUE) ini.Get_Property_Int(szSection, szKeyID);
		m_ShareMemInfo.m_pShareData[i].m_Type = (eSHM_TYPE) ini.Get_Property_Int(szSection, szTypeID);
	}

	__UNGUARD__

}

/*
=======================================================================================================================
 加载跨服配置信息
=======================================================================================================================
*/
void SettingSystem::LoadMultiGroupConfig()
{
	__GUARD__

	Configer	ini(FILE_MULTIGROUPCONFIG);

	m_MultiGroupConfig.m_nGroupCount = ini.Get_Property_Int( "System", "GroupCount" );

	// 2010-12-9 by rj 检测读入数量必须在 MULTI_GROUP_MAX_COUNT 以内
	KCheckEx(m_MultiGroupConfig.m_nGroupCount >= 0 && m_MultiGroupConfig.m_nGroupCount <= MULTI_GROUP_MAX_COUNT, 
		"GroupCount 读入数量必须小于等于 MULTI_GROUP_MAX_COUNT");

	// 跨服战场最大场景数量配置 2010-9-23 by rj
	m_MultiGroupConfig.m_nMax2v2SceneCnt = ini.Get_Property_Int("PvP2v2", "Max_SceneCount");
	m_MultiGroupConfig.m_nMax6v6SceneCnt = ini.Get_Property_Int("PvP6v6", "Max_SceneCount");

	for( int32 i=0; i<m_MultiGroupConfig.m_nGroupCount; i++ )
	{
		char szSection[256];
		memset(szSection, 0, 256);
		sprintf(szSection, "Group%d", i);

		ini.GetText( szSection, "dbc_ip", m_MultiGroupConfig.m_DBCenterInfo[i].m_IP, IP_SIZE );
		m_MultiGroupConfig.m_DBCenterInfo[i].m_Port = ini.Get_Property_Int( szSection, "dbc_port" );
		m_MultiGroupConfig.m_DBCenterInfo[i].m_WorldID = ini.Get_Property_Int( szSection, "dbc_worldid" );

		ini.GetText( szSection, "gl_ip", m_MultiGroupConfig.m_GLServerInfo[i].m_IP, IP_SIZE );
		m_MultiGroupConfig.m_GLServerInfo[i].m_Port = ini.Get_Property_Int( szSection, "gl_port" );
		m_MultiGroupConfig.m_GLServerInfo[i].m_WorldID = ini.Get_Property_Int( szSection, "gl_worldid" );
		
		// 增加跨服 MAP 回退 MAP ip port 支持 2010-10-19 by rj

		char szMapIdString[128] = "", szMapIpString[512] = "", szMapPortString[128] = "";

		ini.GetText(szSection, "backmap_idlist", szMapIdString, 128);
		ini.GetText(szSection, "backmap_iplist", szMapIpString, 512);
		ini.GetText(szSection, "backmap_portlist", szMapPortString, 128);

		char *pMapIdFind = szMapIdString, *pMapIpFind = szMapIpString, *pMapPortFind = szMapPortString;
		char *pMapIdThis, *pMapIpThis, *pMapPortThis;

		// 分割字符串
		while(pMapIdFind && pMapIpFind && pMapPortFind && strlen(pMapIdFind) && strlen(pMapIpFind) && strlen(pMapPortFind))
		{
			pMapIdThis = strstr(pMapIdFind, ",");
			pMapIpThis = strstr(pMapIpFind, ",");
			pMapPortThis = strstr(pMapPortFind, ",");

			if (pMapIdThis && pMapIpThis && pMapPortThis)
			{
				*pMapIdThis = '\0';
				*pMapIpThis = '\0';
				*pMapPortThis = '\0';
			}

			int nIdx = atoi(pMapIdFind);

			// 索引有效性
			KCheck(nIdx >= 0 && nIdx < PERGROUP_MAX_MAPCOUNT);

			// 去 ip 前面的空格
			while (*pMapIpFind == ' ')
			{
				pMapIpFind++;
			}

			strncpy(m_MultiGroupConfig.m_GLServerInfo[i].m_aBackMapIp[nIdx], pMapIpFind, 24 - 1);
			m_MultiGroupConfig.m_GLServerInfo[i].m_aBackMapPort[nIdx] = atoi(pMapPortFind);

			QLogSystem::SLOW_LOG
				(
				SLOW_LOG_SERVER,
				"LoadMultiGroupConfig WorldID = %d, MapServerID = %d, MapServerIp = %s, MapServerPort = %d",
				m_MultiGroupConfig.m_GLServerInfo[i].m_WorldID,
				nIdx,
				m_MultiGroupConfig.m_GLServerInfo[i].m_aBackMapIp[nIdx],
				m_MultiGroupConfig.m_GLServerInfo[i].m_aBackMapPort[nIdx]
				);

			// 三条都必须满足找到 , 才继续向下找
			if (pMapIdThis && pMapIpThis && pMapPortThis)
			{
				pMapIdFind = pMapIdThis + 1;
				pMapIpFind = pMapIpThis + 1;
				pMapPortFind = pMapPortThis + 1;
			}
			else
			{
				// 三条；配置不匹配也一样会舍弃掉一个字段列，保留之前有效列
				break;
			}
		}		
	}

	__UNGUARD__
}

/*
=======================================================================================================================
 加载服务器DB基本配置信息
=======================================================================================================================
*/
void SettingSystem::LoadDBConfig()
{
	__GUARD__ 

	Configer	ini(FILE_DBCONFIG);

	char szDBIP[IP_SIZE] = {0};
	char szDBName[DATABASE_STR_LEN] = {0};
	char szDBUser[DB_USE_STR_LEN] = {0};
	char szPassword[DB_USE_STR_LEN*2+3] = {0};
	char szPassword_Decoded[DB_USE_STR_LEN] = {0};
	uint32 uDBPort;

	ini.GetText("System", "DBIP", szDBIP, IP_SIZE);
	uDBPort = (uint32) (ini.Get_Property_Int("System", "DBPort"));
	ini.GetText("System", "DBName", szDBName, DATABASE_STR_LEN);
	ini.GetText("System", "DBUser", szDBUser, DB_USE_STR_LEN);
	ini.GetText("System", "DBPassword", szPassword, DB_USE_STR_LEN*2+3);

	DecodeDBPassword( szPassword, szPassword_Decoded );

	// 简单进行赋值
	tsnprintf_s(m_LoginInfo.m_DBIP, IP_SIZE, "%s", szDBIP);
	tsnprintf_s(m_LoginInfo.m_DBName, DATABASE_STR_LEN, "%s", szDBName);
	tsnprintf_s(m_LoginInfo.m_DBUser, DB_USE_STR_LEN, "%s", szDBUser);
	tsnprintf_s(m_LoginInfo.m_DBPassword, DB_PASSWORD_STR_LEN, "%s", szPassword_Decoded);
	m_LoginInfo.m_DBPort = uDBPort;

	tsnprintf_s(m_DBCenterInfo.m_DBIP, IP_SIZE, "%s", szDBIP);
	tsnprintf_s(m_DBCenterInfo.m_DBName, DATABASE_STR_LEN, "%s", szDBName);
	tsnprintf_s(m_DBCenterInfo.m_DBUser, DB_USE_STR_LEN, "%s", szDBUser);
	tsnprintf_s(m_DBCenterInfo.m_DBPassword, DB_PASSWORD_STR_LEN, "%s", szPassword_Decoded);
	m_DBCenterInfo.m_DBPort = uDBPort;

	tsnprintf_s(m_ShareMemInfo.m_DBIP, IP_SIZE, "%s", szDBIP);
	tsnprintf_s(m_ShareMemInfo.m_DBName, DATABASE_STR_LEN, "%s", szDBName);
	tsnprintf_s(m_ShareMemInfo.m_DBUser, DB_USE_STR_LEN, "%s", szDBUser);
	tsnprintf_s(m_ShareMemInfo.m_DBPassword, DB_PASSWORD_STR_LEN, "%s", szPassword_Decoded);
	m_ShareMemInfo.m_DBPort = uDBPort;
    
	// ... (Billing) -->
	tsnprintf_s(m_BillingInfo.m_DBIP, IP_SIZE, "%s", szDBIP);
	tsnprintf_s(m_BillingInfo.m_DBName, DATABASE_STR_LEN, "%s", szDBName);
	tsnprintf_s(m_BillingInfo.m_DBUser, DB_USE_STR_LEN, "%s", szDBUser);
	tsnprintf_s(m_BillingInfo.m_DBPassword, DB_PASSWORD_STR_LEN, "%s", szPassword_Decoded);
	m_BillingInfo.m_DBPort = uDBPort;
	// <--

	__UNGUARD__

}

/*
=======================================================================================================================
 加载服务器DBShare的类型和索引信息
=======================================================================================================================
*/
void SettingSystem::LoadDBShareConfig()
{
	__GUARD__ 

	Configer	ini(FILE_DBSHARECONFIG);

	m_DBShareConfig.m_uShareType = ini.Get_Property_Int("System", "DBShareType");

	__UNGUARD__

}

/*
=======================================================================================================================
 加载MapServer索引信息，
=======================================================================================================================
*/
void SettingSystem::LoadServerIndexConfig()
{
	__GUARD__ 

	Configer	ini(FILE_SERVERINDEX);

	m_ConfigInfo.m_ServerID = ini.Get_Property_Int("System", "ServerIndex");

	__UNGUARD__

}

void SettingSystem::LoadGameToggleConfig()
{
	__GUARD__

	Configer	ini(FILE_GAMETOGGLE);
	// 开关选项部分
	m_ConfigInfo.m_PWCardEnable = ini.Get_Property_Int("Toggle", "PWCardEnable");
	m_ConfigInfo.m_MergeDBToggle = ini.Get_Property_Int("Toggle", "MergeDBToggle");
	m_ConfigInfo.m_TestServerToggle = ini.Get_Property_Int("Toggle", "TestServerToggle");
	m_ConfigInfo.m_GuildBattleToggle = ini.Get_Property_Int("Toggle", "GuildBattleToggle");
	m_ConfigInfo.m_KingBattleToggle = ini.Get_Property_Int("Toggle", "KingBattleToggle");
	m_ConfigInfo.m_CountryBattleToggle = ini.Get_Property_Int("Toggle", "CountryBattleLiteToggle");
	m_ConfigInfo.m_ZhuQueBattleToggle = ini.Get_Property_Int("Toggle", "ZhuQueBattleToggle");
	m_ConfigInfo.m_QingLongBattleToggle = ini.Get_Property_Int("Toggle", "QingLongBattleToggle");
	m_ConfigInfo.m_LairdBattleToggle = ini.Get_Property_Int("Toggle", "LairdBattleToggle");

	m_ConfigInfo.m_WorldCupToggle = ini.Get_Property_Int("Toggle", "WorldCupToggle");
	m_ConfigInfo.m_PVP2v2BattleToggle = ini.Get_Property_Int("Toggle", "PVP2v2BattleToggle");
	m_ConfigInfo.m_PVP6v6BattleToggle = ini.Get_Property_Int("Toggle", "PVP6v6BattleToggle");
	m_ConfigInfo.m_nToggleDebugBehavior_Template = ini.Get_Property_Int("Toggle", "ToggleDebugAITemplate");
	m_ConfigInfo.m_nMoneyExchangeFlag = ini.Get_Property_Int("Toggle", "MoneyExchangeFlag");
	m_ConfigInfo.m_nGoldStall = ini.Get_Property_Int("Toggle", "GoldStall");
	m_ConfigInfo.m_WorldGoldShopToggle = ini.Get_Property_Int("Toggle", "WorldGoldShopToggle");
	m_ConfigInfo.m_TestGoldShopToggle = ini.Get_Property_Int("Toggle", "TestGoldShopToggle");
	m_ConfigInfo.m_nUpdateDBBefore = ini.Get_Property_Int("Toggle", "UpdateDBBefore");
	m_ConfigInfo.m_nUpdateDBAfter = ini.Get_Property_Int("Toggle", "UpdateDBAfter");
	m_ConfigInfo.m_nQMoneyToggle = ini.Get_Property_Int("Toggle", "QMoneyToggle");
	m_ConfigInfo.m_uEnableCreateNewChar = ini.Get_Property_Int("Toggle", "EnableCreateNewChar");

	m_ConfigInfo.m_nToggleDebugInherenceBalance = ini.Get_Property_Int("Toggle", "ToggleDebugIherenceBalance");
	m_ConfigInfo.m_nToggleDebugInherenceZhuanjing = ini.Get_Property_Int("Toggle", "ToggleDebugIherenceZhuanjing");

	m_ConfigInfo.m_nOpenWeakCountryCheck = ini.Get_Property_Int("Toggle", "OpenWeakCountryCheck");
	m_ConfigInfo.m_nToggleCountryColleague = ini.Get_Property_Int("Toggle", "ToggleCountryColleague");

__UNGUARD__
}

/*
=======================================================================================================================
加载游戏全局信息
=======================================================================================================================
*/
void SettingSystem::LoadGameConfig()
{
	__GUARD__ 

		Configer	ini(FILE_GAMECONFIG);

	m_ConfigInfo.m_SystemMode = ini.Get_Property_Int("System", "SystemMode");

	m_ConfigInfo.m_ZoneSize = ini.Get_Property_Int("Zone", "ZoneSize");
	m_ConfigInfo.m_MaxPortal = ini.Get_Property_Int("Portal", "MaxCount");
	m_ConfigInfo.m_MaxSkillObj = ini.Get_Property_Int("SkillObj", "MaxCount");
	m_ConfigInfo.m_MaxPlatform = ini.Get_Property_Int("Platform", "MaxCount");
	m_ConfigInfo.m_MaxSpecial = ini.Get_Property_Int("SpecialObj", "MaxCount");
	m_ConfigInfo.m_MaxPlayerShopNum = ini.Get_Property_Int("PlayerShop", "MaxCount");
	m_ConfigInfo.m_MaxTimerCount = ini.Get_Property_Int("SceneTimer", "MaxCount");
	m_ConfigInfo.m_nMaxHumanUseTimer = ini.Get_Property_Int("HumanTimer", "MaxCount");
	m_ConfigInfo.m_nCompressPacket = ini.Get_Property_Int("Global", "CompressPacket");
	m_ConfigInfo.m_nCompressGlobalLog = ini.Get_Property_Int("Global", "CompressGlobalLog");
	m_ConfigInfo.m_nMapThreadCount = ini.Get_Property_Int("Global", "MapThreadCount");
	m_ConfigInfo.m_nEnableRandEncryptKey = ini.Get_Property_Int("Global", "RandEncryptKey");

	char		szText[32];
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	ini.GetText("Global", "DropParam", szText, sizeof(szText) - 1);
	m_ConfigInfo.m_DropParam = (float) (atof(szText));

	ini.GetText("Global", "ExpParam", szText, sizeof(szText) - 1);
	m_ConfigInfo.m_ExpParam = (float) (atof(szText));
	m_ConfigInfo.m_EquipmentDamagePoint = ini.Get_Property_Int("Global", "EquipmentDamagePoint");
	m_ConfigInfo.m_DropSearchRange = ini.Get_Property_Int("Global", "DropSearchRange");
	ini.GetText("Global", "DropPosDistance", szText, sizeof(szText) - 1);
	m_ConfigInfo.m_DropPosDistance = (float) (atof(szText));
	m_ConfigInfo.m_PlayerChangeSceneProtectTime = ini.Get_Property_Int("Global", "PlayerChangeSceneProtectTime");
	m_ConfigInfo.m_MaxOnlineUser = ini.Get_Property_Int("Global", "MaxOnlineUser");
	if(m_ConfigInfo.m_MaxOnlineUser > MAX_WORLD_PLAYER) m_ConfigInfo.m_MaxOnlineUser = MAX_WORLD_PLAYER;
	m_ConfigInfo.m_PunchLevel = ini.Get_Property_Int("Global", "PunchLevel");
	m_ConfigInfo.m_dwOnLineUserCountTimer = ini.Get_Property_Int("ManageLog", "OnLineUserCountTimer");

	m_ConfigInfo.m_WorldCupVersion = ini.Get_Property_Int("BattleSceneFlag", "WorldCupVersion");
	m_ConfigInfo.m_WorldCupMode = ini.Get_Property_Int("BattleSceneFlag", "WorldCupMode");
	m_ConfigInfo.m_PVP2v2BattleRandGroupNum = ini.Get_Property_Int("BattleSceneFlag", "PVP2v2BattleRandGroupNum");
	m_ConfigInfo.m_PVP2v2BattleLevelFlag = ini.Get_Property_Int("BattleSceneFlag", "PVP2v2BattleLevelFlag");
	m_ConfigInfo.m_PVP6v6BattleRandGroupNum = ini.Get_Property_Int("BattleSceneFlag", "PVP6v6BattleRandGroupNum");
	m_ConfigInfo.m_PVP6v6BattleLevelFlag = ini.Get_Property_Int("BattleSceneFlag", "PVP6v6BattleLevelFlag");
	m_ConfigInfo.m_PVP6v6BattleTime = ini.Get_Property_Int("BattleSceneFlag", "PVP6v6BattleTime");
	m_ConfigInfo.m_PVP6v6BattleTeamNumLimit = ini.Get_Property_Int("BattleSceneFlag", "PVP6v6BattleTeamNumLimit");
	m_ConfigInfo.m_CountryBattleKingissueCount = ini.Get_Property_Int("BattleSceneFlag","CountryBattleKingissueCount");
	m_ConfigInfo.m_GuildBattleRandGroupNum = ini.Get_Property_Int("BattleSceneFlag", "GuildBattleRandGroupNum");
	m_ConfigInfo.m_GuildBattleGuildMemberNumLessLimit = ini.Get_Property_Int("BattleSceneFlag", "GuildBattleGuildMemberNumLessLimit");
	m_ConfigInfo.m_CountryBattleLiteWeekFlag = ini.Get_Property_Int("BattleSceneFlag", "CountryBattleLiteWeekFlag");
	m_ConfigInfo.m_CountryBattleLiteWeekDay = ini.Get_Property_Int("BattleSceneFlag", "CountryBattleLiteWeekDay");
	m_ConfigInfo.m_CountryBattleLiteWeekFreq = ini.Get_Property_Int("BattleSceneFlag", "CountryBattleLiteWeekFreq");
	m_ConfigInfo.m_ZhuQueBattleGuildLevel = ini.Get_Property_Int("BattleSceneFlag", "ZhuQueBattleGuildLevel");
	m_ConfigInfo.m_ZhuQueBattleGuildMemberCount = ini.Get_Property_Int("BattleSceneFlag", "ZhuQueBattleGuildMemberCount");
	m_ConfigInfo.m_QingLongBattleGuildLevel = ini.Get_Property_Int("BattleSceneFlag", "QingLongBattleGuildLevel");
	m_ConfigInfo.m_QingLongBattleGuildMemberCount = ini.Get_Property_Int("BattleSceneFlag", "QingLongBattleGuildMemberCount");
	m_ConfigInfo.m_LairdBattleGuildLevel = ini.Get_Property_Int("BattleSceneFlag", "LairdBattleGuildLevel");
	m_ConfigInfo.m_LairdBattleGuildMemberCount = ini.Get_Property_Int("BattleSceneFlag", "LairdBattleGuildMemberCount");
	m_ConfigInfo.m_RecoverTime = ini.Get_Property_Int("TimeSetting", "RecoverTime");
	m_ConfigInfo.m_MaxMonster = ini.Get_Property_Int("Monster", "MaxCount");
	m_ConfigInfo.m_MaxPet = ini.Get_Property_Int("Pet", "MaxCount");
	m_ConfigInfo.m_PetHappinessInterval = ini.Get_Property_Int("Pet", "PetHappinessInterval");
	m_ConfigInfo.m_PetHappinessPoint = ini.Get_Property_Int("Pet", "PetHappinessPoint");
	m_ConfigInfo.m_nHorseCheckUpSpend = ini.Get_Property_Int("Pet", "HorseCheckUpSpend");
	m_ConfigInfo.m_nHorseMattingSpend = ini.Get_Property_Int("Pet", "HorseMattingSpend");
	m_ConfigInfo.m_nHorseComposeSpend = ini.Get_Property_Int("Pet", "HorseComposeSpend");
	m_ConfigInfo.m_nHorseComposeLevel = ini.Get_Property_Int("Pet", "HorseComposeLevel");
	m_ConfigInfo.m_uHorseComposeLockPassItem = ini.Get_Property_Int("Pet", "HorseComposeLockPassItem");
	m_ConfigInfo.m_uHorseComposeRepentItem = ini.Get_Property_Int("Pet", "HorseComposeRepentItem");
	m_ConfigInfo.m_HorseCallUpHappiness = ini.Get_Property_Int("Pet", "PetCallUpHappiness");
	m_ConfigInfo.m_PetHappinessDecExp = ini.Get_Property_Int("Pet", "PetHappinessDecExp");
	m_ConfigInfo.m_MattingPrimaryHorseGeneration = ini.Get_Property_Int("Pet", "MattingPrimaryHorseGeneration");
	m_ConfigInfo.m_MattingSecondaryHorseGeneration = ini.Get_Property_Int("Pet", "MattingSecondaryHorseGeneration");
	m_ConfigInfo.m_MattingPrimaryHorseLevel = ini.Get_Property_Int("Pet", "MattingPrimaryHorseLevel");
	m_ConfigInfo.m_MattingSecondaryHorseLevel = ini.Get_Property_Int("Pet", "MattingSecondaryHorseLevel");
	m_ConfigInfo.m_MattingHorseLevelPara = ini.Get_Property_Int("Pet", "MattingHorseLevelPara");
	m_ConfigInfo.m_ChildHorseTakeLevelPara = ini.Get_Property_Int("Pet", "ChildHorseTakeLevelPara");
	m_ConfigInfo.m_ChildHorsePerceptionPara = ini.Get_Property_Int("Pet", "ChildHorsePerceptionPara");
	m_ConfigInfo.m_ChildHorsePerceptionMode = ini.Get_Property_Int("Pet", "ChildHorsePerceptionMode");
	m_ConfigInfo.m_RestoreHorseHappyMoney = ini.Get_Property_Int("Pet", "RestoreHorseMoney");
	m_ConfigInfo.m_PerceptionLimit = ini.Get_Property_Int("Pet", "PerceptionLimit");
	m_ConfigInfo.m_PerceptionItemPara = ini.Get_Property_Int("Pet", "PerceptionItemPara");
	m_ConfigInfo.m_HorseCallupLevelThanPlayer = ini.Get_Property_Int("Pet", "HorseCallupLevelThanPlayer");
	m_ConfigInfo.m_HorseRemainPointPara = ini.Get_Property_Int("Pet", "HorseRemainPointPara");
	m_ConfigInfo.m_CaptureHorseMinPlayerLevel = ini.Get_Property_Int("Pet", "CaptureHorseMinPlayerLevel");
	m_ConfigInfo.m_TakeHorseNumIncLevelStep = ini.Get_Property_Int("Pet", "TakeHorseNumIncLevelStep");
	m_ConfigInfo.m_DecHorseHappOnMonsterKill = ini.Get_Property_Int("Pet", "DecHorseHappOnMonsterKill");
	m_ConfigInfo.m_DecHorseHpaaOnHumanKill = ini.Get_Property_Int("Pet", "DecHorseHpaaOnHumanKill");
	m_ConfigInfo.m_RemainPointOnLevelup = ini.Get_Property_Int("Pet", "RemainPointOnLevelup");

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	char	pSplitString[255] = { 0 };
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(ini.GetText("Pet", "HorseReplaceOldSkillRate", pSplitString, 255))
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		SplitStringLevelOne	pSplitL1;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		pSplitL1.Reset();
		pSplitL1.Init(',', NULL);
		pSplitL1.DoSplit(pSplitString);

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	iLineCount = pSplitL1.GetResultLineCount();
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(iLineCount > 12) iLineCount = 12;
		for(int32 i = 0; i < iLineCount; ++i)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			const char		*pSplit1Result = pSplitL1.GetResultLine(i);
			SplitStringLevelOne	pSplitL2;
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			pSplitL2.Reset();
			pSplitL2.Init('|', NULL);
			if(FALSE == pSplitL2.DoSplit(pSplit1Result)) break;

			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			int32	iLineCount2 = pSplitL2.GetResultLineCount();
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(iLineCount2 > 12) iLineCount2 = 12;
			for(int32 j = 0; j < iLineCount2; ++j)
			{
				m_ConfigInfo.m_HorseReplaceOldSkillRate[i][j] = atoi(pSplitL2.GetResultLine(j));
			}
		}
	}

	m_ConfigInfo.m_PetReFollowDistanceB = ini.Get_Property_Int("Pet", "PetReFollowDistanceB");
	m_ConfigInfo.m_PetReFollowDistanceC = ini.Get_Property_Int("Pet", "PetReFollowDistanceC");
	m_ConfigInfo.m_PetStandDistanceToOnwerMIN = ini.Get_Property_Int("Pet", "PetStandDistanceToOnwerMIN");
	m_ConfigInfo.m_PetStandDistanceToOnwerMAX = ini.Get_Property_Int("Pet", "PetStandDistanceToOnwerMAX");
	m_ConfigInfo.m_PetBeginMoveRandom = ini.Get_Property_Int("Pet", "PetBeginMoveRandom");
	m_ConfigInfo.m_PetMoveToAPlaceRandom = ini.Get_Property_Int("Pet", "PetMoveToAPlaceRandom");

	m_ConfigInfo.m_DefaultRespawnTime = ini.Get_Property_Int("Monster", "DefaultRespawnTime");
	m_ConfigInfo.m_ValidAttackTime = ini.Get_Property_Int("TimeSetting", "ValidAttack");
	m_ConfigInfo.m_DropBoxRecycleTime = ini.Get_Property_Int("TimeSetting", "DropBoxRecycle");
	m_ConfigInfo.m_DropProtectTime = ini.Get_Property_Int("TimeSetting", "DropProtectTime");
	m_ConfigInfo.m_TimeChangeInterval = ini.Get_Property_Int("TimeSetting", "TimeChangeInterval");
	m_ConfigInfo.m_PositionRange = ini.Get_Property_Int("Monster", "DefaultPositionRange");
	m_ConfigInfo.m_AIType = ini.Get_Property_Int("Monster", "DefaultAIType");
	m_ConfigInfo.m_DisconnectTime = ini.Get_Property_Int("TimeSetting", "DisconnectTime");
	ini.GetText("Temp", "UserPath", m_ConfigInfo.m_UserPath, _MAX_PATH);
	m_ConfigInfo.m_DefaultBodyTime = ini.Get_Property_Int("Monster", "DefaultBodyTime");
	m_ConfigInfo.m_DefaultRefuseScanTime = ini.Get_Property_Int("Monster", "DefaultRefuseScanTime");
	m_ConfigInfo.m_OutGhostTime = ini.Get_Property_Int("Human", "OutGhostTime");
	m_ConfigInfo.m_CanGetExpRange = (float) (ini.Get_Property_Int("Human", "CanGetExpRange"));
	m_ConfigInfo.m_DefaultMoveSpeed = ini.Get_Property_Int("Human", "DefaultMoveSpeed");
	m_ConfigInfo.m_DefaultWalkSpeed = ini.Get_Property_Int("Human", "DefaultWalkSpeed");
	m_ConfigInfo.m_DefaultAttackSpeed = ini.Get_Property_Int("Human", "DefaultAttackSpeed");
	m_ConfigInfo.m_HumanVERecoverInterval = ini.Get_Property_Int("Human", "HumanVERecoverInterval");
	m_ConfigInfo.m_HumanPKValueRecoverInterval = ini.Get_Property_Int("Human", "RecoverPKValueTime");
	m_ConfigInfo.m_HumanPKValueRecoverSize = ini.Get_Property_Int("Human", "RecoverPKValueStride");
	m_ConfigInfo.m_HumanHGRecoverInterval = ini.Get_Property_Int("Human", "HumanHGRecoverInterval");
	m_ConfigInfo.m_ProfessionRAGERecoverInterval[0] = ini.Get_Property_Int("Human", "WUSHIRAGERecoverInterval");
	m_ConfigInfo.m_ProfessionRAGERecoverInterval[1] = ini.Get_Property_Int("Human", "JIANXIARAGERecoverInterval");
	m_ConfigInfo.m_ProfessionRAGERecoverInterval[2] = ini.Get_Property_Int("Human", "QISHERAGERecoverInterval");
	m_ConfigInfo.m_ProfessionRAGERecoverInterval[3] = ini.Get_Property_Int("Human", "HUOQIANGRAGERecoverInterval");
	m_ConfigInfo.m_ProfessionRAGERecoverInterval[4] = ini.Get_Property_Int("Human", "XIANZHIRAGERecoverInterval");
	m_ConfigInfo.m_ProfessionRAGERecoverInterval[5] = ini.Get_Property_Int("Human", "SAMANRAGERecoverInterval");
	m_ConfigInfo.m_ProfessionRAGERecoverInterval[6] = ini.Get_Property_Int("Human", "SHIZIJUNRAGERecoverInterval");
	m_ConfigInfo.m_ProfessionRAGERecoverInterval[7] = ini.Get_Property_Int("Human", "SHENGHUOSHIRAGERecoverInterval");
	m_ConfigInfo.m_ProfessionRAGERecoverInterval[8] = ini.Get_Property_Int("Human", "CIKERAGERecoverInterval");
	m_ConfigInfo.m_ProfessionRAGERecoverInterval[9] = ini.Get_Property_Int("Human", "JINWEIJUNRAGERecoverInterval");
	m_ConfigInfo.m_ProfessionRAGERecoverInterval[10] = ini.Get_Property_Int("Human", "YINXIUSHIRAGERecoverInterval");
	m_ConfigInfo.m_ProfessionRAGERecoverInterval[11] = ini.Get_Property_Int("Human", "LAMARAGERecoverInterval");
	m_ConfigInfo.m_WallowAge = ini.Get_Property_Int("Human", "WallowAge");
	m_ConfigInfo.m_WallowStartTime = ini.Get_Property_Int("Human", "WallowStartTime");
	m_ConfigInfo.m_WallowStartTime2 = ini.Get_Property_Int("Human", "WallowStartTime2");
	m_ConfigInfo.m_WallowAwokeTime = ini.Get_Property_Int("Human", "WallowAwokeTime");

	m_ConfigInfo.m_WallowInterval_1 = ini.Get_Property_Int("Human", "WallowInterval_1");
	m_ConfigInfo.m_WallowInterval_2 = ini.Get_Property_Int("Human", "WallowInterval_2");
	m_ConfigInfo.m_WallowInterval_3 = ini.Get_Property_Int("Human", "WallowInterval_3");
	m_ConfigInfo.m_WallowTotalTime_1 = ini.Get_Property_Int("Human", "WallowTotalTime_1");
	m_ConfigInfo.m_WallowTotalTime_2 = ini.Get_Property_Int("Human", "WallowTotalTime_2");
	m_ConfigInfo.m_WallowTotalTime_3 = ini.Get_Property_Int("Human", "WallowTotalTime_3");
	m_ConfigInfo.m_WallowTotalTime_3dot5 = ini.Get_Property_Int("Human", "WallowTotalTime_3dot5");
	m_ConfigInfo.m_WallowTotalTime_5 = ini.Get_Property_Int("Human", "WallowTotalTime_5");
	m_ConfigInfo.m_ResetWallowTime = ini.Get_Property_Int("Human", "ResetWallowTime");
	m_ConfigInfo.m_SaveOnlineTimeInterval = ini.Get_Property_Int("Human", "SaveOnlineTimeInterval");
	m_ConfigInfo.m_ItemUpdateRate = ini.Get_Property_Int("Human", "ItemUpdateRate");
	m_ConfigInfo.m_ItemUnLockCDTime = ini.Get_Property_Int("Human", "ItemUnLockCDTime");
	m_ConfigInfo.m_ChatReportCoolTime = ini.Get_Property_Int("Human", "ChatReportCoolTime");
	m_ConfigInfo.m_ChatReportMinCount = ini.Get_Property_Int("Human", "ChatReportMinCount");
	m_ConfigInfo.m_WatchKeywordRand = ini.Get_Property_Int("Human", "WatchKeywordRand");
	m_ConfigInfo.m_MailCoolDownTime = ini.Get_Property_Int("Human", "MailCoolDownTime")*1000;

	m_ConfigInfo.m_MaxCurPlayerLevel = ini.Get_Property_Int("Human", "MaxCurPlayerLevel");
	if((m_ConfigInfo.m_MaxCurPlayerLevel > MAX_PLAYER_EXP_LEVEL) || (m_ConfigInfo.m_MaxCurPlayerLevel <= 0))
	{
		m_ConfigInfo.m_MaxCurPlayerLevel = MAX_PLAYER_EXP_LEVEL;
	}

	ini.GetText("Human", "InherenceFixParam", szText, sizeof(szText) - 1);
	m_ConfigInfo.m_fInherenceFixParam = (float) (atof(szText));

	m_ConfigInfo.m_nAvailableFollowDist = ini.Get_Property_Int("Team", "AvailableFollowDist");
	m_ConfigInfo.m_nTimeForLoseFollow = ini.Get_Property_Int("Team", "TimeForLoseFollow");
	ini.GetText("Team", "TeamRage", szText, sizeof(szText) - 1);
	m_ConfigInfo.m_nTeamRage = (float) (atof(szText));
	m_ConfigInfo.m_nTeamFreshTime = ini.Get_Property_Int("Team", "TeamFreshTime");

	/*~~~~~~~~~~~~~~~~~~~~~~*/
	int32	TeamCountRate = 0;
	/*~~~~~~~~~~~~~~~~~~~~~~*/

	m_ConfigInfo.m_TeamCount1Rate = ini.Get_Property_Int("Team", "TeamCount1Rate");
	m_ConfigInfo.m_TeamCount2Rate = ini.Get_Property_Int("Team", "TeamCount2Rate");
	m_ConfigInfo.m_TeamCount3Rate = ini.Get_Property_Int("Team", "TeamCount3Rate");
	m_ConfigInfo.m_TeamCount4Rate = ini.Get_Property_Int("Team", "TeamCount4Rate");
	m_ConfigInfo.m_TeamCount5Rate = ini.Get_Property_Int("Team", "TeamCount5Rate");
	m_ConfigInfo.m_TeamCount6Rate = ini.Get_Property_Int("Team", "TeamCount6Rate");
	m_ConfigInfo.m_TeamCount6Rate = ini.Get_Property_Int("Team", "TeamCount6Rate");
	m_ConfigInfo.m_TeamGoodBad = ini.Get_Property_Int("Team", "TeamGoodBad");
	m_ConfigInfo.m_TeamGoodBadSpecial = ini.Get_Property_Int("Team", "TeamGoodBadSpecial");
	m_ConfigInfo.m_nGoodBadPlayerLevel = ini.Get_Property_Int("Team", "TeamGoodBadPlayerLevel");
	m_ConfigInfo.m_nGoodBadMonsterLevelLow = ini.Get_Property_Int("Team", "TeamGoodBadMonsterLevelLow");
	m_ConfigInfo.m_nGoodBadMonsterLevelHigh = ini.Get_Property_Int("Team", "TeamGoodBadMonsterLevelHigh");
	m_ConfigInfo.m_nTeamGoodBadImpact = ini.Get_Property_Int("Team", "TeamGoodBadImpact");
	ini.GetText("Team", "TeamGoodBadImpactRate", szText, sizeof(szText) - 1);
	m_ConfigInfo.m_fTeamGoodBadImpactRate = (float) (atof(szText));
	ini.GetText("Team", "PrenticeExpRefixWhenMasterHere", szText, sizeof(szText) - 1);
	m_ConfigInfo.m_fPrenticeExpRefixWhenMasterHere = (float) (atof(szText));
	ini.GetText("Team", "PrenticeExpRefixWhenHaveTitle", szText, sizeof(szText) - 1);
	m_ConfigInfo.m_fPrenticeExpRefixWhenHaveTitle = (float) (atof(szText));

	m_ConfigInfo.m_nFoundDurationSec = ini.Get_Property_Int("Guild", "FoundDuration");
	m_ConfigInfo.m_nDefaultMaxMemberCount = ini.Get_Property_Int("Guild", "DefaultMaxMemberCount");
	m_ConfigInfo.m_nResponseUserCount = ini.Get_Property_Int("Guild", "ResponseUserCount");
	m_ConfigInfo.m_nPasswdPoint = ini.Get_Property_Int("Relation", "PasswdPoint");
	m_ConfigInfo.m_nPromptPoint = ini.Get_Property_Int("Relation", "PromptPoint");
	m_ConfigInfo.m_nDeleteDelayTime = ini.Get_Property_Int("MinorPassword", "DeleteDelayTime");
	m_ConfigInfo.m_nProtectDelayTime = ini.Get_Property_Int("MinorPassword", "ProtectDelayTime");
	m_ConfigInfo.m_nProtectDefaultTime = ini.Get_Property_Int("MinorPassword", "ProtectDefaultTime");
	m_ConfigInfo.m_nProtectDefaultError = ini.Get_Property_Int("MinorPassword", "ProtectDefaultError");

	m_ConfigInfo.m_nExpPoint = ini.Get_Property_Int("Relation", "ExpPoint");

	m_ConfigInfo.m_nHashOnlineUserCount = ini.Get_Property_Int("GL", "HashOnlineUserCount");
	m_ConfigInfo.m_nHashMailUserCount = ini.Get_Property_Int("GL", "HashMailUserCount");
	m_ConfigInfo.m_nMaxOfflineUserCount = ini.Get_Property_Int("GL", "MaxOfflineUserCount");
	ini.GetText("Global", "RespawnParam", szText, sizeof(szText) - 1);
	m_ConfigInfo.m_fRespawnParam = (float) (atof(szText));
	m_ConfigInfo.m_KickUserTime = ini.Get_Property_Int("TimeSetting", "KickUserTime");
	m_ConfigInfo.m_nDefaultDamageFluctuation = ini.Get_Property_Int("Combat", "DefaultDamageFluctuation");
	m_ConfigInfo.m_nCriticalDamageRate = ini.Get_Property_Int("Combat", "CriticalDamageRate");
	m_ConfigInfo.m_nToughEffCriticalDamage = ini.Get_Property_Int("Combat", "ToughnessEffCriticalDamage");

	m_ConfigInfo.m_nMinGoodBadValue = ini.Get_Property_Int("GoodBad", "MinGoodBadValue");
	m_ConfigInfo.m_nMaxGoodBadValue = ini.Get_Property_Int("GoodBad", "MaxGoodBadValue");
	m_ConfigInfo.m_nLevelNeeded = ini.Get_Property_Int("GoodBad", "LevelNeeded");
	m_ConfigInfo.m_nMemberLevel = ini.Get_Property_Int("GoodBad", "MemberLevel");
	m_ConfigInfo.m_fGoodBadRadius = (float) ini.Get_Property_Int("GoodBad", "GoodBadRadius");
	m_ConfigInfo.m_nBonusPerMember = ini.Get_Property_Int("GoodBad", "BonusPerMember");
	m_ConfigInfo.m_nMaxBonus = ini.Get_Property_Int("GoodBad", "MaxBonus");
	m_ConfigInfo.m_nPenaltyWhenMemberDie = ini.Get_Property_Int("GoodBad", "PenaltyWhenMemberDie");

	m_ConfigInfo.m_nMinPaiScore = ini.Get_Property_Int("Equip", "MinPaiScore");
	m_ConfigInfo.m_nMinZiPaiScore = ini.Get_Property_Int("Equip", "MinZiPaiScore");
	m_ConfigInfo.m_nComMonsterDrop = ini.Get_Property_Int("Equip", "ComMonsterDrop");
	m_ConfigInfo.m_nSenMonsterDrop = ini.Get_Property_Int("Equip", "SenMonsterDrop");
	m_ConfigInfo.m_nBossDrop = ini.Get_Property_Int("Equip", "BossDrop");
	m_ConfigInfo.m_nEquipDurPer = ini.Get_Property_Int("Equip", "EquipDurPer");
	m_ConfigInfo.m_MinEquipDurReduce = ini.Get_Property_Int("Equip", "MinEquipDurReduce");
	m_ConfigInfo.m_nRefreshAttrToWorldInterval = ini.Get_Property_Int("GL", "RefreshAttrToWorldInterval");

	m_ConfigInfo.m_nSubTrainExp = ini.Get_Property_Int("SubTrain", "SubTrainExp");
	m_ConfigInfo.m_nSubTrainMoney = ini.Get_Property_Int("SubTrain", "SubTrainMoney");

	m_ConfigInfo.m_nDelateNum = ini.Get_Property_Int("Country", "DelateNum");
	m_ConfigInfo.m_nVoteNum = ini.Get_Property_Int("Country", "VoteNum");
	m_ConfigInfo.m_nVoteTime = ini.Get_Property_Int("Country", "VoteTime");
	m_ConfigInfo.m_ApplyKingMoney = ini.Get_Property_Int("Country", "ApplyKingMoney");
	m_ConfigInfo.m_ApplyKingGuildLevel = ini.Get_Property_Int("Country", "ApplyKingGuildLevel");
	m_ConfigInfo.m_ApplyKingGuildCount = ini.Get_Property_Int("Country", "ApplyKingGuildCount");
	m_ConfigInfo.m_nForbidChatDuration = ini.Get_Property_Int("Country", "ForbidChatDuration");
	m_ConfigInfo.m_nEnjailDuration = ini.Get_Property_Int("Country", "EnjailDuration");
	m_ConfigInfo.m_ApplyKingMoneyType = ini.Get_Property_Int("Country", "ApplyKingMoneyType");
	KCheck(m_ConfigInfo.m_ApplyKingMoneyType != 2);
	m_ConfigInfo.m_DonateMoneyType = ini.Get_Property_Int("Country", "DonateMoneyType");
	KCheck(m_ConfigInfo.m_DonateMoneyType != 2);
	m_ConfigInfo.m_FortuneDuration = ini.Get_Property_Int("Country", "FortuneDuration");
	m_ConfigInfo.m_FortuneDuration_RuoGuo = ini.Get_Property_Int("Country", "FortuneDurationRuoGuo");
	m_ConfigInfo.m_FortunePrice1 = ini.Get_Property_Int("Country", "FortunePrice1");
	m_ConfigInfo.m_FortunePrice2 = ini.Get_Property_Int("Country", "FortunePrice2");
	m_ConfigInfo.m_FortunePrice3 = ini.Get_Property_Int("Country", "FortunePrice3");
	m_ConfigInfo.m_FortunePrice4 = ini.Get_Property_Int("Country", "FortunePrice4");
	m_ConfigInfo.m_FortuneMaxCount = ini.Get_Property_Int("Country", "FortuneMaxCount");

	//--add for 青龙， 朱雀
	//--青龙
	m_ConfigInfo.m_ApplyCountryBanghuiMoney[0] = ini.Get_Property_Int("Country", "CountryBanghuiMoney0");
	m_ConfigInfo.m_ApplyCountryBanghuiMoneyType[0] = ini.Get_Property_Int("Country", "CountryBanghuiMoneyType0");
	m_ConfigInfo.m_ApplyCountryBanghuiLevel[0] = ini.Get_Property_Int("Country", "CountryBanghuiLevel0");
	m_ConfigInfo.m_ApplyCountryBanghuiMemberCount[0] = ini.Get_Property_Int("Country", "CountryBanghuiMemberCount0");
	m_ConfigInfo.m_ApplyCountryBanghuiWeek[0] = ini.Get_Property_Int("Country", "CountryBanghuiWeek0");
	m_ConfigInfo.m_ApplyCountryBanghuiStartTime[0] = ini.Get_Property_Int("Country", "CountryBanghuiStartTime0");  //单位为分钟
	m_ConfigInfo.m_ApplyCountryBanghuiEndTime[0] = ini.Get_Property_Int("Country", "CountryBanghuiEndTime0");
	
	//--朱雀
	m_ConfigInfo.m_ApplyCountryBanghuiMoney[1] = ini.Get_Property_Int("Country", "CountryBanghuiMoney1");
	m_ConfigInfo.m_ApplyCountryBanghuiMoneyType[1] = ini.Get_Property_Int("Country", "CountryBanghuiMoneyType1");
	m_ConfigInfo.m_ApplyCountryBanghuiLevel[1] = ini.Get_Property_Int("Country", "CountryBanghuiLevel1");
	m_ConfigInfo.m_ApplyCountryBanghuiMemberCount[1] = ini.Get_Property_Int("Country", "CountryBanghuiMemberCount1");
	m_ConfigInfo.m_ApplyCountryBanghuiWeek[1] = ini.Get_Property_Int("Country", "CountryBanghuiWeek1");
	m_ConfigInfo.m_ApplyCountryBanghuiStartTime[1] = ini.Get_Property_Int("Country", "CountryBanghuiStartTime1");  //单位为分钟
	m_ConfigInfo.m_ApplyCountryBanghuiEndTime[1] = ini.Get_Property_Int("Country", "CountryBanghuiEndTime1");
	
	//--add end
	m_ConfigInfo.m_ApplyKingWeek = ini.Get_Property_Int("Country", "ApplyKingWeek");
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	hour = 0, minute = 0;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~*/

		ini.GetText("Country", "ApplyKingStartTime", szText, sizeof(szText) - 1);
		hour = atoi(szText);

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		char	*pstr = strchr(szText, ':');
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(pstr) minute = atoi(pstr + 1);
		m_ConfigInfo.m_ApplyKingStartTime = hour * 60 + minute;

		hour = minute = 0;
		ini.GetText("Country", "ApplyKingEndTime", szText, sizeof(szText) - 1);
		hour = atoi(szText);
		pstr = strchr(szText, ':');
		if(pstr) minute = atoi(pstr + 1);
		m_ConfigInfo.m_ApplyKingEndTime = hour * 60 + minute;
	}

	m_ConfigInfo.m_AssignGeneralMaxCount = ini.Get_Property_Int("Country", "AssignGeneralMaxCount");
	m_ConfigInfo.m_AssignLMinisterMaxCount = ini.Get_Property_Int("Country", "AssignLMinisterMaxCount");
	m_ConfigInfo.m_AssignRMinisterMaxCount = ini.Get_Property_Int("Country", "AssignRMinisterMaxCount");
	m_ConfigInfo.m_AssignLGuardMaxCount = ini.Get_Property_Int("Country", "AssignLGuardMaxCount");
	m_ConfigInfo.m_AssignRGuardMaxCount = ini.Get_Property_Int("Country", "AssignRGuardMaxCount");

	m_ConfigInfo.m_CancelGeneralMaxCount = ini.Get_Property_Int("Country", "CancelGeneralMaxCount");
	m_ConfigInfo.m_CancelLMinisterMaxCount = ini.Get_Property_Int("Country", "CancelLMinisterMaxCount");
	m_ConfigInfo.m_CancelRMinisterMaxCount = ini.Get_Property_Int("Country", "CancelRMinisterMaxCount");
	m_ConfigInfo.m_CancelLGuardMaxCount = ini.Get_Property_Int("Country", "CancelLGuardMaxCount");
	m_ConfigInfo.m_CancelRGuardMaxCount = ini.Get_Property_Int("Country", "CancelRGuardMaxCount");

	m_ConfigInfo.m_ModifyNoticeMaxCount = ini.Get_Property_Int("Country", "ModifyNoticeMaxCount");
	m_ConfigInfo.m_CollectMaxCount = ini.Get_Property_Int("Country", "CollectMaxCount");
	m_ConfigInfo.m_ForbidChatMaxCount = ini.Get_Property_Int("Country", "ForbidChatMaxCount");
	m_ConfigInfo.m_EnjailMaxCount = ini.Get_Property_Int("Country", "EnjailMaxCount");
	m_ConfigInfo.m_AssoilMaxCount = ini.Get_Property_Int("Country", "AssoilMaxCount");
	m_ConfigInfo.m_KingBattlePrise = ini.Get_Property_Int("Country", "KingBattlePrise");

	m_ConfigInfo.m_nRejoinGuildInterval = ini.Get_Property_Int("Guild", "RejoinGuildInterval");
	m_ConfigInfo.m_nLevelOfCreateGuild = ini.Get_Property_Int("Guild", "LevelOfCreateGuild");
	m_ConfigInfo.m_nLevelOfJoinGuild = ini.Get_Property_Int("Guild", "LevelOfJoinGuild");
	m_ConfigInfo.m_nMoneyOfCreateGuild = ini.Get_Property_Int("Guild", "MoneyOfCreateGuild");
	m_ConfigInfo.m_nModifyTitleInvertal = ini.Get_Property_Int("Guild", "ModifyTitleInvertal");
	m_ConfigInfo.m_nModifyDescInvertal = ini.Get_Property_Int("Guild", "ModifyDescInvertal");
	m_ConfigInfo.m_nMoneyTypeOfCreateGuild = ini.Get_Property_Int("Guild", "MoneyTypeOfCreateGuild");
	m_ConfigInfo.m_nMoneyTypeOfLevelupGuild = ini.Get_Property_Int("Guild", "MoneyTypeOfLevelupGuild");
	m_ConfigInfo.m_nModifyFamilyNameInvertal = ini.Get_Property_Int("Guild", "ModifyFamilyNameInvertal");
	m_ConfigInfo.m_nEnableGuildDie = ini.Get_Property_Int("Guild", "EnableGuildDie");
	ini.GetText("Guild", "GuildDieDate", m_ConfigInfo.m_szGuildDieDate, 31 );

	m_ConfigInfo.m_fMoneyRate = ini.Get_Property_Int("Money", "MoneyRate");

	m_ConfigInfo.m_nBusCreateTime = ini.Get_Property_Int("Bus", "BusCreateTime");

	ini.GetText("Relation", "DepleteFPTime", szText, sizeof(szText) - 1);
	m_ConfigInfo.m_fDepleteFPTime = (float) (atof(szText));
	m_ConfigInfo.m_nDepleteFPValue = ini.Get_Property_Int("Relation", "DepleteFPValue");
	m_ConfigInfo.m_nMarryNeedFriendPoint = ini.Get_Property_Int("Relation", "MarryNeedFriendPoint");
	m_ConfigInfo.m_nMarryNeedLevel = ini.Get_Property_Int("Relation", "MarryNeedLevel");
	m_ConfigInfo.m_nMarryNeedDistance = ini.Get_Property_Int("Relation", "MarryNeedDistance");
	m_ConfigInfo.m_nMarryNeedItem = ini.Get_Property_Int("Relation", "MarryNeedItem");
	m_ConfigInfo.m_nMarryNeedGold = ini.Get_Property_Int("Relation", "MarryNeedGold");
	m_ConfigInfo.m_nMarryFreeMonth = ini.Get_Property_Int("Relation", "MarryFreeMonth");
	m_ConfigInfo.m_nMarryFreeDay = ini.Get_Property_Int("Relation", "MarryFreeDay");
	m_ConfigInfo.m_nRequireMasterLevel = ini.Get_Property_Int("Relation", "RequireMasterLevel");
	m_ConfigInfo.m_nPrenticeLevelLow = ini.Get_Property_Int("Relation", "PrenticeLevelLow");
	m_ConfigInfo.m_nMasterOrPrenticeLevelConfine = ini.Get_Property_Int("Relation", "MasterOrPrenticeLevelConfine");
	m_ConfigInfo.m_nMasterOrPrenticeTimeRequire = ini.Get_Property_Int("Relation", "MasterOrPrenticeTimeRequire");
	m_ConfigInfo.m_nFriendGiftTimeLimit = ini.Get_Property_Int("Relation", "FriendGiftTimeLimit");
	m_ConfigInfo.m_nFriendGiftTimes = ini.Get_Property_Int("Relation", "FriendGiftTimes");
	m_ConfigInfo.m_nMaxFriendPoint = ini.Get_Property_Int("Relation", "MaxFriendPoint");
	m_ConfigInfo.m_nBlackDecFriendPoint = ini.Get_Property_Int("Relation", "BlackDecFriendPoint");
	m_ConfigInfo.m_nEnemyDecFriendPoint = ini.Get_Property_Int("Relation", "EnemyDecFriendPoint");
	m_ConfigInfo.m_nWeddingItem = ini.Get_Property_Int("Relation", "WeddingItem");
	ini.GetText("Relation", "WeddingMoneyRate", szText, sizeof(szText) - 1);
	m_ConfigInfo.m_fWeddingMoneyRate = (float) (atof(szText));

	m_ConfigInfo.m_nBankDataValidTime = ini.Get_Property_Int("WorldBank", "BankDataValidTime");
	m_ConfigInfo.m_nBankMailSendTime = ini.Get_Property_Int("WorldBank", "BankMailSendTime");

	m_ConfigInfo.m_uPurpleAttRate1 = (uint32) ini.Get_Property_Int("Item", "PurpleAttRate1");
	m_ConfigInfo.m_uPurpleAttRate2 = (uint32) ini.Get_Property_Int("Item", "PurpleAttRate2");
	m_ConfigInfo.m_uPurpleAttRate3 = (uint32) ini.Get_Property_Int("Item", "PurpleAttRate3");

	m_ConfigInfo.m_uBlueAttrRate1 = (uint32) ini.Get_Property_Int("Item", "BlueAttRate1");
	m_ConfigInfo.m_uBlueAttrRate2 = (uint32) ini.Get_Property_Int("Item", "BlueAttRate2");
	m_ConfigInfo.m_uBlueAttrRate3 = (uint32) ini.Get_Property_Int("Item", "BlueAttRate3");
	m_ConfigInfo.m_uBlueAttrRate4 = (uint32) ini.Get_Property_Int("Item", "BlueAttRate4");
	m_ConfigInfo.m_uBlueAttrRate5 = (uint32) ini.Get_Property_Int("Item", "BlueAttRate5");

	m_ConfigInfo.m_nGemUninst_NeedItem = ini.Get_Property_Int("Item", "GemUninst_NeedItem");
	m_ConfigInfo.m_nGemUninst_NeedMoney = ini.Get_Property_Int("Item", "GemUninst_NeedMoney");
	m_ConfigInfo.m_nEquipCopy_NeedItem1 = ini.Get_Property_Int("Item", "EquipCopy_NeedItem1");
	m_ConfigInfo.m_nEquipCopy_NeedItem2 = ini.Get_Property_Int("Item", "EquipCopy_NeedItem2");
	m_ConfigInfo.m_nEquipCopy_NeedItem3 = ini.Get_Property_Int("Item", "EquipCopy_NeedItem3");
	m_ConfigInfo.m_nEquipCopy_NeedItem4 = ini.Get_Property_Int("Item", "EquipCopy_NeedItem4");
	m_ConfigInfo.m_nEquipCopy_NeedItem5 = ini.Get_Property_Int("Item", "EquipCopy_NeedItem5");
	m_ConfigInfo.m_nEquipCopy_NeedMoney = ini.Get_Property_Int("Item", "EquipCopy_NeedMoney");
	m_ConfigInfo.m_nEquipSwitchNeedLevel = ini.Get_Property_Int("Item", "EquipSwitchNeedLevel");
		
	m_ConfigInfo.m_nStockCharge = ini.Get_Property_Int("Stock", "StockCharge");
	m_ConfigInfo.m_uStockValidTime = (uint32)ini.Get_Property_Int("Stock", "StockValidTime");
	//m_ConfigInfo.m_uStockValidTime *= 1000;		//单位转为秒 
	m_ConfigInfo.m_uStockRegisterCharge = (uint32)ini.Get_Property_Int("Stock", "StockRegisterCharge");
	m_ConfigInfo.m_uStockAccCDTime = (uint32)ini.Get_Property_Int("Stock", "StockAccCDTime");
	m_ConfigInfo.m_uStockAccCDTimeSendMail = (uint32)ini.Get_Property_Int("Stock", "StockAccCDTimeSendMail");
	m_ConfigInfo.m_uStockAccCDInterval = (uint32)ini.Get_Property_Int("Stock", "StockAccCDInterval");
	m_ConfigInfo.m_uStockAccLateFeeGold = (uint32)ini.Get_Property_Int("Stock", "StockAccLateFeeGold");
	m_ConfigInfo.m_uStockAccLateFeeSiller = (uint32)ini.Get_Property_Int("Stock", "StockAccLateFeeSiller");

	m_ConfigInfo.m_nCountryDelateNeedLevel = ini.Get_Property_Int("CountryDelate", "CountryDelateNeedLevel");
	m_ConfigInfo.m_nCountryDelateNeedUserCount = ini.Get_Property_Int("CountryDelate", "CountryDelateNeedUserCount");
	m_ConfigInfo.m_nCountryDelateNeedChieftainPosInTopList = ini.Get_Property_Int("CountryDelate", "CountryDelateNeedChieftainPosInTopList");
	

	//帮会活跃度参数设置
	m_ConfigInfo.m_arrActivityParam[0] = ini.Get_Property_Int("Guild", "ActivityParam1");
	m_ConfigInfo.m_arrActivityParam[1] = ini.Get_Property_Int("Guild", "ActivityParam2");
	m_ConfigInfo.m_arrActivityParam[2] = ini.Get_Property_Int("Guild", "ActivityParam3");
	m_ConfigInfo.m_arrActivityParam[3] = ini.Get_Property_Int("Guild", "ActivityParam4");
	m_ConfigInfo.m_arrActivityParam[4] = ini.Get_Property_Int("Guild", "ActivityParam5");
	m_ConfigInfo.m_arrActivityParam[5] = ini.Get_Property_Int("Guild", "ActivityParam6");
	m_ConfigInfo.m_arrActivityParam[6] = ini.Get_Property_Int("Guild", "ActivityParam7");
	m_ConfigInfo.m_arrActivityParam[7] = ini.Get_Property_Int("Guild", "ActivityParam8");

	m_ConfigInfo.m_arrActivityParamMaxValue[0] = ini.Get_Property_Int("Guild", "ActivityParamMax1");
	m_ConfigInfo.m_arrActivityParamMaxValue[1] = ini.Get_Property_Int("Guild", "ActivityParamMax2");
	m_ConfigInfo.m_arrActivityParamMaxValue[2] = ini.Get_Property_Int("Guild", "ActivityParamMax3");
	m_ConfigInfo.m_arrActivityParamMaxValue[3] = ini.Get_Property_Int("Guild", "ActivityParamMax4");
	m_ConfigInfo.m_arrActivityParamMaxValue[4] = ini.Get_Property_Int("Guild", "ActivityParamMax5");
	m_ConfigInfo.m_arrActivityParamMaxValue[5] = ini.Get_Property_Int("Guild", "ActivityParamMax6");
	m_ConfigInfo.m_arrActivityParamMaxValue[6] = ini.Get_Property_Int("Guild", "ActivityParamMax7");
	m_ConfigInfo.m_arrActivityParamMaxValue[7] = ini.Get_Property_Int("Guild", "ActivityParamMax8");
	__UNGUARD__

}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SettingSystem::LoadMapData()
{
	__GUARD__	
	
	LoadMapData_Try();
	LoadMapData_ReCache();

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SettingSystem::LoadMapData_Try()
{
	/*~~~~~~~~~~~~*/
	__GUARD__ enum SceneDefinesTab
	{
		SDT_SceneID,
		SDT_ThreadIndex,
		SDT_SceneName,
		SDT_SceneEnable,
		SDT_SceneFilePath,
		SDT_ServerID,
		SDT_SceneType,
		SDT_SecurityLevel,
		SDT_RestrictiveMode,
		SDT_Punish,
		SDT_DefaultX,
		SDT_DefaultZ,
		SDT_ClientRes,
		SDT_DefaultCamp,
		SDT_BusPramID,
	};
	/*~~~~~~~~~~~~*/


	char szMapDefineName[128] = {0};
	switch(m_ServerInfo.m_ServerCount)
	{
	case 7:
		tsnprintf_s(szMapDefineName, 128, "%s", FILE_SCENE_INFO/*FILE_SCENE_INFO_6*/);
		break;
	case 11:
		tsnprintf_s(szMapDefineName, 128, "%s", FILE_SCENE_INFO/*FILE_SCENE_INFO_10*/);
		break;
	default:
		tsnprintf_s(szMapDefineName, 128, "%s", FILE_SCENE_INFO);
		break;
	}
	TABFile ThirdFile(0);
	BOOL ret = ThirdFile.OpenFromTXT(szMapDefineName);
	KCheckEx(ret, szMapDefineName);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	iTableCount = ThirdFile.GetRecordsNum();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(iTableCount <= MAX_SCENE);

	m_MapInfo.m_MapCount = iTableCount;

	m_MapInfo.m_pMap = new MAP_CONFIG[m_MapInfo.m_MapCount];
	memset(m_MapInfo.m_pMap, 0, sizeof(MAP_CONFIG) * m_MapInfo.m_MapCount);

	for(uint32 i = 0; i < m_MapInfo.m_MapCount; i++)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		char	szSection[256] = { 0 };
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		m_MapInfo.m_pMap[i].m_MapID = (MapID_t) ThirdFile.Search_Posistion(i, SDT_SceneID)->iValue;
		if(i == 0)
		{
			KCheckEx(m_MapInfo.m_pMap[i].m_MapID == 0, "场景号必须从0开始!");
		}

		m_MapInfo.m_pMap[i].m_IsActive = ThirdFile.Search_Posistion(i, SDT_SceneEnable)->iValue;;
		strncpy
		(
			m_MapInfo.m_pMap[i].m_szName,
			ThirdFile.Search_Posistion(i, SDT_SceneName)->pString,
			_MAX_PATH - 1
		);
		strncpy
		(
			m_MapInfo.m_pMap[i].m_szFileName,
			ThirdFile.Search_Posistion(i, SDT_SceneFilePath)->pString,
			_MAX_PATH - 1
		);
		m_MapInfo.m_pMap[i].m_ServerID = (ID_t) (ThirdFile.Search_Posistion(i, SDT_ServerID)->iValue);
		m_MapInfo.m_pMap[i].m_Type = (ID_t) (ThirdFile.Search_Posistion(i, SDT_SceneType)->iValue);
		m_MapInfo.m_pMap[i].m_ThreadIndex = (ID_t) (ThirdFile.Search_Posistion(i, SDT_ThreadIndex)->iValue);
		m_MapInfo.m_pMap[i].m_cSecurityLevel = (char) (ThirdFile.Search_Posistion(i, SDT_SecurityLevel)->iValue);
		m_MapInfo.m_pMap[i].m_cRestrictiveMode = (char) (ThirdFile.Search_Posistion(i, SDT_RestrictiveMode)->iValue);
		m_MapInfo.m_pMap[i].m_bPunish = (BOOL) (ThirdFile.Search_Posistion(i, SDT_Punish)->iValue);
		m_MapInfo.m_pMap[i].m_DefaultX = ThirdFile.Search_Posistion(i, SDT_DefaultX)->iValue;
		m_MapInfo.m_pMap[i].m_DefaultZ = ThirdFile.Search_Posistion(i, SDT_DefaultZ)->iValue;
		m_MapInfo.m_pMap[i].m_ClientRet = ThirdFile.Search_Posistion(i, SDT_ClientRes)->iValue;
		m_MapInfo.m_pMap[i].m_DefaultCamp = ThirdFile.Search_Posistion(i, SDT_DefaultCamp)->iValue;
		m_MapInfo.m_pMap[i].m_BusParam = ThirdFile.Search_Posistion(i, SDT_BusPramID)->iValue;
	}

	for(uint32 i = 0; i < m_MapInfo.m_MapCount; i++)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		MapID_t MapID = m_MapInfo.m_pMap[i].m_MapID;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		KCheck(MapID != INVALID_ID && MapID < MAX_SCENE);

		KCheck(m_MapInfo.m_HashScene[MapID] == -1);

		m_MapInfo.m_HashScene[MapID] = i;
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SettingSystem::LoadMapData_ReCache()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
ID_t SettingSystem::MapID2ServerID(MapID_t sID) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(sID >= 0);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(sID < (int32) m_MapInfo.m_MapCount);
	return m_MapInfo.m_pMap[m_MapInfo.m_HashScene[sID]].m_ServerID;

	__UNGUARD__ return -1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL SettingSystem::CheckSceneEnable(MapID_t sID) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(sID >= 0);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KCheck(sID < (int32) m_MapInfo.m_MapCount);
	return m_MapInfo.m_pMap[m_MapInfo.m_HashScene[sID]].m_IsActive;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
ID_t SettingSystem::Key2ServerID(MK_VALUE key) const
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(key > 0);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for(uint32 i = 0; i < m_ServerInfo.m_ServerCount; i++)
	{
		if(m_ServerInfo.m_pServer[i].m_EnableDBShare)
		{
			if(m_ServerInfo.m_pServer[i].m_ItemSerialKey == key)
			{
				return m_ServerInfo.m_pServer[i].m_ServerID;
			}
		}
	}

	return -1;

	__UNGUARD__ return -1;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SettingSystem::LoadMonitorInfo()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	LoadMonitorInfo_Try();
				LoadStockMonitorInfo_Try();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	LoadMonitorInfo_Reload();

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SettingSystem::LoadMonitorInfo_Try()
{

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ Configer	ini(FILE_MONITOR_INFO);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	ini.GetText("System", "ServerIP", m_MonitorInfo.m_ServerIP, IP_SIZE);
	m_MonitorInfo.m_ServerPort = (uint32) ini.Get_Property_Int("System", "ServerPort");
	ini.GetText("System", "ClientIP", m_MonitorInfo.m_ClientIP, IP_SIZE);
	ini.GetText("System", "Account", m_MonitorInfo.m_Account, MAX_ACCOUNT);
	ini.GetText("System", "Password", m_MonitorInfo.m_Password, MAX_PASSWORD);

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SettingSystem::LoadStockMonitorInfo_Try()
{

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ Configer	ini(FILE_STOCK_MONITOR_INFO);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	ini.GetText("System", "ServerIP", m_StockMonitorInfo.m_ServerIP, IP_SIZE);
	m_StockMonitorInfo.m_ServerPort = (uint32) ini.Get_Property_Int("System", "ServerPort");
	ini.GetText("System", "ClientIP", m_StockMonitorInfo.m_ClientIP, IP_SIZE);
	ini.GetText("System", "ManagerAccount", m_StockMonitorInfo.m_Account, MAX_ACCOUNT);
	ini.GetText("System", "Password", m_StockMonitorInfo.m_Password, MAX_PASSWORD);

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SettingSystem::LoadMonitorInfo_Reload()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SettingSystem::PrintAllConfigInfo()
{
	QLogSystem::SLOW_LOG(m_LogPath, "################################################################################################################################");
	QLogSystem::SLOW_LOG(m_LogPath, "#				ALL SERVER CONFIG				");
	QLogSystem::SLOW_LOG(m_LogPath, "################################################################################################################################");
	//////////////////////////////////////////////////////////////////////////
	// Print WorldID
	QLogSystem::SLOW_LOG(m_LogPath, "# WorldID=%d", m_WorldInfo.m_WorldID);
	//////////////////////////////////////////////////////////////////////////
	// Print ServerIndex
	QLogSystem::SLOW_LOG(m_LogPath, "# ServerID=%d", m_ConfigInfo.m_ServerID);
	//////////////////////////////////////////////////////////////////////////
	// Print DBConfig
	QLogSystem::SLOW_LOG(m_LogPath, "# ShareType=%d", m_DBShareConfig.m_uShareType);
	//////////////////////////////////////////////////////////////////////////
	// Print ServersConfig
	QLogSystem::SLOW_LOG(m_LogPath, "# WorldIP=%s, WorldPort=%u", m_ServerInfo.m_World.m_IP, m_ServerInfo.m_World.m_Port);
	QLogSystem::SLOW_LOG(m_LogPath, "# AuthIP=%s, AuthPort=%u", m_ServerInfo.m_Auth.m_IP, m_ServerInfo.m_Auth.m_Port);
	QLogSystem::SLOW_LOG(m_LogPath, "# BillingIP=%s, BillingPort=%u", m_BillingInfo.m_IP, m_BillingInfo.m_Port);
	QLogSystem::SLOW_LOG(m_LogPath, "# DBCenterIP=%s, DBCenterPort=%u", m_DBCenterInfo.m_IP, m_DBCenterInfo.m_Port);
	QLogSystem::SLOW_LOG(m_LogPath, "#------------------------------------------------------------------------------------------------------------------------------#");
	QLogSystem::SLOW_LOG(m_LogPath, "# GLSMU EnableShareMem=%u", m_WorldInfo.m_EnableShareMem);
	QLogSystem::SLOW_LOG(m_LogPath, "# GLSMU MailSMKey=%u", m_WorldInfo.m_MailKey);
	QLogSystem::SLOW_LOG(m_LogPath, "# GLSMU CountrySMKey=%u", m_WorldInfo.m_CountryKey);
	QLogSystem::SLOW_LOG(m_LogPath, "# GLSMU SceneVarSMKey=%u", m_WorldInfo.m_SceneVarKey);
	QLogSystem::SLOW_LOG(m_LogPath, "# GLSMU TopListSMKey=%u", m_WorldInfo.m_TopListKey);
	QLogSystem::SLOW_LOG(m_LogPath, "# GLSMU ShopSMKey=%u", m_WorldInfo.m_ShopKey);
	QLogSystem::SLOW_LOG(m_LogPath, "# GLSMU BankSMKey=%u", m_WorldInfo.m_BankKey);
	QLogSystem::SLOW_LOG(m_LogPath, "# GLSMU MasterCandidateSMKey=%u", m_WorldInfo.m_MasterCandidateKey);
	QLogSystem::SLOW_LOG(m_LogPath, "# GLSMU PrenticeCandidateSMKey=%u", m_WorldInfo.m_PrenticeCandidateKey);
	QLogSystem::SLOW_LOG(m_LogPath, "# GLSMU StockCandidateSMKey=%u", m_WorldInfo.m_StockCandidateKey);
	QLogSystem::SLOW_LOG(m_LogPath, "# GLSMU StockAccCandidateSMKey=%u", m_WorldInfo.m_StockAccCandidateKey);
	QLogSystem::SLOW_LOG(m_LogPath, "# GLSMU StockRecordCandidateSMKey=%u", m_WorldInfo.m_StockRecordCandidateKey);
	QLogSystem::SLOW_LOG(m_LogPath, "#------------------------------------------------------------------------------------------------------------------------------#");
	QLogSystem::SLOW_LOG(m_LogPath, "# ServerCount=%d", m_ServerInfo.m_ServerCount);

	uint32 i;
	for(i = 0; i < m_ServerInfo.m_ServerCount; i++)
	{
		QLogSystem::SLOW_LOG(
			m_LogPath, 
			"# [%u] IP=%s, Port=%d, ServerID=%d, Type=%d, EnableSM=%d, MachineID=%d, HumanKey=%d, ItemKey=%d",
			i, 
			m_ServerInfo.m_pServer[i].m_IP, 
			m_ServerInfo.m_pServer[i].m_Port, 
			m_ServerInfo.m_pServer[i].m_ServerID,
			m_ServerInfo.m_pServer[i].m_Type,
			m_ServerInfo.m_pServer[i].m_EnableDBShare,
			m_ServerInfo.m_pServer[i].m_MachineID,
			m_ServerInfo.m_pServer[i].m_HumanSMKey,
			m_ServerInfo.m_pServer[i].m_ItemSerialKey
			);
	}
	QLogSystem::SLOW_LOG(m_LogPath, "################################################################################################################################");
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void SettingSystem::LoadPetConfigTable()
{
	
}

/*
=======================================================================================================================
 加载log服务器基本配置信息，主要是IP，Port
=======================================================================================================================
*/
void SettingSystem::LoadLogServerConfig()
{
	Configer ini(FILE_LOGSERVERCONFIG);

	m_LogServerInfo.m_bEnable = (uchar)(ini.Get_Property_Int("logserver", "Enable"));
	ini.GetText("logserver", "IP", m_LogServerInfo.m_ServerIP, IP_SIZE);
	m_LogServerInfo.m_ServerPort = (uint32) (ini.Get_Property_Int("logserver", "Port"));

#if ( defined(__LINUX__) && (defined(__MAPSERVER__) || defined(__GLSERVER__)) )
	if( m_LogServerInfo.m_bEnable == 1 )
		g_UdpSender.Init( m_LogServerInfo.m_ServerIP, m_LogServerInfo.m_ServerPort );
#endif
}

