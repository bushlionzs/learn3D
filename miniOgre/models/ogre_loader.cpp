#include "OgreHeader.h"
#include "ogre_loader.h"
#include "OgreDataStream.h"
#include "ogre_mesh_Serializer.h"
#include "OgreMesh.h"
#include "OgreSubMesh.h"
#include "OgreMaterialManager.h"
#include "renderSystem.h"

OgreMeshLoader::OgreMeshLoader()
{
	mVersionData.push_back(new OgreMeshVersionData(
		std::string("[MeshSerializer_v1.100]"),
		new  OgreMeshSerializerImpl()));
}

OgreMeshLoader::~OgreMeshLoader()
{

}

std::shared_ptr<Ogre::Mesh> OgreMeshLoader::loadMeshFromFile(std::shared_ptr<Ogre::DataStream>& stream)
{
	uint16_t headerID;

	Ogre::Serializer serializer;
	serializer.readShorts(stream, &headerID, 1);

	if (headerID != HEADER_CHUNK_ID)
	{
		OGRE_EXCEPT(Ogre::Exception::ERR_INTERNAL_ERROR, "File header not found",
			"MeshSerializer::importMesh");
	}

	String ver = serializer.readString(stream);

	stream->seek(0);

	OgreMeshSerializerImpl* impl = 0;
	for (auto& i : mVersionData)
	{
		if (i->mVersion == ver)
		{
			impl = i->impl;
			break;
		}
	}

	if (!impl)
	{
		OGRE_EXCEPT(Ogre::Exception::ERR_INTERNAL_ERROR, "mesh version error");
	}
	
	auto pMesh = new Ogre::Mesh(stream->getName());

	impl->importMesh(stream, pMesh, nullptr);

	int32_t subCount = pMesh->getSubMeshCount();

	
	

	for (int32_t i = 0; i < subCount; i++)
	{
		Ogre::SubMesh* sub = pMesh->getSubMesh(i);
		const std::string& name = sub->getMaterialName();

		std::shared_ptr<Ogre::Material> mat =
			Ogre::MaterialManager::getSingletonPtr()->getByName(name);
		if (mat)
		{
			sub->setMaterial(mat);
		}
		else
		{
			WARNING_LOG("fail to load material:%s", name.c_str());
		}
	}

	return std::shared_ptr<Ogre::Mesh>(pMesh);
}

