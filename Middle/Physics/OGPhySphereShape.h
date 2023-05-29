#ifndef OGPhySphereShape_h__
#define OGPhySphereShape_h__


#include "OGPhyShape.h"

namespace Orphigine
{
	class PhySphereShape : public PhyShape
	{
	public:
		PhySphereShape(Real radius);
		virtual ~PhySphereShape();

		class CmdRadius : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
		};

		Real				getRadius() const;
		void					setRadius(Real val);

		static CmdRadius		ms_radiusCmd;
	protected:
		Real					m_radius;

	private:
	};
}
#endif // OGPhySphereShape_h__
