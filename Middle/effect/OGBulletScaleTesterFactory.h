#ifndef OGBulletScaleTesterFactory_h__
#define OGBulletScaleTesterFactory_h__

#include "OGBulletOperatorFactory.h"
#include "OGBulletScaleTester.h"

namespace Orphigine
{
	class BulletScaleTesterFactory : public BulletOperatorFactory
	{
	public:
		virtual String getName() const
		{
			return "scale";
		}

		virtual BulletOperator*	createOperator(BulletEventSystem* eventSystem)
		{
			BulletScaleTester* tmpOperator = OGRE_NEW BulletScaleTester(eventSystem);
			m_operators.push_back(tmpOperator);
			return tmpOperator;
		}
	protected:
	private:
	};
}
#endif // OGBulletScaleTesterFactory_h__
