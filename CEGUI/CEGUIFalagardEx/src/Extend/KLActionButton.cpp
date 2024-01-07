

#include "KLActionButton.h"
#include "CEGUIKeyImageAnimationManager.h"
#include "CEGUIKeyImageAnimation.h"
#include <CEGUIFontManager.h>
#include <math.h>
#include "ceguiimageset.h"
#include "ceguiwindowmanager.h"
#include "ceguiimagesetmanager.h"

namespace CEGUI
{
    const utf8  KLActionButton::WidgetTypeName[] = "Falagard/ActionButton";
    
    const String KLActionButton::EventNamespace("Falagard/ActionButton");
    const String KLActionButton::EventDragStarted("DragStarted");
    const String KLActionButton::EventDragEnded("DragEnded");
    const String KLActionButton::EventDragPositionChanged("DragPositionChanged");
    const String KLActionButton::EventDragEnabledChanged("DragEnabledChanged");
    const String KLActionButton::EventDragThresholdChanged("DragThresholdChanged");
    const String KLActionButton::EventDragDropTargetChanged("DragDropTargetChanged");
    const String KLActionButton::EventDropItemEnters("DropItemEnters");
    const String KLActionButton::EventDropItemLeaves("DropItemLeaves");
    const String KLActionButton::EventDropItemDropped("DropItemDropped");
	const String KLActionButton::EventRBClicked((utf8*)"RBClicked");

    KLActionButtonProperties::Empty				KLActionButton::d_emptyProperty;
    KLActionButtonProperties::Checked			KLActionButton::d_checkedProperty;
    KLActionButtonProperties::Default			KLActionButton::d_defaultProperty;
	KLActionButtonProperties::Gloom				KLActionButton::d_gloomProperty;
	KLActionButtonProperties::CornerChar		KLActionButton::d_cornerCharProperty;
    KLActionButtonProperties::DraggingEnabled	KLActionButton::d_dragEnabledProperty;
    KLActionButtonProperties::DragThreshold		KLActionButton::d_dragThresholdProperty;
    KLActionButtonProperties::DragAcceptName	KLActionButton::d_dragAcceptNameProperty;

    KLActionButton::KLActionButton(const String& type, const String& name) :
        FalagardButton(type, name),
		d_empty(true),
		d_checked(false),
		d_default(false),
        d_draggingEnabled(false),
        d_leftMouseDown(false),
        d_dragging(false),
        d_dragThreshold(4.0f),
		m_pLogicData(0),
		d_ActiveButton(LeftButton),
		d_DragButton(RightButton),
		d_pCoverImage(0),
		d_showCoverImage(false),
		d_fCoverImageAlpha(0.5f)
    {
        addActionButtonProperties();

		d_animate1.d_animate = 0;

		setClippedByParent(false);
		d_gloom = false;
		setNeedRealTimeUpdate(true);
    }

    KLActionButton::~KLActionButton()
    {
    }

	void KLActionButton::initialise(void)
	{
		FalagardButton::initialise();
		
		setTooltip(0);
	}

	void KLActionButton::addActionButtonProperties(void)
    {
		CEGUI_START_ADD_STATICPROPERTY( KLActionButton )
		   CEGUI_ADD_STATICPROPERTY( &d_emptyProperty );
           CEGUI_ADD_STATICPROPERTY( &d_checkedProperty );
           CEGUI_ADD_STATICPROPERTY( &d_defaultProperty );
		   CEGUI_ADD_STATICPROPERTY( &d_gloomProperty );
		   CEGUI_ADD_STATICPROPERTY( &d_cornerCharProperty  );
		   CEGUI_ADD_STATICPROPERTY( &d_dragEnabledProperty );
           CEGUI_ADD_STATICPROPERTY( &d_dragThresholdProperty );
           CEGUI_ADD_STATICPROPERTY( &d_dragAcceptNameProperty );
		CEGUI_END_ADD_STATICPROPERTY
	}

	void KLActionButton::setAnimate(const String& name, int time_total, float percent)
	{
		int time_now = (int)(System::getSingleton().getCurTimeElapsed()*1000.0f);
		int time_start = (int)(time_now - time_total*percent);

		if(KeyImageAnimationManager::getSingleton().isAnimatePresent(name))
		{
			d_animate1.d_animate = ( KeyImageAnimation*)KeyImageAnimationManager::getSingleton().getAnimate(name);
			d_animate1.d_time_start = time_start;
			d_animate1.d_time_total = time_total;

			d_animate1.d_currentFrame = KeyImageAnimationManager::getSingleton().getAnimate(name)->getFrame(0, time_total);

			if( name == (utf8*)"CoolDown" )
				m_bCoolDown = true;
			else
				m_bCoolDown = false;
			requestRedraw();
		}
	}

	void KLActionButton::cleanAnimate(void)
	{
		d_animate1.d_animate = 0;
		requestRedraw();
	}

	void KLActionButton::drawSelf( float z )
	{
		if (d_needsRedraw  )
		{
			d_renderCache.clearCachedImagery();
			d_needsRedraw = false;
			
			if(isEmpty())
			{
				bool hover = isHovering();
				if((hover || isPushed()) && !isDisabled(true) )
				{
					drawHover(z);
				}
			}
			else
			{
				drawNormal(z);

				if(d_dragging && !isGloom())
				{
					drawPushed(z);
				}
				else
				{
					if (isDisabled(true) || isGloom() )
					{
						drawDisabled(z);
						if (isPushed() || isChecked()) 
						{
							drawPushed(z);
						}
					}
					else
					{
						
						if (isPushed() || isChecked()) 
						{
							drawPushed(z);
						}
						
						if (isHovering() && !isChecked())
						{
							drawHover(z);
						}

						drawAnimate(z);
						
						if(isDefault())
						{
							drawDefault(z);
						}

						if( d_showCoverImage )
						{
							drawCover(z);
						}
					}

					drawCorner(z);
				}
			}
		}

		Window::drawSelf(z);
	}

	void KLActionButton::drawDefault(float z)
	{
        doButtonRender("Defaulted");
	}

	void KLActionButton::drawCorner(float z)
	{
		ColourRect final_cols(colour(1.0f, 1.0f, 0.0f));
		
		if(!d_CornerChar_TopLeft.d_Char.empty())
		{
			d_renderCache.cacheText(this, 
				d_CornerChar_TopLeft.d_Char, getFont(), (TextFormatting)LeftAligned, 
				Rect(2, 2, getAbsoluteSize().d_width, getAbsoluteSize().d_height), 0.0f, final_cols);
		}				
		
		if(!d_CornerChar_TopRight.d_Char.empty())
		{
			d_renderCache.cacheText(this, 
				d_CornerChar_TopRight.d_Char, getFont(), (TextFormatting)RightAligned, 
				Rect(0, 2, getAbsoluteSize().d_width-2, getAbsoluteSize().d_height), 0.0f, final_cols);
		}				
		
		if(!d_CornerChar_BotLeft.d_Char.empty())
		{
			
			float fFontHeight = getFont()->getFontHeight();
			d_renderCache.cacheText(this, 
				d_CornerChar_BotLeft.d_Char, getFont(), (TextFormatting)LeftAligned, 
				Rect(2, getAbsoluteSize().d_height-fFontHeight-2, getAbsoluteSize().d_width, getAbsoluteSize().d_height), 0.0f, final_cols);
		}				
		
		if(!d_CornerChar_BotRight.d_Char.empty())
		{
			
			float fFontHeight = getFont()->getFontHeight();
			char* p = (char*)d_CornerChar_BotRight.d_Char.c_str();
			d_renderCache.cacheText(this, 
				d_CornerChar_BotRight.d_Char, getFont(), (TextFormatting)RightAligned, 
				Rect(0, getAbsoluteSize().d_height-fFontHeight-2, getAbsoluteSize().d_width-2, getAbsoluteSize().d_height), 0.0f, final_cols);
		}
	}

	void KLActionButton::drawAnimate(float z)
	{
		if(!d_animate1.d_animate || !d_animate1.d_currentFrame) return;
		
		ColourRect color(colour( 1.0f, 1.0f, 0 ));

		color.setAlpha( d_animate1.d_alpha );
		d_renderCache.cacheImage(*(d_animate1.d_currentFrame),
			Rect(0, 0, getAbsoluteSize().d_width, getAbsoluteSize().d_height), 0, color);
	}

	void KLActionButton::drawCover(float z)
	{
		if(!d_showCoverImage || !d_pCoverImage) return;
		
		ColourRect color(colour( 1.0f, 1.0f, 1.0f ));

		color.setAlpha( d_fCoverImageAlpha );
		d_renderCache.cacheImage(*d_pCoverImage,	Rect(0, 0, getAbsoluteSize().d_width, getAbsoluteSize().d_height), 0, color);
	}

    bool KLActionButton::isDraggingThresholdExceeded(const Point& local_mouse)
    {
        float	deltaX = fabsf(local_mouse.d_x - d_dragPoint.d_x);
        float	deltaY = fabsf(local_mouse.d_y - d_dragPoint.d_y);
        
        return (deltaX > d_dragThreshold || deltaY > d_dragThreshold) ? true : false;
    }

	void KLActionButton::updateAnimate(ANIMATE& animate)
	{
		if(!animate.d_animate) return;

		int time_now = (int)(System::getSingleton().getCurTimeElapsed()*1000.0f);

		const Image* pFrame = animate.d_animate->getFrame( time_now-animate.d_time_start, animate.d_time_total );
	
		animate.d_currentFrame = pFrame;
		animate.d_alpha = animate.d_animate->getFrameAlpha( time_now-animate.d_time_start, animate.d_time_total );
		requestRedraw();
		if( pFrame == NULL )
		{
			if( m_bCoolDown ) 
			{
				setAnimate( "CoolDownEnd", -1, 0 );
				animate.d_alpha = 0;
			}
		}
	}

	void KLActionButton::updateSelf(float elapsed)
	{
		updateAnimate(d_animate1);
	}

    void KLActionButton::onMouseButtonDown(MouseEventArgs& e)
    {
		Window::onMouseButtonDown(e);

		if (e.button == LeftButton || e.button == RightButton)
		{
			if (captureInput())
			{
				d_pushed = true;
				updateInternalState(e.position);
				requestRedraw();
			}

			
			e.handled = true;
		}

        if (e.button == LeftButton && isDraggingEnabled())
        {
			if(!d_dragging)
			{
				
				Point localPos = (getMetricsMode() == Relative) ? 
					relativeToAbsolute(screenToWindow(e.position)) :
					screenToWindow(e.position);

				
				d_dragPoint = localPos;
				d_leftMouseDown = true;

			}

			e.handled = true;
        }

		if (e.button == RightButton && isDraggingEnabled())
        {
			e.handled = true;
        }
    }

	void KLActionButton::notifyDragingEnd(void)
	{
		d_dragging = false;
		d_leftMouseDown = false;
		WindowEventArgs args(this);
		fireEvent(EventDragEnded, args, EventNamespace);
		
		requestRedraw();
	}

	void KLActionButton::notifyDragDrop_Droped(KLActionButton* pBtn)
	{

	}

	void KLActionButton::setLogicItemData(void* pData)
	{
		m_pLogicData = pData;
	};


	void* KLActionButton::getLogicItemData(void) const 
	{ 
		return m_pLogicData; 
	}
	void KLActionButton::setCoverImage(const String& imageset, const String& image, float alpha)
	{
		d_pCoverImage = ImagesetManager::getSingleton().getImageset( imageset )->getImage( image );
		d_fCoverImageAlpha = alpha;
	}

	void KLActionButton::setCoverImageShow(bool bshow)
	{
		d_showCoverImage = bshow;
	}

	void KLActionButton::onMouseButtonUp(MouseEventArgs& e)
	{
		if ((e.button == LeftButton) && isPushed())
		{
			Window* sheet = System::getSingleton().getGUISheet();

			if (sheet != NULL)
			{
				if (this == sheet->getChildAtPosition(e.position))
				{
					
					WindowEventArgs args(this);
					onClicked(args);
				}
			}

			e.handled = true;
		}

		if(e.button == RightButton)
		{
			Window* sheet = System::getSingleton().getGUISheet();

			if (sheet != NULL)
			{
				if (this == sheet->getChildAtPosition(e.position))
				{
					
					WindowEventArgs args(this);
					onRBClicked(args);
				}
			}
			
		}

		Window::onMouseButtonUp(e);

		if (e.button == LeftButton || e.button == RightButton)
		{
			releaseInput();
		
			e.handled = true;
		}
        d_leftMouseDown = false;
	}

    void KLActionButton::onMouseMove(MouseEventArgs& e)
    {
		FalagardButton::onMouseMove(e);

		if(isDraggingEnabled() && !d_dragging && !isEmpty())
		{
			Point localMousePos = (getMetricsMode() == Relative) ? 
				relativeToAbsolute(screenToWindow(e.position)) :
				screenToWindow(e.position);
			
			if (d_leftMouseDown)
			{
				if (isDraggingThresholdExceeded(localMousePos))
				{
					
					WindowEventArgs args(this);
					d_dragging = true;
					releaseInput();

					fireEvent(EventDragStarted, e, EventNamespace);
				}
			}
		}
    }

	void KLActionButton::onMouseLeaves(MouseEventArgs& e)
	{
		FalagardButton::onMouseLeaves(e);
		d_leftMouseDown = false;
	}

	void KLActionButton::onClicked(WindowEventArgs& e)
	{
		if(d_dragging) 
			return;

		FalagardButton::onClicked(e);
	}

	void KLActionButton::onRBClicked(WindowEventArgs& e)
	{
		if(d_dragging) 
			return;

		fireEvent(EventRBClicked, e, EventNamespace);
	}

	void KLActionButton::subscribeDragDropStartedEvent(Event::Subscriber subscriber)
	{
		subscribeEvent(EventDragStarted, subscriber);
	}

	void KLActionButton::subscribeMouseEnterEvent(Event::Subscriber subscriber)
	{
		subscribeEvent(EventMouseEnters, subscriber);
	}

	void KLActionButton::subscribeMouseLeaveEvent(Event::Subscriber subscriber)
	{
		subscribeEvent(EventMouseLeaves, subscriber);
	}

	String KLActionButton::getCornerChar(int nPos) const
	{
		switch(nPos)
		{
		case 0: return d_CornerChar_TopLeft.d_Char;
		case 1: return d_CornerChar_TopRight.d_Char;
		case 2: return d_CornerChar_BotLeft.d_Char;
		case 3: return d_CornerChar_BotRight.d_Char;
		default: return "";
		}
	}

	void KLActionButton::setCornerChar(int nPos, const String& strChar, bool isColor)
	{
		String strCharSafe="  ";

		if( !isColor )
		{
			if(strChar.size() > 3)
			{
				strCharSafe += strChar.substr(0, 3);
			}
			else strCharSafe += strChar;
			strCharSafe[0] = 0XFBFFFFFF;
			strCharSafe[1] = 0XFC010101;
		}
		else
		{
			strCharSafe = strChar;
		}

		switch(nPos)
		{
		case 0: d_CornerChar_TopLeft.d_Char		= strCharSafe; break;
		case 1: d_CornerChar_TopRight.d_Char	= strCharSafe; break;
		case 2: d_CornerChar_BotLeft.d_Char		= strCharSafe; break;
		case 3: d_CornerChar_BotRight.d_Char	= strCharSafe; break;
		default: break;
		}

		requestRedraw();
	}

	void KLActionButton::prepareBigchar(void)
	{
		Window::prepareBigchar();

		((Font*)getFont())->prepareString(d_CornerChar_TopLeft.d_Char);
		((Font*)getFont())->prepareString(d_CornerChar_TopRight.d_Char);
		((Font*)getFont())->prepareString(d_CornerChar_BotLeft.d_Char);
		((Font*)getFont())->prepareString(d_CornerChar_BotRight.d_Char);
	}

    
    Window* KLActionButtonFactory::createWindow(const String& name)
    {
        return new KLActionButton(d_type, name);
    }

    void KLActionButtonFactory::destroyWindow(Window* window)
    {
		delete window;
    }
}
