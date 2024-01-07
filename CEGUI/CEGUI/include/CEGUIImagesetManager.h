

#ifndef _CEGUIImagesetManager_h_
#define _CEGUIImagesetManager_h_

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

class CEGUIEXPORT ImagesetManager : public Singleton<ImagesetManager>
{
public:
	
	ImagesetManager(void);


	
	~ImagesetManager(void);


	
	static	ImagesetManager&	getSingleton(void);


	
	static	ImagesetManager*	getSingletonPtr(void);


	
	Imageset*	createImageset(const String& name, Texture* texture);

	
	Imageset*	createImageset(const String& filename, const String& resourceGroup = "");


    
    Imageset* createImagesetFromImageFile(const String& name, const String& filename, const String& resourceGroup = "");

	
	void	destroyImageset(const String& name);

	
	void	destroyImageset(Imageset* imageset);


	
	void	destroyAllImagesets(void);


	
	Imageset*	getImageset(const String& name) const;


	
	bool	isImagesetPresent(const String& name) const			{return d_imagesets.find(name) != d_imagesets.end();}


	
	void	notifyScreenResolution(const Size& size);


    
    void writeImagesetToStream(const String& imageset, OutStream& out_stream) const;

	void setVideoMemorySize(size_t size)	{d_videoMemorySize = size;}
	size_t getVideoMemorySize()				{return d_videoMemorySize;}

private:
	
	typedef	std::map<String, Imageset*>		ImagesetRegistry;
	ImagesetRegistry	d_imagesets;

	size_t		d_videoMemorySize;

public:
	
	typedef	ConstBaseIterator<ImagesetRegistry>	ImagesetIterator;

	
	ImagesetIterator	getIterator(void) const;

	void		FreeUnuseImageset();
	void		setVideoMemoryFilename(const String& filename, bool append = false);
	void		logVideoMemoryFile();
	void		logVideoMemoryFile(const String& layout, const String& imageset);

	static bool d_textureLoadDelay;

};

} 

#if defined(_MSC_VER)
#	pragma warning(pop)
#endif

#endif	
