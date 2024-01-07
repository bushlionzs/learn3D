
#ifndef _CEGUIHyperLinkManager_h_
#define _CEGUIHyperLinkManager_h_

#include "CEGUIBase.h"
#include "CEGUISingleton.h"
#include "CEGUIHyperLink.h"
#include "CEGUIEventSet.h"
#include "CEGUIInputEvent.h"

#include <map>


namespace CEGUI
{
class CEGUIEXPORT HyperLinkManager : public Singleton<HyperLinkManager>, public EventSet
{
public:
	
	HyperLinkManager(void);


	
	~HyperLinkManager(void);

	
	static	HyperLinkManager&	getSingleton(void);


	
	static	HyperLinkManager*	getSingletonPtr(void);

public:
		
		static const String EventNamespace;						

		static const String EventHyperLinkActive;             
		static const String EventHyperLinkLeftActive;			
		static const String EventHyperLinkRightActive;			
        static const String EventHyperLinkInactive;           
		

		void destroyAllHyperLink(void);
		void destroyHyperLink(const String name);

		bool addHyperLink(const Window* OwnerWindow, const String name, const Rect hyper_rect, unsigned long guid = 0);
		bool isHyperLinkRange(const Window* pOwnerWindow,const Point& position, int &gamecursor);

		int getHyperLinkCursor( const String& hyperLink );
		bool doHyperLink(const Window* pOwnerWindow,const Point& position);

		
		bool doHyperLinkByMouseLeft(const Window* pOwnerWindow,const Point& position);
		bool doHyperLinkByMouseRight(const Window* pOwnerWindow,const Point& position);

		
		String getHyperLinkContex(const Window* pOwnerWindow, const Point& position);

		void onHyperLinkLeftActive(HyperLinkEventArgs& e);
		void onHyperLinkRightActive(HyperLinkEventArgs& e);

private:

	typedef std::map< String, HyperLink > HyperLinkNameRegistry;
	
	HyperLinkNameRegistry	d_HyperLinkNameMap;

	String					d_curKeyHyperLink;
};

}

#endif	