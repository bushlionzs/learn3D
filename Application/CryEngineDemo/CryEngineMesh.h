#include <CryRenderer/IRenderMesh.h>
#include <CryEngineCommon.h>
#include <mutex>
#define FRM_RELEASED              BIT(0)
#define FRM_DEPRECTATED_FLAG      BIT(1)
#define FRM_READYTOUPLOAD         BIT(2)
#define FRM_ALLOCFAILURE          BIT(3)
#define FRM_SKINNED               BIT(4)
#define FRM_SKINNEDNEXTDRAW       BIT(5) // no proper support yet for objects that can be skinned and not skinned.
#define FRM_ENABLE_NORMALSTREAM   BIT(6)
#define FRM_SKINNED_EIGHT_WEIGHTS BIT(7)

#if defined(FEATURE_SVO_GI)
#define MAX_RELEASED_MESH_FRAMES (4) // GI voxelization threads may keep using render mesh for several frames
#else
#define MAX_RELEASED_MESH_FRAMES (2)
#endif

namespace Ogre
{
	class Mesh;
}

class CryEngineMesh : public IRenderMesh
{
	friend class CRenderer;
public:
	CryEngineMesh(const char* szType, const char* szSourceName, bool bLock = false);
	CryEngineMesh();

	//! destructor
	~CryEngineMesh();

	virtual bool CanUpdate() final { return (m_nFlags & FRM_ALLOCFAILURE) == 0; }
	virtual bool CanRender() final { return (m_nFlags & FRM_ALLOCFAILURE) == 0; }

	virtual void AddRef() final;
	virtual int Release() final;

	virtual const char* GetTypeName() final;
	virtual const char* GetSourceName() const final;

	virtual int GetIndicesCount() final;
	virtual int GetVerticesCount() final;

	virtual InputLayoutHandle   GetVertexFormat() final;
	virtual ERenderMeshType GetMeshType() final;

	virtual void SetSkinned(bool bSkinned = true) final;
	virtual uint GetSkinningWeightCount() const final;

	virtual float GetGeometricMeanFaceArea() const final;

	virtual void NextDrawSkinned() final;

	virtual void GenerateQTangents() final;
	virtual void CreateChunksSkinned() final;
	virtual void CopyTo(IRenderMesh* pDst, int nAppendVtx = 0, bool bDynamic = false, bool fullCopy = true) final;
	virtual void SetSkinningDataVegetation(struct SMeshBoneMapping_uint8* pBoneMapping) final;
	virtual void SetSkinningDataCharacter(CMesh& mesh, uint32 flags, struct SMeshBoneMapping_uint16* pBoneMapping, struct SMeshBoneMapping_uint16* pExtraBoneMapping) final;
	// Creates an indexed mesh from this render mesh (accepts an optional pointer to an IIndexedMesh object that should be used)
	virtual IIndexedMesh* GetIndexedMesh(IIndexedMesh* pIdxMesh = 0) final;
	virtual int           GetRenderChunksCount(IMaterial* pMat, int& nRenderTrisCount) final;

	virtual IRenderMesh* GenerateMorphWeights() final;
	virtual IRenderMesh* GetMorphBuddy() final;
	virtual void         SetMorphBuddy(IRenderMesh* pMorph) final;

	// Create render buffers from render mesh. Returns the final size of the render mesh or ~0U on failure
	virtual size_t SetMesh(CMesh& mesh, int nSecColorsSetOffset, uint32 flags, const Vec3* pPosOffset, bool requiresLock) final;
	size_t SetMesh_Int(CMesh& mesh, int nSecColorsSetOffset, uint32 flags, const Vec3* pPosOffset);
	// Update system vertices buffer
	virtual bool UpdateVertices(const void* pVertBuffer, int nVertCount, int nOffset, int nStream, uint32 copyFlags, bool requiresLock = true) final;
	// Update system indices buffer
	virtual bool UpdateIndices(const vtx_idx* pNewInds, int nInds, int nOffsInd, uint32 copyFlags, bool requiresLock = true) final;

	virtual void SetCustomTexID(int nCustomTID) final;
	virtual void SetChunk(int nIndex, CRenderChunk& chunk) final;
	virtual void SetChunk(IMaterial* pNewMat, int nFirstVertId, int nVertCount, 
		int nFirstIndexId, int nIndexCount, float texelAreaDensity, int nIndex) final;

	virtual void SetRenderChunks(CRenderChunk* pChunksArray, int nCount, bool bSubObjectChunks) final;

	virtual TRenderChunkArray& GetChunks() final;
	virtual TRenderChunkArray& GetChunksSkinned() final;
	virtual TRenderChunkArray& GetChunksSubObjects() final;
	virtual CryEngineMesh* GetVertexContainer() final;
	virtual void               SetVertexContainer(IRenderMesh* pBuf) final;

	virtual void Render(CRenderObject* pObj, const SRenderingPassInfo& passInfo) final;
	virtual void AddRenderElements(IMaterial* pIMatInfo, CRenderObject* pObj, const SRenderingPassInfo& passInfo, int nSortId = EFSLIST_GENERAL, int nAW = 1) final;
	virtual void SetREUserData(float* pfCustomData, float fFogScale = 0, float fAlpha = 1) final;
	virtual void AddRE(IMaterial* pMaterial, CRenderObject* pObj, IShader* pEf, const SRenderingPassInfo& passInfo, int nList, int nAW) final;

	virtual byte* GetPosPtrNoCache(int32& nStride, uint32 nFlags, int32 nOffset = 0) final;
	virtual byte* GetPosPtr(int32& nStride, uint32 nFlags, int32 nOffset = 0) final;
	virtual byte* GetNormPtr(int32& nStride, uint32 nFlags, int32 nOffset = 0) final;
	virtual byte* GetColorPtr(int32& nStride, uint32 nFlags, int32 nOffset = 0) final;
	virtual byte* GetUVPtrNoCache(int32& nStride, uint32 nFlags, int32 nOffset = 0) final;
	virtual byte* GetUVPtr(int32& nStride, uint32 nFlags, int32 nOffset = 0) final;

	virtual byte* GetTangentPtr(int32& nStride, uint32 nFlags, int32 nOffset = 0) final;
	virtual byte* GetQTangentPtr(int32& nStride, uint32 nFlags, int32 nOffset = 0) final;

	virtual byte* GetHWSkinPtr(int32& nStride, uint32 nFlags, int32 nOffset = 0, bool remapped = false) final;
	virtual byte* GetVelocityPtr(int32& nStride, uint32 nFlags, int32 nOffset = 0) final;

	virtual void UnlockStream(int nStream) final;
	virtual void UnlockIndexStream() final;

	virtual vtx_idx* GetIndexPtr(uint32 nFlags, int32 nOffset = 0) final;
	virtual const PodArray<std::pair<int, int> >* GetTrisForPosition(const Vec3& vPos, IMaterial* pMaterial) final;
	virtual float GetExtent(EGeomForm eForm) final;
	virtual void GetRandomPoints(Array<PosNorm> points, CRndGen& seed, EGeomForm eForm, SSkinningData const* pSkinning = NULL) final;
	virtual uint32* GetPhysVertexMap() final;
	virtual bool IsEmpty() final;

	virtual size_t GetMemoryUsage(ICrySizer* pSizer, EMemoryUsageArgument nType) const final;
	virtual void   GetMemoryUsage(ICrySizer* pSizer) const final;
	virtual float  GetAverageTrisNumPerChunk(IMaterial* pMat) final;
	virtual int    GetTextureMemoryUsage(const IMaterial* pMaterial, ICrySizer* pSizer = NULL, bool bStreamedIn = true) const final;
	// Get allocated only in video memory or only in system memory.
	virtual int GetAllocatedBytes(bool bVideoMem) const final;

	virtual void SetBBox(const Vec3& vBoxMin, const Vec3& vBoxMax) final;
	virtual void GetBBox(Vec3& vBoxMin, Vec3& vBoxMax) final;
	virtual void UpdateBBoxFromMesh() final;

	// Debug draw this render mesh.
	virtual void DebugDraw(const struct SGeometryDebugDrawInfo& info, uint32 nVisibleChunksMask = ~0) final;
	virtual void KeepSysMesh(bool keep) final;
	virtual void UnKeepSysMesh() final;
	virtual void LockForThreadAccess() final;
	virtual void UnLockForThreadAccess() final;

	virtual volatile int* SetAsyncUpdateState() final;
	void CreateRemappedBoneIndicesPair(const uint pairGuid, const TRenderChunkArray& Chunks);
	virtual void CreateRemappedBoneIndicesPair(const DynArray<JointIdType>& arrRemapTable, const uint pairGuid, const void* tag) final;
	virtual void ReleaseRemappedBoneIndicesPair(const uint pairGuid) final;

	virtual void OffsetPosition(const Vec3& delta) final;

	bool RayIntersectMesh(const Ray& ray, Vec3& hitpos, Vec3& p0, Vec3& p1, Vec3& p2, Vec2& uv0, Vec2& uv1, Vec2& uv2) final;

	inline void _SetRenderMeshType(ERenderMeshType eType) 
	{ 
		m_eType = eType; 
	}

	inline int GetStreamStride(int nStream) const;

	inline void _SetVertexFormat(InputLayoutHandle eVF) { m_eVF = eVF; }
	inline void _SetNumVerts(int nVerts) { m_nVerts = max(nVerts, 0); }
	inline void _SetNumInds(int nInds)
	{ 
		m_nInds = nInds; 
	}
	inline void _SetPrimitiveType(const ERenderPrimitiveType nPrimType) 
	{ 
		m_nPrimetiveType = nPrimType; 
	}

	Ogre::Mesh* getOgreMesh()
	{
		return mOgreMesh;
	}

	int getMatId(int index)
	{
		return matIds[index];
	}

	void updateOgreState(bool add)
	{
		mAddToOgre = add;
	}

	bool getOgreState()
	{
		return mAddToOgre;
	}
private:
	int   m_nRefCounter;
	uint16 m_nFlags;

	string m_sType;          //!< pointer to the type name in the constructor call
	string m_sSource;        //!< pointer to the source  name in the constructor call

	Vec3 m_vBoxMin;
	Vec3 m_vBoxMax;

	int32 m_nInds;
	uint32 m_nVerts;

	InputLayoutHandle m_eVF;
	ERenderPrimitiveType m_nPrimetiveType;
	ERenderMeshType m_eType;
	int m_nClientTextureBindID;
	float m_fGeometricMeanFaceArea;

	TRenderChunkArray m_Chunks;
	TRenderChunkArray              m_ChunksSubObjects; // Chunks of sub-objects.
	TRenderChunkArray              m_ChunksSkinned;

	CryEngineMesh* m_pVertexContainer = nullptr;

	std::recursive_mutex _mutex;

	std::string mType;
	std::string mSourceName;
	std::vector<int> matIds;


	Ogre::Mesh* mOgreMesh;

	std::unordered_map<int32_t, std::vector<char>> mVerticesMap;
	std::vector<vtx_idx> mIndexData;
	bool mCreateMesh = false;

	bool mAddToOgre = false;
};