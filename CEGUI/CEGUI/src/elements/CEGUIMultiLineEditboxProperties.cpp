

#include "elements/CEGUIMultiLineEditboxProperties.h"
#include "elements/CEGUIMultiLineEditbox.h"
#include "CEGUIPropertyHelper.h"
#include "CEGUIExceptions.h"
#include "CEGUIFont.h"



namespace CEGUI
{


namespace MultiLineEditboxProperties
{
String ReadOnly::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::boolToString(static_cast<const MultiLineEditbox*>(receiver)->isReadOnly());
}


void ReadOnly::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<MultiLineEditbox*>(receiver)->setReadOnly(PropertyHelper::stringToBool(value));
}


String WordWrap::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::boolToString(static_cast<const MultiLineEditbox*>(receiver)->isWordWrapped());
}


void WordWrap::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<MultiLineEditbox*>(receiver)->setWordWrapping(PropertyHelper::stringToBool(value));
}

String WordBreak::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::boolToString(static_cast<const MultiLineEditbox*>(receiver)->isWordBreaked());
}


void WordBreak::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<MultiLineEditbox*>(receiver)->setWordBreaking(PropertyHelper::stringToBool(value));
}

String CaratIndex::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::uintToString(static_cast<uint>(static_cast<const MultiLineEditbox*>(receiver)->getCaratIndex()));
}


void CaratIndex::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<MultiLineEditbox*>(receiver)->setCaratIndex(PropertyHelper::stringToUint(value));
}


String SelectionStart::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::uintToString(static_cast<uint>(static_cast<const MultiLineEditbox*>(receiver)->getSelectionStartIndex()));
}


void SelectionStart::set(PropertyReceiver* receiver, const String& value)
{
	MultiLineEditbox* eb = static_cast<MultiLineEditbox*>(receiver);
	uint selStart = PropertyHelper::stringToUint(value);
	eb->setSelection(selStart, selStart + eb->getSelectionLength());
}


String SelectionLength::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::uintToString(static_cast<uint>(static_cast<const MultiLineEditbox*>(receiver)->getSelectionLength()));
}


void SelectionLength::set(PropertyReceiver* receiver, const String& value)
{
	MultiLineEditbox* eb = static_cast<MultiLineEditbox*>(receiver);
	uint selLen = PropertyHelper::stringToUint(value);
	eb->setSelection(eb->getSelectionStartIndex(), eb->getSelectionStartIndex() + selLen);
}


String MaxTextLength::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::uintToString(static_cast<uint>(static_cast<const MultiLineEditbox*>(receiver)->getMaxTextLength()));
}


void MaxTextLength::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<MultiLineEditbox*>(receiver)->setMaxTextLength(PropertyHelper::stringToUint(value));
}


String NormalTextColour::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::colourToString(static_cast<const MultiLineEditbox*>(receiver)->getNormalTextColour());
}


void NormalTextColour::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<MultiLineEditbox*>(receiver)->setNormalTextColour(PropertyHelper::stringToColour(value));
}


String SelectedTextColour::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::colourToString(static_cast<const MultiLineEditbox*>(receiver)->getSelectedTextColour());
}


void SelectedTextColour::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<MultiLineEditbox*>(receiver)->setSelectedTextColour(PropertyHelper::stringToColour(value));
}


String ActiveSelectionColour::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::colourToString(static_cast<const MultiLineEditbox*>(receiver)->getNormalSelectBrushColour());
}


void ActiveSelectionColour::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<MultiLineEditbox*>(receiver)->setNormalSelectBrushColour(PropertyHelper::stringToColour(value));
}


String InactiveSelectionColour::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::colourToString(static_cast<const MultiLineEditbox*>(receiver)->getInactiveSelectBrushColour());
}


void InactiveSelectionColour::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<MultiLineEditbox*>(receiver)->setInactiveSelectBrushColour(PropertyHelper::stringToColour(value));
}
String	OnReturnEnable::get(const PropertyReceiver* receiver) const
{
	return "";
}

void OnReturnEnable::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<MultiLineEditbox*>(receiver)->setReturnEnable(PropertyHelper::stringToBool(value));
}


String LostFocus::get(const PropertyReceiver* receiver) const
{
	return PropertyHelper::boolToString(static_cast<const MultiLineEditbox*>(receiver)->isLostFocus());
}


void LostFocus::set(PropertyReceiver* receiver, const String& value)
{
	static_cast<MultiLineEditbox*>(receiver)->setLostFocus(PropertyHelper::stringToBool(value));
}
} 

} 
