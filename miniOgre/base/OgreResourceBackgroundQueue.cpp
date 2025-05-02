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
#include <OgreHeader.h>
#include "OgreResourceBackgroundQueue.h"

namespace Ogre {

    // Note, no locks are required here anymore because all of the parallelisation
    // is now contained in WorkQueue - this class is entirely single-threaded
    //------------------------------------------------------------------------
    //-----------------------------------------------------------------------
    template<> ResourceBackgroundQueue* Singleton<ResourceBackgroundQueue>::msSingleton = 0;
    ResourceBackgroundQueue* ResourceBackgroundQueue::getSingletonPtr(void)
    {
        return msSingleton;
    }
    ResourceBackgroundQueue& ResourceBackgroundQueue::getSingleton(void)
    {  
        assert( msSingleton );  return ( *msSingleton );  
    }
    //------------------------------------------------------------------------
    ResourceBackgroundQueue::ResourceBackgroundQueue() {}
    ResourceBackgroundQueue::~ResourceBackgroundQueue() {}
    //------------------------------------------------------------------------
    std::future<void> ResourceBackgroundQueue::initialiseResourceGroup(const String& name)
    {
        assert_invariant(false);
        auto task = std::make_shared<std::packaged_task<void()>>([]() {});

        return task->get_future();
    }
    //------------------------------------------------------------------------
    std::future<void> ResourceBackgroundQueue::initialiseAllResourceGroups()
    {
        assert_invariant(false);
        auto task = std::make_shared<std::packaged_task<void()>>([]() {});

        return task->get_future();
    }
    //------------------------------------------------------------------------
    std::future<void> ResourceBackgroundQueue::prepareResourceGroup(const String& name)
    {
        assert_invariant(false);
        auto task = std::make_shared<std::packaged_task<void()>>([]() {});

        return task->get_future();
    }
    //------------------------------------------------------------------------
    std::future<void> ResourceBackgroundQueue::loadResourceGroup(const String& name)
    {
        assert_invariant(false);
        auto task = std::make_shared<std::packaged_task<void()>>([]() {});

        return task->get_future();
    }
    //------------------------------------------------------------------------
    std::future<void> ResourceBackgroundQueue::prepare(const ResourcePtr& res)
    {
        auto task = std::make_shared<std::packaged_task<void()>>(
            [res]()
            {
                res->prepare(true);
                Root::getSingleton().getWorkQueue()->addMainThreadTask([res]() { res->_firePreparingComplete(); });
            });
        Root::getSingleton().getWorkQueue()->addTask([task]() { (*task)(); });
        return task->get_future();
    }
    //------------------------------------------------------------------------
    std::future<void> ResourceBackgroundQueue::load(const ResourcePtr& res)
    {
        auto task = std::make_shared<std::packaged_task<void()>>(
            [res]()
            {
                res->load(true);
                Root::getSingleton().getWorkQueue()->addMainThreadTask([res]() { res->_fireLoadingComplete(); });
            });
        Root::getSingleton().getWorkQueue()->addTask([task]() { (*task)(); });
        return task->get_future();
    }
    //---------------------------------------------------------------------
    std::future<void> ResourceBackgroundQueue::unload(const ResourcePtr& res)
    {
        auto task = std::make_shared<std::packaged_task<void()>>([res]() { res->unload(); });
        Root::getSingleton().getWorkQueue()->addTask([task]() { (*task)(); });
        return task->get_future();
    }
    //---------------------------------------------------------------------
    std::future<void> ResourceBackgroundQueue::unloadResourceGroup(const String& name)
    {
        assert_invariant(false);

        auto task = std::make_shared<std::packaged_task<void()>>([]() {});
      
        return task->get_future();
    }

}



