

#include "elements/CEGUIEditboxProperties.h"
#include "elements/CEGUIEditbox.h"
#include "CEGUIPropertyHelper.h"
#include "CEGUIExceptions.h"
#include <cstdlib>
#include <cstdio>



namespace CEGUI
{


namespace EditboxProperties
{

String ReadOnly::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::boolToString(static_cast<const Editbox*>(receiver)->isReadOnly());
}


void ReadOnly::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<Editbox*>(receiver)->setReadOnly(PropertyHelper::stringToBool(value));
}


String MaskText::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::boolToString(static_cast<const Editbox*>(receiver)->isTextMasked());
}


void MaskText::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<Editbox*>(receiver)->setTextMasked(PropertyHelper::stringToBool(value));
}


String MaskCodepoint::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::uintToString(static_cast<const Editbox*>(receiver)->getMaskCodePoint());
}


void MaskCodepoint::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<Editbox*>(receiver)->setMaskCodePoint(PropertyHelper::stringToUint(value));
}


String ValidationString::get(const PropertyReceiver* receiver) const
{
	return static_cast<const Editbox*>(receiver)->getValidationString();
}


void ValidationString::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<Editbox*>(receiver)->setValidationString(value);
}


String CaratIndex::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::uintToString(static_cast<uint>(static_cast<const Editbox*>(receiver)->getCaratIndex()));
}


void CaratIndex::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<Editbox*>(receiver)->setCaratIndex(PropertyHelper::stringToUint(value));
}


String SelectionStart::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::uintToString(static_cast<uint>(static_cast<const Editbox*>(receiver)->getSelectionStartIndex()));
}


void SelectionStart::set(PropertyReceiver* receiver, const String& value)
{
	Editbox* eb = static_cast<Editbox*>(receiver);
	uint selStart = PropertyHelper::stringToUint(value);
	eb->setSelection(selStart, selStart + eb->getSelectionLength());
}


String SelectionLength::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::uintToString(static_cast<uint>(static_cast<const Editbox*>(receiver)->getSelectionLength()));
}


void SelectionLength::set(PropertyReceiver* receiver, const String& value)
{
	Editbox* eb = static_cast<Editbox*>(receiver);
	uint selLen = PropertyHelper::stringToUint(value);
	eb->setSelection(eb->getSelectionStartIndex(), eb->getSelectionStartIndex() + selLen);
}


String MaxTextLength::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::uintToString(static_cast<uint>(static_cast<const Editbox*>(receiver)->getMaxTextLength()));
}


void MaxTextLength::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<Editbox*>(receiver)->setMaxTextLength(PropertyHelper::stringToUint(value));
}


String NormalTextColour::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::colourToString(static_cast<const Editbox*>(receiver)->getNormalTextColour());
}


void NormalTextColour::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<Editbox*>(receiver)->setNormalTextColour(PropertyHelper::stringToColour(value));
}


String SelectedTextColour::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::colourToString(static_cast<const Editbox*>(receiver)->getSelectedTextColour());
}


void SelectedTextColour::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<Editbox*>(receiver)->setSelectedTextColour(PropertyHelper::stringToColour(value));
}


String ActiveSelectionColour::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::colourToString(static_cast<const Editbox*>(receiver)->getNormalSelectBrushColour());
}


void ActiveSelectionColour::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<Editbox*>(receiver)->setNormalSelectBrushColour(PropertyHelper::stringToColour(value));
}


String InactiveSelectionColour::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::colourToString(static_cast<const Editbox*>(receiver)->getInactiveSelectBrushColour());
}


void InactiveSelectionColour::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<Editbox*>(receiver)->setInactiveSelectBrushColour(PropertyHelper::stringToColour(value));
}


String ForbidInput::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::boolToString(static_cast<const Editbox*>(receiver)->isForbidInput());
}


void ForbidInput::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<Editbox*>(receiver)->setForbidInput(PropertyHelper::stringToBool(value));
}


String UseRegex::get(const PropertyReceiver* receiver) const
{
	return ""; 
}


void UseRegex::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<Editbox*>(receiver)->setUseRegex(PropertyHelper::stringToBool(value));
}

String LostFocus::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::boolToString(static_cast<const Editbox*>(receiver)->isLostFocus());
}


void LostFocus::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<Editbox*>(receiver)->setLostFocus(PropertyHelper::stringToBool(value));
}


} 

} 
