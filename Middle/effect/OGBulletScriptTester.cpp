#include "OgreHeader.h"
#include "OGBulletScriptTester.h"

namespace Orphigine
{
	BulletScriptTester::BulletScriptTester( BulletEventSystem* eventSystem )
	{
		m_type = "script";
		m_parent = eventSystem;

		if (initBaseParamters("scale"))
		{

		}
	}

	BulletScriptTester::~BulletScriptTester()
	{

	}

	void BulletScriptTester::operateBulletEventSystem(Real timeElapsed)
	{

	}
}