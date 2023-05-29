#ifndef OGAASBlendByLifeNode_h__
#define OGAASBlendByLifeNode_h__

#include "OGAASCrossFadeByTimeListNode.h"

namespace Orphigine
{
	class AdvancedAnimationSystem;
	class AASPort;

	class AASBlendByLifeNode : public AASCrossFadeByTimeListNode
	{
	public:
		AASBlendByLifeNode(AdvancedAnimationSystem* system,unsigned short handle);
		virtual ~AASBlendByLifeNode();

		virtual void tickAnimation(const float elapsedTime, ReachedAnimSequenceNodeCollection& reachedAnimSequenceNodeCollection);

		AASPort*			getLivingPort() const;
		void				setLivingPort(AASPort* val);

		AASPort*			getDeathPort() const;
		void				setDeathPort(AASPort* val);

		AASPort*			getCorpsePort() const;
		void				setCorpsePort(AASPort* val);

		AASPort*			getBeatBackPort() const;
		void				setBeatBackPort(AASPort* val);

	protected:
		AASPort*			m_livingPort;
		AASPort*			m_deathPort;
		AASPort*			m_corpsePort;
		AASPort*			m_beatBackPort;

	private:
	};
}
#endif // OGAASBlendByLifeNode_h__
