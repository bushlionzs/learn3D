#include "OgreHeader.h"
#include "OGAASCrossFadeNode.h"
#include "OGAdvancedAnimationSystem.h"
#include "OGAASPort.h"

#include "OgreMath.h"

namespace Orphigine
{

	AASCrossFadeNode::AASCrossFadeNode(const String& typeName,AdvancedAnimationSystem* system,
		unsigned short handle)
		: AASNode(typeName,system,handle)
	{
	}

	AASCrossFadeNode::~AASCrossFadeNode()
	{

	}

	void AASCrossFadeNode::initAnim( AASNode* parentNode )
	{
		AASNode::initAnim(parentNode);

		for (unsigned int i = 0;i < getNumPorts();i ++)
		{
			AASPort* port = getPort(i);
			if(!port)
				continue;

			AASNode* childNode = port->getConnectedNode();
			if(!childNode)
				continue;

			childNode->initAnim(this);
		}
	}

	void AASCrossFadeNode::tickAnimation( const float elapsedTime, ReachedAnimSequenceNodeCollection& reachedAnimSequenceNodeCollection )
	{
		for (unsigned int i = 0;i < getNumPorts();i ++)
		{
			accumulateNodeTotalWeights(i);
		}
	}

	void AASCrossFadeNode::accumulateNodeTotalWeights( unsigned int index )
	{
		AASPort* port = getPort(index);

		AASNode* childNode = port->getConnectedNode();

		if (!childNode)
			return;


		Real childNodeWeight = 0.0f;
		Real childNonmaskedBonesWeight = 0.0f;
		Real childMaskedBonesWeight = 0.0f;
		Real childNodeTotalWeight = 0.0f;

		
		TraverseBranchMaskCollection* bonesWeightCollectionCache = getBranchBonesWeightCollectionCache();
		
		childNonmaskedBonesWeight = m_nonmaskedBonesWeight * port->getBlendWeight();
		childMaskedBonesWeight = m_maskedBonesWeight * port->getBlendWeight();
		childNodeWeight = m_blendWeight * port->getBlendWeight();

		childNode->setBranchBonesWeightCollectionCache(bonesWeightCollectionCache);


		childNode->increaseBlendWeightAccumulater(childNodeWeight);
		childNode->increaseNonmaskedBonesWeightAccumulater(childNonmaskedBonesWeight);
		childNode->increaseMaskedBonesWeightAccumulater(childMaskedBonesWeight);

		childNodeTotalWeight = childNode->getBlendWeightAccumulater();

		childNode->setNodeTotalWeight(childNodeTotalWeight);
	}

	unsigned int AASCrossFadeNode::_generateAveragePortIndexByDegreeAuto( Real degree )
	{
		unsigned int numPorts = getNumPorts();

		if(0 == numPorts )
			return 0;

		if (0.0f > degree || 1.0f < degree)
		{
			assert("度数非法 AASNode::_generateAveragePortIndexByDegreeAuto");

			return 0;
		}

		unsigned int portIndex = degree * numPorts;

		if(0 > portIndex)
			portIndex = 0;
		if(numPorts <= portIndex)
			portIndex = numPorts - 1;

		return portIndex;
	}

	Ogre::Real AASCrossFadeNode::getTotalChildrenWeight()
	{
		Real totalChildrenWeight = 0.0f;

		for (unsigned int i = 0;i < getNumPorts();i ++)
		{
			AASPort* port = getPort(i);

			if(!port)
				continue;

			AASNode* childNode = port->getConnectedNode();
			if(!childNode)
				continue;

			totalChildrenWeight += childNode->getBlendWeight();
		}

		return totalChildrenWeight;
	}

	void AASCrossFadeNode::_getNodesInTree( AASNodeVector& nodes )
	{
		assert(ms_isSearching && "搜索非法调用_getNodesInTree");
		if(!ms_isSearching)
			return;

		if (m_searchingTag != AASNode::ms_globalNodesSearchingTag)
		{
			m_searchingTag = AASNode::ms_globalNodesSearchingTag;
			unsigned short numPorts = getNumPorts();

			for (unsigned short i = 0;i < numPorts;i ++)
			{
				AASPort* port = getPort(i);

				AASNode* childNode = port->getConnectedNode();

				if (childNode)
					childNode->_getNodesInTree(nodes);
			}
			nodes.push_back(this);
		}
	}

	bool AASCrossFadeNode::initParameter( const String& typeName )
	{
		if (AASNode::initParameter(typeName))
		{
			return true;
		}

		return false;
	}

	void AASCrossFadeNode::buildTickVec( AASNodeVector& tickVec )
	{
		for (unsigned int i = 0;i < getNumPorts();i ++)
		{
			AASPort* port = getPort(i);
			assert(port && "AASCrossFadeNode::buildTickVec");
			if(!port)
				continue;

			AASNode* childNode = port->getConnectedNode();
			if(!childNode)
				continue;

			
			if(childNode->getNumParentTick() == childNode->getNumParentNodes() && childNode->getTickTag() != m_owner->getSystemTickTag())
			{
				tickVec.push_back(childNode);
				childNode->setTickTag(m_owner->getSystemTickTag());
				childNode->buildTickVec(tickVec);
			}
		}
	}
}