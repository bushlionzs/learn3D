#include "StdAfx.h"
#include "CryEngineMesh.h"
#include "CryEngineRenderView.h"
#include <CryRenderer/IShader.h>
#include <CryRenderer/RenderElements/CREMesh.h>
#include <Cry3DEngine/IIndexedMesh.h>
#include <OgreHeader.h>
#include <OgreMesh.h>
#include <OgreSubMesh.h>
#include <OgreVertexData.h>
#include <OgreIndexData.h>
#include <OgreVertexDeclaration.h>

struct CryEngineVertex
{
	Ogre::Vector3 Pos;
	Ogre::Vector3 Normal;
	Ogre::Vector2 TexC;
	Ogre::Vector4 BoneWeights;
	uint32_t BoneIndices[4];
};


CryEngineMesh::CryEngineMesh(
    const char* szType, const char* szSourceName, bool bLock)
{
	mType = szType;
	mSourceName = szSourceName;
	m_nVerts = 0;
	m_nInds = 0;
	mOgreMesh = nullptr;
}

CryEngineMesh::CryEngineMesh()
{

}

CryEngineMesh::~CryEngineMesh()
{

}

void CryEngineMesh::AddRef()
{

	CryInterlockedIncrement(&m_nRefCounter);
}

int CryEngineMesh::Release()
{
	long refCnt = CryInterlockedDecrement(&m_nRefCounter);
	return refCnt;
}

const char* CryEngineMesh::GetTypeName()
{ 
	return m_sType; 
}
const char* CryEngineMesh::GetSourceName() const
{ 
	return m_sSource; 
}

int CryEngineMesh::GetIndicesCount()
{ 
	return m_nInds; 
}

int CryEngineMesh::GetVerticesCount()
{ 
	return m_nVerts; 
}

InputLayoutHandle   CryEngineMesh::GetVertexFormat()
{ 
	return m_eVF; 
}

ERenderMeshType CryEngineMesh::GetMeshType()
{ 
	return m_eType; 
}

void CryEngineMesh::SetSkinned(bool bSkinned)
{
	if (bSkinned) m_nFlags |= FRM_SKINNED;
	else          m_nFlags &= ~FRM_SKINNED;
};

uint CryEngineMesh::GetSkinningWeightCount() const
{
	return 0;
}

float CryEngineMesh::GetGeometricMeanFaceArea() const 
{ 
	return m_fGeometricMeanFaceArea; 
}

void CryEngineMesh::NextDrawSkinned()
{ 
	m_nFlags |= FRM_SKINNEDNEXTDRAW; 
}

void CryEngineMesh::GenerateQTangents()
{

}


void CryEngineMesh::CreateChunksSkinned()
{

}

void CryEngineMesh::CopyTo(IRenderMesh* pDst, int nAppendVtx, bool bDynamic, bool fullCopy)
{

}

void CryEngineMesh::SetSkinningDataVegetation(struct SMeshBoneMapping_uint8* pBoneMapping)
{

}

void CryEngineMesh::SetSkinningDataCharacter(
	CMesh& mesh,
	uint32 flags, struct SMeshBoneMapping_uint16* pBoneMapping,
	struct SMeshBoneMapping_uint16* pExtraBoneMapping)
{

}

// Creates an indexed mesh from this render mesh (accepts an optional pointer to an IIndexedMesh object that should be used)
IIndexedMesh* CryEngineMesh::GetIndexedMesh(IIndexedMesh* pIdxMesh)
{
	return nullptr;
}

int CryEngineMesh::GetRenderChunksCount(IMaterial* pMat, int& nRenderTrisCount)
{
	return 0;
}

IRenderMesh* CryEngineMesh::GenerateMorphWeights()
{ 
	return NULL; 
}

IRenderMesh* CryEngineMesh::GetMorphBuddy()
{ 
	return NULL; 
}

void CryEngineMesh::SetMorphBuddy(IRenderMesh* pMorph)
{
}

// Create render buffers from render mesh. Returns the final size of the render mesh or ~0U on failure
size_t CryEngineMesh::SetMesh(
	CMesh& mesh,
	int nSecColorsSetOffset,
	uint32 flags, const Vec3* pPosOffset, bool requiresLock)
{
	size_t resultingSize = ~0U;
	if (pPosOffset)
	{
		int kk = 0;
	}
	if (requiresLock)
	{
		std::lock_guard <std::recursive_mutex> lock(_mutex);
		resultingSize = SetMesh_Int(mesh, nSecColorsSetOffset, flags, pPosOffset);
	}
	else
	{
		resultingSize = SetMesh_Int(mesh, nSecColorsSetOffset, flags, pPosOffset);
	}

	return resultingSize;
}

size_t CryEngineMesh::SetMesh_Int(
	CMesh& mesh, 
	int nSecColorsSetOffset, 
	uint32 flags, 
	const Vec3* pPosOffset)
{
	assert(pPosOffset == nullptr);
	assert(mOgreMesh == nullptr);
	auto ogreMesh = new Ogre::Mesh(mSourceName);

	int vertexCount = mesh.GetVertexCount();

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
		if (mesh.m_pPositions)
		{
			Vec3& vec = mesh.m_pPositions[vIndex];
			vertex.Pos = Ogre::Vector3(vec.x, vec.y, vec.z);
			//vertex.Pos = Ogre::Vector3(vec.x, vec.z, vec.y);
		}
		else
		{
			Vec3 vec = mesh.m_pPositionsF16[vIndex].ToVec3();
			vertex.Pos = Ogre::Vector3(vec.x, vec.y, vec.z);
			//vertex.Pos = Ogre::Vector3(vec.x, vec.z, vec.y);
		}


		Vec2 uv = mesh.m_pTexCoord[vIndex].GetUV();
		vertex.TexC = Ogre::Vector2(uv.x, uv.y);

		Vec3 normal = mesh.m_pNorms[vIndex].GetN();
		vertex.Normal = Ogre::Vector3(normal.x, normal.y,
			normal.z);

		if (mesh.m_pBoneMapping)
		{
			vertex.BoneIndices[0] = mesh.m_pBoneMapping[0].boneIds[0];
			vertex.BoneIndices[1] = mesh.m_pBoneMapping[1].boneIds[1];
			vertex.BoneIndices[2] = mesh.m_pBoneMapping[2].boneIds[2];
			vertex.BoneIndices[3] = mesh.m_pBoneMapping[3].boneIds[3];
			vertex.BoneWeights[0] = mesh.m_pBoneMapping[0].weights[0];
			vertex.BoneWeights[1] = mesh.m_pBoneMapping[1].weights[1];
			vertex.BoneWeights[2] = mesh.m_pBoneMapping[2].weights[2];
			vertex.BoneWeights[3] = mesh.m_pBoneMapping[3].weights[3];
		}
	}

	vertexData->writeBindBufferData(0, (const char*)vertexList.data(), vertexCount * sizeof(CryEngineVertex));

	uint32_t subSize = mesh.m_subsets.size();

	matIds.resize(subSize);

	for (uint32_t i = 0; i < subSize; i++)
	{
		matIds[i] = mesh.m_subsets[i].nMatID;

		Ogre::SubMesh* subMesh = ogreMesh->addSubMesh(true, true);
		subMesh->addIndexs(mesh.m_subsets[i].nNumIndices, mesh.m_subsets[i].nFirstIndexId, 0);
	}

	int indexCount = mesh.GetIndexCount();
	if (indexCount > 0)
	{
		IndexData* indexData = ogreMesh->getIndexData();
		indexData->createBuffer(indexCount, 4);
		indexData->writeData((const char*)mesh.m_pIndices, indexCount * 4);
	}
	else
	{
		ogreMesh->releaseIndexData();
	}

	mOgreMesh = ogreMesh;
	return 0;
}

inline int CryEngineMesh::GetStreamStride(int nStream) const
{
	InputLayoutHandle eVF = m_eVF;

	switch (nStream)
	{
	case VSF_GENERAL:
		return 16;
	case VSF_TANGENTS: 
		return 16;
	case VSF_NORMALS:
		return 12;
	case VSF_QTANGENTS: 
	case VSF_HWSKIN_INFO: 
	case VSF_VERTEX_VELOCITY: 
	default:
		assert(false);
		CryWarning(EValidatorModule::VALIDATOR_MODULE_RENDERER, EValidatorSeverity::VALIDATOR_WARNING, "Unknown nStream");
	}

	return 0;
}
// Update system vertices buffer
bool CryEngineMesh::UpdateVertices(
	const void* pVertBuffer, int nVertCount, int nOffset,
	int nStream, uint32 copyFlags, bool requiresLock)
{
	assert(nOffset == 0);
	uint32_t stride = GetStreamStride(nStream);
	if (m_nVerts != nVertCount)
	{
		std::vector<char>& mem = mVerticesMap[nStream];
		mem.resize(nVertCount * stride);
		m_nVerts = nVertCount;
		memcpy(mem.data(), pVertBuffer, nVertCount * stride);
	}
	else
	{
		auto itor = mVerticesMap.find(nStream);
		if (itor != mVerticesMap.end())
		{
			std::vector<char>& mem = itor->second;
			memcpy(mem.data(), pVertBuffer, nVertCount * stride);
		}
		else
		{
			std::vector<char>& mem = mVerticesMap[nStream];
			mem.resize(nVertCount * stride);
			memcpy(mem.data(), pVertBuffer, nVertCount * stride);
		}
	}

	return true;
}

// Update system indices buffer
bool CryEngineMesh::UpdateIndices(
	const vtx_idx* pNewInds, int nInds, int nOffsInd,
	uint32 copyFlags, bool requiresLock)
{
	assert(nOffsInd == 0);

	m_nInds = nInds;
	if (mIndexData.size() != nInds)
	{
		mIndexData.resize(nInds);
	}
	memcpy(mIndexData.data(), pNewInds, sizeof(vtx_idx) * nInds);
	return true;
}

void CryEngineMesh::SetCustomTexID(int nCustomTID)
{

}

void CryEngineMesh::SetChunk(int nIndex, CRenderChunk& inChunk)
{
	if (!inChunk.nNumIndices || !inChunk.nNumVerts)
		return;

	CRenderChunk* pRenderChunk = NULL;

	if (nIndex < 0 || nIndex >= m_Chunks.size())
	{
		// add new chunk
		CRenderChunk matinfo;
		m_Chunks.push_back(matinfo);
		pRenderChunk = &m_Chunks.back();
	}
	else
	{
		// use present chunk
		pRenderChunk = &m_Chunks[nIndex];
	}

	pRenderChunk->m_nMatID = inChunk.m_nMatID;
	pRenderChunk->m_nMatFlags = inChunk.m_nMatFlags;

	pRenderChunk->nFirstIndexId = inChunk.nFirstIndexId;
	pRenderChunk->nNumIndices = std::max<uint32>(inChunk.nNumIndices, 0);
	pRenderChunk->nFirstVertId = inChunk.nFirstVertId;
	pRenderChunk->nNumVerts = std::max<uint32>(inChunk.nNumVerts, 0);
	pRenderChunk->nSubObjectIndex = inChunk.nSubObjectIndex;

	pRenderChunk->m_texelAreaDensity = inChunk.m_texelAreaDensity;

	assert(pRenderChunk->nFirstIndexId + pRenderChunk->nNumIndices <= m_nInds);
}

void CryEngineMesh::SetChunk(
	IMaterial* pNewMat, int nFirstVertId, int nVertCount,
	int nFirstIndexId, int nIndexCount, float texelAreaDensity, int nIndex)
{
	CRenderChunk chunk;

	if (pNewMat)
		chunk.m_nMatFlags = pNewMat->GetFlags();

	if (nIndex < 0 || nIndex >= m_Chunks.size())
		chunk.m_nMatID = m_Chunks.size();
	else
		chunk.m_nMatID = nIndex;

	chunk.nFirstVertId = nFirstVertId;
	chunk.nNumVerts = nVertCount;

	chunk.nFirstIndexId = nFirstIndexId;
	chunk.nNumIndices = nIndexCount;

	chunk.m_texelAreaDensity = texelAreaDensity;

	SetChunk(nIndex, chunk);
}

void CryEngineMesh::SetRenderChunks(
	CRenderChunk* pChunksArray, 
	int nCount, 
	bool bSubObjectChunks)
{
	assert(false);
}

TRenderChunkArray& CryEngineMesh::GetChunks()
{ 
	return m_Chunks; 
}

TRenderChunkArray& CryEngineMesh::GetChunksSkinned()
{ 
	return m_ChunksSkinned; 
}

TRenderChunkArray& CryEngineMesh::GetChunksSubObjects()
{ 
	return m_ChunksSubObjects; 
}

CryEngineMesh* CryEngineMesh::GetVertexContainer()
{
	if (m_pVertexContainer)
		return m_pVertexContainer;
	return this;
}

void CryEngineMesh::SetVertexContainer(IRenderMesh* pBuf)
{
	m_pVertexContainer = (CryEngineMesh*)pBuf;
}

void CryEngineMesh::Render(CRenderObject* pObj, const SRenderingPassInfo& passInfo)
{

}

void CryEngineMesh::AddRenderElements(
	IMaterial* pIMatInfo, CRenderObject* pObj, const SRenderingPassInfo& passInfo,
	int nList, int nAW)
{
	if (m_nVerts == 0)
	{
		return;
	}

	uint32_t nVerts = GetVertexContainer()->m_nVerts;
	uint32_t chunkSize = m_Chunks.size();
	if (nVerts == 0 || !chunkSize || !pIMatInfo)
		return;

	assert(!mAddRenderElement);

	mAddRenderElement = true;

	auto ogreMesh = new Ogre::Mesh(mSourceName);

	int vertexCount = m_nVerts;

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

	SVF_P3S_C4B_T2S* datas = nullptr;
	Vec3* normals = nullptr;
	auto itor = mVerticesMap.find(VSF_GENERAL);
	if (itor != mVerticesMap.end())
	{
		std::vector<char>& mem = itor->second;
		datas = (SVF_P3S_C4B_T2S*)mem.data();
	}

	itor = mVerticesMap.find(VSF_NORMALS);

	if (itor != mVerticesMap.end())
	{
		std::vector<char>& mem = itor->second;
		normals = (Vec3*)mem.data();
	}
	for (int vIndex = 0; vIndex < vertexCount; vIndex++)
	{
		CryEngineVertex& vertex = vertexList[vIndex];
		{
			Vec3 vec = datas[vIndex].xyz.ToVec3();
			vertex.Pos = Ogre::Vector3(vec.x, vec.y, vec.z);

			Vec2 uv = datas[vIndex].st.ToVec2();
			vertex.TexC = Ogre::Vector2(uv.x, uv.y);
		}
		
		if(normals)
		{
			vertex.Normal = Ogre::Vector3(normals[vIndex].x, normals[vIndex].y,
				normals[vIndex].z);
		}
	
	}

	vertexData->writeBindBufferData(0, (const char*)vertexList.data(), vertexCount * sizeof(CryEngineVertex));

	uint32_t subSize = m_Chunks.size();

	matIds.resize(subSize);

	for (uint32_t i = 0; i < subSize; i++)
	{
		CRenderChunk& chunk = m_Chunks[i];
		matIds[i] = chunk.m_nMatID;

		Ogre::SubMesh* subMesh = ogreMesh->addSubMesh(true, true);
		subMesh->addIndexs(chunk.nNumIndices, chunk.nFirstIndexId, 0);
	}

	int indexCount = mIndexData.size();
	if (indexCount > 0)
	{
		IndexData* indexData = ogreMesh->getIndexData();
		indexData->createBuffer(indexCount, 4);
		indexData->writeData((const char*)mIndexData.data(), indexCount * 4);
	}
	else
	{
		ogreMesh->releaseIndexData();
	}

	mOgreMesh = ogreMesh;
}

void CryEngineMesh::SetREUserData(float* pfCustomData, float fFogScale, float fAlpha)
{

}

void CryEngineMesh::AddRE(
	IMaterial* pMaterial, CRenderObject* pObj,
	IShader* pEf, const SRenderingPassInfo& passInfo, int nList, int nAW)
{

}

byte* CryEngineMesh::GetPosPtrNoCache(int32& nStride, uint32 nFlags, int32 nOffset)
{
	return nullptr;
}

byte* CryEngineMesh::GetPosPtr(int32& nStride, uint32 nFlags, int32 nOffset)
{
	return nullptr;
}

byte* CryEngineMesh::GetNormPtr(int32& nStride, uint32 nFlags, int32 nOffset)
{
	return nullptr;
}

byte* CryEngineMesh::GetColorPtr(int32& nStride, uint32 nFlags, int32 nOffset)
{
	return nullptr;
}

byte* CryEngineMesh::GetUVPtrNoCache(int32& nStride, uint32 nFlags, int32 nOffset)
{
	return nullptr;
}

byte* CryEngineMesh::GetUVPtr(int32& nStride, uint32 nFlags, int32 nOffset)
{
	return nullptr;
}

byte* CryEngineMesh::GetTangentPtr(int32& nStride, uint32 nFlags, int32 nOffset)
{
	return nullptr;
}

byte* CryEngineMesh::GetQTangentPtr(int32& nStride, uint32 nFlags, int32 nOffset)
{
	return nullptr;
}

byte* CryEngineMesh::GetHWSkinPtr(int32& nStride, uint32 nFlags, int32 nOffset, bool remapped)
{
	return nullptr;
}

byte* CryEngineMesh::GetVelocityPtr(int32& nStride, uint32 nFlags, int32 nOffset)
{
	return nullptr;
}

void CryEngineMesh::UnlockStream(int nStream)
{

}

void CryEngineMesh::UnlockIndexStream()
{

}

vtx_idx* CryEngineMesh::GetIndexPtr(uint32 nFlags, int32 nOffset)
{
	return nullptr;
}

const PodArray<std::pair<int, int> >* CryEngineMesh::GetTrisForPosition(const Vec3& vPos, IMaterial* pMaterial)
{
	return nullptr;
}

float CryEngineMesh::GetExtent(EGeomForm eForm)
{
	return 0.0f;
}

void CryEngineMesh::GetRandomPoints(
	Array<PosNorm> points, CRndGen& seed,
	EGeomForm eForm, SSkinningData const* pSkinning)
{

}

uint32* CryEngineMesh::GetPhysVertexMap()
{ 
	return NULL; 
}

bool CryEngineMesh::IsEmpty()
{
	return false;
}

size_t CryEngineMesh::GetMemoryUsage(ICrySizer* pSizer, EMemoryUsageArgument nType) const
{
	return 0;
}

void   CryEngineMesh::GetMemoryUsage(ICrySizer* pSizer) const
{

}

float  CryEngineMesh::GetAverageTrisNumPerChunk(IMaterial* pMat)
{
	return 0.0f;
}
int    CryEngineMesh::GetTextureMemoryUsage(
	const IMaterial* pMaterial, ICrySizer* pSizer, bool bStreamedIn) const
{
	return 0;
}

int CryEngineMesh::GetAllocatedBytes(bool bVideoMem) const
{
	return 0;
}

void CryEngineMesh::SetBBox(const Vec3& vBoxMin, const Vec3& vBoxMax) 
{ 
	m_vBoxMin = vBoxMin; 
	m_vBoxMax = vBoxMax; 
}

void CryEngineMesh::GetBBox(Vec3& vBoxMin, Vec3& vBoxMax)
{ 
	vBoxMin = m_vBoxMin; vBoxMax = m_vBoxMax; }
void CryEngineMesh::UpdateBBoxFromMesh()
{

}

// Debug draw this render mesh.
void CryEngineMesh::DebugDraw(
	const struct SGeometryDebugDrawInfo& info, 
	uint32 nVisibleChunksMask)
{

}
void CryEngineMesh::KeepSysMesh(bool keep)
{

}
void CryEngineMesh::UnKeepSysMesh()
{

}
void CryEngineMesh::LockForThreadAccess()
{

}
void CryEngineMesh::UnLockForThreadAccess()
{

}

volatile int* CryEngineMesh::SetAsyncUpdateState()
{
	return nullptr;
}

void CryEngineMesh::CreateRemappedBoneIndicesPair(
	const uint pairGuid, const TRenderChunkArray& Chunks)
{

}

void CryEngineMesh::CreateRemappedBoneIndicesPair(
	const DynArray<JointIdType>& arrRemapTable, 
	const uint pairGuid, const void* tag)
{

}

void CryEngineMesh::ReleaseRemappedBoneIndicesPair(const uint pairGuid)
{

}

void CryEngineMesh::OffsetPosition(const Vec3& delta)
{ 
	m_vBoxMin += delta; m_vBoxMax += delta; 
}

bool CryEngineMesh::RayIntersectMesh(
	const Ray& ray, Vec3& hitpos, Vec3& p0, Vec3& p1, 
	Vec3& p2, Vec2& uv0, Vec2& uv1, Vec2& uv2)
{
	return true;
}
