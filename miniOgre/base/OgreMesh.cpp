#include "OgreHeader.h"
#include "OgreMesh.h"
#include "OgreSubMesh.h"
#include "OgreHardwareBufferManager.h"
#include "OgreMaterial.h"
#include "renderSystem.h"
#include "OgreVertexData.h"
#include "OgreIndexData.h"
#include "OgreVertexDeclaration.h"
#include "OgreSkeletonManager.h"
#include "OgreSkeleton.h"
#include "OgreRoot.h"
#include <filament/FVertexBuffer.h>
#include <filament/FIndexBuffer.h>
#include <filament/OgreFilamentUtils.h>

namespace Ogre {
    Mesh::Mesh(const std::string& name)
    {
        mName = name;
        mVertexData = new VertexData;
        mIndexData = new IndexData;
        mAABB.setInfinite();
    }

    Mesh::~Mesh()
    {

    }

    SubMesh* Mesh::addSubMesh(bool shareVertices, bool shareIndex)
    {
        SubMesh* sub = new SubMesh(this, shareVertices, shareIndex);
        mSubMeshList.push_back(sub);
        return sub;
    }

    int32_t Mesh::getSubMeshCount()
    {
        return (int32_t)mSubMeshList.size();
    }

    SubMesh* Mesh::getSubMesh(int32_t index)
    {
        return mSubMeshList[index];
    }

    bool Mesh::hasSkeleton()
    {
        return !!mSkeleton;
    }

    std::shared_ptr<Skeleton>& Mesh::getSkeleton()
    {
        return mSkeleton;
    }

    void Mesh::applySkeleton(std::shared_ptr<Skeleton>& skeleton)
    {
        mSkeleton = skeleton;
    }

    void Mesh::setSkeletonName(const std::string& skelName)
    {
        mSkelName = skelName;

        mSkeleton = SkeletonManager::getSingletonPtr()->load(mSkelName);
    }

    void Mesh::_initAnimationState(AnimationStateSet* animSet)
    {
        if (mSkeleton)
        {
            // Delegate to Skeleton
            mSkeleton->_initAnimationState(animSet);

        }

        
    }

    void Mesh::_refreshAnimationState(AnimationStateSet* animSet)
    {
        if (mSkeleton)
        {
            mSkeleton->_refreshAnimationState(animSet);
        }
    }

    VertexData* Mesh::getVertexData()
    {
        return mVertexData;
    }

    IndexData* Mesh::getIndexData()
    {
        return mIndexData;
    }

    void Mesh::addBoneAssignment(const VertexBoneAssignment& vertBoneAssign)
    {
        mBoneAssignments.push_back(vertBoneAssign);
    }

    void Mesh::prepare()
    {
        
        if (!mBoneAssignments.empty())
        {
            mVertexData->addBoneInfo(mBoneAssignments);
        }

        if (mVertexData && !mVertexData->empty())
        {
            auto engine = Ogre::Root::getSingleton().getEngine();
            if (engine)
            {
                VertexBuffer::Builder vBuilder;
                auto vertexCount = mVertexData->getVertexCount();
                auto bufferCount = mVertexData->getBufferCount();
                vBuilder.vertexCount(vertexCount);
                vBuilder.bufferCount(bufferCount);

                VertexDeclaration* decl = mVertexData->getVertexDeclaration();

                const VertexDeclaration::VertexElementList& elist = decl->getElementList();

                for (auto& e : elist)
                {
                    auto bufferIndex = e.getIndex();
                    auto stride = decl->getVertexSize(bufferIndex);
                    auto offset = e.getOffset();
                    auto attributeType = filament::mappingOgreVertexType(e.getType());
                    auto attribute = filament::mappingOgreVertexAttribute(e.getSemantic());
                    vBuilder.attribute(attribute, bufferIndex, attributeType, offset, stride);
                }


                mVertexBuffer = vBuilder.build(*engine);
                for (auto i = 0; i < bufferCount; i++)
                {
                    auto buf = mVertexData->getBuffer(i);
                    if (buf)
                    {
                        void* data = buf->lock();
                        auto byteCount = buf->getSizeInBytes();
                        mVertexBuffer->setBufferAt(*engine, 0, { data, byteCount });
                    }
                }

                
                if (mIndexData)
                {
                    auto buf = mIndexData->getIndexBuffer();

                    auto indexCount = buf->getNumVerts();
                    auto indexType = IndexBuffer::IndexType::USHORT;
                    if (buf->getType() == HardwareIndexBuffer::IndexType::IT_32BIT)
                    {
                        indexType = IndexBuffer::IndexType::UINT;
                    };

                    mIndexBuffer = IndexBuffer::Builder()
                        .indexCount(indexCount)
                        .bufferType(indexType)
                        .build(*engine);

                    void* data = buf->lock();
                    auto byteCount = buf->getSizeInBytes();
                    mIndexBuffer->setBuffer(*engine, { data, buf->getSizeInBytes() });
                }
                

            }
        }
        
        
        for (auto sub : mSubMeshList)
        {
            sub->prepare();
        }
    }



    void Mesh::_setBounds(const AxisAlignedBox& bounds, bool pad)
    {
        mAABB = bounds;
    }

    const AxisAlignedBox& Mesh::getBounds(void) const
    {
        return mAABB;
    }

    const std::string& Mesh::getSkeletonName() const
    {
        return mSkelName;
    }
}
