

#ifndef _CEGUIEventSet_h_
#define _CEGUIEventSet_h_

#include "CEGUIBase.h"
#include "CEGUIString.h"
#include "CEGUIEvent.h"
#include "CEGUIIteratorBase.h"
#include <map>

#if defined (_MSC_VER)
#	pragma warning(push)
#	pragma warning(disable : 4251)
#endif



namespace CEGUI
{

class CEGUIEXPORT EventSet
{
public:
	
	EventSet();


	
	virtual ~EventSet(void);


	
	void	addEvent(const String& name);


	
	void	removeEvent(const String& name);


	
	void	removeAllEvents(void);


	
	bool	isEventPresent(const String& name);


    
    virtual Event::Connection subscribeEvent(const String& name, Event::Subscriber subscriber);


    
    virtual Event::Connection subscribeEvent(const String& name, Event::Group group, Event::Subscriber subscriber);

#if 0 

    
    virtual Event::Connection subscribeScriptedEvent(const String& name, const String& subscriber_name);


    
    virtual Event::Connection subscribeScriptedEvent(const String& name, Event::Group group, const String& subscriber_name);

#endif

    
    virtual void fireEvent(const String& name, EventArgs& args, const String& eventNamespace = "");


	
	bool	isMuted(void) const;


	
	void	setMutedState(bool setting);


protected:
    
    Event* getEventObject(const String& name, bool autoAdd = false);

    
    void fireEvent_impl(const String& name, EventArgs& args);


	
	EventSet(EventSet& e) {}
	EventSet& operator=(EventSet& e) {return *this;}

	typedef std::map<String, Event*>	EventMap;
	EventMap	d_events;

	bool	d_muted;	

public:
	
	typedef	ConstBaseIterator<EventMap>	EventIterator;

	
	EventIterator	getIterator(void) const;
};

} 


#if defined(_MSC_VER)
#	pragma warning(pop)
#endif

#endif	
