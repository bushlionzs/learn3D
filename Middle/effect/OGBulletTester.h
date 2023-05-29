#ifndef OGBulletTester_h__
#define OGBulletTester_h__

#include "OGBulletOperator.h"


namespace Orphigine
{
	class BulletEventSystem;

	class _OrphigineExport BulletTester : public BulletOperator
	{
	public:
		virtual ~BulletTester();

		class CmdOutput : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
#if OGRE_STRING_INTERFACE_COPY
			virtual void doCopy(void* target, const void* source);
#endif
		};

		const String& getOutputEventName() const;
		void setOutputEventName(const String& val);

		bool				initBaseParamters(const String& type);

		static CmdOutput	ms_outputCmd;

	protected:
		BulletTester();
	protected:
		String				m_outputEventName;
	};
}
#endif // OGBulletTester_h__