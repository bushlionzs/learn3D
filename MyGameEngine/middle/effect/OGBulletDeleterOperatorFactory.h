#ifndef OGBulletDeleterOperatorFactory_h__
#define OGBulletDeleterOperatorFactory_h__

#include "OGBulletOperatorFactory.h"
#include "OGBulletDeleterOperator.h"

namespace Orphigine
{
	class BulletDeleterOperatorFactory : public BulletOperatorFactory
	{
	public:
		virtual String getName() const
		{
			return "deleter";
		}

		virtual BulletOperator*	createOperator(BulletEventSystem* eventSystem)
		{
			BulletDeleterOperator* tmpOperator = OGRE_NEW BulletDeleterOperator(eventSystem);
			m_operators.push_back(tmpOperator);
			return tmpOperator;
		}
	protected:
	private:
	};
}
#endif // OGBulletDeleterOperatorFactory_h__
