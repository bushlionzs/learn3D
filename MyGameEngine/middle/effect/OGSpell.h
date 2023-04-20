#ifndef OGSpell_h__
#define OGSpell_h__


#include <OgreQuaternion.h>
#include <OgreStringInterface.h>

#include "OGImpactManager.h"
#include "OGSpellRibandModule.h"
#include "OGSpellSoundModule.h"

namespace Orphigine	
{

	class SpellImpactModule;
	class SpellRibbonModule;
	class SpellSoundModule;
	class SpellSceneLightModule;
	class SpellBulletFlowModule;
	class SpellModelModule;

	class _OrphigineExport Spell : public Ogre::StringInterface
	{
		typedef std::vector<Real> TimeArray;

	public:

		class CmdAnimationName : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
#if OGRE_STRING_INTERFACE_COPY
			virtual void doCopy(void* target, const void* source);
#endif
		};

		class CmdHitTime : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
#if OGRE_STRING_INTERFACE_COPY
			virtual void doCopy(void* target, const void* source);
#endif	
		};

		class CmdBreakTime : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
#if OGRE_STRING_INTERFACE_COPY
			virtual void doCopy(void* target, const void* source);
#endif	
		};

		class CmdShakeTime : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
#if OGRE_STRING_INTERFACE_COPY
			virtual void doCopy(void* target, const void* source);
#endif	
		};

		class CmdRepeatEffect : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
#if OGRE_STRING_INTERFACE_COPY
			virtual void doCopy(void* target, const void* source);
#endif      
		};

		//////////////////////////////////////////////////////////////////////////
		Spell(const String &skillName);

		~Spell();

		const String& getAnimationName(void) const
		{
			return mAnimName;
		}

		void setAnimationName(const String &name)
		{
			mAnimName = name;
		}

		const String& getSkillName(void) const
		{
			return mTemplateSkillName;
		}

		bool update()//可能需要一个参数，有待填充内容
		{
			return true;
		}
		int getId()
		{
			return mId;
		}

		void setBreakTime(Real time, unsigned short index)
		{
			assert (index < mBreakTimeArray.size());
			mBreakTimeArray[index] = time;
		}

		Real getBreakTime(unsigned short index) const
		{
			assert (index < mBreakTimeArray.size());
			return mBreakTimeArray[index];
		}

		unsigned short getNumBreakTimes(void);

		void setBreakTimeFromString(const String &breakTimeStr);

		String getBreakTimeString(void) const;

		void setHitTime(Real time, unsigned short index)
		{
			assert (index < mHitTimeArray.size());
			mHitTimeArray[index] = time;
		}

		Real getHitTime(unsigned short index) const
		{
			assert (index < mHitTimeArray.size());
			return mHitTimeArray[index];
		}

		unsigned short getNumHitTimes(void);

		void setHitTimeFromString(const String &hitTimeStr);

		String getHitTimeString(void) const;

		void setShakeTime(Real time, unsigned short index)
		{
			assert (index < mShakeTimeArray.size());
			mShakeTimeArray[index] = time;
		}

		Real getShakeTime(unsigned short index) const
		{
			assert (index < mShakeTimeArray.size());
			return mShakeTimeArray[index];
		}

		unsigned short getNumShakeTimes(void);

		void setShakeTimeFromString(const String &shakeTimeStr);

		String getShakeTimeString(void) const;

		Spell & operator = (const Spell &rhs);
		Spell* Clone();
		// 进行一些skill中各种元素的清除操作
		void shutdown(void);

		void setRepeatEffect(bool repeat)
		{
			mRepeatEffect = repeat;
		}
		bool getRepeatEffect(void) const
		{
			return mRepeatEffect;
		}

		/** 拷贝所有特效参数变量
		@remarks 由于原来用Ogre::StringInterface::copyParametersTo这个函数
		来进行参数的拷贝速度太慢（因为里面有一些字符串的操作），所以
		用一个函数来复制所有的参数变量，每加一个参数，都要在这个函数
		中添加相对项
		*/
		void copyParameters(Spell* newInfo) const;

		//////////////////////////////////////////////////////////////////////////		
		SpellImpactModule* addAnimationEffectInfo(void);

		SpellImpactModule* getAnimationEffectInfo(unsigned short index) const;

		unsigned short getNumAnimationEffectInfos(void) const;

		void removeAnimationEffectInfo(unsigned short index);

		void removeAllAnimationEffectInfos(void);

		//////////////////////////////////////////////////////////////////////////
		SpellRibbonModule* addAnimationRibbon(void);

		SpellRibbonModule* getAnimationRibbon(unsigned short index) const;

		unsigned short getNumAnimationRibbons(void) const;

		void removeAnimationRibbon(unsigned short index);

		void removeAllAnimationRibbons(void);

		//////////////////////////////////////////////////////////////////////////
		SpellSoundModule* addAnimationSound(void);

		SpellSoundModule* getAnimationSound(unsigned short index) const;

		unsigned short getNumAnimationSounds(void) const;

		void removeAnimationSound(unsigned short index);

		void removeAllAnimationSounds(void);

		//////////////////////////////////////////////////////////////////////////		
		SpellSceneLightModule* addAnimationSceneLightInfo(void);

		SpellSceneLightModule* getAnimationSceneLightInfo(unsigned short index) const;

		unsigned short getNumAnimationSceneLightInfos(void) const;

		void removeAnimationSceneLightInfo(unsigned short index);

		void removeAllAnimationSceneLightInfos(void);

		//////////////////////////////////////////////////////////////////////////		
		SpellBulletFlowModule* addAnimationBulletFlow(void);

		SpellBulletFlowModule* getAnimationBulletFlow(unsigned short index) const;

		unsigned short getNumAnimationBulletFlows(void) const;

		void removeAnimationBulletFlow(unsigned short index);

		void removeAllAnimationBulletFlows(void);

		///////////////////////////////////////////////////////////////////////////
		SpellModelModule* addSkillModelElement(void);

		SpellModelModule* getSkillModelElement(unsigned short index) const;

		unsigned short getNumSkillModelElement(void) const;

		void removeSkillModelElement(unsigned short index);

		void removeAllSkillModelElement(void);

		void setPriority(int priority) { mPriority = priority;}
		int  getPriority() { return mPriority;}

		void clear();
	public:

		typedef std::vector<SpellImpactModule *>		AnimationEffectInfos;
		typedef std::vector<SpellRibbonModule *>		AnimationRibbons;
		typedef std::vector<SpellSoundModule * >		AnimationSounds;
        typedef std::vector<SpellSceneLightModule * >		AnimationSceneLightInfos;
		typedef std::vector<SpellBulletFlowModule* >		AnimationBulletFlows;
		typedef std::vector<SpellModelModule* >		SkillModelElements;
	protected:

		bool initParamDictionary(void);

	protected:
		String	mAnimName;
		int		mId;
		String	mTemplateSkillName;

		AnimationEffectInfos		mAnimationEffectInfos;
		AnimationRibbons			mAnimationRibbons;
		AnimationSounds				mAnimationSounds;
		AnimationSceneLightInfos	mAnimationSceneLightInfos;
		AnimationBulletFlows		mAnimationBulletFlows;
		SkillModelElements			mSkillModelElements;

		//Real mHitTime;
		TimeArray	mHitTimeArray;
		//Real mBreakTime;
		TimeArray	mBreakTimeArray;	
		TimeArray	mShakeTimeArray;
		int			mPriority;
		bool		mRepeatEffect;

		Ogre::Quaternion mRotation;
		//////////////////////////////////////////////////////////////////////////
		static CmdAnimationName msAnimationNameCmd;
		static CmdBreakTime msBreakTimeCmd;
		static CmdHitTime msHitTimeCmd;
		static CmdShakeTime msShakeTimeCmd;
		static CmdRepeatEffect msRepeatEffectCmd;
		static int mSkillIdIndex;//用于Skill的id计数，从1开始，自增


	public:
		void*				m_userData;

	public:
		Ogre::Quaternion &getRotation() {return mRotation;}
		void setRotation(const Ogre::Quaternion& rot) { mRotation = rot;}

		void		loadBinary(SpellsSerializer* serializer,Ogre::DataStreamPtr& stream);
		void		saveBinary(SpellsSerializer* serializer);
		std::size_t	calcSerializedSize();
	};
}

#endif // OGSpell_h__