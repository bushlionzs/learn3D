#include "OgreHeader.h"
#include "OGBulletDeleterOperator.h"
#include "OGBulletEventSystem.h"
#include "OGBulletFlowSystem.h"
#include "OGBulletSystem.h"

namespace Orphigine
{


	BulletDeleterOperator::BulletDeleterOperator(BulletEventSystem* eventSystem)
	{
		m_type = "deleter";
		m_parent = eventSystem;
		m_isOperated=false;
	}

	BulletDeleterOperator::~BulletDeleterOperator()
	{

	}

	void BulletDeleterOperator::operateBulletEventSystem(Real timeElapsed)
	{
		BulletFlowSystem* tmpFlowSystem = m_parent->getParent();

		std::vector<BulletSystem*>* tmpActiveArray = m_parent->getActiveBulletSystem();
		std::vector<BulletSystem*>::iterator iter;
		///fsÐÞ¸Ä
		iter=tmpActiveArray->begin();
		while(iter!=tmpActiveArray->end()){
			tmpFlowSystem->removeBulletSystem((*iter));
			m_parent->removeActiveBulletSystem((*iter));
			iter=tmpActiveArray->begin();
		}
	}
}
