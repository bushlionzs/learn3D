#include "OgreHeader.h"
#include "OGModelComponent.h"
#include "OGModelComponentSerializer.h"
#include "OGResources.h"
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreSkeletonManager.h>
#include <OgreSkeleton.h>
#include <OgreSkeletonInstance.h>
#include <OgreTagPoint.h>
#include <OgreAnimation.h>
#include <OgreAnimationState.h>
#include <OgreMeshManager.h>
#include <OgreMesh.h>
#include <OgreEntity.h>
#include <OgreControllerManager.h>
#include <OgreController.h>
#include <OgreEntity.h>
#include <OgreSubEntity.h>
#include <OgreMaterialManager.h>
#include <OgreStringConverter.h>
#include <platform_log.h>
#include "OgreResourceManager.h"

//#include "utf.h"
//#include "tinyxml/tinyxml.h"



namespace Orphigine 
{
	class ModelAnimationControllerValue : public Ogre::ControllerValue<Real>
	{
	protected:
		ModelComponent* mModel;

	public:
		ModelAnimationControllerValue(ModelComponent* model)
			: mModel(model)
		{
		}

		Real getValue(void) const
		{
			return 0;
		}

		void setValue(Real value)
		{
			mModel->addTime(value);
		}
	};

	class ModelTransControllerValue : public Ogre::ControllerValue<Real>
	{
	protected:
		ModelComponent* mModel;
		float	mAlphaBegin;
		float	mAlphaEnd;
		float	mLastTime;
		float	mPassTime;
		bool	mReset;

	public:
		ModelTransControllerValue(ModelComponent* model)
			: mModel(model), mLastTime(-1), mPassTime(0), mReset(true)
		{
		}

		void	setTransparent( float nABegin, float nAEnd, float nTimeLast )
		{
			mAlphaBegin=nABegin; mAlphaEnd=nAEnd; mLastTime=nTimeLast; mPassTime=0;mReset=true;
		}

		Real getValue(void) const
		{
			return 0;
		}

		void setValue(Real value)
		{
			mPassTime += value;
			if( mPassTime > mLastTime )
			{
				if( mReset )
				{
					mModel->updateTransparent(mAlphaEnd);
					mReset = false;
				}
			}
			else
			{
				float nCurAlpha = ((mAlphaEnd - mAlphaBegin) * mPassTime)/mLastTime + mAlphaBegin;
				mModel->updateTransparent( nCurAlpha );
			}
		}
	};	

	//-----------------------------------------------------------------------
	ModelComponent::ModelComponent(Ogre::SceneNode* parent, const String& resourceName, const String& resourceGroup, bool hardwareSkin)
		: mCreator()
		, mParent(parent)
		, mUserObject()
		, mSceneNodes()
		, mMasterObjects()
		, mMovables()
		, mAnimationStates()
		, mBoundingBox()
		, mAnimationType(AT_FULL)
		, mCastShadows(false)
		, mController()
		, mTransController(NULL)
		, mResourceName(resourceName)
		, mResourceGroupName(resourceGroup)
		, mHardwareSkin(hardwareSkin)
	{
		assert(parent);
		mCreator = parent->getCreator();
		create( );
	}
	//-----------------------------------------------------------------------
	ModelComponent::~ModelComponent()
	{		
		cleanup();
	}
	//-----------------------------------------------------------------------
	void ModelComponent::setUserObject(Ogre::UserDefinedObject* userObject)
	{
		mUserObject = userObject;
		for (ObjectList::const_iterator it = mMovables.begin(); it != mMovables.end(); ++it)
		{
			Ogre::MoveObject* movable = *it;
			movable->getUserObjectBindings().setUserAny(userObject);
		}
	}
	//-----------------------------------------------------------------------
	Ogre::UserDefinedObject* ModelComponent::getUserObject(void) const
	{
		return mUserObject;
	}
	//-----------------------------------------------------------------------
	const Ogre::AxisAlignedBox& ModelComponent::getBoundingBox(void) const
	{
		return mBoundingBox;
	}
	//-----------------------------------------------------------------------
	void ModelComponent::setCastShadows(bool castShadows)
	{
		if (mCastShadows != castShadows)
		{
			mCastShadows = castShadows;
			updateCastShadows();
		}
	}
	//-----------------------------------------------------------------------
	void ModelComponent::setAnimationType(AnimationType animationType)
	{
		if (mAnimationType != animationType)
		{
			mAnimationType = animationType;
			updateAnimationType();
		}
	}
	//-----------------------------------------------------------------------
	void ModelComponent::updateCastShadows(void)
	{
		for (auto it = mMovables.begin(); it != mMovables.end(); it++)
		{
			Ogre::MoveObject* mb = *it;
			mb->setCastShadows(mCastShadows);
		}
	}
	//-----------------------------------------------------------------------
	void ModelComponent::updateAnimationType(void)
	{
		if (!mAnimationStates.empty())
		{
			switch (mAnimationType)
			{
			case AT_FULL:
				createController();
				enableAnimationStates();
				break;

			case AT_FROZE:
				destroyController();
				enableAnimationStates();
				break;

			case AT_DISABLE:
				destroyController();
				disableAnimationStates();
				break;
			}
		}
	}
	//-----------------------------------------------------------------------
	void ModelComponent::enableAnimationStates(void)
	{
		Real timePosition = Ogre::Math::UnitRandom();
		for (AnimationStateList::const_iterator it = mAnimationStates.begin();
			it != mAnimationStates.end(); ++it)
		{
			Ogre::AnimationState* as = *it;
			if (!as->getEnabled())
			{
				as->setTimePosition(timePosition * as->getLength());
				as->setEnabled(true);
			}
		}
	}
	//-----------------------------------------------------------------------
	void ModelComponent::disableAnimationStates(void)
	{
		for (AnimationStateList::const_iterator it = mAnimationStates.begin();
			it != mAnimationStates.end(); ++it)
		{
			Ogre::AnimationState* as = *it;
			if (as->getEnabled())
			{
				as->setEnabled(false);
			}
		}
	}
	//-----------------------------------------------------------------------
	void ModelComponent::createController(void)
	{
		if (!mController)
		{
			Ogre::ControllerManager& controllerManager = Ogre::ControllerManager::getSingleton();
			mController = controllerManager.createFrameTimePassthroughController(
				Ogre::ControllerValueRealPtr(new ModelAnimationControllerValue(this)));
		}
	}
	//-----------------------------------------------------------------------
	void ModelComponent::destroyController(void)
	{
		if (mController)
		{
			Ogre::ControllerManager& controllerManager = Ogre::ControllerManager::getSingleton();
			controllerManager.destroyController(mController);
			mController = NULL;
		}
		if( mTransController )
		{
			Ogre::ControllerManager& controllerManager = Ogre::ControllerManager::getSingleton();
			controllerManager.destroyController(mTransController);
			mTransController = NULL;	
		}
	}
	//-----------------------------------------------------------------------
	void ModelComponent::destroyDerivedMaterials( )
	{
		Ogre::MaterialManager* pMaterialManager = Ogre::MaterialManager::getSingletonPtr( );
		if( pMaterialManager == NULL )
			return;

		size_t size = mDerivedMaterials.size( );
		for( size_t i = 0; i < size; ++i )
		{
			if (!mDerivedMaterials[i])
				continue;

			const String& materialName = mDerivedMaterials[i]->getName( );
			mDerivedMaterials[i].reset( );

			pMaterialManager->remove( materialName );
		}

		mDerivedMaterials.clear( );
	}
	//-----------------------------------------------------------------------
	void ModelComponent::addTime(AnimationStateList& animationStates, Real offset)
	{
		for (AnimationStateList::const_iterator it = animationStates.begin(); it != animationStates.end(); ++it)
		{
			Ogre::AnimationState* animationState = *it;
			animationState->addTime(offset);
		}
	}
	//-----------------------------------------------------------------------
	void ModelComponent::addTime(Real offset)
	{
		addTime(mAnimationStates, offset);
	}
	//-----------------------------------------------------------------------
	void ModelComponent::create( )
	{
		Ogre::DataStreamPtr stream = 
			ResourceManager::getSingleton().openResource( mResourceName, mResourceGroupName );
		if(!stream)
		{
			return;
		}

		ModelComponentSerializer serializer;
		serializer.importModelComponent( stream, *this );

		updateCastShadows();
		updateAnimationType();
	}
	//-----------------------------------------------------------------------
	void ModelComponent::cleanup()
	{
		//mMaterialCopyArray.clear();
		destroyController();

		destroyObjects(mCreator, mMovables);
		mMovables.clear();

		destroyObjects(mCreator, mMasterObjects);
		mMasterObjects.clear();

		destroyDerivedMaterials( );

		for (auto it = mSceneNodes.begin(); it != mSceneNodes.end(); it++)
		{
			Ogre::SceneNode* node = *it;
			node->getCreator()->destroySceneNode(node);
		}
		mSceneNodes.clear();

		mAnimationStates.clear();

		mBoundingBox.setNull();
	}
	//-----------------------------------------------------------------------
	void ModelComponent::updateTransparent(float nNewAlpha )
	{
	}
	//-----------------------------------------------------------------------
	void ModelComponent::setTransparent( float nAlphaBegin, float nAlphaEnd, float nTimeLast )
	{
		if( mTransController == NULL )
		{
			mTransController = Ogre::ControllerManager::getSingleton().createFrameTimePassthroughController(
				Ogre::ControllerValueRealPtr(new ModelTransControllerValue(this)));
		}
		ModelTransControllerValue *p = (ModelTransControllerValue *)(mTransController->getDestination().get());
		p->setTransparent( nAlphaBegin, nAlphaEnd, nTimeLast );
	}
	//-----------------------------------------------------------------------
	bool ModelComponent::existsObject(Ogre::MoveObject* object) const
	{			
		return std::find(mMovables.begin(), mMovables.end(), object) != mMovables.end();
	}
	//-----------------------------------------------------------------------
	Ogre::SceneNode* ModelComponent::getParent( ) const
	{
		return mParent;
	}
	//-----------------------------------------------------------------------
	ModelComponent::SceneNodeList& ModelComponent::getSceneNodes( )
	{
		return mSceneNodes;
	}
	//-----------------------------------------------------------------------
	const ModelComponent::ObjectList& ModelComponent::getMasterMovableObjects( ) const
	{
		return mMasterObjects;
	}
	//-----------------------------------------------------------------------
	const ModelComponent::ObjectList& ModelComponent::getMovableObjects( ) const
	{
		return mMovables;
	}
	//-----------------------------------------------------------------------
	const ModelComponent::ObjectList& ModelComponent::getMovableObjects( const MoveObject* pMasterObject ) const
	{
		static const ModelComponent::ObjectList EMPTY_OBJECTS;

		MasterSubObjectMap::const_iterator it = mMasterSubObjectMap.find( pMasterObject );

		if ( it == mMasterSubObjectMap.end( ) )
			return EMPTY_OBJECTS;

		return it->second;
	}
	//-----------------------------------------------------------------------
	Ogre::Entity* ModelComponent::createMasterMovableObject( const Ogre::String& skeletonName )
	{
		Ogre::Entity* pEntity = NULL;

		Ogre::SkeletonPtr skeleton = std::dynamic_pointer_cast<Ogre::Skeleton>(loadCorrelativeResource( skeletonName, BLANKSTRING,
			mResourceName, mResourceGroupName));

		if (!skeleton)
		{
			return pEntity;
		}

	
		if (!skeleton->getNumBones( ) )
		{
			// Null skeleton, don't know why this happen
			static int i;
			++i;
		}
		else
		{
			// Construct fake mesh and entity
			Ogre::MeshPtr mesh = createNullMeshForSkeleton( skeleton );
			pEntity = mCreator->createEntity( mParent->getName( ) + "/" + mesh->getName( ), mesh->getName( ) );

			mMasterObjects.push_back( pEntity );
			mParent->attachObject( pEntity );

			// Merge frame structure bounding box
			mBoundingBox.merge( pEntity->getBoundingBox( ) );

			// Add predefined animations
			Ogre::AnimationState* animationState = getAnimationStateSafely( pEntity, AUTO_ANIMATION_NAME );
			if ( animationState != NULL )
			{
				mAnimationStates.push_back( animationState );
			}
			else
			{
				/// for new we always use the first anim
				if( pEntity && pEntity->getAllAnimationStates( )  )
				{
					const AnimationStateMap& aniMap = pEntity->getAllAnimationStates()->getAnimationStates();

					if (!aniMap.empty())
					{
						mAnimationStates.push_back(aniMap.begin()->second);
					}
				}

			}
		}

		return pEntity;
	}
	//-----------------------------------------------------------------------
	Ogre::Entity* ModelComponent::createMovableObject( const Ogre::String& meshName, const Ogre::MoveObject* pMasterMovableObject )
	{
		// Load the mesh
		Ogre::MeshPtr mesh = loadMesh( meshName, BLANKSTRING, mResourceName, mResourceGroupName );

		// Create the entity
		Ogre::Entity* pEntity = mCreator->createEntity( mParent->getName() + "/" + mesh->getName(), mesh);

		mMovables.push_back( pEntity );
		mMasterSubObjectMap[pMasterMovableObject].push_back( pEntity );


		pEntity->getUserObjectBindings().setUserAny(mUserObject);

		// Compute bounding box
		if ( mesh->hasSkeleton( ) )
		{
			// Merge skinned bounding box
			mBoundingBox.merge( skinningTransformBoundingBox( mesh->getBounds( ), mesh->getSkeleton( ) ) );
		}
		else
		{
			// Merge normal bounding box
			mBoundingBox.merge( mesh->getBounds( ) );
		}

		// Add predefined animations
		Ogre::AnimationState* animationState = getAnimationStateSafely( pEntity, AUTO_ANIMATION_NAME );

		if( animationState == NULL )
		{
			if( pMasterMovableObject == NULL && mesh->hasSkeleton( ) )
			{
				const AnimationStateMap& aniMap = pEntity->getAllAnimationStates()->getAnimationStates();

				if (!aniMap.empty())
				{
					animationState = aniMap.begin()->second;
				}
			}
		}

		if ( animationState != NULL )
		{
			if ( mHardwareSkin )
			{
				//DerivedMaterialsList derivedMat;
				//convertEntityToHardwareSkinning( pEntity, DerivedMat );
				deriveHardwareSkinningMaterial( *pEntity, mDerivedMaterials );
			}
			mAnimationStates.push_back( animationState );
		}

		return pEntity;
	}

}