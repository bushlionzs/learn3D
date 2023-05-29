#ifndef OGSpellSoundModule_h__
#define OGSpellSoundModule_h__


#include "OGSpellSerializer.h"

#include <OgreStringInterface.h>

namespace Orphigine	{

	class _OrphigineExport SpellSoundModule : public Ogre::StringInterface
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

		class CmdSoundName : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
#if OGRE_STRING_INTERFACE_COPY
			virtual void doCopy(void* target, const void* source);
#endif	
		};

		class CmdLooping : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
#if OGRE_STRING_INTERFACE_COPY
			virtual void doCopy(void* target, const void* source);
#endif	
		};

		SpellSoundModule(void);

		void setAttachTime(float time)
		{
			mAttachTime = time;
		}
		float getAttachTime(void) const
		{
			return mAttachTime;
		}

		void setSoundName( const Ogre::String &name )
		{
			mSoundName = name;
		}
		const Ogre::String& getSoundName(void) const
		{
			return mSoundName;
		}

		bool				getLooping() const;
		void				setLooping(bool val);

		/** 拷贝所有特效参数变量
		@remarks 由于原来用Ogre::StringInterface::copyParametersTo这个函数
		来进行参数的拷贝速度太慢（因为里面有一些字符串的操作），所以
		用一个函数来复制所有的参数变量，每加一个参数，都要在这个函数
		中添加相对项
		*/
		void copyParameters(SpellSoundModule& newInfo) const;

	public:

		/// the handle of sound, will set by play sound function.
		int mSoundHandle;
		bool mPlayed;

	protected:

		float	mAttachTime;
		String	mSoundName;
		bool	m_isLooping;

		//////////////////////////////////////////////////////////////////////////
		static CmdAttachTime msAttachTimeCmd;
		static CmdSoundName msSoundNameCmd;
		static CmdLooping	ms_isLoopingCmd;

	public:
		void loadBinary( SpellsSerializer* serializer ,Ogre::DataStreamPtr& stream);
		void saveBinary( SpellsSerializer* serializer );
		std::size_t	calcSerializedSize();
	};
}

#endif // OGSpellSoundModule_h__