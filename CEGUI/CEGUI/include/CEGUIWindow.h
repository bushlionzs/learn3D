

#ifndef _CEGUIWindow_h_
#define _CEGUIWindow_h_

#include "OgreCEGUIRenderer.h"

#include "CEGUIBase.h"
#include "CEGUIString.h"
#include "CEGUIVector.h"
#include "CEGUIRect.h"
#include "CEGUISize.h"
#include "CEGUIEventSet.h"
#include "CEGUIPropertySet.h"
#include "CEGUISystem.h"
#include "CEGUIInputEvent.h"
#include "CEGUIWindowProperties.h"
#include "CEGUIUDim.h"
#include "CEGUIRenderCache.h"
#include "CEGUIWindowFactoryManager.h"
#include "CEGUIWindowFactory.h"
#include "CEGUIKeyImageAnimation.h"
#include "CEGUIFontManager.h"
#include "CEGUIHyperLinkManager.h"
#include <vector>


#if defined(_MSC_VER)
#	pragma warning(push)
#	pragma warning(disable : 4251)
#endif



namespace CEGUI
{


enum MetricsMode
{
	Relative,		
	Absolute,		
	Inherited		
};

enum HookMode
{
	Hook_None = 0,
	Hook_Left,
	Hook_Right,
	Hook_Top,
	Hook_Bottom,
	Hook_LeftTop,
	Hook_LeftBottom,
	Hook_RightTop,
	Hook_RightBottom,
	Hook_Center,
};

enum VerticalAlignment
{
    VA_TOP,        
    VA_CENTRE,     
    VA_BOTTOM      
};


enum HorizontalAlignment
{
    HA_LEFT,        
    HA_CENTRE,      
    HA_RIGHT        
};

enum BaseHorizonE
{
	BHE_LEFT,
	BHE_CENTER,
	BHE_RIGHT,
	BHE_UNKNOWN,
};


class CEGUIEXPORT Window : public PropertyReceiver, public EventSet
{

public:
	static const String EventNamespace;				

	
	
	static const String EventParentSized;				
	static const String EventSized;					
	static const String EventMoved;					
	static const String EventTextChanged;				
	static const String EventFontChanged;				
	static const String EventAlphaChanged;			
	static const String EventIDChanged;				
	static const String EventActivated;				
	static const String EventDeactivated;				
	static const String EventShown;					
	static const String EventHidden;					
	static const String EventParentHidden;				
	static const String EventEnabled;					
	static const String EventDisabled;				
	static const String EventMetricsModeChanged;		
	static const String EventClippedByParentChanged;	
	static const String EventDestroyedByParentChanged;
	static const String EventInheritsAlphaChanged;	
	static const String EventAlwaysOnTopChanged;		
	static const String EventInputCaptureGained;		
	static const String EventInputCaptureLost;		
	static const String EventRenderingStarted;		
	static const String EventRenderingEnded;			
	static const String EventChildAdded;				
	static const String EventChildRemoved;			
	static const String EventDestructionStarted;		
	static const String EventZOrderChanged;			
	static const String EventDragDropItemEnters;	
	static const String EventDragDropItemLeaves;	
	static const String EventDragDropItemDropped;	
    static const String EventVerticalAlignmentChanged;    
    static const String EventHorizontalAlignmentChanged;  

	
	static const String EventMouseEnters;				
	static const String EventMouseLeaves;				
	static const String EventMouseMove;				
	static const String EventMouseWheel;				
	static const String EventMouseButtonDown;			
	static const String EventMouseButtonUp;			
	static const String EventMouseClick;				
	static const String EventMouseDoubleClick;		
	static const String EventMouseTripleClick;		
	static const String EventKeyDown;					
	static const String EventKeyUp;					
	static const String EventCharacterKey;			
	static const String EventMouseLClick;
	static const String EventMouseRClick;
	static const String EventMouseLButtonDown;			
	static const String EventMouseRButtonDown;			

	
	static const String EventMouseMultiDown;

	
	
	Window(const String& type, const String& name);


	
	virtual ~Window(void);


	
	
	const String& getWidgetType(void) const	{ return d_type; }

	
	const String& getType(void) const;


	
	const String& getName(void) const		{return d_name;}


	
	bool	isDestroyedByParent(void) const		{return d_destroyedByParent;}


	
	bool	isAlwaysOnTop(void) const			{return d_alwaysOnTop;}


	
	bool	isDisabled(bool localOnly = false) const;


	
	bool	isVisible(bool localOnly = false) const;


	
	virtual bool	isActive(void) const;


	
	bool	isClippedByParent(void) const		{return d_clippedByParent;}


	
	uint	getID(void) const		{return d_ID;}


	
	uint   getChildCount(void) const      {return (uint)d_children.size();}


	
	bool	isChild(const String& name) const;


	
	bool	isChild(uint ID) const;


	
	bool	isChild(const Window* window) const;


	
	Window*	getChild(const String& name) const;


	
	Window* getChild(uint ID) const;


	
	Window*	getChildAtIdx(uint idx) const		{return d_children[idx];}


	
	Window*	getActiveChild(void);
	const Window* getActiveChild(void) const;


	
	bool	isAncestor(const String& name) const;


	
	bool	isAncestor(uint ID) const;


	
	bool	isAncestor(const Window* window) const;


	
	const Font*		getFont(bool useDefault = true) const;

	
	const bool		getMouseHollow(void) const		{return d_mouseHollow;}

	const bool		getMouseMoveHollow(void) const		{return d_mouseMoveHollow;}

	
	const bool		getMouseLButtonHollow(void) const		{return d_mouseLButtonHollow;}


	
	const bool		getMouseRButtonHollow(void) const		{return d_mouseRButtonHollow;}

	
	const String&	getTextOriginal(void) const		{return d_textOriginal;}
	const String&	getText(void) const		{return d_text;}


	
	bool	inheritsAlpha(void) const		{return d_inheritsAlpha;}


	
	float	getAlpha(void) const			{return d_alpha;}


	
	float	getEffectiveAlpha(void) const;


	
	Rect	getRect(void) const;


	
	virtual Rect	getPixelRect(void) const;


	
	Rect	getInnerRect(void) const;


	
	Rect	getUnclippedPixelRect(void) const;


	
	virtual Rect	getUnclippedInnerRect(void) const;


	
	static	Window*	getCaptureWindow(void)		{return d_captureWindow;}
	static	void	setCaptureWindow(Window* window = NULL)		{ d_captureWindow = window;}


	
	bool	isCapturedByThis(void) const		{return getCaptureWindow() == this;}


	
	bool	isCapturedByAncestor(void) const	{return isAncestor(getCaptureWindow());}


	
	bool	isCapturedByChild(void) const		{return isChild(getCaptureWindow());}


	
	virtual bool	isHit(const Point& position) const;


	
	Window*	getChildAtPosition(const Point& position, int nEventType = 0 ) const;


	
	MetricsMode	getMetricsMode(void) const;


	
	float	getXPosition(void) const;


	
	float	getYPosition(void) const;


	
	Point	getPosition(void) const;


	
	float	getWidth(void) const;

	
	float	getHeight(void) const;


	
	Size	getSize(void) const;


	
	Window*	getParent(void) const				{return d_parent;}


	
	Size	getMaximumSize(void) const;


	
	Size	getMinimumSize(void) const;


	
	const Image*	getMouseCursor(bool useDefault = true) const;


	
    Rect	getRelativeRect(void) const				{ return d_area.asRelative(getParentSize()); }


	
	Point	getRelativePosition(void) const			{ return d_area.getPosition().asRelative(getParentSize()); }


	
	float	getRelativeXPosition(void) const		{ return d_area.d_min.d_x.asRelative(getParentWidth()); }


	
	float	getRelativeYPosition(void) const		{ return d_area.d_min.d_y.asRelative(getParentHeight()); }


	
    Size	getRelativeSize(void) const				{ return d_area.getSize().asRelative(getParentSize()).asSize(); }


	
	float	getRelativeWidth(void) const			{ return d_area.getWidth().asRelative(getParentWidth()); }


	
	float	getRelativeHeight(void) const			{ return d_area.getHeight().asRelative(getParentHeight()); }


	
	Rect	getAbsoluteRect(void) const				{ return Rect(d_area.getPosition().asAbsolute(getParentSize()), d_pixelSize); }


	
	Point	getAbsolutePosition(void) const			{ return d_area.getPosition().asAbsolute(getParentSize()); }


	
	float	getAbsoluteXPosition(void) const		{ return d_area.d_min.d_x.asAbsolute(getParentWidth()); }


	
	float	getAbsoluteYPosition(void) const		{ return d_area.d_min.d_y.asAbsolute(getParentHeight()); }


	
	Size	getAbsoluteSize(void) const				{ return d_pixelSize; }


	
	float	getAbsoluteWidth(void) const			{ return d_pixelSize.d_width; }


	
	float	getAbsoluteHeight(void) const			{ return d_pixelSize.d_height; }


	
	void*	getUserData(void) const			{return d_userData;}


	
	float	getXPosition(MetricsMode mode) const;


	
	float	getYPosition(MetricsMode mode) const;


	
	Point	getPosition(MetricsMode mode) const;


	
	float	getWidth(MetricsMode mode) const;


	
	float	getHeight(MetricsMode mode) const;


	
	Size	getSize(MetricsMode mode) const;


	
	Rect	getRect(MetricsMode mode) const;


	
	bool	restoresOldCapture(void) const		{return d_restoreOldCapture;}


	
	bool	isZOrderingEnabled(void) const;


    
    bool    wantsMultiClickEvents(void) const;


    
    bool    isMouseAutoRepeatEnabled(void) const;


    
    float   getAutoRepeatDelay(void) const;

    
    
    float   getAutoRepeatRate(void) const;


    
    bool    distributesCapturedInputs(void) const;


    
    bool isUsingDefaultTooltip(void) const;

    
    Tooltip* getTooltip(void) const;

    
    String getTooltipType(void) const;

    
    const String& getTooltipText(void) const;

    
    bool inheritsTooltipText(void) const;

    
    bool isRiseOnClickEnabled(void) const   { return d_riseOnClick; }

	
	bool testClassName(const String& class_name) const		{return testClassName_impl(class_name);}

	bool isHandleKeyboard() const							{return d_isHandleKeyboard;}
	void setHandleKeyboard(bool isHandle)					{ d_isHandleKeyboard = isHandle;}

    
    VerticalAlignment getVerticalAlignment() const  {return d_vertAlign;}

    
    HorizontalAlignment getHorizontalAlignment() const  {return d_horzAlign;}

    
    RenderCache& getRenderCache()   { return d_renderCache; }

    
    const String& getLookNFeel();

	
	bool getModalState(void) const	{return (System::getSingleton().getModalTarget() == this);}


	
    const String& getUserString(const String& name) const;

    
    bool isUserStringDefined(const String& name) const;

    
    Window* getActiveSibling();

    
	
    void rename(const String& new_name);

    
	virtual void	initialise(void) {}


	
	void	setDestroyedByParent(bool setting);


	
	void	setAlwaysOnTop(bool setting);

	
	void	setWindowLayOutNum(int laynum);


	
	void	setEnabled(bool setting);


	
	void	enable(void)		{setEnabled(true);}


	
	void	disable(void)		{setEnabled(false);}


	
	void	setVisible(bool setting);


	
	void	show(void)			{setVisible(true);}


	
	void	hide(void)			{setVisible(false);}


	
	void	activate(void);


	
	void	deactivate(void);


	
	void	setClippedByParent(bool setting);
	

	
	void	setID(uint ID);


	
	virtual void	setMouseHollow(bool mousehollow);

	virtual void	setMouseMoveHollow(bool mousehollow);

	
	virtual void	setMouseLButtonHollow(bool mousehollow);

	
	virtual void	setMouseRButtonHollow(bool mousehollow);

	
	void	setTextOriginal(const String& text);
	virtual void	setText(const String& text);


	
	void	setWidth(float width);


	
	void	setHeight(float height);


	
	void	setSize(const Size& size);


	
	void	setXPosition(float x);


	
	void	setYPosition(float y);


	
	void	setPosition(const Point& position);


	
	void	setAreaRect(const Rect& area);

	
	
	void	setFont(const Font* font);


	
	void	setFont(const String& name);


	
	void	addChildWindow(const String& name);


	
	void	addChildWindow(Window* window);


	
	void	removeChildWindow(const String& name);


	
	void	removeChildWindow(Window* window);


	
	void	removeChildWindow(uint ID);


	
	void	moveToFront();


	
	void	moveToBack();


	
	bool	captureInput(void);


	
	void	releaseInput(void);


	
	void	setRestoreCapture(bool setting);


	
	void	setAlpha(float alpha);


	
	void	setInheritsAlpha(bool setting);


	
	void	requestRedraw(void) const;


	
	void setMetricsMode(MetricsMode	mode);


	
	void	setMinimumSize(const Size& sz);


	
	void	setMaximumSize(const Size& sz);


	
	void	setMouseCursor(const Image* image)		{d_mouseCursor = image;}


	
	void	setMouseCursor(MouseCursorImage image)		{d_mouseCursor = (const Image*)image;}


	
	void	setMouseCursor(const String& imageset, const String& image_name);


	
	void	setUserData(void* user_data)		{d_userData = user_data;}


	
	void	setXPosition(MetricsMode mode, float x);


	
	void	setYPosition(MetricsMode mode, float y);


	
	void	setPosition(MetricsMode mode, const Point& position);


	
	void	setWidth(MetricsMode mode, float width);


	
	void	setHeight(MetricsMode mode, float height);


	
	virtual void	setSize(MetricsMode mode, const Size& size);

	
	void	setRect(MetricsMode mode, const Rect& area);


	
	void	setZOrderingEnabled(bool setting);


    
    void setWantsMultiClickEvents(bool setting);

    
    
    void    setMouseAutoRepeatEnabled(bool setting);


    
    void   setAutoRepeatDelay(float delay);

    
    
    void   setAutoRepeatRate(float rate);


    
    void    setDistributesCapturedInputs(bool setting);

    
    void    notifyDragDropItemEnters(DragContainer* item);

    
    void    notifyDragDropItemLeaves(DragContainer* item);

    
    void    notifyDragDropItemDropped(DragContainer* item);

    
    virtual void    destroy(void);

    
    void setTooltip(Tooltip* tooltip);

    
    void setTooltipType(const String& tooltipType);

    
    void setTooltipText(const String& tip);

	
    void setInheritsTooltipText(bool setting);

    
    void setRiseOnClickEnabled(bool setting)    { d_riseOnClick = setting; }

    
    void setVerticalAlignment(const VerticalAlignment alignment);

    
    void setHorizontalAlignment(const HorizontalAlignment alignment);

    
    void setLookNFeel(const String& falagardType, const String& look);

	
	void setModalState(bool state);

    
    virtual void performChildWindowLayout();

    
    void setUserString(const String& name, const String& value);

    
	
	float	absoluteToRelativeX(float val) const;


	
	float	absoluteToRelativeY(float val) const;


	
	Point	absoluteToRelative(const Point& pt) const;


	
	Size	absoluteToRelative(const Size& sze) const;


	
	Rect	absoluteToRelative(const Rect& rect) const;


	
	float	relativeToAbsoluteX(float val) const;


	
	float	relativeToAbsoluteY(float val) const;


	
	Point	relativeToAbsolute(const Point& pt) const;


	
	Size	relativeToAbsolute(const Size& sze) const;


	
	Rect	relativeToAbsolute(const Rect& rect) const;


	
	float	windowToScreenX(float x) const;


	
	float	windowToScreenY(float y) const;
	
	
	
	Point	windowToScreen(const Point& pt) const;


	
	Size	windowToScreen(const Size& sze) const;


	
	Rect	windowToScreen(const Rect& rect) const;


	
	float	screenToWindowX(float x) const;


	
	float	screenToWindowY(float y) const;


	
	Point	screenToWindow(const Point& pt) const;


	
	Size	screenToWindow(const Size& sze) const;


	
	Rect	screenToWindow(const Rect& rect) const;


    
    float unifiedToRelativeX(const UDim& val) const;


    
    float	unifiedToRelativeY(const UDim& val) const;


    
    Vector2 unifiedToRelative(const UVector2& val) const;


    
    Rect unifiedToRelative(const URect& val) const;


    
    float unifiedToAbsoluteX(const UDim& val) const;


    
    float	unifiedToAbsoluteY(const UDim& val) const;


    
    Vector2 unifiedToAbsolute(const UVector2& val) const;


    
    Rect unifiedToAbsolute(const URect& val) const;


    
    float windowToScreenX(const UDim& x) const;


    
    float windowToScreenY(const UDim& y) const;


    
    Vector2 windowToScreen(const UVector2& vec) const;


    
    Rect windowToScreen(const URect& rect) const;


    
    float screenToWindowX(const UDim& x) const;


    
    float screenToWindowY(const UDim& y) const;


    
    Vector2 screenToWindow(const UVector2& vec) const;


    
    Rect screenToWindow(const URect& rect) const;


    
    
    void setWindowArea(const UDim& xpos, const UDim& ypos, const UDim& width, const UDim& height);
    
    
    void setWindowArea(const UVector2& pos, const UVector2& size);
    
    
    void setWindowArea(const URect& area);
    
    
    void setWindowPosition(const UVector2& pos);

    
    void setWindowXPosition(const UDim& x);

    
    void setWindowYPosition(const UDim& y);

    
    void setWindowSize(const UVector2& size);

    
    void setWindowWidth(const UDim& width);

    
    void setWindowHeight(const UDim& height);

    
    void setWindowMaxSize(const UVector2& size);

    
    void setWindowMinSize(const UVector2& size);

	void setIgnoreMaxSizeFlag(bool bIgnore);

    
    const URect& getWindowArea() const;

	
	const int getWindowLayOutNum() const;

    
    const UVector2& getWindowPosition() const;

    
    const UDim& getWindowXPosition() const;

    
    const UDim& getWindowYPosition() const;

    
    UVector2 getWindowSize() const;

    
    UDim getWindowWidth() const;

    
    UDim getWindowHeight() const;

    
    const UVector2& getWindowMaxSize() const;

    
    const UVector2& getWindowMinSize() const;

	void	setTexcoordPercentX( float x )	{ d_xpercent = x; }
	void	setTexcoordPercentY( float y )	{ d_ypercent = y; }
	void	saveOldArea();
	void	revertOldArea();
	void	setAreaAndTexCoord( int iDir_X, float fXPercent, int iDir_Y, float fYPercent );


	
	
	void	renderPrepare(void);

	
	void	render(void);


	
	void	update(float elapsed);
	void	updateAll(float elapsed);


    
    virtual void writeXMLToStream(OutStream& out_stream) const;

	
	bool	isPropertyPresent(const String& name) const;

	
	String	getProperty(const String& name) const;

	
	void setProperty(const String& name, const String& value);

	
	bool isPropertyDefault(const String& name) const;

	
	String	getPropertyDefault(const String& name) const;

	
	virtual void postSizeChanged(void);

	
	void	setStepShowTime(float seconds);
	void	setCurStepShowTime(float seconds) {d_currentStepShowTime = seconds; }
	float	getStepShowTime() const ;
	void	setEnableStepShow(bool setting) {d_enableStepShow = setting; }

	void	setNeedRealTimeUpdate(bool);
	void	setGroupWindow(bool);
	void	setBaseTop(bool flag);
	void	setBaseLeft(BaseHorizonE flag);

	virtual void setSpecialModal(bool spModual);
	bool	getSpecialModal() {return d_specialModal;}

	void	setSpecialModalMode(bool mode) { d_specialModalMode = mode; }
	bool	getSpecialModalMode() { return d_specialModalMode; }

	void setHyperLinkColorDefault(DWORD dwDefaultColor);
	void setHyperLinkColorActive(DWORD dwActiveColor);
	DWORD getHyperLinkColorDefault() const;
	DWORD getHyperLinkColorActive() const;

	void setExtendTooltip(bool flag);
	bool getExtendTooltip();

protected:
	
	friend	class System;


	
	
	virtual void	onSized(WindowEventArgs& e);


	
	virtual void	onMoved(WindowEventArgs& e);


	
	virtual void	onTextChanged(WindowEventArgs& e);


	
	virtual void	onFontChanged(WindowEventArgs& e);


	
	virtual void	onAlphaChanged(WindowEventArgs& e);


	
	virtual void	onIDChanged(WindowEventArgs& e);


	
	virtual void	onShown(WindowEventArgs& e);


	
	virtual void	onHidden(WindowEventArgs& e);

	
	virtual void	onParentHidden(void);

	
	virtual void	onEnabled(WindowEventArgs& e);


	
	virtual void	onDisabled(WindowEventArgs& e);


	
	virtual void	onMetricsChanged(WindowEventArgs& e);


	
	virtual void	onClippingChanged(WindowEventArgs& e);


	
	virtual void	onParentDestroyChanged(WindowEventArgs& e);


	
	virtual void	onInheritsAlphaChanged(WindowEventArgs& e);


	
	virtual void	onAlwaysOnTopChanged(WindowEventArgs& e);


	
	virtual void	onCaptureGained(WindowEventArgs& e);


	
	virtual void	onCaptureLost(WindowEventArgs& e);


	
	virtual void	onRenderingStarted(WindowEventArgs& e);


	
	virtual void	onRenderingEnded(WindowEventArgs& e);


	
	virtual void	onZChanged(WindowEventArgs& e);


	
	virtual void	onDestructionStarted(WindowEventArgs& e);


	
	virtual void	onActivated(ActivationEventArgs& e);


	
	virtual void	onDeactivated(ActivationEventArgs& e);


	
	virtual void	onParentSized(WindowEventArgs& e);


	
	virtual void	onChildAdded(WindowEventArgs& e);


	
	virtual void	onChildRemoved(WindowEventArgs& e);


	
	virtual void	onMouseEnters(MouseEventArgs& e);


	
	virtual void	onMouseLeaves(MouseEventArgs& e);


	
	virtual void	onMouseMove(MouseEventArgs& e);


	
	virtual void	onMouseWheel(MouseEventArgs& e);


	
	virtual void	onMouseButtonDown(MouseEventArgs& e);


	
	virtual void	onMouseButtonUp(MouseEventArgs& e);


	
	virtual void	onMouseClicked(MouseEventArgs& e);


	
	virtual void	onMouseDoubleClicked(MouseEventArgs& e);


	
	virtual void	onMouseTripleClicked(MouseEventArgs& e);

	
	virtual void	onMouseMultiDown(MouseEventArgs& e);


	
	virtual void	onKeyDown(KeyEventArgs& e);


	
	virtual void	onKeyUp(KeyEventArgs& e);


	
	virtual void	onCharacter(KeyEventArgs& e);

    
    virtual void    onDragDropItemEnters(DragDropEventArgs& e);


    
    virtual void    onDragDropItemLeaves(DragDropEventArgs& e);


    
    virtual void    onDragDropItemDropped(DragDropEventArgs& e);

    
    
    virtual void    onVerticalAlignmentChanged(WindowEventArgs& e);

    
    
    virtual void    onHorizontalAlignmentChanged(WindowEventArgs& e);

    
	
	
	virtual void	updateSelf(float elapsed);

	
	virtual	void	prepareBigchar(void);

	
	virtual	void	drawSelf(float z);


	
    virtual void populateRenderCache()  {}


	
	virtual bool	testClassName_impl(const String& class_name) const
	{
		if (class_name==(const utf8*)"Window")	return true;
		return false;
	}


	
	void	setParent(Window* parent);


	
	float	getParentWidth(void) const;


	
	float	getParentHeight(void) const;


	
	Size	getParentSize(void) const;


	
	Rect	absoluteToRelative_impl(const Window* window, const Rect& rect) const;
	Size	absoluteToRelative_impl(const Window* window, const Size& sz) const;
	Point	absoluteToRelative_impl(const Window* window, const Point& pt) const;
	float	absoluteToRelativeX_impl(const Window* window, float x) const;
	float	absoluteToRelativeY_impl(const Window* window, float y) const;


	
	Rect	relativeToAbsolute_impl(const Window* window, const Rect& rect) const;
	Size	relativeToAbsolute_impl(const Window* window, const Size& sz) const;
	Point	relativeToAbsolute_impl(const Window* window, const Point& pt) const;
	float	relativeToAbsoluteX_impl(const Window* window, float x) const;
	float	relativeToAbsoluteY_impl(const Window* window, float y) const;

	Size	getWindowSize_impl(const Window* window) const;


	
	MetricsMode getInheritedMetricsMode(void) const;

    
    
    void    generateAutoRepeatEvent(MouseButton button);

    
    bool    isMouseButtonHollow(MouseButton button);


	
	
	typedef	std::vector<Window*>	ChildList;
	ChildList		d_children;			
    ChildList       d_drawList;         

	
	MetricsMode		d_metricsMode;		
	static Window*	d_captureWindow;	
	Window*			d_oldCapture;		
	Window*			d_parent;			
	const Font*	d_font;				
	bool			d_mouseHollow;		
	bool			d_mouseMoveHollow;
	bool			d_mouseLButtonHollow;	
    bool			d_mouseRButtonHollow;	
	String			d_textOriginal;		
	String			d_text;				
	uint			d_ID;				
	float			d_alpha;			
    URect			d_area;             
	
    Rect*			d_oldArea;          
    Size            d_pixelSize;        
	const Image*	d_mouseCursor;		
	void*			d_userData;			

	typedef std::map<String, String>   UserStringMap;
	UserStringMap  d_userStrings;      

    
    HorizontalAlignment d_horzAlign;    
    VerticalAlignment   d_vertAlign;    
    
	
	UVector2       d_minSize;          
	UVector2       d_maxSize;          
	bool		   d_IsIgnoreMaxSize;  

	
	bool	d_enabled;					
	bool	d_visible;					
	bool	d_active;					
	bool	d_clippedByParent;			
	bool	d_destroyedByParent;		
	bool	d_alwaysOnTop;				
	bool	d_inheritsAlpha;			
	bool	d_restoreOldCapture;		
	bool	d_zOrderingEnabled;			
    bool    d_wantsMultiClicks;         
    bool    d_distCapturedInputs;       
    bool    d_riseOnClick;              

    
    bool    d_autoRepeat;       
    float   d_repeatDelay;      
    float   d_repeatRate;       
    bool    d_repeating;        
    float   d_repeatElapsed;    
    MouseButton d_repeatButton; 

    
    String   d_tooltipText;     
    Tooltip* d_customTip;       
    bool     d_weOwnTip;        
    bool     d_inheritsTipText; 

    
    RenderCache d_renderCache;  
    mutable bool d_needsRedraw;      

    
    String  d_lookName;         

	int		d_windowLayOutNum;	


	
	float	d_xpercent;
	float	d_ypercent;


	float d_stepShowTime;
	float d_currentStepShowTime;
	bool d_enableStepShow;
	bool d_realTimeUpdate;
	bool d_bExtendTooltip;
	bool d_groupWindow;
	bool d_baseTop;
	bool d_specialModal;		
	bool d_specialModalMode;	
	BaseHorizonE d_baseHorizon;	

	DWORD* d_pHyperLinkColor;
	static DWORD ds_dwHyperLinkColorDefault;
	static DWORD ds_dwHyperLinkColorActive;
protected:
	
	static	WindowProperties::AbsoluteHeight	d_absHeightProperty;
	static	WindowProperties::AbsoluteMaxSize	d_absMaxSizeProperty;
	static	WindowProperties::AbsoluteMinSize	d_absMinSizeProperty;
	static	WindowProperties::AbsolutePosition	d_absPositionProperty;
	static	WindowProperties::AbsoluteRect		d_absRectProperty;
	static	WindowProperties::AbsoluteSize		d_absSizeProperty;
	static	WindowProperties::AbsoluteWidth		d_absWidthProperty;
	static	WindowProperties::AbsoluteXPosition	d_absXPosProperty;
	static	WindowProperties::AbsoluteYPosition	d_absYPosProperty;
	static	WindowProperties::Alpha				d_alphaProperty;
	static	WindowProperties::AlwaysOnTop		d_alwaysOnTopProperty;
	static	WindowProperties::ClippedByParent	d_clippedByParentProperty;
	static	WindowProperties::DestroyedByParent	d_destroyedByParentProperty;
	static	WindowProperties::Disabled			d_disabledProperty;
	static	WindowProperties::Font				d_fontProperty;
	static	WindowProperties::Height			d_heightProperty;
	static	WindowProperties::ID				d_IDProperty;
	static	WindowProperties::InheritsAlpha		d_inheritsAlphaProperty;
	static	WindowProperties::MetricsMode		d_metricsModeProperty;
	static	WindowProperties::MouseCursorImage	d_mouseCursorProperty;
	static	WindowProperties::Position			d_positionProperty;
	static	WindowProperties::Rect				d_rectProperty;
	static	WindowProperties::RelativeHeight	d_relHeightProperty;
	static	WindowProperties::RelativeMaxSize	d_relMaxSizeProperty;
	static	WindowProperties::RelativeMinSize	d_relMinSizeProperty;
	static	WindowProperties::RelativePosition	d_relPositionProperty;
	static	WindowProperties::RelativeRect		d_relRectProperty;
	static	WindowProperties::RelativeSize		d_relSizeProperty;
	static	WindowProperties::RelativeWidth		d_relWidthProperty;
	static	WindowProperties::RelativeXPosition	d_relXPosProperty;
	static	WindowProperties::RelativeYPosition	d_relYPosProperty;
	static	WindowProperties::RestoreOldCapture	d_restoreOldCaptureProperty;
	static	WindowProperties::Size				d_sizeProperty;
	static	WindowProperties::MouseHollow		d_mouseHollowProperty;
	static	WindowProperties::MouseMoveHollow		d_mouseMoveHollowProperty;
	static	WindowProperties::MouseLButtonHollow	d_mouseLButtonHollowProperty;
	static	WindowProperties::MouseRButtonHollow	d_mouseRButtonHollowProperty;
	static	WindowProperties::TextOriginal		d_textOriginalProperty;
	static	WindowProperties::Text				d_textProperty;
	static	WindowProperties::Visible			d_visibleProperty;
	static	WindowProperties::Width				d_widthProperty;
	static	WindowProperties::XPosition			d_xPosProperty;
	static	WindowProperties::YPosition			d_yPosProperty;
	static	WindowProperties::ZOrderChangeEnabled	d_zOrderChangeProperty;
    static  WindowProperties::WantsMultiClickEvents d_wantsMultiClicksProperty;
    static  WindowProperties::MouseButtonDownAutoRepeat d_autoRepeatProperty;
    static  WindowProperties::AutoRepeatDelay   d_autoRepeatDelayProperty;
    static  WindowProperties::AutoRepeatRate    d_autoRepeatRateProperty;
    static  WindowProperties::DistributeCapturedInputs d_distInputsProperty;
    static  WindowProperties::CustomTooltipType d_tooltipTypeProperty;
    static  WindowProperties::Tooltip           d_tooltipProperty;
    static  WindowProperties::InheritsTooltipText d_inheritsTooltipProperty;
    static  WindowProperties::RiseOnClick       d_riseOnClickProperty;
    static  WindowProperties::VerticalAlignment   d_vertAlignProperty;
    static  WindowProperties::HorizontalAlignment d_horzAlignProperty;
    static	WindowProperties::UnifiedAreaRect	d_unifiedAreaRectProperty;
    static	WindowProperties::UnifiedPosition	d_unifiedPositionProperty;
    static	WindowProperties::UnifiedXPosition	d_unifiedXPositionProperty;
    static	WindowProperties::UnifiedYPosition	d_unifiedYPositionProperty;
    static	WindowProperties::UnifiedSize		d_unifiedSizeProperty;
    static	WindowProperties::UnifiedWidth		d_unifiedWidthProperty;
    static	WindowProperties::UnifiedHeight		d_unifiedHeightProperty;
    static	WindowProperties::UnifiedMinSize	d_unifiedMinSizeProperty;
    static	WindowProperties::UnifiedMaxSize	d_unifiedMaxSizeProperty;


	static	WindowProperties::ZoomMode			d_zoomModeProperty;
	static	WindowProperties::HookPosition		d_hookPositionProperty;
	static	WindowProperties::HookMode			d_hookModeProperty;

	static	WindowProperties::StepShowTime		d_stepShowTimeProperty;

	static	WindowProperties::NeedRealTimeUpdate d_NeedRealTimeUpdateProperty;
	static  WindowProperties::ExtendTooltip      d_ExtendTooltipProperty;
	static	WindowProperties::GroupWindow 		d_GroupWindowProperty;

	static	WindowProperties::BaseTop 			d_BaseTopProperty;
	static	WindowProperties::BaseHorizon 		d_BaseLeftProperty;
	static	WindowProperties::SpecialModal 		d_SpecialModalProperty;

	static WindowProperties::HyperLinkColorDefault 	 d_HyperLinkColorDefaultProperty;
	static WindowProperties::HyperLinkColorActive 	 d_HyperLinkColorActiveProperty;
	static	WindowProperties::WindowLayOutNum	d_WindowLayOutNumProperty;

	
	
	void	addStandardEvents(void);

	
	virtual void	cleanupChildren(void);

	
	virtual void	addChild_impl(Window* wnd);

	
	virtual void	removeChild_impl(Window* wnd);

	
	virtual void	onZChange_impl(void);


	
	void	addStandardProperties(void);


    
    virtual void moveToFront_impl(bool wasClicked);


    
    void doRiseOnClick(void);

    
    
    void setWindowArea_impl(const UVector2& pos, const UVector2& size, bool topLeftSizing = false, bool fireEvents = true, bool sizeChanged = false);

    
    void addWindowToDrawList(Window& wnd, bool at_back = false);

    
    void removeWindowFromDrawList(const Window& wnd);

	const PropertySet* getPropertyInstance(const String& name) const;

    virtual int writePropertiesXML(OutStream& out_stream) const;
    virtual int writeChildWindowsXML(OutStream& out_stream) const;
	
	
	Window(const Window& wnd) {}
	Window& operator=(const Window& wnd) {return *this;}

	
	const String	d_type;			
	String	d_name;					
	String    d_falagardType;       
	WindowFactory* d_windowFactory; 

	bool			d_isHandleKeyboard;	
	MetricsMode		m_ZoomMode;
	Point			m_ptHookPosition;
	HookMode		m_HookMode;

public:
	WindowFactory* getWindowFactory() {  return d_windowFactory; };

	
	MetricsMode getZoomMode( void ) const { return m_ZoomMode;} ;
	void setZoomMode( MetricsMode mode ){ m_ZoomMode = mode; };

	HookMode    getHookMode( void ) const { return m_HookMode; };
	void		setHookMode( HookMode mode ) { m_HookMode = mode; };

	void		setHookPosition( Point pos ) { m_ptHookPosition = pos ; };
	Point		getHookPosition() const { return m_ptHookPosition; };

	virtual Size	getRenderSize();

	ChildList* getDrawList() {return &d_drawList; };


	virtual bool	isMouseHollow( const Point* pPosition) const	{return d_mouseHollow;}
	virtual bool	isMouseLButtonHollow( const Point* pPosition) const	{return d_mouseLButtonHollow;}
	virtual bool	isMouseRButtonHollow( const Point* pPosition) const	{return d_mouseRButtonHollow;}







	typedef OgreCEGUIRenderer::QuadInfo QuadInfo;

protected:

	
	HyperLink*					d_pCurHyperLink;

	
	bool						d_recalculation;

	
	std::vector< QuadInfo >		d_renderInfo;

	
	int							d_validSize;

	typedef std::map< int, AnimateRuntime* > AnimateRuntimeMap;
	AnimateRuntimeMap			d_animateRuntime;

	typedef std::map< int, FontBlinkRuntime* > FontRuntimeMap;
	FontRuntimeMap				d_fontRuntime;

	typedef std::map< String, HyperLink* > HyperLinkRuntimeMap;
	HyperLinkRuntimeMap			d_hyperlinkRuntime;

public:
	
	virtual bool	doHyperLinkByMouseLeft(const Point& position);

	
	virtual bool	doHyperLinkByMouseRight(const Point& position);

	
	virtual bool	updatePositionChanged();

	
	virtual bool	setCacheRenderInfo(const QuadInfo* pInfo);

	
	virtual bool	getCacheRenderInfo() const;

	
	virtual bool	setAnimateRuntime(const AnimateRuntime* aniRuntime) { return false; }

	
	virtual bool	setFontBlinkRuntime(const FontBlinkRuntime* fontRuntime) { return false; }

	
	virtual bool	setHyperLinkRuntime(int guid, const String name, const Rect hyper_rect) { return false; }

	virtual String  getHyperLinkContex(const Point* position)const { return ""; }

	void			clearAnimateRenderData();

	void			clearFontRenderData();

	void			clearHyperLinkRenderData();
};

} 


#if defined(_MSC_VER)
#	pragma warning(pop)
#endif

#endif	
