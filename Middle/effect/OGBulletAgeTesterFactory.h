#ifndef OGBulletAgeTesterFactory_h__
#define OGBulletAgeTesterFactory_h__

#include "OGBulletOperatorFactory.h"
#include "OGBulletAgeTester.h"

namespace Orphigine
{
	class BulletAgeTesterFactory : public BulletOperatorFactory
	{
	public:
		virtual String getName() const
		{
			return "age";
		}

		virtual BulletOperator*	createOperator(BulletEventSystem* eventSystem)
		{
			BulletAgeTester* tmpOperator = OGRE_NEW BulletAgeTester(eventSystem);
			m_operators.push_back(tmpOperator);
			return tmpOperator;
		}
	protected:
	private:
	};
}

#endif // OGBulletAgeTesterFactory_h__
