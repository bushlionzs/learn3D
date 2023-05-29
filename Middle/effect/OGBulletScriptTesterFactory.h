#ifndef OGBulletScriptTesterFactory_h__
#define OGBulletScriptTesterFactory_h__

#include "OGBulletOperatorFactory.h"
#include "OGBulletScriptTester.h"

namespace Orphigine
{
	class BulletScriptTesterFactory : public BulletOperatorFactory
	{
	public:
		virtual String getName() const
		{
			return "script";
		}

		virtual BulletOperator*	createOperator(BulletEventSystem* eventSystem)
		{
			BulletScriptTester* tmpOperator = OGRE_NEW BulletScriptTester(eventSystem);
			m_operators.push_back(tmpOperator);
			return tmpOperator;
		}
	protected:
	private:
	};
}
#endif // OGBulletScriptTesterFactory_h__
