#pragma once

#include <utils/Allocator.h>
#include <utils/JobSystem.h>


struct SyncToken
{
    utils::JobSystem::Job* rootJob;
};

struct LoadDesc
{
    const char* pFileName;
};
struct MeshLoadDesc: public LoadDesc
{
    Ogre::Mesh* pMesh;
} ;

struct TextureLoadDesc: public LoadDesc
{
    Ogre::TextureProperty* tp;
    Ogre::OgreTexture* pTexture;
};