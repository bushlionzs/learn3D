#ifndef OGSpellBulletFlowModule_h__
#define OGSpellBulletFlowModule_h__


#include <OgreStringInterface.h>
#include <OgreQuaternion.h>
#include "OGSpellSerializer.h"

namespace Orphigine	{

	class _OrphigineExport SpellBulletFlowModule : public Ogre::StringInterface
	{
	public:

		class CmdAttachTime : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
		};

		class CmdAttachPoint : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
		};

		class CmdBulletFlowTemplateName : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
		};

		class CmdOffsetPos : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
		};

		class CmdOffsetRotation : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
		};

		class CmdAttach : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
		};

		class CmdUseAttachRotation : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void   doSet(void* target,const String& val);
#if OGRE_STRING_INTERFACE_COPY
			virtual void doCopy(void* target,const void* source);
#endif
		};

		//////////////////////////////////////////////////////////////////////////

		SpellBulletFlowModule();
		~SpellBulletFlowModule();

		bool initParamDictionary(void);

		void setAttachTime(float time);
		float getAttachTime(void) const;

		void setAttachPoint(const String &point);
		const String& getAttachPoint(void) const;

		void setBulletFlowTemplateName(const String &name);
		const String& getBulletFlowTemplateName(void) const;

		void setOffsetPos(const Ogre::Vector3 &pos);
		const Ogre::Vector3& getOffsetPos(void) const;

		void setOffsetRotation(const Ogre::Quaternion &rotation);
		const Ogre::Quaternion& getOffsetRotation(void) const;

		const bool& getAttach() const;
		void setAttach(const bool& val);

		void setUseAttachRotation(bool useAttachRotation)
		{
			mUseAttachRotation=useAttachRotation;
		}
		bool getUseAttachRotation(void) const
		{
			return mUseAttachRotation;
		}

		/** 拷贝所有特效参数变量
		@remarks 由于原来用Ogre::StringInterface::copyParametersTo这个函数
		来进行参数的拷贝速度太慢（因为里面有一些字符串的操作），所以
		用一个函数来复制所有的参数变量，每加一个参数，都要在这个函数
		中添加相对项
		*/
		void copyParameters(SpellBulletFlowModule& newInfo) const;

	protected:

		float					m_attachTime;
		String					m_attachPoint;
		String					m_bulletFlowTemplateName;
		Ogre::Vector3			m_offsetPos;
		Ogre::Quaternion		m_offsetRotation;
		bool					m_isAttach;
		bool 					mUseAttachRotation;

		//////////////////////////////////////////////////////////////////////////
		static CmdAttachTime				ms_attachTimeCmd;
		static CmdAttachPoint				ms_attachPointCmd;
		static CmdBulletFlowTemplateName	ms_bulletFlowTemplateNameCmd;
		static CmdOffsetPos					ms_offsetPosCmd;
		static CmdOffsetRotation			ms_offsetRotationCmd;
		static CmdAttach					ms_attachCmd;
		static CmdUseAttachRotation			msUseAttachRotationCmd;

	public:
		void loadBinary( SpellsSerializer* serializer,Ogre::DataStreamPtr& stream );
		void saveBinary( SpellsSerializer* serializer );
		std::size_t	calcSerializedSize();
	};
}
#endif // OGSpellBulletFlowModule_h__

