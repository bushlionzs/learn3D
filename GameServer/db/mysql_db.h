
#pragma once

#include <mysql.h>



/**
@brief ��װMySQL�ļ�¼��
*
*	��װMySQL�ļ�¼���������ɶ���߳�ͬʱ����������ʵ��
*/

    class CMySQLRecordSet
    {
        friend class CMySQLConnection;
    public:
        ///���캯��
        CMySQLRecordSet(): m_res(NULL), m_row(NULL)
        {
        }
        
        ///��������
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
        ///��ȡ��¼����
        unsigned int GetRecordCount() { return (m_res ? (unsigned int)mysql_num_rows(m_res) : 0); }
        
        ///��ȡ�ֶθ���
        unsigned int GetFieldCount() { return (m_res ? (unsigned int)mysql_num_fields(m_res) : 0); }
        
        
        ///��ȡ��һ����¼��
        BOOL GetRecord()
        {
            if (m_res == NULL)
                return FALSE;
            m_row = mysql_fetch_row(m_res);
            return (m_row != NULL);
        }
        
        ///��ȡ��ǰ��¼����ĳһ���ֶε�ֵ
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
@brief ��װMySQL������
*
*	��װMySQL�����ӣ������ɶ���߳�ͬʱ����������ʵ��
*/
    
    class CMySQLConnection
    {
    public:
        ///����ExecuteEx�ķ���ֵ
        typedef enum {Failed, NoRecordSet, HasRecordSet} EExecResult;

        ///���캯��
        CMySQLConnection(void);

        ///��������
        ~CMySQLConnection(void);
        
        ///����������Ϣ
        void SetConnectionString(const char* pszServerAddr, int nServerPort, 
            const char* pszDBName, const char* pszUserID, const char* pszPassword);
        
        ///������
        BOOL Connect(const char* pszServerAddr, int nServerPort, 
            const char* pszDBName, const char* pszUserID, const char* pszPassword);
        
        ///�����ӣ�������������Ϣ�����
        BOOL Connect();
        
        ///�ر�����
        void Close();
        
        ///�Ƿ�������
        BOOL IsConnected();
        
        ///ת���ַ�����ʹ֮������MYSQL��ѯ
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
        
        ///�����ܵ����һ��UPDATE��DELETE��INSERT��ѯӰ��(�仯)������
        unsigned int GetAffectedRows() { return (unsigned int)mysql_affected_rows(m_myConnection); }
        
        ///ת���ַ�����ʹ֮������MYSQL��ѯ
        char* EscapeString(const char* pszSrc, char* pszDest)
        {
            return EscapeString(pszSrc, (int)strlen(pszSrc), pszDest);
        }

        ///ת���ַ�����ʹ֮������MYSQL��ѯ����Ҫ����ת��2��������
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
        
        ///�޲��ִ��SQL��䣬ͨ������ֵ�жϾ���Ч��
        int  ExecuteEx(const char* pszSQL, CMySQLRecordSet& rcdSet);
        ///�޲��ִ��SQL��䣬ͨ������ֵ�жϾ���Ч��(֧�ֶ����ƴ�������)
        int  ExecuteEx(const char* pszSQL, int nLength,CMySQLRecordSet& rcdSet);

        ///ִ��һ��SQL��䣬�����ؼ�¼��
        BOOL Execute(const char* pszSQL);
        
        ///ִ��һ��SQL��䣬���ؼ�¼��
        BOOL Execute(const char* pszSQL, CMySQLRecordSet& rcdSet);
        
        ///��ȡ��һ�δ����
        DWORD GetLastError() 
        { 
            if(m_myConnection!=NULL)
            {
                return (DWORD)mysql_errno(m_myConnection);
            }
            return  0;
        }
        
        ///��ȡ��һ�δ�������
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
