#pragma once

#include "pass.h"
#include "renderUtil.h"

class SceneRenderPass : public PassBase
{
	struct SceneFrameData
	{
		filament::backend::Handle<filament::backend::HwBufferObject> passBufferHandle;
		std::vector<filament::backend::Handle<filament::backend::HwBufferObject>> shadowBufferList;
		filament::backend::Handle<filament::backend::HwBufferObject> cascadeBufferHandle;
	};
public:
	SceneRenderPass(RenderPassInput& input);

	virtual void execute(RenderContext& context);

	void drawShadow(RenderContext& context);

	void draw(RenderContext& context);

	virtual void update(RenderContext& context);
private:
	void updateFrameData(
		Ogre::ICamera* camera, 
		Ogre::Light* light,
		RenderContext& context);
	void updateCascadeMatrices(RenderContext& context);
	void initObject(uint32_t frameIndex, Ogre::Renderable* r, RenderContext& context);
	void bindObject(uint32_t frameIndex, Ogre::Renderable* r, RenderContext& context);
	void updateObject(uint32_t frameIndex, Ogre::Renderable* r, RenderContext& context);
	void drawObject(uint32_t frameIndex, Ogre::Renderable* r, RenderContext& context);
private:
	RenderPassInput mPassInput;
	RenderPassInfo mRenderPassInfo;
	FrameConstantBuffer mFrameConstantBuffer;
	std::vector<SceneFrameData> mFrameData;

	RenderSystem* rs;

	filament::backend::Handle<filament::backend::HwProgram> shadowProgramHandle;
};