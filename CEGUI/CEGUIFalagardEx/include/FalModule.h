

#ifndef _FalModule_h_
#define _FalModule_h_




#define FALAGARDBASE_API


#include "CEGUIString.h"



class CEGUI::WindowFactory;


extern "C" FALAGARDBASE_API void registerFactory(const CEGUI::String& type_name);
extern "C" FALAGARDBASE_API CEGUI::uint registerAllFactories(void);

extern "C" FALAGARDBASE_API void registerFalagardFactory(const CEGUI::String& type_name);
extern "C" FALAGARDBASE_API CEGUI::uint registerAllFalagardFactories(void);

void doSafeFactoryRegistration(CEGUI::WindowFactory* factory);
#endif  
