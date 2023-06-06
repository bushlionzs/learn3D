#ifndef OGSkeletonMeshActor_h__
#define OGSkeletonMeshActor_h__

#include "OGActor.h"
#include "OgreColourValue.h"
#include "OGSkeletonMeshComponent.h"


namespace Orphigine 
{
	class SkeletonMeshComponent;
	class ActorFactory;
	class ActorProxy;
	class AASNode;

	//LogicModel执行命令序列的阶段标识
	class LogicModelCommandListFlagCallback
	{
	public:
		virtual bool onLogicModelCommandListFlag(int value1=-1,int value2=-1,int value3=-1) = 0;
	};
	//LogicModel是否创建成功的回调
	class LogicModelHaveCreateCallback
	{
	public:
		virtual bool onLogicModelHaveCreate(int objId=-1,int logicModelId=-1,int typeId=-1) = 0;
	};

	class  SkeletonMeshActor : public Actor
	{
	public:
		class Factory;
	public:
		SkeletonMeshActor(void);
		virtual ~SkeletonMeshActor();
		enum TypeEnum
		{
			TE_UNKNOWN	= -1,
			TE_PREMIER			= 0,//主角(主角、主角马、主角武器、主角宠物)
			TE_PREMIER_RELATE	= 1,//主角相关(队友、仇人、……)
			TE_PLAYER			= 2,//玩家(玩家、玩家马、玩家武器、玩家宠物)
			TE_ACTOR			= 3,//活动体(NPC、bus、……)
			TE_OTHER			= 4,//其它闲杂人等
			TE_FUTURE	= 5
		};

		virtual const String&	getType(void) const;
		virtual const String&	getCategory(void) const;

		virtual void			createRenderInstance();
		virtual void			destroyRenderInstance(void);
		virtual void			setName(const String& name);
		//序列化
		virtual bool loadFromStream(
			Serializer* pSerializer,
			std::shared_ptr<DataStream>& stream,
			int32_t version);
		virtual bool			saveToBinaryFile(Serializer* pSerializer);
		virtual std::size_t		calcSerializedSize();


		void setLogicModelName(const String& modelName);
		void setLogicModelName1(const String& modelName);
		bool setLogicModelName2(const String& modelName,bool& LoadResFlag);

		const String& getLogicModelName(void) const
		{
			return mLogicModelName;
		}
		SkeletonMeshComponent* getLogicModel(void)
		{
			return mLogicModel;
		}
		bool IsLogicModelCreate()
		{
			return mLogicModel!=NULL;
		}

		//////////////////////////////////////////////////////////////////////////

		static const String msType;
		static const String msCategory;

		static ActorFactory* getFactory(void);

		void			_createLogicModel(void);
		void			_destroyLogicModel(void);
		Ogre::Vector2&	getModelGridPosition();
		Ogre::Vector3&	getModelPosition();

		Spell* getCurrentSkill(void);

		void createSkill(
			const String& skillName,
			const Ogre::Quaternion& rot,
			int nAnimFlag,
			bool loop,
			bool anim,
			Ogre::Real delayTime,
			int priority);

		bool setWeaponEffect(
			char* pEffectName, 
			char* pLocatorName, 
			SkeletonMeshComponent::WeaponEnum WeaponType, 
			int priority);
		bool clearWeaponEffect(
			SkeletonMeshComponent::WeaponEnum WeaponType);
	protected:		
		Ogre::Vector2	mModelGridPosition;	//转换LogicModel的位置为格子坐标，用于加载排序
		Ogre::Vector3	mModelPosition;		//LogicModel的位置,用于attach之前的设置
		Ogre::String	mLogicModelName;
		SkeletonMeshComponent*		mLogicModel;
		//身份标识
		TypeEnum		mSkeletonMeshActorType;
		int				mId;
		ActorProxy* mProxy;
	public:
		LogicModelHaveCreateCallback*  mLogicModelHaveCreateCallback;
		bool		setSkeletonMeshActorTypeandId(TypeEnum type,int id);
		int			getSkeletonMeshActorId()	  { return mId; }
		TypeEnum	getSkeletonMeshActorType() { return mSkeletonMeshActorType;}
		//logicModel创建后的通知回调
		bool SetLogicModelIsCreateListener(LogicModelHaveCreateCallback* pLMHCC,int objId=-1,int logicModelId=-1,int typeId=-1);
		//logicModel命令序列执行状态标识回调
		bool setLogicModelCommandListFlagListener(LogicModelCommandListFlagCallback* pLMCLFC,int value1=-1,int value2=-1,int value3=-1);
	protected:
		int				mObjId;
		int				mLogicModelId;
		int				mTypeId;

	public:
		void	addEffect1( const String& effectName,const String& locatorName,
			uint32_t transformType,const Ogre::ColourValue& colour, 
			const String& name, int priority);


		//包装LogicModel的函数
		void									setVisible(bool visible);
		bool									changeAttribute(const String &name, const String &value );
		bool									changeAttribute1(const String &name,const String &value);//内部函数接口
		bool									changeAttribute2(const String &name,const String &value,bool& LoadResFlag);//内部函数接口
		bool									changeAttributes(const std::vector<String> &name, const std::vector<String> &value );
		bool									changeAttributes1(const std::vector<String> &name, const std::vector<String> &value );//内部函数接口
		bool									changeAttributes2(std::vector<String> &name, const std::vector<String> &value,bool& LoadResFlag);//内部函数接口
		
	    bool									getLocatorWorldTransform(const String& name, Ogre::Matrix4& mtx);
		const Ogre::AxisAlignedBox&				getBoundingBox(void);
		const Ogre::AxisAlignedBox*				getWorldBoundingBox();
		void setAdvancedAnimationSystemMonitoringDegree(
			SkeletonMeshComponent::AdvancedAnimationSystemMonitoringDegree monitoringDegreeType = SkeletonMeshComponent::AASMD_NOTHING_DEGREE, 
			Real degree = 0.0f);
		void									setGlobalAnimationRate(Real rate);
		void									setTransparent(Real time, Real transparency);
		Ogre::String							addEffect( const String& effectName, const String& locatorName, 
			uint32_t transformType , const Ogre::ColourValue& colour = Ogre::ColourValue::White, int priority = 3 );
		bool	delEffect(Ogre::String EffectName);
		void	delAllEffect(void);
		void	setHairColour(const Ogre::ColourValue& colour);
		bool	attachModelObj(const String& locatorName, SkeletonMeshActor* model);
		bool	detachModelObj(SkeletonMeshActor* model);
		void	setVisibleFlag(uint32 flags);
		void	setPosition(Ogre::Vector3& pos);
		void	setOrientation(Ogre::Quaternion& orientation);
		void	steSelected(bool selected);
		int		_getTerrainSoundType(void);
		void	setScaleFactor(const Ogre::Vector3& scaleFactor);
		void	setWeaponTypeName(const String& typeName);
		void	delCurrentSkill(void);
		void	setMoodAnimName(const String& name);

		void	forceUpdateBoundingBox();
		void	setAASGlobalAnimRate(Real rate);
		void	setSkillRate(Real val);
		bool	getViewFrustumVisible();
		bool	rayIntersect(const Ogre::Ray& ray);
		bool	isUseExternalBoundingBox(void);
		bool	setForceIgnoreAAS(bool val);


		//dscky add 创建和销毁logicModel需要延迟进行，添加是否创建成功的标志/////////
		bool							mIsLoadingResFlag;				//是否正在加载资源的标志
		unsigned long					mCommandCacheHandle;
		Ogre::OResourcePtrMap			mHaveResMap;
	};

}

#endif // OGSkeletonMeshActor_h__