#ifndef OGAASBlendByPostureNode_h__
#define OGAASBlendByPostureNode_h__

#include "OGAASCrossFadeByTimeListNode.h"

namespace Orphigine
{
	class AdvancedAnimationSystem;

	class AASBlendByPostureNode : public AASCrossFadeByTimeListNode
	{
	public:
		AASBlendByPostureNode(AdvancedAnimationSystem* system,unsigned short handle);
		virtual ~AASBlendByPostureNode();

		virtual void tickAnimation(const float elapsedTime, ReachedAnimSequenceNodeCollection& reachedAnimSequenceNodeCollection);

		AASPort*		getStandPort() const;
		void			setStandPort(AASPort* val);

		AASPort*		getSitPort() const;
		void			setSitPort(AASPort* val);	

	protected:
		AASPort*						m_standPort;
		AASPort*						m_sitPort;

	private:
	};
}
#endif // OGAASBlendByPostureNode_h__
