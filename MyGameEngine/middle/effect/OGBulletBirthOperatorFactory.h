#ifndef OGBulletBirthOperatorFactory_h__
#define OGBulletBirthOperatorFactory_h__

#include "OGBulletBirthOperator.h"
#include "OGBulletOperatorFactory.h"

namespace Orphigine
{
	class BulletBirthOperatorFactory : public BulletOperatorFactory
	{
	public:
		virtual String getName() const
		{
			return "birth";
		}

		virtual BulletOperator*	createOperator(BulletEventSystem* eventSystem)
		{
			BulletBirthOperator* tmpOperator = OGRE_NEW BulletBirthOperator(eventSystem);
			m_operators.push_back(tmpOperator);
			return tmpOperator;
		}
	protected:
	private:
	};
}
#endif // OGBulletBirthOperatorFactory_h__