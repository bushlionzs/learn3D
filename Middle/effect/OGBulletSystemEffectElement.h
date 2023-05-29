#ifndef OGBulletSystemEffectElement_h__
#define OGBulletSystemEffectElement_h__

#include "OGBulletSystemElement.h"
#include "OgreQuaternion.h"

namespace Orphigine
{
	class Impact;

	class BulletSystemEffectElement : public BulletSystemElement
	{
	public:
		BulletSystemEffectElement();
		virtual ~BulletSystemEffectElement();

		class CmdEffectTemplateName : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
		};

		String				getEffectTemplateName() const;
		void						setEffectTemplateName(String val);

		Impact*						getEffect() const;
		void						setEffect(Impact* val);

		void						copyAttributeTo(BulletSystemEffectElement& target) const;

		static CmdEffectTemplateName		ms_effectTemplateNameCmd;
		
	protected:
		String								m_effectTemplateName;
	
		Impact*								m_effect;
		
	private:
	};
}
#endif // OGBulletSystemEffectElement_h__