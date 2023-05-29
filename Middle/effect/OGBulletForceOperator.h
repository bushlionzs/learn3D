#ifndef OGBulletForceOperator_h__
#define OGBulletForceOperator_h__

#include "OGBulletOperator.h"

namespace Orphigine
{
	class BulletEventSystem;
	class BulletForceOperator : public BulletOperator
	{
	public:
		BulletForceOperator(BulletEventSystem* eventSystem);
		virtual ~BulletForceOperator();

		virtual void operateBulletEventSystem(Real timeElapsed);

		class CmdForceVector : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
		};

		const Ogre::Vector3& getForceVector() const;
		void setForceVector(const Ogre::Vector3& val);

		static CmdForceVector ms_forceVectorCmd;
	protected:
		bool				m_isOperated;
		Ogre::Vector3		m_forceVector;

	private:
	};
}
#endif // OGBulletForceOperator_h__