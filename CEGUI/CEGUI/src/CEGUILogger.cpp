

#include "CEGUILogger.h"
#include <ctime>
#include <iomanip>




namespace CEGUI
{
    
    
    template<> Logger* Singleton<Logger>::ms_Singleton  = NULL;


    
    Logger::Logger(void) :
            d_level(Standard),
            d_caching(true),
			d_debugEnvironment(true)
    {
		
    }

    
    Logger::~Logger(void)
    {
        if (d_ostream.is_open())
        {
            logEvent((utf8*)"CEGUI::Logger singleton destroyed.");
            d_ostream.close();
        }
    }

    
    void Logger::logEvent(const String& message, LoggingLevel level )
    {
		
		
		
    }


    void Logger::setLogFilename(const String& filename, bool append)
    {
		
    }

	void Logger::setVideoMemoryFilename(const String& filename, bool append)
	{
		if( !d_debugEnvironment )
			return;

		
		if (d_ostream.is_open())
		{
			d_ostream.close();
		}

		d_ostream.open(filename.c_str(), std::ios_base::out | (append ? std::ios_base::app : std::ios_base::trunc));

		if (!d_ostream)
		{
			throw "Logger::setUIVideoMemoryLogFilename - Failed to open file.";
		}

		
		d_ostream.width(2);

		
		if (d_caching)
		{
			d_caching = false;

			std::vector<std::pair<String, LoggingLevel> >::iterator iter = d_cache.begin();

			while (iter != d_cache.end())
			{
				if (d_level >= (*iter).second)
				{
					
					d_ostream << (*iter).first;
					
					d_ostream.flush();
				}

				++iter;
			}

			d_cache.clear();
		}
	}

	void Logger::logVideoMemoryEvent(const String& message, LoggingLevel level )
	{
		if( !d_debugEnvironment )
			return;

		using namespace std;

		time_t  et;
		time(&et);
		tm* etm = localtime(&et);

		if (etm != NULL)
		{
			
			d_workstream.str("");

			
			d_workstream << setfill('0') << setw(2) << etm->tm_mday << '/' <<
			setfill('0') << setw(2) << 1 + etm->tm_mon << '/' <<
			setw(4) << (1900 + etm->tm_year) << ' ';

			
			d_workstream << setfill('0') << setw(2) << etm->tm_hour << ':' <<
			setfill('0') << setw(2) << etm->tm_min << ':' <<
			setfill('0') << setw(2) << etm->tm_sec << ' ';

			
			switch(level)
			{
			case Errors:
				d_workstream << "(Error)\t";
				break;

			case Standard:
				d_workstream << "(InfL1)\t";
				break;

			case Informative:
				d_workstream << "(InfL2)\t";
				break;

			case Insane:
				d_workstream << "(InfL3)\t";
				break;

			default:
				d_workstream << "(Unkwn)\t";
				break;
			}

			d_workstream << message << endl;

			if (d_caching)
			{
				d_cache.push_back(std::make_pair(d_workstream.str(), level));
			}
			else if (d_level >= level)
			{
				
				d_ostream << d_workstream.str();
				
				d_ostream.flush();
			}
		}
	}

    Logger& Logger::getSingleton(void)
    {
        return Singleton<Logger>::getSingleton();
    }

} 
