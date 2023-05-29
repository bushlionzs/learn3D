#include "OgreHeader.h"
#include "OGAASCrossFadeByValNode.h"
#include "OGAdvancedAnimationSystem.h"
#include "OGAASPort.h"

namespace Orphigine
{
	AASCrossFadeByValNode::AASCrossFadeByValNode(const String& typeName,AdvancedAnimationSystem* system,
		unsigned short handle)
		: AASNode(typeName,system,handle)
	{
		m_activePort1 = NULL;
		m_activePort2 = NULL;
	}

	AASCrossFadeByValNode::~AASCrossFadeByValNode()
	{

	}

	void AASCrossFadeByValNode::tickAnimation( const float elapsedTime, ReachedAnimSequenceNodeCollection& reachedAnimSequenceNodeCollection )
{
		Real	tmpPercentage = _refreshTwoNodesCrossFadePercentage();

		
		Real	tmpProduct = m_blendWeight * tmpPercentage;

		Real	tmpActivePort1Weight = m_blendWeight - tmpProduct;
		Real	tmpActivePort2Weight = tmpProduct;

		/*if(NULL != m_activePort1)
		{
			TraverseBranchMaskCollection tmpActivePort1MaskCollection = traverseBranchMaskCollection;
			tmpActivePort1MaskCollection.m_maskedBonesWeight -=tmpActivePort1MaskCollection.m_maskedBonesWeight * tmpPercentage;

			m_activePort1->evaluateAnimation(elapsedTime,tmpActivePort1Weight,reachedAnimSequenceNodeCollection,
			tmpActivePort1MaskCollection);
		}
		if(NULL != m_activePort2)
		{
			TraverseBranchMaskCollection tmpActivePort2MaskCollection = traverseBranchMaskCollection;
			tmpActivePort2MaskCollection.m_maskedBonesWeight *= tmpPercentage;

			m_activePort2->evaluateAnimation(elapsedTime,tmpActivePort2Weight,reachedAnimSequenceNodeCollection,
			tmpActivePort2MaskCollection);
		}*/
	}
}