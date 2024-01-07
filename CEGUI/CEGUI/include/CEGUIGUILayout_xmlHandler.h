

#ifndef _CEGUIGUILayout_xmlHandler_h_
#define _CEGUIGUILayout_xmlHandler_h_

#include "CEGUIWindowManager.h"
#include "CEGUIWindow.h"
#include "CEGUIXMLHandler.h"

#include <vector>


namespace CEGUI
{

class GUILayout_xmlHandler : public XMLHandler
{
	typedef WindowManager::PropertyCallback PropertyCallback;
public:
	
	
	GUILayout_xmlHandler(const String& name_prefix, PropertyCallback* callback = NULL, void* userdata = NULL) : 
	  d_root(NULL),
	  d_namingPrefix(name_prefix),
	  d_propertyCallback(callback),
	  d_userData(userdata)
	  {}

	
	virtual ~GUILayout_xmlHandler(void) {}

	 
	
    virtual void elementStart(const String& element, const XMLAttributes& attributes);
    virtual void elementEnd(const String& element);

	
	
	void	cleanupLoadedWindows(void);


	
	Window*	getLayoutRootWindow(void) const;

private:
	
	static const String GUILayoutElement;				
	static const String WindowElement;				
	static const String PropertyElement;				
	static const String LayoutImportElement;			
	static const String EventElement;					
	static const char	WindowTypeAttribute[];			
	static const char	WindowNameAttribute[];			
	static const char	PropertyNameAttribute[];		
	static const char	PropertyValueAttribute[];		
	static const char	LayoutParentAttribute[];		
	static const char	LayoutImportFilenameAttribute[];
	static const char	LayoutImportPrefixAttribute[];	
    static const char	LayoutImportResourceGroupAttribute[]; 
	static const char	EventNameAttribute[];			
	static const char	EventFunctionAttribute[];		


	
	typedef std::vector<Window*>	WindowStack;	
	Window*	d_root;				
	WindowStack	d_stack;		
	String		d_layoutParent;	
	const String&		d_namingPrefix;	
	PropertyCallback*	d_propertyCallback; 
	void*				d_userData;			
};


} 


#endif	
