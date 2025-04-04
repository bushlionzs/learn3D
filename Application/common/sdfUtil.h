#pragma once
#include "SDF_Constant.h"
struct MeshInfo
{
    const char* name = nullptr;
    uint32_t materialFlags = MATERIAL_FLAG_NONE;
    float         twoSidedWorldSpaceBias = 0.0f;
    bool          sdfGenerated = false;
};
struct SDFVolumeData;
struct SDFVolumeTextureNode
{
    Vector3i          mAtlasAllocationCoord;
    SDFVolumeData* mSDFVolumeData;
    // the coordinate of this node inside the volume texture atlases
    // not in texel space
    bool mHasBeenAdded;

    SDFVolumeTextureNode(SDFVolumeData* sdfVolumeData) :
    mAtlasAllocationCoord(-1, -1, -1), mSDFVolumeData(sdfVolumeData),

        mHasBeenAdded(false)
    {
    }
};

struct SDFVolumeData
{
    std::vector<float> mSDFVolumeList;
    // Size of the distance volume
    Vector3i mSDFVolumeSize;
    // Local Space of the Bounding Box volume
    Ogre::AxisAlignedBox  mLocalBoundingBox;

    // stores the min & the maximum distances found in the volume
    // in the space of the world voxel volume
    // x stores the minimum while y stores the maximum
    Vector2  mDistMinMax;
    //
    bool  mIsTwoSided;
    //
    float mTwoSidedWorldSpaceBias;

    SDFVolumeTextureNode mSDFVolumeTextureNode;

    SDFVolumeData() :mSDFVolumeTextureNode(this)
    {
        mSDFVolumeSize.x = mSDFVolumeSize.y = mSDFVolumeSize.z = 0;
        mDistMinMax.x = FLT_MAX;
        mDistMinMax.y = FLT_MIN;
        mIsTwoSided = false;
        mTwoSidedWorldSpaceBias = 0.0f;
    }
};

struct SDFMesh
{
    MeshInfo* pSubMeshesInfo = nullptr;
    uint32_t* pSubMeshesGroupsSizes = nullptr;
    uint32_t* pSubMeshesIndices = nullptr;
    uint32_t      numSubMeshesGroups = 0;
    uint32_t      numGeneratedSDFMeshes = 0;
};

void loadBakedSDFData(
    SDFMesh* outMesh,
    uint32_t startIdx,
    bool generateSDFVolumeData,
    std::vector<SDFVolumeData*>& sdfVolumeInstances);

struct SDFTextureLayoutNode
{
    // node coord not in texel space but in raw volume dimension space
    Ogre::Vector3i mNodeCoord;
    Ogre::Vector3i mNodeSize;
    bool  mUsed;
};

struct SDFVolumeTextureAtlasLayout
{
    ~SDFVolumeTextureAtlasLayout()
    {
    }

    SDFVolumeTextureAtlasLayout(const Ogre::Vector3i& atlasLayoutSize)
        : mAtlasLayoutSize(atlasLayoutSize)
    {
        mAllocationCoord =
            Ogre::Vector3i(-SDF_MAX_VOXEL_ONE_DIMENSION_X, 0,
                SDF_DOUBLE_MAX_VOXEL_ONE_DIMENSION_Z * 3);
        mDoubleAllocationCoord =
            Ogre::Vector3i(-SDF_DOUBLE_MAX_VOXEL_ONE_DIMENSION_X, 0, 0);
    }

    bool AddNewNode(const Ogre::Vector3i& volumeDimension, Ogre::Vector3i& outCoord)
    {
        if (volumeDimension.x <= SDF_MAX_VOXEL_ONE_DIMENSION_X &&
            volumeDimension.y <= SDF_MAX_VOXEL_ONE_DIMENSION_Y &&
            volumeDimension.z <= SDF_MAX_VOXEL_ONE_DIMENSION_Z)
        {
            return AddNormalNode(volumeDimension, outCoord);
        }
        return AddDoubleNode(volumeDimension, outCoord);
    }

    bool AddNormalNode(const Ogre::Vector3i& volumeDimension, Ogre::Vector3i& outCoord)
    {
        if ((mAllocationCoord.x + (SDF_MAX_VOXEL_ONE_DIMENSION_X * 2)) <= mAtlasLayoutSize.x)
        {
            mAllocationCoord.x = (mAllocationCoord.x + SDF_MAX_VOXEL_ONE_DIMENSION_X);
            mNodes.push_back(SDFTextureLayoutNode{ mAllocationCoord, volumeDimension, false });
        }
        else if ((mAllocationCoord.y + (SDF_MAX_VOXEL_ONE_DIMENSION_Y * 2)) <= mAtlasLayoutSize.y)
        {
            mAllocationCoord.x = 0;
            mAllocationCoord.y = (mAllocationCoord.y + SDF_MAX_VOXEL_ONE_DIMENSION_Y);
            mNodes.push_back(SDFTextureLayoutNode{ mAllocationCoord, volumeDimension, false });
        }
        else if ((mAllocationCoord.z + (SDF_MAX_VOXEL_ONE_DIMENSION_Z * 2)) <= mAtlasLayoutSize.z)
        {
            mAllocationCoord.x = 0;
            mAllocationCoord.y = 0;
            mAllocationCoord.z = (mAllocationCoord.z + SDF_MAX_VOXEL_ONE_DIMENSION_Z);
            mNodes.push_back(SDFTextureLayoutNode{ mAllocationCoord, volumeDimension, false });
        }
        else
        {
            return false;
        }
        outCoord = mAllocationCoord;
        return true;
    }
    bool AddDoubleNode(const Ogre::Vector3i& volumeDimension, Ogre::Vector3i& outCoord)
    {
        if ((mDoubleAllocationCoord.x + (SDF_DOUBLE_MAX_VOXEL_ONE_DIMENSION_X * 2)) <= mAtlasLayoutSize.x)
        {
            mDoubleAllocationCoord.x = (mDoubleAllocationCoord.x + SDF_DOUBLE_MAX_VOXEL_ONE_DIMENSION_X);
            mNodes.push_back(SDFTextureLayoutNode{ mDoubleAllocationCoord, volumeDimension });
        }
        else if ((mDoubleAllocationCoord.y + (SDF_DOUBLE_MAX_VOXEL_ONE_DIMENSION_Y * 2)) <= mAtlasLayoutSize.y)
        {
            mDoubleAllocationCoord.x = 0;
            mDoubleAllocationCoord.y = (mDoubleAllocationCoord.y + SDF_DOUBLE_MAX_VOXEL_ONE_DIMENSION_Y);
            mNodes.push_back(SDFTextureLayoutNode{ mDoubleAllocationCoord, volumeDimension });
        }
        else if ((mDoubleAllocationCoord.z + (SDF_DOUBLE_MAX_VOXEL_ONE_DIMENSION_Z * 2)) <= mAtlasLayoutSize.z)
        {
            mDoubleAllocationCoord.x = 0;
            mDoubleAllocationCoord.y = 0;
            mDoubleAllocationCoord.z = (mDoubleAllocationCoord.z + SDF_DOUBLE_MAX_VOXEL_ONE_DIMENSION_Z);
            mNodes.push_back(SDFTextureLayoutNode{ mDoubleAllocationCoord, volumeDimension });
        }
        else
        {
            return false;
        }
        outCoord = mDoubleAllocationCoord;
        return true;
    }

    std::vector<SDFTextureLayoutNode> mNodes;

    Ogre::Vector3i mAtlasLayoutSize;
    Ogre::Vector3i mAllocationCoord;
    Ogre::Vector3i mDoubleAllocationCoord;
};

struct SDFVolumeTextureAtlas
{
    SDFVolumeTextureAtlas(const Ogre::Vector3i& atlasSize) :
        mSDFVolumeAtlasLayout(atlasSize) {
    }

    ~SDFVolumeTextureAtlas()
    {
        mNextNodeIndex = 0;
    }

    void AddVolumeTextureNode(SDFVolumeTextureNode* volumeTextureNode)
    {
        if (volumeTextureNode->mHasBeenAdded)
        {
            return;
        }

        mSDFVolumeAtlasLayout.AddNewNode(
            volumeTextureNode->mSDFVolumeData->mSDFVolumeSize,
            volumeTextureNode->mAtlasAllocationCoord);

        mPendingNodeQueue.push_back(volumeTextureNode);
        volumeTextureNode->mHasBeenAdded = true;
    }

    SDFVolumeTextureNode* ProcessQueuedNode()
    {
        if (mNextNodeIndex >= mPendingNodeQueue.size())
        {
            return nullptr;
        }

        return mPendingNodeQueue[mNextNodeIndex++];
    }

    SDFVolumeTextureAtlasLayout mSDFVolumeAtlasLayout;

    size_t mNextNodeIndex = 0;
    std::vector<SDFVolumeTextureNode*> mPendingNodeQueue;
};

Vector3 calculateAABBExtent(const Ogre::AxisAlignedBox* ownerAABB);

Vector3 calculateAABBCenter(const AxisAlignedBox* ownerAABB);