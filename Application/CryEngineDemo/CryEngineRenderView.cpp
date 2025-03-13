// Copyright 2016-2021 Crytek GmbH / Crytek Group. All rights reserved.

#include "StdAfx.h"
#include "CryEngineRenderView.h"

#include <CryRenderer/branchmask.h>


//////////////////////////////////////////////////////////////////////////
CRenderView::CRenderView(const char* name, EViewType type, CRenderView* pParentView, ShadowMapFrustum* pShadowFrustumOwner)
	: m_usageMode(eUsageModeUndefined)
	, m_viewType(type)
	, m_name(name)
	, m_skipRenderingFlags(0)
	, m_frameId(0)
	, m_pParentView(pParentView)
	, m_tempRenderObjects(64, 1 << 20 /* capacity = 1 MiB*/)
	, m_fogVolumeContributions(64, 1 << 20 /* capacity = 1 MiB*/)
	, m_numFogVolumes(0)
	, m_numUsedClientPolygons(0)
	, m_bDeferrredNormalDecals(false)
	, m_bTrackUncompiledItems(true)
	, m_bAddingClientPolys(false)
	, m_permanentRenderObjectsToCompile(64, 1 << 20 /* capacity = 1 MiB*/)
	, m_temporaryCompiledObjects(64, 1 << 20 /* capacity = 1 MiB*/)
	, m_permanentObjects(64, (1 << 14) * sizeof(SPermanentObjectRecord) /* capacity = 16 ki objects*/)
	, m_viewInfoCount(1)
	, m_bPostWriteExecuted(false)
{
	MEMSTAT_CONTEXT(EMemStatContextType::D3D, "CRenderView::CRenderView");

	for (int i = 0; i < EFSLIST_NUM; i++)
	{
		m_addedItems[i] = 0;
		m_batchFlags[i] = 0;

	}

}

//////////////////////////////////////////////////////////////////////////
CRenderView::~CRenderView()
{
	Clear();

	for (auto pClientPoly : m_polygonsPool)
		delete pClientPoly;
}



void CRenderView::Clear()
{
	CRY_ASSERT(m_usageMode == IRenderView::eUsageModeReadingDone ||
	           m_usageMode == IRenderView::eUsageModeWritingDone ||
	           m_usageMode == IRenderView::eUsageModeUndefined);

	if (m_usageMode == IRenderView::eUsageModeWritingDone)
	{
		m_jobstate_Sort.Wait();
		m_jobstate_PostWrite.Wait();
		m_jobstate_ShadowGen.Wait();
	}

	m_usageMode = IRenderView::eUsageModeUndefined;
	m_name.clear();
	m_frameId = -1;
	m_frameTime = CTimeValue();
	m_pParentView = nullptr;

	m_RenderWidth  = -1;
	m_RenderHeight = -1;

	ZeroStruct(m_viewport);
	m_bTrackUncompiledItems = true;
	m_bAddingClientPolys = false;
	m_skinningPoolIndex = 0;
	for (int i = 0; i < CCamera::eEye_eCount; ++i)
		m_camera[i] = m_previousCamera[i] = CCamera();
	ZeroArray(m_viewInfo);
	m_viewInfoCount = 0;
	m_bPostWriteExecuted = false;
	m_vProjMatrixSubPixoffset = Vec2(ZERO);

	m_viewFlags = SRenderViewInfo::eFlags_None;
	m_viewInfoCount = 1;
	m_numUsedClientPolygons = 0;

	for (int i = 0; i < EFSLIST_NUM; i++)
	{
		m_batchFlags[i] = 0;
		m_addedItems[i] = 0;
	}

	for (int i = 0; i < eDLT_NumLightTypes; i++)
	{
		for (auto& light : m_lights[i])
		{
			light.DropResources();
		}
		m_lights[i].clear();
	}

	m_deferredDecals.clear();
	m_bDeferrredNormalDecals = false;
	m_clipVolumes.clear();

	for (int32 i = 0; i < IFogVolumeRenderNode::eFogVolumeType_Count; ++i)
	{
		m_fogVolumes[i].clear();
	}

	for (int32 i = 0; i < CloudBlockerTypeNum; ++i)
	{
		m_cloudBlockers[i].clear();
	}

	m_waterRipples.clear();

	m_fogVolumeContributions.clear();
	m_numFogVolumes = 0;

	m_globalFogDescription = SRenderGlobalFogDescription();

	ClearTemporaryCompiledObjects();
	m_permanentRenderObjectsToCompile.clear();

	m_bTrackUncompiledItems = true;

	m_skipRenderingFlags = 0;

	m_tempRenderObjects.reset_container();

	m_permanentObjects.clear();

	m_bClearTarget = false;
	m_targetClearColor = ColorF(0,0,0,0);

	UnsetRenderOutput();

	m_auxiliaryStatObjects.clear();
}

// Helper function to allocate new compiled object from pool
CCompiledRenderObject* CRenderView::AllocCompiledObject(CRenderObject* pObj, CRenderElement* pElem, const SShaderItem& shaderItem)
{
	assert(false);
	return nullptr;
}

SDeferredDecal* CRenderView::AddDeferredDecal(const SDeferredDecal& source)
{
	if (!source.pMaterial)
	{
		assert(0);
	}
	m_deferredDecals.push_back(source);
	return &m_deferredDecals.back();
}

std::vector<SDeferredDecal>& CRenderView::GetDeferredDecals()
{
	return m_deferredDecals;
}

void CRenderView::SetFrameId(int frameId)
{
	m_frameId = frameId;
}

void CRenderView::SetCameras(const CCamera* pCameras, int cameraCount)
{
	CRY_ASSERT(cameraCount == 1 || cameraCount == 2);

	for (int i = 0; i < cameraCount; ++i)
	{
		CRY_ASSERT(pCameras[i].GetEye() == CCamera::eEye_Left || pCameras[i].GetEye() == CCamera::eEye_Right);

		const CCamera& cam = pCameras[i];
		m_camera[cam.GetEye()] = cam;
	}
}

//////////////////////////////////////////////////////////////////////////
void CRenderView::SetPreviousFrameCameras(const CCamera* pCameras, int cameraCount)
{
	CRY_ASSERT(cameraCount == 1 || cameraCount == 2);

	for (int i = 0; i < cameraCount; ++i)
	{
		CRY_ASSERT(pCameras[i].GetEye() == CCamera::eEye_Left || pCameras[i].GetEye() == CCamera::eEye_Right);
		const CCamera& cam = pCameras[i];
		m_previousCamera[cam.GetEye()] = cam;
	}
}

//////////////////////////////////////////////////////////////////////////
void CRenderView::CalculateViewInfo()
{
	
}

//////////////////////////////////////////////////////////////////////////

void CRenderView::SwitchUsageMode(EUsageMode mode)
{
	
	if (mode == m_usageMode)
		return;

	//assert(mode != m_usageMode);

	if (mode == eUsageModeWriting)
	{
		CRY_ASSERT(m_usageMode == IRenderView::eUsageModeUndefined || m_usageMode == IRenderView::eUsageModeReadingDone);
		CRY_ASSERT(!m_jobstate_Sort.IsRunning());

		m_bPostWriteExecuted = false;
		}

	if (mode == eUsageModeWritingDone)
	{
		CRY_ASSERT(m_usageMode == IRenderView::eUsageModeWriting);
		CRY_ASSERT(!m_jobstate_PostWrite.IsRunning());

		PreparePermanentRenderObjectsForCompile();
		gEnv->pJobManager->AddLambdaJob("JobRenderViewPostWrite", [this] { CRenderView::Job_PostWrite();  }, JobManager::eRegularPriority, &m_jobstate_PostWrite);

		gEnv->pRenderer->WaitAndClearSkinningSimulationJobs();
	}

	if (mode == eUsageModeReading)
	{
		{
			// Prepare view for rasterizing (reading)
			// We now need to wait until all prepare for writing jobs are done.
			m_jobstate_PostWrite.Wait();
			m_jobstate_Sort.Wait();
		}

		//Job_PostWrite();
		CRY_ASSERT(m_bPostWriteExecuted);

		CRY_ASSERT(m_usageMode == IRenderView::eUsageModeWritingDone || m_usageMode == IRenderView::eUsageModeReadingDone);

		CalculateViewInfo();

		//CompileModifiedRenderObjects();
		UpdateModifiedShaderItems();
	}

	if (mode == eUsageModeReadingDone)
	{
		CRY_ASSERT(m_usageMode == IRenderView::eUsageModeReading);
		CRY_ASSERT(!m_jobstate_PostWrite.IsRunning());
		CRY_ASSERT(!m_jobstate_Sort.IsRunning());

	}

	{
		CryAutoLock<CryCriticalSectionNonRecursive> lock(m_lock_UsageMode);
		m_usageMode = mode;
	}
}

void CRenderView::PrepareForRendering()
{
	for (int i = 0; i < EFSLIST_NUM; i++)
	{
		//m_renderItems[i].CoalesceMemory();
		//m_RenderListDesc[0].m_nEndRI[i] = m_renderItems[i].size();
	}
	//ClearBatchFlags();
}

//////////////////////////////////////////////////////////////////////////
void CRenderView::PrepareForWriting()
{
}

//////////////////////////////////////////////////////////////////////////

RenderLightIndex CRenderView::AddDeferredLight(const SRenderLight& pDL, float fMult, const SRenderingPassInfo& passInfo)
{
	CRenderView* pRenderView = passInfo.GetRenderView();
	CRY_ASSERT(pRenderView);

	bool bSort = true;
	bool bAppend = true;

	eDeferredLightType LightType = eDLT_DeferredLight;
	if (pDL.m_Flags & DLF_DEFERRED_CUBEMAPS)
	{
		LightType = eDLT_DeferredCubemap;
		bSort = false;
	}
	else if (pDL.m_Flags & DLF_AMBIENT)
	{
		LightType = eDLT_DeferredAmbientLight;
		bSort = false;
	}

	if (pDL.GetLensOpticsElement() && !pDL.m_pSoftOccQuery)
	{
		SRenderLight* pLight = const_cast<SRenderLight*>(&pDL);

		const uint8 numVisibilityFaders = 2; // For each flare type
	}

	SRenderLight* pAddedLight = nullptr;

	const RenderLightIndex lightsNum = pRenderView->GetLightsCount(LightType);
	RenderLightIndex nLightId = -1;

	
	if (bAppend)
	{
		pAddedLight = pRenderView->AddLightAtIndex(LightType, pDL);
		nLightId = pAddedLight->m_Id;
	}

	if (pDL.m_Flags & DLF_LINK_TO_SKY_COLOR)
	{
#if defined(FEATURE_SVO_GI)
		CSvoRenderer* pSR = CSvoRenderer::GetInstance();
		if (pSR)
		{
			pAddedLight->m_Color *= pSR->GetSkyColor();
		}
		else
#endif

		{
			pAddedLight->m_Color *= gEnv->p3DEngine->GetSkyColor();
		}
	}

	IF_LIKELY((pDL.m_Flags & (DLF_DEFERRED_CUBEMAPS | DLF_AMBIENT)) == 0)
	{
		pAddedLight->m_Color *= fMult;
		pAddedLight->m_SpecMult *= fMult;
	}
	else if (pDL.m_Flags & DLF_AMBIENT)
	{
		ColorF origCol(pAddedLight->m_Color);
		pAddedLight->m_Color.lerpFloat(Col_White, origCol, fMult);
	}
	else
	{
		pAddedLight->m_Color.a = fMult; // store fade-out constant separately in alpha channel for deferred cubemaps
	}

	return nLightId;
}

//////////////////////////////////////////////////////////////////////////
RenderLightIndex CRenderView::AddDynamicLight(const SRenderLight& light)
{
	return AddLight(eDLT_DynamicLight, light);
}

//////////////////////////////////////////////////////////////////////////
RenderLightIndex CRenderView::GetDynamicLightsCount() const
{
	return GetLightsCount(eDLT_DynamicLight);
}

//////////////////////////////////////////////////////////////////////////
SRenderLight& CRenderView::GetDynamicLight(RenderLightIndex nLightId)
{
	return GetLight(eDLT_DynamicLight, nLightId);
}

//////////////////////////////////////////////////////////////////////////
RenderLightIndex CRenderView::AddLight(eDeferredLightType lightType, const SRenderLight& light)
{
	CRY_ASSERT((light.m_Flags & DLF_LIGHTTYPE_MASK) != 0);

	RenderLightIndex nLightId = -1;
	if (!(light.m_Flags & DLF_FAKE))
	{
		nLightId = GetLightsCount(lightType);
	}

	m_lights[lightType].push_back(light);
	SRenderLight* pLight = &m_lights[lightType].back();

	pLight->m_Id = nLightId;

	return nLightId;
}

//////////////////////////////////////////////////////////////////////////
SRenderLight* CRenderView::AddLightAtIndex(eDeferredLightType lightType, const SRenderLight& light, RenderLightIndex nLightId /*=-1*/)
{
	CRY_ASSERT(nLightId == -1 || nLightId < GetLightsCount(lightType));

	SRenderLight* pLight = nullptr;
	if (nLightId < 0)
	{
		nLightId = GetLightsCount(lightType);

		m_lights[lightType].push_back(light);
		pLight = &m_lights[lightType].back();
	}
	else
	{
		// find iterator at given index (assuming no [] operator)
		auto itr = m_lights[lightType].begin();
		while (--nLightId >= 0)
			++itr;
		m_lights[lightType].insert(itr, light);

		// invalidate indices of following lights (ID could also be incremented ...)
		auto stp = m_lights[lightType].end();
		while (++itr != stp)
			(*itr).m_Id = -2;
	}

	pLight->m_Id = nLightId;

	return pLight;
}

RenderLightIndex CRenderView::GetLightsCount(eDeferredLightType lightType) const
{
	return (RenderLightIndex)m_lights[lightType].size();
}

SRenderLight& CRenderView::GetLight(eDeferredLightType lightType, RenderLightIndex nLightId)
{
	CRY_ASSERT(nLightId >= 0 && nLightId < m_lights[lightType].size());

	// find iterator at given index (assuming no [] operator)
	auto itr = m_lights[lightType].begin();
	while (--nLightId >= 0)
		++itr;
	return *itr;
}

//////////////////////////////////////////////////////////////////////////
RenderLightsList& CRenderView::GetLightsArray(eDeferredLightType lightType)
{
	assert(lightType >= 0 && lightType < eDLT_NumLightTypes);
	return m_lights[lightType];
}

//////////////////////////////////////////////////////////////////////////
const SRenderLight* CRenderView::GetSunLight() const
{
	for (const auto& iter : m_lights[eDLT_DynamicLight])
	{
		if (iter.m_Flags & DLF_SUN)
			return &iter;
	}
	return nullptr;
}

const Vec4 CRenderView::GetSunLightColor()
{
	Vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f };
	return color;
}

const Vec3 CRenderView::GetSunLightDirection()
{
	Vec3 lightDir;

	if (m_shaderRenderingFlags & SHDF_SECONDARY_VIEWPORT)
	{
		const SRenderLight* sunLight = GetSunLight();
		if (sunLight)
		{
			lightDir = sunLight->GetPosition().normalized();
		}		
	}
	else
	{
		lightDir = gEnv->p3DEngine->GetSunDirNormalized();
	}

	return lightDir;
}

//////////////////////////////////////////////////////////////////////////
uint8 CRenderView::AddClipVolume(const IClipVolume* pClipVolume)
{
	return -1;
}

void CRenderView::SetClipVolumeBlendInfo(const IClipVolume* pClipVolume, int blendInfoCount, IClipVolume** blendVolumes, Plane* blendPlanes)
{
	size_t nClipVolumeIndex = pClipVolume->GetStencilRef() - 1; // 0 is reserved for outdoor
	CRY_ASSERT(blendInfoCount <= SDeferredClipVolume::MaxBlendInfoCount);
	CRY_ASSERT(nClipVolumeIndex >= 0 && nClipVolumeIndex < m_clipVolumes.size() && m_clipVolumes[nClipVolumeIndex].nStencilRef == pClipVolume->GetStencilRef());

	SDeferredClipVolume& volume = m_clipVolumes[nClipVolumeIndex];

	SDeferredClipVolume::BlendInfo emptyBlendInfo = { std::numeric_limits<uint8>::max(), Vec4(ZERO) };
	std::fill(volume.blendInfo, volume.blendInfo + SDeferredClipVolume::MaxBlendInfoCount, emptyBlendInfo);

	for (int i = 0; i < blendInfoCount; ++i)
	{
		volume.blendInfo[i].blendID = blendVolumes[i] ? blendVolumes[i]->GetStencilRef() : 0;
		volume.blendInfo[i].blendPlane = Vec4(blendPlanes[i].n, blendPlanes[i].d);
	}

	volume.nFlags |= IClipVolume::eClipVolumeBlend;
}

//////////////////////////////////////////////////////////////////////////

void CRenderView::AddFogVolume(const CREFogVolume* pFogVolume)
{

}

const std::vector<SFogVolumeInfo>& CRenderView::GetFogVolumes(IFogVolumeRenderNode::eFogVolumeType volumeType) const
{
	CRY_ASSERT(volumeType < IFogVolumeRenderNode::eFogVolumeType_Count);
	return m_fogVolumes[volumeType];
}

//////////////////////////////////////////////////////////////////////////

void CRenderView::AddCloudBlocker(const Vec3& pos, const Vec3& param, int32 flags)
{
	if (flags == 0)
	{
		if (m_cloudBlockers[0].size() < MaxCloudBlockerWorldSpaceNum)
		{
			SCloudBlocker blocker;
			blocker.position = pos;
			blocker.param = param;
			blocker.flags = flags;
			m_cloudBlockers[0].push_back(blocker);
		}
	}
	else
	{
		if (m_cloudBlockers[1].size() < MaxCloudBlockerScreenSpaceNum)
		{
			SCloudBlocker blocker;
			blocker.position = pos;
			blocker.param = param;
			blocker.flags = flags;
			m_cloudBlockers[1].push_back(blocker);
		}
	}
}

const std::vector<SCloudBlocker>& CRenderView::GetCloudBlockers(uint32 blockerType) const
{
	CRY_ASSERT(blockerType < CloudBlockerTypeNum);
	return m_cloudBlockers[blockerType];
}

//////////////////////////////////////////////////////////////////////////

void CRenderView::AddWaterRipple(const SWaterRippleInfo& waterRippleInfo)
{
	if (m_waterRipples.size() < SWaterRippleInfo::MaxWaterRipplesInScene)
	{
		m_waterRipples.emplace_back(waterRippleInfo);
	}
}

const std::vector<SWaterRippleInfo>& CRenderView::GetWaterRipples() const
{
	return m_waterRipples;
}

//////////////////////////////////////////////////////////////////////////
void CRenderView::AddPolygon(const SRenderPolygonDescription& poly, const SRenderingPassInfo& passInfo)
{
	}

//////////////////////////////////////////////////////////////////////////
CTexture* CRenderView::GetColorTarget() const
{
	return nullptr;
}

CTexture* CRenderView::GetDepthTarget() const
{
	return nullptr;
}


void CRenderView::InspectRenderOutput()
{
	
}

void CRenderView::ChangeRenderResolution(uint32_t renderWidth, uint32_t renderHeight, bool bForce)
{
	}

void CRenderView::UnsetRenderOutput()
{
}

//////////////////////////////////////////////////////////////////////////
template<bool shadowView, class T>
void CountRenderItems(T& permanentRenderItems, std::atomic<size_t> (&addedItems)[EFSLIST_NUM], int frustumSide = 0)
{
	size_t numItems = permanentRenderItems.size();
	assert(numItems < 128); // Sanity check, otherwise too many chunks in the mesh
	for (size_t i = 0; i < numItems; i++)
	{
		auto& RESTRICT_REFERENCE pri = permanentRenderItems[i];

		SShaderItem shaderItem;
		SRendItem::ExtractShaderItem(pri.m_sortValue, pri.m_nBatchFlags, shaderItem);

		CShaderResources* const __restrict pShaderResources = (CShaderResources*)shaderItem.m_pShaderResources;

		// Discard 0 alpha blended geometry - this should be discarded earlier on 3dengine side preferably
		const bool isInvisible = pShaderResources && pShaderResources->::CShaderResources::IsInvisible();
		if (!isInvisible)
		{
			ERenderListID renderList;
			if (shadowView)
				renderList = ERenderListID(frustumSide);
			else
				renderList = pri.m_nRenderList;

			++addedItems[renderList];
		}
	}
}

void CRenderView::AddPermanentObjectImpl(CPermanentRenderObject* pObject, const SRenderingPassInfo& passInfo)
{
	
}

//////////////////////////////////////////////////////////////////////////
void CRenderView::AddPermanentObject(CRenderObject* pObject, const SRenderingPassInfo& passInfo)
{
	
}

//////////////////////////////////////////////////////////////////////////
CRenderObject* CRenderView::AllocateTemporaryRenderObject()
{
	CRenderObject* pObj = m_tempRenderObjects.push_back_new();

	pObj->Init();
	pObj->m_pCompiledObject = nullptr;

	return pObj;
}

//////////////////////////////////////////////////////////////////////////
void CRenderView::SetViewport(const SRenderViewport& viewport)
{
	m_viewport = viewport;

	for (CCamera::EEye eye = CCamera::eEye_Left; eye != CCamera::eEye_eCount; eye = CCamera::EEye(eye + 1))
		m_viewInfo[eye].viewport = viewport;
}

//////////////////////////////////////////////////////////////////////////
const SRenderViewport& CRenderView::GetViewport() const
{
	return m_viewport;
}

//////////////////////////////////////////////////////////////////////////

void CRenderView::SetGraphicsPipeline(std::shared_ptr<CGraphicsPipeline> pipeline)
{
	
}

//////////////////////////////////////////////////////////////////////////
static inline uint32 CalculateRenderItemBatchFlags(
	SShaderItem& shaderItem, 
	CRenderObject* pObj, 
	CRenderElement* re, 
	const SRenderingPassInfo& passInfo, 
	int nAboveWater)
{
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
static inline void AddEf_HandleOldRTMask(CRenderObject* obj)
{
	
}

///////////////////////////////////////////////////////////////////////////////
static inline void AddEf_HandleForceFlags(
	int& nList, int& nAW, uint32& nBatchFlags, 
	const uint32 nShaderFlags, const uint32 nShaderFlags2, CRenderObject* obj)
{
	
}

//////////////////////////////////////////////////////////////////////////
static inline ERenderListID CalculateRenderItemList(
	const SShaderItem& shaderItem, 
	CRenderObject* pObj, 
	uint32& nBatchFlags, 
	int nList, 
	const SRenderingPassInfo& passInfo,
	int nAboveWater)
{
	return ERenderListID(0);
}

///////////////////////////////////////////////////////////////////////////////
void CRenderView::AddRenderObject(
	CRenderElement* pElem, 
	SShaderItem& shaderItem, 
	CRenderObject* pObj, 
	const SRenderingPassInfo& passInfo, 
	int nSuggestedList, int nAW)
{
}

//////////////////////////////////////////////////////////////////////////
void CRenderView::AddRenderItem(CRenderElement* pElem, CRenderObject* RESTRICT_POINTER pObj, const SShaderItem& shaderItem, ERenderListID nList, uint32 nBatchFlags, const SRenderingPassInfo& passInfo,
								SRendItemSorter sorter)
{
	
}

//////////////////////////////////////////////////////////////////////////
template<bool isConcurrent>
inline void UpdateRenderListBatchFlags(volatile uint32& listFlags, int newFlags)
{
	if (isConcurrent)
	{
		CryInterlockedExchangeOr((volatile LONG*)&listFlags, newFlags);
	}
	else
	{
		listFlags |= newFlags;
	}
}

void CRenderView::SPermanentObjectRecord::prepareForCompilation()
{
	
}

void CRenderView::PreparePermanentRenderObjectsForCompile()
{
	CRY_PROFILE_FUNCTION(PROFILE_3DENGINE);

	for (auto& permanentRenderObj : m_permanentObjects)
		permanentRenderObj.prepareForCompilation();
}

void CRenderView::ExpandPermanentRenderObjects()
{

}

//////////////////////////////////////////////////////////////////////////
void CRenderView::CompileModifiedRenderObjects()
{

}

//////////////////////////////////////////////////////////////////////////
void CRenderView::UpdateModifiedShaderItems()
{
	
}

//////////////////////////////////////////////////////////////////////////
void CRenderView::ClearTemporaryCompiledObjects()
{
	
}

CRenderView::ItemsRange CRenderView::GetItemsRange(ERenderListID renderList)
{
	return ItemsRange(0, 0);
}

CRenderView::ItemsRange CRenderView::GetShadowItemsRange(ShadowMapFrustum* pFrustum, int nFrustumSide)
{
	
	return ItemsRange(0, 0);
}

//////////////////////////////////////////////////////////////////////////
void CRenderView::Job_PostWrite()
{
	
}

void CRenderView::Job_SortRenderItemsInList(ERenderListID renderList)
{
	
}

void CRenderView::SortLights()
{
	struct CubemapCompare
	{
		bool operator()(const SRenderLight& l0, const SRenderLight& l1) const
		{
			if (l0.m_nSortPriority != l1.m_nSortPriority)
				return l0.m_nSortPriority > l1.m_nSortPriority;

			if (l0.m_fRadius == l1.m_fRadius)  // Sort by entity id to guarantee deterministic order across frames
				return l0.m_nEntityId > l1.m_nEntityId;

			return l0.m_fRadius < l1.m_fRadius;
		}
	};

}

//////////////////////////////////////////////////////////////////////////
CRenderView* CRenderView::GetShadowsView(ShadowMapFrustum* pFrustum)
{
	assert(0); // Should not be used like this
	return 0;
}


//////////////////////////////////////////////////////////////////////////
void CRenderView::PostWriteShadowViews()
{

}

//////////////////////////////////////////////////////////////////////////
void CRenderView::PrepareShadowViews()
{
	
}

//////////////////////////////////////////////////////////////////////////
void CRenderView::DrawCompiledRenderItems(const SGraphicsPipelinePassContext& passContext) const
{
	
}

//////////////////////////////////////////////////////////////////////////
void CRenderView::CheckAndScheduleForUpdate(const SShaderItem& shaderItem)
{
	
}

// Fog Volume indices use the same convention as Light Volume indices: 0 is invalid, 1 is first valid.
//////////////////////////////////////////////////////////////////////////
uint16 CRenderView::PushFogVolumeContribution(
	const ColorF& fogVolumeContrib, const SRenderingPassInfo& passInfo)
{
	int numFogVolumes = CryInterlockedIncrement(&m_numFogVolumes);
	const size_t maxElems((1 << (sizeof(uint16) * 8)) - 1);

	CRY_ASSERT(numFogVolumes < maxElems);
	if (numFogVolumes >= maxElems)
		return 0;

	uint32 nIndex = ~0;
	m_fogVolumeContributions.push_back(fogVolumeContrib, nIndex);
	return static_cast<uint16>(nIndex + 1);
}

//////////////////////////////////////////////////////////////////////////
void CRenderView::GetFogVolumeContribution(uint16 idx, ColorF& rColor) const
{
	rColor = idx ? m_fogVolumeContributions[idx - 1] : ColorF(0.0f, 0.0f, 0.0f, 1.0f);
}

//////////////////////////////////////////////////////////////////////////
void CRenderView::SetTargetClearColor(const ColorF& color, bool bEnableClear)
{
	m_targetClearColor = color;
	m_bClearTarget = bEnableClear;
}


SRenderViewInfo::SRenderViewInfo()
	: pCamera(nullptr)
	, pFrustumPlanes(nullptr)
	, cameraOrigin(0)
	, cameraVX(0)
	, cameraVY(0)
	, cameraVZ(0)
	, nearClipPlane(0)
	, farClipPlane(1)
	, cameraProjZeroMatrix(IDENTITY)
	, cameraProjMatrix(IDENTITY)
	, cameraProjNearestMatrix(IDENTITY)
	, projMatrix(IDENTITY)
	, unjitteredProjMatrix(IDENTITY)
	, viewMatrix(IDENTITY)
	, invCameraProjMatrix(IDENTITY)
	, invViewMatrix(IDENTITY)
	, prevCameraMatrix(IDENTITY)
	, prevCameraProjMatrix(IDENTITY)
	, prevCameraProjNearestMatrix(IDENTITY)
	, m_frustumCorners {ZERO, ZERO, ZERO, ZERO}
	, downscaleFactor(1)
	, flags(eFlags_None)
{
}

//////////////////////////////////////////////////////////////////////////
void SRenderViewInfo::SetCamera(const CCamera& cam, const CCamera& previousCam, Vec2 subpixelShift, float drawNearestFov, float drawNearestFarPlane)
{
	
}

//////////////////////////////////////////////////////////////////////////
void SRenderViewInfo::ExtractViewMatrices(
	const CCamera& cam, Matrix44& view, Matrix44& viewZero, Matrix44& invView) const
{
	
}

//////////////////////////////////////////////////////////////////////////
float SRenderViewInfo::WorldToCameraZ(const Vec3& wP) const
{
	Vec3 sP(wP - cameraOrigin);
	float zdist = cameraVZ | sP;
	return zdist;
}

//////////////////////////////////////////////////////////////////////////

Matrix44 SRenderViewInfo::GetReprojection() const
{
	assert(false);
	Matrix44_tpl<f64> matReprojection64;
	return (Matrix44)matReprojection64;
}

Matrix44 SRenderViewInfo::GetNearestProjection(float nearestFOV, float farPlane, Vec2 subpixelShift) const
{
	CRY_ASSERT(false);

	Matrix44A result;
	return result;
}

TRect_tpl<uint16> CRenderView::ComputeResolveViewport(const AABB& aabb, bool forceFullscreenUpdate) const
{
	TRect_tpl<uint16> resolveViewport;

	return resolveViewport;
}
