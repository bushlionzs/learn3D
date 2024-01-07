

#ifndef _CEGUIBase_h_
#define _CEGUIBase_h_

#include <cassert>


#include "CEGUIConfig.h"


#include "CEGUIVersion.h"




#define CEGUIEXPORT






#if defined(_MSC_VER) && (_MSC_VER <= 1200)
#   pragma warning(disable : 4786)
#endif
#include <string>


namespace CEGUI
{


typedef	unsigned long	ulong;
typedef unsigned short	ushort;
typedef unsigned int	uint;
typedef unsigned char	uchar;

typedef unsigned int    uint32;
typedef unsigned short  uint16;
typedef unsigned char   uint8;



static const float		DefaultNativeHorzRes	= 1024.0f;		
static const float		DefaultNativeVertRes	= 768.0f;		



typedef std::ostream OutStream;     
}  



#if defined(CEGUI_ALIGN_ELEMENTS_TO_PIXELS)
#	define PixelAligned(x)	( (float)(int)(( x ) + 0.5f) )
#else
#	define PixelAligned(x)	( x )
#endif



#include "CEGUIForwardRefs.h"

#define ENABLE_EXCEPTION

#ifdef ENABLE_EXCEPTION
	#define UI_TRY			try{
	#define UI_CATCH( str )	} catch( ... ){ Logger::getSingleton().logEvent( str, Errors); throw; }
#else
	#define UI_TRY
	#define UI_CATCH( str )
#endif



#ifdef LANG_CT
	#define UI_LANGUAGES_CODE	950		
#else
	#define UI_LANGUAGES_CODE	936
#endif


#endif	
