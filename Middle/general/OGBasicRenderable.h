#ifndef OGRENDERABLE_H
#define OGRENDERABLE_H

#include <OgreRenderable.h>
#include <OgreRenderOperation.h>

namespace Orphigine 
{

	class GeneralRenderable : public Ogre::Renderable
	{
	public:
		GeneralRenderable(Ogre::MoveObject *parent);
		virtual ~GeneralRenderable();
		//÷ÿ‘ÿ∫Ø ˝///////////////////////////////////////////////////
		virtual const std::shared_ptr<Material>& getMaterial();
		virtual void						getRenderOperation(Ogre::RenderOperation& op);

		virtual const Ogre::Matrix4& getModelMatrix();
		virtual void						getWorldTransforms(Ogre::Matrix4* xform) const;
		virtual const Ogre::Quaternion&		getWorldOrientation(void) const;
		virtual const Ogre::Vector3&		getWorldPosition(void) const;
		virtual Ogre::Real					getSquaredViewDepth(const Ogre::Camera* camra) const;
		virtual VertexData* getVertexData();

		virtual IndexData* getIndexData();

		virtual IndexDataView* getIndexView();

		Ogre::RenderOperation	mRenderOp;
		IndexDataView           mIndexDataView;
	protected:
		Ogre::MoveObject*	mParent;
	};

}

#endif // OGRENDERABLE_H
