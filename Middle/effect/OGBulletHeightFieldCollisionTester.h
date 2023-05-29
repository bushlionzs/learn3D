#ifndef OGBulletHeightFieldCollisionTester_h__
#define OGBulletHeightFieldCollisionTester_h__

#include "OGBulletTester.h"
#include "OgreSceneQuery.h"

namespace Orphigine
{
	class BulletEventSystem;
	class BulletHeightFieldCollisionTester : public BulletTester
	{
	public:
		BulletHeightFieldCollisionTester(BulletEventSystem* eventSystem);
		virtual ~BulletHeightFieldCollisionTester();

		virtual void operateBulletEventSystem(Real timeElapsed);

		class CmdLessThan : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
		};

		const Real& getLessThan() const;
		void setLessThan(const Real& val);

		static CmdLessThan ms_lessThanCmd;

	protected:
		Real					m_lessThan;
		Ogre::RaySceneQuery*	m_rayQuery;
	private:
	};
}
#endif // OGBulletHeightFieldCollisionTester_h__