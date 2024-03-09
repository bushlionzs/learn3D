#ifndef OGSkeletonMeshComponent_h__
#define OGSkeletonMeshComponent_h__

#include "OGComponent.h"
#include "OGVariant.h"
#include "terrain_info.h"
#include "OGSkeletonMeshComponentManager.h"
#include "OGImpact.h"
#include "OGBulletCallbacks.h"
#include "OGUtils.h"

#include <OgreQuaternion.h>
#include <OgreAny.h>
#include <OgreMaterial.h>
#include <OgreRay.h>
#include <OgreIteratorWrapper.h>
#include <ogreskeleton.h>
#include <OgreDataStream.h>
#include <OgreCamera.h>

// 动作运行过程中的回调函数
typedef bool          (*OnAnimationFinish)(const char* pAnimationName, unsigned long info, int nFlag );

typedef bool          (*OnSkillHitTime)(const char* pAnimationName, unsigned long info,
										unsigned short index, unsigned short totalCount);

typedef bool          (*OnSkillBreakTime)(const char* pAnimationName, unsigned long info,
										  unsigned short index, unsigned short totalCount);

typedef bool          (*OnSkillShakeTime)(const char* pAnimationName, unsigned long info);
typedef bool          (*OnGetEffectName)(const char* pAnimationName, Ogre::String& effectName);


// 获取游戏世界中某一x，z坐标的高度值
typedef bool         (__stdcall*GetHeightInWorld)(float x, float z, float& y);

// 声音函数指针
typedef int (__stdcall* OnPlaySound)(const char* szSoundFile, float* fvPos, bool isLoop);
typedef void (__stdcall* OnStopSound)(int handle);

namespace Ogre	{

	class Entity;
	class Any;
	class UserDefinedObject;
	class SkeletonInstance;
	class Node;
	class AnimationState;
	class AxisAlignedBox;
	class Serializer;


	/// 布料所需的类声明
	class Fabric;
	class StdCollider;
	class ColliderSet;
}

namespace Orphigine	
{

	const Ogre::ColourValue& _getColourFromMaterial(const Ogre::MaterialPtr& mat);

	enum ModelProjectorType
	{
		MPT_SELECTED,   // 被选中时显示的的projector
		MPT_SHADOW,     // 地下的简单阴影
	};

	class Engine;
	class Impact;
	class Spell;
	class BulletSystem;
	class BulletFlowSystem;
	class AdvancedAnimationSystemInstance;
	class LogicPhySystem;
	class AASNode;

	enum E_ANIM_FALG
	{
		E_ANIM_BASE = 1,
		E_ANIM_ARM = (E_ANIM_BASE << 1 ),
		E_ANIM_BOTH = (E_ANIM_BASE|E_ANIM_ARM),
	}; 

	class _OrphigineExport SkeletonMeshComponent : public Component
	{
		friend class SkeletonMeshComponentManager;
		friend class AdvancedAnimationSystem;
		friend class XMLSkeletonMeshComponentSerializer;
		friend class SkeletonMeshComponentSerializer;
	public:
		//属性相关////////////////////////////////////////
		//类型
		enum AttributeTypeEnum
		{
			AT_UNKNOWN	= 0,
			AT_ENTITY_MESH_NAME		= 1,
			AT_MATERIAL_NAME		= 2,
			AT_SLOT_NAME			= 3,
			AT_MOVEMENT_TYPE		= 4,
			AT_DEFAULT_ANIM_NAME	= 5,
			AT_BOUNDING_BOX			= 6, 
			AT_SCALE				= 7,
			AT_FUTURE	= 8
		};	
		// 角色的属性值
		struct AttribValue
		{
			AttribValue():mAttribValue(""), mAttributeType(AT_UNKNOWN){}
			AttribValue(const String& value,const AttributeTypeEnum& type):mAttribValue(value),mAttributeType(type){}
			String mAttribValue;
			AttributeTypeEnum mAttributeType;
			//String mHint;
		};
		//key是属性名
		typedef std::unordered_map<String, AttribValue> AttribMap;
		// object类型，主要决定了object的行走方式
		enum PoseType
		{
			PT_NORMAL, // 普通类型，不会随地形修正object的方位
			PT_ROTATE_X_AXIS,	// 只能前后摇摆
			PT_ROTATE_X_Z_AXIS,	// 可以前后左右摇摆
		};
		AttributeTypeEnum getAttributeTypeFromString(const Ogre::String& typeString);
		Ogre::String getAttributeStringFromType(const AttributeTypeEnum type);
		//属性相关////////////////////////////////////////

		/// 设置属性时的属性类型
		//static String MESH_HINT;
		//static String MATERIAL_HINT;
		//static String SLOT_CREATE_HINT;

		/// 特殊属性名称
		//static String MOVEMENT_TYPE_ATTRIBUTE;
		//static String DEFAULT_ANIM_NAME;
		//static String BOUNDING_BOX;
		//static String SCALE_FACTOR;

		static String HAIR_MESH_NAME;

		/// addEffect时返回的特效句柄
		typedef uint32 EffectHandle;

		/// 获取locator信息时的标志
		enum GetTransformInfoType
		{
			GTIT_POSITION,	// 只获取位置信息
			GTIT_ORIENTATION,	// 只获取旋转信息
			GTIT_POSITION_ORIENTATION,  // 只获取位置和旋转信息，不获取缩放信息，这其实相当于老版的GTIT_ALL

			GTIT_ALL,	// 获取位置、旋转和缩放信息
		};
		/// 已创建的effect的信息，用于updateAllEffects
		struct CreatedEffectInfo
		{
			CreatedEffectInfo() :
			mEffect(NULL),
			mLocator(""),
			mTransformType(GTIT_POSITION),
			mEffectHandle(0),
			mEffectName("")
		{
			mOffsetPos = Ogre::Vector3::ZERO;
			mOffsetQuat = Ogre::Quaternion::IDENTITY;
		}

		CreatedEffectInfo(Impact* effect, const String& locatorName, 
			GetTransformInfoType transformType, EffectHandle handle,String EffectName, const Ogre::Vector3& OffsetPos, const Ogre::Quaternion& OffsetQuat) :
			mEffect(effect),
			mLocator(locatorName),
			mTransformType(transformType),
			mEffectHandle(handle),
			mEffectName(EffectName)
		{
			mOffsetPos = OffsetPos;
			mOffsetQuat = OffsetQuat;
		}

		//增加偏移 by changhao
		Ogre::Vector3 mOffsetPos;
		Ogre::Quaternion mOffsetQuat;

		Impact* mEffect;
		String mLocator;
		GetTransformInfoType mTransformType;
		EffectHandle mEffectHandle;
		//dscky add LogicModel延迟加载，addEffect返回无效句柄，增加名称，返回名称，用于后续删除//////
		String mEffectName;//特效的唯一名称
		};

		typedef std::list<CreatedEffectInfo> CreatedEffectList;

		/// slot属性
		struct SlotValue
		{
			SlotValue() : mModelName(""), mModel(NULL)
			{
			}

			SlotValue( const String& modelName ) :
			mModelName(modelName),
				mModel(NULL)
			{
			}

			~SlotValue(void)
			{
				if (mModel)
					SkeletonMeshComponentManager::getSingleton().destroyLogicModel(mModel);
			}

			String mModelName;
			SkeletonMeshComponent* mModel;
		};

		typedef std::map<Ogre::String, SlotValue> SlotMap;
		/// locator信息
		struct	LocatorValue
		{
			LocatorValue() : 
			mBoneName(""),
			mOffsetPos(Ogre::Vector3::ZERO),
			mOffsetOrientation(Ogre::Quaternion::IDENTITY),
			mLocatorNode(NULL),
			mTransferable(false),
			mTranslateFirst(false),
			mChildInheritScale(true)
		{
			mSlotMap.clear();
		}

		LocatorValue(const String& boneName, const Ogre::Vector3& pos, 
			const Ogre::Quaternion& orientation, bool transferable = false,
			bool translateFirst = false,bool childInheritScale = true,const String & destLocatorName = String()) :
			mBoneName(boneName),
			mOffsetPos(pos),
			mOffsetOrientation(orientation),
			mLocatorNode(NULL),
			mTransferable(transferable),
			mTranslateFirst(translateFirst),
			mChildInheritScale(childInheritScale),
			mDestLocatorName(destLocatorName)
		{
			mSlotMap.clear();
		}

		LocatorValue& operator = (const LocatorValue& rhs)
		{
			this->mBoneName = rhs.mBoneName;
			this->mOffsetPos = rhs.mOffsetPos;
			this->mOffsetOrientation= rhs.mOffsetOrientation;
			this->mLocatorNode = rhs.mLocatorNode;
			this->mTransferable = rhs.mTransferable;
			this->mTranslateFirst = rhs.mTranslateFirst;
			this->mChildInheritScale = rhs.mChildInheritScale;
			this->mDestLocatorName = rhs.mDestLocatorName;
			return *this;
		}		
		String	mBoneName;
		Ogre::Vector3		mOffsetPos;
		Ogre::Quaternion	mOffsetOrientation;
		Ogre::SceneNode*	mLocatorNode;
		SlotMap				mSlotMap;
		bool				mTransferable;
		bool				mTranslateFirst;   // 在update locator pos时是否先进行translate
		String				mDestLocatorName;   // 在马上的时候特效的绑定点转到mDestLocatorName
		bool				mChildInheritScale; // 绑定到这个绑定点的子节点是否继承这个绑定点的scale属性
		};
		typedef std::unordered_map<String, LocatorValue> LocatorMap;


	protected:
		//LogicModel渐隐渐现所需用的材质实例
		struct ModelMaterialInstance
		{
			ModelMaterialInstance(const Ogre::MaterialPtr& origin);
			~ModelMaterialInstance();

			Ogre::MaterialPtr mClonedOriginMat;
			Ogre::MaterialPtr mClonedDeriveMat;
		};

		/// 透明器
		class EntityTransparentor
		{
		public:
			EntityTransparentor(void);
			EntityTransparentor(Ogre::Entity* entity);
			~EntityTransparentor();
			void		clear(void);
			void		init(Ogre::Entity* entity);
			void		apply(Real transparency);
		protected:
			Ogre::Entity* mEntity;
			size_t		addMaterial(const Ogre::MaterialPtr& material);
			bool		applyTransparency(const Ogre::MaterialPtr& derived, Real transparency);
		public:
			typedef std::vector<ModelMaterialInstance*>		MaterialInstanceList;
			typedef std::vector<size_t>										IndexList;
			MaterialInstanceList			mMaterialInstances;
			IndexList						mSubEntityMaterialIndices;
			Ogre::SceneNode * mParentNode;			
		};

	public:
		typedef std::vector< Ogre::MaterialPtr> ClonedMaterialList;

		/// 普通角色所带的entity的列表
		struct EntityValue
		{
			EntityValue() : mMeshName(""), mMaterialName(""), mEntity(NULL), mTransparentor(NULL),
				mEntityColour(Ogre::ColourValue::Black), mEntityOriginColour(Ogre::ColourValue::Black),
				mEntityColourChanged(false)
			{
			}

			EntityValue(const String& meshName, const String& matName) :
			mMeshName(meshName),
				mMaterialName(matName),
				mEntity(NULL),
				mTransparentor(NULL),
				mEntityColour(Ogre::ColourValue::Black),
				mEntityOriginColour(Ogre::ColourValue::Black),
				mEntityColourChanged(false)
			{
			}

			String mMeshName;
			String mMaterialName;
			Ogre::Entity* mEntity;
			EntityTransparentor* mTransparentor;
			/// 保存clone过的材质
			ClonedMaterialList mClonedMaterials;

			/// 这个entity所设置的颜色值
			Ogre::ColourValue mEntityColour;
			/// entity设置颜色之前的颜色值
			Ogre::ColourValue mEntityOriginColour;
			bool mEntityColourChanged;
		};
	protected:
		typedef std::unordered_map<String, EntityValue> EntityMap;
	public:
		/// material属性
		struct MaterialValue
		{
			MaterialValue() : mEntityEntry(""), mMaterialName("")
			{
			}

			MaterialValue(const String& entityEntry, const String& matName) :
			mEntityEntry(entityEntry),
				mMaterialName(matName)
			{
			}

			String mEntityEntry;
			String mMaterialName;
		};

		typedef std::unordered_map<String, MaterialValue> MaterialMap;
	protected:
		/// 记录obj文件中Effects项的信息
	public:
		struct EffectValue
		{
			EffectValue() :	mEffectName(""), mLocator(""), mTranslateAll(false), mEffectColour(Ogre::ColourValue::White)
			{
				mOffsetPos = Ogre::Vector3::ZERO;
				mOffsetQuat = Ogre::Quaternion::IDENTITY;
			}

			EffectValue(const String& effectName, const String& locatorName, bool translateAll, const Ogre::ColourValue& colour, const Ogre::Vector3& OffsetPos = Ogre::Vector3::ZERO, const Ogre::Quaternion& OffsetQuat = Ogre::Quaternion::IDENTITY) :
				mEffectName(effectName),
				mLocator(locatorName),
				mTranslateAll(translateAll),
				mEffectColour(colour),
				mOffsetPos(OffsetPos),
				mOffsetQuat(OffsetQuat)
			{
				
			}

			String mEffectName;
			String mLocator;
			bool mTranslateAll;
			Ogre::ColourValue mEffectColour;

			//增加偏移和旋转 by changhao
			Ogre::Vector3 mOffsetPos;
			Ogre::Quaternion mOffsetQuat;
		};
		typedef std::unordered_map<String, EffectValue> EffectMap;
	protected:

		/// 被挂接上的物体原来的node
		typedef std::unordered_map<SkeletonMeshComponent*, Ogre::Node*> AttachedModelOriginSceneNodes;

		/// 挂在model上的projector
		struct ModelProjector
		{
			ModelProjector() : mProjectorName(""), mType(MPT_SELECTED), mProjectorEffect(NULL), mProjectorNode(NULL)
			{
			}

			ModelProjector(const String& projectorName, ModelProjectorType type) :
			mProjectorName(projectorName),
				mType(type),
				mProjectorEffect(NULL),
				mProjectorNode(NULL)
			{
			}
			String				mProjectorName;			// 所用特效名称
			ModelProjectorType	mType;					// 投影类型
			Impact*				mProjectorEffect;		// 特效指针
			Ogre::SceneNode*	mProjectorNode;			//
		};
		typedef std::list<ModelProjector*> ModelProjectors;

		/// 不要投阴影的mesh名称
		typedef std::list<String > ShadowUncastableMeshs;

		/// 保存插入动作的列表
		typedef std::list<Ogre::AnimationState* > PlayingAnimationList;
		PlayingAnimationList mPlayingAnimationList;
	public:
		SkeletonMeshComponent( const String& name,int type=4);
		~SkeletonMeshComponent();

		/// Model会进行回收，在回收前要先reset
		void reset(void);

		/// obj文件中属性的设置
		bool addAttribute( const String &name, const String &value, const AttributeTypeEnum& type);
		bool changeAttribute( const String &name, const String &value );
		bool changeAttributes( const std::vector<String> &names, const std::vector<String> &values );
		bool getNewAttributeRequestLoadRes(const String &name, const String &value, Ogre::OResourcePtrMap& HaveResName, Ogre::OStringSet& NoResName);

		Variant getAttribute( const String& attributeName );
		SkeletonMeshComponent* getAttributePtr( const String& attributeName );

		const AttribMap& getAttribMap(void)
		{
			return mAttribMap;
		}


		// dscky add 
		virtual bool		loadFromStream(Ogre::Serializer* pSerializer,Ogre::DataStreamPtr& stream);
		virtual bool		saveToBinaryFile(Ogre::Serializer* pSerializer);
		virtual std::size_t	calcSerializedSize(std::map<Ogre::String,Ogre::String>& tempSkeletonAnimationMap);
		// dscky add

		bool getAttribute( const String& name, String& value);
		bool hasAttribute( const String& name );
		bool addEntity( const String &name, const String &meshName, const String &matName );
		//value为空，只删除旧的entity
		bool changeEntity( const String &name, const String &value );

		bool addMaterial( const String &name, const String &entityEntry, const String &matName );
		bool changeMaterial( const String &name, const String &value );

		bool addLocator( const String &name, const String &boneName, 
			const Ogre::Vector3 &pos, const Ogre::Quaternion &orientation, bool transferable = false, bool translateFirst = false, bool childInheritScale = true,
			const String & destLocatorName = String());

		/// 判断所传入的locator是否为transferable
		bool isLocatorTransferable(const String& name);

		bool isLocatorExist(const String& locator);

		/// 获取locator信息
		bool getLocatorInfo(const String& locator, LocatorValue& locatorInfo);
		bool setLocatorInfo(const String& locator, const LocatorValue& info);

		bool addSlot( const String &locatorName, const String &slotName, const String &modelName);
		bool changeSlotModelName( const String &name, const String &value );

		// 添加特效信息（从obj文件中获取该信息）
		bool addEffectInfo( const String& name, const String& effectName, const String& locatorName, bool translateAll = false, const Ogre::ColourValue& colour = Ogre::ColourValue::White, const Ogre::Vector3& OffsetPos = Ogre::Vector3::ZERO, const Ogre::Quaternion& OffsetQuat = Ogre::Quaternion::IDENTITY);

		bool removeEffectInfo(const String& locatorName, const String& effectName);

		//设置特效的偏移和旋转 by changaho
		bool setEffectInfoOffsePosQuat(const String& locatorName, const String& effectName, Ogre::Vector3* OffsetPos, Ogre::Quaternion* OffsetQuat);

		//得到特效的偏移和旋转 by changaho
		bool getEffectInfoOffsePosQuat(const String& locatorName, const String& effectName, Ogre::Vector3* OffsetPos, Ogre::Quaternion* OffsetQuat);

		//设置特效的偏移和旋转 by changaho
		bool setCreatedEffectOffsePosQuat(const String& locatorName, const String& effectName, Ogre::Vector3* OffsetPos, Ogre::Quaternion* OffsetQuat);

		//得到特效的偏移和旋转 by changaho
		bool getCreatedEffectOffsePosQuat(const String& locatorName, const String& effectName, Ogre::Vector3* OffsetPos, Ogre::Quaternion* OffsetQuat);

		//设置帮顶点偏移和旋转 by changhao
		bool setBindPointInfo(const String& bindName, Ogre::Vector3* OffsetPos, Ogre::Quaternion* OffsetQuat);

		//不可以透射阴影的mesh名称
		bool addShadowUncastable(const String& meshName);
		//判断该mesh是否规定为不可投影
		bool isShadowUncastable(const String& meshName);

		void setUserAny(const Ogre::Any& anything);
		const Ogre::Any& getUserAny(void) const;

		void setUserObject(Ogre::UserDefinedObject* obj);
		Ogre::UserDefinedObject* getUserObject(void) const;

		void setParentSceneNode(Ogre::Node* parentNode, bool changeOrignal = false);		
		Ogre::SceneNode* getSceneNode(void)
		{
			return mModelSceneNode;
		}

		void destroySceneNode(void);

		void destroyEntities(void);

		const Ogre::AxisAlignedBox&     getBoundingBox(void);

		const Ogre::AxisAlignedBox*		getWorldBoundingBox(void);

		void initModel(void);

		/// 每帧中进行必要的更新，如动作，特效，skill的更新
		void execute(Real delta);

		/// 设置全局的动作速率，1.0表示1倍速，2.0表示2倍速
		void setGlobalAnimationRate(Real rate)
		{
			mGlobalAnimationRate = rate;
		}
		Real getGlobalAnimationRate(void)
		{
			return mGlobalAnimationRate;
		}

		/// 设置这个model上所有entity的visible flag
		void setVisibleFlag(uint32 flags);
		uint32 getVisibleFlag(void)
		{
			return mVisibleFlag;
		}

		void setAnimationLoop(bool loop, int nAnimFlag = 0xFFFFFFFF);
		bool getAnimationLoop(void)
		{
			return mAnimationLoop;
		}

		bool isEnableEffectScale() const { return mEnableEffectScale; }  // 本Component是否启用了特效缩放
		void enableEffectScale(bool enable) { mEnableEffectScale = enable; }

		
		void addEffect( const String& effectName, const String& locatorName, GetTransformInfoType transformType = GTIT_POSITION, const Ogre::ColourValue& colour = Ogre::ColourValue::White,const char* pName=NULL, int priority = 3, const Ogre::Vector3& OffsetPos = Ogre::Vector3::ZERO, const Ogre::Quaternion& OffsetQuat = Ogre::Quaternion::IDENTITY);
		
		bool delEffect( EffectHandle handle );
		//end
		bool delEffect(Ogre::String name);

		CreatedEffectList::iterator delEffect( CreatedEffectList::iterator effectIterator );

		void delAllEffect(void);

		Impact* getEffect(EffectHandle handle);

		SkeletonMeshComponent::EffectHandle _addEffect( const String& effectName, const String& locatorName, SkeletonMeshComponent::GetTransformInfoType transformType, const Ogre::ColourValue& colour,const char* pName, int priority = 3, const Ogre::Vector3& OffsetPos = Ogre::Vector3::ZERO, const Ogre::Quaternion& OffsetQuat = Ogre::Quaternion::IDENTITY);
		//end

		Impact* getEffect(Ogre::String name);


		bool getLocatorWorldTransform(const String& name, Orphigine::TransformInfo& info, const Ogre::Vector3& offsetPos = Ogre::Vector3::ZERO,
			const Ogre::Quaternion& offsetRotation = Ogre::Quaternion::IDENTITY, GetTransformInfoType type = GTIT_ALL,bool useAttachRotation = true );
		bool getBoneWorldTransform(const String& name, Orphigine::TransformInfo& info, const Ogre::Vector3& offsetPos = Ogre::Vector3::ZERO,
			const Ogre::Quaternion& offsetRotation = Ogre::Quaternion::IDENTITY, GetTransformInfoType type = GTIT_ALL );

		bool getLocatorWorldTransform(const String& name, Ogre::Matrix4& mtx);


		void createSkill(const String& skillName, const Ogre::Quaternion& rot, int nAnimFlag=E_ANIM_BOTH, bool loop = true, 
			bool anim = false, Ogre::Real delayTime = 0.0f, int priority = 3);
		void delCurrentSkill(void);

		Spell* getCurrentSkill(void)
		{	
			return mCurrentSkill;
		}

		void setName(const String& name)
		{
			mName = name;
		}
		const String& getName(void)
		{
			return mName;
		}		

		bool attachModel(const String& locatorName, SkeletonMeshComponent* model);
		bool detachModel( SkeletonMeshComponent* model );
		void notifyAttach(SkeletonMeshComponent* parentModel)
		{
			mAttachParent = parentModel;
		}

		bool isAttached(void)
		{
			return (mAttachParent != NULL);
		}

		SkeletonMeshComponent* getAttachModel(void)
		{
			return mAttachParent;
		}

		bool isChildModel(void)
		{
			return mChildModel;
		}

		void setChildModel(bool child)
		{
			mChildModel = child;
		}

		void setPosition(Ogre::Vector3& pos);

		Ogre::Vector3& getPosition(void)
		{
			return mModelPosition;
		}

		void setOrientation(Ogre::Quaternion& orientation);

		Ogre::Quaternion& getOrientation(void)
		{
			return mModelOrientation;
		}

		bool isSceneNodeNeedUpdate(void) const
		{
			return mSceneNodeNeedUpdate;
		}

		// 计算根据地形所旋转的角度
		void calZAxisRotation(float deltaX, float deltaZ, float deltaHeight);
		void calXAxisRotation(float deltaX, float deltaZ, float deltaHeight);

		const String& getCurrentAnimName(void) const
		{
			return mCurrentAnimationName;
		}

		void getAllMovableObjects(Ogre::RenderQueue *queue);

		void resetPosition(void);

		/// 设置model是否显示，包括挂接在locator上的物体以及attachModel挂上去的物体
		void setVisible(bool visible);

		bool addProjector(ModelProjectorType type, const String& projectorEffectName,
			bool show = true, float projectorSize = 100.0f);

		
		bool removeProjector(ModelProjectorType type, const String& projectorEffectName);

		
		void setTransparent(Real time, Real transparency);


		void updateTransparency(Real deltaTime);

		
		void setTransparencyInfo(Real currTransparency, Real destTransparency, Real transparentTime);

		void setHairColour(const Ogre::ColourValue& colour);

		Ogre::ColourValue& getHairColour(void)
		{
			return mHairColour;
		}

		void setShadowCastable(bool castable);

	
		void setSelected(bool selected);

		/// 当前人物是否处于选中状态
		bool isSelected(void)
		{
			return mSelected;
		}

		/** 设置身体颜色（头发除外）
		@param colour 要设置的颜色值
		@param method 颜色设置方式
		*/
		void setBodyColour( const Ogre::ColourValue& colour );
		/// 重置身体颜色到原始材质
		void resetBodyColour(void);
		//射线与包围盒进行相交测试，true表示相交
		bool rayIntersect(const Ogre::Ray& ray);
		/// 当前的bounding box是否是外部定义的
		bool isUseExternalBoundingBox(void)
		{
			return NULL != mExternalBoundingBox;
		}
		void enableAnimationState(bool enable = true);

		void setEnableWalkingEffect(bool enable)
		{
			mEnableWalkingEffect = enable;
		}
		bool getEnableWalkingEffect(void)
		{
			return mEnableWalkingEffect;
		}
		const Ogre::AxisAlignedBox& _getFullBoundingBox(void)
		{
			if (!mFullBoundingBox)
				mFullBoundingBox = new Ogre::AxisAlignedBox;
			return *mFullBoundingBox;
		}
		/// 当前摄像机是否能看见该model
		void _refreshViewFrustumVisible(void);
		/// 获取entitymap中的mesh名称
		Ogre::StringVector getOriginMeshNames(void);

		//得到材质链 by changhao
		Ogre::StringVector getOriginMaterialNames(void);

		void playAnimation(const String& animName, Real startTime = 0.0f, Real weight = 1.0f);
		/// 获取指定动作的length
		float getAnimationLength(const String& animName) const;
		/// 设置该model的active状态,如果不是处于active状态,就不刷新
		void setActive(bool active = true) { mIsActive = active; }
		bool isActive(void)	{	return mIsActive; }
		
		void setCurrentAnimTime(Real range);

		/// 设置当前模型的缩放系数
		void setScaleFactor(const Ogre::Vector3& scaleFactor);
		const Ogre::Vector3& getScaleFactor() { return mExternalScaleFactor;}

		/// 更新当前所有的entity的normalize normal状态
		void setEntityNormalizeNormal(bool normal);

		//////////////////////////////////////////////////////////////////////////
		void SetAnimationFinishListener(OnAnimationFinish func, ulong info)
		{
			mOnAnimationFinish = func;
			mCallbackFuncInfo = info;
		}
		OnAnimationFinish GetAnimationFinishListener(void)
		{
			return mOnAnimationFinish;
		}

		void SetSkillHitTimeListener(OnSkillHitTime func, ulong info)
		{
			mOnSkillHitTime = func;
			mCallbackFuncInfo = info;
		}
		OnSkillHitTime GetSkillHitTimeListener(void)
		{
			return mOnSkillHitTime;
		}

		void SetSkillBreakTimeListener(OnSkillBreakTime func, ulong info)
		{
			mOnSkillBreakTime = func;
			mCallbackFuncInfo = info;
		}
		OnSkillBreakTime GetSkillBreakTimeListener(void)
		{
			return mOnSkillBreakTime;
		}

		void SetSkillShakeTimeListener(OnSkillShakeTime func, ulong info)
		{
			mOnSkillShakeTime = func;
			mCallbackFuncInfo = info;
		}
		OnSkillShakeTime GetSkillShakeTimeListener(void)
		{
			return mOnSkillShakeTime;
		}

		void SetGetEffectNameListener(OnGetEffectName func, ulong info)
		{
			mOnGetEffectName = func;
			mCallbackFuncInfo = info;
		}
		OnGetEffectName GetGetEffectNameListener(void)
		{
			return mOnGetEffectName;
		}

		//////////////////////////////////////////////////////////////////////////
		static void SetGetHeightInWorldListener(GetHeightInWorld func)
		{
			mGetHeightInWorld = func;
		}
		static GetHeightInWorld GetGetHeightInWorldListener(void)
		{
			return mGetHeightInWorld;
		}

		static void SetPlaySoundFuncton(OnPlaySound func)
		{
			mOnPlaySound = func;
		}
		static OnPlaySound GetPlaySoundFuncton(void)
		{
			return mOnPlaySound;
		}

		static void SetStopSoundFunction(OnStopSound func)
		{
			mOnStopSound = func;
		}
		static OnStopSound GetStopSoundFunction(void)
		{
			return mOnStopSound;
		}

		/////////////////// 编辑功能 ////////////////////////
		ushort				getNumBones(void);
		const String&		getBoneName( ushort index );
		Ogre::Bone*			getBone(const String& boneName) const;

		Real getCurrentAnimationLength(void);

		ushort getSkeletonAnimationCount(void);

		Ogre::Animation* getSkeletonAnimation( ushort index );

		void getLocatorNames( Ogre::StringVector& names );

		bool getAnimEditing(void)
		{
			return mAnimEditing;
		}
		void setAnimEditing(bool edit = true)
		{	
			mAnimEditing = edit;
		}

		void setAnimTimePos(Real sliderValue)
		{
			mAnimationTimePos = sliderValue;
		}
		Real getAnimTimePos(void)	
		{
			return mAnimationTimePos;
		}

		Real getCurrentTimePos(void);	

		typedef Ogre::MapIterator<LocatorMap> LocatorMapIterator;
		LocatorMapIterator getLocatorMapIterator(void)
		{
			return LocatorMapIterator(
				mLocatorMap.begin(), mLocatorMap.end());
		}

		inline size_t getLocatorSize() {return mLocatorMap.size();}

		/// offer iterator to visit property direct
		typedef Ogre::MapIterator<EntityMap> EntityMapIterator;
		EntityMapIterator getEntityIterator()	{return EntityMapIterator(mEntityMap.begin(),mEntityMap.end());}

		inline size_t getEntitySize() {return mEntityMap.size();}

		typedef Ogre::MapIterator<AttribMap> AttribMapIterator;
		AttribMapIterator getAttribIterator()	{return AttribMapIterator(mAttribMap.begin(),mAttribMap.end());}

		inline size_t getAttribSize() {return mAttribMap.size();}

		typedef Ogre::MapIterator<MaterialMap>	MaterialMapIterator;
		MaterialMapIterator	getMaterialIterator()	{return MaterialMapIterator(mMaterialMap.begin(),mMaterialMap.end());}

		inline size_t getMaterialSize() {return mMaterialMap.size();}

		typedef Ogre::MapIterator<EffectMap>	EffectMapIterator;
		EffectMapIterator	getEffectIterator()	{return EffectMapIterator(mEffectMap.begin(),mEffectMap.end());}

		inline size_t getEffectSize() {return mEffectMap.size();}

		const CreatedEffectList&	GetCreatedEffectList() const	{return mCreatedEffectList;}

		Ogre::Entity*	GetSkeletonEntity()							{return mSkeletonEntity;}

		int _getTerrainSoundType(void);
	
		void loadSkeleton(const String &name);

		void updateLocatorAttachedToBone(Ogre::String& bindPointName, bool isIgnoreXAxisRotation = false, bool isIgnoreYAxisRotation = false,bool isIgnoreZAxisRotation = false);
		
		//end
	public:

		void _updateLocatorAttachedToBone(LocatorValue& locatorValue,bool isIgnoreXAxisRotation = false, bool isIgnoreYAxisRotation = false,bool isIgnoreZAxisRotation = false);

		void _createEntity(void);

		void _setEntityMaterials(void);

		Ogre::Entity* _createEntityImpl( const String& meshName );

		void _destroyEntityImpl(Ogre::Entity* entity);

		void _createMainSceneNode(void);

		void _createLocatorNode(void);

		bool _changeAnimation(const String& animationName, Real delay, int nAnimFlag );

		void _updateLocatorPos(void);

		void _animationBlend(Real delta);

		void _executeLocatorModel(Real delta);

		void _muteCurrentSkillSound(void);

		bool _handleAnimationFinish(Real oldTime, Real currTime, int nFlag);

		void _handleSkillHitTime(Real oldTime, Real currTime);

		void _handleSkillBreakTime(Real oldTime, Real currTime);

		void _handleSkillShakeTime(Real oldTime, Real currTime);

		void _createAnimationEffect(Real oldTime, Real currTime);
		void _updateAttachedAnimationEffect(Real oldTime, Real currTime);

		void _createAnimationBulletFlow(Real oldTime,Real currTime);

		void _createAnimationRibbon(Real oldTime, Real currTime);
		void _updateAnimationRibbon(Real delta);

		void _updateAnimationSound(Real oldTime, Real currTime);

		void _updateAnimationLight(Real oldTime, Real currTime);

		void _createSkillModelElement(Real oldTime,Real currTime);
		void _updateSkillModelElement(Real deltaTime);

		bool _setEntityMaterial(const String& entityEntry, const String& matName);

		void _createEffects(void);

		void _updateAllEffects(void);

		bool updateProjectorsPos(const Ogre::Vector3& newPos);
		void _updateModelProjectors(void);

		void _updateBoundingBox(void);



		// 根据需要旋转物体
		void _rotate(void);

		/// 根据字符串来设置不同的移动类型
		void _setPoseType( const String& value );

		/// 删除挂在model上的所有projector effect
		void _delAllProjector(void);

		/// 实例化model时创建slot上的model
		bool _createModelInSlot(SlotValue& slotValue, LocatorValue& locatorValue);

		/// 设置默认动作名称
		void _setDefaultAnimationName(const String& name)
		{
			mDefaultAnimationName = name;
		}

		/// 处理其他属性（没有hint的属性）
		void _dealWithExtraAttributes(const String& name, const String& value);

		
		Ogre::Entity* _getEntityByName(const String& name);

		
		void _createSkeletonEntity(const Ogre::SkeletonPtr& skeleton);

		/// 删除master entity
		void _delSkeletonEntity(void);

		/// 设置一个entity的颜色
		void _setEntityColour( EntityValue& entityValue, const Ogre::ColourValue& entityColour );
		/// 清除一个entity所clone的材质
		void _clearEntityColorMaterials( EntityValue& entityValue );

		void _updateAllEntitiesTransparency(void);

		/// 利用外部定义的数据，创建出一个bounding box
		void _createBoundingBoxFromExternal(void);

		/// 根据外部定义的数据，设置缩放因子
		void _setScaleFactor(const String& value);

		/// 根据当前位置，获取所对应的模板特效的名称
		bool _getTemplateEffectName(String& effectName, const String& templateName, float& height);

		Ogre::AnimationState* _getAnimationState(const String& animName);

		/// 调用获取地形高度的回调函数
		void _getWorldHeight(float x, float z, float& y);

		/// 更新通过attachModel方法attach到自身的model
		void _executeAttachedModel(Real delta);

		Ogre::SceneNode* _createLocatorSceneNode(const Ogre::Vector3& offsetPos, const Ogre::Quaternion& offsetOri);

		Ogre::SceneNode* _getLocatorSceneNode(LocatorValue& locatorValue);

		void _updatePlayingAnimations(Real deltaTime);

		bool _convertEntityToCharacterMaterial(Ogre::Entity* entity);

		Ogre::MaterialPtr _deriveHardwareSkinningMaterial(const Ogre::MaterialPtr& origin,
			const String& prefix, const String& postfix, bool useSpecular);

		/// 判断当前系统是否支持硬件皮肤
		bool _checkForHardwareSkinningMaterialSupport(void);

		void destroyDerivedMaterial( );

	protected:
		/// 数据成员
		AttribMap			mAttribMap;
		EntityMap			mEntityMap;
		MaterialMap			mMaterialMap;
		LocatorMap			mLocatorMap;
		EffectMap			mEffectMap;//这个保存的是从lmodel中解析出来的effect信息
		//所有LogicModel自己生成的材质名集合，用于卸载
		DerivedMaterialsList mDerivedMaterials;
		//所有LogicModel自己生成的纹理名集合，用于卸载
		//std::vector<Ogre::String> mDerivedTextures;


		int		mSkeletonMeshType;//标明是否主角等，值=SkeletonMeshActor中的mSkeletonMeshType
		bool	mHaveLogicModelShadow;// 是否具有脚下的那个阴影圈


		ShadowUncastableMeshs mShadowUncastableMeshs;

		/// 挂在model上的所有projector effect，有可能是选中标志，地下阴影等
		ModelProjectors mModelProjectors;

		Ogre::Any mUserAny;

		Ogre::SceneNode*	mModelSceneNode;
		Ogre::String		mModelSceneNodeName;//保存名字用于验证场景节点是否存在，解决析构崩溃 [20/03/2009 dscky]
		Ogre::Node*			mParentNode;
		Ogre::Node*			mOrigParentNode;

		Ogre::Entity* mSkeletonEntity;

		uint32_t mCreatedEntityCount;

		Ogre::SkeletonInstance* mSkeleton;

		//完整BoundingBox
		Ogre::AxisAlignedBox* mFullBoundingBox;

		//是否完成BoundingBox
		bool                    mIsPrepareBoundBox;

		Ogre::AnimationState* mCurrentAnimationState;
		Ogre::AnimationState* mFadeOutAnimationState;

		Real mGlobalAnimationRate;

		Real mFadeOutDelay;

		String mCurrentAnimationName;

		bool mAnimationLoop;

		CreatedEffectList mCreatedEffectList; // lmodel里的特效 by changhao

		bool mEnableEffectScale;  // 是否启用特效缩放
		uint32_t mEffectHandleCount;

		Spell* mCurrentSkill;
		// end


		Real mAnimationTimePos;
		bool mAnimEditing;

		String mName;

		bool mChildModel;

		Ogre::Vector3 mModelPosition;
		Ogre::Quaternion mModelOrientation;

		AttachedModelOriginSceneNodes mAttachedModelOriginSceneNodes;

		/// 前后着地点计算出的Orientation
		Ogre::Quaternion mFrontBackOrientation;
		/// 左右着地点计算出的Orientation
		Ogre::Quaternion mLeftRightOrientation;

		bool mSceneNodeNeedUpdate;

		/// 该dobject的类型，不同的类型在更新时会有不同的行为
		PoseType mPoseType;

		/// 当前model的透明度
		Real mCurrentTransparency;

		/// 目标透明度
		Real mDestTransparency;

		/// 透明度delta
		Real mDeltaTransparency;

		/// 透明度是否要求改变
		bool mNeedUpdateTransparency;

		/// 透明度过渡时间
		Real mTransparencyTime;

		/// 初始动作名称，初始动作是这个model一创建出来就开始循环播放的
		String mDefaultAnimationName;

		/// 头发的颜色
		Ogre::ColourValue mHairColour;

		/// 是否可以投影
		bool mShadowCastable;

		/** attach该LogicModel的LogicModel
		@remarks 当调用attachModel和detachModel时，要把this设成被attach的model的mAttachParent，
		这样，自己是被哪个LogicModel所attach的
		*/
		SkeletonMeshComponent* mAttachParent;

		/// 当前是否被选中
		bool mSelected;

		Ogre::AxisAlignedBox* mExternalBoundingBox;
		String mExternalBoundingBoxValue;

		Ogre::AxisAlignedBox* mWorldBoundingBox;

		/// 外部定义的缩放因子
		Ogre::Vector3 mExternalScaleFactor;

		/// 碰撞器集合
		Ogre::ColliderSet* mColliderSet;

		Real mTerrainHeight;

		uint32 mVisibleFlag;

		bool mEnableWalkingEffect;

		// 动作相关回调函数
		OnAnimationFinish				mOnAnimationFinish;
		OnSkillBreakTime				mOnSkillBreakTime;
		OnSkillHitTime					mOnSkillHitTime;
		OnSkillShakeTime				mOnSkillShakeTime;
		OnGetEffectName					mOnGetEffectName;

		ulong mCallbackFuncInfo;

		/// 是否为active，只有active的model才会执行execute
		bool mIsActive;
		/// 是否设为可见
		bool mVisible;

		static GetHeightInWorld          mGetHeightInWorld;

		// 声音的函数指针
		static OnPlaySound               mOnPlaySound;
		static OnStopSound               mOnStopSound;

		Real							 m_skillRate;

	public:


		void	forceUpdateBoundingBox();

		Real	getSkillRate() const;
		void	setSkillRate(Real val);

		//加个资源路径 by changhao
		Ogre::String					 mScriptPath;

	public:
		enum AdvancedAnimationSystemMonitoringDegree
		{
			AASMD_NOTHING_DEGREE = -1,
			AASMD_DIRECTIONAL_DEGREE,
			AASMD_MOVING_DEGREE,
			AASMD_RIDING_DEGREE,
			AASMD_ATTACK_DEGREE,
			AASMD_LIFE_DEGREE,
			AASMD_WEAPON_DEGREE,
			AASMD_DAMAGE_DEGREE,
			AASMD_POSTURE_DEGREE,
			AASMD_EQUITATION_DEGREE,
			AASMD_GUARD_DEGREE,
			AASMD_MOOD_DEGREE,
			AASMD_DANCE_DEGREE,
			AASMD_WALK_DEGREE
		};

		AdvancedAnimationSystemInstance*			getAdvancedAnimationSystem() const;

		const String&						getAdvancedAnimationSystemName() const;
		void										setAdvancedAnimationSystemName(const String& val);

		void										createManualAdvancedAnimationSystem(const String& name);

		void										setAASMonitoringDegree(AdvancedAnimationSystemMonitoringDegree 
			monitoringDegreeType = AASMD_NOTHING_DEGREE,Real degree = 0.0f);

		void										setWeaponTypeName(const String& typeName);
		const	String&								getWeaponTypeName() const;

		void										setMoodAnimName(const String& name);
		const	String&								getMoodAnimName() const;

		class	 AASAnimEndCallback
		{
		public:
			virtual void	onAnimationEnd(const char* animName,const char* parentNodeType,const char* parentNodeName,
				uint64_t info) = 0;
		};

		class	AASAnimPlayCallback
		{
		public:
			virtual void	onAnimationPlay(const char* animName,const String& parentNodeType, uint64_t info) = 0;
		};

		void										setAASAnimEndCallback(AASAnimEndCallback* callback, uint64_t info);

		void										setAASAnimPlayCallback(AASAnimPlayCallback* callback, uint64_t info);

		void										handleAASAnimEndEvent(const String& animName,const String& parentNodeType,
			const String& parentNodeName);

		void										handleAASAnimPlayEvent(const String& animName,const String& parentNodeType,
			unsigned short nodeHandle);

		bool										getForceIgnoreAAS() const;
		void										setForceIgnoreAAS(bool val);

		AASNode*									findAASNode(const String& nodeName);

		Real										getAASGlobalAnimRate() const;
		void										setAASGlobalAnimRate(Real rate);
	protected:
		void										_createAdvancedAnimationSystem();

		void										_updateAdvancedAnimationSystem(Real timeElapsed);

		void										_deleteAdvancedAnimationSystemInstance();
	protected:
		AdvancedAnimationSystemInstance*			m_advancedAnimationSystem;
		String										m_advancedAnimationSystemName;
		AASAnimEndCallback*							m_animEndCallbackAAS;
		AASAnimPlayCallback*						m_animPlayCallbackAAS;
		uint64_t							m_callbackInfoAAS;
		bool										m_isAnimForCurrentSkillStart;
		Real										m_AnimationTimePosForCurrentSkill;
		Ogre::AnimationState*						m_animStateForCurrentSkillCache;
		bool										m_isForceIgnoreAAS;

		
	protected:
		void	tickSkelControl(Real deltaSeconds);

		void	setSkelControlActive(bool isActive,const Ogre::Radian& targetAngleRadian);
	protected:
		Real m_skelControlTimeLeft;
		Ogre::Radian m_skelControlTargetAngleRadian;
		Ogre::Radian m_skelContrlCurrentAngleRadian;
	
	public:

	protected:
		//骨骼与动作的map，key为动作名称,value为包含这个动作的骨骼文件名称
		std::map<String, String>		mAnimationSkeletonMap;
	public:
		//dscky add logicModel延迟加载，客户端设置左右手武器特效的几个接口无法立即得到getAttribute的结果，改成在这里执行整个函数///////////////////
		/// 武器绑定点类型
		enum WeaponEnum
		{
			WE_NONE,		// 空
			WE_RIGHT,		// 右手
			WE_LEFT,		// 左手
			WE_LEFT_SHIELD,	// 左盾牌
		};
		bool setWeaponEffect( const String& EffectName, const String& LocatorName,WeaponEnum WeaponType, int priority = 3);
		bool clearWeaponEffect(WeaponEnum WeaponType);
		bool changeWeaponAction(AdvancedAnimationSystemMonitoringDegree eAction, float fDegree,WeaponEnum WeaponType);
		bool changeWeaponActionSpeed(float fRate,WeaponEnum WeaponType);
		//dscky add logicModel延迟加载，客户端设置左右手武器特效的几个接口无法立即得到getAttribute的结果，改成在这里执行整个函数///////////////////

	protected:
		void	_updateRenderQueue(Real seconds);

		void	_updateLogicQueue(Real delta);

	public:
		bool	getViewFrustumVisible();

	protected:
		bool	m_isViewFrustumVisible;
	};
}

#endif // OGSkeletonMeshComponent_h__