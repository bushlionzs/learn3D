#include "inifile.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

using namespace std;

CIniRead::CIniRead( bool bUseSeq )
{
	memset( m_szFileName , 0 , sizeof( m_szFileName ) );
	m_pIniData = NULL;

	m_bUseSquence = bUseSeq;
}

CIniRead::~CIniRead()
{
	Destroy();
}


bool CIniRead::LoadIni( const char* filename )
{
	if ( NULL == filename || strlen(filename) <= 0 )
	{
		return false;
	}

	try
	{
		FILE* fp = fopen( filename , "rb" );

		if( fp == NULL )
			return false;

		fseek( fp , 0 , SEEK_END );
		
		int filelen = ftell( fp );

		fseek( fp , 0 , SEEK_SET );

		m_pIniData = new char[ filelen ];
		fread( m_pIniData , 1 , filelen , fp );
		fclose(fp );
		Parse( m_pIniData , filelen );
		delete m_pIniData;m_pIniData=NULL;
		return true;
	}
	catch (...)
	{
	}

	return false;
}

void CIniRead::Destroy()
{
	if( m_pIniData )
	{
		delete m_pIniData;
		m_pIniData = NULL;
	}
	m_nIniMap.clear();

	m_nGroupList.clear();
}

void CIniRead::Parse( const char* data , int size )
{
	int index = 0;
	char szGroup[256];
	char szSection[256];
	char szValue[256];
	char szCurrText[256];
	int  currTextIndex = 0;
	
	enum
	{
		state_expectLeftBracket = 0,
		state_findGroup = 1,
		state_expectRightBracket = 2,
		state_expectSection = 3,
		state_expectEqualSign = 4,
		state_expectValue    = 5,
	};
	int state = state_expectLeftBracket;
	while( index < size )
	{
		char c = data[index];
		switch( state )
		{
		case state_expectLeftBracket:
			{
				if( c == '[' )
				{
					state = state_findGroup;
				}
			}
			break;
		case state_expectRightBracket:
			{
				if( c == ']' )
				{
					state = state_expectSection;
				}
				if( c == '\n' )
					state = state_expectLeftBracket;
			}
			break;
		case state_expectEqualSign:
			{
				if( c == '=' )
					state = state_expectValue;
				if( c == '\n' )
					state = state_expectSection;
			}
			break;
		case state_findGroup:
			{
				switch( c )
				{
				case ']':
					szCurrText[ currTextIndex ] = 0;
					state = state_expectSection;
					break;
				case '\t':
					{
						if( currTextIndex > 0 )
						{
							szCurrText[ currTextIndex ] = 0;
							state = state_expectRightBracket;
						}
					}
					break;
				case 0x0d:
				case '\n':
					state = state_expectLeftBracket;
					break;
				}
				if( state == state_findGroup )
				{
					if(  c != '\n' && c != '\t'&& c != 0x0d )
						szCurrText[currTextIndex++] = c;
				}
				else
				{
					strcpy( szGroup , szCurrText );
					currTextIndex = 0;
				}
			}
			break;
		case state_expectSection:
			{
				switch( c )
				{
				case '[':
					if( currTextIndex == 0 )
					{
						state = state_findGroup;
						szCurrText[0] = 0;
					}
					break;
				case 0x0d:
					break;
				case '\n':
				case '\t':
					szCurrText[ currTextIndex ] = 0;
					if( currTextIndex > 0 )
					{
						state = state_expectEqualSign;
					}
					break;
				case '=':
					szCurrText[ currTextIndex ] = 0;
					if( currTextIndex > 0 )
					{
						state = state_expectValue;
					}
					break;
				}
				if( state == state_expectSection )
				{
					if(  c != '\n' && c != '\t'&& c != 0x0d )
						szCurrText[currTextIndex++] = c;
				}
				else
				{
					strcpy( szSection , szCurrText );
					currTextIndex = 0;
				}
			}
			break;
		case state_expectValue:
			{
				switch( c )
				{
				case '\t':
					if( currTextIndex > 0 )
					{
						szCurrText[ currTextIndex ] = 0;
						state = state_expectEqualSign;
					}
					break;
				case 0x0d:
				case '\n':
					{
						szCurrText[ currTextIndex ] = 0;
						state = state_expectSection;
					}
					break;
				}
				if( state == state_expectValue )
				{
					if(  c != '\n' && c != '\t'&& c != 0x0d )
					{
						szCurrText[currTextIndex++] = c;
						if( index == size - 1 )
						{
							szCurrText[currTextIndex]=0;
							strcpy( szValue , szCurrText );
							currTextIndex = 0;
							AddSection( szGroup , szSection , szValue );
						}
					}
				}
				else
				{
					strcpy( szValue , szCurrText );
					currTextIndex = 0;
					AddSection( szGroup , szSection , szValue );
				}
			}
			break;
		}
		index++;
	}
}


bool CIniRead::AddSection( const char* szGroup , const char*szSection , const char*szValue )
{
	string group = szGroup;
	string section = szSection;
	string value   = szValue;

	CutOffSpace( group );
	CutOffSpace( section );
	CutOffSpace( value );

	map< string , map<string,string> >::iterator itor = m_nIniMap.find( group );
	if( itor != m_nIniMap.end() )
	{

		itor->second[section] =  value ;

	}
	else
	{
		m_nIniMap[group].insert( make_pair( section , value ) );
	}
	return true;
}

void CIniRead::GetValue( const char* szGroup , const char* szSection , int& nValue , int nDefault )
{
	string group = szGroup;
	string section = szSection;
	nValue = nDefault;
	map< string , map<string,string> >::iterator itor = m_nIniMap.find( group );
	if( itor != m_nIniMap.end() )
	{
		map<string,string>::iterator itor2 = itor->second.find( section );;
		if( itor2 != itor->second.end() )
		{
			nValue = atoi( itor2->second.c_str() );
		}
	}
	
}

void CIniRead::GetValue( const char* szGroup , const char* szSection , float& fValue , float fDefault )
{
	string group = szGroup;
	string section = szSection;
	fValue = fDefault;
	map< string , map<string,string> >::iterator itor = m_nIniMap.find( group );
	if( itor != m_nIniMap.end() )
	{
		map<string,string>::iterator itor2 = itor->second.find( section );;
		if( itor2 != itor->second.end() )
		{
			fValue = (float)atof( itor2->second.c_str() );
		}
	}
	
}

void CIniRead::GetValue( const char* szGroup , const char* szSection , char* szValue , int size , const char* szDefault)
{
	szValue[0] = 0;
	string group = szGroup;
	string section = szSection;
	strncpy( szValue , szDefault , size );
	map< string , map<string,string> >::iterator itor = m_nIniMap.find( group );
	if( itor != m_nIniMap.end() )
	{
		map<string,string>::iterator itor2 = itor->second.find( section );;
		if( itor2 != itor->second.end() )
		{
			strncpy( szValue , itor2->second.c_str() , size );
		}
	}
	
}

void CIniRead::GetValue( const char* szGroup , const char* szSection , std::string& strValue )
{
	string group = szGroup;
	string section = szSection;
	map< string , map<string,string> >::iterator itor = m_nIniMap.find( group );
	if( itor != m_nIniMap.end() )
	{
		map<string,string>::iterator itor2 = itor->second.find( section );;
		if( itor2 != itor->second.end() )
		{
			strValue = itor2->second;
		}
	}
}

void CIniRead::SetGroup( const char* szGroup , const char* szSection , const char* szValue )
{
	if( !m_bUseSquence )
		return;
	sGroup* pGroup = FindGroup( szGroup );
	sAttr* pAttr = FindSection( pGroup , szSection );
	if( pAttr )
	{
		pAttr->value = szValue;
	}
	else
	{
		sAttr attr;
		attr.section = szSection;
		attr.value   = szValue;
		pGroup->sectionlist.push_back( attr );
	}
}

void CIniRead::AddGroup( const char* szGroup , const char* szSection , const char* szValue )
{
	if( !m_bUseSquence )
		return;
	sGroup group;
	group.group = szGroup;
	sAttr attr;
	attr.section = szSection;
	attr.value   = szValue;
	group.sectionlist.push_back( attr );

	m_nGroupList.push_back( group );
}

void CIniRead::SetValue( const char* szGroup , const char* szSection , int nValue )
{
	string group = szGroup;
	string section = szSection;
	char buf[256];
	sprintf( buf , "%d" , nValue );
	string value   = buf;

	CutOffSpace( group );
	CutOffSpace( section );
	CutOffSpace( value );

	map< string , map<string,string> >::iterator itor = m_nIniMap.find( group );
	if( itor != m_nIniMap.end() )
	{
		itor->second[ section ] = value;

		SetGroup( group.c_str() , section.c_str() , value.c_str() );

	}
	else
	{
		AddSection( szGroup , szSection , buf );

		AddGroup( group.c_str() , section.c_str() , value.c_str() );
	}

}

void CIniRead::SetValue( const char* szGroup , const char* szSection , float fValue )
{
	string group = szGroup;
	string section = szSection;
	char buf[256];
	sprintf( buf , "%f" , fValue );
	string value   = buf;

	CutOffSpace( group );
	CutOffSpace( section );
	CutOffSpace( value );

	map< string , map<string,string> >::iterator itor = m_nIniMap.find( group );
	if( itor != m_nIniMap.end() )
	{
		itor->second[ section ] = value;

		SetGroup( group.c_str() , section.c_str() , value.c_str() );
	}
	else
	{
		AddSection( szGroup , szSection , buf );

		AddGroup( group.c_str() , section.c_str() , value.c_str() );
	}

}

void CIniRead::SetValue( const char* szGroup , const char* szSection , const char* szValue )
{
	string group = szGroup;
	string section = szSection;
	string value   = szValue;

	CutOffSpace( group );
	CutOffSpace( section );
	CutOffSpace( value );

	map< string , map<string,string> >::iterator itor = m_nIniMap.find( group );
	if( itor != m_nIniMap.end() )
	{
		itor->second[ section ] = value;
		SetGroup( group.c_str() , section.c_str() , value.c_str() );
	}
	else
	{
		AddSection( szGroup , szSection , szValue );
		AddGroup( group.c_str() , section.c_str() , value.c_str() );
	}

}

bool CIniRead::SaveIni( const char* filename )
{
	FILE* fp = fopen( filename , "wb" );
	if( fp == NULL )
		return false;

			const char* left = "[";
		const char* right = "]";
		const char* equal = "=";
		const char newline[2] = {0x0d,0x0a};

	if( !m_bUseSquence )
	{
		map< string , map<string,string> >::iterator itor = m_nIniMap.begin();

		

		for( ; itor != m_nIniMap.end() ; itor++ )
		{
			fwrite( left , 1 , 1 , fp );
			fwrite( itor->first.c_str() , 1 , itor->first.length() , fp );
			fwrite( right , 1 , 1 , fp );
			fwrite( newline , 1 , 2 , fp );
			map<string , string>::iterator itor2 = itor->second.begin();
			for( ; itor2 != itor->second.end(); itor2++ )
			{
				fwrite( itor2->first.c_str() , 1 , itor2->first.length() , fp );
				fwrite( equal , 1 , 1 , fp );
				fwrite( itor2->second.c_str() , 1 , itor2->second.length() , fp );
				fwrite( newline , 1 ,2 , fp );
			}
		}
	}
	else
	{
		for( int i = 0; i < (int)m_nGroupList.size(); i++ )
		{
			sGroup& group = m_nGroupList.at(i);

			fwrite( left , 1 , 1 , fp );
			fwrite( group.group.c_str() , 1 , group.group.length() , fp );
			fwrite( right , 1 , 1 , fp );
			fwrite( newline , 1 , 2 , fp );

			for( int j = 0 ; j < (int)group.sectionlist.size(); j++ )
			{
				sAttr& attr = group.sectionlist.at(j);
				fwrite( attr.section.c_str() , 1 , attr.section.length() ,  fp );
				fwrite( equal , 1 , 1 , fp );
				fwrite( attr.value.c_str() , 1 , attr.value.length() , fp );
				fwrite( newline , 1 , 2 , fp );
			}
			fwrite( newline , 1 , 2 , fp );
		}
	}

	fclose(fp);

	return true;


}

void CIniRead::CutOffSpace( string & str )
{
	int start = (int)str.find_first_not_of( ' ' );
	int end = (int)str.find_last_not_of( ' ');

	if( start == - 1 )
		start = 0;
	if( end == -1 )
		return;

	string substr = str.substr( start , end - start + 1 );

	str = substr;
}

vector<string> CIniRead::GetSectionList( const char* szGroup )
{
	vector<string> retlist;

	string group = szGroup;

	map< string , map<string,string> >::iterator itor = m_nIniMap.find( group );
	if( itor != m_nIniMap.end() )
	{
		map<string,string>& submap = itor->second;

		map<string,string>::iterator subItor = submap.begin();
		for( ; subItor != submap.end(); subItor++ )
		{
			retlist.push_back( (*subItor).first );
		}
	}

	return retlist;
}

vector<string> CIniRead::GetGroupList()
{
	vector<string> retlist;

	map< string , map<string,string> >::iterator itor = m_nIniMap.begin();

	for( ; itor != m_nIniMap.end(); itor++ )
	{
		retlist.push_back( (*itor).first );
	}


	return retlist;
}

map<string,string>* CIniRead::GetSecond( const char* szGroup )
{
	string group = szGroup;

	map< string , map<string,string> >::iterator itor = m_nIniMap.find( group );

	if( itor != m_nIniMap.end() )
	{
		return &itor->second;
	}
	return NULL;
}

sGroup* CIniRead::FindGroup( const char* szGroup )
{
	for( int i = 0 ; i < (int)m_nGroupList.size(); i++ )
	{
		sGroup& group = m_nGroupList.at(i);
		if( strcmp( group.group.c_str() , szGroup ) == 0 )
			return &group;
	}
	return NULL;
}

sAttr* CIniRead::FindSection(sGroup* pGroup  , const char* szSection )
{
	vector<sAttr>& sectionlist = pGroup->sectionlist;

	for( int i = 0 ; i < (int)sectionlist.size(); i++ )
	{
		sAttr& attr = sectionlist.at(i);
		if( strcmp( attr.section.c_str() , szSection ) == 0 )
			return &attr;
	}
	return NULL;
}
