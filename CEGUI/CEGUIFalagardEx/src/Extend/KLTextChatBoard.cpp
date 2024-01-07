
#include "KLTextChatBoard.h"
#include "OgreCEGUITexture.h"
#include "CEGUIKeyImageAnimationManager.h"
#include "CEGUIImageset.h"


namespace CEGUI
{
    const utf8  KLTextChatBoard::WidgetTypeName[] = "Falagard/TextChatBoard";

    KLTextChatBoard::KLTextChatBoard(const String& type, const String& name) :
        Window(type, name)
    {
        addChatBoardProperties();
		

		d_renderInfo.clear();
		d_validSize = -1;
		d_pCurHyperLink = NULL;
		d_recalculation = false;
    }

    KLTextChatBoard::~KLTextChatBoard()
    {
    }

	void KLTextChatBoard::addChatBoardProperties(void)
    {
    }

	float KLTextChatBoard::resizeSelf(float maxWidth)
	{
		const Font* font = getFont();
		
		if (font == 0)
			return 0.0f;

		
		Rect absarea(0, 0, maxWidth, getPixelRect().getHeight());
		
		return font->getFormattedSize(d_text, absarea, ((TextFormatting)WordWrapLeftAligned)).d_height 
			+ (Font::LineSpace);
	}

	void KLTextChatBoard::updateSelf(float elapsed)
	{
		Window::updateSelf(elapsed);

		if( !d_fadeEnabled )
			return;

		if( !d_enableStepShow )
			return;

		MouseCursor& mouse = MouseCursor::getSingleton();
		Point position = mouse.getPosition();
		float oldalpha = d_alpha;
		
		{
			if(d_alpha != 0.0f)
			{
				d_currentStepShowTime = d_currentStepShowTime - elapsed;
				if(d_currentStepShowTime<=0.0f)
					d_currentStepShowTime = 0.0f;
				if(d_currentStepShowTime>d_stepShowTime)
					d_currentStepShowTime = d_stepShowTime;
				d_alpha = d_currentStepShowTime/d_stepShowTime;
			}
			else
			{
				d_enableStepShow = false;
				d_inheritsAlpha = true;
				
				
			}
			
			
			
			
			
		}
	}

	void KLTextChatBoard::populateRenderCache()
	{
		const Font* font = getFont();
		
		if (font == 0)
			return;

		
		
		Rect absarea(0, 0, getPixelRect().getWidth(), getPixelRect().getHeight());

		ColourRect final_cols;
		if( d_enableStepShow )
		{
			final_cols = ColourRect(colour(1.0f, 1.0f, 1.0f,d_alpha));
		}
		else
		{
			final_cols = ColourRect(colour(1.0f, 1.0f, 1.0f,getEffectiveAlpha()));
		}

		d_validSize = 0;
		d_pCurHyperLink = NULL;
		clearFontRenderData();
		clearAnimateRenderData();
		clearHyperLinkRenderData();

		d_renderCache.cacheText(this, 
			d_text, font, (TextFormatting)WordWrapLeftAligned, absarea, 0, final_cols);
	}

	bool KLTextChatBoard::isMouseHollow( const Point* pPosition ) const
	{
		if( pPosition == NULL )
			return d_mouseHollow;

		CEGUI::String strUtf = getHyperLinkContex( pPosition );

		if( !strUtf.empty() )
			return false;

		return d_mouseHollow;
	}

	bool KLTextChatBoard::isMouseLButtonHollow( const Point* pPosition ) const
	{
		if( pPosition == NULL || d_mouseLButtonHollow == false)
			return d_mouseLButtonHollow;

		CEGUI::String strUtf = getHyperLinkContex( pPosition );

		if( !strUtf.empty() )
			return false;

		return d_mouseLButtonHollow;
	}

	bool KLTextChatBoard::isMouseRButtonHollow( const Point* pPosition ) const
	{
		if( pPosition == NULL )
			return d_mouseRButtonHollow;

		CEGUI::String strUtf = getHyperLinkContex( pPosition );

		if( !strUtf.empty() )
			return false;

		return d_mouseRButtonHollow;
	}

	bool KLTextChatBoard::getCacheRenderInfo()const
	{
		if( d_renderInfo.size() <= 0 )
			return false;

		for( int i = 0; i < d_validSize; ++i )
		{
			if( d_fontRuntime.size() > 0 )
			{
				
				FontRuntimeMap::const_iterator font = d_fontRuntime.find(d_renderInfo[i].runtimeId);
				if( font != d_fontRuntime.end() )
				{
					FontManager::getSingleton().updateRuntimeBlink( font->second->d_colorRect, (void*)&d_renderInfo[i] );
				}
			}

			if( d_animateRuntime.size() > 0 )
			{
				
				AnimateRuntimeMap::const_iterator iter = d_animateRuntime.find(d_renderInfo[i].runtimeId);
				if( iter != d_animateRuntime.end() )
				{
					KeyImageAnimationManager::getSingleton().updateRuntimeAnimate( *iter->second, (void*)&d_renderInfo[i] );
				}
			}

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

			
			if( d_fadeEnabled )
			{
				if( d_alpha == 0.0f )
					return true;

				FontManager::getSingleton().updateRuntimeBlink( d_alpha, (void*)&d_renderInfo[i] );
			}

			d_renderInfo[i].texture->getTexture()->getRenderer()->addQuad( (void*)&d_renderInfo[i] );
		}

		return true;
	}

	bool KLTextChatBoard::setAnimateRuntime( const AnimateRuntime* aniRuntime )
	{
		AnimateRuntime* runtime = new AnimateRuntime;
		*runtime= *aniRuntime;
		d_animateRuntime.insert( std::make_pair(runtime->d_quadID, runtime) );

		return true;
	}

	bool KLTextChatBoard::setFontBlinkRuntime(const FontBlinkRuntime* fontRuntime)
	{
		FontBlinkRuntime* runtime = new FontBlinkRuntime;
		*runtime = *fontRuntime;
		d_fontRuntime.insert( std::make_pair(runtime->d_quadID, runtime) );

		return true;
	}

	bool KLTextChatBoard::setHyperLinkRuntime(int guid, const String name, const Rect hyper_rect)
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

	String KLTextChatBoard::getHyperLinkContex(const Point* position)const
	{
		if( d_hyperlinkRuntime.size() <= 0 )
			return "";

		HyperLinkRuntimeMap::const_iterator itCur, itEnd;

		itCur		= d_hyperlinkRuntime.begin();
		itEnd		= d_hyperlinkRuntime.end();

		KLTextChatBoard* pWin = (KLTextChatBoard*)this;
		
		while( itCur != itEnd )
		{
			HyperLink* nHyperLink = (HyperLink*)itCur->second;

			if( nHyperLink->isInRange(this, CEGUI::Point( position->d_x,  position->d_y)) )
			{
				pWin->d_pCurHyperLink = (HyperLink*)itCur->second;
				int gamecursor = HyperLinkManager::getSingleton().getHyperLinkCursor(nHyperLink->d_name);
				MouseCursor::getSingleton().setGameCursor(gamecursor);
				return nHyperLink->d_name;
			}

			itCur++;
		}

		pWin->d_pCurHyperLink = NULL;
		MouseCursor::getSingleton().setGameCursor(-1);
		return "";
	}

	void    KLTextChatBoard::onMouseLeaves( MouseEventArgs& e )
	{
		d_pCurHyperLink = NULL;
		MouseCursor::getSingleton().setGameCursor(-1);
		Window::onMouseLeaves( e );
	}

    
    
    
    Window* KLTextChatBoardFactory::createWindow(const String& name)
    {
        return new KLTextChatBoard(d_type, name);
    }

    void KLTextChatBoardFactory::destroyWindow(Window* window)
    {
		delete window;
    }
}