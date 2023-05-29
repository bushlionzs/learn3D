#ifndef OGModelComponent_h__
#define OGModelComponent_h__

#include "OGUtils.h"
#include <OgreAxisAlignedBox.h>
#include <OgreDataStream.h>
#include "OgreUserDefinedObject.h"
#include "OgreController.h"
// ----------------------------------------------------------------------------
// classes
// ----------------------------------------------------------------------------

class Ogre::Serializer;

namespace Orphigine 
{

	class  ModelComponent
	{
	public:
		typedef std::list<Ogre::SceneNode*> SceneNodeList;
		typedef std::list<Ogre::MoveObject*> ObjectList;

	protected:
		typedef std::list<Ogre::AnimationState*> AnimationStateList;
		typedef std::map<const Ogre::MoveObject*, ObjectList> MasterSubObjectMap;

		Ogre::SceneManager*			mCreator;
		Ogre::SceneNode*			mParent;
		Ogre::UserDefinedObject*	mUserObject;
		SceneNodeList				mSceneNodes;
		ObjectList					mMasterObjects;
		ObjectList					mMovables;
		MasterSubObjectMap			mMasterSubObjectMap;
		AnimationStateList			mAnimationStates;
		Ogre::AxisAlignedBox		mBoundingBox;
		bool						mCastShadows;
		AnimationType				mAnimationType;
		Ogre::Controller<Real>*		mController;
		Ogre::Controller<Real>*		mTransController;

		Ogre::String				mResourceName;
		Ogre::String				mResourceGroupName;

		bool						mHardwareSkin;

		//所有LogicModel自己生成的材质名集合，用于卸载
		DerivedMaterialsList		mDerivedMaterials;

	public:
		ModelComponent(Ogre::SceneNode* parent, const String& resourceName, const String& resourceGroup, bool hardwareSkin = true);
		virtual ~ModelComponent();

		void setUserObject(Ogre::UserDefinedObject* userObject);
		Ogre::UserDefinedObject* getUserObject(void) const;

		/// Gets the bounding box
		const Ogre::AxisAlignedBox& getBoundingBox(void) const;

		void setCastShadows(bool castShadows);

		bool getCastShadows(void) const
		{
			return mCastShadows;
		}

		void updateTransparent(float nNewAlpha );
		void setTransparent( float nAlphaBegin, float nAlphaEnd, float nTimeLast );

		void setAnimationType(AnimationType animationType);

		AnimationType getAnimationType(void) const
		{
			return mAnimationType;
		}

		/// Modifies the time position
		void addTime(Real offset);

		bool existsObject(Ogre::MoveObject* object) const;

		const std::list< Ogre::MoveObject* >	&GetObjList()	const {return mMovables;}

		Ogre::SceneNode* getParent( ) const;
		SceneNodeList& getSceneNodes( );

		const ObjectList& getMasterMovableObjects( ) const;
		const ObjectList& getMovableObjects( ) const;
		const ObjectList& getMovableObjects( const Ogre::MoveObject* pMasterObject ) const;

		Ogre::Entity* createMasterMovableObject( const Ogre::String& skeletonName );
		Ogre::Entity* createMovableObject( const Ogre::String& meshName, const Ogre::MoveObject* pMasterMovableObject = NULL );

	protected:
		void create();
		void cleanup();

		void updateCastShadows(void);
		void updateAnimationType(void);
		void enableAnimationStates(void);
		void disableAnimationStates(void);
		void createController(void);
		void destroyController(void);
		void destroyDerivedMaterials();

		static void addTime(AnimationStateList& animationStates, Real offset);
	};

}

#endif // OGModelComponent_h__