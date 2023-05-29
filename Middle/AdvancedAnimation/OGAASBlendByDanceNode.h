#ifndef OGAASBlendByDanceNode_h__
#define OGAASBlendByDanceNode_h__

#include "OGAASCrossFadeByTimeListNode.h"

namespace Orphigine
{
	class AdvancedAnimationSystem;
	class AASPort;

	class AASBlendByDanceNode : public AASCrossFadeByTimeListNode
	{
	public:
		AASBlendByDanceNode(AdvancedAnimationSystem* system,unsigned short handle);
		virtual ~AASBlendByDanceNode();

	protected:
		AASPort*					m_defaultPort;
		AASPort*					m_dancing1Port;
		AASPort*					m_dancing2Port;
		AASPort*					m_dancing3Port;
		AASPort*					m_dancing4Port;
		AASPort*					m_dancing5Port;
		AASPort*					m_dancing6Port;
		AASPort*					m_dancing7Port;
		AASPort*					m_dancing8Port;
		AASPort*					m_dancing9Port;
		AASPort*					m_dancing10Port;


	private:
	};
}
#endif // OGAASBlendByDanceNode_h__
