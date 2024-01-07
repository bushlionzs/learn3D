

#include "elements/CEGUIMultiLineEditbox.h"
#include "elements/CEGUIScrollbar.h"
#include "CEGUITextUtils.h"
#include "CEGUIImage.h"
#include "CEGUIExceptions.h"
#include "CEGUIInputMethodEditor.h"
#include "ceguiwindowmanager.h"
#include "CEGUIKeyImageAnimationManager.h"

namespace CEGUI
{
const String MultiLineEditbox::EventNamespace("MultiLineEditbox");



MultiLineEditboxProperties::ReadOnly				MultiLineEditbox::d_readOnlyProperty;
MultiLineEditboxProperties::WordWrap				MultiLineEditbox::d_wordWrapProperty;
MultiLineEditboxProperties::WordBreak				MultiLineEditbox::d_wordBreakProperty;
MultiLineEditboxProperties::CaratIndex				MultiLineEditbox::d_caratIndexProperty;
MultiLineEditboxProperties::SelectionStart			MultiLineEditbox::d_selectionStartProperty;
MultiLineEditboxProperties::SelectionLength			MultiLineEditbox::d_selectionLengthProperty;
MultiLineEditboxProperties::MaxTextLength			MultiLineEditbox::d_maxTextLengthProperty;
MultiLineEditboxProperties::NormalTextColour		MultiLineEditbox::d_normalTextColourProperty;
MultiLineEditboxProperties::SelectedTextColour		MultiLineEditbox::d_selectedTextColourProperty;
MultiLineEditboxProperties::ActiveSelectionColour	MultiLineEditbox::d_activeSelectionColourProperty;
MultiLineEditboxProperties::InactiveSelectionColour	MultiLineEditbox::d_inactiveSelectionColourProperty;
MultiLineEditboxProperties::OnReturnEnable			MultiLineEditbox::d_ReturnEnableProperty;
MultiLineEditboxProperties::LostFocus				MultiLineEditbox::d_lostFocusProperty;




const String MultiLineEditbox::EventReadOnlyModeChanged( (utf8*)"ReadOnlyChanged" );
const String MultiLineEditbox::EventWordWrapModeChanged( (utf8*)"WordWrapModeChanged" );
const String MultiLineEditbox::EventMaximumTextLengthChanged( (utf8*)"MaximumTextLengthChanged" );
const String MultiLineEditbox::EventCaratMoved( (utf8*)"CaratMoved" );
const String MultiLineEditbox::EventTextSelectionChanged( (utf8*)"TextSelectionChanged" );
const String MultiLineEditbox::EventEditboxFull( (utf8*)"EditboxFullEvent" );
const String MultiLineEditbox::EventVertScrollbarModeChanged( (utf8*)"VertScrollbarModeChanged" );
const String MultiLineEditbox::EventHorzScrollbarModeChanged( (utf8*)"HorzScrollbarModeChanged" );


const argb_t MultiLineEditbox::DefaultNormalTextColour			= 0xFFFFFFFF;
const argb_t MultiLineEditbox::DefaultSelectedTextColour		= 0xFF000000;
const argb_t MultiLineEditbox::DefaultNormalSelectionColour		= 0xFF6060FF;
const argb_t MultiLineEditbox::DefaultInactiveSelectionColour	= 0xFF808080;


String MultiLineEditbox::d_lineBreakChars((utf8*)"\n");



MultiLineEditbox::MultiLineEditbox(const String& type, const String& name) :
	Window(type, name),
	d_readOnly(false),
	d_maxTextLen(String::max_size()),
	d_lostFocus(true),
	d_caratPos(0),
	d_selectionStart(0),
	d_selectionEnd(0),
	d_dragging(false),
	d_dragAnchorIdx(0),
	d_wordWrap(true),
	d_wordBreak(true),
	d_widestExtent(0.0f),
	d_forceVertScroll(false),
	d_forceHorzScroll(false),
	d_selectionBrush(NULL),
	d_normalTextColour(DefaultNormalTextColour),
	d_selectTextColour(DefaultSelectedTextColour),
	d_selectBrushColour(DefaultNormalSelectionColour),
	d_inactiveSelectBrushColour(DefaultInactiveSelectionColour)
{
	addMultiLineEditboxProperties();

	
	d_text.append(1, '\n');
	d_ReturnEnable = true;
}



MultiLineEditbox::~MultiLineEditbox(void)
{
}



void MultiLineEditbox::initialise(void)
{
	d_horzScrollbar = NULL;
	d_vertScrollbar = NULL;
	
	if( WindowManager::getSingleton().isWindowPresent( getName() + "__auto_vscrollbar__") )
	{
		d_vertScrollbar = createVertScrollbar(getName() + "__auto_vscrollbar__");
		addChildWindow(d_vertScrollbar);
		 d_vertScrollbar->subscribeEvent(Scrollbar::EventScrollPositionChanged, Event::Subscriber(&MultiLineEditbox::handle_scrollChange, this));
	}
	if( WindowManager::getSingleton().isWindowPresent( getName() + "__auto_hscrollbar__") )
	{
		d_horzScrollbar = createHorzScrollbar(getName() + "__auto_hscrollbar__");
		addChildWindow(d_horzScrollbar);
		d_horzScrollbar->subscribeEvent(Scrollbar::EventScrollPositionChanged, Event::Subscriber(&MultiLineEditbox::handle_scrollChange, this));
	}

	formatText();
	performChildWindowLayout();
}



bool MultiLineEditbox::hasInputFocus(void) const
{
	return ImeModule::GetActiveIMEEditBox() == this;
}



size_t MultiLineEditbox::getSelectionStartIndex(void) const
{
	return (d_selectionStart != d_selectionEnd) ? d_selectionStart : d_caratPos;
}



size_t MultiLineEditbox::getSelectionEndIndex(void) const
{
	return (d_selectionStart != d_selectionEnd) ? d_selectionEnd : d_caratPos;
}



size_t MultiLineEditbox::getSelectionLength(void) const
{
	return d_selectionEnd - d_selectionStart;
}


void MultiLineEditbox::populateRenderCache()
{
	
	cacheEditboxBaseImagery();

	
	
	
	Rect textarea(getTextRenderArea());

	cacheTextLines(textarea);

	if (hasInputFocus() && !isReadOnly())
	{
		cacheCaratImagery(textarea);
	}

}



void MultiLineEditbox::setReadOnly(bool setting)
{
	
	if (d_readOnly != setting)
	{
		d_readOnly = setting;
		WindowEventArgs args(this);
 		onReadOnlyChanged(args);
	}

}



void MultiLineEditbox::setCaratIndex(size_t carat_pos)
{
	
	if (carat_pos > d_text.length() - 1)
	{
		carat_pos = d_text.length() - 1;
	}

	
	if (d_caratPos != carat_pos)
	{
		d_caratPos = carat_pos;
		ensureCaratIsVisible();

		
		WindowEventArgs args(this);
		onCaratMoved(args);
	}

}



void MultiLineEditbox::setSelection(size_t start_pos, size_t end_pos)
{
	
	if (start_pos > d_text.length() - 1)
	{
		start_pos = d_text.length() - 1;
	}

	
	if (end_pos > d_text.length() - 1)
	{
		end_pos = d_text.length() - 1;
	}

	
	if (start_pos > end_pos)
	{
		size_t tmp = end_pos;
		end_pos = start_pos;
		start_pos = tmp;
	}

	
	if ((start_pos != d_selectionStart) || (end_pos != d_selectionEnd))
	{
		
		d_selectionStart = start_pos;
		d_selectionEnd	 = end_pos;

		
		WindowEventArgs args(this);
		onTextSelectionChanged(args);
	}

}



void MultiLineEditbox::setMaxTextLength(size_t max_len)
{
	if (d_maxTextLen != max_len)
	{
		d_maxTextLen = max_len;

		
		WindowEventArgs args(this);
		onMaximumTextLengthChanged(args);

		
		if (d_text.length() > d_maxTextLen)
		{
			while(d_text.mbcs_length() <= d_maxTextLen)
			{
				d_text.resize(d_text.length()-1);
			}

			onTextChanged(args);
		}

	}

}



void MultiLineEditbox::setNormalTextColour(const colour& col)
{
	d_normalTextColour = col;
	requestRedraw();
}



void MultiLineEditbox::setSelectedTextColour(const colour& col)
{
	d_selectTextColour = col;
	requestRedraw();
}



void MultiLineEditbox::setNormalSelectBrushColour(const colour& col)
{
	d_selectBrushColour = col;
	requestRedraw();
}



void MultiLineEditbox::setInactiveSelectBrushColour(const colour& col)
{
	d_inactiveSelectBrushColour = col;
	requestRedraw();
}



void MultiLineEditbox::ensureCaratIsVisible(void)
{
	
	const Font* fnt = getFont();
	size_t caratLine = getLineNumberFromIndex(d_caratPos);

	if (caratLine < d_lines.size())
	{
		Rect textArea(getTextRenderArea());

		size_t caratLineIdx = d_caratPos - d_lines[caratLine].d_startIdx;

		float ypos = caratLine * fnt->getLineSpacing();
		float xpos = fnt->getTextExtent(d_text.substr(d_lines[caratLine].d_startIdx, caratLineIdx));

		
		if( d_horzScrollbar ) 
			xpos -= d_horzScrollbar->getScrollPosition();
		if( d_vertScrollbar ) 
			ypos -= d_vertScrollbar->getScrollPosition();

		
		if (ypos < 0)
		{
			if( d_vertScrollbar ) 
				d_vertScrollbar->setScrollPosition(d_vertScrollbar->getScrollPosition() + ypos);
		}
		
		else if ((ypos += fnt->getLineSpacing()) > textArea.getHeight())
		{
			if( d_vertScrollbar ) 
				d_vertScrollbar->setScrollPosition(d_vertScrollbar->getScrollPosition() + (ypos - textArea.getHeight()) + fnt->getLineSpacing());
		}

		
		if (xpos < 0)
		{
			if( d_horzScrollbar ) 
				d_horzScrollbar->setScrollPosition(d_horzScrollbar->getScrollPosition() + xpos - 50);
		}
		
		else if (xpos > textArea.getWidth())
		{
			if( d_horzScrollbar ) 
				d_horzScrollbar->setScrollPosition(d_horzScrollbar->getScrollPosition() + (xpos - textArea.getWidth()) + 50);
		}

	}

}



void MultiLineEditbox::setWordWrapping(bool setting)
{
	if (setting != d_wordWrap)
	{
		d_wordWrap = setting;
		formatText();

		WindowEventArgs args(this);
		onWordWrapModeChanged(args);
	}

}


void MultiLineEditbox::setWordBreaking(bool setting)
{
	if (setting != d_wordWrap)
	{
		d_wordBreak = setting;
	}
}


void MultiLineEditbox::configureScrollbars(void)
{
	
	
	float totalHeight	= 0.0f;
	for (size_t i = 0; i < d_lines.size(); ++i)
	{
		const LineInfo& currLine = d_lines[i];
		String lineText(d_text.substr(currLine.d_startIdx, currLine.d_length));
		float nowLineHeight = getFont()->getLineSpacing();
		for(size_t n = 0; n < lineText.length(); n++)
		{
			utf32 value = lineText[n] & 0x00FFFFFF;
			utf32 type = (lineText[n] >> 24)&0xFF;
			if( type == 0xFA || type == 0xE3 )
			{
				int id = (type == 0xE3)?(-1*(int)value):(int)value;
				if(!KeyImageAnimationManager::getSingleton().isAnimatePresent(id))
					continue;
				const KeyImageAnimation* animate = KeyImageAnimationManager::getSingleton().getAnimate(id);
				float height = animate->getSize().d_height;
				if( height > nowLineHeight )
				{
					nowLineHeight = height;
				}
			}
		}
		totalHeight	+= nowLineHeight;
	}
	
	float widestItem	= d_widestExtent;

	
	
	
	
	if ((totalHeight > getTextRenderArea().getHeight()) || d_forceVertScroll)
	{
		
		d_vertScrollbar->show();

		
		if ((widestItem > getTextRenderArea().getWidth()) || d_forceHorzScroll)
		{
			if( d_horzScrollbar )
				d_horzScrollbar->show();
		}
		else
		{
			if( d_horzScrollbar )
				d_horzScrollbar->hide();
		}

	}
	else
	{
		
		if ((widestItem > getTextRenderArea().getWidth()) || d_forceHorzScroll)
		{
			if( d_horzScrollbar )
				d_horzScrollbar->show();

			
			if ((totalHeight > getTextRenderArea().getHeight()) || d_forceVertScroll)
			{
				
				d_vertScrollbar->show();
			}
			else
			{
				if( d_vertScrollbar )
					d_vertScrollbar->hide();
			}

		}
		else
		{
			if( d_vertScrollbar )
				d_vertScrollbar->hide();
			if( d_horzScrollbar )
				d_horzScrollbar->hide();
		}

	}

	
	
	
	Rect renderArea(getTextRenderArea());
	if( d_vertScrollbar )
	{
		d_vertScrollbar->setDocumentSize(totalHeight);
		d_vertScrollbar->setPageSize(renderArea.getHeight());
		d_vertScrollbar->setStepSize(std::max(1.0f, renderArea.getHeight() / 10.0f));
		d_vertScrollbar->setScrollPosition(d_vertScrollbar->getScrollPosition());
	}
	if( d_horzScrollbar )
	{
		d_horzScrollbar->setDocumentSize(widestItem);
		d_horzScrollbar->setPageSize(renderArea.getWidth());
		d_horzScrollbar->setStepSize(std::max(1.0f, renderArea.getWidth() / 10.0f));
		d_horzScrollbar->setScrollPosition(d_horzScrollbar->getScrollPosition());
	}
}



void MultiLineEditbox::cacheTextLines(const Rect& dest_area)
{
    
    Rect drawArea(dest_area);
	float fX = 0;
	float fY = 0;
	if( d_horzScrollbar )
		fX = d_horzScrollbar->getScrollPosition();
	if( d_vertScrollbar )
		fY = d_vertScrollbar->getScrollPosition();
	
    drawArea.offset(Point(-fX, -fY));

    Renderer* renderer = System::getSingleton().getRenderer();
    const Font* fnt = getFont();

    if (fnt)
    {
        
        float textZ = renderer->getZLayer(4) - renderer->getCurrentZ();
        float selZ  = renderer->getZLayer(3) - renderer->getCurrentZ();

        
        ColourRect colours;
        float alpha = getEffectiveAlpha();
        colour normalTextCol = d_normalTextColour;
        normalTextCol.setAlpha(normalTextCol.getAlpha() * alpha);
        colour selectTextCol = d_selectTextColour;
        selectTextCol.setAlpha(selectTextCol.getAlpha() * alpha);
        colour selectBrushCol = hasInputFocus() ? d_selectBrushColour : d_inactiveSelectBrushColour;
        selectBrushCol.setAlpha(selectBrushCol.getAlpha() * alpha);

        
        for (size_t i = 0; i < d_lines.size(); ++i)
        {
            Rect lineRect(drawArea);
            const LineInfo& currLine = d_lines[i];
            String lineText(d_text.substr(currLine.d_startIdx, currLine.d_length));

            
            if ((currLine.d_startIdx >= d_selectionEnd) ||
                ((currLine.d_startIdx + currLine.d_length) <= d_selectionStart) ||
                (d_selectionBrush == NULL))
            {
				if( i == 0 )
				{
					colours.setColours(normalTextCol);
					//d_lines[i].d_color = argb_t(normalTextCol); 
				}
				else
				{
					const LineInfo& LastLine = d_lines[i-1];
					normalTextCol	= colour(LastLine.d_color);
					colours.setColours(normalTextCol);
					//d_lines[i].d_color = argb_t(normalTextCol); 
					lineText = LastLine.d_bakcolor + lineText;
				}
                
                d_renderCache.cacheText(this, lineText, fnt, LeftAligned, lineRect, textZ, colours, &dest_area);
            }
            
            else
            {
                
                String sect;
                size_t sectIdx = 0, sectLen;
                float selStartOffset = 0.0f, selAreaWidth = 0.0f;

                
                if (currLine.d_startIdx < d_selectionStart)
                {
                    
                    sectLen = d_selectionStart - currLine.d_startIdx;

                    
                    sect = lineText.substr(sectIdx, sectLen);
                    sectIdx += sectLen;

                    
                    selStartOffset = fnt->getTextExtent(sect);

                    
                    colours.setColours(normalTextCol);
                    d_renderCache.cacheText(this, sect, fnt, LeftAligned, lineRect, textZ, colours, &dest_area);

                    
                    lineRect.d_left += selStartOffset;
                }

                
                sectLen = std::min(d_selectionEnd - currLine.d_startIdx, currLine.d_length) - sectIdx;

                
                sect = lineText.substr(sectIdx, sectLen);
                sectIdx += sectLen;

                
                selAreaWidth = fnt->getTextExtent(sect);

                
                colours.setColours(selectTextCol);
                d_renderCache.cacheText(this, sect, fnt, LeftAligned, lineRect, textZ, colours, &dest_area);

                
                if (sectIdx < currLine.d_length)
                {
                    
                    lineRect.d_left += selAreaWidth;

                    
                    sectLen = currLine.d_length - sectIdx;

                    
                    sect = lineText.substr(sectIdx, sectLen);

                    
                    colours.setColours(normalTextCol);
                    d_renderCache.cacheText(this, sect, fnt, LeftAligned, lineRect, textZ, colours, &dest_area);
                }

                
                lineRect.d_left = drawArea.d_left + selStartOffset;
                lineRect.d_right = lineRect.d_left + selAreaWidth;
                lineRect.d_bottom = lineRect.d_top + fnt->getLineSpacing();

                
                colours.setColours(selectBrushCol);
                d_renderCache.cacheImage(*d_selectionBrush, lineRect, selZ, colours, &dest_area);
            }

			
			
			float nowLineHeight = fnt->getLineSpacing();
			for(size_t n = 0; n < lineText.length(); n++)
			{
				utf32 value = lineText[n] & 0x00FFFFFF;
				utf32 type = (lineText[n] >> 24)&0xFF;
				if( type == 0xFA || type == 0xE3 )
				{
					int id = (type == 0xE3)?(-1*(int)value):(int)value;
					if(!KeyImageAnimationManager::getSingleton().isAnimatePresent(id))
						continue;
					const KeyImageAnimation* animate = KeyImageAnimationManager::getSingleton().getAnimate(id);
					float height = animate->getSize().d_height;
					if( height > nowLineHeight )
					{
						nowLineHeight = height;
					}
				}
			}
            
			drawArea.d_top += nowLineHeight;
        }
    }
}



void MultiLineEditbox::formatText(void)
{
	
	d_lines.clear();
	d_widestExtent = 0.0f;

	String paraText;

	const Font* fnt = getFont();

	if (fnt != NULL)
	{
		float areaWidth = getTextRenderArea().getWidth();

		String::size_type	currPos = 0;
		String::size_type	paraLen;
		LineInfo	line;
		utf32 linecolor = 0xFFFFFFFF;
		utf32 lineBakColor = 0xFC000000;

		while (currPos < d_text.length())
		{
			if ((paraLen = d_text.find_first_of(d_lineBreakChars, currPos)) == String::npos)
			{
				paraLen = d_text.length() - currPos;
			}
			else
			{
				++paraLen -= currPos;
			}

			paraText = d_text.substr(currPos, paraLen);

			if (!d_wordWrap || (areaWidth <= 0.0f))
			{
				
				line.d_startIdx = currPos;
				line.d_length	= paraLen;
				line.d_extent	= fnt->getTextExtent(paraText, 1.0, (utf32*)&line.d_color, (utf32*)&line.d_bakcolor); 
				d_lines.push_back(line);

				
				if (line.d_extent > d_widestExtent)
				{
					d_widestExtent = line.d_extent;
				}

			}
			
			else
			{
				String::size_type lineIndex = 0;

				
				while (lineIndex < paraLen)
				{
					String::size_type  lineLen = 0;
					float lineExtent = 0.0f;

					
					while (lineLen < (paraLen - lineIndex))
					{
						
						size_t nextTokenSize = getNextTokenLength(paraText, lineIndex + lineLen);

						utf32 templinecolor = 0xFFFFFFFF;

						
						float tokenExtent  = fnt->getTextExtent(paraText.substr(lineIndex + lineLen, nextTokenSize), 1.0f, (utf32*)&templinecolor);

						
						if ((lineExtent + tokenExtent) > areaWidth)
						{
							
							if (lineLen == 0)
							{
								
								lineLen = fnt->getCharAtPixel(paraText.substr(lineIndex, nextTokenSize), areaWidth);
							}

							
							break;
						}

						
						lineLen    += nextTokenSize;
						lineExtent += tokenExtent;
						linecolor = templinecolor;
					}

					
					fnt->getTextExtent(paraText.substr(lineIndex, lineLen), 1.0f, (utf32*)&linecolor, (utf32*)&lineBakColor );

					
					line.d_startIdx = currPos + lineIndex;
					line.d_length	= lineLen;
					line.d_extent	= lineExtent;
					line.d_color	= linecolor;
					line.d_bakcolor = lineBakColor;
					d_lines.push_back(line);

					
					if (lineExtent > d_widestExtent)
					{
						d_widestExtent = lineExtent;
					}

					
					lineIndex += lineLen;
				}

			}

			
			currPos += paraLen;
		}

	}

	configureScrollbars();
	requestRedraw();
}



size_t MultiLineEditbox::getNextTokenLength(const String& text, size_t start_idx) const
{
	String::size_type pos = text.find_first_of( d_wordBreak ? TextUtils::DefaultWrapDelimiters : TextUtils::DefaultBreakDelimiters, start_idx);

	
	if (pos == String::npos)
	{
		return (text.length() - start_idx);
	}
	
	else if ((pos - start_idx) == 0)
	{
		return 1;
	}
	else
	{
		return (pos - start_idx);
	}

}



size_t MultiLineEditbox::getTextIndexFromPosition(const Point& pt) const
{
	
	
	
	Point wndPt = screenToWindow(pt);

	if (getMetricsMode() == Relative)
	{
		wndPt = relativeToAbsolute(wndPt);
	}

	Rect textArea(getTextRenderArea());

	wndPt.d_x -= textArea.d_left;
	wndPt.d_y -= textArea.d_top;

	
	if( d_horzScrollbar )
		wndPt.d_x += d_horzScrollbar->getScrollPosition();
	if( d_vertScrollbar )
		wndPt.d_y += d_vertScrollbar->getScrollPosition();

	size_t lineNumber = static_cast<size_t>(wndPt.d_y / getFont()->getLineSpacing());

	if (lineNumber >= d_lines.size())
	{
		lineNumber = d_lines.size() - 1;
	}

	String lineText(d_text.substr(d_lines[lineNumber].d_startIdx, d_lines[lineNumber].d_length));

	size_t lineIdx = getFont()->getCharAtPixel(lineText, wndPt.d_x);

	if (lineIdx >= lineText.length() - 1)
	{
		lineIdx = lineText.length() - 1;
	}

	return d_lines[lineNumber].d_startIdx + lineIdx;
}



size_t MultiLineEditbox::getLineNumberFromIndex(size_t index) const
{
	size_t lineCount = d_lines.size();

	if (lineCount == 0)
	{
		return 0;
	}
	else if (index >= d_text.length() - 1)
	{
		return lineCount - 1;
	}
	else
	{
		size_t indexCount = 0;
		size_t caratLine = 0;

		for (; caratLine < lineCount; ++caratLine)
		{
			indexCount += d_lines[caratLine].d_length;

			if (index < indexCount)
			{
				return caratLine;
			}

		}

	}

	throw InvalidRequestException((utf8*)"MultiLineEditbox::getLineNumberFromIndex - Unable to identify a line from the given, invalid, index.");
}




void MultiLineEditbox::clearSelection(void)
{
	
	if (getSelectionLength() != 0)
	{
		setSelection(0, 0);
	}

}



void MultiLineEditbox::eraseSelectedText(bool modify_text)
{
	if (getSelectionLength() != 0)
	{
		
		setCaratIndex(getSelectionStartIndex());

		
		if (modify_text)
		{
			d_text.erase(getSelectionStartIndex(), getSelectionLength());

			
			WindowEventArgs args(this);
			onTextChanged(args);
		}

		clearSelection();
	}

}



void MultiLineEditbox::handleBackspace(void)
{
	if (!isReadOnly())
	{
		if (getSelectionLength() != 0)
		{
			eraseSelectedText();
		}
		else if (d_caratPos > 0)
		{
			d_text.erase(d_caratPos - 1, 1);
			setCaratIndex(d_caratPos - 1);

			WindowEventArgs args(this);
			onTextChanged(args);
		}

	}
}



void MultiLineEditbox::handleDelete(void)
{
	if (!isReadOnly())
	{
		if (getSelectionLength() != 0)
		{
			eraseSelectedText();
		}
		else if (getCaratIndex() < d_text.length() - 1)
		{
			d_text.erase(d_caratPos, 1);
			ensureCaratIsVisible();

			WindowEventArgs args(this);
			onTextChanged(args);
		}

	}

}



void MultiLineEditbox::handleCharLeft(uint sysKeys)
{
	if (d_caratPos > 0)
	{
		setCaratIndex(d_caratPos - 1);
	}

	if (sysKeys & Shift)
	{
		setSelection(d_caratPos, d_dragAnchorIdx);	
	}
	else
	{
		clearSelection();
	}

}



void MultiLineEditbox::handleWordLeft(uint sysKeys)
{
	if (d_caratPos > 0)
	{
		setCaratIndex(TextUtils::getWordStartIdx(d_text, getCaratIndex()));
	}

	if (sysKeys & Shift)
	{
		setSelection(d_caratPos, d_dragAnchorIdx);	
	}
	else
	{
		clearSelection();
	}

}



void MultiLineEditbox::handleCharRight(uint sysKeys)
{
	if (d_caratPos < d_text.length() - 1)
	{
		setCaratIndex(d_caratPos + 1);
	}

	if (sysKeys & Shift)
	{
		setSelection(d_caratPos, d_dragAnchorIdx);	
	}
	else
	{
		clearSelection();
	}

}



void MultiLineEditbox::handleWordRight(uint sysKeys)
{
	if (d_caratPos < d_text.length() - 1)
	{
		setCaratIndex(TextUtils::getNextWordStartIdx(d_text, getCaratIndex()));
	}

	if (sysKeys & Shift)
	{
		setSelection(d_caratPos, d_dragAnchorIdx);	
	}
	else
	{
		clearSelection();
	}

}



void MultiLineEditbox::handleDocHome(uint sysKeys)
{
	if (d_caratPos > 0)
	{
		setCaratIndex(0);
	}

	if (sysKeys & Shift)
	{
		setSelection(d_caratPos, d_dragAnchorIdx);	
	}
	else
	{
		clearSelection();
	}

}



void MultiLineEditbox::handleDocEnd(uint sysKeys)
{
	if (d_caratPos < d_text.length() - 1)
	{
		setCaratIndex(d_text.length() - 1);
	}

	if (sysKeys & Shift)
	{
		setSelection(d_caratPos, d_dragAnchorIdx);	
	}
	else
	{
		clearSelection();
	}

}



void MultiLineEditbox::handleLineHome(uint sysKeys)
{
	size_t line = getLineNumberFromIndex(d_caratPos);

	if (line < d_lines.size())
	{
		size_t lineStartIdx = d_lines[line].d_startIdx;

		if (d_caratPos > lineStartIdx)
		{
			setCaratIndex(lineStartIdx);
		}

		if (sysKeys & Shift)
		{
			setSelection(d_caratPos, d_dragAnchorIdx);	
		}
		else
		{
			clearSelection();
		}

	}

}



void MultiLineEditbox::handleLineEnd(uint sysKeys)
{
	size_t line = getLineNumberFromIndex(d_caratPos);

	if (line < d_lines.size())
	{
		size_t lineEndIdx = d_lines[line].d_startIdx + d_lines[line].d_length - 1;

		if (d_caratPos < lineEndIdx)
		{
			setCaratIndex(lineEndIdx);
		}

		if (sysKeys & Shift)
		{
			setSelection(d_caratPos, d_dragAnchorIdx);	
		}
		else
		{
			clearSelection();
		}

	}

}



void MultiLineEditbox::handleLineUp(uint sysKeys)
{
	size_t caratLine = getLineNumberFromIndex(d_caratPos);

	if (caratLine > 0)
	{
		float caratPixelOffset = getFont()->getTextExtent(d_text.substr(d_lines[caratLine].d_startIdx, d_caratPos - d_lines[caratLine].d_startIdx));

		--caratLine;

		size_t newLineIndex = getFont()->getCharAtPixel(d_text.substr(d_lines[caratLine].d_startIdx, d_lines[caratLine].d_length), caratPixelOffset);

		setCaratIndex(d_lines[caratLine].d_startIdx + newLineIndex);
	}

	if (sysKeys & Shift)
	{
		setSelection(d_caratPos, d_dragAnchorIdx);	
	}
	else
	{
		clearSelection();
	}

}



void MultiLineEditbox::handleLineDown(uint sysKeys)
{
	size_t caratLine = getLineNumberFromIndex(d_caratPos);

	if ((d_lines.size() > 1) && (caratLine < (d_lines.size() - 1)))
	{
		float caratPixelOffset = getFont()->getTextExtent(d_text.substr(d_lines[caratLine].d_startIdx, d_caratPos - d_lines[caratLine].d_startIdx));

		++caratLine;

		size_t newLineIndex = getFont()->getCharAtPixel(d_text.substr(d_lines[caratLine].d_startIdx, d_lines[caratLine].d_length), caratPixelOffset);

		setCaratIndex(d_lines[caratLine].d_startIdx + newLineIndex);
	}

	if (sysKeys & Shift)
	{
		setSelection(d_caratPos, d_dragAnchorIdx);	
	}
	else
	{
		clearSelection();
	}

}



void MultiLineEditbox::handleNewLine(uint sysKeys)
{
	
	
	
	

	
	
	
	
	

	
	
	
	

}



void MultiLineEditbox::onMouseButtonDown(MouseEventArgs& e)
{
	
	Window::onMouseButtonDown(e);

	if (e.button == LeftButton)
	{
		
		if (captureInput())
		{
			
			clearSelection();
			d_dragging = true;
			d_dragAnchorIdx = getTextIndexFromPosition(e.position);
			setCaratIndex(d_dragAnchorIdx);
		}

		e.handled = true;
	}

}



void MultiLineEditbox::onMouseButtonUp(MouseEventArgs& e)
{
	
	Window::onMouseButtonUp(e);

	if (e.button == LeftButton)
	{
		releaseInput();
		e.handled = true;
	}

}



void MultiLineEditbox::onMouseDoubleClicked(MouseEventArgs& e)
{
	
	Window::onMouseDoubleClicked(e);

	
	
	
	
	
	

	
	

	
	

}



void MultiLineEditbox::onMouseTripleClicked(MouseEventArgs& e)
{
	
	Window::onMouseTripleClicked(e);

	
	
	
	
	
	

	
	

	
	
	
	
	

	
	

	
	
	
	
	
	
	

	
	
	
	
	
	

}



void MultiLineEditbox::onMouseMove(MouseEventArgs& e)
{
	
	Window::onMouseMove(e);

	if (d_dragging)
	{
		setCaratIndex(getTextIndexFromPosition(e.position));
		setSelection(d_caratPos, d_dragAnchorIdx);
	}

	e.handled = true;
}



void MultiLineEditbox::onCaptureLost(WindowEventArgs& e)
{
	d_dragging = false;

	
	Window::onCaptureLost(e);

	e.handled = true;
}



void MultiLineEditbox::onCharacter(KeyEventArgs& e)
{
	
	Window::onCharacter(e);

	
	String str;
	str = e.codepoint;
	((Font*)getFont())->prepareString( str );
	

	
	if (hasInputFocus() && !isReadOnly() && getFont()->isCodepointAvailable(e.codepoint))
	{
		
		eraseSelectedText();

		
		if (d_text.mbcs_length()+str.mbcs_length() <= d_maxTextLen)
		{
			d_text.insert(getCaratIndex(), 1, e.codepoint);
			d_caratPos++;

			WindowEventArgs args(this);
			onTextChanged(args);
		}
		else
		{
			
			WindowEventArgs args(this);
			onEditboxFullEvent(args);
		}

	}

	e.handled = true;
}



void MultiLineEditbox::onKeyDown(KeyEventArgs& e)
{
	
	Window::onKeyDown(e);

	if (hasInputFocus() && !isReadOnly())
	{
		WindowEventArgs args(this);
		switch (e.scancode)
		{
		case Key::LeftShift:
		case Key::RightShift:
			if (getSelectionLength() == 0)
			{
				d_dragAnchorIdx = getCaratIndex();
			}
			break;

		case Key::Backspace:
			handleBackspace();
			break;

		case Key::Delete:
			handleDelete();
			break;

		case Key::Return:
		case Key::NumpadEnter:
			if( d_ReturnEnable )
				handleNewLine(e.sysKeys);
			break;

		case Key::ArrowLeft:
			if (e.sysKeys & Control)
			{
				handleWordLeft(e.sysKeys);
			}
			else
			{
				handleCharLeft(e.sysKeys);
			}
			break;

		case Key::ArrowRight:
			if (e.sysKeys & Control)
			{
				handleWordRight(e.sysKeys);
			}
			else
			{
				handleCharRight(e.sysKeys);
			}
			break;

		case Key::ArrowUp:
			handleLineUp(e.sysKeys);
			break;

		case Key::ArrowDown:
			handleLineDown(e.sysKeys);
			break;

		case Key::Home:
			if (e.sysKeys & Control)
			{
				handleDocHome(e.sysKeys);
			}
			else
			{
				handleLineHome(e.sysKeys);
			}
			break;

		case Key::End:
			if (e.sysKeys & Control)
			{
				handleDocEnd(e.sysKeys);
			}
			else
			{
				handleLineEnd(e.sysKeys);
			}
			break;

        
        default:
            return;
		}

		e.handled = true;
	}

}



void MultiLineEditbox::onTextChanged(WindowEventArgs& e)
{
    
    if ((d_text.length() == 0) || (d_text[d_text.length() - 1] != '\n'))
        d_text.append(1, '\n');

    
    Window::onTextChanged(e);

    
    clearSelection();
    
    formatText();
    
    performChildWindowLayout();
    
    setCaratIndex(getCaratIndex());
    
    
    
    ensureCaratIsVisible();

    e.handled = true;
}



void MultiLineEditbox::onSized(WindowEventArgs& e)
{
	formatText();

	
	Window::onSized(e);

	e.handled = true;
}



void MultiLineEditbox::onMouseWheel(MouseEventArgs& e)
{
	
	Window::onMouseWheel(e);

	if (d_vertScrollbar && d_vertScrollbar->isVisible() && (d_vertScrollbar->getDocumentSize() > d_vertScrollbar->getPageSize()))
	{
		d_vertScrollbar->setScrollPosition(d_vertScrollbar->getScrollPosition() + d_vertScrollbar->getStepSize() * -e.wheelChange);
	}
	else if (d_horzScrollbar && d_horzScrollbar->isVisible() && (d_horzScrollbar->getDocumentSize() > d_horzScrollbar->getPageSize()))
	{
		d_horzScrollbar->setScrollPosition(d_horzScrollbar->getScrollPosition() + d_horzScrollbar->getStepSize() * -e.wheelChange);
	}

	e.handled = true;
}



void MultiLineEditbox::onReadOnlyChanged(WindowEventArgs& e)
{
	fireEvent(EventReadOnlyModeChanged, e, EventNamespace);
}



void MultiLineEditbox::onWordWrapModeChanged(WindowEventArgs& e)
{
	fireEvent(EventWordWrapModeChanged, e, EventNamespace);
}



void MultiLineEditbox::onMaximumTextLengthChanged(WindowEventArgs& e)
{
	fireEvent(EventMaximumTextLengthChanged, e, EventNamespace);
}



void MultiLineEditbox::onCaratMoved(WindowEventArgs& e)
{
	requestRedraw();
	fireEvent(EventCaratMoved, e, EventNamespace);
}



void MultiLineEditbox::onTextSelectionChanged(WindowEventArgs& e)
{
	requestRedraw();
	fireEvent(EventTextSelectionChanged, e, EventNamespace);
}



void MultiLineEditbox::onEditboxFullEvent(WindowEventArgs& e)
{
	fireEvent(EventEditboxFull, e, EventNamespace);
}



void MultiLineEditbox::onVertScrollbarModeChanged(WindowEventArgs& e)
{
	requestRedraw();
	fireEvent(EventVertScrollbarModeChanged, e, EventNamespace);
}



void MultiLineEditbox::onHorzScrollbarModeChanged(WindowEventArgs& e)
{
	requestRedraw();
	fireEvent(EventHorzScrollbarModeChanged, e, EventNamespace);
}



bool MultiLineEditbox::isWordWrapped(void) const
{
	return d_wordWrap;
}


bool MultiLineEditbox::isWordBreaked(void) const
{
	return d_wordBreak;
}


void MultiLineEditbox::addMultiLineEditboxProperties(void)
{
	CEGUI_START_ADD_STATICPROPERTY( MultiLineEditbox );
	   CEGUI_ADD_STATICPROPERTY( &d_readOnlyProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_wordWrapProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_wordBreakProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_caratIndexProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_selectionStartProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_selectionLengthProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_maxTextLengthProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_normalTextColourProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_selectedTextColourProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_activeSelectionColourProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_inactiveSelectionColourProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_ReturnEnableProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_lostFocusProperty );
	CEGUI_END_ADD_STATICPROPERTY
}


bool MultiLineEditbox::handle_scrollChange(const EventArgs& args)
{
    
    requestRedraw();
    return true;
}

const String MultiLineEditbox::getRealText( void ) const
{
	if( d_text.empty() )
		return "";

	String str = d_text.substr( 0, d_text.find_last_of("\n") );
	return str;
}


} 
