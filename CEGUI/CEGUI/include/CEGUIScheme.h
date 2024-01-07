

#ifndef _CEGUIScheme_h_
#define _CEGUIScheme_h_

#include "CEGUIBase.h"
#include "CEGUIString.h"
#include "CEGUISchemeManager.h"

#include <vector>


#if defined(_MSC_VER)
#	pragma warning(push)
#	pragma warning(disable : 4251)
#endif



namespace CEGUI
{


enum FontType;


class CEGUIEXPORT Scheme
{
	friend class Scheme_xmlHandler;
public:
	
	void	loadResources(void);


	
	void	unloadResources(void);


	
	bool	resourcesLoaded(void) const;


	
	const String& getName(void) const		{return d_name;}

private:
	
	static const char	GUISchemeSchemaName[];			

	
	friend	Scheme* SchemeManager::loadScheme(const String& scheme_filename, const String& resourceGroup);
	friend	void	SchemeManager::unloadScheme(const String& scheme_name);


	
	
	Scheme(const String& filename, const String& resourceGroup);


public:		
	
	~Scheme(void);

	
private:
	
	struct LoadableUIElement
	{
		String	name;
		String	filename;
        String  resourceGroup;
	};

	struct	UIElementFactory
	{
		String name;
	};

	struct	UIModule
	{
		String name;
		FactoryModule*	module;
		std::vector<UIElementFactory>	factories;
	};

	struct AliasMapping
	{
		String aliasName;
		String targetName;
	};
public:
    struct FalagardMapping
    {
        String windowName;
        String targetName;
        String lookName;
    };

	struct FontElement
	{
		String		name;
		String		filename;
		String		resourceGroup;
		FontType	type;
	};

	
	String	d_name;			

	UIElementFactory					d_imagesets_bin;
	std::vector<LoadableUIElement>		d_imagesets;
	std::vector<LoadableUIElement>		d_imagesetsFromImages;
	std::vector<FontElement>			d_fonts;
	std::vector<UIModule>				d_widgetModules;
	std::vector<AliasMapping>			d_aliasMappings;
    std::vector<LoadableUIElement>		d_looknfeels;
    std::vector<FalagardMapping>        d_falagardMappings;

	float								d_fontBlinkTime;
};

} 

#if defined(_MSC_VER)
#	pragma warning(pop)
#endif

#endif	
