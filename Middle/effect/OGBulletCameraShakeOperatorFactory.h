#ifndef OGBulletCameraShakeOperatorFactory_h__
#define OGBulletCameraShakeOperatorFactory_h__

#include "OGBulletCameraShakeOperator.h"
#include "OGBulletOperatorFactory.h"

namespace Orphigine
{
	class BulletCameraShakeOperatorFactory : public BulletOperatorFactory
	{
	public:
		virtual String getName() const
		{
			return "camerashake";
		}

		virtual BulletOperator*	createOperator(BulletEventSystem* eventSystem)
		{
			BulletCameraShakeOperator* tmpOperator = OGRE_NEW BulletCameraShakeOperator(eventSystem);
			m_operators.push_back(tmpOperator);
			return tmpOperator;
		}
	protected:
	private:
	};
}
#endif // OGBulletCameraShakeOperatorFactory_h__