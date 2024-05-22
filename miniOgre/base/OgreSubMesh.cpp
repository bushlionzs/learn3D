#include "OgreHeader.h"
#include "OgreSubMesh.h"
#include "OgreHardwareBufferManager.h"
#include "OgreMaterial.h"
#include "OgreMesh.h"
#include "renderSystem.h"
#include "OgreVertexData.h"
#include "OgreIndexData.h"
#include "OgreVertexDeclaration.h"
#include "OgreRoot.h"
#include <filament/FVertexBuffer.h>
#include <filament/FIndexBuffer.h>
#include <filament/OgreFilamentUtils.h>


namespace Ogre {
    SubMesh::SubMesh(
        Mesh* mesh, 
        bool sharedVertices,
        bool sharedIndex
    )
    {
        mParent = mesh;
        mIndexView.mIndexCount = 0;
        mIndexView.mBaseVertexLocation = 0;
        mIndexView.mIndexLocation = 0;

        mSharedVertices = sharedVertices;
        mSharedIndex = sharedIndex;
        if (!sharedVertices)
        {
            mVertexData = new VertexData;
            
        }
        else
        {
            mVertexData = nullptr;
            
        }

        if (!sharedIndex)
        {
            mIndexData = new IndexData;
        }
        else
        {
            mIndexData = nullptr;
        }

        mPosition = Ogre::Vector3::ZERO;
    }

    SubMesh::~SubMesh()
    {

    }


    

    VertexData* SubMesh::getVertexData()
    {
        if (mSharedVertices)
        {
            return mParent->getVertexData();
        }
        return mVertexData;
    }

    IndexData* SubMesh::getIndexData()
    {
        if (mSharedIndex)
        {
            return mParent->getIndexData();
        }
        return mIndexData;
    }

    OperationType SubMesh::getOperationType()
    {
        return mOperationType;
    }

    void SubMesh::setOperationType(OperationType ot)
    {
        mOperationType = ot;
    }


    void SubMesh::addIndexs(
        uint32_t drawCount,
        uint32_t indexLocation,
        uint32_t baseVertexLocation)
    {
        mIndexView.mIndexCount = drawCount;
        mIndexView.mIndexLocation = indexLocation;
        mIndexView.mBaseVertexLocation = baseVertexLocation;
    }


    IndexDataView* SubMesh::getIndexView()
    {
        return &mIndexView;
    }

    void SubMesh::setMaterial(std::shared_ptr<Material>& mat)
    {
        mMaterial = mat;
    }

    const std::shared_ptr<Material>& SubMesh::getMaterial()
    {
        return mMaterial;
    }

    void SubMesh::setMaterialName(std::string& name)
    {
        mMatName = name;
    }

    const std::string& SubMesh::getMaterialName()
    {
        return mMatName;
    }

    void SubMesh::addBoneAssignment(const VertexBoneAssignment& vertBoneAssign)
    {
        mBoneAssignments.push_back(vertBoneAssign);
    }

    void SubMesh::prepare()
    {
        if (!mBoneAssignments.empty())
        {
            mVertexData->addBoneInfo(mBoneAssignments);
        }
        auto engine = Ogre::Root::getSingleton().getEngine();
        if (engine)
        {
            VertexBuffer* vb = nullptr;
            IndexBuffer* ib = nullptr;
            if (mVertexData)
            {
                VertexBuffer::Builder vBuilder;

                auto bufferCount = mVertexData->getBufferCount();
                vBuilder.vertexCount(mVertexData->getVertexCount());
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


                vb = vBuilder.build(*engine);
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

                ib = IndexBuffer::Builder()
                    .indexCount(indexCount)
                    .bufferType(indexType)
                    .build(*engine);

                ib->setBuffer(*engine, { buf->lock(), buf->getSizeInBytes() });
            }
            

            if (vb == nullptr)
            {
                vb = mParent->getVertexBuffer();
            }

            if (ib == nullptr)
            {
                ib = mParent->getIndexbuffer();
            }
            updateBuffer(vb, ib);
        }
        
    }


    void SubMesh::setPosition(Ogre::Vector3& pos)
    {
        mPosition = pos;
    }


    const Ogre::Vector3& SubMesh::getPosition()
    {
        return mPosition;
    }
}