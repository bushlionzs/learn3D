#include "OgreHeader.h"
#include "OGAASContinuousNode.h"
#include "OGAASPort.h"

namespace Orphigine
{
	
	AASContinuousNode::AASContinuousNode( const String& typeName,AdvancedAnimationSystem* system ,
		unsigned short handle)
		: AASNode(typeName,system,handle)
	{
		m_port1 = NULL;
		m_port2 = NULL;
	}

	AASContinuousNode::~AASContinuousNode()
	{

	}

	void AASContinuousNode::tickAnimation( const float elapsedTime,
		ReachedAnimSequenceNodeCollection& reachedAnimSequenceNodeCollection,
		TraverseBranchMaskCollection& traverseBranchMaskCollection)
	{
		Real	tmpBlendValue = _refreshContinuousBlendValue();

		
		Real	tmpProduct = m_blendWeight * tmpBlendValue;

		/*Real	tmpActivePort1Weight = m_blendWeight - tmpProduct;
		Real	tmpActivePort2Weight = tmpProduct;*/

		/*if(NULL != m_port1)
		{
			TraverseBranchMaskCollection tmpActivePort1MaskCollection = traverseBranchMaskCollection;
			tmpActivePort1MaskCollection.m_maskedBonesWeight =tmpActivePort1MaskCollection.m_maskedBonesWeight;

			m_port1->evaluateAnimation(elapsedTime,m_blendWeight,reachedAnimSequenceNodeCollection,
				tmpActivePort1MaskCollection);
		}
		if(NULL != m_port2)
		{
			TraverseBranchMaskCollection tmpActivePort2MaskCollection = traverseBranchMaskCollection;
			tmpActivePort2MaskCollection.m_maskedBonesWeight *= tmpBlendValue;

			m_port2->evaluateAnimation(elapsedTime,tmpProduct,reachedAnimSequenceNodeCollection,
				tmpActivePort2MaskCollection);
		}*/

		///*Real	tmpBlendTime = _getBlendTime();

		//if (0.0f < tmpBlendTime)
		//{

		//}*/
		//if(NULL != m_port1)
		//{
		//	TraverseBranchMaskCollection tmpPort1MaskCollection = traverseBranchMaskCollection;
		//	m_port1->evaluateAnimation(elapsedTime,m_blendWeight,reachedAnimSequenceNodeCollection,
		//	tmpPort1MaskCollection);
		//}
		//if(NULL != m_port2)
		//{
		//	TraverseBranchMaskCollection tmpPort2MaskCollection = traverseBranchMaskCollection;
		//	m_port2->evaluateAnimation(elapsedTime,tmpBlendValue * m_blendWeight,
		//	reachedAnimSequenceNodeCollection,tmpPort2MaskCollection);	
		//}
	}

	AASPort* AASContinuousNode::getPort1() const
	{
		return m_port1;
	}

	void AASContinuousNode::setPort1( AASPort* val )
	{
		m_port1 = val;
	}

	AASPort* AASContinuousNode::getPort2() const
	{
		return m_port2;
	}

	void AASContinuousNode::setPort2( AASPort* val )
	{
		m_port2 = val;
	}
}