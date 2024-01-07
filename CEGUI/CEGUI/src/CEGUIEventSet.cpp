

#include "CEGUIEventSet.h"
#include "CEGUIExceptions.h"
#include "CEGUIGlobalEventSet.h"
#include "CEGUIScriptModule.h"
#include "CEGUISystem.h"


namespace CEGUI
{

EventSet::EventSet() :
	d_muted(false)
{
}



EventSet::~EventSet(void)
{
	removeAllEvents();
}



void EventSet::addEvent(const String& name)
{
	if (isEventPresent(name))
	{
		throw AlreadyExistsException("An event named '" + name + "' already exists in the EventSet.");
	}

	d_events[name] = new Event(name);
}



void EventSet::removeEvent(const String& name)
{
	EventMap::iterator pos = d_events.find(name);

	if (pos != d_events.end())
	{
		delete pos->second;
		d_events.erase(pos);
	}

}



void EventSet::removeAllEvents(void)
{
	EventMap::iterator pos = d_events.begin();
	EventMap::iterator end = d_events.end()	;

	for (; pos != end; ++pos)
	{
		delete pos->second;
	}

	d_events.clear();
}



bool EventSet::isEventPresent(const String& name)
{
	return (d_events.find(name) != d_events.end());
}

#if 0 


Event::Connection EventSet::subscribeScriptedEvent(const String& name, const String& subscriber_name)
{
	
	ScriptModule* sm = System::getSingletonPtr()->getScriptingModule();
	if (!sm)
	{
	   throw InvalidRequestException("[EventSet::subscribeScriptedEvent] No scripting module is available");
	}
	return sm->subscribeEvent(this, name, subscriber_name);
}


Event::Connection EventSet::subscribeScriptedEvent(const String& name, Event::Group group, const String& subscriber_name)
{
        
        ScriptModule* sm = System::getSingletonPtr()->getScriptingModule();
	if (!sm)
	{
	   throw InvalidRequestException("[EventSet::subscribeScriptedEvent] No scripting module is available");
	}
	return sm->subscribeEvent(this, name, group, subscriber_name);
}

#endif


Event::Connection EventSet::subscribeEvent(const String& name, Event::Subscriber subscriber)
{
    
    return getEventObject(name, true)->subscribe(subscriber);
}



Event::Connection EventSet::subscribeEvent(const String& name, Event::Group group, Event::Subscriber subscriber)
{
    
    return getEventObject(name, true)->subscribe(group, subscriber);
}


void EventSet::fireEvent(const String& name, EventArgs& args, const String& eventNamespace)
{
    
    GlobalEventSet::getSingleton().fireEvent(name, args, eventNamespace);
    
    fireEvent_impl(name, args);
}



bool EventSet::isMuted(void) const
{
	return d_muted;
}



void EventSet::setMutedState(bool setting)
{
	d_muted = setting;
}



Event* EventSet::getEventObject(const String& name, bool autoAdd)
{
    EventMap::iterator pos = d_events.find(name);

    
    if (pos == d_events.end())
    {
        if (autoAdd)
        {
            addEvent(name);
            return d_events.find(name)->second;
        }
        else
        {
            return 0;
        }
    }

    return pos->second;
}



void EventSet::fireEvent_impl(const String& name, EventArgs& args)
{
    
    Event* ev = getEventObject(name);

    
    if ((ev != 0) && !d_muted)
        (*ev)(args);
}



EventSet::EventIterator EventSet::getIterator(void) const
{
	return EventIterator(d_events.begin(), d_events.end());
}


} 
