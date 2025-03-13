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

