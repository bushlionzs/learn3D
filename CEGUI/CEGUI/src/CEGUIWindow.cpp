

#include "CEGUIWindow.h"
#include "CEGUIExceptions.h"
#include "CEGUIWindowManager.h"
#include "CEGUISystem.h"
#include "CEGUIFontManager.h"
#include "CEGUIImagesetManager.h"
#include "CEGUIImageset.h"
#include "CEGUIMouseCursor.h"
#include "elements/CEGUITooltip.h"
#include "falagard/CEGUIFalWidgetLookManager.h"
#include "falagard/CEGUIFalWidgetLookFeel.h"
#include "CEGUIWindowFactoryManager.h"
#include "CEGUIWindowFactory.h"
#include <algorithm>
#include <cmath>
#include <stdio.h>
#include "OgreCEGUITexture.h"
#include "CEGUIHyperLinkManager.h"


namespace CEGUI
{
#define MAX_SIZE 2048

const String Window::EventNamespace("Window");


WindowProperties::AbsoluteHeight	Window::d_absHeightProperty;
WindowProperties::AbsoluteMaxSize	Window::d_absMaxSizeProperty;
WindowProperties::AbsoluteMinSize	Window::d_absMinSizeProperty;
WindowProperties::AbsolutePosition	Window::d_absPositionProperty;
WindowProperties::AbsoluteRect		Window::d_absRectProperty;
WindowProperties::AbsoluteSize		Window::d_absSizeProperty;
WindowProperties::AbsoluteWidth		Window::d_absWidthProperty;
WindowProperties::AbsoluteXPosition	Window::d_absXPosProperty;
WindowProperties::AbsoluteYPosition	Window::d_absYPosProperty;
WindowProperties::Alpha				Window::d_alphaProperty;
WindowProperties::AlwaysOnTop		Window::d_alwaysOnTopProperty;
WindowProperties::ClippedByParent	Window::d_clippedByParentProperty;
WindowProperties::DestroyedByParent	Window::d_destroyedByParentProperty;
WindowProperties::Disabled			Window::d_disabledProperty;
WindowProperties::Font				Window::d_fontProperty;
WindowProperties::Height			Window::d_heightProperty;
WindowProperties::ID				Window::d_IDProperty;
WindowProperties::InheritsAlpha		Window::d_inheritsAlphaProperty;
WindowProperties::MetricsMode		Window::d_metricsModeProperty;
WindowProperties::MouseCursorImage	Window::d_mouseCursorProperty;
WindowProperties::Position			Window::d_positionProperty;
WindowProperties::Rect				Window::d_rectProperty;
WindowProperties::RelativeHeight	Window::d_relHeightProperty;
WindowProperties::RelativeMaxSize	Window::d_relMaxSizeProperty;
WindowProperties::RelativeMinSize	Window::d_relMinSizeProperty;
WindowProperties::RelativePosition	Window::d_relPositionProperty;
WindowProperties::RelativeRect		Window::d_relRectProperty;
WindowProperties::RelativeSize		Window::d_relSizeProperty;
WindowProperties::RelativeWidth		Window::d_relWidthProperty;
WindowProperties::RelativeXPosition	Window::d_relXPosProperty;
WindowProperties::RelativeYPosition	Window::d_relYPosProperty;	
WindowProperties::RestoreOldCapture	Window::d_restoreOldCaptureProperty;
WindowProperties::Size				Window::d_sizeProperty;
WindowProperties::MouseHollow		Window::d_mouseHollowProperty;
WindowProperties::MouseMoveHollow		Window::d_mouseMoveHollowProperty;
WindowProperties::MouseLButtonHollow	Window::d_mouseLButtonHollowProperty;
WindowProperties::MouseRButtonHollow	Window::d_mouseRButtonHollowProperty;
WindowProperties::TextOriginal		Window::d_textOriginalProperty;
WindowProperties::Text				Window::d_textProperty;
WindowProperties::Visible			Window::d_visibleProperty;
WindowProperties::Width				Window::d_widthProperty;
WindowProperties::XPosition			Window::d_xPosProperty;
WindowProperties::YPosition			Window::d_yPosProperty;
WindowProperties::ZOrderChangeEnabled	Window::d_zOrderChangeProperty;
WindowProperties::WantsMultiClickEvents Window::d_wantsMultiClicksProperty;
WindowProperties::MouseButtonDownAutoRepeat Window::d_autoRepeatProperty;
WindowProperties::AutoRepeatDelay   Window::d_autoRepeatDelayProperty;
WindowProperties::AutoRepeatRate    Window::d_autoRepeatRateProperty;
WindowProperties::DistributeCapturedInputs Window::d_distInputsProperty;
WindowProperties::CustomTooltipType Window::d_tooltipTypeProperty;
WindowProperties::Tooltip           Window::d_tooltipProperty;
WindowProperties::InheritsTooltipText Window::d_inheritsTooltipProperty;
WindowProperties::RiseOnClick       Window::d_riseOnClickProperty;
WindowProperties::VerticalAlignment   Window::d_vertAlignProperty;
WindowProperties::HorizontalAlignment Window::d_horzAlignProperty;
WindowProperties::UnifiedAreaRect	Window::d_unifiedAreaRectProperty;
WindowProperties::UnifiedPosition	Window::d_unifiedPositionProperty;
WindowProperties::UnifiedXPosition	Window::d_unifiedXPositionProperty;
WindowProperties::UnifiedYPosition	Window::d_unifiedYPositionProperty;
WindowProperties::UnifiedSize		Window::d_unifiedSizeProperty;
WindowProperties::UnifiedWidth		Window::d_unifiedWidthProperty;
WindowProperties::UnifiedHeight		Window::d_unifiedHeightProperty;
WindowProperties::UnifiedMinSize	Window::d_unifiedMinSizeProperty;
WindowProperties::UnifiedMaxSize	Window::d_unifiedMaxSizeProperty;
WindowProperties::ZoomMode			Window::d_zoomModeProperty;
WindowProperties::HookPosition		Window::d_hookPositionProperty;
WindowProperties::HookMode			Window::d_hookModeProperty;


WindowProperties::StepShowTime		Window::d_stepShowTimeProperty;
WindowProperties::NeedRealTimeUpdate Window::d_NeedRealTimeUpdateProperty;
WindowProperties::ExtendTooltip      Window::d_ExtendTooltipProperty;

WindowProperties::GroupWindow 		Window::d_GroupWindowProperty;
WindowProperties::BaseTop 			Window::d_BaseTopProperty;
WindowProperties::BaseHorizon 		Window::d_BaseLeftProperty;
WindowProperties::SpecialModal 		Window::d_SpecialModalProperty;

WindowProperties::WindowLayOutNum	Window::d_WindowLayOutNumProperty;


Window*	Window::d_captureWindow		= NULL;

//syq:HyperLinkColor
WindowProperties::HyperLinkColorDefault 	Window::d_HyperLinkColorDefaultProperty;
WindowProperties::HyperLinkColorActive 		Window::d_HyperLinkColorActiveProperty;

DWORD Window::ds_dwHyperLinkColorDefault = 0xFF00CCFF;
DWORD Window::ds_dwHyperLinkColorActive = 0xFF00FF00;


const String Window::EventParentSized( (utf8*)"ParentSized" );
const String Window::EventSized( (utf8*)"Sized" );
const String Window::EventMoved( (utf8*)"Moved" );
const String Window::EventTextChanged( (utf8*)"TextChanged" );
const String Window::EventFontChanged( (utf8*)"FontChanged" );
const String Window::EventAlphaChanged( (utf8*)"AlphaChanged" );
const String Window::EventIDChanged( (utf8*)"IDChanged" );
const String Window::EventActivated( (utf8*)"Activated" );
const String Window::EventDeactivated( (utf8*)"Deactivated" );
const String Window::EventShown( (utf8*)"Shown" );
const String Window::EventHidden( (utf8*)"Hidden" );
const String Window::EventParentHidden( (utf8*)"ParentHidden" );
const String Window::EventEnabled( (utf8*)"Enabled" );
const String Window::EventDisabled( (utf8*)"Disabled" );
const String Window::EventMetricsModeChanged( (utf8*)"MetricsChanged" );
const String Window::EventClippedByParentChanged( (utf8*)"ClippingChanged" );
const String Window::EventDestroyedByParentChanged( (utf8*)"DestroyedByParentChanged" );
const String Window::EventInheritsAlphaChanged( (utf8*)"InheritAlphaChanged" );
const String Window::EventAlwaysOnTopChanged( (utf8*)"AlwaysOnTopChanged" );
const String Window::EventInputCaptureGained( (utf8*)"CaptureGained" );
const String Window::EventInputCaptureLost( (utf8*)"CaptureLost" );
const String Window::EventRenderingStarted( (utf8*)"StartRender" );
const String Window::EventRenderingEnded( (utf8*)"EndRender" );
const String Window::EventChildAdded( (utf8*)"AddedChild" );
const String Window::EventChildRemoved( (utf8*)"RemovedChild" );
const String Window::EventDestructionStarted( (utf8*)"DestructStart" );
const String Window::EventZOrderChanged( (utf8*)"ZChanged" );
const String Window::EventDragDropItemEnters("DragDropItemEnters");
const String Window::EventDragDropItemLeaves("DragDropItemLeaves");
const String Window::EventDragDropItemDropped("DragDropItemDropped");
const String Window::EventVerticalAlignmentChanged("VerticalAlignmentChanged");
const String Window::EventHorizontalAlignmentChanged("HorizontalAlignmentChanged");
const String Window::EventMouseEnters( (utf8*)"MouseEnter" );
const String Window::EventMouseLeaves( (utf8*)"MouseLeave" );
const String Window::EventMouseMove( (utf8*)"MouseMove" );
const String Window::EventMouseWheel( (utf8*)"MouseWheel" );
const String Window::EventMouseButtonDown( (utf8*)"MouseButtonDown" );
const String Window::EventMouseButtonUp( (utf8*)"MouseButtonUp" );
const String Window::EventMouseClick( (utf8*)"MouseClick" );
const String Window::EventMouseDoubleClick( (utf8*)"MouseDoubleClick" );
const String Window::EventMouseTripleClick( (utf8*)"MouseTripleClick" );
const String Window::EventKeyDown( (utf8*)"KeyDown" );
const String Window::EventKeyUp( (utf8*)"KeyUp" );
const String Window::EventCharacterKey( (utf8*)"CharacterKey" );
const String Window::EventMouseLClick( (utf8*)"MouseLClick" );
const String Window::EventMouseRClick( (utf8*)"MouseRClick" );
const String Window::EventMouseLButtonDown( (utf8*)"MouseLButtonDown" );
const String Window::EventMouseRButtonDown( (utf8*)"MouseRButtonDown" );

const String Window::EventMouseMultiDown((utf8*)"MouseMultiDown");

Window::Window(const String& type, const String& name) :
	d_type(type),
	d_name(name),
	d_windowFactory(WindowFactoryManager::getSingleton().getFactory(d_type))
{
	
	d_metricsMode	= Relative;
	d_parent		= NULL;
	d_font			= NULL;
	d_ID			= 0;
	d_alpha			= 1.0f;
	d_mouseCursor	= (const Image*)DefaultMouseCursor;
	d_userData		= NULL;
	d_needsRedraw   = true;
	d_mouseHollow	= false;		
	d_mouseMoveHollow = false;		
	d_mouseLButtonHollow = false;
	d_mouseRButtonHollow = false;

	
	d_enabled			= true;
	d_visible			= true;
	d_active			= false;
	d_clippedByParent	= true;
	d_destroyedByParent	= true;
	d_alwaysOnTop		= false;
	d_inheritsAlpha		= true;
	d_restoreOldCapture	= false;
	d_zOrderingEnabled	= true;
    d_wantsMultiClicks  = true;
    d_distCapturedInputs = false;
    d_riseOnClick       = true;

    
    d_repeatButton = NoButton;
    d_autoRepeat   = false;
    d_repeating    = false;
    d_repeatDelay  = 0.3f;
    d_repeatRate   = 0.06f;

    
    d_customTip = 0;
    d_weOwnTip = false;
    d_inheritsTipText = false;
	
	d_isHandleKeyboard = false;

    
    d_minSize = UVector2(cegui_reldim(0), cegui_reldim(0));
    d_maxSize = UVector2(cegui_reldim(1), cegui_reldim(1));
	d_IsIgnoreMaxSize = false;

    
    d_area = URect(cegui_reldim(0), cegui_reldim(0), cegui_reldim(0), cegui_reldim(0));
    d_pixelSize = Size(0, 0);
	d_oldArea = NULL;

    
    d_horzAlign = HA_LEFT;
    d_vertAlign = VA_TOP;

	m_ZoomMode = Inherited;
	m_HookMode = Hook_None;
	m_ptHookPosition = Point( 0,0 );

	d_xpercent = 1.0f;
	d_ypercent = 1.0f;


	d_stepShowTime = 0.0f;
	d_currentStepShowTime = 0.0f;
	d_enableStepShow = false;
	d_realTimeUpdate = false;
	d_bExtendTooltip = false;
	d_groupWindow = false;
	d_baseTop = true;
	d_baseHorizon  = BHE_LEFT;
	d_specialModal = false;
	d_specialModalMode = true;

	d_validSize	= -1;
	d_renderInfo.clear();
	d_animateRuntime.clear();
	d_hyperlinkRuntime.clear();
	d_fontRuntime.clear();

	d_recalculation = true;
	d_pCurHyperLink = NULL;

	d_windowLayOutNum	= 50;

	d_pHyperLinkColor = NULL;
	
	addStandardProperties();
}


Window::~Window(void)
{
    
	if(d_realTimeUpdate)
		System::getSingleton().cancelRealTimeUpdateWindow(this);
	if( d_oldArea )
	{
		delete d_oldArea;
		d_oldArea = NULL;
	}
	if(d_pHyperLinkColor)
	{
		delete [] d_pHyperLinkColor;
		d_pHyperLinkColor = NULL;
	}

	clearFontRenderData();
	clearAnimateRenderData();
	clearHyperLinkRenderData();
}



const String& Window::getType(void) const
{
    return d_falagardType.empty() ? d_type : d_falagardType;
}



bool Window::isDisabled(bool localOnly) const
{
	bool parDisabled = ((d_parent == NULL) || localOnly) ? false : d_parent->isDisabled();

	return (!d_enabled) || parDisabled;
}



bool Window::isVisible(bool localOnly) const
{
	bool parVisible = ((d_parent == NULL) || localOnly) ? true : d_parent->isVisible();

	return d_visible && parVisible;
}



bool Window::isActive(void) const
{
	bool parActive = (d_parent == NULL) ? true : d_parent->isActive();

	return d_active && parActive;
}



bool Window::isChild(const String& name) const
{
	uint child_count = getChildCount();

	for (uint i = 0; i < child_count; ++i)
	{
		if (d_children[i]->getName() == name)
		{
			return true;
		}

	}

	return false;
}


bool Window::isChild(uint ID) const
{
	uint child_count = getChildCount();

	for (uint i = 0; i < child_count; ++i)
	{
		if (d_children[i]->getID() == ID)
		{
			return true;
		}

	}

	return false;
}



bool Window::isChild(const Window* window) const
{
	uint child_count = getChildCount();

	for (uint i = 0; i < child_count; ++i)
	{
		if (d_children[i] == window)
		{
			return true;
		}

	}

	return false;
}



Window* Window::getChild(const String& name) const
{
	uint child_count = getChildCount();

	for (uint i = 0; i < child_count; ++i)
	{
		if (d_children[i]->getName() == name)
		{
			return d_children[i];
		}

	}

	throw UnknownObjectException((utf8*)"Window::getChild - The Window object named '" + name +"' is not attached to Window '" + d_name + "'.");
}



Window* Window::getChild(uint ID) const
{
	uint child_count = getChildCount();

	for (uint i = 0; i < child_count; ++i)
	{
		if (d_children[i]->getID() == ID)
		{
			return d_children[i];
		}

	}

	
	char strbuf[16];
	sprintf(strbuf, "%X", ID);
	throw UnknownObjectException("Window::getChild - The Window with ID: '" + std::string(strbuf) + "' is not attached to Window '" + d_name + "'.");
}



Window* Window::getActiveChild(void)
{
	return const_cast<Window*>(static_cast<const Window*>(this)->getActiveChild());
}



const Window* Window::getActiveChild(void) const
{
	
	if (!isActive())
	{
		return NULL;
	}

	uint pos = getChildCount();

	while (pos-- > 0)
	{
		
		
		if (d_drawList[pos]->d_active)
			return d_drawList[pos]->getActiveChild();
	}

	
	return this;
}



bool Window::isAncestor(const String& name) const
{
	
	if (d_parent == NULL)
	{
		return false;
	}

	
	if (d_parent->getName() == name)
	{
		return true;
	}

	
	return d_parent->isAncestor(name);
}



bool Window::isAncestor(uint ID) const
{
	
	if (d_parent == NULL)
	{
		return false;
	}

	
	if (d_parent->getID() == ID)
	{
		return true;
	}

	
	return d_parent->isAncestor(ID);
}



bool Window::isAncestor(const Window* window) const
{
	
	if (d_parent == NULL)
	{
		return false;
	}

	
	if (d_parent == window)
	{
		return true;
	}

	
	return d_parent->isAncestor(window);
}



const Font* Window::getFont(bool useDefault) const
{
	if (d_font == NULL)
	{
		return useDefault ? System::getSingleton().getDefaultFont() : 0;
	}

	return d_font;
}



float Window::getEffectiveAlpha(void) const
{
	if ((d_parent == NULL) || (!inheritsAlpha()))
	{
		return d_alpha;
	}

	return d_alpha * d_parent->getEffectiveAlpha();
}



Rect Window::getRect(void) const
{
    return (getMetricsMode() == Relative) ? getRelativeRect() : getAbsoluteRect();
}



Rect Window::getPixelRect(void) const
{
	
	if (isClippedByParent() && (d_parent != NULL))
	{
		return getUnclippedPixelRect().getIntersection(d_parent->getInnerRect());
	}
	
	else
	{
		return getUnclippedPixelRect().getIntersection(System::getSingleton().getRenderer()->getRect());
	}

}



Rect Window::getInnerRect(void) const
{
	
	if (isClippedByParent() && (d_parent != NULL))
	{
		return getUnclippedInnerRect().getIntersection(d_parent->getInnerRect());
	}
	
	else
	{
		return getUnclippedInnerRect().getIntersection(System::getSingleton().getRenderer()->getRect());
	}

}



Rect Window::getUnclippedPixelRect(void) const
{
	if (getMetricsMode() == Relative)
	{
		return windowToScreen(Rect(0, 0, 1, 1));
	}
	else
	{
		return windowToScreen(Rect(0, 0, getAbsoluteWidth(), getAbsoluteHeight()));
	}
}



Rect Window::getUnclippedInnerRect(void) const
{
	return getUnclippedPixelRect();
}



bool Window::isHit(const Point& position) const
{
	
	if (isDisabled())
	{
		return false;
	}

	Rect clipped_area(getPixelRect());

	if (clipped_area.getWidth() == 0)
	{
		return false;
	}

	return clipped_area.isPointInRect(position);
}


Window* Window::getChildAtPosition(const Point& position, int nEventType  ) const
{
	ChildList::const_reverse_iterator	child, end;

	end = d_drawList.rend();

	for (child = d_drawList.rbegin(); child != end; ++child)
	{
		if ((*child)->isVisible())
		{
			
			Window* wnd = (*child)->getChildAtPosition(position, nEventType );

			
			if (wnd != NULL)
			{
				return wnd;
			}
			
			else
			{

				
				if( (*child)->isHit(position) )
				{
					switch( nEventType )
					{
					case 0:		
						if( (*child)->getMouseHollow() )
							continue;
						break;

					case 1:		
						if( (*child)->getMouseHollow() )
							continue;
						if( (*child)->isMouseLButtonHollow(&position) ) 
							continue;
						break;

					case 2:		
						if( (*child)->getMouseHollow() )
							continue;
						if( (*child)->isMouseRButtonHollow(&position) )  
							continue;
						break;

					case 3:		
						if( ( *child )->getMouseMoveHollow()  )
						{
							continue;
						}
					default:
						break;
					}
					return (*child);
				}
				
			}

		}

	}

	
	return NULL;
}



MetricsMode Window::getMetricsMode(void) const
{
	if (d_metricsMode == Inherited)
	{
		return getInheritedMetricsMode();
	}

	return d_metricsMode;
}



float Window::getXPosition(void) const
{
    return (getMetricsMode() == Relative) ? getRelativeXPosition() : getAbsoluteXPosition();
}



float Window::getYPosition(void) const
{
    return (getMetricsMode() == Relative) ? getRelativeYPosition() : getAbsoluteYPosition();
}



Point Window::getPosition(void) const
{
    return (getMetricsMode() == Relative) ? getRelativePosition() : getAbsolutePosition();
}



float Window::getWidth(void) const
{
    return (getMetricsMode() == Relative) ? getRelativeWidth() : getAbsoluteWidth();
}



float Window::getHeight(void) const
{
    return (getMetricsMode() == Relative) ? getRelativeHeight() : getAbsoluteHeight();
}



Size Window::getSize(void) const
{
    return (getMetricsMode() == Relative) ? getRelativeSize() : getAbsoluteSize();
}



void Window::setAlwaysOnTop(bool setting)
{
	
	if (isAlwaysOnTop() != setting)
	{
		d_alwaysOnTop = setting;

		
		if (d_parent != NULL)
		{
			Window* org_parent = d_parent;

			org_parent->removeChild_impl(this);
			org_parent->addChild_impl(this);

			onZChange_impl();
		}

		WindowEventArgs args(this);
		onAlwaysOnTopChanged(args);
	}

}


void Window::setWindowLayOutNum(int laynum)
{
	d_windowLayOutNum	= laynum;
}



void Window::setEnabled(bool setting)
{
	
	if (d_enabled != setting)
	{
		d_enabled = setting;
        WindowEventArgs args(this);

        if (d_enabled)
        {
            
            
            if ((d_parent && !d_parent->isDisabled()) || !d_parent)
                onEnabled(args);
        }
        else
        {
            onDisabled(args);
        }
    }
}



void Window::setVisible(bool setting)
{
	UI_TRY
	
	if (d_visible != setting)
	{
		d_visible = setting;
        WindowEventArgs args(this);
		d_visible ? onShown(args) : onHidden(args);
	}
	UI_CATCH( "setVisible --Window::setVisible" )
}



void Window::activate(void)
{
	
	
	
	if ((d_captureWindow != NULL) && (d_captureWindow != this))
	{
		Window* tmpCapture = d_captureWindow;
		d_captureWindow = NULL;

		WindowEventArgs args(NULL);
		tmpCapture->onCaptureLost(args);
	}

	moveToFront();
}



void Window::deactivate(void)
{
	ActivationEventArgs args(this);
	args.otherWindow = NULL;
	onDeactivated(args);
}



void Window::setClippedByParent(bool setting)
{
	
	if (d_clippedByParent != setting)
	{
		d_clippedByParent = setting;
        WindowEventArgs args(this);
		onClippingChanged(args);
	}

}


void Window::setMouseHollow(bool mousehollow)
{
	d_mouseHollow = mousehollow;
	d_mouseLButtonHollow = d_mouseRButtonHollow = d_mouseHollow;
}
void	Window::setMouseMoveHollow(bool mousehollow)
{
	d_mouseMoveHollow = mousehollow;
}


void Window::setMouseLButtonHollow(bool mouselbuttonhollow)
{
	if(!d_mouseHollow)
		d_mouseLButtonHollow = mouselbuttonhollow;
	else
		d_mouseLButtonHollow = d_mouseHollow;
}


void Window::setMouseRButtonHollow(bool mouserbuttonhollow)
{
	if(!d_mouseHollow)
		d_mouseRButtonHollow = mouserbuttonhollow;
	else
		d_mouseRButtonHollow = d_mouseHollow;
}


void Window::setTextOriginal(const String& text)
{
	d_textOriginal = text;
}

void Window::setText(const String& text)
{
	d_text = text;
    WindowEventArgs args(this);
	onTextChanged(args);
}



void Window::setWidth(float width)
{
	setSize(Size(width, getHeight()));
}



void Window::setHeight(float height)
{
	setSize(Size(getWidth(), height));
}



void Window::setSize(const Size& size)
{
	setSize(getMetricsMode(), size);
}



void Window::setXPosition(float x)
{
	setPosition(Point(x, getYPosition()));
}



void Window::setYPosition(float y)
{
	setPosition(Point(getXPosition(), y));
}



void Window::setPosition(const Point& position)
{
	setPosition(getMetricsMode(), position);
}



void Window::setAreaRect(const Rect& area)
{
	setRect(getMetricsMode(), area);
}



void Window::setFont(const Font* font)
{
	d_font = font;
    WindowEventArgs args(this);
	onFontChanged(args);
}



void Window::setFont(const String& name)
{
	if (name.empty())
	{
		setFont(NULL);
	}
	else
	{
		setFont(FontManager::getSingleton().getFont(name));
	}
	
}



void Window::addChildWindow(const String& name)
{
	addChildWindow(WindowManager::getSingleton().getWindow(name));
}



void Window::addChildWindow(Window* window)
{
	addChild_impl(window);
    WindowEventArgs args(window);
	onChildAdded(args);
	window->onZChange_impl();
}



void Window::removeChildWindow(const String& name)
{
	uint child_count = getChildCount();

	for (uint i = 0; i < child_count; ++i)
	{
		if (d_children[i]->getName() == name)
		{
			removeChildWindow(d_children[i]);
			return;
		}

	}

}



void Window::removeChildWindow(Window* window)
{
	removeChild_impl(window);
    WindowEventArgs args(window);
	onChildRemoved(args);
	window->onZChange_impl();
}



void Window::removeChildWindow(uint ID)
{
	uint child_count = getChildCount();

	for (uint i = 0; i < child_count; ++i)
	{
		if (d_children[i]->getID() == ID)
		{
			removeChildWindow(d_children[i]);
			return;
		}

	}

}



void Window::moveToFront()
{
    moveToFront_impl(false);
}



void Window::moveToFront_impl(bool wasClicked)
{
	
	if (d_parent == NULL)
	{
		
		if (!isActive())
		{
            ActivationEventArgs args(this);
			args.otherWindow = NULL;
			onActivated(args);
		}

		return;
	}

	
    wasClicked ? d_parent->doRiseOnClick() : d_parent->moveToFront_impl(false);

    
    Window* activeWnd = getActiveSibling();

    
    if (activeWnd != this)
    {
        ActivationEventArgs args(this);

        
        if (activeWnd)
        {
            args.window = activeWnd;
            args.otherWindow = this;
            args.handled = false;
            activeWnd->onDeactivated(args);
        }

        
		args.otherWindow = activeWnd;
        onActivated(args);
    }

    
    if (d_zOrderingEnabled)
    {
        
        d_parent->removeWindowFromDrawList(*this);
        
        
        d_parent->addWindowToDrawList(*this);
        
        onZChange_impl();
    }
}



void Window::moveToBack()
{
	
	if (isActive())
	{
        ActivationEventArgs args(this);
		args.otherWindow = NULL;
		onDeactivated(args);
	}

    
    if (d_parent)
    {
        if (d_zOrderingEnabled)
        {
            
            d_parent->removeWindowFromDrawList(*this);
            
            
            d_parent->addWindowToDrawList(*this, true);
            
            onZChange_impl();
        }

        d_parent->moveToBack();
    }
}



bool Window::captureInput(void)
{
	
	if (!isActive()) {
		return false;
	}

	Window* current_capture = d_captureWindow;
	d_captureWindow = this;
    WindowEventArgs args(this);

	
	if ((current_capture != NULL) && (current_capture != this) && (!d_restoreOldCapture)) {
		current_capture->onCaptureLost(args);
	}

	if (d_restoreOldCapture) {
		d_oldCapture = current_capture;
	}

	onCaptureGained(args);

	return true;
}



void Window::releaseInput(void)
{
	
	if (!isCapturedByThis()) {
		return;
	}

	
	if (d_restoreOldCapture) {
		d_captureWindow = d_oldCapture;

		
		if (d_oldCapture != NULL) {
			d_oldCapture = NULL;
			d_captureWindow->moveToFront();
		}

	}
	else {
		d_captureWindow = NULL;
	}

    WindowEventArgs args(this);
	onCaptureLost(args);
}



void Window::setRestoreCapture(bool setting)
{
	d_restoreOldCapture = setting;

	uint child_count = getChildCount();

	for (uint i = 0; i < child_count; ++i)
	{
		d_children[i]->setRestoreCapture(setting);
	}

}



void Window::setAlpha(float alpha)
{
	d_alpha = alpha;
	WindowEventArgs args(this);
	onAlphaChanged(args);
}



void Window::setInheritsAlpha(bool setting)
{
	if (d_inheritsAlpha != setting)
	{
		
		float oldAlpha = getEffectiveAlpha();

		
		d_inheritsAlpha = setting;

		WindowEventArgs args(this);
		onInheritsAlphaChanged(args);

		
		if (oldAlpha != getEffectiveAlpha())
		{
			args.handled = false;
			onAlphaChanged(args);
		}

	}

}



void Window::requestRedraw(void) const
{
    d_needsRedraw = true;
	System::getSingleton().signalRedraw();
}



float Window::absoluteToRelativeX(float val) const
{
	return absoluteToRelativeX_impl(this, val);
}



float Window::absoluteToRelativeY(float val) const
{
	return absoluteToRelativeY_impl(this, val);
}



Point Window::absoluteToRelative(const Point& pt) const
{
	return absoluteToRelative_impl(this, pt);
}



Size Window::absoluteToRelative(const Size& sze) const
{
	return absoluteToRelative_impl(this, sze);
}



Rect Window::absoluteToRelative(const Rect& rect) const
{
	return absoluteToRelative_impl(this, rect);
}



float Window::relativeToAbsoluteX(float val) const
{
	return relativeToAbsoluteX_impl(this, val);
}



float Window::relativeToAbsoluteY(float val) const
{
	return relativeToAbsoluteY_impl(this, val);
}



Point Window::relativeToAbsolute(const Point& pt) const
{
	return relativeToAbsolute_impl(this, pt);
}



Size Window::relativeToAbsolute(const Size& sze) const
{
	return relativeToAbsolute_impl(this, sze);
}



Rect Window::relativeToAbsolute(const Rect& rect) const
{
		return relativeToAbsolute_impl(this, rect);
}



float Window::windowToScreenX(float x) const
{
    float baseX = 0;

    if (d_parent)
    {
        baseX = d_parent->windowToScreenX(baseX);
    }

    switch(d_horzAlign)
    {
        case HA_CENTRE:
            baseX += getAbsoluteXPosition() + ((getParentWidth() - getAbsoluteWidth()) * 0.5f);
            break;
        case HA_RIGHT:
            baseX += getAbsoluteXPosition() + (getParentWidth() - getAbsoluteWidth());
            break;
        default:
            baseX += getAbsoluteXPosition();
            break;
    }

	if (getMetricsMode() == Relative)
	{
		return baseX + relativeToAbsoluteX(x);
	}
	else
	{
		return baseX + x;
	}

}



float Window::windowToScreenY(float y) const
{
    float baseY = 0;

    if (d_parent)
    {
        baseY = d_parent->windowToScreenY(baseY);
    }

    switch(d_vertAlign)
    {
        case VA_CENTRE:
            baseY += getAbsoluteYPosition() + ((getParentHeight() - getAbsoluteHeight()) * 0.5f);
            break;
        case VA_BOTTOM:
            baseY += getAbsoluteYPosition() + (getParentHeight() - getAbsoluteHeight());
            break;
        default:
            baseY += getAbsoluteYPosition();
            break;
    }

	if (getMetricsMode() == Relative)
	{
		return baseY + relativeToAbsoluteY(y);
	}
	else
	{
		return baseY + y;
	}

}



Point Window::windowToScreen(const Point& pt) const
{
	Point base(0, 0);
    
    if (d_parent)
    {
        base = d_parent->windowToScreen(base);
    }

    switch(d_horzAlign)
    {
        case HA_CENTRE:
            base.d_x += getAbsoluteXPosition() + ((getParentWidth() - getAbsoluteWidth()) * 0.5f);
            break;
        case HA_RIGHT:
            base.d_x += getAbsoluteXPosition() + (getParentWidth() - getAbsoluteWidth());
            break;
        default:
            base.d_x += getAbsoluteXPosition();
            break;
    }

    switch(d_vertAlign)
    {
        case VA_CENTRE:
            base.d_y += getAbsoluteYPosition() + ((getParentHeight() - getAbsoluteHeight()) * 0.5f);
            break;
        case VA_BOTTOM:
            base.d_y += getAbsoluteYPosition() + (getParentHeight() - getAbsoluteHeight());
            break;
        default:
            base.d_y += getAbsoluteYPosition();
            break;
    }

	if (getMetricsMode() == Relative)
	{
		return base + relativeToAbsolute(pt);
	}
	else
	{
		return base + pt;
	}

}



Size Window::windowToScreen(const Size& sze) const
{
	if (getMetricsMode() == Relative)
	{
		return Size(sze.d_width * getAbsoluteWidth(), sze.d_height * getAbsoluteHeight());
	}
	else
	{
		return sze;
	}

}



Rect Window::windowToScreen(const Rect& rect) const
{
    Point base(0, 0);

    if (d_parent)
    {
        base = d_parent->windowToScreen(base);
    }

    switch(d_horzAlign)
    {
        case HA_CENTRE:
            base.d_x += getAbsoluteXPosition() + ((getParentWidth() - getAbsoluteWidth()) * 0.5f);
            break;
        case HA_RIGHT:
            base.d_x += getAbsoluteXPosition() + (getParentWidth() - getAbsoluteWidth());
            break;
        default:
            base.d_x += getAbsoluteXPosition();
            break;
    }

    switch(d_vertAlign)
    {
        case VA_CENTRE:
            base.d_y += getAbsoluteYPosition() + ((getParentHeight() - getAbsoluteHeight()) * 0.5f);
            break;
        case VA_BOTTOM:
            base.d_y += getAbsoluteYPosition() + (getParentHeight() - getAbsoluteHeight());
            break;
        default:
            base.d_y += getAbsoluteYPosition();
            break;
    }

	if (getMetricsMode() == Relative)
	{
		return relativeToAbsolute(rect).offset(base);
	}
	else
	{
		Rect tmp(rect);
		return tmp.offset(base);
	}

}



float Window::screenToWindowX(float x) const
{
	x -= windowToScreenX(0);

	if (getMetricsMode() == Relative)
	{
		x /= getAbsoluteWidth();
	}

	return x;
}



float Window::screenToWindowY(float y) const
{
	y -= windowToScreenY(0);

	if (getMetricsMode() == Relative)
	{
		y /= getAbsoluteHeight();
	}

	return y;
}



Point Window::screenToWindow(const Point& pt) const
{
	Point tmp(pt);

	tmp.d_x -= windowToScreenX(0);
	tmp.d_y -= windowToScreenY(0);

	if (getMetricsMode() == Relative)
	{
		tmp.d_x /= getAbsoluteWidth();
		tmp.d_y /= getAbsoluteHeight();
	}

	return tmp;
}



Size Window::screenToWindow(const Size& sze) const
{
	Size tmp(sze);

	if (getMetricsMode() == Relative)
	{
		tmp.d_width		/= getAbsoluteWidth();
		tmp.d_height	/= getAbsoluteHeight();
	}

	return tmp;
}



Rect Window::screenToWindow(const Rect& rect) const
{
	Rect tmp(rect);

	tmp.d_left		-= windowToScreenX(0);
	tmp.d_top		-= windowToScreenY(0);
	tmp.d_right		-= windowToScreenX(0);
	tmp.d_bottom	-= windowToScreenY(0);

	if (getMetricsMode() == Relative)
	{
		tmp.d_left		/= getAbsoluteWidth();
		tmp.d_top		/= getAbsoluteHeight();
		tmp.d_right		/= getAbsoluteWidth();
		tmp.d_bottom	/= getAbsoluteHeight();
	}

	return tmp;
}



float Window::unifiedToRelativeX(const UDim& val) const
{
    return val.asRelative(d_pixelSize.d_width);
}


float Window::unifiedToRelativeY(const UDim& val) const
{
    return val.asRelative(d_pixelSize.d_height);
}


Vector2 Window::unifiedToRelative(const UVector2& val) const
{
    return val.asRelative(d_pixelSize);
}


Rect Window::unifiedToRelative(const URect& val) const
{
    return val.asRelative(d_pixelSize);
}


float Window::unifiedToAbsoluteX(const UDim& val) const
{
    return val.asAbsolute(d_pixelSize.d_width);
}


float Window::unifiedToAbsoluteY(const UDim& val) const
{
    return val.asAbsolute(d_pixelSize.d_height);
}


Vector2 Window::unifiedToAbsolute(const UVector2& val) const
{
    return val.asAbsolute(d_pixelSize);
}


Rect Window::unifiedToAbsolute(const URect& val) const
{
    return val.asAbsolute(d_pixelSize);
}


float Window::windowToScreenX(const UDim& x) const
{
    float baseX = d_parent ?  d_parent->windowToScreenX(0) + getAbsoluteXPosition() : getAbsoluteXPosition();

    switch(d_horzAlign)
    {
        case HA_CENTRE:
            baseX += (getParentWidth() - d_pixelSize.d_width) * 0.5f;
            break;
        case HA_RIGHT:
            baseX += getParentWidth() - d_pixelSize.d_width;
            break;
        default:
            break;
    }

    return baseX + x.asAbsolute(d_pixelSize.d_width);
}


float Window::windowToScreenY(const UDim& y) const
{
    float baseY = d_parent ?  d_parent->windowToScreenY(0) + getAbsoluteYPosition() : getAbsoluteYPosition();

    switch(d_vertAlign)
    {
        case VA_CENTRE:
            baseY += (getParentHeight() - d_pixelSize.d_height) * 0.5f;
            break;
        case VA_BOTTOM:
            baseY += getParentHeight() - d_pixelSize.d_height;
            break;
        default:
            break;
    }

    return baseY + y.asAbsolute(d_pixelSize.d_height);
}


Vector2 Window::windowToScreen(const UVector2& vec) const
{
    Vector2 base = d_parent ? d_parent->windowToScreen(base) + getAbsolutePosition() : getAbsolutePosition();

    switch(d_horzAlign)
    {
        case HA_CENTRE:
            base.d_x += (getParentWidth() - d_pixelSize.d_width) * 0.5f;
            break;
        case HA_RIGHT:
            base.d_x += getParentWidth() - d_pixelSize.d_width;
            break;
        default:
            break;
    }

    switch(d_vertAlign)
    {
        case VA_CENTRE:
            base.d_y += (getParentHeight() - d_pixelSize.d_height) * 0.5f;
            break;
        case VA_BOTTOM:
            base.d_y += getParentHeight() - d_pixelSize.d_height;
            break;
        default:
            break;
    }

    return base + vec.asAbsolute(d_pixelSize);
}


Rect Window::windowToScreen(const URect& rect) const
{
    Vector2 base = d_parent ? d_parent->windowToScreen(base) + getAbsolutePosition() : getAbsolutePosition();

    switch(d_horzAlign)
    {
        case HA_CENTRE:
            base.d_x += (getParentWidth() - d_pixelSize.d_width) * 0.5f;
            break;
        case HA_RIGHT:
            base.d_x += getParentWidth() - d_pixelSize.d_width;
            break;
        default:
            break;
    }

    switch(d_vertAlign)
    {
        case VA_CENTRE:
            base.d_y += (getParentHeight() - d_pixelSize.d_height) * 0.5f;
            break;
        case VA_BOTTOM:
            base.d_y += getParentHeight() - d_pixelSize.d_height;
            break;
        default:
            break;
    }

    Rect tmp(rect.asAbsolute(d_pixelSize));
    return tmp.offset(base);
}


float Window::screenToWindowX(const UDim& x) const
{
    return screenToWindowX(x.asAbsolute(System::getSingleton().getRenderer()->getWidth()));
}


float Window::screenToWindowY(const UDim& y) const
{
    return screenToWindowY(y.asAbsolute(System::getSingleton().getRenderer()->getHeight()));
}


Vector2 Window::screenToWindow(const UVector2& vec) const
{
    return screenToWindow(vec.asAbsolute(System::getSingleton().getRenderer()->getSize()));
}


Rect Window::screenToWindow(const URect& rect) const
{
    return screenToWindow(rect.asAbsolute(System::getSingleton().getRenderer()->getSize()));
}


void Window::renderPrepare(void)
{
	
	if (!isVisible()) {
		return;
	}

	
	prepareBigchar();

	
	uint child_count = getChildCount();

	for (uint i = 0; i < child_count; ++i)
	{
		d_drawList[i]->renderPrepare();
	}
}


void Window::prepareBigchar(void)
{
	if(!d_text.empty() && getFont())
	{
		((Font*)getFont())->prepareString(d_text);
	}
}


void Window::render(void)
{
	
	if (!isVisible()) {
		return;
	}

	
	WindowEventArgs args(this);
	onRenderingStarted(args);

	
	Renderer* renderer = System::getSingleton().getRenderer();
	drawSelf(renderer->getCurrentZ());
	renderer->advanceZValue();

	
	uint child_count = getChildCount();

	for (uint i = 0; i < child_count; ++i)
	{
		d_drawList[i]->render();
	}

	
	onRenderingEnded(args);
}



void Window::drawSelf(float z)
{
    if (d_needsRedraw)
    {
        
        d_renderCache.clearCachedImagery();
        
        populateRenderCache();
        
        d_needsRedraw = false;
    }

    
    if (d_renderCache.hasCachedImagery())
    {
		Point absPos(getUnclippedPixelRect().getPosition());
        
        Rect clipper(getPixelRect());
        
        if (clipper.getWidth())
        {
            
			UI_TRY

			d_renderCache.render(absPos, z, clipper, d_xpercent, d_ypercent);

			UI_CATCH( "Window Type:" + d_type + " ---Window Name:" + d_name + " ---Window::drawSelf - failed render." )
        }
    }
}



void Window::setParent(Window* parent)
{
	d_parent = parent;
}



const int Window::getWindowLayOutNum(void) const
{
	
		return d_windowLayOutNum;
	
	
}


float Window::getParentWidth(void) const
{
	if (d_parent == NULL)
	{
		return System::getSingleton().getRenderer()->getWidth();
	}

	return d_parent->getAbsoluteWidth();
}



float Window::getParentHeight(void) const
{
	if (d_parent == NULL)
	{
		return System::getSingleton().getRenderer()->getHeight();
	}

	return d_parent->getAbsoluteHeight();
}



Size Window::getParentSize(void) const
{
	return getWindowSize_impl(d_parent);
}


void Window::cleanupChildren(void)
{
	while(getChildCount() != 0)
	{
		Window* wnd = d_children[0];

		
		removeChildWindow(wnd);

		
		if (wnd->isDestroyedByParent())
		{
			WindowManager::getSingleton().destroyWindow(wnd);
		}

	}

}



void Window::addChild_impl(Window* wnd)
{
	
	if (wnd->getParent() != NULL)
		wnd->getParent()->removeChildWindow(wnd);

    addWindowToDrawList(*wnd);

    
    d_children.push_back(wnd);

	
	wnd->setParent(this);

	
    WindowEventArgs args(this);
	wnd->onParentSized(args);
}



void Window::removeChild_impl(Window* wnd)
{
    
    removeWindowFromDrawList(*wnd);

    
    if (!d_children.empty())
    {
        
        ChildList::iterator	position = std::find(d_children.begin(), d_children.end(), wnd);

        
        if (position != d_children.end())
        {
            
            d_children.erase(position);
            
            wnd->setParent(0);
        }
    }
}



void Window::onZChange_impl(void)
{
	if (d_parent == NULL)
	{
        WindowEventArgs args(this);
		onZChanged(args);
	}
	else
	{
		uint child_count = d_parent->getChildCount();

		for (uint i = 0; i < child_count; ++i)
		{
            WindowEventArgs args(d_parent->d_children[i]);
			d_parent->d_children[i]->onZChanged(args);
		}

	}

}



Rect Window::absoluteToRelative_impl(const Window* window, const Rect& rect) const
{
	
	Size sz = getWindowSize_impl(window);

	Rect tmp;

	if (sz.d_width)
	{
		tmp.d_left	= PixelAligned(rect.d_left) / sz.d_width;
		tmp.d_right = PixelAligned(rect.d_right) / sz.d_width;
	}
	else
	{
		tmp.d_left = tmp.d_right = 0;
	}

	if (sz.d_height)
	{
		tmp.d_top		= PixelAligned(rect.d_top) / sz.d_height;
		tmp.d_bottom	= PixelAligned(rect.d_bottom) / sz.d_height;
	}
	else
	{
		tmp.d_top = tmp.d_bottom= 0;
	}

	return tmp;
}



Size Window::absoluteToRelative_impl(const Window* window, const Size& sz) const
{
	
	Size wndsz = getWindowSize_impl(window);

	Size tmp;

	if (wndsz.d_width)
	{
		tmp.d_width = PixelAligned(sz.d_width) / wndsz.d_width;
	}
	else
	{
		tmp.d_width = 0;
	}

	if (wndsz.d_height)
	{
		tmp.d_height = PixelAligned(sz.d_height) / wndsz.d_height;
	}
	else
	{
		tmp.d_height = 0;
	}

	return tmp;
}



Point Window::absoluteToRelative_impl(const Window* window, const Point& pt) const
{
	
	Size sz = getWindowSize_impl(window);

	Point tmp;

	if (sz.d_width)
	{
		tmp.d_x = PixelAligned(pt.d_x) / sz.d_width;
	}
	else
	{
		tmp.d_x = 0;
	}

	if (sz.d_height)
	{
		tmp.d_y = PixelAligned(pt.d_y) / sz.d_height;
	}
	else
	{
		tmp.d_y = 0;
	}

	return tmp;
}



float Window::absoluteToRelativeX_impl(const Window* window, float x) const
{
	
	Size sz = getWindowSize_impl(window);

	if (sz.d_width)
	{
		return PixelAligned(x) / sz.d_width;
	}
	else
	{
		return 0;
	}
}



float Window::absoluteToRelativeY_impl(const Window* window, float y) const
{
	
	Size sz = getWindowSize_impl(window);

	if (sz.d_height)
	{
		return PixelAligned(y) / sz.d_height;
	}
	else
	{
		return 0;
	}
}



Rect Window::relativeToAbsolute_impl(const Window* window, const Rect& rect) const
{
	
	Size sz = getWindowSize_impl(window);

	return Rect(
		PixelAligned(rect.d_left * sz.d_width),
		PixelAligned(rect.d_top * sz.d_height),
		PixelAligned(rect.d_right * sz.d_width),
		PixelAligned(rect.d_bottom * sz.d_height)
		);
}



Size Window::relativeToAbsolute_impl(const Window* window, const Size& sz) const
{
	
	Size wndsz = getWindowSize_impl(window);

	return Size(
		PixelAligned(sz.d_width * wndsz.d_width),
		PixelAligned(sz.d_height * wndsz.d_height)
		);
}



Point Window::relativeToAbsolute_impl(const Window* window, const Point& pt) const
{
	
	Size sz = getWindowSize_impl(window);

	return Point(
		PixelAligned(pt.d_x * sz.d_width),
		PixelAligned(pt.d_y * sz.d_height)
		);
}



float Window::relativeToAbsoluteX_impl(const Window* window, float x) const
{
	
	Size sz = getWindowSize_impl(window);

	return PixelAligned(x * sz.d_width);
}



float Window::relativeToAbsoluteY_impl(const Window* window, float y) const
{
	
	Size sz = getWindowSize_impl(window);

	return PixelAligned(y * sz.d_height);
}



Size Window::getWindowSize_impl(const Window* window) const
{
	if (window == NULL)
	{
		return System::getSingleton().getRenderer()->getSize();
	}
	else
	{
        return window->getAbsoluteSize();
	}

}



Size Window::getMaximumSize(void) const
{
	if (getMetricsMode() == Absolute)
	{
        return d_maxSize.asAbsolute(System::getSingleton().getRenderer()->getSize()).asSize();
	}
	else
	{
        return d_maxSize.asRelative(System::getSingleton().getRenderer()->getSize()).asSize();
    }

}



Size Window::getMinimumSize(void) const
{
	if (getMetricsMode() == Absolute)
    {
        return d_minSize.asAbsolute(System::getSingleton().getRenderer()->getSize()).asSize();
    }
    else
    {
        return d_minSize.asRelative(System::getSingleton().getRenderer()->getSize()).asSize();
    }

}



void Window::setMinimumSize(const Size& sz)
{
    UVector2 usz;
    
    if (getMetricsMode() == Absolute)
    {
        usz.d_x = cegui_absdim(PixelAligned(sz.d_width));
        usz.d_y = cegui_absdim(PixelAligned(sz.d_height));
    }
    else
    {
        usz.d_x = cegui_reldim(sz.d_width);
        usz.d_y = cegui_reldim(sz.d_height);
    }

    setWindowMinSize(usz);
}



void Window::setMaximumSize(const Size& sz)
{
    UVector2 usz;

    if (getMetricsMode() == Absolute)
    {
        usz.d_x = cegui_absdim(PixelAligned(sz.d_width));
        usz.d_y = cegui_absdim(PixelAligned(sz.d_height));
    }
    else
    {
        usz.d_x = cegui_reldim(sz.d_width);
        usz.d_y = cegui_reldim(sz.d_height);
    }

    setWindowMaxSize(usz);
}



const Image* Window::getMouseCursor(bool useDefault) const
{
	if (d_mouseCursor != (const Image*)DefaultMouseCursor)
	{
		return d_mouseCursor;
	}
	else
	{
		return useDefault ? System::getSingleton().getDefaultMouseCursor() : 0;
	}

}



void Window::setMouseCursor(const String& imageset, const String& image_name)
{
	d_mouseCursor = ImagesetManager::getSingleton().getImageset(imageset)->getImage(image_name);
}



void Window::setID(uint ID)
{
	if (d_ID != ID)
	{
		d_ID = ID;

		WindowEventArgs args(this);
		onIDChanged(args);
	}

}



void Window::setMetricsMode(MetricsMode	mode)
{
	if (d_metricsMode != mode)
	{
		MetricsMode oldMode = d_metricsMode;
		d_metricsMode = mode;

		
		if ((d_metricsMode != Inherited) || (oldMode != getMetricsMode()))
		{
			WindowEventArgs args(this);
			onMetricsChanged(args);
		}

	}

}



void Window::setDestroyedByParent(bool setting)
{
	if (d_destroyedByParent != setting)
	{
		d_destroyedByParent = setting;

		WindowEventArgs args(this);
		onParentDestroyChanged(args);
	}

}



MetricsMode Window::getInheritedMetricsMode(void) const
{
	return (d_parent == NULL) ? Relative : d_parent->getMetricsMode();
}



float Window::getXPosition(MetricsMode mode) const
{
	
	if (mode == Inherited)
	{
		mode = getInheritedMetricsMode();
	}

    return (mode == Relative) ? getRelativeXPosition() : getAbsoluteXPosition();
}



float Window::getYPosition(MetricsMode mode) const
{
	
	if (mode == Inherited)
	{
		mode = getInheritedMetricsMode();
	}

    return (mode == Relative) ? getRelativeYPosition() : getAbsoluteYPosition();
}



Point Window::getPosition(MetricsMode mode) const
{
	
	if (mode == Inherited)
	{
		mode = getInheritedMetricsMode();
	}

    return (mode == Relative) ? getRelativePosition() : getAbsolutePosition();
}



float Window::getWidth(MetricsMode mode) const
{
	
	if (mode == Inherited)
	{
		mode = getInheritedMetricsMode();
	}

    return (mode == Relative) ? getRelativeWidth() : getAbsoluteWidth();
}



float Window::getHeight(MetricsMode mode) const
{
	
	if (mode == Inherited)
	{
		mode = getInheritedMetricsMode();
	}

    return (mode == Relative) ? getRelativeHeight() : getAbsoluteHeight();
}



Size Window::getSize(MetricsMode mode) const
{
	
	if (mode == Inherited)
	{
		mode = getInheritedMetricsMode();
	}

    return (mode == Relative) ? getRelativeSize() : getAbsoluteSize();
}



Rect Window::getRect(MetricsMode mode) const
{
	
	if (mode == Inherited)
	{
		mode = getInheritedMetricsMode();
	}

    return (mode == Relative) ? getRelativeRect() : getAbsoluteRect();
}



void Window::setXPosition(MetricsMode mode, float x)
{
	setPosition(mode, Point(x, getYPosition(mode)));
}



void Window::setYPosition(MetricsMode mode, float y)
{
	setPosition(mode, Point(getXPosition(mode), y));
}



void Window::setPosition(MetricsMode mode, const Point& position)
{
	if (mode == Inherited)
	{
		mode = getInheritedMetricsMode();
	}

	if (mode == Relative)
	{
        setWindowPosition(UVector2(cegui_reldim(position.d_x), cegui_reldim(position.d_y)));
	}
	else
	{
        setWindowPosition(UVector2(cegui_absdim(PixelAligned(position.d_x)), cegui_absdim(PixelAligned(position.d_y))));
	}
}



void Window::setWidth(MetricsMode mode, float width)
{
	setSize(mode, Size(width, getHeight(mode)));
}



void Window::setHeight(MetricsMode mode, float height)
{
	setSize(mode, Size(getWidth(mode), height));
}



void Window::setSize(MetricsMode mode, const Size& size)
{
	if (mode == Inherited)
	{
		mode = getInheritedMetricsMode();
	}

    UVector2 usz(((mode == Relative) ? UVector2(cegui_reldim(size.d_width), cegui_reldim(size.d_height)) : UVector2(cegui_absdim(PixelAligned(size.d_width)), cegui_absdim(PixelAligned(size.d_height)))));

    setWindowSize(usz);
}



void Window::setRect(MetricsMode mode, const Rect& area)
{
	if (mode == Inherited)
	{
		mode = getInheritedMetricsMode();
	}

    URect uarea;
    
	if (mode == Relative)
	{
        uarea = URect(
                cegui_reldim(area.d_left),
                cegui_reldim(area.d_top),
                cegui_reldim(area.d_right),
                cegui_reldim(area.d_bottom)
                      );
	}
	else
	{
        uarea = URect(
                cegui_absdim(PixelAligned(area.d_left)),
                cegui_absdim(PixelAligned(area.d_top)),
                cegui_absdim(PixelAligned(area.d_right)),
                cegui_absdim(PixelAligned(area.d_bottom))
                      );
    }

    setWindowArea(uarea);
}



void Window::generateAutoRepeatEvent(MouseButton button)
{
    MouseEventArgs ma(this);
    ma.position = MouseCursor::getSingleton().getPosition();
    ma.moveDelta = Vector2(0.0f, 0.0f);
    ma.button = button;
    ma.sysKeys = System::getSingleton().getSystemKeys();
    ma.wheelChange = 0;
    onMouseButtonDown(ma);
}


bool Window::isMouseButtonHollow(MouseButton button)
{
	bool isButtonHollow = false;
	const char* pName = getName().c_str();
	switch(button)
	{
	case LeftButton:
		if(getMouseLButtonHollow())
			isButtonHollow = true;
		break;
	case RightButton:
		if(getMouseRButtonHollow())
			isButtonHollow = true;
		break;
	default:
		isButtonHollow = false;
		break;
	}

	if(getMouseHollow())
		isButtonHollow = true;

	return isButtonHollow;
}


void Window::addStandardProperties(void)
{
	CEGUI_START_ADD_STATICPROPERTY( Window );
		CEGUI_ADD_STATICPROPERTY( &d_absHeightProperty );
		CEGUI_ADD_STATICPROPERTY( &d_absMaxSizeProperty );
		CEGUI_ADD_STATICPROPERTY( &d_absMinSizeProperty );
		CEGUI_ADD_STATICPROPERTY( &d_absPositionProperty );
		CEGUI_ADD_STATICPROPERTY( &d_absRectProperty );
		CEGUI_ADD_STATICPROPERTY( &d_absSizeProperty );
		CEGUI_ADD_STATICPROPERTY( &d_absWidthProperty );
		CEGUI_ADD_STATICPROPERTY( &d_absXPosProperty );
		CEGUI_ADD_STATICPROPERTY( &d_absYPosProperty );
		CEGUI_ADD_STATICPROPERTY( &d_alphaProperty );
		CEGUI_ADD_STATICPROPERTY( &d_alwaysOnTopProperty );
		CEGUI_ADD_STATICPROPERTY( &d_clippedByParentProperty );
		CEGUI_ADD_STATICPROPERTY( &d_destroyedByParentProperty );
		CEGUI_ADD_STATICPROPERTY( &d_disabledProperty );
		CEGUI_ADD_STATICPROPERTY( &d_fontProperty );
		CEGUI_ADD_STATICPROPERTY( &d_heightProperty );
		CEGUI_ADD_STATICPROPERTY( &d_IDProperty );
		CEGUI_ADD_STATICPROPERTY( &d_inheritsAlphaProperty );
		CEGUI_ADD_STATICPROPERTY( &d_metricsModeProperty );
		CEGUI_ADD_STATICPROPERTY( &d_mouseCursorProperty );
		CEGUI_ADD_STATICPROPERTY( &d_positionProperty );
		CEGUI_ADD_STATICPROPERTY( &d_rectProperty );
		CEGUI_ADD_STATICPROPERTY( &d_relHeightProperty );
		CEGUI_ADD_STATICPROPERTY( &d_relMaxSizeProperty );
		CEGUI_ADD_STATICPROPERTY( &d_relMinSizeProperty );
		CEGUI_ADD_STATICPROPERTY( &d_relPositionProperty );
		CEGUI_ADD_STATICPROPERTY( &d_relRectProperty );
		CEGUI_ADD_STATICPROPERTY( &d_relSizeProperty );
		CEGUI_ADD_STATICPROPERTY( &d_relWidthProperty );
		CEGUI_ADD_STATICPROPERTY( &d_relXPosProperty );
		CEGUI_ADD_STATICPROPERTY( &d_relYPosProperty );
		CEGUI_ADD_STATICPROPERTY( &d_restoreOldCaptureProperty );
		CEGUI_ADD_STATICPROPERTY( &d_sizeProperty );
		CEGUI_ADD_STATICPROPERTY( &d_mouseHollowProperty );
		CEGUI_ADD_STATICPROPERTY( &d_mouseMoveHollowProperty );
		CEGUI_ADD_STATICPROPERTY( &d_mouseLButtonHollowProperty );
		CEGUI_ADD_STATICPROPERTY( &d_mouseRButtonHollowProperty );
		CEGUI_ADD_STATICPROPERTY( &d_textOriginalProperty );
		CEGUI_ADD_STATICPROPERTY( &d_textProperty );
		CEGUI_ADD_STATICPROPERTY( &d_visibleProperty );
		CEGUI_ADD_STATICPROPERTY( &d_widthProperty );
		CEGUI_ADD_STATICPROPERTY( &d_xPosProperty );
		CEGUI_ADD_STATICPROPERTY( &d_yPosProperty );
		CEGUI_ADD_STATICPROPERTY( &d_zOrderChangeProperty );
		CEGUI_ADD_STATICPROPERTY( &d_wantsMultiClicksProperty );
		CEGUI_ADD_STATICPROPERTY( &d_autoRepeatProperty );
		CEGUI_ADD_STATICPROPERTY( &d_autoRepeatDelayProperty );
		CEGUI_ADD_STATICPROPERTY( &d_autoRepeatRateProperty );
		CEGUI_ADD_STATICPROPERTY( &d_distInputsProperty );
		CEGUI_ADD_STATICPROPERTY( &d_tooltipTypeProperty );
		CEGUI_ADD_STATICPROPERTY( &d_tooltipProperty );
		CEGUI_ADD_STATICPROPERTY( &d_inheritsTooltipProperty );
		CEGUI_ADD_STATICPROPERTY( &d_riseOnClickProperty );
		CEGUI_ADD_STATICPROPERTY( &d_vertAlignProperty );
		CEGUI_ADD_STATICPROPERTY( &d_horzAlignProperty );
		CEGUI_ADD_STATICPROPERTY( &d_unifiedAreaRectProperty );
		CEGUI_ADD_STATICPROPERTY( &d_unifiedPositionProperty );
		CEGUI_ADD_STATICPROPERTY( &d_unifiedXPositionProperty );
		CEGUI_ADD_STATICPROPERTY( &d_unifiedYPositionProperty );
		CEGUI_ADD_STATICPROPERTY( &d_unifiedSizeProperty );
		CEGUI_ADD_STATICPROPERTY( &d_unifiedWidthProperty );
		CEGUI_ADD_STATICPROPERTY( &d_unifiedHeightProperty );
		CEGUI_ADD_STATICPROPERTY( &d_unifiedMinSizeProperty );
		CEGUI_ADD_STATICPROPERTY( &d_unifiedMaxSizeProperty );
		
		CEGUI_ADD_STATICPROPERTY( &d_zoomModeProperty );
		CEGUI_ADD_STATICPROPERTY( &d_hookPositionProperty);
		CEGUI_ADD_STATICPROPERTY( &d_hookModeProperty);
		CEGUI_ADD_STATICPROPERTY( &d_stepShowTimeProperty);
		CEGUI_ADD_STATICPROPERTY( &d_NeedRealTimeUpdateProperty);
		CEGUI_ADD_STATICPROPERTY( &d_ExtendTooltipProperty);		
		CEGUI_ADD_STATICPROPERTY( &d_GroupWindowProperty);
		CEGUI_ADD_STATICPROPERTY( &d_BaseTopProperty);
		CEGUI_ADD_STATICPROPERTY( &d_BaseLeftProperty);
		CEGUI_ADD_STATICPROPERTY( &d_SpecialModalProperty);
		CEGUI_ADD_STATICPROPERTY( &d_WindowLayOutNumProperty);
		CEGUI_ADD_STATICPROPERTY( &d_HyperLinkColorDefaultProperty);
		CEGUI_ADD_STATICPROPERTY( &d_HyperLinkColorActiveProperty);

	CEGUI_END_ADD_STATICPROPERTY
}



bool Window::isZOrderingEnabled(void) const
{
	return d_zOrderingEnabled;
}



void Window::setZOrderingEnabled(bool setting)
{
	if (d_zOrderingEnabled != setting)
	{
		d_zOrderingEnabled = setting;
	}

}



bool Window::wantsMultiClickEvents(void) const
{
    return d_wantsMultiClicks;
}



void Window::setWantsMultiClickEvents(bool setting)
{
    if (d_wantsMultiClicks != setting)
    {
        d_wantsMultiClicks = setting;

        
    }

}



bool Window::isMouseAutoRepeatEnabled(void) const
{
    return d_autoRepeat;
}



float Window::getAutoRepeatDelay(void) const
{
    return d_repeatDelay;
}

    

float Window::getAutoRepeatRate(void) const
{
    return d_repeatRate;
}



void Window::setMouseAutoRepeatEnabled(bool setting)
{
    if (d_autoRepeat != setting)
    {
        d_autoRepeat = setting;
        d_repeatButton = NoButton;
 
        
    }

}



void Window::setAutoRepeatDelay(float delay)
{
    if (d_repeatDelay != delay)
    {
        d_repeatDelay = delay;

        
    }

}

    

void Window::setAutoRepeatRate(float rate)
{
    if (d_repeatRate != rate)
    {
        d_repeatRate = rate;

        
    }

}



void Window::update(float elapsed)
{
	
	if(!d_realTimeUpdate)
	{
		return;
	}

	updateSelf(elapsed);
}



void Window::updateAll(float elapsed)
{
	uint child_count = getChildCount();

	if(!d_realTimeUpdate && child_count == 0)
	{
		return;
	}

	
	updateSelf(elapsed);

	
	for (uint i = 0; i < child_count; ++i)
	{
		d_children[i]->updateAll(elapsed);
	}
}


void Window::updateSelf(float elapsed)
{
	UI_TRY
    
    if (d_autoRepeat && d_repeatButton != NoButton)
    {
        d_repeatElapsed += elapsed;

        if (d_repeating)
        {
            if (d_repeatElapsed > d_repeatRate)
            {
                d_repeatElapsed -= d_repeatRate;
                
                generateAutoRepeatEvent(d_repeatButton);
            }
        }
        else
        {
            if (d_repeatElapsed > d_repeatDelay)
            {
                d_repeatElapsed = 0;
                d_repeating = true;
                
                generateAutoRepeatEvent(d_repeatButton);
            }
        }
    }
	UI_CATCH( "updateSelf --Window::updateSelf" )
}

bool Window::distributesCapturedInputs(void) const
{
    return d_distCapturedInputs;
}

void Window::setDistributesCapturedInputs(bool setting)
{
    if (d_distCapturedInputs != setting)
    {
        d_distCapturedInputs = setting;

        
    }
}

void Window::notifyDragDropItemEnters(DragContainer* item)
{
    if (item)
    {
        DragDropEventArgs args(this);
        args.dragDropItem = item;
        onDragDropItemEnters(args);
    }
}

void Window::notifyDragDropItemLeaves(DragContainer* item)
{
    if (item)
    {
        DragDropEventArgs args(this);
        args.dragDropItem = item;
        onDragDropItemLeaves(args);
    }
}

void Window::notifyDragDropItemDropped(DragContainer* item)
{
    if (item)
    {
        DragDropEventArgs args(this);
        args.dragDropItem = item;
        onDragDropItemDropped(args);
    }
}

void Window::destroy(void)
{
    
    
    
    WindowManager& wmgr = WindowManager::getSingleton();

    if (wmgr.isWindowPresent(this->getName()))
    {
        wmgr.destroyWindow(this);

        
        
        return;
    }

    releaseInput();

    
    WindowEventArgs args(this);
    onDestructionStarted(args);

    
    if (d_parent != NULL)
    {
        d_parent->removeChildWindow(this);
    }

    cleanupChildren();
}

bool Window::isUsingDefaultTooltip(void) const
{
    return d_customTip == 0;
}

Tooltip* Window::getTooltip(void) const
{
    return isUsingDefaultTooltip() ? System::getSingleton().getDefaultTooltip() : d_customTip;
}

void Window::setTooltip(Tooltip* tooltip)
{
    
    if (d_customTip && d_weOwnTip)
        WindowManager::getSingleton().destroyWindow(d_customTip);

    
    d_weOwnTip = false;
    d_customTip = tooltip;
}

void Window::setTooltipType(const String& tooltipType)
{
    
    if (d_customTip && d_weOwnTip)
        WindowManager::getSingleton().destroyWindow(d_customTip);

    if (tooltipType.empty())
    {
        d_customTip = 0;
        d_weOwnTip = false;
    }
    else
    {
        try
        {
            d_customTip = static_cast<Tooltip*>(WindowManager::getSingleton().createWindow(tooltipType, getName() + "__auto_tooltip__"));
            d_weOwnTip = true;
        }
        catch (UnknownObjectException x)
        {
            d_customTip = 0;
            d_weOwnTip = false;
        }
    }
}

String Window::getTooltipType(void) const
{
    return isUsingDefaultTooltip() ? String("") : d_customTip->getType();
}

void Window::setTooltipText(const String& tip)
{
    d_tooltipText = tip;

    Tooltip* tooltip = getTooltip();

    if (tooltip && tooltip->getTargetWindow() == this)
    {
        tooltip->setText(tip);
    }
}

const String& Window::getTooltipText(void) const
{
    if (d_inheritsTipText && d_parent && d_tooltipText.empty())
    {
		UI_TRY
        return d_parent->getTooltipText();
		UI_CATCH( "d_parent->getTooltipText()--Window::getTooltipText" )
    }
    else
    {
        return d_tooltipText;
    }
}

bool Window::inheritsTooltipText(void) const
{
    return d_inheritsTipText;
}
   
void Window::setInheritsTooltipText(bool setting)
{
    if (d_inheritsTipText != setting)
    {
        d_inheritsTipText = setting;

        
    }
}

void Window::doRiseOnClick(void)
{
    
    if (d_riseOnClick)
    {
        moveToFront_impl(true);
    }
    else if (d_parent)
    {
        d_parent->doRiseOnClick();
    }
}

void Window::setWindowArea_impl(const UVector2& pos, const UVector2& outer_size, bool topLeftSizing, bool fireEvents, bool sizeChanged)
{
    
    bool moved = false, sized;
    
	UVector2 size = outer_size;

    
    Size oldSize(d_pixelSize);
	
	Size ScreenRect = System::getSingleton().getRenderer()->getSize();
	Size OldScreenRect = System::getSingleton().getRenderer()->getOldSize();
	UVector2 oldtempposition = *(&d_area.getPosition());
	float OldScreenX = oldtempposition.d_x.asAbsolute(OldScreenRect.d_width);
	

    
    Vector2 absMax(d_maxSize.asAbsolute(ScreenRect));
    Vector2 absMin(d_minSize.asAbsolute(ScreenRect));
	switch( m_ZoomMode )
	{
	case Absolute:
	case Relative:
		d_pixelSize = size.asAbsolute(Size( 1024, 768 )).asSize();
		break;
	case Inherited:
	default:
		d_pixelSize = size.asAbsolute(getParentSize()).asSize();
		break;
	}

	

	if(d_groupWindow)
	{
		float xscale = ScreenRect.d_width/1024;
		float yscale = ScreenRect.d_height/768;			

		d_pixelSize.d_width = d_pixelSize.d_width/xscale * yscale;
	}

	d_area.setSize(size);

	
    if (d_pixelSize.d_width < absMin.d_x)
        d_pixelSize.d_width = absMin.d_x;
	else if (!d_IsIgnoreMaxSize && d_pixelSize.d_width > absMax.d_x)
        d_pixelSize.d_width = absMax.d_x;
    if (d_pixelSize.d_height < absMin.d_y)
        d_pixelSize.d_height = absMin.d_y;
    else if (!d_IsIgnoreMaxSize && d_pixelSize.d_height > absMax.d_y)
        d_pixelSize.d_height = absMax.d_y;

    sized = (d_pixelSize != oldSize);

    
    

    if (!topLeftSizing || sized)
    {
        
		switch( m_ZoomMode )
		{
		case Absolute:
			{
				Point newPos = m_ptHookPosition;
				if( m_HookMode != Hook_None )
				{
					switch( m_HookMode )
					{
					case Hook_Left:
						newPos.d_y -= d_pixelSize.d_height / 2;
						break;
					case Hook_Right:
						newPos.d_x -= d_pixelSize.d_width;
						newPos.d_y -= d_pixelSize.d_height / 2;
						break;
					case Hook_Top:
						newPos.d_x -= d_pixelSize.d_width / 2;
						break;
					case Hook_Bottom:
						newPos.d_x -= d_pixelSize.d_width / 2;
						newPos.d_y -= d_pixelSize.d_height;
						break;
					case Hook_LeftTop:
						break;
					case Hook_LeftBottom:
						newPos.d_y -= d_pixelSize.d_height;
						break;
					case Hook_RightTop:
						newPos.d_x -= d_pixelSize.d_width;
						break;
					case Hook_RightBottom:
						newPos.d_x -= d_pixelSize.d_width;
						newPos.d_y -= d_pixelSize.d_height;
						break;
					case Hook_Center:
						newPos.d_x -= d_pixelSize.d_width / 2;
						newPos.d_y -= d_pixelSize.d_height / 2;
						break;
					default:
						break;
					}
					d_area.setPosition( UVector2(cegui_absdim(PixelAligned(newPos.d_x)), cegui_absdim(PixelAligned( newPos.d_y) ) ) );
				}
			}
			break;
		case Relative:
				{
					Point newPos;
					if( getParent() )
					{
						newPos.d_x = m_ptHookPosition.d_x * getParent()->getAbsoluteWidth();
						newPos.d_y = m_ptHookPosition.d_y * getParent()->getAbsoluteHeight();
					}
					else
					{
						newPos.d_x = m_ptHookPosition.d_x * System::getSingleton().getRenderer()->getSize().d_width;
						newPos.d_y = m_ptHookPosition.d_y * System::getSingleton().getRenderer()->getSize().d_height;
					}
					if( m_HookMode != Hook_None )
					{
						switch( m_HookMode )
						{
						case Hook_Left:
							newPos.d_y -= d_pixelSize.d_height / 2;
							break;
						case Hook_Right:
							newPos.d_x -= d_pixelSize.d_width;
							newPos.d_y -= d_pixelSize.d_height / 2;
							break;
						case Hook_Top:
							newPos.d_x -= d_pixelSize.d_width / 2;
							break;
						case Hook_Bottom:
							newPos.d_x -= d_pixelSize.d_width / 2;
							newPos.d_y -= d_pixelSize.d_height;
							break;
						case Hook_LeftTop:
							break;
						case Hook_LeftBottom:
							newPos.d_y -= d_pixelSize.d_height;
							break;
						case Hook_RightTop:
							newPos.d_x -= d_pixelSize.d_width;
							break;
						case Hook_RightBottom:
							newPos.d_x -= d_pixelSize.d_width;
							newPos.d_y -= d_pixelSize.d_height;
							break;
						case Hook_Center:
							newPos.d_x -= d_pixelSize.d_width / 2;
							newPos.d_y -= d_pixelSize.d_height / 2;
							break;
						default:
							break;
						}
						d_area.setPosition( UVector2(cegui_absdim(PixelAligned(newPos.d_x)), cegui_absdim(PixelAligned( newPos.d_y) ) ) );
					}
				}
				break;
		case Inherited:
		default:
			d_area.setPosition(pos);
			break;
		}
		moved = true;
    }

	
	if (!topLeftSizing &&
		d_groupWindow && 
		sizeChanged &&
		d_pixelSize.d_width > 5.f &&
		OldScreenRect.d_width > 10.0f && 
		(BHE_RIGHT == d_baseHorizon || BHE_CENTER == d_baseHorizon) && 
		ScreenRect != OldScreenRect)
	{
		sized = true;
	}

	if(d_groupWindow && sized)
	{
		UVector2 tempposition = *(&d_area.getPosition());
		UDim ScreenY = tempposition.d_y;
		UDim ScreenX = tempposition.d_x;

		if(OldScreenRect.d_width>10.0f)
		{
			switch(d_baseHorizon)
			{
			case BHE_RIGHT:
				{
					
					
					float newrightScreenX = 0.0f;
					if( getParent() )
					{
						newrightScreenX = getParent()->getAbsolutePosition().d_x + getParent()->getAbsoluteWidth() - d_pixelSize.d_width;
					}
					else
					{
						newrightScreenX = ScreenRect.d_width - d_pixelSize.d_width;
					}
					d_area.setPosition(UVector2(cegui_absdim(PixelAligned(newrightScreenX)), ScreenY  ));
				}
				break;
			case BHE_CENTER:
				{
					float ScreenX = ScreenRect.d_width/2.0f - d_pixelSize.d_width/2.0f;
					d_area.setPosition(UVector2(cegui_absdim(PixelAligned(ScreenX)), ScreenY  ));				
				}
				break;
			default:
				{
					float xleftscale = OldScreenX/OldScreenRect.d_width;
					float newleftScreenX = xleftscale*ScreenRect.d_width;
					d_area.setPosition(UVector2(cegui_absdim(PixelAligned(newleftScreenX)), ScreenY  ));
				}
				break;
			}
		}
		else
		{
			switch(d_baseHorizon)
			{
			case BHE_RIGHT:
				{
					
					float newrightScreenX = ScreenRect.d_width - d_pixelSize.d_width;
					d_area.setPosition(UVector2(cegui_absdim(PixelAligned(newrightScreenX)), ScreenY  ));
				}
				break;
			case BHE_CENTER:
				{
					float ScreenX = ScreenRect.d_width/2.0f - d_pixelSize.d_width/2.0f;
					d_area.setPosition(UVector2(cegui_absdim(PixelAligned(ScreenX)), ScreenY  ));				
				}
				break;
			default:
				{
					
					
					d_area.setPosition(UVector2(ScreenX, ScreenY  ));
				}
				break;
			}
		}

	}

    
    if (fireEvents)
    {
        WindowEventArgs args(this);

        if (moved)
        {
            onMoved(args);
            
            args.handled = false;
        }
    
        if (sized)
        {
            onSized(args);
        }
    }
}

void Window::saveOldArea()
{
	if( d_oldArea == NULL )
	{
		d_oldArea = new Rect;
		*d_oldArea = getRect();
	}
}

void Window::revertOldArea()
{
	setRect(getMetricsMode(), *d_oldArea); 
}









void Window::setAreaAndTexCoord( int iDir_X, float fXPercent, int iDir_Y, float fYPercent )
{
	saveOldArea();
	revertOldArea();

	
	enum CHANGE_DIR_X
	{
		LEFT_TO_RIGHT = 1,
		RIGHT_TO_LEFT,
	};
	enum CHANGE_DIR_Y
	{
		TOP_TO_BOTTOM = 1,
		BOTTOM_TO_TOP,
	};

	
	Point oPos = getPosition();
	Rect oWindowSize = getRect();

	
	
	

	if( d_oldArea != NULL )
	{
		CHANGE_DIR_X oCdX = (CHANGE_DIR_X)(iDir_X);
		float fScaleW = oWindowSize.getWidth() * fXPercent;
		float fIvtW = oWindowSize.getWidth() - fScaleW;

		if( oCdX == LEFT_TO_RIGHT )
		{
			oWindowSize.d_left += fIvtW;
			oPos.d_x += fIvtW;
		}
		else if( oCdX == RIGHT_TO_LEFT )
		{
			oWindowSize.d_right = oWindowSize.d_left + fScaleW;
			fXPercent = -fXPercent;
		}
		
		setTexcoordPercentX( fXPercent );
	}

	if( d_oldArea != NULL )
	{
		CHANGE_DIR_Y oCdY = (CHANGE_DIR_Y)(iDir_Y);
		float fScaleH = oWindowSize.getHeight() * fYPercent;
		float fIvtH = oWindowSize.getHeight() - fScaleH;

		if( oCdY == TOP_TO_BOTTOM )
		{
			oWindowSize.d_top += fIvtH;
			oPos.d_y += fIvtH;
		}
		else if( oCdY == BOTTOM_TO_TOP )
		{
			oWindowSize.d_bottom = oWindowSize.d_top + fScaleH;
			fYPercent = -fYPercent;
		}
		
		setTexcoordPercentY( fYPercent );
	}

	
	setPosition(oPos);
	setRect(getMetricsMode(), oWindowSize);
}

void Window::setWindowArea(const UDim& xpos, const UDim& ypos, const UDim& width, const UDim& height)
{
    setWindowArea(UVector2(xpos, ypos), UVector2(width, height));
}

void Window::setWindowArea(const UVector2& pos, const UVector2& size)
{
    setWindowArea_impl(pos, size);
}

void Window::setWindowArea(const URect& area)
{
    setWindowArea(area.d_min, area.getSize());
}

void Window::setWindowPosition(const UVector2& pos)
{
    setWindowArea_impl(pos, d_area.getSize());
}

void Window::setWindowXPosition(const UDim& x)
{
    setWindowArea_impl(UVector2(x, d_area.d_min.d_y), d_area.getSize());
}

void Window::setWindowYPosition(const UDim& y)
{
    setWindowArea_impl(UVector2(d_area.d_min.d_x, y), d_area.getSize());
}

void Window::setWindowSize(const UVector2& size)
{
    setWindowArea_impl(d_area.getPosition(), size);
}

void Window::setWindowWidth(const UDim& width)
{
    setWindowArea_impl(d_area.getPosition(), UVector2(width, d_area.getSize().d_y));
}

void Window::setWindowHeight(const UDim& height)
{
    setWindowArea_impl(d_area.getPosition(), UVector2(d_area.getSize().d_x, height));
}

void Window::setWindowMaxSize(const UVector2& size)
{
    d_maxSize = size;

    
    setWindowArea(d_area);
}

void Window::setWindowMinSize(const UVector2& size)
{
    d_minSize = size;

    
    setWindowArea(d_area);
}

void Window::setIgnoreMaxSizeFlag(bool bIgnore)
{
	d_IsIgnoreMaxSize = bIgnore;
}

const URect& Window::getWindowArea() const
{
    return d_area;
}

const UVector2& Window::getWindowPosition() const
{
    return d_area.d_min;
}

const UDim& Window::getWindowXPosition() const
{
    return d_area.d_min.d_x;
}

const UDim& Window::getWindowYPosition() const
{
    return d_area.d_min.d_y;
}

UVector2 Window::getWindowSize() const
{
    return d_area.getSize();
}

UDim Window::getWindowWidth() const
{
    return d_area.getSize().d_x;
}

UDim Window::getWindowHeight() const
{
    return d_area.getSize().d_y;
}

const UVector2& Window::getWindowMaxSize() const
{
    return d_maxSize;
}

const UVector2& Window::getWindowMinSize() const
{
    return d_minSize;
}

void Window::setVerticalAlignment(const VerticalAlignment alignment)
{
    if (d_vertAlign != alignment)
    {
        d_vertAlign = alignment;

        WindowEventArgs args(this);
        onVerticalAlignmentChanged(args);
    }
}

void Window::setHorizontalAlignment(const HorizontalAlignment alignment)
{
    if (d_horzAlign != alignment)
    {
        d_horzAlign = alignment;

        WindowEventArgs args(this);
        onHorizontalAlignmentChanged(args);
    }
}

const String& Window::getLookNFeel()
{
    return d_lookName;
}

void Window::setLookNFeel(const String& falagardType, const String& look)
{
    if (d_lookName.empty())
    {
        d_falagardType = falagardType;
        d_lookName = look;
        Logger::getSingleton().logEvent("Assigning LookNFeel '" + look +"' to window '" + d_name + "'.", Informative);

        
        const WidgetLookFeel& wlf = WidgetLookManager::getSingleton().getWidgetLook(look);
        
        wlf.initialiseWidget(*this);
    }
    else
    {
        throw InvalidRequestException("Window::setLookNFeel - The window '" + d_name + "' already has a look assigned (" + d_lookName + ").");
    }
}

void Window::setModalState(bool state)
{
	bool already_modal = getModalState();

	
	if (state == true && !already_modal)
	{
		activate();
		System::getSingleton().setModalTarget(this);
	}
	
	else if (already_modal)
	{
		System::getSingleton().setModalTarget(NULL);
	}
}

void Window::performChildWindowLayout()
{
    if (!d_lookName.empty())
    {
        
        try
        {
            const WidgetLookFeel& wlf = WidgetLookManager::getSingleton().getWidgetLook(d_lookName);
            
            wlf.layoutChildWidgets(*this);
        }
        catch (UnknownObjectException)
        {
            Logger::getSingleton().logEvent("Window::performChildWindowLayout - assigned widget look was not found.", Errors);
        }
    }
}

const String& Window::getUserString(const String& name) const
{
    UserStringMap::const_iterator iter = d_userStrings.find(name);

    if (iter != d_userStrings.end())
    {
        return (*iter).second;
    }
    else
    {
        throw UnknownObjectException("Window::getUserString - a user string named '" + name + "' has not been set for this Window.");
    }
}

bool Window::isUserStringDefined(const String& name) const
{
     return d_userStrings.find(name) != d_userStrings.end();
}

void Window::setUserString(const String& name, const String& value)
{
    d_userStrings[name] = value;
}

void Window::writeXMLToStream(OutStream& out_stream) const
{
    
    out_stream << "<Window Type=\"" << getType() << "\" ";
    
    if (getName().compare(0, WindowManager::GeneratedWindowNameBase.length(), WindowManager::GeneratedWindowNameBase) != 0)
    {
        out_stream << "Name=\"" << getName() << "\" ";
    }
    
    out_stream << ">" << std::endl;

    
    writePropertiesXML(out_stream);
    
    writeChildWindowsXML(out_stream);
    
    out_stream << "</Window>" << std::endl;
}

int Window::writePropertiesXML(OutStream& out_stream) const
{
	return 0;
#if 0
    int propertiesWritten = 0;
    PropertyIterator iter =  PropertySet::getIterator();

    while(!iter.isAtEnd())
    {
			try
			{
        
        if (!iter.getCurrentValue()->isDefault(this))
        {
            iter.getCurrentValue()->writeXMLToStream(this, out_stream);
            ++propertiesWritten;
        }
			}
			catch (InvalidRequestException)
			{
				
				Logger::getSingleton().logEvent("Window::writePropertiesXML - property receiving failed. Continuing...", Errors);
			}

        ++iter;
    }

    return propertiesWritten;
#endif
}

const PropertySet* Window::getPropertyInstance(const String& name) const
{
	
	if(d_windowFactory && d_windowFactory->isPropertyPresent(name))
	{
		return d_windowFactory;
	}

	
    if (!d_lookName.empty())
    {
		const WidgetLookFeel& wlf = WidgetLookManager::getSingleton().getWidgetLook(d_lookName);
		if(wlf.isPropertyPresent(name)) return &wlf;
    }

	return 0;
}

bool Window::isPropertyPresent(const String& name) const
{
	return getPropertyInstance(name) != 0;
}

String Window::getProperty(const String& name) const
{
	const PropertySet* propertySet = getPropertyInstance(name);
	if(propertySet)
	{
		return propertySet->getProperty(name, *this);
	}

	throw UnknownObjectException("There is no Property named '" + name + "' available in the window." + d_name + " Class:" + d_type);
}

void Window::setProperty(const String& name, const String& value)
{
	const PropertySet* propertySet = getPropertyInstance(name);
	if(propertySet)
	{
		return propertySet->setProperty(name, value, *this);
	}

	
	throw UnknownObjectException("There is no Property named '" + name + "' available in the window '" + d_name + "' Class:" + d_type);
}

bool Window::isPropertyDefault(const String& name) const
{
	const PropertySet* propertySet = getPropertyInstance(name);
	if(propertySet)
	{
		return propertySet->isPropertyDefault(name, *this);
	}

	throw UnknownObjectException("There is no Property named '" + name + "' available in the window.");
}

String Window::getPropertyDefault(const String& name) const
{
	const PropertySet* propertySet = getPropertyInstance(name);
	if(propertySet)
	{
		return propertySet->getPropertyDefault(name, *this);
	}

	throw UnknownObjectException("There is no Property named '" + name + "' available in the window.");
}

int Window::writeChildWindowsXML(OutStream& out_stream) const
{
    int windowsWritten = 0;

    for (uint i = 0; i < getChildCount(); ++i)
    {
        Window* child = d_children[i];

        
        if (child->getName().find("__auto_") == String::npos)
        {
            child->writeXMLToStream(out_stream);
            ++windowsWritten;
        }
    }

    return windowsWritten;
}

void Window::addWindowToDrawList(Window& wnd, bool at_back)
{
    
    if (at_back)
    {
         
        ChildList::iterator pos = d_drawList.begin();
        if (wnd.isAlwaysOnTop())
        {
            
            while ((pos != d_drawList.end()) && (!(*pos)->isAlwaysOnTop()))
                ++pos;
        }
        
        d_drawList.insert(pos, &wnd);
    }
    
    else
    {
        
        ChildList::reverse_iterator	position = d_drawList.rbegin();
        if (!wnd.isAlwaysOnTop())
        {
            
            while ((position != d_drawList.rend()) && ((*position)->isAlwaysOnTop()))
                ++position;
        }
        
        d_drawList.insert(position.base(), &wnd);
    }
}

void Window::removeWindowFromDrawList(const Window& wnd)
{
    
    if (!d_drawList.empty())
    {
        
        ChildList::iterator	position = std::find(d_drawList.begin(), d_drawList.end(), &wnd);

        
        if (position != d_drawList.end())
            d_drawList.erase(position);
    }
}

Window* Window::getActiveSibling()
{
    
    Window* activeWnd = isActive() ? this : 0;

    
    if (!activeWnd && d_parent)
    {
        
        
        uint idx = d_parent->getChildCount();
        while (idx-- > 0)
        {
            
            if (d_parent->d_drawList[idx]->isActive())
            {
                
                activeWnd = d_parent->d_drawList[idx];
                
                break;
            }
        }
    }

    
    return activeWnd;
}

void Window::rename(const String& new_name)
{
    WindowManager& winMgr = WindowManager::getSingleton();
    
    if (winMgr.isWindowPresent(d_name))
    {
        winMgr.renameWindow(this, new_name);
        
        
        return;
    }

    if (winMgr.isWindowPresent(new_name))
        throw AlreadyExistsException("Window::rename - a Window named '" +
                new_name + "' already exists within the system.");

    
    if (!d_lookName.empty())
    {
        const WidgetLookFeel& wlf =
                WidgetLookManager::getSingleton().getWidgetLook(d_lookName);

        
        wlf.renameChildren(*this, new_name);
    }

    
    const String autoPrefix(d_name + "__auto_");
    
    const size_t oldNameLength = d_name.length();

    
    for (size_t i = 0; i < getChildCount(); ++i)
    {
        
        if (!d_children[i]->d_name.compare(0, autoPrefix.length(), autoPrefix))
        {
            winMgr.renameWindow(d_children[i],
                                new_name +
                                d_children[i]->d_name.substr(oldNameLength));
        }
    }

    
    Logger::getSingleton().logEvent("Renamed window: " + d_name +
                                    " as: " + new_name,
                                    Informative);

    
    d_name = new_name;
}






void Window::onSized(WindowEventArgs& e)
{
	
	uint child_count = getChildCount();
	for (uint i = 0; i < child_count; ++i)
	{
		WindowEventArgs args(this);
		d_children[i]->onParentSized(args);
	}

	performChildWindowLayout();

	requestRedraw();

	fireEvent(EventSized, e, EventNamespace);
}


void Window::onMoved(WindowEventArgs& e)
{
	updatePositionChanged();

	int child_count = getChildCount();

	for (int i = 0; i < child_count; ++i)
	{
		d_children[i]->onMoved(e);
	}

    
    
    System::getSingleton().signalRedraw();
	fireEvent(EventMoved, e, EventNamespace);
}


void Window::onTextChanged(WindowEventArgs& e)
{
	requestRedraw();
	fireEvent(EventTextChanged, e, EventNamespace);
}


void Window::onFontChanged(WindowEventArgs& e)
{
	requestRedraw();
	fireEvent(EventFontChanged, e, EventNamespace);
}


void Window::onAlphaChanged(WindowEventArgs& e)
{
	
	int child_count = getChildCount();

	for (int i = 0; i < child_count; ++i)
	{
		if (d_children[i]->inheritsAlpha())
		{
            WindowEventArgs args(d_children[i]);
			d_children[i]->onAlphaChanged(args);
		}
	}

	requestRedraw();
	fireEvent(EventAlphaChanged, e, EventNamespace);
}


void Window::onIDChanged(WindowEventArgs& e)
{
	fireEvent(EventIDChanged, e, EventNamespace);
}


void Window::onShown(WindowEventArgs& e)
{
	requestRedraw();
	fireEvent(EventShown, e, EventNamespace);
}


void Window::onHidden(WindowEventArgs& e)
{
	requestRedraw();
	fireEvent(EventHidden, e, EventNamespace);

    uint child_count = getChildCount();
    for (uint i = 0; i < child_count; ++i)
    {
		d_children[i]->onParentHidden();
	}
}

void Window::onParentHidden(void)
{
	WindowEventArgs args(this);
	fireEvent(EventParentHidden, args, EventNamespace);

    Tooltip* tip = getTooltip();
    if (tip && tip->getTargetWindow()==this)
    {
        tip->setTargetWindow(0);
    }

	uint child_count = getChildCount();
    for (uint i = 0; i < child_count; ++i)
    {
		d_children[i]->onParentHidden();
	}
}

void Window::onEnabled(WindowEventArgs& e)
{
    
    uint child_count = getChildCount();
    for (uint i = 0; i < child_count; ++i)
    {
        if (d_children[i]->d_enabled)
        {
            WindowEventArgs args(d_children[i]);
            d_children[i]->onEnabled(args);
        }
    }

    requestRedraw();
    fireEvent(EventEnabled, e, EventNamespace);
}


void Window::onDisabled(WindowEventArgs& e)
{
    
    uint child_count = getChildCount();
    for (uint i = 0; i < child_count; ++i)
    {
        if (d_children[i]->d_enabled)
        {
            WindowEventArgs args(d_children[i]);
            d_children[i]->onDisabled(args);
        }
    }

	requestRedraw();
	fireEvent(EventDisabled, e, EventNamespace);
}


void Window::onMetricsChanged(WindowEventArgs& e)
{
	fireEvent(EventMetricsModeChanged, e, EventNamespace);
}


void Window::onClippingChanged(WindowEventArgs& e)
{
	requestRedraw();
	fireEvent(EventClippedByParentChanged, e, EventNamespace);
}


void Window::onParentDestroyChanged(WindowEventArgs& e)
{
	fireEvent(EventDestroyedByParentChanged, e, EventNamespace);
}


void Window::onInheritsAlphaChanged(WindowEventArgs& e)
{
	requestRedraw();
	fireEvent(EventInheritsAlphaChanged, e, EventNamespace);
}


void Window::onAlwaysOnTopChanged(WindowEventArgs& e)
{
    
    
    System::getSingleton().signalRedraw();
	fireEvent(EventAlwaysOnTopChanged, e, EventNamespace);
}


void Window::onCaptureGained(WindowEventArgs& e)
{
	fireEvent(EventInputCaptureGained, e, EventNamespace);
}


void Window::onCaptureLost(WindowEventArgs& e)
{
    
    d_repeatButton = NoButton;

	
	if (d_restoreOldCapture && (d_oldCapture != NULL)) {
		d_oldCapture->onCaptureLost(e);
		d_oldCapture = NULL;
	}

	
	
	

	fireEvent(EventInputCaptureLost, e, EventNamespace);
}


void Window::onRenderingStarted(WindowEventArgs& e)
{
	fireEvent(EventRenderingStarted, e, EventNamespace);
}


void Window::onRenderingEnded(WindowEventArgs& e)
{
	fireEvent(EventRenderingEnded, e, EventNamespace);
}


void Window::onZChanged(WindowEventArgs& e)
{
    
    
    System::getSingleton().signalRedraw();
	fireEvent(EventZOrderChanged, e, EventNamespace);
}


void Window::onDestructionStarted(WindowEventArgs& e)
{
	fireEvent(EventDestructionStarted, e, EventNamespace);
}


void Window::onActivated(ActivationEventArgs& e)
{
	d_active = true;
	requestRedraw();
	fireEvent(EventActivated, e, EventNamespace);
}


void Window::onDeactivated(ActivationEventArgs& e)
{
	
	uint child_count = getChildCount();
	for (uint i = 0; i < child_count; ++i)
	{
		if (d_children[i]->isActive())
		{
			d_children[i]->onDeactivated(e);
		}

	}

	d_active = false;
	requestRedraw();
	fireEvent(EventDeactivated, e, EventNamespace);
}


void Window::onParentSized(WindowEventArgs& e)
{
    
    
    setWindowArea_impl(d_area.getPosition(), d_area.getSize(), false, false, true);

    
    if ((d_area.d_min.d_x.d_scale != 0) || (d_area.d_min.d_y.d_scale != 0))
    {
        WindowEventArgs args(this);
        onMoved(args);
    }

    if ((d_area.d_max.d_x.d_scale != 0) || (d_area.d_max.d_y.d_scale != 0))
    {
        WindowEventArgs args(this);
        onSized(args);
    }
    
    fireEvent(EventParentSized, e, EventNamespace);
}

void Window::setStepShowTime(float seconds)
{
	d_stepShowTime = seconds;
	if(d_stepShowTime > 0.0f)
	{
		d_enableStepShow = true;
		d_currentStepShowTime = d_stepShowTime;
		setNeedRealTimeUpdate(true);
	}
}

float Window::getStepShowTime() const
{
	return d_stepShowTime;
}

void Window::setNeedRealTimeUpdate(bool flag)
{
	d_realTimeUpdate = flag;
	if(d_realTimeUpdate)
	{
		System::getSingleton().addRealTimeUpdateWindow(this);
	}
	else
	{
		System::getSingleton().cancelRealTimeUpdateWindow(this);
	}
}

void Window::setExtendTooltip(bool flag)
{
	d_bExtendTooltip = flag;
}

bool Window::getExtendTooltip()
{
	return d_bExtendTooltip;
}

void Window::setGroupWindow(bool flag)
{
	d_groupWindow = flag;
}

void Window::setBaseTop(bool flag)
{
	d_baseTop = flag;
}

void Window::setSpecialModal(bool spModual)
{
	d_specialModal = spModual;
}
void Window::setBaseLeft(BaseHorizonE flag)
{
	d_baseHorizon = flag;
}


void Window::postSizeChanged(void)
{
	
	uint child_count = getChildCount();
	for (uint i = 0; i < child_count; ++i)
	{
		WindowEventArgs args(this);
		d_children[i]->postSizeChanged();
	}
}

void Window::onChildAdded(WindowEventArgs& e)
{
    
    
    System::getSingleton().signalRedraw();
	fireEvent(EventChildAdded, e, EventNamespace);
}


void Window::onChildRemoved(WindowEventArgs& e)
{
    
    
    System::getSingleton().signalRedraw();
	fireEvent(EventChildRemoved, e, EventNamespace);
}


void Window::onMouseEnters(MouseEventArgs& e)
{
	
	MouseCursor::getSingleton().setImage(getMouseCursor());

    
    Tooltip* tip = getTooltip();
    if (tip)
    {
        tip->setTargetWindow(this);
    }


	fireEvent(EventMouseEnters, e, EventNamespace);
}


void Window::onMouseLeaves(MouseEventArgs& e)
{
    
    Tooltip* tip = getTooltip();
    if (tip)
    {
        tip->setTargetWindow(0);
    }


    fireEvent(EventMouseLeaves, e, EventNamespace);
}


void Window::onMouseMove(MouseEventArgs& e)
{
    
    Tooltip* tip = getTooltip();
    if (tip)
    {
        tip->resetTimer();
    }

    fireEvent(EventMouseMove, e, EventNamespace);
}


void Window::onMouseWheel(MouseEventArgs& e)
{
	fireEvent(EventMouseWheel, e, EventNamespace);
}


void Window::onMouseButtonDown(MouseEventArgs& e)
{
    
	UI_TRY
    Tooltip* tip = getTooltip();
    if (tip)
    {
        tip->setTargetWindow(0);
    }
	UI_CATCH( "setTargetWindow --Window::onMouseButtonDown" )


 	UI_TRY
	if (e.button == LeftButton || e.button == RightButton)
	{
		doRiseOnClick();
	}
	UI_CATCH( "doRiseOnClick --Window::onMouseButtonDown" )

    
    
    
    if (d_autoRepeat && d_repeatButton != e.button)
    {
        d_repeatButton = e.button;
        d_repeatElapsed = 0;
        d_repeating = false;
    }
 	UI_TRY
	if( e.button == LeftButton )
		fireEvent( EventMouseLButtonDown, e, EventNamespace );
	else if( e.button == RightButton )
		fireEvent( EventMouseRButtonDown, e, EventNamespace );

	fireEvent(EventMouseButtonDown, e, EventNamespace);
	UI_CATCH( "fireEvent --Window::onMouseButtonDown" )
}


void Window::onMouseButtonUp(MouseEventArgs& e)
{
    
    d_repeatButton = NoButton;

	fireEvent(EventMouseButtonUp, e, EventNamespace);
}


void Window::onMouseClicked(MouseEventArgs& e)
{
	if( e.button == LeftButton )
		fireEvent(EventMouseLClick, e, EventNamespace);
	else if( e.button == RightButton )
		fireEvent(EventMouseRClick, e, EventNamespace);
	fireEvent(EventMouseClick, e, EventNamespace);
}


void Window::onMouseDoubleClicked(MouseEventArgs& e)
{
	if(e.button == LeftButton)
		fireEvent(EventMouseDoubleClick, e, EventNamespace);
}


void Window::onMouseTripleClicked(MouseEventArgs& e)
{
	fireEvent(EventMouseTripleClick, e, EventNamespace);
}

void Window::onMouseMultiDown(MouseEventArgs& e)
{
	fireEvent(EventMouseMultiDown, e, EventNamespace);
}

void Window::onKeyDown(KeyEventArgs& e)
{
	fireEvent(EventKeyDown, e, EventNamespace);
}


void Window::onKeyUp(KeyEventArgs& e)
{
	fireEvent(EventKeyUp, e, EventNamespace);
}


void Window::onCharacter(KeyEventArgs& e)
{
	fireEvent(EventCharacterKey, e, EventNamespace);
}

void Window::onDragDropItemEnters(DragDropEventArgs& e)
{
    fireEvent(EventDragDropItemEnters, e, EventNamespace);
}

void Window::onDragDropItemLeaves(DragDropEventArgs& e)
{
    fireEvent(EventDragDropItemLeaves, e, EventNamespace);
}

void Window::onDragDropItemDropped(DragDropEventArgs& e)
{
    fireEvent(EventDragDropItemDropped, e, EventNamespace);
}

void Window::onVerticalAlignmentChanged(WindowEventArgs& e)
{
    fireEvent(EventVerticalAlignmentChanged, e, EventNamespace);
}

void Window::onHorizontalAlignmentChanged(WindowEventArgs& e)
{
    fireEvent(EventHorizontalAlignmentChanged, e, EventNamespace);
}

Size Window::getRenderSize()
{
	Size size = getAbsoluteSize();
	return size;
}

bool Window::setCacheRenderInfo( const QuadInfo* pInfo )
{
	if( d_recalculation )
		return false;

	if( d_validSize < 0 )
		return false;

	if( (int)d_renderInfo.size() <= d_validSize )
	{
		d_renderInfo.push_back(*pInfo);
	}
	else
	{
		d_renderInfo[d_validSize] = *pInfo;
	}

	++d_validSize;

	return true;
}

bool Window::getCacheRenderInfo()const
{
	if( d_recalculation )
		return false;

	if( d_renderInfo.size() <= 0 )
		return false;

	for( int i = 0; i < d_validSize; ++i )
	{
		d_renderInfo[i].texture->getTexture()->getRenderer()->addQuad( (void*)&d_renderInfo[i] );
	}

	return true;
}

bool Window::updatePositionChanged()
{
	if( d_recalculation )
		return false;

	d_needsRedraw = true;

	return true;
}

bool Window::doHyperLinkByMouseLeft(const Point& position)
{
	if( d_recalculation )
		return false;

	String str = getHyperLinkContex(&position);
	if( str.empty() )
		return false;
	
	HyperLinkEventArgs e(getName(), str);
	HyperLinkManager::getSingleton().onHyperLinkLeftActive(e);

	return true;
}

bool Window::doHyperLinkByMouseRight(const Point& position)
{
	if( d_recalculation )
		return false;

	String str = getHyperLinkContex(&position);
	if( str.empty() )
		return false;

	HyperLinkEventArgs e(getName(), str);
	HyperLinkManager::getSingleton().onHyperLinkRightActive(e);

	return true;
}

void Window::clearAnimateRenderData()
{
	AnimateRuntimeMap::iterator ani;
	while( !d_animateRuntime.empty() )
	{
		ani = d_animateRuntime.begin();
		delete ani->second;
		d_animateRuntime.erase(ani);
	}
	d_animateRuntime.clear();
}

void Window::clearFontRenderData()
{
	FontRuntimeMap::iterator font;
	while( !d_fontRuntime.empty() )
	{
		font = d_fontRuntime.begin();
		delete font->second;
		d_fontRuntime.erase(font);
	}
	d_fontRuntime.clear();
}

void Window::clearHyperLinkRenderData()
{
	HyperLinkRuntimeMap::iterator link;
	while( !d_hyperlinkRuntime.empty() )
	{
		link = d_hyperlinkRuntime.begin();
		delete link->second;
		d_hyperlinkRuntime.erase(link);
	}
	d_hyperlinkRuntime.clear();
}

void Window::setHyperLinkColorDefault(DWORD dwDefaultColor)
{
	if(!d_pHyperLinkColor)
		d_pHyperLinkColor = new DWORD[2];
	d_pHyperLinkColor[0] = dwDefaultColor;
}
void Window::setHyperLinkColorActive(DWORD dwActiveColor)
{
	if(!d_pHyperLinkColor)
		d_pHyperLinkColor = new DWORD[2];
	d_pHyperLinkColor[1] = dwActiveColor;
}
DWORD Window::getHyperLinkColorDefault() const 
{
	if(d_pHyperLinkColor) 
		return d_pHyperLinkColor[0];
	else
	{
		Window* pParent = getParent();
		if(pParent)
			return pParent->getHyperLinkColorDefault();
		else
			return Window::ds_dwHyperLinkColorDefault;
} 
}
DWORD Window::getHyperLinkColorActive() const 
{
	if(d_pHyperLinkColor) 
		return d_pHyperLinkColor[1];
	else
	{
		Window* pParent = getParent();
		if(pParent)
			return pParent->getHyperLinkColorActive();
		else
			return Window::ds_dwHyperLinkColorActive;
	}
}
} 
