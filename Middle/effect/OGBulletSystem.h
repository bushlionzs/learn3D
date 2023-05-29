#ifndef OGBulletSystem_h__
#define OGBulletSystem_h__

#include "OgreStringInterface.h"
#include "OgreSceneNode.h"
#include "OGBullet.h"
#include "OGImpact.h"

namespace Orphigine
{
	class BulletSystemEffectElement;
	class SpellRibbonModule;
	class SpellSoundModule;
	class SpellSceneLightModule;
	class BulletSystemBeamElement;
	class Engine;
	class BulletFlowSystem;

	class _OrphigineExport BulletSystem :public Ogre::StringInterface ,public Bullet
	{
	public:
		BulletSystem(const String& templateName);
		virtual ~BulletSystem();

		BulletSystem& operator = (const BulletSystem& rhs);

		class CmdAttach : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
		};

		void						initParameters();

		void						createSceneNode();

		void						createSceneNode(Ogre::SceneNode* parentNode);

		void						removeSceneNode();

		void						setTransformInfo(const TransformInfo& info);

		const	TransformInfo&		getTransformInfo() const;

		void						update(Real time);

		const Ogre::Vector3&		getPotentialTargetPos() const;
		void						setPotentialTargetPos(const Ogre::Vector3& val);

		const String&		getTemplateName() const;

		bool						getAttach() const;
		void						setAttach(bool val);

		Real						getAge() const;
		void						setAge(Real val);

		Real						getEventAge() const;
		void						setEventAge(Real val);

		const Ogre::Vector3&		getSourcePosition() const;
		void						setSourcePosition(const Ogre::Vector3& val);

		const Ogre::Vector3&		getDestPosition() const;
		void						setDestPosition(const Ogre::Vector3& val);

		//////////////////////////////////////////////////////////////////////////		
		BulletSystemEffectElement*	addBulletSystemEffectElement(void);

		BulletSystemEffectElement*	getBulletSystemEffectElement(unsigned short index) const;

		unsigned short				getNumBulletSystemEffectElements(void) const;

		void						removeBulletSystemEffectElement(unsigned short index);

		void						removeAllBulletSystemEffectElements(void);

		//////////////////////////////////////////////////////////////////////////
		SpellRibbonModule*			addAnimationRibbon(void);

		SpellRibbonModule*			getAnimationRibbon(unsigned short index) const;

		unsigned short				getNumAnimationRibbons(void) const;

		void						removeAnimationRibbon(unsigned short index);

		void						removeAllAnimationRibbons(void);

		//////////////////////////////////////////////////////////////////////////
		SpellSoundModule*				addAnimationSound(void);

		SpellSoundModule*				getAnimationSound(unsigned short index) const;

		unsigned short				getNumAnimationSounds(void) const;

		void						removeAnimationSound(unsigned short index);

		void						removeAllAnimationSounds(void);

		//////////////////////////////////////////////////////////////////////////		
		SpellSceneLightModule*	addAnimationSceneLightInfo(void);

		SpellSceneLightModule*	getAnimationSceneLightInfo(unsigned short index) const;

		unsigned short				getNumAnimationSceneLightInfos(void) const;

		void						removeAnimationSceneLightInfo(unsigned short index);

		void						removeAllAnimationSceneLightInfos(void);

		//////////////////////////////////////////////////////////////////////////
		BulletSystemBeamElement*	addBulletSystemBeamElement();

		BulletSystemBeamElement*	getBulletSystemBeamElement(unsigned short index) const;

		unsigned short				getNumBulletSystemBeamElements() const;

		void						removeBulletSystemBeamElement(unsigned short index);

		void						removeAllBulletSystemBeamElements();


		void						copyAttributesTo(BulletSystem& dest) const;

		typedef std::vector<BulletSystemEffectElement *> BulletSystemEffectElements;
		typedef std::vector<SpellRibbonModule *> AnimationRibbons;
		typedef std::vector<SpellSoundModule *> AnimationSounds;
		typedef std::vector<SpellSceneLightModule *> AnimationSceneLightInfos;
		typedef std::vector<BulletSystemBeamElement*> BulletSystemBeamElements;

		static		CmdAttach			ms_attachCmd;

		void							setPriority(int priority) { m_Priority = priority;}
		int								getPriority() {return m_Priority;}
		//end
	protected:
		void							_createElements();

		void							_updateElements(Real	time);
	protected:
		BulletSystemEffectElements		mBulletSystemEffectElements;
		AnimationRibbons				mAnimationRibbons;
		AnimationSounds					mAnimationSounds;
		AnimationSceneLightInfos		mAnimationSceneLightInfos;
		BulletSystemBeamElements		mBulletSystemBeamElements;

		bool							m_isAttach;

		String							m_templateName;
		bool							m_isCreated;
		TransformInfo					m_transWorld;
		Real							m_age;
		Real							m_eventAge;

		Ogre::Vector3					m_sourcePosition;
		Ogre::Vector3					m_destPosition;
		int								m_Priority;
	public:
		void*							m_userData;
	};
}

#endif // OGBulletSystem_h__