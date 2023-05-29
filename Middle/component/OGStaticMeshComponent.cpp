#include "OgreHeader.h"
#include "OGStaticMeshComponent.h"
#include "OGActorProxy.h"
#include "OGStaticMeshActor.h"
#include "OGUtils.h"
#include <OgreControllerManager.h>
#include <OgreMeshManager.h>
#include <OgreAnimationState.h>
#include <OgreNode.h>
#include <OgreSceneManager.h>
#include <OgreSubEntity.h>
#include <OgreMaterialManager.h>
#include <OgreCamera.h>
#include "OgreStringConverter.h"
#include "OgreTextureUnit.h"

namespace Ogre {

	StaticMeshBaseComponent::StaticMeshBaseComponent()
		:beyondFogDirty(true)
	{

	}
	//-----------------------------------------------------------------------
	StaticMeshBaseComponent::StaticMeshBaseComponent(const String& name, MeshPtr& mesh, bool suppressSkeletalAnimation)
		: Entity(name, mesh), beyondFogDirty(true)
	{
	}
	//-----------------------------------------------------------------------
	StaticMeshBaseComponent::~StaticMeshBaseComponent( )
	{
		//卸载生成的材质
		mMaterialBackupList.clear( );

		//减少SubEntity的引用记数
		for( size_t i = 0; i < mSubEntityList.size(); ++i )
		{
			SubEntity* pSubEntity = getSubEntity(i);
			if( pSubEntity == NULL )
				continue;
			pSubEntity->setMaterialName( "BaseWhiteNoLighting" );
		}

		Ogre::MaterialManager* pMaterialManager = Ogre::MaterialManager::getSingletonPtr( );
		if( pMaterialManager == NULL )
			return;

		size_t size = mDerivedMaterials.size( );

		for( size_t i = 0; i < size; ++i )
		{
			if (!mDerivedMaterials[i])
				continue;
			
			const Ogre::String& materialName = mDerivedMaterials[i]->getName( );
			mDerivedMaterials[i].reset();

			pMaterialManager->remove( materialName );
		}
		
		mDerivedMaterials.clear( );
	}
	//-----------------------------------------------------------------------
	void StaticMeshBaseComponent::_notifyCurrentCamera(Camera* camera)
	{
		

		// Do nothing now
		Entity::_notifyCurrentCamera(camera);
	}
	//---------------------------------------------------------------------
	void StaticMeshBaseComponent::convertToHardwareSkinning( )
	{
		Orphigine::deriveHardwareSkinningMaterial( *this, mDerivedMaterials );
	}
	//-----------------------------------------------------------------------
	void StaticMeshBaseComponent::deriveFogMaterial( )
	{
		bool hardwareSkin = hasSkeleton( );

		size_t numSubEntities = getNumSubEntities( );
		mMaterialBackupList.resize( numSubEntities );

		for ( uint i = 0; i < numSubEntities; ++i )
		{
			SubEntity* subEntity = getSubEntity( i );
			const MaterialPtr& material = subEntity->getMaterial( );
			mMaterialBackupList[i] = material;

			if ( !material || !material->isTransparent( ) )
				subEntity->setMaterialName( "FogColor" );
		}

		if ( !hardwareSkin )
			return;

		bool deriveSucceed = true;

		for ( uint i = 0; i < numSubEntities; ++i )
		{
			SubEntity* subEntity = getSubEntity( i );
			const MaterialPtr& material = subEntity->getMaterial( );

			if ( material->isTransparent( ) )
				continue;

			MaterialPtr derivedMaterial = Orphigine::deriveHardwareSkinningMaterial( *subEntity );
			if ( derivedMaterial.get( ) != material.get( ) )
			{
				subEntity->setMaterialName( derivedMaterial->getName( ) );
				continue;
			}

			deriveSucceed = false;
			break;
		}
		
		if ( deriveSucceed )
			return;

		for ( uint i = 0; i < numSubEntities; ++i )
		{
			SubEntity* subEntity = getSubEntity( i );
			const MaterialPtr& material = mMaterialBackupList[i];

			if ( material)
				subEntity->setMaterialName( material->getName( ) );
		}
	}
	//-----------------------------------------------------------------------
	void StaticMeshBaseComponent::updateFogMaterial( )
	{
		if ( !hasSkeleton( ))
			return;

		size_t numSubEntities = getNumSubEntities();

		for ( uint i = 0; i < numSubEntities; ++i )
		{
			SubEntity* subEntity = getSubEntity(i);

			const MaterialPtr& material = subEntity->getMaterial( );
			if ( !material || material->isTransparent( ) )
				continue;

			material->getTextureUnit(0)->setColourOperationEx( Ogre::LBX_SOURCE1, Ogre::LBS_MANUAL, Ogre::LBS_CURRENT, mManager->getFogColour( ) );
		}
	}
	//-----------------------------------------------------------------------
	StaticMeshComponent::StaticMeshComponent()
		: StaticMeshBaseComponent()
		, mAutoUpdateAnimationStateList()
		, mLastUpdateTime()
	{
	}
	//-----------------------------------------------------------------------
	StaticMeshComponent::StaticMeshComponent(const String& name, MeshPtr& mesh)
		: StaticMeshBaseComponent(name, mesh)
		, mAutoUpdateAnimationStateList()
		, mLastUpdateTime()
	{
	}
	//-----------------------------------------------------------------------
	const String& StaticMeshComponent::getMovableType(void) const
	{
		return StaticMeshComponentFactory::FACTORY_TYPE_NAME;
	}
	//-----------------------------------------------------------------------
	//void StaticMeshComponent::_notifyCurrentCamera(Camera* camera)
	//{
	//	// Do nothing now
	//	Entity::_notifyCurrentCamera(camera);
	//}
	//-----------------------------------------------------------------------
	void StaticMeshComponent::_updateAutoAnimationStates(void)
	{
		Real currentTime = Ogre::ControllerManager::getSingleton().getElapsedTime();

		if (mLastUpdateTime != currentTime)
		{
			mLastUpdateTime = currentTime;

			AnimationStateList::const_iterator it, itend;
			itend = mAutoUpdateAnimationStateList.end();
			for (it = mAutoUpdateAnimationStateList.begin(); it != itend; ++it)
			{
				AnimationState* as = it->first;
				if (as->getEnabled())
				{
					Real timeOffset = it->second;
					as->setTimePosition(timeOffset + currentTime);
				}
			}
		}
	}
	//-----------------------------------------------------------------------
	void StaticMeshComponent::_updateRenderQueue(RenderQueue* queue)
	{
	}
	
	//-----------------------------------------------------------------------
	void StaticMeshComponent::addAutoUpdateAnimationState(const String& name, Real timeOffset)
	{
		AnimationState* as = getAnimationState(name);

		// Scale by animation length if time offset less than zero
		if (timeOffset < 0)
		{
			timeOffset = - timeOffset * as->getLength();
		}

		// Enable and set current time position
		as->setEnabled(true);
		as->setTimePosition(timeOffset);

		// Adjust offset by current elapsed time
		timeOffset -= Ogre::ControllerManager::getSingleton().getElapsedTime();

		mAutoUpdateAnimationStateList[as] = timeOffset;
	}
	//-----------------------------------------------------------------------
	void StaticMeshComponent::removeAutoUpdateAnimationState(const String& name)
	{
		AnimationState* as = getAnimationState(name);
		mAutoUpdateAnimationStateList.erase(as);
	}
	//-----------------------------------------------------------------------
	void StaticMeshComponent::removeAllAutoUpdateAnimationStates(void)
	{
		mAutoUpdateAnimationStateList.clear();
	}
	//-----------------------------------------------------------------------
	const StaticMeshComponent::AnimationStateList& StaticMeshComponent::getAutoUpdateAnimationStateList(void) const
	{
		return mAutoUpdateAnimationStateList;
	}
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	MoveObject* StaticMeshBaseComponentFactory::createInstanceImpl(const String& name, const NameValuePairList* params)
	{
		// must have mesh parameter
		MeshPtr pMesh;
		bool suppressSkeletalAnimation = false;
		if (params != 0)
		{
			NameValuePairList::const_iterator ni = params->find("mesh");
			if (ni != params->end())
			{
				// Get mesh (load if required)
				pMesh = MeshManager::getSingleton().load(
					ni->second);
			}

			ni = params->find("suppressSkeletalAnimation");
			if (ni != params->end())
			{
				suppressSkeletalAnimation =
					StringConverter::parseBool(ni->second);
			}
		}		
		if (!pMesh)
		{
			OGRE_EXCEPT(Exception::ERR_INVALIDPARAMS,
				"'mesh' parameter required when constructing an Entity.",
				"EntityFactory::createInstance");
		}

		return OGRE_NEW StaticMeshBaseComponent(name, pMesh, suppressSkeletalAnimation);
	}
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	String StaticMeshComponentFactory::FACTORY_TYPE_NAME = "StaticMeshComponent";
	//-----------------------------------------------------------------------
	const String& StaticMeshComponentFactory::getType(void) const
	{
		return FACTORY_TYPE_NAME;
	}
	//-----------------------------------------------------------------------
	MoveObject* StaticMeshComponentFactory::createInstanceImpl(const String& name,
		const NameValuePairList* params)
	{
		// must have mesh parameter
		MeshPtr mesh;
		if (params)
		{
			NameValuePairList::const_iterator ni = params->find("mesh");
			if (ni != params->end())
			{
				const String& meshName = ni->second;

				// Get mesh (load if required)
				mesh = MeshManager::getSingleton().load(meshName);
			}
		}

		if (!mesh)
		{
			OGRE_EXCEPT(Exception::ERR_INVALIDPARAMS, 
				"'mesh' parameter required when constructing an StaticMeshComponent.", 
				"StaticMeshComponentFactory::createInstance");
		}

		return new StaticMeshComponent(name, mesh);
	}
	//-----------------------------------------------------------------------
	void StaticMeshComponentFactory::destroyInstance( MoveObject* obj)
	{
		delete obj;
	}

} // namespace
