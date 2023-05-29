#include "OgreHeader.h"
#include "OGAASNode.h"
#include "OGAASPort.h"
#include "OGAASFileFormat.h"


namespace Orphigine
{
	bool AASNode::ms_isSearching = false;
	int AASNode::ms_globalNodesSearchingTag = 0;
	AASNode::CmdNodeName	AASNode::ms_nodeNameCmd;
	AASNode::AASNodeSerializerImplMap AASNode::ms_serializersMap;

	/// stream overhead = ID + size
	//const long STREAM_OVERHEAD_SIZE = sizeof(uint16) + sizeof(uint32);

	AASNode::AASNode(const String& typeName,AdvancedAnimationSystem* system,unsigned short handle)
		: m_type(typeName.c_str()),
		m_name(""),
		m_handle(handle),
		m_owner(system),
		m_blendWeight(0.0f),
		m_maskedBonesWeight(0.0f),
		m_nonmaskedBonesWeight(0.0f),
		m_blendWeightAccumulater(0.0f),
		m_maskedBonesWeightAccumulater(0.0f),
		m_nonmaskedBonesWeightAccumulater(0.0f),
		m_inputNode(NULL),
		m_isActive(false),
		m_justCeaseActive(false),
		m_justBecomeActive(false),
		m_branchBonesWeightCollectionCache(NULL),
		m_searchingTag(0),
		m_nodeTotalWeight(0.0f),
		m_tickTag(0)

	{
		m_portDictionary.clear();
		m_portVec.clear();
		m_parentNodes.clear();
	}

	AASNode::~AASNode()
	{
		std::map<String,AASPort*>::iterator iter;

		for (iter = m_portDictionary.begin();iter != m_portDictionary.end();iter ++)
		{
			assert(NULL != iter->second );

			delete iter->second;
			iter->second = NULL;
		}

		m_portDictionary.clear();

		m_portVec.clear();

		m_parentNodes.clear();
	}

	bool AASNode::initParameter( const String& typeName )
	{
		if (createParamDictionary(typeName))
		{
			Ogre::ParamDictionary* tmpDict = getParamDictionary();

			tmpDict->addParameter(Ogre::ParameterDef("NodeName","The name of node",Ogre::PT_STRING),
				&ms_nodeNameCmd);

			return true;
		}

		return false;
	}

	void AASNode::copyParameters( AASNode* dest )
	{
		dest->m_name = m_name;
	}

	AASPort* AASNode::addPort( const String& name )
	{
		AASPort* tmpPort = getPort(name);

		if (NULL != tmpPort)
		{
			
			return NULL;
		}

		unsigned int portVecSize = (unsigned int)m_portVec.size();

		tmpPort = new AASPort(name,portVecSize);

		tmpPort->setParentNode(this);

		m_portDictionary.insert(std::map<String,AASPort*>::value_type(name,tmpPort));

		m_portVec.push_back(tmpPort);

		_notifyAddPort(tmpPort);

		return tmpPort;
	}

	AASPort* AASNode::getPort( const String& name )
	{
		std::map<String,AASPort*>::iterator iter = m_portDictionary.find(name);
		if (m_portDictionary.end() != iter)
			return iter->second;
		else
			return NULL;
	}

	AASPort* AASNode::getPort( unsigned int index )
	{
		assert(index < (unsigned int)m_portVec.size() && "越界 AASNode::getPort");

		std::vector<AASPort*>::iterator iter = m_portVec.begin() + index;

		return (*iter);
	}

	/*float AASNode::getBlendWeight() const
	{
		return m_blendWeight;
	}*/

	/*void AASNode::setBlendWeight( const float val )
	{
		m_blendWeight = val;
	}*/

	/*Real AASNode::getMaskedBonesWeight() const
	{
		return m_maskedBonesWeight;
	}*/

	/*void AASNode::setMaskedBonesWeight( Real val )
	{
		m_maskedBonesWeight = val;
	}*/

	/*Real AASNode::getNonmaskedBonesWeight() const
	{
		return m_nonmaskedBonesWeight;
	}*/

	/*void AASNode::setNonmaskedBonesWeight( Real val )
	{
		m_nonmaskedBonesWeight = val;
	}*/

	/*Real AASNode::getBlendWeightAccumulater() const
	{
		return m_blendWeightAccumulater;
	}*/

	/*void AASNode::resetBlendWeightAccumulater()
	{
		m_blendWeightAccumulater = 0.0f;
	}*/

	/*void AASNode::increaseBlendWeightAccumulater( Real val )
	{
		m_blendWeightAccumulater += val; 
		if(1.0f < m_blendWeightAccumulater)
			m_blendWeightAccumulater = 1.0f;
	}*/

	/*Real AASNode::getMaskedBonesWeightAccumulater() const
	{
		return m_maskedBonesWeightAccumulater;
	}*/

	/*void AASNode::resetMaskedBonesWeightAccumulater()
	{
		m_maskedBonesWeightAccumulater = 0.0f;
	}*/

	/*void AASNode::increaseMaskedBonesWeightAccumulater( Real val )
	{
		m_maskedBonesWeightAccumulater += val; 
		if(1.0f < m_maskedBonesWeightAccumulater)
			m_maskedBonesWeightAccumulater = 1.0f;
	}*/

	/*Real AASNode::getNonmaskedBonesWeightAccumulater() const
	{
		return m_nonmaskedBonesWeightAccumulater;
	}*/

	/*void AASNode::resetNonmaskedBonesWeightAccumulater()
	{
		m_nonmaskedBonesWeightAccumulater = 0.0f;
	}*/

	/*void AASNode::increaseNonmaskedBonesWeightAccumulater( Real val )
	{
		m_nonmaskedBonesWeightAccumulater += val; 
		if(1.0f < m_nonmaskedBonesWeightAccumulater)
			m_nonmaskedBonesWeightAccumulater = 1.0f;
	}*/

	Real			AASNode::getNodeTotalWeight() const
	{
		return m_nodeTotalWeight;
	}
	
	void			AASNode::setNodeTotalWeight(Real val)
	{
		if (m_handle == 18)
		{
			int kk = 0;
		}
		m_nodeTotalWeight = val;
	}

	unsigned short AASNode::getHandle() const
	{
		return m_handle;
	}

	void AASNode::setHandle( unsigned short val )
	{
		m_handle = val;
	}

	AASNode::PortsIterator AASNode::getPortsIterator()
	{
		return PortsIterator(m_portDictionary.begin(),m_portDictionary.end());
	}

	unsigned int AASNode::getNumPorts() const
	{
		return (unsigned int)m_portDictionary.size();
	}

	const Ogre::String& AASNode::getType() const
	{
		return m_type;
	}

	void AASNode::setType( const String& val )
	{
		m_type = val.c_str();
	}

	AdvancedAnimationSystem* AASNode::getParent() const
	{
		return m_owner;
	}

	AASNode* AASNode::getInputNode() const
	{
		return m_inputNode;
	}

	void AASNode::setInputNode( AASNode* val )
	{
		m_inputNode = val;
	}

	AASNode::PortsVecIterator AASNode::getPortsVecIterator()
	{
		return PortsVecIterator(m_portVec.begin(),m_portVec.end());
	}

	void AASNode::_notifyAddPort(AASPort*	port)
	{
		
	}

	void AASNode::_notifyDisconnectPort( AASPort* port )
	{
		
	}

	void AASNode::_notifyConnectPort( AASPort* port )
	{
		
	}

	void AASNode::_onBecomeActive()
	{
		
	}

	void AASNode::_onCeaseActive()
	{
		
	}

	bool AASNode::getActive() const
	{
		return m_isActive;
	}

	void AASNode::setActive( bool val )
	{
		m_isActive = val;
	}

	/*bool AASNode::getJustBecomeActive()
	{
		return m_justBecomeActive;
	}*/

	/*void AASNode::setJustBecomeActive( bool val )
	{
		m_justBecomeActive = val;
	}*/

	/*bool AASNode::getJustCeaseActive() const
	{
		return m_justCeaseActive;
	}*/

	/*void AASNode::setJustCeaseActive( bool val )
	{
		m_justCeaseActive = val;
	}*/

	void AASNode::playAnim(bool isLooping,Real rate, Real startTime )
	{
		
	}

	void AASNode::initAnim( AASNode* parentNode )
	{
		
	}

	TraverseBranchMaskCollection* AASNode::getBranchBonesWeightCollectionCache()
	{
		return m_branchBonesWeightCollectionCache;
	}

	void AASNode::setBranchBonesWeightCollectionCache( TraverseBranchMaskCollection* branchBonesWeightCollection )
	{
		m_branchBonesWeightCollectionCache = branchBonesWeightCollection;
	}

	AASNode* AASNode::findAASNode( const String& nodeName )
	{
		AASNodeVector nodesInTree;
		getNodesInTree(nodesInTree);

		for (int i = 0;i < (int)nodesInTree.size();i ++)
		{
			AASNode* node = nodesInTree[i];

			if(node->getName() == nodeName.c_str())
				return node;
		}

		return NULL;
	}

	void AASNode::getNodesInTree( AASNodeVector& nodes )
	{
		assert(!ms_isSearching && "另一个搜索正在进行AASNode::getNodesInTree");
		if(ms_isSearching)
			return;

		AASNode::ms_isSearching = true;
		AASNode::ms_globalNodesSearchingTag ++;

		_getNodesInTree(nodes);

		AASNode::ms_isSearching = false;
	}

	void AASNode::_getNodesInTree( AASNodeVector& nodes )
	{
		
		assert(ms_isSearching && "搜索非法调用_getNodesInTree");
		if(!ms_isSearching)
			return;

		if (m_searchingTag != AASNode::ms_globalNodesSearchingTag)
		{
			m_searchingTag = AASNode::ms_globalNodesSearchingTag;

			nodes.push_back(this);
		}
	}

	const Ogre::String& AASNode::getName() const
	{
		return m_name;
	}

	void AASNode::setName(const String& val )
	{
		m_name = val.c_str();
	}

	void AASNode::writeToBinary( AdvancedAnimationSystemSerializerImpl* serializer, AdvancedAnimationSystem* system )
	{
		
	}

	void AASNode::readFromBinary( AdvancedAnimationSystemSerializerImpl* serializer,Ogre::DataStreamPtr& stream, AdvancedAnimationSystem* system )
	{
		AASNodeSerializerImplMap::iterator iter = ms_serializersMap.find(
			serializer->mVersion);

		if (ms_serializersMap.end() == iter)
		{
			OGRE_EXCEPT(Ogre::Exception::ERR_INTERNAL_ERROR, "Cannot find serializer implementation for "
				"current version " + serializer->mVersion, "AASNode::writeToBinary");
		}

		iter->second->readFromBinary(serializer,stream,system,this);
	}

	size_t AASNode::calcSize( AdvancedAnimationSystemSerializerImpl* serializer )
	{
		size_t tmpSize = Ogre::Serializer::STREAM_OVERHEAD_SIZE;

		tmpSize += getType().length() + 1;

		tmpSize += sizeof(unsigned short);

		tmpSize += getName().length() + 1;

		return tmpSize;
	}

	float		AASNode::getBlendWeight() const
	{
		return m_blendWeight;
	}
	void			AASNode::setBlendWeight(const float val)
	{
		if (m_handle == 111 && val > 0.001f)
		{
			int kk = 0;
		}
		m_blendWeight = val;
	}

	void			AASNode::resetBlendWeightAccumulater()
	{
		m_blendWeightAccumulater = 0.0f;
	}

	void			AASNode::increaseBlendWeightAccumulater(Real val)
	{
		m_blendWeightAccumulater += val;
		if (1.0f < m_blendWeightAccumulater)
			m_blendWeightAccumulater = 1.0f;
	}

	void AASNode::_initSerializers()
	{
		assert(ms_serializersMap.empty() && "AASNode::_initSerializers");

		ms_serializersMap.clear();
		ms_serializersMap["[Serializer_v1.10]"] = new AASNodeSerializerImpl_v1_2;
		ms_serializersMap["[AASSerializer_v1.20]"] = new AASNodeSerializerImpl_v1_2;
		ms_serializersMap["[AASSerializer_v1.30]"] = new AASNodeSerializerImpl;
	}

	void AASNode::_deinitSerializers()
	{
		assert(!ms_serializersMap.empty() && "AASNode::_initSerializers");

		AASNodeSerializerImplMap::iterator iter;
		for ( iter = ms_serializersMap.begin();iter != ms_serializersMap.end();iter ++)
		{
			delete iter->second;
			iter->second = NULL;
		}

		ms_serializersMap.clear();
	}

	/*Real AASNode::getNodeTotalWeight() const
	{
		return m_nodeTotalWeight;
	}*/

	/*void AASNode::setNodeTotalWeight( Real val )
	{
		m_nodeTotalWeight = val;
	}*/

	bool AASNode::isAnimSequenceNode()
	{
		return false;
	}

	int Orphigine::AASNode::getTickTag() const
	{
		return m_tickTag;
	}

	void AASNode::setTickTag( int val )
	{
		m_tickTag = val;
	}

	void AASNode::buildTickVec( AASNodeVector& tickVec )
	{

	}

	int AASNode::getNumParentTick()
	{
		int numParentTick = 0;

		AASNodeVector::iterator iter;
		for (iter = m_parentNodes.begin();iter != m_parentNodes.end();iter ++)
		{
			AASNode* parentNode = (*iter);
			
			if(parentNode->getTickTag() == m_owner->getSystemTickTag())
				numParentTick ++;
		}
		return numParentTick;
	}

	AASNode* AASNode::getParentNode( unsigned short index )
	{
		assert(index < (unsigned short)m_parentNodes.size() && "AASNode::getParentNode");

		return m_parentNodes[index];
	}

	void AASNode::addParentNode( AASNode* node )
	{
		AASNodeVector::iterator iter = std::find(m_parentNodes.begin(),m_parentNodes.end(),node);
		if(iter == m_parentNodes.end())
			m_parentNodes.push_back(node);
	}

	void AASNode::removeParentNode( unsigned short index )
	{
		AASNode* node = getParentNode(index);

		AASNodeVector::iterator iter = std::find(m_parentNodes.begin(),m_parentNodes.end(),node);
		if(iter != m_parentNodes.end())
			m_parentNodes.erase(iter);
	}

	void AASNode::removeParentNode( AASNode* node )
	{
		AASNodeVector::iterator iter = std::find(m_parentNodes.begin(),m_parentNodes.end(),node);
		if(iter != m_parentNodes.end())
			m_parentNodes.erase(iter);
	}

	unsigned short AASNode::getNumParentNodes()
	{
		return (unsigned short)m_parentNodes.size();
	}

	Ogre::String AASNode::CmdNodeName::doGet( const void* target ) const
	{
		return static_cast<const AASNode*>(target)->getName().c_str();
	}

	void AASNode::CmdNodeName::doSet( void* target, const String& val )
	{
		static_cast<AASNode*>(target)->setName(val);
	}
}

namespace Orphigine
{
	void AASNodeSerializerImpl::readFromBinary( AdvancedAnimationSystemSerializerImpl* serializer,Ogre::DataStreamPtr& stream, AdvancedAnimationSystem* system,AASNode* node )
	{
		
	}

	void AASNodeSerializerImpl_v1_2::readFromBinary( AdvancedAnimationSystemSerializerImpl* serializer,Ogre::DataStreamPtr& stream, AdvancedAnimationSystem* system,AASNode* node )
	{

	}
}
