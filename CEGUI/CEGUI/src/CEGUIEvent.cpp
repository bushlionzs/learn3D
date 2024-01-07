

#include "CEGUIEvent.h"

#if defined (_MSC_VER)
#	pragma warning(disable : 4251)
#	pragma warning(disable : 4786)
#	if !defined (_MSC_EXTENSIONS)
#		pragma warning (disable : 4224)
#	endif
#endif



namespace CEGUI {

class ConnectionImpl : public Event::ConnectionInterface {
public:
	ConnectionImpl(Event* event_, Event::Group group_, Event::Subscriber subscriber_) : 
		event(event_), group(group_), subscriber(subscriber_)
		{
		}

		virtual bool connected()
		{
			return event != 0;
		}

		virtual void disconnect()
		{
			if (event)
			{
				event->unsubscribe(subscriber, group);
			}

		}

protected:
	Event* event;
	Event::Group group;
	Event::Subscriber subscriber;

	friend class Event;
};


Event::Event(const String& name) : d_name(name)
{
}


Event::~Event()
{
	ConnectionOrdering::iterator i = connectionOrdering.begin();
	for (;i != connectionOrdering.end(); i++)
	{
		if (((ConnectionImpl*)i->second.get())->event)
		{
			i->first.subscriber.release();
		}

	}
}


Event::Connection Event::subscribe(Group group, Subscriber subscriber)
{
	ConnectionImpl* conn = new ConnectionImpl(this, group, subscriber);
	connectionOrdering[GroupSubscriber(group, subscriber)] = conn;
	return conn;
}


void Event::operator()(EventArgs& args)
{
	ConnectionOrdering::iterator i = connectionOrdering.begin();

	for (;i != connectionOrdering.end(); ++i)
	{
		if (((ConnectionImpl*)i->second.get())->event)
		{
			args.handled |= i->first.subscriber(args);
		}

	}

}


bool Event::unsubscribe(Subscriber subscriber, Group group)
{
	ConnectionOrdering::iterator j = connectionOrdering.find(GroupSubscriber(group, subscriber));

	if (j == connectionOrdering.end())
	{
		return false;
	}

	ConnectionImpl* c = (ConnectionImpl*)j->second.get();
	c->event = 0;
	c->subscriber.release();
	connectionOrdering.erase(j);
	return true;
}

} 

