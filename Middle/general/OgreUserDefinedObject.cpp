#include "OgreHeader.h"
#include "OgreUserDefinedObject.h"
#include "OgreString.h"

namespace Ogre
{

    UserDefinedObject::UserDefinedObject()
    {
    }

    long UserDefinedObject::getTypeID(void) const
    {
        return 0;
    }
    const String& UserDefinedObject::getTypeName(void) const
    {
        static String sName("Unspecified");
        return sName;
    }

}

