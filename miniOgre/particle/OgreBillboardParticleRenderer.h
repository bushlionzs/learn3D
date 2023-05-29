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
#ifndef __BillboardParticleRenderer_H__
#define __BillboardParticleRenderer_H__

#include "OgreParticleSystemRenderer.h"
#include "OgreBillboardSet.h"
#include "OgreFactoryObj.h"
#include "OgreParticleSystemRenderer.h"
#include "particle_common.h"

class RenderQueue;

namespace Ogre {

    /** \addtogroup Core
    *  @{
    */
    /** \addtogroup Effects
    *  @{
    */

    /** Specialisation of ParticleSystemRenderer to render particles using 
        a BillboardSet. 
    @remarks
        This renderer has a few more options than the standard particle system,
        which will be passed to it automatically when the particle system itself
        does not understand them.
    */

    

    class  BillboardParticleRenderer : public ParticleSystemRenderer
    {
    protected:
        /// The billboard set that's doing the rendering
        BillboardSet* mBillboardSet;
        Real mSpeedRelativedSizeFactor;
        Ogre::Vector2 mStacksSlices;
    public:
        BillboardParticleRenderer();
        ~BillboardParticleRenderer();

        /** Command object for billboard type (see ParamCommand).*/
        class  CmdBillboardType : public ParamCommand
        {
        public:
            String doGet(const void* target) const;
            void doSet(void* target, const String& val);
        };
        /** Command object for billboard origin (see ParamCommand).*/
        class  CmdBillboardOrigin : public ParamCommand
        {
        public:
            String doGet(const void* target) const;
            void doSet(void* target, const String& val);
        };
        /** Command object for billboard rotation type (see ParamCommand).*/
        class  CmdBillboardRotationType : public ParamCommand
        {
        public:
            String doGet(const void* target) const;
            void doSet(void* target, const String& val);
        };
        /** Command object for common direction (see ParamCommand).*/
        class  CmdCommonDirection : public ParamCommand
        {
        public:
            String doGet(const void* target) const;
            void doSet(void* target, const String& val);
        };
        /** Command object for common up-vector (see ParamCommand).*/
        class  CmdCommonUpVector : public ParamCommand
        {
        public:
            String doGet(const void* target) const;
            void doSet(void* target, const String& val);
        };
        /** Command object for point rendering (see ParamCommand).*/
        class  CmdPointRendering : public ParamCommand
        {
        public:
            String doGet(const void* target) const;
            void doSet(void* target, const String& val);
        };
        /** Command object for accurate facing(see ParamCommand).*/
        class  CmdAccurateFacing : public ParamCommand
        {
        public:
            String doGet(const void* target) const;
            void doSet(void* target, const String& val);
        };

        class  CmdStacksAndSlices : public ParamCommand
        {
        public:
            String doGet(const void* target) const;
            void doSet(void* target, const String& val);
        };

        /** Command object for speed relatived size factor (see ParamCommand).*/
        class  CmdSpeedRelativedSizeFactor : public ParamCommand
        {
        public:
            String doGet(const void* target) const;
            void doSet(void* target, const String& val);
        };

        static CmdBillboardType msBillboardTypeCmd;
        static CmdBillboardOrigin msBillboardOriginCmd;
        static CmdBillboardRotationType msBillboardRotationTypeCmd;
        static CmdCommonDirection msCommonDirectionCmd;
        static CmdCommonUpVector msCommonUpVectorCmd;
        static CmdPointRendering msPointRenderingCmd;
        static CmdAccurateFacing msAccurateFacingCmd;
        static CmdStacksAndSlices msStacksAndSlicesCmd;
        static CmdSpeedRelativedSizeFactor msSpeedRelativedSizeFactorCmd;

        /// @copydoc BillboardSet::setTextureStacksAndSlices
        void setTextureStacksAndSlices(uchar stacks, uchar slices)
        {
            mStacksSlices = Vector2(stacks, slices); // cache for get call
            mBillboardSet->setTextureStacksAndSlices(stacks, slices);
        }

        const Vector2& getTextureStacksAndSlices() const { return mStacksSlices; }

        /// @copydoc BillboardSet::setBillboardType
        void setBillboardType(BillboardType bbt) { mBillboardSet->setBillboardType(bbt); }
        /// @copydoc BillboardSet::getBillboardType
        BillboardType getBillboardType(void) const { return mBillboardSet->getBillboardType(); }
        /// @copydoc BillboardSet::setUseAccurateFacing
        void setUseAccurateFacing(bool acc) { mBillboardSet->setUseAccurateFacing(acc); }
        /// @copydoc BillboardSet::getUseAccurateFacing
        bool getUseAccurateFacing(void) const { return mBillboardSet->getUseAccurateFacing(); }
        /// @copydoc BillboardSet::setBillboardOrigin
        void setBillboardOrigin(BillboardOrigin origin) { mBillboardSet->setBillboardOrigin(origin); }
        /// @copydoc BillboardSet::getBillboardOrigin
        BillboardOrigin getBillboardOrigin(void) const { return mBillboardSet->getBillboardOrigin(); }
        /// @copydoc BillboardSet::setBillboardRotationType
        void setBillboardRotationType(BillboardRotationType rotationType)
        {
            mBillboardSet->setBillboardRotationType(rotationType);
        }
        /// @copydoc BillboardSet::getBillboardRotationType
        BillboardRotationType getBillboardRotationType() const
        {
            return mBillboardSet->getBillboardRotationType();
        }
        /// @copydoc BillboardSet::setCommonDirection
        void setCommonDirection(const Vector3& vec) { mBillboardSet->setCommonDirection(vec); }
        /// @copydoc BillboardSet::getCommonDirection
        const Vector3& getCommonDirection(void) const { return mBillboardSet->getCommonDirection(); }
        /// @copydoc BillboardSet::setCommonUpVector
        void setCommonUpVector(const Vector3& vec) { mBillboardSet->setCommonUpVector(vec); }
        /// @copydoc BillboardSet::getCommonUpVector
        const Vector3& getCommonUpVector(void) const { return mBillboardSet->getCommonUpVector(); }
        /// @copydoc BillboardSet::setPointRenderingEnabled
        void setPointRenderingEnabled(bool enabled) { mBillboardSet->setPointRenderingEnabled(enabled); }
        /// @copydoc BillboardSet::isPointRenderingEnabled
        bool isPointRenderingEnabled(void) const { return mBillboardSet->isPointRenderingEnabled(); }

        void setSpeedRelativedSizeFactor(Real factor);
        Real getSpeedRelativedSizeFactor(void) const;

        /// @copydoc ParticleSystemRenderer::getType
        const String& getType(void) const;
        /// @copydoc ParticleSystemRenderer::_updateRenderQueue
        void _updateRenderQueue(RenderQueue* queue, 
            std::vector<Particle*>& currentParticles, bool cullIndividually);

        void _setMaterial(MaterialPtr& mat) 
        {
            mBillboardSet->setMaterial(mat);
        }
        /// @copydoc ParticleSystemRenderer::_notifyCurrentCamera
        void _notifyCurrentCamera(Camera* cam);
        /// @copydoc ParticleSystemRenderer::_notifyParticleRotated
        void _notifyParticleRotated(void)
        {
            mBillboardSet->_notifyBillboardRotated();
        }
        /// @copydoc ParticleSystemRenderer::_notifyParticleResized
        void _notifyParticleResized(void)
        {
            mBillboardSet->_notifyBillboardResized();
        }
        /// @copydoc ParticleSystemRenderer::_notifyParticleQuota
        void _notifyParticleQuota(size_t quota) { mBillboardSet->setPoolSize(quota); }
        /// @copydoc ParticleSystemRenderer::_notifyAttached
        void _notifyAttached(Node* parent, bool isTagPoint = false)
        {
            mBillboardSet->_notifyAttached(parent, isTagPoint);
        }
        /// @copydoc ParticleSystemRenderer::_notifyDefaultDimensions
        void _notifyDefaultDimensions(Real width, Real height)
        {
            mBillboardSet->setDefaultDimensions(width, height);
        }
        /// @copydoc ParticleSystemRenderer::setRenderQueueGroup
        void setRenderQueueGroup(uint8 queueID) { }
        /// @copydoc MovableObject::setRenderQueueGroupAndPriority
        void setRenderQueueGroupAndPriority(uint8 queueID, ushort priority)
        {
           
        }
        /// @copydoc ParticleSystemRenderer::setKeepParticlesInLocalSpace
        void setKeepParticlesInLocalSpace(bool keepLocal)
        {
            mBillboardSet->setBillboardsInWorldSpace(!keepLocal);
        }
        /// @copydoc ParticleSystemRenderer::_getSortMode
        SortMode _getSortMode(void) const { return mBillboardSet->_getSortMode(); }

        Renderable* getRenderable()
        {
            return mBillboardSet;
        }
        /// Access BillboardSet in use
        BillboardSet* getBillboardSet(void) const { return mBillboardSet; }

        virtual bool loadFromStream(Serializer* pSerializer, DataStreamPtr& stream);
        virtual char* readFromBuffer(char* pCurrent);
        void _notifyBoundingBox(const AxisAlignedBox& aabb) ;

        void _notifyCastShadows(bool enabled)  {  }
    };



    /** Factory class for BillboardParticleRenderer */
    class  BillboardParticleRendererFactory : public ParticleSystemRendererFactory
    {
    public:
        /// @copydoc FactoryObj::getType
        const String& getType() const;
        /// @copydoc FactoryObj::createInstance
        ParticleSystemRenderer* createInstance( const String& name );
    };
    /** @} */
    /** @} */

} // namespace Ogre


#endif // __BillboardParticleRenderer_H__

