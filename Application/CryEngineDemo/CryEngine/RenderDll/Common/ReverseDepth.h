// Copyright 2015-2021 Crytek GmbH / Crytek Group. All rights reserved.

#pragma once

struct ReverseDepthHelper
{
	static Matrix44 Convert(const Matrix44& m)
	{
		Matrix44 result = m;
		result.m02 = -m.m02 + m.m03;
		result.m12 = -m.m12 + m.m13;
		result.m22 = -m.m22 + m.m23;
		result.m32 = -m.m32 + m.m33;

		return result;
	}

	static D3DViewPort Convert(const D3DViewPort& vp)
	{
		D3DViewPort result = vp;
		result.MinDepth = 1.0f - vp.MaxDepth;
		result.MaxDepth = 1.0f - vp.MinDepth;

		return result;
	}

	static uint64 ConvertDepthFunc(uint64 nState)
	{
		uint64 nDepthFuncRemapped = nState & GS_DEPTHFUNC_MASK;

		switch (nState & GS_DEPTHFUNC_MASK)
		{
		case GS_DEPTHFUNC_LESS:
			nDepthFuncRemapped = GS_DEPTHFUNC_GREAT;
			break;

		case GS_DEPTHFUNC_LEQUAL:
			nDepthFuncRemapped = GS_DEPTHFUNC_GEQUAL;
			break;

		case GS_DEPTHFUNC_GREAT:
			nDepthFuncRemapped = GS_DEPTHFUNC_LESS;
			break;

		case GS_DEPTHFUNC_GEQUAL:
			nDepthFuncRemapped = GS_DEPTHFUNC_LEQUAL;
			break;
		}

		nState &= ~GS_DEPTHFUNC_MASK;
		nState |= nDepthFuncRemapped;

		return nState;
	}
};
