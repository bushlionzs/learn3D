#include "OgreHeader.h"
#include "OGBulletTester.h"
#include "OgreStringInterface.h"
#include "OgreStringConverter.h"

namespace Orphigine
{
	BulletTester::CmdOutput BulletTester::ms_outputCmd;

	BulletTester::BulletTester()
		: m_outputEventName("")
	{
		m_isLogicOperator = true;
	}

	BulletTester::~BulletTester()
	{

	}

	const String& BulletTester::getOutputEventName() const
	{
		return m_outputEventName;
	}

	void BulletTester::setOutputEventName( const String& val )
	{
		m_outputEventName = val;
	}

	bool BulletTester::initBaseParamters( const String& type )
	{
		if (createParamDictionary(type + "Dict"))
		{
			Ogre::ParamDictionary* tmpDict = getParamDictionary();

			tmpDict->addParameter(
				Ogre::ParameterDef("output",
				"The output event name",
				Ogre::PT_STRING),&ms_outputCmd);

			return true;
		}
		return false;
	}

	Ogre::String BulletTester::CmdOutput::doGet( const void* target ) const
	{
		return static_cast<const BulletTester*>(target)->getOutputEventName();
	}

	void BulletTester::CmdOutput::doSet( void* target, const String& val )
	{
		static_cast<BulletTester*>(target)->setOutputEventName(val);
	}

#if OGRE_STRING_INTERFACE_COPY
	void BulletTester::CmdOutput::doCopy( void* target, const void* source )
	{
		static_cast<BulletTester*>(target)->setOutputEventName(
			static_cast<const BulletTester*>(source)->getOutputEventName());
	}
#endif

}