

#ifndef _CEGUIRenderer_h_
#define _CEGUIRenderer_h_

#include "CEGUIBase.h"
#include "CEGUIString.h"
#include "CEGUIRect.h"
#include "CEGUIColourRect.h"
#include "CEGUIEventSet.h"

#include <vector>

typedef 	void (*GetMovableList)(const void *, void *queue);
typedef 	void (*callbackSetLogicModelPosition)(const void *, void* vec3, void* );


namespace CEGUI
{
	

enum OrientationFlags {
	FlipHorizontal		= 1,	
	FlipVertical		= 2,	
	RotateRightAngle	= 4		
};


enum QuadSplitMode
{
	TopLeftToBottomRight,	
	BottomLeftToTopRight	
};



class CEGUIEXPORT Renderer : public EventSet
{
public:
	static const String EventNamespace;				

	
	
	static const String EventDisplaySizeChanged;


	
	
	virtual	unsigned long	addQuad(const Rect& dest_rect, float z, const Imageset* tex, const Rect& texture_rect, const ColourRect& colours, QuadSplitMode quad_split_mode, void* pUserData = 0, bool isActiveHyperLink = false) = 0;
	virtual	unsigned long	addQuad(const void* quad) = 0;

	
	virtual unsigned long addTriangle(const Point* pt, const Point* uv, const Imageset* tex, 
		                              const colour& diffuse, float z) = 0;

	virtual uint32    colourToOgre(const colour& col) const = 0;

	
	virtual	void	adjustQuad(unsigned long id, const Imageset* tex, const Rect& texture_rect, const ColourRect& colours) = 0;

	
	virtual	void	doRender(bool redraw) = 0;

	
	
	virtual void initMinimapRender(const String&backgroundname, const String &alphaname, const size_t size) = 0;
	virtual void destroyMinimapRender(void) = 0;
	
	virtual void addMinimapQuad(const Rect& alpha_rect, const Rect& tex_rect,const Rect& vertex_rect,const Texture* tex, float z) = 0;

	
	virtual void add3DWindow(float, Window *) = 0;

	virtual void Register3DWindowFactory() = 0;

	virtual void setGetMovableList(GetMovableList fun) = 0;

	virtual void setLogicModelPosition(callbackSetLogicModelPosition fun) = 0;





	
	virtual	void	clearRenderList(void) = 0;


	
	virtual void	setQueueingEnabled(bool setting) = 0;


	
	virtual	Texture*	createTexture(void) = 0;


	
	virtual	Texture*	createTexture(const String& filename, const String& resourceGroup) = 0;


		
	virtual	Texture*	createTexture(float size) = 0;


	
	virtual	void		destroyTexture(Texture* texture) = 0;

	
	
	virtual void		destroyAllTextures(void) = 0;


	
	virtual bool	isQueueingEnabled(void) const = 0;


	
	virtual float	getWidth(void) const	= 0;


	
	virtual float	getHeight(void) const	= 0;


	
	virtual Size	getSize(void) const		= 0;

	virtual Size	getOldSize(void) const		= 0;


	
	virtual Rect	getRect(void) const		= 0;


	
	virtual	uint	getMaxTextureSize(void) const	= 0;


	
	virtual	uint	getHorzScreenDPI(void) const	= 0;


	
	virtual	uint	getVertScreenDPI(void) const	= 0;


	
	
	void	resetZValue(void)				{d_current_z = GuiZInitialValue;}


	
	void	advanceZValue(void)				{d_current_z -= GuiZElementStep;}


	
	float	getCurrentZ(void) const			{return d_current_z;}


	
	float	getZLayer(uint layer) const		{return d_current_z - ((float)layer * GuiZLayerStep);}


    
    const String& getIdentifierString() const;

    virtual ResourceProvider* createResourceProvider(void);

protected:
	
	Renderer(void);

public:		
	virtual ~Renderer(void);

private:
	
	static const float	GuiZInitialValue;		
	static const float	GuiZElementStep;		
	static const float	GuiZLayerStep;			


	
	float	d_current_z;		

protected:
    ResourceProvider* d_resourceProvider;      
    String d_identifierString;                 
	GetMovableList mGetMovableList;
	callbackSetLogicModelPosition mLogicModelPosition;
};

} 


#endif	
