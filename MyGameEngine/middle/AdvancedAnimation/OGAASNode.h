#ifndef OGAASNode_h__
#define OGAASNode_h__

#include "OGAdvancedAnimationSystem.h"
#include "OGAdvancedAnimationSystemSerializer.h"

#include "OgreSerializer.h"
#include "OgrePrerequisites.h"
#include "OgreStringInterface.h"

#include <map>

namespace Orphigine
{

	class AASNodeSerializerImpl : public AASSerializerImplBase
	{
	public:
		virtual void	readFromBinary(AdvancedAnimationSystemSerializerImpl* serializer,Ogre::DataStreamPtr& stream,
			AdvancedAnimationSystem* system,AASNode* node);
	};
	class AASNodeSerializerImpl_v1_2 : public AASNodeSerializerImpl
	{
	public:
		virtual void	readFromBinary(AdvancedAnimationSystemSerializerImpl* serializer,Ogre::DataStreamPtr& stream,
			AdvancedAnimationSystem* system,AASNode* node);
	};

	class AASPort;
	class AdvancedAnimationSystem;
	class AdvancedAnimationSystemSerializerImpl;

	class _OrphigineExport AASNode : public Ogre::StringInterface
	{
	public:

		virtual ~AASNode();

		virtual bool	initParameter(const String& typeName);
		
		virtual void	copyParameters(AASNode* dest);

		const Ogre::String&	getType() const;
		void			setType(const String& val);

		class CmdNodeName : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
		};

		const Ogre::String&	getName() const;
		void			setName(const String& val);

		AdvancedAnimationSystem* getParent() const;

		AASPort*		addPort(const String& name);
		AASPort*		getPort(const String& name);
		AASPort*		getPort(unsigned int index);
		unsigned int	getNumPorts() const;

		typedef Ogre::MapIterator<std::map<String,AASPort*> >	PortsIterator;
		PortsIterator	getPortsIterator();

		typedef Ogre::VectorIterator<std::vector<AASPort*> >	PortsVecIterator;
		PortsVecIterator	getPortsVecIterator();

		virtual void	tickAnimation(const float elapsedTime,
						ReachedAnimSequenceNodeCollection& reachedAnimSequenceNodeCollection) = 0;

		virtual void	writeToBinary(AdvancedAnimationSystemSerializerImpl* serializer,
			AdvancedAnimationSystem* system);

		virtual void	readFromBinary(AdvancedAnimationSystemSerializerImpl* serializer,Ogre::DataStreamPtr& stream,
			AdvancedAnimationSystem* system);

		virtual size_t calcSize(AdvancedAnimationSystemSerializerImpl* serializer);

		float		getBlendWeight() const;

		void			setBlendWeight(const float val);


		inline Real			getMaskedBonesWeight() const
		{
			return m_maskedBonesWeight;
		}
		inline void			setMaskedBonesWeight(Real val)
		{
			m_maskedBonesWeight = val;
		}

		inline Real			getNonmaskedBonesWeight() const
		{
			return m_nonmaskedBonesWeight;
		}
		inline void			setNonmaskedBonesWeight(Real val)
		{
			m_nonmaskedBonesWeight = val;
		}

		inline Real			getBlendWeightAccumulater() const
		{
			return m_blendWeightAccumulater;
		}
		void			resetBlendWeightAccumulater();

		void			increaseBlendWeightAccumulater(Real val);

		inline Real			getMaskedBonesWeightAccumulater() const
		{
			return m_maskedBonesWeightAccumulater;
		}
		void			resetMaskedBonesWeightAccumulater()
		{
			m_maskedBonesWeightAccumulater = 0.0f;
		}

		void			increaseMaskedBonesWeightAccumulater(Real val)
		{
			m_maskedBonesWeightAccumulater += val; 
			if(1.0f < m_maskedBonesWeightAccumulater)
				m_maskedBonesWeightAccumulater = 1.0f;
		}

		inline Real			getNonmaskedBonesWeightAccumulater() const
		{
			return m_nonmaskedBonesWeightAccumulater;
		}
		inline void			resetNonmaskedBonesWeightAccumulater()
		{
			m_nonmaskedBonesWeightAccumulater = 0.0f;
		}
		inline void			increaseNonmaskedBonesWeightAccumulater(Real val)
		{
			m_nonmaskedBonesWeightAccumulater += val; 
			if(1.0f < m_nonmaskedBonesWeightAccumulater)
				m_nonmaskedBonesWeightAccumulater = 1.0f;
		}

		inline bool			getJustBecomeActive()
		{
			return m_justBecomeActive;
		}
		inline void			setJustBecomeActive(bool val)
		{
			m_justBecomeActive = val;
		}

		inline bool			getJustCeaseActive() const
		{
			return m_justCeaseActive;
		}
		inline void			setJustCeaseActive(bool val)
		{
			m_justCeaseActive = val;
		}

		Real			getNodeTotalWeight() const;
		void			setNodeTotalWeight(Real val);

		unsigned short	getHandle() const;
		void			setHandle(unsigned short val);

		AASNode*		getInputNode() const;
		void			setInputNode(AASNode* val);

		virtual void	_notifyDisconnectPort(AASPort* port);

		virtual void	_notifyConnectPort(AASPort* port);

		virtual	void	_onBecomeActive();

		virtual void	_onCeaseActive();

		bool			getActive() const;
		void			setActive(bool val);

		virtual void	playAnim(bool isLooping = false,Real rate = 1.0f,Real startTime = 0.0f);

		virtual void	initAnim(AASNode* parentNode);

		TraverseBranchMaskCollection*	getBranchBonesWeightCollectionCache() ;
		void							setBranchBonesWeightCollectionCache(TraverseBranchMaskCollection* branchBonesWeightCollection);

		AASNode*		findAASNode(const String& nodeName);

		void			getNodesInTree(AASNodeVector& nodes);

		virtual void	_getNodesInTree(AASNodeVector& nodes);

		virtual bool	isAnimSequenceNode();

		int				getTickTag() const;
		void			setTickTag(int val);

		virtual void	buildTickVec(AASNodeVector& tickVec);

		int				getNumParentTick();

		AASNode*		getParentNode(unsigned short index);
		void			addParentNode(AASNode* node);
		void			removeParentNode(unsigned short index);
		void			removeParentNode(AASNode* node);
		unsigned short	getNumParentNodes();

		static bool		ms_isSearching;
		static int		ms_globalNodesSearchingTag;
		static CmdNodeName	ms_nodeNameCmd;

		static void		_initSerializers();
		static void     _deinitSerializers();

		typedef		std::map<String,AASNodeSerializerImpl*>	AASNodeSerializerImplMap;
		static AASNodeSerializerImplMap	ms_serializersMap;
	protected:
		AASNode(const String& typeName,AdvancedAnimationSystem* system,unsigned short handle);
		
		virtual	void	_notifyAddPort(AASPort*	port);

	protected:
		Ogre::String				m_type;
		Ogre::String				m_name;
		unsigned short				m_handle;
		AdvancedAnimationSystem*	m_owner;
		float						m_blendWeight;
		Real						m_maskedBonesWeight;
		Real						m_nonmaskedBonesWeight;
		Real						m_blendWeightAccumulater;
		Real						m_maskedBonesWeightAccumulater;
		Real						m_nonmaskedBonesWeightAccumulater;

		TraverseBranchMaskCollection*	m_branchBonesWeightCollectionCache;
		AASNode*					m_inputNode;
		AASNodeVector				m_parentNodes;
		bool						m_isActive;
		bool						m_justBecomeActive;
		bool						m_justCeaseActive;
		std::map<String,AASPort*>	m_portDictionary;
		std::vector<AASPort*>		m_portVec;
		int							m_searchingTag;
		Real						m_nodeTotalWeight;
		int							m_tickTag;	
	private:
	};
}
#endif // OGAASNode_h__