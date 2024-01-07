

#include "CEGUIHyperLinkManager.h"
#include "CEGUIHyperLink.h"
#include "CEGUILogger.h"
#include "CEGUIWindow.h"
#include "CEGUIMouseCursor.h"


namespace CEGUI
{
	const String HyperLinkManager::EventNamespace("HyperLinkManager");

    
    
    const String HyperLinkManager::EventHyperLinkActive("HyperLinkActive");
	const String HyperLinkManager::EventHyperLinkLeftActive("HyperLinkLeftActive");
	const String HyperLinkManager::EventHyperLinkRightActive("HyperLinkRightActive");
    const String HyperLinkManager::EventHyperLinkInactive("HyperLinkInactive");
	



template<> HyperLinkManager* Singleton<HyperLinkManager>::ms_Singleton	= NULL;




HyperLinkManager::HyperLinkManager(void)
{
	
	d_curKeyHyperLink = "";
}


HyperLinkManager::~HyperLinkManager(void)
{
	
}

HyperLinkManager& HyperLinkManager::getSingleton(void)
{
	return Singleton<HyperLinkManager>::getSingleton();
}


HyperLinkManager* HyperLinkManager::getSingletonPtr(void)
{
	return Singleton<HyperLinkManager>::getSingletonPtr();
}



void HyperLinkManager::destroyHyperLink(const String name)
{
	HyperLinkNameRegistry::iterator pos = d_HyperLinkNameMap.find(name);

	if (pos != d_HyperLinkNameMap.end())
	{
		pos->second.CleanUp();

		d_HyperLinkNameMap.erase(pos);
	}
}



void HyperLinkManager::destroyAllHyperLink(void)
{
	while (!d_HyperLinkNameMap.empty())
	{
		destroyHyperLink(d_HyperLinkNameMap.begin()->first);
	}
}


bool HyperLinkManager::addHyperLink(const Window* OwnerWindow,const String name, const Rect hyper_rect, unsigned long guid )
{
	

	HyperLinkNameRegistry::iterator pos = d_HyperLinkNameMap.find(name);

	if( guid != 0 )
		((Window*)OwnerWindow)->setHyperLinkRuntime(guid, name, hyper_rect);

	if (pos != d_HyperLinkNameMap.end())
	{
		pos->second.addNewRect(OwnerWindow,hyper_rect, guid);
	}
	else
	{
		HyperLink newHyperLink;
		newHyperLink.CleanUp();
		newHyperLink.d_name = name;
		newHyperLink.addNewRect(OwnerWindow,hyper_rect, guid);

		d_HyperLinkNameMap[name] = newHyperLink;
	}

	if( d_curKeyHyperLink == name )
		return true;

	return false;
}

bool HyperLinkManager::isHyperLinkRange(const Window* pOwnerWindow, const Point& position, int &gamecursor)
{
	HyperLinkNameRegistry::const_iterator itCur, itEnd;
	HyperLink nHyperLink;

	itCur		= d_HyperLinkNameMap.begin();
	itEnd		= d_HyperLinkNameMap.end();

	while ( itCur != itEnd )
	{
		nHyperLink = itCur->second;

		if(nHyperLink.isInRange(pOwnerWindow,position))
		{
			HyperLinkEventArgs e(pOwnerWindow->getName(), nHyperLink.d_name);

			fireEvent(EventHyperLinkInactive, e, EventNamespace);		

			d_curKeyHyperLink = nHyperLink.d_name;
			gamecursor = getHyperLinkCursor(nHyperLink.d_name);

			return true;
		}
		else
		{
			String str = pOwnerWindow->getHyperLinkContex(&position);
			if( !str.empty() )
			{
				HyperLinkEventArgs e(pOwnerWindow->getName(), str);

				fireEvent(EventHyperLinkActive, e, EventNamespace);
				d_curKeyHyperLink = str;
				gamecursor = getHyperLinkCursor(d_curKeyHyperLink);

				return true;
			}
		}

		itCur++;
	}

    if( !d_curKeyHyperLink.empty() )
	{
		d_curKeyHyperLink = "";
		MouseCursor::getSingleton().setGameCursor(-1);
	}

	return false;
}


String HyperLinkManager::getHyperLinkContex(const Window* pOwnerWindow, const Point& position)
{
	HyperLinkNameRegistry::const_iterator itCur, itEnd;
	HyperLink nHyperLink;

	itCur		= d_HyperLinkNameMap.begin();
	itEnd		= d_HyperLinkNameMap.end();

	while ( itCur != itEnd )
	{
		nHyperLink = itCur->second;

		if(nHyperLink.isInRange(pOwnerWindow,position) )
		{
			return nHyperLink.d_name;
		}
		else
		{
			String str = pOwnerWindow->getHyperLinkContex(&position);
			if( !str.empty() )
			{
				return str;
			}
		}

		itCur++;
	}
	return "";
}

bool HyperLinkManager::doHyperLink(const Window* pOwnerWindow,const Point& position)
{

	HyperLinkNameRegistry::const_iterator itCur, itEnd;
	HyperLink nHyperLink;

	itCur		= d_HyperLinkNameMap.begin();
	itEnd		= d_HyperLinkNameMap.end();

	while ( itCur != itEnd )
	{
		nHyperLink = itCur->second;

		if(nHyperLink.isInRange(pOwnerWindow,position))
		{
			HyperLinkEventArgs e(pOwnerWindow->getName(), nHyperLink.d_name);

			fireEvent(EventHyperLinkActive, e, EventNamespace);
			return true;
		}

		itCur++;
	}
	return false;

}

bool HyperLinkManager::doHyperLinkByMouseLeft(const Window* pOwnerWindow,const Point& position)
{

	HyperLinkNameRegistry::const_iterator itCur, itEnd;
	HyperLink nHyperLink;

	itCur		= d_HyperLinkNameMap.begin();
	itEnd		= d_HyperLinkNameMap.end();

	while ( itCur != itEnd )
	{
		nHyperLink = itCur->second;

		if(nHyperLink.isInRange(pOwnerWindow,position))
		{
			HyperLinkEventArgs e(pOwnerWindow->getName(), nHyperLink.d_name);

			onHyperLinkLeftActive(e);
			return true;
		}

		itCur++;
	}

	return false;
}

bool HyperLinkManager::doHyperLinkByMouseRight(const Window* pOwnerWindow,const Point& position)
{

	HyperLinkNameRegistry::const_iterator itCur, itEnd;
	HyperLink nHyperLink;

	itCur		= d_HyperLinkNameMap.begin();
	itEnd		= d_HyperLinkNameMap.end();

	while ( itCur != itEnd )
	{
		nHyperLink = itCur->second;

		if(nHyperLink.isInRange(pOwnerWindow,position))
		{
			HyperLinkEventArgs e(pOwnerWindow->getName(), nHyperLink.d_name);

			onHyperLinkRightActive(e);
			return true;
		}

		itCur++;
	}
	return false;

}

int HyperLinkManager::getHyperLinkCursor( const String& hyperLink )
{
	if ( hyperLink.find("mission_") != hyperLink.npos )
		return 21;
	else if ( hyperLink.find("item_") != hyperLink.npos )
		return 21;
	else if ( hyperLink.find("mission_") != hyperLink.npos )
		return 21;
	else if ( hyperLink.find("horse_") != hyperLink.npos )
		return 21;
	else if ( hyperLink.find("skill_") != hyperLink.npos )
		return 21;
	else if ( hyperLink.find("onfight_") != hyperLink.npos )
		return 3;
	else if ( hyperLink.find("npc_") != hyperLink.npos )
		return 3;
	else if ( hyperLink.find("goto_") != hyperLink.npos )
		return 3;

	return 21;
}

void HyperLinkManager::onHyperLinkLeftActive(HyperLinkEventArgs& e)
{
	fireEvent(EventHyperLinkLeftActive, e, EventNamespace);
}

void HyperLinkManager::onHyperLinkRightActive(HyperLinkEventArgs& e)
{
	fireEvent(EventHyperLinkRightActive, e, EventNamespace);
}

}

