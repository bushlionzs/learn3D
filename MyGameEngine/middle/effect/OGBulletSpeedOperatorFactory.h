#ifndef OGBulletSpeedOperatorFactory_h__
#define OGBulletSpeedOperatorFactory_h__


#include "OGBulletSpeedOperator.h"
#include "OGBulletOperatorFactory.h"

namespace Orphigine
{
	class BulletSpeedOperatorFactory : public BulletOperatorFactory
	{
	public:
		virtual String getName() const
		{
			return "speed";
		}

		virtual BulletOperator*	createOperator(BulletEventSystem* eventSystem)
		{
			BulletSpeedOperator* tmpOperator = OGRE_NEW BulletSpeedOperator(eventSystem);
			m_operators.push_back(tmpOperator);
			return tmpOperator;
		}
	protected:
	private:
	};
}
#endif // OGBulletSpeedOperatorFactory_h__