#ifndef OGAASBlendByEquitationNode_h__
#define OGAASBlendByEquitationNode_h__

#include "OGAASCrossFadeByTimeListNode.h"

namespace Orphigine
{
	class AdvancedAnimationSystem;
	class AASPort;

	class AASBlendByEquitationNode : public AASCrossFadeByTimeListNode
	{
	public:
		AASBlendByEquitationNode(AdvancedAnimationSystem* system,unsigned short handle);
		virtual ~AASBlendByEquitationNode();

		virtual	void	tickAnimation(const float elapsedTime,
			ReachedAnimSequenceNodeCollection& reachedAnimSequenceNodeCollection);

		AASPort*		getDefaultPort() const;
		void			setDefaultPort(AASPort* val);

		AASPort*		getHoofUpPort() const;
		void			setHoofUpPort(AASPort* val);

		AASPort*		getJumpPort() const;
		void			setJumpPort(AASPort* val);
	
	protected:
		AASPort*					m_defaultPort;
		AASPort*					m_hoofUpPort;
		AASPort*					m_jumpPort;

	private:
	};
}
#endif // OGAASBlendByEquitationNode_h__
