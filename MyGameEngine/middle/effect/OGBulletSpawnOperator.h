#ifndef OGBulletSpawnOperator_h__
#define OGBulletSpawnOperator_h__

#include "OGBulletOperator.h"

namespace Orphigine
{
	class BulletEventSystem;
	class BulletSpawnOperator : public BulletOperator
	{
	public:
		BulletSpawnOperator(BulletEventSystem* eventSystem);
		virtual ~BulletSpawnOperator();

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

		bool						getIsDeleteSource() const;
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
#endif // OGBulletSpawnOperator_h__