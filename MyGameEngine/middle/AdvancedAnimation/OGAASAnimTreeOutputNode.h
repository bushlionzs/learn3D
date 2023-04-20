/********************************************************************
	created:	2008/04/09
	created:	9:4:2008   15:07
	file base:	OGAASAnimTreeOutputNode
	file ext:	h
	author:		½ªÍþ
	email:		jiang628@hotmail.com
	purpose:	
*********************************************************************/
#ifndef OGAASAnimTreeOutputNode_h__
#define OGAASAnimTreeOutputNode_h__

#include "OGAASNode.h"
#include "OGAASCrossFadeNode.h"

namespace Orphigine
{
	class AdvancedAnimationSystem;
	class AASPort;

	class AASAnimTreeOutputNode : public AASCrossFadeNode
	{
	public:
		AASAnimTreeOutputNode(AdvancedAnimationSystem* system,unsigned short handle);
		virtual ~AASAnimTreeOutputNode();

		AASPort*			getInPort() const;
		void				setInPort(AASPort* val);

		virtual void		initAnim(AASNode* parentNode);

		/*virtual	void		tickAnimation(const float elapsedTime,
			ReachedAnimSequenceNodeCollection& reachedAnimSequenceNodeCollection);*/
	protected:
		AASPort*			m_inPort;

	private:
	};
}
#endif // OGAASAnimTreeOutputNode_h__
