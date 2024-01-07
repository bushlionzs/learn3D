

#ifndef _CEGUIGlobalEventSet_h_
#define _CEGUIGlobalEventSet_h_

#include "CEGUIEventSet.h"
#include "CEGUISingleton.h"


#if defined(_MSC_VER)
#	pragma warning(push)
#	pragma warning(disable : 4275)
#endif


namespace CEGUI
{

class CEGUIEXPORT GlobalEventSet : public EventSet, public Singleton<GlobalEventSet>
{
public:
	GlobalEventSet();
	~GlobalEventSet();


	
	static	GlobalEventSet&	getSingleton(void);


	
	static	GlobalEventSet*	getSingletonPtr(void);

	
	virtual void	fireEvent(const String& name, EventArgs& args, const String& eventNamespace = "");
};

} 


#if defined(_MSC_VER)
#	pragma warning(pop)
#endif

#endif	
