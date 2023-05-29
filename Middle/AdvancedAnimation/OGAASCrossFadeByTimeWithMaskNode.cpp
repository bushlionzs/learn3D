#include "OgreHeader.h"
#include "OGAASCrossFadeByTimeWithMaskNode.h"
#include "OGAASPort.h"
#include "OGSkeletonMeshComponent.h"

#include "OgreStringConverter.h"
#include "OgreBone.h"
#include "OgreString.h"

namespace Orphigine
{
	AASCrossFadeByTimeWithMaskNode::CmdBranchBoneName AASCrossFadeByTimeWithMaskNode::ms_branchBonesNameCmd;
	AASCrossFadeByTimeWithMaskNode::AASCrossFadeByTimeWithMaskNodeSerializerImplMap AASCrossFadeByTimeWithMaskNode::ms_serializersMap;

	AASCrossFadeByTimeWithMaskNode::AASCrossFadeByTimeWithMaskNode(const String& typeName,AdvancedAnimationSystem* system,
		unsigned short handle)
		: AASCrossFadeByTimeNode(typeName,system,handle)
		, m_sourcePort(NULL)
		, m_targetPort(NULL)
		, m_maskedBonesHandleStr("")
	{
		m_maskedBoneHandles.clear();
	}

	AASCrossFadeByTimeWithMaskNode::~AASCrossFadeByTimeWithMaskNode()
	{
		for (unsigned int i = 0;i < getNumPorts();i ++)
		{
			AASPort* port = getPort(i);

			port->destroyBranchBonesWeightCollection();
		}
	}

	void AASCrossFadeByTimeWithMaskNode::initAnim( AASNode* parentNode )
	{
		AASCrossFadeByTimeNode::initAnim(parentNode);

		unsigned short numBones = getParent()->getNumBones();

		for (unsigned int i = 0;i < getNumPorts();i ++)
		{
			AASPort* port = getPort(i);

			TraverseBranchMaskCollection* portBonesWeightCollection = port->createBranchBonesWeightCollection();
			assert(portBonesWeightCollection && "AASCrossFadeByTimeWithMaskNode::initAnim");

			if (portBonesWeightCollection)
			{
				portBonesWeightCollection->m_traverseBranchMaskVec.reserve(numBones);

				for (unsigned short j = 0;j < numBones;j ++)
				{
					portBonesWeightCollection->m_traverseBranchMaskVec.push_back(false);
				}

				for (unsigned short j = 0;j < getNumBonesHandle();j ++)
				{
					unsigned short maskedBoneHandle = getBonesHandle(j);
					if (maskedBoneHandle < portBonesWeightCollection->m_traverseBranchMaskVec.size())
					{
						portBonesWeightCollection->m_traverseBranchMaskVec[maskedBoneHandle] = true;
					}					
				}
			}
		}

	}

	void AASCrossFadeByTimeWithMaskNode::tickAnimation( const float elapsedTime, ReachedAnimSequenceNodeCollection& reachedAnimSequenceNodeCollection )
	{
		AASCrossFadeByTimeNode::tickAnimation(elapsedTime,reachedAnimSequenceNodeCollection);
	}

	void AASCrossFadeByTimeWithMaskNode::accumulateNodeTotalWeights( unsigned int index )
	{
		AASPort* port = getPort(index);

		AASNode* childNode = port->getConnectedNode();

		if (!childNode)
			return;

		Real childNodeWeight = 0.0f;
		Real childNonmaskedBonesWeight = 0.0f;
		Real childMaskedBonesWeight = 0.0f;
		Real childNodeTotalWeight = 0.0f;

		
		TraverseBranchMaskCollection* portBonesWeightCollection = port->getBranchBonesWeightCollection();
		assert(portBonesWeightCollection && "AASCrossFadeByTimeWithMaskNode::accumulateNodeTotalWeights");
		if(!portBonesWeightCollection)
			return;

		
		if (0 == port->getHandle())
		{
			childNonmaskedBonesWeight = m_blendWeight;
			childNodeWeight = m_blendWeight;
		} 
		
		else
		{
			childNonmaskedBonesWeight = 0.0f;
			childNodeWeight = m_blendWeight * port->getBlendWeight();
		}

		TraverseBranchMaskCollection* bonesWeightCollectionCache = getBranchBonesWeightCollectionCache();
		
		float port_weight = port->getBlendWeight();

		if (port_weight < 0.99f && port_weight > 0.001f)
		{
			int kk = 0;
		}
		if (bonesWeightCollectionCache)
			childMaskedBonesWeight = m_maskedBonesWeight * port_weight;
		else
			childMaskedBonesWeight = m_blendWeight * port_weight;

		_accumulateTraverseMaskCollection(port);

		

		childNode->increaseBlendWeightAccumulater(childNodeWeight);
		childNode->increaseNonmaskedBonesWeightAccumulater(childNonmaskedBonesWeight);
		childNode->increaseMaskedBonesWeightAccumulater(childMaskedBonesWeight);

		childNodeTotalWeight = childNode->getNonmaskedBonesWeightAccumulater() + 
			childNode->getMaskedBonesWeightAccumulater();
		childNode->setNodeTotalWeight(childNodeTotalWeight);
	}

	void AASCrossFadeByTimeWithMaskNode::_accumulateTraverseMaskCollection(AASPort* port)
	{
		AASNode* childNode = port->getConnectedNode();

		if (!childNode)
			return;

		TraverseBranchMaskCollection* portBonesWeightCollection = port->getBranchBonesWeightCollection();
		assert(portBonesWeightCollection && "AASCrossFadeByTimeWithMaskNode::_accumulateTraverseMaskCollection");
		if(!portBonesWeightCollection)
			return;

		int maskedPortActived = _accumulateMaskPortsWeight() > 0.00001f ? 1 : 0;

		if(m_branchBonesWeightCollectionCache)
		{
			portBonesWeightCollection->m_traverseFeatherNodeCount = 
				m_branchBonesWeightCollectionCache->m_traverseFeatherNodeCount + maskedPortActived;
		}
		else
			portBonesWeightCollection->m_traverseFeatherNodeCount = maskedPortActived;

		childNode->setBranchBonesWeightCollectionCache(portBonesWeightCollection);
	}


	Ogre::Real AASCrossFadeByTimeWithMaskNode::_accumulateMaskPortsWeight()
	{
		AASPort* maskPort = getPort(1);
		assert(maskPort && "AASCrossFadeByTimeWithMaskNode::_accumulateMaskPortsWeight");
		if(maskPort)
			return maskPort->getBlendWeight();

		return 0.0f;
	}

	unsigned short AASCrossFadeByTimeWithMaskNode::getNumBonesHandle() const
	{
		return (unsigned short)m_maskedBoneHandles.size();
	}

	unsigned short AASCrossFadeByTimeWithMaskNode::getBonesHandle( unsigned short index ) const
	{
		assert((unsigned short)m_maskedBoneHandles.size() > index && "Ô½½ç AASMask::getBonesHandle");

		return m_maskedBoneHandles[index];
	}

	const Ogre::String& AASCrossFadeByTimeWithMaskNode::getBonesNameVec() const
	{
		return m_maskedBonesHandleStr;
	}

	void AASCrossFadeByTimeWithMaskNode::setBonesNameVec(const Ogre::String& val)
	{
		m_maskedBonesHandleStr = val;

		m_maskedBoneHandles.clear();

		std::vector<String> tmpBonesHandleNameVec = Ogre::StringUtil::split(val.c_str());

		for (int i = 0;i < (int)tmpBonesHandleNameVec.size();i ++)
		{
			String& maskedBoneHandleName = tmpBonesHandleNameVec[i];

			if("" == maskedBoneHandleName)
				continue;

			m_maskedBoneHandles.push_back(Ogre::StringConverter::parseInt(maskedBoneHandleName));
		}
	}

	void AASCrossFadeByTimeWithMaskNode::setBonesNameVec(const Ogre::String& val, const BoneHandles& valList)
	{
		m_maskedBonesHandleStr = val;
		m_maskedBoneHandles = valList;
	}

	void AASCrossFadeByTimeWithMaskNode::setSourcePort(AASPort*	sourcePort )
	{
		m_sourcePort = sourcePort;
	}

	void AASCrossFadeByTimeWithMaskNode::setTargetPort( AASPort* targetPort )
	{
		m_targetPort = targetPort;
	}

	bool AASCrossFadeByTimeWithMaskNode::initParameter( const String& typeName )
	{
		if (AASCrossFadeByTimeNode::initParameter(typeName))
		{
			Ogre::ParamDictionary* tmpDict = getParamDictionary();
	
			tmpDict->addParameter(Ogre::ParameterDef(
				"branchbonename","The branch bone name vector",Ogre::PT_STRING),&ms_branchBonesNameCmd);

			return true;
		}
		return false;
	}

	void AASCrossFadeByTimeWithMaskNode::copyParameters( AASNode* dest )
	{
		AASCrossFadeByTimeNode::copyParameters(dest);

		AASCrossFadeByTimeWithMaskNode* destNode = (AASCrossFadeByTimeWithMaskNode*)dest;
		assert(destNode && "AASCrossFadeByTimeWithMaskNode::copyParameter");

		destNode->setBonesNameVec(m_maskedBonesHandleStr, m_maskedBoneHandles);
	}

	void AASCrossFadeByTimeWithMaskNode::writeToBinary( AdvancedAnimationSystemSerializerImpl* serializer, AdvancedAnimationSystem* system )
	{
	
	}

	void AASCrossFadeByTimeWithMaskNode::readFromBinary( AdvancedAnimationSystemSerializerImpl* serializer,Ogre::DataStreamPtr& stream, AdvancedAnimationSystem* system )
	{
		AASCrossFadeByTimeNode::readFromBinary(serializer,stream,system);

		AASCrossFadeByTimeWithMaskNodeSerializerImplMap::iterator iter = ms_serializersMap.find(
			serializer->mVersion);

		if (ms_serializersMap.end() == iter)
		{
			OGRE_EXCEPT(Ogre::Exception::ERR_INTERNAL_ERROR, "Cannot find serializer implementation for "
				"current version " + AdvancedAnimationSystemSerializer::ms_currentVersion, "AASCrossFadeByTimeWithMaskNode::readFromBinary");
		}

		iter->second->readFromBinary(serializer,stream,system,this);
	}

	size_t AASCrossFadeByTimeWithMaskNode::calcSize(AdvancedAnimationSystemSerializerImpl* serializer)
	{
		size_t tmpSize = AASCrossFadeByTimeNode::calcSize(serializer);

		tmpSize += getBonesNameVec().length() + 1;

		return tmpSize;
	}

	void AASCrossFadeByTimeWithMaskNode::_initSerializers()
	{
		assert(ms_serializersMap.empty() && "AASCrossFadeByTimeWithMaskNode::_initSerializers");

		ms_serializersMap.clear();
		ms_serializersMap["[Serializer_v1.10]"] = new AASCrossFadeByTimeWithMaskNodeSerializerImpl_v1_2;
		ms_serializersMap["[AASSerializer_v1.20]"] = new AASCrossFadeByTimeWithMaskNodeSerializerImpl_v1_2;
		ms_serializersMap["[AASSerializer_v1.30]"] = new AASCrossFadeByTimeWithMaskNodeSerializerImpl;
	}

	void AASCrossFadeByTimeWithMaskNode::_deinitSerializers()
	{
		assert(!ms_serializersMap.empty() && "AASCrossFadeByTimeWithMaskNode::_deinitSerializers");

		AASCrossFadeByTimeWithMaskNodeSerializerImplMap::iterator iter;
		for (iter = ms_serializersMap.begin();iter != ms_serializersMap.end();iter ++)
		{
			delete iter->second;
			iter->second = NULL;
		}

		ms_serializersMap.clear();
	}

	Ogre::String AASCrossFadeByTimeWithMaskNode::CmdBranchBoneName::doGet( const void* target ) const
	{
		return static_cast<const AASCrossFadeByTimeWithMaskNode*>(target)->getBonesNameVec().c_str();
	}

	void AASCrossFadeByTimeWithMaskNode::CmdBranchBoneName::doSet( void* target, const String& val )
	{
		static_cast<AASCrossFadeByTimeWithMaskNode*>(target)->setBonesNameVec(val.c_str());
	}
}

namespace Orphigine
{
	void AASCrossFadeByTimeWithMaskNodeSerializerImpl::readFromBinary( AdvancedAnimationSystemSerializerImpl* serializer,Ogre::DataStreamPtr& stream, AdvancedAnimationSystem* system,AASCrossFadeByTimeWithMaskNode* node )
	{
		String maskedBonesHandleStr;
		maskedBonesHandleStr = serializer->readString(stream);

		node->setBonesNameVec(maskedBonesHandleStr.c_str());
	}

	void AASCrossFadeByTimeWithMaskNodeSerializerImpl_v1_2::readFromBinary( AdvancedAnimationSystemSerializerImpl* serializer,Ogre::DataStreamPtr& stream, AdvancedAnimationSystem* system,AASCrossFadeByTimeWithMaskNode* node )
	{
		String bonesNameVec = serializer->readString(stream);

		SkeletonMeshComponent* tmpModel = node->getParent()->getParent();
		if(NULL == tmpModel)
			return;

		String maskedBonesHandleStr;
		std::vector<String> tmpBonesNameVec = Ogre::StringUtil::split(bonesNameVec);

		for (int i = 0;i < (int)tmpBonesNameVec.size();i ++)
		{
			String tmpBoneName = tmpBonesNameVec[i];

			if("" == tmpBoneName)
				continue;

			Ogre::Bone*	tmpBone = tmpModel->getBone(tmpBoneName);

			unsigned short boneHandle = tmpBone->getBoneId();
			maskedBonesHandleStr += Ogre::StringConverter::toString(boneHandle);
			maskedBonesHandleStr += " ";
		}
		node->setBonesNameVec(bonesNameVec.c_str());
	}
}