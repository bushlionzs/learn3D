#pragma once
#include "OgreRenderable.h"


class CustomRenderable : public Renderable
{
public:
	CustomRenderable(VertexData* vertexData, IndexData* indexData);
	~CustomRenderable();

    virtual VertexData* getVertexData();
    virtual IndexData* getIndexData();
	virtual IndexDataView* getIndexView();
	const Ogre::Matrix4& getModelMatrix();
	void prepare();
private:
	VertexData* mVertexData;
	IndexData*  mIndexData;
	IndexDataView* mIndexDataView;

	Ogre::Matrix4 mLocal;
};