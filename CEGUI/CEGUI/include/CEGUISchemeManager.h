

#ifndef _CEGUISchemeManager_h_
#define _CEGUISchemeManager_h_

#include "CEGUIBase.h"
#include "CEGUIString.h"
#include "CEGUISingleton.h"
#include "CEGUIIteratorBase.h"
#include <map>


#if defined(_MSC_VER)
#	pragma warning(push)
#	pragma warning(disable : 4275)
#	pragma warning(disable : 4251)
#endif



namespace CEGUI
{

class CEGUIEXPORT SchemeManager : public Singleton<SchemeManager>
{
public:
	
	SchemeManager(void);


	
	~SchemeManager(void);


	
	static	SchemeManager&	getSingleton(void);


	
	static	SchemeManager*	getSingletonPtr(void);


	
	Scheme*	loadScheme(const String& scheme_filename, const String& resourceGroup = "");


	
	void	unloadScheme(const String& scheme_name);


	
	bool	isSchemePresent(const String& scheme_name) const		{return (d_schemes.find(scheme_name) != d_schemes.end());}


	
	Scheme*	getScheme(const String& name) const;


	
	void	unloadAllSchemes(void);

private:
	
	typedef	std::map<String, Scheme*> SchemeRegistry;
	SchemeRegistry	d_schemes;			


public:
	
	typedef	ConstBaseIterator<SchemeRegistry>	SchemeIterator;

	
	SchemeIterator	getIterator(void) const;
};

} 

#if defined(_MSC_VER)
#	pragma warning(pop)
#endif

#endif	
