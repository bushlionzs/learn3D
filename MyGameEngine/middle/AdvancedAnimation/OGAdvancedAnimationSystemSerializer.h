#ifndef OGAdvancedAnimationSystemSerializer_h__
#define OGAdvancedAnimationSystemSerializer_h__


#include "OgreSerializer.h"
#include "OgreDataStream.h"

namespace Orphigine
{
	class AdvancedAnimationSystem;
	class AASNode;

	/*enum AASSerializerImplType
	{
		AASSI_TYPE_ADVANCEDANIMATIONSYSTEM = 0,
		AASSI_TYPE_AASNODE,
		AASSI_TYPE_AASRANDOMNODE,
		AASSI_TYPE_AAS
	};*/
	class AASSerializerImplBase : public Ogre::Serializer
	{
		friend class AASNode;
		friend class AASNodeSerializerImpl;
		friend class AASNodeSerializerImpl_v1_2;
		friend class AASAnimTreeOutputNode;
		friend class AASBlendByDirectionalNode;
		friend class AASBlendByIdleNode;
		friend class AASBlendByLifeNode;
		friend class AASBlendByPostureNode;
		friend class AASBlendByRandomNode;
		friend class AASBlendByDamageNode;
		friend class AASBlendByWeaponTypeNode;
		friend class AASAnimSequenceNode;
		friend class AASAttackAnimSequenceNode;
		friend class AASWeaponAnimSequenceNode;
		friend class AASBlendByAttackNode;
		friend class AASBlendByRidingNode;
		friend class AASBlendByEquitationNode;
		friend class AASBlendByGuardNode;
		friend class AASBlendByMoodNode;
		friend class AASMoodAnimSequenceNode;
		friend class AASBlendByDanceNode;
		friend class AASBlendByWalkNode;
		friend class AASBlendByRandomNodeSerializerImpl;
		friend class AASBlendByRandomNodeSerializerImpl_v1_1;
		friend class AASBlendByRandomNodeSerializerImpl_v1_2;
		friend class AASCrossFadeNode;
		friend class AASCrossFadeByTimeNode;
		friend class AASCrossFadeByTimeListNode;
		friend class AASCrossFadeByTimeWithMaskNode;
		friend class AASCrossFadeByTimeWithMaskNodeSerializerImpl;
		friend class AASCrossFadeByTimeWithMaskNodeSerializerImpl_v1_2;
		friend class AASAnimSequenceNodeSerializerImpl;
		friend class AASAnimSequenceNodeSerializerImpl_v1_2;
	public:
		AASSerializerImplBase();
		const String&  getType() const;
		void setType(const String& val);

	protected:
		String		m_type;
	};

	class AdvancedAnimationSystemSerializerImpl : public AASSerializerImplBase
	{
	public:
		AdvancedAnimationSystemSerializerImpl();
		virtual ~AdvancedAnimationSystemSerializerImpl();

		//************************************
		// Brief:	  导出AdvancedAnimationSystem所有信息
		// Method:    exportAdvancedAnimationSystem
		// FullName:  Orphigine::AdvancedAnimationSystemSerializer::exportAdvancedAnimationSystem
		// Access:    public 
		// Returns:   void
		// Parameter: AdvancedAnimationSystem * system
		// Parameter: const String & name
		// Parameter: Endian endianMode
		//************************************
		void			exportAdvancedAnimationSystem(AdvancedAnimationSystem* system,const String& name,
			Endian endianMode = ENDIAN_NATIVE);

		//************************************
		// Brief:	  导入AdvancedAnimationSystem所有信息
		// Method:    importAdvancedAnimationSystem
		// FullName:  Orphigine::AdvancedAnimationSystemSerializer::importAdvancedAnimationSystem
		// Access:    public 
		// Returns:   void
		// Parameter: Ogre::DataStreamPtr & stream
		// Parameter: AdvancedAnimationSystem * system
		//************************************
		void			importAdvancedAnimationSystem(Ogre::DataStreamPtr& stream,AdvancedAnimationSystem* system);
	protected:
		virtual void	writeAdvancedAnimationSystem(AdvancedAnimationSystem* system);
		virtual void	writeAASNode(AdvancedAnimationSystem* system,AASNode* node);
		virtual void	writeAASConnection(AdvancedAnimationSystem* system,AASNode* node);

		virtual void	readAdvancedAnimationSystem(Ogre::DataStreamPtr& stream,AdvancedAnimationSystem* system);
		virtual void	readAASNode(Ogre::DataStreamPtr& stream,AdvancedAnimationSystem* system);
		virtual void	readAASConnection(Ogre::DataStreamPtr& stream,AdvancedAnimationSystem* system);

		virtual size_t	calcAASConnection(AdvancedAnimationSystem* system,AASNode* node);

	private:
	};


	class AdvancedAnimationSystemSerializerImpl_v1_2 : public AdvancedAnimationSystemSerializerImpl
	{
	public:
		AdvancedAnimationSystemSerializerImpl_v1_2();

		virtual void	readAASNode(Ogre::DataStreamPtr& stream,AdvancedAnimationSystem* system);

	protected:
	private:
	};

	class AdvancedAnimationSystemSerializerImpl_v1_1 : public AdvancedAnimationSystemSerializerImpl_v1_2
	{
	public:
		AdvancedAnimationSystemSerializerImpl_v1_1();
	};

	
	class _OrphigineExport AdvancedAnimationSystemSerializer : public Ogre::Serializer
	{
	public:

		AdvancedAnimationSystemSerializer();
		virtual ~AdvancedAnimationSystemSerializer();

		static void		_initSerializers();

		static void		_deinitSerializers();
		//************************************
		// Brief:	  导出AdvancedAnimationSystem所有信息
		// Method:    exportAdvancedAnimationSystem
		// FullName:  Orphigine::AdvancedAnimationSystemSerializer::exportAdvancedAnimationSystem
		// Access:    public 
		// Returns:   void
		// Parameter: AdvancedAnimationSystem * system
		// Parameter: const String & name
		// Parameter: Endian endianMode
		//************************************
		void			exportAdvancedAnimationSystem(AdvancedAnimationSystem* system,const String& name,
			Endian endianMode = ENDIAN_NATIVE);

		//************************************
		// Brief:	  导入AdvancedAnimationSystem所有信息
		// Method:    importAdvancedAnimationSystem
		// FullName:  Orphigine::AdvancedAnimationSystemSerializer::importAdvancedAnimationSystem
		// Access:    public 
		// Returns:   void
		// Parameter: Ogre::DataStreamPtr & stream
		// Parameter: AdvancedAnimationSystem * system
		//************************************
		void			importAdvancedAnimationSystem(Ogre::DataStreamPtr& stream,AdvancedAnimationSystem* system);

		typedef	std::map<String,AdvancedAnimationSystemSerializerImpl*>	AASSerializerImplMap;
		static AASSerializerImplMap	ms_serializersMap;

		static	String	ms_currentVersion;

	};


}
#endif // OGAdvancedAnimationSystemSerializer_h__
