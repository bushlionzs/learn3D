/***********************************************************************
    created:    Tue Feb 17 2009
    author:     Paul D Turner
*************************************************************************/
/***************************************************************************
 *   Copyright (C) 2004 - 2013 Paul D Turner & The CEGUI Development Team
 *
 *   Permission is hereby granted, free of charge, to any person obtaining
 *   a copy of this software and associated documentation files (the
 *   "Software"), to deal in the Software without restriction, including
 *   without limitation the rights to use, copy, modify, merge, publish,
 *   distribute, sublicense, and/or sell copies of the Software, and to
 *   permit persons to whom the Software is furnished to do so, subject to
 *   the following conditions:
 *
 *   The above copyright notice and this permission notice shall be
 *   included in all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 *   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 *   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 *   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 *   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 *   OTHER DEALINGS IN THE SOFTWARE.
 ***************************************************************************/
#include "CEGUI/RendererModules/Ogre/GeometryBuffer.h"
#include "CEGUI/RendererModules/Ogre/Texture.h"
#include "CEGUI/Vertex.h"
#include "CEGUI/RenderEffect.h"

#include <RenderSystem.h>
#include <OgreQuaternion.h>
#include <OgreHardwareBufferManager.h>
#include <vertex_declaration.h>
#include <OgreMaterial.h>
#include <OgreTextureUnit.h>
#include <CEGUIManager.h>

// Start of CEGUI namespace section
namespace CEGUI
{


    CEGUIRenderable::CEGUIRenderable(OgreGeometryBuffer* owner)
    {
        _owner = owner;
        mMaterial = std::make_shared<Ogre::Material>("CEGUI");
        mMaterial->addTexture("white1x1.dds", nullptr);
        ShaderInfo sInfo;
        sInfo.shaderName = "cegui";
        mMaterial->addShader(sInfo);
        Ogre::ColourBlendState mBlendState;
        mBlendState.sourceFactor = Ogre::SBF_SOURCE_ALPHA;
        mBlendState.destFactor = Ogre::SBF_ONE_MINUS_SOURCE_ALPHA;
        mBlendState.sourceFactorAlpha = Ogre::SBF_SOURCE_ALPHA;
        mBlendState.destFactorAlpha = Ogre::SBF_ONE_MINUS_SOURCE_ALPHA;

        mBlendState.sourceFactor = Ogre::SBF_SOURCE_ALPHA;
        mBlendState.destFactor = Ogre::SBF_ONE_MINUS_SOURCE_ALPHA;
        mBlendState.sourceFactorAlpha = Ogre::SBF_ONE_MINUS_SOURCE_ALPHA;
        mBlendState.destFactorAlpha = Ogre::SBF_ONE;
        mMaterial->setBlendState(mBlendState);
        mMaterial->setWriteDepth(false);
        mMaterial->setDepthTest(false);
        mMaterial->setCullMode(Ogre::CULL_NONE);
        mMaterial->load();
    }

    VertexData* CEGUIRenderable::getVertexData()
    {
        return _owner->getVertexData();
    }

    const Ogre::Matrix4& CEGUIRenderable::getModelMatrix()
    {
        return _owner->getModelMatrix();
    }

    void CEGUIRenderable::updateRenderable(uint32_t vertexStart, uint32_t vertexCount, const Ogre::TexturePtr& tex)
    {
        _rd_view.mVertexStart = vertexStart;
        _rd_view.mVertexCount = vertexCount;
        auto& tu = mMaterial->getTextureUnit(0);
        tu->setTexture(0, tex);
    }

//----------------------------------------------------------------------------//
// Helper to allocate a vertex buffer and initialse a Ogre::RenderOperation
static void initialiseRenderOp(
    Ogre::RenderOperation& rop,
    Ogre::HardwareVertexBufferSharedPtr& vb,
    size_t count)
{
    using namespace Ogre;


    
}

//----------------------------------------------------------------------------//
// Helper to cleanup what initialiseRenderOp did.
static void cleanupRenderOp(
        Ogre::RenderOperation& rop,
        Ogre::HardwareVertexBufferSharedPtr& vb
    )
{
    OGRE_DELETE rop.vertexData;
    rop.vertexData = 0;
    vb.reset();
}

//----------------------------------------------------------------------------//
OgreGeometryBuffer::OgreGeometryBuffer(OgreRenderer& owner,
                                       RenderSystem& rs) :
    d_owner(owner),
    d_renderSystem(rs),
    d_activeTexture(0),
    d_clipRect(0, 0, 0, 0),
    d_clippingActive(true),
    d_translation(0, 0, 0),
    d_rotation(Quaternion::IDENTITY),
    d_pivot(0, 0, 0),
    d_effect(0),
    d_texelOffset(0.0f, 0.0f),//zhousha
    d_matrixValid(false),
    d_sync(false)
{

    // basic initialisation of render op
    d_renderOp.vertexData = OGRE_NEW VertexData();
    d_renderOp.operationType = RenderOperation::OT_TRIANGLE_LIST;
    d_renderOp.useIndexes = false;

    // setup vertex declaration for format we will use
    VertexDeclaration* vd = d_renderOp.vertexData->vertexDeclaration;
    size_t vd_offset = 0;
    vd->addElement(0, 0, vd_offset, VET_FLOAT3, VES_POSITION);
    vd_offset += VertexElement::getTypeSize(VET_FLOAT3);
    
    vd->addElement(0, 0, vd_offset, VET_FLOAT4, VES_DIFFUSE);
    vd_offset += VertexElement::getTypeSize(VET_FLOAT4);
    vd->addElement(0, 0, vd_offset, VET_FLOAT2, VES_TEXTURE_COORDINATES);

    auto vertexSize = vd->getVertexSize(0);

    d_renderOp.vertexData->vertexSlotInfo.emplace_back();

    auto& back = d_renderOp.vertexData->vertexSlotInfo.back();

    back.mSlot = 0;
    back.mVertexSize = vertexSize;
    back.createBuffer(vertexSize, 2048);
}

//----------------------------------------------------------------------------//
OgreGeometryBuffer::~OgreGeometryBuffer()
{
  
}

VertexData* OgreGeometryBuffer::getVertexData()
{
    return d_renderOp.vertexData;
}

IndexData* OgreGeometryBuffer::getIndexData()
{
    return nullptr;
}

IndexDataView* OgreGeometryBuffer::getIndexView()
{
    return nullptr;
}

const Ogre::Matrix4& OgreGeometryBuffer::getModelMatrix()
{
    return this->getMatrix();
    static Ogre::Matrix4 aa = Ogre::Matrix4::IDENTITY;
    return aa;
}

//----------------------------------------------------------------------------//
void OgreGeometryBuffer::draw() const
{
    if (!d_sync)
        syncHardwareBuffer();


    const int pass_count = d_effect ? d_effect->getPassCount() : 1;
    uint32_t index = 0;
    for (int pass = 0; pass < pass_count; ++pass)
    {
        // set up RenderEffect
        if (d_effect)
            d_effect->performPreRenderFunctions(pass);

        // draw the batches
        size_t pos = 0;
        BatchList::const_iterator i = d_batches.begin();
        for ( ; i != d_batches.end(); ++i)
        {
            // Set up clipping for this buffer


            d_renderOp.vertexData->vertexStart = pos;
            d_renderOp.vertexData->vertexCount = i->vertexCount;

 
            updateRenderable(index++, pos, i->vertexCount, i->texture);


            if (i->vertexCount == 54)
            {
                int kk = 0;
            }

            pos += i->vertexCount;
            
        }
    }


    // clean up RenderEffect
    if (d_effect)
        d_effect->performPostRenderFunctions();


    for (auto i = 0; i < index; i++)
    {
        CEGUIManager::getSingleton().addRenderable((Ogre::Renderable*)d_Renderables[i]);
    }


    
}

//----------------------------------------------------------------------------//
void OgreGeometryBuffer::setTranslation(const Vector3f& v)
{
    d_translation = v;
    d_matrixValid = false;
}

//----------------------------------------------------------------------------//
void OgreGeometryBuffer::setRotation(const Quaternion& r)
{
    d_rotation = r;
    d_matrixValid = false;
}

//----------------------------------------------------------------------------//
void OgreGeometryBuffer::setPivot(const Vector3f& p)
{
    d_pivot = p;
    d_matrixValid = false;
}

//----------------------------------------------------------------------------//
void OgreGeometryBuffer::setClippingRegion(const Rectf& region)
{
    d_clipRect.top(ceguimax(0.0f, region.top()));
    d_clipRect.bottom(ceguimax(0.0f, region.bottom()));
    d_clipRect.left(ceguimax(0.0f, region.left()));
    d_clipRect.right(ceguimax(0.0f, region.right()));
}

//----------------------------------------------------------------------------//
void OgreGeometryBuffer::appendVertex(const Vertex& vertex)
{
    appendGeometry(&vertex, 1);
}

//----------------------------------------------------------------------------//
void OgreGeometryBuffer::appendGeometry(const Vertex* const vbuff,
                                        uint vertex_count)
{
    // see if we should start a new batch
    Ogre::TexturePtr t;
    if (d_activeTexture)
        t = d_activeTexture->getOgreTexture();

    if (d_batches.empty() ||
        d_batches.back().texture != t ||
        d_batches.back().clip != d_clippingActive)
    {
        const BatchInfo batch = {t, 0, d_clippingActive};
        d_batches.push_back(batch);
    }

    // update size of current batch
    d_batches.back().vertexCount += vertex_count;

    // buffer these vertices
    OgreVertex v;
    for (uint i = 0; i < vertex_count; ++i)
    {
        const Vertex& vs = vbuff[i];
        // convert from CEGUI::Vertex to something directly usable by Ogre.
        v.x       = vs.position.d_x + d_texelOffset.d_x;
        v.y       = vs.position.d_y + d_texelOffset.d_y;
        v.z       = vs.position.d_z;
        v.colour[0] = vs.colour_val.getRed();
        v.colour[1] = vs.colour_val.getGreen();
        v.colour[2] = vs.colour_val.getBlue();
        v.colour[3] = vs.colour_val.getAlpha();

        v.u       = vs.tex_coords.d_x;
        v.v       = vs.tex_coords.d_y;

        d_vertices.push_back(v);
    }

    d_sync = false;
}

//----------------------------------------------------------------------------//
void OgreGeometryBuffer::setActiveTexture(Texture* texture)
{
    d_activeTexture = static_cast<OgreTexture*>(texture);
}

//----------------------------------------------------------------------------//
void OgreGeometryBuffer::reset()
{
    d_vertices.clear();
    d_batches.clear();
    d_activeTexture = 0;
    d_sync = false;
}

//----------------------------------------------------------------------------//
Texture* OgreGeometryBuffer::getActiveTexture() const
{
    return d_activeTexture;
}

//----------------------------------------------------------------------------//
uint OgreGeometryBuffer::getVertexCount() const
{
    return d_vertices.size();
}

//----------------------------------------------------------------------------//
uint OgreGeometryBuffer::getBatchCount() const
{
    return d_batches.size();
}

//----------------------------------------------------------------------------//
void OgreGeometryBuffer::setRenderEffect(RenderEffect* effect)
{
    d_effect = effect;
}

//----------------------------------------------------------------------------//
RenderEffect* OgreGeometryBuffer::getRenderEffect()
{
    return d_effect;
}

//----------------------------------------------------------------------------//
Ogre::RGBA OgreGeometryBuffer::colourToOgre(const Colour& col) const
{
    Ogre::ColourValue ocv(col.getRed(),
                          col.getGreen(),
                          col.getBlue(),
                          col.getAlpha());

    uint32 final ;
    
    Ogre::ColourValue v(col.getRed(), col.getGreen(), col.getBlue(), col.getAlpha());
    final = v.getAsBYTE();

    return final;
}

//----------------------------------------------------------------------------//
void OgreGeometryBuffer::updateMatrix() const
{
    // translation to position geometry and offset to pivot point
    Ogre::Matrix4 trans;
    trans.makeTrans(d_translation.d_x + d_pivot.d_x,
                    d_translation.d_y + d_pivot.d_y,
                    d_translation.d_z + d_pivot.d_z);

    // rotation
    Ogre::Matrix4 rot(Ogre::Quaternion(
        d_rotation.d_w, d_rotation.d_x, d_rotation.d_y, d_rotation.d_z));

    // translation to remove rotation pivot offset
    Ogre::Matrix4 inv_pivot_trans;
    inv_pivot_trans.makeTrans(-d_pivot.d_x, -d_pivot.d_y, -d_pivot.d_z);

    // calculate final matrix
    d_matrix = trans * rot * inv_pivot_trans;

    d_matrixValid = true;
}

//----------------------------------------------------------------------------//
void OgreGeometryBuffer::syncHardwareBuffer() const
{
    // Reallocate h/w buffer as requied
    auto hwBuffer = d_renderOp.vertexData->getBuffer(0);
    size_t size = hwBuffer->getNumVerts();
    const size_t required_size = d_vertices.size();
    if(size < required_size)
    {
        // calculate new size to use
        while(size < required_size)
            size *= 2;

    }

    // copy vertex data into hw buffer
    if (required_size > 0)
    {
        std::memcpy(hwBuffer->lock(Ogre::HardwareVertexBuffer::HBL_DISCARD),
                    &d_vertices[0], sizeof(OgreVertex) * d_vertices.size());
        hwBuffer->unlock();

        
    }

    d_sync = true;
}

//----------------------------------------------------------------------------//
const Ogre::Matrix4& OgreGeometryBuffer::getMatrix() const
{
    if (!d_matrixValid)
        updateMatrix();

    return d_matrix;
}

//----------------------------------------------------------------------------//
void OgreGeometryBuffer::initialiseTextureStates() const
{

}

void OgreGeometryBuffer::updateRenderable(uint32_t index, uint32_t vertexStart, uint32_t vertexCount, const Ogre::TexturePtr& tex) const
{
    CEGUIRenderable* r = nullptr;
    if (index >= d_Renderables.size())
    {
        r = new CEGUIRenderable((OgreGeometryBuffer*)this);
        d_Renderables.push_back(r);
    }
    else
    {
        r = d_Renderables[index];
    }

    r->updateRenderable(vertexStart, vertexCount, tex);
}

//----------------------------------------------------------------------------//
void OgreGeometryBuffer::setClippingActive(const bool active)
{
    d_clippingActive = active;
}

//----------------------------------------------------------------------------//
bool OgreGeometryBuffer::isClippingActive() const
{
    return d_clippingActive;
}

//----------------------------------------------------------------------------//

} // End of  CEGUI namespace section
