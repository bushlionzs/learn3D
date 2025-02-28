#include <Cry3DEngine/CGF/ReadOnlyChunkFile.h>
#include <Cry3DEngine/CGF/CGFLoader.h>
#include <OgreHeader.h>
#include <OgreMeshManager.h>
#include <OgreMesh.h>
#include <OgreSubMesh.h>
#include <OgreVertexData.h>
#include <OgreIndexData.h>
#include <OgreVertexDeclaration.h>
#include <OgreMaterialManager.h>
#include <CrySystem/XML/xml.h>
struct CryEngineVertex
{
	Ogre::Vector3 Pos;
	Ogre::Vector3 Normal;
	Ogre::Vector2 TexC;
	Ogre::Vector4 BoneWeights;
	uint32_t BoneIndices[4];
};
#pragma warning(disable:4189)
void createCryEngineMesh(const std::string& meshName)
{
	const char* filename = "D:/CryEngine/My Project/Assets/objects/characters/samplecharacter/motusBody.skin";

	CReadOnlyChunkFile chunkFile(false, false);


	class Listener : public ILoaderCGFListener
	{
	public:
		virtual void Warning(const char* format) override { assert(false); }
		virtual void Error(const char* format)   override { assert(false); }

		virtual bool IsValidationEnabled()       override { return true; }
	};

	Listener listener;
	CLoaderCGF cgfLoader;
	CContentCGF cgfContent(filename);

	if (!cgfLoader.LoadCGF(&cgfContent, filename, chunkFile, &listener, 0))
	{
		assert(false);
	}

	int count = cgfContent.GetNodeCount();

	for (int i = 0; i < count; i++)
	{
		CNodeCGF* node = cgfContent.GetNode(i);
		CMaterialCGF* pMaterial = node->pMaterial;
		CMesh* mesh = node->pMesh;
		uint32_t subMatSize = pMaterial->subMaterials.size();

		for (auto j = 0; j < subMatSize; j++)
		{
			CMaterialCGF* subMat = pMaterial->subMaterials[j];

			subMat = subMat;
		}
		std::shared_ptr<Ogre::Mesh>ogreMesh = std::make_shared<Ogre::Mesh>(meshName);
		Ogre::MeshManager::getSingleton().addMesh(meshName, ogreMesh);
		
		int vertexCount = mesh->GetVertexCount();

		VertexData*  vertexData = ogreMesh->getVertexData();

		
		VertexDeclaration* decl = vertexData->getVertexDeclaration();

		decl->addElement(0, 0, 0, Ogre::VET_FLOAT3, Ogre::VES_POSITION);
		decl->addElement(0, 0, 12, Ogre::VET_FLOAT3, Ogre::VES_NORMAL);
		decl->addElement(0, 0, 24, Ogre::VET_FLOAT2, Ogre::VES_TEXTURE_COORDINATES);
		decl->addElement(0, 0, 32, Ogre::VET_FLOAT4, Ogre::VES_BLEND_WEIGHTS);
		decl->addElement(0, 0, 48, Ogre::VET_UINT4, Ogre::VES_BLEND_INDICES);
		vertexData->addBindBuffer(sizeof(CryEngineVertex), vertexCount);

		std::vector<CryEngineVertex> vertexList;
		vertexList.resize(vertexCount);

		for (int i = 0; i < vertexCount; i++)
		{
			CryEngineVertex& vertex = vertexList[i];
			vertex.Pos = Ogre::Vector3(mesh->m_pPositions[i].x, mesh->m_pPositions[i].y, 
				mesh->m_pPositions[i].z);
			Vec2 uv = mesh->m_pTexCoord[i].GetUV();
			vertex.TexC = Ogre::Vector2(uv.x, uv.y);

			Vec3 normal = mesh->m_pNorms[i].GetN();
			vertex.Normal = Ogre::Vector3(normal.x, normal.y,
				normal.z);

			if (mesh->m_pBoneMapping)
			{
				vertex.BoneIndices[0] = mesh->m_pBoneMapping[i].boneIds[0];
				vertex.BoneIndices[1] = mesh->m_pBoneMapping[i].boneIds[1];
				vertex.BoneIndices[2] = mesh->m_pBoneMapping[i].boneIds[2];
				vertex.BoneIndices[3] = mesh->m_pBoneMapping[i].boneIds[3];
				vertex.BoneWeights[0] = mesh->m_pBoneMapping[i].weights[0];
				vertex.BoneWeights[1] = mesh->m_pBoneMapping[i].weights[1];
				vertex.BoneWeights[2] = mesh->m_pBoneMapping[i].weights[2];
				vertex.BoneWeights[3] = mesh->m_pBoneMapping[i].weights[3];
			}
		}

		vertexData->writeBindBufferData(0, (const char*)vertexList.data(), vertexCount * sizeof(CryEngineVertex));

		IndexData* indexData = ogreMesh->getIndexData();


		uint32_t subSize = mesh->m_subsets.size();

		int maxIndex = 0;

		auto& mat = Ogre::MaterialManager::getSingleton().getByName("BaseWhite");
		for (uint32_t i = 0; i < subSize; i++)
		{
			SMeshSubset& subset = mesh->m_subsets[i];
			Ogre::SubMesh* subMesh = ogreMesh->addSubMesh(true, true);
			subMesh->addIndexs(subset.nNumIndices, subset.nFirstIndexId, subset.nFirstVertId);

			maxIndex = std::max(maxIndex, subset.nFirstIndexId + subset.nNumIndices);

			subMesh->setMaterial(mat);
		}

		indexData->createBuffer(maxIndex, 4);
		indexData->writeData((const char*)mesh->m_pIndices, maxIndex * 4);
	}
}

void addCryEngineMaterial(const std::string& matName, const std::string& matFileName)
{
	XmlParser parser(false);
	XmlNodeRef mtlNode = parser.ParseFile(matFileName.c_str(), true);
	int mtlFlags = 0;
	mtlNode->getAttr("MtlFlags", mtlFlags);

	XmlNodeRef publicVarsNode = mtlNode->findChild("PublicParams");

	XmlNodeRef childsNode = mtlNode->findChild("SubMaterials");

	if (childsNode)
	{
		int nSubMtls = childsNode->getChildCount();
		
		for (int i = 0; i < nSubMtls; i++)
		{
			XmlNodeRef mtlNode = childsNode->getChild(i);
			if (mtlNode->isTag("Material"))
			{
				const char* name = mtlNode->getAttr("Name");


			}
			else
			{
				const char* name = mtlNode->getAttr("Name");
				if (name[0])
				{

				}
			}
		}
	}
}

#include <CrySystem/CryPak.h>
#include <CrySystem/SystemInitParams.h>
#include <CrySystem/System.h>
void loadCryEngineLevel(struct CryEngineContext& context)
{
	SSystemInitParams startupParams;
	LPSTR cmdline = GetCommandLineA();
	strncpy(startupParams.szSystemCmdLine, cmdline, sizeof(startupParams.szSystemCmdLine) - 1);
	std::unique_ptr<CSystem> pSystem = stl::make_unique<CSystem>(startupParams);
	pSystem->Initialize(startupParams);
	ICryPak* pak = pSystem->GetIPak();
	pak->FOpen("D:\\CryEngine\\ThirdPerson\\Assets\\Levels\\asset_zoo\\mission_mission0.xml", "rb");
}