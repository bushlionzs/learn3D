#ifndef OGBulletSpawnOperatorFactory_h__
#define OGBulletSpawnOperatorFactory_h__

#include "OGBulletSpawnOperator.h"
#include "OGBulletOperatorFactory.h"

namespace Orphigine
{
	class BulletSpawnOperatorFactory : public BulletOperatorFactory
	{
	public:
		virtual String getName() const
		{
			return "spawn";
		}

		virtual BulletOperator*	createOperator(BulletEventSystem* eventSystem)
		{
			BulletSpawnOperator* tmpOperator = OGRE_NEW BulletSpawnOperator(eventSystem);
			m_operators.push_back(tmpOperator);
			return tmpOperator;
		}
	protected:
	private:
	};
}
#endif // OGBulletSpawnOperatorFactory_h__