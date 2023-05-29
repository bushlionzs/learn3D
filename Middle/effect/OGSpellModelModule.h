#ifndef OGSpellModelModule_h__
#define OGSpellModelModule_h__



#include <OgreStringInterface.h>
#include <OgreQuaternion.h>
#include "OGSpellSerializer.h"


namespace Orphigine
{
	class SkeletonMeshComponent;

	class SpellModelModule : public Ogre::StringInterface
	{
	public:

		class CmdAttachTime : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
#if OGRE_STRING_INTERFACE_COPY
			virtual void doCopy(void* target, const void* source);
#endif
		};

		class CmdAttachPoint : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
#if OGRE_STRING_INTERFACE_COPY
			virtual void doCopy(void* target, const void* source);
#endif
		};

		class CmdModelTemplateName : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
#if OGRE_STRING_INTERFACE_COPY
			virtual void doCopy(void* target, const void* source);
#endif
		};

		class CmdSubSkillTemplateName : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
#if OGRE_STRING_INTERFACE_COPY
			virtual void doCopy(void* target, const void* source);
#endif
		};

		class CmdOffsetPos : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
#if OGRE_STRING_INTERFACE_COPY
			virtual void doCopy(void* target, const void* source);
#endif
		};

		class CmdOffsetRotation : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
#if OGRE_STRING_INTERFACE_COPY
			virtual void doCopy(void* target, const void* source);
#endif
		};

		class CmdAttach : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
#if OGRE_STRING_INTERFACE_COPY
			virtual void doCopy(void* target, const void* source);
#endif
		};

		class CmdLifeTime : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
#if OGRE_STRING_INTERFACE_COPY
			virtual void doCopy(void* target, const void* source);
#endif
		};
		//////////////////////////////////////////////////////////////////////////

		SpellModelModule();
		~SpellModelModule();

		bool						initParamDictionary(void);

		void						setAttachTime(float time);
		float						getAttachTime(void) const;

		void						setAttachPoint(const String &point);
		const String&				getAttachPoint(void) const;

		void						setModelTemplateName(const String &name);
		const String&				getModelTemplateName(void) const;

		String				getSubSkillTemplateName() const;
		void						setSubSkillTemplateName(String val);

		void						setOffsetPos(const Ogre::Vector3 &pos);
		const Ogre::Vector3&		getOffsetPos(void) const;

		void						setOffsetRotation(const Ogre::Quaternion &rotation);
		const Ogre::Quaternion&		getOffsetRotation(void) const;

		void						setAttach(bool attach);
		bool						getAttach(void) const;

		Real					getLifeTime() const;
		void						setLifeTime(Real val);

		SkeletonMeshComponent *				getModel() const;
		void						setModel(SkeletonMeshComponent * val);

		void						updateRenderInstance(Real time);

		bool						getIsCreatedInstance() const;
		void						setIsCreatedInstance(bool val);

		Real					getCurrentLifeTime() const;
		void						setCurrentLifeTime(Real val);
		/** 拷贝所有特效参数变量
		@remarks 由于原来用Ogre::StringInterface::copyParametersTo这个函数
		来进行参数的拷贝速度太慢（因为里面有一些字符串的操作），所以
		用一个函数来复制所有的参数变量，每加一个参数，都要在这个函数
		中添加相对项
		*/
		void						copyAttributesTo(SpellModelModule& newInfo) const;

	protected:

		float				mAttachTime;
		String				mAttachPoint;
		String				mModelTemplateName;
		String				mSubSkillTemplateName;
		Ogre::Vector3		mOffsetPos;
		Ogre::Quaternion	mOffsetRotation;
		/// if this is true, the effect will move along to the bone.
		bool				mAttach;
		Real				mLifeTime;


		SkeletonMeshComponent*			mModel;
		bool				mIsCreatedInstance;
		Real				mCurrentLifeTime;

		//////////////////////////////////////////////////////////////////////////
		static CmdAttachTime msAttachTimeCmd;
		static CmdAttachPoint msAttachPointCmd;
		static CmdModelTemplateName msModelTemplateNameCmd;
		static CmdOffsetPos msOffsetPosCmd;
		static CmdOffsetRotation msOffsetRotationCmd;
		static CmdAttach msAttachCmd;
		static CmdSubSkillTemplateName		msSubSkillTemplateNameCmd;
		static CmdLifeTime					msLifeTimeCmd;

	public:
		void loadBinary( SpellsSerializer* serializer,Ogre::DataStreamPtr& stream );
		void saveBinary( SpellsSerializer* serializer );
		std::size_t calcSerializedSize();

	};
}
#endif // OGSpellModelModule_h__