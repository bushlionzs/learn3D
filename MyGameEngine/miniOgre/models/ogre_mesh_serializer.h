#pragma once

#include "OgreSerializer.h"

class VertexData;
class EdgeData;
class MeshSerializerListener;

class  OgreMeshSerializerImpl : public Ogre::Serializer
{
public:
	OgreMeshSerializerImpl();
	virtual ~OgreMeshSerializerImpl();

	void importMesh(const std::shared_ptr<Ogre::DataStream>& stream, Ogre::Mesh* pDest, MeshSerializerListener* listener);

private:
	virtual void readMesh(const std::shared_ptr<Ogre::DataStream>& stream, Ogre::Mesh* pMesh, MeshSerializerListener* listener);
	virtual void readSubMesh(const std::shared_ptr<Ogre::DataStream>& stream, Ogre::Mesh* pMesh, MeshSerializerListener* listener);
	virtual void readGeometry(const std::shared_ptr<Ogre::DataStream>& stream, Ogre::Mesh* pMesh, VertexData* vd);
	virtual void readGeometryVertexDeclaration(const std::shared_ptr<Ogre::DataStream>& stream, Ogre::Mesh* pMesh, VertexData* vd);
	virtual void readGeometryVertexElement(const std::shared_ptr<Ogre::DataStream>& stream, Ogre::Mesh* pMesh, VertexData* vd);
	virtual void readGeometryVertexBuffer(const std::shared_ptr<Ogre::DataStream>& stream, Ogre::Mesh* pMesh, VertexData* vd);
	virtual void readSubMeshOperation(const std::shared_ptr<Ogre::DataStream>& stream,
		Ogre::Mesh* pMesh, Ogre::SubMesh* sm);
	void readMeshLodLevel(const std::shared_ptr<Ogre::DataStream>& stream, Ogre::Mesh* pMesh);
	void readBoundsInfo(const std::shared_ptr<Ogre::DataStream>& stream, Ogre::Mesh* pMesh);
	void readSubMeshNameTable(const std::shared_ptr<Ogre::DataStream>& stream, Ogre::Mesh* pMesh);
	void readEdgeList(const std::shared_ptr<Ogre::DataStream>& stream, Ogre::Mesh* pMesh);
	void readEdgeListLodInfo(const std::shared_ptr<Ogre::DataStream>& stream, EdgeData* edgeData);
	void readMeshBoneAssignment(
		const std::shared_ptr<Ogre::DataStream>& stream,
		Ogre::Mesh* pMesh);
	void readSubMeshBoneAssignment(const std::shared_ptr<Ogre::DataStream>& stream,
		Ogre::Mesh* pMesh, Ogre::SubMesh* sub);
	void readSkeletonLink(
		const std::shared_ptr<Ogre::DataStream>& stream,
		Ogre::Mesh* pMesh,
		MeshSerializerListener* listener);
};