#ifndef OGBulletDeleterOperator_h__
#define OGBulletDeleterOperator_h__

#include "OGBulletOperator.h"

namespace Orphigine
{
	class BulletEventSystem;
	class BulletDeleterOperator : public BulletOperator
	{
	public:
		BulletDeleterOperator(BulletEventSystem* eventSystem);
		virtual ~BulletDeleterOperator();

		virtual void operateBulletEventSystem(Real timeElapsed);

	protected:
		bool				m_isOperated;
	private:
	};
}
#endif // OGBulletDeleterOperator_h__
