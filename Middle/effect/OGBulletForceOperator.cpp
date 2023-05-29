#include "OgreHeader.h"
#include "OGBulletForceOperator.h"
#include "OGBulletSystem.h"
#include "OGBulletEventSystem.h"

#include "OgreStringInterface.h"
#include "OgreStringConverter.h"

namespace Orphigine
{
	BulletForceOperator::CmdForceVector BulletForceOperator::ms_forceVectorCmd;

	Orphigine::BulletForceOperator::BulletForceOperator( BulletEventSystem* eventSystem )
	{
		m_type = "force";
		m_parent = eventSystem;
		m_isOperated = false;
		m_forceVector = Ogre::Vector3(0.0f,0.0f,0.0f);

		if (createParamDictionary("ForceOperatorDict"))
		{
			Ogre::ParamDictionary* tmpDict = getParamDictionary();

			tmpDict->addParameter(
				Ogre::ParameterDef("forcevector","The force vector",Ogre::PT_VECTOR3),
				&ms_forceVectorCmd);

		}
	}

	Orphigine::BulletForceOperator::~BulletForceOperator()
	{

	}

	const Ogre::Vector3& Orphigine::BulletForceOperator::getForceVector() const
	{
		return m_forceVector;
	}

	void Orphigine::BulletForceOperator::setForceVector( const Ogre::Vector3& val )
	{
		m_forceVector = val;
	}

	String Orphigine::BulletForceOperator::CmdForceVector::doGet( const void* target ) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const BulletForceOperator*>(target)->getForceVector());
	}
	void Orphigine::BulletForceOperator::CmdForceVector::doSet( void* target, const String& val )
	{
		static_cast<BulletForceOperator*>(target)->setForceVector(
			Ogre::StringConverter::parseVector3(val));
	}

	void BulletForceOperator::operateBulletEventSystem(Real timeElapsed)
	{
		/*if (!m_isOperated)
		{*/
		std::vector<BulletSystem*>* tmpActiveBS = m_parent->getActiveBulletSystem();
		std::vector<BulletSystem*>::iterator iter;

		for (iter = tmpActiveBS->begin();iter != tmpActiveBS->end();iter ++)
		{
			(*iter)->setAccelerationWorld(m_forceVector);
		}
			
			//m_isOperated = true;
		//}
	}
}





