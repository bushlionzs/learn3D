#include "stdafx.h"
#include "mysql_db.h"

#pragma comment(lib, "libmysql.lib")


CMySQLConnection::CMySQLConnection(void)
{
    memset(m_szServerAddr, 0, sizeof(m_szServerAddr));
    memset(m_szDBName, 0, sizeof(m_szDBName));
    memset(m_szUserID, 0, sizeof(m_szUserID));
    memset(m_szPassword, 0, sizeof(m_szPassword));
    m_myConnection = mysql_init(NULL);
    m_bConnected   = FALSE;
}

CMySQLConnection::~CMySQLConnection(void)
{
    if (m_myConnection)
    {
        mysql_close(m_myConnection);
    }
}

void   CMySQLConnection::SetConnectionString(const char* pszServerAddr, int nServerPort, 
                                                  const char* pszDBName, const char* pszUserID, const char* pszPassword)
{
    strncpy(m_szServerAddr, pszServerAddr, sizeof(m_szServerAddr) - 1);
    strncpy(m_szDBName, pszDBName, sizeof(m_szDBName) - 1);
    strncpy(m_szUserID, pszUserID, sizeof(m_szUserID) - 1);
    strncpy(m_szPassword, pszPassword, sizeof(m_szPassword) - 1);
    m_nServerPort = nServerPort ;
}

BOOL  CMySQLConnection::Connect(const char* pszServerAddr, int nServerPort, 
                                     const char* pszDBName, const char* pszUserID, const char* pszPassword)
{
    SetConnectionString(pszServerAddr, nServerPort, pszDBName, pszUserID, pszPassword);
    return Connect();
}

BOOL  CMySQLConnection::Connect()
{
    if (m_myConnection == NULL)
    {
        m_myConnection = mysql_init(NULL);
    }
    if (m_myConnection == NULL)
    {
        return FALSE;
    }

    MYSQL* myConn = mysql_real_connect(m_myConnection, m_szServerAddr, 
        m_szUserID, m_szPassword, m_szDBName, m_nServerPort, NULL, 0);
    if (!myConn)
    {
        Close();
        return FALSE;
    }
    m_bConnected = TRUE;
    return TRUE;
}

void  CMySQLConnection::Close()
{
    mysql_close(m_myConnection);
    m_myConnection = NULL;
    m_bConnected   = FALSE;
}

BOOL  CMySQLConnection::IsConnected()
{
    if(!m_bConnected)
    {
        return  FALSE;
    }
    return (mysql_ping(m_myConnection)==0);
}

BOOL  CMySQLConnection::Execute(const char* pszSQL)
{
    return (0 == mysql_query(m_myConnection, pszSQL));
}

BOOL  CMySQLConnection::Execute(const char* pszSQL, CMySQLRecordSet& rcdSet)
{
    if (0 != mysql_query(m_myConnection, pszSQL))
        return FALSE;
    if (rcdSet.m_res)
        mysql_free_result(rcdSet.m_res); 
    rcdSet.m_res = mysql_store_result(m_myConnection);
    return (rcdSet.m_res != NULL);
}

int  CMySQLConnection::ExecuteEx(const char* pszSQL, CMySQLRecordSet& rcdSet)
{
    
    if (0 != mysql_query(m_myConnection, pszSQL))
        return Failed;
    if (rcdSet.m_res)
        mysql_free_result(rcdSet.m_res); 
    rcdSet.m_res = mysql_store_result(m_myConnection);
    if(rcdSet.m_res != NULL)
    {
        return HasRecordSet;       ///Rescord Set
    }
    
    if(!mysql_field_count(m_myConnection))
    {
        return  NoRecordSet;       ///NO Rescord Set
    }
    return  Failed;
    
}

int   CMySQLConnection::ExecuteEx(const char* pszSQL, int nLength,CMySQLRecordSet& rcdSet)
{
    if (0 != mysql_real_query(m_myConnection, pszSQL,nLength))
        return Failed;
    if (rcdSet.m_res)
        mysql_free_result(rcdSet.m_res); 
    rcdSet.m_res = mysql_store_result(m_myConnection);
    if(rcdSet.m_res != NULL)
    {
        return HasRecordSet;       ///Rescord Set
    }

    if(!mysql_field_count(m_myConnection))
    {
        return  NoRecordSet;       ///NO Rescord Set
    }
    return  Failed;
}

