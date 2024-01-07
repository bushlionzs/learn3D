

#ifndef _CEGUIScriptModule_h_
#define _CEGUIScriptModule_h_

#include "CEGUIBase.h"
#include "CEGUIString.h"
#include "CEGUIEvent.h"



namespace CEGUI
{

class CEGUIEXPORT ScriptModule
{
public:
	
	
	ScriptModule(void);


	
	virtual ~ScriptModule(void) {}


	
	
	virtual	void	executeScriptFile(const String& filename, const String& resourceGroup = "")	= 0;


	
	virtual int	executeScriptGlobal(const String& function_name)	= 0;


	
	virtual	bool	executeScriptedEventHandler(const String& handler_name, const EventArgs& e)		= 0;


    
    virtual void executeString(const String& str) = 0;


    
    virtual void createBindings(void) {}


    
    virtual void destroyBindings(void) {}

    
    const String& getIdentifierString() const;

#if 0	
    
    virtual Event::Connection	subscribeEvent(EventSet* target, const String& name, const String& subscriber_name) = 0;

    
    virtual Event::Connection	subscribeEvent(EventSet* target, const String& name, Event::Group group, const String& subscriber_name) = 0;
#endif

protected:
    String d_identifierString;                 
};



class CEGUIEXPORT ScriptFunctor
{
public:
	ScriptFunctor(const String& functionName) : scriptFunctionName(functionName) {}
    ScriptFunctor(const ScriptFunctor& obj) : scriptFunctionName(obj.scriptFunctionName) {}
	bool	operator()(const EventArgs& e) const;

private:
    
    ScriptFunctor& operator=(const ScriptFunctor& rhs);

	const String	scriptFunctionName;
};

} 


#endif	
