


#include <CEGUISystem.h>
#include <CEGUIExceptions.h>
#include "OgreCEGUITexture.h"
#include "OgreCEGUIRenderer.h"
#include <string_util.h>
#include <OgreTextureManager.h>
#include <OgreDataStream.h>
#include <OgreMemoryStream.h>
#include <OgreResourceManager.h>

namespace CEGUI
{

uint32 OgreCEGUITexture::d_texturenumber		= 0;

OgreCEGUITexture::OgreCEGUITexture(Renderer* owner) :
	Texture(owner)
{
	d_ogre_texture.reset();
	d_isLinked = false;
}

OgreCEGUITexture::~OgreCEGUITexture(void)
{
	freeOgreTexture();
}

void OgreCEGUITexture::loadFromFile(const String& filename, const String& resourceGroup)
{
	using namespace Ogre;
	freeOgreTexture();
	try
	{
		TextureManager& textureManager = TextureManager::getSingleton();
		
		Ogre::TexturePtr ogreTexture = (Ogre::TexturePtr)textureManager.getByName(filename.c_str());

		if (ogreTexture)
		{
			
			d_ogre_texture = ogreTexture;
			d_isLinked = true;
		}
		else
		{
            String orpGroup;
            if (resourceGroup.empty())
            {
                const String& defGrp = CEGUI::System::getSingleton().getResourceProvider()->getDefaultResourceGroup();
                orpGroup = defGrp.empty() ? Ogre::ResourceManager::DEFAULT_RESOURCE_GROUP_NAME.c_str() : defGrp;
            }
            else
            {
                orpGroup = resourceGroup;
            }
			d_ogre_texture = TextureManager::getSingleton().load(filename.c_str(), nullptr);
			d_isLinked = false;
		}
	}
	catch(Ogre::Exception e)
	{
		throw RendererException((utf8*)"Failed to create Texture object from file '" + filename + "'. Additional Information:\n" + e.getFullDescription().c_str());
	}
	
	if (d_ogre_texture)
	{
		d_width		= d_ogre_texture->getWidth();
		d_height	= d_ogre_texture->getHeight();
	}
	else
	{
		throw RendererException((utf8*)"Failed to create Texture object from file '" + filename + "'.  Ogre returned a NULL pointer.");
	}
}

void _byteSwap(unsigned char* b, int n)
{
    register int i = 0;
    register int j = n-1;
    while (i<j)
    {
        std::swap(b[i], b[j]);
        i++, j--;
    }
}

#define byteSwap(x) _byteSwap((unsigned char*) &x,sizeof(x))

void OgreCEGUITexture::loadFromMemory(const void* buffPtr, uint buffWidth, uint buffHeight)
{
	using namespace Ogre;

	freeOgreTexture();
	
    uint32 bytesize = ((buffWidth * sizeof(uint32)) * buffHeight);


	DataStreamPtr odc(new Ogre::MemoryDataStream((const char*)(buffPtr), bytesize));

	TextureProperty property;
	property._width = buffWidth;
	property._height = buffHeight;
	property._tex_format = PF_A8R8G8B8;
	d_ogre_texture = TextureManager::getSingleton().loadRawData(getUniqueName(),  odc, property);

	
	if (d_ogre_texture)
	{
		d_width		= d_ogre_texture->getWidth();
		d_height	= d_ogre_texture->getHeight();
	}
	
	else
	{
		throw RendererException((utf8*)"Failed to create Texture object from memory:  Ogre returned a NULL Ogre::Texture pointer.");
	}

}


void OgreCEGUITexture::loadFromMemoryLA(const void* buffPtr, uint buffWidth, uint buffHeight)
{
	using namespace Ogre;
	freeOgreTexture();
	
	uint32 bytesize = ((buffWidth * sizeof(uint8) * 2) * buffHeight);
	DataStreamPtr odc(new MemoryDataStream((const char*)(buffPtr), bytesize));

	TextureProperty property;
	property._width = buffWidth;
	property._height = buffHeight;
	property._tex_format = PF_A8R8G8B8;
	d_ogre_texture = TextureManager::getSingleton().loadRawData(getUniqueName(), odc, property);

	
	if (d_ogre_texture)
	{
		d_width		= d_ogre_texture->getWidth();
		d_height	= d_ogre_texture->getHeight();
	}
	
	else
	{
		throw RendererException((utf8*)"Failed to create Texture object from memory:  Ogre returned a NULL Ogre::Texture pointer.");
	}
}

void OgreCEGUITexture::setOgreTextureSize(uint size)
{
	using namespace Ogre;
	freeOgreTexture();

	TextureProperty property;
	property._width = size;
	property._height = size;
	property._tex_format = PF_A8R8G8B8;

	d_ogre_texture = TextureManager::getSingleton().createManual(getUniqueName(), property);

	
	if (d_ogre_texture)
	{
		d_width		= d_ogre_texture->getWidth();
		d_height	= d_ogre_texture->getHeight();
	}
	
	else
	{
		throw RendererException((utf8*)"Failed to create texture of specified size: Ogre::Texture creation failed.");
	}
}

void OgreCEGUITexture::freeOgreTexture(void)
{
	if ((d_ogre_texture) && !d_isLinked)
	{
		Ogre::TextureManager::getSingleton().remove(d_ogre_texture->getName());
	}
	d_ogre_texture.reset();
}

Ogre::String OgreCEGUITexture::getUniqueName(void)
{
	Ogre::String str;
	str = dy::str_format("_cegui_ogre_%d", d_texturenumber);
	
	++d_texturenumber;

	return str;
}

void OgreCEGUITexture::setOgreTexture(Ogre::TexturePtr& texture)
{
	freeOgreTexture();

	d_ogre_texture = texture;
	d_width	 = d_ogre_texture->getWidth();
	d_height = d_ogre_texture->getHeight();
	d_isLinked = true;
}

} 

