

#include "elements/CEGUIComboDropList.h"
#include "elements/CEGUIScrollbar.h"



namespace CEGUI
{
const String ComboDropList::EventNamespace("ComboDropList");



const String ComboDropList::EventListSelectionAccepted( (utf8*)"ListSelectionAccepted" );



ComboDropList::ComboDropList(const String& type, const String& name) :
	Listbox(type, name)
{
	d_autoArm = false;
	d_armed = false;

	hide();

    
    setDistributesCapturedInputs(true);
}



ComboDropList::~ComboDropList(void)
{
}



void ComboDropList::initialise(void)
{
	Listbox::initialise();

	
	if( d_vertScrollbar )
		d_vertScrollbar->setRestoreCapture(true);
	if( d_horzScrollbar )
		d_horzScrollbar->setRestoreCapture(true);
}


void ComboDropList::onListSelectionAccepted(WindowEventArgs& e)
{
	fireEvent(EventListSelectionAccepted, e, EventNamespace);
}



void ComboDropList::onMouseMove(MouseEventArgs& e)
{
	Listbox::onMouseMove(e);

	
	if (isHit(e.position))
	{
		if (getChildAtPosition(e.position) == NULL)
		{
			
			if (d_autoArm)
			{
				d_armed = true;
			}

			if (d_armed)
			{
				
				
				
				Point localPos(screenToWindow(e.position));

				if (getMetricsMode() == Relative)
				{
					localPos = relativeToAbsolute(localPos);
				}

				
				ListboxItem* selItem = getItemAtPoint(localPos);

				
				if (selItem != NULL)
				{
					setItemSelectState(selItem, true);
				}
				else
				{
					clearAllSelections();
				}

			}
		}

		e.handled = true;
	}
	
	else
	{
		
		if (e.sysKeys & LeftMouse)
		{
			clearAllSelections();
		}

	}

}



void ComboDropList::onMouseButtonDown(MouseEventArgs& e)
{
	Listbox::onMouseButtonDown(e);

	if (e.button == LeftButton)
	{
		if (!isHit(e.position))
		{
			clearAllSelections();
			releaseInput();
		}
		else
		{
			d_armed = true;
		}

		e.handled = true;
	}

}

void ComboDropList::onSized(WindowEventArgs& e)
{
	Window::onSized(e);

	if( d_visible )
	{
		clearAllSelections();
		releaseInput();
	}
}




void ComboDropList::onMouseButtonUp(MouseEventArgs& e)
{
	Listbox::onMouseButtonUp(e);

	if (e.button == LeftButton)
	{
		if (d_armed && (getChildAtPosition(e.position) == NULL))
		{
			releaseInput();

			
			if (getSelectedCount() > 0)
			{
				WindowEventArgs args(this);
				onListSelectionAccepted(args);
			}

		}
		
		else
		{
			d_armed = true;
		}

		e.handled = true;
	}

}



void ComboDropList::onCaptureLost(WindowEventArgs& e)
{
	Listbox::onCaptureLost(e);
	d_armed = false;
	hide();
	e.handled = true;
}



void ComboDropList::onActivated(ActivationEventArgs& e)
{
	Listbox::onActivated(e);
}


void ComboDropList::resizeSelf(void)
{
	Rect rect = getListRenderArea();
	float fWidth = getAbsoluteWidth();
	float fHeight = getTotalItemsHeight();

	float fMaxHeight = System::getSingleton().getRenderer()->getHeight() - getPixelRect().getPosition().d_y - 20;

	fHeight += rect.d_top * 2;
	if( fHeight > fMaxHeight )
		fHeight = fMaxHeight;
	setSize( Absolute, Size( fWidth, fHeight ) );
	d_vertScrollbar->setPageSize( fHeight );
	d_vertScrollbar->setDocumentSize( fHeight );
}

void ComboDropList::repositionSelf(Window *editbox)
{
	
	const int MAX_LINE = 10;

	float fWidth = getAbsoluteWidth();
	float fTotalHeight = getTotalItemsHeight();
	float fHeight = getItemHeight();
	if( fHeight > 0 )
		fHeight *= MAX_LINE;

	Rect rect = getListRenderArea();
	fTotalHeight += rect.d_top * 2;
	fHeight += rect.d_top * 2;

	float ScreenHeight = System::getSingleton().getRenderer()->getHeight();
	float fMaxHeight1 = ScreenHeight - editbox->getPixelRect().d_bottom - 20;

	if( fTotalHeight > fHeight )
	{
		if( fHeight > fMaxHeight1 )
		{
			if(editbox)
			{
				Rect parentrect = editbox->getPixelRect();
				float fMaxHeight2 = parentrect.d_top - 20;
				if( fMaxHeight2 >= fHeight )
				{
					Point position = editbox->getPosition(Absolute);
					position.d_y = position.d_y-fHeight;
					setPosition(Absolute,position);
					setSize( Absolute, Size( fWidth, fHeight ) );
					d_vertScrollbar->setPageSize( fHeight - rect.d_top * 2 );
					d_vertScrollbar->setDocumentSize( fTotalHeight );
				}
				
				
				
				
			}
			else
			{
				resizeSelf();
				return;
			}
		}
		else
		{
			Point position = editbox->getPosition(Absolute);
			Size size = editbox->getSize(Absolute);
			position.d_y = position.d_y + size.d_height;
			setPosition(Absolute,position);		

			setSize( Absolute, Size( fWidth, fHeight ) );
			d_vertScrollbar->setPageSize( fHeight - rect.d_top * 2 );
			d_vertScrollbar->setDocumentSize( fTotalHeight );
		}
	}
	else
	{
		if( fTotalHeight > fMaxHeight1 )
		{
			if(editbox)
			{
				Rect parentrect = editbox->getPixelRect();
				float fMaxHeight2 = parentrect.d_top - 20;
				if( fMaxHeight2 >= fTotalHeight )
				{
					Point position = editbox->getPosition(Absolute);
					position.d_y = position.d_y - fTotalHeight;
					setPosition(Absolute,position);

					setSize( Absolute, Size( fWidth, fTotalHeight ) );
					d_vertScrollbar->setPageSize( fTotalHeight - rect.d_top * 2 );
					d_vertScrollbar->setDocumentSize( fTotalHeight );
				}
				
				
				
				
			}
			else
			{
				resizeSelf();
				return;
			}
		}
		else
		{
			Point position = editbox->getPosition(Absolute);
			Size size = editbox->getSize(Absolute);
			position.d_y = position.d_y + size.d_height;
			setPosition(Absolute,position);		
			
			setSize( Absolute, Size( fWidth, fTotalHeight ) );
			d_vertScrollbar->setScrollPosition( 0 );
			d_vertScrollbar->setPageSize( fTotalHeight );
			d_vertScrollbar->setDocumentSize( fTotalHeight );
			d_vertScrollbar->hide();
		}
	}
}

} 
