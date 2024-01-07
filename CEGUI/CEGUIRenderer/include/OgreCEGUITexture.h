#ifndef _OgreCEGUITexture_h_
#define _OgreCEGUITexture_h_

#include <CEGUIBase.h>
#include <CEGUIRenderer.h>
#include <CEGUITexture.h>
#include "OgreCEGUIRenderer.h"


namespace CEGUI
{

class OGRE_GUIRENDERER_API OgreCEGUITexture : public Texture
{
private:
	
	friend	Texture* OgreCEGUIRenderer::createTexture(void);
	friend	Texture* OgreCEGUIRenderer::createTexture(const String& filename, const String& resourceGroup);
	friend	Texture* OgreCEGUIRenderer::createTexture(float size);
	friend	void	 OgreCEGUIRenderer::destroyTexture(Texture* texture);

	OgreCEGUITexture(Renderer* owner);
	virtual ~OgreCEGUITexture(void);

public:
	
	virtual	ushort	getWidth(void) const		{return d_width;}


	
	virtual	ushort	getHeight(void) const		{return d_height;}

	virtual size_t	calculateSize(void) const	{return d_ogre_texture->getSize();}

	
	virtual void	loadFromFile(const String& filename, const String& resourceGroup);


	
	virtual void	loadFromMemory(const void* buffPtr, uint buffWidth, uint buffHeight);

	virtual void	loadFromMemoryLA(const void* buffPtr, uint buffWidth, uint buffHeight);

	
	Ogre::TexturePtr	getOgreTexture(void) const		{return d_ogre_texture;}


	
	void	setOgreTextureSize(uint size);


	
	void	setOgreTexture(Ogre::TexturePtr& texture);


private:
	
	
	void	freeOgreTexture(void);

	
	Ogre::String	getUniqueName(void);


	
	static	uint32          d_texturenumber;	

	Ogre::TexturePtr		d_ogre_texture;		

	ushort					d_width;			
	ushort					d_height;			

	bool	d_isLinked;		
};


} 


#endif	
