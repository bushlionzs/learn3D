

#ifndef _CEGUIWindowManager_h_
#define _CEGUIWindowManager_h_

#include "CEGUIBase.h"
#include "CEGUIString.h"
#include "CEGUISingleton.h"
#include "CEGUILogger.h"
#include "CEGUIIteratorBase.h"
#include <map>
#include <vector>

#if defined(_MSC_VER)
#	pragma warning(push)
#	pragma warning(disable : 4275)
#	pragma warning(disable : 4251)
#endif



namespace CEGUI
{

class CEGUIEXPORT WindowManager : public Singleton <WindowManager>
{
public:
    
    static const String GeneratedWindowNameBase;      

	
	typedef bool PropertyCallback(Window* window, String& propname, String& propvalue, void* userdata);
	
	
	
	WindowManager(void);


	
	~WindowManager(void);


	
	static	WindowManager&	getSingleton(void);


	
	static	WindowManager*	getSingletonPtr(void);


	
	
	Window*	createWindow(const String& type, const String& name = "");


	
	void	destroyWindow(Window* window);


	
	void	destroyWindow(const String& window);


	
	Window*	getWindow(const String& name) const;


	
	bool	isWindowPresent(const String& name) const;


	
	void	destroyAllWindows(void);


	
	Window*	loadWindowLayout(const String& filename, const String& name_prefix = "", const String& resourceGroup = "", PropertyCallback* callback = NULL, void* userdata = NULL);

    
    bool isDeadPoolEmpty(void) const;

    
    void cleanDeadPool(void);

    
    void writeWindowLayoutToStream(const Window& window, OutStream& out_stream, bool writeParent = false) const;

    
    void writeWindowLayoutToStream(const String& window, OutStream& out_stream, bool writeParent = false) const;

    
    void renameWindow(const String& window, const String& new_name);

    
    void renameWindow(Window* window, const String& new_name);

	PropertyCallback*	getPropertyCallback() {return d_propertyCallback;}

private:
    
    
    String generateUniqueWindowName();

	
	static const char	GUILayoutSchemaName[];			


	
	typedef std::map<String, Window*>			WindowRegistry;				
    typedef std::vector<Window*>    WindowVector;   

	WindowRegistry			d_windowRegistry;			
    WindowVector			d_deathrow;     

	PropertyCallback*		d_propertyCallback; 

    unsigned long			d_uid_counter;  

public:
	
	typedef	ConstBaseIterator<WindowRegistry>	WindowIterator;

	
	WindowIterator	getIterator(void) const;
};

} 

#if defined(_MSC_VER)
#	pragma warning(pop)
#endif

#endif	
