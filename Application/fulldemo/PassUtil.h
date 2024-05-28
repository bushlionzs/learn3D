#pragma once

#include <filament/DriverEnums.h>
#include <fg/FrameGraphId.h>
#include <fg/FrameGraphTexture.h>
#include <filament/FEngine.h>

using namespace filament;
using namespace filament::backend;
class PassUtil
{
public:
	struct PassConfig
	{
		Ogre::SceneManager* scene;
		Ogre::Camera* cam;
		FView* view;
		backend::TextureFormat hdrFormat;
		// MSAA sample count
		uint8_t msaa = 1;
		// Clear flags
		backend::TargetBufferFlags clearFlags = backend::TargetBufferFlags::NONE;
		// Clear color
		math::float4 clearColor = {};
		// Clear stencil
		uint8_t clearStencil = 0u;
	};

	static FrameGraphId<FrameGraphTexture> colorPass(
		FrameGraph& fg, const char* name, Engine& engine, FView const& view,
		FrameGraphTexture::Descriptor const& colorBufferDesc,
		PassConfig const& config) noexcept;

	static FrameGraphId<FrameGraphTexture> renderTexturePass(
		FrameGraph& fg, const char* name, Engine& engine,
		FrameGraphTexture::Descriptor const& colorBufferDesc,
		PassConfig const& config) noexcept;

	static FrameGraphId<FrameGraphTexture> guiPass(
		FrameGraph& fg, const char* name, Engine& engine, FView const& view,
		FrameGraphTexture::Descriptor const& colorBufferDesc,
		PassConfig const& config) noexcept;
};