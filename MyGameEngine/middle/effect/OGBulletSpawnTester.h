#ifndef OGBulletSpawnTester_h__
#define OGBulletSpawnTester_h__

#include "OGBulletTester.h"

namespace Orphigine
{
	class BulletEventSystem;
	class BulletSpawnTester : public BulletTester
	{
	public:
		BulletSpawnTester(BulletEventSystem* eventSystem);
		virtual ~BulletSpawnTester();

		virtual void operateBulletEventSystem(Real timeElapsed);


		class CmdBulletSystemTemplateName : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);

		};

		class CmdIsDeleteSource : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
		};

		const String&	getBulletSystemName() const;
		void					setBulletSystemName(const String& val);

		bool					getIsDeleteSource() const;
		void					setIsDeleteSource(bool val);

		static CmdBulletSystemTemplateName	ms_bulletTemplateCmd;
		static CmdIsDeleteSource			ms_isDeleteSourceCmd;
	protected:
		String				m_bulletSystemName;
		bool				m_isDeleteSource;
		int					m_spawnedTimes;
		bool				m_isOperated;
	private:
	};
}

#endif // OGBulletSpawnTester_h__