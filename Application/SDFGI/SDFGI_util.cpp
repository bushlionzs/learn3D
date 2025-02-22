#include <OgreHeader.h>

Ogre::Matrix3 EulerAnglesToRotationMatrix(const Ogre::Vector3& eulerAngles)
{
    float sx = sinf(eulerAngles.x);
    float cx = cosf(eulerAngles.x);
    float sy = sinf(eulerAngles.y);
    float cy = cosf(eulerAngles.y);
    float sz = sinf(eulerAngles.z);
    float cz = cosf(eulerAngles.z);

    


    // Rxyz = Rx (pitch) * Ry (yaw) * Rz (roll)
    Ogre::Matrix3 rotation = {
         cy * cz,                       -cy * sz,                     sy ,
         cx * sz + cz * sx * sy, cx * cz - sx * sy * sz,  -cy * sx ,
         sx * sz - cx * cz * sy,  cz * sx + cx * sy * sz, cx * cy ,
    };


    return rotation;
}

uint32_t DivRoundUp(uint32_t x, uint32_t y)
{
    if (x % y) return 1 + x / y;
    else return x / y;
}