/********************************************************************
	created:	2008/04/07
	created:	7:4:2008   16:35
	file base:	OGAdvancedAnimationSystemManager
	file ext:	h
	author:		姜威
	email:		jiang628@hotmail.com
	purpose:	
*********************************************************************/
#ifndef OGAdvancedAnimationSystemManager_h__
#define OGAdvancedAnimationSystemManager_h__

#include "OGAdvancedAnimationSystem.h"

#include "OgreSingleton.h"
#include "OgreScriptLoader.h"
namespace Orphigine
{
	class AASNode;
	class AASNodeFactory;
	class AdvancedAnimationSystem;
	class SkeletonMeshComponent;

	class  AdvancedAnimationSystemManager: public ScriptLoader, 
		public Ogre::Singleton<AdvancedAnimationSystemManager>
	{
	public:
		AdvancedAnimationSystemManager();
		virtual ~AdvancedAnimationSystemManager();

		virtual	AdvancedAnimationSystemPtr		createManual(const String& name,const String& groupName,
			Ogre::ManualResourceLoader* loader = 0);

		virtual Ogre::Resource*					createImpl(const String& name, Ogre::ResourceHandle handle, 
			const String& group, bool isManual, Ogre::ManualResourceLoader* loader, 
			const Ogre::NameValuePairList* createParams);


		AASNode* createNode(const String& typeName,unsigned short handle,AdvancedAnimationSystem* system);

		void destroyNode(AASNode* node);

		void addNodeFactory(AASNodeFactory* nodeFactory);

		virtual String getSuffix();
		virtual void parseScript(ResourceInfo* res, const String& groupName);
		virtual Real getLoadingOrder(void) const;


		AdvancedAnimationSystemPtr getAnimationSystem(const String& name);
	protected:

		void registerNodeFactories();

		void unregisterNodeFactories();

		void registerAASSerializers();

		void unregisterAASSerializers();
	public:
		void loadAASCache(Ogre::OStringSet& aasSet);
		void unloadAASCache();
	protected:
		std::map<String,AASNodeFactory*> m_nodeFactories; //工厂列表
	private:		
		typedef std::unordered_map<String, Orphigine::AdvancedAnimationSystemPtr > AASCache;
		AASCache		mAASCache;
	};
}
#endif // OGAdvancedAnimationSystemManager_h__
