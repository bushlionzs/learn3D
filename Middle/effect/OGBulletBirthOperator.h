#ifndef OGBulletBirthOperator_h__
#define OGBulletBirthOperator_h__

#include "OGBulletOperator.h"

namespace Orphigine
{
	class BulletEventSystem;
	class BulletBirthOperator : public BulletOperator
	{
	public:
		BulletBirthOperator(BulletEventSystem* eventSystem);
		virtual ~BulletBirthOperator();

		virtual void operateBulletEventSystem(Real timeElapsed);


		class CmdBulletSystemTemplateName : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
#if OGRE_STRING_INTERFACE_COPY
			virtual void doCopy(void* target, const void* source);
#endif
		};

		class CmdBirthTimes : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
#if OGRE_STRING_INTERFACE_COPY
			virtual void doCopy(void* target, const void* source);
#endif
		};

		class CmdIsDynamicAdapter : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
#if OGRE_STRING_INTERFACE_COPY
			virtual void doCopy(void* target, const void* source);
#endif
		};

		const String&	getBulletSystemName() const;
		void					setBulletSystemName(const String& val);

		int						getBirthTimes() const;
		void					setBirthTimes(int val);

		bool					getDynamicAdapter() const;
		void					setDynamicAdapter(bool val);

		static CmdBulletSystemTemplateName	ms_bulletTemplateCmd;
		static CmdBirthTimes				 ms_birthTimesCmd;
		static CmdIsDynamicAdapter			ms_isDynamicAdapterCmd;
	protected:
		String				m_bulletSystemName;
		int					m_birthTimes;
		bool				m_isDynamicAdapter;
		int					m_birthedTimes;
		bool				m_isOperated;
	private:
	};
}
#endif // OGBulletBirthOperator_h__