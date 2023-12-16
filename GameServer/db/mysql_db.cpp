#include "stdafx.h"
#include "mysql_db.h"


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


bool  CMySQLConnection::connect()
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

bool  CMySQLConnection::isConnected()
{
    if(!m_bConnected)
    {
        return  FALSE;
    }
    return (mysql_ping(m_myConnection)==0);
}


bool  CMySQLConnection::execute(const char* sql)
{
    if (0 != mysql_query(m_myConnection, sql))
        return FALSE;
    if (mRecordSet.m_res)
        mysql_free_result(mRecordSet.m_res);
    mRecordSet.m_res = mysql_store_result(m_myConnection);
    return (mRecordSet.m_res != NULL);
}


