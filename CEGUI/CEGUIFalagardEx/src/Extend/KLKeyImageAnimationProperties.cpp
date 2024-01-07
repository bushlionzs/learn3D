
#include "KLKeyImageAnimationProperties.h"
#include "KLKeyImageAnimation.h"
#include "CEGUIPropertyHelper.h"


namespace CEGUI
{
namespace KLKeyImageAnimationProperties
{

	String FalKeyImageAnimation::get(const PropertyReceiver* receiver) const
    {
        return "";
    }

    void FalKeyImageAnimation::set(PropertyReceiver* receiver, const String& value)
    {
		static_cast<KLKeyImageAnimation*>(receiver)->SetAnimate( value );
    }

}
}
