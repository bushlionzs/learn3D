




#ifndef _CEGUIConfig_h_
#define _CEGUIConfig_h_


#include <OgreHeader.h>









#define CEGUI_LOAD_MODULE_APPEND_SUFFIX_FOR_DEBUG 1






#define CEGUI_LOAD_MODULE_DEBUG_SUFFIX	""







#define CEGUI_ALIGN_ELEMENTS_TO_PIXELS 1







#if defined(_MSC_VER) || defined(__APPLE__)












#define CEGUI_SAMPLES_USE_OGRE


#endif 





#if defined(_MSC_VER)






#define CEGUI_SAMPLES_USE_DIRECTX_9





#define _STLP_NEW_PLATFORM_SDK

#endif 

#endif	
