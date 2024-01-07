

#include "elements/CEGUIEditbox.h"
#include "CEGUITextUtils.h"
#include "CEGUIExceptions.h"
#include "CEGUIFont.h"
#include "../pcre/pcre.h"
#include <string.h>



namespace CEGUI
{
const String Editbox::EventNamespace("Editbox");


struct RegexValidator
{
	RegexValidator(void) : d_regex(0) {}
	~RegexValidator(void) { release(); }

	void release()
	{
		if (d_regex != 0)
		{
			pcre_free(d_regex);
			d_regex = 0;
		}

	}

	pcre* d_regex;
};



EditboxProperties::ReadOnly					Editbox::d_readOnlyProperty;
EditboxProperties::MaskText					Editbox::d_maskTextProperty;
EditboxProperties::MaskCodepoint			Editbox::d_maskCodepointProperty;
EditboxProperties::ValidationString			Editbox::d_validationStringProperty;
EditboxProperties::CaratIndex				Editbox::d_caratIndexProperty;
EditboxProperties::SelectionStart			Editbox::d_selectionStartProperty;
EditboxProperties::SelectionLength			Editbox::d_selectionLengthProperty;
EditboxProperties::MaxTextLength			Editbox::d_maxTextLengthProperty;
EditboxProperties::NormalTextColour			Editbox::d_normalTextColourProperty;
EditboxProperties::SelectedTextColour		Editbox::d_selectedTextColourProperty;
EditboxProperties::ActiveSelectionColour	Editbox::d_activeSelectionColourProperty;
EditboxProperties::InactiveSelectionColour	Editbox::d_inactiveSelectionColourProperty;
EditboxProperties::ForbidInput				Editbox::d_forbidInputProperty;
EditboxProperties::UseRegex					Editbox::d_useRegexProperty;
EditboxProperties::LostFocus				Editbox::d_lostFocusProperty;




const argb_t Editbox::DefaultNormalTextColour			= 0xFFFFFFFF;
const argb_t Editbox::DefaultSelectedTextColour			= 0xFF000000;
const argb_t Editbox::DefaultNormalSelectionColour		= 0xFF6060FF;
const argb_t Editbox::DefaultInactiveSelectionColour	= 0xFF808080;



const String Editbox::EventReadOnlyModeChanged( (utf8*)"ReadOnlyChanged" );
const String Editbox::EventMaskedRenderingModeChanged( (utf8*)"MaskRenderChanged" );
const String Editbox::EventMaskCodePointChanged( (utf8*)"MaskCPChanged" );
const String Editbox::EventValidationStringChanged( (utf8*)"ValidatorChanged" );
const String Editbox::EventMaximumTextLengthChanged( (utf8*)"MaxTextLenChanged" );
const String Editbox::EventTextInvalidated( (utf8*)"TextInvalidated" );
const String Editbox::EventInvalidEntryAttempted( (utf8*)"InvalidInputAttempt" );
const String Editbox::EventCaratMoved( (utf8*)"TextCaratMoved" );
const String Editbox::EventTextSelectionChanged( (utf8*)"TextSelectChanged" );
const String Editbox::EventEditboxFull( (utf8*)"EditboxFull" );
const String Editbox::EventTextAccepted( (utf8*)"TextAccepted" );
const String Editbox::EventTabPressed( (utf8*)"TabPressed" );



Editbox::Editbox(const String& type, const String& name) :
	Window(type, name),
	d_readOnly(false),
	d_forbidInput(false),
	d_useRegex(true),
	d_lostFocus(true),
	d_maskText(false),
	d_maskCodePoint('*'),
	d_maxTextLen(String::max_size()),
	d_caratPos(0),
	d_selectionStart(0),
	d_selectionEnd(0),
	d_dragging(false),
	d_dragAnchorIdx(0),
	d_normalTextColour(DefaultNormalTextColour),
	d_selectTextColour(DefaultSelectedTextColour),
	d_selectBrushColour(DefaultNormalSelectionColour),
	d_inactiveSelectBrushColour(DefaultInactiveSelectionColour)
{
	d_validator = new RegexValidator;

	addEditboxProperties();

	
	setValidationString((utf8*)".*");
	setNeedRealTimeUpdate(true);
}



Editbox::~Editbox(void)
{
	delete d_validator;
}



bool Editbox::hasInputFocus(void) const
{
	return isActive();
}



bool Editbox::isTextValid(void) const
{
	return isStringValid(d_text);
}



size_t Editbox::getSelectionStartIndex(void) const
{
	return (d_selectionStart != d_selectionEnd) ? d_selectionStart : d_caratPos;
}



size_t Editbox::getSelectionEndIndex(void) const
{
	return (d_selectionStart != d_selectionEnd) ? d_selectionEnd : d_caratPos;
}



size_t Editbox::getSelectionLength(void) const
{
	return d_selectionEnd - d_selectionStart;
}



void Editbox::setReadOnly(bool setting)
{
	
	if (d_readOnly != setting)
	{
		d_readOnly = setting;
		WindowEventArgs args(this);
		onReadOnlyChanged(args);
	}

}



void Editbox::setTextMasked(bool setting)
{
	
	if (d_maskText != setting)
	{
		d_maskText = setting;
		WindowEventArgs args(this);
		onMaskedRenderingModeChanged(args);
	}

}



void Editbox::setValidationString(const String& validation_string)
{
	if (d_validationString != validation_string)
	{
		d_validationString = validation_string;
		d_validator->release();

		
		const char* prce_error;
		int pcre_erroff;
		d_validator->d_regex = pcre_compile(d_validationString.c_str(), PCRE_UTF8, &prce_error, &pcre_erroff, 0);

		
		if (d_validator->d_regex == 0)
		{
			throw InvalidRequestException("The Editbox named '" + getName() + "' had the following bad validation expression set: '" + validation_string + "'.  Additional Information: " + prce_error);			
		}

		
		WindowEventArgs args(this);
		onValidationStringChanged(args);

		if (!isTextValid())
		{
			
			onTextInvalidatedEvent(args);
		}

	}

}



void Editbox::setCaratIndex(size_t carat_pos)
{
	
	if (carat_pos > d_text.length())
	{
		carat_pos = d_text.length();
	}

	
	if (d_caratPos != carat_pos)
	{
		d_caratPos = carat_pos;

		
		WindowEventArgs args(this);
		onCaratMoved(args);
	}

}



void Editbox::setSelection(size_t start_pos, size_t end_pos)
{
	
	if (start_pos > d_text.length())
	{
		start_pos = d_text.length();
	}

	
	if (end_pos > d_text.length())
	{
		end_pos = d_text.length();
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



void Editbox::setMaskCodePoint(utf32 code_point)
{
	if (code_point != d_maskCodePoint)
	{
		d_maskCodePoint = code_point;

		
		WindowEventArgs args(this);
		onMaskCodePointChanged(args);
	}

}



void Editbox::setMaxTextLength(size_t max_len)
{
	if (d_maxTextLen != max_len)
	{
		d_maxTextLen = max_len;
		
		
		WindowEventArgs args(this);
		onMaximumTextLengthChanged(args);

		
		if (d_text.mbcs_length() > d_maxTextLen)
		{
			while(d_text.mbcs_length() <= d_maxTextLen)
			{
				d_text.resize(d_text.length()-1);
			}
			onTextChanged(args);

			
			if (!isTextValid())
			{
				
				onTextInvalidatedEvent(args);
			}

		}

	}

}



void Editbox::clearSelection(void)
{
	
	if (getSelectionLength() != 0)
	{
		setSelection(0, 0);
	}

}



void Editbox::eraseSelectedText(bool modify_text)
{
	if (getSelectionLength() != 0)
	{
		
		setCaratIndex(getSelectionStartIndex());
		clearSelection();

		
		if (modify_text)
		{
			d_text.erase(getSelectionStartIndex(), getSelectionLength());

			
			WindowEventArgs args(this);
			onTextChanged(args);
		}

	}

}



bool Editbox::isStringValid(const String& str) const
{
	
	if (d_validator->d_regex == 0)
	{
		throw InvalidRequestException("Editbox::isStringValid - An attempt was made to use the invalid RegEx '" + d_validationString + "'.");
	}

	const char* utf8str = str.c_str();
	int	match[3];
	int len = static_cast<int>(strlen(utf8str));
	int result = pcre_exec(d_validator->d_regex, NULL, utf8str, len, 0, 0, match, 3);

	if (result >= 0)
	{
		
		return (match[1] - match[0] == len);
	}
	
	else if ((result == PCRE_ERROR_NOMATCH) || (result == PCRE_ERROR_NULL))
	{
		return false;
	}
	
	else
	{
		throw InvalidRequestException("Editbox::isStringValid - An internal error occurred while attempting to match the invalid RegEx '" + d_validationString + "'.");
	}

}



void Editbox::onMouseButtonDown(MouseEventArgs& e)
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


void Editbox::onMouseButtonUp(MouseEventArgs& e)
{
	
	Window::onMouseButtonUp(e);

	if (e.button == LeftButton)
	{
		releaseInput();
		e.handled = true;
	}

}



void Editbox::onMouseDoubleClicked(MouseEventArgs& e)
{
	
	Window::onMouseDoubleClicked(e);

	if (e.button == LeftButton && !d_readOnly)
	{
		selectAll();
		e.handled = true;
	}

}

void Editbox::selectAll(void)
{
	
	if (isTextMasked())
	{
		d_dragAnchorIdx = 0;
		setCaratIndex(d_text.length());
	}
	
	else
	{
		d_dragAnchorIdx = TextUtils::getWordStartIdx(d_text, (d_caratPos == d_text.length()) ? d_caratPos : d_caratPos + 1);
		d_caratPos		= TextUtils::getNextWordStartIdx(d_text, d_caratPos);
	}

	
	setSelection(d_dragAnchorIdx, d_caratPos);
}


void Editbox::onMouseTripleClicked(MouseEventArgs& e)
{
	
	Window::onMouseTripleClicked(e);

	if (e.button == LeftButton && !d_readOnly)
	{
		d_dragAnchorIdx = 0;
		setCaratIndex(d_text.length());
		setSelection(d_dragAnchorIdx, d_caratPos);
		e.handled = true;
	}

}



void Editbox::onMouseMove(MouseEventArgs& e)
{
	
	Window::onMouseMove(e);

	if (d_dragging)
	{
		setCaratIndex(getTextIndexFromPosition(e.position));
		setSelection(d_caratPos, d_dragAnchorIdx);
	}

	e.handled = true;
}


void Editbox::onCaptureLost(WindowEventArgs& e)
{
	d_dragging = false;

	
	Window::onCaptureLost(e);

	e.handled = true;
}


void     Editbox::addCharater( const utf32 &codepoint )
{
	if( !isVisible() )
		return;
	
	String str;
	str = codepoint;
	((Font*)getFont())->prepareString( str );
	

	
	if (hasInputFocus() && getFont()->isCodepointAvailable(codepoint) && !isReadOnly())
	{
		
		String tmp(d_text);
		char szstr[512];
		memset(szstr,0x00,512);
		sprintf(szstr,tmp.c_str());
		tmp.erase(getSelectionStartIndex(), getSelectionLength());
		if( tmp.size() == 0 )
			setCaratIndex(0);

		
		if (tmp.mbcs_length() + str.mbcs_length() <= d_maxTextLen)
		{
			tmp.insert(getSelectionStartIndex(), 1, codepoint);

			if ( !d_useRegex || isStringValid(tmp) )
			{
				
				eraseSelectedText(false);

                
                d_caratPos++;

                
				setText(tmp);
			}
			else
			{
				
				WindowEventArgs args(this);
				onInvalidEntryAttempted(args);
			}

		}
		else
		{
			
			WindowEventArgs args(this);
			onEditboxFullEvent(args);
		}

	}

	
}
void Editbox::onCharacter(KeyEventArgs& e)
{
	
	Window::onCharacter(e);
	addCharater( e.codepoint );
	e.handled = true;
}

void Editbox::setText(const String& text)
{
	if( text.length() > d_maxTextLen )
		return;

	d_text = text;
	WindowEventArgs args(this);
	onTextChanged(args);
}


void Editbox::onKeyDown(KeyEventArgs& e)
{
	
	Window::onKeyDown(e);

	
	
	if (hasInputFocus() && !isForbidInput())
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

		case Key::Tab:
			onTabPressedEvent(args);
			break;

		case Key::Return:
		case Key::NumpadEnter:
			
			onTextAcceptedEvent(args);
			break;

		case Key::ArrowLeft:
			if (e.sysKeys & Control)
			{
				
				
				handleCharLeft(e.sysKeys);
			}
			else
			{
				handleCharLeft(e.sysKeys);
			}
			break;

		case Key::ArrowRight:
			if (e.sysKeys & Control)
			{
				
				
				handleCharRight(e.sysKeys);
			}
			else
			{
				handleCharRight(e.sysKeys);
			}
			break;

		case Key::Home:
			handleHome(e.sysKeys);
			break;

		case Key::End:
			handleEnd(e.sysKeys);
			break;

        
        default:
            return;
		}

		e.handled = true;
	}

}


void Editbox::onKeyUp(KeyEventArgs& e)
{
	
	Window::onKeyUp(e);

	if (hasInputFocus() )
	{
		WindowEventArgs args(this);

		e.handled = true;
	}
}


void Editbox::handleBackspace(void)
{
	if (!isReadOnly())
	{
		String tmp(d_text);

		if (getSelectionLength() != 0)
		{
			tmp.erase(getSelectionStartIndex(), getSelectionLength());

			if (!d_useRegex || isStringValid(tmp))
			{
				
				eraseSelectedText(false);

				
				setText(tmp);
			}
			else
			{
				
				WindowEventArgs args(this);
				onInvalidEntryAttempted(args);
			}

		}
		else if (getCaratIndex() > 0)
		{
			tmp.erase(d_caratPos - 1, 1);

			if (!d_useRegex || isStringValid(tmp))
			{
				setCaratIndex(d_caratPos - 1);

				
				setText(tmp);
			}
			else
			{
				
				WindowEventArgs args(this);
				onInvalidEntryAttempted(args);
			}

		}

	}

}



void Editbox::handleDelete(void)
{
	if (!isReadOnly())
	{
		String tmp(d_text);

		if (getSelectionLength() != 0)
		{
			tmp.erase(getSelectionStartIndex(), getSelectionLength());

			if (!d_useRegex || isStringValid(tmp))
			{
				
				eraseSelectedText(false);

				
				setText(tmp);
			}
			else
			{
				
				WindowEventArgs args(this);
				onInvalidEntryAttempted(args);
			}

		}
		else if (getCaratIndex() < tmp.length())
		{
			tmp.erase(d_caratPos, 1);

			if (!d_useRegex || isStringValid(tmp))
			{
				
				setText(tmp);
			}
			else
			{
				
				WindowEventArgs args(this);
				onInvalidEntryAttempted(args);
			}

		}

	}

}



void Editbox::handleCharLeft(uint sysKeys)
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



void Editbox::handleWordLeft(uint sysKeys)
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



void Editbox::handleCharRight(uint sysKeys)
{
	if (d_caratPos < d_text.length())
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



void Editbox::handleWordRight(uint sysKeys)
{
	if (d_caratPos < d_text.length())
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



void Editbox::handleHome(uint sysKeys)
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



void Editbox::handleEnd(uint sysKeys)
{
	if (d_caratPos < d_text.length())
	{
		setCaratIndex(d_text.length());
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


void Editbox::onReadOnlyChanged(WindowEventArgs& e)
{
	requestRedraw();
	fireEvent(EventReadOnlyModeChanged, e, EventNamespace);
}



void Editbox::onMaskedRenderingModeChanged(WindowEventArgs& e)
{
	requestRedraw();
	fireEvent(EventMaskedRenderingModeChanged , e, EventNamespace);
}



void Editbox::onMaskCodePointChanged(WindowEventArgs& e)
{
	
	if (isTextMasked())
	{
		requestRedraw();
	}

	fireEvent(EventMaskCodePointChanged , e, EventNamespace);
}



void Editbox::onValidationStringChanged(WindowEventArgs& e)
{
	fireEvent(EventValidationStringChanged , e, EventNamespace);
}



void Editbox::onMaximumTextLengthChanged(WindowEventArgs& e)
{
	fireEvent(EventMaximumTextLengthChanged , e, EventNamespace);
}



void Editbox::onTextInvalidatedEvent(WindowEventArgs& e)
{
	fireEvent(EventTextInvalidated, e, EventNamespace);
}



void Editbox::onInvalidEntryAttempted(WindowEventArgs& e)
{
	fireEvent(EventInvalidEntryAttempted , e, EventNamespace);
}



void Editbox::onCaratMoved(WindowEventArgs& e)
{
	requestRedraw();
	fireEvent(EventCaratMoved , e, EventNamespace);
}



void Editbox::onTextSelectionChanged(WindowEventArgs& e)
{
	requestRedraw();
	fireEvent(EventTextSelectionChanged , e, EventNamespace);
}



void Editbox::onEditboxFullEvent(WindowEventArgs& e)
{
	fireEvent(EventEditboxFull, e, EventNamespace);
}



void Editbox::onTextAcceptedEvent(WindowEventArgs& e)
{
	fireEvent(EventTextAccepted, e, EventNamespace);
}



void Editbox::onTabPressedEvent(WindowEventArgs& e)
{
	fireEvent(EventTabPressed, e, EventNamespace);
}



void Editbox::setNormalTextColour(const colour& col)
{
	d_normalTextColour = col;
	requestRedraw();
}



void Editbox::setSelectedTextColour(const colour& col)
{
	d_selectTextColour = col;
	requestRedraw();
}



void Editbox::setNormalSelectBrushColour(const colour& col)
{
	d_selectBrushColour = col;
	requestRedraw();
}



void Editbox::setInactiveSelectBrushColour(const colour& col)
{
	d_inactiveSelectBrushColour = col;
	requestRedraw();
}



void Editbox::onTextChanged(WindowEventArgs& e)
{
	
	Window::onTextChanged(e);

	
	clearSelection();

	
	if (getCaratIndex() > d_text.length())
	{
		setCaratIndex(d_text.length());
	}

	e.handled = true;
}


void Editbox::addEditboxProperties(void)
{
	CEGUI_START_ADD_STATICPROPERTY( Editbox );
	   CEGUI_ADD_STATICPROPERTY( &d_readOnlyProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_maskTextProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_maskCodepointProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_validationStringProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_caratIndexProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_selectionStartProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_selectionLengthProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_maxTextLengthProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_normalTextColourProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_selectedTextColourProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_activeSelectionColourProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_inactiveSelectionColourProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_forbidInputProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_useRegexProperty );
	   CEGUI_ADD_STATICPROPERTY( &d_lostFocusProperty );
	CEGUI_END_ADD_STATICPROPERTY
}

void Editbox::clearText( void )
{
	d_text.clear();

	WindowEventArgs args(this);
	onTextChanged(args);
};

} 
