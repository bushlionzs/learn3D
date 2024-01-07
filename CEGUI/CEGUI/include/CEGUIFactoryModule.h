

#ifndef _CEGUIFactoryModule_h_
#define _CEGUIFactoryModule_h_


#if defined(__WIN32__) || defined(_WIN32)
#    define DYNLIB_HANDLE hInstance
#    define DYNLIB_LOAD( a ) LoadLibrary( a )
#    define DYNLIB_GETSYM( a, b ) GetProcAddress( a, b )
#    define DYNLIB_UNLOAD( a ) !FreeLibrary( a )
#    define DYNLIB_ERROR( )  "Unknown Error"

	struct HINSTANCE__;
	typedef struct HINSTANCE__* hInstance;

#elif defined(__linux__)
#    define DYNLIB_HANDLE void*
#    define DYNLIB_LOAD( a ) dlopen( a, RTLD_LAZY )
#    define DYNLIB_GETSYM( a, b ) dlsym( a, b )
#    define DYNLIB_UNLOAD( a ) dlclose( a )
#    define DYNLIB_ERROR( ) dlerror( )

#elif defined(__APPLE_CC__)
#    define DYNLIB_HANDLE CFBundleRef
#    define DYNLIB_LOAD( a ) mac_loadExeBundle( a )
#    define DYNLIB_GETSYM( a, b ) mac_getBundleSym( a, b )
#    define DYNLIB_UNLOAD( a ) mac_unloadExeBundle( a )
#    define DYNLIB_ERROR( ) mac_errorBundle()
#endif



namespace CEGUI
{


class FactoryModule
{
public:
	
	FactoryModule(const String& filename);


	
	virtual ~FactoryModule(void);


	
	void	registerFactory(const String& type) const;


    
    uint registerAllFactories() const;

private:
	
	static const char	RegisterFactoryFunctionName[];
    static const char   RegisterAllFunctionName[];

	typedef void (*FactoryRegisterFunction)(const String&); 
    typedef uint (*RegisterAllFunction)(void);

	FactoryRegisterFunction	d_regFunc;	
    RegisterAllFunction d_regAllFunc;   
	String			d_moduleName;		
	DYNLIB_HANDLE	d_handle;			
};

} 


#endif	
