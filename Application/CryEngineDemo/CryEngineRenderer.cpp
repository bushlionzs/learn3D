// Copyright 2004-2021 Crytek GmbH / Crytek Group. All rights reserved.

#include "StdAfx.h"

#include <CryCore/CryCustomTypes.h>
#include <Cry3DEngine/IStatObj.h>
#include <Cry3DEngine/I3DEngine.h>
#include <CryMovie/IMovieSystem.h>
#include <Cry3DEngine/IIndexedMesh.h>
#include <CryCore/BitFiddling.h>                              // IntegerLog2()
#include <Cry3DEngine/ImageExtensionHelper.h>                 // CImageExtensionHelper
#include <CryFont/IFont.h>
#include <CryRenderer/RenderObject.h>
#include <Cry3DEngine/IGeomCache.h>
#include <Cry3DEngine/ITimeOfDay.h>
#include <CryRenderer/IRenderMesh.h>
#include <CryThreading/IJobManager_JobDelegator.h>
#include <CryThreading/IThreadManager.h>
#include <CryEngineRenderer.h>
#include <CryEngineMesh.h>
#include <CryEngineRenderView.h>
#include <CryEngineShader.h>

#define PROCESS_TEXTURES_IN_PARALLEL

#if CRY_PLATFORM_LINUX || CRY_PLATFORM_ANDROID
	#include <CrySystem/ILog.h>
#endif
#include <CryRenderer/IShader.h>
#include <OgreHeader.h>
#include <shaderManager.h>


namespace
{
	class CConditonalLock
	{
		CryCriticalSection& _lock;
		bool _bActive;
	public:
		CConditonalLock(CryCriticalSection& lock, bool bActive)
			: _lock(lock), _bActive(bActive)
		{ if (_bActive) _lock.Lock(); }
		~CConditonalLock()
		{ if (_bActive) _lock.Unlock(); }
	};
}

#if defined(DX11_ALLOW_D3D_DEBUG_RUNTIME)
string D3DDebug_GetLastMessage();
#endif

// Enum -> Bitmask lookup table
uint32 ColorMasks[(GS_NOCOLMASK_COUNT >> GS_COLMASK_SHIFT)][4] =
{
	{ 0x0, 0x0, 0x0, 0x0 }, // GS_NOCOLMASK_NONE
	{ 0x1, 0x1, 0x1, 0x1 }, // GS_NOCOLMASK_R
	{ 0x2, 0x2, 0x2, 0x2 }, // GS_NOCOLMASK_G
	{ 0x4, 0x4, 0x4, 0x4 }, // GS_NOCOLMASK_B
	{ 0x8, 0x8, 0x8, 0x8 }, // GS_NOCOLMASK_A
	{ 0xE, 0xE, 0xE, 0xE }, // GS_NOCOLMASK__GBA
	{ 0xD, 0xD, 0xD, 0xD }, // GS_NOCOLMASK_R_BA
	{ 0xB, 0xB, 0xB, 0xB }, // GS_NOCOLMASK_RG_A
	{ 0x7, 0x7, 0x7, 0x7 }, // GS_NOCOLMASK_RGB_
	{ 0xF, 0xF, 0xF, 0xF }, // GS_NOCOLMASK_RGBA
	{ 0x8, 0x8, 0xC, 0x8 }, // GS_NOCOLMASK_GBUFFER_OVERLAY
};

// Bitmask -> Enum lookup table
std::array<uint32, (GS_NOCOLMASK_COUNT >> GS_COLMASK_SHIFT)> AvailableColorMasks =
{
	{
		0x0, // GS_NOCOLMASK_NONE
		0x1, // GS_NOCOLMASK_R
		0x2, // GS_NOCOLMASK_G
		0x4, // GS_NOCOLMASK_B
		0x8, // GS_NOCOLMASK_A
		0xE, // GS_NOCOLMASK__GBA
		0xD, // GS_NOCOLMASK_R_BA
		0xB, // GS_NOCOLMASK_RG_A
		0x7, // GS_NOCOLMASK_RGB_
		0xF, // GS_NOCOLMASK_RGBA
		0xC  // GS_NOCOLMASK_GBUFFER_OVERLAY
	}
};


#define RENDERER_DEFAULT_FONT "Fonts/default.xml"


// per-frame profilers: collect the information for each frame for
// displaying statistics at the beginning of each frame
//#define PROFILER(ID,NAME) DEFINE_FRAME_PROFILER(ID,NAME)
//#include "FrameProfilers-list.h"
//#undef PROFILER

CRenderer::CRenderer()
	: m_bStopRendererAtFrameEnd(false)
	, m_bEditor(false)
	, m_beginFrameCount(0)
{
	InitRenderViewPool();
	mTextures.resize(mTextureMaxId);
	for (auto& tex : mTextures)
	{
		tex = nullptr;
	}

	mRenderViewList.resize(IRenderView::eViewType_Count);
	for (auto& obj : mRenderViewList)
	{
		obj = nullptr;
	}
}

void CRenderer::InitRenderer()
{
	m_pIntroMovieRenderer = 0;

	m_bShaderCacheGen      = false;
	m_bSystemResourcesInit = 0;

	m_bSystemTargetsInit = 0;

	m_bShadowsEnabled      = true;
	m_bCloudShadowsEnabled = true;

#if defined(VOLUMETRIC_FOG_SHADOWS)
	m_bVolFogShadowsEnabled      = false;
	m_bVolFogCloudShadowsEnabled = false;
#endif
	m_bVolumetricFogEnabled = false;
	m_bVolumetricCloudsEnabled = false;
	m_bDeferredRainEnabled = false;
	m_bDeferredRainOcclusionEnabled = false;
	m_bDeferredSnowEnabled = false;

	m_bAllowTerrainLayerBlending = 0;
	m_nDisableTemporalEffects = 0;

	m_ReqViewportScale = m_CurViewportScale = m_PrevViewportScale = Vec2(1, 1);

	m_nCurMinAniso        = 1;
	m_nCurMaxAniso        = 16;
	m_fCurMipLodBias      = 0.0f;
	m_wireframe_mode      = R_SOLID_MODE;
	m_wireframe_mode_prev = R_SOLID_MODE;

	m_pSpriteVerts = NULL;
	m_pSpriteInds  = NULL;


	m_nGPU = 1;

	m_cClearColor  = ColorF(0, 0, 0, 128.0f / 255.0f); // 128 is default GBuffer value
	m_LogFile      = NULL;
	m_pDefaultFont = NULL;
	m_TexGenID     = 1;

#if defined(SUPPORT_DEVICE_INFO_USER_DISPLAY_OVERRIDES)
	m_overrideRefreshRate   = CV_r_overrideRefreshRate;
	m_overrideScanlineOrder = CV_r_overrideScanlineOrder;
#endif
	m_Features              = 0;
	m_bVendorLibInitialized = false;

	//init_math();

	m_bPauseTimer = 0;
	m_fPrevTime   = -1.0f;

	//  m_RP.m_ShaderCurrTime = 0.0f;

	m_CurFontColor = Col_White;



	m_bSwapBuffers = true;


	m_nShadowPoolHeight = m_nShadowPoolWidth = 0;

	m_cloudShadowTexId      = 0;
	m_cloudShadowSpeed      = Vec3(0, 0, 0);
	m_cloudShadowTiling     = 1;
	m_cloudShadowInvert     = false;
	m_cloudShadowBrightness = 1;

	m_volumetricCloudTexId = 0;
	m_volumetricCloudNoiseTexId = 0;
	m_volumetricCloudEdgeNoiseTexId = 0;

	m_nGPUs = 1;

	//assert(!(FOB_MASK_AFFECTS_MERGING & 0xffff));
	//assert(sizeof(CRenderObject) == 256);
	STATIC_CHECK(!(FOB_MASK_AFFECTS_MERGING & 0xffff), FOB_MASK_AFFECTS_MERGING);


	//m_RP.m_VertPosCache.m_nBufSize = 500000 * sizeof(Vec3);
	//m_RP.m_VertPosCache.m_pBuf = new byte [gRenDev->m_RP.m_VertPosCache.m_nBufSize];

	m_pDefaultMaterial        = NULL;
	m_pTerrainDefaultMaterial = NULL;

	m_IdentityMatrix.SetIdentity();

	m_nFlushAllPendingTextureStreamingJobs = 0;
	m_fTexturesStreamingGlobalMipFactor    = 0.f;

	m_fogCullDistance = 0.0f;

	m_pDebugRenderNode = NULL;

	m_bCollectDrawCallsInfo        = false;
	m_bCollectDrawCallsInfoPerNode = false;

	m_nMeshPoolTimeoutCounter = nMeshPoolMaxTimeoutCounter;

	ZeroArray(m_streamZonesRoundId);

}

CRenderer::~CRenderer()
{
	//Code now moved to Release()
}

//////////////////////////////////////////////////////////////////////////
void CRenderer::PostInit()
{
	CRY_PROFILE_FUNCTION(PROFILE_LOADING_ONLY);


	//////////////////////////////////////////////////////////////////////////
	// Load internal renderer font.
	//////////////////////////////////////////////////////////////////////////
	if (gEnv->pCryFont)
	{
		m_pDefaultFont = gEnv->pCryFont->GetFont("default");
		if (!m_pDefaultFont)
			CryWarning(VALIDATOR_MODULE_SYSTEM, VALIDATOR_ERROR, "Error getting default font");
	}

	// load all default textures
	if (!m_bShaderCacheGen && m_pTextureManager)
	{
		if (ISystemUserCallback* pUserCallback = gEnv->pSystem->GetUserCallback())
		{
			pUserCallback->OnInitProgress("Preloading default textures...");
		}
	}

	if (!m_bShaderCacheGen)
	{
		ICVar* pIntroMoviesDuringInit = gEnv->pConsole->GetCVar("sys_intromoviesduringinit");
		bool   bIntroMoviesDuringInit = pIntroMoviesDuringInit ? pIntroMoviesDuringInit->GetIVal() != 0 : false;

		// Create system resources while in fast load phase
		if (bIntroMoviesDuringInit == false)    // don't create resources here when we have a movies during init, else we get concurrent device context access
		{
			if (ISystemUserCallback* pUserCallback = gEnv->pSystem->GetUserCallback())
			{
				pUserCallback->OnInitProgress("Compiling default renderer resources...");
			}

			gEnv->pRenderer->InitSystemResources(FRR_SYSTEM_RESOURCES);
		}
	}
}

//////////////////////////////////////////////////////////////////////////

#define INTRO_MOVIES_PAK "_fastload/IntroMovies.pak"
#define USE_INTRO_MOVIES 1               // Change this if your title uses this pak, otherwise "normal" Movies.pak is assumed

void CRenderer::StartRenderIntroMovies()
{
	CRY_PROFILE_FUNCTION(PROFILE_LOADING_ONLY);
	MEMSTAT_CONTEXT(EMemStatContextType::Other, "Staer Render Intro Movie");
	assert(m_pIntroMovieRenderer == 0);

#if USE_INTRO_MOVIES
	// Make sure intro pak is valid and excistion else don't bother rendering them
	if (!gEnv->pCryPak->OpenPack(PathUtil::GetGameFolder(), INTRO_MOVIES_PAK,
	                             ICryPak::FLAGS_PAK_IN_MEMORY))
		return;

	gEnv->pCryPak->LoadPakToMemory(INTRO_MOVIES_PAK, ICryPak::eInMemoryPakLocale_GPU);
#endif

}

void CRenderer::StopRenderIntroMovies(bool bWaitForFinished)
{
	if (m_pIntroMovieRenderer == 0)
		return;


	StopLoadtimeFlashPlayback();
	SAFE_DELETE(m_pIntroMovieRenderer);
#if USE_INTRO_MOVIES
	// we don't need the intro movies in memory anymore
	gEnv->pCryPak->LoadPakToMemory(INTRO_MOVIES_PAK, ICryPak::eInMemoryPakLocale_Unload);
	gEnv->pCryPak->ClosePack(INTRO_MOVIES_PAK, 0);
#endif
}

bool CRenderer::IsRenderingIntroMovies() const
{
	return (m_pIntroMovieRenderer != NULL);
}

//////////////////////////////////////////////////////////////////////////

void CRenderer::Release()
{
	
}

//////////////////////////////////////////////////////////////////////
void CRenderer::AddListener(IRendererEventListener* pRendererEventListener)
{
	stl::push_back_unique(m_listRendererEventListeners, pRendererEventListener);
}

//////////////////////////////////////////////////////////////////////
void CRenderer::RemoveListener(IRendererEventListener* pRendererEventListener)
{
	stl::find_and_erase(m_listRendererEventListeners, pRendererEventListener);
}

int CRenderer::GetFrameID(bool bIncludeRecursiveCalls /*=true*/)
{
	return gEnv->nMainFrameID;
}

//////////////////////////////////////////////////////////////////////////
void CRenderer::OnEntityDeleted(IRenderNode* pRenderNode)
{
	
}

#pragma pack (push)
#pragma pack (1)
typedef struct
{
	unsigned char  id_length, colormap_type, image_type;
	unsigned short colormap_index, colormap_length;
	unsigned char  colormap_size;
	unsigned short x_origin, y_origin, width, height;
	unsigned char  pixel_size, attributes;
} __PACKED TargaHeader_t;
#pragma pack (pop)

//////////////////////////////////////////////////////////////////////////
bool CRenderer::SaveTga(unsigned char* sourcedata, int sourceformat, int w, int h, const char* filename, bool flip) const
{
	//assert(0);
	//  return CImage::SaveTga(sourcedata,sourceformat,w,h,filename,flip);

	if (flip)
	{
		int size             = w * (sourceformat / 8);
		unsigned char* tempw = new unsigned char[size];
		unsigned char* src1  = sourcedata;
		unsigned char* src2  = sourcedata + (w * (sourceformat / 8)) * (h - 1);
		for (int k = 0; k < h / 2; k++)
		{
			memcpy(tempw, src1, size);
			memcpy(src1, src2, size);
			memcpy(src2, tempw, size);
			src1 += size;
			src2 -= size;
		}
		delete[] tempw;
	}

	unsigned char* oldsourcedata = sourcedata;

	if (sourceformat == FORMAT_8_BIT)
	{

		unsigned char* desttemp = new unsigned char[w * h * 3];
		memset(desttemp, 0, w * h * 3);

		unsigned char* destptr = desttemp;
		unsigned char* srcptr  = sourcedata;

		unsigned char col;

		for (int k = 0; k < w * h; k++)
		{
			col        = *srcptr++;
			*destptr++ = col;
			*destptr++ = col;
			*destptr++ = col;
		}

		sourcedata = desttemp;

		sourceformat = FORMAT_24_BIT;
	}

	TargaHeader_t header;

	memset(&header, 0, sizeof(header));
	header.image_type = 2;
	header.width      = w;
	header.height     = h;
	header.pixel_size = sourceformat;

	unsigned char* data   = new unsigned char[w * h * (sourceformat >> 3)];
	unsigned char* dest   = data;
	unsigned char* source = sourcedata;

	//memcpy(dest,source,w*h*(sourceformat>>3));

	for (int ax = 0; ax < h; ax++)
	{
		for (int by = 0; by < w; by++)
		{
			unsigned char r, g, b, a;
			r = *source;
			source++;
			g = *source;
			source++;
			b = *source;
			source++;
			if (sourceformat == FORMAT_32_BIT)
			{
				a = *source;
				source++;
			}
			*dest = b;
			dest++;
			*dest = g;
			dest++;
			*dest = r;
			dest++;
			if (sourceformat == FORMAT_32_BIT)
			{
				*dest = a;
				dest++;
			}
		}
	}

	FILE* f = fxopen(filename, "wb");
	if (!f)
	{
		//("Cannot save %s\n",filename);
		delete[] data;
		return (false);
	}

	if (!fwrite(&header, sizeof(header), 1, f))
	{
		//CLog::LogToFile("Cannot save %s\n",filename);
		delete[] data;
		fclose(f);
		return (false);
	}

	if (!fwrite(data, w * h * (sourceformat >> 3), 1, f))
	{
		//CLog::LogToFile("Cannot save %s\n",filename);
		delete[] data;
		fclose(f);
		return (false);
	}

	fclose(f);

	delete[] data;
	if (sourcedata != oldsourcedata)
		delete[] sourcedata;

	return (true);
}

int32_t CRenderer::allocTextureId()
{
	if (mTextureAllocId == mTextureMaxId)
	{
		assert_invariant(false);
		return 0;
	}

	return ++mTextureAllocId;
}

Ogre::PixelFormat translateTextureFormat(ETEX_Format eTFSrc)
{
	switch (eTFSrc)
	{
	case eTF_BC3:
		return Ogre::PixelFormat::PFG_BC3_UNORM;
	case eTF_R32F:
		return Ogre::PixelFormat::PF_FLOAT32_R;
	default:
		assert_invariant(false);
	}
	return  Ogre::PixelFormat::PF_UNKNOWN;
}

unsigned int CRenderer::UploadToVideoMemory(
	unsigned char* data, int w, int h, ETEX_Format eTFSrc, ETEX_Format eTFDst, 
	int8 nummipmap, bool repeat, int filter, int id, 
	const char* szCacheName, int flags, EEndian eEndian, 
	RectI* pRegion, bool bAsynDevTexCreation)
{
	assert_invariant(eTFSrc == eTFDst);

	Ogre::PixelFormat ogreFormat = translateTextureFormat(eTFDst);

	Ogre::TextureProperty texProperty;
	texProperty._width = w;
	texProperty._height = h;
	texProperty._tex_format = ogreFormat;
	texProperty._tex_usage = Ogre::TextureUsage::WRITEABLE;
	if (repeat)
	{
		texProperty._samplerParams.wrapS = filament::backend::SamplerWrapMode::REPEAT;
		texProperty._samplerParams.wrapT = filament::backend::SamplerWrapMode::REPEAT;
		texProperty._samplerParams.wrapR = filament::backend::SamplerWrapMode::REPEAT;
	}
	else
	{
		texProperty._samplerParams.wrapS = filament::backend::SamplerWrapMode::CLAMP_TO_EDGE;
		texProperty._samplerParams.wrapT = filament::backend::SamplerWrapMode::CLAMP_TO_EDGE;
		texProperty._samplerParams.wrapR = filament::backend::SamplerWrapMode::CLAMP_TO_EDGE;
	}
	if (id == 0)
	{
		id = allocTextureId();
		if (id == 0)
		{
			return 0;
		}

		RenderSystem* rs = Ogre::Root::getSingleton().getRenderSystem();
		Ogre::OgreTexture* tex = rs->createManualTexture(szCacheName, &texProperty);

		mTextures[id] = tex;
	}
	
	if (data)
	{
		Ogre::OgreTexture* tex = mTextures[id];

		uint32_t size = Ogre::PixelUtil::getMemorySize(w, h, 1, ogreFormat);
		tex->uploadTextureData((const char*)data, size, texProperty);
	}
	
	return id;
}

unsigned int CRenderer::UploadToVideoMemory3D(
	unsigned char* data, int w, int h, int d, ETEX_Format eTFSrc, ETEX_Format eTFDst, 
	int8 nummipmap, bool repeat, int filter, int Id, 
	const char* szCacheName, int flags, EEndian eEndian, 
	RectI* pRegion, bool bAsynDevTexCreation)
{
	assert(false);
	return 0;
}

unsigned int CRenderer::UploadToVideoMemoryCube(
	unsigned char* data, int w, int h, ETEX_Format eTFSrc, ETEX_Format eTFDst, 
	int8 nummipmap, bool repeat, int filter, int Id, const char* szCacheName, 
	int flags, EEndian eEndian, RectI* pRegion, bool bAsynDevTexCreation)
{
	assert(false);
	return 0;
}

void CRenderer::UpdateTextureInVideoMemory(
	uint32 tnum, unsigned char* newdata, int posx, int posy, int w, int h, 
	ETEX_Format eTFSrc, int posz, int sizez)
{
	assert(false);
}

//================================================================
SInputShaderResources* CRenderer::EF_CreateInputShaderResource(IRenderShaderResources* pOptionalCopyFrom)
{
	if (pOptionalCopyFrom)
		return new SInputShaderResources(pOptionalCopyFrom);
	return new SInputShaderResources;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//#include "../Common/Character/CryModel.h"

#if CRY_PLATFORM_DURANGO
void CRenderer::SuspendDevice()
{
	m_pRT->RC_SuspendDevice();
}
void CRenderer::ResumeDevice()
{
	m_pRT->RC_ResumeDevice();
}
#endif



CRenderView* CRenderer::GetOrCreateRenderView(IRenderView::EViewType Type)
{
	if (mRenderViewList[Type] == nullptr)
	{
		mRenderViewList[Type] = new CRenderView("", Type);
	}
	return mRenderViewList[Type];
}

void CRenderer::ReturnRenderView(CRenderView* pRenderView)
{
	pRenderView->Clear();
}

void CRenderer::DeleteRenderViews()
{

}

//////////////////////////////////////////////////////////////////////////

static CryCriticalSection gs_contextLock;



std::shared_ptr<CGraphicsPipeline> CRenderer::FindGraphicsPipeline(const SGraphicsPipelineKey& key)  const
{
	return nullptr;
}

void CRenderer::ResetActiveGraphicsPipeline()
{
	m_pActiveGraphicsPipeline = nullptr;
}

std::shared_ptr<CGraphicsPipeline> CRenderer::SetCurrentGraphicsPipeline(const SGraphicsPipelineKey& key)
{
	m_pActiveGraphicsPipeline = FindGraphicsPipeline(key);
	return m_pActiveGraphicsPipeline;
}



SGraphicsPipelineKey CRenderer::CreateGraphicsPipeline(const SGraphicsPipelineDescription& desc)
{
	SGraphicsPipelineKey key;
	return key;
}

SGraphicsPipelineKey CRenderer::RT_CreateGraphicsPipeline(const SGraphicsPipelineDescription& desc)
{
	SGraphicsPipelineKey key;
	return key;
}

void CRenderer::ResizePipelineAndContext(const SGraphicsPipelineKey& graphicsPipelineKey, const SDisplayContextKey& displayContextKey, int width, int height)
{
	ResizeContext(displayContextKey, width, height);
	ResizeGraphicsPipeline(graphicsPipelineKey, width, height);
}

void CRenderer::ResizeGraphicsPipeline(const SGraphicsPipelineKey& key, int width, int height)
{
	std::shared_ptr<CGraphicsPipeline> pGP = FindGraphicsPipeline(key);
	if (pGP)
		ResizeGraphicsPipeline(pGP, width, height);
}

void CRenderer::ResizeGraphicsPipeline(std::shared_ptr<CGraphicsPipeline> graphicsPipeline, int width, int height)
{
	
}

bool CRenderer::RT_DeleteGraphicsPipeline(const SGraphicsPipelineKey& key)
{
	auto it = m_graphicsPipelines.find(key);
	if (it == m_graphicsPipelines.end())
		return false;

	auto deletedPipeline = std::move(it->second);
	m_graphicsPipelines.erase(it);

	return true;
}

bool CRenderer::DeleteGraphicsPipeline(const SGraphicsPipelineKey& key)
{
	return true;
}

void CRenderer::SetActiveContext(const std::shared_ptr<CRenderDisplayContext>& ctx, const SDisplayContextKey& key)
{
	m_pActiveContext = ctx;
	m_activeContextKey = key;
}


const std::shared_ptr<CGraphicsPipeline>& CRenderer::GetActiveGraphicsPipeline() const
{
	return m_pActiveGraphicsPipeline;
}



#ifdef CRY_PLATFORM_WINDOWS
RectI CRenderer::GetDefaultContextWindowCoordinates()
{
	return RectI
				 { 0, 0, 0, 0};
}
#endif

bool CRenderer::IsCurrentContextMainVP()
{
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void CRenderer::InitSystemResources(int nFlags)
{
	CRY_PROFILE_FUNCTION(PROFILE_LOADING_ONLY);
	MEMSTAT_CONTEXT(EMemStatContextType::Other, "Init System Resources");

	if (!m_bSystemResourcesInit)
	{
		

		m_bSystemResourcesInit = 1;
	}
}

void CRenderer::FreeSystemResources(int nFlags)
{
	
}

////////////////////////////////////////////////////////////////////////////////////////////////////

Vec2 CRenderer::SetViewportDownscale(float xscale, float yscale)
{
	assert(false);
	return Vec2(0, 0);
}

EScreenAspectRatio CRenderer::GetScreenAspect(int nWidth, int nHeight)
{
	EScreenAspectRatio eSA = eAspect_Unknown;

	float fNeed16_9  = 16.0f / 9.0f;
	float fNeed16_10 = 16.0f / 10.0f;
	float fNeed4_3   = 4.0f / 3.0f;

	float fCur = (float)nWidth / (float)nHeight;
	if (fabs(fCur - fNeed16_9) < 0.1f)
		eSA = eAspect_16_9;

	if (fabs(fCur - fNeed4_3) < 0.1f)
		eSA = eAspect_4_3;

	if (fabs(fCur - fNeed16_10) < 0.1f)
		eSA = eAspect_16_10;

	return eSA;
}

bool CRenderer::WriteTGA(const byte* dat, int wdt, int hgt, const char* name, int src_bits_per_pixel, int dest_bits_per_pixel)
{
	return true;
}

bool CRenderer::WriteDDS(const byte* dat, int wdt, int hgt, int Size, const char* nam, ETEX_Format eFDst, int NumMips)
{
	return true;
}

void CRenderer::EF_SetShaderMissCallback(ShaderCacheMissCallback callback)
{
	
}

const char* CRenderer::EF_GetShaderMissLogPath()
{
	return nullptr;
}

string* CRenderer::EF_GetShaderNames(int& nNumShaders)
{
	return nullptr;
}

IShader* CRenderer::EF_LoadShader(const char* name, int flags, uint64 nMaskGen)
{
	RenderShader* shader = new RenderShader(name);
	return shader;
}

void CRenderer::EF_SetShaderQuality(EShaderType eST, EShaderQuality eSQ)
{
	
}

uint64 CRenderer::EF_GetRemapedShaderMaskGen(const char* name, uint64 nMaskGen, bool bFixup)
{
	assert(false);
	return 0;
}

uint64 CRenderer::EF_GetShaderGlobalMaskGenFromString(const char* szShaderName, const char* szShaderGen, uint64 nMaskGen)
{
	return 0;
}

// inverse of EF_GetShaderMaskGenFromString
const char* CRenderer::EF_GetStringFromShaderGlobalMaskGen(const char* szShaderName, uint64 nMaskGen)
{
	return "\0";
}



SShaderItem CRenderer::EF_LoadShaderItem(const char* szName, bool bShare, int flags, SInputShaderResources* Res, uint64 nMaskGen, const SLoadShaderItemArgs* pArgs)
{
	SShaderItem item;

	auto shaderResources = new RenderShaderResources;
	item.m_pShaderResources = shaderResources;
	item.m_pShaderResources->SetShaderParams(Res, nullptr);
	item.m_pShader = new RenderShader(szName);
	auto diffuse = Res->m_LMaterial.m_Diffuse;
	shaderResources->setDiffuse(diffuse);

	item.m_nPreprocessFlags = FB_GENERAL;
    auto* zPrePass = 
		Ogre::ShaderManager::getSingleton().getShader(szName, EngineType_Dx12, "ZPrePass");

	if (zPrePass)
	{
		item.m_nPreprocessFlags |= FB_ZPREPASS;
	}

	return item;
}

//////////////////////////////////////////////////////////////////////////
bool CRenderer::EF_ReloadFile_Request(const char* szFileName)
{
	assert(false);
	return true;
}

bool CRenderer::EF_ReloadFile(const char* szFileName)
{
	assert(false);
	return true;
}

void CRenderer::EF_ReloadShaderFiles(int nCategory)
{
	//gRenDev->m_cEF.mfLoadFromFiles(nCategory);
}

void CRenderer::EF_ReloadTextures()
{
}

void CRenderer::EF_RefreshTextures()
{
	
}

DynArray<uint16_t> CRenderer::EF_RenderEnvironmentCubeHDR(int size, const Vec3& Pos)
{
	return DynArray<uint16_t>();
}

bool CRenderer::WriteTIFToDisk(const void* pData, int width, int height, int bytesPerChannel, int numChannels, bool bFloat, const char* szPreset, const char* szFileName)
{
	return true;
}

int CRenderer::EF_LoadLightmap(const char* name)
{
	return 0;
}

ITexture* CRenderer::EF_GetTextureByID(int Id)
{
	return NULL;
}

ITexture* CRenderer::EF_GetTextureByName(const char* nameTex, uint32 flags)
{
	return NULL;
}

ITexture* CRenderer::EF_LoadTexture(const char* szName, const uint32 flags)
{
	return NULL;
}

IDynTextureSource* CRenderer::EF_LoadDynTexture(const char* dynsourceName, bool sharedRT)
{
	return nullptr;
}

bool SShaderItem::Update()
{
	return true;
}

bool SShaderItem::RefreshResourceConstants()
{
	return true;
}

void CRenderer::EF_StartEf(const SRenderingPassInfo& passInfo)
{
	
}

void CRenderer::EF_SubmitWind(const SWindGrid* pWind)
{
	
}

CRenderElement* CRenderer::EF_CreateRE(EDataType edt)
{
	return nullptr;
}

float CRenderer::EF_GetWaterZElevation(float fX, float fY)
{
	I3DEngine* eng = (I3DEngine*)gEnv->p3DEngine;
	if (!eng)
		return 0;
	return eng->GetWaterLevel();
}

void CRenderer::Logv(const char* format, ...)
{
	va_list argptr;

	if (m_LogFile)
	{
		va_start(argptr, format);
		vfprintf(m_LogFile, format, argptr);
		va_end(argptr);
	}
}

void CRenderer::LogStrv(const char* format, ...)
{
	va_list argptr;

	if (m_LogFileStr)
	{
		va_start(argptr, format);
		vfprintf(m_LogFileStr, format, argptr);
		va_end(argptr);
	}
}

void CRenderer::LogShv(const char* format, ...)
{
	va_list argptr;

	if (m_LogFileSh)
	{
		va_start(argptr, format);
		vfprintf(m_LogFileSh, format, argptr);
		va_end(argptr);
		fflush(m_LogFileSh);
	}
}

void CRenderer::Log(const char* str)
{
	if (m_LogFile)
	{
		fprintf(m_LogFile, "%s", str);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

// Dynamic lights
bool CRenderer::EF_IsFakeDLight(const SRenderLight* Source) const
{
	return true;
}

void CRenderer::EF_CheckLightMaterial(SRenderLight* pLight, uint16 nRenderLightID, const SRenderingPassInfo& passInfo)
{

}

void CRenderer::EF_ADDDlight(SRenderLight* Source, const SRenderingPassInfo& passInfo)
{
}

int CRenderer::EF_AddDeferredLight(const SRenderLight& pLight, float fMult, const SRenderingPassInfo& passInfo)
{
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

bool CRenderer::EF_AddDeferredDecal(const SDeferredDecal& rDecal, const SRenderingPassInfo& passInfo)
{
	
	return false;
}

void CRenderer::ClearPerFrameData(const SRenderingPassInfo& passInfo)
{
}

inline Matrix44 ToLightMatrix(const Ang3& angle)
{
	Matrix33 ViewMatZ = Matrix33::CreateRotationZ(-angle.x);
	Matrix33 ViewMatX = Matrix33::CreateRotationX(-angle.y);
	Matrix33 ViewMatY = Matrix33::CreateRotationY(+angle.z);
	return Matrix44(ViewMatX * ViewMatY * ViewMatZ).GetTransposed();
}

bool CRenderer::EF_UpdateDLight(SRenderLight* dl) const
{
	
	return false;
}

EShaderQuality CRenderer::EF_GetShaderQuality(EShaderType eST)
{
	

	return eSQ_Low;
}


int CRenderer::CurThreadList()
{
	return 0;
}

namespace {
	// util funtion to write to the provided output memory
	template<typename T>
	void WriteQueryResult(void* pOutput, uint32 nOutputSize, const T& rQueryResult)
	{
#if !defined(_RELEASE)
		if (pOutput == NULL)
			CryFatalError("No Output Storage Specified");
		if (sizeof(T) != nOutputSize)
			CryFatalError("Insufficient storage for EF_Query Output");
#endif
		*alias_cast<T*>(pOutput) = rQueryResult;
	}

	// util function to read POD types from query parameters
	template<typename T>
	T ReadQueryParameter(void* pInput, uint32 nInputSize)
	{
#if !defined(_RELEASE)
		if (pInput == NULL)
			CryFatalError("No Input Storage Specified");
		if (sizeof(T) != nInputSize)
			CryFatalError("Insufficient storage for EF_Query Input");
#endif
		return *alias_cast<T*>(pInput);
	}
}

void CRenderer::EF_QueryImpl(ERenderQueryTypes eQuery, void* pInOut0, uint32 nInOutSize0, void* pInOut1, uint32 nInOutSize1)
{
	
}

#if CRY_PLATFORM_WINDOWS
#pragma warning( pop )              //AMD Port
#endif

void CRenderer::ForceGC()
{
	
}

//================================================================================================================

_smart_ptr<IRenderMesh> CRenderer::CreateRenderMesh(
	const char* szType, 
	const char* szSourceName, 
	IRenderMesh::SInitParamerers* pInitParams, 
	ERenderMeshType eBufType)
{
	if (strstr(szSourceName, "house2.cgf"))
	{
		int kk = 0;
	}
	if (pInitParams)
	{
		return CreateRenderMeshInitialized(pInitParams->pVertBuffer, pInitParams->nVertexCount, pInitParams->eVertexFormat, pInitParams->pIndices, pInitParams->nIndexCount, pInitParams->nPrimetiveType, szType, szSourceName,
			pInitParams->eType, pInitParams->nRenderChunkCount, pInitParams->nClientTextureBindID, 0, 0, pInitParams->bOnlyVideoBuffer, pInitParams->bPrecache, pInitParams->pTangents, pInitParams->bLockForThreadAccess, pInitParams->pNormals);
	}

	MEMSTAT_CONTEXT(EMemStatContextType::RenderMeshType, szType);
	MEMSTAT_CONTEXT(EMemStatContextType::RenderMesh, szSourceName);

	// make material table with clean elements
	_smart_ptr<CryEngineMesh> pRenderMesh = new CryEngineMesh(szType, szSourceName);
	pRenderMesh->_SetRenderMeshType(eBufType);

	return pRenderMesh.get();
}


inline ERenderPrimitiveType GetInternalPrimitiveType(PublicRenderPrimitiveType t)
{
	switch (t)
	{
	case prtTriangleList:
	default:
		return eptTriangleList;
	case prtTriangleStrip:
		return eptTriangleStrip;
	case prtLineList:
		return eptLineList;
	case prtLineStrip:
		return eptLineStrip;
	}
}
_smart_ptr<IRenderMesh> CRenderer::CreateRenderMeshInitialized(
	const void* pVertBuffer, int nVertCount, InputLayoutHandle eVF,
	const vtx_idx* pIndices, int nIndices,
	const PublicRenderPrimitiveType nPrimetiveType, const char* szType, const char* szSourceName, ERenderMeshType eBufType,
	int nMatInfoCount, int nClientTextureBindID,
	bool (*PrepareBufferCallback)(IRenderMesh*, bool),
	void* CustomData, bool bOnlyVideoBuffer, bool bPrecache,
	const SPipTangents* pTangents, bool bLockForThreadAcc, Vec3* pNormals)
{
	MEMSTAT_CONTEXT(EMemStatContextType::RenderMeshType, szType);
	MEMSTAT_CONTEXT(EMemStatContextType::RenderMesh, szSourceName);

	_smart_ptr<CryEngineMesh> pRenderMesh = new CryEngineMesh(szType, szSourceName, bLockForThreadAcc);
	pRenderMesh->_SetRenderMeshType(eBufType);
	pRenderMesh->LockForThreadAccess();

	// make mats info list
	pRenderMesh->m_Chunks.reserve(nMatInfoCount);

	pRenderMesh->_SetVertexFormat(eVF);
	pRenderMesh->_SetNumVerts(nVertCount);
	pRenderMesh->_SetNumInds(nIndices);

	// copy vert buffer
	if (pVertBuffer && !PrepareBufferCallback && !bOnlyVideoBuffer)
	{
		pRenderMesh->UpdateVertices(pVertBuffer, nVertCount, 0, VSF_GENERAL, 0u, false);
		if (pTangents)
			pRenderMesh->UpdateVertices(pTangents, nVertCount, 0, VSF_TANGENTS, 0u, false);
#if ENABLE_NORMALSTREAM_SUPPORT
		if (pNormals)
			pRenderMesh->UpdateVertices(pNormals, nVertCount, 0, VSF_NORMALS, 0u, false);
#endif
	}

	if (CustomData)
		CryFatalError("CRenderMesh::CustomData not supported anymore. Will be removed from interface");

	if (pIndices)
		pRenderMesh->UpdateIndices(pIndices, nIndices, 0, 0u, false);
	pRenderMesh->_SetPrimitiveType(GetInternalPrimitiveType(nPrimetiveType));

	pRenderMesh->m_nClientTextureBindID = nClientTextureBindID;

	pRenderMesh->UnLockForThreadAccess();
	return pRenderMesh.get();
}

//=======================================================================

int CRenderer::GetWhiteTextureId() const
{
	return 0;
}

float CRenderer::ScaleCoordX(float value) const
{
	return 0.0f;
}

float CRenderer::ScaleCoordY(float value) const
{
	return 0.0f;
}

void CRenderer::ScaleCoord(float& x, float& y) const
{
	
}

int CRenderer::GetOverlayWidth() const
{
	return 0;
}

int CRenderer::GetOverlayHeight() const
{
	return 0;
}

// used for sprite generation
void CRenderer::SetTextureAlphaChannelFromRGB(byte* pMemBuffer, int nTexSize)
{
	// set alpha channel
	for (int y = 0; y < nTexSize; y++)
		for (int x = 0; x < nTexSize; x++)
		{
			int t = (x + nTexSize * y) * 4;
			if (abs(pMemBuffer[t + 0] - pMemBuffer[0 + 0]) < 2 &&
			    abs(pMemBuffer[t + 1] - pMemBuffer[0 + 1]) < 2 &&
			    abs(pMemBuffer[t + 2] - pMemBuffer[0 + 2]) < 2)
				pMemBuffer[t + 3] = 0;
			else
				pMemBuffer[t + 3] = 255;

			// set border alpha to 0
			if (x == 0 || y == 0 || x == nTexSize - 1 || y == nTexSize - 1)
				pMemBuffer[t + 3] = 0;
		}
}

//=============================================================================
// Precaching
void CRenderer::PrecacheTexture(ITexture* pTP, float fMipFactor, float fTimeToReady, int Flags, int nUpdateId)
{
	
}

bool CRenderer::EF_PrecacheResource(ITexture* pTP, float fMipFactor, float fTimeToReady, int Flags, int nUpdateId)
{
	return true;
}

bool CRenderer::EF_PrecacheResource(SRenderLight* pLS, float fMipFactor, float fTimeToReady, int Flags, int nUpdateId)
{
	CRY_ASSERT(pLS, "Invalid parameter given to EF_PrecacheResource");
	ITexture* pLightTexture = pLS->m_pLightImage ? pLS->m_pLightImage : pLS->m_pLightDynTexSource ? pLS->m_pLightDynTexSource->GetTexture() : NULL;

	if (pLightTexture)
		CRenderer::EF_PrecacheResource(pLightTexture, fMipFactor, 0, Flags, nUpdateId);
	if (pLS->GetDiffuseCubemap())
		CRenderer::EF_PrecacheResource(pLS->GetDiffuseCubemap(), fMipFactor, 0, Flags, nUpdateId);
	if (pLS->GetSpecularCubemap())
		CRenderer::EF_PrecacheResource(pLS->GetSpecularCubemap(), fMipFactor, 0, Flags, nUpdateId);

	return true;
}

bool CRenderer::EF_PrecacheResource(IRenderShaderResources* pShaderResources, float fMipFactorSI, float fTimeToReady, int nFlags, int nUpdateId)
{
	

	return true;
}

bool CRenderer::EF_PrecacheResource(IRenderShaderResources* pShaderResources, int iScreenTexels, float fTimeToReady, int Flags, int nUpdateId)
{
	

	return true;
}

bool CRenderer::EF_PrecacheResource(SShaderItem* pSI, float fMipFactorSI, float fTimeToReady, int Flags, int nUpdateId)
{
	

	return true;
}

bool CRenderer::EF_PrecacheResource(SShaderItem* pSI, int iScreenTexels, float fTimeToReady, int Flags, int nUpdateId)
{
	

	return true;
}

bool CRenderer::EF_PrecacheResource(IShader* pSH, float fMipFactor, float fTimeToReady, int Flags, int nUpdateId)
{
	return true;
}

bool CRenderer::EF_PrecacheResource(IRenderMesh* _pPB, IMaterial* pMaterial, float fMipFactor, float fTimeToReady, int nFlags, int nUpdateId)
{
	return true;
}

//////////////////////////////////////////////////////////////////////////
// HDR_UPPERNORM -> factor used when converting from [0,32768] high dynamic range images
//                  to [0,1] low dynamic range images; 32768 = 2^(2^4-1), 4 exponent bits
// LDR_UPPERNORM -> factor used when converting from [0,1] low dynamic range images
//                  to 8bit outputs

#define HDR_UPPERNORM 1.0f  // factor set to 1.0, to be able to see content in our rather dark HDR images
#define LDR_UPPERNORM 255.0f

static float GammaToLinear(float x)
{
	return (x <= 0.04045f) ? x / 12.92f : powf((x + 0.055f) / 1.055f, 2.4f);
}

static float LinearToGamma(float x)
{
	return (x <= 0.0031308f) ? x * 12.92f : 1.055f * powf(x, 1.0f / 2.4f) - 0.055f;
}

//////////////////////////////////////////////////////////////////////////

#define PROCESS_IN_PARALLEL

// preserve the ability to use the old squish code in parallel
#define squish  squishccr
#define SQUISH_USE_CPP
#define SQUISH_USE_SSE  2
#define SQUISH_USE_XSSE 0
#define SQUISH_USE_CCR


// number of bytes per block per type
#define BLOCKSIZE_BC1 8
#define BLOCKSIZE_BC2 16
#define BLOCKSIZE_BC3 16
#define BLOCKSIZE_BC4 8
#define BLOCKSIZE_BC5 16
#define BLOCKSIZE_BC6 16
#define BLOCKSIZE_BC7 16


bool CRenderer::DXTDecompress(const byte* sourceData, const size_t srcFileSize, byte* destinationData, int width, int height, int mips, ETEX_Format sourceFormat, bool bUseHW, int nDstBytesPerPix)
{
	return true;
}

bool CRenderer::DXTCompress(const byte* sourceData, int width, int height, ETEX_Format destinationFormat, bool bUseHW, bool bGenMips, int nSrcBytesPerPix, MIPDXTcallback callback)
{
	return true;
}

bool CRenderer::WriteJPG(const byte* dat, int wdt, int hgt, char* name, int src_bits_per_pixel, int nQuality)
{
	return true;
}

//////////////////////////////////////////////////////////////////////////
ITexture* CRenderer::CreateTexture(const char* name, int width, int height, int numMips, unsigned char* pData, ETEX_Format eTF, int flags)
{
	return nullptr;
}

//////////////////////////////////////////////////////////////////////////
ITexture* CRenderer::CreateTextureArray(const char* name, ETEX_Type eType, uint32 nWidth, uint32 nHeight, uint32 nArraySize, int nMips, uint32 nFlags, ETEX_Format eTF, int nCustomID)
{
	return nullptr;
}

//////////////////////////////////////////////////////////////////////////
void CRenderer::CopyTextureRegion(ITexture* pSrc, RectI srcRegion, ITexture* pDst, RectI dstRegion, ColorF& color, const int renderStateFlags)
{
	
}

//////////////////////////////////////////////////////////////////////////
IShaderPublicParams* CRenderer::CreateShaderPublicParams()
{
	return nullptr;
}

//////////////////////////////////////////////////////////////////////////

void CRenderer::SetLevelLoadingThreadId(threadID threadId)
{
	
}

void CRenderer::GetThreadIDs(threadID& mainThreadID, threadID& renderThreadID) const
{
	
}
//////////////////////////////////////////////////////////////////////////
void CRenderer::PostLevelLoading()
{
	
}

const char* CRenderer::GetTextureFormatName(ETEX_Format eTF)
{
	return "";
}

uint32 CRenderer::GetTextureFormatDataSize(int nWidth, int nHeight, int nDepth, int nMips, ETEX_Format eTF, ETEX_TileMode mode)
{
	return 0;
}

//////////////////////////////////////////////////////////////////////////
ERenderType CRenderer::GetRenderType() const
{
	return ERenderType::Direct3D11;
}

int CRenderer::GetPolyCount()
{
	return 0;
}

void CRenderer::GetPolyCount(int& nPolygons, int& nShadowPolys)
{

}

int CRenderer::GetNumGeomInstances()
{
	return 0;
}

int CRenderer::GetNumGeomInstanceDrawCalls()
{
	return 0;
}

int CRenderer::GetCurrentNumberOfDrawCalls()
{
	return 0;
}

void CRenderer::GetCurrentNumberOfDrawCalls(int& nGeneral, int& nShadowGen)
{

}

int CRenderer::GetCurrentNumberOfDrawCalls(const uint32 EFSListMask)
{
	return 0;
}

void CRenderer::SetDebugRenderNode(IRenderNode* pRenderNode)
{
	m_pDebugRenderNode = pRenderNode;
}

bool CRenderer::IsDebugRenderNode(IRenderNode* pRenderNode) const
{
	return (m_pDebugRenderNode && m_pDebugRenderNode == pRenderNode);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
void SRenderStatistics::Begin(const SRenderStatistics* prevData)
{
#if defined(_DEBUG)
	memcpy(this, prevData, sizeof(SRenderStatistics));
#else
	memset(this, 0, sizeof(SRenderStatistics));
#endif
}

void SRenderStatistics::Finish()
{
	
}

#if defined(ENABLE_PROFILING_CODE)
int SRenderStatistics::GetNumGeomInstances() const
{
	return m_nNumInsts; // +m_nAsynchNumInsts; impossible because of non-atomicity of stat-collection
}

int SRenderStatistics::GetNumGeomInstanceDrawCalls() const
{
	return m_nNumInstCalls; // +m_nAsynchNumInstCalls; impossible because of non-atomicity of stat-collection
}

int SRenderStatistics::GetNumberOfDrawCalls() const
{
	int nDIPs = 0;
	for (int i = 0; i < EFSLIST_NUM; i++)
	{
		nDIPs += m_nDIPs[i]; // +m_nAsynchDIPs[i]; impossible because of non-atomicity of stat-collection
	}
	return nDIPs;
}

int SRenderStatistics::GetNumberOfDrawCalls(const uint32 EFSListMask) const
{
	int nDIPs = 0;
	for (uint32 i = 0; i < EFSLIST_NUM; i++)
	{
		if ((1 << i) & EFSListMask)
		{
			nDIPs += m_nDIPs[i]; // +m_nAsynchDIPs[i]; impossible because of non-atomicity of stat-collection
		}
	}
	return nDIPs;
}

int SRenderStatistics::GetNumberOfPolygons() const
{
	int nDIPs = 0;
	for (int i = 0; i < EFSLIST_NUM; i++)
	{
		nDIPs += m_nPolygons[i]; // +m_nAsynchPolygons[i]; impossible because of non-atomicity of stat-collection
	}
	return nDIPs;
}

int SRenderStatistics::GetNumberOfPolygons(const uint32 EFSListMask) const
{
	int nDIPs = 0;
	for (uint32 i = 0; i < EFSLIST_NUM; i++)
	{
		if ((1 << i) & EFSListMask)
		{
			nDIPs += m_nPolygons[i]; // +m_nAsynchPolygons[i]; impossible because of non-atomicity of stat-collection
		}
	}
	return nDIPs;
}
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////
#if defined(DO_RENDERSTATS)
void IRenderer::SDrawCallCountInfo::Update(CRenderObject* pObj, IRenderMesh* pRM, EShaderTechniqueID techniqueID)
{
	if (((IRenderNode*)pObj->m_pRenderNode))
	{
		pPos = pObj->GetMatrix().GetTranslation();

		if (meshName[0] == '\0')
		{
			const char* pMeshName = pRM->GetSourceName();
			if (pMeshName)
			{
				const size_t nameLen = strlen(pMeshName);

				// truncate if necessary
				if (nameLen >= sizeof(meshName))
				{
					pMeshName += nameLen - (sizeof(meshName) - 1);
				}
				cry_strcpy(meshName, pMeshName);
			}

			const char* pTypeName = pRM->GetTypeName();
			if (pTypeName)
			{
				cry_strcpy(typeName, pTypeName);
			}
		}

		if (techniqueID == TTYPE_GENERAL || techniqueID == TTYPE_Z)
		{
			nGeneral++;
		}
		else if (techniqueID == TTYPE_SHADOWGEN)
		{
			nShadows++;
		}
		else if (techniqueID == TTYPE_ZPREPASS)
		{
			nZpass++;
		}
		else
		{
			nMisc++;
		}
	}
}
#endif
/////////////////////////////////////////////////////////////////////////////////////////////////////

void S3DEngineCommon::Update(const SRenderingPassInfo& passInfo)
{
}

void S3DEngineCommon::UpdateSkyInfo(const SRenderingPassInfo& passInfo)
{
	
}

void S3DEngineCommon::UpdateRainInfo(const SRenderingPassInfo& passInfo)
{
	if (passInfo.IsAuxWindow())
	{
		// Secondary viewport: We only update rain for the primary viewport. Otherwise update will use wrong camera. This is needed as long as rain and snow are
		// global engine states, with no regard to output context.
		return;
	}

	gEnv->p3DEngine->GetRainParams(m_RainInfo);

	const Vec3 vCamPos = passInfo.GetCamera().GetPosition();
	const float fUnderWaterAtten = clamp_tpl(vCamPos.z - m_OceanInfo.m_fWaterLevel + 1.f, 0.f, 1.f);
	m_RainInfo.fCurrentAmount *= fUnderWaterAtten;

#ifdef RAIN_DEBUG
	m_RainInfo.fAmount               = 1.f;
	m_RainInfo.fCurrentAmount        = 1.f;
	m_RainInfo.fRadius               = 2000.f;
	m_RainInfo.fFakeGlossiness       = 0.5f;
	m_RainInfo.fFakeReflectionAmount = 1.5f;
	m_RainInfo.fDiffuseDarkening     = 0.5f;
	m_RainInfo.fRainDropsAmount      = 0.5f;
	m_RainInfo.fRainDropsSpeed       = 1.f;
	m_RainInfo.fRainDropsLighting    = 1.f;
	m_RainInfo.fMistAmount           = 3.f;
	m_RainInfo.fMistHeight           = 8.f;
	m_RainInfo.fPuddlesAmount        = 1.5f;
	m_RainInfo.fPuddlesMaskAmount    = 1.0f;
	m_RainInfo.fPuddlesRippleAmount  = 2.0f;
	m_RainInfo.fSplashesAmount       = 1.3f;

	m_RainInfo.vColor.Set(1, 1, 1);
	m_RainInfo.vWorldPos.Set(0, 0, 0);
#endif
}

void S3DEngineCommon::UpdateSnowInfo(const SRenderingPassInfo& passInfo)
{
	if (passInfo.IsAuxWindow())
	{
		// Secondary viewport: See UpdateRainInfo() comment.
		return;
	}

	gEnv->p3DEngine->GetSnowSurfaceParams(m_SnowInfo.m_vWorldPos, m_SnowInfo.m_fRadius, m_SnowInfo.m_fSnowAmount, m_SnowInfo.m_fFrostAmount, m_SnowInfo.m_fSurfaceFreezing);
	gEnv->p3DEngine->GetSnowFallParams(m_SnowInfo.m_nSnowFlakeCount, m_SnowInfo.m_fSnowFlakeSize, m_SnowInfo.m_fSnowFallBrightness, m_SnowInfo.m_fSnowFallGravityScale, m_SnowInfo.m_fSnowFallWindScale, m_SnowInfo.m_fSnowFallTurbulence, m_SnowInfo.m_fSnowFallTurbulenceFreq);
}

void S3DEngineCommon::UpdateRainOccInfo(const SRenderingPassInfo& passInfo)
{
	
}

/////////////////////////////////////////////////////////////////////////////////////////////////////

void CRenderer::GetMemoryUsage(ICrySizer* pSizer)
{
	
}

// retrieves the bandwidth calculations for the audio streaming
void CRenderer::GetBandwidthStats(float* fBandwidthRequested)
{

}

//////////////////////////////////////////////////////////////////////////
void CRenderer::SetTextureStreamListener(ITextureStreamListener* pListener)
{

}

#if defined(CRY_ENABLE_RC_HELPER)
void CRenderer::AddAsyncTextureCompileListener(IAsyncTextureCompileListener* pListener)
{
	
}

void CRenderer::RemoveAsyncTextureCompileListener(IAsyncTextureCompileListener* pListener)
{
	
}
#endif

//////////////////////////////////////////////////////////////////////////
float CRenderer::GetGPUFrameTime()
{
	return 0.0f;
}

void CRenderer::GetRenderTimes(SRenderTimes& outTimes)
{
	
}

//////////////////////////////////////////////////////////////////////////
void CRenderer::PreShutDown()
{
	
}

//////////////////////////////////////////////////////////////////////////
void CRenderer::PostShutDown()
{
	SAFE_DELETE(m_pTextureManager);
}

//////////////////////////////////////////////////////////////////////////
void CRenderer::UpdateRenderingModesInfo()
{
	
}

//////////////////////////////////////////////////////////////////////////

bool CRenderer::IsCustomRenderModeEnabled(uint32 nRenderModeMask)
{
	return false;
}

//////////////////////////////////////////////////////////////////////////
bool CRenderer::IsPost3DRendererEnabled() const
{
	

	return false;
}

void CRenderer::ExecuteAsyncDIP()
{
	CryFatalError("The external ExecuteAsyncDIP functionality is only supported on Durango");
}

//////////////////////////////////////////////////////////////////////////
void CRenderer::EF_SetPostEffectParam(const char* pParam, float fValue, bool bForceValue)
{
	
}

void CRenderer::EF_SetPostEffectParamVec4(const char* pParam, const Vec4& pValue, bool bForceValue)
{
	
}

//////////////////////////////////////////////////////////////////////////
void CRenderer::EF_SetPostEffectParamString(const char* pParam, const char* pszArg)
{
	
}

//////////////////////////////////////////////////////////////////////////
void CRenderer::EF_GetPostEffectParam(const char* pParam, float& fValue)
{
	
}

//////////////////////////////////////////////////////////////////////////
void CRenderer::EF_GetPostEffectParamVec4(const char* pParam, Vec4& pValue)
{
}

//////////////////////////////////////////////////////////////////////////
void CRenderer::EF_GetPostEffectParamString(const char* pParam, const char*& pszArg)
{
	
}

//////////////////////////////////////////////////////////////////////////
int32 CRenderer::EF_GetPostEffectID(const char* pPostEffectName)
{
	return 0;
}

//////////////////////////////////////////////////////////////////////////
void CRenderer::EF_ResetPostEffects(bool bOnSpecChange)
{
	
}

//////////////////////////////////////////////////////////////////////////
void CRenderer::EF_DisableTemporalEffects()
{
	
}

void CRenderer::SetTexturePrecaching(bool stat)
{
	
}

void CRenderer::PrecachePostponedTextures()
{
}

IOpticsElementBase* CRenderer::CreateOptics(EFlareType type) const
{
	return nullptr;
}

//////////////////////////////////////////////////////////////////////////
SSkinningData* CRenderer::EF_CreateSkinningData(IRenderView* pRenderView, uint32 nNumBones, bool bNeedJobSyncVar)
{
	return nullptr;
}

SSkinningData* CRenderer::EF_CreateRemappedSkinningData(IRenderView* pRenderView, uint32 nNumBones, SSkinningData* pSourceSkinningData, uint32 nCustomDataSize, uint32 pairGuid)
{
	return nullptr;
}

void CRenderer::EF_EnqueueComputeSkinningData(IRenderView* pRenderView, SSkinningData* pData)
{

}

size_t CRenderer::GetTexturesStreamPoolSize()
{
	return 0;
}

void CRenderer::ClearSkinningDataPool()
{

}

void CRenderer::EnqueueSkinningSimulationJob(JobManager::SJobState* pJob)
{

}

void CRenderer::WaitAndClearSkinningSimulationJobs()
{

}



int CRenderer::EF_GetSkinningPoolID()
{
	return m_nPoolIndex;
}

void CRenderer::UpdateShaderItem(SShaderItem* pShaderItem, IMaterial* pMaterial)
{
	
}

void CRenderer::RefreshShaderResourceConstants(SShaderItem* pShaderItem, IMaterial* pMaterial)
{
	
}

void CRenderer::ForceUpdateShaderItem(SShaderItem* pShaderItem, IMaterial* pMaterial)
{
	
}

bool CRenderer::LoadShaderStartupCache()
{
	return true;
}

void CRenderer::UnloadShaderStartupCache()
{
	
}

void CRenderer::ClearShaderPipelineStateCache()
{
	
}

void CRenderer::FlushPendingTextureTasks()
{

}

void CRenderer::FlushPendingUploads()
{
}

void CRenderer::SetCloakParams(const SRendererCloakParams& cloakParams)
{
	
}

float CRenderer::GetCloakFadeLightScale() const
{
	return 0.0f;
}

void CRenderer::SetCloakFadeLightScale(float fColorScale)
{

}

void CRenderer::SetShadowJittering(float shadowJittering)
{
	m_shadowJittering = shadowJittering;
}

float CRenderer::GetShadowJittering() const
{
	return m_shadowJittering;
}

void CRenderer::SyncMainWithRender()
{
	
}

void CRenderer::RegisterSyncWithMainListener(ISyncMainWithRenderListener* pListener)
{
	stl::push_back_unique(m_syncMainWithRenderListeners, pListener);
}

void CRenderer::RemoveSyncWithMainListener(const ISyncMainWithRenderListener* pListener)
{
	stl::find_and_erase(m_syncMainWithRenderListeners, pListener);
}

void CRenderer::FreePermanentRenderObjects(int bufferId)
{
	
}

void CRenderer::SetCloudShadowsParams(int nTexID, const Vec3& speed, float tiling, bool invert, float brightness)
{
	m_cloudShadowTexId      = nTexID;
	m_cloudShadowSpeed      = speed;
	m_cloudShadowTiling     = tiling;
	m_cloudShadowInvert     = invert;
	m_cloudShadowBrightness = brightness;
}

bool CRenderer::GetCloudShadowsEnabled() const
{
	return m_bCloudShadowsEnabled && (m_cloudShadowTexId > 0);
}

void CRenderer::SetVolumetricCloudParams(int nTexID)
{
	ITexture* tex = EF_GetTextureByID(m_volumetricCloudTexId);
	if (tex)
	{
		tex->Release();
	}
	m_volumetricCloudTexId = nTexID;
}

void CRenderer::SetVolumetricCloudNoiseTex(int cloudNoiseTexId, int edgeNoiseTexId)
{
	ITexture* tex = EF_GetTextureByID(m_volumetricCloudNoiseTexId);
	if (tex)
	{
		tex->Release();
	}
	m_volumetricCloudNoiseTexId = cloudNoiseTexId;

	tex = EF_GetTextureByID(m_volumetricCloudEdgeNoiseTexId);
	if (tex)
	{
		tex->Release();
	}
	m_volumetricCloudEdgeNoiseTexId = edgeNoiseTexId;
}

void CRenderer::GetVolumetricCloudTextureInfo(SVolumetricCloudTexInfo& info) const
{
	info.cloudTexId = m_volumetricCloudTexId;
	info.cloudNoiseTexId = m_volumetricCloudNoiseTexId;
	info.edgeNoiseTexId = m_volumetricCloudEdgeNoiseTexId;
}

void CRenderer::UpdateCachedShadowsLodCount(int nGsmLods) const
{
	
}


#ifdef ENABLE_PROFILING_CODE
void CRenderer::AddRecordedProfilingStats(const SProfilingStats& stats, ERenderListID renderList, bool bAsynchronous)
{
	
}
#endif

void CRenderer::CollectDrawCallsInfo(bool status)
{
	m_bCollectDrawCallsInfo = status;
}

void CRenderer::CollectDrawCallsInfoPerNode(bool status)
{
	m_bCollectDrawCallsInfoPerNode = status;
}

void CRenderer::EnableLevelUnloading(bool enable)
{
	
}

void CRenderer::EnableBatchMode(bool enable)
{
	
}

bool CRenderer::StopRendererAtFrameEnd(uint timeoutMilliseconds)
{
	m_mtxStopAtRenderFrameEnd.Lock();
	m_bStopRendererAtFrameEnd = true;

	if (!m_condStopAtRenderFrameEnd.TimedWait(m_mtxStopAtRenderFrameEnd, timeoutMilliseconds))
	{
		m_mtxStopAtRenderFrameEnd.Unlock();
		return false;
	}

	m_mtxStopAtRenderFrameEnd.Unlock();
	return true;
}

void CRenderer::ResumeRendererFromFrameEnd()
{
	m_mtxStopAtRenderFrameEnd.Lock();
	if (!m_bStopRendererAtFrameEnd)
	{
		m_mtxStopAtRenderFrameEnd.Unlock();
		CryFatalError("Trying to resume render thread but render thread was not stopped before. Use StopRendererAtFrameEnd() prior using ResumeRendererFromFrameEnd().");
	}
	m_bStopRendererAtFrameEnd = false;
	m_mtxStopAtRenderFrameEnd.Unlock();
	m_condStopAtRenderFrameEnd.Notify();
}

void CRenderer::QueryActiveGpuInfo(SGpuInfo& info) const
{
	info = m_adapterInfo;
}

void CRenderer::SetRenderQuality(const SRenderQuality& quality)
{
	m_renderQuality = quality;
}

void CRenderer::ScheduleResourceForDelete(CBaseResource* pResource)
{
	
}

//////////////////////////////////////////////////////////////////////////
void CRenderer::RT_DelayedDeleteResources(bool bAllResources)
{
	
}
static const char* cc_RenderViewName[IRenderView::eViewType_Count] = 
{ "Normal View", "Recursive View", "Shadow View", "BillboardGen View" };
//////////////////////////////////////////////////////////////////////////
void CRenderer::InitRenderViewPool()
{
	for (int type = 0; type < IRenderView::eViewType_Count; ++type)
	{
		m_pRenderViewPool[type].allocElementFunction = [type]() -> CRenderView*
			{
				return new CRenderView(cc_RenderViewName[type], IRenderView::EViewType(type));
			};
		m_pRenderViewPool[type].freeElementFunction = [](CRenderView*) {};
	}
}

//=============================================================================

alloc_info_struct* CRenderer::GetFreeChunk(int bytes_count, int nBufSize, PodArray<alloc_info_struct>& alloc_info, const char* szSource)
{
	int best_i = -1;
	int min_size = 10000000;

	// find best chunk
	for (int i = 0; i < alloc_info.Count(); i++)
	{
		if (!alloc_info[i].busy)
		{
			if (alloc_info[i].bytes_num >= bytes_count)
			{
				if (alloc_info[i].bytes_num < min_size)
				{
					best_i = i;
					min_size = alloc_info[i].bytes_num;
				}
			}
		}
	}

	if (best_i >= 0)
	{
		// use best free chunk
		alloc_info[best_i].busy = true;
		alloc_info[best_i].szSource = szSource;

		int bytes_free = alloc_info[best_i].bytes_num - bytes_count;
		if (bytes_free > 0)
		{
			// modify reused shunk
			alloc_info[best_i].bytes_num = bytes_count;

			// insert another free shunk
			alloc_info_struct new_chunk;
			new_chunk.bytes_num = bytes_free;
			new_chunk.ptr = alloc_info[best_i].ptr + alloc_info[best_i].bytes_num;
			new_chunk.busy = false;

			if (best_i < alloc_info.Count() - 1) // if not last
			{
				alloc_info.InsertBefore(new_chunk, best_i + 1);
			}
			else
			{
				alloc_info.Add(new_chunk);
			}
		}

		return &alloc_info[best_i];
	}

	int res_ptr = 0;

	int piplevel = alloc_info.Count() ? (alloc_info.Last().ptr - alloc_info[0].ptr) + alloc_info.Last().bytes_num : 0;
	if (piplevel + bytes_count >= nBufSize)
	{
		return NULL;
	}
	else
	{
		res_ptr = piplevel;
	}

	// register new chunk
	alloc_info_struct ai;
	ai.ptr = res_ptr;
	ai.szSource = szSource;
	ai.bytes_num = bytes_count;
	ai.busy = true;
	alloc_info.Add(ai);

	return &alloc_info[alloc_info.Count() - 1];
}

bool CRenderer::ReleaseChunk(int p, PodArray<alloc_info_struct>& alloc_info)
{
	for (int i = 0; i < alloc_info.Count(); i++)
	{
		if (alloc_info[i].ptr == p)
		{
			alloc_info[i].busy = false;

			// delete info about last unused chunks
			while (alloc_info.Count() && alloc_info.Last().busy == false)
			{
				alloc_info.Delete(alloc_info.Count() - 1);
			}

			// merge unused chunks
			for (int s = 0; s < alloc_info.Count() - 1; s++)
			{
				assert(alloc_info[s].ptr < alloc_info[s + 1].ptr);

				if (alloc_info[s].busy == false)
				{
					if (alloc_info[s + 1].busy == false)
					{
						alloc_info[s].bytes_num += alloc_info[s + 1].bytes_num;
						alloc_info.Delete(s + 1);
						s--;
					}
				}
			}

			return true;
		}
	}

	return false;
}

///////////////////////////////////////////////////////////////////////////////
CRenderObject* CRenderer::EF_GetObject()
{
	CRenderObject* pObj = new IPermanentRenderObject;
	return pObj;
}

///////////////////////////////////////////////////////////////////////////////
void CRenderer::EF_FreeObject(CRenderObject* pObj)
{
	delete pObj;
}

///////////////////////////////////////////////////////////////////////////////
CRenderObject* CRenderer::EF_DuplicateRO(CRenderObject* pSrc, const SRenderingPassInfo& passInfo)
{
	if (pSrc->m_bPermanent)
	{
		// Clone object and attach to the end of linked list of the source object
		IPermanentRenderObject* pObjSrc = static_cast<IPermanentRenderObject*>(pSrc);
		IPermanentRenderObject* pObjNew = static_cast<IPermanentRenderObject*>(CRenderer::EF_GetObject());

		pObjNew->CloneObject(pObjSrc);

		// Link duplicated object to the source object
		{
			pObjNew->m_pNextPermanent = pObjSrc->m_pNextPermanent;
			pObjSrc->m_pNextPermanent = pObjNew;
		}

		return pObjNew;
	}

	CRenderObject* pObjNew = passInfo.GetRenderView()->AllocateTemporaryRenderObject();
	pObjNew->CloneObject(pSrc);
	return pObjNew;
}


gpu_pfx2::IManager* CRenderer::GetGpuParticleManager()
{
	return m_pGpuParticleManager;
}

