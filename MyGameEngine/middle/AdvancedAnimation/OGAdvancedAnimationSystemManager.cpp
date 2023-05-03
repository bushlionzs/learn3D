#include "OgreHeader.h"
#include "OGAdvancedAnimationSystemManager.h"
#include "OGAASAnimSequenceNodeFactory.h"
#include "OGAASAnimTreeOutputNodeFactory.h"
#include "OGAASBlendByDamageNodeFactory.h"
#include "OGAASBlendByDirectionalNodeFactory.h"
#include "OGAASBlendByIdleNodeFactory.h"
#include "OGAASBlendByLifeNodeFactory.h"
#include "OGAASBlendByPostureNodeFactory.h"
#include "OGAASBlendByWeaponTypeNodeFactory.h"
#include "OGAASBlendByRandomNodeFactory.h"
#include "OGAASBlendByAttackNodeFactory.h"
#include "OGAASBlendByRidingNodeFactory.h"
#include "OGAASAttackAnimSequenceNodeFactory.h"
#include "OGAASBlendByEquitationNodeFactory.h"
#include "OGAASBlendByGuardNodeFactory.h"
#include "OGAASWeaponAnimSequenceNodeFactory.h"
#include "OGAASBlendByMoodNodeFactory.h"
#include "OGAASMoodAnimSequenceNodeFactory.h"
#include "OGAASBlendByDanceNodeFactory.h"
#include "OGAASBlendByWalkNodeFactory.h"
#include "OGAASCrossFadeByTimeListNodeFactory.h"
#include "OGAASCrossFadeByTimeSlotNodeFactory.h"

#include "OGAASWeaponAnimExtSequenceNode.h"

#include "OGAdvancedAnimationSystem.h"
#include "OGSkeletonMeshComponentManager.h"
#include "OGSkeletonMeshComponent.h"
#include "OgreMemoryStream.h"
#include "platform_log.h"
#include "myutils.h"

template<> Orphigine::AdvancedAnimationSystemManager* 
Ogre::Singleton<Orphigine::AdvancedAnimationSystemManager>::msSingleton = NULL;

namespace Orphigine
{

	AdvancedAnimationSystemManager::AdvancedAnimationSystemManager()
	{
		
		registerNodeFactories();
		registerAASSerializers();
	}

	AdvancedAnimationSystemManager::~AdvancedAnimationSystemManager()
	{
		unloadAASCache();

		//Ogre::ResourceGroupManager::getSingleton()._unregisterResourceManager(mResourceType);

		unregisterNodeFactories();

		unregisterAASSerializers();
	}
	
	void AdvancedAnimationSystemManager::loadAASCache(Ogre::OStringSet& aasSet)
	{
		
		
	}
	void AdvancedAnimationSystemManager::unloadAASCache()
	{
		mAASCache.clear();
	}

	AASNode* AdvancedAnimationSystemManager::createNode( const String& typeName,unsigned short handle,
		AdvancedAnimationSystem* system )
	{
		std::map<String,AASNodeFactory*>::iterator iter = m_nodeFactories.find(typeName);

		if (iter == m_nodeFactories.end())
		{
			OGRE_EXCEPT(Ogre::Exception::ERR_INVALIDPARAMS, String("Cannot find requested node type. name = ") + typeName.c_str(), 
				"AdvancedAnimationSystemManager::createNode");
		}

		return iter->second->createNode(system,handle);
	}

	void AdvancedAnimationSystemManager::destroyNode( AASNode* node )
	{
		std::map<String,AASNodeFactory*>::iterator iter = m_nodeFactories.find(node->getType().c_str());

		if (iter == m_nodeFactories.end())
		{
			OGRE_EXCEPT(Ogre::Exception::ERR_INVALIDPARAMS, String("Cannot find requested node type. name = ") + node->getType().c_str(), 
				"AdvancedAnimationSystemManager::createNode");
		}

		iter->second->destroyNode(node);
	}

	void AdvancedAnimationSystemManager::addNodeFactory( AASNodeFactory* nodeFactory )
	{
		String tmpName = nodeFactory->getName();

		std::map<String,AASNodeFactory*>::iterator iter = m_nodeFactories.find(tmpName);
		if (iter != m_nodeFactories.end())
		{
			
		}

		m_nodeFactories.insert(std::map<String,AASNodeFactory*>::value_type(
			tmpName,nodeFactory));

		//WARNING_LOG("Advanced Animation System Node factory type '" 
		//	+ tmpName + "' registered",Ogre::LML_TRIVIAL);
	}

	String AdvancedAnimationSystemManager::getSuffix()
	{
		return ".aas";
	}
	void AdvancedAnimationSystemManager::parseScript(ResourceInfo* res, const String& groupName)
	{
		std::shared_ptr<DataStream> stream = std::make_shared<MemoryDataStream>(res);
		AdvancedAnimationSystemSerializer tmpSerializer;
		auto name = stream->getName();

		String shortname = getShortFilename(name);
		AdvancedAnimationSystem* aas = new AdvancedAnimationSystem(nullptr, shortname, 0, groupName);
		tmpSerializer.importAdvancedAnimationSystem(stream, aas);

		mAASCache[shortname] = Orphigine::AdvancedAnimationSystemPtr(aas);

	}
	Real AdvancedAnimationSystemManager::getLoadingOrder(void) const
	{
		return 300.0f;
	}

	AdvancedAnimationSystemPtr AdvancedAnimationSystemManager::getAnimationSystem(const String& name)
	{
		auto itor = mAASCache.find(name);
		if (itor != mAASCache.end())
		{
			return itor->second;
		}
		return AdvancedAnimationSystemPtr();
	}

	void AdvancedAnimationSystemManager::registerNodeFactories()
	{
		addNodeFactory(new AASAnimSequenceNodeFactory());
		addNodeFactory(new AASAnimTreeOutputNodeFactory());
		addNodeFactory(new AASBlendByDamageNodeFactory());
		addNodeFactory(new AASBlendByDirectionalNodeFactory());
		addNodeFactory(new AASBlendByIdleNodeFactory());
		addNodeFactory(new AASBlendByLifeNodeFactory());
		addNodeFactory(new AASBlendByPostureNodeFactory());
		addNodeFactory(new AASBlendByWeaponTypeNodeFactory());
		addNodeFactory(new AASBlendByRandomNodeFactory());
		addNodeFactory(new AASBlendByAttackNodeFactory());
		addNodeFactory(new AASBlendByRidingNodeFactory());
		addNodeFactory(new AASAttackAnimSequenceNodeFactory());
		addNodeFactory(new AASBlendByEquitationNodeFactory());
		addNodeFactory(new AASBlendByGuardNodeFactory());
		addNodeFactory(new AASWeaponAnimSequenceNodeFactory());
		addNodeFactory(new AASBlendByMoodNodeFactory());
		addNodeFactory(new AASMoodAnimSequenceNodeFactory());
		addNodeFactory(new AASBlendByDanceNodeFactory());
		addNodeFactory(new AASBlendByWalkNodeFactory());
		addNodeFactory(new AASCrossFadeByTimeListNodeFactory());
		addNodeFactory(new AASCrossFadeByTimeSlotNodeFactory());

		addNodeFactory(new AASWeaponAnimExtSequenceNodeFactory());
	}

	Ogre::Resource* AdvancedAnimationSystemManager::createImpl( const String& name, 
		Ogre::ResourceHandle handle, const String& group, bool isManual, Ogre::ManualResourceLoader* loader, 
		const Ogre::NameValuePairList* createParams )
	{
		return OGRE_NEW AdvancedAnimationSystem(nullptr,name,handle,group,isManual,loader);
	}

	Orphigine::AdvancedAnimationSystemPtr AdvancedAnimationSystemManager::createManual( const String& name,
		const String& groupName, Ogre::ManualResourceLoader* loader /*= 0*/ )
	{
		return AdvancedAnimationSystemPtr();
	}

	void AdvancedAnimationSystemManager::unregisterNodeFactories()
	{
		std::map<String,AASNodeFactory*>::iterator iter;
		for (iter = m_nodeFactories.begin();iter != m_nodeFactories.end();iter ++)
		{
			delete iter->second;
			iter->second = NULL;
		}
		m_nodeFactories.clear();
	}

	void AdvancedAnimationSystemManager::registerAASSerializers()
	{
		AdvancedAnimationSystemSerializer::_initSerializers();
		AASNode::_initSerializers();
		AASCrossFadeByTimeNode::_initSerializers();
		AASCrossFadeByTimeListNode::_initSerializers();
		AASCrossFadeByTimeWithMaskNode::_initSerializers();
		AASBlendByRandomNode::_initSerializers();
		AASAnimSequenceNode::_initSerializers();
	} 

	void AdvancedAnimationSystemManager::unregisterAASSerializers()
	{
		AdvancedAnimationSystemSerializer::_deinitSerializers();
		AASNode::_deinitSerializers();
		AASCrossFadeByTimeNode::_deinitSerializers();
		AASCrossFadeByTimeListNode::_deinitSerializers();
		AASCrossFadeByTimeWithMaskNode::_deinitSerializers();
		AASBlendByRandomNode::_deinitSerializers();
		AASAnimSequenceNode::_deinitSerializers();
	}
}