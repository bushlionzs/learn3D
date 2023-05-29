#ifndef OGBulletHeightFieldCollisionTesterFactory_h__
#define OGBulletHeightFieldCollisionTesterFactory_h__

#include "OGBulletOperatorFactory.h"
#include "OGBulletHeightFieldCollisionTester.h"

namespace Orphigine
{
	class BulletHeightFieldTesterFactory : public BulletOperatorFactory
	{
	public:
		virtual String getName() const
		{
			return "heightfieldcollision";
		}

		virtual BulletOperator*	createOperator(BulletEventSystem* eventSystem)
		{
			BulletHeightFieldCollisionTester* tmpOperator = OGRE_NEW BulletHeightFieldCollisionTester(eventSystem);
			m_operators.push_back(tmpOperator);
			return tmpOperator;
		}
	protected:
	private:
	};
}
#endif // OGBulletHeightFieldCollisionTesterFactory_h__
