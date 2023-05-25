#ifndef OGPhyConvexCullShape_h__
#define OGPhyConvexCullShape_h__

#include "OGPhyShape.h"
#include "OgreVector3.h"

namespace Orphigine
{
	class PhyConvexHullShape : public PhyShape
	{
	public:
		PhyConvexHullShape(const std::vector<Ogre::Vector3>& planes );
		virtual ~PhyConvexHullShape();

	protected:
		void			_createConvexHullShapeImpl(const std::vector<Ogre::Vector3>& planes);
	private:
	};
}
#endif // OGPhyConvexCullShape_h__
