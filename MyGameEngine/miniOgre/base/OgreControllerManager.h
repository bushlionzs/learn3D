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
#ifndef __ControllerManager_H__
#define __ControllerManager_H__

#include "OgreCommon.h"
#include "OgreSingleton.h"
#include "OgreController.h"

class TextureUnitState;

namespace Ogre {
    /** \addtogroup Core
    *  @{
    */
    /** \addtogroup Animation
    *  @{
    */

    typedef std::shared_ptr< ControllerValue<Real> > ControllerValueRealPtr;
    typedef std::shared_ptr< ControllerFunction<Real> > ControllerFunctionRealPtr;

    /** Class for managing Controller instances.
    @remarks
        This class is responsible to keeping tabs on all the Controller instances registered
        and updating them when requested. It also provides a number of convenience methods
        for creating commonly used controllers (such as texture animators).
    */
    class  ControllerManager : public Singleton<ControllerManager>, public ControllerAlloc
    {
    private:
        typedef std::set<ControllerReal*> ControllerList;
        ControllerList mControllers;

        /// Global predefined controller
        ControllerValueRealPtr mFrameTimeController;
        
        /// Global predefined controller
        ControllerFunctionRealPtr mPassthroughFunction;

        /// Last frame number updated
        unsigned long mLastFrameNumber;

    public:
        ControllerManager();
        ~ControllerManager();

        /** Creates a new controller and registers it with the manager.
        */
        ControllerReal* createController(const ControllerValueRealPtr& src,
            const ControllerValueRealPtr& dest, const ControllerFunctionRealPtr& func);

        /** Creates a new controller use frame time source and passthrough controller function.
        */
        ControllerReal* createFrameTimePassthroughController(const ControllerValueRealPtr& dest);

        /** Destroys all the controllers in existence.
        */
        void clearControllers(void);

        /** Updates all the registered controllers.
        */
        void updateAllControllers(void);


        /** Returns a ControllerValue which provides the time since the last frame as a control value source.

            A common source value to use to feed into a controller is the time since the last frame. This method
            returns a pointer to a common source value which provides this information.
        @par
            Remember the value will only be up to date after the RenderSystem::beginFrame method is called.
        @see
            RenderSystem::beginFrame
        */
        const ControllerValueRealPtr& getFrameTimeSource(void) const;

        /** Retrieve a simple passthrough controller function. */
        const ControllerFunctionRealPtr& getPassthroughControllerFunction(void) const;

        /** Creates a texture layer animator controller.

            This helper method creates the Controller, ControllerValue and ControllerFunction classes required
            to animate a texture.
        @param layer
            TextureUnitState object to animate
        @param sequenceTime
            The amount of time in seconds it will take to loop through all the frames.
        */
        ControllerReal* createTextureAnimator(TextureUnitState* layer, Real sequenceTime);

        /** Creates a basic time-based texture uv coordinate modifier designed for creating scrolling textures.

            This simple method allows you to easily create constant-speed uv scrolling textures. If you want to 
            specify different speed values for horizontal and vertical scroll, use the specific methods
            ControllerManager::createTextureUScroller and ControllerManager::createTextureVScroller.
            If you want more control, look up the ControllerManager::createTextureWaveTransformer 
            for more complex wave-based scrollers / stretchers / rotators.
        @param layer
            The texture layer to animate.
        @param speed
            Speed of horizontal (u-coord) and vertical (v-coord) scroll, in complete wraps per second.
        */
        ControllerReal* createTextureUVScroller(TextureUnitState* layer, Real speed);

        /** Creates a basic time-based texture u coordinate modifier designed for creating scrolling textures.

            This simple method allows you to easily create constant-speed u scrolling textures. If you want more
            control, look up the ControllerManager::createTextureWaveTransformer for more complex wave-based
            scrollers / stretchers / rotators.
        @param layer
            The texture layer to animate.
        @param uSpeed
            Speed of horizontal (u-coord) scroll, in complete wraps per second.
        */
        ControllerReal* createTextureUScroller(TextureUnitState* layer, Real uSpeed);

        /** Creates a basic time-based texture v coordinate modifier designed for creating scrolling textures.

            This simple method allows you to easily create constant-speed v scrolling textures. If you want more
            control, look up the ControllerManager::createTextureWaveTransformer for more complex wave-based
            scrollers / stretchers / rotators.
        @param layer
            The texture layer to animate.
        @param vSpeed
            Speed of vertical (v-coord) scroll, in complete wraps per second.
        */
        ControllerReal* createTextureVScroller(TextureUnitState* layer, Real vSpeed);

        /** Creates a basic time-based texture coordinate modifier designed for creating rotating textures.

            This simple method allows you to easily create constant-speed rotating textures. If you want more
            control, look up the ControllerManager::createTextureWaveTransformer for more complex wave-based
            scrollers / stretchers / rotators.
        @param layer
            The texture layer to rotate.
        @param speed
            Speed of rotation, in complete anticlockwise revolutions per second.
        */
        ControllerReal* createTextureRotater(TextureUnitState* layer, Real speed);

       
        /** Removes & destroys the controller passed in as a pointer.
        */
        void destroyController(ControllerReal* controller);

        /** Return relative speed of time as perceived by time based controllers.

            See setTimeFactor for full information on the meaning of this value.
        */
        Real getTimeFactor(void) const;

        /** Set the relative speed to update frame time based controllers.

            Normally any controllers which use time as an input (FrameTimeController) are updated
            automatically in line with the real passage of time. This method allows you to change
            that, so that controllers are told that the time is passing slower or faster than it
            actually is. Use this to globally speed up / slow down the effect of time-based controllers.
        @param tf
            The virtual speed of time (1.0 is real time).
        */
        void setTimeFactor(Real tf);

        /** Gets the constant that is added to time lapsed between each frame.
        @remarks
            See setFrameDelay for full information on the meaning of this value.
        */
        Real getFrameDelay(void) const;

        /** Sets a constant frame rate.

            This function is useful when rendering a sequence to
            files that should create a film clip with constant frame
            rate.
            It will ensure that scrolling textures and animations
            move at a constant frame rate.
        @param fd
            The delay in seconds wanted between each frame 
            (1.0f / 25.0f means a seconds worth of animation is done 
            in 25 frames).
        */
        void setFrameDelay(Real fd);

        /** Return the elapsed time.
        @remarks
            See setElapsedTime for full information on the meaning of this value.
        */
        Real getElapsedTime(void) const;

        /** Set the elapsed time.

            Normally elapsed time accumulated all frames time (which speed relative to time
            factor) since the rendering loop started. This method allows your to change that to
            special time, so some elapsed-time-based globally effect is repeatable.
        @param elapsedTime
            The new elapsed time.
        */
        void setElapsedTime(Real elapsedTime);

        /// @copydoc Singleton::getSingleton()
        static ControllerManager& getSingleton(void);
        /// @copydoc Singleton::getSingleton()
        static ControllerManager* getSingletonPtr(void);
    };

    /** @} */
    /** @} */

} // namespace Ogre


#endif // __ControllerManager_H__
