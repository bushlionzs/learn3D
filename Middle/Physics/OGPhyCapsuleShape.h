#ifndef OGPhyCapsuleShape_h__
#define OGPhyCapsuleShape_h__

#include "OGPhyShape.h"

namespace Orphigine
{
	class PhyCapsuleShape : public PhyShape
	{
	public:
		PhyCapsuleShape(Real radius,Real height);
		virtual ~PhyCapsuleShape();

		Real				getRadius() const;
		void					setRadius(Real val);

		Real				getHeight() const;
		void					setHeight(Real val);
	protected:
		Real					m_radius;
		Real					m_height;

	private:
	};
}
#endif // OGPhyCapsuleShape_h__