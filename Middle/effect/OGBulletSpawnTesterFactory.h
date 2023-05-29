#ifndef OGBulletSpawnTesterFactory_h__
#define OGBulletSpawnTesterFactory_h__

#include "OGBulletOperatorFactory.h"
#include "OGBulletSpawnTester.h"

namespace Orphigine
{
	class BulletSpawnTesterFactory : public BulletOperatorFactory
	{
	public:
		virtual String getName() const
		{
			return "SpawnTester";
		}

		virtual BulletOperator*	createOperator(BulletEventSystem* eventSystem)
		{
			BulletSpawnTester* tmpOperator = OGRE_NEW BulletSpawnTester(eventSystem);
			m_operators.push_back(tmpOperator);
			return tmpOperator;
		}
	protected:
	private:
	};
}
#endif // OGBulletSpawnTesterFactory_h__
