

#include "CEGUIBase.h"
#include "CEGUIString.h"
#include "CEGUIExceptions.h"
#include "CEGUIFactoryModule.h"

#if defined(__WIN32__) || defined(_WIN32)
#	if defined(_MSC_VER)
#		pragma warning(disable : 4552)	
#	endif
#   define WIN32_LEAN_AND_MEAN
#   include <windows.h>
#endif

#if defined(__APPLE_CC__)
#   include "macPlugins.h"
#endif

#if defined(__linux__)
#   include "dlfcn.h"
#endif


namespace CEGUI
{

const char	FactoryModule::RegisterFactoryFunctionName[] = "registerFactory";
const char  FactoryModule::RegisterAllFunctionName[]     = "registerAllFactories";



FactoryModule::FactoryModule(const String& filename) :
	d_moduleName(filename)
{
#if defined(__linux__)
	
	if (d_moduleName.substr(d_moduleName.length() - 3, 3) != (utf8*)".so")
	{
		d_moduleName += (utf8*)".so";
	}

	
	if (d_moduleName.substr(0, 3) != (utf8*)"lib")
	{
		d_moduleName.insert(0, (utf8*)"lib");
	}
#endif

	
#if defined(__WIN32__) || defined(_WIN32)
#	if defined (_DEBUG) && defined (CEGUI_LOAD_MODULE_APPEND_SUFFIX_FOR_DEBUG)
	
	if (d_moduleName.substr(d_moduleName.length() - 4, 4) != (utf8*)".dll")
	{
		d_moduleName += (utf8*)CEGUI_LOAD_MODULE_DEBUG_SUFFIX;
	}
#	endif
#endif
#ifdef CEGUIBASE_LIB
	
	d_regFunc = (FactoryRegisterFunction)DYNLIB_GETSYM(d_handle, RegisterFactoryFunctionName);
	d_regAllFunc = (RegisterAllFunction)DYNLIB_GETSYM(d_handle, RegisterAllFunctionName);
#else

	d_handle = DYNLIB_LOAD(d_moduleName.c_str());

	
	if (d_handle == NULL)
	{
		throw	GenericException((utf8*)"FactoryModule::FactoryModule - Failed to load module '" + d_moduleName + "'.");
	}

    
    d_regFunc = (FactoryRegisterFunction)DYNLIB_GETSYM(d_handle, RegisterFactoryFunctionName);
    d_regAllFunc = (RegisterAllFunction)DYNLIB_GETSYM(d_handle, RegisterAllFunctionName);
#endif
}



FactoryModule::~FactoryModule(void)
{
	DYNLIB_UNLOAD(d_handle);
}



void FactoryModule::registerFactory(const String& type) const
{
    
    if (!d_regFunc)
    {
        throw InvalidRequestException("FactoryModule::registerFactory - Required function export 'void registerFactory(const String& type)' was not found in module '" + d_moduleName + "'.");
    }

	d_regFunc(type);
}

uint FactoryModule::registerAllFactories() const
{
    
    if (!d_regAllFunc)
    {
        throw InvalidRequestException("FactoryModule::registerAllFactories - Required function export 'uint registerAllFactories(void)' was not found in module '" + d_moduleName + "'.");
    }

    return d_regAllFunc();
}

} 
