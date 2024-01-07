
#include "CEGUIKeyImageAnimation_xmlhandler.h"

#include "CEGUIExceptions.h"
#include "CEGUISystem.h"
#include "CEGUILogger.h"
#include "CEGUIXMLAttributes.h"
#include "CEGUIKeyImageAnimation.h"
#include "CEGUIKeyImageAnimationManager.h"
#include "CEGUIPropertyHelper.h"


namespace CEGUI
{
	
	
	const String KeyImageAnimation_xmlHandler::AnimateManagerElement( (utf8*)"AnimateManager" );
	const String KeyImageAnimation_xmlHandler::AnimateElement( (utf8*)"Animate" );
	const String KeyImageAnimation_xmlHandler::AniamteItemElement( (utf8*)"Image" );

	const char	KeyImageAnimation_xmlHandler::AnimateNameAttribute[]			= "Name";
	const char	KeyImageAnimation_xmlHandler::AnimatePlayLoop[]				= "Loop";
	const char  KeyImageAnimation_xmlHandler::AnimateTime[]					= "PlayTime";
	const char  KeyImageAnimation_xmlHandler::AnimateID[]						= "FaceMotionID";
	const char  KeyImageAnimation_xmlHandler::AniamteImage[]					= "ImageName";
	const char  KeyImageAnimation_xmlHandler::AnimateAlphaMode[]				= "AlphaMode";
	const char  KeyImageAnimation_xmlHandler::AnimateAlphaType[]				= "AlphaType";

	
	void KeyImageAnimation_xmlHandler::elementStart(const String& element, const XMLAttributes& attributes)
	{
		
		if(element == AnimateManagerElement)
		{
		}
		else if(element == AnimateElement)
		{
			String	name(attributes.getValueAsString(AnimateNameAttribute));

			bool loop = attributes.getValueAsBool(AnimatePlayLoop);
	
			int id = attributes.getValueAsInteger(AnimateID, -1);

			int totalTime = attributes.getValueAsInteger(AnimateTime, -1);

			bool alpha = attributes.getValueAsBool( AnimateAlphaMode );

			int  loopType = attributes.getValueAsInteger(AnimateAlphaType, 1 );

			d_animate = KeyImageAnimationManager::getSingleton().createAnimate(name, id, loop, totalTime, alpha, loopType );
		}
		else if (element == AniamteItemElement )
		{
			if(d_animate == 0)
			{
				throw GenericException("Aniamte::xmlHandler::startElement - Invalid file struct.");
			}
			const Image* pImage = PropertyHelper::stringToImage(attributes.getValueAsString(AniamteImage));
			if(pImage)
			{
				d_animate->defineAnimateKey(pImage);
				KeyImageAnimationManager::getSingleton().addAnimateImageset(pImage->getImagesetName());
			}
		}
		else
		{
			throw FileIOException("Aniamte::xmlHandler::startElement - Unexpected data was found while parsing the animatefile: '" + element + "' is unknown.");
		}
	}

	void KeyImageAnimation_xmlHandler::elementEnd(const String& element)
	{
		if (element == AnimateElement)
		{
			Logger::getSingleton().logEvent("Finished creation of KeyImageAnimation '" + d_animate->d_name + "' via XML file.", Informative);
		}
		
	}
};