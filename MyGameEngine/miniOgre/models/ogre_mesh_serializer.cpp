#include "OgreHeader.h"
#include "ogre_mesh_Serializer.h"
#include "OgreDataStream.h"
#include "OgreMeshFileFormat.h"
#include "OgreSubMesh.h"
#include "OgreMesh.h"
#include "OgreMaterialManager.h"
#include "OgreHardwareVertexBuffer.h"
#include "vertex_declaration.h"
#include "vertex_data.h"
#include "OgreHardwareBufferManager.h"

OgreMeshSerializerImpl::OgreMeshSerializerImpl()
{
    mVersion = "[MeshSerializer_v1.100]";
}

OgreMeshSerializerImpl::~OgreMeshSerializerImpl()
{

}

void OgreMeshSerializerImpl::importMesh(
	const std::shared_ptr<Ogre::DataStream>& stream,
    Ogre::Mesh* pMesh,
	MeshSerializerListener* listener)
{
	readFileHeader(stream);
	pushInnerChunk(stream);
	uint32_t streamID = readChunk(stream);

    while (!stream->eof())
    {
        switch (streamID)
        {
        case Ogre::M_MESH:
            readMesh(stream, pMesh, nullptr);
            break;
        }

        streamID = readChunk(stream);
    }
    popInnerChunk(stream);
}

void OgreMeshSerializerImpl::readMesh(
    const std::shared_ptr<Ogre::DataStream>& stream, Ogre::Mesh* pMesh, MeshSerializerListener* listener)
{
    bool skeletallyAnimated;
    readBools(stream, &skeletallyAnimated, 1);

    // Find all substreams
    if (!stream->eof())
    {
        pushInnerChunk(stream);
        unsigned short streamID = readChunk(stream);
        while (!stream->eof() &&
            (streamID == Ogre::M_GEOMETRY ||
                streamID == Ogre::M_SUBMESH ||
                streamID == Ogre::M_MESH_SKELETON_LINK ||
                streamID == Ogre::M_MESH_BONE_ASSIGNMENT ||
                streamID == Ogre::M_MESH_LOD_LEVEL ||
                streamID == Ogre::M_MESH_BOUNDS ||
                streamID == Ogre::M_SUBMESH_NAME_TABLE ||
                streamID == Ogre::M_EDGE_LISTS ||
                streamID == Ogre::M_POSES ||
                streamID == Ogre::M_ANIMATIONS ||
                streamID == Ogre::M_TABLE_EXTREMES))
        {
            switch (streamID)
            {
            case Ogre::M_GEOMETRY:
            {
                VertexData* vd = pMesh->getVertexData();
                readGeometry(stream, pMesh, vd);
            }
                
                break;
            case Ogre::M_SUBMESH:
                readSubMesh(stream, pMesh, listener);
                break;
            case Ogre::M_MESH_SKELETON_LINK:
                readSkeletonLink(stream, pMesh, listener);
                break;
            case Ogre::M_MESH_BONE_ASSIGNMENT:
                readMeshBoneAssignment(stream, pMesh);
                break;
            case Ogre::M_MESH_LOD_LEVEL:
                readMeshLodLevel(stream, pMesh);
                break;
            case Ogre::M_MESH_BOUNDS:
                readBoundsInfo(stream, pMesh);
                break;
            case Ogre::M_SUBMESH_NAME_TABLE:
                readSubMeshNameTable(stream, pMesh);
                break;
            case Ogre::M_EDGE_LISTS:
                readEdgeList(stream, pMesh);
                break;
            case Ogre::M_POSES:
                //readPoses(stream, pMesh);
                break;
            case Ogre::M_ANIMATIONS:
                //readAnimations(stream, pMesh);
                break;
            case Ogre::M_TABLE_EXTREMES:
                //readExtremes(stream, pMesh);
                break;
            }

            if (!stream->eof())
            {
                streamID = readChunk(stream);
            }

        }
        if (!stream->eof())
        {
            OGRE_EXCEPT(Ogre::Exception::ERR_INTERNAL_ERROR, "mesh error");
        }
        popInnerChunk(stream);
    }
}

void OgreMeshSerializerImpl::readSubMesh(
    const std::shared_ptr<Ogre::DataStream>& stream, Ogre::Mesh* pMesh, MeshSerializerListener* listener)
{
    uint16_t streamID;
    String materialName = readString(stream);

  
    bool useSharedVertices;
    readBools(stream, &useSharedVertices, 1);

    Ogre::SubMesh* sm = pMesh->addSubMesh(useSharedVertices);

    sm->setMaterialName(materialName);

    uint32_t indexCount = 0;
    readInts(stream, &indexCount, 1);

    bool idx32bit;
    readBools(stream, &idx32bit, 1);

    if (indexCount > 0)
    {
        IndexData* indexData = nullptr;
        if (useSharedVertices)
        {
            indexData = pMesh->getIndexData();
        }
        else
        {
            indexData = sm->getIndexData();
        }
        indexData->mIndexCount = indexCount;
        if (idx32bit)
        {
            indexData->createBuffer(4, indexCount);
            void* data = indexData->mIndexBuffer->lock();
            readInts(stream, (uint32_t*)data, indexCount);
            indexData->mIndexBuffer->unlock();
        }
        else
        {
            indexData->createBuffer(2, indexCount);
            void* data = indexData->mIndexBuffer->lock();
            readShorts(stream, (uint16_t*)data, indexCount);
            indexData->mIndexBuffer->unlock();
        }
        sm->addIndexs(indexCount, 0, 0);
    }

    pushInnerChunk(stream);
    {
        if (!useSharedVertices)
        {
            streamID = readChunk(stream);
            if (streamID != Ogre::M_GEOMETRY)
            {
                OGRE_EXCEPT(Ogre::Exception::ERR_INTERNAL_ERROR, "Missing geometry data in mesh file",
                    "MeshSerializerImpl::readSubMesh");
            }
            readGeometry(stream, pMesh, sm->getVertexData());
        }

        // Find all bone assignments, submesh operation, and texture aliases (if present)
        if (!stream->eof())
        {
            streamID = readChunk(stream);
            bool seenTexAlias = false;
            while (!stream->eof() &&
                (streamID == Ogre::M_SUBMESH_BONE_ASSIGNMENT ||
                    streamID == Ogre::M_SUBMESH_OPERATION ||
                    streamID == Ogre::M_SUBMESH_TEXTURE_ALIAS))
            {
                switch (streamID)
                {
                case Ogre::M_SUBMESH_OPERATION:
                    readSubMeshOperation(stream, pMesh, sm);
                    break;
                case Ogre::M_SUBMESH_BONE_ASSIGNMENT:
                    readSubMeshBoneAssignment(stream, pMesh, sm);
                    break;
                case Ogre::M_SUBMESH_TEXTURE_ALIAS:
                    seenTexAlias = true;
                    //readSubMeshTextureAlias(stream, pMesh, sm);
                    break;
                }

                if (!stream->eof())
                {
                    streamID = readChunk(stream);
                }

            }

            if (seenTexAlias)
            {

            }
          

            if (!stream->eof())
            {
                // Backpedal back to start of stream
                backpedalChunkHeader(stream);
            }
        }
    }

    popInnerChunk(stream);
}

void OgreMeshSerializerImpl::readGeometry(
    const std::shared_ptr<Ogre::DataStream>& stream,
    Ogre::Mesh* pMesh,
    VertexData* vd)
{
    uint32_t vertexCount = 0;
    readInts(stream, &vertexCount, 1);
    vd->vertexCount = vertexCount;
    // Find optional geometry streams
    if (!stream->eof())
    {
        pushInnerChunk(stream);
        unsigned short streamID = readChunk(stream);
        while (!stream->eof() &&
            (streamID == Ogre::M_GEOMETRY_VERTEX_DECLARATION ||
                streamID == Ogre::M_GEOMETRY_VERTEX_BUFFER))
        {
            switch (streamID)
            {
            case Ogre::M_GEOMETRY_VERTEX_DECLARATION:
                readGeometryVertexDeclaration(stream, pMesh, vd);
                break;
            case Ogre::M_GEOMETRY_VERTEX_BUFFER:
                readGeometryVertexBuffer(stream, pMesh, vd);
                break;
            }
            // Get next stream
            if (!stream->eof())
            {
                streamID = readChunk(stream);
            }
        }
        if (!stream->eof())
        {
            // Backpedal back to start of non-submesh stream
            backpedalChunkHeader(stream);
        }
        popInnerChunk(stream);
    }
}

void OgreMeshSerializerImpl::readGeometryVertexDeclaration(
    const std::shared_ptr<Ogre::DataStream>& stream,
    Ogre::Mesh* pMesh,
    VertexData* vd)
{
    // Find optional geometry streams
    if (!stream->eof())
    {
        pushInnerChunk(stream);
        uint16_t streamID = readChunk(stream);
        while (!stream->eof() &&
            (streamID == Ogre::M_GEOMETRY_VERTEX_ELEMENT))
        {
            switch (streamID)
            {
            case Ogre::M_GEOMETRY_VERTEX_ELEMENT:
                readGeometryVertexElement(stream, pMesh, vd);
                break;
            }
            // Get next stream
            if (!stream->eof())
            {
                streamID = readChunk(stream);
            }
        }
        if (!stream->eof())
        {
            // Backpedal back to start of non-submesh stream
            backpedalChunkHeader(stream);
        }
        popInnerChunk(stream);
    }
}

void OgreMeshSerializerImpl::readGeometryVertexElement(
    const std::shared_ptr<Ogre::DataStream>& stream,
    Ogre::Mesh* pMesh,
    VertexData* vd)
{
    uint16_t source, offset, index, tmp;
    VertexElementType vType;
    VertexElementSemantic vSemantic;
    // unsigned short source;   // buffer bind source
    readShorts(stream, &source, 1);
    // unsigned short type;     // VertexElementType
    readShorts(stream, &tmp, 1);
    if (tmp == 4 || tmp == 11)
        vType = VET_UBYTE4_NORM;
    else
        vType = static_cast<VertexElementType>(tmp);
    // unsigned short semantic; // VertexElementSemantic
    readShorts(stream, &tmp, 1);
    vSemantic = static_cast<VertexElementSemantic>(tmp);
    // unsigned short offset;   // start offset in buffer in bytes
    readShorts(stream, &offset, 1);
    // unsigned short index;    // index of the semantic
    readShorts(stream, &index, 1);

   

    vd->vertexDeclaration->addElement(source, index, offset, vType, vSemantic);

    if (vType == _DETAIL_SWAP_RB)
    {
        
    }
}

void OgreMeshSerializerImpl::readGeometryVertexBuffer(
    const std::shared_ptr<Ogre::DataStream>& stream,
    Ogre::Mesh* pMesh,
    VertexData* vd)
{
    uint16_t bindIndex, vertexSize;
    // unsigned short bindIndex;    // Index to bind this buffer to
    readShorts(stream, &bindIndex, 1);
    // unsigned short vertexSize;   // Per-vertex size, must agree with declaration at this index
    readShorts(stream, &vertexSize, 1);
    

    pushInnerChunk(stream);
    {
        // Check for vertex data header
        uint16_t headerID;
        headerID = readChunk(stream);
        if (headerID != Ogre::M_GEOMETRY_VERTEX_BUFFER_DATA)
        {
            OGRE_EXCEPT(Ogre::Exception::ERR_ITEM_NOT_FOUND, "Can't find vertex buffer data area",
                "MeshSerializerImpl::readGeometryVertexBuffer");
        }
        // Check that vertex size agrees
        uint32_t vsize = vd->vertexDeclaration->getVertexSize(bindIndex);
        if (vsize != vertexSize)
        {
            OGRE_EXCEPT(Ogre::Exception::ERR_INTERNAL_ERROR, "Buffer vertex size does not agree with vertex declaration",
                "MeshSerializerImpl::readGeometryVertexBuffer");
        }

        vd->vertexSlotInfo.emplace_back();
        VertexSlotInfo& slotInfo = vd->vertexSlotInfo.back();
        slotInfo.slot = bindIndex;
        slotInfo.vertexSize = vertexSize;
        slotInfo.createBuffer(vertexSize, vd->vertexCount);
        void* data = slotInfo.hardwareVertexBuffer->lock();
        stream->read((void*)data, vd->vertexCount * vertexSize);
        Ogre::Vector3* tmp = (Ogre::Vector3*)data;
        for (int32_t i = 0; i < vd->vertexCount; i++)
        {
            tmp = (Ogre::Vector3 *)((char*)data + i * vertexSize);

            int kk = 0;
        }
        slotInfo.hardwareVertexBuffer->unlock();
    }
    popInnerChunk(stream);
}

void OgreMeshSerializerImpl::readSubMeshOperation(
    const std::shared_ptr<Ogre::DataStream>& stream,
    Ogre::Mesh* pMesh, Ogre::SubMesh* sm)
{
    uint16_t opType;
    readShorts(stream, &opType, 1);
    sm->setOperationType(static_cast<OperationType>(opType));
}
#define OGRE_NO_MESHLOD 1
void OgreMeshSerializerImpl::readMeshLodLevel(
    const std::shared_ptr<Ogre::DataStream>& stream, Ogre::Mesh* pMesh)
{
#if OGRE_NO_MESHLOD

    /*
    //Since the chunk sizes in old versions are messed up, we can't use this clean solution.
    // We need to walk through the data to not rely on the chunk size!
    stream->skip(mCurrentstreamLen);

    // Since we got here, we have already read the chunk header.
    backpedalChunkHeader(stream);
    */
    uint16 numSubs = pMesh->getSubMeshCount();
    String strategyName = readString(stream);
    uint16 numLods;
    readShorts(stream, &numLods, 1);
    pushInnerChunk(stream);
    for (int lodID = 1; lodID < numLods; lodID++) {
        unsigned short streamID = readChunk(stream);
        Real usageValue;
        readFloats(stream, &usageValue, 1);
        switch (streamID) {
        case Ogre::M_MESH_LOD_MANUAL:
        {
            String manualName = readString(stream);
            break;
        }
        case Ogre::M_MESH_LOD_GENERATED:
            for (int i = 0; i < numSubs; ++i)
            {
                unsigned int numIndexes;
                readInts(stream, &numIndexes, 1);

                unsigned int offset;
                readInts(stream, &offset, 1);

                // For merged buffers, you can pass the index of previous Lod.
                // To create buffer it should be -1.
                unsigned int bufferIndex;
                readInts(stream, &bufferIndex, 1);
                if (bufferIndex == (unsigned int)-1) {
                    // generate buffers

                    // bool indexes32Bit
                    bool idx32Bit;
                    readBools(stream, &idx32Bit, 1);

                    unsigned int buffIndexCount;
                    readInts(stream, &buffIndexCount, 1);

                    size_t buffSize = buffIndexCount * (idx32Bit ? 4 : 2);
                    stream->skip(buffSize);
                }
            }
            break;
        default:
            OGRE_EXCEPT(Ogre::Exception::ERR_INVALIDPARAMS,
                "Invalid Lod Usage type in " + pMesh->getName(),
                "MeshSerializerImpl::readMeshLodInfo");
        }
    }
    popInnerChunk(stream);
#else
    // Read the strategy to be used for this mesh
    String strategyName = readString(stream);
    //LodStrategy* strategy = LodStrategyManager::getSingleton().getStrategy(strategyName);

    //// Check that valid strategy name was given, otherwise use default
    //if (strategy == 0)
    //    strategy = LodStrategyManager::getSingleton().getDefaultStrategy();

    //pMesh->setLodStrategy(strategy);

    // unsigned short numLevels;

    uint16_t numLoads;
    readShorts(stream, &numLoads, 1);
    /*pMesh->mMeshLodUsageList.resize(pMesh->mNumLods);
    for (auto* s : pMesh->getSubMeshes())
    {
        assert(s->mLodFaceList.empty());
        s->mLodFaceList.resize(pMesh->mNumLods - 1);
    }*/
    pushInnerChunk(stream);
    // lodID=0 is the original mesh. We need to skip it.
    for (int lodID = 1; lodID < numLoads; lodID++) {
        // Read depth
        MeshLodUsage& usage = pMesh->mMeshLodUsageList[lodID];
        unsigned short streamID = readChunk(stream);
        readFloats(stream, &(usage.userValue), 1);
        switch (streamID) {
        case M_MESH_LOD_MANUAL:
            readMeshLodUsageManual(stream, pMesh, lodID, usage);
            break;
        case M_MESH_LOD_GENERATED:
            readMeshLodUsageGenerated(stream, pMesh, lodID, usage);
            break;
        default:
            OGRE_EXCEPT(Exception::ERR_INVALIDPARAMS,
                "Invalid Lod Usage type in " + pMesh->getName(),
                "MeshSerializerImpl::readMeshLodInfo");
        }
        usage.manualMesh.reset(); // will trigger load later with manual Lod
        usage.edgeData = NULL;
    }
    popInnerChunk(stream);
#endif
}

void OgreMeshSerializerImpl::readBoundsInfo(
    const std::shared_ptr<Ogre::DataStream>& stream, Ogre::Mesh* pMesh)
{
    Ogre::Vector3 min_v, max_v;
    readFloats(stream, min_v.ptr(), 3);
    readFloats(stream, max_v.ptr(), 3);

    Ogre::AxisAlignedBox box(min_v, max_v);
    pMesh->_setBounds(box, false);

    float radius;
    readFloats(stream, &radius, 1);
 
}

void OgreMeshSerializerImpl::readSubMeshNameTable(
    const std::shared_ptr<Ogre::DataStream>& stream, Ogre::Mesh* pMesh)
{
    std::map<unsigned short, String> subMeshNames;
    unsigned short streamID, subMeshIndex;

    // Need something to store the index, and the objects name
    // This table is a method that imported meshes can retain their naming
    // so that the names established in the modelling software can be used
    // to get the sub-meshes by name. The exporter must support exporting
    // the optional stream M_SUBMESH_NAME_TABLE.

    // Read in all the sub-streams. Each sub-stream should contain an index and Ogre::String for the name.
    if (!stream->eof())
    {
        pushInnerChunk(stream);
        streamID = readChunk(stream);
        while (!stream->eof() && (streamID == Ogre::M_SUBMESH_NAME_TABLE_ELEMENT))
        {
            // Read in the index of the submesh.
            readShorts(stream, &subMeshIndex, 1);
            // Read in the String and map it to its index.
            subMeshNames[subMeshIndex] = readString(stream);

            // If we're not end of file get the next stream ID
            if (!stream->eof())
                streamID = readChunk(stream);
        }
        if (!stream->eof())
        {
            // Backpedal back to start of stream
            backpedalChunkHeader(stream);
        }
        popInnerChunk(stream);
    }

    // Set all the submeshes names
    // ?
    // Loop through and save out the index and names.
    for (auto& sn : subMeshNames)
    {
        // Name this submesh to the stored name.
        //pMesh->nameSubMesh(sn.second, sn.first);
    }
}

void OgreMeshSerializerImpl::readEdgeList(
    const std::shared_ptr<Ogre::DataStream>& stream, Ogre::Mesh* pMesh)
{
    if (!stream->eof())
    {
        pushInnerChunk(stream);
        unsigned short streamID = readChunk(stream);
        while (!stream->eof() &&
            streamID == Ogre::M_EDGE_LIST_LOD)
        {
            // Process single LOD

            // unsigned short lodIndex
            unsigned short lodIndex;
            readShorts(stream, &lodIndex, 1);

            // bool isManual            // If manual, no edge data here, loaded from manual mesh
            bool isManual;
            readBools(stream, &isManual, 1);
            // Only load in non-manual levels; others will be connected up by Mesh on demand
#if OGRE_NO_MESHLOD
                // 
            if (!isManual)
                if (lodIndex != 0) {
                    readEdgeListLodInfo(stream, NULL);
                }
                else {
#else
            if (!isManual) {
#endif
               /* MeshLodUsage& usage = pMesh->mMeshLodUsageList[lodIndex];

                usage.edgeData = OGRE_NEW EdgeData();*/

                // Read detail information of the edge list
                readEdgeListLodInfo(stream, nullptr);

                // Postprocessing edge groups
                //for (auto& edgeGroup : usage.edgeData->edgeGroups)
                //{
                //    // Populate edgeGroup.vertexData pointers
                //    // If there is shared vertex data, vertexSet 0 is that,
                //    // otherwise 0 is first dedicated
                //    if (pMesh->sharedVertexData)
                //    {
                //        if (edgeGroup.vertexSet == 0)
                //        {
                //            edgeGroup.vertexData = pMesh->sharedVertexData;
                //        }
                //        else
                //        {
                //            edgeGroup.vertexData = pMesh->getSubMesh(
                //                (unsigned short)edgeGroup.vertexSet - 1)->vertexData;
                //        }
                //    }
                //    else
                //    {
                //        edgeGroup.vertexData = pMesh->getSubMesh(
                //            (unsigned short)edgeGroup.vertexSet)->vertexData;
                //    }
                //}
            }

            if (!stream->eof())
            {
                streamID = readChunk(stream);
            }

                }
        if (!stream->eof())
        {
            // Backpedal back to start of stream
            backpedalChunkHeader(stream);
        }
        popInnerChunk(stream);
        }

    //pMesh->mEdgeListsBuilt = true;
}

void OgreMeshSerializerImpl::readEdgeListLodInfo(
    const std::shared_ptr<Ogre::DataStream>& stream,
    EdgeData* edgeData)
{
#if OGRE_NO_MESHLOD
    if (edgeData == NULL) { // skip it!
        bool isClosed;
        readBools(stream, &isClosed, 1);
        // unsigned long numTriangles
        uint32 numTriangles;
        readInts(stream, &numTriangles, 1);
        // unsigned long numEdgeGroups
        uint32 numEdgeGroups;
        readInts(stream, &numEdgeGroups, 1);
        stream->skip(numTriangles * (8 * sizeof(uint32) + 4 * sizeof(float)));
        pushInnerChunk(stream);
        for (uint32 eg = 0; eg < numEdgeGroups; ++eg)
        {
            unsigned short streamID = readChunk(stream);
            if (streamID != Ogre::M_EDGE_GROUP)
            {
                OGRE_EXCEPT(Ogre::Exception::ERR_INTERNAL_ERROR,
                    "Missing M_EDGE_GROUP stream",
                    "MeshSerializerImpl::readEdgeListLodInfo");
            }
            uint32 tmp[3];
            // unsigned long vertexSet
            readInts(stream, &tmp[0], 3);
            uint32 numEdges;
            readInts(stream, &numEdges, 1);

            stream->skip(numEdges * (6 * sizeof(uint32) + sizeof(bool)));
        }
        popInnerChunk(stream);
        return;
    }
#endif
    bool isClosed;
    readBools(stream, &isClosed, 1);
    // unsigned long numTriangles
    uint32 numTriangles;
    readInts(stream, &numTriangles, 1);
    // Allocate correct amount of memory
    /*edgeData->triangles.resize(numTriangles);
    edgeData->triangleFaceNormals.resize(numTriangles);
    edgeData->triangleLightFacings.resize(numTriangles);*/
    // unsigned long numEdgeGroups
    uint32 numEdgeGroups;
    readInts(stream, &numEdgeGroups, 1);
    // Allocate correct amount of memory
    //edgeData->edgeGroups.resize(numEdgeGroups);
    // Triangle* triangleList
    uint32 tmp[3];
    for (size_t t = 0; t < numTriangles; ++t)
    {
        //EdgeData::Triangle& tri = edgeData->triangles[t];
        // unsigned long indexSet
        readInts(stream, tmp, 1);
        //tri.indexSet = tmp[0];
        // unsigned long vertexSet
        readInts(stream, tmp, 1);
        //tri.vertexSet = tmp[0];
        // unsigned long vertIndex[3]
        readInts(stream, tmp, 3);

        //tri.vertIndex[0] = tmp[0];
        //tri.vertIndex[1] = tmp[1];
        //tri.vertIndex[2] = tmp[2];
        // unsigned long sharedVertIndex[3]
        readInts(stream, tmp, 3);
        //tri.sharedVertIndex[0] = tmp[0];
        //tri.sharedVertIndex[1] = tmp[1];
        //tri.sharedVertIndex[2] = tmp[2];
        float normal[4];
        readFloats(stream, &(normal[0]), 4);

    }
    pushInnerChunk(stream);
    for (uint32 eg = 0; eg < numEdgeGroups; ++eg)
    {
        unsigned short streamID = readChunk(stream);
        if (streamID != Ogre::M_EDGE_GROUP)
        {
            OGRE_EXCEPT(Ogre::Exception::ERR_INTERNAL_ERROR,
                "Missing M_EDGE_GROUP stream",
                "MeshSerializerImpl::readEdgeListLodInfo");
        }
       // EdgeData::EdgeGroup& edgeGroup = edgeData->edgeGroups[eg];

        // unsigned long vertexSet
        readInts(stream, tmp, 1);
       // edgeGroup.vertexSet = tmp[0];
        // unsigned long triStart
        readInts(stream, tmp, 1);
        //edgeGroup.triStart = tmp[0];
        // unsigned long triCount
        readInts(stream, tmp, 1);
        //edgeGroup.triCount = tmp[0];
        // unsigned long numEdges
        uint32 numEdges;
        readInts(stream, &numEdges, 1);
        //edgeGroup.edges.resize(numEdges);
        // Edge* edgeList
        for (uint32 e = 0; e < numEdges; ++e)
        {
           // EdgeData::Edge& edge = edgeGroup.edges[e];
            // unsigned long  triIndex[2]
            readInts(stream, tmp, 2);
          //  edge.triIndex[0] = tmp[0];
          //  edge.triIndex[1] = tmp[1];
            // unsigned long  vertIndex[2]
            readInts(stream, tmp, 2);
          //  edge.vertIndex[0] = tmp[0];
          //  edge.vertIndex[1] = tmp[1];
            // unsigned long  sharedVertIndex[2]
            readInts(stream, tmp, 2);
          //  edge.sharedVertIndex[0] = tmp[0];
          //  edge.sharedVertIndex[1] = tmp[1];
            bool degenerate;
            readBools(stream, &degenerate, 1);
        }
    }
    popInnerChunk(stream);
}

void OgreMeshSerializerImpl::readMeshBoneAssignment(
    const std::shared_ptr<Ogre::DataStream>& stream,
    Ogre::Mesh* pMesh)
{
    VertexBoneAssignment assign;

    // unsigned int vertexIndex;
    readInts(stream, &(assign.vertexIndex), 1);
    // unsigned short boneIndex;
    readShorts(stream, &(assign.boneIndex), 1);
    // float weight;
    readFloats(stream, &(assign.weight), 1);

    pMesh->addBoneAssignment(assign);

}

void OgreMeshSerializerImpl::readSubMeshBoneAssignment(
    const std::shared_ptr<Ogre::DataStream>& stream,
    Ogre::Mesh* pMesh, Ogre::SubMesh* sub)
{
    VertexBoneAssignment assign;

    // unsigned int vertexIndex;
    readInts(stream, &(assign.vertexIndex), 1);
    // unsigned short boneIndex;
    readShorts(stream, &(assign.boneIndex), 1);
    // float weight;
    readFloats(stream, &(assign.weight), 1);

    sub->addBoneAssignment(assign);
}

void OgreMeshSerializerImpl::readSkeletonLink(
    const std::shared_ptr<Ogre::DataStream>& stream,
    Ogre::Mesh* pMesh,
    MeshSerializerListener* listener)
{
    String skelName = readString(stream);

    pMesh->setSkeletonName(skelName);
}