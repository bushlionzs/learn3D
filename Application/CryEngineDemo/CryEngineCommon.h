#pragma once

//#include <d3d11.h>
#include <stdint.h>

enum ERenderPrimitiveType : int16_t
{
	eptUnknown = -1,
	eptTriangleList = 0,
	eptTriangleStrip,
	eptLineList,
	eptLineStrip,
	eptPointList,
	ept1ControlPointPatchList,
	ept2ControlPointPatchList,
	ept3ControlPointPatchList,
	ept4ControlPointPatchList,

	// non-real primitives, used for logical batching
	eptHWSkinGroups = 0x3f
};

enum EBatchFlags
{
	FB_GENERAL = 0x1,
	FB_TRANSPARENT = 0x2,
	// UNUSED          = 0x4,
	FB_Z = 0x8,
	FB_BELOW_WATER = 0x10,
	FB_ZPREPASS = 0x20,
	FB_PREPROCESS = 0x40,
	FB_MOTIONBLUR = 0x80,
	FB_POST_3D_RENDER = 0x100,
	// UNUSED          = 0x200,
	FB_COMPILED_OBJECT = 0x400,
	FB_CUSTOM_RENDER = 0x800,
	FB_RESOLVE_FULL = 0x1000,
	FB_LAYER_EFFECT = 0x2000,
	FB_WATER_REFL = 0x4000,
	FB_WATER_CAUSTIC = 0x8000,
	// UNUSED          = 0x10000,
	FB_TILED_FORWARD = 0x20000,
	FB_REFRACTION = 0x40000,
	FB_EYE_OVERLAY = 0x80000,

	FB_MASK = 0xfffff //! FB flags cannot exceed 0xfffff
};