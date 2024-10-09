#include "OgreHeader.h"
#include "OGBasicRenderable.h"
#include <OgreNode.h>
#include "OgreSceneNode.h"
#include <OgreSceneNode.h>
#include <OgreMaterial.h>
#include <OgreMaterialManager.h>
#include <OgreMoveObject.h>

namespace Orphigine 
{

	GeneralRenderable::GeneralRenderable(Ogre::MoveObject *parent): Renderable()
		, mParent(parent), mRenderOp()
	{
	}
	GeneralRenderable::~GeneralRenderable()
	{
	}
	
	const std::shared_ptr<Material>& GeneralRenderable::getMaterial()
	{
		return mMaterial;
	}
	void GeneralRenderable::getRenderOperation(Ogre::RenderOperation& op)
	{
		op = mRenderOp;
	}

	const Ogre::Matrix4& GeneralRenderable::getModelMatrix()
	{
		const Ogre::Matrix4& m =  mParent->_getParentNodeFullTransform();

		return m;
	}

	void GeneralRenderable::getWorldTransforms(Ogre::Matrix4* xform) const
	{
		*xform = mParent->_getParentNodeFullTransform();
	}
	const Ogre::Quaternion&	GeneralRenderable::getWorldOrientation(void) const
	{
		Ogre::Node* n = mParent->getParentSceneNode();
		assert(n);
		return n->_getDerivedOrientation();
	}
	const Ogre::Vector3& GeneralRenderable::getWorldPosition(void) const
	{
		Ogre::Node* n = mParent->getParentSceneNode();
		assert(n);
		return n->_getDerivedPosition();
	}
	Ogre::Real GeneralRenderable::getSquaredViewDepth(const Ogre::Camera* camera) const
	{
		Ogre::Node* n = mParent->getParentSceneNode();
		assert(n);
		return n->getSquaredViewDepth(camera);
	}

	VertexData* GeneralRenderable::getVertexData()
	{
		return mRenderOp.vertexData;
	}

	IndexData* GeneralRenderable::getIndexData()
	{
		return mRenderOp.indexData;
	}

	IndexDataView* GeneralRenderable::getIndexView()
	{
		mIndexDataView.mBaseVertexLocation = 0;
		mIndexDataView.mIndexLocation = 0;
		mIndexDataView.mIndexCount = mRenderOp.indexData->getIndexCount();
		return &mIndexDataView;
	}
}
