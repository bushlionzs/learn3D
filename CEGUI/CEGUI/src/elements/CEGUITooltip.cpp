

#include "elements/CEGUITooltip.h"
#include "CEGUILogger.h"
#include "CEGUIFont.h"
#include "CEGUIImage.h"
#include "CEGUIWindowManager.h"


namespace CEGUI
{
    
    
    const String Tooltip::EventNamespace("Tooltip");
    const String Tooltip::EventHoverTimeChanged("HoverTimeChanged");
    const String Tooltip::EventDisplayTimeChanged("DisplayTimeChanged");
    const String Tooltip::EventFadeTimeChanged("FadeTimeChanged");
    const String Tooltip::EventTooltipActive("TooltipActive");
    const String Tooltip::EventTooltipInactive("TooltipInactive");
    
    TooltipProperties::HoverTime    Tooltip::d_hoverTimeProperty;
    TooltipProperties::DisplayTime  Tooltip::d_displayTimeProperty;
    TooltipProperties::FadeTime     Tooltip::d_fadeTimeProperty;
    TooltipProperties::MaxWidth     Tooltip::d_maxWidthProperty;
    

    Tooltip::Tooltip(const String& type, const String& name) :
            Window(type, name)
    {
        d_hoverTime     = 0.0f;
        d_displayTime   = 10000.0f;
        d_fadeTime      = 0.1f;
		d_maxWidth		= 210;

        addTooltipProperties();

        setClippedByParent(false);
        setDestroyedByParent(false);
        setAlwaysOnTop(true);

        switchToInactiveState();
		setNeedRealTimeUpdate(true);
    }

    Tooltip::~Tooltip(void)
    {}

    void Tooltip::positionSelf(void)
    {
		UI_TRY
        MouseCursor& cursor = MouseCursor::getSingleton();
        Rect screen(System::getSingleton().getRenderer()->getRect());
        Rect tipRect(getUnclippedPixelRect());
        const Image* mouseImage = cursor.getImage();

        Point mousePos(cursor.getPosition());
        Size mouseSz(0,0);

        if (mouseImage)
        {
            mouseSz = mouseImage->getSize();
        }
		
        
		Point tmpPos(mousePos.d_x + mouseSz.d_width + 32, mousePos.d_y + mouseSz.d_height + 5);
        tipRect.setPosition(tmpPos);

        
        
        if (screen.d_right < tipRect.d_right)
        {
            tmpPos.d_x = mousePos.d_x - tipRect.getWidth() - 5;
        }

        
        
        if (screen.d_bottom < tipRect.d_bottom)
        {
            tmpPos.d_y = mousePos.d_y - tipRect.getHeight() - 5;
        }

        
        setPosition(Absolute, tmpPos);
		UI_CATCH( "positionSelf --Tooltip::positionSelf" )
    }

    void Tooltip::setTargetWindow(Window* wnd)
    {
        if (wnd)
        {
            if (d_target != wnd)
            {
                System::getSingleton().getGUISheet()->addChildWindow(this);
            }

            
            setText(wnd->getTooltipText());

            
            setSize(Absolute, getTextSize());
            positionSelf();
        }

        resetTimer();
        d_target = wnd;
		if (wnd) {
			d_targetName = wnd->getName();			
		}
    }

    const Window* Tooltip::getTargetWindow()
    {
        return d_target;
    }

    Size Tooltip::getTextSize() const
    {
        const Font* fnt = getFont();

        if (fnt && !d_text.empty())
        {
            Rect area(System::getSingleton().getRenderer()->getRect());
			if(area.getWidth() > (float)d_maxWidth) area.d_right = area.d_left + d_maxWidth;

            
            
			Size sz = fnt->getFormattedSize(d_text, area, WordWrapLeftAligned);
            float height = sz.d_height;
            float width = sz.d_width;

            return Size(width, height);
        }
        else
        {
            return Size(0,0);
        }
    }

    void Tooltip::resetTimer(void)
    {
        
        
        if (d_state == Active || d_state == Inactive)
        {
            d_elapsed = 0;
        }
    }

    float Tooltip::getHoverTime(void) const
    {
        return d_hoverTime;
    }

    void Tooltip::setHoverTime(float seconds)
    {
        if (d_hoverTime != seconds)
        {
            d_hoverTime = seconds;

            WindowEventArgs args(this);
            onHoverTimeChanged(args);
        }
    }

    float Tooltip::getDisplayTime(void) const
    {
        return d_displayTime;
    }

    void Tooltip::setDisplayTime(float seconds)
    {
        if (d_displayTime != seconds)
        {
            d_displayTime = seconds;

            WindowEventArgs args(this);
            onDisplayTimeChanged(args);
        }
    }

    float Tooltip::getFadeTime(void) const
    {
        return d_fadeTime;
    }

    void Tooltip::setFadeTime(float seconds)
    {
        if (d_fadeTime != seconds)
        {
            d_fadeTime = seconds;

            WindowEventArgs args(this);
            onFadeTimeChanged(args);
        }
    }

    void Tooltip::doActiveState(float elapsed)
    {
        
        if (!d_target || d_target->getTooltipText().empty())
        {
            switchToInactiveState();
        }
        
        else if ((d_displayTime > 0) && ((d_elapsed += elapsed) >= d_displayTime))
        {
            
            switchToFadeOutState();
        }
    }

    void Tooltip::doInactiveState(float elapsed)
    {
        UI_TRY

		if (!d_target)
			return ;

		if (d_target)
		{
			if (!CEGUI::WindowManager::getSingleton().isWindowPresent(d_targetName))
			{
				d_target = 0;
				return;
			}
			else
			{
				d_target = CEGUI::WindowManager::getSingleton().getWindow(d_targetName);
				if (IsBadCodePtr(FARPROC(d_target)))
				{
					d_target = 0;
					return;
				}
			}
		}

		if(d_target->getTooltipText().empty())
			return ;
		UI_CATCH( "doInactiveState--1 --Tooltip::doInactiveState" )

		UI_TRY
		if(((d_elapsed += elapsed) >= d_hoverTime))
        {
            switchToFadeInState();
        }
		UI_CATCH( "doInactiveState--2 --Tooltip::doInactiveState" )
    }

    void Tooltip::doFadeInState(float elapsed)
    {
 		UI_TRY
		
        if (!d_target || d_target->getTooltipText().empty())
        {
            switchToInactiveState();
        }
        else
        {
            if ((d_elapsed += elapsed) >= d_fadeTime)
            {
                setAlpha(1.0f);
                switchToActiveState();
            }
            else
            {
                setAlpha((1.0f / d_fadeTime) * d_elapsed);
            }
        }
 		UI_CATCH( "doFadeInState --Tooltip::doFadeInState" )
   }

    void Tooltip::doFadeOutState(float elapsed)
    {
  		UI_TRY
       
        if (!d_target || d_target->getTooltipText().empty())
        {
            switchToInactiveState();
        }
        else
        {
            if ((d_elapsed += elapsed) >= d_fadeTime)
            {
                setAlpha(0.0f);
                switchToInactiveState();
            }
            else
            {
                setAlpha(1.0f - (1.0f / d_fadeTime) * d_elapsed);
            }
        }
 		UI_CATCH( "doFadeOutState --Tooltip::doFadeOutState" )
    }

    void Tooltip::switchToInactiveState(void)
    {
		UI_TRY
        setAlpha(0.0f);
        d_state = Inactive;
        d_elapsed = 0;

        if (d_parent)
            d_parent->removeChildWindow(this);

        
        WindowEventArgs args(this);
        onTooltipInactive(args);

        d_target = 0;
		d_targetName.clear();
        hide();
		UI_CATCH( "switchToInactiveState --Tooltip::switchToInactiveState" )
    }

    void Tooltip::switchToActiveState(void)
    {
        d_state = Active;
        d_elapsed = 0;
    }

    void Tooltip::switchToFadeInState(void)
    {
		UI_TRY
        positionSelf();
        d_state = FadeIn;
        d_elapsed = 0;
        show();

        
        
        WindowEventArgs args(this);
        onTooltipActive(args);
		UI_CATCH( "switchToFadeInState --Tooltip::switchToFadeInState" )
    }

    void Tooltip::switchToFadeOutState(void)
    {
        d_state = FadeOut;
        d_elapsed = 0;
    }

    void Tooltip::updateSelf(float elapsed)
    {
        
        Window::updateSelf(elapsed);

        
        switch (d_state)
        {
        case Inactive:
            doInactiveState(elapsed);
            break;

        case Active:
            doActiveState(elapsed);
            break;

        case FadeIn:
            doFadeInState(elapsed);
            break;

        case FadeOut:
            doFadeOutState(elapsed);
            break;

        default:
            
            Logger::getSingleton().logEvent("Tooltip (Name: " + getName() + "of Class: " + getType() + ") is in an unknown state.  Switching to Inactive state.", Errors);
            switchToInactiveState();
        }
    }

    void Tooltip::addTooltipProperties(void)
    {
		CEGUI_START_ADD_STATICPROPERTY( Tooltip );
			CEGUI_ADD_STATICPROPERTY( &d_hoverTimeProperty );
			CEGUI_ADD_STATICPROPERTY( &d_displayTimeProperty );
			CEGUI_ADD_STATICPROPERTY( &d_fadeTimeProperty );
			CEGUI_ADD_STATICPROPERTY( &d_maxWidthProperty );
		CEGUI_END_ADD_STATICPROPERTY
	}

    void Tooltip::onMouseEnters(MouseEventArgs& e)
    {
        positionSelf();

        Window::onMouseEnters(e);
    }

    void Tooltip::onTextChanged(WindowEventArgs& e)
    {
        
        Window::onTextChanged(e);

        
        setSize(Absolute, getTextSize());
        positionSelf();

        
        
    }

    void Tooltip::onHoverTimeChanged(WindowEventArgs& e)
    {
        fireEvent(EventHoverTimeChanged, e, EventNamespace);
    }

    void Tooltip::onDisplayTimeChanged(WindowEventArgs& e)
    {
        fireEvent(EventDisplayTimeChanged, e, EventNamespace);
    }

    void Tooltip::onFadeTimeChanged(WindowEventArgs& e)
    {
        fireEvent(EventFadeTimeChanged, e, EventNamespace);
    }

    void Tooltip::onTooltipActive(WindowEventArgs& e)
    {
		UI_TRY
        fireEvent(EventTooltipActive, e, EventNamespace);
		UI_CATCH( "onTooltipActive --Tooltip::onTooltipActive" )
    }

    void Tooltip::onTooltipInactive(WindowEventArgs& e)
    {
        fireEvent(EventTooltipInactive, e, EventNamespace);
    }

} 
