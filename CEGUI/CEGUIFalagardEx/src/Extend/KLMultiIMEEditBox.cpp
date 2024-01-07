#include "KLMultiIMEEditBox.h"
#include "falagard/CEGUIFalWidgetLookManager.h"
#include "falagard/CEGUIFalWidgetLookFeel.h"
#include "CEGUIInputMethodEditor.h"


namespace CEGUI
{
    const utf8  KLMultiIMEEditBox::WidgetTypeName[] = "Falagard/MultiIMEEditBox";

	KLMultiIMEEditBoxProperties::DefaultEditBox	KLMultiIMEEditBox::d_defaultEditBoxProperty;

    KLMultiIMEEditBox::KLMultiIMEEditBox(const String& type, const String& name) :
        FalagardMultiLineEditbox(type, name),
		d_lastTextOffset(0),
		d_caretOn(true),
		d_lastTextLen(0)
    {
        addMultiIMEEditBoxProperties();

		d_blinkTime = ImeModule::GetCaretBlinkTime()*0.001f;
		d_lastBlink = System::getSingleton().getCurTimeElapsed();
	}

    KLMultiIMEEditBox::~KLMultiIMEEditBox()
    {
    }

	void KLMultiIMEEditBox::addMultiIMEEditBoxProperties(void)
    {
		CEGUI_START_ADD_STATICPROPERTY( KLMultiIMEEditBox )
		   CEGUI_ADD_STATICPROPERTY( &d_defaultEditBoxProperty );
		CEGUI_END_ADD_STATICPROPERTY
	}

	bool KLMultiIMEEditBox::hasInputFocus(void) const
	{
		return ImeModule::GetActiveIMEEditBox() == this;
	}
	void KLMultiIMEEditBox::updateSelf(float elapsed)
	{
		float time_now = System::getSingleton().getCurTimeElapsed();

		int textLen = (int)getText().size();
		if(textLen != d_lastTextLen) 
		{
			resetCaretBlink();
			d_lastTextLen = textLen;
		}

		
		
		
		if( time_now - d_lastBlink >= d_blinkTime )
		{
			d_caretOn = !d_caretOn;
			d_lastBlink = time_now;

			requestRedraw();
		}

		FalagardMultiLineEditbox::updateSelf(elapsed);
	}

	void KLMultiIMEEditBox::cacheCaratImagery(const Rect& textArea)
	{
		if( hasInputFocus() && d_caretOn )
			FalagardMultiLineEditbox::cacheCaratImagery( textArea );
	}
    
	void KLMultiIMEEditBox::resetCaretBlink(void)
	{
		d_caretOn = true;
		d_lastBlink = System::getSingleton().getCurTimeElapsed();
		requestRedraw();
	}

	void KLMultiIMEEditBox::onCaratMoved(WindowEventArgs& e)
	{
		resetCaretBlink();
		fireEvent(EventCaratMoved , e, EventNamespace);
	}

	void KLMultiIMEEditBox::onActivated(ActivationEventArgs& e)
	{
		FalagardMultiLineEditbox::onActivated(e);

		if( !isReadOnly() )
		ImeModule::SetActiveIMEEditBox(this, true);
	}
		
	void KLMultiIMEEditBox::onDeactivated(ActivationEventArgs& e)
	{
		FalagardMultiLineEditbox::onDeactivated(e);
	}
	
	void KLMultiIMEEditBox::onMouseButtonDown(MouseEventArgs& e)
	{
		
		FalagardMultiLineEditbox::onMouseButtonDown(e);

		if( !isReadOnly() )
		ImeModule::SetActiveIMEEditBox(this, true);
	}

	void KLMultiIMEEditBox::onParentHidden(void)
	{
		
		FalagardMultiLineEditbox::onParentHidden();

		if( !isReadOnly() )
		ImeModule::SetActiveIMEEditBox(this, false);
	}
    
    Window* KLMultiIMEEditBoxFactory::createWindow(const String& name)
    {
        return new KLMultiIMEEditBox(d_type, name);
    }

    void KLMultiIMEEditBoxFactory::destroyWindow(Window* window)
    {
		delete window;
    }

}

	