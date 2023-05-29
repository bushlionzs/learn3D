#pragma once

#include "OgreRenderable.h"

namespace MyGUI
{
	class OgreVertexBuffer;
	class OgreTexture;
	class MyGUIRender: public Ogre::Renderable
	{
	public:
		MyGUIRender();
		~MyGUIRender();
		void update(OgreVertexBuffer* vertexBuffer, OgreTexture* tex);

		virtual VertexData* getVertexData();
		virtual IndexData* getIndexData();
		virtual IndexDataView* getIndexView();

		const Ogre::Matrix4& getModelMatrix();
	private:
		OgreVertexBuffer* mVertexBuffer;
		OgreTexture* mTexture;
	};
}