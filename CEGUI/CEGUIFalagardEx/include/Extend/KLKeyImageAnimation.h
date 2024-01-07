#pragma once
#include "falmodule.h"
#include "ceguiwindowfactory.h"
#include "falbutton.h"
#include "KLKeyImageAnimationProperties.h"
#include "IKLKeyImageAnimation.h"
namespace CEGUI
{
	class KeyImageAnimation;
	class FALAGARDBASE_API KLKeyImageAnimation :	public FalagardButton,public IKLKeyImageAnimation
	{
	public:
		static const utf8   WidgetTypeName[];       
		virtual void	updateSelf(float elapsed);
		virtual void	drawSelf(float z);
	protected:
		virtual void	onMouseMove(MouseEventArgs& e);
		int				m_nAnimateStart;
		KeyImageAnimation			*m_pAnimate;
		void			drawNormal(float z);

		float			m_fAlpha;
		bool			m_bPlay;
	public:

		virtual void Play( bool bPlay );
		virtual size_t   getFrameNumber();
		virtual String getFrameName(const size_t&);
		static KLKeyImageAnimationProperties::FalKeyImageAnimation    d_AnimateNameProperty;

		void SetAnimate( const String& strAnimate );
		KLKeyImageAnimation(const String& type, const String& name);
		~KLKeyImageAnimation(void);
	};

	class FALAGARDBASE_API KLAnimateFactory : public WindowFactory
    {
    public:
        KLAnimateFactory(void) : WindowFactory(KLKeyImageAnimation::WidgetTypeName) { }
        ~KLAnimateFactory(void){}
        Window* createWindow(const String& name);
        void destroyWindow(Window* window);
    };
}