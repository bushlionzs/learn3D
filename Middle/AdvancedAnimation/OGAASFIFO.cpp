#include "OgreHeader.h"
#include "OGAASFIFO.h"
#include "OGAASPort.h"

namespace Orphigine
{


	AASFIFO::AASFIFO()
	{
		m_topStatePort = NULL;
		m_bottomStatePort = NULL;
		m_isInTransit = false;
	}

	AASFIFO::~AASFIFO()
	{
		
	}

	RefreshStateResult AASFIFO::setActiveChildBackup( AASPort* newStatePort )
	{
		assert(NULL != m_topStatePort || NULL != m_bottomStatePort);
		
		RefreshStateResult tmpResult;

		tmpResult = FSR_NOTHING;

		
		if (NULL != m_bottomStatePort)
		{
			if (newStatePort == m_bottomStatePort)
			{
				tmpResult = FSR_NOTHING;
			}
			else if (newStatePort != m_bottomStatePort)
			{
				
				m_topStatePort = m_bottomStatePort;
				m_bottomStatePort = newStatePort;
				tmpResult = FSR_REPLACE;
				m_isInTransit = true;
			}
		}
		else
		{
			
			if (newStatePort == m_topStatePort)
			{
				tmpResult = FSR_NOTHING;
				
			}
			else
			{
				m_bottomStatePort = newStatePort;
				tmpResult = FSR_PUSHBACK;
				m_isInTransit = true;
			}
		}
		return tmpResult;
	}

	AASPort* AASFIFO::getTopStatePort() const
	{
		return m_topStatePort;
	}

	void AASFIFO::setTopStatePort( AASPort* val )
	{
		m_topStatePort = val;
	}

	AASPort* AASFIFO::getBottomStatePort() const
	{
		return m_bottomStatePort;
	}

	void AASFIFO::setBottomStatePort( AASPort* val )
	{
		m_bottomStatePort = val;
	}

	void AASFIFO::transitionFinished()
	{
		m_topStatePort = m_bottomStatePort;
		m_bottomStatePort = NULL;
		m_isInTransit = false;
	}

	bool AASFIFO::getInTransit() const
	{
		return m_isInTransit;
	}

	void AASFIFO::setInTransit( bool val )
	{
		m_isInTransit = val;
	}
}