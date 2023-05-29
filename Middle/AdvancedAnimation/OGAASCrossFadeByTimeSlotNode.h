#ifndef OGAASCrossFadeByTimeSlotNode_h__
#define OGAASCrossFadeByTimeSlotNode_h__

#include "OGAASCrossFadeNode.h"

namespace Orphigine
{
	class AASAnimSequenceNode;

	class AASCrossFadeByTimeSlotNode : public AASCrossFadeNode
	{
	public:
		AASCrossFadeByTimeSlotNode(const String& typeName,AdvancedAnimationSystem* system,unsigned short handle);

		virtual ~AASCrossFadeByTimeSlotNode();

		virtual void				initAnim(AASNode* parentNode);

		virtual void				tickAnimation(const float elapsedTime, 
			ReachedAnimSequenceNodeCollection& reachedAnimSequenceNodeCollection);

		virtual void				playUserDefineAnimation(const String& animName,Real blendInTime,
			Real blendOutTime,bool isLooping,Real rate,bool isRestart);

		virtual void				stopUserDefineAnimation(Real blendOutTime);

		AASAnimSequenceNode*		getUserDefineAnimSeqNode();

		int							findBestUserDefineAnimSeqIndex();
	protected:
		virtual void				setActiveChild(AASPort* activePort,Real	blendTime);

	protected:
		unsigned short				m_userDefineChildIndex;		
		Real						m_timeLeft;
		bool						m_isPlayingUserDefineAnim;
		Real						m_pendingBlendOutTime;
	private:
	};
}

#endif // OGAASCrossFadeByTimeSlotNode_h__
