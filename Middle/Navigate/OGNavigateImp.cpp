/********************************************************************
	created:	2008/03/05
	created:	5:3:2008   16:48
	file base:	NeSDKImp
	file ext:	cpp
	author:		½ªÍþ
	email:		jiang628@hotmail.com
	purpose:	
*********************************************************************/
#include "OgreHeader.h"
#include "OGNavigateImp.h"
#include "OGNavigateSpaceImp.h"
#include "OGNavigateUtilLibImp.h"

namespace Orphigine 
{

NeSDKImp::NeSDKImp()
{
	m_spaces.clear();
	m_utilLib = NULL;
}

NeSDKImp::~NeSDKImp()
{
	for (int i = 0;i < (int)m_spaces.size();i ++)
	{
		delete (NeSpaceImp*)m_spaces[i];
		m_spaces[i] = NULL;

	}

	m_spaces.clear();
}
NeSpace* NeSDKImp::createSpace()
{
	NeSpace* tmpSpace = new NeSpaceImp();

	m_spaces.push_back(tmpSpace);

	return tmpSpace;
}

void NeSDKImp::removeSpace( NeSpace* space )
{
	std::vector<NeSpace*>::iterator iter = find(m_spaces.begin(),m_spaces.end(),space);

	if(m_spaces.end() != iter)
	{
		delete (NeSpaceImp*)(*iter);
		(*iter) = NULL;

		m_spaces.erase(iter);
	}
}

NeSpace* NeSDKImp::getSpace( int index ) const
{
	return m_spaces[index];
}

NeUtilLib* NeSDKImp::getUtilLib()
{
	if(NULL == m_utilLib)
		m_utilLib = new NeUtilLibImp();

	return m_utilLib;
}

} // namespace Orphigine
