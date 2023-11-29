#ifndef __NBINITREAD_H__
#define __NBINITREAD_H__
#include <map>
#include <string>
#include <list>
#include <vector>

#define MAX_FILE_PATH 260

struct sAttr
{
	std::string section;
	std::string value;
};

struct sGroup
{
	std::string group;
	std::vector<sAttr> sectionlist;
};


class  CIniRead
{
public:
	CIniRead( bool bUseSeq = false);
	~CIniRead();
private:
	void Parse( const char* data , int size );
	bool AddSection( const char*szGroup , const char*szSection , const char*szValue );
public:
	bool LoadIni( const char* filename );
	void Destroy();

	void GetValue( const char* szGroup , const char* szSection , int& nValue , int nDefault = 0);
	void GetValue( const char* szGroup , const char* szSection , float& value , float fDefault = 0.0f );
	void GetValue( const char* szGroup , const char* szSection , char* szValue , int size , const char* szDefault = "" );
	void GetValue( const char* szGroup , const char* szSection , std::string& strValue );

	void SetValue( const char* szGroup , const char* szSection , int value );
	void SetValue( const char* szGroup , const char* szSection , float fValue );
	void SetValue( const char* szGroup , const char* szSection , const char* szValue );

	bool SaveIni( const char* filename );

	std::vector<std::string> GetSectionList( const char* szGroup );
	std::vector<std::string> GetGroupList();
	std::map<std::string, std::string>* GetSecond( const char* szGroup );

	sGroup* FindGroup( const char* szGroup );
	sAttr* FindSection( sGroup* pGroup , const char* szSection );

	void SetGroup( const char* szGroup , const char* szSection , const char* szValue );
	void AddGroup( const char* szGroup , const char* szSection , const char* szValue );
private:
	void CutOffSpace( std::string& str );
private:
	char m_szFileName[MAX_FILE_PATH];
	char* m_pIniData;
	std::map< std::string ,std::map<std::string, std::string> > m_nIniMap;
	
	std::vector< sGroup > m_nGroupList;

	bool m_bUseSquence;

};
#endif //__NBINITREAD_H__
