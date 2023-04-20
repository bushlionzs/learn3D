#ifndef OGBulletFindTargetTesterFactory_h__
#define OGBulletFindTargetTesterFactory_h__

#include "OGBulletOperatorFactory.h"
#include "OGBulletFindTargetTester.h"

namespace Orphigine
{
	class BulletFindTargetTesterFactory : public BulletOperatorFactory
	{
	public:
		virtual String getName() const
		{
			return "findtarget";
		}

		virtual BulletOperator*	createOperator(BulletEventSystem* eventSystem)
		{
			BulletFindTargetTester* tmpOperator = OGRE_NEW BulletFindTargetTester(eventSystem);
			m_operators.push_back(tmpOperator);
			return tmpOperator;
		}
	protected:
	private:
	};
}
#endif // OGBulletFindTargetTesterFactory_h__
