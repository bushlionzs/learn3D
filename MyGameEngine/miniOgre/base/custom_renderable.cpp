#include "OgreHeader.h"
#include "custom_renderable.h"
#include "vertex_data.h"
#include "index_data.h"
#include "engine_struct.h"
CustomRenderable::CustomRenderable(VertexData* vertexData, IndexData* indexData)
{
    mLocal = Ogre::Matrix4::IDENTITY;
    mVertexData = vertexData;
    mIndexData = indexData;
    mIndexDataView = new IndexDataView;
}

CustomRenderable::~CustomRenderable()
{

}

VertexData* CustomRenderable::getVertexData()
{
    return mVertexData;
}

IndexData* CustomRenderable::getIndexData()
{
    return mIndexData;
}

IndexDataView* CustomRenderable::getIndexView()
{
    return mIndexDataView;
}

const Ogre::Matrix4& CustomRenderable::getModelMatrix()
{
    return mLocal;
}