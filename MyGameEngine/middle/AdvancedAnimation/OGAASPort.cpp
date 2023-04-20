#include "OgreHeader.h"
#include "OGAASPort.h"
#include "OGAASNode.h"

namespace Orphigine
{


	AASPort::AASPort(const String& name ,unsigned int handle)
		: m_name(name)
		, m_handle(handle)
		, m_targetWeight(0.0f)
		, m_blendWeight(0.0f)
		, m_maskedBonesWeight(0.0f)
		, m_nonmaskedBonesWeight(0.0f)
		, m_branchBonesWeightCollection(NULL)
	{
		m_parentNode = NULL;
		m_connectedNode = NULL;
	}

	AASPort::~AASPort()
	{

	}

	AASNode* AASPort::getParentNode() const
	{
		return m_parentNode;
	}

	void AASPort::setParentNode(AASNode* val )
	{
		m_parentNode = val;
	}

	AASNode* AASPort::getConnectedNode() const
	{
		return m_connectedNode;
	}

	void AASPort::setConnectedNode( AASNode* val )
	{
		if(NULL == val)
		{
			if(NULL != m_connectedNode)
			{
				m_connectedNode->_notifyDisconnectPort(this);
				m_connectedNode->setInputNode(NULL);
				m_connectedNode->removeParentNode(this->getParentNode());
				m_connectedNode = NULL;
			}
		}
		else
		{
			m_connectedNode = val;
			m_connectedNode->setInputNode(this->getParentNode());
			m_connectedNode->addParentNode(this->getParentNode());
			m_connectedNode->_notifyConnectPort(this);
		}
	}

	String AASPort::getName() const
	{
		return m_name;
	}

	void AASPort::setName( const String& val )
	{
		m_name = val;
	}

	unsigned int AASPort::getHandle() const
	{
		return m_handle;
	}

	void AASPort::setHandle( unsigned int val )
	{
		m_handle = val;
	}

	Real AASPort::getTargetWeight() const
	{
		return m_targetWeight;
	}

	void AASPort::setTargetWeight( Real val )
	{
		m_targetWeight = val;
	}

	/*Ogre::Real AASPort::getBlendWeight() const
	{
		return m_blendWeight;
	}*/

	/*void AASPort::setBlendWeight( Real val )
	{
		m_blendWeight = val;
	}*/

	TraverseBranchMaskCollection* AASPort::getBranchBonesWeightCollection() const
	{
		return m_branchBonesWeightCollection;
	}

	void AASPort::setBranchBonesWeightCollection( TraverseBranchMaskCollection* val )
	{
		m_branchBonesWeightCollection = val;
	}

	TraverseBranchMaskCollection* AASPort::createBranchBonesWeightCollection()
	{
		if(m_branchBonesWeightCollection)
		{
			delete m_branchBonesWeightCollection;
			m_branchBonesWeightCollection = NULL;
		}

		m_branchBonesWeightCollection = new TraverseBranchMaskCollection();

		return m_branchBonesWeightCollection;
	}

	void AASPort::destroyBranchBonesWeightCollection()
	{
		delete m_branchBonesWeightCollection;
		m_branchBonesWeightCollection = NULL;
	}
}
