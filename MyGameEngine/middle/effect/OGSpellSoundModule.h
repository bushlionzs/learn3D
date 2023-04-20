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

		/** ����������Ч��������
		@remarks ����ԭ����Ogre::StringInterface::copyParametersTo�������
		�����в����Ŀ����ٶ�̫������Ϊ������һЩ�ַ����Ĳ�����������
		��һ���������������еĲ���������ÿ��һ����������Ҫ���������
		����������
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