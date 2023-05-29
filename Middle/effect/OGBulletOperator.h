#ifndef OGBulletOperator_h__
#define OGBulletOperator_h__

#include "OgreStringInterface.h"

namespace Orphigine
{
	class BulletEventSystem;

	class BulletOperator : public Ogre::StringInterface
	{
	public:
		virtual void operateBulletEventSystem(Real timeElapsed) = 0;

		const String& getType() const { return m_type; }

		bool				 isLogicOperator() const { return m_isLogicOperator;}

		virtual ~BulletOperator() {}
	protected:
		BulletOperator() : m_type(""),m_parent(NULL),m_isLogicOperator(false) {}

	protected:
		String					m_type;
		BulletEventSystem*		m_parent;
		bool					m_isLogicOperator;
	private:
	};
}
#endif // OGBulletOperator_h__