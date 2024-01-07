

#ifndef _CEGUIFontManager_h_
#define _CEGUIFontManager_h_

#include "CEGUIBase.h"
#include "CEGUIString.h"
#include "CEGUISingleton.h"
#include "CEGUIIteratorBase.h"
#include "CEGUIFont.h"
#include "CEGUIDataContainer.h"
#include <map>
#include <vector>

#if defined(_MSC_VER)
#	pragma warning(push)
#	pragma warning(disable : 4275)
#	pragma warning(disable : 4251)
#endif



namespace CEGUI
{

struct CEGUIEXPORT FontBlinkRuntime
{
	Imageset*		d_texture;			
	Rect			d_textureRect;		
	unsigned long	d_quadID;			
	ColourRect		d_colorRect;		
	float			d_originalAlpha;			
};


class CEGUIEXPORT FontManager : public Singleton<FontManager>
{
public:
	
	FontManager(void);


	
	~FontManager(void);


	
	static	FontManager&	getSingleton(void);


	
	static	FontManager*	getSingletonPtr(void);


	
	Font*	createFont(FontType type, const String& filename, const String& resourceGroup = "");

	
	void	destroyFont(const String& name);


	
	void	destroyFont(Font* font);


	
	void	destroyAllFonts(void);


	
	bool	isFontPresent(const String& name) const;


	
	Font*	getFont(const String& name) const;


	
	void	notifyScreenResolution(const Size& size);

    
	void prepareFontTexture(void);
	
	
	void	addRuntimeBlink(const Window* OwnerWindow, const Image* img,unsigned long& quadID,const Vector3& position, const Size& size, const Rect& clip_rect, const ColourRect& col_rect);

	
	void	clearRuntimeBlinkList(void);

	
	void	updateRuntimeBlinkList(void);

	void	updateRuntimeBlink( FontBlinkRuntime &runtime );
	void	updateRuntimeBlink( const ColourRect &runtimeColor, void* pInfo );
	void	updateRuntimeBlink( float alpha, void* pInfo );

	
	void	calculateBlinkAlphaValue(void);

	
	float	getBlinkAlphaValue(void){ return d_curBlinkAlpha;}

	
	void	setFontBlinkTime(const float& time = 0.8){ if(time > 0.5f && time < 20.0f) d_totalLife = time; }


	
	bool	isFontRawDataPresent(const String& name) const;		
	RawDataContainer*	getFontRawData(const String& name);
	bool	destroyFontRawData(RawDataContainer* pRawDataContainer);
	RawDataContainer*	createFontRawData( const String& filename, const String& resourceGroup);
	



private:
	
	typedef	std::map<String, Font*>		FontRegistry;
	FontRegistry		d_fonts;			

	
	typedef	std::map<String, RawDataContainer*>				FontRawDataContainerMap;
	typedef	std::map<String, RawDataContainer*>::iterator	FontRawDataContainerMapIterator;
	FontRawDataContainerMap		d_fontRawContainers;	
	


	struct FontManagerImplData;
	FontManagerImplData*	d_implData;

	typedef std::vector< FontBlinkRuntime >		FontBlinkRegistry;
	
	float					d_timeOld;		
	float					d_totalLife;	
	float					d_minAlpha;		

	float					d_curBlinkAlpha;		
    
	FontBlinkRegistry		d_runtimeBlink;
	
public:
	
	typedef	ConstBaseIterator<FontRegistry>	FontIterator;

	
	FontIterator	getIterator(void) const;
};

} 


#if defined(_MSC_VER)
#	pragma warning(pop)
#endif

#endif	
