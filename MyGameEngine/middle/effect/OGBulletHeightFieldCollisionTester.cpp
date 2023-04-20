#include "OgreHeader.h"
#include "OGBulletHeightFieldCollisionTester.h"
#include "OGBulletSystem.h"
#include "OGBulletEventSystem.h"

#include "OgreStringInterface.h"
#include "OgreStringConverter.h"
#include "OgreSceneManager.h"
#include "OgreRoot.h"
#include "engine_manager.h"

#include <vector>

namespace Orphigine
{

	BulletHeightFieldCollisionTester::CmdLessThan BulletHeightFieldCollisionTester::ms_lessThanCmd;

	BulletHeightFieldCollisionTester::BulletHeightFieldCollisionTester( BulletEventSystem* eventSystem )
	{
		m_type = "heightfieldcollision";
		m_parent = eventSystem;

		m_lessThan = 0.0f;

		if (initBaseParamters("heightfieldcollision"))
		{
			Ogre::ParamDictionary* tmpDict = getParamDictionary();

			tmpDict->addParameter(
				Ogre::ParameterDef("lessthan",
				"The Collision is detected when distance is less than this paramter",
				Ogre::PT_REAL),&ms_lessThanCmd);
		}

		Ogre::SceneManager* tmpManager = NULL;
		tmpManager = Ogre::Root::getSingleton().getSceneManager("OrphigineMainScene");
		if(NULL != tmpManager)
			m_rayQuery = tmpManager->createRayQuery(Ogre::Ray());
	}

	BulletHeightFieldCollisionTester::~BulletHeightFieldCollisionTester()
	{
		if(m_rayQuery)//½â¾öÄÚ´æÐ¹Â© [03/14/2009 dscky]
		{
			delete m_rayQuery;
			m_rayQuery=NULL;			
		}
	}

	void BulletHeightFieldCollisionTester::operateBulletEventSystem(Real timeElapsed)
	{
		std::vector<BulletSystem*>* tmpActiveBulletSystem = m_parent->getActiveBulletSystem();
		std::vector<BulletSystem*>::iterator iter;

		static Ogre::Ray tmpRay;

		for (iter =tmpActiveBulletSystem->begin();iter != tmpActiveBulletSystem->end();iter ++)
		{
			Ogre::Vector3 tmpBulletPos = (*iter)->getPositionWorld();
			tmpBulletPos.y = 10000;

			tmpRay.setOrigin(tmpBulletPos);
			tmpRay.setDirection(Ogre::Vector3::NEGATIVE_UNIT_Y);

			Ogre::Vector3 tmpIntersectsPos = Ogre::Vector3(0.0f,0.0f,0.0f);

			EngineManager::getSingleton().getTerrainIntersects(tmpRay,tmpIntersectsPos);

			tmpBulletPos = (*iter)->getPositionWorld();

			Real tmpDistance = tmpBulletPos.distance(tmpIntersectsPos);
			if (tmpDistance< m_lessThan || tmpBulletPos.y < tmpIntersectsPos.y)
			{
				BulletFlowSystem* tmpFlow = m_parent->getParent();
				m_parent->addTransition(m_outputEventName,(*iter));
			}
		}
		
	}

	const Real& BulletHeightFieldCollisionTester::getLessThan() const
	{
		return m_lessThan;
	}

	void BulletHeightFieldCollisionTester::setLessThan( const Real& val )
	{
		m_lessThan = val;
	}

	String BulletHeightFieldCollisionTester::CmdLessThan::doGet( const void* target ) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const BulletHeightFieldCollisionTester*>(target)->getLessThan());
	}

	void BulletHeightFieldCollisionTester::CmdLessThan::doSet( void* target, const String& val )
	{
		static_cast<BulletHeightFieldCollisionTester*>(target)->setLessThan(
			Ogre::StringConverter::parseReal(val));
	}
}