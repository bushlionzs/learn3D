
#pragma once

#include <mysql.h>



/**
@brief 封装MySQL的记录集
*
*	封装MySQL的记录集，不可由多个线程同时操作本对象实例
*/

    class CMySQLRecordSet
    {
        friend class CMySQLConnection;
    public:
        ///构造函数
        CMySQLRecordSet(): m_res(NULL), m_row(NULL)
        {
        }
        
        ///析构函数
        ~CMySQLRecordSet()
        {
            Clear();
        }
        
        void Clear()
        {
            if (m_res)
                mysql_free_result(m_res);
            m_res = nullptr;
        }
        ///获取记录个数
        unsigned int GetRecordCount() { return (m_res ? (unsigned int)mysql_num_rows(m_res) : 0); }
        
        ///获取字段个数
        unsigned int GetFieldCount() { return (m_res ? (unsigned int)mysql_num_fields(m_res) : 0); }
        
        
        ///获取下一个记录行
        BOOL GetRecord()
        {
            if (m_res == NULL)
                return FALSE;
            m_row = mysql_fetch_row(m_res);
            return (m_row != NULL);
        }
        
        ///获取当前记录行中某一个字段的值
        const char* GetFieldValue(unsigned int nIndex)
        {
            if (m_row == NULL)
                return NULL;
            if (nIndex >= GetFieldCount())
                return NULL;
            return m_row[nIndex];
        }
    private:
        MYSQL_RES*  m_res;
        MYSQL_ROW   m_row;        
    };
    
/**
@brief 封装MySQL的连接
*
*	封装MySQL的连接，不可由多个线程同时操作本对象实例
*/
    
    class CMySQLConnection
    {
    public:
        ///定义ExecuteEx的返回值
        typedef enum {Failed, NoRecordSet, HasRecordSet} EExecResult;

        ///构造函数
        CMySQLConnection(void);

        ///析构函数
        ~CMySQLConnection(void);
        
        ///设置连接信息
        void SetConnectionString(const char* pszServerAddr, int nServerPort, 
            const char* pszDBName, const char* pszUserID, const char* pszPassword);
        
        ///打开连接
        BOOL Connect(const char* pszServerAddr, int nServerPort, 
            const char* pszDBName, const char* pszUserID, const char* pszPassword);
        
        ///打开连接，在设置连接信息后调用
        BOOL Connect();
        
        ///关闭连接
        void Close();
        
        ///是否已连接
        BOOL IsConnected();
        
        ///转义字符串，使之可用于MYSQL查询
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
        
        ///返回受到最后一个UPDATE、DELETE或INSERT查询影响(变化)的行数
        unsigned int GetAffectedRows() { return (unsigned int)mysql_affected_rows(m_myConnection); }
        
        ///转义字符串，使之可用于MYSQL查询
        char* EscapeString(const char* pszSrc, char* pszDest)
        {
            return EscapeString(pszSrc, (int)strlen(pszSrc), pszDest);
        }

        ///转义字符串，使之可用于MYSQL查询，主要用在转意2进制数据
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
        
        ///无差别执行SQL语句，通过返回值判断具体效果
        int  ExecuteEx(const char* pszSQL, CMySQLRecordSet& rcdSet);
        ///无差别执行SQL语句，通过返回值判断具体效果(支持二进制代码数据)
        int  ExecuteEx(const char* pszSQL, int nLength,CMySQLRecordSet& rcdSet);

        ///执行一条SQL语句，不返回记录集
        BOOL Execute(const char* pszSQL);
        
        ///执行一条SQL语句，返回记录集
        BOOL Execute(const char* pszSQL, CMySQLRecordSet& rcdSet);
        
        ///获取上一次错误号
        DWORD GetLastError() 
        { 
            if(m_myConnection!=NULL)
            {
                return (DWORD)mysql_errno(m_myConnection);
            }
            return  0;
        }
        
        ///获取上一次错误描述
        const char* GetLastErrorInfo()
        { 
            if(m_myConnection!=NULL)
            {
                return mysql_error(m_myConnection);
            }
            return NULL;
        }
        
    private:

        char    m_szServerAddr[24];
        char    m_szDBName[24];
        char    m_szUserID[24];
        char    m_szPassword[24];
        
        int     m_nServerPort;
        MYSQL*  m_myConnection;
        BOOL    m_bConnected;
    };
