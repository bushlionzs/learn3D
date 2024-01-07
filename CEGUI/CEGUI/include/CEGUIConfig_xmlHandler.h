

#ifndef _CEGUIConfig_xmlHandler_h_
#define _CEGUIConfig_xmlHandler_h_

#include "CEGUIBase.h"
#include "CEGUIString.h"
#include "CEGUILogger.h"
#include "CEGUIXMLHandler.h"

#include <vector>


namespace CEGUI
{

class Config_xmlHandler : public XMLHandler
{
public:
	
	
	Config_xmlHandler(void) {}

	
	virtual ~Config_xmlHandler(void) {}

	 
	
    virtual void elementStart(const String& element, const XMLAttributes& attributes);

	
	
	const String&	getLogFilename(void) const				{return d_logFilename;}


	
	const String&	getSchemeFilename(void) const			{return d_schemeFilename;}


	
	const String&	getLayoutFilename(void) const			{return d_layoutFilename;}


	
	const String&	getInitScriptFilename(void) const		{return d_initScriptFilename;}


	
	const String&	getTermScriptFilename(void) const		{return d_termScriptFilename;}


	
	const String&	getDefaultFontName(void) const		{return d_defaultFontName;}


	
	const String&	getDefaultResourceGroup(void) const		{return d_defaultResourceGroup;}

    
    LoggingLevel getLoggingLevel(void) const     {return d_logLevel;}


private:
	
	static const String CEGUIConfigElement;				
	static const char	ConfigLogfileAttribute[];			
	static const char	ConfigSchemeAttribute[];			
	static const char	ConfigLayoutAttribute[];			
	static const char	ConfigDefaultFontAttribute[];		
	static const char	ConfigInitScriptAttribute[];		
	static const char	ConfigTerminateScriptAttribute[];	
    static const char   ConfigDefaultResourceGroupAttribute[]; 
    static const char   ConfigLoggingLevelAttribute[];      

	
	String		d_logFilename;			
	String		d_schemeFilename;		
	String		d_layoutFilename;		
	String		d_initScriptFilename;	
	String		d_termScriptFilename;	
	String		d_defaultFontName;		
    String      d_defaultResourceGroup; 
    LoggingLevel    d_logLevel;         
};


} 

#endif	
