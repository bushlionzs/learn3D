/*
-----------------------------------------------------------------------------
This source file is part of OGRE
    (Object-oriented Graphics Rendering Engine)
For the latest info, see http://www.ogre3d.org

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
#include "OgreHeader.h"
#include "OgreHardwarePixelBuffer.h"
#include "OgreImage.h"
#include "OgreRoot.h"
#include "OgreTexture.h"
//#include "OgreRenderTexture.h"

namespace Ogre 
{
  
    //-----------------------------------------------------------------------------    
    HardwarePixelBuffer::HardwarePixelBuffer(uint32 width, uint32 height, uint32 depth,
            PixelFormat format,
            HardwareBuffer::Usage usage, bool useSystemMemory, bool useShadowBuffer):
        HardwareBuffer(),
        mCurrentLockOptions(), mWidth(width), mHeight(height), mDepth(depth),
        mFormat(format)
    {
        // Default
        mRowPitch = mWidth;
        mSlicePitch = mHeight*mWidth;
        mSizeInBytes = PixelUtil::getMemorySize(mWidth, mHeight, mDepth, mFormat);
    }
    
    //-----------------------------------------------------------------------------    
    HardwarePixelBuffer::~HardwarePixelBuffer()
    {
        if (mUsage & TU_RENDERTARGET)
        {
            assert(false);
        }
    }
    
  
   

    //-----------------------------------------------------------------------------    

    void HardwarePixelBuffer::blit(const HardwarePixelBufferPtr&src, const Box &srcBox, const Box &dstBox)
    {
        
    }
    //-----------------------------------------------------------------------------       
    void HardwarePixelBuffer::blit(const HardwarePixelBufferPtr&src)
    {
        blit(src, Box(src->getSize()), Box(getSize()));
    }
    //-----------------------------------------------------------------------------    
    void HardwarePixelBuffer::readData(size_t offset, size_t length, void* pDest)
    {
        // allow easy full buffer reads
        if (offset == 0 && length == mSizeInBytes)
        {
            Box box(0, 0, 0, mWidth, mHeight, mDepth);
            blitToMemory(box, PixelBox(box, mFormat, pDest));
            return;
        }

        // TODO
        OGRE_EXCEPT(Exception::ERR_NOT_IMPLEMENTED,
                "Reading a byte range is not implemented. Use blitToMemory.",
                "HardwarePixelBuffer::readData");
    }
    //-----------------------------------------------------------------------------    

    void HardwarePixelBuffer::writeData(size_t offset, size_t length, const void* pSource,
            bool discardWholeBuffer)
    {
        // allow easy full buffer updates
        if (offset == 0 && length == mSizeInBytes)
        {
            Box box(0, 0, 0, mWidth, mHeight, mDepth);
            // we know pSource will not be written to
            blitFromMemory(PixelBox(box, mFormat, const_cast<void*>(pSource)), box);
            return;
        }

        // TODO
        OGRE_EXCEPT(Exception::ERR_NOT_IMPLEMENTED,
                "Writing a byte range is not implemented. Use blitFromMemory.",
                "HardwarePixelBuffer::writeData");
    }
    //-----------------------------------------------------------------------------    
    
    RenderTexture *HardwarePixelBuffer::getRenderTarget(size_t zoffset)
    {
        assert(mUsage & TU_RENDERTARGET);
        return mSliceTRT.at(zoffset);
    }
    //-----------------------------------------------------------------------------    

    void HardwarePixelBuffer::_clearSliceRTT(size_t zoffset)
    {
        if(zoffset < mSliceTRT.size())
            mSliceTRT[zoffset] = NULL;
    }

}
