#pragma once

#include <CryMemory/CryPool/PoolAlloc.h>
#include <CryThreading/IJobManager.h>
#include <CryThreading/CryThreadSafePushContainer.h>
#include <concqueue/concqueue.hpp>
#include <Cry3DEngine/I3DEngine.h>
#include <CryEngine/RenderDll/Common/ElementPool.h>

namespace Ogre
{
	class OgreTexture;
}
typedef void (PROCRENDEF)(SShaderPass* l, int nPrimType);

#define USE_NATIVE_DEPTH 1

enum eAntialiasingType
{
	eAT_NOAA = 0,
	eAT_SMAA_1X,
	eAT_SMAA_1TX,
	eAT_SMAA_2TX,
	eAT_TSAA,
	eAT_AAMODES_COUNT,

	eAT_DEFAULT_AA                  = eAT_SMAA_1TX,

	eAT_NOAA_MASK                   = (1 << eAT_NOAA),
	eAT_SMAA_1X_MASK                = (1 << eAT_SMAA_1X),
	eAT_SMAA_1TX_MASK               = (1 << eAT_SMAA_1TX),
	eAT_SMAA_2TX_MASK               = (1 << eAT_SMAA_2TX),
	eAT_TSAA_MASK                   = (1 << eAT_TSAA),

	eAT_SMAA_MASK                   = (eAT_SMAA_1X_MASK | eAT_SMAA_1TX_MASK | eAT_SMAA_2TX_MASK),

	eAT_REQUIRES_PREVIOUSFRAME_MASK = (eAT_SMAA_1TX_MASK | eAT_SMAA_2TX_MASK | eAT_TSAA_MASK),
	eAT_REQUIRES_SUBPIXELSHIFT_MASK = (                    eAT_SMAA_2TX_MASK | eAT_TSAA_MASK)
};

constexpr const char* s_pszAAModes[eAT_AAMODES_COUNT] =
{
	"NO AA",
	"SMAA 1X",
	"SMAA 1TX",
	"SMAA 2TX",
	"TSAA"
};


struct IOpticsManager;
struct IStatObj;
struct ShadowMapFrustum;
struct SShaderPass;

class CREParticle;
class CD3DStereoRenderer;
class CTextureManager;
class CIntroMovieRenderer;
class CDeviceResourceSet;
class CVertexBuffer;
class CIndexBuffer;
class CStandardGraphicsPipeline;
class CMinimumGraphicsPipeline;
class CBillboardGraphicsPipeline;
class CMobileGraphicsPipeline;
class CBaseResource;
class CSwapChainBackedRenderDisplayContext;

namespace gpu_pfx2 {
class IManager;
class CManager;
}

namespace compute_skinning {
class CStorage;
struct IComputeSkinningStorage;
}

typedef int (* pDrawModelFunc)(void);

//=============================================================

#define D3DRGBA(r, g, b, a)                                \
  ((((int)((a) * 255)) << 24) | (((int)((r) * 255)) << 16) \
   | (((int)((g) * 255)) << 8) | (int)((b) * 255)          \
  )

struct alloc_info_struct
{
	int         ptr;
	int         bytes_num;
	bool        busy;
	const char* szSource;
	unsigned Size()                                  { return sizeof(*this); }

	void     GetMemoryUsage(ICrySizer* pSizer) const {}
};

const float TANGENT30_2 = 0.57735026918962576450914878050196f * 2;   // 2*tan(30)

// Assuming 24 bits of depth precision
#define DBT_SKY_CULL_DEPTH                    0.99999994f

#define DEF_SHAD_DBT_DEFAULT_VAL              1
#define SHADOWS_DBT_DEFAULT_VAL               1

#define TEXSTREAMING_DEFAULT_VAL              2

#define GEOM_INSTANCING_DEFAULT_VAL           0
#define COLOR_GRADING_DEFAULT_VAL             1
#define SUNSHAFTS_DEFAULT_VAL                 2
#define HDR_RANGE_ADAPT_DEFAULT_VAL           0
#define HDR_RENDERING_DEFAULT_VAL             1
#define TEXPREALLOCATLAS_DEFAULT_VAL          0
#define TEXMAXANISOTROPY_DEFAULT_VAL          8
#if CRY_PLATFORM_DESKTOP
	#define TEXNOANISOALPHATEST_DEFAULT_VAL     0
#else
	#define TEXNOANISOALPHATEST_DEFAULT_VAL     1
#endif

#if CRY_PLATFORM_CONSOLE && defined(_RELEASE)
#define SHADERS_ALLOW_COMPILATION_DEFAULT_VAL 0
#else
#define SHADERS_ALLOW_COMPILATION_DEFAULT_VAL 1
#endif

#define ENVTEXRES_DEFAULT_VAL                 3
#define WATERREFLQUAL_DEFAULT_VAL             4
#define DOF_DEFAULT_VAL                       2
#define SHADERS_PREACTIVATE_DEFAULT_VAL       3
#define CUSTOMVISIONS_DEFAULT_VAL             3
#define FLARES_DEFAULT_VAL                    1
#define WATERVOLCAUSTICS_DEFAULT_VAL          1
#define FLARES_HQSHAFTS_DEFAULT_VAL           1
#define DEF_SHAD_SSS_DEFAULT_VAL              1

#define MULTITHREADED_DEFAULT_VAL             1
#define ZPASS_DEPTH_SORT_DEFAULT_VAL          1
#define TEXSTREAMING_UPDATETYPE_DEFAULT_VAL   1

#define MAX_PREDICTION_ZONES                  MAX_STREAM_PREDICTION_ZONES

#define MAX_SHADOWMAP_FRUSTUMS                1024
#define MAX_DEFERRED_LIGHTS                   256

#define TEMP_REND_OBJECTS_POOL                (2048)

#define MAX_REND_LIGHTS                       32

#if CRY_PLATFORM_WINDOWS || CRY_PLATFORM_APPLE || CRY_PLATFORM_LINUX || CRY_PLATFORM_ANDROID
	#define CBUFFER_NATIVE_DEPTH_DEAFULT_VAL 1
#else
	#define CBUFFER_NATIVE_DEPTH_DEAFULT_VAL 0
#endif





//////////////////////////////////////////////////////////////////////
// 3D engine duplicated data for non-thread safe data
namespace N3DEngineCommon
{

struct SOceanInfo
{
	Vec4  m_vCausticsParams = { 0.0f, 0.0f, 0.0f, 0.0f };
	Vec4  m_vMeshParams = { 0.0f, 0.0f, 0.0f, 0.0f };
	float m_fWaterLevel = 0.0f;
	uint8 m_nOceanRenderFlags = 0;
};

struct SSkyInfo
{
	bool                  m_bIsVisible;
	bool                  m_bApplySkyDome;
	bool                  m_bApplySkyBox;

	float                 m_fSkyBoxStretching = 1;

	// These params can be overridden by the sky material
	float                 m_fSkyBoxAngle = 0;
	float                 m_fSkyBoxMultiplier;
	Vec3                  m_vSkyBoxEmittance;
	Vec3                  m_vSkyBoxFilter;

	_smart_ptr<IMaterial> m_pSkyMaterial;


	~SSkyInfo() { Release(); }
	void Release()
	{
		m_pSkyMaterial = nullptr;
	}
};

struct SVisAreaInfo
{
	SVisAreaInfo() : nFlags(0)
	{
	};
	uint32 nFlags;
};

struct SRainOccluder
{
	SRainOccluder() : m_RndMesh(0), m_WorldMat(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0) {}
	_smart_ptr<IRenderMesh> m_RndMesh;
	Matrix34                m_WorldMat;
};

typedef std::vector<SRainOccluder> ArrOccluders;

struct SRainOccluders
{
	ArrOccluders m_arrOccluders;
	size_t       m_nNumOccluders;
	bool         m_bProcessed[MAX_GPU_NUM];

	SRainOccluders() : m_nNumOccluders(0) { for (int i = 0; i < MAX_GPU_NUM; ++i) m_bProcessed[i] = true; }
	~SRainOccluders() { Release(); }
	void Release()
	{
		stl::free_container(m_arrOccluders);
		m_nNumOccluders = 0;
		for (int i = 0; i < MAX_GPU_NUM; ++i) m_bProcessed[i] = true;
	}
};

struct SCausticInfo
{
	SCausticInfo() : m_pCausticQuadMesh(0), m_nCausticMeshWidth(0), m_nCausticMeshHeight(0), m_nCausticQuadTaps(0), m_nVertexCount(0), m_nIndexCount(0),
		m_mCausticMatr(IDENTITY), m_mCausticViewMatr(IDENTITY)
	{
	}

	~SCausticInfo() { Release(); }
	void Release()
	{
		m_pCausticQuadMesh = NULL;
	}

	_smart_ptr<IRenderMesh> m_pCausticQuadMesh;
	uint32                  m_nCausticMeshWidth;
	uint32                  m_nCausticMeshHeight;
	uint32                  m_nCausticQuadTaps;
	uint32                  m_nVertexCount;
	uint32                  m_nIndexCount;

	Matrix44A               m_mCausticMatr;
	Matrix34                m_mCausticViewMatr;
};
}

struct SRenderThread;
struct S3DEngineCommon
{
	enum EVisAreaFlags
	{
		VAF_EXISTS_FOR_POSITION    = (1 << 0),
		VAF_CONNECTED_TO_OUTDOOR   = (1 << 1),
		VAF_AFFECTED_BY_OUT_LIGHTS = (1 << 2),
		VAF_MASK                   = VAF_EXISTS_FOR_POSITION | VAF_CONNECTED_TO_OUTDOOR | VAF_AFFECTED_BY_OUT_LIGHTS
	};

	N3DEngineCommon::SVisAreaInfo   m_pCamVisAreaInfo;
	N3DEngineCommon::SSkyInfo       m_SkyInfo;
	N3DEngineCommon::SOceanInfo     m_OceanInfo;
	N3DEngineCommon::SRainOccluders m_RainOccluders;
	N3DEngineCommon::SCausticInfo   m_CausticInfo;
	SRainParams                     m_RainInfo;
	SSnowParams                     m_SnowInfo;

	void Update(const SRenderingPassInfo& passInfo);
	void UpdateSkyInfo(const SRenderingPassInfo& passInfo);
	void UpdateRainInfo(const SRenderingPassInfo& passInfo);
	void UpdateRainOccInfo(const SRenderingPassInfo& passInfo);
	void UpdateSnowInfo(const SRenderingPassInfo& passInfo);
};

struct SVolumetricCloudTexInfo
{
	int32 cloudTexId;
	int32 cloudNoiseTexId;
	int32 edgeNoiseTexId;
};

// Structure that describe properties of the current rendering quality
struct SRenderQuality
{
	EShaderQuality shaderQuality = eSQ_Max;
	ERenderQuality renderQuality = eRQ_Max;

	Vec2           downscaleFactor;

	//////////////////////////////////////////////////////////////////////////
	SRenderQuality() : downscaleFactor(Vec2(1.0f, 1.0f)) {}
};

struct SMSAA
{
	SMSAA() : Type(0), Quality(0), m_pZTexture(nullptr) {}
	void Clear()
	{
		Type = 0;
		Quality = 0;
		m_pZTexture = nullptr;
	}

	uint32    Type;
	uint32    Quality;
	CTexture* m_pZTexture;
};

struct SRTargetStat
{
	string      m_Name;
	uint32      m_nSize;
	uint32      m_nWidth;
	uint32      m_nHeight;
	ETEX_Format m_eTF;

	void        GetMemoryUsage(ICrySizer* pSizer) const
	{
		pSizer->AddObject(m_Name);
	}
};

class CHWShader;

struct CRY_ALIGN(128) SRenderStatistics
{
	struct SFrameSummary
	{
		float idleLoading = 0;
		float busyLoading = 0;

		float waitForMain = 0;
		float waitForRender = 0;
		float waitForGPU_MT = 0;
		float waitForGPU_RT = 0;
		float waitForPresentQueue_RT = 0;
		float waitForGPUActual_RT = 0;
		float waitForFlip_RT = 0;
		float gpuIdlePerc = 0;

		float gpuFrameTime = 0.0166667f;
		float frameTime = 0.0166667f;
		float renderTime = 0.0166667f;

		float sceneTime = 0;
		float flashTime = 0;
		float miscTime = 0;
		float endTime = 0;
	}
	m_Summary;

	int m_NumRendHWInstances;
	int m_RendHWInstancesPolysAll;
	int m_RendHWInstancesPolysOne;
	int m_RendHWInstancesDIPs;
	int m_NumTextChanges;
	int m_NumRTChanges;
	int m_NumStateChanges;
	int m_NumRendSkinnedObjects;
	int m_NumVShadChanges;
	int m_NumPShadChanges;
	int m_NumGShadChanges;
	int m_NumDShadChanges;
	int m_NumHShadChanges;
	int m_NumCShadChanges;
	int m_NumVShaders;
	int m_NumPShaders;
	int m_NumGShaders;
	int m_NumDShaders;
	int m_NumHShaders;
	int m_NumRTs;
	int m_NumSprites;
	int m_NumSpriteDIPS;
	int m_NumSpritePolys;
	int m_NumSpriteUpdates;
	int m_NumSpriteAltasesUsed;
	int m_NumSpriteCellsUsed;
	int m_NumQIssued;
	int m_NumQOccluded;
	int m_NumQNotReady;
	int m_NumQStallTime;
	int m_NumImpostersUpdates;
	int m_NumCloudImpostersUpdates;
	int m_NumImpostersDraw;
	int m_NumCloudImpostersDraw;
	int m_NumTextures;

#if defined(ENABLE_PROFILING_CODE)
	uint32 m_NumShadowPoolFrustums;
	uint32 m_NumShadowPoolAllocsThisFrame;
	uint32 m_NumShadowMaskChannels;
	uint32 m_NumTiledShadingSkippedLights;
#endif

	int m_NumPSInstructions;
	int m_NumVSInstructions;
	int m_RTCleared;
	int m_RTClearedSize;
	int m_RTCopied;
	int m_RTCopiedSize;
	int m_RTSize;

	CHWShader* m_pMaxPShader;
	CHWShader* m_pMaxVShader;
	void* m_pMaxPSInstance;
	void* m_pMaxVSInstance;

	size_t m_ManagedTexturesStreamSysSize;
	size_t m_ManagedTexturesStreamVidSize;
	size_t m_ManagedTexturesSysMemSize;
	size_t m_ManagedTexturesVidMemSize;
	size_t m_DynTexturesSize;
	size_t m_MeshUpdateBytes;
	size_t m_DynMeshUpdateBytes;
	float m_fOverdraw;
	float m_fSkinningTime;
	float m_fPreprocessTime;
	float m_fSceneTimeMT;
	float m_fTexUploadTime;
	float m_fTexRestoreTime;
	float m_fOcclusionTime;
	float m_fRenderTime;
	float m_fEnvCMapUpdateTime;
	float m_fEnvTextUpdateTime;

	float m_fRefractionPartialResolveEstimatedCost;
	int m_refractionPartialResolveCount;
	int m_refractionPartialResolvePixelCount;

	int m_NumRendMaterialBatches;
	int m_NumRendGeomBatches;
	int m_NumRendInstances;

#if defined(ENABLE_PROFILING_CODE)
	// Synchronously recorded stats
	int m_nNumInsts;
	int m_nNumInstCalls;

	int m_nNumPSOSwitches;
	int m_nNumLayoutSwitches;
	int m_nNumResourceSetSwitches;
	int m_nNumInlineSets;
	int m_nNumTopologySets;
	int m_nDIPs[EFSLIST_NUM];
	int m_nPolygons[EFSLIST_NUM];
	int m_nPolygonsByTypes[EFSLIST_NUM][EVCT_NUM][2];

	// Asynchronously recorded stats
	int m_nAsynchNumInsts;
	int m_nAsynchNumInstCalls;

	int m_nAsynchNumPSOSwitches;
	int m_nAsynchNumLayoutSwitches;
	int m_nAsynchNumResourceSetSwitches;
	int m_nAsynchNumInlineSets;
	int m_nAsynchNumTopologySets;
	int m_nAsynchDIPs[EFSLIST_NUM];
	int m_nAsynchPolygons[EFSLIST_NUM];
	int m_nAsynchPolygonsByTypes[EFSLIST_NUM][EVCT_NUM][2];
#endif

	int m_nModifiedCompiledObjects;
	int m_nTempCompiledObjects;
	int m_nIncompleteCompiledObjects;

	int m_nNumBoundVertexBuffers[2];   // Local=0,PCIe=1 - or in tech-speak, L1=0 and L0=1
	int m_nNumBoundIndexBuffers[2];    // Local=0,PCIe=1 - or in tech-speak, L1=0 and L0=1
	int m_nNumBoundConstBuffers[2];    // Local=0,PCIe=1 - or in tech-speak, L1=0 and L0=1
	int m_nNumBoundInlineBuffers[2];   // Local=0,PCIe=1 - or in tech-speak, L1=0 and L0=1
	int m_nNumBoundUniformBuffers[2];  // Local=0,PCIe=1 - or in tech-speak, L1=0 and L0=1
	int m_nNumBoundUniformTextures[2]; // Local=0,PCIe=1 - or in tech-speak, L1=0 and L0=1


	void Begin(const SRenderStatistics* prevData);
	void Finish();

#if defined(ENABLE_PROFILING_CODE)
	int GetNumGeomInstances() const;
	int GetNumGeomInstanceDrawCalls() const;

	int GetNumberOfDrawCalls() const;
	int GetNumberOfDrawCalls(const uint32 EFSListMask) const;
	int GetNumberOfPolygons() const;
	int GetNumberOfPolygons(const uint32 EFSListMask) const;
#endif
};
class CRenderDisplayContext;
class CParticleBufferSet;
//////////////////////////////////////////////////////////////////////
class  CRenderer : public IRenderer
{
	friend class CRendererResources;
	friend class CRendererCVars;

public:

	CRenderer();
	virtual ~CRenderer();

	virtual void InitRenderer();

	virtual void PostInit() override;

	virtual void StartRenderIntroMovies() override;
	virtual void StopRenderIntroMovies(bool bWaitForFinished) override;
	virtual bool IsRenderingIntroMovies() const override;

	virtual void PostLevelLoading() override;

	void         PreShutDown();
	void         PostShutDown();


	virtual void SyncComputeVerticesJobs() override {}

	virtual void RT_SplashFast() {}
	virtual void RT_ClearFast() {}
	virtual void RT_PresentFast() {}

	virtual int  CurThreadList() override;
	virtual void RT_BeginFrame(
		const SDisplayContextKey& displayContextKey, const SGraphicsPipelineKey& graphicsPipelineKey) {
	}
	virtual void RT_EndFrame() {}

	virtual void RT_Init() {}
	virtual void RT_ShutDown(uint32 nFlags) {}
	virtual bool RT_CreateDevice() 
	{
		return true;
	}
	virtual void RT_Reset() {}

	virtual void RT_RenderScene(CRenderView* pRenderView) {}

	virtual void RT_ReleaseRenderResources(uint32 nFlags) {}

	virtual void RT_CreateRenderResources() {}
    virtual void RT_PrecacheDefaultShaders() {}
	virtual bool RT_ReadTexture(void* pDst, int destinationWidth,
		int destinationHeight, EReadTextureFormat dstFormat, CTexture* pSrc) 
	{
		return true;
	}
	virtual bool RT_StoreTextureToFile(const char* szFilePath, CTexture* pSrc)
	{
		return true;
	}
	virtual void FlashRenderPlayer(std::shared_ptr<IFlashPlayer>&& pPlayer) override {}
	virtual void FlashRender(std::shared_ptr<IFlashPlayer_RenderProxy>&& pPlayer) override {}
	virtual void FlashRenderPlaybackLockless(
		std::shared_ptr<IFlashPlayer_RenderProxy>&& pPlayer, int cbIdx, bool finalPlayback) override 
	{
	}
	virtual void FlashRemoveTexture(ITexture* pTexture) override {}

	virtual void RT_RenderDebug(bool bRenderStats = true) {}

	virtual void RT_FlashRenderInternal(std::shared_ptr<IFlashPlayer>&& pPlayer)
	{

	}
	virtual void RT_FlashRenderInternal(std::shared_ptr<IFlashPlayer_RenderProxy>&& pPlayer, bool doRealRender)
	{

	}
	virtual void RT_FlashRenderPlaybackLocklessInternal(
		std::shared_ptr<IFlashPlayer_RenderProxy>&& pPlayer, int cbIdx, bool finalPlayback, bool doRealRender)
	{

	}
	virtual bool FlushRTCommands(bool bWait, bool bImmediatelly, bool bForce) override { return true; }
	virtual bool ForceFlushRTCommands() { return true; }
	virtual void WaitForParticleBuffer(int frameId)
	{

	}

	virtual void RequestFlushAllPendingTextureStreamingJobs(int nFrames) override 
	{ 
		m_nFlushAllPendingTextureStreamingJobs = nFrames; 
	}
	virtual void SetTexturesStreamingGlobalMipFactor(float fFactor) override      { m_fTexturesStreamingGlobalMipFactor = fFactor; }

	virtual void SetRendererCVar(ICVar* pCVar, const char* pArgText, const bool bSilentMode = false) override
	{

	}

#ifdef CRY_PLATFORM_WINDOWS
	virtual RectI GetDefaultContextWindowCoordinates() final;
#endif
	bool          IsCurrentContextMainVP();

	void          SetActiveContext(const std::shared_ptr<CRenderDisplayContext>& ctx, const SDisplayContextKey& key);

	/////////////////////////////////////////////////////////////////////////////////
	// Render-pipeline management
	/////////////////////////////////////////////////////////////////////////////////
	const std::shared_ptr<CGraphicsPipeline>&  GetActiveGraphicsPipeline() const;
	virtual void                               ResetActiveGraphicsPipeline() final;
	virtual std::shared_ptr<CGraphicsPipeline> FindGraphicsPipeline(const SGraphicsPipelineKey& key) const final;
	std::shared_ptr<CGraphicsPipeline>         SetCurrentGraphicsPipeline(const SGraphicsPipelineKey& key);
	virtual bool                               DeleteGraphicsPipeline(const SGraphicsPipelineKey& key)  final;
	virtual SGraphicsPipelineKey               CreateGraphicsPipeline(const SGraphicsPipelineDescription& desc)  final;
	void                                       ResizeGraphicsPipeline(std::shared_ptr<CGraphicsPipeline> graphicsPipeline, int width, int height) ;
	virtual void                               ResizeGraphicsPipeline(const SGraphicsPipelineKey& key, int width, int height)  final;
	virtual void                               ResizePipelineAndContext(const SGraphicsPipelineKey& graphicsPipelineKey, const SDisplayContextKey& displayContextKey, int width, int height)  final;

	virtual SGraphicsPipelineKey               RT_CreateGraphicsPipeline(const SGraphicsPipelineDescription& desc) final;
	virtual bool                               RT_DeleteGraphicsPipeline(const SGraphicsPipelineKey& key) final;
	//===============================================================================

	virtual float* PinOcclusionBuffer(Matrix44A& camera, const SGraphicsPipelineKey& graphicsPipelineKey) override
	{
		return nullptr;
	}

	virtual void        UnpinOcclusionBuffer(const SGraphicsPipelineKey& graphicsPipelineKey) override
	{

	}

	virtual void        AddListener(IRendererEventListener* pRendererEventListener) override;
	virtual void        RemoveListener(IRendererEventListener* pRendererEventListener) override;

	virtual ERenderType GetRenderType() const override;

	virtual CRY_HWND    Init(int x, int y, int width, int height, unsigned int cbpp, int zbpp, int sbits, SSystemInitParams& initParams, bool bReInit = false) override
	{
		return nullptr;
	}

	virtual int         GetFeatures() override { return m_Features; }

	virtual int         GetNumGeomInstances() override;

	virtual int         GetNumGeomInstanceDrawCalls() override;

	virtual int         GetCurrentNumberOfDrawCalls() override;

	virtual void        GetCurrentNumberOfDrawCalls(int& nGeneral, int& nShadowGen) override;

	virtual int         GetCurrentNumberOfDrawCalls(const uint32 EFSListMask) override;

	virtual void        SetDebugRenderNode(IRenderNode* pRenderNode) override;

	virtual bool        IsDebugRenderNode(IRenderNode* pRenderNode) const override;

	EScreenAspectRatio  GetScreenAspect(int nWidth, int nHeight);

	virtual Vec2        SetViewportDownscale(float xscale, float yscale) override;

	virtual void        Release() override;
	virtual void        FreeSystemResources(int nFlags) override;
	virtual void        InitSystemResources(int nFlags) override;

	virtual void        BeginFrame(const SDisplayContextKey& displayContextKey, const SGraphicsPipelineKey& graphicsPipelineKey) override {}
	virtual void        FillFrame(ColorF clearColor) override {}
	virtual void        SplashFrame(ColorF clearColor, ITexture* splashTexture) override {}
	virtual void        RenderDebug(bool bRenderStats = true) override {}
	virtual void        EndFrame() override {}

	virtual void        TryFlush() override {}

	virtual void        Reset(void) {}

	float               GetDrawNearestFOV() const { return m_drawNearFov; }

	virtual void        EnableVSync(bool enable) override {}

	virtual bool        SaveTga(unsigned char* sourcedata, int sourceformat, int w, int h, const char* filename, bool flip) const override;

	//download an image to video memory. 0 in case of failure
	int32_t allocTextureId();
	virtual unsigned int UploadToVideoMemory(
		unsigned char* data, int w, int h, ETEX_Format eTFSrc, ETEX_Format eTFDst, 
		int8 nummipmap, bool repeat = true, int filter = FILTER_BILINEAR, int Id = 0, 
		const char* szCacheName = NULL, int flags = 0, EEndian eEndian = eLittleEndian, 
		RectI* pRegion = NULL, bool bAsynDevTexCreation = false) override;
	virtual unsigned int UploadToVideoMemory3D(unsigned char* data, int w, int h, int d, 
		ETEX_Format eTFSrc, ETEX_Format eTFDst, int8 nummipmap, bool repeat = true, 
		int filter = FILTER_BILINEAR, int Id = 0, const char* szCacheName = NULL, 
		int flags = 0, EEndian eEndian = eLittleEndian, RectI* pRegion = NULL, bool bAsynDevTexCreation = false) override;
	virtual unsigned int UploadToVideoMemoryCube(unsigned char* data, int w, int h, ETEX_Format eTFSrc,
		ETEX_Format eTFDst, int8 nummipmap, bool repeat = true, int filter = FILTER_BILINEAR,
		int Id = 0, const char* szCacheName = NULL, int flags = 0, EEndian eEndian = eLittleEndian,
		RectI* pRegion = NULL, bool bAsynDevTexCreation = false) override;
	virtual void UpdateTextureInVideoMemory(
		uint32 tnum, unsigned char* newdata, int posx, int posy, int w, int h,
		ETEX_Format eTFSrc = eTF_R8G8B8A8, int posz = 0, int sizez = 1) override;

	virtual bool         DXTCompress(const byte* raw_data, int nWidth, int nHeight, ETEX_Format eTF, bool bUseHW, bool bGenMips, int nSrcBytesPerPix, MIPDXTcallback callback) override;
	virtual bool         DXTDecompress(const byte* srcData, const size_t srcFileSize, byte* dstData, int nWidth, int nHeight, int nMips, ETEX_Format eSrcTF, bool bUseHW, int nDstBytesPerPix) override;

	virtual bool         SetGammaDelta(const float fGamma) override { return true; }

	virtual void         RemoveTexture(unsigned int TextureId) override {}
	virtual void PostLevelUnload() {}
	virtual int          GetWhiteTextureId() const override;

	CTextureManager*     GetTextureManager() { return m_pTextureManager; }

	virtual void         PrintResourcesLeaks() {}

	inline float         ScaleCoordXInternal(float value, const SRenderViewport& vp) const       { value *= float(vp.width) / 800.0f; return (value); }
	inline float         ScaleCoordYInternal(float value, const SRenderViewport& vp) const       { value *= float(vp.height) / 600.0f; return (value); }
	inline void          ScaleCoordInternal(float& x, float& y, const SRenderViewport& vp) const { x = ScaleCoordXInternal(x, vp); y = ScaleCoordYInternal(y, vp); }

	virtual float        ScaleCoordX(float value) const override;
	virtual float        ScaleCoordY(float value) const override;
	virtual void         ScaleCoord(float& x, float& y) const override;

//	void                 SetWidth(int nW)                              { ChangeRenderResolution(nW, CRendererResources::s_renderHeight); }
//	void                 SetHeight(int nH)                             { ChangeRenderResolution(CRendererResources::s_renderWidth, nH); }
//	void                 SetPixelAspectRatio(float fPAR)               { m_pixelAspectRatio = fPAR; }

	virtual int          GetWidth() const override { return 0; }
	virtual int          GetHeight() const override { return 0; }

	virtual int          GetOverlayWidth() const override;
	virtual int          GetOverlayHeight() const override;

	virtual float        GetPixelAspectRatio() const override { return (m_pixelAspectRatio); }

	virtual bool         IsStereoEnabled() const override     { return false; }

	virtual float        GetNearestRangeMax() const override { return 0.0f; }

	virtual int          GetWireframeMode()                   { return(m_wireframe_mode); }

	virtual CRenderView* GetOrCreateRenderView(IRenderView::EViewType Type = IRenderView::eViewType_Default)  final;
	virtual void         ReturnRenderView(CRenderView* pRenderView)  final;
	void                 DeleteRenderViews();

	void                 GetPolyCount(int& nPolygons, int& nShadowPolys) override;
	int                  GetPolyCount() override;

	virtual bool         WriteDDS(const byte* dat, int wdt, int hgt, int Size, const char* name, ETEX_Format eF, int NumMips) override;
	virtual bool         WriteTGA(const byte* dat, int wdt, int hgt, const char* name, int src_bits_per_pixel, int dest_bits_per_pixel) override;
	virtual bool         WriteJPG(const byte* dat, int wdt, int hgt, char* name, int src_bits_per_pixel, int nQuality = 100) override;

	virtual void         GetMemoryUsage(ICrySizer* Sizer) override;

	virtual void         GetBandwidthStats(float* fBandwidthRequested) override;

	virtual void         SetTextureStreamListener(ITextureStreamListener* pListener) override;

#if defined(CRY_ENABLE_RC_HELPER)
	virtual void AddAsyncTextureCompileListener(IAsyncTextureCompileListener* pListener);
	virtual void RemoveAsyncTextureCompileListener(IAsyncTextureCompileListener* pListener);
#endif

	virtual void GetLogVBuffers() {}

	virtual int  GetFrameID(bool bIncludeRecursiveCalls = true) override;

	// GPU being updated
	int32 RT_GetCurrGpuID() const;

	// Project/UnProject.  Returns true if successful.
	virtual bool ProjectToScreen(float ptx, float pty, float ptz, float* sx, float* sy, float* sz) override
	{
		return true;
	}
	virtual int  UnProject(float sx, float sy, float sz,
		float* px, float* py, float* pz,
		const float modelMatrix[16],
		const float projMatrix[16],
		const int viewport[4]) override 
	{
		return 0;
	}
	virtual int UnProjectFromScreen(float sx, float sy, float sz, float* px, float* py, float* pz) override 
	{
		return 0;
	}

	// Shadow Mapping
	virtual void OnEntityDeleted(IRenderNode* pRenderNode) override;

	virtual void SetHighlightColor(ColorF color) override { m_highlightColor = color; }
	virtual void SetSelectionColor(ColorF color) override { m_SelectionColor = color; }
	virtual void SetHighlightParams(float outlineThickness, float fGhostAlpha) override
	{
		m_highlightParams = Vec4(outlineThickness, fGhostAlpha, 0.0f, 0.0f);
	}

	ColorF& GetHighlightColor()  { return m_highlightColor; }
	ColorF& GetSelectionColor()  { return m_SelectionColor; }
	Vec4&   GetHighlightParams() { return m_highlightParams; }

	//misc
	virtual bool                ScreenShot(const char* filename = NULL, const SDisplayContextKey& displayContextKey = {}) override
	{
		return true;
	}
	virtual bool                ReadFrameBuffer(
		uint32* pDstRGBA8, int destinationWidth, int destinationHeight,
		bool readPresentedBackBuffer = true, EReadTextureFormat format = EReadTextureFormat::RGB8) override
	{
		return true;
	}

	virtual int                 GetColorBpp() override   { return m_cbpp; }
	virtual int                 GetDepthBpp() override   { return m_zbpp; }
	virtual int                 GetStencilBpp() override { return m_sbpp; }

	virtual void                Set2DMode(bool enable, int ortox, int ortoy, float znear = -1e10f, float zfar = 1e10f) override
	{

	}

	virtual void                LockParticleVideoMemory(int frameId) override                 {}
	virtual void                UnLockParticleVideoMemory(int frameId) override               {}

	virtual void                ActivateLayer(const char* pLayerName, bool activate) override {}

	virtual void                FlushPendingTextureTasks() override;
	virtual void                FlushPendingUploads() override;

	virtual void                SetCloakParams(const SRendererCloakParams& cloakParams) override;
	virtual float               GetCloakFadeLightScale() const override;
	virtual void                SetCloakFadeLightScale(float fColorScale) override;
	virtual void                SetShadowJittering(float shadowJittering) override;
	virtual float               GetShadowJittering() const override;

	virtual void*               FX_AllocateCharInstCB(SSkinningData*, uint32) { return NULL; }
	virtual void                FX_ClearCharInstCB(uint32)                    {}

	virtual EShaderQuality      EF_GetShaderQuality(EShaderType eST) final;
	virtual ERenderQuality      EF_GetRenderQuality() const final { return m_renderQuality.renderQuality; }

	virtual void                EF_SubmitWind(const SWindGrid* pWind) override;

	virtual float               EF_GetWaterZElevation(float fX, float fY) override;

	virtual IOpticsElementBase* CreateOptics(EFlareType type) const override;

	virtual bool                EF_PrecacheResource(ITexture* pTP, float fMipFactor, float fTimeToReady, int Flags, int nUpdateId) final;
	virtual bool                EF_PrecacheResource(SRenderLight* pLS, float fMipFactor, float fTimeToReady, int Flags, int nUpdateId) final;
	virtual bool                EF_PrecacheResource(IRenderShaderResources* pShaderResources, float fMipFactor, float fTimeToReady, int Flags, int nUpdateId) final;
	virtual bool                EF_PrecacheResource(IRenderShaderResources* pShaderResources, int iScreenTexels, float fTimeToReady, int Flags, int nUpdateId) final;
	virtual bool                EF_PrecacheResource(SShaderItem* pSI, int iScreenTexels, float fTimeToReady, int Flags, int nUpdateId) final;
	virtual bool                EF_PrecacheResource(SShaderItem* pSI, float fMipFactor, float fTimeToReady, int Flags, int nUpdateId) final;
	virtual bool                EF_PrecacheResource(IShader* pSH, float fMipFactor, float fTimeToReady, int Flags, int nUpdateId) final;
	virtual bool                EF_PrecacheResource(IRenderMesh* pPB, IMaterial* pMaterial, float fMipFactor, float fTimeToReady, int Flags, int nUpdateId) final;

	// functions for handling particle jobs which cull particles and generate their vertices/indices
	virtual void EF_AddMultipleParticlesToScene(
		const SAddParticlesToSceneJob* jobs, size_t numJobs, const SRenderingPassInfo& passInfo) override 
	{
	}

	//==========================================================
	// external interface for shaders
	//==========================================================
	// Shaders management
	virtual void        EF_SetShaderMissCallback(ShaderCacheMissCallback callback) override;
	virtual const char* EF_GetShaderMissLogPath() override;
	virtual string*     EF_GetShaderNames(int& nNumShaders) override;
	virtual IShader*    EF_LoadShader(const char* name, int flags = 0, uint64 nMaskGen = 0) override;
	virtual SShaderItem EF_LoadShaderItem(const char* name, bool bShare, int flags = 0, SInputShaderResources* Res = NULL, uint64 nMaskGen = 0, const SLoadShaderItemArgs* pArgs = 0) override;
	virtual uint64      EF_GetRemapedShaderMaskGen(const char* name, uint64 nMaskGen = 0, bool bFixup = 0) override;

	virtual uint64      EF_GetShaderGlobalMaskGenFromString(const char* szShaderName, const char* szShaderGen, uint64 nMaskGen = 0) override;
	virtual const char* EF_GetStringFromShaderGlobalMaskGen(const char* szShaderName, uint64 nMaskGen = 0) override;

	// reload file
	virtual bool                   EF_ReloadFile(const char* szFileName) override;
	virtual bool                   EF_ReloadFile_Request(const char* szFileName) override;
	virtual void                   EF_ReloadShaderFiles(int nCategory) override;
	virtual void                   EF_ReloadTextures() override;
	virtual void                   EF_RefreshTextures() override;
	virtual int                    EF_LoadLightmap(const char* nameTex) override;
	virtual DynArray<uint16_t>     EF_RenderEnvironmentCubeHDR(int size, const Vec3& Pos) override;
	virtual bool                   WriteTIFToDisk(const void* pData, int width, int height, int bytesPerChannel, int numChannels, bool bFloat, const char* szPreset, const char* szFileName) override;
	virtual ITexture*              EF_GetTextureByID(int Id) override;
	virtual ITexture*              EF_GetTextureByName(const char* name, uint32 flags = 0) override;
	virtual ITexture*              EF_LoadTexture(const char* nameTex, const uint32 flags = 0) override;
	virtual IDynTextureSource*     EF_LoadDynTexture(const char* dynsourceName, bool sharedRT = false) override;
	virtual const SShaderProfile& GetShaderProfile(EShaderType eST) const override
	{
		static SShaderProfile aa;
		return aa;
	}
	virtual void                   EF_SetShaderQuality(EShaderType eST, EShaderQuality eSQ) override;


	// Create new RE of type (edt)
	virtual CRenderElement* EF_CreateRE(EDataType edt) override;

	// Begin using shaders
	virtual void EF_StartEf(const SRenderingPassInfo& passInfo) override;

	// Get Object for RE transformation
	virtual CRenderObject* EF_DuplicateRO(CRenderObject* pObj, const SRenderingPassInfo& passInfo) final;
	virtual CRenderObject* EF_GetObject() final;
	virtual void           EF_FreeObject(CRenderObject* pObj) final;

	// Draw all shaded REs in the list
	virtual void         EF_EndEf3D(const int nPrecacheUpdateId, const int nNearPrecacheUpdateId, const SRenderingPassInfo& passInfo, const int nRenderFlags) override {}

	virtual void         EF_PrepareShadowTasksForRenderView(const SRenderingPassInfo& passInfo) override {}

	virtual IRenderView* GetNextAvailableShadowsView(IRenderView* pMainRenderView, ShadowMapFrustum* pOwnerFrustum) override
	{
		return nullptr;
	}
	virtual uint32       PrepareShadowFrustumForShadowPool(
		IRenderView* pMainRenderView, ShadowMapFrustum* pFrustum,
		const SRenderLight& light, uint32 frameID, uint32* timeSlicedShadowsUpdated) final
	{
		return 0;
	}

	// 2d interface for shaders
	virtual void EF_EndEf2D(const bool bSort) override {}

	// Dynamic lights
	virtual bool                   EF_IsFakeDLight(const SRenderLight* Source) const override;
	virtual void                   EF_ADDDlight(SRenderLight* Source, const SRenderingPassInfo& passInfo) override;
	virtual bool                   EF_AddDeferredDecal(const SDeferredDecal& rDecal, const SRenderingPassInfo& passInfo) override;

	virtual int                    EF_AddDeferredLight(const SRenderLight& pLight, float fMult, const SRenderingPassInfo& passInfo) override;

	virtual void                   EF_ReleaseDeferredData(CGraphicsPipeline* pGraphicsPipeline) override {}
	virtual SInputShaderResources* EF_CreateInputShaderResource(IRenderShaderResources* pOptionalCopyFrom = nullptr) override;
	virtual void                   ClearPerFrameData(const SRenderingPassInfo& passInfo);
	virtual bool                   EF_UpdateDLight(SRenderLight* pDL) const override;
	void                           EF_CheckLightMaterial(SRenderLight* pLight, uint16 nRenderLightID, const SRenderingPassInfo& passInfo);

	virtual void                   EF_QueryImpl(ERenderQueryTypes eQuery, void* pInOut0, uint32 nInOutSize0, void* pInOut1, uint32 nInOutSize1) override;

	//////////////////////////////////////////////////////////////////////////
	// Post processing effects interfaces

	virtual void  EF_SetPostEffectParam(const char* pParam, float fValue, bool bForceValue = false) override;
	virtual void  EF_SetPostEffectParamVec4(const char* pParam, const Vec4& pValue, bool bForceValue = false) override;
	virtual void  EF_SetPostEffectParamString(const char* pParam, const char* pszArg) override;

	virtual void  EF_GetPostEffectParam(const char* pParam, float& fValue) override;
	virtual void  EF_GetPostEffectParamVec4(const char* pParam, Vec4& pValue) override;
	virtual void  EF_GetPostEffectParamString(const char* pParam, const char*& pszArg) override;

	virtual int32 EF_GetPostEffectID(const char* pPostEffectName) override;

	virtual void  EF_ResetPostEffects(bool bOnSpecChange = false) override;

	virtual void  EF_DisableTemporalEffects() override;

	virtual void  ForceGC() override;

	// create/delete RenderMesh object
	virtual _smart_ptr<IRenderMesh> CreateRenderMesh(
		const char* szType
		, const char* szSourceName
		, IRenderMesh::SInitParamerers* pInitParams = NULL
		, ERenderMeshType eBufType = eRMT_Static
		) override;

	virtual _smart_ptr<IRenderMesh> CreateRenderMeshInitialized(
		const void* pVertBuffer, int nVertCount, InputLayoutHandle eVF,
		const vtx_idx* pIndices, int nIndices,
		const PublicRenderPrimitiveType nPrimetiveType, const char* szType, const char* szSourceName, ERenderMeshType eBufType = eRMT_Static,
		int nMatInfoCount = 1, int nClientTextureBindID = 0,
		bool (*PrepareBufferCallback)(IRenderMesh*, bool) = NULL,
		void* CustomData = NULL,
		bool bOnlyVideoBuffer = false, bool bPrecache = true, const SPipTangents* pTangents = NULL, bool bLockForThreadAcc = false, Vec3* pNormals = NULL) override;

	virtual int GetMaxActiveTexturesARB() { return 0; }

	//////////////////////////////////////////////////////////////////////
	// Replacement functions for the Font engine ( vlad: for font can be used old functions )
	virtual bool FontUploadTexture(class CFBitmap*, ETEX_Format eSrcFormat = eTF_R8G8B8A8) override 
	{
		return true;
	}
	virtual int  FontCreateTexture(int Width, int Height, const byte* pSrcData, ETEX_Format eSrcFormat = eTF_R8G8B8A8, bool genMips = false) override 
	{
		return 0;
	}
	virtual bool FontUpdateTexture(int nTexId, int X, int Y, int USize, int VSize, const byte* pSrcData) override 
	{
		return true;
	}
	virtual void FontReleaseTexture(class CFBitmap* pBmp) override {}

	//////////////////////////////////////////////////////////////////////
	// Used for pausing timer related stuff (eg: for texture animations, and shader 'time' parameter)
	void                         PauseTimer(bool bPause) override { m_bPauseTimer = bPause; }
	virtual IShaderPublicParams* CreateShaderPublicParams() override;

	virtual void                 SetLevelLoadingThreadId(threadID threadId) override;
	virtual void                 GetThreadIDs(threadID& mainThreadID, threadID& renderThreadID) const override;

#if RENDERER_SUPPORT_SCALEFORM
	void                        SF_ConfigMask(int st, uint32 ref);
	virtual int                 SF_CreateTexture(int width, int height, int numMips, const unsigned char* pSrcData, ETEX_Format eSrcFormat, int flags) override;
	virtual void                SF_GetMeshMaxSize(int& numVertices, int& numIndices) const override;

	virtual IScaleformPlayback* SF_CreatePlayback() const override;
	virtual void                SF_Playback(IScaleformPlayback* pRenderer, GRendererCommandBufferReadOnly* pBuffer) const override;
	virtual void                SF_Drain(GRendererCommandBufferReadOnly* pBuffer) const override;
#else // #if RENDERER_SUPPORT_SCALEFORM
	// These dummy functions are required when the feature is disabled, do not remove without testing the RENDERER_SUPPORT_SCALEFORM=0 case!
	virtual int                 SF_CreateTexture(int width, int height, int numMips, const unsigned char* pSrcData, ETEX_Format eSrcFormat, int flags) override { return 0; }
	virtual void                SF_GetMeshMaxSize(int& numVertices, int& numIndices) const override                                                             { numVertices = 0; numIndices = 0; }
	virtual IScaleformPlayback* SF_CreatePlayback() const override { return nullptr; }
	virtual void                SF_Playback(IScaleformPlayback* pRenderer, GRendererCommandBufferReadOnly* pBuffer) const override                              {}
	virtual void                SF_Drain(GRendererCommandBufferReadOnly* pBuffer) const override                                                                {}
#endif // #if RENDERER_SUPPORT_SCALEFORM

	virtual ITexture* CreateTexture(const char* name, int width, int height, int numMips, unsigned char* pSrcData, ETEX_Format eSrcFormat, int flags) override;
	virtual ITexture* CreateTextureArray(const char* name, ETEX_Type eType, uint32 nWidth, uint32 nHeight, uint32 nArraySize, int nMips, uint32 nFlags, ETEX_Format eSrcFormat, int nCustomID) override;

	enum ESPM {ESPM_PUSH = 0, ESPM_POP = 1};
	virtual void                                      SetProfileMarker(const char* label, ESPM mode) const {}

	virtual int                                       GetMaxTextureSize() override                         { return m_MaxTextureSize; }

	virtual void                                      SetCloudShadowsParams(int nTexID, const Vec3& speed, float tiling, bool invert, float brightness) override;
	int                                               GetCloudShadowTextureId() const { return m_cloudShadowTexId; }
	bool                                              GetCloudShadowsEnabled() const;

	virtual void                                      SetVolumetricCloudParams(int nTexID) override;
	virtual void                                      SetVolumetricCloudNoiseTex(int cloudNoiseTexId, int edgeNoiseTexId) override;
	void                                              GetVolumetricCloudTextureInfo(SVolumetricCloudTexInfo& info) const;

	virtual SShadowCacheUpdateMasks*                  GetShadowCacheUdapteMasks() override                                                          
	{
		return nullptr;
	}

	virtual const StaticArray<int, MAX_GSM_LODS_NUM>& GetCachedShadowsResolution() const override                                                   { return m_CachedShadowsResolution; }
	virtual void                                      SetCachedShadowsResolution(const StaticArray<int, MAX_GSM_LODS_NUM>& arrResolutions) override { m_CachedShadowsResolution = arrResolutions; }
	virtual void                                      UpdateCachedShadowsLodCount(int nGsmLods) const override;

	virtual bool                                      IsPost3DRendererEnabled() const override;

	virtual void                                      ExecuteAsyncDIP() override;

	alloc_info_struct*                                GetFreeChunk(int bytes_count, int nBufSize, PodArray<alloc_info_struct>& alloc_info, const char* szSource);
	bool                                              ReleaseChunk(int p, PodArray<alloc_info_struct>& alloc_info);

	virtual const char*                               GetTextureFormatName(ETEX_Format eTF) override;
	virtual uint32                                    GetTextureFormatDataSize(int nWidth, int nHeight, int nDepth, int nMips, ETEX_Format eTF, ETEX_TileMode mode) override;
	virtual void                                      SetDefaultMaterials(IMaterial* pDefMat, IMaterial* pTerrainDefMat) override                          { m_pDefaultMaterial = pDefMat; m_pTerrainDefaultMaterial = pTerrainDefMat; }
	virtual byte*                                     GetTextureSubImageData32(byte* pData, int nDataSize, int nX, int nY, int nW, int nH, CTexture* pTex) { return 0; }

	void                                              PrecacheTexture(ITexture* pTP, float fMipFactor, float fTimeToReady, int Flags, int nUpdateId);

	virtual SSkinningData*                            EF_CreateSkinningData(IRenderView* pRenderView, uint32 nNumBones, bool bNeedJobSyncVar) override;
	virtual SSkinningData*                            EF_CreateRemappedSkinningData(IRenderView* pRenderView, uint32 nNumBones, SSkinningData* pSourceSkinningData, uint32 nCustomDataSize, uint32 pairGuid) override;
	virtual void                                      EF_EnqueueComputeSkinningData(IRenderView* pRenderView, SSkinningData* pData) override;
	virtual int                                       EF_GetSkinningPoolID() override;
	void                                              ClearSkinningDataPool();
	virtual void                                      EnqueueSkinningSimulationJob(JobManager::SJobState*) override;
	virtual void                                      WaitAndClearSkinningSimulationJobs() override;


	virtual void                                      UpdateShaderItem(SShaderItem* pShaderItem, IMaterial* pMaterial) override;
	virtual void                                      ForceUpdateShaderItem(SShaderItem* pShaderItem, IMaterial* pMaterial) override;
	virtual void                                      RefreshShaderResourceConstants(SShaderItem* pShaderItem, IMaterial* pMaterial) override;

	virtual bool                                      LoadShaderStartupCache() override;

	virtual void                                      UnloadShaderStartupCache() override;

	virtual void                                      CopyTextureRegion(ITexture* pSrc, RectI srcRegion, ITexture* pDst, RectI dstRegion, ColorF& color, const int renderStateFlags) override;

	virtual bool                                      LoadShaderLevelCache() override   { return false; }
	virtual void                                      UnloadShaderLevelCache() override {}

	virtual void                                      ClearShaderPipelineStateCache() override;

	virtual void                                      RegisterSyncWithMainListener(ISyncMainWithRenderListener* pListener) override;
	virtual void                                      RemoveSyncWithMainListener(const ISyncMainWithRenderListener* pListener) override;

	virtual void                                      SetCurDownscaleFactor(Vec2 sf) {}

	virtual IGraphicsDeviceConstantBufferPtr          CreateGraphiceDeviceConstantBuffer() override                                              { assert(0);  return 0; }

	virtual void                                      MakeMatrix(const Vec3& pos, const Vec3& angles, const Vec3& scale, Matrix34* mat) override { assert(0); }

public:
	//////////////////////////////////////////////////////////////////////////
	// PUBLIC HELPER METHODS
	//////////////////////////////////////////////////////////////////////////
	void   SyncMainWithRender();

	uint32 GetActiveGPUCount() const override { return 1; }

#if defined(DO_RENDERSTATS)
	std::map<struct IRenderNode*, IRenderer::SDrawCallCountInfo>* GetDrawCallInfoPerNode() { return &m_drawCallInfoPerNode; }
	std::map<struct IRenderMesh*, IRenderer::SDrawCallCountInfo>* GetDrawCallInfoPerMesh() { return &m_drawCallInfoPerMesh; }
#endif

	void Logv(const char* format, ...);
	void LogStrv(const char* format, ...);
	void LogShv(const char* format, ...);
	void Log(const char* str);


	void                            UpdateRenderingModesInfo();
	bool                            IsCustomRenderModeEnabled(uint32 nRenderModeMask);

	bool                            IsEditorMode() const
	{
#if CRY_PLATFORM_DESKTOP
		return (m_bEditor != 0);
#else
		return false;
#endif
	}

	bool IsShaderCacheGenMode() const
	{
#if CRY_PLATFORM_DESKTOP
		return (m_bShaderCacheGen != 0);
#else
		return false;
#endif
	}

	static size_t        GetTexturesStreamPoolSize();

protected:
	void FreePermanentRenderObjects(int bufferId);

public:
	void* operator new(size_t Size)
	{
		void* pPtrRes = CryModuleMemalign(Size, 16);
		memset(pPtrRes, 0, Size);
		return pPtrRes;
	}
	void operator delete(void* Ptr)
	{
		CryModuleMemalignFree(Ptr);
	}

	virtual CRY_HWND GetHWND() override
	{
		return nullptr;
	}

	void             SetTextureAlphaChannelFromRGB(byte* pMemBuffer, int nTexSize);

	void             EnableSwapBuffers(bool bEnable) override { m_bSwapBuffers = bEnable; }
	bool m_bSwapBuffers;

	virtual bool StopRendererAtFrameEnd(uint timeoutMilliseconds) override;
	virtual void ResumeRendererFromFrameEnd() override;
	volatile bool m_bStopRendererAtFrameEnd;

	virtual void                                     SetTexturePrecaching(bool stat) override;
	virtual void                                     PrecachePostponedTextures() override;

	virtual const RPProfilerStats*                   GetRPPStats(ERenderPipelineProfilerStats eStat, bool bCalledFromMainThread = true) override                       { return nullptr; }
	virtual const RPProfilerStats*                   GetRPPStatsArray(bool bCalledFromMainThread = true) override                                                      { return nullptr; }
	virtual const DynArray<RPProfilerDetailedStats>* GetRPPDetailedStatsArray(bool bCalledFromMainThread = true) override                                              { return nullptr; }

	virtual int                                      GetPolygonCountByType(uint32 EFSList, EVertexCostTypes vct, uint32 z, bool bCalledFromMainThread = true) override { return 0; }

	//platform specific
	virtual void        RT_InsertGpuCallback(uint32 context, GpuCallbackFunc callback) override {}
	virtual void        EnablePipelineProfiler(bool bEnable) override {}

	virtual float       GetGPUFrameTime() override;
	virtual void        GetRenderTimes(SRenderTimes& outTimes) override;
	virtual void        LogShaderImportMiss(const CShader* pShader) {}


#ifdef ENABLE_PROFILING_CODE
	void AddRecordedProfilingStats(const struct SProfilingStats& stats, ERenderListID renderList, bool bAsynchronous);
#endif

	virtual void                                       CollectDrawCallsInfo(bool status) override;
	virtual void                                       CollectDrawCallsInfoPerNode(bool status) override;
	virtual void                                       EnableLevelUnloading(bool enable) override;
	virtual void                                       EnableBatchMode(bool enable) override;
	virtual bool                                       IsStereoModeChangePending() override { return false; }

	virtual void  QueryActiveGpuInfo(SGpuInfo& info) const override;
	virtual bool  IsTextureFormatSupported(ETEX_Format eTF) { return true; }
	virtual void  StopLoadtimeFlashPlayback() {}
	virtual void  StartLoadtimeFlashPlayback(ILoadtimeCallback* pCallback) {}
	virtual bool  SF_ClearTexture(int texId, int mipLevel, int numRects,
		const SUpdateRect* pRects, const unsigned char* pData) 
	{
		return true;
	}
	virtual bool SF_UpdateTexture(int texId, int mipLevel, int numRects, const SUpdateRect* pRects, const unsigned char* pData, size_t pitch, size_t size, ETEX_Format eTF)
	{
		return true;
	}
	virtual bool                SetWindowIcon(const char* path)
	{
		return true;
	}

	virtual void CaptureFrameBufferCallBack(void)
	{

	}

	virtual void CloseCaptureFrameBufferFast(void)
	{

	}

	virtual bool UnRegisterCaptureFrame(ICaptureFrameListener* pCapture)
	{
		return true;
	}

	virtual bool RegisterCaptureFrame(ICaptureFrameListener* pCapture)
	{
		return true;
	}

	virtual bool CopyFrameBufferFast(unsigned char* pDstRGB8, int destinationWidth, int destinationHeight)
	{
		return true;
	}

	virtual bool CaptureFrameBufferFast(unsigned char* pDstRGB8, int destinationWidth, int destinationHeight)
	{
		return true;
	}

	virtual bool BakeMesh(const SMeshBakingInputParams* pInputParams, SMeshBakingOutput* pReturnValues)
	{
		return true;
	}

	virtual bool InitCaptureFrameBufferFast(uint32 bufferWidth = 0, uint32 bufferHeight = 0)
	{
		return true;
	}


	virtual void                  Graph(byte* g, int x, int y, int wdt, int hgt, int nC, int type, const char* text, ColorF& color, float fScale)
	{

	}

	virtual IStereoRenderer* GetIStereoRenderer() const
	{
		return nullptr;
	}

	virtual CVrProjectionManager* GetVrProjectionManager()
	{
		return nullptr;
	}

	virtual void            UpdateAuxDefaultCamera(const CCamera& systemCamera)
	{

	}
	virtual void            SubmitAuxGeom(IRenderAuxGeom* pRenderAuxGeom, bool merge = true)
	{

	}

	virtual void DeleteAuxGeom(IRenderAuxGeom* pRenderAuxGeom)
	{

	}

	virtual IRenderAuxGeom* GetOrCreateIRenderAuxGeom(const CCamera* pCustomCamera = nullptr)
	{
		return nullptr;
	}

	virtual IRenderAuxGeom* GetIRenderAuxGeom()
	{
		return nullptr;
	}

	virtual void  PushProfileMarker(const char* label) {}
	virtual void  PopProfileMarker(const char* label) {}
	virtual IStereoRenderer* GetIStereoRenderer()
	{
		return nullptr;
	}

	virtual void         PrepareShadowPool(CRenderView* pRenderView) const
	{

	}

	virtual void UpdateVsync() {}
	virtual void UpdateWindowMode() {}
	virtual void UpdateResolution() {}
	virtual void GetVideoMemoryUsageStats(size_t& vidMemUsedThisFrame, size_t& vidMemUsedRecently, bool bGetPoolsSizes = false)
	{

	}

	virtual SDisplayContextKey CreateSwapChainBackedContext(const SDisplayContextDescription& desc)
	{
		SDisplayContextKey key;
		return key;
	}

	virtual void               ResizeContext(const SDisplayContextKey& key, int width, int height)
	{

	}

	virtual bool               DeleteContext(const SDisplayContextKey& key)
	{
		return true;
	}

	virtual void ShutDown(bool bReInit = false)
	{

	}

	virtual void ShutDownFast()
	{

	}

	virtual int EnumDisplayFormats(SDispFormat* Formats)
	{
		return 1;
	}

	virtual void RestoreGamma(void)
	{

	}
	virtual int	GetDetailedRayHitInfo(IPhysicalEntity* pCollider, const Vec3& vOrigin, const Vec3& vDirection, const float maxRayDist, float* pUOut, float* pVOut)
	{
		return 0;
	}

	virtual Vec3 UnprojectFromScreen(int x, int y)
	{
		return Vec3();
	}

	virtual compute_skinning::IComputeSkinningStorage* GetComputeSkinningStorage()
	{
		return nullptr;
	}
	virtual gpu_pfx2::IManager*                        GetGpuParticleManager() override;


	int GetStreamZoneRoundId(int zone) const 
	{ 
		assert(zone >= 0 && zone < MAX_PREDICTION_ZONES); return m_streamZonesRoundId[zone]; 
	}

	// Only should be used to get current frame id internally in the render thread.
	int                             GetRenderFrameID() const;
	int                             GetMainFrameID()   const;

	threadID                        GetMainThreadID() const   { return m_nFillThreadID; }
	threadID                        GetRenderThreadID() const { return m_nProcessThreadID; }

	//////////////////////////////////////////////////////////////////////////
	// Query Anti-Aliasing information.
	bool                  IsMSAAEnabled() const { return m_MSAAData.Type > 0; }
	const SMSAA&          GetMSAA() const       { return m_MSAAData; }

	void                  SetRenderQuality(const SRenderQuality& quality);
	const SRenderQuality& GetRenderQuality() const { return m_renderQuality; }

	// Animation time is used for rendering animation effects and can be paused if CRenderer::m_bPauseTimer is true
	void       SetAnimationTime(CTimeValue time) { m_animationTime = time; }
	CTimeValue GetAnimationTime() const          { return m_animationTime; }

	// Time of the last main to renderer thread sync
	void       SetFrameSyncTime(CTimeValue time) { m_frameSyncTime = time; }
	CTimeValue GetFrameSyncTime() const          { return m_frameSyncTime; }

	
	// Called every frame from the Render Thread to reclaim deleted resources.
	void      ScheduleResourceForDelete(CBaseResource* pResource);
	void      RT_DelayedDeleteResources(bool bAllResources = false);

public:

	std::vector<Ogre::OgreTexture*> mTextures;
	int32_t mTextureAllocId = 0;
	int32_t mTextureMaxId = 1000;

	Matrix44A      m_IdentityMatrix;

	byte           m_bSystemResourcesInit;
	byte           m_bSystemTargetsInit;
	bool           m_bAquireDeviceThread;
	bool           m_bInitialized;

	SRenderThread* m_pRT;

	CIntroMovieRenderer* m_pIntroMovieRenderer;

	int                  m_CurVertBufferSize;
	int                  m_CurIndexBufferSize;

	int                  m_nGPU;
	int                  m_VSync;
	int                  m_Resizable;
	int                  m_Predicated;

	int                  m_nGraphicsPipeline;

#if defined(SUPPORT_DEVICE_INFO_USER_DISPLAY_OVERRIDES)
	float m_overrideRefreshRate;
	int   m_overrideScanlineOrder;
#endif

	byte      m_bDeviceSupportsInstancing;

	uint32    m_bDeviceSupports_AMDExt;
	uint32    m_bDeviceSupports_NVDBT          : 1;
	uint32    m_bDeviceSupportsTessellation    : 1;
	uint32    m_bDeviceSupportsGeometryShaders : 1;

	uint32    m_bEditor                        : 1; // Render instance created from editor
	uint32    m_bShaderCacheGen                : 1; // Render instance create from shader cache gen mode
	uint32    m_bUseHWSkinning                 : 1;
	uint32    m_bShadersPresort                : 1;
	uint32    m_bEndLevelLoading               : 1;
	uint32    m_bLevelUnloading                : 1;
	uint32    m_bStartLevelLoading             : 1;
	uint32    m_bInLevel                       : 1;
	uint32    m_bUseWaterTessHW                : 1;
	uint32    m_bUseSilhouettePOM              : 1;
	uint32    m_bAllowTerrainLayerBlending     : 1;
	uint32    m_bWaterCaustics                 : 1;
	uint32    m_bInShutdown                    : 1;
	uint32    m_bDeferredDecals                : 1;
	uint32    m_bShadowsEnabled                : 1;
	uint32    m_bCloudShadowsEnabled           : 1;
#if defined(VOLUMETRIC_FOG_SHADOWS)
	uint32    m_bVolFogShadowsEnabled          : 1;
	uint32    m_bVolFogCloudShadowsEnabled     : 1;
#endif
	uint32    m_bVolumetricFogEnabled          : 1;
	uint32    m_bVolumetricCloudsEnabled       : 1;
	uint32    m_bDeferredRainEnabled           : 1;
	uint32    m_bDeferredRainOcclusionEnabled  : 1;
	uint32    m_bDeferredSnowEnabled           : 1;
	uint32    m_UseZPass                       : 2;

	uint8     m_nDisableTemporalEffects;
	uint32    m_nGPULimited;           // How many frames we are GPU limited
	int8      m_nCurMinAniso;
	int8      m_nCurMaxAniso;
	float     m_fCurMipLodBias;

	uint32    m_nShadowPoolHeight;
	uint32    m_nShadowPoolWidth;

	ColorF    m_CurFontColor;

	DWORD     m_Features;
	int       m_MaxTextureSize;
	size_t    m_MaxTextureMemory;
	int       m_nShadowTexSize;

	float     m_fLastGamma;
	float     m_fLastBrightness;
	float     m_fLastContrast;
	float     m_fDeltaGamma;

	float     m_fogCullDistance;

	enum { nMeshPoolMaxTimeoutCounter = 150 /*150 ms*/};
	int m_nMeshPoolTimeoutCounter;

	// Cached verts/inds used for sprites
	SVF_P3F_C4B_T2F* m_pSpriteVerts;
	uint16*          m_pSpriteInds;

	// Custom render modes states
	uint32 m_nThermalVisionMode : 2;
	uint32 m_nSonarVisionMode   : 2;
	uint32 m_nNightVisionMode   : 2;

	int    m_nFlushAllPendingTextureStreamingJobs;
	float  m_fTexturesStreamingGlobalMipFactor;

	SGpuInfo m_adapterInfo = {};
public:
	// these ids can be used for triple (or more) buffered structures
	// they are incremented in RenderWorld on the mainthread
	// use m_nPoolIndex from the mainthread (or jobs which are synced before Renderworld)
	// and m_nPoolIndexRT from the renderthread
	// right now the skinning data pool and particle are using this id
	uint32  m_nPoolIndex = 0;

	bool    m_bVendorLibInitialized;

	uint32  m_nFrameLoad;
	uint32  m_nFrameReset;
	uint32  m_nFrameSwapID;             // without recursive calls, access through GetFrameID(false)

	ColorF  m_cClearColor;
	int     m_NumResourceSlots;
	int     m_NumSamplerSlots;

	////////////////////////////////////////////////////////
	// downscaling viewport information.

	// Set from CrySystem via IRenderer interface
	Vec2 m_ReqViewportScale;

	// Updated in RT_EndFrame. Fixed across the whole frame.
	Vec2 m_CurViewportScale;
	Vec2 m_PrevViewportScale;

	////////////////////////////////////////////////////////

	class CPostEffectsMgr* m_pPostProcessMgr;
	class CWater*          m_pWaterSimMgr;

	CTextureManager*       m_pTextureManager;

	// Used for pausing timer related stuff (eg: for texture animations, and shader 'time' parameter)
	bool                   m_bPauseTimer;
	float                  m_fPrevTime;
	uint8                  m_nUseZpass : 2;
	bool                   m_bCollectDrawCallsInfo;
	bool                   m_bCollectDrawCallsInfoPerNode;

	S3DEngineCommon        m_p3DEngineCommon[RT_COMMAND_BUF_COUNT];

	//Debug Gun
	IRenderNode*     m_pDebugRenderNode;

	const SWindGrid* m_pCurWindGrid;

	_smart_ptr<IMaterial> m_pDefaultMaterial;
	_smart_ptr<IMaterial> m_pTerrainDefaultMaterial;

	int                   m_TexGenID;

	uint32_t              m_uniquePipelineCounter = 0;

	IFFont*               m_pDefaultFont;

	static int            m_iGeomInstancingThreshold; // internal value, auto mapped depending on GPU hardware, 0 means not set yet

	// Limit for local sorting array
	static const int      nMaxParticleContainer = 8 * 1024;

	JobManager::SJobState m_ComputeVerticesJobState;


	FILE*                 m_LogFile;
	FILE*                 m_LogFileStr;
	FILE*                 m_LogFileSh;

protected:
	//================================================================================
	int                                        m_cbpp, m_zbpp, m_sbpp;
	int                                        m_wireframe_mode, m_wireframe_mode_prev;
	uint32                                     m_nGPUs;                      // Use GetActiveGPUCount() to read
	float                                      m_drawNearFov;
	float                                      m_pixelAspectRatio;
	float                                      m_shadowJittering;
	StaticArray<int, MAX_GSM_LODS_NUM>         m_CachedShadowsResolution;

	std::array<std::vector<SSkinningData*>, 3> m_computeSkinningData;
	compute_skinning::CStorage*                m_pComputeSkinningStorage;

	gpu_pfx2::IManager*                        m_pGpuParticleManager;

	int                                        m_cloudShadowTexId;
	Vec3                                       m_cloudShadowSpeed;
	float                                      m_cloudShadowTiling;
	bool                                       m_cloudShadowInvert;
	float                                      m_cloudShadowBrightness;
	int                                        m_volumetricCloudTexId;
	int                                        m_volumetricCloudNoiseTexId;
	int                                        m_volumetricCloudEdgeNoiseTexId;

	// Shaders/Shaders support
	// RE - RenderElement
	bool m_bTimeProfileUpdated;
	int  m_PrevProfiler;
	int  m_nCurSlotProfiler;

	int  m_beginFrameCount;

	typedef std::list<IRendererEventListener*> TListRendererEventListeners;
	TListRendererEventListeners               m_listRendererEventListeners;

	std::vector<ISyncMainWithRenderListener*> m_syncMainWithRenderListeners;

#if defined(DO_RENDERSTATS)
	std::map<struct IRenderNode*, IRenderer::SDrawCallCountInfo> m_drawCallInfoPerNode;
	std::map<struct IRenderMesh*, IRenderer::SDrawCallCountInfo> m_drawCallInfoPerMesh;
#endif

	CryMutex             m_mtxStopAtRenderFrameEnd;
	CryConditionVariable m_condStopAtRenderFrameEnd;

	ColorF               m_highlightColor;
	ColorF               m_SelectionColor;
	Vec4                 m_highlightParams;

	SElementPool<CRenderView> m_pRenderViewPool[IRenderView::eViewType_Count];
	void InitRenderViewPool();

	// Temporary render objects storage
	struct STempObjects
	{
		std::shared_ptr<class CRenderObjectsPools> m_renderObjectsPools;
		// Array of render objects that need to be deleted next frame
		CryMT::CThreadSafePushContainer<class CPermanentRenderObject*> m_persistentRenderObjectsToDelete[RT_COMMAND_BUF_COUNT];
	};
	STempObjects m_tempRenderObjects;

	// Resource deletion is delayed for at least 3 frames.
	CryMT::CThreadSafePushContainer<CBaseResource*> m_resourcesToDelete[RT_COMMAND_BUF_COUNT];
	volatile int m_currentResourceDeleteBuffer = 0;

	// rounds ID from 3D engine, useful for texture streaming
	int m_streamZonesRoundId[MAX_PREDICTION_ZONES];

	int m_nRenderThreadFrameID = 0;

	struct SWaterUpdateInfo
	{
		float m_fLastWaterFOVUpdate;
		Vec3  m_LastWaterViewdirUpdate;
		Vec3  m_LastWaterUpdirUpdate;
		Vec3  m_LastWaterPosUpdate;
		float m_fLastWaterUpdate;
		int   m_nLastWaterFrameID;
	};
	SWaterUpdateInfo m_waterUpdateInfo;

	// Antialiasing data.
	SMSAA m_MSAAData;

	// Render frame statistics
	SRenderStatistics m_frameRenderStats[RT_COMMAND_BUF_COUNT];

	// Render target statistics
	std::vector<SRTargetStat> m_renderTargetStats;

	// Rendering Quality
	SRenderQuality m_renderQuality;

	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	// Animation time is used for rendering animation effects and can be paused if CRenderer::m_bPauseTimer is true
	CTimeValue m_animationTime;
	// Time of the last main to renderer thread sync
	CTimeValue m_frameSyncTime;
	//////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////////
	// Render-context management
	/////////////////////////////////////////////////////////////////////////////////
	std::map<SDisplayContextKey, std::shared_ptr<CRenderDisplayContext>> m_displayContexts;

	uint32                                                m_uniqueDisplayContextId = 0;
	std::shared_ptr<CRenderDisplayContext>                m_pActiveContext;
	SDisplayContextKey                                    m_activeContextKey;
	std::shared_ptr<CSwapChainBackedRenderDisplayContext> m_pBaseDisplayContext;

	/////////////////////////////////////////////////////////////////////////////////
	// Render-pipeline management
	/////////////////////////////////////////////////////////////////////////////////
	std::shared_ptr<CGraphicsPipeline> m_pBaseGraphicsPipeline;
	std::shared_ptr<CGraphicsPipeline> m_pActiveGraphicsPipeline;
	std::map<SGraphicsPipelineKey, std::shared_ptr<CGraphicsPipeline>> m_graphicsPipelines;

	std::vector<CRenderView*> mRenderViewList;

public: // TEMPORARY PUBLIC
	friend struct SRenderThread;
	//////////////////////////////////////////////////////////////////////////
	// Render Thread support
	threadID m_nFillThreadID;
	threadID m_nProcessThreadID;
	//////////////////////////////////////////////////////////////////////////

};

inline int32 CRenderer::RT_GetCurrGpuID() const
{
	return 0;
}

inline int CRenderer::GetRenderFrameID() const
{
	return 0;
}

inline int CRenderer::GetMainFrameID() const
{
	return 0;
}

#define SKY_BOX_SIZE 32.f
