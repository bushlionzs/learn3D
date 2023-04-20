#ifndef OGBulletForceOperatorFactory_h__
#define OGBulletForceOperatorFactory_h__

#include "OGBulletForceOperator.h"
#include "OGBulletOperatorFactory.h"

namespace Orphigine
{
	class BulletForceOperatorFactory : public BulletOperatorFactory
	{
	public:
		virtual String getName() const
		{
			return "force";
		}

		virtual BulletOperator*	createOperator(BulletEventSystem* eventSystem)
		{
			BulletForceOperator* tmpOperator = OGRE_NEW BulletForceOperator(eventSystem);
			m_operators.push_back(tmpOperator);
			return tmpOperator;
		}
	protected:
	private:
	};
}
#endif // OGBulletForceOperatorFactory_h__