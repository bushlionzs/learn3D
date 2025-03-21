#pragma once 

struct VoxelizationContext
{
    Ogre::RenderTarget* diffuseTarget;
    Ogre::RenderTarget* normalTarget;
    Ogre::RenderTarget* specularTarget;
    Ogre::RenderTarget* emissiveTarget;
    Ogre::RenderTarget* depthTarget;

    Ogre::RenderTarget* voxelizationTarget;
    Handle<HwSampler> voxelizationSampler;

    
    
    Ogre::RenderTarget* tracingResultTarget;
    Handle<HwSampler> tracingSampler;

    RenderPipeline* renderPipeline;
};