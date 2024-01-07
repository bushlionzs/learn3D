
#ifndef _CEGUIKeyImageAnimation_xmlHandler_h_
#define _CEGUIKeyImageAnimation_xmlHandler_h_

#include "CEGUIXMLHandler.h"
#include "CEGUIKeyImageAnimation.h"
#include "CEGUIString.h"


namespace CEGUI
{
	
	
	class KeyImageAnimation_xmlHandler :	public XMLHandler
	{
	public:
		
		
		KeyImageAnimation_xmlHandler() {};
		
		virtual ~KeyImageAnimation_xmlHandler(){};

		 
		
		virtual void elementStart(const String& element, const XMLAttributes& attributes);
		virtual void elementEnd(const String& element);

		
		KeyImageAnimation*	getAnimate(void) const				{return d_animate;}

	private:
		
		static const String AnimateManagerElement;		
		static const String AnimateElement;				
		static const String AniamteItemElement;			
		static const char	AnimateNameAttribute[];		
		static const char	AnimatePlayLoop[];			
		static const char	AnimateTime[];				
		static const char   AnimateID[];				
		static const char   AniamteImage[];				
		static const char	AnimateAlphaMode[];
		static const char   AnimateAlphaType[];

		
		KeyImageAnimation*   d_animate;			
	};
};

#endif