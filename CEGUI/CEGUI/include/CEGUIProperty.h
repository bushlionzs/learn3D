

#ifndef _CEGUIProperty_h_
#define _CEGUIProperty_h_

#include "CEGUIBase.h"
#include "CEGUIString.h"



namespace CEGUI
{


class CEGUIEXPORT PropertyReceiver
{
public:
	PropertyReceiver() {}
	virtual ~PropertyReceiver() {}
};



class CEGUIEXPORT Property
{
public:
	
	Property(const String& name, const String& help, const String& defaultValue = "", bool writesXML = true) :
	  d_name(name),
	  d_help(help),
	  d_default(defaultValue),
	  d_writeXML(writesXML)
	{
	}


	
	virtual ~Property(void) {}


	
	const String& getHelp(void) const		{return d_help;}


	
	const String& getName(void) const		{return d_name;}


	
	virtual String	get(const PropertyReceiver* receiver) const = 0;


	
	virtual void	set(PropertyReceiver* receiver, const String& value) = 0;


	
	virtual bool	isDefault(const PropertyReceiver* receiver) const;


	
	virtual String	getDefault(const PropertyReceiver* receiver) const;


    
    void writeXMLToStream(const PropertyReceiver* receiver, OutStream& out_stream) const;

protected:
	String	d_name;		
	String	d_help;		
	String	d_default;	
	bool    d_writeXML; 
};

} 

#endif	
