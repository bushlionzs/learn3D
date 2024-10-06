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
#include "OgreHeader.h"
#include "OgreControllerManager.h"
#include "OgrePredefinedControllers.h"
#include "OgreRoot.h"

namespace Ogre {
    //-----------------------------------------------------------------------
    template<> ControllerManager* Singleton<ControllerManager>::msSingleton = 0;
    ControllerManager* ControllerManager::getSingletonPtr(void)
    {
        return msSingleton;
    }
    ControllerManager& ControllerManager::getSingleton(void)
    {  
        assert( msSingleton );  return ( *msSingleton );  
    }
    //-----------------------------------------------------------------------
    ControllerManager::ControllerManager()
        :mFrameTimeController(OGRE_NEW FrameTimeControllerValue()),
        mPassthroughFunction(OGRE_NEW PassthroughControllerFunction()),
        mLastFrameNumber(0)
    {

    }
    //-----------------------------------------------------------------------
    ControllerManager::~ControllerManager()
    {
        clearControllers();
    }
    //-----------------------------------------------------------------------
    ControllerReal* ControllerManager::createController(
        const ControllerValueRealPtr& src, const ControllerValueRealPtr& dest,
        const ControllerFunctionRealPtr& func)
    {
        ControllerReal* c = OGRE_NEW ControllerReal(src, dest, func);

        mControllers.insert(c);
        return c;
    }
    //-----------------------------------------------------------------------
    ControllerReal* ControllerManager::createFrameTimePassthroughController(
        const ControllerValueRealPtr& dest)
    {
        return createController(getFrameTimeSource(), dest, getPassthroughControllerFunction());
    }
    //-----------------------------------------------------------------------
    void ControllerManager::updateAllControllers(void)
    {
        // Only update once per frame
        unsigned long thisFrameNumber = Root::getSingleton().getCurrentFrame();
        if (thisFrameNumber != mLastFrameNumber)
        {
            ControllerList::const_iterator ci;
            for (ci = mControllers.begin(); ci != mControllers.end(); ++ci)
            {
                (*ci)->update();
            }
            mLastFrameNumber = thisFrameNumber;
        }
    }
    //-----------------------------------------------------------------------
    void ControllerManager::clearControllers(void)
    {
        ControllerList::iterator ci;
        for (ci = mControllers.begin(); ci != mControllers.end(); ++ci)
        {
            OGRE_DELETE *ci;
        }
        mControllers.clear();
    }
    //-----------------------------------------------------------------------
    const ControllerValueRealPtr& ControllerManager::getFrameTimeSource(void) const
    {
        return mFrameTimeController;
    }
    //-----------------------------------------------------------------------
    const ControllerFunctionRealPtr& ControllerManager::getPassthroughControllerFunction(void) const
    {
        return mPassthroughFunction;
    }
    //-----------------------------------------------------------------------
    ControllerReal* ControllerManager::createTextureAnimator(TextureUnitState* layer, Real sequenceTime)
    {
        return nullptr;
    }
    //-----------------------------------------------------------------------
    ControllerReal* ControllerManager::createTextureUVScroller(TextureUnitState* layer, Real speed)
    {
        return nullptr;
    }
    //-----------------------------------------------------------------------
    ControllerReal* ControllerManager::createTextureUScroller(TextureUnitState* layer, Real uSpeed)
    {
        return nullptr;
    }
    //-----------------------------------------------------------------------
    ControllerReal* ControllerManager::createTextureVScroller(TextureUnitState* layer, Real vSpeed)
    {
        return nullptr;
    }
    //-----------------------------------------------------------------------
    ControllerReal* ControllerManager::createTextureRotater(TextureUnitState* layer, Real speed)
    {
        return nullptr;
    }
    
    //-----------------------------------------------------------------------
    void ControllerManager::destroyController(ControllerReal* controller)
    {
        ControllerList::iterator i = mControllers.find(controller);
        if (i != mControllers.end())
        {
            mControllers.erase(i);
            OGRE_DELETE controller;
        }
    }
    //-----------------------------------------------------------------------
    Real ControllerManager::getTimeFactor(void) const {
        return 0.0f;
    }
    //-----------------------------------------------------------------------
    void ControllerManager::setTimeFactor(Real tf) {
        
    }
    //-----------------------------------------------------------------------
    Real ControllerManager::getFrameDelay(void) const {
        return 0.0f;
    }
    //-----------------------------------------------------------------------
    void ControllerManager::setFrameDelay(Real fd) {
        
    }
    //-----------------------------------------------------------------------
    Real ControllerManager::getElapsedTime(void) const
    {
        return 0.0f;
    }
    //-----------------------------------------------------------------------
    void ControllerManager::setElapsedTime(Real elapsedTime)
    {
    }
}
