#include "OgreHeader.h"
#include "OGSkeletonMeshActor.h"
#include "OGActorFactory.h"
#include "OGActorProxy.h"
#include "OGEffectActor.h"
#include "OgreDataStream.h"
#include "scene_serializer.h"
#include "OGSkeletonMeshComponentManager.h"
#include "OGSkeletonMeshComponent.h"
#include "OgreStringConverter.h"
#include "OGSkeletonMeshComponentCommand.h"
#include "terrain_info.h"
#include "terrain.h"


namespace Orphigine 
{
	const String SkeletonMeshActor::msType = "SkeletonMeshActor";
	const String SkeletonMeshActor::msCategory = "SkeletonMesh";

	//////////////////////////////////////////////////////////////////////////
	// Factory
	//////////////////////////////////////////////////////////////////////////

	class SkeletonMeshActor::Factory : public ActorFactory
	{
	public:
		const String& getType(void) const
		{
			return msType;
		}

		Actor* createInstance(void)
		{
			return new SkeletonMeshActor;
		}
	};

	
	//////////////////////////////////////////////////////////////////////////
	// Commands
	//////////////////////////////////////////////////////////////////////////
	namespace
	{
		struct LogicModelNameCmd : public PropertyCommand
		{
			Variant doGet(const void* source) const
			{
				const SkeletonMeshActor* object = static_cast<const SkeletonMeshActor*>(source);
				return object->getLogicModelName();
			}

			String doGetAsString(const void* source) const
			{
				const SkeletonMeshActor* object = static_cast<const SkeletonMeshActor*>(source);
				return object->getLogicModelName();
			}

			void doSet(void* target, const Variant& value)
			{
				SkeletonMeshActor* object = static_cast<SkeletonMeshActor*>(target);
				String actorName = VariantCast<String>(value);
				object->setLogicModelName(actorName);
			}

			void doSetAsString(void* target, const String& value)
			{
				SkeletonMeshActor* object = static_cast<SkeletonMeshActor*>(target);
				object->setLogicModelName(value);
			}
		};

		struct PositionCmd : public PropertyCommand
		{
			Variant doGet(const void* source) const
			{
				SkeletonMeshActor* object = const_cast<SkeletonMeshActor*>(static_cast<const SkeletonMeshActor*>(source));
				return object->getModelPosition();
			}

			String doGetAsString(const void* source) const
			{
				SkeletonMeshActor* object = const_cast<SkeletonMeshActor*>(static_cast<const SkeletonMeshActor*>(source));
				return Ogre::StringConverter::toString(object->getModelPosition());
			}

			void doSet(void* target, const Variant& value)
			{
				SkeletonMeshActor* object = static_cast<SkeletonMeshActor*>(target);
				Ogre::Vector3 actorPos = VariantCast<Ogre::Vector3>(value);
				object->setPosition(actorPos);
			}

			void doSetAsString(void* target, const String& value)
			{
				SkeletonMeshActor* object = static_cast<SkeletonMeshActor*>(target);
				Ogre::Vector3 actorPos = Ogre::StringConverter::parseVector3(value);
				object->setPosition(actorPos);
			}
		};

		struct OrientationCmd : public PropertyCommand
		{
			Variant doGet(const void* source) const
			{
				SkeletonMeshActor* object = const_cast<SkeletonMeshActor*>(static_cast<const SkeletonMeshActor*>(source));
				SkeletonMeshComponent* pComponent = object->getLogicModel();
				Ogre::Quaternion ori = (pComponent) ? pComponent->getOrientation() : Ogre::Quaternion::IDENTITY;
				return ori;
			}

			String doGetAsString(const void* source) const
			{
				SkeletonMeshActor* object = const_cast<SkeletonMeshActor*>(static_cast<const SkeletonMeshActor*>(source));
				SkeletonMeshComponent* pComponent = object->getLogicModel();
				Ogre::Quaternion ori = (pComponent) ? pComponent->getOrientation() : Ogre::Quaternion::IDENTITY;
				return Ogre::StringConverter::toString(ori);
			}

			void doSet(void* target, const Variant& value)
			{
				SkeletonMeshActor* object = static_cast<SkeletonMeshActor*>(target);
				Ogre::Quaternion actorOri = VariantCast<Ogre::Quaternion>(value);
				object->setOrientation(actorOri);
			}

			void doSetAsString(void* target, const String& value)
			{
				SkeletonMeshActor* object = static_cast<SkeletonMeshActor*>(target);
				Ogre::Quaternion actorOri = Ogre::StringConverter::parseQuaternion(value);
				object->setOrientation(actorOri);
			}
		};

		struct ScaleCmd : public PropertyCommand
		{
			Variant doGet(const void* source) const
			{
				//SkeletonMeshActor* object = const_cast<SkeletonMeshActor*>(static_cast<const SkeletonMeshActor*>(source));
				//return object->getLogicModel()->getSca;
				return Ogre::Vector3(1, 1, 1);
			}

			String doGetAsString(const void* source) const
			{
				//SkeletonMeshActor* object = const_cast<SkeletonMeshActor*>(static_cast<const SkeletonMeshActor*>(source));
				//return Ogre::StringConverter::toString(object->getModelScale());
				return Ogre::StringConverter::toString(Ogre::Vector3(1, 1, 1));
			}

			void doSet(void* target, const Variant& value)
			{
				//SkeletonMeshActor* object = static_cast<SkeletonMeshActor*>(target);
				//Ogre::Vector3 actorPos = VariantCast<Ogre::Vector3>(value);
				//object->setScale(actorPos);
			}

			void doSetAsString(void* target, const String& value)
			{
				//SkeletonMeshActor* object = static_cast<SkeletonMeshActor*>(target);
				//Ogre::Vector3 actorPos = Ogre::StringConverter::parseVector3(value);
				//object->setScale(actorPos);
			}
		};

		struct BoundingBoxCmd : public PropertyCommand
		{
			Variant doGet(const void* source) const
			{
				SkeletonMeshActor* object = const_cast<SkeletonMeshActor*>(static_cast<const SkeletonMeshActor*>(source));
				return object->getBoundingBox();
			}

			String doGetAsString(const void* source) const
			{
				return String();
			}

			void doSet(void* target, const Variant& value)
			{
			}

			void doSetAsString(void* target, const String& value)
			{
			}
		};

	}

	//////////////////////////////////////////////////////////////////////////
	SkeletonMeshActor::SkeletonMeshActor() :
		mModelGridPosition(Ogre::Vector2::ZERO)
		,mModelPosition(Ogre::Vector3::ZERO)
		,mLogicModelName("")
		,mSkeletonMeshActorType(TE_UNKNOWN)
		,mId(-1)
		,mLogicModelHaveCreateCallback(nullptr)
		,mObjId(-1)
		,mLogicModelId(-1)
		,mLogicModel(nullptr)
		,mTypeId(-1)
		,mIsLoadingResFlag(false)
		,mCommandCacheHandle(0)
		, mProxy(nullptr)
	{
		if (createPropertyDictionary("SkeletonMeshComponent"))
		{
			static LogicModelNameCmd logicModelNameCmd;
			defineProperty(
				"logic model name",
				"The logic model filename use to create this logic model.",
				"LogicModelName",
				&logicModelNameCmd,
				PF_PRIMARY);

			static PositionCmd sPositionCmd;
			defineProperty("position", "The position", "position", &sPositionCmd);

			static OrientationCmd sOrientationCmd;
			defineProperty("orientation", "The orientation", "orientation", &sOrientationCmd);

			static ScaleCmd sScaleCmd;
			defineProperty("scale", "The scale", "scale", &sScaleCmd);

			static BoundingBoxCmd sBoundingBoxCmd;
			defineProperty("bounding box", "The bounding box", "AxisAlignedBox", &sBoundingBoxCmd);
		}

		static uint32_t skeletonMeshActorIndex = 0;
		mName = Ogre::StringUtil::format("SkeletonMesh%.5d", skeletonMeshActorIndex++);

		EngineManager::getSingletonPtr()->registerObject(mName, this);
	}

	SkeletonMeshActor::~SkeletonMeshActor()
	{
		EngineManager::getSingletonPtr()->unregisterObject(mName);
	}
	void SkeletonMeshActor::setName(const String& name)
	{		
		
	}		
	//-----------------------------------------------------------------------
	const String& SkeletonMeshActor::getType(void) const
	{
		return msType;
	}
	//-----------------------------------------------------------------------
	const String& SkeletonMeshActor::getCategory(void) const
	{
		return msCategory;
	}
	//-----------------------------------------------------------------------
	ActorFactory* SkeletonMeshActor::getFactory(void)
	{
		static Factory factory;
		return &factory;
	}	
	bool SkeletonMeshActor::loadFromStream(
		Serializer* pSerializer, 
		std::shared_ptr<DataStream>& stream,
		int32_t version)
	{
		return false;		
	}
	bool SkeletonMeshActor::saveToBinaryFile(Serializer* pSerializer)//逻辑实体的读写操作未实现
	{
		return false;		
	}	
	std::size_t	SkeletonMeshActor::calcSerializedSize()//逻辑实体的读写操作未实现
	{
		return 0;
	}
	//-----------------------------------------------------------------------
	void SkeletonMeshActor::createRenderInstance()
	{		
		mProxy = new ActorProxy(shared_from_this());
		if (!mLogicModelName.empty())
		{
			_createLogicModel();
		}
	}	
	//-----------------------------------------------------------------------
	void SkeletonMeshActor::destroyRenderInstance(void)
	{		
		
	}			
	//-----------------------------------------------------------------------
	void SkeletonMeshActor::setLogicModelName(const String& modelName)//外部调用
	{
		setLogicModelName1(modelName);
	}

	void SkeletonMeshActor::setLogicModelName1(const String& modelName)//直接执行
	{
		if (mLogicModelName != modelName)
		{
			if (mLogicModel)
			{
				_destroyLogicModel();
			}
			mLogicModelName = modelName;
			if (mProxy && !mLogicModelName.empty())//需要创建
			{
				_createLogicModel();
			}
		}
	}	
	bool SkeletonMeshActor::setLogicModelName2(const String& modelName,bool& LoadResFlag)//队列中执行
	{
		
		return true;
	}
	//-----------------------------------------------------------------------
	void SkeletonMeshActor::_createLogicModel(void)
	{
		assert(!mLogicModel);
		assert(mProxy && !mLogicModelName.empty());
		mLogicModel = SkeletonMeshComponentManager::getSingleton().createLogicModel(mLogicModelName, (int)mSkeletonMeshActorType);
		mLogicModel->setUserObject(mProxy);
		if (mLogicModelHaveCreateCallback)//通知客户端
			mLogicModelHaveCreateCallback->onLogicModelHaveCreate(mObjId, mLogicModelId, mTypeId);

		mLogicModel->setVisible(true);
	}	
	//-----------------------------------------------------------------------
	void SkeletonMeshActor::_destroyLogicModel(void)
	{
		
		
	}
	//dscky add///////////////////////////	
	void SkeletonMeshActor::setVisible(bool visible)
	{		
					
	}
	bool SkeletonMeshActor::changeAttribute(const String &name,const String &value)//外部调用
	{		
		return true;
	}	
	bool SkeletonMeshActor::changeAttribute1(const String &name,const String &value)//直接执行
	{
		
		return true;
	}
	bool SkeletonMeshActor::changeAttribute2(const String &name,const String &value,bool& LoadResFlag)//队列中执行
	{
		
		return true;
	}
	bool SkeletonMeshActor::changeAttributes(const std::vector<String> &name, const std::vector<String> &value)
	{
		if (name.size() != value.size())//2个数组大小必须对应
		{
			assert(false);
			return false;
		}

		LogicModelCommand* pLMC = OGRE_NEW LMchangeAttributes2Command(mName, name, value, false);
		assert(pLMC);

		pLMC->execute();
		return true;
	}
	bool SkeletonMeshActor::changeAttributes1(const std::vector<String> &name, const std::vector<String> &value)//直接执行
	{
		return true;
	}
	bool SkeletonMeshActor::changeAttributes2(std::vector<String> &name, const std::vector<String> &value,bool& LoadResFlag)//队列中执行
	{
		if (mLogicModel && name.size() == value.size())
		{
			if (LoadResFlag)//已经加载过资源
			{
				//超过3ms则在后一帧再继续创建
				unsigned long startTime = Ogre::Root::getSingletonPtr()->getTimer()->getMilliseconds();
				unsigned long curTime = 0;
				int vecLen = name.size();
				int vecIndex = 0;
				while (vecIndex != vecLen)
				{
					if (!name[vecIndex].empty())
					{
						mLogicModel->changeAttribute(name[vecIndex], value[vecIndex]);
						name[vecIndex].clear();
					}

					curTime = Ogre::Root::getSingletonPtr()->getTimer()->getMilliseconds();
					if ((curTime - startTime) > 3) //超过3ms不再继续处理
						break;
					++vecIndex;
				}
				if (vecIndex == vecLen)
				{
					mHaveResMap.clear();
					return true;
				}
				else
				{
					//返回false表示阻塞队列
					return false;
				}
				//mLogicModel->changeAttributes(name,value);
				//mHaveResMap.clear();
				//return true;
			}
			else
			{
				//统计所有需要加载的资源
				mHaveResMap.clear();
				Ogre::OStringSet allNoResName;
				int vecLen = name.size();
				for (int vecIndex = 0; vecIndex != vecLen; ++vecIndex)
				{
					Ogre::OResourcePtrMap curHaveResName;
					Ogre::OStringSet curNoResName;
					mLogicModel->getNewAttributeRequestLoadRes(name[vecIndex], value[vecIndex], curHaveResName, curNoResName);
					mHaveResMap.insert(curHaveResName.begin(), curHaveResName.end());
					allNoResName.insert(curNoResName.begin(), curNoResName.end());
				}
				if (!allNoResName.empty())//需要加载资源
				{
					assert(false);
				}

				{
					LoadResFlag = true;
					//超过3ms则在后一帧再继续创建
					unsigned long startTime = Ogre::Root::getSingletonPtr()->getTimer()->getMilliseconds();
					unsigned long curTime = 0;
					int vecLen = name.size();
					int vecIndex = 0;
					while (vecIndex != vecLen)
					{
						//mLogicModel->changeAttribute(name[vecIndex],value[vecIndex]);
						if (!name[vecIndex].empty())
						{
							mLogicModel->changeAttribute(name[vecIndex], value[vecIndex]);
							name[vecIndex].clear();
						}
						curTime = Ogre::Root::getSingletonPtr()->getTimer()->getMilliseconds();

						++vecIndex;
					}
					if (vecIndex == vecLen)
					{
						mHaveResMap.clear();
						return true;
					}
					else
					{
						//返回false表示阻塞队列
						return false;
					}
					//mLogicModel->changeAttributes(name,value);
					//mHaveResMap.clear();
					return true;
				}
			}
		}
		return true;
	}
	
	bool SkeletonMeshActor::getLocatorWorldTransform(const String& name, Ogre::Matrix4& mtx)
	{
			
		return false;
	}

	const Ogre::AxisAlignedBox& SkeletonMeshActor::getBoundingBox(void)
	{	
		static Ogre::AxisAlignedBox tempLMOAAB;
		return tempLMOAAB;
	}
	const Ogre::AxisAlignedBox* SkeletonMeshActor::getWorldBoundingBox()
	{	
		return NULL;
	}

	void SkeletonMeshActor::setAdvancedAnimationSystemMonitoringDegree(
		SkeletonMeshComponent::AdvancedAnimationSystemMonitoringDegree monitoringDegreeType,
		Real degree)
	{
		mLogicModel->setAASMonitoringDegree(monitoringDegreeType, degree);
	}

	void SkeletonMeshActor::setGlobalAnimationRate(Real rate)
	{
		
	}
	void SkeletonMeshActor::setTransparent(Real time, Real transparency)
	{
		
	}
	
	String SkeletonMeshActor::addEffect( const String& effectName, const String& locatorName, 
		uint32_t transformType, const Ogre::ColourValue& colour, int priority)
	{
		return String();
	}

	void SkeletonMeshActor::addEffect1( const String& effectName, const String& locatorName,
		uint32_t transformType,const Ogre::ColourValue& colour,const String& name, int priority)
	{

		
	}

	bool SkeletonMeshActor::delEffect(Ogre::String EffectName)
	{
		return true;
	}
	void SkeletonMeshActor::delAllEffect(void)
	{
		
	}
	void SkeletonMeshActor::setHairColour(const Ogre::ColourValue& colour)
	{
		
	}
	
	
	bool SkeletonMeshActor::attachModelObj(const String& locatorName, SkeletonMeshActor* modelObj)
	{	
		return mLogicModel->attachModel(locatorName, modelObj->getLogicModel());
	}
	bool SkeletonMeshActor::detachModelObj(SkeletonMeshActor* modelObj)
	{		
		return mLogicModel->detachModel(modelObj->getLogicModel());
	}
	void SkeletonMeshActor::setVisibleFlag(uint32 flags)
	{
		
	}

	void SkeletonMeshActor::setPosition(Ogre::Vector3& pos)
	{
		if (EngineManager::getSingleton().getTerrain())
		{
			std::pair<Ogre::Real, Ogre::Real> Pos = 
				EngineManager::getSingleton().getTerrain()->getTerrainInfo()->getRealGridIndexFromWorldIndex(pos.x, pos.z);
			mModelGridPosition = Ogre::Vector2(Pos.first, Pos.second);
		}
		mModelPosition = pos;
		
		if (mLogicModel)
			mLogicModel->setPosition(pos);

	}

	Ogre::Vector2& SkeletonMeshActor::getModelGridPosition()
	{
		return mModelGridPosition;
	}
	Ogre::Vector3&	SkeletonMeshActor::getModelPosition()
	{
		return mModelPosition;
	}
	void SkeletonMeshActor::setOrientation(Ogre::Quaternion& orientation)
	{
		mLogicModel->setOrientation(orientation);
	}
	void SkeletonMeshActor::setSelected(bool selected)
	{
		
	}
	int SkeletonMeshActor::_getTerrainSoundType(void)
	{
		return 0;
	}

	void SkeletonMeshActor::setScaleFactor(const Ogre::Vector3& scaleFactor)
	{
		
	}

	void SkeletonMeshActor::setWeaponTypeName(const String& typeName)
	{
		
	}
	void SkeletonMeshActor::delCurrentSkill(void)
	{
		
	}
	void SkeletonMeshActor::setMoodAnimName(const String& name)
	{
		mLogicModel->setMoodAnimName(name);
	}

	
	void SkeletonMeshActor::forceUpdateBoundingBox()
	{
		
	}
	
	

	void SkeletonMeshActor::setSkillRate( Real val )
	{
		
	}

	bool SkeletonMeshActor::getViewFrustumVisible()
	{
		
		return false;
	}
	bool SkeletonMeshActor::rayIntersect(const Ogre::Ray& ray)
	{
		
		return false;
	}
	bool SkeletonMeshActor::isUseExternalBoundingBox(void)
	{
		
		return false;
	}
	
	bool SkeletonMeshActor::setForceIgnoreAAS(bool val)
	{
		
		return true;
	}	
	bool SkeletonMeshActor::SetLogicModelIsCreateListener(LogicModelHaveCreateCallback* pLMHCC,int objId,int logicModelId,int typeId)
	{
		if(pLMHCC)
		{
			mLogicModelHaveCreateCallback = pLMHCC;		
			mObjId=objId;
			mLogicModelId=logicModelId;
			mTypeId=typeId;
			return true;
		}
		return false;
	}
	bool SkeletonMeshActor::setLogicModelCommandListFlagListener(LogicModelCommandListFlagCallback* pLMCLFC,int value1,int value2,int value3)
	{
		
		return false;

	}
	bool SkeletonMeshActor::setSkeletonMeshActorTypeandId(TypeEnum type,int id)
	{		
		mSkeletonMeshActorType=type;
		mId=id;
		return true;
	}

	Spell* SkeletonMeshActor::getCurrentSkill(void)
	{
		if (mLogicModel && Orphigine::CommandCacheManager::getSingleton().commandCacheisEmpty(mCommandCacheHandle))
		{
			return mLogicModel->getCurrentSkill();
		}
		return nullptr;
	}

	void SkeletonMeshActor::createSkill(
		const String& skillName, 
		const Ogre::Quaternion& rot, 
		int nAnimFlag, 
		bool loop, 
		bool anim, 
		Ogre::Real delayTime, 
		int priority)
	{
		mLogicModel->createSkill(
			skillName, rot, nAnimFlag, loop, anim, delayTime, priority);
	}
}