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

// �������й����еĻص�����
typedef bool          (*OnAnimationFinish)(const char* pAnimationName, unsigned long info, int nFlag );

typedef bool          (*OnSkillHitTime)(const char* pAnimationName, unsigned long info,
										unsigned short index, unsigned short totalCount);

typedef bool          (*OnSkillBreakTime)(const char* pAnimationName, unsigned long info,
										  unsigned short index, unsigned short totalCount);

typedef bool          (*OnSkillShakeTime)(const char* pAnimationName, unsigned long info);
typedef bool          (*OnGetEffectName)(const char* pAnimationName, Ogre::String& effectName);


// ��ȡ��Ϸ������ĳһx��z����ĸ߶�ֵ
typedef bool         (__stdcall*GetHeightInWorld)(float x, float z, float& y);

// ��������ָ��
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


	/// ���������������
	class Fabric;
	class StdCollider;
	class ColliderSet;
}

namespace Orphigine	
{

	const Ogre::ColourValue& _getColourFromMaterial(const Ogre::MaterialPtr& mat);

	enum ModelProjectorType
	{
		MPT_SELECTED,   // ��ѡ��ʱ��ʾ�ĵ�projector
		MPT_SHADOW,     // ���µļ���Ӱ
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
		//�������////////////////////////////////////////
		//����
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
		// ��ɫ������ֵ
		struct AttribValue
		{
			AttribValue():mAttribValue(""), mAttributeType(AT_UNKNOWN){}
			AttribValue(const String& value,const AttributeTypeEnum& type):mAttribValue(value),mAttributeType(type){}
			String mAttribValue;
			AttributeTypeEnum mAttributeType;
			//String mHint;
		};
		//key��������
		typedef std::unordered_map<String, AttribValue> AttribMap;
		// object���ͣ���Ҫ������object�����߷�ʽ
		enum PoseType
		{
			PT_NORMAL, // ��ͨ���ͣ��������������object�ķ�λ
			PT_ROTATE_X_AXIS,	// ֻ��ǰ��ҡ��
			PT_ROTATE_X_Z_AXIS,	// ����ǰ������ҡ��
		};
		AttributeTypeEnum getAttributeTypeFromString(const Ogre::String& typeString);
		Ogre::String getAttributeStringFromType(const AttributeTypeEnum type);
		//�������////////////////////////////////////////

		/// ��������ʱ����������
		//static String MESH_HINT;
		//static String MATERIAL_HINT;
		//static String SLOT_CREATE_HINT;

		/// ������������
		//static String MOVEMENT_TYPE_ATTRIBUTE;
		//static String DEFAULT_ANIM_NAME;
		//static String BOUNDING_BOX;
		//static String SCALE_FACTOR;

		static String HAIR_MESH_NAME;

		/// addEffectʱ���ص���Ч���
		typedef uint32 EffectHandle;

		/// ��ȡlocator��Ϣʱ�ı�־
		enum GetTransformInfoType
		{
			GTIT_POSITION,	// ֻ��ȡλ����Ϣ
			GTIT_ORIENTATION,	// ֻ��ȡ��ת��Ϣ
			GTIT_POSITION_ORIENTATION,  // ֻ��ȡλ�ú���ת��Ϣ������ȡ������Ϣ������ʵ�൱���ϰ��GTIT_ALL

			GTIT_ALL,	// ��ȡλ�á���ת��������Ϣ
		};
		/// �Ѵ�����effect����Ϣ������updateAllEffects
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

		//����ƫ�� by changhao
		Ogre::Vector3 mOffsetPos;
		Ogre::Quaternion mOffsetQuat;

		Impact* mEffect;
		String mLocator;
		GetTransformInfoType mTransformType;
		EffectHandle mEffectHandle;
		//dscky add LogicModel�ӳټ��أ�addEffect������Ч������������ƣ��������ƣ����ں���ɾ��//////
		String mEffectName;//��Ч��Ψһ����
		};

		typedef std::list<CreatedEffectInfo> CreatedEffectList;

		/// slot����
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
		/// locator��Ϣ
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
		bool				mTranslateFirst;   // ��update locator posʱ�Ƿ��Ƚ���translate
		String				mDestLocatorName;   // �����ϵ�ʱ����Ч�İ󶨵�ת��mDestLocatorName
		bool				mChildInheritScale; // �󶨵�����󶨵���ӽڵ��Ƿ�̳�����󶨵��scale����
		};
		typedef std::unordered_map<String, LocatorValue> LocatorMap;


	protected:
		//LogicModel�������������õĲ���ʵ��
		struct ModelMaterialInstance
		{
			ModelMaterialInstance(const Ogre::MaterialPtr& origin);
			~ModelMaterialInstance();

			Ogre::MaterialPtr mClonedOriginMat;
			Ogre::MaterialPtr mClonedDeriveMat;
		};

		/// ͸����
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

		/// ��ͨ��ɫ������entity���б�
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
			/// ����clone���Ĳ���
			ClonedMaterialList mClonedMaterials;

			/// ���entity�����õ���ɫֵ
			Ogre::ColourValue mEntityColour;
			/// entity������ɫ֮ǰ����ɫֵ
			Ogre::ColourValue mEntityOriginColour;
			bool mEntityColourChanged;
		};
	protected:
		typedef std::unordered_map<String, EntityValue> EntityMap;
	public:
		/// material����
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
		/// ��¼obj�ļ���Effects�����Ϣ
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

			//����ƫ�ƺ���ת by changhao
			Ogre::Vector3 mOffsetPos;
			Ogre::Quaternion mOffsetQuat;
		};
		typedef std::unordered_map<String, EffectValue> EffectMap;
	protected:

		/// ���ҽ��ϵ�����ԭ����node
		typedef std::unordered_map<SkeletonMeshComponent*, Ogre::Node*> AttachedModelOriginSceneNodes;

		/// ����model�ϵ�projector
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
			String				mProjectorName;			// ������Ч����
			ModelProjectorType	mType;					// ͶӰ����
			Impact*				mProjectorEffect;		// ��Чָ��
			Ogre::SceneNode*	mProjectorNode;			//
		};
		typedef std::list<ModelProjector*> ModelProjectors;

		/// ��ҪͶ��Ӱ��mesh����
		typedef std::list<String > ShadowUncastableMeshs;

		/// ������붯�����б�
		typedef std::list<Ogre::AnimationState* > PlayingAnimationList;
		PlayingAnimationList mPlayingAnimationList;
	public:
		SkeletonMeshComponent( const String& name,int type=4);
		~SkeletonMeshComponent();

		/// Model����л��գ��ڻ���ǰҪ��reset
		void reset(void);

		/// obj�ļ������Ե�����
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
		//valueΪ�գ�ֻɾ���ɵ�entity
		bool changeEntity( const String &name, const String &value );

		bool addMaterial( const String &name, const String &entityEntry, const String &matName );
		bool changeMaterial( const String &name, const String &value );

		bool addLocator( const String &name, const String &boneName, 
			const Ogre::Vector3 &pos, const Ogre::Quaternion &orientation, bool transferable = false, bool translateFirst = false, bool childInheritScale = true,
			const String & destLocatorName = String());

		/// �ж��������locator�Ƿ�Ϊtransferable
		bool isLocatorTransferable(const String& name);

		bool isLocatorExist(const String& locator);

		/// ��ȡlocator��Ϣ
		bool getLocatorInfo(const String& locator, LocatorValue& locatorInfo);
		bool setLocatorInfo(const String& locator, const LocatorValue& info);

		bool addSlot( const String &locatorName, const String &slotName, const String &modelName);
		bool changeSlotModelName( const String &name, const String &value );

		// �����Ч��Ϣ����obj�ļ��л�ȡ����Ϣ��
		bool addEffectInfo( const String& name, const String& effectName, const String& locatorName, bool translateAll = false, const Ogre::ColourValue& colour = Ogre::ColourValue::White, const Ogre::Vector3& OffsetPos = Ogre::Vector3::ZERO, const Ogre::Quaternion& OffsetQuat = Ogre::Quaternion::IDENTITY);

		bool removeEffectInfo(const String& locatorName, const String& effectName);

		//������Ч��ƫ�ƺ���ת by changaho
		bool setEffectInfoOffsePosQuat(const String& locatorName, const String& effectName, Ogre::Vector3* OffsetPos, Ogre::Quaternion* OffsetQuat);

		//�õ���Ч��ƫ�ƺ���ת by changaho
		bool getEffectInfoOffsePosQuat(const String& locatorName, const String& effectName, Ogre::Vector3* OffsetPos, Ogre::Quaternion* OffsetQuat);

		//������Ч��ƫ�ƺ���ת by changaho
		bool setCreatedEffectOffsePosQuat(const String& locatorName, const String& effectName, Ogre::Vector3* OffsetPos, Ogre::Quaternion* OffsetQuat);

		//�õ���Ч��ƫ�ƺ���ת by changaho
		bool getCreatedEffectOffsePosQuat(const String& locatorName, const String& effectName, Ogre::Vector3* OffsetPos, Ogre::Quaternion* OffsetQuat);

		//���ðﶥ��ƫ�ƺ���ת by changhao
		bool setBindPointInfo(const String& bindName, Ogre::Vector3* OffsetPos, Ogre::Quaternion* OffsetQuat);

		//������͸����Ӱ��mesh����
		bool addShadowUncastable(const String& meshName);
		//�жϸ�mesh�Ƿ�涨Ϊ����ͶӰ
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

		/// ÿ֡�н��б�Ҫ�ĸ��£��綯������Ч��skill�ĸ���
		void execute(Real delta);

		/// ����ȫ�ֵĶ������ʣ�1.0��ʾ1���٣�2.0��ʾ2����
		void setGlobalAnimationRate(Real rate)
		{
			mGlobalAnimationRate = rate;
		}
		Real getGlobalAnimationRate(void)
		{
			return mGlobalAnimationRate;
		}

		/// �������model������entity��visible flag
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

		bool isEnableEffectScale() const { return mEnableEffectScale; }  // ��Component�Ƿ���������Ч����
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

		// ������ݵ�������ת�ĽǶ�
		void calZAxisRotation(float deltaX, float deltaZ, float deltaHeight);
		void calXAxisRotation(float deltaX, float deltaZ, float deltaHeight);

		const String& getCurrentAnimName(void) const
		{
			return mCurrentAnimationName;
		}

		void getAllMovableObjects(Ogre::RenderQueue *queue);

		void resetPosition(void);

		/// ����model�Ƿ���ʾ�������ҽ���locator�ϵ������Լ�attachModel����ȥ������
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

		/// ��ǰ�����Ƿ���ѡ��״̬
		bool isSelected(void)
		{
			return mSelected;
		}

		/** ����������ɫ��ͷ�����⣩
		@param colour Ҫ���õ���ɫֵ
		@param method ��ɫ���÷�ʽ
		*/
		void setBodyColour( const Ogre::ColourValue& colour );
		/// ����������ɫ��ԭʼ����
		void resetBodyColour(void);
		//�������Χ�н����ཻ���ԣ�true��ʾ�ཻ
		bool rayIntersect(const Ogre::Ray& ray);
		/// ��ǰ��bounding box�Ƿ����ⲿ�����
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
		/// ��ǰ������Ƿ��ܿ�����model
		void _refreshViewFrustumVisible(void);
		/// ��ȡentitymap�е�mesh����
		Ogre::StringVector getOriginMeshNames(void);

		//�õ������� by changhao
		Ogre::StringVector getOriginMaterialNames(void);

		void playAnimation(const String& animName, Real startTime = 0.0f, Real weight = 1.0f);
		/// ��ȡָ��������length
		float getAnimationLength(const String& animName) const;
		/// ���ø�model��active״̬,������Ǵ���active״̬,�Ͳ�ˢ��
		void setActive(bool active = true) { mIsActive = active; }
		bool isActive(void)	{	return mIsActive; }
		
		void setCurrentAnimTime(Real range);

		/// ���õ�ǰģ�͵�����ϵ��
		void setScaleFactor(const Ogre::Vector3& scaleFactor);
		const Ogre::Vector3& getScaleFactor() { return mExternalScaleFactor;}

		/// ���µ�ǰ���е�entity��normalize normal״̬
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

		/////////////////// �༭���� ////////////////////////
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



		// ������Ҫ��ת����
		void _rotate(void);

		/// �����ַ��������ò�ͬ���ƶ�����
		void _setPoseType( const String& value );

		/// ɾ������model�ϵ�����projector effect
		void _delAllProjector(void);

		/// ʵ����modelʱ����slot�ϵ�model
		bool _createModelInSlot(SlotValue& slotValue, LocatorValue& locatorValue);

		/// ����Ĭ�϶�������
		void _setDefaultAnimationName(const String& name)
		{
			mDefaultAnimationName = name;
		}

		/// �����������ԣ�û��hint�����ԣ�
		void _dealWithExtraAttributes(const String& name, const String& value);

		
		Ogre::Entity* _getEntityByName(const String& name);

		
		void _createSkeletonEntity(const Ogre::SkeletonPtr& skeleton);

		/// ɾ��master entity
		void _delSkeletonEntity(void);

		/// ����һ��entity����ɫ
		void _setEntityColour( EntityValue& entityValue, const Ogre::ColourValue& entityColour );
		/// ���һ��entity��clone�Ĳ���
		void _clearEntityColorMaterials( EntityValue& entityValue );

		void _updateAllEntitiesTransparency(void);

		/// �����ⲿ��������ݣ�������һ��bounding box
		void _createBoundingBoxFromExternal(void);

		/// �����ⲿ��������ݣ�������������
		void _setScaleFactor(const String& value);

		/// ���ݵ�ǰλ�ã���ȡ����Ӧ��ģ����Ч������
		bool _getTemplateEffectName(String& effectName, const String& templateName, float& height);

		Ogre::AnimationState* _getAnimationState(const String& animName);

		/// ���û�ȡ���θ߶ȵĻص�����
		void _getWorldHeight(float x, float z, float& y);

		/// ����ͨ��attachModel����attach�������model
		void _executeAttachedModel(Real delta);

		Ogre::SceneNode* _createLocatorSceneNode(const Ogre::Vector3& offsetPos, const Ogre::Quaternion& offsetOri);

		Ogre::SceneNode* _getLocatorSceneNode(LocatorValue& locatorValue);

		void _updatePlayingAnimations(Real deltaTime);

		bool _convertEntityToCharacterMaterial(Ogre::Entity* entity);

		Ogre::MaterialPtr _deriveHardwareSkinningMaterial(const Ogre::MaterialPtr& origin,
			const String& prefix, const String& postfix, bool useSpecular);

		/// �жϵ�ǰϵͳ�Ƿ�֧��Ӳ��Ƥ��
		bool _checkForHardwareSkinningMaterialSupport(void);

		void destroyDerivedMaterial( );

	protected:
		/// ���ݳ�Ա
		AttribMap			mAttribMap;
		EntityMap			mEntityMap;
		MaterialMap			mMaterialMap;
		LocatorMap			mLocatorMap;
		EffectMap			mEffectMap;//���������Ǵ�lmodel�н���������effect��Ϣ
		//����LogicModel�Լ����ɵĲ��������ϣ�����ж��
		DerivedMaterialsList mDerivedMaterials;
		//����LogicModel�Լ����ɵ����������ϣ�����ж��
		//std::vector<Ogre::String> mDerivedTextures;


		int		mSkeletonMeshType;//�����Ƿ����ǵȣ�ֵ=SkeletonMeshActor�е�mSkeletonMeshType
		bool	mHaveLogicModelShadow;// �Ƿ���н��µ��Ǹ���ӰȦ


		ShadowUncastableMeshs mShadowUncastableMeshs;

		/// ����model�ϵ�����projector effect���п�����ѡ�б�־��������Ӱ��
		ModelProjectors mModelProjectors;

		Ogre::Any mUserAny;

		Ogre::SceneNode*	mModelSceneNode;
		Ogre::String		mModelSceneNodeName;//��������������֤�����ڵ��Ƿ���ڣ������������ [20/03/2009 dscky]
		Ogre::Node*			mParentNode;
		Ogre::Node*			mOrigParentNode;

		Ogre::Entity* mSkeletonEntity;

		uint32_t mCreatedEntityCount;

		Ogre::SkeletonInstance* mSkeleton;

		//����BoundingBox
		Ogre::AxisAlignedBox* mFullBoundingBox;

		//�Ƿ����BoundingBox
		bool                    mIsPrepareBoundBox;

		Ogre::AnimationState* mCurrentAnimationState;
		Ogre::AnimationState* mFadeOutAnimationState;

		Real mGlobalAnimationRate;

		Real mFadeOutDelay;

		String mCurrentAnimationName;

		bool mAnimationLoop;

		CreatedEffectList mCreatedEffectList; // lmodel�����Ч by changhao

		bool mEnableEffectScale;  // �Ƿ�������Ч����
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

		/// ǰ���ŵص�������Orientation
		Ogre::Quaternion mFrontBackOrientation;
		/// �����ŵص�������Orientation
		Ogre::Quaternion mLeftRightOrientation;

		bool mSceneNodeNeedUpdate;

		/// ��dobject�����ͣ���ͬ�������ڸ���ʱ���в�ͬ����Ϊ
		PoseType mPoseType;

		/// ��ǰmodel��͸����
		Real mCurrentTransparency;

		/// Ŀ��͸����
		Real mDestTransparency;

		/// ͸����delta
		Real mDeltaTransparency;

		/// ͸�����Ƿ�Ҫ��ı�
		bool mNeedUpdateTransparency;

		/// ͸���ȹ���ʱ��
		Real mTransparencyTime;

		/// ��ʼ�������ƣ���ʼ���������modelһ���������Ϳ�ʼѭ�����ŵ�
		String mDefaultAnimationName;

		/// ͷ������ɫ
		Ogre::ColourValue mHairColour;

		/// �Ƿ����ͶӰ
		bool mShadowCastable;

		/** attach��LogicModel��LogicModel
		@remarks ������attachModel��detachModelʱ��Ҫ��this��ɱ�attach��model��mAttachParent��
		�������Լ��Ǳ��ĸ�LogicModel��attach��
		*/
		SkeletonMeshComponent* mAttachParent;

		/// ��ǰ�Ƿ�ѡ��
		bool mSelected;

		Ogre::AxisAlignedBox* mExternalBoundingBox;
		String mExternalBoundingBoxValue;

		Ogre::AxisAlignedBox* mWorldBoundingBox;

		/// �ⲿ�������������
		Ogre::Vector3 mExternalScaleFactor;

		/// ��ײ������
		Ogre::ColliderSet* mColliderSet;

		Real mTerrainHeight;

		uint32 mVisibleFlag;

		bool mEnableWalkingEffect;

		// ������ػص�����
		OnAnimationFinish				mOnAnimationFinish;
		OnSkillBreakTime				mOnSkillBreakTime;
		OnSkillHitTime					mOnSkillHitTime;
		OnSkillShakeTime				mOnSkillShakeTime;
		OnGetEffectName					mOnGetEffectName;

		ulong mCallbackFuncInfo;

		/// �Ƿ�Ϊactive��ֻ��active��model�Ż�ִ��execute
		bool mIsActive;
		/// �Ƿ���Ϊ�ɼ�
		bool mVisible;

		static GetHeightInWorld          mGetHeightInWorld;

		// �����ĺ���ָ��
		static OnPlaySound               mOnPlaySound;
		static OnStopSound               mOnStopSound;

		Real							 m_skillRate;

	public:


		void	forceUpdateBoundingBox();

		Real	getSkillRate() const;
		void	setSkillRate(Real val);

		//�Ӹ���Դ·�� by changhao
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
		//�����붯����map��keyΪ��������,valueΪ������������Ĺ����ļ�����
		std::map<String, String>		mAnimationSkeletonMap;
	public:
		//dscky add logicModel�ӳټ��أ��ͻ�������������������Ч�ļ����ӿ��޷������õ�getAttribute�Ľ�����ĳ�������ִ����������///////////////////
		/// �����󶨵�����
		enum WeaponEnum
		{
			WE_NONE,		// ��
			WE_RIGHT,		// ����
			WE_LEFT,		// ����
			WE_LEFT_SHIELD,	// �����
		};
		bool setWeaponEffect( const String& EffectName, const String& LocatorName,WeaponEnum WeaponType, int priority = 3);
		bool clearWeaponEffect(WeaponEnum WeaponType);
		bool changeWeaponAction(AdvancedAnimationSystemMonitoringDegree eAction, float fDegree,WeaponEnum WeaponType);
		bool changeWeaponActionSpeed(float fRate,WeaponEnum WeaponType);
		//dscky add logicModel�ӳټ��أ��ͻ�������������������Ч�ļ����ӿ��޷������õ�getAttribute�Ľ�����ĳ�������ִ����������///////////////////

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