#pragma once

#include <d3d11_1.h>
#include <wrl.h>
class Dx11Shader;
class Dx11RenderableData;
namespace Ogre
{
	class Material;
	class Renderable;
}

class Dx11Pass
{
public:
	Ogre::Material* _mat;
	Dx11Shader* _shader;
	Ogre::Renderable* _render;
	Dx11RenderableData* _renderData;
};