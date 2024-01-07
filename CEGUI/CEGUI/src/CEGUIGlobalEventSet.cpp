

#include "CEGUIGlobalEventSet.h"
#include "CEGUILogger.h"



namespace CEGUI
{
	
	
	template<> GlobalEventSet* Singleton<GlobalEventSet>::ms_Singleton	= NULL;

	
	GlobalEventSet::GlobalEventSet()
	{
		
	}

	
	GlobalEventSet::~GlobalEventSet()
	{
		
	}

	
	GlobalEventSet&	GlobalEventSet::getSingleton(void)
	{
		return Singleton<GlobalEventSet>::getSingleton();
	}

	
	GlobalEventSet*	GlobalEventSet::getSingletonPtr(void)
	{
		return Singleton<GlobalEventSet>::getSingletonPtr();
	}

	
	void GlobalEventSet::fireEvent(const String& name, EventArgs& args, const String& eventNamespace)
	{
        fireEvent_impl(eventNamespace + "/" + name, args);
	}

} 
