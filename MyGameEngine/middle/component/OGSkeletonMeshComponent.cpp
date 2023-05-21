#include "OgreHeader.h"
#include "OGSkeletonMeshComponent.h"
#include "OGUtils.h"
#include "OGFlags.h"
#include "OGImpactManager.h"
#include "OGSpell.h"
#include "OGSpellRibandModule.h"
#include "OGSpellImpactModule.h"
#include "OGSpellSoundModule.h"
#include "OGImpactProjectorModule.h"
#include "OGSpellSceneLightModule.h"
#include "OGMainSceneLight.h"
#include "OGBulletSystem.h"
#include "OGBulletSystemManager.h"
#include "OGBulletFlowSystem.h"
#include "OGBulletFlowSystemManager.h"
#include "OGSpellBulletFlowModule.h"
#include "OGBulletCallbacks.h"
#include "OGSpellModelModule.h"
#include "OGSpellManager.h"

#include "OGAdvancedAnimationSystem.h"
#include "OGAdvancedAnimationSystemInstance.h"
#include "OGAdvancedAnimationSystemManager.h"
#include "OGAASAnimSequenceNode.h"
#include "OGAASAnimation.h"
#include "OgreString.h"
#include <platform_log.h>
#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include <OgreStringConverter.h>
#include <OgreSkeletonInstance.h>
#include <OgreBone.h>
#include <OgreSubEntity.h>
#include <OgreSubMesh.h>
#include <OgreMaterialManager.h>
#include <OgreCamera.h>
#include <OgreAxisAlignedBox.h>
#include <OgreAnimation.h>
#include <OgreSkeletonManager.h>
#include <OgreTextureManager.h>
#include <OgreMeshManager.h>
#include <OgreSubMesh.h>
#include "OgreRoot.h"
#include "OgreMeshManager.h"
#include "OGSkeletonMeshComponentSerializer.h"
#include "engine_manager.h"
#include "OgreSceneManager.h"
#include "OGEffectActor.h"

#include <iomanip>

#define EFFECT_RESTRICT 1 //是否限制effect的数量
namespace Orphigine	
{

	OnPlaySound SkeletonMeshComponent::mOnPlaySound = NULL;
	OnStopSound SkeletonMeshComponent::mOnStopSound = NULL;
	GetHeightInWorld SkeletonMeshComponent::mGetHeightInWorld = NULL;

	String SkeletonMeshComponent::HAIR_MESH_NAME = "HairMesh";

#define MAX_DELTA_HEIGHT 550.0f
#define  MIN_DELTA_ROTATION_DEGREE 10.0f
#define  MAX_DELTA_TANGENT 0.83f

	//////////////////////////////////////////////////////////////////////////
	//-----------------------------------------------------------------------
	const Ogre::ColourValue& _getColourFromMaterial(const Ogre::MaterialPtr& mat)
	{
		assert (mat);

		const Ogre::ColourValue realZero(0.0,0.0,0.0,1.0);

		return mat->getSelfIllumination();
	}

	//从旧材质生成两个新的材质实例(原材质的克隆体和带透明属性的继承材质)
	SkeletonMeshComponent::ModelMaterialInstance::ModelMaterialInstance(const Ogre::MaterialPtr& origin) 
		: mClonedOriginMat()
		, mClonedDeriveMat()
	{
		static int ModelMaterialInstanceIndex=0;
		
		
		//mClonedDeriveMat->compile();
	}
	//-----------------------------------------------------------------------
	SkeletonMeshComponent::ModelMaterialInstance::~ModelMaterialInstance()
	{
		//简单的remove材质是远远不够的，必须正确的设置引用计数，而且要先unload再remove
		if (mClonedDeriveMat)
		{
			String clonedDerivedMatName = mClonedDeriveMat->getName();
			mClonedDeriveMat.reset();
			Ogre::MaterialManager::getSingleton().remove(clonedDerivedMatName);
		}
	}
	//////////////////////////////////////////////////////////////////////////
	//添加材质，返回索引
	size_t SkeletonMeshComponent::EntityTransparentor::addMaterial(const Ogre::MaterialPtr& material)
	{
		size_t index = 0;
		MaterialInstanceList::const_iterator it, itend;
		itend = mMaterialInstances.end();
		for (it = mMaterialInstances.begin(); it != itend; ++it, ++index)
		{
			ModelMaterialInstance* materialInstance = *it;
			if (materialInstance->mClonedOriginMat->getName() == material->getName())
				return index;
		}
		mMaterialInstances.push_back(new ModelMaterialInstance(material));


		return index;
	}
	//-----------------------------------------------------------------------
	SkeletonMeshComponent::EntityTransparentor::EntityTransparentor(void)
		: mEntity(NULL), mParentNode(0)
	{
	}
	//-----------------------------------------------------------------------
	SkeletonMeshComponent::EntityTransparentor::EntityTransparentor(Ogre::Entity* entity)
		: mEntity(NULL), mParentNode(0)
	{
		init(entity);
	}
	//-----------------------------------------------------------------------
	SkeletonMeshComponent::EntityTransparentor::~EntityTransparentor()
	{
		clear();
	}
	//-----------------------------------------------------------------------
	void SkeletonMeshComponent::EntityTransparentor::clear(void)
	{
		MaterialInstanceList::const_iterator it, itend;
		itend = mMaterialInstances.end();
		for (it = mMaterialInstances.begin(); it != itend; ++it)
		{
			ModelMaterialInstance* materialInstance = *it;
			delete materialInstance;
		}
		mMaterialInstances.clear();
		mSubEntityMaterialIndices.clear();
	}
	//-----------------------------------------------------------------------
	void SkeletonMeshComponent::EntityTransparentor::init(Ogre::Entity* entity)
	{
		clear();
		mEntity = entity;
		size_t numSubEntities = mEntity->getNumSubEntities();
		mSubEntityMaterialIndices.resize(numSubEntities);
		for (uint i = 0; i < numSubEntities; ++i)
		{
			Ogre::SubEntity* subEntity = mEntity->getSubEntity(i);
			const Ogre::MaterialPtr& material = subEntity->getMaterial();
			size_t index = addMaterial(material);
			mSubEntityMaterialIndices[i] = index;
		}
	}
	//-----------------------------------------------------------------------
	void SkeletonMeshComponent::EntityTransparentor::apply(Real transparency)
	{
		assert(mEntity);

		size_t numSubEntities = mEntity->getNumSubEntities();
		/*
		下面的代码会导致人出现时闪一下，先注掉
		if (transparency >= 1)
		{
			// Complete transparency, just as invisible
			mEntity->setVisible(false);
		}
		else if (transparency <= 0)	*/
		if (transparency <= 0)
		{
			// Complete opaque, just as origin
			mEntity->setVisible(true);
			for (uint i = 0; i < numSubEntities; ++i)
			{
				Ogre::SubEntity* subEntity = mEntity->getSubEntity(i);
				subEntity->setMaterialName(mMaterialInstances[mSubEntityMaterialIndices[i]]->mClonedOriginMat->getName());
			}
		}
		else//在0～1之间
		{
			// Derive transparency material first
			MaterialInstanceList::const_iterator it, itend;
			itend = mMaterialInstances.end();
			for (it = mMaterialInstances.begin(); it != itend; ++it)
			{
				ModelMaterialInstance* materialInstance = *it;
				applyTransparency(materialInstance->mClonedDeriveMat, transparency);
			}

			// Applies derived transparency material to sub-entities.
			mEntity->setVisible(true);
			for (uint i = 0; i < numSubEntities; ++i)
			{
				Ogre::SubEntity* subEntity = mEntity->getSubEntity(i);
				subEntity->setMaterialName(mMaterialInstances[mSubEntityMaterialIndices[i]]->mClonedDeriveMat->getName());//更新材质
			}
		}
	}
	//-----------------------------------------------------------------------
	bool SkeletonMeshComponent::EntityTransparentor::applyTransparency(const Ogre::MaterialPtr& derived, Real transparency)
	{
		

		return false;
	}
	//-----------------------------------------------------------------------
	// MovableListener
	class SkeletonMeshMovableListener : public Ogre::MoveObject
	{
	public:
		virtual bool objectRendering(const Ogre::MoveObject* object, const Ogre::Camera* camera)
		{
			return camera == NULL ? true : !false;
		}
	};
	//-----------------------------------------------------------------------
	SkeletonMeshComponent::SkeletonMeshComponent(const String& name,int type) :
	mSkeletonMeshType(type),
	mName(name),
		mModelSceneNode(NULL),
		mModelSceneNodeName(""),
		mParentNode(NULL),
		mSkeletonEntity(NULL),
		mCreatedEntityCount(0),
		mSkeleton(NULL),
		mFullBoundingBox(NULL),
		mIsPrepareBoundBox(false),

		mCurrentAnimationState(NULL),
		mFadeOutAnimationState(NULL),

		mFadeOutDelay(0.0f),
		mCurrentAnimationName(""),
		mAnimationLoop(false),

		mEnableEffectScale(false),
		mEffectHandleCount(0),
		mCurrentSkill(NULL),

		mOnAnimationFinish(NULL),
		mOnSkillBreakTime(NULL),
		mOnSkillHitTime(NULL),
		mOnSkillShakeTime(NULL),
		mOnGetEffectName(NULL),
		mCallbackFuncInfo(0),
		mAnimEditing(false),
		mAnimationTimePos(0.0f),
		mChildModel(false),
		mSceneNodeNeedUpdate(false),
		mPoseType(PT_NORMAL),
		mModelPosition(Ogre::Vector3::ZERO),
		mModelOrientation(Ogre::Quaternion::IDENTITY),
		mCurrentTransparency(0.0f),
		mDestTransparency(0.0f),
		mNeedUpdateTransparency(false),
		mTransparencyTime(0.0f),
		mDefaultAnimationName(""),
		mHairColour(Ogre::ColourValue::Black),
		mShadowCastable(true),//更改默认值，与ogre内部的MovableObject中的mCastShadows值保持一致
		mAttachParent(NULL),
		mSelected(false),
		mExternalBoundingBox(NULL),
		mWorldBoundingBox(NULL),
		mExternalBoundingBoxValue(""),
		mExternalScaleFactor(Ogre::Vector3::UNIT_SCALE),
		mColliderSet(NULL),
		mTerrainHeight(Ogre::Math::POS_INFINITY),
		mVisibleFlag(OVF_DEFAULT),
		mEnableWalkingEffect(true),
		mIsActive(true),
		mVisible(false),
		mFrontBackOrientation(Ogre::Quaternion::IDENTITY),
		mLeftRightOrientation(Ogre::Quaternion::IDENTITY),
		m_advancedAnimationSystem(NULL),
		m_advancedAnimationSystemName(""),
		m_animEndCallbackAAS(NULL),
		m_animPlayCallbackAAS(NULL),
		m_callbackInfoAAS(0),
		m_isAnimForCurrentSkillStart(false),
		m_AnimationTimePosForCurrentSkill(0.0f),
		m_animStateForCurrentSkillCache(NULL),
		m_isForceIgnoreAAS(false),
		m_skillRate(1.0f),
		m_skelControlTimeLeft(0.0f),
		m_skelControlTargetAngleRadian(0.0f),
		m_skelContrlCurrentAngleRadian(0.0f),
		m_isViewFrustumVisible(false),
		mOrigParentNode(NULL),
		mHaveLogicModelShadow(false)
	{
		mUserAny = Ogre::Any();

		mAttribMap.clear();
		mEntityMap.clear();
		mLocatorMap.clear();
		mEffectMap.clear();
		mAttachedModelOriginSceneNodes.clear();
		mModelProjectors.clear();
		mShadowUncastableMeshs.clear();
		mMaterialMap.clear();
		mCreatedEffectList.clear();
	}
	//-----------------------------------------------------------------------
	SkeletonMeshComponent::~SkeletonMeshComponent()
	{
		try
		{
			AttachedModelOriginSceneNodes::iterator it, next;
			
			for (it = mAttachedModelOriginSceneNodes.begin(); it != mAttachedModelOriginSceneNodes.end(); it = next)
			{
				next = it; next ++;
				SkeletonMeshComponent * child = it->first;
				detachModel(child);
			}		
			
			if (mAttachParent)
			{
				mAttachParent->detachModel(this);
			}
		}
		
		catch(...) 
		{
			
		}
		try
		{
			if (mWorldBoundingBox)
			{
				delete mWorldBoundingBox;
				mWorldBoundingBox=NULL;
			}
		}
		
		catch(...) 
		{
			WARNING_LOG("delete mWorldBoundingBox Failed.--SkeletonMeshComponent::~LogicModell");
		}
		try
		{

			if (mExternalBoundingBox)
			{
				delete mExternalBoundingBox;
				mExternalBoundingBox=NULL;
			}
		}
		catch( const std::exception& e )
		{
			Ogre::String strCPPException = e.what();
			Ogre::String Msg = "delete mExternalBoundingBox Failed:" + strCPPException + "--SkeletonMeshComponent::~SkeletonMeshComponent";
		}
		catch(...) 
		{
			WARNING_LOG("delete mExternalBoundingBox Failed.--SkeletonMeshComponent::~SkeletonMeshComponent");
		}
		try
		{
			if (mFullBoundingBox)
			{
				delete mFullBoundingBox;
				mFullBoundingBox=NULL;
			}
		}
		catch( const std::exception& e )
		{
			Ogre::String strCPPException = e.what();
			Ogre::String Msg = "delete mFullBoundingBox Failed:" + strCPPException + "--SkeletonMeshComponent::~SkeletonMeshComponent";
		}
		catch(...) 
		{
		
		}		
		try
		{
			// 先删除挂在自己身上的model（如武器等）
			mLocatorMap.clear();

			mShadowUncastableMeshs.clear();

			mAttribMap.clear();
		}
		
		catch(...) 
		{
			WARNING_LOG("LocatorMap clear Failed.--SkeletonMeshComponent::~SkeletonMeshComponent");
		}
		try
		{
			_delAllProjector();
		}
	
		catch(...) 
		{
			
		}
		try
		{
			destroyEntities();
		}
		catch( const std::exception& e )
		{
			Ogre::String strCPPException = e.what();
			Ogre::String Msg = "destroyEntities Failed:" + strCPPException + "--SkeletonMeshComponent::~SkeletonMeshComponent";
		
		}
		catch(...) 
		{
			
		}
		try
		{
			_delSkeletonEntity();
		}
		catch( const std::exception& e )
		{
			Ogre::String strCPPException = e.what();
			Ogre::String Msg = "_delSkeletonEntity Failed:" + strCPPException + "--SkeletonMeshComponent::~SkeletonMeshComponent";
			
		}
	
		try
		{
			destroySceneNode();
		}
		catch( const std::exception& e )
		{
			Ogre::String strCPPException = e.what();
			Ogre::String Msg = "destroySceneNode Failed:" + strCPPException + "--SkeletonMeshComponent::~SkeletonMeshComponent";
			
		}
		
		
		{
			delAllEffect();
		}
		
		
		{
			delCurrentSkill();
		}
		

		try
		{
			_deleteAdvancedAnimationSystemInstance();
		}
	
		catch(...) 
		{
			WARNING_LOG("_deleteAdvancedAnimationSystemInstance Failed.--SkeletonMeshComponent::~SkeletonMeshComponent");
		}
		//卸载继承的材质
		
		{
			destroyDerivedMaterial( );
		}
		
		
	}
	//-----------------------------------------------------------------------
	void reset(void)
	{

	}
	//-----------------------------------------------------------------------
	bool SkeletonMeshComponent::addAttribute( const String &name, const String &value,const AttributeTypeEnum& type)
	{
		AttribMap::iterator i = mAttribMap.find(name);

		if ( i != mAttribMap.end() )
		{
			//WARNING_LOG( "Logic Model Attribute with name '" + name + "' already exists! " +
			//	"SkeletonMeshComponent::addAttribute " + mName, Ogre::LML_TRIVIAL );

			return false;
		}

		std::pair<AttribMap::iterator, bool> inserted = 
			mAttribMap.insert( AttribMap::value_type( name, AttribValue(value, type) ) );

		if (false == inserted.second)
		{
			//WARNING_LOG( "Logic Model Attribute with name '" + name + "' inserted failed! " +
			//	"SkeletonMeshComponent::addAttribute " + mName, Ogre::LML_TRIVIAL);

			return false;
		}
		// 处理其他类型的属性
		_dealWithExtraAttributes(name, value);

		return true;
	}
	//-----------------------------------------------------------------------
	bool SkeletonMeshComponent::changeAttribute( const String &name, const String &value )
	{
		AttribMap::iterator i = mAttribMap.find(name);

		if ( i == mAttribMap.end() )
		{
			//WARNING_LOG( "Logic Model Attribute with name '" + name + "' doesn't exists! " +
			//	"SkeletonMeshComponent::changeAttribute " + mName,Ogre::LML_TRIVIAL);

			return false;
		}

		AttribValue& tempValue = i->second;

		// 如果当前属性值就是要设置的值，直接返回
		if (tempValue.mAttribValue == value)
			return true;

		// 判断hint
		if ( tempValue.mAttributeType == AT_ENTITY_MESH_NAME )
		{
			if ( changeEntity(name, value) )
			{
				tempValue.mAttribValue = value;
				return true;
			}
		}
		else if ( tempValue.mAttributeType == AT_SLOT_NAME )
		{
			if ( changeSlotModelName(name, value) )
			{
				tempValue.mAttribValue = value;
				return true;
			}
		}	
		else if ( tempValue.mAttributeType == AT_MATERIAL_NAME )
		{
			if ( changeMaterial(name, value) )
			{
				tempValue.mAttribValue = value;
				return true;
			}
		}
		else
		{
			// 处理其他类型的属性
			_dealWithExtraAttributes(name, value);
		}

		return false;
	}
	bool SkeletonMeshComponent::getNewAttributeRequestLoadRes(const String &name,const String &value, Ogre::OResourcePtrMap& HaveResName, Ogre::OStringSet& NoResName)
	{
		return false;
	}
	bool SkeletonMeshComponent::changeAttributes( const std::vector<String> &names, const std::vector<String> &values )
	{
		bool Result = false;
		if(names.size()!=values.size())
			return Result;
		int vecLen = names.size();
		for(int vecIndex = 0 ; vecIndex != vecLen ; ++ vecIndex)
		{
			if(!changeAttribute(names[vecIndex],values[vecIndex]))
				Result = false;
		}
		return Result;
	}
	//-----------------------------------------------------------------------
	bool SkeletonMeshComponent::getAttribute( const String& name, String& value)
	{
		AttribMap::iterator i = mAttribMap.find(name);

		if ( i == mAttribMap.end() )
		{
			//WARNING_LOG( "Logic Model Attribute with name '" + name + "' doesn't exists! " +
			//    "SkeletonMeshComponent::getAttribute " + mName );
			return false;
		}

		value = i->second.mAttribValue;

		return true;
	}
	//-----------------------------------------------------------------------
	Variant SkeletonMeshComponent::getAttribute( const String& attributeName )
	{
		AttribMap::iterator i = mAttribMap.find(attributeName);

		if ( i == mAttribMap.end() )
		{
			//WARNING_LOG( "Logic Model Attribute with name '" + attributeName + "' doesn't exists! " +
			//    "SkeletonMeshComponent::getAttribute " + mName );

			return Variant();
		}

		AttribValue& tempValue = i->second;

		// 判断hint
		if ( tempValue.mAttributeType == AT_SLOT_NAME )
		{
			for ( LocatorMap::iterator itLocator = mLocatorMap.begin();
				itLocator != mLocatorMap.end(); ++itLocator )
			{
				LocatorValue& tempLocatorValue = itLocator->second;

				SlotMap::iterator itSlot = tempLocatorValue.mSlotMap.find(attributeName);

				if ( itSlot != tempLocatorValue.mSlotMap.end() )
				{
					SlotValue& tempSlotValue = itSlot->second;

					return tempSlotValue.mModel;
				}			
			}
		}

		return Variant();
	}
	//-----------------------------------------------------------------------
	SkeletonMeshComponent* SkeletonMeshComponent::getAttributePtr( const String& attributeName )
	{
		AttribMap::iterator i = mAttribMap.find(attributeName);

		if ( i == mAttribMap.end() )
		{
			//WARNING_LOG( "Logic Model Attribute with name '" + attributeName + "' doesn't exists! " +
			//    "SkeletonMeshComponent::getAttribute " + mName );

			return NULL;
		}

		AttribValue& tempValue = i->second;

		// 判断hint
		if ( tempValue.mAttributeType == AT_SLOT_NAME )
		{
			for ( LocatorMap::iterator itLocator = mLocatorMap.begin();
				itLocator != mLocatorMap.end(); ++itLocator )
			{
				LocatorValue& tempLocatorValue = itLocator->second;

				SlotMap::iterator itSlot = tempLocatorValue.mSlotMap.find(attributeName);

				if ( itSlot != tempLocatorValue.mSlotMap.end() )
				{
					SlotValue& tempSlotValue = itSlot->second;

					return tempSlotValue.mModel;
				}			
			}
		}

		return NULL;
	}
	bool SkeletonMeshComponent::setWeaponEffect( const String& EffectName, const String& LocatorName,WeaponEnum WeaponType, int priority)
	{
		if(EffectName==String("") || LocatorName==String(""))
			return false;
		SkeletonMeshComponent* pWeaponModel = NULL;
		switch(WeaponType)
		{
		case WE_LEFT:
			pWeaponModel = getAttributePtr("LeftWeaponObj");
			break;
		case WE_LEFT_SHIELD:
			pWeaponModel = getAttributePtr("LeftShieldObj");
			break;
		case WE_RIGHT:
			pWeaponModel = getAttributePtr("RightWeaponObj");
			break;
		}
		if(pWeaponModel)
		{
			//pWeaponModel->addEffect(EffectName,LocatorName, Orphigine::SkeletonMeshComponent::GTIT_ALL);
			pWeaponModel->addEffect(EffectName,LocatorName, Orphigine::SkeletonMeshComponent::GTIT_ALL, Ogre::ColourValue::White, 0, priority);
			return true;
		}
		return false;
	}	
	bool SkeletonMeshComponent::clearWeaponEffect(WeaponEnum WeaponType)
	{
		SkeletonMeshComponent* pWeaponModel = NULL;
		switch(WeaponType)
		{
		case WE_LEFT:
			pWeaponModel = getAttributePtr("LeftWeaponObj");
			break;
		case WE_LEFT_SHIELD:
			pWeaponModel = getAttributePtr("LeftShieldObj");
			break;
		case WE_RIGHT:
			pWeaponModel = getAttributePtr("RightWeaponObj");
			break;
		}
		if(pWeaponModel)
		{
			pWeaponModel->delAllEffect();
			return true;
		}			
		return false;
	}	
	bool SkeletonMeshComponent::changeWeaponAction(AdvancedAnimationSystemMonitoringDegree eAction,float fDegree,WeaponEnum WeaponType)
	{
		SkeletonMeshComponent* pWeaponModel = NULL;
		switch(WeaponType)
		{
		case WE_LEFT:
			pWeaponModel = getAttributePtr("LeftWeaponObj");
			break;
		case WE_LEFT_SHIELD:
			pWeaponModel = getAttributePtr("LeftShieldObj");
			break;
		case WE_RIGHT:
			pWeaponModel = getAttributePtr("RightWeaponObj");
			break;
		}
		if(pWeaponModel)
		{
			pWeaponModel->setAASMonitoringDegree(eAction,fDegree);
			return true;
		}			
		return false;		
	}	
	bool SkeletonMeshComponent::changeWeaponActionSpeed(float fRate,WeaponEnum WeaponType)
	{
		SkeletonMeshComponent* pWeaponModel = NULL;
		switch(WeaponType)
		{
		case WE_LEFT:
			pWeaponModel = getAttributePtr("LeftWeaponObj");
			break;
		case WE_LEFT_SHIELD:
			pWeaponModel = getAttributePtr("LeftShieldObj");
			break;
		case WE_RIGHT:
			pWeaponModel = getAttributePtr("RightWeaponObj");
			break;
		}
		if(pWeaponModel)
		{
			pWeaponModel->setGlobalAnimationRate(fRate);
			return true;
		}			
		return false;		
	}	
	//-----------------------------------------------------------------------
	bool SkeletonMeshComponent::hasAttribute( const String& name )
	{
		AttribMap::iterator i = mAttribMap.find(name);

		return ( i != mAttribMap.end() );
	}
	//-----------------------------------------------------------------------
	bool SkeletonMeshComponent::addEntity( const String &name, const String &meshName, const String &matName )
	{
		EntityMap::iterator i = mEntityMap.find(name);

		if ( i != mEntityMap.end() )
		{


			return false;
		}

		std::pair<EntityMap::iterator, bool> inserted = 
			mEntityMap.insert( EntityMap::value_type( name, EntityValue(meshName, matName) ) );

		if (false == inserted.second)
		{


			return false;
		}

		return true;
	}
	//-----------------------------------------------------------------------
	bool SkeletonMeshComponent::changeEntity( const String &name, const String &value )//value是mesh的名字
	{
		EntityMap::iterator i = mEntityMap.find(name);

		if ( i == mEntityMap.end() )
		{
			return false;
		}

		EntityValue& tempValue = i->second;

		// 删除原有的entity
		if (tempValue.mEntity)
		{
			_destroyEntityImpl(tempValue.mEntity);
			tempValue.mEntity = NULL;

			// 删除原有的transparentor
			if (tempValue.mTransparentor)
			{
				delete tempValue.mTransparentor;
				tempValue.mTransparentor = NULL;
			}

			// 删除clone过的material
			_clearEntityColorMaterials(tempValue);

			//卸载继承的材质
			destroyDerivedMaterial( );				
		}

		if (false == value.empty())
		{
			tempValue.mMeshName =  value; //dscky add//////
			tempValue.mEntity = _createEntityImpl(value);

			if( tempValue.mEntity == NULL )
				return false;

			if (tempValue.mEntityColourChanged)
				_setEntityColour(tempValue, tempValue.mEntityColour);

			if (mCurrentTransparency > 0.0f)
			{
				tempValue.mTransparentor = new EntityTransparentor(tempValue.mEntity);
				tempValue.mTransparentor->apply(mCurrentTransparency);
			}			
		}

		// 如果在obj文件中没定义包围盒的大小，就根据entity创建包围盒
		if (NULL == mExternalBoundingBox)
			_updateBoundingBox();

		return true;
	}
	//-----------------------------------------------------------------------
	bool SkeletonMeshComponent::addMaterial( const String &name, const String &entityEntry, const String &matName )
	{
		MaterialMap::iterator i = mMaterialMap.find(name);

		if ( i != mMaterialMap.end() )
		{


			return false;
		}

		std::pair<MaterialMap::iterator, bool> inserted = 
			mMaterialMap.insert( MaterialMap::value_type( name, MaterialValue(entityEntry, matName) ) );

		if (false == inserted.second)
		{


			return false;
		}

		return true;
	}
	//-----------------------------------------------------------------------
	bool SkeletonMeshComponent::changeMaterial( const String &name, const String &value )
	{
		MaterialMap::iterator i = mMaterialMap.find(name);

		if ( i == mMaterialMap.end() )
		{


			return false;
		}

		MaterialValue& tempValue = i->second;

		if ( _setEntityMaterial(tempValue.mEntityEntry, value) )
		{
			tempValue.mMaterialName = value;

			return true;
		}
		else
			return false;
	}
	//-----------------------------------------------------------------------
	bool SkeletonMeshComponent::addLocator( const String &name, const String &boneName, 
		const Ogre::Vector3 &pos, const Ogre::Quaternion &orientation, bool transferable, bool translateFirst,bool childInheritScale
		,const String & destLocatorName)
	{
		LocatorMap::iterator i = mLocatorMap.find(name);

		if ( i != mLocatorMap.end() )
		{


			return false;
		}

		std::pair<LocatorMap::iterator, bool> inserted = 
			mLocatorMap.insert( LocatorMap::value_type( name, 
			LocatorValue(boneName, pos, orientation, transferable, translateFirst, childInheritScale,destLocatorName) ) );

		if (false == inserted.second)
		{


			return false;
		}

		return true;
	}
	//-----------------------------------------------------------------------
	bool SkeletonMeshComponent::isLocatorTransferable(const String& name)
	{
		LocatorMap::iterator i = mLocatorMap.find(name);

		if (i != mLocatorMap.end())
		{
			return i->second.mTransferable;
		}
		else
			return false;
	}
	//-----------------------------------------------------------------------
	bool SkeletonMeshComponent::isLocatorExist(const String& locator)
	{
		LocatorMap::iterator i = mLocatorMap.find(locator);

		if (i != mLocatorMap.end())
		{
			return true;
		}
		else
			return false;
	}
	//-----------------------------------------------------------------------
	bool SkeletonMeshComponent::getLocatorInfo(const String& locator, LocatorValue& locatorInfo)
	{
		LocatorMap::const_iterator i = mLocatorMap.find(locator);

		if (i != mLocatorMap.end())
		{
			locatorInfo = i->second;
			return true;
		}
		else
			return false;
	}
	//-----------------------------------------------------------------------
	bool SkeletonMeshComponent::setLocatorInfo(const String& locator, const LocatorValue& info)
	{
		LocatorMap::iterator i = mLocatorMap.find(locator);

		if (i != mLocatorMap.end())
		{
			i->second = info;
			return true;
		}
		else
			return false;
	}
	//-----------------------------------------------------------------------
	bool SkeletonMeshComponent::addSlot( const String &locatorName, const String &slotName, const String &modelName)
	{
		LocatorMap::iterator i = mLocatorMap.find(locatorName);

		if ( i == mLocatorMap.end() )
		{
		

			return false;
		}

		SlotMap &slotMap = i->second.mSlotMap;
		std::pair<SlotMap::iterator, bool> inserted = 
			slotMap.insert( SlotMap::value_type( slotName, SlotValue(modelName) ) );

		if (false == inserted.second)
		{


			return false;
		}

		return true;
	}  
	//-----------------------------------------------------------------------
	bool SkeletonMeshComponent::changeSlotModelName( const String &name, const String &value )
	{
		for ( LocatorMap::iterator itLocator = mLocatorMap.begin();
			itLocator != mLocatorMap.end(); ++itLocator )
		{
			LocatorValue& tempLocatorValue = itLocator->second;

			SlotMap::iterator itSlot = tempLocatorValue.mSlotMap.find(name);

			if ( itSlot != tempLocatorValue.mSlotMap.end() )
			{
				SlotValue& tempSlotValue = itSlot->second;

				// 如果value是""，就删除原有的物体
				if ( value.empty() )
				{
					if (tempSlotValue.mModel)
						SkeletonMeshComponentManager::getSingleton().destroyLogicModel(tempSlotValue.mModel);

					tempSlotValue.mModel = NULL;
					tempSlotValue.mModelName = value;

					return true;
				}
				else
				{
					tempSlotValue.mModelName = value;

					return _createModelInSlot(tempSlotValue, tempLocatorValue);
				}				
			}			
		}

		return false;
	}
	//-----------------------------------------------------------------------
	bool SkeletonMeshComponent::addEffectInfo( const String& name, const String& effectName,
		const String& locatorName, bool translateAll, const Ogre::ColourValue& colour, const Ogre::Vector3& OffsetPos, const Ogre::Quaternion& OffsetQuat )
	{
		EffectMap::iterator i = mEffectMap.find(name);

		if ( i != mEffectMap.end() )
		{


			return false;
		}

		std::pair<EffectMap::iterator, bool> inserted = 
			mEffectMap.insert( EffectMap::value_type( name, EffectValue(effectName, locatorName, translateAll, colour, OffsetPos, OffsetQuat) ) );

		if (false == inserted.second)
		{


			return false;
		}

		return true;
	}

	bool SkeletonMeshComponent::removeEffectInfo(const String& locatorName, const String& effectName)
	{
		EffectMap::iterator iter = mEffectMap.begin();
		while (iter != mEffectMap.end())
		{
			EffectValue& value = iter->second;

			if (value.mEffectName == effectName && value.mLocator == locatorName)
			{
				mEffectMap.erase(iter);

				return true;
			}

			iter ++;
		}

		return false;
	}

	bool SkeletonMeshComponent::setEffectInfoOffsePosQuat(const String& locatorName, const String& effectName, Ogre::Vector3* OffsetPos, Ogre::Quaternion* OffsetQuat)
	{
		EffectMap::iterator iter = mEffectMap.begin();
		while (iter != mEffectMap.end())
		{
			EffectValue& value = iter->second;

			if (value.mEffectName == effectName && value.mLocator == locatorName)
			{
				if (OffsetPos)
				{
					value.mOffsetPos = *OffsetPos;
				}

				if (OffsetQuat)
				{
					value.mOffsetQuat = *OffsetQuat;
				}

				return true;
			}

			iter ++;
		}

		return false;
	}

	bool SkeletonMeshComponent::getEffectInfoOffsePosQuat(const String& locatorName, const String& effectName, Ogre::Vector3* OffsetPos, Ogre::Quaternion* OffsetQuat)
	{
		EffectMap::iterator iter = mEffectMap.begin();
		while (iter != mEffectMap.end())
		{
			EffectValue& value = iter->second;

			if (value.mEffectName == effectName && value.mLocator == locatorName)
			{
				if (OffsetPos)
				{
					*OffsetPos = value.mOffsetPos;
				}

				if (OffsetQuat)
				{
					*OffsetQuat = value.mOffsetQuat;
				}

				return true;
			}

			iter ++;
		}

		return false;
	}

//////////////////////////

	bool SkeletonMeshComponent::setCreatedEffectOffsePosQuat(const String& locatorName, const String& effectName, Ogre::Vector3* OffsetPos, Ogre::Quaternion* OffsetQuat)
	{
		CreatedEffectList::iterator i = mCreatedEffectList.begin();

		while (i != mCreatedEffectList.end() )
		{
			CreatedEffectInfo& cei = *i;

			if (cei.mEffect->getTemplateName() == effectName && cei.mLocator == locatorName)
			{
				if (OffsetPos)
				{
					cei.mOffsetPos = *OffsetPos;
				}

				if (OffsetQuat)
				{
					cei.mOffsetQuat = *OffsetQuat;
				}

				return true;
			}

			i ++;
		}

		return false;
	}

	bool SkeletonMeshComponent::getCreatedEffectOffsePosQuat(const String& locatorName, const String& effectName, Ogre::Vector3* OffsetPos, Ogre::Quaternion* OffsetQuat)
	{
		CreatedEffectList::iterator i = mCreatedEffectList.begin();

		while (i != mCreatedEffectList.end() )
		{
			CreatedEffectInfo& cei = *i;

			if (cei.mEffect->getTemplateName() == effectName && cei.mLocator == locatorName)
			{
				if (OffsetPos)
				{
					*OffsetPos = cei.mOffsetPos;
				}

				if (OffsetQuat)
				{
					*OffsetQuat = cei.mOffsetQuat;
				}

				return true;
			}

			i ++;
		}

		return false;
	}

	bool SkeletonMeshComponent::setBindPointInfo(const String& bindName, Ogre::Vector3* OffsetPos, Ogre::Quaternion* OffsetQuat)
	{
		SkeletonMeshComponent::LocatorMap::iterator iter = mLocatorMap.begin();
		while (iter != mLocatorMap.end())
		{
			const Ogre::String& name = iter->first;

			if (name == bindName)
			{
				if (OffsetPos)
				{
					iter->second.mOffsetPos = *OffsetPos;
				}

				if (OffsetQuat)
				{
					iter->second.mOffsetOrientation = *OffsetQuat;
				}

				return true;

			}
			
			iter ++;
		}

		return false;
	}

	//-----------------------------------------------------------------------
	bool SkeletonMeshComponent::addShadowUncastable(const String& meshName)
	{
		ShadowUncastableMeshs::iterator i = mShadowUncastableMeshs.begin();

		// 查找是否有重名的
		while (i != mShadowUncastableMeshs.end())
		{
			if (*i == meshName)
				break;
			++i;
		}
		if ( i != mShadowUncastableMeshs.end() )
		{
			return false;
		}
		mShadowUncastableMeshs.push_back(meshName);
		return true;
	}
	//-----------------------------------------------------------------------
	bool SkeletonMeshComponent::isShadowUncastable(const String& meshName)
	{
		ShadowUncastableMeshs::iterator i = mShadowUncastableMeshs.begin();
		// 查找是否有重名的
		while (i != mShadowUncastableMeshs.end())
		{
			if (*i == meshName)
				return true;
			++i;
		}
		return false;
	}
	//-----------------------------------------------------------------------
	void SkeletonMeshComponent::_createEntity(void)
	{
		// 遍历entity列表并创建出相应的entity
		for (EntityMap::iterator i = mEntityMap.begin();
			i != mEntityMap.end(); ++i)
		{
			EntityValue& tempValue = i->second;
			String meshName = tempValue.mMeshName;
			String materialName = tempValue.mMaterialName;
			// 如果xml文件中mesh文件名不为空,直接创建
			if (false == meshName.empty())
			{
				tempValue.mMeshName = meshName; //dscky add//////
				tempValue.mEntity = _createEntityImpl(meshName);

				if (tempValue.mEntity && !materialName.empty())
				{
					if (mSkeletonMeshType == 0)//主角
					{
						String newMatName;
						assert(false);
						//设置新材质
						if (materialName.find(";") != String::npos)
						{
							
						}
						else
						{
							newMatName = "Premier_" + materialName;
							Ogre::MaterialPtr oldMat = Ogre::MaterialManager::getSingletonPtr()->getByName(materialName);
							Ogre::MaterialPtr newMat = Ogre::MaterialManager::getSingletonPtr()->getByName(newMatName);
							
						}
						_setEntityMaterial(i->first, newMatName);//更改材质的时候，需要改变Texture的引用计数
						tempValue.mMaterialName = newMatName;
						//ConfigManager::getSingletonPtr()->setTextureQuality(oldTexQuality);
					}
					else
					{
						_setEntityMaterial(i->first, materialName);//更改材质的时候，需要改变Texture的引用计数
					}

					if (tempValue.mEntityColourChanged)
						_setEntityColour(tempValue, tempValue.mEntityColour);//这里貌似也会更改材质，同样需要改变Texture的引用计数

					if (mCurrentTransparency > 0.0f)
					{
						tempValue.mTransparentor = new EntityTransparentor(tempValue.mEntity);//这里同样需要改变Texture的引用计数
						tempValue.mTransparentor->apply(mCurrentTransparency);
					}
				}
			}
		}
	}
	//-----------------------------------------------------------------------
	void SkeletonMeshComponent::destroyEntities(void)
	{
		
	}
	//-----------------------------------------------------------------------
	void SkeletonMeshComponent::setUserAny(const Ogre::Any& anything)
	{
		mUserAny = anything;

		for ( EntityMap::iterator i = mEntityMap.begin();
			i != mEntityMap.end(); ++i )
		{
			if (i->second.mEntity)
				i->second.mEntity->getUserObjectBindings().setUserAny(anything);
		}

		// locator上的model也要设置
		for ( LocatorMap::iterator itLocator = mLocatorMap.begin();
			itLocator != mLocatorMap.end(); ++itLocator )
		{
			LocatorValue& tempValue = itLocator->second;

			for ( SlotMap::iterator itSlot = tempValue.mSlotMap.begin();
				itSlot != tempValue.mSlotMap.end(); ++itSlot )
			{
				SlotValue& tempSlot = itSlot->second;

				if (tempSlot.mModel)
					tempSlot.mModel->setUserAny(anything);
			}
		}
	}
	//-----------------------------------------------------------------------
	const Ogre::Any& SkeletonMeshComponent::getUserAny(void) const
	{
		return mUserAny;
	}
	//-----------------------------------------------------------------------
	void SkeletonMeshComponent::setUserObject(Ogre::UserDefinedObject* obj)
	{
		setUserAny(Ogre::Any(obj));
	}
	//-----------------------------------------------------------------------
	Ogre::UserDefinedObject* SkeletonMeshComponent::getUserObject(void) const
	{
		return !mUserAny.has_value() ? 0 : Ogre::any_cast<Ogre::UserDefinedObject*>(mUserAny);
	}
	//-----------------------------------------------------------------------
	void SkeletonMeshComponent::setParentSceneNode( Ogre::Node* parentNode )
	{
		if (mModelSceneNode && mModelSceneNode->getParent())
		{
			auto p = mModelSceneNode->getParent();
			p->removeChild(mModelSceneNode);
		}
			

		if (parentNode)
		{
			parentNode->addChild(mModelSceneNode);
		}

		mParentNode = parentNode;
	}
	//-----------------------------------------------------------------------
	void SkeletonMeshComponent::destroySceneNode(void)
	{
		
	}
	//-----------------------------------------------------------------------
	const Ogre::AxisAlignedBox& SkeletonMeshComponent::getBoundingBox(void)
	{
		if (mExternalBoundingBox)
			return *mExternalBoundingBox;
		else
		{
			return _getFullBoundingBox();
		}
	}
	//-----------------------------------------------------------------------
	void SkeletonMeshComponent::_destroyEntityImpl(Ogre::Entity* entity)
	{
			
	}
	//-----------------------------------------------------------------------
	Ogre::Entity* SkeletonMeshComponent::_createEntityImpl( const String& meshName )
	{
		auto mesh = MeshManager::getSingleton().load(meshName);

		if (!mesh)
		{
			WARNING_LOG("fail to load mesh:%s", meshName.c_str());
			return nullptr;
		}

		auto sceneMgr = EngineManager::getSingleton().getSceneManager();
		auto entity = sceneMgr->createEntity(mName, mesh);

		entity->getUserObjectBindings().setUserAny(getUserAny());

		if (mModelSceneNode == nullptr)
		{
			mModelSceneNode = 
				EngineManager::getSingleton().getBaseSceneNode()->createChildSceneNode(mName);
		}
		mModelSceneNode->attachObject(entity);


		entity->setVisible(true);

		if (entity->hasSkeleton())
		{
			if (nullptr == mSkeletonEntity)
			{
				const Ogre::MeshPtr& originMesh = entity->getMesh();

				const Ogre::SkeletonPtr& originSke = originMesh->getSkeleton();

				_createSkeletonEntity(originSke);
			}

			entity->shareSkeletonInstanceWith(mSkeletonEntity);
		}

		if (mSkeletonEntity && !mSkeleton)
		{
			mSkeleton = mSkeletonEntity->getSkeleton();
		}
		if (nullptr == m_advancedAnimationSystem)
			_createAdvancedAnimationSystem();
		return entity;
	}
	//-----------------------------------------------------------------------
	void SkeletonMeshComponent::_createMainSceneNode(void)
	{
		static uint32_t index = 0;
		String name = Ogre::StringUtil::format("SkeletonMeshComponent%d", ++index);
		mModelSceneNode = EngineManager::getSingleton().getBaseSceneNode()->createChildSceneNode(name);
		mModelSceneNodeName = mModelSceneNode->getName();
		//char Msg[256]={0,0};
		//sprintf(Msg,"SkeletonMeshComponent CreateMainSceneNode Success.Name=%s\n",mModelSceneNodeName.c_str());
		//OutputDebugString(Msg);
		mParentNode = mModelSceneNode->getParent();
		mOrigParentNode = mParentNode;
		// 设置缩放因子
		mModelSceneNode->setScale(mExternalScaleFactor);
	}
	//-----------------------------------------------------------------------
	void SkeletonMeshComponent::initModel(void)
	{
		_createMainSceneNode();

		_createEntity();

		_setEntityMaterials();

		_createLocatorNode();

		_createEffects();
	}
	//-----------------------------------------------------------------------
	void SkeletonMeshComponent::_createLocatorNode(void)
	{
		for ( LocatorMap::iterator i = mLocatorMap.begin();
			i != mLocatorMap.end(); ++i )
		{
			LocatorValue& tempValue = i->second;

			// 这里先不创建locator所需的scene node，等到需要时才创建
			//	assert (NULL == tempValue.mLocatorNode);
			//	tempValue.mLocatorNode = 
			//        _createLocatorSceneNode(tempValue.mOffsetPos, tempValue.mOffsetOrientation);

			// 创建初始的model
			for ( SlotMap::iterator itSlot = tempValue.mSlotMap.begin();
				itSlot != tempValue.mSlotMap.end(); ++itSlot )
			{
				SlotValue& tempSlot = itSlot->second;

				if (false == tempSlot.mModelName.empty())
					_createModelInSlot(tempSlot, tempValue);
			}
		}
	}
	//-----------------------------------------------------------------------
	void SkeletonMeshComponent::execute(Real delta)
	{
		{
			// 不可见的obj，不用更新
			if(!mVisible)
				return;

			_refreshViewFrustumVisible();

			
			_updateRenderQueue(delta);

			_updateLogicQueue(delta);
		}
	
	}
	//---------------------------------------------------------------------
	void SkeletonMeshComponent::_updateRenderQueue( Real seconds )
	{
		try
		{
			// 根据当前地形来旋转物体
			if ( (mPoseType != PT_NORMAL) && mGetHeightInWorld )
			{
				if (mSceneNodeNeedUpdate)
				{
					// 如果位置或旋转发生了变化，就需要及时更新main node
					//mModelSceneNode->_update(true, false);
					_rotate();
					mSceneNodeNeedUpdate = false;
				}
				tickSkelControl(seconds);
			}
		}
		catch(...)
		{
			WARNING_LOG("SkeletonMeshComponent::_updateRenderQueue Failed 1, --SkeletonMeshComponent::_updateRenderQueue");
			//OGRE_EXCEPT(Ogre::Exception::ERR_INTERNAL_ERROR,"SkeletonMeshComponent::_updateRenderQueue Failed!", "SkeletonMeshComponent::_updateRenderQueue" );
			throw;
		}
		
		try
		{
			// 设置透明度

			if (mNeedUpdateTransparency)
				updateTransparency(seconds);
		}
		catch(...)
		{
			WARNING_LOG("SkeletonMeshComponent::_updateRenderQueue Failed 2, --SkeletonMeshComponent::_updateRenderQueue");
			//OGRE_EXCEPT(Ogre::Exception::ERR_INTERNAL_ERROR,"SkeletonMeshComponent::_updateRenderQueue Failed!", "SkeletonMeshComponent::_updateRenderQueue" );
			throw;
		}
		

		{
			if(NULL != m_advancedAnimationSystem && !m_isForceIgnoreAAS)
				_updateAdvancedAnimationSystem(seconds);
		}

	}
	//-----------------------------------------------------------------------
	void SkeletonMeshComponent::_updateLogicQueue( Real delta )
	{
		if (!m_isForceIgnoreAAS)
		{
			if (m_isAnimForCurrentSkillStart)
			{
				Real oldTime = m_AnimationTimePosForCurrentSkill;
				
				m_AnimationTimePosForCurrentSkill += delta * m_skillRate;
				Real currTime = m_AnimationTimePosForCurrentSkill;

				if (mCurrentSkill && mVisible)
				{
					_createAnimationEffect(oldTime, currTime);
					_updateAttachedAnimationEffect(oldTime, currTime);

					_createAnimationBulletFlow(oldTime, currTime);

					_createAnimationRibbon(oldTime, currTime);
					_updateAnimationRibbon(delta);

					_updateAnimationSound(oldTime, currTime);

					_updateAnimationLight(oldTime, currTime);

					_createSkillModelElement(oldTime, currTime);
					_updateSkillModelElement(delta);
				}
			}

		}
		else if (mCurrentAnimationState)
		{
			////      // 更新主动作
			_animationBlend(delta);

			Real totalen = 0.0f;
			Real oldTime = 0.0f;
			Real currTime = 0.0f;
			//
			totalen = mCurrentAnimationState->getLength();

			// 如果这个动作的长度不为0，就正常地addTime，并计算出正确的oldTime和currTime
			if (false == Ogre::Math::RealEqual(0.0f, totalen))
			{
				oldTime = mCurrentAnimationState->getTimePosition() / totalen;

				mCurrentAnimationState->addTime(delta);

				// Make sure the skeletal animation of the entities up-to-date, so all bones,
				// tag-points transform will up-to-date on demand
				/*static bool old = false;
				if (old)
					mSkeleton->setAnimationState(*mSkeletonEntity->getAllAnimationStates());
				else
					mSkeletonEntity->_updateSkeletalAnimation();*/ //todo123

				currTime = mCurrentAnimationState->getTimePosition() / totalen;
			}

			bool animationConitnue = _handleAnimationFinish(oldTime, currTime, -1);

			if (mCurrentSkill)
			{
				_handleSkillHitTime(oldTime, currTime);
				_handleSkillBreakTime(oldTime, currTime);
				_handleSkillShakeTime(oldTime, currTime);

				if (mCurrentSkill && mVisible)
				{
					_createAnimationEffect(oldTime, currTime);
					_updateAttachedAnimationEffect(oldTime, currTime);

					_createAnimationBulletFlow(oldTime, currTime);

					_createAnimationRibbon(oldTime, currTime);
					_updateAnimationRibbon(delta);

					_updateAnimationSound(oldTime, currTime);

					_updateAnimationLight(oldTime, currTime);

					_createSkillModelElement(oldTime, currTime);
					_updateSkillModelElement(delta);
				}
			}

		}
		
		// 更新挂在model上的effect
		_updateAllEffects();

		_updateModelProjectors();//人物不动的话，是不是不用更新这个？？

		_executeLocatorModel(delta);

		// 更新通过attachModel上的model
		_executeAttachedModel(delta);

		_updateLocatorPos();
	}
	//-----------------------------------------------------------------------
	void SkeletonMeshComponent::setVisibleFlag(uint32 flags)
	{
		if (mVisibleFlag != flags)
		{
			mVisibleFlag = flags;

			// 设置自身的entity
			for ( EntityMap::iterator itEntity = mEntityMap.begin();
				itEntity != mEntityMap.end(); ++itEntity )
			{
				Ogre::Entity* pEntity = itEntity->second.mEntity;
				if (pEntity)
					pEntity->setVisibilityFlags(flags);
			}

			// 通过addEffect添加上去的effect也要设置visible flag（如武器特效）
			CreatedEffectList::iterator i = mCreatedEffectList.begin();

			while ( i != mCreatedEffectList.end() )
			{
				Orphigine::Impact* effect = (*i).mEffect;

				if (effect)
				{
					effect->setVisibleFlag(flags);
				}

				++i;
			}
			// locator上的model也要设置
			for ( LocatorMap::iterator itLocator = mLocatorMap.begin();
				itLocator != mLocatorMap.end(); ++itLocator )
			{
				LocatorValue& tempValue = itLocator->second;

				for ( SlotMap::iterator itSlot = tempValue.mSlotMap.begin();
					itSlot != tempValue.mSlotMap.end(); ++itSlot )
				{
					SlotValue& tempSlot = itSlot->second;

					if (tempSlot.mModel)
						tempSlot.mModel->setVisibleFlag(flags);
				}
			}
		}		
	}
	//-----------------------------------------------------------------------
	bool SkeletonMeshComponent::_changeAnimation(const String& animationName,  Real delay,   int nAnimFlag)
	{

		

		return true;
	}
	//-----------------------------------------------------------------------
	void SkeletonMeshComponent::_updateLocatorPos(void)
	{
	
		LocatorMap::iterator itEnd = mLocatorMap.end();
		for ( LocatorMap::iterator i = mLocatorMap.begin();i != itEnd; ++i )
		{
			LocatorValue& tempValue = i->second;
			

			// 只更新创建出来的（已经使用的）locator node
			if (tempValue.mLocatorNode && !tempValue.mBoneName.empty())
			{
				const String& sLocateName = i->first;
				bool noXAngle = (strstr( sLocateName.c_str(), "_nox" ) != NULL );
				bool noYAngle = (strstr( sLocateName.c_str(), "_noy" ) != NULL );
				bool noZAngle = (strstr( sLocateName.c_str(), "_noz" ) != NULL );

				_updateLocatorAttachedToBone(tempValue,noXAngle,noYAngle,noZAngle);
			}
		}

	}

	void SkeletonMeshComponent::updateLocatorAttachedToBone(Ogre::String& bindPointName ,bool isIgnoreXAxisRotation, bool isIgnoreYAxisRotation,bool isIgnoreZAxisRotation)
	{
		LocatorMap::iterator itEnd = mLocatorMap.end();
		for ( LocatorMap::iterator i = mLocatorMap.begin();i != itEnd; ++i )
		{
			LocatorValue& tempValue = i->second;
			const String &sLocateName = i->first;

			if (sLocateName == bindPointName)
			{
				_updateLocatorAttachedToBone(tempValue, isIgnoreXAxisRotation, isIgnoreYAxisRotation, isIgnoreZAxisRotation);
				return;
			}
		}
	}

	void SkeletonMeshComponent::_updateLocatorAttachedToBone(
		LocatorValue& locatorValue ,
		bool isIgnoreXAxisRotation,
		bool isIgnoreYAxisRotation,
		bool isIgnoreZAxisRotation)
	{

		if (mSkeletonEntity == nullptr)
		{
			return;
		}

		Ogre::Bone* bone = NULL;
		if (!mSkeleton)
		{
			mSkeleton = mSkeletonEntity->getSkeleton();
		}
		
		
		bone = mSkeleton->getBone(locatorValue.mBoneName);
		
		
		Ogre::SceneNode* locatorNode = _getLocatorSceneNode(locatorValue);
		assert(locatorNode);

		locatorNode->setPosition(bone->_getDerivedPosition());

		if ((!isIgnoreXAxisRotation) && (!isIgnoreYAxisRotation) && (!isIgnoreZAxisRotation))
			locatorNode->setOrientation(bone->_getDerivedOrientation());
		else
		{
			Ogre::Quaternion parentQuaternion = bone->_getDerivedOrientation();
			Ogre::Matrix3 rotm;
			parentQuaternion.ToRotationMatrix(rotm);
			Ogre::Radian y, x, z;
			rotm.ToEulerAnglesYXZ(y, x, z);

			if (isIgnoreXAxisRotation)
				x = 0;
			if (isIgnoreYAxisRotation)
				y = 0;
			if (isIgnoreZAxisRotation)
				z = 0;

			rotm.FromEulerAnglesYXZ(y, x, z);
			parentQuaternion = rotm;
			locatorNode->setOrientation(parentQuaternion);

		}

		if (locatorValue.mTranslateFirst)
		{
			locatorNode->translate(locatorValue.mOffsetPos, Ogre::Node::TS_LOCAL);
			locatorNode->rotate(locatorValue.mOffsetOrientation, Ogre::Node::TS_LOCAL);
		}
		else
		{
			locatorNode->rotate(locatorValue.mOffsetOrientation, Ogre::Node::TS_LOCAL);
			locatorNode->translate(locatorValue.mOffsetPos, Ogre::Node::TS_LOCAL);
		}


		locatorNode->updatechildren();
	}
	//-----------------------------------------------------------------------
	void SkeletonMeshComponent::setAnimationLoop(bool loop, int nAnimFlag)
	{
		mAnimationLoop = loop;

		if (mCurrentAnimationState)
		{
			mCurrentAnimationState->setLoop(loop);
		}		
	}
	//-----------------------------------------------------------------------
	void SkeletonMeshComponent::_animationBlend(Real delta)
	{
		if (mFadeOutAnimationState && mCurrentAnimationState)
		{
			if (mFadeOutDelay <= delta)
			{
				mFadeOutAnimationState->setWeight(0);
				mFadeOutAnimationState->setEnabled(false);
				mCurrentAnimationState->setWeight(1);
				mFadeOutAnimationState = NULL;
			}
			else
			{
				Real weight = mCurrentAnimationState->getWeight();
				weight = weight + delta * (1 - weight) / mFadeOutDelay;


				mCurrentAnimationState->setWeight(weight);
				mFadeOutAnimationState->setWeight(1 - weight);

				//				mComposeCurrentAnimationState.setWeight( weight );
				//				mComposeLastAnimationState.setWeight( 1- weight );

				mFadeOutAnimationState->addTime(delta);
				//				mComposeLastAnimationState.addTime( delta * mGlobalAnimationRate );
			}

			mFadeOutDelay -= delta;
		}
	}
	//-----------------------------------------------------------------------
	void SkeletonMeshComponent::_executeLocatorModel(Real delta)
	{
		LocatorMap::iterator itEnd = mLocatorMap.end();
		for ( LocatorMap::iterator itLocator = mLocatorMap.begin();
			itLocator != itEnd; ++itLocator )
		{
			LocatorValue& tempValue = itLocator->second;

			for ( SlotMap::iterator itSlot = tempValue.mSlotMap.begin();
				itSlot != tempValue.mSlotMap.end(); ++itSlot )
			{
				SlotValue& tempSlot = itSlot->second;

				if (tempSlot.mModel)
					tempSlot.mModel->execute(delta);
			}
		}
	}
	//-----------------------------------------------------------------------
	void SkeletonMeshComponent::addEffect( const String& effectName, const String& locatorName,
		SkeletonMeshComponent::GetTransformInfoType transformType, const Ogre::ColourValue& colour,const char* pName, int priority, const Ogre::Vector3& OffsetPos, const Ogre::Quaternion& OffsetQuat)
	{

	}
	//-----------------------------------------------------------------------
	SkeletonMeshComponent::EffectHandle SkeletonMeshComponent::_addEffect( const String& effectName, const String& locatorName,
		SkeletonMeshComponent::GetTransformInfoType transformType, const Ogre::ColourValue& colour,const char* pName, int priority, const Ogre::Vector3& OffsetPos, const Ogre::Quaternion& OffsetQuat)
	{	
		
				return 0;		
	}
	//-----------------------------------------------------------------------	
	bool SkeletonMeshComponent::delEffect( EffectHandle handle )
	{
		assert (handle > 0);

		CreatedEffectList::iterator i = mCreatedEffectList.begin();

		// 定位effect
		while ( i != mCreatedEffectList.end() )
		{
			if ( (*i).mEffectHandle == handle )
			{
				break;
			}

			++i;
		}

		if ( i != mCreatedEffectList.end() )
		{
			ImpactManager::getSingleton().removeEffect(((*i).mEffect),false);

			// 去除对已remove的effect的引用
			(*i).mEffect = NULL;

			// erase，并返回下个iterator
			mCreatedEffectList.erase(i);
			return true;
		}
		else
		{
			// 所找的effect不存在
			//OGRE_EXCEPT(Ogre::Exception::ERR_ITEM_NOT_FOUND,
			//    "the handle " + Ogre::StringConverter::toString(handle) + " is wrong!",
			//    "SkeletonMeshComponent::delEffect");
			//应客户端要求，不抛出异常，只输出log
			return false;
		}
	}
	bool SkeletonMeshComponent::delEffect(Ogre::String name)
	{
#if EFFECT_RESTRICT

		ImpactManager::getSingleton().removeCreateEffectReq(name); 
#endif
		CreatedEffectList::iterator i = mCreatedEffectList.begin();
		// 定位effect
		while ( i != mCreatedEffectList.end() )
		{
			if ( (*i).mEffectName == name )
			{
				break;
			}
			++i;
		}
		if ( i != mCreatedEffectList.end() )
		{
			ImpactManager::getSingleton().removeEffect(((*i).mEffect),false);

			(*i).mEffect = NULL;

			mCreatedEffectList.erase(i);
			return true;
		}
		else
		{
			return false;
		}
	}
	Impact* SkeletonMeshComponent::getEffect(Ogre::String name)
	{
		CreatedEffectList::iterator i = mCreatedEffectList.begin();

		// 定位effect
		while ( i != mCreatedEffectList.end() )
		{
			if ( (*i).mEffectName == name )
			{
				break;
			}

			++i;
		}

		if ( i != mCreatedEffectList.end() )
		{
			return (*i).mEffect;
		}
		else
		{
			// 所找的effect不存在
			/*OGRE_EXCEPT(Ogre::Exception::ERR_ITEM_NOT_FOUND,
			"the handle " + Ogre::StringConverter::toString(handle) + " is wrong!",
			"SkeletonMeshComponent::getEffect");*/
			return NULL;
		}
	}
	//-----------------------------------------------------------------------
	SkeletonMeshComponent::CreatedEffectList::iterator 
		SkeletonMeshComponent::delEffect( SkeletonMeshComponent::CreatedEffectList::iterator effectIterator )
	{
		assert ( effectIterator != mCreatedEffectList.end() );

		ImpactManager::getSingleton().removeEffect(((*effectIterator).mEffect),false);

		// 去除对已remove的effect的引用
		(*effectIterator).mEffect = NULL;

		// erase，并返回下个iterator
		return mCreatedEffectList.erase(effectIterator);
	}
	//-----------------------------------------------------------------------
	void SkeletonMeshComponent::delAllEffect(void)
	{
#if EFFECT_RESTRICT
		try
		{
			ImpactManager::getSingleton().removeCreateEffectReq(this);
		}
		
		catch(...) 
		{
			
		}
		//end
#endif
		try
		{
			for ( CreatedEffectList::iterator i = mCreatedEffectList.begin();
				i != mCreatedEffectList.end(); ++i )
			{		
				Impact* effect = (*i).mEffect;
				if (effect)
				{
					ImpactManager::getSingleton().removeEffect(effect,false);

					// 去除对已remove的effect的引用
					(*i).mEffect = NULL;
				}
			}
			mCreatedEffectList.clear();
		}
		catch( const std::exception& e )
		{
			
		}
		catch(...) 
		{
			
		}
	}
	//-----------------------------------------------------------------------	
	Impact* SkeletonMeshComponent::getEffect(SkeletonMeshComponent::EffectHandle handle)
	{
		assert (handle > 0);

		CreatedEffectList::iterator i = mCreatedEffectList.begin();

		// 定位effect
		while ( i != mCreatedEffectList.end() )
		{
			if ( (*i).mEffectHandle == handle )
			{
				break;
			}

			++i;
		}

		if ( i != mCreatedEffectList.end() )
		{
			return (*i).mEffect;
		}
		else
		{
			// 所找的effect不存在

			return NULL;
		}
	}	
	//-----------------------------------------------------------------------
	bool SkeletonMeshComponent::getLocatorWorldTransform(const String& name, TransformInfo& info, const Ogre::Vector3& offsetPos,
		const Ogre::Quaternion& offsetRotation, SkeletonMeshComponent::GetTransformInfoType type,bool useAttachRotation )
	{
		Ogre::Matrix4 mtx;
		Ogre::Matrix3 mat(Ogre::Matrix3::IDENTITY);

		LocatorMap::iterator it = mLocatorMap.find(name);

		if (it == mLocatorMap.end())
		{
			return false;
		}
		else
		{
			LocatorValue& tempValue = it->second;
			Ogre::SceneNode* locatorNode = _getLocatorSceneNode(tempValue);

			switch (type)
			{
			case GTIT_ALL:
				{
					if(useAttachRotation)
					{
						info.mRotation = locatorNode->_getDerivedOrientation() * offsetRotation;
						info.mPosition = locatorNode->_getDerivedOrientation() * ( locatorNode->_getDerivedScale() * offsetPos ) + locatorNode->_getDerivedPosition();
					}
					else
					{
						info.mRotation = offsetRotation;
						info.mPosition = ( locatorNode->_getDerivedScale() * offsetPos ) + locatorNode->_getDerivedPosition();
					}

					info.mScale = locatorNode->_getDerivedScale();
				}
				break;

			case GTIT_POSITION_ORIENTATION:
				{
					if(useAttachRotation)
					{
						info.mRotation = locatorNode->_getDerivedOrientation() * offsetRotation;
						info.mPosition = locatorNode->_getDerivedOrientation() * ( locatorNode->_getDerivedScale() * offsetPos ) + locatorNode->_getDerivedPosition();
					}
					else
					{
						info.mRotation = offsetRotation;
						info.mPosition = ( locatorNode->_getDerivedScale() * offsetPos ) + locatorNode->_getDerivedPosition();
					}
				}
				break;

			case GTIT_POSITION:
				if(useAttachRotation)
				{
					info.mPosition = locatorNode->_getDerivedOrientation() * ( locatorNode->_getDerivedScale() * offsetPos )
						+ locatorNode->_getDerivedPosition();
				}
				else
				{
					info.mPosition = ( locatorNode->_getDerivedScale() * offsetPos )
						+ locatorNode->_getDerivedPosition();
				}

				break;

			case GTIT_ORIENTATION:
				if(useAttachRotation)
				{
					info.mRotation = locatorNode->_getDerivedOrientation() * offsetRotation;
				}
				else
				{
					info.mRotation = offsetRotation;
				}

				break;

			default:
				return false;
			}

			return true;
		}		
	}
	//-----------------------------------------------------------------------
	bool SkeletonMeshComponent::getBoneWorldTransform(const String& name, TransformInfo& info, const Ogre::Vector3& offsetPos,
		const Ogre::Quaternion& offsetRotation, SkeletonMeshComponent::GetTransformInfoType type )
	{
		

		return true;		
	}
	//-----------------------------------------------------------------------
	bool SkeletonMeshComponent::getLocatorWorldTransform(const String& name, Ogre::Matrix4& mtx)
	{
		LocatorMap::iterator it = mLocatorMap.find(name);

		if (it == mLocatorMap.end())
			return false;
		else
		{
			LocatorValue& tempValue = it->second;

			Ogre::SceneNode* locatorNode = _getLocatorSceneNode(tempValue);

			mtx = locatorNode->_getFullTransform();

			return true;
		}
	}
	//-----------------------------------------------------------------------
	//切换动作通过这个函数实现
	void SkeletonMeshComponent::createSkill(const String& skillName, const Ogre::Quaternion & rot,
		int nAnimFlag, bool loop, bool anim, Real delayTime, int priority)
	{
		//_muteCurrentSkillSound();

		delCurrentSkill();

		m_isAnimForCurrentSkillStart = true;
		m_AnimationTimePosForCurrentSkill = 0.0f;

		if(NULL != m_advancedAnimationSystem && !m_isForceIgnoreAAS)
		{
			mCurrentSkill = ImpactManager::getSingleton().createSkill(skillName);

			if (mCurrentSkill)
			{
				mCurrentSkill->setPriority(priority);
				mCurrentSkill->setRotation(rot);
			}
			//end
			if (NULL == mCurrentSkill)
				m_advancedAnimationSystem->setAttackAnimName(skillName);
			else
				m_advancedAnimationSystem->setAttackAnimName(mCurrentSkill->getAnimationName());
		}
		else
		{
			if ( false == anim )
			{
				mCurrentSkill = ImpactManager::getSingleton().createSkill(skillName);
				if (mCurrentSkill)
				{
					mCurrentSkill->setPriority(priority);
					mCurrentSkill->setRotation(rot);
				}
				//end

				if (NULL == mCurrentSkill)
				{
					_changeAnimation(skillName, delayTime, nAnimFlag);
				}
				else
				{
					_changeAnimation(mCurrentSkill->getAnimationName(), delayTime, nAnimFlag);
				}
			}
			else
			{
				_changeAnimation(skillName, delayTime , nAnimFlag);
			}	

			setAnimationLoop(loop, nAnimFlag);
		}

	}
	//-----------------------------------------------------------------------
	void SkeletonMeshComponent::delCurrentSkill(void)
	{
		if (mCurrentSkill)
		{
			try
			{

				DestroySkillCallback* tmpCallback = SpellManager::getSingleton().getDestroySkillCallback();
				if(NULL != tmpCallback)
					tmpCallback->onDestroySkill(mCurrentSkill);
				//需要删除声音
				_muteCurrentSkillSound();
			}
			
			catch(...) 
			{
				
			}
			try
			{
				ImpactManager::getSingleton().removeSkill(mCurrentSkill);
				mCurrentSkill = NULL;

				m_isAnimForCurrentSkillStart = false;
				m_AnimationTimePosForCurrentSkill = 0.0f;
				m_animStateForCurrentSkillCache = NULL;
			}
			
			catch(...) 
			{
				
			}
		}

		//	mSk.delCurrentSkill();
	}
	//-----------------------------------------------------------------------
	void SkeletonMeshComponent::_muteCurrentSkillSound(void)
	{
		if (mCurrentSkill)
		{
			if ( mOnStopSound )
			{
				for ( ushort i=0; i<mCurrentSkill->getNumAnimationSounds(); ++i )
				{
					SpellSoundModule *sound = mCurrentSkill->getAnimationSound(i);
					assert (sound);
					if (sound->mSoundHandle != -1)
					{						
						mOnStopSound(sound->mSoundHandle);
						sound->mSoundHandle=-1;
					}
				}
			}
		}
	}
	//-----------------------------------------------------------------------
	bool SkeletonMeshComponent::_handleAnimationFinish(Real oldTime, Real currTime, int nFlag)
	{
		if (currTime <= oldTime && false == mAnimationLoop)
		{
			if ( mOnAnimationFinish )
			{
				//	std::string sAnimName = mCurrentAnimationName;
				if( nFlag & E_ANIM_BASE )
					mOnAnimationFinish(mCurrentAnimationName.c_str(), mCallbackFuncInfo, E_ANIM_BASE);
				else if( (nFlag & E_ANIM_ARM) )/// && (sAnimName == mCurrentAnimationName) )
				{
					mOnAnimationFinish(mCurrentAnimationName.c_str(), mCallbackFuncInfo, E_ANIM_ARM);
				}

				return false;
			}
		}

		return true;
	}
	//-----------------------------------------------------------------------
	void SkeletonMeshComponent::_handleSkillHitTime(Real oldTime, Real currTime)
	{
		if (mCurrentSkill)
		{
			unsigned short hitTimeCount = mCurrentSkill->getNumHitTimes();
			for (ushort i=0; i<hitTimeCount; ++i)
			{
				Real hitTime = mCurrentSkill->getHitTime(i);

				if (hitTime >= 0.0f && hitTime <= 1.0f)
				{
					if((currTime >= oldTime && hitTime >= oldTime && hitTime < currTime) || 
						(currTime < oldTime && (hitTime >= oldTime || hitTime < currTime)))
					{
						if (mOnSkillHitTime)
							mOnSkillHitTime(mCurrentAnimationName.c_str(), mCallbackFuncInfo, i, hitTimeCount);

						if ( mCurrentSkill == NULL )
							break;
					}
				}
			}
		}		
	}
	//-----------------------------------------------------------------------
	void SkeletonMeshComponent::_handleSkillBreakTime(Real oldTime, Real currTime)
	{
		if (mCurrentSkill)
		{
			unsigned short breakTimeCount = mCurrentSkill->getNumBreakTimes();
			for (ushort i=0; i<breakTimeCount; ++i)
			{
				Real breakTime = mCurrentSkill->getBreakTime(i);

				if (breakTime >= 0.0f && breakTime <= 1.0f)
				{
					if((currTime >= oldTime && breakTime >= oldTime && breakTime < currTime) || 
						(currTime < oldTime && (breakTime >= oldTime || breakTime < currTime)))
					{
						if (mOnSkillBreakTime)
							mOnSkillBreakTime(mCurrentAnimationName.c_str(), mCallbackFuncInfo, i, breakTimeCount);

						if ( mCurrentSkill == NULL )
							break;
					}
				}
			}
		}
	}
	//-----------------------------------------------------------------------
	void SkeletonMeshComponent::_handleSkillShakeTime(Real oldTime, Real currTime)
	{
		if (mCurrentSkill)
		{
			for (ushort i=0; i<mCurrentSkill->getNumShakeTimes(); ++i)
			{
				Real shakeTime = mCurrentSkill->getShakeTime(i);

				if (shakeTime >= 0.0f && shakeTime <= 1.0f)
				{
					if((currTime >= oldTime && shakeTime >= oldTime && shakeTime < currTime) || 
						(currTime < oldTime && (shakeTime >= oldTime || shakeTime < currTime)))
					{
						if (mOnSkillShakeTime)
							mOnSkillShakeTime(mCurrentAnimationName.c_str(), mCallbackFuncInfo);
					}
				}
			}
		}
	}
	//-----------------------------------------------------------------------
	void SkeletonMeshComponent::_createAnimationEffect(Real oldTime, Real currTime)
	{
		for ( ushort i = 0; i < mCurrentSkill->getNumAnimationEffectInfos(); ++i )
		{
			SpellImpactModule *effectInfo = mCurrentSkill->getAnimationEffectInfo(i);
			assert (effectInfo);

			Real time = effectInfo->getAttachTime();

			if((currTime >= oldTime && time >= oldTime && time < currTime) || 
				(currTime < oldTime && (time >= oldTime || time < currTime)))
			{
				Impact *effect = effectInfo->getEffect();

				// 获取脚本中的特效名称
				const String& effectTemplateName = effectInfo->getEffectTemplateName();

				String realEffectTemplate;

				// 如果是模板特效名称
				if ( effectTemplateName.find("<") != String::npos )
				{
					if ( false == mEnableWalkingEffect ||
						false == _getTemplateEffectName( realEffectTemplate, effectTemplateName, mTerrainHeight ) )
						continue;
				}
				else
				{
					realEffectTemplate = effectTemplateName;

					mTerrainHeight = Ogre::Math::POS_INFINITY;
				}

				//////////////////////////////////////////////////////////////////////////
				String attachPoint = effectInfo->getAttachPoint();

				TransformInfo info;

				// 先从绑定点找，如果没有再从骨头名称找
				if ( getLocatorWorldTransform( attachPoint, info, effectInfo->getOffsetPos(), 
					effectInfo->getOffsetRotation(),GTIT_ALL,effectInfo->getUseAttachRotation()))
				{
				}
				else if ( getBoneWorldTransform( attachPoint, info, effectInfo->getOffsetPos(), 
					effectInfo->getOffsetRotation() ) )
				{
				}

				if (mTerrainHeight < Ogre::Math::POS_INFINITY && info.mPosition.y >= mTerrainHeight)
					return;
				//////////////////////////////////////////////////////////////////////////

				if ( false == effectInfo->getAttach() )
				{
					// 根据需要调整高度数据
					if (mTerrainHeight < Ogre::Math::POS_INFINITY)
					{
						info.mPosition.y = mTerrainHeight;
					}

					if(NULL != mModelSceneNode)
					{
						Ogre::Quaternion &rot = mCurrentSkill->getRotation();
						if (rot != Ogre::Quaternion::IDENTITY)
						{
							String locatorName = effectInfo->getAttachPoint();						

							String strTransferLocatorName;
							LocatorMap::iterator it = mLocatorMap.find(locatorName);
							if ( it != mLocatorMap.end() )
							{
								strTransferLocatorName = it->second.mDestLocatorName;
							}

							SkeletonMeshComponent * lmodel = this;
							if ( mAttachParent 
								&& isLocatorTransferable(locatorName) 
								&& mAttachParent->isLocatorExist(strTransferLocatorName) 
								)
							{
								lmodel = mAttachParent;
								locatorName = strTransferLocatorName;
							}

							//--------------
							it = lmodel->mLocatorMap.find(locatorName);

							if (it != lmodel->mLocatorMap.end())
							{
								LocatorValue& tempValue = it->second;

								Ogre::SceneNode* locatorNode = lmodel->_getLocatorSceneNode(tempValue);

								if (locatorNode)
								{
									Ogre::Quaternion rotation = mCurrentSkill->getRotation();
									if (mAttachParent && lmodel == this) //不转移到坐骑上
									{
										Ogre::Quaternion parentOrient = Ogre::Quaternion::IDENTITY;
										parentOrient = mAttachParent->getSceneNode()->_getDerivedOrientation();
										Ogre::Radian rAngle, rAngle1;
										Ogre::Vector3 oAxis,oAxis1;
										

										Ogre::Vector3 parentPos = locatorNode->_getDerivedPosition();
										Ogre::Vector3 curPos = info.mPosition;
										curPos.y = 0.f; parentPos.y = 0.f;
										Ogre::Vector3 dir = curPos - parentPos;
										
										Ogre::Vector3 axis = rotation.zAxis();

										Ogre::Vector3 pos = axis * dir.length() + parentPos;
										pos.y = info.mPosition.y;

											
										info.mPosition = pos;
									}
									else 
									{
										info.mPosition = rotation * ( locatorNode->_getDerivedScale() * effectInfo->getOffsetPos() )
											+ locatorNode->_getDerivedPosition();
									}

									info.mRotation = rotation * effectInfo->getOffsetRotation();
								}
							}
						}
						else
						{						
							info.mRotation = mModelSceneNode->_getDerivedOrientation() * effectInfo->getOffsetRotation();
						}

					}
				}	

				//info.mRotation = mCurrentSkill->getRotation() * info.mRotation;
#if EFFECT_RESTRICT
				ImpactManager::SkeletonMeshComponentImpactParam param;
				param.model = this;
				param.reqType = 1;
				param.effectName = realEffectTemplate;
				param.rotation = info.mRotation;
				param.position = info.mPosition;
				param.skill = mCurrentSkill;
				param.effectInfo = effectInfo;
				param.priority = mCurrentSkill->getPriority();
#endif
				if (effect)
				{
					// 如果动作是循环的(可以走到这里，这个动作肯定是loop的)，而且当前skill需要在每次进行动作时都创建一个新特效
					if (mCurrentSkill->getRepeatEffect())
					{
						// 先把旧的删除，在创建新的
						ImpactManager::getSingleton().removeEffect(effect, false, false);						
						effectInfo->setEffect(0);
#if EFFECT_RESTRICT
						ImpactManager::getSingleton().requestCreateEffect(param);						                     
#else
						effect = ImpactManager::getSingleton().addEffect(realEffectTemplate);
						effect->createSceneNode();

						effectInfo->setEffect(effect);
#endif												

					}
				}
				else
				{					
#if EFFECT_RESTRICT
					ImpactManager::getSingleton().requestCreateEffect(param);					
#else
					effect = ImpactManager::getSingleton().addEffect(realEffectTemplate);
					effect->createSceneNode();
					effectInfo->setEffect(effect);
#endif

				}
#if EFFECT_RESTRICT
#else
				if ( false == effectInfo->getAttach() )
				{                    
					effect->setTransformInfo(info);
				}	
#endif
				continue;
			}
		}
	}
	//end******************************
	//-----------------------------------------------------------------------
	void SkeletonMeshComponent::_updateAttachedAnimationEffect(Real oldTime, Real currTime)
	{
		for ( ushort i = 0; i < mCurrentSkill->getNumAnimationEffectInfos(); ++i )
		{
			SpellImpactModule *effectInfo = mCurrentSkill->getAnimationEffectInfo(i);
			assert (effectInfo);

			Impact *effect = effectInfo->getEffect();

			if (effect && effectInfo->getAttach())
			{

				String locatorName = effectInfo->getAttachPoint();

				TransformInfo info;

				String strTransferLocatorName;
				LocatorMap::iterator it = mLocatorMap.find(locatorName);
				if ( it != mLocatorMap.end() )
				{
					strTransferLocatorName = it->second.mDestLocatorName;
				}

				if ( mAttachParent // 自身被一个LogicModel所attach
					&& isLocatorTransferable(locatorName) // 该locator是可以转移的
					&& mAttachParent->isLocatorExist(strTransferLocatorName) // attachParent上有这个locator 
					)
				{

					// 获取attachParent上locator的位置
					mAttachParent->getLocatorWorldTransform(strTransferLocatorName, info, effectInfo->getOffsetPos(),
						effectInfo->getOffsetRotation(), GTIT_ALL, effectInfo->getUseAttachRotation());
				}
				else
				{
					// 获取自身的locator位置
					getLocatorWorldTransform( locatorName, info, effectInfo->getOffsetPos(),
						effectInfo->getOffsetRotation(), GTIT_ALL, effectInfo->getUseAttachRotation());	
				}

				// 给effect传入点
				if (!effectInfo->getUseAttachRotation() &&
					NULL != mModelSceneNode)
					info.mRotation = mModelSceneNode->_getDerivedOrientation() * effectInfo->getOffsetRotation();
	
				
				effect->setTransformInfo(info);
			}
		}
	}


	void SkeletonMeshComponent::_createAnimationBulletFlow( Real oldTime,Real currTime )
	{
		for ( ushort i = 0; i < mCurrentSkill->getNumAnimationBulletFlows(); ++i )
		{
			SpellBulletFlowModule *tmpAnimationBulletFlow = mCurrentSkill->getAnimationBulletFlow(i);
			assert (tmpAnimationBulletFlow);

			Real time = tmpAnimationBulletFlow->getAttachTime();

			if((currTime >= oldTime && time >= oldTime && time < currTime) || 
				(currTime < oldTime && (time >= oldTime || time < currTime)))
			{

				// 获取脚本中的特效名称
				const String& tmpBulletFlowTemplateName = tmpAnimationBulletFlow->getBulletFlowTemplateName();

				mTerrainHeight = Ogre::Math::POS_INFINITY;

				//////////////////////////////////////////////////////////////////////////
				String attachPoint = tmpAnimationBulletFlow->getAttachPoint();

				TransformInfo info;

				// 先从绑定点找，如果没有再从骨头名称找
				if ( getLocatorWorldTransform( attachPoint, info, tmpAnimationBulletFlow->getOffsetPos(), 
					tmpAnimationBulletFlow->getOffsetRotation(),GTIT_ALL,tmpAnimationBulletFlow->getUseAttachRotation() ) )
				{
				}
				else if ( getBoneWorldTransform( attachPoint, info, tmpAnimationBulletFlow->getOffsetPos(), 
					tmpAnimationBulletFlow->getOffsetRotation() ) )
				{
				}

				if (mTerrainHeight < Ogre::Math::POS_INFINITY && info.mPosition.y >= mTerrainHeight)
					return;
				//////////////////////////////////////////////////////////////////////////

				if (mTerrainHeight < Ogre::Math::POS_INFINITY)
				{
					info.mPosition.y = mTerrainHeight;
				}

				CreateBulletFlowCallback* tmpBulletFlowCallback = BulletFlowSystemManager::getSingleton().
					getCreateBulletFlowCallback();
				if(NULL != tmpBulletFlowCallback) 
					tmpBulletFlowCallback->onCreateBulletFlow(tmpBulletFlowTemplateName,attachPoint,
					info,mCurrentSkill->m_userData, mCurrentSkill->getPriority());
			}
		}
	}	
	//-----------------------------------------------------------------------
	void SkeletonMeshComponent::_createAnimationRibbon(Real oldTime, Real currTime)
	{
		for ( ushort i = 0; i < mCurrentSkill->getNumAnimationRibbons(); ++i )
		{
			SpellRibbonModule *ribbon = mCurrentSkill->getAnimationRibbon(i);
			assert (ribbon);

			Real time = ribbon->getAttachTime();

			if((currTime >= oldTime && time >= oldTime && time < currTime) || 
				(currTime < oldTime && (time >= oldTime || time < currTime)))
			{
				ribbon->createRenderInstance();
			}
		}
	}
	//-----------------------------------------------------------------------
	void SkeletonMeshComponent::_updateAnimationRibbon(Real delta)
	{
		for ( ushort i = 0; i < mCurrentSkill->getNumAnimationRibbons(); ++i )
		{
			SpellRibbonModule *ribbon = mCurrentSkill->getAnimationRibbon(i);
			assert (ribbon);

			String attachPoint = ribbon->getAttachPoint();

			TransformInfo info;

			// 先从绑定点找，如果没有再从骨头名称找
			if ( getLocatorWorldTransform( attachPoint, info, ribbon->getOffsetPos(), 
				ribbon->getOffsetRotation(),GTIT_ALL,ribbon->getUseAttachRotation() ) )
			{
			}
			else if ( getBoneWorldTransform( attachPoint, info, ribbon->getOffsetPos(), 
				ribbon->getOffsetRotation() ) )
			{
			}

			// 给effect传入点
			ribbon->updateRenderInstance(delta, info);
		}
	}
	//-----------------------------------------------------------------------
	void SkeletonMeshComponent::_updateAnimationSound(Real oldTime, Real currTime)
	{
		if (mOnPlaySound)
		{
			// sound
			for ( ushort i = 0; i < mCurrentSkill->getNumAnimationSounds(); ++i )
			{					
				SpellSoundModule *sound = mCurrentSkill->getAnimationSound(i);
				assert (sound);

				if (false == sound->mPlayed)
				{
					Real time = sound->getAttachTime();

					if((currTime >= oldTime && time >= oldTime && time < currTime) || 
						(currTime < oldTime && (time >= oldTime || time < currTime)))
					{

						const Ogre::Matrix4& mtx = mModelSceneNode->_getFullTransform();
						Real pos[3] = { mtx.getTrans().x, mtx.getTrans().y, mtx.getTrans().z };
						sound->mSoundHandle = mOnPlaySound(sound->getSoundName().c_str(), pos, sound->getLooping());
						sound->mPlayed = true;
					}
				}
				
			}
		}
	}
	//-----------------------------------------------------------------------
	void SkeletonMeshComponent::_updateAnimationLight(Real oldTime, Real currTime)
	{
		return;
		MainSceneLight* light = ImpactManager::getSingleton().getMainSceneLight();

		assert (light);

		unsigned short lightInfoNum = mCurrentSkill->getNumAnimationSceneLightInfos();

		// 如果当前发招者不在摄像机内，就不改变灯光
		if (lightInfoNum > 0 && !m_isViewFrustumVisible)
		{
			return;
		}

		for ( ushort i = 0; i < lightInfoNum; ++i )
		{
			SpellSceneLightModule *lightInfo = mCurrentSkill->getAnimationSceneLightInfo(i);
			assert (lightInfo);

			Real time = lightInfo->getAttachTime();

			if((currTime >= oldTime && time >= oldTime && time < currTime) || 
				(currTime < oldTime && (time >= oldTime || time < currTime)))
			{
				LightModifyPhase modifyPhase = light->getLightModifyPhase();

				if (modifyPhase == LMP_IDLE)
				{
					light->setFadeTime( lightInfo->getFadeInTime(), lightInfo->getFadeOutTime() );

					light->setLastTime(lightInfo->getLastTime());

					light->setColourValue(lightInfo->getDestColour());
				}

				if (modifyPhase == LMP_LAST)
					light->addLastTime(lightInfo->getLastTime());
			}
		}
	}

	void SkeletonMeshComponent::_createSkillModelElement( Real oldTime,Real currTime )
	{
		for ( ushort i = 0; i < mCurrentSkill->getNumSkillModelElement(); ++i )
		{
			SpellModelModule *tmpSkillModelElement = mCurrentSkill->getSkillModelElement(i);
			assert (tmpSkillModelElement);

			Real time = tmpSkillModelElement->getAttachTime();

			if((currTime >= oldTime && time >= oldTime && time < currTime) || 
				(currTime < oldTime && (time >= oldTime || time < currTime)))
			{
				String attachPoint = tmpSkillModelElement->getAttachPoint();

				TransformInfo info;

				// 先从绑定点找，如果没有再从骨头名称找
				if ( getLocatorWorldTransform( attachPoint, info, tmpSkillModelElement->getOffsetPos(), 
					tmpSkillModelElement->getOffsetRotation() ) )
				{
				}
				else if ( getBoneWorldTransform( attachPoint, info, tmpSkillModelElement->getOffsetPos(), 
					tmpSkillModelElement->getOffsetRotation() ) )
				{
				}

				SkeletonMeshComponent* tmpModel = tmpSkillModelElement->getModel();
				if(NULL != tmpModel)
				{
					SkeletonMeshComponentManager::getSingleton().destroyLogicModel(tmpModel);
					tmpModel = SkeletonMeshComponentManager::getSingleton().createLogicModel(tmpSkillModelElement->getModelTemplateName());
					tmpModel->createSkill(tmpSkillModelElement->getSubSkillTemplateName(), Ogre::Quaternion::IDENTITY);
				}
				else
				{
					tmpModel = SkeletonMeshComponentManager::getSingleton().createLogicModel(tmpSkillModelElement->getModelTemplateName());
					tmpModel->createSkill(tmpSkillModelElement->getSubSkillTemplateName(), Ogre::Quaternion::IDENTITY);
				}

				if(NULL != mModelSceneNode)
					info.mRotation = mModelSceneNode->_getDerivedOrientation();
				tmpModel->setPosition(info.mPosition);
				tmpModel->setOrientation(info.mRotation);

				if(NULL != tmpModel)
				{
					tmpSkillModelElement->setModel(tmpModel);
					tmpSkillModelElement->setIsCreatedInstance(true);
				}
			}
		}
	}

	void SkeletonMeshComponent::_updateSkillModelElement( Real deltaTime )
	{
		for (int i = 0;i < mCurrentSkill->getNumSkillModelElement();i ++)
		{
			SpellModelModule* tmpSkillModelElement = mCurrentSkill->getSkillModelElement(i);

			tmpSkillModelElement->updateRenderInstance(deltaTime);
		}
	}


	//-----------------------------------------------------------------------
	bool SkeletonMeshComponent::attachModel(const String& locatorName, SkeletonMeshComponent* model)
	{
		LocatorMap::iterator itLocator = mLocatorMap.find(locatorName);

		if (itLocator == mLocatorMap.end())
		{
			

			return false;
		}

		AttachedModelOriginSceneNodes::iterator it = mAttachedModelOriginSceneNodes.find(model);

		if (it != mAttachedModelOriginSceneNodes.end())
			it->second = mParentNode;
		else
		{
			std::pair<AttachedModelOriginSceneNodes::iterator, bool> inserted =
				mAttachedModelOriginSceneNodes.insert(AttachedModelOriginSceneNodes::value_type
				(model, mParentNode));

			assert(inserted.second);
		}

		Ogre::SceneNode* locatorNode = _getLocatorSceneNode(itLocator->second);

		model->setParentSceneNode(locatorNode);

		//todo
		//model->mModelSceneNode->setInheritScale(itLocator->second.mChildInheritScale);

		// 被挂接的model要重置位置，这样才能保证被挂接到locator的位置上
		model->resetPosition();

		// 如果在obj文件中没定义包围盒的大小，就根据entity创建包围盒
		if (NULL == mExternalBoundingBox)
			_updateBoundingBox();

		// 告诉被挂接者是谁attach它的
		model->notifyAttach(this);

		return true;
	}
	//-----------------------------------------------------------------------
	bool SkeletonMeshComponent::detachModel( SkeletonMeshComponent* model )
	{
		assert (model);

		AttachedModelOriginSceneNodes::iterator it = mAttachedModelOriginSceneNodes.find(model);

		if ( it == mAttachedModelOriginSceneNodes.end() )
			return false;

		model->setParentSceneNode(it->second);

		mAttachedModelOriginSceneNodes.erase(it);

		// detach，所以挂接者为NULL
		model->notifyAttach(NULL);

		return true;
	}
	//-----------------------------------------------------------------------
	ushort SkeletonMeshComponent::getNumBones(void)
	{
		if (mSkeleton)
			return mSkeleton->getNumBones();
		else
			return 0;
	}
	//-----------------------------------------------------------------------
	const String& SkeletonMeshComponent::getBoneName( ushort index )
	{
		Ogre::Bone* bone = mSkeleton->getBone(index);
		assert(bone);
		return bone->getName();
	}
	//-----------------------------------------------------------------------
	Real SkeletonMeshComponent::getCurrentAnimationLength(void)
	{
		if(mCurrentAnimationState)
		{
			return mCurrentAnimationState->getLength();
		}
		else
			return 0.0f;
	}
	//-----------------------------------------------------------------------
	ushort SkeletonMeshComponent::getSkeletonAnimationCount(void)
	{
		if (mSkeleton)
			return mSkeleton->getNumAnimations();
		else
			return 0;
	}
	//-----------------------------------------------------------------------
	Ogre::Animation* SkeletonMeshComponent::getSkeletonAnimation( ushort index )
	{
		if (mSkeleton)
			return mSkeleton->getAnimation(index);
		else
			return NULL;
	}
	//-----------------------------------------------------------------------
	void SkeletonMeshComponent::getLocatorNames( Ogre::StringVector& names )
	{
		for ( LocatorMap::iterator i = mLocatorMap.begin();
			i != mLocatorMap.end(); ++i )
		{
			names.push_back(i->first);
		}
	}
	//-----------------------------------------------------------------------
	bool SkeletonMeshComponent::_setEntityMaterial(const String& entityEntry, const String& matName)
	{
		// 如果传入一个空字符串，也return true，因为客户端在卸载装备时会给material传入""
		if (matName.empty()) 
		{
			return true;
		}
		else
		{
			EntityMap::iterator itEntity = mEntityMap.find(entityEntry);

			if ( itEntity == mEntityMap.end() )
			{
			
				return false;
			}

			EntityValue& tempEntityValue = itEntity->second;			

			Ogre::Entity* entity = tempEntityValue.mEntity;
			// 此处的修改是因为处理模型的不完整性
			if( NULL == entity )
				return false;
			assert (entity);
			//重新设置entity中的TextureName的引用计数
			// 多材质利用";"来分隔开
			if (matName.find(";") != String::npos)
			{
				Ogre::StringVector matNames = Ogre::StringUtil::split(matName, ";");
				assert (matName.size() > 1);				
				for( uint i=0; i<entity->getNumSubEntities(); ++i )
				{
					Ogre::SubEntity* subEntity = entity->getSubEntity(i);
					assert (subEntity);
					// 如果有配对的material，就使用，没有的话使用第一个material
					Ogre::String subMatName;
					if (i < matNames.size())
					{
						subMatName = matNames[i];
					}
					else
					{
						subMatName = matNames[0];
					}
					// 先检测是否有这个材质
					const Ogre::MaterialPtr subMat = Ogre::MaterialManager::getSingleton().getByName(subMatName);
					if (subMat)
					{
						subEntity->setMaterialName( subMatName );						
					}
				}				
			}
			else
			{
				// 先检测是否有这个材质
				const Ogre::MaterialPtr entityMat = Ogre::MaterialManager::getSingleton().getByName(matName);

				if (entityMat)
				{
					entity->setMaterialName(matName);					
				}
			}	
			//设置材质之后也要再次调用，因为entity中的材质已经变化了
			//_convertEntityToCharacterMaterial(entity);
			deriveHardwareSkinningMaterial( *entity, mDerivedMaterials );

			if (tempEntityValue.mEntityColourChanged)
				_setEntityColour(tempEntityValue, tempEntityValue.mEntityColour);

			if (mCurrentTransparency > 0.0f)
			{
				if (tempEntityValue.mTransparentor)
					delete tempEntityValue.mTransparentor;
				tempEntityValue.mTransparentor = new EntityTransparentor(tempEntityValue.mEntity);
				tempEntityValue.mTransparentor->apply(mCurrentTransparency);
			}
			return true;
		}		
	}
	//-----------------------------------------------------------------------
	void SkeletonMeshComponent::_setEntityMaterials(void)
	{
		for ( MaterialMap::iterator i = mMaterialMap.begin();
			i != mMaterialMap.end(); ++i )
		{
			MaterialValue& tempValue = i->second;			

			_setEntityMaterial(tempValue.mEntityEntry, tempValue.mMaterialName);
		}
	}
	//-----------------------------------------------------------------------
	void SkeletonMeshComponent::_createEffects()
	{
		for ( EffectMap::iterator i = mEffectMap.begin();
			i != mEffectMap.end(); ++i )
		{
			EffectValue& tempValue = i->second;

			if (tempValue.mTranslateAll)
				addEffect(tempValue.mEffectName, tempValue.mLocator, GTIT_ALL, tempValue.mEffectColour, NULL, 3, tempValue.mOffsetPos, tempValue.mOffsetQuat);
			else
				addEffect(tempValue.mEffectName, tempValue.mLocator, GTIT_POSITION, tempValue.mEffectColour, NULL, 3, tempValue.mOffsetPos, tempValue.mOffsetQuat);
		}
	}
	//-----------------------------------------------------------------------
	void SkeletonMeshComponent::_updateAllEffects(void)
	{
		CreatedEffectList::iterator i = mCreatedEffectList.begin();

		while ( i != mCreatedEffectList.end() )
		{
			CreatedEffectInfo& cei = *i;
			
			Orphigine::Impact* effect = cei.mEffect;

			if (effect)
			{
				if ( false == effect->isAlive() )
				{
					i = delEffect(i);

					continue;
				}		
				else
				{
					TransformInfo info;

					GetTransformInfoType transType = cei.mTransformType;
					if(GTIT_ALL == transType && !mEnableEffectScale)  // 此绑定的特效，原来指定的是可以缩放的，但是本Component禁用特效缩放
					{
						transType = GTIT_POSITION_ORIENTATION;  // 所以把转换类型设为没有缩放的
					}

					const String& locatorName = cei.mLocator;

					// 判断是否出于被attach的状态下，如果是，并且locator是可转移的，就要获取
					// attachParent的locator位置了，如上马后，脚下光圈点的特效就要转移到马的
					// 脚下光圈点（在表现上是这样，并不是真的把effect挂接到马的脚下光圈点上）

					if ( mAttachParent // 自身被一个LogicModel所attach
						&& isLocatorTransferable(locatorName) // 该locator是可以转移的
						&& mAttachParent->isLocatorTransferable(locatorName) // attachParent上有这个locator，并且也是可转移的 
						)
					{
						// 获取attachParent上locator的位置
						mAttachParent->getLocatorWorldTransform(locatorName, info, cei.mOffsetPos, cei.mOffsetQuat, transType);
					}
					else
					{
						// 获取自身的locator位置
						getLocatorWorldTransform( locatorName, info, cei.mOffsetPos, cei.mOffsetQuat, transType);
					}

					// 给effect传入点
					effect->setTransformInfo(info);
				}			
			}

			++i;
		}		
	}
	//-----------------------------------------------------------------------
	void SkeletonMeshComponent::setPosition(Ogre::Vector3& pos)
	{
		mModelPosition = pos;
		if (mOrigParentNode == mModelSceneNode->getParent())
		{
			mModelSceneNode->setPosition(mModelPosition);
			mModelSceneNode->updatechildren();
			mSceneNodeNeedUpdate = true;
		}		
	}
	//-----------------------------------------------------------------------
	void SkeletonMeshComponent::setOrientation(Ogre::Quaternion& orientation)
	{
		mModelOrientation = orientation;
		if (mOrigParentNode == mModelSceneNode->getParent())
		{
			mModelSceneNode->setOrientation(mModelOrientation);
			mSceneNodeNeedUpdate = true;
		}		
	}
	//-----------------------------------------------------------------------
	void SkeletonMeshComponent::_updateBoundingBox(void)
	{
		if (!mFullBoundingBox)
			mFullBoundingBox = new Ogre::AxisAlignedBox;

		mFullBoundingBox->setNull();

		// 遍历当前所有的entity
		for ( EntityMap::iterator i = mEntityMap.begin();
			i != mEntityMap.end(); ++i )
		{
			Ogre::Entity* workingEntity = i->second.mEntity;

			if (workingEntity)
			{
				mFullBoundingBox->merge( workingEntity->getBoundingBox() );
			}
		}

		// 遍历所有的attach model
		AttachedModelOriginSceneNodes::const_iterator it = 
			mAttachedModelOriginSceneNodes.begin();

		while (it != mAttachedModelOriginSceneNodes.end())
		{
			if (it->first)
				mFullBoundingBox->merge( it->first->_getFullBoundingBox() );

			++it;
		}
	}
	//-----------------------------------------------------------------------
	void SkeletonMeshComponent::calXAxisRotation(float deltaX, float deltaZ, float deltaHeight)
	{
		float deltaLength = Ogre::Math::Sqrt( deltaZ * deltaZ + deltaX * deltaX );
		float angle = deltaHeight / deltaLength;
		Ogre::Radian radian = Ogre::Math::ATan( angle );

		Ogre::Vector3 axis = mModelSceneNode->getOrientation() * Ogre::Vector3::NEGATIVE_UNIT_X;
		mFrontBackOrientation.FromAngleAxis( radian, axis );
	}
	//-----------------------------------------------------------------------
	void SkeletonMeshComponent::calZAxisRotation(float deltaX, float deltaZ, float deltaHeight)
	{
		float deltaLength = Ogre::Math::Sqrt( deltaZ * deltaZ + deltaX * deltaX );
		float angle = deltaHeight / deltaLength;
		Ogre::Radian radian = Ogre::Math::ATan( angle );

		Ogre::Vector3 axis = mModelSceneNode->getOrientation() * Ogre::Vector3::NEGATIVE_UNIT_Z;
		mLeftRightOrientation.FromAngleAxis( radian, axis );
	}
	//-----------------------------------------------------------------------
	void SkeletonMeshComponent::_rotate(void)
	{
		if (mModelSceneNode)
		{
			if (mPoseType == PT_ROTATE_X_AXIS ||
				mPoseType == PT_ROTATE_X_Z_AXIS)
			{
				TransformInfo frontPointInfo;

				bool succeedFront = getLocatorWorldTransform( "FrontPoint", frontPointInfo, Ogre::Vector3::ZERO,
					Ogre::Quaternion::IDENTITY, GTIT_POSITION );

				TransformInfo backPointInfo;

				bool succeedBack = getLocatorWorldTransform( "BackPoint", backPointInfo, Ogre::Vector3::ZERO,
					Ogre::Quaternion::IDENTITY, GTIT_POSITION );

				if (succeedFront && succeedBack)
				{
					// 获取四个点的地形高度
					float lfy = 0.0f;
					_getWorldHeight(frontPointInfo.mPosition.x, frontPointInfo.mPosition.z, lfy);
					float lby = 0.0f;
					_getWorldHeight(backPointInfo.mPosition.x, backPointInfo.mPosition.z, lby);

					float deltaHeight = lfy-lby;

					// 如果前后点差距太大，就直接跳过
					if (Ogre::Math::Abs(deltaHeight) > MAX_DELTA_HEIGHT)
					{
						
						return;
					}

					float dz = frontPointInfo.mPosition.z - backPointInfo.mPosition.z;
					float dx = frontPointInfo.mPosition.x - backPointInfo.mPosition.x;

					Real deltaLenght = Ogre::Math::Sqrt(dz * dz + dx * dx);
					Real tangent = deltaHeight / deltaLenght;

					if(tangent > MAX_DELTA_TANGENT)
						tangent = MAX_DELTA_TANGENT;
					else if(tangent < -MAX_DELTA_TANGENT)
						tangent = -MAX_DELTA_TANGENT;

					Ogre::Radian rotationAngleRadian = Ogre::Math::ATan(tangent);

					
					if (abs(rotationAngleRadian.valueDegrees() - m_skelControlTargetAngleRadian.valueDegrees()) > 
						MIN_DELTA_ROTATION_DEGREE)
						setSkelControlActive(true,rotationAngleRadian);
				}	
			}			
		}	
	}
	//-----------------------------------------------------------------------
	void SkeletonMeshComponent::_setPoseType( const String& value )
	{
		if ( value == "Normal" )
			mPoseType = PT_NORMAL;
		else if ( value == "RotateX" )
			mPoseType = PT_ROTATE_X_AXIS;
		else if ( value == "RotateXZ" )
			mPoseType = PT_ROTATE_X_Z_AXIS;
		else
		{
			
		}
	}

	void SkeletonMeshComponent::getAllMovableObjects(Ogre::RenderQueue *queue)
	{
		
	}

	//-----------------------------------------------------------------------
	void SkeletonMeshComponent::resetPosition(void)
	{
		mModelPosition = Ogre::Vector3::ZERO;
		mModelOrientation = Ogre::Quaternion::IDENTITY;

		mModelSceneNode->setPosition(mModelPosition);
		mModelSceneNode->setOrientation(mModelOrientation);
	}
	//-----------------------------------------------------------------------
	void SkeletonMeshComponent::setVisible(bool visible)
	{ 
		if (mModelSceneNode)
		{
			mModelSceneNode->setVisible(visible);

			Ogre::Node* parentNode = mModelSceneNode->getParent();

			// 当前要转成可见
			if (visible)
			{
				// 之前removechild了，也就是说这时mVisible为false
				if (parentNode == NULL)
				{
					mParentNode->addChild(mModelSceneNode);
				}
				else
				{
					if (mParentNode != parentNode)
					{
						WARNING_LOG("setVisible error 1");
					}
				}
			}
			else
			{
				if (parentNode != NULL)
				{
					if (mParentNode != parentNode)
					{
						WARNING_LOG("setVisible error 2");
					}

					parentNode->removeChild(mModelSceneNode);
				}
				else
				{
					if (mVisible != visible)
					{
						WARNING_LOG("setVisible error 3");
					}
				}
			}
		}

		mVisible = visible;

		// 通过addEffect添加的特效也要隐藏
		CreatedEffectList::iterator i = mCreatedEffectList.begin();

		while ( i != mCreatedEffectList.end() )
		{
			Orphigine::Impact* effect = (*i).mEffect;

			if (effect)
			{
				effect->setVisible(visible);
			}

			++i;
		}

		// locator上的model也要设置
		for ( LocatorMap::iterator itLocator = mLocatorMap.begin();
			itLocator != mLocatorMap.end(); ++itLocator )
		{
			LocatorValue& tempValue = itLocator->second;

			for ( SlotMap::iterator itSlot = tempValue.mSlotMap.begin();
				itSlot != tempValue.mSlotMap.end(); ++itSlot )
			{
				SlotValue& tempSlot = itSlot->second;

				if (tempSlot.mModel)
					tempSlot.mModel->setVisible(visible);
			}
		}

		// 设置projector
		for ( ModelProjectors::iterator i = mModelProjectors.begin();
			i != mModelProjectors.end(); ++i )
		{
			(*i)->mProjectorEffect->setVisible(visible);
		}

		// 如果把人物隐藏了，他当前所执行的skill也要删除，不然会在场景里留下skill的特效
		if (!visible)
			delCurrentSkill();
	}
	//-----------------------------------------------------------------------
	bool SkeletonMeshComponent::addProjector(ModelProjectorType type, const String& projectorEffectName,
		bool show, float projectorSize)
	{
		
		return true;
	}
	//-----------------------------------------------------------------------
	bool SkeletonMeshComponent::removeProjector(ModelProjectorType type, const String& projectorEffectName)
	{
		
		return false;
	}
	//-----------------------------------------------------------------------
	void SkeletonMeshComponent::_delAllProjector(void)
	{
		for ( ModelProjectors::iterator i = mModelProjectors.begin();
			i != mModelProjectors.end(); ++i )
		{
			ImpactManager::getSingleton().removeEffect((*i)->mProjectorEffect, false);

			delete *i;
			*i = NULL;
		}

		mModelProjectors.clear();
	}
	//-----------------------------------------------------------------------
	void SkeletonMeshComponent::_updateModelProjectors(void)
	{
		// 更新当前挂在人物身上的projector的位置
		for ( ModelProjectors::iterator i = mModelProjectors.begin();
			i != mModelProjectors.end(); ++i )
		{
			Ogre::SceneNode* projectorNode = (*i)->mProjectorNode;
			if (projectorNode)
				// 把这个model当前的世界坐标设置到projector上
				projectorNode->setPosition(mModelSceneNode->_getDerivedPosition());
		}
	}
	bool SkeletonMeshComponent::updateProjectorsPos(const Ogre::Vector3& newPos)
	{
		assert(false);
		return true;
	}
	//-----------------------------------------------------------------------
	void SkeletonMeshComponent::setTransparent(Real time, Real transparency)//这是个递归函数
	{
		// 如果时间为0，就马上设置透明度
		if ( Ogre::Math::RealEqual(time,0.0f) )
		{
			mCurrentTransparency = mDestTransparency = transparency;
			_updateAllEntitiesTransparency();
		}
		else
		{
			// Clamp transparency to range [0, 1]
			if (transparency < 0)
				transparency = 0;
			else if (transparency > 1)
				transparency = 1;

			if (false == Ogre::Math::RealEqual(mDestTransparency,transparency))
			{              
				mDestTransparency = transparency;
				mTransparencyTime = time;
				mNeedUpdateTransparency = true;
				mDeltaTransparency = mDestTransparency - mCurrentTransparency;

				// updateTransparency();
			}
		}
		// locator上的model也要设置
		for ( LocatorMap::iterator itLocator = mLocatorMap.begin();
			itLocator != mLocatorMap.end(); ++itLocator )
		{
			LocatorValue& tempValue = itLocator->second;

			for ( SlotMap::iterator itSlot = tempValue.mSlotMap.begin();
				itSlot != tempValue.mSlotMap.end(); ++itSlot )
			{
				SlotValue& tempSlot = itSlot->second;

				if (tempSlot.mModel)
					tempSlot.mModel->setTransparent(time, transparency);
			}
		}
	}

	//-----------------------------------------------------------------------
	void SkeletonMeshComponent::updateTransparency(Real deltaTime)
	{
		assert (mTransparencyTime > 0.0f);

		Real transparencyInc = deltaTime / mTransparencyTime * mDeltaTransparency;

		mCurrentTransparency += transparencyInc;        

		if ( (mDeltaTransparency >= 0.0f) && (mCurrentTransparency >= mDestTransparency) ||
			(mDeltaTransparency < 0.0f) && (mCurrentTransparency < mDestTransparency) )
		{
			mNeedUpdateTransparency = false;
			mCurrentTransparency = mDestTransparency;
		}

		_updateAllEntitiesTransparency();
	}
	//-----------------------------------------------------------------------
	bool SkeletonMeshComponent::_createModelInSlot(SlotValue& slotValue, LocatorValue& locatorValue)
	{
		if (slotValue.mModelName.empty())
			return false;

		SkeletonMeshComponent* tempModel = SkeletonMeshComponentManager::getSingleton().createLogicModel(slotValue.mModelName,mSkeletonMeshType);

		if (tempModel)
		{
			// 删除原来挂的model
			if (slotValue.mModel)
				SkeletonMeshComponentManager::getSingleton().destroyLogicModel(slotValue.mModel);

			slotValue.mModel = tempModel;

			Ogre::SceneNode* locatorNode = _getLocatorSceneNode(locatorValue);

			tempModel->setParentSceneNode( locatorNode );
			tempModel->setChildModel(true);

			tempModel->setTransparencyInfo(mCurrentTransparency, mDestTransparency,
				Ogre::Math::Abs(mDestTransparency - mCurrentTransparency) * mTransparencyTime);

			// 设置为挂接上的物体的visible flag
			tempModel->setVisibleFlag(mVisibleFlag);
			tempModel->setVisible(mVisible);

			tempModel->setScaleFactor(mExternalScaleFactor);

			return true;
		}

		return false;
	}
	//-----------------------------------------------------------------------
	void SkeletonMeshComponent::_dealWithExtraAttributes(const String& name, const String& value)
	{
		// 处理其他类型的属性
		if (getAttributeTypeFromString(name) == AT_MOVEMENT_TYPE)
		{
			// 设置移动类型
			_setPoseType(value);
		}
		else if (getAttributeTypeFromString(name) == AT_DEFAULT_ANIM_NAME)
		{
			_setDefaultAnimationName(value);
		}
		else if (getAttributeTypeFromString(name) == AT_BOUNDING_BOX)
		{
			mExternalBoundingBoxValue = value;
			// _createBoundingBoxFromExternal(value);
		}
		else if (getAttributeTypeFromString(name) == AT_SCALE)
		{
			_setScaleFactor(value);
		}
	}
	SkeletonMeshComponent::AttributeTypeEnum SkeletonMeshComponent::getAttributeTypeFromString(const Ogre::String& typeString)
	{
		if(typeString == "Mesh")
			return SkeletonMeshComponent::AT_ENTITY_MESH_NAME;
		else if(typeString == "Material")
			return SkeletonMeshComponent::AT_MATERIAL_NAME;
		else if(typeString == "SlotCreate")
			return SkeletonMeshComponent::AT_SLOT_NAME;
		else if(typeString == "MovementType")
			return SkeletonMeshComponent::AT_MOVEMENT_TYPE;
		else if(typeString == "DefaultAnimation")
			return SkeletonMeshComponent::AT_DEFAULT_ANIM_NAME;
		else if(typeString == "BoundingBox")
			return SkeletonMeshComponent::AT_BOUNDING_BOX;
		else if(typeString == "Scale")
			return SkeletonMeshComponent::AT_SCALE;
		else
			return SkeletonMeshComponent::AT_UNKNOWN;
	}
	Ogre::String SkeletonMeshComponent::getAttributeStringFromType(const AttributeTypeEnum type)
	{
		Ogre::String typeString;
		switch(type)
		{
		case AT_ENTITY_MESH_NAME:
			typeString = "Mesh";
			break;
		case AT_MATERIAL_NAME:
			typeString = "Material";
			break;
		case AT_SLOT_NAME:
			typeString = "SlotCreate";
			break;
		case AT_MOVEMENT_TYPE:
			typeString = "MovementType";
			break;
		case AT_DEFAULT_ANIM_NAME:
			typeString = "DefaultAnimation";
			break;
		case AT_BOUNDING_BOX:
			typeString = "BoundingBox";
			break;
		case AT_SCALE:
			typeString = "Scale";
			break;
		default:
			typeString = "Unknown";
			break;
		}
		return typeString;		
	}
	//-----------------------------------------------------------------------
	void SkeletonMeshComponent::setHairColour(const Ogre::ColourValue& colour)
	{
		EntityMap::iterator i = mEntityMap.find(HAIR_MESH_NAME);

		if (i != mEntityMap.end())
		{
			// 获取头发entity
			Ogre::Entity* hairEntity = i->second.mEntity;

			if (hairEntity)
			{
				// 设置颜色变量
				mHairColour = colour;

				_setEntityColour(i->second, colour);
			}
		}
	}
	//-----------------------------------------------------------------------
	Ogre::Entity* SkeletonMeshComponent::_getEntityByName(const String& name)
	{
		EntityMap::iterator i = mEntityMap.find(name);

		if ( i != mEntityMap.end() )
		{
			return i->second.mEntity;
		}
		else
			return NULL;
	}
	//-----------------------------------------------------------------------
	void SkeletonMeshComponent::setShadowCastable(bool castable)
	{
		if (mShadowCastable != castable)
		{
			mShadowCastable = castable;

			// 对当前所有的entity都进行设置
			for ( EntityMap::iterator i = mEntityMap.begin();
				i != mEntityMap.end(); ++i )
			{                
				const String& meshName = i->second.mMeshName;

				// 如果当前这个mesh是规定为不可投影的，就跳到下一个
				if ( isShadowUncastable(meshName) )
					continue;

				Ogre::Entity* workingEntity = i->second.mEntity;
				if (workingEntity)
				{
					workingEntity->setCastShadows(mShadowCastable);
				}
			}
		}        
	}	
	//-----------------------------------------------------------------------
	void SkeletonMeshComponent::_createSkeletonEntity(const Ogre::SkeletonPtr& skeleton)
	{
		mSkeletonEntity = SkeletonMeshComponentManager::getSingleton()._createSkeletalEntity(skeleton);

		mModelSceneNode->attachObject(mSkeletonEntity);
	}
	//-----------------------------------------------------------------------
	void SkeletonMeshComponent::_delSkeletonEntity(void)
	{
		try
		{
			if (mSkeletonEntity)
			{
				// Detach from parent scene node
				Ogre::SceneNode* sn = mSkeletonEntity->getParentSceneNode();
				if (sn && sn == mSkeletonEntity->getParentNode())
				{
					sn->detachObject(mSkeletonEntity);
				}

				// The manager will take care with skeletal entity caching
				SkeletonMeshComponentManager::getSingleton()._destroySkeletalEntity(mSkeletonEntity);
				mSkeletonEntity = 0;
			}
		}
	
		catch(...) 
		{
			
		}
	}
	//-----------------------------------------------------------------------
	void SkeletonMeshComponent::setSelected(bool selected)
	{
		if (mSelected != selected)
		{
			mSelected = selected;

			if (mSelected)
				setBodyColour(Ogre::ColourValue::White);
			else
				resetBodyColour();
		}        
	}
	//-----------------------------------------------------------------------
	void SkeletonMeshComponent::setBodyColour( const Ogre::ColourValue& colour )
	{
		for ( EntityMap::iterator i = mEntityMap.begin();
			i != mEntityMap.end(); ++i )
		{  
			// 不改变头发的颜色
			if (i->first == HAIR_MESH_NAME)
				continue;

			EntityValue& tempValue = i->second;

			_setEntityColour(tempValue, colour);
		}
	}
	//-----------------------------------------------------------------------
	void SkeletonMeshComponent::_setEntityColour( EntityValue& entityValue, const Ogre::ColourValue& entityColour )
	{
		

	}
	//-----------------------------------------------------------------------
	void SkeletonMeshComponent::_clearEntityColorMaterials( EntityValue& entityValue )
	{
		// 删除clone过的material,清除资源难道仅仅remove就行了么？
		for (size_t cloneMatI = 0; cloneMatI < entityValue.mClonedMaterials.size();
			++cloneMatI)
		{
			ClonedMaterialList& materials = entityValue.mClonedMaterials;
			Ogre::String matName = materials[cloneMatI]->getName();

			Ogre::MaterialManager::getSingleton().remove(matName);
		}

		entityValue.mClonedMaterials.clear();
	}
	//-----------------------------------------------------------------------
	void SkeletonMeshComponent::resetBodyColour(void)
	{
		for ( EntityMap::iterator i = mEntityMap.begin();
			i != mEntityMap.end(); ++i )
		{  
			// 不改变头发的颜色
			if (i->first == HAIR_MESH_NAME)
				continue;

			EntityValue& tempValue = i->second;

			tempValue.mEntityColour = Ogre::ColourValue::Black;
			tempValue.mEntityColourChanged = false;

			_setEntityColour(tempValue, tempValue.mEntityOriginColour);
		}
	}

	//-----------------------------------------------------------------------
	void SkeletonMeshComponent::_updateAllEntitiesTransparency(void)
	{
		// 设置自身的entity
		for ( EntityMap::iterator itEntity = mEntityMap.begin();
			itEntity != mEntityMap.end(); ++itEntity )
		{
			Ogre::Entity* pEntity = itEntity->second.mEntity;
			EntityTransparentor* transparentor = itEntity->second.mTransparentor;

			if (pEntity)
			{
				if (transparentor)
				{
					transparentor->apply(mCurrentTransparency);

					//           if (mCurrentTransparency <= 0)
					//           {
					//               delete itEntity->second.mTransparentor;
					//               itEntity->second.mTransparentor = 0;
					//           }
				}
				//    else if (mDestTransparency > 0)
				else
				{
					itEntity->second.mTransparentor = new EntityTransparentor(pEntity);

					itEntity->second.mTransparentor->apply(mCurrentTransparency);
				}
			}           
		}		
	}
	//-----------------------------------------------------------------------
	void SkeletonMeshComponent::setTransparencyInfo(Real currTransparency, Real destTransparency, Real transparentTime)
	{
		if ( mCurrentTransparency != currTransparency ||
			mDestTransparency != destTransparency )
		{
			mCurrentTransparency = currTransparency;
			mDestTransparency = destTransparency;

			if (Ogre::Math::RealEqual(transparentTime, 0.0f))
				_updateAllEntitiesTransparency();
			else
			{
				mTransparencyTime = transparentTime;
				// 这里需要把这个flag设置为true，不然在execute中不update transparency
				mNeedUpdateTransparency = true;

				mDeltaTransparency = mDestTransparency - mCurrentTransparency;
			}
		}
	}
	//-----------------------------------------------------------------------
	void SkeletonMeshComponent::_createBoundingBoxFromExternal(void)
	{
		Ogre::StringVector values = Ogre::StringUtil::split(mExternalBoundingBoxValue, " ");

		if (values.size() != 3)
		{
			OGRE_EXCEPT(Ogre::Exception::ERR_INVALIDPARAMS,
				"the bounding box parameter count must be 3!",
				"SkeletonMeshComponent::_createBoundingBoxFromExternal"); 

			return;
		}

		Real x = Ogre::StringConverter::parseReal(values[0]);
		Real y = Ogre::StringConverter::parseReal(values[1]);
		Real z = Ogre::StringConverter::parseReal(values[2]);

		Ogre::Vector3 minPoint;
		minPoint.x = -x / 2;
		minPoint.z = -z / 2;
		minPoint.y = 0.0f;


		Ogre::Vector3 maxPoint;
		maxPoint.x = x / 2;
		maxPoint.z = z / 2;
		maxPoint.y = y;
		if(mExternalBoundingBox)
		{
			delete mExternalBoundingBox;
			mExternalBoundingBox=NULL;
		}
		mExternalBoundingBox = new Ogre::AxisAlignedBox(minPoint, maxPoint);
	}
	//-----------------------------------------------------------------------
	bool SkeletonMeshComponent::rayIntersect(const Ogre::Ray& ray)
	{
		if (mExternalBoundingBox)
		{
			// 用当前scene node来transform当前指定的boundingbox（因为当前的boundingbox都是局部坐标系的）
			Ogre::AxisAlignedBox intersectedBox(mExternalBoundingBox->getMinimum(), mExternalBoundingBox->getMaximum());

			intersectedBox.transform(mModelSceneNode->_getFullTransform());

			// 把转换后的boundingbox和ray进行检测
			return Ogre::Math::intersects(ray, intersectedBox).first;
		}
		else if (mFullBoundingBox)
		{
			// 用当前scene node来transform当前指定的boundingbox（因为当前的boundingbox都是局部坐标系的）
			Ogre::AxisAlignedBox intersectedBox(mFullBoundingBox->getMinimum(), mFullBoundingBox->getMaximum());

			intersectedBox.transform(mModelSceneNode->_getFullTransform());

			// 把转换后的boundingbox和ray进行检测
			return Ogre::Math::intersects(ray, intersectedBox).first;
		}        
		else
			return false;
	}
	//-----------------------------------------------------------------------
	void SkeletonMeshComponent::_setScaleFactor(const String& value)
	{
		Ogre::StringVector values = Ogre::StringUtil::split(value, " ");

		if (values.size() != 3)
		{
			OGRE_EXCEPT(Ogre::Exception::ERR_INVALIDPARAMS,
				"the scale factor parameter count must be 3!",
				"SkeletonMeshComponent::_setScaleFactor"); 

			return;
		}

		setScaleFactor(Ogre::StringConverter::parseVector3(value));
	}
	//-----------------------------------------------------------------------
	bool SkeletonMeshComponent::_getTemplateEffectName(String& effectName, const String& templateName, float& height)
	{
		
			return true;
	}

	
	void SkeletonMeshComponent::loadSkeleton(const String &name)
	{
		
	}
	//end
	//-----------------------------------------------------------------------
	Ogre::AnimationState* SkeletonMeshComponent::_getAnimationState(const String& animName)
	{
		if (!mSkeletonEntity)
			return nullptr;
		if (!mSkeletonEntity->getAllAnimationStates()->hasAnimationState(animName))
		{
			Animation* ani = mSkeletonEntity->getSkeleton()->getAnimation(animName);
			if (nullptr == ani)
			{
				mSkeletonEntity->getSkeleton()->addLinkedSkeletonAnimationSource(
					SkeletonMeshComponentManager::getSingleton().getSkeletonFromAnimationName(mName, animName));

			}
			
			mSkeletonEntity->refreshAvailableAnimationState();
		}
		return mSkeletonEntity->getAnimationState(animName);
	}
	//---------------------------------------------------------------------
	void SkeletonMeshComponent::_getWorldHeight(float x, float z, float& y)
	{
		try
		{
			mGetHeightInWorld(x,z,y);
		}
		catch (...)
		{

			throw;
		}
	}

	//---------------------------------------------------------------------
	void SkeletonMeshComponent::_executeAttachedModel(Real delta)
	{
		AttachedModelOriginSceneNodes::const_iterator it = 
			mAttachedModelOriginSceneNodes.begin();

		while (it != mAttachedModelOriginSceneNodes.end())
		{
			if (it->first)
				it->first->execute(delta);

			++it;
		}
	}	
	//---------------------------------------------------------------------
	void SkeletonMeshComponent::enableAnimationState(bool enable)
	{
		if (mCurrentAnimationState && mCurrentAnimationState->getEnabled() != enable)
			mCurrentAnimationState->setEnabled(enable);

		if (mFadeOutAnimationState && mFadeOutAnimationState->getEnabled() != enable)
			mFadeOutAnimationState->setEnabled(enable);
	}
	//---------------------------------------------------------------------
	Ogre::SceneNode* SkeletonMeshComponent::_createLocatorSceneNode(const Ogre::Vector3& offsetPos, 
		const Ogre::Quaternion& offsetOri)
	{
		static uint count = 0;
		String name = Ogre::StringUtil::format("Locator_%.5d", count++);
		Ogre::SceneNode* locatorNode = mModelSceneNode->createChildSceneNode(name);
		return locatorNode;
	}
	//---------------------------------------------------------------------
	Ogre::SceneNode* SkeletonMeshComponent::_getLocatorSceneNode(LocatorValue& locatorValue)
	{
		if ( !(locatorValue.mLocatorNode) )
		{
			locatorValue.mLocatorNode =
				_createLocatorSceneNode(locatorValue.mOffsetPos, locatorValue.mOffsetOrientation);
			if (!locatorValue.mBoneName.empty())
				_updateLocatorAttachedToBone(locatorValue);
			else
			{
				locatorValue.mLocatorNode->translate( locatorValue.mOffsetPos );
				locatorValue.mLocatorNode->setOrientation( locatorValue.mOffsetOrientation );

			}
		}

		return locatorValue.mLocatorNode;
	}
	//---------------------------------------------------------------------
	void SkeletonMeshComponent::_refreshViewFrustumVisible(void)
	{
		
	}
	//---------------------------------------------------------------------
	Ogre::StringVector SkeletonMeshComponent::getOriginMeshNames(void)
	{
		Ogre::StringVector nameVector;

		EntityMap::iterator i = mEntityMap.begin();

		while ( i != mEntityMap.end() )
		{
			const EntityValue& entity = i->second;

			if (false == entity.mMeshName.empty())
				nameVector.push_back(entity.mMeshName);

			++i;
		}

		return nameVector;
	}

	Ogre::StringVector SkeletonMeshComponent::getOriginMaterialNames(void)
	{
		Ogre::StringVector nameVector;

		EntityMap::iterator i = mEntityMap.begin();

		while ( i != mEntityMap.end() )
		{
			const EntityValue& entity = i->second;

			if (false == entity.mMaterialName.empty())
				nameVector.push_back(entity.mMaterialName);

			++i;
		}

		return nameVector;
	}

	//---------------------------------------------------------------------
	void SkeletonMeshComponent::playAnimation(const String& animName, Real startTime, Real weight)
	{
		// 检查列表中是否有这个动作，如果有的话，把旧的删除掉
		PlayingAnimationList::iterator animIterator = mPlayingAnimationList.begin();

		while (animIterator != mPlayingAnimationList.end())
		{
			Ogre::AnimationState* state = *animIterator;

			assert(state);

			if (state->getAnimationName() == animName)
			{
				state->setEnabled(false);
				mPlayingAnimationList.erase(animIterator);
				break;
			}

			++animIterator;
		}

		Ogre::AnimationState* state = NULL;

		
		// 有可能因为资源的原因，缺少所需的skeleton文件，所以这个entity为空
		if (mSkeletonEntity)
		{
			state = _getAnimationState(animName);
			/*mSkeleton->getAnimation(animName)->setInterpolationMode(
				SkeletonMeshComponentManager::getSingleton().getAnimationInterpolationMode());*/
		}
		else
		{

			return;
		}

		if (state)
		{
			state->setEnabled(true);
			state->setLoop(true);
			state->setTimePosition(startTime);
			state->setWeight(weight);

			mPlayingAnimationList.push_back(state);
		}
	}
	//---------------------------------------------------------------------
	void SkeletonMeshComponent::_updatePlayingAnimations(Real deltaTime)
	{
		PlayingAnimationList::iterator animIterator = mPlayingAnimationList.begin();

		while (animIterator != mPlayingAnimationList.end())
		{
			Ogre::AnimationState* state = *animIterator;

			assert(state);

			// 如果这个动作已经播放完毕，就把它从列表中删除
			if (state->getTimePosition() >= state->getLength())
			{
				state->setEnabled(false);
				animIterator = mPlayingAnimationList.erase(animIterator);
			}
			else
			{
				// 否则，继续执行这个动作
				state->addTime(deltaTime);
				++animIterator;
			}
		}
	}
	//---------------------------------------------------------------------
	bool SkeletonMeshComponent::_convertEntityToCharacterMaterial(Ogre::Entity* entity)
	{        
			
		return true;
	}
	//---------------------------------------------------------------------
	Ogre::MaterialPtr SkeletonMeshComponent::_deriveHardwareSkinningMaterial(const Ogre::MaterialPtr& origin,
		const String& prefix, const String& postfix, bool useSpecular)
	{
		
		return Ogre::MaterialPtr();
	}
	//---------------------------------------------------------------------
	bool SkeletonMeshComponent::_checkForHardwareSkinningMaterialSupport(void)
	{
		
		return true;
	}
	//---------------------------------------------------------------------
	void SkeletonMeshComponent::destroyDerivedMaterial( )
	{
		//卸载继承的材质
		Ogre::MaterialManager* pMaterialManager = Ogre::MaterialManager::getSingletonPtr( );
		if( pMaterialManager != NULL )
		{
			size_t size = mDerivedMaterials.size( );
			for( size_t i = 0; i < size; ++i )
			{
				if (!mDerivedMaterials[i])
					continue;

				const String& materialName = mDerivedMaterials[i]->getName( );
				mDerivedMaterials[i].reset();

				pMaterialManager->remove( materialName );
			}

			mDerivedMaterials.clear( );
		}
	}
	//---------------------------------------------------------------------
	float SkeletonMeshComponent::getAnimationLength(const String& animName) const
	{
		
			return -1.0f;
	}
	//---------------------------------------------------------------------
	void SkeletonMeshComponent::setCurrentAnimTime(Real range)
	{
		assert (range >= 0.0f && range <= 1.0f);

		if (mCurrentAnimationState)
		{
			mCurrentAnimationState->setTimePosition( mCurrentAnimationState->getLength() * range );
		}
	}
	//---------------------------------------------------------------------
	void SkeletonMeshComponent::setScaleFactor(const Ogre::Vector3& scaleFactor)
	{
		if (!mExternalScaleFactor.positionEquals(scaleFactor))
		{
			mExternalScaleFactor = scaleFactor;

			// child model是不需要把缩放因子设置到节点中的，因为缩放因子会传递下去
			if (false == isChildModel() && mModelSceneNode)
				mModelSceneNode->setScale(mExternalScaleFactor);

			setEntityNormalizeNormal(!mExternalScaleFactor.positionEquals(Ogre::Vector3::UNIT_SCALE));
		}
	}
	//---------------------------------------------------------------------
	void SkeletonMeshComponent::setEntityNormalizeNormal(bool normal)
	{
		// 设置自身的entity
		for ( EntityMap::iterator i = mEntityMap.begin();
			i != mEntityMap.end(); ++i )
		{
			Ogre::Entity* workingEntity = i->second.mEntity;

			if (workingEntity)
			{
				workingEntity->setNormaliseNormals(normal);
			}
		}

		// 设置locator上的model
		for ( LocatorMap::iterator itLocator = mLocatorMap.begin();
			itLocator != mLocatorMap.end(); ++itLocator )
		{
			LocatorValue& tempValue = itLocator->second;

			for ( SlotMap::iterator itSlot = tempValue.mSlotMap.begin();
				itSlot != tempValue.mSlotMap.end(); ++itSlot )
			{
				SlotValue& tempSlot = itSlot->second;

				if (tempSlot.mModel)
					tempSlot.mModel->setEntityNormalizeNormal(normal);
			}
		}
	}
	//616====== 获取当前所在的地面的类型， 以便播放不同的声音
	int SkeletonMeshComponent::_getTerrainSoundType(void)
	{
		return 0;
	}
	void SkeletonMeshComponent::forceUpdateBoundingBox()
	{
		_updateBoundingBox();
	}

	void SkeletonMeshComponent::_createAdvancedAnimationSystem()
	{
		if (!m_advancedAnimationSystemName.empty())
		{
			AdvancedAnimationSystemPtr tmpResourcePtr = AdvancedAnimationSystemManager::getSingleton().
				getAnimationSystem(m_advancedAnimationSystemName);
		
			m_advancedAnimationSystem = new AdvancedAnimationSystemInstance(tmpResourcePtr);
			m_advancedAnimationSystem->setParent(this);
			m_advancedAnimationSystem->load();
			m_advancedAnimationSystem->init();
		}
	}

	AdvancedAnimationSystemInstance* SkeletonMeshComponent::getAdvancedAnimationSystem() const
	{
		return m_advancedAnimationSystem;
	}

	const String& SkeletonMeshComponent::getAdvancedAnimationSystemName() const
	{
		return m_advancedAnimationSystemName;
	}

	void SkeletonMeshComponent::setAdvancedAnimationSystemName( const String& val )
	{ 
		m_advancedAnimationSystemName = val;
	}

	void SkeletonMeshComponent::createManualAdvancedAnimationSystem( const String& name )
	{
		
	}

	void SkeletonMeshComponent::_updateAdvancedAnimationSystem( Real timeElapsed )
	{
		if(NULL == m_advancedAnimationSystem)
			return;

		m_advancedAnimationSystem->update(timeElapsed);

	}

	Ogre::Bone* SkeletonMeshComponent::getBone( const String& boneName ) const
	{
		return nullptr;
	}
	//动作切换是通过这里的接口实现
	void SkeletonMeshComponent::setAASMonitoringDegree( AdvancedAnimationSystemMonitoringDegree monitoringDegreeType,Real degree)
	{
		if(NULL == m_advancedAnimationSystem)
			return;

		switch (monitoringDegreeType)
		{
		case AASMD_DIRECTIONAL_DEGREE:
			m_advancedAnimationSystem->setDirectionalDegree(degree);
			break;
		case AASMD_MOVING_DEGREE:
			m_advancedAnimationSystem->setMovingDegree(degree);
			break;
		case AASMD_RIDING_DEGREE:
			m_advancedAnimationSystem->setRidingDegree(degree);
			break;
		case AASMD_ATTACK_DEGREE:
			m_advancedAnimationSystem->setAttackDegree(degree);
			break;
		case AASMD_LIFE_DEGREE:
			m_advancedAnimationSystem->setLivingDegree(degree);
			break;
		case AASMD_WEAPON_DEGREE:
			m_advancedAnimationSystem->setWeaponDegree(degree);
			break;
		case AASMD_DAMAGE_DEGREE:
			m_advancedAnimationSystem->setDamageDegree(degree);
			break;
		case AASMD_POSTURE_DEGREE:
			m_advancedAnimationSystem->setPostureDegree(degree);
			break;
		case AASMD_EQUITATION_DEGREE:
			m_advancedAnimationSystem->setEquitationDegree(degree);
			break;
		case AASMD_GUARD_DEGREE:
			m_advancedAnimationSystem->setGuardDegree(degree);
			break;
		case AASMD_MOOD_DEGREE:
			m_advancedAnimationSystem->setMoodDegree(degree);
			break;
		case AASMD_DANCE_DEGREE:
			m_advancedAnimationSystem->setDanceDegree(degree);
			break;
		case AASMD_WALK_DEGREE:
			m_advancedAnimationSystem->setWalkDegree(degree);
			break;
		}
	}

	void SkeletonMeshComponent::setAASAnimEndCallback( AASAnimEndCallback* callback, uint64_t info )
	{
		m_animEndCallbackAAS = callback;
		m_callbackInfoAAS = info;
	}

	void SkeletonMeshComponent::setAASAnimPlayCallback( AASAnimPlayCallback* callback, uint64_t info )
	{
		m_animPlayCallbackAAS = callback;
		m_callbackInfoAAS = info;
	}

	void SkeletonMeshComponent::handleAASAnimEndEvent( const String& animName,const String& parentNodeType,const String& parentNodeName )
	{
		if(NULL != m_animEndCallbackAAS)
			m_animEndCallbackAAS->onAnimationEnd(animName.c_str(),parentNodeType.c_str(),parentNodeName.c_str(),m_callbackInfoAAS);
	}

	void SkeletonMeshComponent::handleAASAnimPlayEvent( const String& animName,const String& parentNodeType ,
		unsigned short nodeHandle)
	{
		if(NULL != m_animPlayCallbackAAS)
			m_animPlayCallbackAAS->onAnimationPlay(animName.c_str(),parentNodeType,m_callbackInfoAAS);
	}

	void SkeletonMeshComponent::_deleteAdvancedAnimationSystemInstance()
	{
		try
		{
			if(NULL != m_advancedAnimationSystem)
			{
				delete m_advancedAnimationSystem;

				m_advancedAnimationSystem = NULL;
			}
		}
		catch( const std::exception& e )
		{
			
		}
		catch(...) 
		{
			
		}
	}
	void SkeletonMeshComponent::setWeaponTypeName( const String& typeName )
	{
		if(NULL != m_advancedAnimationSystem)
			m_advancedAnimationSystem->setWeaponTypeName(typeName);
	}

	const	String& SkeletonMeshComponent::getWeaponTypeName() const
	{
		assert(NULL != m_advancedAnimationSystem && "AdvancedAnimationSystem不能为空 SkeletonMeshComponent::getWeaponTypeName()" );

		return	m_advancedAnimationSystem->getWeaponTypeName();
	}

	bool SkeletonMeshComponent::getForceIgnoreAAS() const
	{
		return m_isForceIgnoreAAS;
	}

	void SkeletonMeshComponent::setForceIgnoreAAS( bool val )
	{
		m_isForceIgnoreAAS = val;
	}

	void SkeletonMeshComponent::setMoodAnimName( const String& name )
	{
		delCurrentSkill();

		if(NULL != m_advancedAnimationSystem && !m_isForceIgnoreAAS)
		{
			mCurrentSkill = ImpactManager::getSingleton().createSkill(name);

			if (NULL == mCurrentSkill)
				m_advancedAnimationSystem->setMoodAnimName(name);
			else
				m_advancedAnimationSystem->setMoodAnimName(mCurrentSkill->getAnimationName());
		}
	}

	const	String& SkeletonMeshComponent::getMoodAnimName() const
	{
		assert(NULL != m_advancedAnimationSystem && "AdvancedAnimationSystem不能为空 SkeletonMeshComponent::getMoodAnimName()" );

		return	m_advancedAnimationSystem->getMoodAnimName();
	}

	AASNode* SkeletonMeshComponent::findAASNode( const String& nodeName )
	{
		if (m_advancedAnimationSystem)
			return m_advancedAnimationSystem->findAASNode(nodeName);

		return NULL;
	}

	Ogre::Real SkeletonMeshComponent::getAASGlobalAnimRate() const
	{
		if(m_advancedAnimationSystem)
			return m_advancedAnimationSystem->getGlobalAnimRateScale();
		return 1.0f;
	}

	void SkeletonMeshComponent::setAASGlobalAnimRate( Real rate )
	{
		if (m_advancedAnimationSystem)
			m_advancedAnimationSystem->setGlobalAnimRateScale(rate);
	}

	Real SkeletonMeshComponent::getSkillRate() const
	{
		return m_skillRate;
	}

	void SkeletonMeshComponent::setSkillRate( Real val )
	{
		m_skillRate = val;
	}

	void SkeletonMeshComponent::tickSkelControl( Real deltaSeconds )
	{
		if (m_skelControlTimeLeft > 0.0f)
		{
			if (m_skelControlTimeLeft < deltaSeconds)
			{
				m_skelControlTimeLeft = 0.0f;
				m_skelContrlCurrentAngleRadian = m_skelControlTargetAngleRadian;
			} 
			else
			{
				
				m_skelContrlCurrentAngleRadian += (deltaSeconds / m_skelControlTimeLeft) * 
					(m_skelControlTargetAngleRadian - m_skelContrlCurrentAngleRadian);

				m_skelControlTimeLeft -= deltaSeconds;
			}
		}
		Ogre::Vector3 axis = mModelSceneNode->getOrientation() * Ogre::Vector3::NEGATIVE_UNIT_X;

		mFrontBackOrientation.FromAngleAxis(m_skelContrlCurrentAngleRadian, axis );
		mFrontBackOrientation.normalise();

		mModelSceneNode->setOrientation(mFrontBackOrientation * mModelOrientation);
	}

	void SkeletonMeshComponent::setSkelControlActive(bool isActive,const Ogre::Radian& targetAngleRadian)
	{
		if (isActive)
		{
			m_skelControlTimeLeft = 0.5f;
			m_skelControlTargetAngleRadian = targetAngleRadian;
		} 
	}

	bool SkeletonMeshComponent::getViewFrustumVisible()
	{
		return m_isViewFrustumVisible;
	}

	const Ogre::AxisAlignedBox* SkeletonMeshComponent::getWorldBoundingBox()
	{
		if( mWorldBoundingBox == NULL )
		{
			mWorldBoundingBox = new Ogre::AxisAlignedBox();
		}
		if (mExternalBoundingBox)
		{
			// 用当前scene node来transform当前指定的boundingbox（因为当前的boundingbox都是局部坐标系的）
			mWorldBoundingBox->setMinimum(mExternalBoundingBox->getMinimum());
			mWorldBoundingBox->setMaximum(mExternalBoundingBox->getMaximum());
			mWorldBoundingBox->transform(mModelSceneNode->_getFullTransform());
			return mWorldBoundingBox;
		}
		else if (mFullBoundingBox)
		{
			// 用当前scene node来transform当前指定的boundingbox（因为当前的boundingbox都是局部坐标系的）
			mWorldBoundingBox->setMinimum(mFullBoundingBox->getMinimum());
			mWorldBoundingBox->setMaximum(mFullBoundingBox->getMaximum());
			mWorldBoundingBox->transform(mModelSceneNode->_getFullTransform());
			return mWorldBoundingBox;
		}

		return NULL;
	}
	bool SkeletonMeshComponent::loadFromStream(Ogre::Serializer* pSerializer,Ogre::DataStreamPtr& stream)
	{
		if(pSerializer && stream->eof() == false)
		{
			unsigned short chunkId = pSerializer->readChunk(stream);
			if(chunkId != SkeletonMeshComponentSerializer::SMCFF_SKELETONMESHCOMPONENT)
			{
				WARNING_LOG("Load SkeletonMeshComponent From Stream Failed. ChunkId Error");
				// 因为不读取，所以直接跳过相应数据段长
				pSerializer->skipChunk(stream);
				return false;
			}
			//name
			mName = pSerializer->readStringBin(stream);
			//Attributes
			size_t attributeSize = 0;
			pSerializer->readData(stream,&attributeSize,1,sizeof(attributeSize));
			mAttribMap.clear();
			for (size_t attributeIndex = 0 ; attributeIndex != attributeSize; ++attributeIndex)
			{
				Ogre::String name = pSerializer->readStringBin(stream);
				Ogre::String value = pSerializer->readStringBin(stream);
				AttributeTypeEnum attributeType;
				pSerializer->readData(stream,&attributeType,1,sizeof(attributeType));
				addAttribute(name, value,attributeType);
			}						
			//EntityList
			size_t entitySize = 0;
			pSerializer->readData(stream,&entitySize,1,sizeof(entitySize));
			mEntityMap.clear();
			for (size_t entityIndex = 0 ; entityIndex != entitySize; ++entityIndex)
			{
				Ogre::String entityName = pSerializer->readStringBin(stream);
				Ogre::String meshName = pSerializer->readStringBin(stream);
				Ogre::String matName = pSerializer->readStringBin(stream);
				addEntity(entityName, meshName, matName);
			}
			//MaterialList
			size_t materialSize = 0;
			pSerializer->readData(stream,&materialSize,1,sizeof(materialSize));
			mMaterialMap.clear();
			for (size_t materialIndex = 0 ; materialIndex != materialSize; ++materialIndex)
			{
				Ogre::String materialName = pSerializer->readStringBin(stream);
				Ogre::String entityName = pSerializer->readStringBin(stream);
				Ogre::String matFileName = pSerializer->readStringBin(stream);
				addMaterial(materialName, entityName, matFileName);
			}		
			//Locators
			size_t locatorSize = 0;
			pSerializer->readData(stream,&locatorSize,1,sizeof(locatorSize));
			mLocatorMap.clear();
			for (size_t locatorIndex = 0 ; locatorIndex != locatorSize; ++locatorIndex)
			{
				Ogre::String locatorName = pSerializer->readStringBin(stream);
				Ogre::String boneName = pSerializer->readStringBin(stream);
				
				Ogre::Vector3 locatorOffPos(0,0,0);
				pSerializer->readData(stream,&locatorOffPos,1,sizeof(locatorOffPos));
				Ogre::Radian offRotAngle(0);
				Ogre::Vector3 offRotAxis(1,1,1);
				pSerializer->readData(stream,&offRotAxis,1,sizeof(offRotAxis));			
				pSerializer->readData(stream,&offRotAngle,1,sizeof(offRotAngle));
				//四元数
				Ogre::Quaternion locatorOffRot;
				locatorOffRot.FromAngleAxis(offRotAngle,offRotAxis);

				bool transferableFlag=false, translateFirstFlag=false, childInheritScaleFlag=false;
				pSerializer->readData(stream,&transferableFlag,1,sizeof(transferableFlag));
				pSerializer->readData(stream,&translateFirstFlag,1,sizeof(translateFirstFlag));
				pSerializer->readData(stream,&childInheritScaleFlag,1,sizeof(childInheritScaleFlag));

				Ogre::String transferDestLocatorName = pSerializer->readStringBin(stream);

				if(!transferDestLocatorName.empty())	
					transferableFlag = true;					

				bool locatorIsAddFlag = addLocator(locatorName, boneName, locatorOffPos,locatorOffRot,transferableFlag, 
					translateFirstFlag,childInheritScaleFlag,transferDestLocatorName);
				//slot信息
				size_t slotSize = 0;
				pSerializer->readData(stream,&slotSize,1,sizeof(slotSize));
				LocatorMap::iterator itLocator = mLocatorMap.find(locatorName);
				if(itLocator!=mLocatorMap.end())
				{
					SlotMap& slotMap = itLocator->second.mSlotMap;
					slotMap.clear();
				}
				for (size_t slotIndex = 0 ; slotIndex != slotSize; ++slotIndex)
				{
					Ogre::String slotName = pSerializer->readStringBin(stream);
					Ogre::String slotObjectName = pSerializer->readStringBin(stream);
					if(locatorIsAddFlag)
						addSlot(locatorName,slotName,slotObjectName);
				}				
			}		
			//effects	
			size_t effectSize = 0;
			pSerializer->readData(stream,&effectSize,1,sizeof(effectSize));
			mEffectMap.clear();
			for (size_t effectIndex = 0 ; effectIndex != effectSize; ++effectIndex)
			{
				Ogre::String effectName = pSerializer->readStringBin(stream);
				Ogre::String effectTemplateName = pSerializer->readStringBin(stream);
				Ogre::String locatorName = pSerializer->readStringBin(stream);
				bool translateAllFlag = false;
				pSerializer->readData(stream,&translateAllFlag,1,sizeof(translateAllFlag));
				Ogre::ColourValue effectColor;
				pSerializer->readData(stream,&effectColor,1,sizeof(effectColor));
				addEffectInfo(effectName,effectTemplateName,locatorName,translateAllFlag,effectColor);			
			}		
			//Skeletons
			size_t skeletonSize = 0;
			pSerializer->readData(stream,&skeletonSize,1,sizeof(skeletonSize));
			mAnimationSkeletonMap.clear();
			for (size_t skeletonIndex = 0 ; skeletonIndex != skeletonSize; ++skeletonIndex)
			{
				Ogre::String skeletonName = pSerializer->readStringBin(stream);
				Ogre::String animationsName = pSerializer->readStringBin(stream);
				Ogre::StringVector animationArray = Ogre::StringUtil::split(animationsName);
				for (size_t animationIndex = 0; animationIndex != animationArray.size(); ++animationIndex)
				{
					// 往link map中插入动作与骨骼名称的对应关系
					mAnimationSkeletonMap.insert(std::make_pair(animationArray[animationIndex],skeletonName));
				}
			}
			//advancedAnimationSystem
			size_t aasSize = 0;
			pSerializer->readData(stream,&aasSize,1,sizeof(aasSize));
			for (size_t aasIndex = 0 ; aasIndex != aasSize; ++aasIndex)
			{
				m_advancedAnimationSystemName = pSerializer->readStringBin(stream);
			}		
			return true;
		}
		return false;
	}
	bool SkeletonMeshComponent::saveToBinaryFile(Ogre::Serializer* pSerializer)
	{
		
		return false;
	}
	std::size_t SkeletonMeshComponent::calcSerializedSize(std::map<Ogre::String,Ogre::String>& tempSkeletonAnimationMap)
	{
		size_t tmpSize = Ogre::Serializer::STREAM_OVERHEAD_SIZE;
		//name
		tmpSize += mName.length() + 1;	
		//Attributes
		tmpSize += sizeof(size_t);
		AttribMap::iterator itAttribute = mAttribMap.begin();
		while(itAttribute!=mAttribMap.end())
		{
			tmpSize += itAttribute->first.length() + 1;	
            tmpSize += itAttribute->second.mAttribValue.length() + 1;	
			tmpSize += sizeof(AttributeTypeEnum);	
			++itAttribute;
		}	
		//EntityList
		tmpSize += sizeof(size_t);
		EntityMap::iterator itEntity = mEntityMap.begin();
		while(itEntity!=mEntityMap.end())
		{
			tmpSize += itEntity->first.length() + 1;	
            tmpSize += itEntity->second.mMeshName.length() + 1;	
			tmpSize += itEntity->second.mMaterialName.length() + 1;	
			++itEntity;
		}	
		//MaterialList
		tmpSize += sizeof(size_t);
		MaterialMap::iterator itMaterial = mMaterialMap.begin();
		while(itMaterial!=mMaterialMap.end())
		{
			tmpSize += itMaterial->first.length() + 1;	
            tmpSize += itMaterial->second.mEntityEntry.length() + 1;	
			tmpSize += itMaterial->second.mMaterialName.length() + 1;	
			++itMaterial;
		}	
		//Locators
		tmpSize += sizeof(size_t);
		LocatorMap::iterator itLocator = mLocatorMap.begin();
		while(itLocator!=mLocatorMap.end())
		{
			tmpSize += itLocator->first.length() + 1;	
			tmpSize += itLocator->second.mBoneName.length() + 1;	

			tmpSize += sizeof(itLocator->second.mOffsetPos);
			tmpSize += sizeof(Ogre::Vector3);
			tmpSize += sizeof(Ogre::Radian);
			tmpSize += sizeof(itLocator->second.mTransferable);
			tmpSize += sizeof(itLocator->second.mTranslateFirst);
			tmpSize += sizeof(itLocator->second.mChildInheritScale);
			tmpSize += itLocator->second.mDestLocatorName.length() + 1;
            //slot
			tmpSize += sizeof(size_t);
			SlotMap::iterator itSlot = itLocator->second.mSlotMap.begin();
			while(itSlot!=itLocator->second.mSlotMap.end())
			{
				tmpSize += itSlot->first.length() + 1;	
				tmpSize += itSlot->second.mModelName.length() + 1;	
				++itSlot;
			}
			++itLocator;
		}
		//effects	
		tmpSize += sizeof(size_t);
		EffectMap::iterator itEffect = mEffectMap.begin();
		while(itEffect!=mEffectMap.end())
		{
			tmpSize += itEffect->first.length() + 1;	
			tmpSize += itEffect->second.mEffectName.length() + 1;	
			tmpSize += itEffect->second.mLocator.length() + 1;	
			tmpSize += sizeof(itEffect->second.mTranslateAll);
			tmpSize += sizeof(itEffect->second.mEffectColour);
			++itEffect;
		}
		//Skeletons
		std::map<Ogre::String,std::set<Ogre::String> > tempSkeletonAnimationSetMap;
		std::map<String, String>::iterator itAnimationSkeleton = mAnimationSkeletonMap.begin();
		while(itAnimationSkeleton!=mAnimationSkeletonMap.end())
		{
			std::set<Ogre::String> AnimationSet;
			std::map<Ogre::String,std::set<Ogre::String> >::iterator itSkeletonAnimation = tempSkeletonAnimationSetMap.find(itAnimationSkeleton->second);
			if(itSkeletonAnimation == tempSkeletonAnimationSetMap.end())
			{
				AnimationSet.insert(itAnimationSkeleton->first);					
				tempSkeletonAnimationSetMap.insert(std::make_pair(itAnimationSkeleton->second,AnimationSet));
			}
			else
			{
				(itSkeletonAnimation->second).insert(itAnimationSkeleton->first);
			}
			++itAnimationSkeleton;
		}
		tempSkeletonAnimationMap.clear();
		std::map<Ogre::String,std::set<Ogre::String> >::iterator itSkeletonAnimationSet = tempSkeletonAnimationSetMap.begin();
		while(itSkeletonAnimationSet!=tempSkeletonAnimationSetMap.end())
		{
			Ogre::String animationNames;
			std::set<Ogre::String>::iterator itAnimation = (itSkeletonAnimationSet->second).begin();
			while(itAnimation == (itSkeletonAnimationSet->second).end())
			{
				animationNames.append(*itAnimation + " ");
				++itAnimation;
			}
			tempSkeletonAnimationMap.insert(std::make_pair(itSkeletonAnimationSet->first,animationNames));
			++itSkeletonAnimationSet;
		}	
		tmpSize += sizeof(size_t);
		std::map<Ogre::String,Ogre::String>::iterator itSkeletonAnimation = tempSkeletonAnimationMap.begin();
		while(itSkeletonAnimation!=tempSkeletonAnimationMap.end())
		{	
			tmpSize += itSkeletonAnimation->first.length() + 1;	
			tmpSize += itSkeletonAnimation->second.length() + 1;	
			++itSkeletonAnimation;
		}			
		//advancedAnimationSystem
		if(!m_advancedAnimationSystemName.empty())
		{
			tmpSize += sizeof(size_t);
			tmpSize += m_advancedAnimationSystemName.length() + 1;	
		}
		return tmpSize;
	}
}

