

#ifndef _CEGUIImageset_h_
#define _CEGUIImageset_h_

#include "CEGUIBase.h"
#include "CEGUIString.h"
#include "CEGUIRect.h"
#include "CEGUIColourRect.h"
#include "CEGUIImagesetManager.h"
#include "CEGUIImage.h"
#include "CEGUIIteratorBase.h"

#include <map>


#if defined(_MSC_VER)
#	pragma warning(push)
#	pragma warning(disable : 4251)
#endif



namespace CEGUI
{


class CEGUIEXPORT Imageset
{
	friend class Imageset_xmlHandler;
private:
	typedef	std::map<String, Image>	ImageRegistry;

	
	friend Imageset*	ImagesetManager::createImageset(const String& name, Texture* texture);
	friend Imageset*	ImagesetManager::createImageset(const String& filename, const String& resourceGroup );
	friend Imageset*	ImagesetManager::createImagesetFromImageFile(const String& name, const String& filename, const String& resourceGroup);
	friend void			ImagesetManager::destroyImageset(const String& name);


	
	
	Imageset(const String& name, Texture* texture );


	
	Imageset(const String& filename, const String& resourceGroup  );


    
    Imageset(const String& name, const String& filename, const String& resourceGroup  );

public:	
	
	~Imageset(void);


public:
	typedef	ConstBaseIterator<ImageRegistry>	ImageIterator;	

	
	
	Texture*	getTexture(void) const;						
	Texture*	getOriginTexture(void) const;


	
	const String&	getName(void) const						{return d_name;}


	
	uint      getImageCount(void) const               {return (uint)d_images.size();}

 
	
	bool		isImageDefined(const String& name) const	{return d_images.find(name) != d_images.end();}

 
	
	const Image*	getImage(const String& name) const;


	
	void	undefineImage(const String& name);


	
	void	undefineAllImages(void);


	
	Size	getImageSize(const String& name) const;


	
	float	getImageWidth(const String& name) const;


	
	float	getImageHeight(const String& name) const;


	
	Point	getImageOffset(const String& name) const;


	
	float	getImageOffsetX(const String& name) const;


	
	float	getImageOffsetY(const String& name) const;

	
	bool	isTextureLoadDelay(void) const { return d_textureLoadDelay; }

	
	void	defineImage(const String& name, const Point& position, const Size& size, const Point& render_offset)
	{
		defineImage(name, Rect(position.d_x, position.d_y, position.d_x + size.d_width, position.d_y + size.d_height), render_offset);
	}


	
	void	defineImage(const String& name, const Rect& image_rect, const Point& render_offset);


	
	unsigned long	draw(const Rect& source_rect, const Rect& dest_rect, float z, const Rect& clip_rect,
		const ColourRect& colours, QuadSplitMode quad_split_mode, float xtex = 1.0f, float ytex = 1.0f, void* pUserData = 0, bool isActiveHyperLink = false) const;

	
	unsigned long   drawTri(const Rect& source_rect, const Rect& dest_rect, float z, const colour& diffuse, 
					     const Point* image_uv, float xtex, float ytex) const;

	
	unsigned int	draw(const Rect& source_rect, const Rect& dest_rect, float z, const Rect& clip_rect, const colour& top_left_colour = 0xFFFFFFFF, 
		const colour& top_right_colour = 0xFFFFFFFF,  const colour& bottom_left_colour = 0xFFFFFFFF, 
		const colour& bottom_right_colour = 0xFFFFFFFF, QuadSplitMode quad_split_mode = TopLeftToBottomRight, 
		float xtex = 1.0f, float ytex = 1.0f) const
	{
		return draw(source_rect, dest_rect, z, clip_rect, ColourRect(top_left_colour, top_right_colour, bottom_left_colour, bottom_right_colour), 
			quad_split_mode, xtex, ytex);
	}


	
	bool	isAutoScaled(void) const		{return d_autoScale;}


	
	Size	getNativeResolution(void) const	{return Size(d_nativeHorzRes, d_nativeVertRes);}


	
	void	setAutoScalingEnabled(bool setting);


	
	void	setNativeResolution(const Size& size);


	
	void	notifyScreenResolution(const Size& size);


	
	ImageIterator	getIterator(void) const;


    
    void writeXMLToStream(OutStream& out_stream) const;

	int	 setLayoutRefCount(bool addOrDec);
	void destroyImagesetTexture();



	void setImageArea( const String& name, Rect rect );

	void	AutoFree();


	void    setAutoFree( bool bAutoFree ) { d_useAutoFree = bAutoFree; };
	void    setTextureLoadDelay( bool bDelay ) { d_textureLoadDelay = bDelay; };

	const String& getTextureFilename(void) const { return d_textureFilename; }

	size_t	getTextureSize(void) const;

	int		getRefCount(void) const {return d_layoutRefCount;}


protected:
	
	static const char	ImagesetSchemaName[];			


	
		
	void	load(const String& filename, const String& resourceGroup);

		
	void	checkLoad(void);

	
	void	unload(void);


	
	void	setTexture(Texture* texture);


	
	void	updateImageScalingFactors(void);


	
	String			d_name;						
	ImageRegistry	d_images;					
	Texture*		d_texture;					
    String          d_textureFilename;          
	String			d_resourceGroup;
	bool			d_isFromFile;

	
	bool	d_autoScale;			
	float	d_horzScaling;			
	float	d_vertScaling;			
	float	d_nativeHorzRes;		
	float	d_nativeVertRes;		

	
	bool	d_textureLoadDelay;		
	bool	d_needFree;
	bool    d_useAutoFree;
	int		d_layoutRefCount;

};

} 

#if defined(_MSC_VER)
#	pragma warning(pop)
#endif

#endif	
