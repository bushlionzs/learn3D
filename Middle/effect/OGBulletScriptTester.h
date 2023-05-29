#ifndef OGBulletScriptTester_h__
#define OGBulletScriptTester_h__

#include "OGBulletTester.h"

namespace Orphigine
{
	class BulletEventSystem;

	class BulletScriptTester : public BulletTester
	{
	public:
		BulletScriptTester(BulletEventSystem* eventSystem);
		virtual ~BulletScriptTester();

		virtual void operateBulletEventSystem(Real timeElapsed);

	protected:

	private:
	};
}
#endif // OGBulletScriptTester_h__