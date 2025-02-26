#pragma once
#include "OgreMatrix4.h"

namespace Ogre {
    class  OrientedBoundingBox
    {
    public:
        Vector3 origin;
        Vector4 rotation;
        Vector3 e;          
    public:
        inline OrientedBoundingBox() 
        {

        }

        OrientedBoundingBox& operator=(const OrientedBoundingBox& rhs)
        {      
            return *this;
        }

        ~OrientedBoundingBox()
        {
        }
    };

    /** @} */
    /** @} */
} // namespace Ogre

