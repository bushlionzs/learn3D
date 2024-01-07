
#include "KLComplexWindowProperties.h"
#include "KLComplexWindow.h"
#include "CEGUIExceptions.h"
#include "CEGUIWindowManager.h"
#include "elements/CEGUIScrollbar.h"
#include "falagard/CEGUIFalWidgetLookManager.h"
#include "falagard/CEGUIFalWidgetLookFeel.h"
#include "FalButton.h"
#include "KLPrizeButton.h"
#include "KLWealth.h"
#include "KLActionButton.h"
#include "CEGUIHyperLinkManager.h"
#include "CEGUIPropertyHelper.h"
#include "OgreCEGUITexture.h"
#include "CEGUIImageset.h"



namespace CEGUI
{
	const utf8 KLComplexWindow::ParentWindow::WidgetTypeName[] = "Falagard/ComplexWindow/ParentWindow";

	KLComplexWindowProperties::ActionButtonSize		KLComplexWindow::d_ActionButtonSizeProperty;

	
	KLComplexWindowProperties::TextColour		KLComplexWindow::d_textColorProperty;
	KLComplexWindowProperties::NormalTextColour		KLComplexWindow::d_optionNormalTextColour;
	KLComplexWindowProperties::HoverTextColour		KLComplexWindow::d_optionHoverTextColour;
	KLComplexWindowProperties::PushedTextColour		KLComplexWindow::d_optionPushedTextColour;

	KLComplexWindowProperties::ActionButtonDistance	KLComplexWindow::d_ActionButtonDistanceProperty;
	KLComplexWindowProperties::TextAniName			KLComplexWindow::d_textAniProperty;
	KLComplexWindowProperties::OptionButtonSize		KLComplexWindow::d_OptionButtonSizeProperty;
	KLComplexWindowProperties::TextFixedValue			KLComplexWindow::d_TextFixedValueProperty;


	Window* KLComplexWindow::ParentWindowFactory::createWindow(const String& name)
    {
		return new KLComplexWindow::ParentWindow(d_type, name);
    }

	void KLComplexWindow::ParentWindowFactory::destroyWindow(Window* window)
    {
		delete window;
    }

	KLComplexWindow::ParentWindow::ParentWindow(const String& type, const String& name) :
        Window(type, name)
	{
		d_pCurHyperLink = NULL;
		d_recalculation = false;
	}

	KLComplexWindow::ParentWindow::~ParentWindow()
    {
    }

	void KLComplexWindow::updateSelf(float elapsed)
	{/*
		if (d_NeedUpdate)
		{
			d_NeedUpdate = false;
			performWindowLayout();
		}*/
		Window::updateSelf(elapsed);
	}

	bool KLComplexWindow::ParentWindow::isMouseHollow( const Point* pPosition ) const
	{
		if( pPosition == NULL )
			return d_mouseHollow;

		CEGUI::String strUtf = getHyperLinkContex( pPosition );

		if( !strUtf.empty() )
			return false;

		return d_mouseHollow;
	}

	bool KLComplexWindow::ParentWindow::isMouseLButtonHollow( const Point* pPosition ) const
	{
		if( pPosition == NULL || d_mouseLButtonHollow == false)
			return d_mouseLButtonHollow;

		CEGUI::String strUtf = getHyperLinkContex( pPosition );

		if( !strUtf.empty() )
			return false;

		return d_mouseLButtonHollow;
	}

	bool KLComplexWindow::ParentWindow::isMouseRButtonHollow( const Point* pPosition ) const
	{
		if( pPosition == NULL )
			return d_mouseRButtonHollow;

		CEGUI::String strUtf = getHyperLinkContex( pPosition );

		if( !strUtf.empty() )
			return false;

		return d_mouseRButtonHollow;
	}

	bool KLComplexWindow::ParentWindow::getCacheRenderInfo()const
	{
		if( d_renderInfo.size() <= 0 )
			return false;

		for( int i = 0; i < d_validSize; ++i )
		{
			if( d_hyperlinkRuntime.size() > 0 )
			{
				
				bool& isHyperLinkActive = (bool&)d_renderInfo[i].isHyperLinkActive;
				if( d_pCurHyperLink && d_pCurHyperLink->isInRange(d_renderInfo[i].runtimeId) )
				{
					isHyperLinkActive = true;
					DWORD& dwHyperLinkActiveColor = (DWORD&)d_renderInfo[i].dwHyperLinkActiveColor;
					dwHyperLinkActiveColor = getHyperLinkColorActive();
				}
				else
				{
					isHyperLinkActive = false;
				}
			}

			d_renderInfo[i].texture->getTexture()->getRenderer()->addQuad( (void*)&d_renderInfo[i] );
		}

		return true;
	}

	bool KLComplexWindow::ParentWindow::setHyperLinkRuntime(int guid, const String name, const Rect hyper_rect)
	{
		HyperLinkRuntimeMap::iterator pos = d_hyperlinkRuntime.find(name);

		if (pos != d_hyperlinkRuntime.end())
		{
			pos->second->addNewRect(this, hyper_rect, guid);
		}
		else
		{
			HyperLink* newHyperLink = new HyperLink;
			newHyperLink->CleanUp();
			newHyperLink->d_name = name;
			newHyperLink->addNewRect(this, hyper_rect, guid);

			d_hyperlinkRuntime.insert( std::make_pair(name, newHyperLink) );
		}

		return false;
	}

	String KLComplexWindow::ParentWindow::getHyperLinkContex(const Point* position)const
	{
		if( d_hyperlinkRuntime.size() <= 0 )
			return "";

		HyperLinkRuntimeMap::const_iterator itCur, itEnd;

		itCur		= d_hyperlinkRuntime.begin();
		itEnd		= d_hyperlinkRuntime.end();

		KLComplexWindow::ParentWindow* pWin = (KLComplexWindow::ParentWindow*)this;

		while( itCur != itEnd )
		{
			HyperLink* nHyperLink = (HyperLink*)itCur->second;

			if( nHyperLink->isInRange(this, CEGUI::Point( position->d_x,  position->d_y)) )
			{
				pWin->d_pCurHyperLink = (HyperLink*)itCur->second;
				if( !(System::getSingleton().getModalTarget() && !getModalState()) )
				{
					int gamecursor = HyperLinkManager::getSingleton().getHyperLinkCursor(nHyperLink->d_name);
					MouseCursor::getSingleton().setGameCursor(gamecursor);
				}
				return nHyperLink->d_name;
			}

			itCur++;
		}

		pWin->d_pCurHyperLink = NULL;
		MouseCursor::getSingleton().setGameCursor(-1);
		return "";
	}

	void    KLComplexWindow::ParentWindow::onMouseLeaves( MouseEventArgs& e )
	{
		d_pCurHyperLink = NULL;
		MouseCursor::getSingleton().setGameCursor(-1);
		Window::onMouseLeaves( e );
	}
	
	void KLComplexWindow::ParentWindow::populateRenderCache()
	{
		d_validSize = 0;
		d_pCurHyperLink = NULL;
		clearHyperLinkRenderData();

		
		Rect absarea(getPixelRect());
		Rect clipper(absarea);

	    ColourRect final_cols(colour(1.0f, 1.0f, 1.0f));

		for(int i=0; i<(int)d_ComplexWindow->d_ChildVector.size(); i++)
		{
			ChildElement* pElement = d_ComplexWindow->d_ChildVector[i];
			const Font* font = pElement->d_Font;

			switch(pElement->d_Type)
			{
			case CT_Text:
				{
					ChildElement_Text* pTextElement = (ChildElement_Text*)pElement;
					Rect textArea(pElement->d_rectClient);
					textArea.d_top -= d_ComplexWindow->d_vertScrollbar->getScrollPosition();

					
					final_cols = d_ComplexWindow->d_textColor;

					d_renderCache.cacheText(this, 
						pTextElement->d_Text, font, (TextFormatting)pTextElement->d_Typeset, textArea, 0.0f, final_cols);
				}
				break;

			case CT_Option:
				{
				}
				break;

			case CT_Item:
				{
				}
				break;
			}
		}
	}
	
	
	
	
	
    const utf8 KLComplexWindow::WidgetTypeName[] = "Falagard/ComplexWindow";

	
	const String KLComplexWindow::EventNamespace("KLComplexWindow");
	const String KLComplexWindow::EventOptionClicked( (utf8*)"OptionClicked" );
	const String KLComplexWindow::EventLinkClicked( (utf8*)"LinkClicked" );
	const String KLComplexWindow::EventRewardItemClicked( (utf8*)"RewardItemClicked" );
	const String KLComplexWindow::EventRewardItemMouseEnter( (utf8*)"RewardItemMouseEnter" );
	const String KLComplexWindow::EventRewardItemMouseLeave( (utf8*)"RewardItemMouseLeave" );

    KLComplexWindow::KLComplexWindow(const String& type, const String& name) :
        Window(type, name), 
		d_ParentWindow(0),
		d_vertScrollbar(0),
		d_enableVertScrollbar(false),
		d_NeedUpdate(false),
		d_totalHeight(0.0f), d_curActionId(-1)
		
		
		,d_textColor(1,1,1,1)
		,d_NormalTextColour(1,1,1,1)
		,d_HoverTextColour(1,1,1,1)
		,d_PushedTextColour(1,1,1,1)
		
    {
		d_textFixedValue = 1.0f;
		CEGUI_START_ADD_STATICPROPERTY( KLComplexWindow )
			CEGUI_ADD_STATICPROPERTY( &d_ActionButtonSizeProperty  );
		
		
		
		CEGUI_ADD_STATICPROPERTY( &d_textColorProperty );
		CEGUI_ADD_STATICPROPERTY( &d_optionNormalTextColour );
		CEGUI_ADD_STATICPROPERTY( &d_optionHoverTextColour );
		CEGUI_ADD_STATICPROPERTY( &d_optionPushedTextColour );
		


		CEGUI_ADD_STATICPROPERTY( &d_ActionButtonDistanceProperty  );
		CEGUI_ADD_STATICPROPERTY( &d_textAniProperty  );
		CEGUI_ADD_STATICPROPERTY( &d_OptionButtonSizeProperty );
			CEGUI_ADD_STATICPROPERTY( &d_TextFixedValueProperty );
		CEGUI_END_ADD_STATICPROPERTY


		d_ActionButtonSize = Size( 0.129293f,0.1236715f );

		d_ActionButtonDistance = Size( 0.0f,0.0f );// Size( 0.129293f,0.1236715f );
		
		d_OptionButtonSize	= Size( 0.909293f,0.10546875f );
		d_recalculation = false;
    }

    KLComplexWindow::~KLComplexWindow()
    {
		_destroyAllElements();
    }

	void KLComplexWindow::initialise(void)
	{
		
		d_ParentWindow = static_cast<ParentWindow*>(WindowManager::getSingleton().getWindow(getName() + "__auto_parent__"));
		d_vertScrollbar = static_cast<Scrollbar*>(WindowManager::getSingleton().getWindow(getName() + "__auto_vscrollbar__"));

		d_ParentWindow->SetComplexWindow(this);
		d_vertScrollbar->hide();

		addChildWindow(d_vertScrollbar);

		performWindowLayout();
		performChildWindowLayout();

		
		d_vertScrollbar->subscribeEvent(Scrollbar::EventScrollPositionChanged, Event::Subscriber(&KLComplexWindow::handleScrollbarChange, this));
	}


	

	
	bool KLComplexWindow::handleScrollbarChange(const EventArgs& e)
	{
		performWindowLayout();
		requestRedraw();
		d_ParentWindow->requestRedraw();
		return true;
	}

	
	bool KLComplexWindow::handleOptionClicked(const EventArgs& e)
	{
		WindowEventArgs arg( ((const WindowEventArgs&) e).window);
		fireEvent(EventOptionClicked, arg, EventNamespace);

		return true;
	}

	void KLComplexWindow::setMouseHollow(bool mousehollow)
	{
		d_mouseHollow = mousehollow;
		d_mouseLButtonHollow = d_mouseRButtonHollow = d_mouseHollow;
		d_ParentWindow->setMouseHollow(mousehollow);
	}

	void	KLComplexWindow::setMouseMoveHollow(bool mousehollow)
	{
		d_mouseMoveHollow = mousehollow;
		d_ParentWindow->setMouseMoveHollow(mousehollow);
	}

	
	void KLComplexWindow::setMouseLButtonHollow(bool mouselbuttonhollow)
	{
		if(!d_mouseHollow)
			d_mouseLButtonHollow = mouselbuttonhollow;
		else
			d_mouseLButtonHollow = d_mouseHollow;
		d_ParentWindow->setMouseLButtonHollow(mouselbuttonhollow);
	}

	
	void KLComplexWindow::setMouseRButtonHollow(bool mouserbuttonhollow)
	{
		if(!d_mouseHollow)
			d_mouseRButtonHollow = mouserbuttonhollow;
		else
			d_mouseRButtonHollow = d_mouseHollow;
		d_ParentWindow->setMouseRButtonHollow(mouserbuttonhollow);
	}

	void KLComplexWindow::onMouseWheel(MouseEventArgs& e)
	{
		if(d_vertScrollbar)
		{
			d_vertScrollbar->onMouseWheel(e);
		}
	}

	
	bool KLComplexWindow::handleLinkClicked(const EventArgs& e)
	{
		WindowEventArgs arg( ((const WindowEventArgs&) e).window);
		fireEvent(EventLinkClicked, arg, EventNamespace);

		return true;
	}

	
	bool KLComplexWindow::handleRewardItemClicked(const EventArgs& e)
	{
		
		
		KLPrizeButton* pRewardItem =  static_cast<KLPrizeButton*>(((const WindowEventArgs&) e).window);
		if(!pRewardItem) return true;
		
		ChildElement_Item* pItemElement = (ChildElement_Item*)pRewardItem->getHelper();
		if(!pItemElement) return true;

		if(!(pItemElement->d_Radio)) return true;

		for(int i=0; i<(int)d_RadioChild.size(); i++)
		{
			if(d_RadioChild[i] == pItemElement) 
				d_RadioChild[i]->d_Button->setChecked(true);
			else
				d_RadioChild[i]->d_Button->setChecked(false);
			d_RadioChild[i]->d_Button->requestRedraw();
		}

		
		
		WindowEventArgs arg( ((const WindowEventArgs&) e).window);
		fireEvent(EventRewardItemClicked, arg, EventNamespace);

		return true;
	}

	bool KLComplexWindow::MouseEnters( const EventArgs& e)
	{
		KLPrizeButton* pRewardItem =  static_cast<KLPrizeButton*>( ((const MouseEventArgs&) e).window );
		if(!pRewardItem) return true;
	
		ChildElement_Item* pItemElement = (ChildElement_Item*)pRewardItem->getHelper();
		if(!pItemElement) return true;
	
		d_curActionId = pItemElement->d_ActionId;

		WindowEventArgs arg( ((const WindowEventArgs&) e).window);
		fireEvent(EventRewardItemMouseEnter, arg, EventNamespace);
		return true;
	}

	bool KLComplexWindow::MouseLeaves( const EventArgs& e)
	{
		KLPrizeButton* pRewardItem =  static_cast<KLPrizeButton*>( ((const MouseEventArgs&) e).window );
		if(!pRewardItem) return true;
	
		ChildElement_Item* pItemElement = (ChildElement_Item*)pRewardItem->getHelper();
		if(!pItemElement) return true;

		d_curActionId = pItemElement->d_ActionId;
	
		WindowEventArgs arg( ((const WindowEventArgs&) e).window);
		fireEvent(EventRewardItemMouseLeave, arg, EventNamespace);
		return true;
	}

	
	void KLComplexWindow::onSized(WindowEventArgs& e)
	{
		Window::onSized(e);

		performWindowLayout();
		requestRedraw();
	}

	Rect KLComplexWindow::getTextRenderArea(void) const
	{
		return d_ParentWindow->getPixelRect();
	}
	void KLComplexWindow::setActionButtonSize( const Size& rect )
	{


		d_ActionButtonSize = rect;

		requestRedraw();
		d_ParentWindow->requestRedraw();
	}

	const Size KLComplexWindow::getActionButtonSize() const 
	{
		return d_ActionButtonSize;
	}
	void KLComplexWindow::setActionButtonDistance( const Size& rect )
	{
		d_ActionButtonDistance = rect;
	}

	const Size KLComplexWindow::getActionButtonDistance() const 
	{
		return d_ActionButtonDistance;
	}

	void KLComplexWindow::setOptionButtonSize( const Size& rect )
	{
		
		
		d_OptionButtonSize = rect;
		
		requestRedraw();
		d_ParentWindow->requestRedraw();
	}

	const Size KLComplexWindow::getOptionButtonSize() const 
	{
		return d_OptionButtonSize;
	}

	int KLComplexWindow::AddChildElement_Text(String strText, Font* font, TextFormatting typeset, bool showImage, bool showButton
		)
	{
		ChildElement_Text* pNewChild = new ChildElement_Text;

		pNewChild->d_Name = (utf8*)"text";
		pNewChild->d_Type = CT_Text;
		pNewChild->d_Text = strText;
		pNewChild->d_Typeset = typeset;
		pNewChild->d_showImage = showImage;
		pNewChild->d_showButton = showButton;
		
	
		if( pNewChild->d_showImage )
		{
			if( pNewChild->d_finishAni == 0 )
			{
				char szTempName[32];
				int nIndex = 0;
				for(int i=0; i<(int)d_ChildVector.size(); i++)
				{
					if( d_ChildVector[i]->d_Type == CT_Text )
					{
						nIndex++;
					}
				}
				_snprintf(szTempName, 32, "_Ani_%02d", nIndex);

				pNewChild->d_finishAni = static_cast<KLKeyImageAnimation*>(WindowManager::getSingleton().createWindow((utf8*)"KylinUI/Animate", getName() + szTempName));
			}
		}

		if( pNewChild->d_finishAni )
		{
			pNewChild->d_finishAni->hide();
			pNewChild->d_finishAni->setNeedRealTimeUpdate(false);
			pNewChild->d_finishAni->SetAnimate(d_textAniString);
			pNewChild->d_finishAni->setMouseHollow(true);
			pNewChild->d_finishAni->setMouseMoveHollow(true);
			d_ParentWindow->addChildWindow(pNewChild->d_finishAni);
		}

		if (pNewChild->d_showButton)
		{
			if (0 == pNewChild->d_Button)
			{
				char szTempName[64] = {0};				
				_snprintf(szTempName, 32, "_InBnt_%02d", pNewChild->d_Index);

				pNewChild->d_Button = static_cast<PushButton*>(WindowManager::getSingleton().createWindow((utf8*)"KylinUI/Button_2", getName() + szTempName));

				if (pNewChild->d_Button)
				{
					pNewChild->d_Button->hide();
					d_ParentWindow->addChildWindow(pNewChild->d_Button);
				}
			}
		}

		if( font ) 
			pNewChild->d_Font = font;
		else 
			pNewChild->d_Font = getFont();

		d_ChildVector.push_back(pNewChild);

		
		//NeedUpdate();
		performWindowLayout();

		return pNewChild->d_Index;
	}

	void KLComplexWindow::AddChildElement_Option(String strText,String strExtra1,String strExtra2, String strText3, Font* font)
	{
		ChildElement_Option* pNewChild = new ChildElement_Option;

		pNewChild->d_Type = CT_Option;
		pNewChild->d_Text = strText;
		if(font) pNewChild->d_Font = font;
		else pNewChild->d_Font = getFont();

		char szTempName[32];
		int nIndex = 0;
		for(int i=0; i<(int)d_ChildVector.size(); i++)
		{
			if(d_ChildVector[i]->d_Name.substr(0, 10) == (utf8*)"__option__")
			{
				nIndex++;
			}
		}

		_snprintf(szTempName, 32, "__option__%02d#%d,%d", nIndex,atoi(strExtra1.c_str()),atoi(strExtra2.c_str()));

		pNewChild->d_Name = (utf8*)szTempName;
		pNewChild->d_State = atoi(strText3.c_str());
		switch( pNewChild->d_State)
		{
			
		case 1:
			pNewChild->d_Button = static_cast<FalagardButton*>(WindowManager::getSingleton().createWindow((utf8*)"KylinUI/QuestButton_1", getName() + szTempName));
			break;
		case 2:
			pNewChild->d_Button = static_cast<FalagardButton*>(WindowManager::getSingleton().createWindow((utf8*)"KylinUI/QuestButton_2", getName() + szTempName));
			break;
		case 3:
			pNewChild->d_Button = static_cast<FalagardButton*>(WindowManager::getSingleton().createWindow((utf8*)"KylinUI/QuestButton_3", getName() + szTempName));
			break;
		case 4:
			pNewChild->d_Button = static_cast<FalagardButton*>(WindowManager::getSingleton().createWindow((utf8*)"KylinUI/QuestButton_4", getName() + szTempName));
			break;
		case 5:
			pNewChild->d_Button = static_cast<FalagardButton*>(WindowManager::getSingleton().createWindow((utf8*)"KylinUI/QuestButton_5", getName() + szTempName));
			break;
		case 6:
			pNewChild->d_Button = static_cast<FalagardButton*>(WindowManager::getSingleton().createWindow((utf8*)"KylinUI/QuestButton_6", getName() + szTempName));
			break;
		case 7:
			pNewChild->d_Button = static_cast<FalagardButton*>(WindowManager::getSingleton().createWindow((utf8*)"KylinUI/QuestButton_7", getName() + szTempName));
			break;
		case 8:
			pNewChild->d_Button = static_cast<FalagardButton*>(WindowManager::getSingleton().createWindow((utf8*)"KylinUI/QuestButton_8", getName() + szTempName));
			break;
		case 9:
			pNewChild->d_Button = static_cast<FalagardButton*>(WindowManager::getSingleton().createWindow((utf8*)"KylinUI/QuestButton_9", getName() + szTempName));
			break;
		case 10:
			pNewChild->d_Button = static_cast<FalagardButton*>(WindowManager::getSingleton().createWindow((utf8*)"KylinUI/QuestButton_10", getName() + szTempName));
			break;
		case 11:
			pNewChild->d_Button = static_cast<FalagardButton*>(WindowManager::getSingleton().createWindow((utf8*)"KylinUI/QuestButton_11", getName() + szTempName));
			break;
		case 12:
			pNewChild->d_Button = static_cast<FalagardButton*>(WindowManager::getSingleton().createWindow((utf8*)"KylinUI/QuestButton_12", getName() + szTempName));
			break;
		case 13:
			pNewChild->d_Button = static_cast<FalagardButton*>(WindowManager::getSingleton().createWindow((utf8*)"KylinUI/QuestButton_13", getName() + szTempName));
			break;
		case 14:
			pNewChild->d_Button = static_cast<FalagardButton*>(WindowManager::getSingleton().createWindow((utf8*)"KylinUI/QuestButton_14", getName() + szTempName));
			break;
		case 15:
			pNewChild->d_Button = static_cast<FalagardButton*>(WindowManager::getSingleton().createWindow((utf8*)"KylinUI/QuestButton_15", getName() + szTempName));
			break;
		case 16:
			pNewChild->d_Button = static_cast<FalagardButton*>(WindowManager::getSingleton().createWindow((utf8*)"KylinUI/QuestButton_16", getName() + szTempName));
			break;
		case 17:
			pNewChild->d_Button = static_cast<FalagardButton*>(WindowManager::getSingleton().createWindow((utf8*)"KylinUI/QuestButton_17", getName() + szTempName));
			break;
		case 18:
			pNewChild->d_Button = static_cast<FalagardButton*>(WindowManager::getSingleton().createWindow((utf8*)"KylinUI/QuestButton_18", getName() + szTempName));
			break;
		case 19:
			pNewChild->d_Button = static_cast<FalagardButton*>(WindowManager::getSingleton().createWindow((utf8*)"KylinUI/QuestButton_19", getName() + szTempName));
			break;
		case 20:
			pNewChild->d_Button = static_cast<FalagardButton*>(WindowManager::getSingleton().createWindow((utf8*)"KylinUI/QuestButton_20", getName() + szTempName));
			break;
		case 21:
			pNewChild->d_Button = static_cast<FalagardButton*>(WindowManager::getSingleton().createWindow((utf8*)"KylinUI/QuestButton_21", getName() + szTempName));
			break;
		default:
			pNewChild->d_Button = static_cast<FalagardButton*>(WindowManager::getSingleton().createWindow((utf8*)"KylinUI/QuestButton_1", getName() + szTempName));
			break;
		}

		if( !pNewChild->d_Button )
			return;

		
		pNewChild->d_Button->setText( strText );

		
		pNewChild->d_Button->setProperty("NormalTextColour", PropertyHelper::colourToString(d_NormalTextColour));
		pNewChild->d_Button->setProperty("HoverTextColour",  PropertyHelper::colourToString(d_HoverTextColour));
		pNewChild->d_Button->setProperty("PushedTextColour", PropertyHelper::colourToString(d_PushedTextColour));



		pNewChild->d_Button->show();
		pNewChild->d_Button->subscribeEvent(PushButton::EventClicked, Event::Subscriber(&KLComplexWindow::handleOptionClicked, this));
		

		
		d_ParentWindow->addChildWindow(pNewChild->d_Button);

		d_ChildVector.push_back(pNewChild);
		
		//NeedUpdate();
		performWindowLayout();
	}


	Window* KLComplexWindow::AddChildElement_Item(String strIconImage, String strText,  bool bRadio, bool bReArrange, Font* font, int ActionID, int nCount, bool isMask )
	{
		ChildElement_Item* pNewChild = new ChildElement_Item;

		pNewChild->d_Type		= CT_Item;
		pNewChild->d_Text		= strText;
		if(font) pNewChild->d_Font = font;
		else pNewChild->d_Font = getFont();

		char szTempName[32];
		int nIndex = 0;

		if(bRadio)
		{
			for(int i=0; i<(int)d_ChildVector.size(); i++)
			{
				if(d_ChildVector[i]->d_Name.substr(0, 16) == (utf8*)"__reward_radio__") nIndex++;
				_snprintf(szTempName, 32, "__reward_radio__%02d", nIndex);
			}
		}
		else
		{
			_snprintf(szTempName, 32, "__reward__%02d", (int)d_ChildVector.size());
		}

		pNewChild->d_Name = (utf8*)szTempName;
		pNewChild->d_ReArrange = bReArrange;
		pNewChild->d_Button = static_cast<KLPrizeButton*>(WindowManager::getSingleton().createWindow((utf8*)"KylinUI/RewardItem", getName() + szTempName));
		pNewChild->d_Button->setProperty("NormalImage", strIconImage);
		
		
		pNewChild->d_Button->show();
		pNewChild->d_Radio = bRadio;
		pNewChild->d_Button->setHelper((void*)pNewChild);
		pNewChild->d_Button->subscribeEvent(PushButton::EventClicked, Event::Subscriber(&KLComplexWindow::handleRewardItemClicked, this));
		pNewChild->d_Button->setMasked(isMask);

		if( ActionID != -1 )
		{
			pNewChild->d_ActionId = ActionID;
			pNewChild->d_Button->subscribeEvent( Window::EventMouseEnters, Event::Subscriber(&CEGUI::KLComplexWindow::MouseEnters, this));
			pNewChild->d_Button->subscribeEvent( Window::EventMouseLeaves, Event::Subscriber(&CEGUI::KLComplexWindow::MouseLeaves, this) );
		}

		if( nCount > 1 )
			pNewChild->d_Button->setCornerChar( PropertyHelper::intToString(nCount) );


		
		d_ParentWindow->addChildWindow(pNewChild->d_Button);

		d_ChildVector.push_back(pNewChild);
		if(bRadio) d_RadioChild.push_back(pNewChild);
		
		//NeedUpdate();
		performWindowLayout();
		return pNewChild->d_Button;
	}

	Window* KLComplexWindow::AddChildElement_Action(String strIconImage, int ActionID, bool bRadio, bool bReArrange, Font* font)
	{
		ChildElement_Action* pNewChild = new ChildElement_Action;

		pNewChild->d_Type		= CT_Action;
		pNewChild->d_Text		= (utf8*)"action";
		if(font) pNewChild->d_Font = font;
		else pNewChild->d_Font = getFont();

		char szTempName[32];
		int nIndex = 0;

		if(bRadio)
		{
			for(int i=0; i<(int)d_ChildVector.size(); i++)
			{
				if(d_ChildVector[i]->d_Name.substr(0, 16) == (utf8*)"__reward_radio__") nIndex++;
				_snprintf(szTempName, 32, "__reward_radio_%02d_%02d", (int)ActionID,nIndex);
			}
		}
		else
		{

			_snprintf(szTempName, 32, "__reward__%02d", (int)ActionID);
		}

		pNewChild->d_Name = (utf8*)szTempName;
		pNewChild->d_ReArrange = bReArrange;
		pNewChild->d_Radio = bRadio;
		pNewChild->d_ActionButton = static_cast<KLActionButton*>(WindowManager::getSingleton().createWindow((utf8*)"KylinUI/ActionButton", getName() + szTempName));
		pNewChild->d_ActionButton->setLogicItemData((void*)(__w64 int)ActionID);
		pNewChild->d_ActionButton->show();
		pNewChild->d_ActionButton->setProperty("ClippedByParent", "True");
		pNewChild->d_ActionButton->setProperty("Empty", "False");
		
		if(!strIconImage.empty())
		{
			pNewChild->d_ActionButton->setProperty("NormalImage", strIconImage);
		}

		
		d_ParentWindow->addChildWindow(pNewChild->d_ActionButton);

		d_ChildVector.push_back(pNewChild);

		
		//NeedUpdate();
		performWindowLayout();
		return pNewChild->d_ActionButton;
	}


	void KLComplexWindow::AddChildElement_HyperLink( String strText,	int nLinkID, bool bReArrange, Font* font)
	{
		ChildElement_HyperLink* pNewChild = new ChildElement_HyperLink;

		pNewChild->d_Type		= CT_HyperLink;
		pNewChild->d_Text		= strText;
		if(font) pNewChild->d_Font = font;
		else pNewChild->d_Font = getFont();

		char szTempName[32];
		int nIndex = 0;

		_snprintf(szTempName, 32, "%d", nLinkID);

		pNewChild->d_Name = (utf8*)szTempName;
		pNewChild->d_ReArrange = bReArrange;
		pNewChild->d_Button = static_cast<FalagardButton*>(WindowManager::getSingleton().createWindow((utf8*)"KylinUI/Button_1", getName() + szTempName));
		pNewChild->d_Button->setText(strText);
		pNewChild->d_Button->show();
		pNewChild->d_Button->subscribeEvent(PushButton::EventClicked, Event::Subscriber(&KLComplexWindow::handleLinkClicked, this));



		
		d_ParentWindow->addChildWindow(pNewChild->d_Button);

		d_ChildVector.push_back(pNewChild);

		
		//NeedUpdate();
		performWindowLayout();
		return ;
	}


	void KLComplexWindow::AddChildElement_Money(int money, Font* font)

	{
		ChildElement_Money* pNewChild = new ChildElement_Money;

		pNewChild->d_Type = CT_Money;
		pNewChild->d_Name = (utf8*)"money";
		if(font) pNewChild->d_Font = font;
		else pNewChild->d_Font = getFont();

		pNewChild->d_Money = static_cast<KLWealth*>(WindowManager::getSingleton().createWindow((utf8*)"KylinUI/Wealth"));
		pNewChild->d_Money->setMoneyNumber(money);
		pNewChild->d_Money->show();

		
		d_ParentWindow->addChildWindow(pNewChild->d_Money);

		d_ChildVector.push_back(pNewChild);
		
		//NeedUpdate();
		performWindowLayout();

	}

	void KLComplexWindow::performWindowLayout(void)
	{
		d_validSize = 0;

        
        const WidgetLookFeel& wlf = WidgetLookManager::getSingleton().getWidgetLook(d_lookName);
        


		Rect absarea(getTextRenderArea());
		
		absarea.setHeight(absarea.getHeight());
		absarea.setWidth((this->getAbsoluteWidth() - d_vertScrollbar->getAbsoluteWidth())*0.95f);
		
		float fHeightNow = 3.0f;
		float fItemPosition = 0.0f;
		float fTextPosition = 0.0f;
		for(int i=0; i<(int)d_ChildVector.size(); i++)
		{
			ChildElement* pElement = d_ChildVector[i];
			const Font* font = pElement->d_Font;

			switch(pElement->d_Type)
			{
			case CT_Text:
				{
					Rect absareaTemp = absarea;
					fItemPosition = 0.0f;
					ChildElement_Text* pTextElement = (ChildElement_Text*)pElement;					

					
					Size buttonSize(0.f, 0.f);
					if (pTextElement->d_showButton && pTextElement->d_Button)
					{
						pTextElement->d_Button->setPosition(Absolute, Point(0.0f, fHeightNow-2 - d_vertScrollbar->getScrollPosition()));
						pTextElement->d_Button->show();
				
						buttonSize = pTextElement->d_Button->getSize(Absolute);

						absareaTemp.d_left += buttonSize.d_width;
					}

					
					Size textSize = font->getFormattedSize(pTextElement->d_Text, absareaTemp, (TextFormatting)pTextElement->d_Typeset);					
					pTextElement->d_rectClient.setPosition(Point(buttonSize.d_width + 1.0f, fHeightNow));
					pTextElement->d_rectClient.setSize(Size(absareaTemp.getWidth(), textSize.d_height));
					
					
					float fTextHeight = textSize.d_height * d_textFixedValue;
					if (fTextHeight >= buttonSize.d_height)
						fHeightNow += fTextHeight;
					else
						fHeightNow += buttonSize.d_height;

					
					if( pTextElement->d_showImage )
					{
						pTextElement->d_finishAni->setPosition( Absolute, 
							Point( buttonSize.d_width, 
							       pTextElement->d_rectClient.getPosition().d_y-4 - d_vertScrollbar->getScrollPosition() ) );
						pTextElement->d_finishAni->setSize(Absolute, Size(absareaTemp.getWidth(), textSize.d_height + 6));
						pTextElement->d_finishAni->show();
						pTextElement->d_finishAni->setNeedRealTimeUpdate(true);
						((KLKeyImageAnimation*)pTextElement->d_finishAni)->Play(true);
					}
				}
				break;

			case CT_Option:
				{
					fItemPosition = 0.0f;
					fTextPosition = 0.0f;
					ChildElement_Option* pOptionElement = (ChildElement_Option*)pElement;
					if(i > 0)
					{
						ChildElement* pElement_Before = d_ChildVector[i-1];

						if( pElement_Before && pElement_Before->d_Type != CT_Option )
							fHeightNow += font->getLineSpacing() * 2.0f;
					}

					float textHeight = font->getLineSpacing()*1.7f;

					pOptionElement->d_rectClient.setPosition(Point(0.0f, fHeightNow));
					
					pOptionElement->d_rectClient.setSize(Size(absarea.getWidth(), absarea.getWidth() * d_OptionButtonSize.d_height));

					pOptionElement->d_Button->setPosition(Absolute, Point(0.0f, fHeightNow-d_vertScrollbar->getScrollPosition()));
					
					pOptionElement->d_Button->setSize(Absolute, Size(absarea.getWidth(), absarea.getWidth() * d_OptionButtonSize.d_height));

					
					fHeightNow += (int)(absarea.getWidth() * d_OptionButtonSize.d_height * 1.08);
				}
				break;
			case CT_HyperLink:
				{
					
				}
				break;
			case CT_Item:
				{
					fTextPosition = 0.0f;
					ChildElement_Item*	pItemElement = (ChildElement_Item*)pElement;
					if(i > 0)
					{
						ChildElement* pElement_Before = d_ChildVector[i-1];

	
	
						if(pElement_Before && pElement_Before->d_Type != CT_Item && pElement_Before->d_Type != CT_Action)
							fHeightNow += d_ActionButtonDistance.d_height  * absarea.getHeight();
					}

					if(pItemElement->d_ReArrange)
					{
						pItemElement->d_rectClient.setPosition(Point(0.0f, fHeightNow));
						fItemPosition = 0.0f;
					}
					else
					{

						float temp = fItemPosition + ( ( d_ActionButtonSize.d_width  + d_ActionButtonDistance.d_width ) * absarea.getWidth() );

						if( temp > absarea.getWidth() )
							fItemPosition = 0.0f;
						else if(fItemPosition != 0.0f)
						{
							fHeightNow -= ( ( d_ActionButtonSize.d_height  + d_ActionButtonDistance.d_height ) * absarea.getHeight() );
						}
					}

					pItemElement->d_rectClient.setPosition(Point(fItemPosition, fHeightNow));


					pItemElement->d_rectClient.setSize(Size(d_ActionButtonSize.d_width * absarea.getWidth(), d_ActionButtonSize.d_height * absarea.getHeight() ) );

					pItemElement->d_Button->setPosition(Absolute, Point(fItemPosition, fHeightNow-d_vertScrollbar->getScrollPosition()));

					pItemElement->d_Button->setSize(Relative, Size(d_ActionButtonSize.d_width, d_ActionButtonSize.d_height) );


					fHeightNow += ( ( d_ActionButtonSize.d_height  + d_ActionButtonDistance.d_height ) * absarea.getHeight() );
					fItemPosition += ( ( d_ActionButtonSize.d_width  + d_ActionButtonDistance.d_width ) * absarea.getWidth() );
					
					if(i == (int)d_ChildVector.size() )
						fHeightNow -= (d_ActionButtonDistance.d_height  * absarea.getHeight());
				}
				break;

			case CT_Action:
				{
					fTextPosition = 0.0f;
					ChildElement_Action*	pItemElement = (ChildElement_Action*)pElement;

					if(i > 0)
					{
						ChildElement* pElement_Before = d_ChildVector[i-1];

						if(pElement_Before->d_Type != CT_Item && pElement_Before->d_Type != CT_Action)
							fHeightNow += d_ActionButtonDistance.d_height  * absarea.getHeight();
					}

					if(pItemElement->d_ReArrange)
					{
						pItemElement->d_rectClient.setPosition(Point(0.0f, fHeightNow));
						fItemPosition = 0.0f;
					}
					else
					{

						float temp = fItemPosition + ( ( d_ActionButtonSize.d_width  + d_ActionButtonDistance.d_width ) * absarea.getWidth() );

						if( temp > absarea.getWidth() )
							fItemPosition = 0.0f;
						else if(fItemPosition != 0.0f)
						{
							fHeightNow -= ( ( d_ActionButtonSize.d_height  + d_ActionButtonDistance.d_height ) * absarea.getHeight() );
						}
					}

					pItemElement->d_rectClient.setPosition(Point(fItemPosition, fHeightNow));


					pItemElement->d_rectClient.setSize(Size(d_ActionButtonSize.d_width * absarea.getWidth(), d_ActionButtonSize.d_height * absarea.getHeight() ) );

					pItemElement->d_ActionButton->setPosition(Absolute, Point(fItemPosition, fHeightNow-d_vertScrollbar->getScrollPosition()));

					pItemElement->d_ActionButton->setSize(Relative, Size(d_ActionButtonSize.d_width, d_ActionButtonSize.d_height) );


					fHeightNow += ( ( d_ActionButtonSize.d_height  + d_ActionButtonDistance.d_height ) * absarea.getHeight() );
					fItemPosition += ( ( d_ActionButtonSize.d_width  + d_ActionButtonDistance.d_width ) * absarea.getWidth() );
					
					if(i == (int)d_ChildVector.size() - 1 )
						fHeightNow -= (d_ActionButtonDistance.d_height  * absarea.getHeight());
				}
				break;
			case CT_Money:
				{
					fTextPosition = 0.0f;
					fItemPosition = 0.0f;
					ChildElement_Money* pMoneyElement = (ChildElement_Money*)pElement;

					float textHeight = font->getLineSpacing() * 1.4f;

					pMoneyElement->d_rectClient.setPosition(Point(0.0f, fHeightNow));
					pMoneyElement->d_rectClient.setSize(Size(absarea.getWidth(), textHeight));

					pMoneyElement->d_Money->setPosition(Absolute, Point(0.0f, fHeightNow-d_vertScrollbar->getScrollPosition()));
					pMoneyElement->d_Money->setSize(Absolute, Size(absarea.getWidth(), textHeight));

					fHeightNow += textHeight;
				}
				break;
			}
		}

		d_totalHeight = fHeightNow;

		configureScrollbars();
	}

	void KLComplexWindow::ClearAllElement(void)
	{
		_destroyAllElements();

		performWindowLayout();
		requestRedraw();
		d_ParentWindow->requestRedraw();
	}

	void KLComplexWindow::_destroyAllElements(void)
	{
		for(int i=0; i<(int)d_ChildVector.size(); i++)
		{
			ChildElement* pElement = d_ChildVector[i];
			switch(pElement->d_Type)
			{
			case CT_Text:
				{
					ChildElement_Text* pTextElement = (ChildElement_Text*)pElement;
					if( pTextElement->d_finishAni )
						WindowManager::getSingleton().destroyWindow(pTextElement->d_finishAni);
					if( pTextElement->d_Button )
						WindowManager::getSingleton().destroyWindow(pTextElement->d_Button);
				}
				break;

			case CT_Option:
				WindowManager::getSingleton().destroyWindow(((ChildElement_Option*)pElement)->d_Button);
				break;

			case CT_Item:
				WindowManager::getSingleton().destroyWindow(((ChildElement_Item*)pElement)->d_Button);
				break;

			case CT_Action:
				WindowManager::getSingleton().destroyWindow(((ChildElement_Action*)pElement)->d_ActionButton);
				break;

			case CT_Money:
				WindowManager::getSingleton().destroyWindow(((ChildElement_Money*)pElement)->d_Money);
				break;

			case CT_HyperLink:
				WindowManager::getSingleton().destroyWindow(((ChildElement_HyperLink*)pElement)->d_Button);
				break;
			}

			delete d_ChildVector[i];
			d_ChildVector[i] = NULL;
		}
		d_ChildVector.clear();
		d_RadioChild.clear();
		requestRedraw();
		d_ParentWindow->requestRedraw();

	}

	void KLComplexWindow::configureScrollbars(void)
	{
		Scrollbar* vertScrollbar;

		try
		{
			vertScrollbar = static_cast<Scrollbar*>(WindowManager::getSingleton().getWindow(getName() + "__auto_vscrollbar__"));
		}
		catch (UnknownObjectException)
		{
			
			return;
		}

		Rect initialArea(getTextRenderArea());
		float totalHeight	= d_totalHeight;

		
		
		
		
		if( (int)totalHeight > (int)getTextRenderArea().getHeight() )
		{
			vertScrollbar->show();
		}
		else
		{
			vertScrollbar->hide();
		}

		
		
		
		Rect renderArea(getTextRenderArea());

		vertScrollbar->setDocumentSize(totalHeight);
		vertScrollbar->setPageSize(renderArea.getHeight());
		vertScrollbar->setStepSize(ceguimax(1.0f, renderArea.getHeight() / 10.0f));
		vertScrollbar->setScrollPosition(d_vertScrollbar->getScrollPosition());
		requestRedraw();
		d_ParentWindow->requestRedraw();
	}

	void KLComplexWindow::PageEnd()
	{
		Rect renderArea(getTextRenderArea());
		d_vertScrollbar->setScrollPosition( d_totalHeight - renderArea.getHeight() );
		configureScrollbars();
	}

	void KLComplexWindow::prepareBigchar(void)
	{
		Window::prepareBigchar();

		for(int i=0; i<(int)d_ChildVector.size(); i++)
		{
			ChildElement* pElement = d_ChildVector[i];
			if(CT_Text == pElement->d_Type && pElement->d_Font)
			{
				((Font*)(pElement->d_Font))->prepareString(((ChildElement_Text*)pElement)->d_Text);
			}
		}
	}

	bool KLComplexWindow::isMouseHollow( const Point* pPosition ) const
	{
		if( pPosition == NULL )
			return d_mouseHollow;

		CEGUI::String strUtf = CEGUI::HyperLinkManager::getSingleton().getHyperLinkContex(this, CEGUI::Point( pPosition->d_x,  pPosition->d_y) );

		if( !strUtf.empty() )
			return false;

		return d_mouseHollow;
	}

	bool KLComplexWindow::isMouseLButtonHollow( const Point* pPosition ) const
	{
		if( pPosition == NULL || d_mouseLButtonHollow == false)
			return d_mouseLButtonHollow;

		CEGUI::String strUtf = CEGUI::HyperLinkManager::getSingleton().getHyperLinkContex(this, CEGUI::Point( pPosition->d_x,  pPosition->d_y) );

		if( !strUtf.empty() )
			return false;

		return d_mouseLButtonHollow;
	}

	bool KLComplexWindow::isMouseRButtonHollow( const Point* pPosition ) const
	{
		if( pPosition == NULL )
			return d_mouseRButtonHollow;

		CEGUI::String strUtf = CEGUI::HyperLinkManager::getSingleton().getHyperLinkContex(this, CEGUI::Point( pPosition->d_x,  pPosition->d_y) );

		if( !strUtf.empty() )
			return false;

		return d_mouseRButtonHollow;
	}

	void KLComplexWindow::setTextItemAni(const String aniName)
	{
		d_textAniString = aniName;
	}

	void KLComplexWindow::setTextFixedValue( float fix )
	{
		d_textFixedValue = fix;
	}

	Window* KLComplexWindow::GetInlineButtion(int nChildWindowIndex)
	{
		for(int i=0; i<(int)d_ChildVector.size(); i++)
		{
			if (d_ChildVector[i] && 
				d_ChildVector[i]->d_Index == nChildWindowIndex && 
				d_ChildVector[i]->d_Type == CT_Text)
			{
				ChildElement_Text* pText = (ChildElement_Text*)d_ChildVector[i];
				return pText->d_Button;
			}
		}
		return NULL;
	}

    Window* KLComplexWindowFactory::createWindow(const String& name)
    {
        return new KLComplexWindow(d_type, name);
    }

    void KLComplexWindowFactory::destroyWindow(Window* window)
    {
		delete window;
    }
};