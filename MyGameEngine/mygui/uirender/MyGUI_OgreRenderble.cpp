#include <OgreHeader.h>
#include "MyGUI_OgreRenderable.h"
#include "MyGUI_OgreVertexBuffer.h"
#include "MyGUI_OgreTexture.h"
#include "OgreRenderOperation.h"
#include "OgreMaterial.h"
#include "OgreTextureUnit.h"

namespace MyGUI
{
	MyGUIRender::MyGUIRender()
	{
		mMaterial = std::make_shared<Ogre::Material>("");
		mMaterial->addTexture("white1x1.dds");
		ShaderInfo sInfo;
		sInfo.shaderName = "mygui";
		mMaterial->addShader(sInfo);
		Ogre::ColourBlendState mBlendState;
		mBlendState.sourceFactor = Ogre::SBF_SOURCE_ALPHA;
		mBlendState.destFactor = Ogre::SBF_ONE_MINUS_SOURCE_ALPHA;
		mBlendState.sourceFactorAlpha = Ogre::SBF_SOURCE_ALPHA;
		mBlendState.destFactorAlpha = Ogre::SBF_ONE_MINUS_SOURCE_ALPHA;
		mMaterial->setBlendState(mBlendState);
		mMaterial->setWriteDepth(false);
	}

	MyGUIRender::~MyGUIRender()
	{

	}

	void MyGUIRender::update(OgreVertexBuffer* vertexBuffer, OgreTexture* tex)
	{
		auto unit = mMaterial->getTextureUnit(0);
		unit->setTexture(tex->getOgreTexture());
		mVertexBuffer = vertexBuffer;
		mTexture = tex;
	}

	VertexData* MyGUIRender::getVertexData()
	{
		return mVertexBuffer->getRenderOperation()->vertexData;
	}

	IndexData* MyGUIRender::getIndexData()
	{
		return nullptr;
	}

	IndexDataView* MyGUIRender::getIndexView()
	{
		return nullptr;
	}

	const Ogre::Matrix4& MyGUIRender::getModelMatrix()
	{
		return mWorld;
	}
}