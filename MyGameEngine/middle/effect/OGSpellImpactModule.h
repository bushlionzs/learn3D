#ifndef OGSpellImpactModule_h__
#define OGSpellImpactModule_h__



#include <OgreStringInterface.h>
#include <OgreQuaternion.h>


#include "OGImpact.h"
#include "OGSpellSerializer.h"

namespace Orphigine	{

	class _OrphigineExport SpellImpactModule : public Ogre::StringInterface
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

		class CmdEffectTemplateName : public Ogre::ParamCommand
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

		SpellImpactModule();
		~SpellImpactModule();

		bool initParamDictionary(void);

		void setAttachTime(float time)
		{
			mAttachTime = time;
		}
		float getAttachTime(void) const
		{
			return mAttachTime;
		}

		void setAttachPoint(const String &point)
		{
			mAttachPoint = point;
		}
		const String& getAttachPoint(void) const
		{
			return mAttachPoint;
		}

		void setEffectTemplateName(const String &name)
		{
			mEffectTemplateName = name;
		}
		const String& getEffectTemplateName(void) const
		{
			return mEffectTemplateName;
		}

		void setOffsetPos(const Ogre::Vector3 &pos)
		{
			mOffsetPos = pos;
		}
		const Ogre::Vector3& getOffsetPos(void) const
		{
			return mOffsetPos;
		}

		void setOffsetRotation(const Ogre::Quaternion &rotation)
		{
			mOffsetRotation = rotation;
		}
		const Ogre::Quaternion& getOffsetRotation(void) const
		{
			return mOffsetRotation;
		}

		void setAttach(bool attach)
		{
			mAttach = attach;
		}
		bool getAttach(void) const
		{
			return mAttach;
		}

		void setUseAttachRotation(bool useAttachRotation)
		{
			mUseAttachRotation=useAttachRotation;
		}
		bool getUseAttachRotation(void) const
		{
			return mUseAttachRotation;
		}

		Impact *getEffect(void)
		{
			return mEffect;
		}

		void setEffect(Impact *effect)
		{
			mEffect = effect;
		}

		/** 拷贝所有特效参数变量
		@remarks 由于原来用Ogre::StringInterface::copyParametersTo这个函数
		来进行参数的拷贝速度太慢（因为里面有一些字符串的操作），所以
		用一个函数来复制所有的参数变量，每加一个参数，都要在这个函数
		中添加相对项
		*/
		void copyParameters(SpellImpactModule& newInfo) const;

	protected:

		float				mAttachTime;
		String				mAttachPoint;
		String				mEffectTemplateName;
		Impact*				mEffect;
		Ogre::Vector3		mOffsetPos;
		Ogre::Quaternion	mOffsetRotation;
		/// if this is true, the effect will move along to the bone.
		bool				mAttach;
		/// if this is true, the effect will use the bone rotation to cal the position and rotation.
		bool				mUseAttachRotation;

		//////////////////////////////////////////////////////////////////////////
		static CmdAttachTime msAttachTimeCmd;
		static CmdAttachPoint msAttachPointCmd;
		static CmdEffectTemplateName msEffectTemplateNameCmd;
		static CmdOffsetPos msOffsetPosCmd;
		static CmdOffsetRotation msOffsetRotationCmd;
		static CmdAttach msAttachCmd;
		static CmdUseAttachRotation msUseAttachRotationCmd;

	public:
		void loadBinary( SpellsSerializer* serializer ,Ogre::DataStreamPtr& stream);
		void saveBinary( SpellsSerializer* serializer );
		std::size_t calcSerializedSize();
	};
}

#endif // OGSpellImpactModule_h__