

#ifdef HAVE_CONFIG_H
#   include "config.h"
#endif

#include "CEGUISystem.h"
#include "CEGUILogger.h"
#include "CEGUIImagesetManager.h"
#include "CEGUIFontManager.h"
#include "CEGUIWindowFactoryManager.h"
#include "CEGUIWindowManager.h"
#include "CEGUISchemeManager.h"
#include "CEGUIMouseCursor.h"
#include "CEGUIWindow.h"
#include "CEGUIImageset.h"
#include "CEGUIExceptions.h"
#include "elements/CEGUIGUISheet.h"
#include "elements/CEGUIDragContainer.h"
#include "elements/CEGUIScrolledContainer.h"
#include "elements/CEGUITooltip.h"
#include "CEGUIScriptModule.h"
#include "CEGUIConfig_xmlHandler.h"
#include "CEGUIDataContainer.h"
#include "CEGUIResourceProvider.h"
#include "CEGUIGlobalEventSet.h"
#include "falagard/CEGUIFalWidgetLookManager.h"
#include "CEGUIPropertyHelper.h"
#include "CEGUIKeyImageAnimationManager.h"
#include "CEGUIInputMethodEditor.h"
#include "CEGUIHyperLinkManager.h"
#include <time.h>











#include "CEGUIExpatParser.h"
#define CEGUI_DEFAULT_XMLPARSER ExpatParser


namespace CEGUI
{
const String System::EventNamespace("System");


class SimpleTimer
{
	clock_t d_baseTime;

public:
	SimpleTimer() : d_baseTime(clock()) {}

	void	restart()	{ d_baseTime = clock(); }
	double	elapsed()	{ return static_cast<double>(clock() - d_baseTime) / CLOCKS_PER_SEC; }
};


struct MouseClickTracker
{
	MouseClickTracker(void) : d_click_count(0), d_click_area(0, 0, 0, 0) {}

	SimpleTimer		d_timer;			
	int				d_click_count;		
	Rect			d_click_area;		
    Window*         d_target_window;    
};


struct MouseClickTrackerImpl
{
	MouseClickTracker	click_trackers[MouseButtonCount];
};



const char	System::CEGUIConfigSchemaName[]		= "CEGUIConfig.xsd";




template<> System* Singleton<System>::ms_Singleton	= NULL;


const double	System::DefaultSingleClickTimeout	= 0.2;
const double	System::DefaultMultiClickTimeout	= 0.33;
const Size		System::DefaultMultiClickAreaSize(12,12);


const String System::EventGUISheetChanged( (utf8*)"GUISheetChanged" );
const String System::EventSingleClickTimeoutChanged( (utf8*)"SingleClickTimeoutChanged" );
const String System::EventMultiClickTimeoutChanged( (utf8*)"MultiClickTimeoutChanged" );
const String System::EventMultiClickAreaSizeChanged( (utf8*)"MultiClickAreaSizeChanged" );
const String System::EventDefaultFontChanged( (utf8*)"DefaultFontChanged" );
const String System::EventDefaultMouseCursorChanged( (utf8*)"DefaultMouseCursorChanged" );
const String System::EventMouseMoveScalingChanged( (utf8*)"MouseMoveScalingChanged" );



System::System(Renderer* renderer, const utf8* logFile) :
	d_clickTrackerPimpl(new MouseClickTrackerImpl)
{
	constructor_impl(renderer, NULL, NULL, NULL, (const utf8*)"", logFile);
}

System::System(Renderer* renderer, ResourceProvider* resourceProvider,const utf8* logFile) :
	d_clickTrackerPimpl(new MouseClickTrackerImpl)
{
    constructor_impl(renderer, resourceProvider, NULL, NULL, (const utf8*)"", logFile);
}


System::System(Renderer* renderer, ScriptModule* scriptModule, const utf8* configFile) :
	d_clickTrackerPimpl(new MouseClickTrackerImpl)
{

    constructor_impl(renderer, NULL, NULL, scriptModule, configFile, (const utf8*)"Engine.log");
}



System::System(Renderer* renderer, ScriptModule* scriptModule, ResourceProvider* resourceProvider, const utf8* configFile) :
	d_clickTrackerPimpl(new MouseClickTrackerImpl)
{
 
    constructor_impl(renderer, resourceProvider, NULL, scriptModule, configFile, (const utf8*)"Engine.log");
}


System::System(Renderer* renderer, XMLParser* xmlParser, const utf8* logFile) :
        d_clickTrackerPimpl(new MouseClickTrackerImpl)
{
    constructor_impl(renderer, NULL, xmlParser, NULL, (const utf8*)"", logFile);
}


System::System(Renderer* renderer, ResourceProvider* resourceProvider, XMLParser* xmlParser, const utf8* logFile) :
        d_clickTrackerPimpl(new MouseClickTrackerImpl)
{
    constructor_impl(renderer, resourceProvider, xmlParser, NULL, (const utf8*)"", logFile);
}


System::System(Renderer* renderer, XMLParser* xmlParser, ScriptModule* scriptModule, const utf8* configFile) :
        d_clickTrackerPimpl(new MouseClickTrackerImpl)
{
    
    constructor_impl(renderer, NULL, xmlParser, scriptModule, configFile, (const utf8*)"Engine.log");
}


System::System(Renderer* renderer, ResourceProvider* resourceProvider, XMLParser* xmlParser, ScriptModule* scriptModule, const utf8* configFile) :
        d_clickTrackerPimpl(new MouseClickTrackerImpl)
{
 
    constructor_impl(renderer, resourceProvider, xmlParser, scriptModule, configFile, (const utf8*)"Engine.log");
}


void System::constructor_impl(Renderer* renderer, ResourceProvider* resourceProvider,  XMLParser* xmlParser, ScriptModule* scriptModule, const String& configFile, const String& logFile)
{
    
    new Logger();

    
    d_strVersion = PropertyHelper::uintToString(CEGUI_VERSION_MAJOR) + "." +
       PropertyHelper::uintToString(CEGUI_VERSION_MINOR) + "." +
       PropertyHelper::uintToString(CEGUI_VERSION_PATCH);

	d_renderer		= renderer;
	d_gui_redraw	= false;
	d_defaultFont	= NULL;
	d_wndWithMouse	= NULL;
	d_activeSheet	= NULL;
	d_modalTarget	= NULL;
	d_sysKeys		= 0;

	d_lshift	= false;
	d_rshift	= false;
	d_lctrl		= false;
	d_rctrl		= false;
    d_ralt      = false;
    d_lalt      = false;

	d_timeElapsed = 0;

	d_click_timeout		= DefaultSingleClickTimeout;
	d_dblclick_timeout	= DefaultMultiClickTimeout;
	d_dblclick_size		= DefaultMultiClickAreaSize;

	d_defaultMouseCursor = NULL;
	d_scriptModule		 = scriptModule;

	d_mouseScalingFactor = 1.0f;

    
    d_defaultTooltip = 0;
    d_weOwnTooltip = false;

    
    d_resourceProvider = resourceProvider ? resourceProvider : renderer->createResourceProvider();

    
    if (xmlParser)
    {
        d_xmlParser = xmlParser;
        d_ourXmlParser = false;
    }
    else
    {
        d_xmlParser = new CEGUI_DEFAULT_XMLPARSER;
        d_ourXmlParser = true;
    }

    
    d_xmlParser->initialise();

	
	String configLogname, configSchemeName, configLayoutName, configInitScript, defaultFontName;

	
	if (!configFile.empty())
	{
        
        Config_xmlHandler handler;

		
		try
		{
            d_xmlParser->parseXMLFile(handler, configFile, CEGUIConfigSchemaName, "");
		}
		catch(...)
		{
			Logger::getSingleton().logEvent("System::constructor_impl parseXMLFile failed.", Errors);

			
            d_xmlParser->cleanup();
            delete d_xmlParser;
			Logger::getSingleton().logEvent("System::constructor_impl - parseXMLFile '" + configFile +"' failed.", Errors);
            throw;
		}

        
        Logger::getSingleton().setLoggingLevel(handler.getLoggingLevel());

        
        configLogname		= handler.getLogFilename();
        configSchemeName	= handler.getSchemeFilename();
        configLayoutName	= handler.getLayoutFilename();
        defaultFontName		= handler.getDefaultFontName();
        configInitScript	= handler.getInitScriptFilename();
        d_termScriptName	= handler.getTermScriptFilename();

        
        if (!handler.getDefaultResourceGroup().empty())
        {
            d_resourceProvider->setDefaultResourceGroup(handler.getDefaultResourceGroup());
        }
	}

	
	
	if (!configLogname.empty())
	{
        Logger::getSingleton().setLogFilename(configLogname, false);
	}
	
	else
	{
        Logger::getSingleton().setLogFilename(logFile, false);
	}

	
	

	
	new ImagesetManager();
	new FontManager();
	new WindowFactoryManager();
	new WindowManager();
	new SchemeManager();
	new MouseCursor();
	new GlobalEventSet();
    new WidgetLookManager();
	new HyperLinkManager();

    
    
    WindowFactoryManager::getSingleton().addFactory(new GUISheetFactory);
    WindowFactoryManager::getSingleton().addFactory(new DragContainerFactory);
    WindowFactoryManager::getSingleton().addFactory(new ScrolledContainerFactory);

	
	WindowFactoryManager::getSingleton().addWindowTypeAlias((utf8*)"DefaultGUISheet", GUISheet::WidgetTypeName);

	
	
	
    
    
    
    Logger::getSingleton().logEvent(d_scriptModule ? "---- Scripting module is: " + d_scriptModule->getIdentifierString() + " ----" : "---- Scripting module is: None ----");
	
	d_renderer->subscribeEvent(Renderer::EventDisplaySizeChanged, Event::Subscriber(&CEGUI::System::handleDisplaySizeChange, this));

	
	if (!configSchemeName.empty())
	{
		try
		{
			SchemeManager::getSingleton().loadScheme(configSchemeName, d_resourceProvider->getDefaultResourceGroup());

			
			if (!defaultFontName.empty())
			{
				setDefaultFont(defaultFontName);
			}

		}
		catch (CEGUI::Exception exc) 
		{
			Logger::getSingleton().logEvent("System::constructor_impl loadScheme failed.", Errors);
		}  

	}

	
	if (!configLayoutName.empty())
	{
		try
		{
			setGUISheet(WindowManager::getSingleton().loadWindowLayout(configLayoutName));
		}
		catch (CEGUI::Exception exc) 
		{
			Logger::getSingleton().logEvent("System::constructor_impl loadWindowLayout failed.", Errors);

		}  

	}

    
    if (d_scriptModule)
    {
        d_scriptModule->createBindings();
    }

	
	if (!configInitScript.empty())
	{
		try
		{
			executeScriptFile(configInitScript);
		}
		catch (...) 
		{
			Logger::getSingleton().logEvent("System::constructor_impl executeScriptFile failed.", Errors);

		}  

	}
}



System::~System(void)
{
	Logger::getSingleton().logEvent((utf8*)"---- Begining CEGUI System destruction ----");

	
	if (!d_termScriptName.empty())
	{
		try
		{
			executeScriptFile(d_termScriptName);
		}
		catch (...) 
		{
			Logger::getSingleton().logEvent("System::~System executeScriptFile failed.", Errors);

		}  

	}

    
    if (d_scriptModule)
    {
        d_scriptModule->destroyBindings();
    }

	
    if (d_xmlParser)
    {
        d_xmlParser->cleanup();
        if (d_ourXmlParser)
            delete d_xmlParser;
    }

    
	
	
	
    WindowManager::getSingleton().destroyAllWindows();
    WindowManager::getSingleton().cleanDeadPool();

	
	WindowFactory* guiSheetFactory =
        WindowFactoryManager::getSingleton().getFactory(GUISheet::WidgetTypeName);

    WindowFactory* dragContainerFactory =
        WindowFactoryManager::getSingleton().getFactory(DragContainer::WidgetTypeName);

    WindowFactory* scrolledContainerFactory =
        WindowFactoryManager::getSingleton().getFactory(ScrolledContainer::WidgetTypeName);

    
	WindowFactoryManager::getSingleton().removeAllFactories();

	
	delete guiSheetFactory;
    delete dragContainerFactory;
    delete scrolledContainerFactory;

	
	delete	HyperLinkManager::getSingletonPtr();
	delete	SchemeManager::getSingletonPtr();
	delete	WindowManager::getSingletonPtr();
	delete	WindowFactoryManager::getSingletonPtr();
    delete  WidgetLookManager::getSingletonPtr();
	delete	FontManager::getSingletonPtr();
	delete	MouseCursor::getSingletonPtr();
	delete	ImagesetManager::getSingletonPtr();
	delete	GlobalEventSet::getSingletonPtr();

	
	
	delete Logger::getSingletonPtr();

	delete d_clickTrackerPimpl;
}



void System::renderGUI(void)
{
	
	
	
	
	
	
	
	
	
    static size_t number = 0;
	bool redraw = d_gui_redraw;
	if (d_gui_redraw)
	{
		UI_TRY
		d_renderer->resetZValue();
		d_renderer->setQueueingEnabled(true);
		d_renderer->clearRenderList();
		UI_CATCH( "System::renderGUI 1 - failed render." )

		UI_TRY
		if( KeyImageAnimationManager::getSingletonPtr() )
			KeyImageAnimationManager::getSingleton().clearRuntimeAnimateList();
		UI_CATCH( "System::renderGUI 2 - failed render." )

		UI_TRY
		if( HyperLinkManager::getSingletonPtr() )
			HyperLinkManager::getSingleton().destroyAllHyperLink();
		UI_CATCH( "System::renderGUI 3 - failed render." )

		UI_TRY
		if( FontManager::getSingletonPtr())
			FontManager::getSingleton().clearRuntimeBlinkList();
		UI_CATCH( "System::renderGUI 4 - failed render." )

		UI_TRY
		renderActiveSheet();
		UI_CATCH( "System::renderGUI 5 - failed render." )

		d_gui_redraw = false;
	}
	else
	{
		UI_TRY
		if( KeyImageAnimationManager::getSingletonPtr() )
			KeyImageAnimationManager::getSingleton().updateRuntimeAnimateList();
		UI_CATCH( "System::renderGUI 6 - failed render." )

		UI_TRY
		if( FontManager::getSingletonPtr())
			FontManager::getSingleton().updateRuntimeBlinkList();
		UI_CATCH( "System::renderGUI 7 - failed render." )
	}

	UI_TRY
	d_renderer->doRender(redraw);
	UI_CATCH( "System::renderGUI 8 - failed render." )

	UI_TRY
	
	d_renderer->setQueueingEnabled(false);
	MouseCursor::getSingleton().draw();
	UI_CATCH( "System::renderGUI 9 - failed render." )

	UI_TRY
    
    WindowManager::getSingleton().cleanDeadPool();	
	UI_CATCH( "System::renderGUI 10 - failed render." )
}


void System::renderActiveSheet()
{
	if (d_activeSheet != NULL)
	{
		UI_TRY
		d_activeSheet->renderPrepare();
		UI_CATCH( "renderActiveSheet 1 - System--renderActiveSheet." )
		UI_TRY
		FontManager::getSingleton().prepareFontTexture();
		UI_CATCH( "renderActiveSheet 2 - System--renderActiveSheet." )
		UI_TRY
		d_activeSheet->render();
		UI_CATCH( "renderActiveSheet 3 - System--renderActiveSheet." )

	}
}

Window* System::setGUISheet(Window* sheet)
{
	Window* old = d_activeSheet;
	d_activeSheet = sheet;

    
    
    if (sheet != 0)
    {
        WindowEventArgs sheetargs(0);
        sheet->onParentSized(sheetargs);
    }

	
	WindowEventArgs args(old);
	onGUISheetChanged(args);

	return old;
}



void System::setDefaultFont(const String& name)
{
	if (name.empty())
	{
		setDefaultFont(NULL);
	}
	else
	{
		setDefaultFont(FontManager::getSingleton().getFont(name));
	}

}



void System::setDefaultFont(Font* font)
{
	d_defaultFont = font;

	
	EventArgs args;
	onDefaultFontChanged(args);
}



void System::setDefaultMouseCursor(const Image* image)
{
    
    if (image == (const Image*)DefaultMouseCursor)
        image = 0;

    
    
    
    
    
    
    
    if (MouseCursor::getSingleton().getImage() == d_defaultMouseCursor)
    {
        
        if ((d_wndWithMouse) && (0 == d_wndWithMouse->getMouseCursor(false)))
        {
            
            MouseCursor::getSingleton().setImage(image);
        }
    }

    
    d_defaultMouseCursor = image;

    
    EventArgs args;
    onDefaultMouseCursorChanged(args);
}



void System::setDefaultMouseCursor(const String& imageset, const String& image_name)
{
	setDefaultMouseCursor(ImagesetManager::getSingleton().getImageset(imageset)->getImage(image_name));
}



ScriptModule* System::getScriptingModule(void) const
{
	return d_scriptModule;
}


ResourceProvider* System::getResourceProvider(void) const
{
	return d_resourceProvider;
}


void System::executeScriptFile(const String& filename, const String& resourceGroup) const
{
	if (d_scriptModule != NULL)
	{
		try
		{
			d_scriptModule->executeScriptFile(filename, resourceGroup);
		}
		catch(...)
		{
			throw GenericException((utf8*)"System::executeScriptFile - An exception was thrown during the execution of the script file.");
		}

	}
	else
	{
		Logger::getSingleton().logEvent((utf8*)"System::executeScriptFile - the script named '" + filename +"' could not be executed as no ScriptModule is available.", Errors);
	}

}



int	System::executeScriptGlobal(const String& function_name) const
{
	if (d_scriptModule != NULL)
	{
		try
		{
			return d_scriptModule->executeScriptGlobal(function_name);
		}
		catch(...)
		{
			throw GenericException((utf8*)"System::executeScriptGlobal - An exception was thrown during execution of the scripted function.");
		}

	}
	else
	{
		Logger::getSingleton().logEvent((utf8*)"System::executeScriptGlobal - the global script function named '" + function_name +"' could not be executed as no ScriptModule is available.", Errors);
	}

	return 0;
}



void System::executeScriptString(const String& str) const
{
    if (d_scriptModule != NULL)
    {
        try
        {
            d_scriptModule->executeString(str);
        }
        catch(...)
        {
            throw GenericException((utf8*)"System::executeScriptString - An exception was thrown during execution of the script code.");
        }

    }
    else
    {
        Logger::getSingleton().logEvent((utf8*)"System::executeScriptString - the script code could not be executed as no ScriptModule is available.", Errors);
    }
}



float System::getMouseMoveScaling(void) const
{
	return d_mouseScalingFactor;
}



void System::setMouseMoveScaling(float scaling)
{
	d_mouseScalingFactor = scaling;

	
	EventArgs args;
	onMouseMoveScalingChanged(args);
}



bool System::injectMouseMove(float delta_x, float delta_y)
{
	MouseEventArgs ma(NULL);
	MouseCursor& mouse = MouseCursor::getSingleton();

	ma.moveDelta.d_x = delta_x * d_mouseScalingFactor;
	ma.moveDelta.d_y = delta_y * d_mouseScalingFactor;
	ma.sysKeys = d_sysKeys;
	ma.wheelChange = 0;
	ma.clickCount = 0;

	
	mouse.offsetPosition(ma.moveDelta);
	ma.position = mouse.getPosition();

	Window* dest_window = getTargetWindow(ma.position, 3 );

	
	if (dest_window != NULL)
	{
		if (dest_window != d_wndWithMouse)
		{
			if (d_wndWithMouse != NULL)
			{
				ma.window = d_wndWithMouse;
				d_wndWithMouse->onMouseLeaves(ma);
			}

			d_wndWithMouse = dest_window;
			ma.window = dest_window;
			dest_window->onMouseEnters(ma);
		}

		
		ma.handled = false;

		if( HyperLinkManager::getSingletonPtr() )
		{
			int nGameCursor = 21;
			if(HyperLinkManager::getSingleton().isHyperLinkRange(dest_window,ma.position, nGameCursor))
			{
				
				MouseCursor::getSingleton().setGameCursor(nGameCursor);
			}
		}

		
		while ((!ma.handled) && (dest_window != NULL))
		{
			
			
			
			
			
			
			
			ma.window = dest_window;
			dest_window->onMouseMove(ma);
			dest_window = getNextTargetWindow(dest_window);
		}

	}

	return ma.handled;
}



bool System::injectMouseLeaves(void)
{
	MouseEventArgs ma(NULL);

	
	
	if (d_wndWithMouse != NULL)
	{
		ma.position = MouseCursor::getSingleton().getPosition();
		ma.moveDelta = Vector2(0.0f, 0.0f);
		ma.button = NoButton;
		ma.sysKeys = d_sysKeys;
		ma.wheelChange = 0;
		ma.window = d_wndWithMouse;
		ma.clickCount = 0;

		d_wndWithMouse->onMouseLeaves(ma);
		d_wndWithMouse = NULL;
	}

	return ma.handled;
}


bool System::injectMouseButtonDown(MouseButton button)
{
	
	d_sysKeys |= mouseButtonToSyskey(button);

	MouseEventArgs ma(NULL);
	ma.position = MouseCursor::getSingleton().getPosition();
	ma.moveDelta = Vector2(0.0f, 0.0f);
	ma.button = button;
	ma.sysKeys = d_sysKeys;
	ma.wheelChange = 0;

    
	Window* dest_window;
	if( button == LeftButton )
		dest_window = getTargetWindow(ma.position, 1);
	else
		dest_window = getTargetWindow(ma.position, 2);

    
	
	
	MouseClickTracker& tkr = d_clickTrackerPimpl->click_trackers[button];

	tkr.d_click_count++;

    
    if ((tkr.d_timer.elapsed() > d_dblclick_timeout) ||
        (!tkr.d_click_area.isPointInRect(ma.position)) ||
        (tkr.d_target_window != dest_window) ||
        (tkr.d_click_count > 3))
    {
        
        tkr.d_click_count = 1;

        
        tkr.d_click_area.setPosition(ma.position);
        tkr.d_click_area.setSize(d_dblclick_size);
        tkr.d_click_area.offset(Point(-(d_dblclick_size.d_width / 2), -(d_dblclick_size.d_height / 2)));

        
        tkr.d_target_window = dest_window;
    }

	
	ma.clickCount = tkr.d_click_count;

	
	while ((!ma.handled) && (dest_window != NULL))
	{
		
		if( dest_window->isMouseLButtonHollow(&ma.position) )
		{
			dest_window = getNextTargetWindow(dest_window);
			continue;
		}

		ma.window = dest_window;
        if (dest_window->wantsMultiClickEvents())
        {
            switch (tkr.d_click_count)
            {
            case 1:
                dest_window->onMouseButtonDown(ma);
                break;

            case 2:
                dest_window->onMouseDoubleClicked(ma);
                break;

            case 3:
                dest_window->onMouseTripleClicked(ma);
                break;
            }
        }
        
        
        else
        {
            dest_window->onMouseButtonDown(ma);
        }

		dest_window = getNextTargetWindow(dest_window);
	}

	
	tkr.d_timer.restart();

	return ma.handled;
}

bool System::injectMouseButtonRepeatDown(MouseButton button)
{
	
	d_sysKeys |= mouseButtonToSyskey(button);

	MouseEventArgs ma(NULL);
	ma.position = MouseCursor::getSingleton().getPosition();
	ma.moveDelta = Vector2(0.0f, 0.0f);
	ma.button = button;
	ma.sysKeys = d_sysKeys;
	ma.wheelChange = 0;

	
	Window* dest_window = NULL;
	if( button == LeftButton )
		dest_window = getTargetWindow(ma.position, 1);

	
	while ((!ma.handled) && (dest_window != NULL))
	{
		
		if(dest_window->getMouseHollow() || dest_window->isMouseButtonHollow(button)) 
		{
			dest_window = getNextTargetWindow(dest_window);
			continue;
		}

		ma.window = dest_window;
		if (dest_window->wantsMultiClickEvents())
		{
			dest_window->onMouseMultiDown(ma);
		}

		dest_window = getNextTargetWindow(dest_window);
	}

	return ma.handled;
}

bool System::injectMouseButtonUp(MouseButton button)
{
	
	d_sysKeys &= ~mouseButtonToSyskey(button);

	MouseEventArgs ma(NULL);
	ma.position = MouseCursor::getSingleton().getPosition();
	ma.moveDelta = Vector2(0.0f, 0.0f);
	ma.button = button;
	ma.sysKeys = d_sysKeys;
	ma.wheelChange = 0;

    
    MouseClickTracker& tkr = d_clickTrackerPimpl->click_trackers[button];
    
    ma.clickCount = tkr.d_click_count;

    Window* initial_dest_window;
	if( button == LeftButton )
		initial_dest_window = getTargetWindow(ma.position, 1);
	else
		initial_dest_window = getTargetWindow(ma.position, 2);

	Window* dest_window = initial_dest_window;

	
	while ((!ma.handled) && (dest_window != NULL))
	{
		
		if(dest_window->getMouseHollow() || dest_window->isMouseButtonHollow(button)) 
		{
			dest_window = getNextTargetWindow(dest_window);
			continue;
		}

		ma.window = dest_window;
		dest_window->onMouseButtonUp(ma);
		dest_window = getNextTargetWindow(dest_window);
	}

	bool wasUpHandled = ma.handled;

    
    
     if ((tkr.d_click_area.isPointInRect(ma.position)) &&
        (tkr.d_target_window == initial_dest_window))
    {
		ma.handled = false;
        dest_window = initial_dest_window;

		
		while ((!ma.handled) && (dest_window != NULL))
		{
			
			if(dest_window->getMouseHollow()) 
			{
				dest_window = getNextTargetWindow(dest_window);
				continue;
			}

			ma.window = dest_window;

			if( HyperLinkManager::getSingletonPtr() )
			{
				if(button == LeftButton)
				{
					if( dest_window->doHyperLinkByMouseLeft(ma.position) || 
						HyperLinkManager::getSingleton().doHyperLinkByMouseLeft(dest_window,ma.position) )
						ma.handled = true;
				}
				else if(button == RightButton)
				{
					if( dest_window->doHyperLinkByMouseRight(ma.position) || 
						HyperLinkManager::getSingleton().doHyperLinkByMouseRight(dest_window,ma.position) )
						ma.handled = true;
				}
			}

			if(dest_window->isMouseButtonHollow(button))
			{
				dest_window = getNextTargetWindow(dest_window);
				continue;
			}

			dest_window->onMouseClicked(ma);
			dest_window = getNextTargetWindow(dest_window);
		}
	}

	
	
	
	
	

	return (ma.handled | wasUpHandled);
}



bool System::injectKeyDown(uint key_code)
{
	
	d_sysKeys |= keyCodeToSyskey((Key::Scan)key_code, true);

	KeyEventArgs args(NULL);

	if (d_activeSheet != NULL)
	{
		args.scancode = (Key::Scan)key_code;
		args.sysKeys = d_sysKeys;

		Window* dest = getKeyboardTargetWindow();

		
		while ((dest != NULL) && (!args.handled))
		{
			args.window = dest;
			dest->onKeyDown(args);
			dest = getNextTargetWindow(dest);
		}

	}

	return args.handled;
}



bool System::injectKeyUp(uint key_code)
{
	
	d_sysKeys &= ~keyCodeToSyskey((Key::Scan)key_code, false);

	KeyEventArgs args(NULL);

	if (d_activeSheet != NULL)
	{
		args.scancode = (Key::Scan)key_code;
		args.sysKeys = d_sysKeys;

		Window* dest = getKeyboardTargetWindow();

		
		while ((dest != NULL) && (!args.handled))
		{
			args.window = dest;
			dest->onKeyUp(args);
			dest = getNextTargetWindow(dest);
		}

	}

	return args.handled;
}



bool System::injectChar(utf32 code_point)
{
	KeyEventArgs args(NULL);

	if (d_activeSheet != NULL)
	{
		args.codepoint = code_point;
		args.sysKeys = d_sysKeys;

		Window* dest = NULL;

		if( ImeModule::HasInputFocus() ) 
		{
			if( !ImeModule::HasForbidInput() )
				dest = ImeModule::GetActiveIMEEditBox();

			if (d_modalTarget != NULL && dest != d_modalTarget)
			{
				if( dest && !dest->isAncestor(d_modalTarget) )
				{
					if ( d_modalTarget->getSpecialModalMode() )
					{
						
						if( !dest->getSpecialModal() )
						{
							dest = NULL;
						}
					}
					else
					{
						dest = NULL;
					}
				}
			}
		}
		else
		{
			dest = getKeyboardTargetWindow();
		}

		
		while ((dest != NULL) && (!args.handled))
		{
			args.window = dest;
			dest->onCharacter(args);
			dest = getNextTargetWindow(dest);
		}

	}

	return args.handled;
}



bool System::injectMouseWheelChange(float delta)
{
	MouseEventArgs ma(NULL);
	ma.position = MouseCursor::getSingleton().getPosition();
	ma.moveDelta = Vector2(0.0f, 0.0f);
	ma.button = NoButton;
	ma.sysKeys = d_sysKeys;
	ma.wheelChange = delta;
	ma.clickCount = 0;

	Window* dest_window = getTargetWindow(ma.position);

	
	while ((!ma.handled) && (dest_window != NULL))
	{
		ma.window = dest_window;
		dest_window->onMouseWheel(ma);
		dest_window = getNextTargetWindow(dest_window);
	}

	return ma.handled;
}



bool System::injectMousePosition(float x_pos, float y_pos)
{
	
	MouseCursor::getSingleton().setPosition(Point(x_pos, y_pos));

	
	return injectMouseMove(0, 0);
}



bool System::injectTimePulse(float timeElapsed)
{
	RealTimeWindowSet::iterator it = d_needRealtimeUpdateWindowSet.begin();
	while(it != d_needRealtimeUpdateWindowSet.end())
	{
		(*it)->update(timeElapsed);
		it++;
	}
	
	
	
	
	d_timeElapsed += timeElapsed;

	if(FontManager::getSingletonPtr())
		FontManager::getSingleton().calculateBlinkAlphaValue();

	return true;
}



Window*	System::getTargetWindow(const Point& pt, int nEventType ) const
{
	Window* dest_window = NULL;

	
	if (d_activeSheet != NULL)
	{
		dest_window = Window::getCaptureWindow();

		if (dest_window == NULL)
		{
			dest_window = getActiveSheetChildAtPosition(pt, nEventType);

			if (dest_window == NULL)
			{
				dest_window = d_activeSheet;
			}
		}
		else
		{
            if (dest_window->distributesCapturedInputs())
            {
                Window* child_window = dest_window->getChildAtPosition(pt, nEventType);

                if (child_window != NULL)
                {
                    dest_window = child_window;
                }
            }
		}

		
		if (d_modalTarget != NULL && dest_window != d_modalTarget)
		{
			if( dest_window && !dest_window->isAncestor(d_modalTarget) )
			{
				if ( d_modalTarget->getSpecialModalMode() )
				{
					
					if( !dest_window->getSpecialModal() )
					{
						dest_window = d_modalTarget;
					}
				}
				else
				{
					dest_window = d_modalTarget;
				}
			}
		}
	}

	return dest_window;
}

Window*	System::getActiveSheetChildAtPosition(const Point& position, int nEventType) const
{
	return d_activeSheet->getChildAtPosition(position, nEventType);
}


Window* System::getKeyboardTargetWindow(void) const
{
	if( ImeModule::GetActiveIMEEditBox() ) 
	{
		Window* dest = NULL;

		dest = ImeModule::GetActiveIMEEditBox();

		if (d_modalTarget != NULL && dest != d_modalTarget)
		{
			if( dest && !dest->isAncestor(d_modalTarget) )
			{
				if ( d_modalTarget->getSpecialModalMode() )
				{
					
					if( !dest->getSpecialModal() )
					{
						dest = NULL;
					}
				}
				else
				{
					dest = NULL;
				}
			}
		}
		return dest;
	}

	Window* target = NULL;

	if (d_modalTarget == NULL)
	{
		target = d_activeSheet->getActiveChild();
	}
	else
	{
		target = d_modalTarget->getActiveChild();
		if (target == NULL)
		{
			target = d_modalTarget;
		}
	}

	return target;
}



Window* System::getNextTargetWindow(Window* w) const
{
	
	if (w != d_modalTarget)
	{
		return w->getParent();
	}

	
	return NULL;
}



SystemKey System::mouseButtonToSyskey(MouseButton btn) const
{
	switch (btn)
	{
	case LeftButton:
		return LeftMouse;

	case RightButton:
		return RightMouse;

	case MiddleButton:
		return MiddleMouse;

	case X1Button:
		return X1Mouse;

	case X2Button:
		return X2Mouse;

	default:
		throw InvalidRequestException((utf8*)"System::mouseButtonToSyskey - the parameter 'btn' is not a valid MouseButton value.");
	}
}



SystemKey System::keyCodeToSyskey(Key::Scan key, bool direction)
{
	switch (key)
	{
	case Key::LeftShift:
		d_lshift = direction;

		if (!d_rshift)
		{
			return Shift;
		}
		break;

	case Key::RightShift:
		d_rshift = direction;

		if (!d_lshift)
		{
			return Shift;
		}
		break;


	case Key::LeftControl:
		d_lctrl = direction;

		if (!d_rctrl)
		{
			return Control;
		}
		break;

	case Key::RightControl:
		d_rctrl = direction;

		if (!d_lctrl)
		{
			return Control;
		}
		break;

	case Key::LeftAlt:
		d_lalt = direction;

		if (!d_ralt)
		{
			return Alt;
		}
		break;

	case Key::RightAlt:
		d_ralt = direction;

		if (!d_lalt)
		{
			return Alt;
		}
		break;

    default:
        break;
	}

	
	return (SystemKey)0;
}


System&	System::getSingleton(void)
{
	return Singleton<System>::getSingleton();
}


System*	System::getSingletonPtr(void)
{
	return Singleton<System>::getSingletonPtr();
}




void System::setSingleClickTimeout(double timeout)
{
	d_click_timeout = timeout;

	
	EventArgs args;
	onSingleClickTimeoutChanged(args);
}



void System::setMultiClickTimeout(double timeout)
{
	d_dblclick_timeout = timeout;

	
	EventArgs args;
	onMultiClickTimeoutChanged(args);
}



void System::setMultiClickToleranceAreaSize(const Size&	sz)
{
	d_dblclick_size = sz;

	
	EventArgs args;
	onMultiClickAreaSizeChanged(args);
}


void System::onGUISheetChanged(WindowEventArgs& e)
{
	fireEvent(EventGUISheetChanged, e, EventNamespace);
}



void System::onSingleClickTimeoutChanged(EventArgs& e)
{
	fireEvent(EventSingleClickTimeoutChanged, e, EventNamespace);
}



void System::onMultiClickTimeoutChanged(EventArgs& e)
{
	fireEvent(EventMultiClickTimeoutChanged, e, EventNamespace);
}



void System::onMultiClickAreaSizeChanged(EventArgs& e)
{
	fireEvent(EventMultiClickAreaSizeChanged, e, EventNamespace);
}



void System::onDefaultFontChanged(EventArgs& e)
{
	fireEvent(EventDefaultFontChanged, e, EventNamespace);
}



void System::onDefaultMouseCursorChanged(EventArgs& e)
{
	fireEvent(EventDefaultMouseCursorChanged, e, EventNamespace);
}



void System::onMouseMoveScalingChanged(EventArgs& e)
{
	fireEvent(EventMouseMoveScalingChanged, e, EventNamespace);
}



bool System::handleDisplaySizeChange(const EventArgs& e)
{
	
	Size new_sz = getRenderer()->getSize();
	ImagesetManager::getSingleton().notifyScreenResolution(new_sz);
	FontManager::getSingleton().notifyScreenResolution(new_sz);

	
	
	if (d_activeSheet != NULL)
	{
		WindowEventArgs args(NULL);
		d_activeSheet->onParentSized(args);

		d_activeSheet->postSizeChanged();
	}

	return true;
}



void System::notifyWindowDestroyed(const Window* window)
{
	if (d_wndWithMouse == window)
	{
		d_wndWithMouse = NULL;
	}

	if (d_activeSheet == window)
	{
		d_activeSheet = NULL;
	}

	if (d_modalTarget == window)
	{
		d_modalTarget = NULL;
	}

}

void System::setTooltip(Tooltip* tooltip)
{
    
    if (d_defaultTooltip && d_weOwnTooltip)
        WindowManager::getSingleton().destroyWindow(d_defaultTooltip);

    
    d_weOwnTooltip = false;
    d_defaultTooltip = tooltip;
}

void System::setTooltip(const String& tooltipType)
{
    
    if (d_defaultTooltip && d_weOwnTooltip)
        WindowManager::getSingleton().destroyWindow(d_defaultTooltip);

    if (tooltipType.empty())
    {
        d_defaultTooltip = 0;
        d_weOwnTooltip = false;
    }
    else
    {
        try
        {
            d_defaultTooltip = static_cast<Tooltip*>(WindowManager::getSingleton().createWindow(tooltipType, "CEGUI::System::default__auto_tooltip__"));
            d_weOwnTooltip = true;
        }
        catch(UnknownObjectException x)
        {
            d_defaultTooltip = 0;
            d_weOwnTooltip = false;
        }
    }
}
float	System::getCurTimeElapsed()
{
	return d_timeElapsed;
}

} 
