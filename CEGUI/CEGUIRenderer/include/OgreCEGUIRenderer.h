#ifndef _OgreCEGUIRenderer_h_
#define _OgreCEGUIRenderer_h_

#include "OgreUIPreDefine.h"
#include <CEGUIBase.h>
#include <CEGUIRenderer.h>
#include <CEGUITexture.h>
#include "Ogre3DUIRenderQueue.h"
#include <OgreMaterialManager.h>
#include <OgreRoot.h>
#include <renderSystem.h>
#include <OgreRenderOperation.h>

namespace CEGUI
{
class OgreCEGUITexture;
class OgreCEGUIRenderer;
class Ogre3DUIWindow;
class Ogre::Camera;

class CEGUIRQListener
{
public:
	CEGUIRQListener(OgreCEGUIRenderer* renderer, uint32_t queue_id, bool post_queue)
	{
		d_renderer		= renderer;
		d_queue_id		= queue_id;
		d_post_queue	= post_queue;
	}

	virtual ~CEGUIRQListener() {}

	virtual void	renderQueueStarted(uint32_t id, const Ogre::String& invocation, bool& skipThisQueue);
	virtual void	renderQueueEnded(uint32_t id, const Ogre::String& invocation, bool& repeatThisQueue);
	void	setTargetRenderQueue(uint32_t queue_id)		{d_queue_id = queue_id;}
	void	setPostRenderQueue(bool post_queue)		{d_post_queue = post_queue;}

private:
	OgreCEGUIRenderer*				d_renderer;		
	uint32_t	d_queue_id;
	bool						d_post_queue;	
};

class OGRE_GUIRENDERER_API OgreCEGUIRenderer : public Renderer
{
public:
	enum RENDERTYPE
	{
		RT_SCENE,
		RT_CUSTOM,
		RT_COMMON,
		RT_MINIMAP,
		RT_TRI, 
		RT_NODE,
		RT_UNKNOWN,
	};

	
	struct QuadInfo
	{
		const Imageset*		texture;
		Rect				position;
		Rect				texPosition;
		uint32		        topLeftCol;
		uint32		        topRightCol;
		uint32		        bottomLeftCol;
		uint32		        bottomRightCol;
		float				z;
		int					runtimeId;

		
		bool				isHyperLinkActive;
		DWORD               dwHyperLinkActiveColor;

		void init()
		{
			texture = 0;
			runtimeId = 0;
			isHyperLinkActive = false;
			dwHyperLinkActiveColor = 0;
		}
	};

	struct Quad3DInfo
	{
		const OgreCEGUITexture* texture;
		Rect mVertexRect;
		Rect mCoordRect;
		Rect mAlphaRect;
		void init()
		{
			texture = 0;
		}
	};

	struct UI3DWindowInfo
	{
		Ogre3DUIWindow *mWindow;
		Ogre::AxisAlignedBox mAABBBox;
		Ogre::Camera *mCamera;
		const OgreCEGUITexture* mTexture;
		void init()
		{
		}
	};

	
	struct TriangleInfo
	{
		const Imageset* texture;
		Point pt[3];
		Point uv[3];
		uint32 diffuse;
		void init()
		{
			texture = 0;
		}
	};

	struct RenderAsserts
	{
		RENDERTYPE mType;
		float	z;
		size_t mStartIndex;
		size_t mEndIndex;
		size_t mVertexNum; 

		QuadInfo mCommonQuadInfo;
		TriangleInfo mTriangleInfo; 
		Quad3DInfo mMinimapQuad3DInfo;
		UI3DWindowInfo m3DWindowInfo;

		RenderAsserts()
		{
			init();
		}
		void init()
		{
			mType = RT_UNKNOWN;
			mStartIndex = 0;
			mEndIndex = 0;
			mVertexNum = 0;
			mCommonQuadInfo.init();
			mMinimapQuad3DInfo.init();
			m3DWindowInfo.init();
		}
	};

public:
	OgreCEGUIRenderer(Ogre::RenderTarget* target, uint32_t queue_id, bool post_queue = false, uint max_quads = 0);
	OgreCEGUIRenderer(Ogre::RenderTarget* target, uint32_t queue_id, bool post_queue, uint max_quads, Ogre::SceneManager* scene_manager);
	virtual ~OgreCEGUIRenderer(void);
	virtual	unsigned long	addQuad(const Rect& dest_rect, float z, const Imageset* tex, const Rect& texture_rect, const ColourRect& colours, QuadSplitMode quad_split_mode, void* pUserData = 0, bool isActiveHyperLink = false);
	virtual	unsigned long	addQuad(const void* quad);
	virtual	void	adjustQuad(unsigned long id, const Imageset* tex, const Rect& texture_rect, const ColourRect& colours);
	virtual	void	doRender(bool redraw = true);
	
	
	virtual unsigned long addTriangle(const Point* pt, const Point* uv, const Imageset* tex, 
		const colour& diffuse, float z);

	
	virtual void addMinimapQuad(const Rect& alpha_rect, const Rect& tex_rect,const Rect& vertex_rect,const Texture* tex, float z);
	
	
	
	virtual void initMinimapRender(const String&backgroundname, const String &alphaname, const size_t size);
	virtual void destroyMinimapRender(void);

	virtual void setGetMovableList(GetMovableList fun);
	virtual void setLogicModelPosition(callbackSetLogicModelPosition fun);

	
	virtual void add3DWindow(float, Window *);
	virtual void Register3DWindowFactory();
	void init3DRender();
	void destroy3DRender(void);
	void restore3DRenderState(void);



	virtual	void	clearRenderList(void);
	virtual void	setQueueingEnabled(bool setting)		{d_queueing = setting;}
	virtual	Texture*	createTexture(void);
	virtual	Texture*	createTexture(const String& filename, const String& resourceGroup = "General");
	virtual	Texture*	createTexture(float size);
    virtual ResourceProvider* createResourceProvider(void);
	virtual	void		destroyTexture(Texture* texture);
	virtual void		destroyAllTextures(void);
	virtual bool	isQueueingEnabled(void) const	{return d_queueing;}
	virtual float	getWidth(void) const		{return d_display_area.getWidth();}
	virtual float	getHeight(void) const		{return d_display_area.getHeight();}

	virtual Size	getSize(void) const			{return d_display_area.getSize();}
	virtual Size	getOldSize(void) const		{return d_old_display_area.getSize();};
	virtual Rect	getRect(void) const			{return d_display_area;}
	virtual	uint	getMaxTextureSize(void) const		{return 2048;}		
	virtual	uint	getHorzScreenDPI(void) const	{return 96;}
	virtual	uint	getVertScreenDPI(void) const	{return 96;}
	void	setTargetSceneManager(Ogre::SceneManager* scene_manager);
	void	setTargetRenderQueue(uint32_t queue_id, bool post_queue);
	Texture*	createTexture(Ogre::TexturePtr& texture);
	void	setDisplaySize(const Size& sz);

	void	_notifySizeChanged(void);

	void createMinimapMaterial();

	bool	isRenderDisable(void) const;
	void	setRenderDisable(bool bDisable);

private:
	
	static const size_t    VERTEX_PER_QUAD;						 
	static const size_t    VERTEX_PER_TRIANGLE;					 
    static const size_t    VERTEXBUFFER_INITIAL_CAPACITY;		 
    static const size_t    UNDERUSED_FRAME_THRESHOLD;            
	static const size_t	 MIMIMAPBUFFERSIZE;
	static const size_t    OGRE3DBUFFERSIZE;

	
	
	struct QuadVertex {
		float x, y, z;			
		Ogre::RGBA diffuse;		
		float tu1, tv1;			
	};

	
	void	initRenderStates(void);
	void	sortQuads(void);
	void	renderQuadDirect(const Rect& dest_rect, float z, const Texture* tex, const Rect& texture_rect, const ColourRect& colours, QuadSplitMode quad_split_mode);
    virtual uint32    colourToOgre(const colour& col) const;
	void	constructor_impl(Ogre::RenderTarget* target, uint32_t queue_id, bool post_queue, uint max_quads);

	void preparePrimitiveForRender();

	size_t mCommonElementVertexNumber;
	size_t mMinimapElementNumber;
	
	Rect				d_display_area;
	Rect				d_old_display_area;

	bool	 d_queueing;		

	friend CEGUIRQListener;
	
	Ogre::Root*					d_ogre_root;		
	RenderSystem*			d_render_sys;		
	Ogre::RenderTarget*			d_render_target;	
	uint32_t				d_queue_id;			
	Ogre::RenderOperation		d_render_op;
	Ogre::RenderOperation		d_direct_render_op;
	Ogre::HardwareVertexBufferSharedPtr	d_buffer;	
    size_t d_underused_framecount;                  	
	Ogre::HardwareVertexBufferSharedPtr	d_direct_buffer;	
	Ogre::SceneManager*			d_sceneMngr;		
	Ogre::LayerBlendModeEx		d_colourBlendMode;	
	Ogre::LayerBlendModeEx		d_alphaBlendMode;	


	Ogre::SceneNode *mOgre3DUINode;

	CEGUIRQListener*			d_ourlistener;
	bool						d_post_queue;		
	size_t						d_bufferPos;		
	bool						d_sorted;			
	Point						d_texelOffset;		
	bool						d_renderDisable;

	std::list<OgreCEGUITexture*> d_texturelist;		

    unsigned long   d_uid_counter;  

	
	

	

	
	
	Ogre::TexturePtr d_pAlphaTexture;
	Ogre::MaterialPtr mMinimapMaterial;

	
	Ogre::RenderOperation		d_3D_render_op;
	Ogre::HardwareVertexBufferSharedPtr	 d_3D_buffer;
	Ogre::Camera *m3DUIObjectCamera;
	
	typedef std::multimap<float, Ogre3DUIWindow*>Ogre3DUIWindowMap;
	Ogre3DUIWindowMap mOgre3DUIWindowMap;

	
	typedef std::multimap<float,RenderAsserts*, std::greater<float> >RenderAssertsMap;

	
	RenderAssertsMap mRenderAssertsMap;

	
	Ogre3DUIRenderQueue::RenderableList mRenderableList;

	
	Ogre3DUIRenderQueue mOgre3DUIRenderQueue;
	
	Ogre::MaterialPtr mGuiMaterial;
	
	std::vector<RenderAsserts*> mQuads;
};

} 


#endif	
