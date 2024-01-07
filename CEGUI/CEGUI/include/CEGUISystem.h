

#ifndef _CEGUISystem_h_
#define _CEGUISystem_h_

#include "CEGUIBase.h"
#include "CEGUIString.h"
#include "CEGUISingleton.h"
#include "CEGUIRenderer.h"
#include "CEGUIMouseCursor.h"
#include "CEGUIInputEvent.h"
#include "CEGUIResourceProvider.h"

#include <set>


#if defined(_MSC_VER)
#	pragma warning(push)
#	pragma warning(disable : 4275)
#	pragma warning(disable : 4251)
#endif



namespace CEGUI
{

struct MouseClickTrackerImpl;



class CEGUIEXPORT System : public Singleton<System>, public EventSet
{
public:
	static const String EventNamespace;				

	
	static const double		DefaultSingleClickTimeout;		
	static const double		DefaultMultiClickTimeout;		
	static const Size		DefaultMultiClickAreaSize;		

	
	static const String EventGUISheetChanged;				
	static const String EventSingleClickTimeoutChanged;	
	static const String EventMultiClickTimeoutChanged;	
	static const String EventMultiClickAreaSizeChanged;	
	static const String EventDefaultFontChanged;			
	static const String EventDefaultMouseCursorChanged;	
	static const String EventMouseMoveScalingChanged;		


	
	
	
	System(Renderer* renderer, const utf8* logFile = (const utf8*)"Engine.log");

	
    
    System(Renderer* renderer, ResourceProvider* resourceProvider, const utf8* logFile = (const utf8*)"Engine.log");


	
	System(Renderer* renderer, ScriptModule* scriptModule, const utf8* configFile = (const utf8*)"cegui.config");


	
	System(Renderer* renderer, ScriptModule* scriptModule, ResourceProvider* resourceProvider, const utf8* configFile = (const utf8*)"cegui.config");


    
    
    System(Renderer* renderer, XMLParser* xmlParser, const utf8* logFile = (const utf8*)"Engine.log");

    
    
    
    System(Renderer* renderer, ResourceProvider* resourceProvider, XMLParser* xmlParser, const utf8* logFile = (const utf8*)"Engine.log");

    
    
    System(Renderer* renderer, XMLParser* xmlParser, ScriptModule* scriptModule, const utf8* configFile = (const utf8*)"cegui.config");

        
    
    System(Renderer* renderer, ResourceProvider* resourceProvider, XMLParser* xmlParser, ScriptModule* scriptModule, const utf8* configFile = (const utf8*)"cegui.config");


	
	virtual ~System(void);


	
	Renderer*	getRenderer(void) const			{return d_renderer;}


	
	static	System&	getSingleton(void);


	
	static	System*	getSingletonPtr(void);


	
	void	setDefaultFont(const String& name);


	
	void	setDefaultFont(Font* font);


	
	Font*	getDefaultFont(void) const				{return d_defaultFont;}


	
	void	signalRedraw()		{d_gui_redraw = true;}


	
	void addRealTimeUpdateWindow(Window *w) {d_needRealtimeUpdateWindowSet.insert(w);}

	void cancelRealTimeUpdateWindow(Window *w) {d_needRealtimeUpdateWindowSet.erase(w);}
	
	bool	isRedrawRequested() const		{return d_gui_redraw;}


	
	void	renderGUI(void);

	
	virtual void renderActiveSheet();

	
	virtual Window*	getActiveSheetChildAtPosition(const Point& position, int nEventType = 0 ) const;

	
	Window*	setGUISheet(Window* sheet);


	
	Window*	getGUISheet(void) const		{return d_activeSheet;}


	
	double	getSingleClickTimeout(void) const		{return d_click_timeout;}


	
	double	getMultiClickTimeout(void) const		{return d_dblclick_timeout;}


	
	const Size&	getMultiClickToleranceAreaSize(void) const		{return d_dblclick_size;}


	
	void	setSingleClickTimeout(double timeout);


	
	void setMultiClickTimeout(double timeout);


	
	void setMultiClickToleranceAreaSize(const Size&	sz);


	
	const Image*	getDefaultMouseCursor(void) const	{return d_defaultMouseCursor;}


	
	void	setDefaultMouseCursor(const Image* image);


	
	void	setDefaultMouseCursor(MouseCursorImage image)		{setDefaultMouseCursor((const Image*)image);}


	
	void	setDefaultMouseCursor(const String& imageset, const String& image_name);


	
	Window*	getWindowContainingMouse(void) const	{return d_wndWithMouse;}


	
	ScriptModule*	getScriptingModule(void) const;

	
	ResourceProvider* getResourceProvider(void) const;

	
	void	executeScriptFile(const String& filename, const String& resourceGroup = "") const;


	
	int		executeScriptGlobal(const String& function_name) const;


    
    void executeScriptString(const String& str) const;


    
	float	getMouseMoveScaling(void) const;


	
	void	setMouseMoveScaling(float scaling);


	
	void	notifyWindowDestroyed(const Window* window);


    
    uint    getSystemKeys(void) const   { return d_sysKeys; }

    
    XMLParser* getXMLParser(void) const     { return d_xmlParser; }


    
    void setTooltip(Tooltip* tooltip);

    
    void setTooltip(const String& tooltipType);

    
    Tooltip* getDefaultTooltip(void) const  { return d_defaultTooltip; }


	
	void setModalTarget(Window* target)		{d_modalTarget = target;}

	
	Window* getModalTarget(void) const		{return d_modalTarget;}


	
	
	bool	injectMouseMove(float delta_x, float delta_y);


	
	bool	injectMouseLeaves(void);


	
	bool	injectMouseButtonDown(MouseButton button);

	
	bool injectMouseButtonRepeatDown(MouseButton button);
	
	bool	injectMouseButtonUp(MouseButton button);


	
	bool	injectKeyDown(uint key_code);


	
	bool	injectKeyUp(uint key_code);


	
	bool	injectChar(utf32 code_point);


	
	bool	injectMouseWheelChange(float delta);


	
	bool	injectMousePosition(float x_pos, float y_pos);


	
	
	virtual bool	injectTimePulse(float timeElapsed);


private:
    
    System(const System& obj);
    System& operator=(const System& obj);

	
	static const char	CEGUIConfigSchemaName[];			


	
public:
	
	
	virtual Window*	getTargetWindow(const Point& pt, int nEventType = 0 ) const;

	virtual void setTargetWindowValid(bool valid) {}

	
	Window* getKeyboardTargetWindow(void) const;


	
	Window* getNextTargetWindow(Window* w) const;


private:
	
	SystemKey	mouseButtonToSyskey(MouseButton btn) const;


	
	SystemKey	keyCodeToSyskey(Key::Scan key, bool direction);


	
       void	constructor_impl(Renderer* renderer, ResourceProvider* resourceProvider, XMLParser* xmlParser, ScriptModule* scriptModule, const String& configFile, const String& logFile);


	
	bool	handleDisplaySizeChange(const EventArgs& e);


	
	
	void	onGUISheetChanged(WindowEventArgs& e);


	
	void	onSingleClickTimeoutChanged(EventArgs& e);


	
	void	onMultiClickTimeoutChanged(EventArgs& e);


	
	void	onMultiClickAreaSizeChanged(EventArgs& e);


	
	void	onDefaultFontChanged(EventArgs& e);


	
	void	onDefaultMouseCursorChanged(EventArgs& e);


	
	void	onMouseMoveScalingChanged(EventArgs& e);


	
	Renderer*	d_renderer;			
    ResourceProvider* d_resourceProvider;      
	Font*	d_defaultFont;		
	bool		d_gui_redraw;		

	Window*		d_wndWithMouse;		
	Window*		d_activeSheet;		
	Window*		d_modalTarget;		

	String d_strVersion;    

	uint		d_sysKeys;			
	bool		d_lshift;			
	bool		d_rshift;			
	bool		d_lctrl;			
	bool		d_rctrl;			
	bool		d_lalt;				
	bool		d_ralt;				

	double		d_click_timeout;	
	double		d_dblclick_timeout;	
	Size		d_dblclick_size;	

	MouseClickTrackerImpl* const	d_clickTrackerPimpl;		

	
	const Image*	d_defaultMouseCursor;

	
	ScriptModule*	d_scriptModule;		
	String			d_termScriptName;	

	float			d_mouseScalingFactor;

    XMLParser*		d_xmlParser;        
    bool			d_ourXmlParser;     

    Tooltip*		d_defaultTooltip;   
    bool			d_weOwnTooltip;     

	typedef std::set<Window *> RealTimeWindowSet;
	RealTimeWindowSet d_needRealtimeUpdateWindowSet;

protected:
	float			d_timeElapsed;		

public:
	float	getCurTimeElapsed();
};

} 


#if defined(_MSC_VER)
#	pragma warning(pop)
#endif

#endif	
