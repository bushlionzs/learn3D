#define _DISABLE_EXTENDED_ALIGNED_STORAGE 1
#include <OgreHeader.h>
#include "CryEngineUtil.h"
#include "CryEngineCommon.h"
#include <CryEngine/Cry3DEngine/CGF/ReadOnlyChunkFile.h>
#include <CryEngine/Cry3DEngine/CGF/CGFLoader.h>
#include <OgreMeshManager.h>
#include <OgreMesh.h>
#include <OgreCamera.h>
#include <OgreSubEntity.h>
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
#include <CryEngineRenderer.h>
#include <CryEngineMesh.h>
#include <CryEngineShader.h>
#include <CryEngineRenderView.h>
#include "game_camera.h"
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

	std::string matName = mtlName;
	dy::to_lower(matName);
	mat->name = dy::removeSuffix(matName);

	auto pos = mat->name.find("assets/");
	if (pos != std::string::npos)
	{
		mat->name = mat->name.substr(pos + 7, mat->name.length());
	}
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

struct CryEngineVertex
{
	Ogre::Vector3 Pos;
	Ogre::Vector3 Normal;
	Ogre::Vector2 TexC;
	Ogre::Vector4 BoneWeights;
	uint32_t BoneIndices[4];
};

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

		VertexData* vertexData = ogreMesh->getVertexData();


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
				vertex.BoneIndices[0] = mesh->m_pBoneMapping[0].boneIds[0];
				vertex.BoneIndices[1] = mesh->m_pBoneMapping[1].boneIds[1];
				vertex.BoneIndices[2] = mesh->m_pBoneMapping[2].boneIds[2];
				vertex.BoneIndices[3] = mesh->m_pBoneMapping[3].boneIds[3];
				vertex.BoneWeights[0] = mesh->m_pBoneMapping[0].weights[0];
				vertex.BoneWeights[1] = mesh->m_pBoneMapping[1].weights[1];
				vertex.BoneWeights[2] = mesh->m_pBoneMapping[2].weights[2];
				vertex.BoneWeights[3] = mesh->m_pBoneMapping[3].weights[3];
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

Matrix34 translateMatrix(Ogre::Camera* ogreCam)
{
	auto& position = ogreCam->getDerivedPosition();
	auto& viewMatrix = ogreCam->getViewMatrix();
	auto& forward = viewMatrix.getForward();
	auto& right = viewMatrix.getRight();
	Matrix34 m;
	m.SetIdentity();
	m.SetTranslation(Vec3(position.x, position.y, position.z));
	m.SetColumn(1, Vec3(-forward.x, -forward.y, -forward.z));
	m.SetColumn(2, Vec3(0, 0, 1));
	m.SetColumn(0, Vec3(right.x, right.y, right.z));
	return m;
}
bool LoadTerrain(XmlNodeRef pDoc, CryEngineContext& context);

static void test()
{
	auto ogreM = Ogre::Math::makeLookAt(
		{ 95, 148.5, 34},
		{ 35, 20, 34 },
		{ 0, 0, 1 });
	Matrix44A cryM;
	mathMatrixLookAt(&cryM, { 95, 148.5, 34 },
		{ 35, 20, 34 },
		{ 0, 0, 1 });

	int kk = 0;
}
void loadCryEngineLevel(CryEngineContext& context)
{
	test();
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
			dy::to_lower(shortname);
			Ogre::ResourceManager::getSingleton().addResource(shortname, name);
		}
		else if (strcmp(suffix, ".tif") == 0)
		{
			std::string shortname = dy::get_short_name(name);
			dy::to_lower(shortname);
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

	string enginePath = PathUtil::GetEnginePath();

	if (!enginePath.empty())
	{
		std::vector<std::string> filenameList;
		std::string path = enginePath.c_str();
		path += "/Engine";
		Ogre::ResourceManager::getSingleton().traverseDir(path, "", filenameList, true);

		for (auto& name : filenameList)
		{
			const char* suffix = dy::getSuffix(name);
			if (strcmp(suffix, ".dds") == 0)
			{
				std::string shortname = dy::get_short_name(name);
				dy::to_lower(shortname);
				Ogre::ResourceManager::getSingleton().addResource(shortname, name, false);
			}
		}
	}

	IResourceList* pResList = pSystem->GetIResourceManager()->GetLevelResourceList();
	Cry3DEngineBase::m_pObjManager = new CObjManager;
	Cry3DEngineBase::m_pMatMan = new CMatMan;
	Cry3DEngineBase::m_pSystem = pSystem;
	
	CRenderer* renderer = new CRenderer();
	Cry3DEngineBase::m_pRenderer = renderer;
	gEnv->pRenderer = Cry3DEngineBase::m_pRenderer;
	
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
			/*Ogre::Mesh* ogreMesh = loadCGF(szResFileName);
			
			bool add = Ogre::MeshManager::getSingleton().addMesh(szResFileName, std::shared_ptr<Ogre::Mesh>(ogreMesh));

			assert_invariant(add);*/
		}
	}

	//load terrain
	XmlNodeRef m_xmlLevelData = pSystem->LoadXmlFromFile(levelDataPath.c_str());
	XmlNodeRef nodeRef = m_xmlLevelData->findChild("SurfaceTypes");

	//bool load = levelSystem->LoadLevel("asset_zoo");

	Cry3DEngineBase::m_p3DEngine->SetLevelPath(levelPath.c_str());
	bool loadTerrain = LoadTerrain(nodeRef, context);
    
	assert_invariant(loadTerrain);
	Cry3DEngineBase::m_p3DEngine->LoadVisAreas(&context.pStatObjTable, &context.pMatTable);
	{
		auto graphicsPipelineKey = SGraphicsPipelineKey::BaseGraphicsPipelineKey;

		CCamera cam;
		
		Ogre::Camera* ogreCam = context.gameCamera->getCamera();
		
		Matrix34 m = translateMatrix(ogreCam);
		cam.SetMatrix(m);
		//cam.SetPosition(Vec3(83.33, 41.79557, 59.02676));
		uint32_t width = 1600;
		uint32_t height = 900;
		float aspect = width / (float)height;
		float fov = Ogre::Math::PI / 3.0f;
		cam.SetFrustum(width, height, fov, 0.1, 10000, aspect);
		
		pSystem->SetViewCamera(cam);

		for (uint32_t i = 0; i < 3; i++)
		{
			pSystem->GetStreamEngine()->Update();
			pSystem->SetSystemGlobalState(ESYSTEM_GLOBAL_STATE_LEVEL_LOAD_COMPLETE);
			pSystem->Render(graphicsPipelineKey);

			CrySleep(500);
		}
		
	}
	
	
	COctreeNode* octreeNode = Cry3DEngineBase::m_p3DEngine->m_pObjectsTree;
	PodArray<IRenderNode*> lstObjects;
	octreeNode->GetObjects(lstObjects, nullptr);
	uint32_t objectSize = lstObjects.size();
	std::set<std::string> shaderSet;
	for (uint32_t i = 0; i < objectSize; i++)
	{
		IRenderNode* renderNode = lstObjects.GetAt(i);

		IStatObj* statObj = renderNode->GetEntityStatObj();

		if (statObj == nullptr)
		{
			continue;
		}

		const char* path = statObj->GetFilePath();
		
		IMaterial* mat = statObj->GetMaterial();
		CryEngineMesh* renderMesh = (CryEngineMesh*)statObj->GetRenderMesh();

		if (renderMesh == nullptr)
		{
			if (strstr(path, "turning_plattform.cgf"))
			{
				int kk = 0;
			}
			continue;
		}
			

		std::string name = statObj->GetFilePath();

		dy::to_lower(name);

		Ogre::Mesh* ogreMesh = renderMesh->getOgreMesh();

		std::string entityName = name + std::to_string(i);
		Ogre::Entity* entity = context.sceneManager->createEntity(entityName, ogreMesh);

		
		auto& baseWhiteMat = Ogre::MaterialManager::getSingleton().getByName("BaseWhite");
		for (uint32_t subIndex = 0; subIndex < entity->getNumSubEntities(); subIndex++)
		{
			Ogre::SubEntity* subEntity = entity->getSubEntity(subIndex);
			if (subEntity->getMaterial().get())
			{
				continue;
			}
			int matId = renderMesh->getMatId(subIndex);
			IMaterial* subMat = mat->GetSubMtl(matId);
			if (subMat == nullptr)
			{
				subMat = mat;
			}
			SShaderItem& shaderItem = subMat->GetShaderItem();

			RenderShaderResources* shaderResources = (RenderShaderResources*)shaderItem.m_pShaderResources;

			shaderSet.insert(shaderItem.m_pShader->GetName());
			std::vector<std::string>& texs = shaderResources->getTextureNames();

			if (texs[EFTT_DIFFUSE].empty())
			{
				subEntity->setMaterial(baseWhiteMat);
			}
			else
			{
				const char* matName = subMat->GetName();
				Ogre::Material* mat = new Ogre::Material(matName, false);

				std::string shortname = dy::get_short_name(texs[EFTT_DIFFUSE].c_str());
				dy::to_lower(shortname);
				mat->addTexture(shortname);
				GeneralMaterialConstantBuffer& matInfo = mat->getMatInfo();

				auto& diffuse = shaderResources->getDiffuse();
				matInfo.DiffuseAlbedo = Ogre::Vector4(diffuse.r, diffuse.g, diffuse.b, 1.0f);
				subEntity->setMaterial(std::shared_ptr<Ogre::Material>(mat));

				const char* shaderName = shaderItem.m_pShader->GetName();
				mat->getShaderInfo().shaderName = shaderName;
				mat->getShaderInfo().shaderName = "basic";
			}
		}


		Ogre::SceneNode* entityNode = context.root->createChildSceneNode(entityName);
		entityNode->attachObject(entity);

		Vec3 vec = renderNode->GetPos();
		
		entityNode->setPosition(Ogre::Vector3(vec.x, vec.y, vec.z));

		EERType type = renderNode->GetRenderNodeType();
		if (type == eERType_Brush)
		{
			IBrush* brush = (IBrush*)renderNode;
			float scale = brush->GetScale();
			entityNode->setScale(Ogre::Vector3(scale, scale, scale));

			const Matrix34& m = brush->GetMatrix();

			Ogre::Matrix3 rotMat;
			
			auto column0 = m.GetColumn(0).GetNormalized();
			auto column1 = m.GetColumn(1).GetNormalized();
			auto column2 = m.GetColumn(2).GetNormalized();

			rotMat.SetColumn(0, Ogre::Vector3(column0.x, column0.y, column0.z));
			rotMat.SetColumn(1, Ogre::Vector3(column1.x, column1.y, column1.z));
			rotMat.SetColumn(2, Ogre::Vector3(column2.x, column2.y, column2.z));
			
			Ogre::Quaternion q;
			q.FromRotationMatrix(rotMat);

			entityNode->setOrientation(q);
		}
	}
}

void updateCryEngineLevel(CryEngineContext& context)
{
	gEnv->nMainFrameID++;
	CSystem* pSystem = (CSystem*)Cry3DEngineBase::m_pSystem;

	CCamera cam = pSystem->GetViewCamera();

	
	Matrix34 m = translateMatrix(context.gameCamera->getCamera());
	
	cam.SetMatrix(m);
	Matrix34_tpl<f64>mCam34 = cam.GetMatrix();
	pSystem->SetViewCamera(cam);
	for (uint32_t i = 0; i < 1; i++)
	{
		pSystem->GetStreamEngine()->Update();
		pSystem->SetSystemGlobalState(ESYSTEM_GLOBAL_STATE_LEVEL_LOAD_COMPLETE);
		auto graphicsPipelineKey = SGraphicsPipelineKey::BaseGraphicsPipelineKey;
		pSystem->Render(graphicsPipelineKey);
	}
	auto* renderer = (CRenderer*)Cry3DEngineBase::m_pRenderer;
	CRenderView* renderView = renderer->GetOrCreateRenderView(IRenderView::eViewType_Default);

	auto& terrainNodeList = renderView->getTerrainNodeList();

	for (uint32_t i = 0; i < terrainNodeList.size(); i++)
	{
		if (terrainNodeList[i]->getOgreState())
			continue;
		terrainNodeList[i]->updateOgreState(true);
		std::string entityName = "terrainNode" + std::to_string(i);
		Ogre::Entity* entity = context.sceneManager->createEntity(entityName, terrainNodeList[i]->getOgreMesh());
		Ogre::SceneNode* entityNode = context.root->createChildSceneNode(entityName);
		entityNode->attachObject(entity);
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