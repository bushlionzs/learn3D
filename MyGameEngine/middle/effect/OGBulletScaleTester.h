#ifndef OGBulletScaleTester_h__
#define OGBulletScaleTester_h__

#include "OGBulletTester.h"

namespace Orphigine
{
	class BulletEventSystem;

	class BulletScaleTester : public BulletTester
	{
	public:
		BulletScaleTester(BulletEventSystem* eventSystem);
		virtual ~BulletScaleTester();

		virtual void operateBulletEventSystem(Real timeElapsed);

		const Real& getMaxScale() const;
		void setMaxScale(const Real& val);

		class CmdMaxScale : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
		};

		static CmdMaxScale	ms_maxScaleCmd;
	protected:
		Real	m_maxScale;

	private:
	};
}
#endif // OGBulletScaleTester_h__