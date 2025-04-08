#include <OgreHeader.h>
#include "sdfUtil.h"
#include "OgreResourceManager.h"
#include "SDF_Constant.h"

bool GenerateVolumeDataFromFile(SDFVolumeData** ppOutVolumeData, MeshInfo* pMeshInfo)
{
    ResourceInfo* resInfo = Ogre::ResourceManager::getSingleton().getResourceInfo(pMeshInfo->name);

    if (nullptr == resInfo)
    {
        assert_invariant(false);
        return false;
    }

    Ogre::DataStreamPtr stream = Ogre::ResourceManager::getSingleton().openResource(pMeshInfo->name);


    *ppOutVolumeData = new(SDFVolumeData);
    SDFVolumeData& outVolumeData = **ppOutVolumeData;
    int32_t x, y, z;
    stream->read(&x, sizeof(int32_t));
    stream->read(&y, sizeof(int32_t));
    stream->read(&z, sizeof(int32_t));
    outVolumeData.mSDFVolumeSize.x = x;
    outVolumeData.mSDFVolumeSize.y = y;
    outVolumeData.mSDFVolumeSize.z = z;

    uint32_t finalSDFVolumeDataCount = x * y * z;

    outVolumeData.mSDFVolumeList.resize(finalSDFVolumeDataCount);
    stream->read(outVolumeData.mSDFVolumeList.data(), finalSDFVolumeDataCount * sizeof(float));
    Ogre::Vector3 minBounds;
    Ogre::Vector3 maxBounds;

    stream->read(&minBounds, sizeof(Ogre::Vector3));
    stream->read(&maxBounds, sizeof(Ogre::Vector3));

    outVolumeData.mLocalBoundingBox.setMinimum(minBounds);
    outVolumeData.mLocalBoundingBox.setMaximum(maxBounds);
    stream->read(&outVolumeData.mIsTwoSided, sizeof(bool));
    outVolumeData.mTwoSidedWorldSpaceBias = pMeshInfo->twoSidedWorldSpaceBias;
    return true;
}






#define UNREF_PARAM(x)         ((void)(x))



void loadBakedSDFData(
    SDFMesh* outMesh, 
    uint32_t startIdx, 
    bool generateSDFVolumeData, 
    std::vector<SDFVolumeData*>& sdfVolumeInstances)
{
    UNREF_PARAM(generateSDFVolumeData);
    uint32_t idxFirstMeshInGroup = 0;

    // for each submesh group.
    // in case there is no submesh groups, numSubMeshesGroups = numSubMeshes in the geometry
    for (uint32_t groupNum = 0; groupNum < outMesh->numSubMeshesGroups; ++groupNum)
    {
        MeshInfo& meshInfo = outMesh->pSubMeshesInfo[idxFirstMeshInGroup];
        uint32_t       meshGroupSize = outMesh->pSubMeshesGroupsSizes ? outMesh->pSubMeshesGroupsSizes[groupNum] : 1;
        SDFVolumeData* volumeData = nullptr;

        GenerateVolumeDataFromFile(&volumeData, &meshInfo);

        sdfVolumeInstances.push_back(volumeData);

        if (volumeData)
        {
            meshInfo.sdfGenerated = true;
            ++outMesh->numGeneratedSDFMeshes;
        }

        idxFirstMeshInGroup += meshGroupSize;
    }
}


Ogre::Vector3 calculateAABBExtent(const Ogre::AxisAlignedBox* ownerAABB)
{ 
    return 0.5f * (ownerAABB->getMaximum() - ownerAABB->getMinimum());
}

Ogre::Vector3 calculateAABBCenter(const Ogre::AxisAlignedBox* ownerAABB) 
{ 
    return (ownerAABB->getMaximum() + ownerAABB->getMinimum()) * 0.5f;
}

