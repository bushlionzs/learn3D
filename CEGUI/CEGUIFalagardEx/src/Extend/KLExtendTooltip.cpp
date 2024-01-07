#include "KLExtendTooltip.h"
#include "falagard/CEGUIFalWidgetLookManager.h"
#include "falagard/CEGUIFalWidgetLookFeel.h"
#include <CEGUIWindowManager.h>


namespace CEGUI
{
	static std::vector< String > split_string( const String& str, const String& delims = "\t\n ", unsigned int maxSplits = 0);

	
	
	
	
	
	const utf8  KLExtendTooltip::ResizeText::WidgetTypeName[] = "Falagard/ExtendTooltip";

	KLResizeTextProperties::TopFrame		KLExtendTooltip::ResizeText::d_topFrameProperty;
	KLResizeTextProperties::MiddleFrame	KLExtendTooltip::ResizeText::d_middleFrameProperty;
	KLResizeTextProperties::BottomFrame	KLExtendTooltip::ResizeText::d_bottomFrameProperty;
	KLResizeTextProperties::TextArea 		KLExtendTooltip::ResizeText::d_textAreaProperty;

	KLExtendTooltip::ResizeText::ResizeText(const String& type, const String& name) :
	KLSimpleText(type, name), 
		d_topFrame(0),
		d_middleFrame(0),
		d_bottomFrame(0)
	{
		addResizeTextProperties();
	}

	KLExtendTooltip::ResizeText::~ResizeText()
	{
	}

	Size KLExtendTooltip::ResizeText::_resizeSelf(const Size size)
	{
		const Font* font = getFont();
		
		if (font == 0)
			return Size(0.0f,0.0f);

		
		Rect textArea(d_textArea.asAbsolute(getAbsoluteSize()));

		float fTotalWidth = 0.0f;
		Size fTextSize = font->getFormattedSize(d_text, textArea, (TextFormatting)d_horzFormatting);
		float fTotalHeight = fTextSize.d_height + (Font::LineSpace);
		if( fTotalWidth < fTextSize.d_width )
			fTotalWidth = fTextSize.d_width;

		float fTopFrameHeight = d_topFrame ? d_topFrame->getSourceTextureArea().getHeight() : 0.f;
		float fMiddleFrameHeight = d_middleFrame ? d_middleFrame->getSourceTextureArea().getHeight() : 0.f;
		float fBottomFrameHeight = d_bottomFrame ? d_bottomFrame->getSourceTextureArea().getHeight() : 0.f;

		Rect wndArea(getAbsoluteRect());
		fTotalHeight += wndArea.getHeight() - textArea.getHeight();

		Size curSize = System::getSingleton().getRenderer()->getSize();

		UDim uTotalHeight;
		uTotalHeight.d_scale = 0;
		uTotalHeight.d_offset = fTotalHeight;
		fTotalHeight = uTotalHeight.asRelative(curSize.d_height * size.d_height);

		UDim uTotalWidth;
		uTotalWidth.d_scale = 0;
		if( fTextSize.d_width > textArea.getWidth() )
		{
			uTotalWidth.d_offset = fTextSize.d_width - textArea.getWidth() + d_pixelSize.d_width;
			fTotalWidth = uTotalWidth.asRelative(curSize.d_width * size.d_width);
		}
		else
		{
			fTotalWidth = 0.0f;
		}

		return Size(fTotalWidth, fTotalHeight);
	}

	void KLExtendTooltip::ResizeText::populateRenderCache()
	{
		if( !d_topFrame || !d_middleFrame || !d_bottomFrame )
			return;

		Rect wndArea(getAbsoluteRect());

		float fTopFrameHeight = d_topFrame ? d_topFrame->getSourceTextureArea().getHeight() : 0.f;
		float fBottomFrameHeight = d_bottomFrame ? d_bottomFrame->getSourceTextureArea().getHeight() : 0.f;

		float fMiddleFrameHeight = wndArea.getHeight()-fTopFrameHeight-fBottomFrameHeight;

		ColourRect final_cols(colour(1.0f, 1.0f, 1.0f));
		d_renderCache.cacheImage(*d_topFrame, Rect(0, 0, wndArea.getWidth(),fTopFrameHeight), 0.0f, final_cols);
		d_renderCache.cacheImage(*d_middleFrame, 
			Rect(0, fTopFrameHeight, wndArea.getWidth(), fTopFrameHeight+fMiddleFrameHeight), 0.0f, final_cols);
		d_renderCache.cacheImage(*d_bottomFrame, 
			Rect(0, fTopFrameHeight+fMiddleFrameHeight, wndArea.getWidth(), wndArea.getHeight()), 0.0f, final_cols);

		KLSimpleText::populateRenderCache();
	}

	Rect KLExtendTooltip::ResizeText::getTextRenderArea(void) const
	{
		return Rect(d_textArea.asAbsolute(getAbsoluteSize()));
	}

	void KLExtendTooltip::ResizeText::addResizeTextProperties(void)
	{
		CEGUI_START_ADD_STATICPROPERTY( ResizeText )
			CEGUI_ADD_STATICPROPERTY( &d_topFrameProperty );
			CEGUI_ADD_STATICPROPERTY( &d_middleFrameProperty );
			CEGUI_ADD_STATICPROPERTY( &d_bottomFrameProperty );
			CEGUI_ADD_STATICPROPERTY( &d_textAreaProperty );
		CEGUI_END_ADD_STATICPROPERTY
	}

	
	
	
	Window* KLExtendTooltip::ResizeTextFactory::createWindow(const String& name)
	{
		return new ResizeText(d_type, name);
	}

	void KLExtendTooltip::ResizeTextFactory::destroyWindow(Window* window)
	{
		delete window;
	}

	
	
	
	
	
	const utf8  KLExtendTooltip::WidgetTypeName[] = "Falagard/SuperTooltip";

	FalagardExtendTooltipProperties::PageElements	KLExtendTooltip::d_pageElementsProperty;
	FalagardExtendTooltipProperties::PageBak			KLExtendTooltip::d_pageBakProperty;
	FalagardExtendTooltipProperties::PageClose		KLExtendTooltip::d_pageCloseProperty;
	FalagardExtendTooltipProperties::ResizeMaxWidth	KLExtendTooltip::d_defaultWidthProperty;
	FalagardExtendTooltipProperties::ConditionWidth	KLExtendTooltip::d_conditionWidthProperty;

	KLExtendTooltip::KLExtendTooltip(const String& type, const String& name) :
	Window(type, name)
	{
		addSuperTooltipProperties();

		setAlwaysOnTop(true);

		d_pagebakWindow = NULL;
		d_pageCloseWindow = NULL;
	
		d_defaultCondition = 0;
		d_lastCondition = 0;
		d_curCondition = 0;
		d_closeWidth = 0.0f;
		d_defaultWidth = 0.0f;
		d_curDefaultWidth = 0.0f;
		d_conditionWidth = 0.0f;
	}

	KLExtendTooltip::~KLExtendTooltip()
	{
	}

	void KLExtendTooltip::addSuperTooltipProperties(void)
	{
		CEGUI_START_ADD_STATICPROPERTY( KLExtendTooltip )
			CEGUI_ADD_STATICPROPERTY( &d_pageElementsProperty );
			CEGUI_ADD_STATICPROPERTY( &d_pageBakProperty );
			CEGUI_ADD_STATICPROPERTY( &d_pageCloseProperty );
			CEGUI_ADD_STATICPROPERTY( &d_defaultWidthProperty );
			CEGUI_ADD_STATICPROPERTY( &d_conditionWidthProperty );
		CEGUI_END_ADD_STATICPROPERTY
	}

	String KLExtendTooltip::getPageElementsName(void) const
	{
		String strOut;

		ElementsVector::const_iterator it;
		for(it=d_VectorElements.begin(); it!=d_VectorElements.end(); it++)
		{
			strOut += it->pWindow->getName();
			strOut += (utf8*)";";
		}

		return strOut;
	}

	void KLExtendTooltip::setPageElementsName(const String& strName)
	{
		
		std::vector< String > vElementNameVector = split_string(strName, (utf8*)";", getChildCount());

		
		int nChildSize = (int)getChildCount();
		for(int i=0; i<nChildSize; i++)
		{
			d_children[i]->hide();
		}

		
		d_VectorElements.clear();
		int nSize = (int)vElementNameVector.size();
		for(int i=0; i<nSize; i++)
		{
			
			if(!isChild(vElementNameVector[i])) continue;

			
			Window* pChild = getChild(vElementNameVector[i]);
			pChild->show();

			Elements newElement;
			newElement.pWindow = pChild;
		
			
			if( pChild->testClassName("KLExtendTooltip/ResizeText") )
			{
				newElement.bDynamicSize = true;
			}
			else
			{
				newElement.bDynamicSize = false;
			}

			d_VectorElements.push_back(newElement);
		}

		if( d_pagebakWindow )
			d_pagebakWindow->show();
		if( d_pageCloseWindow )
			d_pageCloseWindow->show();
	}

	String KLExtendTooltip::getPageBakName(void) const
	{
		if( d_pagebakWindow )
			return d_pagebakWindow->getName();

		return "";
	}

	void KLExtendTooltip::setPageBakName(const String& strName)
	{
		d_pagebakWindow = getChild(strName);

	}

	String KLExtendTooltip::getPageCloseName(void) const
	{
		if( d_pageCloseWindow )
			return d_pageCloseWindow->getName();

		return "";
	}

	void KLExtendTooltip::setPageCloseName(const String& strName, float close)
	{
		d_pageCloseWindow = getChild(strName);
		if( d_pageCloseWindow )
			d_pageCloseWindow->show();		
		d_closeWidth = close;
	}

	void KLExtendTooltip::onSized(WindowEventArgs& e)
	{
		Window::onSized( e );

		if( d_visible )
			resizeSelf();
	}

	void KLExtendTooltip::populateRenderCache()
	{
		
		if( d_VectorElements.empty() )
			return;

		

		
		const WidgetLookFeel& wlf = WidgetLookManager::getSingleton().getWidgetLook(d_lookName);
	
		
		const StateImagery* imagery = &wlf.getStateImagery("Frame");
	
		
		imagery->render(*this);
	}

	float KLExtendTooltip::computeExtendWidth(Window* pWindow)
	{
		float diff = 0.f;
		float bkLeft = 0.f;
		if(d_pagebakWindow)
			bkLeft = d_pagebakWindow->getRect().d_left;

		for( size_t i = 0; i < pWindow->getChildCount(); ++i )
		{
			Window* pChild = pWindow->getChildAtIdx(i);
			if(pChild && pChild->getExtendTooltip())
			{
				float childWidth = pChild->getAbsoluteWidth();
				Point childPos = pChild->getAbsolutePosition();
				childPos.d_x += childWidth;

				float x = pWindow->getAbsolutePosition().d_x + childPos.d_x;
		
				diff = ceguimax(diff, x - bkLeft);
			}
		}

		return (diff + 10.f) / getAbsoluteWidth();
	}

	void KLExtendTooltip::resizeSelf(void)
	{
		size_t nElementNum = d_VectorElements.size();
		if( nElementNum == 0 )
			return;

		if( d_curDefaultWidth != 0.0f )
		{
			size_t nChildSize = getChildCount();
			for(size_t j = 0; j < nChildSize; ++j )
			{
				if( d_children[j]->testClassName("KLExtendTooltip/ResizeText") )
				{
					Size size = d_children[j]->getSize();
					if( size.d_height > 0 && size.d_width > 0 )
					{
						size.d_width -= d_curDefaultWidth;
						d_children[j]->setSize( size );
					}
				}
			}

			
			if( d_pagebakWindow )
			{
				Size size = d_pagebakWindow->getSize();
				size.d_width -= d_curDefaultWidth;
				d_pagebakWindow->setSize( size );
			}
			d_curDefaultWidth = 0.0f;
		}

		std::vector< Size > vPartHeight(nElementNum);
		Size size = getSize();
		float tmpWidth = 0;
		float extendWidth = 0.f;
		for( size_t i = 0; i < nElementNum; ++i )
		{
			Elements& element = d_VectorElements[i];

			if( element.bDynamicSize )
			{
				if( element.pWindow->getText().empty() )
				{
					element.pWindow->setText((utf8*)" ");
				}

				element.pWindow->setSize( Size(element.pWindow->getSize().d_width, 0) );
				vPartHeight[i] = ((ResizeText*)element.pWindow)->_resizeSelf(size);
				tmpWidth = ceguimax(tmpWidth, vPartHeight[i].d_width);
			}
			else
			{
				vPartHeight[i].d_height = element.pWindow->getHeight();
			}

			//计算最大扩展宽度
			extendWidth = ceguimax(extendWidth, computeExtendWidth(element.pWindow));
		}

		
		int nDelta = d_curCondition - d_lastCondition;
		
		{
			
			float curWidth = nDelta * d_conditionWidth;
			d_lastCondition = d_curCondition;

			while( d_defaultWidth + curWidth < tmpWidth )
			{
				curWidth += d_conditionWidth;
				d_curDefaultWidth += d_conditionWidth;
			}

			if( curWidth != 0 )
			{
				size_t nChildSize = getChildCount();
				for(size_t j = 0; j < nChildSize; ++j )
				{
					if( d_children[j]->testClassName("KLExtendTooltip/ResizeText") )
					{
						Size size = d_children[j]->getSize();
						size.d_width += curWidth;
						d_children[j]->setSize( size );
					}
				}
			}

			
			
			
			if( d_pagebakWindow )
			{
				Size size = d_pagebakWindow->getSize();
				size.d_width = d_curCondition * d_conditionWidth + d_conditionWidth * 0.3;
				
				size.d_width = ceguimax(extendWidth, size.d_width);

				d_pagebakWindow->setSize( size );
			}
		}

		
		
		
		size = getSize();
		for( size_t i = 0; i < nElementNum; ++i )
		{
			Elements& element = d_VectorElements[i];

			if( element.bDynamicSize )
			{
				if( element.pWindow->getText().empty() )
				{
					element.pWindow->setText((utf8*)" ");
				}

				vPartHeight[i] = ((ResizeText*)element.pWindow)->_resizeSelf(size);
			}
			else
			{
				vPartHeight[i].d_height = element.pWindow->getHeight();
			}
		}
		

		float fHeightStep = 0.0f;
		for( size_t i = 0; i < nElementNum; ++i )
		{
			Elements& element = d_VectorElements[i];

			if( element.bDynamicSize && element.pWindow->getText().empty() )
				continue;

			element.pWindow->setHeight( vPartHeight[i].d_height );
			element.pWindow->setPosition( Point(element.pWindow->getXPosition(), fHeightStep) );

			fHeightStep += element.pWindow->getHeight();
		}	

		if( d_pagebakWindow )
		{
			d_pagebakWindow->setSize(Size(d_pagebakWindow->getSize().d_width, fHeightStep));
		}
		if( d_pageCloseWindow )
		{
			Point pt = d_pageCloseWindow->getPosition();
			float closeWidth = d_pageCloseWindow->getSize().d_width;
			float width = d_pagebakWindow->getRect().d_right;
			d_pageCloseWindow->setPosition( Point(width - closeWidth - d_closeWidth, pt.d_y) );
		}
	}

	CEGUI::Size KLExtendTooltip::getRealSize()
	{
		if( d_pagebakWindow )
			return d_pagebakWindow->getSize();

		return getSize();
	}

	float KLExtendTooltip::getRealAbsoluteWidth()
	{
		if( d_pagebakWindow )
			return d_pagebakWindow->getAbsoluteWidth();

		return getAbsoluteWidth();
	}

	float KLExtendTooltip::getRealAbsoluteHeight()
	{
		if( d_pagebakWindow )
			return d_pagebakWindow->getAbsoluteHeight();

		return getAbsoluteHeight();
	}

	void KLExtendTooltip::setDefaultWidth( float width )
	{
		d_defaultWidth = width;
	}

	void KLExtendTooltip::setConditionWidth( int starNum, float starWidth )
	{
		d_defaultCondition	= starNum;
		d_curCondition		= starNum;
		d_lastCondition		= starNum;
		d_conditionWidth	= starWidth;
	}

	void KLExtendTooltip::setCurCondition( int curStarNum )
	{
		
		d_curCondition = curStarNum;
		if( curStarNum < d_defaultCondition )
			d_curCondition = d_defaultCondition;
	}
	
	
	
	Window* KLExtendTooltipFactory::createWindow(const String& name)
	{
		return new KLExtendTooltip(d_type, name);
	}

	void KLExtendTooltipFactory::destroyWindow(Window* window)
	{
		delete window;
	}

	
	
	
	
	std::vector<String> split_string( const String& str, const String& delims, unsigned int maxSplits)
	{
		
		std::vector<String> ret;
		unsigned int numSplits = 0;

		
		size_t start, pos;
		start = 0;
		do 
		{
			pos = str.find_first_of(delims, start);
			if (pos == start)
			{
				
				start = pos + 1;
			}
			else if (pos == String::npos || (maxSplits && numSplits == maxSplits))
			{
				
				ret.push_back( str.substr(start) );
				break;
			}
			else
			{
				
				ret.push_back( str.substr(start, pos - start) );
				start = pos + 1;
			}
			
			start = str.find_first_not_of(delims, start);
			++numSplits;

		} while (pos != String::npos);

		return ret;
	}
}