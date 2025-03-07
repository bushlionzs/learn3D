#include "stdafx.h"
#include <CryCore/BaseTypes.h>
#include <CryCore/Common_TypeInfo.h>
#include <Cry3DEngine/IIndexedMesh_info.h>
#include <Cry3DEngine/CGF/CGFContent_info.h>

#include <CryPhysics/primitives.h>
using namespace primitives;
#include <CryEngine/CryPhysics/bvtree.h>


#include <CryEngine/Cry3DEngine/terrain_sector_info.h>
#include <CryEngine/Cry3DEngine/SkyLightNishita_info.h>
#include <../CryAction/PlayerProfiles/RichSaveGameTypes_info.h>
#include <CryPhysics/primitives_info.h>
#include "aabbtree_info.h"
#include "obbtree_info.h"
#include "geoman_info.h"
AUTO_TYPE_INFO(EERType);
STRUCT_INFO_BEGIN(SImageSubInfo)
VAR_INFO(nDummy)
VAR_INFO(nDim)
VAR_INFO(fTilingIn)
VAR_INFO(fTiling)
VAR_INFO(fSpecularAmount)
VAR_INFO(nSortOrder)
STRUCT_INFO_END(SImageSubInfo)

STRUCT_INFO_BEGIN(SImageInfo)
VAR_INFO(baseInfo)
VAR_INFO(detailInfo)
VAR_INFO(szDetMatName)
VAR_INFO(arrTextureId)
VAR_INFO(nPhysSurfaceType)
VAR_INFO(szBaseTexName)
VAR_INFO(fUseRemeshing)
VAR_INFO(layerFilterColor)
VAR_INFO(nLayerId)
VAR_INFO(fBr)
STRUCT_INFO_END(SImageInfo)

TYPE_INFO_PLAIN(primitives::getHeightCallback)
TYPE_INFO_PLAIN(primitives::getSurfTypeCallback)
void test()
{

}