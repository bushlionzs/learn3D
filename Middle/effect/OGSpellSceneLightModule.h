#ifndef OGSpellSceneLightModule_h__
#define OGSpellSceneLightModule_h__


#include "OGSpellSerializer.h"

#include <OgreStringInterface.h>
#include <OgreColourValue.h>

namespace Orphigine
{
	class _OrphigineExport SpellSceneLightModule : public Ogre::StringInterface
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

		class CmdLastTime : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
#if OGRE_STRING_INTERFACE_COPY
			virtual void doCopy(void* target, const void* source);
#endif      
		};

		class CmdFadeInTime : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
#if OGRE_STRING_INTERFACE_COPY
			virtual void doCopy(void* target, const void* source);
#endif      
		};

		class CmdFadeOutTime : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
#if OGRE_STRING_INTERFACE_COPY
			virtual void doCopy(void* target, const void* source);
#endif      
		};

		class CmdDestColour : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
#if OGRE_STRING_INTERFACE_COPY
			virtual void doCopy(void* target, const void* source);
#endif      
		};

		SpellSceneLightModule(void);

		void setAttachTime(float time)
		{
			mAttachTime = time;
		}
		float getAttachTime(void) const
		{
			return mAttachTime;
		}

		void setLastTime(float time)
		{
			mLastTime = time;
		}
		float getLastTime(void) const
		{
			return mLastTime;
		}

		void setFadeInTime(float time)
		{
			mFadeInTime = time;
		}
		float getFadeInTime(void) const
		{
			return mFadeInTime;
		}

		void setFadeOutTime(float time)
		{
			mFadeOutTime = time;
		}
		float getFadeOutTime(void) const
		{
			return mFadeOutTime;
		}

		void setDestColour(const Ogre::ColourValue& colour)
		{
			mDestColour = colour;
		}
		const Ogre::ColourValue& getDestColour(void) const
		{
			return mDestColour;
		}

		/** ����������Ч��������
		@remarks ����ԭ����Ogre::StringInterface::copyParametersTo�������
		�����в����Ŀ����ٶ�̫������Ϊ������һЩ�ַ����Ĳ�����������
		��һ���������������еĲ���������ÿ��һ����������Ҫ���������
		����������
		*/
		void copyParameters(SpellSceneLightModule& newInfo) const;

	protected:

		float mAttachTime;
		float mLastTime;
		float mFadeInTime;
		float mFadeOutTime;
		Ogre::ColourValue mDestColour;

		//////////////////////////////////////////////////////////////////////////
		static CmdAttachTime msAttachTimeCmd;
		static CmdLastTime msLastTimeCmd;
		static CmdFadeInTime msFadeInTimeCmd;
		static CmdFadeOutTime msFadeOutTimeCmd;
		static CmdDestColour msDestColourCmd;

	public:
		void loadBinary( SpellsSerializer* serializer ,Ogre::DataStreamPtr& stream);
		void saveBinary( SpellsSerializer* serializer );
		std::size_t	calcSerializedSize();
	};
}

#endif // OGSpellSceneLightModule_h__