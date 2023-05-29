#include "OgreHeader.h"
#include "OGMeshInformer.h"

#include <OgreMesh.h>
#include <OgreSubMesh.h>
#include <OgreEntity.h>
#include <OgreSubEntity.h>

#include "vertex_data.h"
#include "vertex_declaration.h"
#include "index_data.h"
#include "OgreHardwareIndexBuffer.h"
#include "OgreRenderOperation.h"

namespace Orphigine {
    using namespace Ogre;

    //-----------------------------------------------------------------------
    size_t
    MeshInformer::getVertices(Vector3* pDst,
                              const VertexData* vertexData)
    {
        const VertexElement* posElem = 
            vertexData->vertexDeclaration->findElementBySemantic(VES_POSITION);
        HardwareVertexBufferSharedPtr vbuf = vertexData->getBuffer(posElem->getSource());
        size_t vertex_stride = vbuf->getVertexSize();
        size_t vertexCount = vertexData->vertexCount;

        void* pBase = vbuf->lock(
            HardwareBuffer::HBL_READ_ONLY);

        float* pFloat; 
        posElem->baseVertexPointerToElement(pBase, &pFloat);
        for (size_t i = 0; i < vertexCount; ++i, pFloat += vertex_stride, ++pDst)
        {
            pDst->x = pFloat[0];
            pDst->y = pFloat[1];
            pDst->z = pFloat[2];
        }

        vbuf->unlock();

        return vertexCount;
    }
    //-----------------------------------------------------------------------
    template <typename DestType, typename SrcType>
    size_t
    MeshInformer::getTriangleIndices(DestType* pDest,
                                     const SrcType* pSrc, size_t count, size_t offset, int operationType)
    {
        size_t i;

        assert(count >= 3);
        switch (operationType)
        {
        case RenderOperation::OT_TRIANGLE_LIST:
            assert(count % 3 == 0);
            for (i = 0; i < count; ++i)
            {
                *pDest++ = *pSrc++ + offset;
            }
            return count;

        case RenderOperation::OT_TRIANGLE_STRIP:
            for (i = 0; i < count - 3; i += 2)
            {
                pDest[0] = pSrc[0] + offset;
                pDest[4] = pDest[1] = pSrc[1] + offset;
                pDest[3] = pDest[2] = pSrc[2] + offset;
                pDest[5] = pSrc[3] + offset;
                pDest += 6;
                pSrc += 2;
            }
            if (count & 1)
            {
                pDest[0] = pSrc[0] + offset;
                pDest[1] = pSrc[1] + offset;
                pDest[2] = pSrc[2] + offset;
            }
            return (count - 2) * 3;

        case RenderOperation::OT_TRIANGLE_FAN:
            for (i = 0; i < count - 2; ++i)
            {
                *pDest++ = pSrc[0]     + offset;
                *pDest++ = pSrc[i + 1] + offset;
                *pDest++ = pSrc[i + 2] + offset;
            }
            return (count - 2) * 3;

        default:
            assert(false);
            return 0;
        }
    }
    //-----------------------------------------------------------------------
    size_t
    MeshInformer::getTriangles(size_t* pDst,
                               const IndexData* indexData, size_t offset, int operationType)
    {
        size_t index_stride = indexData->mIndexBuffer->getIndexSize();
        size_t index_count = indexData->mIndexCount;

        const void* pBase = indexData->mIndexBuffer->lock(
            HardwareBuffer::HBL_READ_ONLY);

        size_t result;
        if (indexData->mIndexBuffer->getType() == HardwareIndexBuffer::IT_16BIT)
        {
            const uint16* pSrc = static_cast<const uint16*>(pBase);
            result = getTriangleIndices(pDst, pSrc, index_count, offset, operationType);
        }
        else
        {
            const uint32* pSrc = static_cast<const uint32*>(pBase);
            result = getTriangleIndices(pDst, pSrc, index_count, offset, operationType);
        }

        indexData->mIndexBuffer->unlock();

        return result;
    }
    //-----------------------------------------------------------------------
    void
    MeshInformer::getMeshStatistics(const MeshPtr& mesh, size_t& numVertices, size_t& numIndices)
    {
        size_t numSubMeshes = mesh->getSubMeshCount();
        bool added_shared_vertex = false;

        for (size_t i = 0; i < numSubMeshes; ++i)
        {
            auto subMesh = mesh->getSubMesh(i);

            if (subMesh->getOperationType() == RenderOperation::OT_TRIANGLE_LIST ||
                subMesh->getOperationType() == RenderOperation::OT_TRIANGLE_STRIP ||
                subMesh->getOperationType() == RenderOperation::OT_TRIANGLE_FAN)
            {
                if (subMesh->useSharedVertices())
                {
                    if (!added_shared_vertex)
                    {
                        added_shared_vertex = true;
                        numVertices += subMesh->getParent()->getVertexData()->vertexCount;
                    }
                }
                else
                {
                    numVertices += subMesh->getVertexData()->vertexCount;
                }

        
                switch (subMesh->getOperationType())
                {
                case RenderOperation::OT_TRIANGLE_LIST:
                    assert(subMesh->getIndexData()->mIndexCount % 3 == 0);
                    numIndices += subMesh->getIndexData()->mIndexCount;
                    break;

                case RenderOperation::OT_TRIANGLE_STRIP:
                case RenderOperation::OT_TRIANGLE_FAN:
                    numIndices += (subMesh->getIndexData()->mIndexCount - 2) * 3;
                    break;
                }
            }
        }
    }
    //-----------------------------------------------------------------------
    void
    MeshInformer::getMeshTriangles(const MeshPtr& mesh,
                                   std::vector<Vector3>& vertices,
                                   std::vector<size_t>& indices,
                                   std::vector<size_t>* indexOffsets)
    {
        size_t numVertices = 0, numIndices = 0;
        getMeshStatistics(mesh, numVertices, numIndices);

        size_t vertex_offset = vertices.size();
        size_t index_offset = indices.size();

        vertices.resize(vertex_offset + numVertices);
        indices.resize(index_offset + numIndices);

        Vector3* pVertices = &vertices[0];
        size_t* pIndices = &indices[0];
        size_t shared_vertex_offset = vertex_offset;
        bool added_shared_vertex = false;

        size_t numSubMeshes = mesh->getSubMeshCount();
        for (size_t i = 0; i < numSubMeshes; ++i)
        {
            auto subMesh = mesh->getSubMesh(i);

            if (indexOffsets)
            {
                indexOffsets->push_back(index_offset);
            }

            if (subMesh->getOperationType() == RenderOperation::OT_TRIANGLE_LIST ||
                subMesh->getOperationType() == RenderOperation::OT_TRIANGLE_STRIP ||
                subMesh->getOperationType() == RenderOperation::OT_TRIANGLE_FAN)
            {
                size_t current_vertex_offset;
                if (subMesh->useSharedVertices())
                {
                    if (!added_shared_vertex)
                    {
                        size_t vertexCount = getVertices(pVertices + vertex_offset, 
                            subMesh->getParent()->getVertexData());
                        shared_vertex_offset = vertex_offset;
                        vertex_offset += vertexCount;
                        added_shared_vertex = true;
                    }

                    current_vertex_offset = shared_vertex_offset;
                }
                else
                {
                    size_t vertexCount = getVertices(pVertices + vertex_offset, subMesh->getVertexData());
                    current_vertex_offset = vertex_offset;
                    vertex_offset += vertexCount;
                }

                size_t index_count = getTriangles(pIndices + index_offset, subMesh->getIndexData(), 
                    current_vertex_offset, subMesh->getOperationType());
                index_offset += index_count;
            }
        }
    }
    //-----------------------------------------------------------------------
    void
    MeshInformer::getEntityStatistics(const Entity* entity, size_t& numVertices, size_t& numIndices)
    {
        size_t numSubEntities = entity->getNumSubEntities();
        bool added_shared_vertex = false;

        for (size_t i = 0; i < numSubEntities; ++i)
        {
            auto subEntity = entity->getSubEntity(i);
            if (!subEntity->isVisible())
            {
                // Skip non-visible sub-entity
                continue;
            }

            auto subMesh = subEntity->getSubMesh();

            if (subMesh->getOperationType() == RenderOperation::OT_TRIANGLE_LIST ||
                subMesh->getOperationType() == RenderOperation::OT_TRIANGLE_STRIP ||
                subMesh->getOperationType() == RenderOperation::OT_TRIANGLE_FAN)
            {
                if (subMesh->useSharedVertices())
                {
                    if (!added_shared_vertex)
                    {
                        added_shared_vertex = true;
                        numVertices += subMesh->getParent()->getVertexData()->vertexCount;
                    }
                }
                else
                {
                    numVertices += subMesh->getVertexData()->vertexCount;
                }

                assert(subMesh->getIndexData()->mIndexCount >= 3);
                switch (subMesh->getOperationType())
                {
                case RenderOperation::OT_TRIANGLE_LIST:
                    assert(subMesh->getIndexData()->mIndexCount % 3 == 0);
                    numIndices += subMesh->getIndexData()->mIndexCount;
                    break;

                case RenderOperation::OT_TRIANGLE_STRIP:
                case RenderOperation::OT_TRIANGLE_FAN:
                    numIndices += (subMesh->getIndexData()->mIndexCount - 2) * 3;
                    break;
                }
            }
        }
    }
    //-----------------------------------------------------------------------
    void
    MeshInformer::getEntityTriangles(const Entity* entity,
                                     std::vector<Vector3>& vertices,
                                     std::vector<size_t>& indices,
                                     std::vector<size_t>* indexOffsets)
    {
        size_t numVertices = 0, numIndices = 0;
        getEntityStatistics(entity, numVertices, numIndices);

        size_t vertex_offset = vertices.size();
        size_t index_offset = indices.size();

        vertices.resize(vertex_offset + numVertices);
        indices.resize(index_offset + numIndices);

        // Software blended vertex data available only if animation enabled, and software animation are
        // used by internally engine, or user requested software animation.

        // Use skinned vertex data only if blended data available and skeleton animation enabled.
        bool useSkinned = entity->hasSkeleton();

        Vector3* pVertices = &vertices[0];
        size_t* pIndices = &indices[0];
        size_t shared_vertex_offset = vertex_offset;
        bool added_shared_vertex = false;

        size_t numSubEntities = entity->getNumSubEntities();
        for (size_t i = 0; i < numSubEntities; ++i)
        {
            SubEntity* subEntity = entity->getSubEntity(i);
            if (!subEntity->isVisible())
            {
                // Skip non-visible sub-entity
                continue;
            }

            auto subMesh = subEntity->getSubMesh();

            if (indexOffsets)
            {
                indexOffsets->push_back(index_offset);
            }

            if (subMesh->getOperationType() == RenderOperation::OT_TRIANGLE_LIST ||
                subMesh->getOperationType() == RenderOperation::OT_TRIANGLE_STRIP ||
                subMesh->getOperationType() == RenderOperation::OT_TRIANGLE_FAN)
            {
                size_t current_vertex_offset;
                if (subMesh->useSharedVertices())
                {
                    if (!added_shared_vertex)
                    {
                        size_t vertexCount = getVertices(pVertices + vertex_offset,
                            subMesh->getParent()->getVertexData());
                        shared_vertex_offset = vertex_offset;
                        vertex_offset += vertexCount;
                        added_shared_vertex = true;
                    }

                    current_vertex_offset = shared_vertex_offset;
                }
                else
                {
                    size_t vertexCount = getVertices(pVertices + vertex_offset,
                        subMesh->getVertexData());
                    current_vertex_offset = vertex_offset;
                    vertex_offset += vertexCount;
                }

                size_t index_count = getTriangles(pIndices + index_offset, 
                    subMesh->getIndexData(), current_vertex_offset, subMesh->getOperationType());
                index_offset += index_count;
            }
        }
    }

}
