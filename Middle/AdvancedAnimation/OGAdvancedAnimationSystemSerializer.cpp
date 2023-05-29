#include "OgreHeader.h"
#include "OGAdvancedAnimationSystemSerializer.h"
#include "OGAASFileFormat.h"
#include "OGAASNode.h"
#include "OGAASPort.h"
#include "OGAASBlendByRandomNode.h"

#include "platform_log.h"

namespace Orphigine
{
	/// stream overhead = ID + size
	//const long STREAM_OVERHEAD_SIZE = sizeof(uint16) + sizeof(uint32);

	AASSerializerImplBase::AASSerializerImplBase()
	{
		
	}

	const String& AASSerializerImplBase::getType() const
	{
		return m_type;
	}

	void AASSerializerImplBase::setType( const String& val )
	{
		m_type = val;
	}
	
	AdvancedAnimationSystemSerializerImpl::AdvancedAnimationSystemSerializerImpl()
	{
		 mVersion = "[AASSerializer_v1.30]";
	}

	AdvancedAnimationSystemSerializerImpl::~AdvancedAnimationSystemSerializerImpl()
	{
		
	}

	void AdvancedAnimationSystemSerializerImpl::exportAdvancedAnimationSystem( AdvancedAnimationSystem* system,const String& name, Endian endianMode /*= ENDIAN_NATIVE*/ )
	{
		
	}

	void AdvancedAnimationSystemSerializerImpl::importAdvancedAnimationSystem( Ogre::DataStreamPtr& stream,AdvancedAnimationSystem* system )
	{
		determineEndianness(stream);

		readFileHeader(stream);

		
		readAdvancedAnimationSystem(stream,system);

	}

	void AdvancedAnimationSystemSerializerImpl::writeAdvancedAnimationSystem( AdvancedAnimationSystem* system )
	{
		AASNodeVector nodesInTree;
		AASNode* animTreeOutNode = system->getAnimTreeOutputNode();

		animTreeOutNode->getNodesInTree(nodesInTree);
		int tmpNumNodes = (int)nodesInTree.size();

		for (int i = 0;i < tmpNumNodes;i ++)
		{
			AASNode* tmpNode = nodesInTree[i];
			if(NULL == tmpNode)
				continue;

			writeAASNode(system,tmpNode);
			
		}

		for (int i = 0;i < tmpNumNodes;i ++)
		{
			AASNode* tmpNode = nodesInTree[i];
			if(NULL == tmpNode)
				continue;

			writeAASConnection(system,tmpNode);
		}
	}

	void AdvancedAnimationSystemSerializerImpl::writeAASNode( AdvancedAnimationSystem* system,AASNode* node )
	{
		node->writeToBinary(this,system);
	}

	void AdvancedAnimationSystemSerializerImpl::writeAASConnection( AdvancedAnimationSystem* system,AASNode* node )
	{
		
	}

	void AdvancedAnimationSystemSerializerImpl::readAdvancedAnimationSystem( Ogre::DataStreamPtr& stream ,
		AdvancedAnimationSystem* system)
	{
		unsigned short streamID;
		while(!stream->eof())
		{
			streamID = readChunk(stream);
			switch (streamID)
			{
			case AAS_NODE:
				readAASNode(stream, system);
				break;
			case AAS_CONNECTION:
				readAASConnection(stream,system);
				break;
			}
		}
	}

	void AdvancedAnimationSystemSerializerImpl::readAASNode( Ogre::DataStreamPtr& stream,
		AdvancedAnimationSystem* system)
	{

		String tmpNodeType = readString(stream);

		unsigned short tmpHandle;
		readShorts(stream,&tmpHandle,1);

		AASNode* tmpNode = system->addNode(tmpNodeType,tmpHandle);

		String nodeName = readString(stream);
		tmpNode->setName(nodeName);

		tmpNode->readFromBinary(this,stream,system);
	}

	void AdvancedAnimationSystemSerializerImpl::readAASConnection( Ogre::DataStreamPtr& stream,AdvancedAnimationSystem* system )
	{
		unsigned short tmpInputHandle;
		readShorts(stream,&tmpInputHandle,1);

		String tmpPortName;
		tmpPortName = readString(stream);

		unsigned short tmpOutputHandle;
		readShorts(stream,&tmpOutputHandle,1);

		AASNode* tmpNode = system->getNode(tmpInputHandle);

		AASPort* tmpPort = tmpNode->getPort(tmpPortName);

		if(NULL == tmpPort)
			tmpPort = tmpNode->addPort(tmpPortName);

		AASNode* tmpOutputNode = system->getNode(tmpOutputHandle);
		tmpPort->setConnectedNode(tmpOutputNode);
	}

	size_t AdvancedAnimationSystemSerializerImpl::calcAASConnection(AdvancedAnimationSystem* system,AASNode* node)
	{
		size_t tmpSize = STREAM_OVERHEAD_SIZE;

		AASNode::PortsIterator tmpIter = node->getPortsIterator();
		while (tmpIter.hasMoreElements())
		{
			AASPort* tmpPort = tmpIter.getNext();

			if(NULL == tmpPort->getConnectedNode())
				continue;

			tmpSize += sizeof(unsigned short);

			tmpSize += tmpPort->getName().length() + 1;

			tmpSize += sizeof(unsigned short);

		}
		
		return tmpSize;
	}

	AdvancedAnimationSystemSerializerImpl_v1_2::AdvancedAnimationSystemSerializerImpl_v1_2()
	{
		mVersion = "[AASSerializer_v1.20]";
	}

	void AdvancedAnimationSystemSerializerImpl_v1_2::readAASNode( Ogre::DataStreamPtr& stream,AdvancedAnimationSystem* system )
	{
		String tmpNodeType = readString(stream);
		unsigned short tmpHandle;
		readShorts(stream,&tmpHandle,1);

		AASNode* tmpNode = system->addNode(tmpNodeType,tmpHandle);

		tmpNode->readFromBinary(this,stream,system);
	}

	AdvancedAnimationSystemSerializerImpl_v1_1::AdvancedAnimationSystemSerializerImpl_v1_1()
	{
		mVersion = "[Serializer_v1.10]";
	}

	String	AdvancedAnimationSystemSerializer::ms_currentVersion = "[AASSerializer_v1.30]";

	AdvancedAnimationSystemSerializer::AASSerializerImplMap AdvancedAnimationSystemSerializer::ms_serializersMap;

	AdvancedAnimationSystemSerializer::AdvancedAnimationSystemSerializer()
	{

	}

	AdvancedAnimationSystemSerializer::~AdvancedAnimationSystemSerializer()
	{
	}

	void AdvancedAnimationSystemSerializer::exportAdvancedAnimationSystem( AdvancedAnimationSystem* system,const String& name, 
		Endian endianMode /*= ENDIAN_NATIVE*/ )
	{
		AASSerializerImplMap::iterator iter = ms_serializersMap.find(
			ms_currentVersion);

		if (ms_serializersMap.end() != iter)
		{
			iter->second->exportAdvancedAnimationSystem(system,name,endianMode);
		}
		else
		{
			OGRE_EXCEPT(Ogre::Exception::ERR_INTERNAL_ERROR, "Cannot find serializer implementation for "
				"current version " + ms_currentVersion, "AdvancedAnimationSystemSerializer::exportAdvancedAnimationSystem");
		}
	}

	void AdvancedAnimationSystemSerializer::importAdvancedAnimationSystem( Ogre::DataStreamPtr& stream,AdvancedAnimationSystem* system )
	{
		determineEndianness(stream);

		unsigned short headerId;
		readShorts(stream,&headerId,1);

		if (headerId != AAS_FILEHEADER)
		{
			OGRE_EXCEPT(Ogre::Exception::ERR_INTERNAL_ERROR, "File header not found",
				"AdvancedAnimationSystemSerializer::importAdvancedAnimationSystem");
		}

		String version = readString(stream);

		stream->seek(0);

		AASSerializerImplMap::iterator iter = ms_serializersMap.find(
			version);

		if (ms_serializersMap.end() == iter)
		{
			OGRE_EXCEPT(Ogre::Exception::ERR_INTERNAL_ERROR, "Cannot find serializer implementation for "
				"current version " + ms_currentVersion, "AdvancedAnimationSystemSerializer::importAdvancedAnimationSystem");
		}

		iter->second->importAdvancedAnimationSystem(stream,system);
	}

	void AdvancedAnimationSystemSerializer::_initSerializers()
	{
		ms_serializersMap.clear();
		ms_serializersMap["[Serializer_v1.10]"] = new AdvancedAnimationSystemSerializerImpl_v1_1();
		ms_serializersMap["[AASSerializer_v1.20]"] = new AdvancedAnimationSystemSerializerImpl_v1_2();
		ms_serializersMap["[AASSerializer_v1.30]"] = new AdvancedAnimationSystemSerializerImpl();
	}

	void AdvancedAnimationSystemSerializer::_deinitSerializers()
	{
		AdvancedAnimationSystemSerializer::AASSerializerImplMap::iterator iter;
		for (iter = ms_serializersMap.begin();iter != 
			ms_serializersMap.end();iter ++)
		{
			delete iter->second;
			iter->second = NULL;
		}
		ms_serializersMap.clear();
	}
}