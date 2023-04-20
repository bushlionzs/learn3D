/*
-----------------------------------------------------------------------------
This source file is part of OGRE
(Object-oriented Graphics Rendering Engine)
For the latest info, see http://www.ogre3d.org/

Copyright (c) 2000-2014 Torus Knot Software Ltd

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
-----------------------------------------------------------------------------
*/
#ifndef __D3D12MAPPINGS_H__
#define __D3D12MAPPINGS_H__

#include "d3dx12.h"
#include "RenderSystem.h"
#include "OgreBlendMode.h"
#include "OgreCommon.h"
#include "OgreHardwareVertexBuffer.h"

namespace Ogre 
{
    class  D3D12Mappings
	{
	public:

		/// return a D3D11 equivalent for a Ogre SceneBlendFactor value
		static D3D12_BLEND get(SceneBlendFactor sbf, bool forAlpha);
		/// return a D3D11 equivalent for a Ogre SceneBlendOperation value
		static D3D12_BLEND_OP get(SceneBlendOperation sbo);
		/// return a D3D11 equivalent for a Ogre CompareFunction value
		static D3D12_COMPARISON_FUNC get(CompareFunction cf);
		

		static LPCSTR getSemanticName(VertexElementSemantic sem);

		static PixelFormat _getClosestSupportedPF(PixelFormat ogrePF);

		/// utility method, convert Ogre pixel format to D3D11 pixel format
		static DXGI_FORMAT _getPF(PixelFormat ogrePF);
		/// utility method, optionally maps plain format to _SRGB counterparts
		static DXGI_FORMAT _getGammaFormat(DXGI_FORMAT format, bool appendSRGB);
	};
}
#endif
