#define _DISABLE_EXTENDED_ALIGNED_STORAGE 1
#include <OgreHeader.h>
#include "CryEngineUtil.h"

#include <CryEngine/Cry3DEngine/CGF/ReadOnlyChunkFile.h>
#include <CryEngine/Cry3DEngine/CGF/CGFLoader.h>
#include <OgreMeshManager.h>
#include <OgreMesh.h>
#include <OgreSubMesh.h>
#include <OgreVertexData.h>
#include <OgreIndexData.h>
#include <OgreVertexDeclaration.h>
#include <OgreMaterialManager.h>
#include <OgreSceneManager.h>
#include <OgreResourceManager.h>
#include <OgreEntity.h>
#include <CryEngine/CrySystem/XML/xml.h>
#include <string_util.h>

#include <CryEngine/CrySystem/CryPak.h>
#include <CrySystem/SystemInitParams.h>
#include <CryEngine/CrySystem/System.h>
#include <CryEngine/CryAction/CryAction.h>
#include <CryEngine/CryAction/LevelSystem.h>
#include <CrySystem/File/IResourceManager.h>
#include <CryRenderer/IRenderer.h>
#include <CryEngine/Cry3DEngine/ObjMan.h>
#include <CryEngine/Cry3DEngine/MatMan.h>
#include <CryEngine/Cry3DEngine/cvars.h>
#include <CryEngine/Cry3DEngine/3dEngine.h>
#include <CryEngine/Cry3DEngine/MaterialHelpers.h>
#include <CryString/CryPath.h>

struct CryEngineVertex
{
	Ogre::Vector3 Pos;
	Ogre::Vector3 Normal;
	Ogre::Vector2 TexC;
	Ogre::Vector4 BoneWeights;
	uint32_t BoneIndices[4];
};
#pragma warning(disable:4189)

class Listener : public ILoaderCGFListener
{
public:
	virtual void Warning(const char* format) override { assert(false); }
	virtual void Error(const char* format)   override { assert(false); }

	virtual bool IsValidationEnabled()       override { return true; }
};

struct CryEngineTextureProperty
{
	std::string texName;
	bool             m_bUTile;
	bool             m_bVTile;
	signed char      m_Filter;
};

struct CryEngineSubMaterial
{
	std::string name;
	std::string surfaceType;
	Ogre::Vector3 diffuse = Ogre::Vector3::ZERO;
	Ogre::Vector3 specular = Ogre::Vector3::ZERO;
	Ogre::Vector4 emittance = Ogre::Vector4(1.0f, 1.0f, 1.0f, 0.0f);
	float opacity = 0.0f;
	float smoothness = 0.0f;
	float alphaTest = 0.0f;

	uint8_t m_FurAmount = 0;
	uint8_t m_VoxelCoverage = 255;
	uint8_t m_HeatAmount = 0;
	uint8_t m_CloakAmount = 255;
	std::vector<CryEngineTextureProperty> texs;
};

struct CryEngineMaterial
{
	std::string name;
	
	std::vector<CryEngineSubMaterial> subMaterials;
};


std::unordered_map<std::string, CryEngineMaterial*> materialMap;

void parseMaterialProperty(XmlNodeRef xmlNode, CryEngineSubMaterial* subMaterial)
{
	// Load lighting data.
	Vec3 vColor;
	Vec4 vColor4;
	if (xmlNode->getAttr("Diffuse", vColor))
	{
		subMaterial->diffuse = Ogre::Vector3(vColor.x, vColor.y, vColor.z);
	}
	if (xmlNode->getAttr("Specular", vColor))
	{
		subMaterial->specular = Ogre::Vector3(vColor.x, vColor.y, vColor.z);
	}
	if (xmlNode->getAttr("Emittance", vColor4))
	{
		subMaterial->emittance = Ogre::Vector4(vColor4.x, vColor4.y, vColor4.z, vColor4.w);
	}

	xmlNode->getAttr("Shininess", subMaterial->smoothness);
	xmlNode->getAttr("Opacity", subMaterial->opacity);
	xmlNode->getAttr("AlphaTest", subMaterial->alphaTest);
	xmlNode->getAttr("FurAmount", subMaterial->m_FurAmount);
	xmlNode->getAttr("VoxelCoverage", subMaterial->m_VoxelCoverage);
	xmlNode->getAttr("CloakAmount", subMaterial->m_CloakAmount);
	xmlNode->getAttr("HeatAmountScaled", subMaterial->m_HeatAmount);
}

CryEngineMaterial* loadCryEngineMaterial(const char* mtlName)
{
	CryEngineMaterial* mat = new CryEngineMaterial;

	std::string shortname = dy::get_short_name(mtlName);
	mat->name = dy::removeSuffix(shortname);

	XmlParser parser(false);
	XmlNodeRef mtlNode = parser.ParseFile(mtlName, true);
	int mtlFlags = 0;
	mtlNode->getAttr("MtlFlags", mtlFlags);

	XmlNodeRef childsNode = mtlNode->findChild("SubMaterials");

	if (childsNode)
	{
		int nSubMtls = childsNode->getChildCount();

		for (int i = 0; i < nSubMtls; i++)
		{
			XmlNodeRef subMtlNode = childsNode->getChild(i);

			if (subMtlNode->isTag("Material"))
			{
				mat->subMaterials.emplace_back();
				CryEngineSubMaterial& subMat = mat->subMaterials.back();
				subMat.texs.resize(EFTT_MAX);
				const char* name = subMtlNode->getAttr("Name");
				subMat.name = name;

				parseMaterialProperty(subMtlNode, &subMat);
				XmlNodeRef texturesNode = subMtlNode->findChild("Textures");
				if (texturesNode)
				{
					for (int c = 0; c < texturesNode->getChildCount(); c++)
					{
						XmlNodeRef texNode = texturesNode->getChild(c);

						const char* const szTexmap = texNode->getAttr("Map");

						const char* const szFile = texNode->getAttr("File");
						static MaterialHelpers matHelpers;
						const EEfResTextures texId = matHelpers.FindTexSlot(szTexmap);
						if (texId == EFTT_UNKNOWN)
						{
							continue;
						}
						subMat.texs[texId].texName = dy::get_short_name(szFile);
					}
				}
			}
			else
			{
				assert_invariant(false);
			}
		}
	}
	else
	{
		if (!(mtlFlags & MTL_FLAG_MULTI_SUBMTL))
		{
			mat->subMaterials.emplace_back();
			CryEngineSubMaterial& subMat = mat->subMaterials.back();
			subMat.texs.resize(EFTT_MAX);
			subMat.name = mat->name;
			parseMaterialProperty(mtlNode, &subMat);
			XmlNodeRef texturesNode = mtlNode->findChild("Textures");
			if (texturesNode)
			{
				for (int c = 0; c < texturesNode->getChildCount(); c++)
				{
					XmlNodeRef texNode = texturesNode->getChild(c);

					const char* const szTexmap = texNode->getAttr("Map");

					const char* const szFile = texNode->getAttr("File");
					static MaterialHelpers matHelpers;
					const EEfResTextures texId = matHelpers.FindTexSlot(szTexmap);
					if (texId == EFTT_UNKNOWN)
					{
						continue;
					}
					subMat.texs[texId].texName = dy::get_short_name(szFile);
				}
			}
		}
	}
	

	

	return mat;
}

Ogre::Mesh* loadCGF(const std::string& cgfName)
{
	Ogre::Mesh* ogreMesh = new Ogre::Mesh(cgfName);
	//const char* filename = "D:/CryEngine/My Project/Assets/objects/characters/samplecharacter/motusBody.skin";
	const char* filename = cgfName.c_str();
	CReadOnlyChunkFile chunkFile(false, false);

	std::vector<Ogre::Mesh*> meshlist;
	Listener listener;
	CLoaderCGF cgfLoader;
	CContentCGF cgfContent(filename);

	if (!cgfLoader.LoadCGF(&cgfContent, filename, chunkFile, &listener, 0))
	{
		assert(false);
	}

	int count = cgfContent.GetNodeCount();


	for (int i = 0; i < 1; i++)
	{
		CNodeCGF* node = cgfContent.GetNode(i);	
		CMesh* mesh = node->pMesh;
			
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
		Ogre::Matrix4 transformMatrix =
		{
			1, 0, 0, 0,
			0, 0, 1, 0,
			0, 1, 0, 0,
			0, 0, 0, 1
		};
		for (int vIndex = 0; vIndex < vertexCount; vIndex++)
		{
			CryEngineVertex& vertex = vertexList[vIndex];
			if (mesh->m_pPositions)
			{
				Vec3& vec = mesh->m_pPositions[vIndex];
				vertex.Pos = Ogre::Vector3(vec.x, vec.y, vec.z);
				//vertex.Pos = Ogre::Vector3(vec.x, vec.z, vec.y);
			}
			else
			{
				Vec3 vec = mesh->m_pPositionsF16[vIndex].ToVec3();
				vertex.Pos = Ogre::Vector3(vec.x, vec.y, vec.z);
				//vertex.Pos = Ogre::Vector3(vec.x, vec.z, vec.y);
			}
			
			
			Vec2 uv = mesh->m_pTexCoord[vIndex].GetUV();
			vertex.TexC = Ogre::Vector2(uv.x, uv.y);

			Vec3 normal = mesh->m_pNorms[vIndex].GetN();
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

		uint32_t subSize = mesh->m_subsets.size();
		
		if (strstr(node->pMaterial->name, "ground1"))
		{
			int kk = 0;
		}

		bool haveMat = true;
		auto itor = materialMap.find(node->pMaterial->name);
		if (itor == materialMap.end())
		{
			std::string shortName = dy::get_short_name(node->pMaterial->name);
			itor = materialMap.find(shortName);
			if (itor == materialMap.end())
			{
				haveMat = false;
			}
		}
		if (cgfName == "objects/plattforms/rocket.cgf")
		{
			int kk = 0;
		}
		auto& baseWhiteMat = Ogre::MaterialManager::getSingleton().getByName("BaseWhite");
		for (uint32_t subIndex = 0; subIndex < subSize; subIndex++)
		{
			SMeshSubset& subset = mesh->m_subsets[subIndex];
			Ogre::SubMesh* subMesh = ogreMesh->addSubMesh(true, true);
			subMesh->addIndexs(subset.nNumIndices, subset.nFirstIndexId, 0);

			
			if (haveMat)
			{
				CryEngineSubMaterial& subMat = itor->second->subMaterials[subset.nMatID];
				if (subMat.texs[EFTT_DIFFUSE].texName.empty())
				{
					subMesh->setMaterial(baseWhiteMat);
				}
				else
				{
					Ogre::Material* mat = new Ogre::Material(node->pMaterial->name, false);
					mat->addTexture(subMat.texs[EFTT_DIFFUSE].texName);
					GeneralMaterialConstantBuffer& matInfo = mat->getMatInfo();
					matInfo.DiffuseAlbedo = subMat.diffuse;
					subMesh->setMaterial(std::shared_ptr<Ogre::Material>(mat));

					mat->getShaderInfo().shaderName = "basic";
				}
			}
			else
			{
				subMesh->setMaterial(baseWhiteMat);
			}
			
		}
		int indexCount = mesh->GetIndexCount();
		if (indexCount > 0)
		{
			IndexData* indexData = ogreMesh->getIndexData();
			indexData->createBuffer(indexCount, 4);
			indexData->writeData((const char*)mesh->m_pIndices, indexCount * 4);
		}
		else
		{
			ogreMesh->releaseIndexData();
		}
		
	}

	return ogreMesh;
}



bool LoadTerrain(XmlNodeRef pDoc, CryEngineContext& context);
void loadCryEngineLevel(CryEngineContext& context)
{
	std::string rootPath = PathUtil::GetPathWithoutFilename(context.projectName.c_str());
	rootPath.pop_back();
	std::string levelPath = rootPath + "/Assets/Levels/asset_zoo/";
	
	std::vector<std::string> filenameList;
	Ogre::ResourceManager::getSingleton().traverseDir(rootPath, "", filenameList, true);
	std::vector<std::string> mtlNameList;
	std::vector<std::string> ddsNameList;

	for (auto& name : filenameList)
	{
		const char* suffix = dy::getSuffix(name);
		if (strcmp(suffix, ".mtl") == 0)
		{
			mtlNameList.push_back(name);
		}
		else if (strcmp(suffix, ".dds") == 0)
		{
			std::string shortname = dy::get_short_name(name);
			Ogre::ResourceManager::getSingleton().addResource(shortname, name);
		}
		else if (strcmp(suffix, ".tif") == 0)
		{
			std::string shortname = dy::get_short_name(name);
			Ogre::ResourceManager::getSingleton().addResource(shortname, name);
		}
	}
	
	context.terrainName = levelPath + "terrain/terrain.dat";
	std::string levelDataPath = levelPath + "leveldata.xml";
	SSystemInitParams startupParams;
	LPSTR cmdline = GetCommandLineA();
	strncpy(startupParams.szSystemCmdLine, cmdline, sizeof(startupParams.szSystemCmdLine) - 1);
	CSystem* pSystem = new CSystem(startupParams);
	pSystem->Initialize(startupParams);
	startupParams.pSystem = pSystem;
	new CCryAction(const_cast<SSystemInitParams&>(startupParams));
	ICryPak* pak = pSystem->GetIPak();
	ILevelSystem* levelSystem = CCryAction::GetCryAction()->GetILevelSystem();
	levelSystem->PrepareNextLevel("asset_zoo");

	
	IResourceList* pResList = pSystem->GetIResourceManager()->GetLevelResourceList();
	Cry3DEngineBase::m_pObjManager = new CObjManager;
	Cry3DEngineBase::m_pMatMan = new CMatMan;
	Cry3DEngineBase::m_pSystem = pSystem;
	Cry3DEngineBase::m_p3DEngine = new C3DEngine(pSystem);
	Cry3DEngineBase::m_p3DEngine->Init();
	CryPathString mtlFilename;
	CryPathString mtlName;

	
	//load material
	for (auto& matName: mtlNameList)
	{
		CryEngineMaterial* mat = loadCryEngineMaterial(matName.c_str());
		materialMap[mat->name] = mat;
	}

	//load cgf
	for (const char* szResFileName = pResList->GetFirst(); szResFileName != nullptr; szResFileName = pResList->GetNext())
	{
		const char* szFileExt = PathUtil::GetExt(szResFileName);
		const bool isCgf = cry_stricmp(szFileExt, CRY_GEOMETRY_FILE_EXT) == 0;

		if (isCgf)
		{
			Ogre::Mesh* ogreMesh = loadCGF(szResFileName);
			
			bool add = Ogre::MeshManager::getSingleton().addMesh(szResFileName, std::shared_ptr<Ogre::Mesh>(ogreMesh));

			assert_invariant(add);
		}
	}

	//load terrain
	XmlNodeRef m_xmlLevelData = pSystem->LoadXmlFromFile(levelDataPath.c_str());
	XmlNodeRef nodeRef = m_xmlLevelData->findChild("SurfaceTypes");
	bool loadTerrain = LoadTerrain(nodeRef, context);
    
	assert_invariant(loadTerrain);

	for (uint32_t i = 0; i < context.pStatObjTable->size(); i++)
	{
		IStatObj* statObj = context.pStatObjTable->at(i);
		std::string name = statObj->GetFilePath();

		dy::to_lower(name);

		//printf("name:%s\n", name.c_str());
	}

	
	COctreeNode* octreeNode = Cry3DEngineBase::m_p3DEngine->m_pObjectsTree;
	PodArray<IRenderNode*> lstObjects;
	octreeNode->GetObjects(lstObjects, nullptr);
	uint32_t objectSize = lstObjects.size();
	for (uint32_t i = 0; i < objectSize; i++)
	{
		IRenderNode* renderNode = lstObjects.GetAt(i);
		
		IStatObj* statObj = renderNode->GetEntityStatObj();
		std::string name = statObj->GetFilePath();

		dy::to_lower(name);

//		printf("name:%s\n", name.c_str());

		auto meshPtr = Ogre::MeshManager::getSingleton().getByName(name);

		if (!meshPtr)
		{
			printf("unkown name:%s\n", name.c_str());
			continue;
		}
		std::string entityName = name + std::to_string(i);
		Ogre::Entity* entity = context.sceneManager->createEntity(entityName, name);
		Ogre::SceneNode* entityNode = context.root->createChildSceneNode(entityName);
		entityNode->attachObject(entity);

		Vec3 vec = renderNode->GetPos();
		
		entityNode->setPosition(Ogre::Vector3(vec.x, vec.y, vec.z));
	}
}

bool LoadTerrain(XmlNodeRef pDoc, CryEngineContext& context)
{
	ISystem* pSystem = Cry3DEngineBase::m_pSystem;
	ICryPak* pak = pSystem->GetIPak();
	// open file
	FILE* f = pak->FOpen(context.terrainName.c_str(), "rb");
	if (!f)
		return false;
	// read header
	STerrainChunkHeader header;
	if (!pak->FRead(&header, 1, f, false))
	{
		pak->FClose(f);
		return 0;
	}

	SwapEndian(header, (header.nFlags & SERIALIZATION_FLAG_BIG_ENDIAN) ? eBigEndian : eLittleEndian);

	bool levelFilesEndian = (header.nFlags & SERIALIZATION_FLAG_BIG_ENDIAN) ? eBigEndian : eLittleEndian;

	// detect old header format where unitSize_InMeters was an int (now it is float)
	if (header.TerrainInfo.unitSize_InMeters < 0.25f || header.TerrainInfo.unitSize_InMeters > 64.f)
	{
		int unitSize_InMeters = *(int*)&header.TerrainInfo.unitSize_InMeters;
		header.TerrainInfo.unitSize_InMeters = (float)unitSize_InMeters;
	}

	if (header.nChunkSize)
	{

		Cry3DEngineBase::m_pTerrain = new CTerrain(header.TerrainInfo);
		

		Cry3DEngineBase::m_pTerrain->LoadSurfaceTypesFromXML(pDoc);


		if (!Cry3DEngineBase::m_pTerrain->Load(f, header.nChunkSize - sizeof(STerrainChunkHeader), &header,
			&context.pStatObjTable, &context.pMatTable))
		{
			delete Cry3DEngineBase::m_pTerrain;
			Cry3DEngineBase::m_pTerrain = NULL;
		}
		for (uint32_t i = 0; i < context.pStatObjTable->size(); i++)
		{
			IStatObj* statObj = context.pStatObjTable->at(i);
			IRenderMesh* renderMesh = statObj->GetRenderMesh();
			if (renderMesh == nullptr)
			{
				
			}
		}
	}
	return true;
}