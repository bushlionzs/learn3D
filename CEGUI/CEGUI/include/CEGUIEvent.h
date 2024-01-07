

#ifndef _CEGUIEvent_h_
#define _CEGUIEvent_h_

#if defined (_MSC_VER)
#	pragma warning(push)
#	pragma warning(disable : 4786)
#	pragma warning(disable : 4251)
#	if !defined (_MSC_EXTENSIONS)
#		pragma warning (disable : 4224)
#	endif
#endif

#include "CEGUIBase.h"
#include "CEGUIString.h"
#include "CEGUIEventArgs.h"
#include "CEGUIRefPtr.h"

#include <map>



namespace CEGUI
{


template <typename Ret, typename Args>
class SubscriberInterface {
public:
  virtual Ret operator()(Args) const = 0;
  virtual ~SubscriberInterface() {}
};



template <typename Ret, typename Args>
class _freeBinder : public SubscriberInterface<Ret,Args>
{
public:
  virtual Ret operator()(Args args) const 
  {
    return d_f(args);
  }
  typedef Ret (*SlotFunction)(Args);
  _freeBinder(SlotFunction f) : d_f(f) {}
protected:
  SlotFunction d_f;
};



template <class Functor, typename Ret, typename Args>
class _functorBinder : public SubscriberInterface<Ret,Args>
{
public:
  virtual Ret operator()(Args args) const 
  {
    return d_f(args);
  }
  _functorBinder(const Functor& f) : d_f(f) {}
protected:
  Functor d_f;
};



template <class T, typename Ret, typename Args>
class _memberBinder : public SubscriberInterface<Ret,Args>
{
  typedef Ret (T::*F)(Args);
public:
  virtual Ret operator()(Args args) const
  {
    return (d_t->*d_f)(args);
  }
  _memberBinder(F f, T* t) : d_f(f), d_t(t) {}
protected:
  F  d_f;
  T* d_t;
};



template <typename Ret, typename Args>
class SubscriberTemplate
{
public:
  Ret operator()(Args args) const
  {
    return (*d_si)(args);  
  }

  typedef Ret (*SlotFunction)(Args);

  
  SubscriberTemplate(SlotFunction f)
  {
    d_si = new _freeBinder<Ret,Args>(f);
  }

  
  template <class T>
  SubscriberTemplate(Ret (T::*f)(Args), T* target)
  {
    d_si = new _memberBinder<T,Ret,Args>(f, target);
  }

  
  template <typename Functor> 
  SubscriberTemplate(const Functor& f)
  {
    d_si = new _functorBinder<Functor,Ret,Args>(f);
  }

  
  SubscriberTemplate(SubscriberInterface<Ret,Args>* si) : d_si(si) {}

  
  SubscriberTemplate(const SubscriberTemplate<Ret,Args>& copy) : d_si(copy.d_si) {}

  
  bool operator<(const SubscriberTemplate<Ret,Args>& rhs) const { return d_si < rhs.d_si; }

  
  void release() const
  {
    delete d_si;
  }

protected:
  SubscriberInterface<Ret,Args>* d_si;
};



template <class Functor, typename Ret, typename Args>
class _refBinder : public SubscriberInterface<Ret,Args>
{
public:
  virtual Ret operator()(Args args) const
  {
    return d_f(args);
  }
  _refBinder(const Functor& f) : d_f(f) {}
protected:
  const Functor& d_f;
};


template <class Functor>
SubscriberInterface<bool, const EventArgs&>*
SubscriberRef(const Functor& f)
{
  return new _refBinder<Functor,bool,const EventArgs&>(f);
}



class CEGUIEXPORT Event
{
public:
    
	class ConnectionInterface : public Referenced {
	public:
		virtual bool connected() { return false; }
		virtual void disconnect() {}
	};
	typedef RefPtr<ConnectionInterface> Connection;

    
	class ScopedConnection {
	public:
		ScopedConnection(Connection conn_) : conn(conn_) {}
		~ScopedConnection() { conn->disconnect(); }
		Connection conn;
	};


	typedef SubscriberTemplate<bool, const EventArgs&> Subscriber;
	typedef int Group;

	
	
	Event(const String& name);

	
	virtual ~Event(void);


	
	const String& getName(void) const	{return d_name;}


	
	Connection subscribe(Subscriber subscriber) { return subscribe(0, subscriber); }


	
	Connection subscribe(Group group, Subscriber subscriber);
  

	
	void	operator()(EventArgs& args);

private:
	
	Event(const Event& evt)	{}
	Event& operator=(const Event& evt)	{return *this;}

	
	bool unsubscribe(Subscriber subscriber, Group group=0);

	class GroupSubscriber {
	public:
		Group group;
		Subscriber subscriber;
		GroupSubscriber(Group group_, Subscriber subscriber_) 
			: group(group_), subscriber(subscriber_) {}
	};

	struct ltGroupSubscriber
	{
		bool operator()(const GroupSubscriber& gs1, const GroupSubscriber& gs2) const
		{
			return gs1.group <  gs2.group ||
				gs1.group == gs2.group && gs1.subscriber < gs2.subscriber;
		}
	};
	typedef std::map<GroupSubscriber, Connection, ltGroupSubscriber> ConnectionOrdering;


	
	const String	d_name;		
	ConnectionOrdering connectionOrdering;
	friend class ConnectionImpl;
};


} 

#if defined(_MSC_VER)
#	pragma warning(pop)
#endif

#endif	
