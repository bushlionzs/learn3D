

#include "FalTabControlProperties.h"
#include "FalTabControl.h"


namespace CEGUI
{
namespace FalagardTabControlProperties
{
String TabButtonType::get(const PropertyReceiver* receiver) const
{
    return static_cast<const FalagardTabControl*>(receiver)->getTabButtonType();
}

void TabButtonType::set(PropertyReceiver* receiver, const String &value)
{
    static_cast<FalagardTabControl*>(receiver)->setTabButtonType(value);
}

}

} 
