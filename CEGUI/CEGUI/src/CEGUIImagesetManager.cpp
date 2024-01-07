

#include "CEGUIImagesetManager.h"
#include "CEGUIExceptions.h"
#include "CEGUILogger.h"
#include "CEGUIImageset.h"
#include "CEGUISystem.h"
#include "CEGUIPropertyHelper.h"


namespace CEGUI
{


template<> ImagesetManager* Singleton<ImagesetManager>::ms_Singleton	= NULL;

bool ImagesetManager::d_textureLoadDelay = true;

ImagesetManager::ImagesetManager(void)
{
	

	d_videoMemorySize = 0;
}



ImagesetManager::~ImagesetManager(void)
{
	Logger::getSingleton().logEvent((utf8*)"---- Begining cleanup of Imageset system ----");

	destroyAllImagesets();

	
}



Imageset* ImagesetManager::createImageset(const String& name, Texture* texture)
{
	

	if (isImagesetPresent(name))
	{
		throw	AlreadyExistsException("ImagesetManager::createImageset - An Imageset object named '" + name + "' already exists.");
	}

	Imageset* temp = new Imageset(name, texture);
	d_imagesets[name] = temp;

	return temp;
}



Imageset* ImagesetManager::createImageset(const String& filename, const String& resourceGroup )
{
	
	const char* aa = filename.c_str();
	printf("imageset:%s\n", aa);
	Imageset* temp = new Imageset(filename, resourceGroup );

	String	name = temp->getName();

	if (isImagesetPresent(name))
	{
		delete temp;

		throw	AlreadyExistsException("ImagesetManager::createImageset - An Imageset object named '" + name + "' already exists.");
	}

	d_imagesets[name] = temp;

	return temp;
}



Imageset* ImagesetManager::createImagesetFromImageFile(const String& name, const String& filename, const String& resourceGroup)
{
    

    if (isImagesetPresent(name))
    {
        throw	AlreadyExistsException("ImagesetManager::createImageset - An Imageset object named '" + name + "' already exists.");
    }

    Imageset* temp = new Imageset(name, filename, resourceGroup);
    d_imagesets[name] = temp;

    return temp;
}


void ImagesetManager::destroyImageset(const String& name)
{
	ImagesetRegistry::iterator	pos = d_imagesets.find(name);

	if (pos != d_imagesets.end())
	{
		String tmpName(name);

		delete pos->second;
		d_imagesets.erase(pos);

		Logger::getSingleton().logEvent((utf8*)"Imageset '" + tmpName +"' has been destroyed.", Informative);
	}

}



void ImagesetManager::destroyImageset(Imageset* imageset)
{
	if (imageset != NULL)
	{
		destroyImageset(imageset->getName());
	}

}



void ImagesetManager::destroyAllImagesets(void)
{
	while (!d_imagesets.empty())
	{
		destroyImageset(d_imagesets.begin()->first);
	}
}


Imageset* ImagesetManager::getImageset(const String& name) const
{
	ImagesetRegistry::const_iterator	pos = d_imagesets.find(name);

	if (pos == d_imagesets.end())
	{
		return NULL;
		
	}

	return pos->second;
}



void ImagesetManager::notifyScreenResolution(const Size& size)
{
	
	ImagesetRegistry::iterator pos = d_imagesets.begin(), end = d_imagesets.end();

	for (; pos != end; ++pos)
	{
		pos->second->notifyScreenResolution(size);
	}

}


ImagesetManager& ImagesetManager::getSingleton(void)
{
	return Singleton<ImagesetManager>::getSingleton();
}


ImagesetManager* ImagesetManager::getSingletonPtr(void)
{
	return Singleton<ImagesetManager>::getSingletonPtr();
}



ImagesetManager::ImagesetIterator ImagesetManager::getIterator(void) const
{
	return ImagesetIterator(d_imagesets.begin(), d_imagesets.end());
}


void ImagesetManager::writeImagesetToStream(const String& imageset, OutStream& out_stream) const
{
    const Imageset* iset = getImageset(imageset);

    
    out_stream << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << std::endl;

    
    iset->writeXMLToStream(out_stream);
}

void ImagesetManager::FreeUnuseImageset()
{
	ImagesetRegistry::iterator pos = d_imagesets.begin(), end = d_imagesets.end();
	for (; pos != end; ++pos)
	{
		pos->second->AutoFree();
	}
}

void ImagesetManager::logVideoMemoryFile()
{
	try
	{
		ImagesetRegistry::iterator pos = d_imagesets.begin(), end = d_imagesets.end();
		for (; pos != end; ++pos)
		{
			if( pos->second->getOriginTexture() != NULL )
			{
				String sizeB = PropertyHelper::intToString( (int)pos->second->getTextureSize());
				String sizeKB = PropertyHelper::floatToString( (float)pos->second->getTextureSize() / 1024.0f );
				String sizeMB = PropertyHelper::floatToString( (float)pos->second->getTextureSize() / 1048576.0f );
				Logger::getSingleton().logVideoMemoryEvent("Texture File: " + pos->first + " ---> " + sizeB + "B   " + sizeKB + "KB   " + sizeMB + "MB.", Standard);
			}
		}
	}
	catch (UnknownObjectException)
	{
		
	}
}

void ImagesetManager::logVideoMemoryFile(const String& layout, const String& imageset)
{
	try
	{
		const Imageset* iset = getImageset(imageset);
		if( iset )
		{
			if( iset->getOriginTexture() != NULL )
			{
				String refCount = PropertyHelper::intToString( iset->getRefCount() );
				Logger::getSingleton().logVideoMemoryEvent("Layout File: " + layout + " ---> " + imageset + "   RefCount=" + refCount + ".", Standard);
			}
		}
	}
	catch (UnknownObjectException)
	{
		
	}
}

void ImagesetManager::setVideoMemoryFilename( const String& filename, bool append  )
{
	Logger::getSingleton().setVideoMemoryFilename(filename, append);
}
} 
