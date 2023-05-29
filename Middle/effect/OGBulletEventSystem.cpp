#include "OgreHeader.h"
#include "OGBulletEventSystem.h"
#include "OGBulletFlowSystemManager.h"
#include "OGBulletFlowSystem.h"
#include "OGBulletOperator.h"
#include "OGBulletOperatorFactory.h"
#include "OGBulletSystem.h"


namespace Orphigine
{


	BulletEventSystem::BulletEventSystem(const String& templateName,BulletFlowSystem* parent)
	{
		m_templateName = templateName;
		m_parent = parent;
		m_activeBulletSystem.clear();
		m_operators.clear();
		m_transitionCache.clear();
		m_newTransferredBulletSystem.clear();
	}

	BulletEventSystem::~BulletEventSystem()
	{
		std::map<String,BulletSystemCollection*>::iterator iter;
		for (iter = m_transitionCache.begin();iter != m_transitionCache.end();iter ++)
		{
			delete iter->second;
			iter->second = NULL;
		}
		m_transitionCache.clear();
		
		m_activeBulletSystem.clear();

		m_newTransferredBulletSystem.clear();

		removeAllBulletOperators();

		m_operators.clear();
	}

	void BulletEventSystem::addActiveBulletSystem( BulletSystem* bulletSystem )
	{
		m_activeBulletSystem.push_back(bulletSystem);
	}

	void BulletEventSystem::removeActiveBulletSystem( BulletSystem* bulletSystem )
	{
		std::vector<BulletSystem*>::iterator iter = 
			std::find(m_activeBulletSystem.begin(),m_activeBulletSystem.end(),bulletSystem);
		if(m_activeBulletSystem.end() != iter)
			m_activeBulletSystem.erase(iter);
	}

	BulletOperator* BulletEventSystem::addBulletOperator( const String& typeName ,BulletOperatorAddMode addMode,
		unsigned int insertIndex)
	{
		BulletOperator* tmpBulletOperator = BulletFlowSystemManager::getSingleton().
			createBulletOperator(typeName,this);

		if (BOAM_APPEND == addMode)
		{
			m_operators.push_back(tmpBulletOperator);
		} 
		else
		{
			std::vector<BulletOperator*>::iterator iter = m_operators.begin() + insertIndex;
			m_operators.insert(iter,tmpBulletOperator);
		}

		return tmpBulletOperator;
	}

	void BulletEventSystem::addTransition( const String& eventName,BulletSystem* bulletSystem )
	{
		if(eventName.empty())
			return;

		std::map<String,BulletSystemCollection*>::iterator iter= m_transitionCache.find(eventName);
		if (m_transitionCache.end() == iter)
		{	
			BulletSystemCollection* tmpCollection = new BulletSystemCollection;
			tmpCollection->m_bulletSystemCollectition.push_back(bulletSystem);
			m_transitionCache.insert(std::map<String,BulletSystemCollection*>::
				value_type(eventName,tmpCollection));
		} 
		else
		{
			BulletSystemCollection* tmpCollection = iter->second;

			tmpCollection->m_bulletSystemCollectition.push_back(bulletSystem);
		}
	
	}

	void BulletEventSystem::update( Real time )
	{
		std::vector<BulletOperator*>::iterator operatorIter;
		for (operatorIter = m_operators.begin();operatorIter != m_operators.end();operatorIter ++)
		{
			(*operatorIter)->operateBulletEventSystem(time);
		}

		m_newTransferredBulletSystem.clear();

		/*
		 *	下面做BulletSystem的迁移，从当前BulletEventSystem迁移到目标BuleltEventSystem
		 *	最后清空m_transitionCache;
		 */
		std::map<String,BulletSystemCollection*>::iterator iter;
		for (iter = m_transitionCache.begin();iter != m_transitionCache.end();iter ++)
		{
			String tmpEventName = iter->first;
			BulletSystemCollection* tmpCollection = iter->second;

			BulletEventSystem* tmpEventSystem = m_parent->getBulletEventSystem(tmpEventName);

			std::vector<BulletSystem*>::iterator vecIter;
			for (vecIter = tmpCollection->m_bulletSystemCollectition.begin();
				vecIter != tmpCollection->m_bulletSystemCollectition.end(); vecIter ++)
			{
				tmpEventSystem->addActiveBulletSystem(*vecIter);
				tmpEventSystem->addNewTransferredBulletSystem(*vecIter);
				(*vecIter)->setEventAge(0.0f);

				this->removeActiveBulletSystem(*vecIter);
			}

			tmpCollection->m_bulletSystemCollectition.clear();
		}
	}

	BulletFlowSystem* BulletEventSystem::getParent()
	{
		return m_parent;
	}

	std::vector<BulletSystem*>* BulletEventSystem::getActiveBulletSystem()
	{
		return &m_activeBulletSystem;
	}

	BulletEventSystem& BulletEventSystem::operator=( const BulletEventSystem& rhs )
	{
		removeAllBulletOperators();

		for (int i = 0;i < rhs.getNumBulletOperator();i ++)
		{
			BulletOperator* tmpRHSOperator = rhs.getBulletOperator(i);
			BulletOperator* tmpNewOperator = addBulletOperator(tmpRHSOperator->getType());

			tmpRHSOperator->copyParametersTo(tmpNewOperator);
		}
		return *this;
	}

	int BulletEventSystem::getNumBulletOperator() const
	{
		return (int)m_operators.size();
	}

	BulletOperator* BulletEventSystem::getBulletOperator( int index ) const
	{
		return m_operators[index];
	}

	const String& BulletEventSystem::getTemplateName() const
	{
		return m_templateName;
	}

	void BulletEventSystem::addNewTransferredBulletSystem( BulletSystem* bulletSystem )
	{
		m_newTransferredBulletSystem.push_back(bulletSystem);
	}

	std::vector<BulletSystem*>* BulletEventSystem::getNewTransferredBulletSystem()
	{
		return &m_newTransferredBulletSystem;
	}

	void BulletEventSystem::removeBulletOperator( unsigned int index )
	{
		assert(index < m_operators.size());

		std::vector<BulletOperator*>::iterator iter = m_operators.begin() + index;

		BulletFlowSystemManager::getSingleton().destroyBulletOperator((*iter));

		m_operators.erase(iter);
	}

	void BulletEventSystem::removeAllBulletOperators()
	{
		std::vector<BulletOperator*>::iterator iter;
		for (iter = m_operators.begin();iter != m_operators.end();iter ++)
		{
			BulletFlowSystemManager::getSingleton().destroyBulletOperator((*iter));
		}

		m_operators.clear();
	}
	void BulletOperatorFactory::destroyOperator(BulletOperator* bulletOperator)
	{
		std::vector<BulletOperator*>::iterator iter = std::find(m_operators.begin(),m_operators.end(),bulletOperator);

		OGRE_DELETE (*iter);
		(*iter) = NULL;

		m_operators.erase(iter);
	}
}