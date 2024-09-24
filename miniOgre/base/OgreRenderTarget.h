/*
-----------------------------------------------------------------------------
This source file is part of OGRE
    (Object-oriented Graphics Rendering Engine)
For the latest info, see http://www.ogre3d.org/

Copyright (c) 2000-2014 Torus Knot Software Ltd

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
-----------------------------------------------------------------------------
*/
#ifndef __RenderTarget_H__
#define __RenderTarget_H__

#include "OgrePixelFormat.h"


/* Define the number of priority groups for the render system's render targets. */
#ifndef OGRE_NUM_RENDERTARGET_GROUPS
    #define OGRE_NUM_RENDERTARGET_GROUPS 10
    #define OGRE_DEFAULT_RT_GROUP 4
    #define OGRE_REND_TO_TEX_RT_GROUP 2
#endif

namespace Ogre {

    /** \addtogroup Core
    *  @{
    */
    /** \addtogroup RenderSystem
    *  @{
    */
    /** A 'canvas' which can receive the results of a rendering
        operation.
        @remarks
            This abstract class defines a common root to all targets of rendering operations. A
            render target could be a window on a screen, or another
            offscreen surface like a texture or bump map etc.
        @author
            Steven Streeting
        @version
            1.0
     */
    class  RenderTarget
    {
    public:
        struct FrameStats
        {
            /// frames per second (FPS) based on the frames rendered in the last second
            float lastFPS;
            /// average frames per second (FPS) since call to Root::startRendering
            float avgFPS;
            /// best frames per second (FPS) since call to Root::startRendering
            float bestFPS;
            /// worst frames per second (FPS) since call to Root::startRendering
            float worstFPS;
            unsigned long bestFrameTime;
            unsigned long worstFrameTime;
            /// number of triangles rendered in the last update() call.
            size_t triangleCount;
            /// number of batches rendered in the last update() call.
            size_t batchCount;
            int vBlankMissCount; // -1 means that the value is not applicable
        };

        enum FrameBuffer:uint8_t
        {
            FB_FRONT,
            FB_BACK,
            FB_AUTO
        };

        RenderTarget();
        virtual ~RenderTarget();

        /// Retrieve target's name.
        virtual const String& getName(void) const;


        virtual uint32 getWidth(void) const;
        virtual uint32 getHeight(void) const;

        
        virtual void swapBuffers() {}

        
        virtual Viewport* addViewport(Camera* cam, int ZOrder = 0, float left = 0.0f, float top = 0.0f,
            float width = 1.0f, float height = 1.0f) 
        {
            return nullptr;
        }

        
        virtual void _endUpdate() {}

        virtual void preRender(const ColourValue& colour)
        {
        }
        virtual void postRender()
        {
        }
    protected:
        /// The name of this target.
        String mName;
       

        uint32 mWidth;
        uint32 mHeight;
       

       
    };
    /** @} */
    /** @} */

} // Namespace


#endif
