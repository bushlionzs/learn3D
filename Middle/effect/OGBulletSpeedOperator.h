#ifndef OGBulletSpeedOperator_h__
#define OGBulletSpeedOperator_h__

#include "OGBulletOperator.h"

namespace Orphigine
{
	class BulletEventSystem;
	class BulletSpeedOperator : public BulletOperator
	{
	public:
		BulletSpeedOperator(BulletEventSystem* eventSystem);
		virtual ~BulletSpeedOperator();

		virtual void operateBulletEventSystem(Real timeElapsed);

		class CmdMode : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
		};

		class CmdDirection : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
		};

		class CmdSpeed : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
		};

		const String&		getMode() const;
		void						setMode(const String& val);

		const Ogre::Vector3&		getDirection() const;
		void						setDirection(const Ogre::Vector3& val);

		const Real&			getSpeed() const;
		void						setSpeed(const Real& val);

		static CmdMode			ms_modeCmd;
		static CmdDirection		ms_directionCmd;
		static CmdSpeed			ms_speedCmd;
	protected:
		String				m_mode;
		Ogre::Vector3		m_direction;
		Real				m_speed;
		bool				m_isOperated;
	private:
	};
}
#endif // OGBulletSpeedOperator_h__