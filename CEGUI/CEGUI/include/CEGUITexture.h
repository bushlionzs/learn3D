

#ifndef _CEGUITexture_h_
#define _CEGUITexture_h_

#include "CEGUIBase.h"
#include "CEGUIString.h"


namespace CEGUI
{

class CEGUIEXPORT Texture
{
public:
	
	
	virtual	ushort	getWidth(void) const = 0;


	
	virtual	ushort	getHeight(void) const = 0;


	
	virtual void	loadFromFile(const String& filename, const String& resourceGroup) = 0;


	
	virtual void	loadFromMemory(const void* buffPtr, uint buffWidth, uint buffHeight) = 0;
	virtual void	loadFromMemoryLA(const void* buffPtr, uint buffWidth, uint buffHeight) = 0;


	virtual size_t	calculateSize(void) const = 0;


	
	Renderer*	getRenderer(void) const			{return d_owner;}


protected:
	
	
	Texture(Renderer* owner) : d_owner(owner) {}

public:		
	
	virtual ~Texture(void) {}

private:
	Renderer* d_owner;		
};

} 

#endif	
