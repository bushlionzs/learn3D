#pragma once
#include "OgreMatrix4.h"

namespace Ogre {
    class  OrientedBoundingBox
    {
    public:
        Vector3 origin;
        Quaternion rotation;
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

