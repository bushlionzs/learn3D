#include "OgreHeader.h"
#include "OGAASSkelControlBase.h"
#include "OGAASPort.h"

namespace Orphigine
{
	AASSkelControlBase::AASSkelControlBase( const String& typeName,AdvancedAnimationSystem* system,unsigned short handle )
		: AASNode(typeName,system,handle)
	{

	}

	AASPort* AASSkelControlBase::getInPort() const
	{
		return m_inPort;
	}

	void AASSkelControlBase::setInPort( AASPort* val )
	{
		m_inPort = val;
	}

	AASPort* AASSkelControlBase::getOutPort() const
	{
		return m_outPort;
	}

	void AASSkelControlBase::setOutPort( AASPort* val )
	{
		m_outPort = val;
	}

	void AASSkelControlBase::tickSkelControl( const float elapsedTime )
	{
		
	}

	void AASSkelControlBase::setActive( bool isActive )
	{
		
	}
}
