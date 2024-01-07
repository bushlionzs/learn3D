#include "KLTextChatHistory.h"
#include "CEGUIExceptions.h"
#include "CEGUIWindowManager.h"
#include "elements/CEGUIPushButton.h"
#include "elements/CEGUIScrollbar.h"
#include "falagard/CEGUIFalWidgetLookManager.h"
#include "falagard/CEGUIFalWidgetLookFeel.h"
#include "KLTextChatBoard.h"


namespace CEGUI
{
	const utf8 KLTextChatHistory::ParentWindow::WidgetTypeName[] = "Falagard/TextChatHistory/ParentWindow";

	const String KLTextChatHistory::EventNamespace("KLTextChatHistory");
	const String KLTextChatHistory::EventParentMouseEnters( (utf8*)"ParentMouseEnter" );
	const String KLTextChatHistory::EventParentMouseLeaves( (utf8*)"ParentMouseLeave" );


	KLTextChatHistory::ParentWindow::ParentWindow(const String& type, const String& name) :
        Window(type, name)
	{
	}

	KLTextChatHistory::ParentWindow::~ParentWindow()
    {
    }

	Window* KLTextChatHistory::ParentWindowFactory::createWindow(const String& name)
    {
		return new KLTextChatHistory::ParentWindow(d_type, name);
    }

	void KLTextChatHistory::ParentWindowFactory::destroyWindow(Window* window)
    {
		delete window;
    }	
	
	
	
	
	
    const utf8  KLTextChatHistory::WidgetTypeName[] = "Falagard/TextChatHistory";

	KLTextChatHistoryProperties::ChatBoardNumber		KLTextChatHistory::d_chatBoardNumProperty;
	KLTextChatHistoryProperties::FadeEnabled			KLTextChatHistory::d_FadeEnabledProperty;

    KLTextChatHistory::KLTextChatHistory(const String& type, const String& name) :
        Window(type, name), 
		d_parentWindow(0),
		d_vertScrollbar(0),
		d_totalHeight(0),
		d_chatBoardNum(3),
		d_first(true),
		d_extendHeight(0),
		d_fadeShowTime(0.0f),
		d_fadeEnabled(false),
		d_startOffsetY(0),  
		d_currentOffsetY(0) 

    {
        addChatHistoryProperties();
    }

    KLTextChatHistory::~KLTextChatHistory()
    {
    }

	void KLTextChatHistory::addChatHistoryProperties(void)
    {
		CEGUI_START_ADD_STATICPROPERTY( KLTextChatHistory )
			CEGUI_ADD_STATICPROPERTY( &d_chatBoardNumProperty );
			CEGUI_ADD_STATICPROPERTY( &d_FadeEnabledProperty );
		CEGUI_END_ADD_STATICPROPERTY
	}

	void KLTextChatHistory::initialise(void)
	{
		
		d_parentWindow = static_cast<ParentWindow*>(WindowManager::getSingleton().getWindow(getName() + "__auto_parent__"));
		if( d_parentWindow )
		{
			d_parentWindow->subscribeEvent( Window::EventMouseEnters, Event::Subscriber(&CEGUI::KLTextChatHistory::ParentMouseEnters, this));
			d_parentWindow->subscribeEvent( Window::EventMouseLeaves, Event::Subscriber(&CEGUI::KLTextChatHistory::ParentMouseLeaves, this) );
		}
		d_vertScrollbar = static_cast<Scrollbar*>(WindowManager::getSingleton().getWindow(getName() + "__auto_vscrollbar__"));
		d_toEnd = static_cast<PushButton*>(WindowManager::getSingleton().getWindow(getName() + "__auto_toend_btn__"));

		
		
		
		


		d_vertScrollbar->show();
		d_toEnd->show();

		d_parentWindow->setChatHistoryWindow(this);

		addChildWindow(d_vertScrollbar);
		addChildWindow(d_toEnd);

		
		performChildWindowLayout();
		
		performWindowLayout();

		

		d_vertScrollbar->setScrollPosition(0);
		d_vertScrollbar->subscribeEvent(Scrollbar::EventScrollPositionChanged, Event::Subscriber(&KLTextChatHistory::handleScrollbarChange, this));
		d_toEnd->subscribeEvent(PushButton::EventMouseButtonDown, Event::Subscriber(&KLTextChatHistory::handleToEndBtnClick, this));
		
	}

	bool KLTextChatHistory::ParentMouseEnters( const EventArgs& e)
	{
		WindowEventArgs arg( ((const WindowEventArgs&) e).window);
		fireEvent(EventParentMouseEnters, arg, EventNamespace);
		return true;
	}

	bool KLTextChatHistory::ParentMouseLeaves( const EventArgs& e)
	{
		WindowEventArgs arg( ((const WindowEventArgs&) e).window);
		fireEvent(EventParentMouseLeaves, arg, EventNamespace);
		return true;
	}

	Rect KLTextChatHistory::getTextRenderArea(void) const
	{
		return d_parentWindow->getPixelRect();
	}

	void KLTextChatHistory::updateSelf(float elapsed)
	{
		if( !d_fadeEnabled )
			return;

		if(d_enableStepShow)
		{
			MouseCursor& mouse = MouseCursor::getSingleton();
			Point position = mouse.getPosition();
			float oldalpha = d_alpha;

			
			if( isHit(position) )
			{
				d_currentStepShowTime = d_stepShowTime;
				d_alpha = 1.0f;

				std::list< KLTextChatBoard* >::iterator it;
				for(it=m_listChatBoard.begin(); it!=m_listChatBoard.end(); it++)
				{
					KLTextChatBoard* child = (KLTextChatBoard*)(*it);
					child->setCurStepShowTime(d_stepShowTime);
					child->setEnableStepShow(true);
					child->setAlpha(1.0f);
				}
				if( d_vertScrollbar )
					d_vertScrollbar->setAlpha(1.0f);
				if( d_toEnd )
					d_toEnd->setAlpha(1.0f);
			}
			
			else
			{
				if(d_alpha != 0.0f)
				{
					d_currentStepShowTime = d_currentStepShowTime - elapsed;
					if(d_currentStepShowTime<=0.0f)
						d_currentStepShowTime = 0.0f;
					if(d_currentStepShowTime>d_stepShowTime)
						d_currentStepShowTime = d_stepShowTime;
					d_alpha = d_currentStepShowTime/d_stepShowTime;

					if( d_vertScrollbar )
						d_vertScrollbar->setAlpha(d_alpha);
					if( d_toEnd )
						d_toEnd->setAlpha(d_alpha);
				}
			}
			
			
			
			
			
		}
	}


	void KLTextChatHistory::setNeedUpdate()
	{
		performWindowLayout();
		requestRedraw();
	}

	
	size_t KLTextChatHistory::insertChatString(const String& strChat)
	{
		
		
		if( m_listChatBoard.size() == 5 )
		{
			d_vertScrollbar->show();
			d_toEnd->show();
		}

		KLTextChatBoard* pWindow = static_cast<KLTextChatBoard*>(WindowManager::getSingleton().createWindow((utf8*)"KylinUI/ChatBoard"));
		if( !pWindow )
			return 0;
		pWindow->subscribeEvent( Window::EventMouseEnters, Event::Subscriber(&CEGUI::KLTextChatHistory::ParentMouseEnters, this));
		pWindow->subscribeEvent( Window::EventMouseLeaves, Event::Subscriber(&CEGUI::KLTextChatHistory::ParentMouseLeaves, this) );
		pWindow->setText(strChat);
		pWindow->setStepShowTime(d_stepShowTime);
		pWindow->setFadeEnabled(d_fadeEnabled);
		pWindow->setInheritsAlpha(false);
		pWindow->show();
		pWindow->setSpecialModal(d_specialModal);

		if( d_mouseMoveHollow )
			pWindow->setMouseMoveHollow(true);

		if( d_mouseLButtonHollow )
			pWindow->setMouseLButtonHollow(true);

		
		
		bool bDelCurShow = false;
		bool bAddCurShow = false;
		

		if(m_listChatBoard.size() == d_chatBoardNum && m_listChatBoard.size() > 0)
		{
			KLTextChatBoard* child = *m_listChatBoard.begin();

			
			
			float fHeight = child->getAbsoluteHeight();
			Point pos = child->getAbsolutePosition();
			if(child->isVisible() && pos.d_y + fHeight > 0.f)
				bDelCurShow = true;
			

			removeChildWindow( child );
			WindowManager::getSingleton().destroyWindow( child );
			m_listChatBoard.erase(m_listChatBoard.begin());

			
			
			d_startOffsetY += fHeight;
			d_currentOffsetY -= d_startOffsetY;
			d_startOffsetY = 0;
			d_totalHeight = d_currentOffsetY;
			configureScrollbars();
			if(bDelCurShow)
				d_vertScrollbar->setScrollPosition(0.f);
			

		}

		d_parentWindow->addChildWindow(pWindow);
		m_listChatBoard.push_back(pWindow);

		
		
		bAddCurShow = UpdateAddNewWindow();
		
		
		if(bDelCurShow || bAddCurShow)
			Layout();
		

		
		

		
		
		
		
		
		
		
		

		
		
		
		
		
		
		
		

		
		
		
		
		
		
		
		

		
		

		return m_listChatBoard.size();
	}

	 Window *KLTextChatHistory::getChatBoard(const size_t index)
	 {
		 if(index < m_listChatBoard.size())

		 {
			 std::list< KLTextChatBoard* >::iterator it = m_listChatBoard.begin();
			 std::advance(it,index);
			 return (*it);
		 }
		 return 0;
	 }
	void KLTextChatHistory::onMouseEnters(MouseEventArgs& e)
	{

	}

	void KLTextChatHistory::setSpecialModal(bool spModual)
	{
		d_specialModal = spModual;

		if( d_parentWindow )
			d_parentWindow->setSpecialModal(spModual);

		if( d_vertScrollbar )
			d_vertScrollbar->setSpecialModal(spModual);

		if( d_toEnd )
			d_toEnd->setSpecialModal(spModual);
	}

	bool KLTextChatHistory::updatePositionChanged()
	{
		
		
		requestRedraw();
		return true;
	}

	
	void KLTextChatHistory::removeAllChatStrings()
	{
		std::list< KLTextChatBoard* >::iterator it = m_listChatBoard.begin();
		while( it != m_listChatBoard.end() )
		{
			KLTextChatBoard* child = *it;
			removeChildWindow( child );
			WindowManager::getSingleton().destroyWindow( child );
			m_listChatBoard.erase(it);

			it = m_listChatBoard.begin();
		}

		m_listChatBoard.clear();
		d_extendHeight = 0.0f;

		performWindowLayout();

		d_first = false;
	}

	
	void KLTextChatHistory::extendClearRegion()
	{
		if(m_listChatBoard.empty())
		{
			d_extendHeight = 0.0f;
			return;
		}

		
		scrollToEnd();

		Rect absarea(getTextRenderArea());
		d_extendHeight = absarea.getHeight();	

		performWindowLayout();
		
		d_vertScrollbar->setScrollPosition(
			d_vertScrollbar->getDocumentSize()-d_vertScrollbar->getPageSize()+d_extendHeight);
	}

	
	void KLTextChatHistory::scrollToEnd()
	{
		d_extendHeight = 0.0f;
		performWindowLayout();
		
		d_vertScrollbar->setScrollPosition(
			d_vertScrollbar->getDocumentSize()-d_vertScrollbar->getPageSize());
	}

	
	
	SCB_POS_STATE KLTextChatHistory::GetScbPosState()
	{
		if(!d_vertScrollbar) return SPS_NONE;
		Rect absarea(getTextRenderArea());
		float fTolerance = 0; 
		float totalHeight = d_vertScrollbar->getDocumentSize();
		float scbPos      = d_vertScrollbar->getScrollPosition();
		if(scbPos + absarea.getSize().d_height >= totalHeight - fTolerance)
			return SPS_END;
		else if(scbPos - fTolerance <= 0)
			return SPS_TOP;
		else
			return SPS_MIDDLE;
	}

	
	bool KLTextChatHistory::UpdateAddNewWindow()
	{
		if(m_listChatBoard.size() == 0) return false;

		bool bAddCurShow = false;
		Rect absarea(getTextRenderArea());

		SCB_POS_STATE oldsps = GetScbPosState();

		std::list< KLTextChatBoard* >::reverse_iterator it = m_listChatBoard.rbegin();
		KLTextChatBoard* pLast = (*it);

		float childHeight = pLast->resizeSelf(absarea.getWidth());
		pLast->setSize(Absolute, Size(absarea.getWidth(), childHeight));
		pLast->setVisible(false);

		d_currentOffsetY += childHeight;
		d_totalHeight = d_currentOffsetY - d_startOffsetY;

		d_vertScrollbar->setDocumentSize(d_totalHeight);
		if(oldsps == SPS_END)
		{
			d_vertScrollbar->setScrollPosition(d_vertScrollbar->getDocumentSize() - absarea.getSize().d_height);
			d_vertScrollbar->requestRedraw();
			bAddCurShow = true;
		}

		configureScrollbars();
		return bAddCurShow;
	}

	void KLTextChatHistory::validateScbRange()
	{
		Rect absarea(getTextRenderArea());
		if(d_vertScrollbar->getAbsolutePosition().d_y + absarea.getSize().d_height > d_vertScrollbar->getDocumentSize())
			d_vertScrollbar->setScrollPosition(d_vertScrollbar->getDocumentSize() - absarea.getSize().d_height);
		Layout();
	}

	
	void KLTextChatHistory::Layout()
	{
		if(!d_vertScrollbar)
			return;

		Rect absarea(getTextRenderArea());
		float fHeight = 0.f;
		float fHeightOffset;

		float totalHeight = d_vertScrollbar->getDocumentSize();
		float scbPos = d_vertScrollbar->getScrollPosition();

		
		SCB_POS_STATE sps = GetScbPosState();
		if(sps == SPS_NONE)
		{
		}
		else if(sps == SPS_END)
		{
			fHeightOffset = absarea.getSize().d_height;

			std::list< KLTextChatBoard* >::reverse_iterator it = m_listChatBoard.rbegin();
			while(it != m_listChatBoard.rend())
			{
				KLTextChatBoard* p = (*it);

				float fHeight = p->getAbsoluteSize().d_height;
				fHeightOffset -= fHeight;

				if( fHeightOffset + fHeight < 0.0f )
				{
					p->setVisible(false);
					p->setNeedRealTimeUpdate(false);
				}
				else
				{
					p->setPosition(Absolute, Point(0.0f, fHeightOffset) );
					p->setVisible(true);
					p->setNeedRealTimeUpdate(true);
					p->requestRedraw();
				}

				++it;
			}
		}
		
		else if(sps == SPS_TOP)
		{
			fHeightOffset = -scbPos;

			std::list< KLTextChatBoard* >::iterator it = m_listChatBoard.begin();
			while(it != m_listChatBoard.end())
			{
				KLTextChatBoard* p = (*it);

				float fHeight = p->getAbsoluteSize().d_height;
				if(fHeightOffset + fHeight < 0.0f || fHeightOffset > absarea.getSize().d_height)
				{
					p->setVisible(false);
					p->setNeedRealTimeUpdate(false);
				}
				else
				{
					p->setPosition(Absolute, Point(0.0f, fHeightOffset) );
					p->setVisible(true);
					p->setNeedRealTimeUpdate(true);
					p->requestRedraw();
				}

				fHeightOffset += fHeight;
				++it;
			}
		}
		
		else
		{
			float offsetY = -d_vertScrollbar->getScrollPosition();
			std::list< KLTextChatBoard* >::iterator it = 	m_listChatBoard.begin();
			while(it != m_listChatBoard.end())
			{
				KLTextChatBoard* p = (*it);

				float fHeight = p->getAbsoluteSize().d_height;
				if(offsetY + fHeight < 0.f || offsetY > absarea.getHeight())
				{
					p->setVisible(false);
					p->setNeedRealTimeUpdate(false);
					offsetY += fHeight;
					++it;
					continue;
				}

				p->setVisible(true);
				p->setNeedRealTimeUpdate(true);
				p->setPosition( Absolute, Point(0.0f, offsetY) );
				p->requestRedraw();

				offsetY += fHeight;

				++it;
			}

		}
	}
	
	
	bool KLTextChatHistory::handleScrollbarChange(const EventArgs& e)
	{
		
		
		
		
		Layout();
		

		requestRedraw();
		d_parentWindow->requestRedraw();
		return true;
	}
	void KLTextChatHistory::onSized(WindowEventArgs& e)
	{
		Window::onSized(e);

		performWindowLayout();

		
		
		validateScbRange();
		

		requestRedraw();
	}

	
	void KLTextChatHistory::performWindowLayout(void)
	{
		Rect absarea(getTextRenderArea());

		std::list< KLTextChatBoard* >::iterator it;
		float fHeightNow = 0.0f;

		for(it=m_listChatBoard.begin(); it!=m_listChatBoard.end(); it++)
		{
			KLTextChatBoard& child = *(*it);
			
			float childHeight = child.resizeSelf(absarea.getWidth());

			child.setSize(Absolute, Size(absarea.getWidth(), childHeight));

			float childHeightTmp = fHeightNow - d_vertScrollbar->getScrollPosition();
			child.setPosition( Absolute, Point(0.0f, childHeightTmp) );
			if( childHeightTmp < 0.0f && (-childHeightTmp) >= childHeight )
				child.setNeedRealTimeUpdate(false);
			else
				child.setNeedRealTimeUpdate(true);
			child.requestRedraw();

			fHeightNow += childHeight;
		}

		d_totalHeight = fHeightNow + d_extendHeight;

		configureScrollbars();

		
		d_startOffsetY = 0;
		d_currentOffsetY = fHeightNow;
	}

	void KLTextChatHistory::configureScrollbars()
	{
		
		if(!d_vertScrollbar) return;

		Rect initialArea(getTextRenderArea());

		
		
		
		Rect renderArea(getTextRenderArea());

		d_vertScrollbar->setDocumentSize(d_totalHeight);
		d_vertScrollbar->setPageSize(renderArea.getHeight());
		d_vertScrollbar->setStepSize(ceguimax(1.0f, renderArea.getHeight() / 10.0f));
		d_vertScrollbar->setScrollPosition(d_vertScrollbar->getScrollPosition());

		requestRedraw();
		d_parentWindow->requestRedraw();
	}



	
	bool KLTextChatHistory::handleToEndBtnClick(const EventArgs& e)
	{
		scrollToEnd();
		return true;
	}

	void KLTextChatHistory::onMouseWheel(MouseEventArgs& e)
	{
		if(d_vertScrollbar)
		{
			d_vertScrollbar->onMouseWheel(e);
		}
	}

	void KLTextChatHistory::setMouseHollow( bool mousehollow )
	{
		d_mouseHollow = mousehollow;

		if( d_parentWindow )
			d_parentWindow->setMouseHollow(mousehollow);
	}
	void KLTextChatHistory::setMouseMoveHollow( bool mousehollow )
	{
		d_mouseMoveHollow = mousehollow;

		if( d_parentWindow )
			d_parentWindow->setMouseMoveHollow(mousehollow);
	}

	void KLTextChatHistory::setMouseLButtonHollow( bool mousehollow )
	{
		d_mouseLButtonHollow = mousehollow;

		if( d_parentWindow )
			d_parentWindow->setMouseLButtonHollow(mousehollow);
	}

	void KLTextChatHistory::setMouseRButtonHollow( bool mousehollow )
	{
		d_mouseRButtonHollow = mousehollow;

		if( d_parentWindow )
			d_parentWindow->setMouseRButtonHollow(mousehollow);
	}
    
    Window* KLTextChatHistoryFactory::createWindow(const String& name)
    {
        return new KLTextChatHistory(d_type, name);
    }

    void KLTextChatHistoryFactory::destroyWindow(Window* window)
    {
		delete window;
    }
}

