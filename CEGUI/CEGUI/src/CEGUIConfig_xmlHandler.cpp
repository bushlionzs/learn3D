

#include "CEGUIConfig_xmlHandler.h"
#include "CEGUIExceptions.h"
#include "CEGUISystem.h"
#include "CEGUIXMLAttributes.h"



namespace CEGUI
{
    
    const String Config_xmlHandler::CEGUIConfigElement( (utf8*)"CEGUIConfig" );
    const char  Config_xmlHandler::ConfigLogfileAttribute[]         = "Logfile";
    const char  Config_xmlHandler::ConfigSchemeAttribute[]          = "Scheme";
    const char  Config_xmlHandler::ConfigLayoutAttribute[]          = "Layout";
    const char  Config_xmlHandler::ConfigDefaultFontAttribute[]     = "DefaultFont";
    const char  Config_xmlHandler::ConfigInitScriptAttribute[]      = "InitScript";
    const char  Config_xmlHandler::ConfigTerminateScriptAttribute[] = "TerminateScript";
    const char  Config_xmlHandler::ConfigDefaultResourceGroupAttribute[] = "DefaultResourceGroup";
    const char  Config_xmlHandler::ConfigLoggingLevelAttribute[]    = "LoggingLevel";

    void Config_xmlHandler::elementStart(const String& element, const XMLAttributes& attributes)
    {
        
        if (element == CEGUIConfigElement)
        {
            d_logFilename           = attributes.getValueAsString(ConfigLogfileAttribute);
            d_schemeFilename        = attributes.getValueAsString(ConfigSchemeAttribute);
            d_layoutFilename        = attributes.getValueAsString(ConfigLayoutAttribute);
            d_initScriptFilename    = attributes.getValueAsString(ConfigInitScriptAttribute);
            d_termScriptFilename    = attributes.getValueAsString(ConfigTerminateScriptAttribute);
            d_defaultFontName       = attributes.getValueAsString(ConfigDefaultFontAttribute);
            d_defaultResourceGroup  = attributes.getValueAsString(ConfigDefaultResourceGroupAttribute);

            
            String logLevelStr = attributes.getValueAsString(ConfigLoggingLevelAttribute, "Standard");

            if (logLevelStr == "Errors")
            {
                d_logLevel = Errors;
            }
            else if (logLevelStr == "Informative")
            {
                d_logLevel = Informative;
            }
            else if (logLevelStr == "Insane")
            {
                d_logLevel = Insane;
            }
            else
            {
                d_logLevel = Standard;
            }
        }
        
        else
        {
            String message("Config_xmlHandler::startElement - Unexpected data was found while parsing the configuration file: '" + element + "' is unknown.");

            
            throw message.c_str();
        }

    }

} 
