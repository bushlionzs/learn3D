#ifndef OGBulletAgeTester_h__
#define OGBulletAgeTester_h__

#include "OGBulletTester.h"

namespace Orphigine
{
	class BulletEventSystem;

	class BulletAgeTester : public BulletTester
	{
	public:
		BulletAgeTester(BulletEventSystem* eventSystem);
		virtual ~BulletAgeTester();


		virtual void operateBulletEventSystem(Real timeElapsed);

		Real					getMaxTime() const;
		void					setMaxTime(Real val);

		bool					getUseEventAge() const;
		void					setUseEventAge(bool val);

		class CmdMaxTime : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
#if OGRE_STRING_INTERFACE_COPY
			virtual void doCopy(void* target, const void* source);
#endif
		};

		class CmdIsUseEventAge : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
#if OGRE_STRING_INTERFACE_COPY
			virtual void doCopy(void* target, const void* source);
#endif
		};

		static CmdMaxTime	ms_maxTimeCmd;
		static CmdIsUseEventAge	ms_isUseEventAgeCmd;
	protected:
		Real	m_maxTime;
		bool	m_isUseEventAge;

	private:
	};
}
#endif // OGBulletAgeTester_h__