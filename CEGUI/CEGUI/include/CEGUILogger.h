

#ifndef _CEGUILogger_h_
#define _CEGUILogger_h_

#include "CEGUIBase.h"
#include "CEGUIString.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <utility>
#include "CEGUISingleton.h"


#if defined(_MSC_VER)
#	pragma warning(push)
#	pragma warning(disable : 4275)
#	pragma warning(disable : 4251)
#endif



namespace CEGUI
{


enum LoggingLevel
{
	Errors,			
	Standard,		
	Informative,	
	Insane			
};


class CEGUIEXPORT Logger : public Singleton <Logger>
{
public:
	
	Logger(void);

	
	~Logger(void);

	
	
	static Logger&	getSingleton(void);


	
	void	setLoggingLevel(LoggingLevel level)		{d_level = level;}


	
	LoggingLevel	getLoggingLevel(void) const		{return d_level;}


	
	void	logEvent(const String& message, LoggingLevel level = Standard);
	void	logVideoMemoryEvent(const String& message, LoggingLevel level = Standard);

    
    void    setLogFilename(const String& filename, bool append = false);
	void    setVideoMemoryFilename(const String& filename, bool append = false);

	void	setDebugEnvironment(const bool isDebug) {d_debugEnvironment = isDebug;}
	bool	isDebugEnvironment() { return d_debugEnvironment;}

protected:
    
	LoggingLevel	d_level;		
	std::ofstream	d_ostream;		
    std::vector<std::pair<String, LoggingLevel> > d_cache;    
    std::ostringstream d_workstream;
    bool d_caching;                 

	bool d_debugEnvironment;
    
private:
	
	Logger(const Logger& logger) {}
	Logger& operator=(const Logger& logger) {return *this;}

};


#if defined(DEBUG) || defined (_DEBUG)
#	define CEGUI_LOGINSANE( message ) CEGUI::Logger::getSingleton().logEvent((message), CEGUI::Insane);
#else
#	define CEGUI_LOGINSANE( message )
#endif

} 

#if defined(_MSC_VER)
#	pragma warning(pop)
#endif

#endif	
