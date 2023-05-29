#ifndef OGBulletCameraShakeOperator_h__
#define OGBulletCameraShakeOperator_h__

#include "OGBulletOperator.h"


namespace Orphigine
{
	class BulletEventSystem;
	class BulletCameraShakeOperator : public BulletOperator
	{
	public:
		BulletCameraShakeOperator(BulletEventSystem* eventSystem);
		virtual ~BulletCameraShakeOperator();

		virtual void operateBulletEventSystem(Real timeElapsed);

		class CmdAmplitude : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
#if OGRE_STRING_INTERFACE_COPY
			virtual void doCopy(void* target, const void* source);
#endif
		};

		class CmdDuration : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
#if OGRE_STRING_INTERFACE_COPY
			virtual void doCopy(void* target, const void* source);
#endif
		};

		Real getAmplitude() const;
		void setAmplitude(const Real val);

		Real getDuration() const;
		void setDuration(const Real val);

		static CmdAmplitude ms_amplitudeCmd;
		static CmdDuration	ms_durationCmd;
	protected:
		Real	m_amplitude;
		Real	m_duration;
		Real	m_age;
		bool	m_isStart;
	private:
	};
}

#endif // OGBulletCameraShakeOperator_h__