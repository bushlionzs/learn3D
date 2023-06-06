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

	//LogicModelִ���������еĽ׶α�ʶ
	class LogicModelCommandListFlagCallback
	{
	public:
		virtual bool onLogicModelCommandListFlag(int value1=-1,int value2=-1,int value3=-1) = 0;
	};
	//LogicModel�Ƿ񴴽��ɹ��Ļص�
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
			TE_PREMIER			= 0,//����(���ǡ��������������������ǳ���)
			TE_PREMIER_RELATE	= 1,//�������(���ѡ����ˡ�����)
			TE_PLAYER			= 2,//���(��ҡ�����������������ҳ���)
			TE_ACTOR			= 3,//���(NPC��bus������)
			TE_OTHER			= 4,//���������˵�
			TE_FUTURE	= 5
		};

		virtual const String&	getType(void) const;
		virtual const String&	getCategory(void) const;

		virtual void			createRenderInstance();
		virtual void			destroyRenderInstance(void);
		virtual void			setName(const String& name);
		//���л�
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
		Ogre::Vector2	mModelGridPosition;	//ת��LogicModel��λ��Ϊ�������꣬���ڼ�������
		Ogre::Vector3	mModelPosition;		//LogicModel��λ��,����attach֮ǰ������
		Ogre::String	mLogicModelName;
		SkeletonMeshComponent*		mLogicModel;
		//��ݱ�ʶ
		TypeEnum		mSkeletonMeshActorType;
		int				mId;
		ActorProxy* mProxy;
	public:
		LogicModelHaveCreateCallback*  mLogicModelHaveCreateCallback;
		bool		setSkeletonMeshActorTypeandId(TypeEnum type,int id);
		int			getSkeletonMeshActorId()	  { return mId; }
		TypeEnum	getSkeletonMeshActorType() { return mSkeletonMeshActorType;}
		//logicModel�������֪ͨ�ص�
		bool SetLogicModelIsCreateListener(LogicModelHaveCreateCallback* pLMHCC,int objId=-1,int logicModelId=-1,int typeId=-1);
		//logicModel��������ִ��״̬��ʶ�ص�
		bool setLogicModelCommandListFlagListener(LogicModelCommandListFlagCallback* pLMCLFC,int value1=-1,int value2=-1,int value3=-1);
	protected:
		int				mObjId;
		int				mLogicModelId;
		int				mTypeId;

	public:
		void	addEffect1( const String& effectName,const String& locatorName,
			uint32_t transformType,const Ogre::ColourValue& colour, 
			const String& name, int priority);


		//��װLogicModel�ĺ���
		void									setVisible(bool visible);
		bool									changeAttribute(const String &name, const String &value );
		bool									changeAttribute1(const String &name,const String &value);//�ڲ������ӿ�
		bool									changeAttribute2(const String &name,const String &value,bool& LoadResFlag);//�ڲ������ӿ�
		bool									changeAttributes(const std::vector<String> &name, const std::vector<String> &value );
		bool									changeAttributes1(const std::vector<String> &name, const std::vector<String> &value );//�ڲ������ӿ�
		bool									changeAttributes2(std::vector<String> &name, const std::vector<String> &value,bool& LoadResFlag);//�ڲ������ӿ�
		
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


		//dscky add ����������logicModel��Ҫ�ӳٽ��У�����Ƿ񴴽��ɹ��ı�־/////////
		bool							mIsLoadingResFlag;				//�Ƿ����ڼ�����Դ�ı�־
		unsigned long					mCommandCacheHandle;
		Ogre::OResourcePtrMap			mHaveResMap;
	};

}

#endif // OGSkeletonMeshActor_h__