#pragma once

#include "OgreLight.h"
#include "OgreColourValue.h"



#define MaxLightsEachType 4



struct TestConstantBuffer
{
    Ogre::Matrix4 world = Ogre::Matrix4::IDENTITY;
    Ogre::Matrix4 view = Ogre::Matrix4::IDENTITY;
    Ogre::Matrix4 proj = Ogre::Matrix4::IDENTITY;
};







