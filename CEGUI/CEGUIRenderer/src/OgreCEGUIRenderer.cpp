

#include <OgreHeader.h>
#include <CEGUIImagesetManager.h>
#include <CEGUIImageset.h>
#include <CEGUIImage.h>
#include <CEGUIExceptions.h>
#include <CEGUISystem.h>

#include "OgreCEGUIRenderer.h"
#include "OgreCEGUITexture.h"
#include "OgreCEGUIResourceProvider.h"

#include <RenderSystem.h>
#include <OgreRoot.h>
#include <OgreHardwareBufferManager.h>
#include <OgreRenderTarget.h>
#include <OgreTextureManager.h>
#include <OgreHardwarePixelBuffer.h>
#include <OgreViewPort.h>
#include <OgreRenderOperation.h>
#include "Ogre3DUIWindow.h"
#include <OgreResourceManager.h>

#include <OgreEntity.h>
#include <OgreParticleSystem.h>

#include <OgreCamera.h>
#include "CEGUIPropertyHelper.h"
#include <vertex_declaration.h>
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <Windows.h>



namespace CEGUI
{

const size_t	OgreCEGUIRenderer::VERTEX_PER_QUAD			= 6;
const size_t	OgreCEGUIRenderer::VERTEX_PER_TRIANGLE		= 3;
const size_t	OgreCEGUIRenderer::VERTEXBUFFER_INITIAL_CAPACITY	= 256;
const size_t    OgreCEGUIRenderer::UNDERUSED_FRAME_THRESHOLD = 50000; 
const size_t	 OgreCEGUIRenderer::OGRE3DBUFFERSIZE = 6;
const String MINIMAPTATERIALNAME = "minimapmaterial";
const String MINIMAPBASETEXTURENAME = "basetexture";
const String MINIMAPALPHATEXTURENAME = "alphatexture";

const size_t OGRE3DWINDOWVISIBLAFLAG = 1 << 2; 

static Ogre3DUIWindowFactory g3DFactory;



void createQuadRenderOp(Ogre::RenderOperation &d_render_op, 
    Ogre::HardwareVertexBufferSharedPtr &d_buffer, size_t nVerts)
{
    using namespace Ogre;
	d_render_op.vertexData = new VertexData;
	d_render_op.vertexData->vertexStart = 0;
	VertexDeclaration* vd = d_render_op.vertexData->vertexDeclaration;
	size_t vd_offset = 0;
	vd->addElement(0, 0, vd_offset, VET_FLOAT3, VES_POSITION);
	vd_offset += VertexElement::getTypeSize(VET_FLOAT3);
	vd->addElement(0, 0, vd_offset, VET_COLOUR, VES_DIFFUSE);
	vd_offset += VertexElement::getTypeSize(VET_COLOUR);
	vd->addElement(0, 0, vd_offset, VET_FLOAT2, VES_TEXTURE_COORDINATES);
	d_buffer = HardwareBufferManager::getSingleton().createVertexBuffer(vd->getVertexSize(0), nVerts,  
        HardwareBuffer::HBU_DYNAMIC_WRITE_ONLY_DISCARDABLE);

	d_render_op.vertexData->setBinding(0, d_buffer);
	d_render_op.operationType = RenderOperation::OT_TRIANGLE_LIST;
	d_render_op.useIndexes = false;

	
	d_render_op.srcRenderable = NULL;
}

void destroyQuadRenderOp(Ogre::RenderOperation &d_render_op, 
    Ogre::HardwareVertexBufferSharedPtr &d_buffer)
{
    delete d_render_op.vertexData;
    d_render_op.vertexData = 0;
    d_buffer.reset();
}

void resizeQuadRenderOp(Ogre::RenderOperation &d_render_op, Ogre::HardwareVertexBufferSharedPtr &d_buffer,size_t requestedSize)
{	
	size_t size = d_buffer->getNumVerts();
	if(size < requestedSize)
	{
		while(size < requestedSize)
			size = size * 2;
		destroyQuadRenderOp(d_render_op, d_buffer);
		createQuadRenderOp(d_render_op, d_buffer, size);
	}
}

void create3DRenderOp(Ogre::RenderOperation &d_render_op, 
					  Ogre::HardwareVertexBufferSharedPtr &d_buffer, size_t nquads)
{
	using namespace Ogre;
	
	d_render_op.vertexData = new VertexData;
	d_render_op.vertexData->vertexStart = 0;

	VertexDeclaration* vd = d_render_op.vertexData->vertexDeclaration;
	size_t vd_offset = 0;
	vd->addElement(0, 0, vd_offset, VET_FLOAT3, VES_POSITION);
	vd_offset += VertexElement::getTypeSize(VET_FLOAT3);
	
	vd->addElement(0, 0, vd_offset, VET_FLOAT2, VES_TEXTURE_COORDINATES);
	vd_offset += VertexElement::getTypeSize(VET_FLOAT2);
	vd->addElement(0, 1, vd_offset, VET_FLOAT2, VES_TEXTURE_COORDINATES);
	
	d_buffer = HardwareBufferManager::getSingleton().createVertexBuffer(vd->getVertexSize(0), nquads,  
		HardwareBuffer::HBU_DYNAMIC_WRITE_ONLY_DISCARDABLE);
	
	d_render_op.vertexData->setBinding(0, d_buffer);
	
	d_render_op.operationType = RenderOperation::OT_TRIANGLE_LIST;
	d_render_op.useIndexes = false;
	
	d_render_op.srcRenderable = NULL;
}

void resize3DRenderOp(Ogre::RenderOperation &d_render_op, Ogre::HardwareVertexBufferSharedPtr &d_buffer,size_t requestedSize)
{	
	size_t size = d_buffer->getNumVerts();
	if(size < requestedSize)
	{
		while(size < requestedSize)
			size = size * 2;
		destroyQuadRenderOp(d_render_op, d_buffer);
		create3DRenderOp(d_render_op, d_buffer, size);
	}
}

OgreCEGUIRenderer::OgreCEGUIRenderer(Ogre::RenderTarget* target, uint32_t queue_id, bool post_queue, uint max_quads)
{
	constructor_impl(target, queue_id, post_queue, max_quads);
}

OgreCEGUIRenderer::OgreCEGUIRenderer(Ogre::RenderTarget* target, uint32_t queue_id, bool post_queue, uint max_quads, Ogre::SceneManager* scene_manager)
{
	constructor_impl(target, queue_id, post_queue, max_quads);
	
	Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().getByName("BaseWhiteNoLighting");
	
	mGuiMaterial = material->clone("Gui_Default_Render");

	mGuiMaterial->addTexture("Gui_Default_Render_Pass0_Tex0");
	
	mGuiMaterial->load();
		
	setTargetSceneManager(scene_manager);
	mOgre3DUIRenderQueue.setQueueGroupVector(&mRenderableList);
}

OgreCEGUIRenderer::~OgreCEGUIRenderer(void)
{
	setTargetSceneManager(NULL);

	if (d_ourlistener)
	{
		delete d_ourlistener;
	}
	

	destroyMinimapRender();
	destroyAllTextures();
}

unsigned long OgreCEGUIRenderer::addQuad(const Rect& dest_rect, float z, const Imageset* tex, const Rect& texture_rect, const ColourRect& colours,
										 QuadSplitMode quad_split_mode, void* pUserData, bool isActiveHyperLink)
{
	RenderAsserts* renderquad = new RenderAsserts;
	renderquad->mType = RT_COMMON;
	renderquad->z				= -1 + z;
	QuadInfo *quad = &(renderquad->mCommonQuadInfo);
		
	quad->z = -1 + z;
		
	quad->position.d_left	= dest_rect.d_left;
	quad->position.d_right	= dest_rect.d_right;
	quad->position.d_top	= d_display_area.getHeight() - dest_rect.d_top;
	quad->position.d_bottom	= d_display_area.getHeight() - dest_rect.d_bottom;
	quad->position.offset(d_texelOffset);
		
	quad->position.d_left	/= (d_display_area.getWidth() * 0.5f);
	quad->position.d_right	/= (d_display_area.getWidth() * 0.5f);
	quad->position.d_top	/= (d_display_area.getHeight() * 0.5f);
	quad->position.d_bottom	/= (d_display_area.getHeight() * 0.5f);
	quad->position.offset(Point(-1.0f, -1.0f));

	quad->texture		= tex;
	quad->texPosition	= texture_rect;
		
	quad->topLeftCol	= colourToOgre(colours.d_bottom_left);
	quad->topRightCol	= colourToOgre(colours.d_bottom_right);
	quad->bottomLeftCol	= colourToOgre(colours.d_top_left);
	quad->bottomRightCol= colourToOgre(colours.d_top_right);

	mCommonElementVertexNumber += VERTEX_PER_QUAD;

	mQuads.push_back(renderquad);
	int ret = mQuads.size() - 1;
	quad->runtimeId = ret;

	DWORD dwHyperLinkColorActive = 0;
	if( pUserData )
	{
		dwHyperLinkColorActive = static_cast<Window*>(pUserData)->getHyperLinkColorActive();
		static_cast<Window*>(pUserData) ->setCacheRenderInfo( quad );
	}

	if( isActiveHyperLink )
	{
		utf32 curValue = utf32(dwHyperLinkColorActive);//0xffb642f3
		CEGUI::colour hyperColor = curValue;
		ColourRect col(hyperColor);

		quad->topLeftCol	= colourToOgre(col.d_bottom_left);
		quad->topRightCol	= colourToOgre(col.d_bottom_right);
		quad->bottomLeftCol	= colourToOgre(col.d_top_left);
		quad->bottomRightCol= colourToOgre(col.d_top_right);
	}

	return ret;
}

unsigned long OgreCEGUIRenderer::addTriangle(const Point* pt, const Point* uv, const Imageset* tex, 
									const colour& diffuse, float z)
{
	RenderAsserts* pRenderAsserts = new RenderAsserts;
	pRenderAsserts->mType = RT_TRI;
	pRenderAsserts->z = -1 + z;

	TriangleInfo* pTriInfo = &(pRenderAsserts->mTriangleInfo);
	memcpy(&pTriInfo->pt[0], pt, sizeof(Point)*3);
	memcpy(&pTriInfo->uv[0], uv, sizeof(Point)*3);
	pTriInfo->texture = tex;
	pTriInfo->diffuse = diffuse;

	for(int i=0;i<3;i++)
	{
		pTriInfo->pt[i].d_y	= d_display_area.getHeight() - pTriInfo->pt[i].d_y;
		pTriInfo->pt[i].d_x += d_texelOffset.d_x;
		pTriInfo->pt[i].d_y += d_texelOffset.d_y;
		
		pTriInfo->pt[i].d_x	/= (d_display_area.getWidth() * 0.5f);
		pTriInfo->pt[i].d_y /= (d_display_area.getHeight() * 0.5f);

		pTriInfo->pt[i].d_x -= 1.f;
		pTriInfo->pt[i].d_y -= 1.f;
	}

	mCommonElementVertexNumber += VERTEX_PER_TRIANGLE;

	mQuads.push_back(pRenderAsserts);
	return mQuads.size() - 1;
}

unsigned long OgreCEGUIRenderer::addQuad(const void* quad)
{
	RenderAsserts *renderquad = new RenderAsserts;
	QuadInfo* quadInfo =  (QuadInfo*)quad;
	renderquad->mCommonQuadInfo = *quadInfo;
	if( quadInfo->isHyperLinkActive )
	{
		utf32 curValue = utf32(quadInfo->dwHyperLinkActiveColor);//0xFFb642f3
		CEGUI::colour hyperColor = curValue;
		ColourRect col(hyperColor);

		renderquad->mCommonQuadInfo.topLeftCol		= colourToOgre(col.d_bottom_left);
		renderquad->mCommonQuadInfo.topRightCol		= colourToOgre(col.d_bottom_right);
		renderquad->mCommonQuadInfo.bottomLeftCol	= colourToOgre(col.d_top_left);
		renderquad->mCommonQuadInfo.bottomRightCol	= colourToOgre(col.d_top_right);
	}
	renderquad->mType  = RT_COMMON;
	renderquad->z	   = quadInfo->z;

	mCommonElementVertexNumber += VERTEX_PER_QUAD;

	mQuads.push_back(renderquad);
	return mQuads.size() - 1;
}

void OgreCEGUIRenderer::add3DWindow(float z, Window *w)
{
	RenderAsserts *renderquad = new RenderAsserts;
	renderquad->z				= -1 + z;
	UI3DWindowInfo *info = &(renderquad->m3DWindowInfo);
	info->mWindow = reinterpret_cast<Ogre3DUIWindow*>(w);
	if(info->mWindow->get3DUIGeometryType() == "scene")
		renderquad->mType = RT_SCENE;
	else if(info->mWindow->get3DUIGeometryType() == "node")
		renderquad->mType = RT_NODE;
	mQuads.push_back(renderquad);
}

void OgreCEGUIRenderer::addMinimapQuad(const Rect& alpha_rect, const Rect& tex_rect,
									   const Rect& vertex_rect,const Texture* tex, float z)
{	
	RenderAsserts *renderquad = new RenderAsserts;
	renderquad->mType = RT_MINIMAP;
	renderquad->z				= -1 + z;
	
	Quad3DInfo *info = &(renderquad->mMinimapQuad3DInfo);
	Rect vertexrect = vertex_rect;
	vertexrect.d_top		= d_display_area.getHeight() - vertex_rect.d_top;
	vertexrect.d_bottom	= d_display_area.getHeight() - vertex_rect.d_bottom;
	vertexrect.d_left	/= (d_display_area.getWidth() * 0.5f);
	vertexrect.d_right	/= (d_display_area.getWidth() * 0.5f);
	vertexrect.d_top		/= (d_display_area.getHeight() * 0.5f);
	vertexrect.d_bottom	/= (d_display_area.getHeight() * 0.5f);
	vertexrect.offset(Point(-1.0f, -1.0f));

	info->mAlphaRect = alpha_rect;
	info->mCoordRect = tex_rect;
	info->mVertexRect = vertexrect;
	info->texture = static_cast<const OgreCEGUITexture*>(tex);

	mMinimapElementNumber++;
	mQuads.push_back(renderquad);
}

void OgreCEGUIRenderer::createMinimapMaterial()
{
	mMinimapMaterial = Ogre::MaterialManager::getSingleton().getByName(MINIMAPTATERIALNAME.c_str());
	if(!mMinimapMaterial)
	{
		Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().getByName("BaseWhiteNoLighting");
		mMinimapMaterial = material->clone(MINIMAPTATERIALNAME.c_str());
	}


	mMinimapMaterial->addTexture(MINIMAPBASETEXTURENAME.c_str());
	mMinimapMaterial->addTexture(MINIMAPALPHATEXTURENAME.c_str());


	mMinimapMaterial->touch();
}

void OgreCEGUIRenderer::adjustQuad(unsigned long id, const Imageset* tex, const Rect& texture_rect, const ColourRect& colours)
{
	RenderAsserts* renderquad = mQuads[id];
	if( renderquad == NULL )
		return;

	QuadInfo *quad = &(renderquad->mCommonQuadInfo);

	quad->texture		= tex;
	quad->texPosition	= texture_rect;
	
	quad->topLeftCol	= colourToOgre(colours.d_bottom_left);
	quad->topRightCol	= colourToOgre(colours.d_bottom_right);
	quad->bottomLeftCol	= colourToOgre(colours.d_top_left);
	quad->bottomRightCol= colourToOgre(colours.d_top_right);
}

void OgreCEGUIRenderer::doRender(bool redraw)
{	
	if (d_render_sys->_getViewport()->getOverlaysEnabled() 
		&& d_render_sys->_getViewport()->getTarget() == d_render_target &&
		!d_renderDisable )
	{

		if(redraw)
		{
			preparePrimitiveForRender();
		}


		initRenderStates();

		size_t elementnumber = mQuads.size();
		RenderAsserts **renderassert = mQuads.data();

		for(size_t i=0; i<elementnumber; i++)
		{
			RenderAsserts* tempAssert = renderassert[i];
			switch(tempAssert->mType)
			{
			case RT_SCENE:
				{
					UI3DWindowInfo *info = &(tempAssert->m3DWindowInfo);
					Ogre3DUIWindow *window = info->mWindow;
					if(!window->getLogicModelObjPointer() || !window->getCameraPointer())
						break;

					size_t startindex = tempAssert->mStartIndex;
					size_t endindex = tempAssert->mEndIndex;

					Rect target = window->getPixelRect();
			
					info->mCamera->setAspectRatio(target.getWidth()/target.getHeight());
					
					
					for(size_t i = startindex; i<endindex; i++)
					{
						auto r = mRenderableList[i];	
						d_render_sys->render(r, RenderListType_Opaque);
					}

					initRenderStates();
				}	
				break;
			case RT_NODE:
				{
					size_t startindex = tempAssert->mStartIndex;
					size_t endindex = tempAssert->mEndIndex;

					UI3DWindowInfo *info = &(tempAssert->m3DWindowInfo);
					Ogre3DUIWindow *window = info->mWindow;

					Ogre::AxisAlignedBox aabbBox = info->mAABBBox;

					const Ogre::Vector3 &vMin = aabbBox.getMinimum();
					const Ogre::Vector3 &vMax = aabbBox.getMaximum();
					Ogre::Vector3 vExt = vMax - vMin;

					Ogre::Matrix4 worldmatrix = Ogre::Matrix4::IDENTITY;
					Rect target = window->getPixelRect();

					target.d_top		= d_display_area.getHeight() - target.d_top;
					target.d_bottom	= d_display_area.getHeight() - target.d_bottom;
					target.d_left	/= (d_display_area.getWidth() * 0.5f);
					target.d_right	/= (d_display_area.getWidth() * 0.5f);
					target.d_top		/= (d_display_area.getHeight() * 0.5f);
					target.d_bottom	/= (d_display_area.getHeight() * 0.5f);
					target.offset(Point(-1.0f, -1.0f));

					float xscale = (target.d_top - target.d_bottom)/(vExt.x);
					float yscale = (target.d_right - target.d_left)/(vExt.y);
					float zscale = 1/(vExt.z);

					float xtrans = (target.d_left + target.d_right)/2.0f;
					float ytrans = (target.d_top + target.d_bottom)/2.0f;

					worldmatrix.setScale(Ogre::Vector3(xscale,yscale,zscale));
					worldmatrix.setTrans(Ogre::Vector3(xtrans,ytrans,0.0f));




					for(size_t i = startindex; i<endindex; i++)
					{
						Ogre3DUIRenderQueue::RenderablePass t = mRenderableList[i];
						if (t.renderable == NULL)
							continue;
		
					}		
	
					initRenderStates();
				}
				break;
			case RT_COMMON:
				{
					d_render_op.vertexData->vertexStart = tempAssert->mStartIndex;
					size_t j = i+1;
					while(j < elementnumber  
						&& renderassert[j]->mType == RT_COMMON 
						&& renderassert[j]->mCommonQuadInfo.texture == renderassert[i]->mCommonQuadInfo.texture)
					{
						i++; j++;
					}
					d_render_op.vertexData->vertexCount = renderassert[i]->mEndIndex - d_render_op.vertexData->vertexStart;

					const OgreCEGUITexture* currTexture = (const OgreCEGUITexture*)renderassert[i]->mCommonQuadInfo.texture->getTexture();
					
				
				}
				break;

			case RT_TRI:
				{

					d_render_op.vertexData->vertexStart = tempAssert->mStartIndex;
					size_t j = i+1;
					while(j < elementnumber  
						&& renderassert[j]->mType == RT_TRI 
						&& renderassert[j]->mTriangleInfo.texture == renderassert[i]->mTriangleInfo.texture)
					{
						i++; j++;
					}
					d_render_op.vertexData->vertexCount = renderassert[i]->mEndIndex - d_render_op.vertexData->vertexStart;

					const OgreCEGUITexture* currTexture = (const OgreCEGUITexture*)renderassert[i]->mTriangleInfo.texture->getTexture();
					
				}
				break;
			case RT_MINIMAP:
				{

					initRenderStates();
				}
				break;
			case RT_CUSTOM:
				break;
			default:
				break;
			}
		}
	}
}

void OgreCEGUIRenderer::preparePrimitiveForRender()
{
	if(mMinimapElementNumber)
		resize3DRenderOp(d_3D_render_op,d_3D_buffer,mMinimapElementNumber*VERTEX_PER_QUAD);
	if(mCommonElementVertexNumber)
		resizeQuadRenderOp(d_render_op,d_buffer,mCommonElementVertexNumber);
	size_t elementnumber = mQuads.size();
	RenderAsserts **renderassert = mQuads.data();

	size_t customindex = 0;
	float *custommen = (float *)d_3D_buffer->lock(Ogre::HardwareVertexBuffer::HBL_DISCARD);

	size_t commonindex = 0;
	QuadVertex*	 commonmem = (QuadVertex*)d_buffer->lock(Ogre::HardwareVertexBuffer::HBL_DISCARD);
	
	for(size_t i=0; i<elementnumber; i++)
	{
		RenderAsserts *tempasserts = renderassert[i];
		switch(tempasserts->mType)
		{
		case RT_MINIMAP:
			{
				UI_TRY
				Quad3DInfo *info = &(tempasserts->mMinimapQuad3DInfo);
				tempasserts->mStartIndex = customindex;

				
				*custommen++ = info->mVertexRect.d_left;
				*custommen++ = info->mVertexRect.d_bottom;
				*custommen++ = -0.5f;

				*custommen++ = info->mCoordRect.d_left;
				*custommen++ = info->mCoordRect.d_bottom;
				*custommen++ = info->mAlphaRect.d_left;
				*custommen++ = info->mAlphaRect.d_bottom;
				++customindex;

				
				*custommen++ = info->mVertexRect.d_right;
				*custommen++ = info->mVertexRect.d_bottom;
				*custommen++ = -0.5f;
				
				

				*custommen++ = info->mCoordRect.d_right;
				*custommen++ = info->mCoordRect.d_bottom;
				*custommen++ = info->mAlphaRect.d_right;
				*custommen++ = info->mAlphaRect.d_bottom;
				++customindex;

				
				*custommen++ = info->mVertexRect.d_left;
				*custommen++ = info->mVertexRect.d_top;
				*custommen++ = -0.5f;
				
				

				*custommen++ = info->mCoordRect.d_left;
				*custommen++ = info->mCoordRect.d_top;
				*custommen++ = info->mAlphaRect.d_left;
				*custommen++ = info->mAlphaRect.d_top;
				++customindex;

				
				*custommen++ = info->mVertexRect.d_right;
				*custommen++ = info->mVertexRect.d_bottom;
				*custommen++ = -0.5f;
				
				

				*custommen++ = info->mCoordRect.d_right;
				*custommen++ = info->mCoordRect.d_bottom;
				*custommen++ = info->mAlphaRect.d_right;
				*custommen++ = info->mAlphaRect.d_bottom;
				++customindex;

				
				*custommen++ = info->mVertexRect.d_right;
				*custommen++ = info->mVertexRect.d_top;
				*custommen++ = -0.5f;
				
				

				*custommen++ = info->mCoordRect.d_right;
				*custommen++ = info->mCoordRect.d_top;
				*custommen++ = info->mAlphaRect.d_right;
				*custommen++ = info->mAlphaRect.d_top;
				++customindex;

				
				*custommen++ = info->mVertexRect.d_left;
				*custommen++ = info->mVertexRect.d_top;
				*custommen++ = -0.5f;
				
				

				*custommen++ = info->mCoordRect.d_left;
				*custommen++ = info->mCoordRect.d_top;
				*custommen++ = info->mAlphaRect.d_left;
				*custommen++ = info->mAlphaRect.d_top;
				++customindex;
				tempasserts->mEndIndex = customindex;
				UI_CATCH( "RT_MINIMAP --OgreCEGUIRenderer::preparePrimitiveForRender" )
			}
			break;
		case RT_COMMON:
			{
				UI_TRY
				QuadInfo *quad = &(tempasserts->mCommonQuadInfo);
				tempasserts->mStartIndex = commonindex;

				
				commonmem->x = quad->position.d_left;
				commonmem->y = quad->position.d_bottom;
				commonmem->z = tempasserts->z;
				commonmem->diffuse = quad->topLeftCol;
				commonmem->tu1 = quad->texPosition.d_left;
				commonmem->tv1 = quad->texPosition.d_bottom;
				++commonmem;

				
				commonmem->x = quad->position.d_right;
				commonmem->y = quad->position.d_top;
				commonmem->z = tempasserts->z;
				commonmem->diffuse = quad->bottomRightCol;
				commonmem->tu1 = quad->texPosition.d_right;
				commonmem->tv1 = quad->texPosition.d_top;
				++commonmem;

				
				commonmem->x = quad->position.d_left;
				commonmem->y = quad->position.d_top;
				commonmem->z = tempasserts->z;
				commonmem->diffuse = quad->bottomLeftCol;
				commonmem->tu1 = quad->texPosition.d_left;
				commonmem->tv1 = quad->texPosition.d_top;
				++commonmem;

				
				commonmem->x = quad->position.d_right;
				commonmem->y = quad->position.d_bottom;
				commonmem->z = tempasserts->z;
				commonmem->diffuse = quad->topRightCol;
				commonmem->tu1 = quad->texPosition.d_right;
				commonmem->tv1 = quad->texPosition.d_bottom;
				++commonmem;

				
				commonmem->x = quad->position.d_right;
				commonmem->y = quad->position.d_top;
				commonmem->z = tempasserts->z;
				commonmem->diffuse = quad->bottomRightCol;
				commonmem->tu1 = quad->texPosition.d_right;
				commonmem->tv1 = quad->texPosition.d_top;
				++commonmem;

				
				commonmem->x = quad->position.d_left;
				commonmem->y = quad->position.d_bottom;
				commonmem->z = tempasserts->z;
				commonmem->diffuse = quad->topLeftCol;
				commonmem->tu1 = quad->texPosition.d_left;
				commonmem->tv1 = quad->texPosition.d_bottom;
				++commonmem;

				commonindex += VERTEX_PER_QUAD;
				tempasserts->mEndIndex = commonindex;
				UI_CATCH( "RT_COMMON --OgreCEGUIRenderer::preparePrimitiveForRender" )
			}
			break;

		case RT_TRI:
			{
				UI_TRY
				TriangleInfo *tri = &(tempasserts->mTriangleInfo);
				tempasserts->mStartIndex = commonindex;

				
				commonmem->x = tri->pt[0].d_x;
				commonmem->y = tri->pt[0].d_y;
				commonmem->z = tempasserts->z;
				commonmem->diffuse = tri->diffuse;
				commonmem->tu1 = tri->uv[0].d_x;
				commonmem->tv1 = tri->uv[0].d_y;
				++commonmem;

				
				commonmem->x = tri->pt[1].d_x;
				commonmem->y = tri->pt[1].d_y;
				commonmem->z = tempasserts->z;
				commonmem->diffuse = tri->diffuse;
				commonmem->tu1 = tri->uv[1].d_x;
				commonmem->tv1 = tri->uv[1].d_y;
				++commonmem;

				
				commonmem->x = tri->pt[2].d_x;
				commonmem->y = tri->pt[2].d_y;
				commonmem->z = tempasserts->z;
				commonmem->diffuse = tri->diffuse;
				commonmem->tu1 = tri->uv[2].d_x;
				commonmem->tv1 = tri->uv[2].d_y;
				++commonmem;

				commonindex += VERTEX_PER_TRIANGLE;
				tempasserts->mEndIndex = commonindex;
				UI_CATCH( "RT_TRI --OgreCEGUIRenderer::preparePrimitiveForRender" )
			}
			break;

		case RT_SCENE:
			{
				UI3DWindowInfo *info = &(tempasserts->m3DWindowInfo);
				Ogre3DUIWindow *window = 0;
				void *logicmodel = 0;
				Ogre::Camera *camera = 0;

				UI_TRY				

				info->mCamera = 0;
				tempasserts->mStartIndex = mRenderableList.size();
				tempasserts->mEndIndex = mRenderableList.size();

				UI_CATCH( "RT_SCENE1 --OgreCEGUIRenderer::preparePrimitiveForRender" )				
				UI_TRY
				if (info == NULL)
				{
					break;
				}
				window = info->mWindow;
				
				if (window == NULL)
					break;

				if(!mGetMovableList || !window->getLogicModelObjPointer() || !window->getCameraPointer())
					break;			

				
				camera = static_cast<Ogre::Camera *>(window->getCameraPointer());
				if (camera == NULL)
					break;
				
				UI_CATCH( "RT_SCENE2 --OgreCEGUIRenderer::preparePrimitiveForRender" )				
				UI_TRY

				logicmodel = window->getLogicModelObjPointer();

				if(camera && logicmodel)
				{
					tempasserts->mStartIndex = mRenderableList.size();
					mGetMovableList(logicmodel,&mOgre3DUIRenderQueue);
					tempasserts->mEndIndex = mRenderableList.size();
					info->mCamera = camera;
				}
				UI_CATCH( "RT_SCENE3 --OgreCEGUIRenderer::preparePrimitiveForRender" )
			}
			break;
		case RT_NODE:
			{
				UI_TRY
				UI3DWindowInfo *info = &(tempasserts->m3DWindowInfo);

				Ogre3DUIWindow *window = info->mWindow;
				String objectname = window->getSceneObjectName();
				String movabletype = window->getMovableType();
				String movableresourcename = window->getMovableResourceName();
				if(!d_sceneMngr->hasMovableObject(objectname.c_str(), movabletype.c_str()))
				{
					
					if(movabletype == "Entity")
					{
						Ogre::Entity *e = d_sceneMngr->createEntity(objectname.c_str(),movableresourcename.c_str());
						e->setVisibilityFlags(OGRE3DWINDOWVISIBLAFLAG);
						mOgre3DUINode->attachObject(e);
					}
					else if(movabletype == "ParticleSystem")
					{
						Ogre::ParticleSystem *ps = d_sceneMngr->createParticleSystem(objectname.c_str(),movableresourcename.c_str());
						ps->setVisibilityFlags(OGRE3DWINDOWVISIBLAFLAG);
						mOgre3DUINode->attachObject(ps);
						break;
					}
				}
				Ogre::MoveObject*object = d_sceneMngr->createMovableObject(objectname.c_str(), movabletype.c_str(), nullptr);
				tempasserts->mStartIndex = mRenderableList.size();
				//object->_updateRenderQueue(&mOgre3DUIRenderQueue);
				tempasserts->mEndIndex = mRenderableList.size();
				info->mAABBBox = object->getBoundingBox();
				UI_CATCH( "RT_NODE --OgreCEGUIRenderer::preparePrimitiveForRender" )
			}
			break;
		default:
			break;
		}
	}

	d_buffer->unlock();
	d_3D_buffer->unlock();
}

void OgreCEGUIRenderer::initMinimapRender(const String&backgroundname, const String &alphaname, const size_t size)
{	
	try
	{
		Ogre::TextureManager& textureManager = Ogre::TextureManager::getSingleton();
		Ogre::TexturePtr ogreTexture = (Ogre::TexturePtr)textureManager.getByName(alphaname.c_str());

		if (ogreTexture)
		{
			d_pAlphaTexture = ogreTexture;
		}
		else
		{
			d_pAlphaTexture = Ogre::TextureManager::getSingleton().load(alphaname.c_str(), nullptr);
		}

	}
	catch(Ogre::Exception e)
	{
		throw RendererException((utf8*)"Failed to create Texture object from file '" + alphaname + "'. Additional Information:\n" + e.getFullDescription().c_str());
	}
	createMinimapMaterial();

}

void OgreCEGUIRenderer::destroyMinimapRender(void)
{
	 

}

void OgreCEGUIRenderer::setGetMovableList(GetMovableList fun)
{
	assert(!mGetMovableList && fun);
	mGetMovableList = fun;
}

void OgreCEGUIRenderer::setLogicModelPosition(callbackSetLogicModelPosition fun)
{
	assert(!mLogicModelPosition && fun);
	mLogicModelPosition = fun;
}

void OgreCEGUIRenderer::Register3DWindowFactory()
{

	WindowFactoryManager& wfm = WindowFactoryManager::getSingleton();
	if (wfm.isFactoryPresent(g3DFactory.getTypeName()))
	{
		Logger::getSingleton().logEvent("Falagard widget factory '" + g3DFactory.getTypeName() + "' appears to be already registered, skipping.",Informative);
	}
	else
	{
		wfm.addFactory(&g3DFactory);
	}
}
void OgreCEGUIRenderer::init3DRender()
{
	
	create3DRenderOp(d_3D_render_op, d_3D_buffer, OGRE3DBUFFERSIZE);
}
void OgreCEGUIRenderer::destroy3DRender()
{
	
	
}
void OgreCEGUIRenderer::restore3DRenderState()
{
	
}

void OgreCEGUIRenderer::clearRenderList(void)
{
	d_sorted = true;

	mOgre3DUIWindowMap.clear();
	mRenderAssertsMap.clear();
	mRenderableList.clear();
	mCommonElementVertexNumber = 0;
	mMinimapElementNumber = 0;
}

Texture* OgreCEGUIRenderer::createTexture(void)
{
	OgreCEGUITexture* tex = new OgreCEGUITexture(this);
	d_texturelist.push_back(tex);
	return tex;
}

Texture* OgreCEGUIRenderer::createTexture(const String& filename, const String& resourceGroup)
{
	OgreCEGUITexture* tex = (OgreCEGUITexture*)createTexture();
	tex->loadFromFile(filename, resourceGroup);

	return tex;
}

Texture* OgreCEGUIRenderer::createTexture(float size)
{
	OgreCEGUITexture* tex = (OgreCEGUITexture*)createTexture();
	tex->setOgreTextureSize((uint)size);

	return tex;
}

void OgreCEGUIRenderer::destroyTexture(Texture* texture)
{
	if (texture != NULL)
	{
		OgreCEGUITexture* tex = (OgreCEGUITexture*)texture;

		d_texturelist.remove(tex);
		delete tex;
	}
}

void OgreCEGUIRenderer::destroyAllTextures(void)
{
	while (!d_texturelist.empty())
	{
		destroyTexture(*(d_texturelist.begin()));
	}
}

void OgreCEGUIRenderer::initRenderStates(void)
{
}

void OgreCEGUIRenderer::sortQuads(void)
{
	if (!d_sorted)
	{
		d_sorted = true;
	}
}



uint32 OgreCEGUIRenderer::colourToOgre(const colour& col) const
{
	Ogre::ColourValue cv(col.getRed(), col.getGreen(), col.getBlue(), col.getAlpha());

    uint32 final = cv.getAsBYTE();

	return final;
}

void OgreCEGUIRenderer::setTargetSceneManager(Ogre::SceneManager* scene_manager)
{	
	if (d_sceneMngr != NULL)
	{
		d_sceneMngr = NULL;
	}
	
	if (scene_manager != NULL)
	{
		d_sceneMngr = scene_manager;

		mOgre3DUINode = d_sceneMngr->getRoot()->createChildSceneNode("CEGUINode");

		m3DUIObjectCamera = d_sceneMngr->createCamera("Iam3dUI");
	}
}

void OgreCEGUIRenderer::setTargetRenderQueue(uint32_t queue_id, bool post_queue)
{
	d_queue_id		= queue_id;
	d_post_queue	= post_queue;

	if (d_ourlistener != NULL)
	{
		d_ourlistener->setTargetRenderQueue(queue_id);
		d_ourlistener->setPostRenderQueue(post_queue);
	}
}

void OgreCEGUIRenderer::constructor_impl(Ogre::RenderTarget* target, uint32_t queue_id, bool post_queue, uint max_quads)
{
	using namespace Ogre;
	
	d_queueing		= true;
	d_queue_id		= queue_id;
	d_post_queue	= post_queue;
	d_sceneMngr		= NULL;
	d_bufferPos		= 0;
	d_sorted		= true;
	d_ogre_root		= Root::getSingletonPtr();
	d_render_sys	= d_ogre_root->getRenderSystem();
	d_render_target = target;
    
    d_identifierString = "CEGUI::OgreRenderer - Official Ogre based renderer module for CEGUI";

    createQuadRenderOp(d_render_op, d_buffer, VERTEXBUFFER_INITIAL_CAPACITY);
    d_underused_framecount = 0;

    
    createQuadRenderOp(d_direct_render_op, d_direct_buffer, VERTEX_PER_QUAD);
	init3DRender();

	d_display_area.d_left	= 0;
	d_display_area.d_top	= 0;
	d_display_area.d_right	= target->getWidth();
	d_display_area.d_bottom	= target->getHeight();

	d_old_display_area.d_bottom = 0;
	d_old_display_area.d_left = 0;
	d_old_display_area.d_right = 0;
	d_old_display_area.d_top = 0;

	
	d_texelOffset = Point((float)0.0f, -(float)0.0f);

	d_ourlistener = new CEGUIRQListener(this, queue_id, post_queue);

	
	d_colourBlendMode.blendType	= Ogre::LBT_COLOUR;
	d_colourBlendMode.source1	= Ogre::LBS_TEXTURE;
	d_colourBlendMode.source2	= Ogre::LBS_DIFFUSE;
	d_colourBlendMode.operation	= Ogre::LBX_MODULATE;

	d_alphaBlendMode.blendType	= Ogre::LBT_ALPHA;
	d_alphaBlendMode.source1	= Ogre::LBS_TEXTURE;
	d_alphaBlendMode.source2	= Ogre::LBS_DIFFUSE;
	d_alphaBlendMode.operation	= Ogre::LBX_MODULATE;

	d_uid_counter = 0;
	d_renderDisable = false;

	
	mGetMovableList = 0;
	mLogicModelPosition = 0;
	
}

void OgreCEGUIRenderer::_notifySizeChanged(void)
{
	Rect display_area;

	
	display_area.d_left		= 0;
	display_area.d_top		= 0;
	display_area.d_right	= d_render_target->getWidth();
	display_area.d_bottom	= d_render_target->getHeight();

	if (d_display_area != display_area)
	{
        
		d_old_display_area = d_display_area;
		d_display_area = display_area;

		EventArgs args;
		fireEvent(EventDisplaySizeChanged, args, EventNamespace);
	    
	    System::getSingleton().signalRedraw();
	}
}

Texture* OgreCEGUIRenderer::createTexture(Ogre::TexturePtr& texture)
{
	OgreCEGUITexture* t = (OgreCEGUITexture*)createTexture();

	if (texture)
	{
		t->setOgreTexture(texture);
	}

	return t;
}

ResourceProvider* OgreCEGUIRenderer::createResourceProvider(void)
{
    d_resourceProvider = new OgreCEGUIResourceProvider();
    return d_resourceProvider;
}

void OgreCEGUIRenderer::setDisplaySize(const Size& sz)
{
	if (d_display_area.getSize() != sz)
	{		
		d_old_display_area = d_display_area;
		d_display_area.setSize(sz);

		EventArgs args;
		fireEvent(EventDisplaySizeChanged, args, EventNamespace);
	}
}

bool OgreCEGUIRenderer::isRenderDisable( void ) const
{
	return d_renderDisable;
}

void OgreCEGUIRenderer::setRenderDisable( bool bDisable )
{
	d_renderDisable = bDisable;
}

void CEGUIRQListener::renderQueueStarted(uint32_t id, const Ogre::String& invocation, 
										 bool& skipThisQueue)
{
	try
	{
		if ((!d_post_queue) && (d_queue_id == id) &&
			d_renderer->d_render_sys->_getViewport() &&
			d_renderer->d_render_sys->_getViewport()->getTarget() == d_renderer->d_render_target)
		{
			CEGUI::System::getSingleton().renderGUI();
		}
	}
	catch(...)
	{
		Logger::getSingleton().logEvent("CEGUIRQListener::renderQueueStarted failed.", Errors);
		throw;
	}
}

void CEGUIRQListener::renderQueueEnded(uint32_t id, const Ogre::String& invocation, bool& repeatThisQueue)
{
	try
	{
		if ((d_post_queue) && (d_queue_id == id) &&
			d_renderer->d_render_sys->_getViewport() &&
			d_renderer->d_render_sys->_getViewport()->getTarget() == d_renderer->d_render_target)
		{
			CEGUI::System::getSingleton().renderGUI();
		}
	}
	catch(...)
	{
		Logger::getSingleton().logEvent("CEGUIRQListener::renderQueueEnded failed.", Errors);
		throw;
	}
}

}
