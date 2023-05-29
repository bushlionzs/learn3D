#include "OgreHeader.h"
#include "OGBulletSystemEffectElement.h"
#include "OGImpactManager.h"

#include "OgreStringConverter.h"
namespace Orphigine
{

	BulletSystemEffectElement::CmdEffectTemplateName		BulletSystemEffectElement::ms_effectTemplateNameCmd;

	BulletSystemEffectElement::BulletSystemEffectElement()
		: BulletSystemElement("BulletSystemEffectElement")
	{
		m_effectTemplateName = "";
		m_effect = NULL;
		
		if (_initParameters("BulletSystemEffectElement"))
		{
			Ogre::ParamDictionary* tmpDict = getParamDictionary();

			tmpDict->addParameter(Ogre::ParameterDef("EffectTemplateName","The effect template name",Ogre::PT_STRING),
				&ms_effectTemplateNameCmd);
		}
	}

	BulletSystemEffectElement::~BulletSystemEffectElement()
	{
		if (NULL != m_effect)
		{
			ImpactManager::getSingleton().removeEffect(m_effect,false,false);
			m_effect = NULL;
		}	
	}

	String BulletSystemEffectElement::getEffectTemplateName() const
	{
		return m_effectTemplateName;
	}

	void BulletSystemEffectElement::setEffectTemplateName(String val )
	{
		m_effectTemplateName = val;
	}

	Impact* BulletSystemEffectElement::getEffect() const
	{
		return m_effect;
	}

	void BulletSystemEffectElement::setEffect( Impact* val )
	{
		m_effect = val;
	}

	void BulletSystemEffectElement::copyAttributeTo( BulletSystemEffectElement& target ) const
	{
		target.m_effectTemplateName = m_effectTemplateName;
		target.m_offsetPosition = m_offsetPosition;
		target.m_offsetQuaternion = m_offsetQuaternion;
	}

	Ogre::String BulletSystemEffectElement::CmdEffectTemplateName::doGet( const void* target ) const
	{
		return static_cast<const BulletSystemEffectElement*>(target)->
			getEffectTemplateName();
	}

	void BulletSystemEffectElement::CmdEffectTemplateName::doSet( void* target, const String& val )
	{
		static_cast<BulletSystemEffectElement*>(target)->setEffectTemplateName(val);
	}

}