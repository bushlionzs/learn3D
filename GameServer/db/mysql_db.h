
#pragma once

#include <mysql.h>
#include "record_set.h"
    class CMySQLRecordSet: public IRecordSet
    {
        friend class CMySQLConnection;
    public:
 
        CMySQLRecordSet(): m_res(NULL), m_row(NULL)
        {
        }
        
        ~CMySQLRecordSet()
        {
            clear();
        }
        
        virtual void clear() override
        {
            if (m_res)
                mysql_free_result(m_res);
            m_res = nullptr;
        }
     
        virtual uint32_t getRecordCount() override
        { 
            return (m_res ? (unsigned int)mysql_num_rows(m_res) : 0); 
        }
        
     
        virtual uint32_t getFieldCount() override
        { 
            return (m_res ? (unsigned int)mysql_num_fields(m_res) : 0); 
        }
        
        

        virtual bool getNextRecord() override
        {
            if (m_res == nullptr)
                return false;
            m_row = mysql_fetch_row(m_res);
            return (m_row != nullptr);
        }
        
        ///获取当前记录行中某一个字段的值
        const char* getFieldValue(unsigned int nIndex)
        {
            if (m_row == NULL)
                return NULL;
            if (nIndex >= getFieldCount())
                return NULL;
            return m_row[nIndex];
        }
    private:
        MYSQL_RES*  m_res;
        MYSQL_ROW   m_row;        
    };
    
    
    class CMySQLConnection: public IDBConnect
    {
    public:
        static CMySQLConnection* createConnection(const char* pszServerAddr, int nServerPort,
            const char* pszDBName, const char* pszUserID, const char* pszPassword)
        {
            CMySQLConnection* conn = new CMySQLConnection;
            conn->SetConnectionString(pszServerAddr, nServerPort, pszDBName, pszUserID, pszPassword);
            return conn;
        }
        typedef enum {Failed, NoRecordSet, HasRecordSet} EExecResult;

        CMySQLConnection(void);

        ~CMySQLConnection(void);
        
        void SetConnectionString(const char* pszServerAddr, int nServerPort, 
            const char* pszDBName, const char* pszUserID, const char* pszPassword);
        
        virtual bool connect() override;
        
        void Close();

        virtual bool isConnected() override;
        
        char* EscapeString(const char* pszSrc, int nSize, char* pszDest)
        {		
            if (m_myConnection)
            {
                mysql_real_escape_string(m_myConnection, pszDest, pszSrc, nSize);
                return pszDest;
            }
            else
                return NULL;
        }
        
        unsigned int GetAffectedRows() { return (unsigned int)mysql_affected_rows(m_myConnection); }
        
        char* EscapeString(const char* pszSrc, char* pszDest)
        {
            return EscapeString(pszSrc, (int)strlen(pszSrc), pszDest);
        }

        size_t EscapeStringEx(const char* pszSrc, int nSize, char* pszDest)
        {
            if (m_myConnection)
            {
                return mysql_real_escape_string(m_myConnection, pszDest, pszSrc, nSize);
            }
            else
            {
                return NULL;
            }
        }
        
        
        virtual bool execute(const char* sql) override;
        
        virtual uint32_t getLastError() override
        { 
            if(m_myConnection!=NULL)
            {
                return (DWORD)mysql_errno(m_myConnection);
            }
            return  0;
        }
        
        const char* GetLastErrorInfo()
        { 
            if(m_myConnection!=NULL)
            {
                return mysql_error(m_myConnection);
            }
            return NULL;
        }

        virtual IRecordSet* getRecordSet()
        {
            return &mRecordSet;
        }
        
    private:

        char    m_szServerAddr[24];
        char    m_szDBName[24];
        char    m_szUserID[24];
        char    m_szPassword[24];
        
        int     m_nServerPort;
        MYSQL*  m_myConnection;
        BOOL    m_bConnected;

        CMySQLRecordSet mRecordSet;
    };
