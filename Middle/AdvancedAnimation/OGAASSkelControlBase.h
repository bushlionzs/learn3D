#ifndef OGAASSkelControlBase_h__
#define OGAASSkelControlBase_h__

#include "OGAASNode.h"

namespace Orphigine
{
	class AdvancedAnimationSystem;
	class AASPort;

	class AASSkelControlBase : public AASNode
	{
	public:
		AASSkelControlBase(const String& typeName,AdvancedAnimationSystem* system,unsigned short handle);

		AASPort*			getInPort() const;
		void				setInPort(AASPort* val);

		AASPort*			getOutPort() const;
		void				setOutPort(AASPort* val);
	
		virtual	void		tickSkelControl(const float elapsedTime);

		void				setActive(bool isActive);
	protected:
		AASPort*			m_inPort;
		AASPort*			m_outPort;
		Real				m_blendInTime;
		Real				m_blendOutTime;
		Real				m_timeLeft;

	private:
	};
}
#endif // OGAASSkelControlBase_h__
