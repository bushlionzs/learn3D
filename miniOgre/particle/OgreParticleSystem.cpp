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
#include "OgreParticleSystem.h"
#include "OgreParticleEmitter.h"
#include "OgreParticleAffector.h"
#include "OgreParticle.h"
#include "OgreParticleAffectorFactory.h"
#include "OgreParticleSystemRenderer.h"
#include "OgreSerializer.h"
#include "OgreDataStream.h"
#include "OgreMaterial.h"
#include "OgreMaterialManager.h"
#include "OgreStringConverter.h"
#include "OgreController.h"
#include "OgreParticleSystemManager.h"
#include "renderSystem.h"
#include "OgreNode.h"
#include "OgreCamera.h"
#include "OgreRadixSort.h"
#include "OgreControllerManager.h"
#include "OgreRoot.h"

namespace Ogre {
    /** Command object for quota (see ParamCommand).*/
    class  CmdQuota : public ParamCommand
    {
    public:
        String doGet(const void* target) const;
        void doSet(void* target, const String& val);
    };
    /** Command object for emittedEmitterQuota (see ParamCommand).*/
    class  CmdEmittedEmitterQuota : public ParamCommand
    {
    public:
        String doGet(const void* target) const;
        void doSet(void* target, const String& val);
    };
    /** Command object for material (see ParamCommand).*/
    class  CmdMaterial : public ParamCommand
    {
    public:
        String doGet(const void* target) const;
        void doSet(void* target, const String& val);
    };
    /** Command object for cull_each (see ParamCommand).*/
    class  CmdCull : public ParamCommand
    {
    public:
        String doGet(const void* target) const;
        void doSet(void* target, const String& val);
    };
    /** Command object for particle_width (see ParamCommand).*/
    class  CmdWidth : public ParamCommand
    {
    public:
        String doGet(const void* target) const;
        void doSet(void* target, const String& val);
    };
    /** Command object for particle_height (see ParamCommand).*/
    class  CmdHeight : public ParamCommand
    {
    public:
        String doGet(const void* target) const;
        void doSet(void* target, const String& val);
    };
    /** Command object for renderer (see ParamCommand).*/
    class  CmdRenderer : public ParamCommand
    {
    public:
        String doGet(const void* target) const;
        void doSet(void* target, const String& val);
    };
    /** Command object for sorting (see ParamCommand).*/
    class CmdSorted : public ParamCommand
    {
    public:
        String doGet(const void* target) const;
        void doSet(void* target, const String& val);
    };
    /** Command object for local space (see ParamCommand).*/
    class CmdLocalSpace : public ParamCommand
    {
    public:
        String doGet(const void* target) const;
        void doSet(void* target, const String& val);
    };
    /** Command object for iteration interval(see ParamCommand).*/
    class CmdIterationInterval : public ParamCommand
    {
    public:
        String doGet(const void* target) const;
        void doSet(void* target, const String& val);
    };
    /** Command object for nonvisible timeout (see ParamCommand).*/
    class CmdNonvisibleTimeout : public ParamCommand
    {
    public:
        String doGet(const void* target) const;
        void doSet(void* target, const String& val);
    };
    /// Command objects
    static CmdCull msCullCmd;
    static CmdHeight msHeightCmd;
    static CmdMaterial msMaterialCmd;
    static CmdQuota msQuotaCmd;
    static CmdEmittedEmitterQuota msEmittedEmitterQuotaCmd;
    static CmdWidth msWidthCmd;
    static CmdRenderer msRendererCmd;
    static CmdSorted msSortedCmd;
    static CmdLocalSpace msLocalSpaceCmd;
    static CmdIterationInterval msIterationIntervalCmd;
    static CmdNonvisibleTimeout msNonvisibleTimeoutCmd;

    Real ParticleSystem::msDefaultIterationInterval = 0;
    Real ParticleSystem::msDefaultNonvisibleTimeout = 0;

    //-----------------------------------------------------------------------
    // Local class for updating based on time
    class ParticleSystemUpdateValue : public ControllerValue<Real>
    {
    protected:
        ParticleSystem* mTarget;
    public:
        ParticleSystemUpdateValue(ParticleSystem* target) : mTarget(target) {}

        Real getValue(void) const { return 0; } // N/A

        void setValue(Real value) { mTarget->_update(value); }

    };
    //-----------------------------------------------------------------------
    ParticleSystem::ParticleSystem() 
      : MoveObject(std::string("ParticleSystem")),
        mAABB(),
        mBoundingRadius(1.0f),
        mBoundsAutoUpdate(true),
        mBoundsUpdateTime(10.0f),
        mUpdateRemainTime(0),
        mIsRendererConfigured(false),
        mSpeedFactor(1.0f),
        mIterationInterval(0),
        mIterationIntervalSet(false),
        mSorted(false),
        mLocalSpace(false),
        mNonvisibleTimeout(0),
        mNonvisibleTimeoutSet(false),
        mTimeSinceLastVisible(0),
        mLastVisibleFrame(0),
        mTimeController(0),
        mEmittedEmitterPoolInitialised(false),
        mIsEmitting(true),
        mRenderer(0),
        mCullIndividual(false),
        mPoolSize(0),
        mEmittedEmitterPoolSize(0),
        mVersion(101)
    {
        initParameters();

        // Default to billboard renderer
        setRenderer("billboard");
    }
    //-----------------------------------------------------------------------
    ParticleSystem::ParticleSystem(const String& name, const String& resourceGroup)
      : MoveObject(name),
        mAABB(),
        mBoundingRadius(1.0f),
        mBoundsAutoUpdate(true),
        mBoundsUpdateTime(10.0f),
        mUpdateRemainTime(0),
        mResourceGroupName(resourceGroup),
        mIsRendererConfigured(false),
        mSpeedFactor(1.0f),
        mIterationInterval(0),
        mIterationIntervalSet(false),
        mSorted(false),
        mLocalSpace(false),
        mNonvisibleTimeout(0),
        mNonvisibleTimeoutSet(false),
        mTimeSinceLastVisible(0),
        mTimeController(0),
        mEmittedEmitterPoolInitialised(false),
        mIsEmitting(true),
        mRenderer(0), 
        mCullIndividual(false),
        mPoolSize(0),
        mEmittedEmitterPoolSize(0),
        mVersion(101)
    {
        setDefaultDimensions( 100, 100 );
        mMaterial = MaterialManager::getSingleton().getDefaultMaterial();
        // Default to 10 particles, expect app to specify (will only be increased, not decreased)
        setParticleQuota( 10 );
        setEmittedEmitterQuota( 3 );
        initParameters();

        // Default to billboard renderer
        setRenderer("billboard");

        mAABB.setInfinite();

        mLastVisibleFrame =
            Ogre::Root::getSingleton().getNextFrameNumber();
    }
    //-----------------------------------------------------------------------
    ParticleSystem::~ParticleSystem()
    {
        if (mTimeController)
        {
            // Destroy controller
            ControllerManager::getSingleton().destroyController(mTimeController);
            mTimeController = 0;
        }

        // Arrange for the deletion of emitters & affectors
        removeAllEmitters();
        removeAllEmittedEmitters();
        removeAllAffectors();

        // Free pool items
        for (auto p : mParticlePool)
        {
            OGRE_DELETE p;
        }

        if (mRenderer)
        {
            ParticleSystemManager::getSingleton()._destroyRenderer(mRenderer);
            mRenderer = 0;
        }

    }
    //-----------------------------------------------------------------------
    ParticleEmitter* ParticleSystem::addEmitter(const String& emitterType)
    {
        ParticleEmitter* em = 
            ParticleSystemManager::getSingleton()._createEmitter(emitterType, this);
        mEmitters.push_back(em);
        return em;
    }
    //-----------------------------------------------------------------------
    ParticleEmitter* ParticleSystem::getEmitter(unsigned short index) const
    {
        assert(index < mEmitters.size() && "Emitter index out of bounds!");
        return mEmitters[index];
    }
    //-----------------------------------------------------------------------
    unsigned short ParticleSystem::getNumEmitters(void) const
    {
        return static_cast< unsigned short >( mEmitters.size() );
    }
    //-----------------------------------------------------------------------
    void ParticleSystem::removeEmitter(unsigned short index)
    {
        assert(index < mEmitters.size() && "Emitter index out of bounds!");
        ParticleEmitterList::iterator ei = mEmitters.begin() + index;
        ParticleSystemManager::getSingleton()._destroyEmitter(*ei);
        mEmitters.erase(ei);
    }
    //-----------------------------------------------------------------------
    void ParticleSystem::removeEmitter(ParticleEmitter* emitter)
    {
        auto ei = std::find(mEmitters.begin(), mEmitters.end(), emitter);
        assert(ei != mEmitters.end(), "Emitter is not a part of ParticleSystem!");
        ParticleSystemManager::getSingleton()._destroyEmitter(*ei);
        mEmitters.erase(ei);
    }
    //-----------------------------------------------------------------------
    void ParticleSystem::removeAllEmitters(void)
    {
        // DON'T delete directly, we don't know what heap these have been created on
        for (auto e : mEmitters)
        {
            ParticleSystemManager::getSingleton()._destroyEmitter(e);
        }
        mEmitters.clear();
    }
    //-----------------------------------------------------------------------
    ParticleAffector* ParticleSystem::addAffector(const String& affectorType)
    {
        ParticleAffector* af = 
            ParticleSystemManager::getSingleton()._createAffector(affectorType, this);
        mAffectors.push_back(af);
        return af;
    }
    //-----------------------------------------------------------------------
    ParticleAffector* ParticleSystem::getAffector(unsigned short index) const
    {
        assert(index < mAffectors.size() && "Affector index out of bounds!");
        return mAffectors[index];
    }
    //-----------------------------------------------------------------------
    unsigned short ParticleSystem::getNumAffectors(void) const
    {
        return static_cast< unsigned short >( mAffectors.size() );
    }
    //-----------------------------------------------------------------------
    void ParticleSystem::removeAffector(unsigned short index)
    {
        assert(index < mAffectors.size() && "Affector index out of bounds!");
        ParticleAffectorList::iterator ai = mAffectors.begin() + index;
        ParticleSystemManager::getSingleton()._destroyAffector(*ai);
        mAffectors.erase(ai);
    }
    //-----------------------------------------------------------------------
    void ParticleSystem::removeAllAffectors(void)
    {
        // DON'T delete directly, we don't know what heap these have been created on
        for (auto a : mAffectors)
        {
            ParticleSystemManager::getSingleton()._destroyAffector(a);
        }
        mAffectors.clear();
    }
    //-----------------------------------------------------------------------
    ParticleSystem& ParticleSystem::operator=(const ParticleSystem& rhs)
    {
        // Blank this system's emitters & affectors
        removeAllEmitters();
        removeAllEmittedEmitters();
        removeAllAffectors();

        // Copy emitters
        for(unsigned short i = 0; i < rhs.getNumEmitters(); ++i)
        {
            ParticleEmitter* rhsEm = rhs.getEmitter(i);
            ParticleEmitter* newEm = addEmitter(rhsEm->getType());
            rhsEm->copyParametersTo(newEm);
        }
        // Copy affectors
        for(unsigned short i = 0; i < rhs.getNumAffectors(); ++i)
        {
            ParticleAffector* rhsAf = rhs.getAffector(i);
            ParticleAffector* newAf = addAffector(rhsAf->getType());
            rhsAf->copyParametersTo(newAf);
        }
        setParticleQuota(rhs.getParticleQuota());
        setEmittedEmitterQuota(rhs.getEmittedEmitterQuota());
        setMaterialName(rhs.getMaterialName(), BLANKSTRING);
        setDefaultDimensions(rhs.mDefaultWidth, rhs.mDefaultHeight);
        mCullIndividual = rhs.mCullIndividual;
        mSorted = rhs.mSorted;
        mLocalSpace = rhs.mLocalSpace;
        mIterationInterval = rhs.mIterationInterval;
        mIterationIntervalSet = rhs.mIterationIntervalSet;
        mNonvisibleTimeout = rhs.mNonvisibleTimeout;
        mNonvisibleTimeoutSet = rhs.mNonvisibleTimeoutSet;
        // last frame visible and time since last visible should be left default

        setRenderer(rhs.getRendererName());
        // Copy settings
        if (mRenderer && rhs.getRenderer())
        {
            rhs.getRenderer()->copyParametersTo(mRenderer);
        }

        return *this;

    }
    //-----------------------------------------------------------------------
    size_t ParticleSystem::getNumParticles(void) const
    {
        return mActiveParticles.size();
    }
    //-----------------------------------------------------------------------
    size_t ParticleSystem::getParticleQuota(void) const
    {
        return mPoolSize;
    }
    //-----------------------------------------------------------------------
    void ParticleSystem::setParticleQuota(size_t size)
    {
        // Never shrink below size()
        size_t currSize = mParticlePool.size();

        if( currSize < size )
        {
            // Will allocate particles on demand
            mPoolSize = size;
            
        }
    }
    //-----------------------------------------------------------------------
    size_t ParticleSystem::getEmittedEmitterQuota(void) const
    {
        return mEmittedEmitterPoolSize;
    }
    //-----------------------------------------------------------------------
    void ParticleSystem::setEmittedEmitterQuota(size_t size)
    {
        // Never shrink below size()
        size_t currSize = 0;
        for (auto& kv : mEmittedEmitterPool)
        {
            currSize += kv.second.size();
        }

        if( currSize < size )
        {
            // Will allocate emitted emitters on demand
            mEmittedEmitterPoolSize = size;
        }
    }
    //-----------------------------------------------------------------------
    void ParticleSystem::setNonVisibleUpdateTimeout(Real timeout)
    {
        mNonvisibleTimeout = timeout;
        mNonvisibleTimeoutSet = true;
    }
    //-----------------------------------------------------------------------
    void ParticleSystem::setIterationInterval(Real interval)
    {
        mIterationInterval = interval;
        mIterationIntervalSet = true;
    }
    //-----------------------------------------------------------------------
    void ParticleSystem::_update(Real timeElapsed)
    {
        // Only update if attached to a node
        if (!mParent)
            return;

        Real nonvisibleTimeout = mNonvisibleTimeoutSet ?
            mNonvisibleTimeout : msDefaultNonvisibleTimeout;

        if (nonvisibleTimeout > 0)
        {
            // Check whether it's been more than one frame (update is ahead of
            // camera notification by one frame because of the ordering)
            long frameDiff = Ogre::Root::getSingleton().getNextFrameNumber() - mLastVisibleFrame;
            if (frameDiff > 1 || frameDiff < 0) // < 0 if wrap only
            {
                mTimeSinceLastVisible += timeElapsed;
                if (mTimeSinceLastVisible >= nonvisibleTimeout)
                {
                    // No update
                    return;
                }
            }
        }

        // Scale incoming speed for the rest of the calculation
        timeElapsed *= mSpeedFactor;

        // Init renderer if not done already
        configureRenderer();

        // Initialise emitted emitters list if not done already
        initialiseEmittedEmitters();

        Real iterationInterval = mIterationIntervalSet ? 
            mIterationInterval : msDefaultIterationInterval;
        if (iterationInterval > 0)
        {
            mUpdateRemainTime += timeElapsed;

            while (mUpdateRemainTime >= iterationInterval)
            {
                // Update existing particles
                _expire(iterationInterval);
                _triggerAffectors(iterationInterval);
                _applyMotion(iterationInterval);

                if(mIsEmitting)
                {
                    // Emit new particles
                    _triggerEmitters(iterationInterval);
                }

                mUpdateRemainTime -= iterationInterval;
            }
        }
        else
        {
            // Update existing particles
            _expire(timeElapsed);
            _triggerAffectors(timeElapsed);
            _applyMotion(timeElapsed);

            if(mIsEmitting)
            {
                // Emit new particles
                _triggerEmitters(timeElapsed);
            }
        }

        if (!mBoundsAutoUpdate && mBoundsUpdateTime > 0.0f)
            mBoundsUpdateTime -= timeElapsed; // count down 
        _updateBounds();

    }

    const std::vector<Renderable*>& ParticleSystem::getRenderableList()
    {
        if (mRenderables.empty())
        {
            mRenderables.push_back(mRenderer->getRenderable());
        }
        return mRenderables;
    }

    //-----------------------------------------------------------------------
    void ParticleSystem::_expire(Real timeElapsed)
    {
        Particle* pParticle;
        ParticleEmitter* pParticleEmitter;

        auto iend = mActiveParticles.end();
        for (auto i = mActiveParticles.begin(); i != iend;)
        {
            pParticle = static_cast<Particle*>(*i);
            if (pParticle->mTimeToLive < timeElapsed)
            {
                // Notify renderer
                mRenderer->_notifyParticleExpired(pParticle);

                // Identify the particle type
                if (pParticle->mParticleType == Particle::Visual)
                {
                    // add back to free list
                    mFreeParticles.push_back(pParticle);
                }
                else
                {
                    // For now, it can only be an emitted emitter
                    pParticleEmitter = static_cast<ParticleEmitter*>(*i);
                    std::list<ParticleEmitter*>* fee = findFreeEmittedEmitter(pParticleEmitter->getName());
                    fee->push_back(pParticleEmitter);

                    // Also erase from mActiveEmittedEmitters
                    removeFromActiveEmittedEmitters (pParticleEmitter);
                }

                // And remove from mActiveParticles
                *i = std::move(*(--iend));
            }
            else
            {
                // Decrement TTL
                pParticle->mTimeToLive -= timeElapsed;
                ++i;
            }
        }

        mActiveParticles.erase(iend, mActiveParticles.end());
    }
    //-----------------------------------------------------------------------
    void ParticleSystem::_triggerEmitters(Real timeElapsed)
    {
        // Add up requests for emission
        static std::vector<unsigned> requested;
        static std::vector<unsigned> emittedRequested;

        if( requested.size() != mEmitters.size() )
            requested.resize( mEmitters.size() );
        if( emittedRequested.size() != mEmittedEmitterPoolSize)
            emittedRequested.resize( mEmittedEmitterPoolSize );

        size_t totalRequested, emitterCount, emittedEmitterCount, i, emissionAllowed;
        ParticleEmitterList::iterator itEmit, iEmitEnd;
        ActiveEmittedEmitterList::iterator itActiveEmit, itActiveEnd;

        iEmitEnd = mEmitters.end();
        emitterCount = mEmitters.size();
        emittedEmitterCount=mActiveEmittedEmitters.size();
        itActiveEnd=mActiveEmittedEmitters.end();
        emissionAllowed = mFreeParticles.size();
        totalRequested = 0;

        // Count up total requested emissions for regular emitters (and exclude the ones that are used as
        // a template for emitted emitters)
        for (itEmit = mEmitters.begin(), i = 0; itEmit != iEmitEnd; ++itEmit, ++i)
        {
            if (!(*itEmit)->isEmitted())
            {
                requested[i] = (*itEmit)->_getEmissionCount(timeElapsed);
                totalRequested += requested[i];
            }
        }

        // Add up total requested emissions for (active) emitted emitters
        for (itActiveEmit = mActiveEmittedEmitters.begin(), i=0; itActiveEmit != itActiveEnd; ++itActiveEmit, ++i)
        {
            emittedRequested[i] = (*itActiveEmit)->_getEmissionCount(timeElapsed);
            totalRequested += emittedRequested[i];
        }

        // Check if the quota will be exceeded, if so reduce demand
        Real ratio =  1.0f;
        if (totalRequested > emissionAllowed)
        {
            // Apportion down requested values to allotted values
            ratio =  (Real)emissionAllowed / (Real)totalRequested;
            for (i = 0; i < emitterCount; ++i)
            {
                requested[i] = static_cast<unsigned>(requested[i] * ratio);
            }
            for (i = 0; i < emittedEmitterCount; ++i)
            {
                emittedRequested[i] = static_cast<unsigned>(emittedRequested[i] * ratio);
            }
        }

        // Emit
        // For each emission, apply a subset of the motion for the frame
        // this ensures an even distribution of particles when many are
        // emitted in a single frame
        for (itEmit = mEmitters.begin(), i = 0; itEmit != iEmitEnd; ++itEmit, ++i)
        {
            // Trigger the emitters, but exclude the emitters that are already in the emitted emitters list; 
            // they are handled in a separate loop
            if (!(*itEmit)->isEmitted())
                _executeTriggerEmitters (*itEmit, static_cast<unsigned>(requested[i]), timeElapsed);
        }

        // Do the same with all active emitted emitters
        for (itActiveEmit = mActiveEmittedEmitters.begin(), i = 0; itActiveEmit != mActiveEmittedEmitters.end(); ++itActiveEmit, ++i)
            _executeTriggerEmitters (*itActiveEmit, emittedRequested[i], timeElapsed);
    }
    //-----------------------------------------------------------------------
    void ParticleSystem::_executeTriggerEmitters(ParticleEmitter* emitter, unsigned requested, Real timeElapsed)
    {
        Real timePoint = 0.0f;


        // avoid any divide by zero conditions
        if(!requested) 
            return;

        Real timeInc = timeElapsed / requested;

        for (unsigned int j = 0; j < requested; ++j)
        {
            // Create a new particle & init using emitter
            // The particle is a visual particle if the emit_emitter property of the emitter isn't set 
            Particle* p = 0;
            String  emitterName = emitter->getEmittedEmitter();
            if (emitterName.empty())
                p = createParticle();
            else
                p = createEmitterParticle(emitterName);

            // Only continue if the particle was really created (not null)
            if (!p)
                return;

            emitter->_initParticle(p);

            // Translate position & direction into world space
            if (!mLocalSpace)
            {
                p->mPosition = mParent->convertLocalToWorldPosition(p->mPosition);
                p->mDirection = mParent->convertLocalToWorldDirection(p->mDirection, false);
            }

            // apply partial frame motion to this particle
            p->mPosition += (p->mDirection * timePoint);

            // apply particle initialization by the affectors
            for (auto a : mAffectors)
                a->_initParticle(p);

            // Increment time fragment
            timePoint += timeInc;

            // Notify renderer
            mRenderer->_notifyParticleEmitted(p);
        }
    }
    //-----------------------------------------------------------------------
    void ParticleSystem::_applyMotion(Real timeElapsed)
    {
        for (auto pParticle : mActiveParticles)
        {
            pParticle->mPosition += (pParticle->mDirection * timeElapsed);
        }

        // Notify renderer
        mRenderer->_notifyParticleMoved(mActiveParticles);
    }
    //-----------------------------------------------------------------------
    void ParticleSystem::_triggerAffectors(Real timeElapsed)
    {
        for (auto a : mAffectors)
        {
            a->_affectParticles(this, timeElapsed);
        }
    }
    //-----------------------------------------------------------------------
    void ParticleSystem::increasePool(size_t size)
    {
        size_t oldSize = mParticlePool.size();

        // Increase size
        mParticlePool.resize(size);

        // Create new particles
        for( size_t i = oldSize; i < size; i++ )
        {
            mParticlePool[i] = OGRE_NEW Particle();
        }
    }
    //-----------------------------------------------------------------------
    Particle* ParticleSystem::getParticle(size_t index) 
    {
        assert (index < mActiveParticles.size() && "Index out of bounds!");
        return mActiveParticles[index];
    }
    //-----------------------------------------------------------------------
    Particle* ParticleSystem::createParticle(void)
    {
        Particle* p = 0;
        if (!mFreeParticles.empty())
        {
            // Fast creation (don't use superclass since emitter will init)
            p = mFreeParticles.back();
            mActiveParticles.push_back(p);
            mFreeParticles.pop_back();
        }

        p->_notifyOwner(this);

        return p;

    }
    //-----------------------------------------------------------------------
    Particle* ParticleSystem::createEmitterParticle(const String& emitterName)
    {
        // Get the appropriate list and retrieve an emitter 
        ParticleEmitter* p = 0;
        std::list<ParticleEmitter*>* fee = findFreeEmittedEmitter(emitterName);
        if (fee && !fee->empty())
        {
            p = fee->front();
            p->mParticleType = Particle::Emitter;
            fee->pop_front();
            mActiveParticles.push_back(p);

            // Also add to mActiveEmittedEmitters. This is needed to traverse through all active emitters
            // that are emitted. Don't use mActiveParticles for that (although they are added to
            // mActiveParticles also), because it would take too long to traverse.
            mActiveEmittedEmitters.push_back(p);
        }

        return p;
    }
    //-----------------------------------------------------------------------
    void ParticleSystem::_updateRenderQueue(RenderQueue* queue)
    {
    }

    void ParticleSystem::update(float delta)
    {
        _update(delta);
        if (mRenderer)
        {
            mRenderer->_updateRenderQueue(nullptr, mActiveParticles, mCullIndividual);
        }
    }
    
    //---------------------------------------------------------------------
    void ParticleSystem::initParameters(void)
    {
        if (createParamDictionary("ParticleSystem"))
        {
            ParamDictionary* dict = getParamDictionary();

            dict->addParameter(ParameterDef("quota", 
                "The maximum number of particles allowed at once in this system.",
                PT_UNSIGNED_INT),
                &msQuotaCmd);

            dict->addParameter(ParameterDef("emit_emitter_quota", 
                "The maximum number of emitters to be emitted at once in this system.",
                PT_UNSIGNED_INT),
                &msEmittedEmitterQuotaCmd);

            dict->addParameter(ParameterDef("material", 
                "The name of the material to be used to render all particles in this system.",
                PT_STRING),
                &msMaterialCmd);

            dict->addParameter(ParameterDef("particle_width", 
                "The width of particles in world units.",
                PT_REAL),
                &msWidthCmd);

            dict->addParameter(ParameterDef("particle_height", 
                "The height of particles in world units.",
                PT_REAL),
                &msHeightCmd);

            dict->addParameter(ParameterDef("cull_each", 
                "If true, each particle is culled in it's own right. If false, the entire system is culled as a whole.",
                PT_BOOL),
                &msCullCmd);

            dict->addParameter(ParameterDef("renderer", 
                "Sets the particle system renderer to use (default 'billboard').",
                PT_STRING),
                &msRendererCmd);

            dict->addParameter(ParameterDef("sorted", 
                "Sets whether particles should be sorted relative to the camera. ",
                PT_BOOL),
                &msSortedCmd);

            dict->addParameter(ParameterDef("local_space", 
                "Sets whether particles should be kept in local space rather than "
                "emitted into world space. ",
                PT_BOOL),
                &msLocalSpaceCmd);

            dict->addParameter(ParameterDef("iteration_interval", 
                "Sets a fixed update interval for the system, or 0 for the frame rate. ",
                PT_REAL),
                &msIterationIntervalCmd);

            dict->addParameter(ParameterDef("nonvisible_update_timeout", 
                "Sets a timeout on updates to the system if the system is not visible "
                "for the given number of seconds (0 to always update)",
                PT_REAL),
                &msNonvisibleTimeoutCmd);

        }
    }
    //-----------------------------------------------------------------------
    void ParticleSystem::_updateBounds()
    {

    }
    //-----------------------------------------------------------------------
    void ParticleSystem::fastForward(Real time, Real interval)
    {
        // First make sure all transforms are up to date
        size_t steps = size_t(time/interval + 0.5f); // integer round
        for (size_t i = 0; i < steps; i++)
        {
            _update(interval);
        }
    }
    //-----------------------------------------------------------------------
    void ParticleSystem::setEmitting(bool v)
    {
        mIsEmitting = v;
    }
    //-----------------------------------------------------------------------
    bool ParticleSystem::getEmitting() const
    {
        return mIsEmitting;
    }
    //-----------------------------------------------------------------------
    const String& ParticleSystem::getMovableType(void) const
    {
        return ParticleSystemFactory::FACTORY_TYPE_NAME;
    }

    void ParticleSystem::_notifyParticleResized(void)
    {
        if (mRenderer)
        {
            mRenderer->_notifyParticleResized();
        }
    }

    /** Internal callback used by Particles to notify their parent that they have been rotated.
    */
    void ParticleSystem::_notifyParticleRotated(void)
    {
        if (mRenderer)
        {
            mRenderer->_notifyParticleRotated();
        }
    }
    //-----------------------------------------------------------------------
    void ParticleSystem::setDefaultDimensions( Real width, Real height )
    {
        assert(width >= 0 && height >= 0 && "Particle dimensions can not be negative");
        mDefaultWidth = width;
        mDefaultHeight = height;
        if (mRenderer)
        {
            mRenderer->_notifyDefaultDimensions(width, height);
        }
    }
    //-----------------------------------------------------------------------
    void ParticleSystem::setDefaultWidth(Real width)
    {
        assert(width >= 0 && "Particle dimensions can not be negative");
        mDefaultWidth = width;
        if (mRenderer)
        {
            mRenderer->_notifyDefaultDimensions(mDefaultWidth, mDefaultHeight);
        }
    }
    //-----------------------------------------------------------------------
    Real ParticleSystem::getDefaultWidth(void) const
    {
        return mDefaultWidth;
    }
    //-----------------------------------------------------------------------
    void ParticleSystem::setDefaultHeight(Real height)
    {
        assert(height >= 0 && "Particle dimensions can not be negative");
        mDefaultHeight = height;
        if (mRenderer)
        {
            mRenderer->_notifyDefaultDimensions(mDefaultWidth, mDefaultHeight);
        }
    }
    //-----------------------------------------------------------------------
    Real ParticleSystem::getDefaultHeight(void) const
    {
        return mDefaultHeight;
    }
    //-----------------------------------------------------------------------
    void ParticleSystem::_notifyCurrentCamera(ICamera* cam)
    {
        Camera* pCamera = (Camera*)cam;
        if (true)
        {
            mLastVisibleFrame = Root::getSingleton().getNextFrameNumber();
            mTimeSinceLastVisible = 0.0f;

            if (mSorted)
            {
                _sortParticles(pCamera);
            }

            if (mRenderer)
            {
                if (!mIsRendererConfigured)
                    configureRenderer();

                mRenderer->_notifyCurrentCamera(pCamera);
            }
        }
    }
    //-----------------------------------------------------------------------
    void ParticleSystem::_notifyAttached(Node* parent, bool isTagPoint)
    {
        MoveObject::_notifyAttached(parent, isTagPoint);
    }

    bool ParticleSystem::loadFromStream(Serializer* pSerializer, std::shared_ptr<DataStream>& stream, int version)
    {
        const String& name = stream->getName();

        this->mVersion = version;
        if (pSerializer && stream->eof() == false)
        {
            unsigned short id = pSerializer->readChunk(stream);
            if (id != PSFF_PARTICLE_SYSTEM)
            {

                pSerializer->skipChunk(stream);
                return false;
            }

            //����
            loadAttribute(pSerializer, stream);
            //��Ⱦ��
            loadRenderer(pSerializer, stream);
            //������
            loadEmitter(pSerializer, stream);
            //Ӱ����
            loadAffector(pSerializer, stream);
        }
        return false;
    }

    bool ParticleSystem::loadAttribute(Serializer* pSerializer, std::shared_ptr<DataStream>& stream)
    {
        mName = pSerializer->readStringBin(stream);

        //����--�����ͽ���
        pSerializer->readData(stream, &mCullIndividual, 1, sizeof(mCullIndividual));
        mMaterialName = pSerializer->readStringBin(stream);
        pSerializer->readData(stream, &mPoolSize, 1, sizeof(int32_t));
        pSerializer->readData(stream, &mDefaultWidth, 1, sizeof(mDefaultWidth));
        pSerializer->readData(stream, &mDefaultHeight, 1, sizeof(mDefaultHeight));
        pSerializer->readData(stream, &mSorted, 1, sizeof(mSorted));
        pSerializer->readData(stream, &mLocalSpace, 1, sizeof(mLocalSpace));
        pSerializer->readData(stream, &mIterationInterval, 1, sizeof(mIterationInterval));
        pSerializer->readData(stream, &mIterationIntervalSet, 1, sizeof(mIterationIntervalSet));
        pSerializer->readData(stream, &mNonvisibleTimeout, 1, sizeof(mNonvisibleTimeout));
        pSerializer->readData(stream, &mSpeedFactor, 1, sizeof(mSpeedFactor));
        pSerializer->readData(stream, &mNonvisibleTimeoutSet, 1, sizeof(mNonvisibleTimeoutSet));
        
        if (this->mVersion == 101)
        {
            pSerializer->readData(stream, &mTextureAtlasWidth, 1, sizeof(mTextureAtlasWidth));
            pSerializer->readData(stream, &mTextureAtlasHeight, 1, sizeof(mTextureAtlasHeight));
            pSerializer->readData(stream, &mTextureWidthIndex, 1, sizeof(mTextureWidthIndex));
            pSerializer->readData(stream, &mTextureHeightIndex, 1, sizeof(mTextureHeightIndex));
        }
        //end
        //-----------------------------------------
        return true;
    }

    bool ParticleSystem::loadRenderer(Serializer* pSerializer, std::shared_ptr<DataStream>& stream)
    {
        String renderType = pSerializer->readStringBin(stream);
        setRenderer(renderType);
        mRenderer->loadFromStream(pSerializer, stream);
        return true;
    }

    bool ParticleSystem::loadEmitter(Serializer* pSerializer, std::shared_ptr<DataStream>& stream)
    {
        int32_t emitterSize = 0;
        pSerializer->readData(stream, &emitterSize, 1, sizeof(emitterSize));
        for (int32_t emitterIndex = 0; emitterIndex != emitterSize; ++emitterIndex)
        {
            String emitterType = pSerializer->readStringBin(stream);
            ParticleEmitter* pEmitter = addEmitter(emitterType);
            pEmitter->loadFromStream(pSerializer, stream);
        }
        return true;
    }

    bool ParticleSystem::loadAffector(Serializer* pSerializer, std::shared_ptr<DataStream>& stream)
    {
        int32_t affectorSize = 0;
        pSerializer->readData(stream, &affectorSize, 1, sizeof(affectorSize));
        for (int32_t affectorIndex = 0; affectorIndex != affectorSize; ++affectorIndex)
        {
            String affectorType = pSerializer->readStringBin(stream);
            ParticleAffector* pAffector = addAffector(affectorType);
            //Ӱ��������--�����ƽ���
            pAffector->loadFromStream(pSerializer, stream);
        }
        return true;
    }
    //-----------------------------------------------------------------------
    void ParticleSystem::setMaterialName( const String& name, const String& groupName /* = ResourceGroupManager::AUTODETECT_RESOURCE_GROUP_NAME */)
    {
        mMaterialName = name;
        mMaterial = MaterialManager::getSingleton().getByName(name, groupName);
        if (!mMaterial)
        {
            assert(false);
            mMaterial = MaterialManager::getSingleton().getDefaultMaterial();
        }
        if (mIsRendererConfigured)
        {
            mMaterial->load();
            mRenderer->_setMaterial(mMaterial);
        }
    }
    //-----------------------------------------------------------------------
    const String& ParticleSystem::getMaterialName(void) const
    {
        return mMaterialName;
    }
    //-----------------------------------------------------------------------
    void ParticleSystem::clear()
    {
        // Notify renderer if exists
        if (mRenderer)
        {
            mRenderer->_notifyParticleCleared(mActiveParticles);
        }

        // reset active and free lists
        mActiveParticles.clear();
        mFreeParticles.clear();
        mFreeParticles.insert(mFreeParticles.end(), mParticlePool.begin(), mParticlePool.end());

        // Add active emitted emitters to free list
        addActiveEmittedEmittersToFreeList();

        // Remove all active emitted emitter instances
        mActiveEmittedEmitters.clear();

        // Reset update remain time
        mUpdateRemainTime = 0;
    }
    //-----------------------------------------------------------------------
    void ParticleSystem::setRenderer(const String& rendererName)
    {
        if (mRenderer)
        {
            // Destroy existing
            ParticleSystemManager::getSingleton()._destroyRenderer(mRenderer);
            mRenderer = 0;
        }

        if (!rendererName.empty())
        {
            mRenderer = ParticleSystemManager::getSingleton()._createRenderer(rendererName);
            mIsRendererConfigured = false;
            mRenderer->setParticleSystem(this);
        }
    }
    //-----------------------------------------------------------------------
    void ParticleSystem::configureRenderer(void)
    {
        // Actual allocate particles
        size_t currSize = mParticlePool.size();
        size_t size = mPoolSize;
        if( currSize < size )
        {
            this->increasePool(size);

            // Add new items to the queue
            mFreeParticles.insert(mFreeParticles.end(), mParticlePool.begin() + currSize,
                                  mParticlePool.end());

            // Tell the renderer, if already configured
            if (mRenderer && mIsRendererConfigured)
            {
                mRenderer->_notifyParticleQuota(size);
            }
        }

        if (mRenderer && !mIsRendererConfigured)
        {
            mRenderer->_notifyParticleQuota(mParticlePool.size());
            mRenderer->_notifyAttached(mParent, false);
            mRenderer->_notifyDefaultDimensions(mDefaultWidth, mDefaultHeight);
            mMaterial->load();
            mRenderer->_setMaterial(mMaterial);
            mRenderer->setKeepParticlesInLocalSpace(mLocalSpace);
            mIsRendererConfigured = true;
        }
    }
    //-----------------------------------------------------------------------
    ParticleSystemRenderer* ParticleSystem::getRenderer(void) const
    {
        return mRenderer;
    }
    //-----------------------------------------------------------------------
    const String& ParticleSystem::getRendererName(void) const
    {
        if (mRenderer)
        {
            return mRenderer->getType();
        }
        else
        {
            return BLANKSTRING;
        }
    }
    //-----------------------------------------------------------------------
    bool ParticleSystem::getCullIndividually(void) const
    {
        return mCullIndividual;
    }
    //-----------------------------------------------------------------------
    void ParticleSystem::setCullIndividually(bool cullIndividual)
    {
        mCullIndividual = cullIndividual;
    }
    //-----------------------------------------------------------------------
    void ParticleSystem::setBounds(const AxisAlignedBox& aabb)
    {
        mAABB = aabb;
        mBoundingRadius = Math::boundingRadiusFromAABB(mAABB);

    }
    //-----------------------------------------------------------------------
    void ParticleSystem::setBoundsAutoUpdated(bool autoUpdate, Real stopIn)
    {
        mBoundsAutoUpdate = autoUpdate;
        mBoundsUpdateTime = stopIn;
    }
    //-----------------------------------------------------------------------
    void ParticleSystem::setRenderQueueGroup(uint8 queueID)
    {
      
    }
    //-----------------------------------------------------------------------
    void ParticleSystem::setRenderQueueGroupAndPriority(uint8 queueID, ushort priority)
    {
    }
    //-----------------------------------------------------------------------
    void ParticleSystem::setKeepParticlesInLocalSpace(bool keepLocal)
    {
        mLocalSpace = keepLocal;
        if (mRenderer)
        {
            mRenderer->setKeepParticlesInLocalSpace(keepLocal);
        }
    }
    //-----------------------------------------------------------------------
    void ParticleSystem::_sortParticles(Camera* cam)
    {
        static RadixSort<ParticlePool, Particle*, float> mRadixSorter;
        if (mRenderer)
        {
            SortMode sortMode =
                cam->getSortMode() == SM_DIRECTION ? SM_DIRECTION : mRenderer->_getSortMode();

            if (sortMode == SM_DIRECTION)
            {
                Vector3 camDir = cam->getDerivedDirection();
                if (mLocalSpace)
                {
                    // transform the camera direction into local space
                    camDir = mParent->convertWorldToLocalDirection(camDir, false);
                }
                mRadixSorter.sort(mActiveParticles, SortByDirectionFunctor(- camDir));
            }
            else if (sortMode == SM_DISTANCE)
            {
                Vector3 camPos = cam->getDerivedPosition();
                if (mLocalSpace)
                {
                    // transform the camera position into local space
                    camPos = mParent->convertWorldToLocalPosition(camPos);
                }
                mRadixSorter.sort(mActiveParticles, SortByDistanceFunctor(camPos));
            }
        }
    }
    ParticleSystem::SortByDirectionFunctor::SortByDirectionFunctor(const Vector3& dir)
        : sortDir(dir)
    {
    }
    float ParticleSystem::SortByDirectionFunctor::operator()(Particle* p) const
    {
        return sortDir.dotProduct(p->mPosition);
    }
    ParticleSystem::SortByDistanceFunctor::SortByDistanceFunctor(const Vector3& pos)
        : sortPos(pos)
    {
    }
    float ParticleSystem::SortByDistanceFunctor::operator()(Particle* p) const
    {
        // Sort descending by squared distance
        return - (sortPos - p->mPosition).squaredLength();
    }
    //-----------------------------------------------------------------------
    uint32 ParticleSystem::getTypeFlags(void) const
    {
        return 0x20000000;
    }
    //-----------------------------------------------------------------------
    void ParticleSystem::initialiseEmittedEmitters(void)
    {
        // Initialise the pool if needed
        size_t currSize = 0;
        if (mEmittedEmitterPool.empty())
        {
            if (mEmittedEmitterPoolInitialised)
            {
                // It was already initialised, but apparently no emitted emitters were used
                return;
            }
            else
            {
                initialiseEmittedEmitterPool();
            }
        }
        else
        {
            for (auto& kv : mEmittedEmitterPool)
            {
                currSize += kv.second.size();
            }
        }

        size_t size = mEmittedEmitterPoolSize;
        if( currSize < size && !mEmittedEmitterPool.empty())
        {
            // Increase the pool. Equally distribute over all vectors in the map
            increaseEmittedEmitterPool(size);
            
            // Add new items to the free list
            addFreeEmittedEmitters();
        }
    }

    //-----------------------------------------------------------------------
    void ParticleSystem::initialiseEmittedEmitterPool(void)
    {
        if (mEmittedEmitterPoolInitialised)
            return;

        // Run through mEmitters and add keys to the pool
        for (ParticleEmitter* emitter : mEmitters)
        {
            // Determine the names of all emitters that are emitted
            if (!emitter->getEmittedEmitter().empty())
            {
                // This one will be emitted, register its name and leave the vector empty!
                mEmittedEmitterPool[emitter->getEmittedEmitter()];
            }
        }

        // Determine whether the emitter itself will be emitted and set the 'mEmitted' attribute
        for (ParticleEmitter* emitter : mEmitters)
        {
            if (mEmittedEmitterPool.find(emitter->getName()) != mEmittedEmitterPool.end())
            {
                emitter->setEmitted(true);
            }
        }

        mEmittedEmitterPoolInitialised = true;
    }
    //-----------------------------------------------------------------------
    void ParticleSystem::increaseEmittedEmitterPool(size_t size)
    {
        // Don't proceed if the pool doesn't contain any keys of emitted emitters
        if (mEmittedEmitterPool.empty())
            return;

        ParticleEmitter* clonedEmitter = 0;
        size_t maxNumberOfEmitters = size / mEmittedEmitterPool.size(); // equally distribute the number for each emitted emitter list
    
        // Run through mEmittedEmitterPool and search for every key (=name) its corresponding emitter in mEmitters
        for (auto& kv : mEmittedEmitterPool)
        {
            const auto& name = kv.first;
            auto& e = kv.second;

            // Search the correct emitter in the mEmitters vector
            for (ParticleEmitter* emitter : mEmitters)
            {
                if (name == emitter->getName())
                {
                    // Found the right emitter, clone each emitter a number of times
                    size_t oldSize = e.size();
                    for (size_t t = oldSize; t < maxNumberOfEmitters; ++t)
                    {
                        clonedEmitter = ParticleSystemManager::getSingleton()._createEmitter(emitter->getType(), this);
                        emitter->copyParametersTo(clonedEmitter);
                        clonedEmitter->setEmitted(emitter->isEmitted()); // is always 'true' by the way, but just in case

                        // Initially deactivate the emitted emitter if duration/repeat_delay are set
                        if (clonedEmitter->getDuration() != 0.0f && clonedEmitter->getRepeatDelay() > 0.0f)
                            clonedEmitter->setEnabled(false);

                        // Add cloned emitters to the pool
                        e.push_back(clonedEmitter);
                    }
                }
            }
        }
    }
    //-----------------------------------------------------------------------
    void ParticleSystem::addFreeEmittedEmitters(void)
    {
        // Don't proceed if the EmittedEmitterPool is empty
        if (mEmittedEmitterPool.empty())
            return;

        // Copy all pooled emitters to the free list
        std::list<ParticleEmitter*>* fee = 0;

        // Run through the emittedEmitterPool map
        for (auto& kv : mEmittedEmitterPool)
        {
            const auto& name = kv.first;
            auto& emittedEmitters = kv.second;
            fee = findFreeEmittedEmitter(name);

            // If its not in the map, create an empty one
            if (!fee)
            {
                mFreeEmittedEmitters[name];
                fee = findFreeEmittedEmitter(name);
            }

            // Check anyway if its ok now
            if (!fee)
                return; // forget it!

            // Add all emitted emitters from the pool to the free list
            for(ParticleEmitter* emitter : emittedEmitters)
            {
                fee->push_back(emitter);
            }
        }
    }
    //-----------------------------------------------------------------------
    void ParticleSystem::removeAllEmittedEmitters(void)
    {
        for (auto& kv : mEmittedEmitterPool)
        {
            for (ParticleEmitter* emitter : kv.second)
            {
                ParticleSystemManager::getSingleton()._destroyEmitter(emitter);
            }
            kv.second.clear();
        }

        // Don't leave any references behind
        mEmittedEmitterPool.clear();
        mFreeEmittedEmitters.clear();
        mActiveEmittedEmitters.clear();
    }
    //-----------------------------------------------------------------------
    std::list<ParticleEmitter*>* ParticleSystem::findFreeEmittedEmitter (const String& name)
    {
        FreeEmittedEmitterMap::iterator it;
        it = mFreeEmittedEmitters.find (name);
        if (it != mFreeEmittedEmitters.end())
        {
            // Found it
            return &it->second;
        }

        return 0;
    }
    //-----------------------------------------------------------------------
    void ParticleSystem::removeFromActiveEmittedEmitters (ParticleEmitter* emitter)
    {
        assert(emitter && "Emitter to be removed is 0!");
        ActiveEmittedEmitterList::iterator itActiveEmit;
        for (itActiveEmit = mActiveEmittedEmitters.begin(); itActiveEmit != mActiveEmittedEmitters.end(); ++itActiveEmit)
        {
            if (emitter == (*itActiveEmit))
            {
                mActiveEmittedEmitters.erase(itActiveEmit);
                break;
            }
        }
    }
    //-----------------------------------------------------------------------
    void ParticleSystem::addActiveEmittedEmittersToFreeList (void)
    {
        ActiveEmittedEmitterList::iterator itActiveEmit;
        for (itActiveEmit = mActiveEmittedEmitters.begin(); itActiveEmit != mActiveEmittedEmitters.end(); ++itActiveEmit)
        {
            std::list<ParticleEmitter*>* fee = findFreeEmittedEmitter ((*itActiveEmit)->getName());
            if (fee)
                fee->push_back(*itActiveEmit);
        }
    }
    //-----------------------------------------------------------------------
    void ParticleSystem::_notifyReorganiseEmittedEmitterData (void)
    {
        removeAllEmittedEmitters();
        mEmittedEmitterPoolInitialised = false; // Don't rearrange immediately; it will be performed in the regular flow
    }
    //-----------------------------------------------------------------------
    String CmdCull::doGet(const void* target) const
    {
        return StringConverter::toString(
            static_cast<const ParticleSystem*>(target)->getCullIndividually() );
    }
    void CmdCull::doSet(void* target, const String& val)
    {
        static_cast<ParticleSystem*>(target)->setCullIndividually(
            StringConverter::parseBool(val));
    }
    //-----------------------------------------------------------------------
    String CmdHeight::doGet(const void* target) const
    {
        return StringConverter::toString(
            static_cast<const ParticleSystem*>(target)->getDefaultHeight() );
    }
    void CmdHeight::doSet(void* target, const String& val)
    {
        static_cast<ParticleSystem*>(target)->setDefaultHeight(
            StringConverter::parseReal(val));
    }
    //-----------------------------------------------------------------------
    String CmdWidth::doGet(const void* target) const
    {
        return StringConverter::toString(
            static_cast<const ParticleSystem*>(target)->getDefaultWidth() );
    }
    void CmdWidth::doSet(void* target, const String& val)
    {
        static_cast<ParticleSystem*>(target)->setDefaultWidth(
            StringConverter::parseReal(val));
    }
    //-----------------------------------------------------------------------
    String CmdMaterial::doGet(const void* target) const
    {
        return static_cast<const ParticleSystem*>(target)->getMaterialName();
    }
    void CmdMaterial::doSet(void* target, const String& val)
    {
        static_cast<ParticleSystem*>(target)->setMaterialName(val, BLANKSTRING);
    }
    //-----------------------------------------------------------------------
    String CmdQuota::doGet(const void* target) const
    {
        return StringConverter::toString(
            static_cast<const ParticleSystem*>(target)->getParticleQuota() );
    }
    void CmdQuota::doSet(void* target, const String& val)
    {
        static_cast<ParticleSystem*>(target)->setParticleQuota(
            StringConverter::parseUnsignedInt(val));
    }
    //-----------------------------------------------------------------------
    String CmdEmittedEmitterQuota::doGet(const void* target) const
    {
        return StringConverter::toString(
            static_cast<const ParticleSystem*>(target)->getEmittedEmitterQuota() );
    }
    void CmdEmittedEmitterQuota::doSet(void* target, const String& val)
    {
        static_cast<ParticleSystem*>(target)->setEmittedEmitterQuota(
            StringConverter::parseUnsignedInt(val));
    }
    //-----------------------------------------------------------------------
    String CmdRenderer::doGet(const void* target) const
    {
        return static_cast<const ParticleSystem*>(target)->getRendererName();
    }
    void CmdRenderer::doSet(void* target, const String& val)
    {
        static_cast<ParticleSystem*>(target)->setRenderer(val);
    }
    //-----------------------------------------------------------------------
    String CmdSorted::doGet(const void* target) const
    {
        return StringConverter::toString(
            static_cast<const ParticleSystem*>(target)->getSortingEnabled());
    }
    void CmdSorted::doSet(void* target, const String& val)
    {
        static_cast<ParticleSystem*>(target)->setSortingEnabled(
            StringConverter::parseBool(val));
    }
    //-----------------------------------------------------------------------
    String CmdLocalSpace::doGet(const void* target) const
    {
        return StringConverter::toString(
            static_cast<const ParticleSystem*>(target)->getKeepParticlesInLocalSpace());
    }
    void CmdLocalSpace::doSet(void* target, const String& val)
    {
        static_cast<ParticleSystem*>(target)->setKeepParticlesInLocalSpace(
            StringConverter::parseBool(val));
    }
    //-----------------------------------------------------------------------
    String CmdIterationInterval::doGet(const void* target) const
    {
        return StringConverter::toString(
            static_cast<const ParticleSystem*>(target)->getIterationInterval());
    }
    void CmdIterationInterval::doSet(void* target, const String& val)
    {
        static_cast<ParticleSystem*>(target)->setIterationInterval(
            StringConverter::parseReal(val));
    }
    //-----------------------------------------------------------------------
    String CmdNonvisibleTimeout::doGet(const void* target) const
    {
        return StringConverter::toString(
            static_cast<const ParticleSystem*>(target)->getNonVisibleUpdateTimeout());
    }
    void CmdNonvisibleTimeout::doSet(void* target, const String& val)
    {
        static_cast<ParticleSystem*>(target)->setNonVisibleUpdateTimeout(
            StringConverter::parseReal(val));
    }
   //-----------------------------------------------------------------------
    ParticleAffector::~ParticleAffector() 
    {
    }
    //-----------------------------------------------------------------------
    ParticleAffectorFactory::~ParticleAffectorFactory() 
    {
        // Destroy all affectors
        std::vector<ParticleAffector*>::iterator i;
        for (i = mAffectors.begin(); i != mAffectors.end(); ++i)
        {
            OGRE_DELETE (*i);
        }
            
        mAffectors.clear();

    }
    //-----------------------------------------------------------------------
    void ParticleAffectorFactory::destroyAffector(ParticleAffector* e)
    {
        std::vector<ParticleAffector*>::iterator i;
        for (i = mAffectors.begin(); i != mAffectors.end(); ++i)
        {
            if ((*i) == e)
            {
                mAffectors.erase(i);
                OGRE_DELETE e;
                break;
            }
        }
    }

}
