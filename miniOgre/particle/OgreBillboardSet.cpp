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

#include "OgreBillboardSet.h"
#include "OgreBillboard.h"
#include "OgreParticle.h"
#include "OgreMaterial.h"
#include "OgreMaterialManager.h"
#include "OgreRadixSort.h"
#include "OgreCamera.h"
#include "OgreNode.h"
#include "OgreSceneNode.h"
#include "OgreVertexData.h"
#include "OgreIndexData.h"
#include "OgreVertexDeclaration.h"
#include "OgreSceneManager.h"
#include "OgreRoot.h"
#include "OgreStringConverter.h"
#include "OgreHardwareIndexBuffer.h"
#define USE_VIDEO_DYN_BUFFER 1
namespace Ogre {
    //-----------------------------------------------------------------------
    BillboardSet::BillboardSet() :
        MoveObject(std::string("billboardset")),
        mBoundingRadius(0.0f),
        mOriginType(BBO_CENTER),
        mRotationType(BBR_TEXCOORD),
        mAutoExtendPool(true),
        mSortingEnabled(false),
        mAccurateFacing(false),
        mWorldSpace(false),
        mCullIndividual(false),
        mBillboardType(BBT_POINT),
        mCommonDirection(Ogre::Vector3::UNIT_Z),
        mCommonUpVector(Vector3::UNIT_Y),
        mPointRendering(false),
        mBuffersCreated(false),
        mPoolSize(0),
        mExternalData(false),
        mAutoUpdate(true),
        mBillboardDataChanged(true),
        mFirstNotifyCamera(true)
    {
        mUAltasNum = 0;
        mVAltasNum = 0;
        mTextureAltasIndex = -1;
        mAllDefaultSize = true;
        mAllDefaultRotation = true;
        setDefaultDimensions(100, 100);
        mMaterial = MaterialManager::getSingleton().getDefaultMaterial();
        mMaterial->load(nullptr);
        setTextureStacksAndSlices(1, 1);
    }

    //-----------------------------------------------------------------------
    BillboardSet::BillboardSet(
        const String& name,
        unsigned int poolSize,
        bool externalData) :
        MoveObject(name),
        mBoundingRadius(0.0f),
        mOriginType(BBO_CENTER),
        mRotationType(BBR_TEXCOORD),
        mAutoExtendPool(true),
        mSortingEnabled(false),
        mAccurateFacing(false),
        mWorldSpace(false),
        mActiveBillboards(0),
        mCullIndividual(false),
        mBillboardType(BBT_POINT),
        mCommonDirection(Ogre::Vector3::UNIT_Z),
        mCommonUpVector(Vector3::UNIT_Y),
        mPointRendering(false),
        mBuffersCreated(false),
        mPoolSize(poolSize),
        mExternalData(externalData),
        mAutoUpdate(true),
        mBillboardDataChanged(true)
    {
        mUAltasNum = 0;
        mVAltasNum = 0;
        mTextureAltasIndex = -1;
        mAllDefaultSize = true;
        mAllDefaultRotation = true;
        setDefaultDimensions(100, 100);
        mMaterial = MaterialManager::getSingleton().getDefaultMaterial();
        //mMaterial->load();
        setPoolSize(poolSize);
        setTextureStacksAndSlices(1, 1);
    }
    //-----------------------------------------------------------------------
    BillboardSet::~BillboardSet()
    {
        // Free pool items
        BillboardPool::iterator i;
        for (i = mBillboardPool.begin(); i != mBillboardPool.end(); ++i)
        {
            OGRE_DELETE* i;
        }

        // Delete shared buffers
        _destroyBuffers();
    }
    //-----------------------------------------------------------------------
    Billboard* BillboardSet::createBillboard(
        const Vector3& position,
        const ColourValue& colour)
    {
        if (mActiveBillboards == mBillboardPool.size())
        {
            if (mAutoExtendPool)
            {
                setPoolSize(getPoolSize() * 2);
            }
            else
            {
                return 0;
            }
        }

        // Get a new billboard
        Billboard* newBill = mBillboardPool[mActiveBillboards++];
        newBill->setPosition(position);
        newBill->setColour(colour);
        newBill->mDirection = Vector3::ZERO;
        newBill->setRotation(Radian(0));
        newBill->setTexcoordIndex(0);
        newBill->resetDimensions();
        newBill->_notifyOwner(this);

        // Merge into bounds
        Real adjust = std::max(mDefaultWidth, mDefaultHeight);
        Vector3 vecAdjust(adjust, adjust, adjust);
        Vector3 newMin = position - vecAdjust;
        Vector3 newMax = position + vecAdjust;

        mAABB.merge(newMin);
        mAABB.merge(newMax);

        mBoundingRadius = Math::boundingRadiusFromAABB(mAABB);

        return newBill;
    }

    //-----------------------------------------------------------------------
    void BillboardSet::clear()
    {
        mActiveBillboards = 0;
    }

    //-----------------------------------------------------------------------
    Billboard* BillboardSet::getBillboard(unsigned int index) const
    {
        assert(index < mActiveBillboards && "Billboard index out of bounds.");
        return mBillboardPool[index];
    }

    //-----------------------------------------------------------------------
    void BillboardSet::removeBillboard(unsigned int index)
    {
        assert(index < mActiveBillboards && "Billboard isn't in the active list.");
        std::swap(mBillboardPool[index], mBillboardPool[--mActiveBillboards]);
    }

    //-----------------------------------------------------------------------
    void BillboardSet::removeBillboard(Billboard* pBill)
    {
        auto it = std::find(mBillboardPool.begin(), mBillboardPool.begin() + mActiveBillboards, pBill);
        removeBillboard(std::distance(mBillboardPool.begin(), it));
    }
    //-----------------------------------------------------------------------
    void BillboardSet::setMaterialName(const String& name, const String& groupName /* = ResourceGroupManager::AUTODETECT_RESOURCE_GROUP_NAME */)
    {
        mMaterial = MaterialManager::getSingleton().getByName(name, groupName);

        if (!mMaterial)
            OGRE_EXCEPT(Exception::ERR_ITEM_NOT_FOUND, "Could not find material " + name,
                "BillboardSet::setMaterialName");

        /* Ensure that the new material was loaded (will not load again if
           already loaded anyway)
        */
        mMaterial->load(nullptr);
    }

    //-----------------------------------------------------------------------
    void BillboardSet::_sortBillboards(Camera* cam)
    {
        static RadixSort<BillboardPool, Billboard*, float> mRadixSorter;

        switch (_getSortMode())
        {
        case SM_DIRECTION:
            mRadixSorter.sort(mBillboardPool.begin(), mBillboardPool.begin() + mActiveBillboards,
                SortByDirectionFunctor(-mCamDir));
            break;
        case SM_DISTANCE:
            mRadixSorter.sort(mBillboardPool.begin(), mBillboardPool.begin() + mActiveBillboards,
                SortByDistanceFunctor(mCamPos));
            break;
        }
    }
    BillboardSet::SortByDirectionFunctor::SortByDirectionFunctor(const Vector3& dir)
        : sortDir(dir)
    {
    }
    float BillboardSet::SortByDirectionFunctor::operator()(Billboard* bill) const
    {
        return sortDir.dotProduct(bill->getPosition());
    }
    BillboardSet::SortByDistanceFunctor::SortByDistanceFunctor(const Vector3& pos)
        : sortPos(pos)
    {
    }
    float BillboardSet::SortByDistanceFunctor::operator()(Billboard* bill) const
    {
        // Sort descending by squared distance
        return -(sortPos - bill->getPosition()).squaredLength();
    }
    //-----------------------------------------------------------------------
    SortMode BillboardSet::_getSortMode(void) const
    {
        // Need to sort by distance if we're using accurate facing, or perpendicular billboard type.
        if (mAccurateFacing ||
            mBillboardType == BBT_PERPENDICULAR_SELF ||
            mBillboardType == BBT_PERPENDICULAR_COMMON)
        {
            return SM_DISTANCE;
        }
        else
        {
            return SM_DIRECTION;
        }
    }

    const String& BillboardSet::getMaterialName(void) const 
    { 
        return mMaterial->getName(); 
    }
    //-----------------------------------------------------------------------
    void BillboardSet::_notifyCurrentCamera(Camera* cam)
    {
        mCurrentCamera = cam;

        // Calculate camera orientation and position
        mCamQ = mCurrentCamera->getDerivedOrientation();
        mCamPos = mCurrentCamera->getDerivedPosition();
        if (!mWorldSpace)
        {
            // Default behaviour is that billboards are in local node space
            // so orientation of camera (in world space) must be reverse-transformed
            // into node space
            mCamQ = mParent->convertWorldToLocalOrientation(mCamQ);
            mCamPos = mParent->convertWorldToLocalPosition(mCamPos);
        }

        // Camera direction points down -Z
        mCamDir = mCamQ * Vector3::NEGATIVE_UNIT_Z;
    }
    //-----------------------------------------------------------------------
    void BillboardSet::beginBillboards(size_t numBillboards)
    {
        // create vertex and index buffers if they haven't already been
        if (!mBuffersCreated)
            _createBuffers();

        // Only calculate vertex offets et al if we're not point rendering
        if (!mPointRendering)
        {

            // Get offsets for origin type
            getParametricOffsets(mLeftOff, mRightOff, mTopOff, mBottomOff);

            // Generate axes etc up-front if not oriented per-billboard
            if (mBillboardType != BBT_ORIENTED_SELF &&
                mBillboardType != BBT_PERPENDICULAR_SELF &&
                !(mAccurateFacing && mBillboardType != BBT_PERPENDICULAR_COMMON))
            {
                genBillboardAxes(&mCamX, &mCamY);

                /* If all billboards are the same size we can precalculate the
                   offsets and just use '+' instead of '*' for each billboard,
                   and it should be faster.
                */
                genVertOffsets(mLeftOff, mRightOff, mTopOff, mBottomOff,
                    mDefaultWidth, mDefaultHeight, mCamX, mCamY, mVOffset);

            }
        }

        // Init num visible
        mNumVisibleBillboards = 0;

        auto back = mVertexData->getBuffer(0);
        // Lock the buffer
        if (numBillboards) // optimal lock
        {
            // clamp to max
            numBillboards = std::min(mPoolSize, numBillboards);

            size_t billboardSize;
            if (mPointRendering)
            {
                // just one vertex per billboard (this also excludes texcoords)
                billboardSize = mVertexData->getVertexSize(0);
            }
            else
            {
                // 4 corners
                billboardSize = mVertexData->getVertexSize(0) * 4;
            }


            mLockPtr = reinterpret_cast<float*>(back->lock());
        }
        else // lock the entire thing
        {
            mLockPtr = reinterpret_cast<float*>(back->lock());
        }

    }
    //-----------------------------------------------------------------------
    void BillboardSet::injectBillboard(const Billboard& bb)
    {
        // Don't accept injections beyond pool size
        if (mNumVisibleBillboards == mPoolSize) return;

        // Skip if not visible (NB always true if not bounds checking individual billboards)
        if (!billboardVisible(mCurrentCamera, bb)) return;

        // Increment visibles
        mNumVisibleBillboards++;

        if (mPointRendering)
        {
            genPointVertices(bb);
            return;
        }

        if ((mBillboardType == BBT_ORIENTED_SELF || mBillboardType == BBT_PERPENDICULAR_SELF ||
            (mAccurateFacing && mBillboardType != BBT_PERPENDICULAR_COMMON)))
        {
            // Have to generate axes & offsets per billboard
            genBillboardAxes(&mCamX, &mCamY, &bb);
        }

        if ((mBillboardType == BBT_ORIENTED_SELF || mBillboardType == BBT_PERPENDICULAR_SELF ||
            bb.mOwnDimensions || (mAccurateFacing && mBillboardType != BBT_PERPENDICULAR_COMMON)))
        {
            // If it has own dimensions, or self-oriented, gen offsets
            Vector3 vOwnOffset[4];
            Real width = bb.mOwnDimensions ? bb.mWidth : mDefaultWidth;
            Real height = bb.mOwnDimensions ? bb.mHeight : mDefaultHeight;
            genVertOffsets(mLeftOff, mRightOff, mTopOff, mBottomOff,
                width, height, mCamX, mCamY, vOwnOffset);
            genQuadVertices(vOwnOffset, bb);
        }
        else
        {
            // Use default dimension, already computed before the loop, for faster creation
            genQuadVertices(mVOffset, bb);
        }
    }

    void BillboardSet::injectBillboard(Particle* p)
    {

        // If they're all the same size or we're point rendering
        if (mAllDefaultSize || mPointRendering)
        {
            /* No per-billboard checking, just blast through.
            Saves us an if clause every billboard which may
            make a difference.
            */

            if (!mPointRendering &&
                (mBillboardType == BBT_ORIENTED_SELF ||
                    mBillboardType == BBT_PERPENDICULAR_SELF ||
                    (mAccurateFacing && mBillboardType != BBT_PERPENDICULAR_COMMON)))
            {
                genVertOffsets(mDefaultWidth, mDefaultHeight, p->mXAxis, p->mYAxis, mVOffset);
            }
#if USE_VIDEO_DYN_BUFFER
            genVertices(mVOffset, p);
#else
            genMemoryBufferVertices(mVOffset, p);
#endif
        }
        else // not all default size and not point rendering
        {
            Vector3 vOwnOffset[4];
            // If it has own dimensions, or self-oriented, gen offsets
            if (mBillboardType == BBT_ORIENTED_SELF ||
                mBillboardType == BBT_PERPENDICULAR_SELF ||
                (mAccurateFacing && mBillboardType != BBT_PERPENDICULAR_COMMON))
            {
                // Generate using own dimensions
                genVertOffsets(p->mWidth, p->mHeight, p->mXAxis, p->mYAxis, vOwnOffset);
                // Create vertex data
#if USE_VIDEO_DYN_BUFFER
                genVertices(vOwnOffset, p);
#else
                genMemoryBufferVertices(vOwnOffset, p);
#endif
            }
            else // Use default dimension, already computed before the loop, for faster creation
            {
                if (p->mOwnDimensions)
                {
                    genVertOffsets(p->mWidth, p->mHeight, mCamX, mCamY, mVOffset);
                }
#if USE_VIDEO_DYN_BUFFER
                genVertices(mVOffset, p);
#else
                genMemoryBufferVertices(mVOffset, p);
#endif
            }
        }
        // Increment visibles
        mNumVisibleBillboards++;
    }

    //-----------------------------------------------------------------------
    void BillboardSet::endBillboards(void)
    {
        mVertexData->getBuffer(0)->unlock();
    }
    //-----------------------------------------------------------------------
    void BillboardSet::setBounds(const AxisAlignedBox& box, Real radius)
    {
        mAABB = box;
        mBoundingRadius = radius;
    }
    //-----------------------------------------------------------------------
    void BillboardSet::_updateBounds(void)
    {
        if (mActiveBillboards == 0)
        {
            // No billboards, null bbox
            mAABB.setNull();
            mBoundingRadius = 0.0f;
        }
        else
        {
            mAABB.setNull();
            auto iend = mBillboardPool.begin() + mActiveBillboards;
            Ogre::Matrix4 invWorld;
            bool invert = mWorldSpace && getParentSceneNode();
            if (invert)
                invWorld = getParentSceneNode()->_getFullTransform().inverse();

            for (auto i = mBillboardPool.begin(); i != iend; ++i)
            {
                Vector3 pos = (*i)->getPosition();
                // transform from world space to local space
                if (invert)
                    pos = invWorld * pos;

                mAABB.merge(pos);
            }
            // Adjust for billboard size
            Real adjust = std::max(mDefaultWidth, mDefaultHeight);
            Vector3 vecAdjust(adjust, adjust, adjust);

            mAABB.setExtents(mAABB.getMinimum() - vecAdjust, mAABB.getMaximum() + vecAdjust);
            mBoundingRadius = Math::boundingRadiusFromAABB(mAABB);
        }

        if (mParent)
            mParent->needUpdate();

    }

    //-----------------------------------------------------------------------
    void BillboardSet::_updateRenderQueue(RenderQueue* queue)
    {
        // If we're driving this from our own data, update geometry if need to.
        if (!mExternalData && (mAutoUpdate || mBillboardDataChanged || !mBuffersCreated))
        {
            if (mSortingEnabled)
            {
                _sortBillboards(mCurrentCamera);
            }

            beginBillboards(mActiveBillboards);
            auto iend = mBillboardPool.begin() + mActiveBillboards;
            for (auto it = mBillboardPool.begin(); it != iend; ++it)
            {
                injectBillboard(*(*it));
            }
            endBillboards();
            mBillboardDataChanged = false;
        }

      
    }

    void BillboardSet::setMaterial(const MaterialPtr& material)
    {
        assert(material);
        mMaterial = material;
    }

   

    //-----------------------------------------------------------------------
    void BillboardSet::getWorldTransforms(Matrix4* xform) const
    {
        if (mWorldSpace)
        {
            *xform = Matrix4::IDENTITY;
        }
        else
        {
            *xform = _getParentNodeFullTransform();
        }
    }

    void BillboardSet::_notifyBillboardResized(void)
    {
        mAllDefaultSize = false;
    }

    /** Internal callback used by Billboards to notify their parent that they have been rotated..
    */
    void BillboardSet::_notifyBillboardRotated(void)
    {
        mAllDefaultRotation = false;
    }

    //-----------------------------------------------------------------------
    void BillboardSet::setPoolSize(size_t size)
    {
        // If we're driving this from our own data, allocate billboards
        if (!mExternalData)
        {
            // Never shrink below size()
            size_t currSize = mBillboardPool.size();
            if (currSize >= size)
                return;

            this->increasePool(size);
        }

        mPoolSize = size;

        _destroyBuffers();
    }

    //-----------------------------------------------------------------------
    void BillboardSet::_createBuffers(void)
    {
        /* Allocate / reallocate vertex data
           Note that we allocate enough space for ALL the billboards in the pool, but only issue
           rendering operations for the sections relating to the active billboards
        */

        /* Alloc positions   ( 1 or 4 verts per billboard, 3 components )
                 colours     ( 1 x RGBA per vertex )
                 indices     ( 6 per billboard ( 2 tris ) if not point rendering )
                 tex. coords ( 2D coords, 1 or 4 per billboard )
        */

        // Warn if user requested an invalid setup
        // Do it here so it only appears once
        if (mPointRendering && mBillboardType != BBT_POINT)
        {

   
        }

        mVertexData.reset(new VertexData());
        if (mPointRendering)
            mVertexData->setVertexCount(mPoolSize);
        else
            mVertexData->setVertexCount(mPoolSize * 4);



        // Vertex declaration
        VertexDeclaration* decl = mVertexData->getVertexDeclaration();

        size_t offset = 0;
        offset += mVertexData->addElement(0, 0, offset, VET_FLOAT3, VES_POSITION).getSize();
        offset += mVertexData->addElement(0, 0, offset, VET_UBYTE4_NORM, VES_DIFFUSE).getSize();
        // Texture coords irrelevant when enabled point rendering (generated
        // in point sprite mode, and unused in standard point mode)
        if (!mPointRendering)
        {
            mVertexData->addElement(0, 0, offset, VET_FLOAT2, VES_TEXTURE_COORDINATES);
        }



  
        auto vertexSize = decl->getVertexSize(0);
        
        mVertexData->addBindBuffer(0, vertexSize, mVertexData->getVertexCount());

        if (!mPointRendering)
        {
            mIndexData.reset(new IndexData());
            mIndexData->mIndexStart = 0;
            mIndexData->mIndexCount = mPoolSize * 6;
            mIndexData->createBuffer(2, 6 * mIndexData->mIndexCount);
            /* Create indexes (will be the same every frame)
               Using indexes because it means 1/3 less vertex transforms (4 instead of 6)

               Billboard layout relative to camera:

                0-----1
                |    /|
                |  /  |
                |/    |
                2-----3
            */

            HardwareBufferLockGuard lockGuard(mIndexData->mIndexBuffer.get());
            uint16_t* pIdx = (uint16_t*)lockGuard.data();

            for (
                size_t idx, idxOff, bboard = 0;
                bboard < mPoolSize;
                ++bboard)
            {
                // Do indexes
                idx = bboard * 6;
                idxOff = bboard * 4;

                pIdx[idx] = static_cast<unsigned short>(idxOff); // + 0;, for clarity
                pIdx[idx + 1] = static_cast<unsigned short>(idxOff + 2);
                pIdx[idx + 2] = static_cast<unsigned short>(idxOff + 1);
                pIdx[idx + 3] = static_cast<unsigned short>(idxOff + 1);
                pIdx[idx + 4] = static_cast<unsigned short>(idxOff + 2);
                pIdx[idx + 5] = static_cast<unsigned short>(idxOff + 3);

            }
        }

        mBuffersCreated = true;
    }
    //-----------------------------------------------------------------------
    void BillboardSet::_destroyBuffers(void)
    {
        mVertexData.reset();
        mIndexData.reset();

        mBuffersCreated = false;
    }

    //-----------------------------------------------------------------------
    void BillboardSet::getParametricOffsets(
        Real& left, Real& right, Real& top, Real& bottom)
    {
        switch (mOriginType)
        {
        case BBO_TOP_LEFT:
            left = 0.0f;
            right = 1.0f;
            top = 0.0f;
            bottom = -1.0f;
            break;

        case BBO_TOP_CENTER:
            left = -0.5f;
            right = 0.5f;
            top = 0.0f;
            bottom = -1.0f;
            break;

        case BBO_TOP_RIGHT:
            left = -1.0f;
            right = 0.0f;
            top = 0.0f;
            bottom = -1.0f;
            break;

        case BBO_CENTER_LEFT:
            left = 0.0f;
            right = 1.0f;
            top = 0.5f;
            bottom = -0.5f;
            break;

        case BBO_CENTER:
            left = -0.5f;
            right = 0.5f;
            top = 0.5f;
            bottom = -0.5f;
            break;

        case BBO_CENTER_RIGHT:
            left = -1.0f;
            right = 0.0f;
            top = 0.5f;
            bottom = -0.5f;
            break;

        case BBO_BOTTOM_LEFT:
            left = 0.0f;
            right = 1.0f;
            top = 1.0f;
            bottom = 0.0f;
            break;

        case BBO_BOTTOM_CENTER:
            left = -0.5f;
            right = 0.5f;
            top = 1.0f;
            bottom = 0.0f;
            break;

        case BBO_BOTTOM_RIGHT:
            left = -1.0f;
            right = 0.0f;
            top = 1.0f;
            bottom = 0.0f;
            break;
        }
    }

    const Ogre::Matrix4& BillboardSet::getModelMatrix()
    {
        if (mWorldSpace)
        {
            return Matrix4::IDENTITY;
        }
        else
        {
            return mParent->getWorldModelMatrix();
        }
    }

    VertexData* BillboardSet::getVertexData()
    {
        return mVertexData.get();
    }

    IndexData* BillboardSet::getIndexData()
    {
        return mIndexData.get();
    }

    IndexDataView* BillboardSet::getIndexView()
    {
        if (!mIndexDataView)
        {
            mIndexDataView = std::make_unique<IndexDataView>();
            mIndexDataView->mBaseVertexLocation = 0;
            mIndexDataView->mIndexLocation = 0;
        }

        mIndexDataView->mIndexCount = mNumVisibleBillboards * 6;

        return mIndexDataView.get();
    }
    //-----------------------------------------------------------------------
    bool BillboardSet::billboardVisible(Camera* cam, const Billboard& bill)
    {
        // Return always visible if not culling individually
        if (!mCullIndividual) return true;

        // Cull based on sphere (have to transform less)
        Sphere sph;
        Matrix4 xworld;

        getWorldTransforms(&xworld);

        sph.setCenter(xworld * bill.mPosition);

        if (bill.mOwnDimensions)
        {
            sph.setRadius(std::max(bill.mWidth, bill.mHeight));
        }
        else
        {
            sph.setRadius(std::max(mDefaultWidth, mDefaultHeight));
        }

        return cam->isVisible(sph);

    }
    //-----------------------------------------------------------------------
    void BillboardSet::increasePool(size_t size)
    {
        size_t oldSize = mBillboardPool.size();

        // Increase size
        mBillboardPool.resize(size);

        // Create new billboards
        for (size_t i = oldSize; i < size; ++i)
            mBillboardPool[i] = OGRE_NEW Billboard();

    }
    //-----------------------------------------------------------------------
    void BillboardSet::genBillboardAxes(Vector3* pX, Vector3* pY, const Billboard* bb)
    {
        // If we're using accurate facing, recalculate camera direction per BB
        if (mAccurateFacing &&
            (mBillboardType == BBT_POINT ||
                mBillboardType == BBT_ORIENTED_COMMON ||
                mBillboardType == BBT_ORIENTED_SELF))
        {
            // cam -> bb direction
            mCamDir = bb->mPosition - mCamPos;
            mCamDir.normalise();
        }


        switch (mBillboardType)
        {
        case BBT_POINT:
            if (mAccurateFacing)
            {
                // Point billboards will have 'up' based on but not equal to cameras
                // Use pY temporarily to avoid allocation
                *pY = mCamQ * Vector3::UNIT_Y;
                *pX = mCamDir.crossProduct(*pY);
                pX->normalise();
                *pY = pX->crossProduct(mCamDir); // both normalised already
            }
            else
            {
                // Get camera axes for X and Y (depth is irrelevant)
                *pX = mCamQ * Vector3::UNIT_X;
                *pY = mCamQ * Vector3::UNIT_Y;
            }
            break;

        case BBT_ORIENTED_COMMON:
            // Y-axis is common direction
            // X-axis is cross with camera direction
            *pY = mCommonDirection;
            *pX = mCamDir.crossProduct(*pY);
            pX->normalise();
            break;

        case BBT_ORIENTED_SELF:
            // Y-axis is direction
            // X-axis is cross with camera direction
            // Scale direction first
            *pY = bb->mDirection;
            *pX = mCamDir.crossProduct(*pY);
            pX->normalise();
            break;

        case BBT_PERPENDICULAR_COMMON:
            // X-axis is up-vector cross common direction
            // Y-axis is common direction cross X-axis
            *pX = mCommonUpVector.crossProduct(mCommonDirection);
            *pY = mCommonDirection.crossProduct(*pX);
            break;

        case BBT_PERPENDICULAR_SELF:
            // X-axis is up-vector cross own direction
            // Y-axis is own direction cross X-axis
            *pX = mCommonUpVector.crossProduct(bb->mDirection);
            pX->normalise();
            *pY = bb->mDirection.crossProduct(*pX); // both should be normalised
            break;
        }

    }

    void BillboardSet::genBillboardAxes(Vector3* pX, Vector3* pY, const Particle* pParticle)
    {
        // If we're using accurate facing, recalculate camera direction per BB
        if (mAccurateFacing &&
            (mBillboardType == BBT_POINT ||
                mBillboardType == BBT_ORIENTED_COMMON ||
                mBillboardType == BBT_ORIENTED_SELF))
        {
            // cam -> bb direction
            mCamDir = pParticle->mPosition - mCamPos;
            mCamDir.normalise();
        }

        Vector3 dir;

        switch (mBillboardType)
        {
        case BBT_POINT:
            if (mAccurateFacing)
            {
                // Point billboards will have 'up' based on but not equal to cameras
                // Use pY temporarily to avoid allocation
                *pY = mCamQ * Vector3::UNIT_Y;
                *pX = mCamDir.crossProduct(*pY);
                pX->normalise();
                *pY = pX->crossProduct(mCamDir); // both normalised already
            }
            else
            {
                if (!mWorldSpace)
                {
                    // Get camera axes for X and Y (depth is irrelevant)
                    *pX = mCamQ * Vector3::UNIT_X;
                    *pY = mCamQ * Vector3::UNIT_Y;
                }
                else
                {
                    //ʹ��camera�����ֵ
                    // Get camera axes for X and Y (depth is irrelevant)
                    *pX = mCurrentCamera->getDerivedRight();
                    *pY = mCurrentCamera->getDerivedUp();
                }

            }
            break;

        case BBT_ORIENTED_COMMON:
            // Y-axis is common direction
            // X-axis is cross with camera direction
            *pY = mCommonDirection;
            *pX = mCamDir.crossProduct(*pY);
            pX->normalise();
            break;

        case BBT_ORIENTED_SELF:
            // Y-axis is direction
            // X-axis is cross with camera direction
            // Scale direction first
            dir = pParticle->mDirection;
            if (mSpeedRelativedSizeFactor > 0.0f)
            {
                dir *= mSpeedRelativedSizeFactor;
            }
            *pY = dir;
            *pX = mCamDir.crossProduct(*pY);
        
            pX->normalise();
            break;

        case BBT_PERPENDICULAR_COMMON:
            // X-axis is up-vector cross common direction
            // Y-axis is common direction cross X-axis
            *pX = mCommonUpVector.crossProduct(mCommonDirection);
            *pY = mCommonDirection.crossProduct(*pX);
            break;

        case BBT_PERPENDICULAR_SELF:
            // X-axis is up-vector cross own direction
            // Y-axis is own direction cross X-axis
            dir = pParticle->mDirection;
            dir.normalise();
            *pX = mCommonUpVector.crossProduct(dir);
            pX->normalise();
            *pY = dir.crossProduct(*pX); // both should be normalised
            break;
        }

    }

    //-----------------------------------------------------------------------
    uint32 BillboardSet::getTypeFlags(void) const
    {
        return SceneManager::FX_TYPE_MASK;
    }

    void BillboardSet::updateOrientationAndOffset(const  std::vector<Particle*>& currentParticles, Camera* cam)
    {
        bool bCameraChange = false;

        if (mCurrentCamera != cam)
        {
            mCurrentCamera = cam;

            bCameraChange = true;
        }

        Quaternion camQ = mCurrentCamera->getDerivedOrientation();
        Vector3 camPos = mCurrentCamera->getDerivedPosition();
        Vector3 camDir;

        if (!mWorldSpace)  // �����ڱ��ؿռ�
        {
            // Default behaviour is that billboards are in local node space
            // so orientation of camera (in world space) must be reverse-transformed
            // into node space

            Quaternion inverse = mParent->_getDerivedOrientation().UnitInverse();
            camQ = inverse * camQ;
            camPos = inverse * (camPos - mParent->_getDerivedPosition()) / mParent->_getDerivedScale();

            // Camera direction points down -Z
            camDir = camQ * Vector3::NEGATIVE_UNIT_Z;
        }
        else  // ����������ռ�
        {
            camDir = mCurrentCamera->getDerivedDirection();
        }

        if (!mCamQ.realEquals(camQ))
        {
            mCamQ = camQ;

            bCameraChange = true;
        }

        if (!mCamPos.realEquals(camPos))
        {
            mCamPos = camPos;

            bCameraChange = true;
        }

        if (!mCamDir.realEquals(camDir))
        {
            mCamDir = camDir;

            bCameraChange = true;
        }

        if (mFirstNotifyCamera)
        {
            //��һ�ε�ʱ�����mLeftOff��mRightOff��mTopOff��mBottomOff����Щֻ��Ҫ����һ�Ρ�
            // Get offsets for origin type
            getParametricOffsets(mLeftOff, mRightOff, mTopOff, mBottomOff);
        }

        //���camera�仯���ߵ�һ��ʱ��������set���õ�һЩֵ
        if (bCameraChange || mFirstNotifyCamera)
        {
            //ĳЩ��������ӵ�x���y������set��һ���ģ����������һ�ξ�����
            if (!(mAccurateFacing && mBillboardType != BBT_PERPENDICULAR_COMMON) &&
                (mBillboardType == BBT_ORIENTED_COMMON || mBillboardType == BBT_PERPENDICULAR_COMMON || mBillboardType == BBT_POINT))
            {
                updateOrientationAndOffsetPerSet();
            }
        }

        //ĳЩ��������ӵ�x���y����ÿ�����Ӷ���һ���ģ���Ҫÿ�����Ӽ���һ��
        if (!mPointRendering &&
            (mBillboardType == BBT_ORIENTED_SELF ||
                mBillboardType == BBT_PERPENDICULAR_SELF ||
                (mAccurateFacing && mBillboardType != BBT_PERPENDICULAR_COMMON)))
        {

            getParametricOffsets(mLeftOff, mRightOff, mTopOff, mBottomOff);

            for (auto i = currentParticles.begin();
                i != currentParticles.end(); ++i)
            {
                Particle* p = *i;

                bool bNeedRecal = bCameraChange || p->mNeedRecalAxis || mFirstNotifyCamera;
                if (bNeedRecal)
                {
                    genBillboardAxes(&p->mXAxis, &p->mYAxis, (const Particle*)p);
                    p->mNeedRecalAxis = false;
                }
            }
        }

        mFirstNotifyCamera = false;
    }

    void BillboardSet::updateOrientationAndOffsetPerSet()
    {
        genBillboardAxes(&mCamX, &mCamY, (const Particle*)NULL);
        genVertOffsets(mDefaultWidth, mDefaultHeight, mCamX, mCamY, mVOffset);
    }

    //-----------------------------------------------------------------------
    void BillboardSet::genPointVertices(const Billboard& bb)
    {
        RGBA colour = bb.mColour.getAsBYTE(); //todoeffect
        // Single vertex per billboard, ignore offsets
        // position
        *mLockPtr++ = bb.mPosition.x;
        *mLockPtr++ = bb.mPosition.y;
        *mLockPtr++ = bb.mPosition.z;
        // Colour

        memcpy(mLockPtr++, &colour, sizeof(RGBA));
        // No texture coords in point rendering
    }
    void BillboardSet::genQuadVertices(const Vector3* const offsets, const Billboard& bb)
    {
        RGBA colour = bb.mColour.getAsBYTE();

        // Texcoords
        assert(bb.mUseTexcoordRect || bb.mTexcoordIndex < mTextureCoords.size());
        const Ogre::FloatRect& r =
            bb.mUseTexcoordRect ? bb.mTexcoordRect : mTextureCoords[bb.mTexcoordIndex];

        if (bb.mRotation == Radian(0))
        {
            // Left-top
            // Positions
            *mLockPtr++ = offsets[0].x + bb.mPosition.x;
            *mLockPtr++ = offsets[0].y + bb.mPosition.y;
            *mLockPtr++ = offsets[0].z + bb.mPosition.z;
            // Colour
            memcpy(mLockPtr++, &colour, sizeof(RGBA));
            // Texture coords
            *mLockPtr++ = r.left;
            *mLockPtr++ = r.top;

            // Right-top
            // Positions
            *mLockPtr++ = offsets[1].x + bb.mPosition.x;
            *mLockPtr++ = offsets[1].y + bb.mPosition.y;
            *mLockPtr++ = offsets[1].z + bb.mPosition.z;
            // Colour
            memcpy(mLockPtr++, &colour, sizeof(RGBA));
            // Texture coords
            *mLockPtr++ = r.right;
            *mLockPtr++ = r.top;

            // Left-bottom
            // Positions
            *mLockPtr++ = offsets[2].x + bb.mPosition.x;
            *mLockPtr++ = offsets[2].y + bb.mPosition.y;
            *mLockPtr++ = offsets[2].z + bb.mPosition.z;
            // Colour
            memcpy(mLockPtr++, &colour, sizeof(RGBA));
            // Texture coords
            *mLockPtr++ = r.left;
            *mLockPtr++ = r.bottom;

            // Right-bottom
            // Positions
            *mLockPtr++ = offsets[3].x + bb.mPosition.x;
            *mLockPtr++ = offsets[3].y + bb.mPosition.y;
            *mLockPtr++ = offsets[3].z + bb.mPosition.z;
            // Colour
            memcpy(mLockPtr++, &colour, sizeof(RGBA));
            // Texture coords
            *mLockPtr++ = r.right;
            *mLockPtr++ = r.bottom;
        }
        else if (mRotationType == BBR_VERTEX)
        {
            // TODO: Cache axis when billboard type is BBT_POINT or BBT_PERPENDICULAR_COMMON
            Vector3 axis = (offsets[3] - offsets[0]).crossProduct(offsets[2] - offsets[1]).normalisedCopy();

            Matrix3 rotation;
            rotation.FromAngleAxis(axis, bb.mRotation);

            Vector3 pt;

            // Left-top
            // Positions
            pt = rotation * offsets[0];
            *mLockPtr++ = pt.x + bb.mPosition.x;
            *mLockPtr++ = pt.y + bb.mPosition.y;
            *mLockPtr++ = pt.z + bb.mPosition.z;
            // Colour
            memcpy(mLockPtr++, &colour, sizeof(RGBA));
            // Texture coords
            *mLockPtr++ = r.left;
            *mLockPtr++ = r.top;

            // Right-top
            // Positions
            pt = rotation * offsets[1];
            *mLockPtr++ = pt.x + bb.mPosition.x;
            *mLockPtr++ = pt.y + bb.mPosition.y;
            *mLockPtr++ = pt.z + bb.mPosition.z;
            // Colour
            memcpy(mLockPtr++, &colour, sizeof(RGBA));
            // Texture coords
            *mLockPtr++ = r.right;
            *mLockPtr++ = r.top;

            // Left-bottom
            // Positions
            pt = rotation * offsets[2];
            *mLockPtr++ = pt.x + bb.mPosition.x;
            *mLockPtr++ = pt.y + bb.mPosition.y;
            *mLockPtr++ = pt.z + bb.mPosition.z;
            // Colour
            memcpy(mLockPtr++, &colour, sizeof(RGBA));
            // Texture coords
            *mLockPtr++ = r.left;
            *mLockPtr++ = r.bottom;

            // Right-bottom
            // Positions
            pt = rotation * offsets[3];
            *mLockPtr++ = pt.x + bb.mPosition.x;
            *mLockPtr++ = pt.y + bb.mPosition.y;
            *mLockPtr++ = pt.z + bb.mPosition.z;
            // Colour
            memcpy(mLockPtr++, &colour, sizeof(RGBA));
            // Texture coords
            *mLockPtr++ = r.right;
            *mLockPtr++ = r.bottom;
        }
        else
        {
            const Real      cos_rot(Math::Cos(bb.mRotation));
            const Real      sin_rot(Math::Sin(bb.mRotation));

            float width = (r.right - r.left) / 2;
            float height = (r.bottom - r.top) / 2;
            float mid_u = r.left + width;
            float mid_v = r.top + height;

            float cos_rot_w = cos_rot * width;
            float cos_rot_h = cos_rot * height;
            float sin_rot_w = sin_rot * width;
            float sin_rot_h = sin_rot * height;

            // Left-top
            // Positions
            *mLockPtr++ = offsets[0].x + bb.mPosition.x;
            *mLockPtr++ = offsets[0].y + bb.mPosition.y;
            *mLockPtr++ = offsets[0].z + bb.mPosition.z;
            // Colour
            memcpy(mLockPtr++, &colour, sizeof(RGBA));
            // Texture coords
            *mLockPtr++ = mid_u - cos_rot_w + sin_rot_h;
            *mLockPtr++ = mid_v - sin_rot_w - cos_rot_h;

            // Right-top
            // Positions
            *mLockPtr++ = offsets[1].x + bb.mPosition.x;
            *mLockPtr++ = offsets[1].y + bb.mPosition.y;
            *mLockPtr++ = offsets[1].z + bb.mPosition.z;
            // Colour
            memcpy(mLockPtr++, &colour, sizeof(RGBA));
            // Texture coords
            *mLockPtr++ = mid_u + cos_rot_w + sin_rot_h;
            *mLockPtr++ = mid_v + sin_rot_w - cos_rot_h;

            // Left-bottom
            // Positions
            *mLockPtr++ = offsets[2].x + bb.mPosition.x;
            *mLockPtr++ = offsets[2].y + bb.mPosition.y;
            *mLockPtr++ = offsets[2].z + bb.mPosition.z;
            // Colour
            memcpy(mLockPtr++, &colour, sizeof(RGBA));
            // Texture coords
            *mLockPtr++ = mid_u - cos_rot_w - sin_rot_h;
            *mLockPtr++ = mid_v - sin_rot_w + cos_rot_h;

            // Right-bottom
            // Positions
            *mLockPtr++ = offsets[3].x + bb.mPosition.x;
            *mLockPtr++ = offsets[3].y + bb.mPosition.y;
            *mLockPtr++ = offsets[3].z + bb.mPosition.z;
            // Colour
            memcpy(mLockPtr++, &colour, sizeof(RGBA));
            // Texture coords
            *mLockPtr++ = mid_u + cos_rot_w - sin_rot_h;
            *mLockPtr++ = mid_v + sin_rot_w + cos_rot_h;
        }
    }

    void BillboardSet::genVertOffsets(Real width, Real height,
        const Vector3& x, const Vector3& y, Vector3* pDestVec)
    {
        Vector3 vLeftOff, vRightOff, vTopOff, vBottomOff;
        /* Calculate default offsets. Scale the axes by
        parametric offset and dimensions, ready to be added to
        positions.
        */

        vLeftOff = x * (mLeftOff * width);
        vRightOff = x * (mRightOff * width);
        vTopOff = y * (mTopOff * height);
        vBottomOff = y * (mBottomOff * height);

        // Make final offsets to vertex positions
        pDestVec[0] = vLeftOff + vTopOff;
        pDestVec[1] = vRightOff + vTopOff;
        pDestVec[2] = vLeftOff + vBottomOff;
        pDestVec[3] = vRightOff + vBottomOff;
    }
    //-----------------------------------------------------------------------
    void BillboardSet::genVertOffsets(Real inleft, Real inright, Real intop, Real inbottom,
        Real width, Real height, const Vector3& x, const Vector3& y, Vector3* pDestVec)
    {
        Vector3 vLeftOff, vRightOff, vTopOff, vBottomOff;
        /* Calculate default offsets. Scale the axes by
           parametric offset and dimensions, ready to be added to
           positions.
        */

        vLeftOff = x * (inleft * width);
        vRightOff = x * (inright * width);
        vTopOff = y * (intop * height);
        vBottomOff = y * (inbottom * height);

        // Make final offsets to vertex positions
        pDestVec[0] = vLeftOff + vTopOff;
        pDestVec[1] = vRightOff + vTopOff;
        pDestVec[2] = vLeftOff + vBottomOff;
        pDestVec[3] = vRightOff + vBottomOff;

    }

    void BillboardSet::genVertices(const Vector3* const offsets, Particle* p)
    {
        RGBA colour = p->mColour.getAsBYTE();
        //RGBA color;
        //Root::getSingleton().convertColourValue(p->colour, &colour);
        RGBA* pCol;

        // Texcoords
        /*assert( bb.mUseTexcoordRect || bb.mTexcoordIndex < mTextureCoords.size() );
        const Ogre::FloatRect & r =
            bb.mUseTexcoordRect ? bb.mTexcoordRect : mTextureCoords[bb.mTexcoordIndex];*/

        Ogre::FloatRect& r = mTextureCoords[0];

        if (mTextureAltasIndex != -1)
            r = mTextureCoords[this->mTextureAltasIndex];

        if (mPointRendering)
        {
            // Single vertex per billboard, ignore offsets
            // position
            *mLockPtr++ = p->mPosition.x;
            *mLockPtr++ = p->mPosition.y;
            *mLockPtr++ = p->mPosition.z;
            // Colour
            // Convert float* to RGBA*
            pCol = static_cast<RGBA*>(static_cast<void*>(mLockPtr));
            *pCol++ = colour;
            // Update lock pointer
            mLockPtr = static_cast<float*>(static_cast<void*>(pCol));
            // No texture coords in point rendering
        }
        else if (mAllDefaultRotation || p->mRotation == Radian(0))
        {
            // Left-top
            // Positions
            *mLockPtr++ = offsets[0].x + p->mPosition.x;
            *mLockPtr++ = offsets[0].y + p->mPosition.y;
            *mLockPtr++ = offsets[0].z + p->mPosition.z;
            // Colour
            // Convert float* to RGBA*
            pCol = static_cast<RGBA*>(static_cast<void*>(mLockPtr));
            *pCol++ = colour;
            // Update lock pointer
            mLockPtr = static_cast<float*>(static_cast<void*>(pCol));
            // Texture coords
            *mLockPtr++ = r.left;
            *mLockPtr++ = r.top;

            // Right-top
            // Positions
            *mLockPtr++ = offsets[1].x + p->mPosition.x;
            *mLockPtr++ = offsets[1].y + p->mPosition.y;
            *mLockPtr++ = offsets[1].z + p->mPosition.z;
            // Colour
            // Convert float* to RGBA*
            pCol = static_cast<RGBA*>(static_cast<void*>(mLockPtr));
            *pCol++ = colour;
            // Update lock pointer
            mLockPtr = static_cast<float*>(static_cast<void*>(pCol));
            // Texture coords
            *mLockPtr++ = r.right;
            *mLockPtr++ = r.top;

            // Left-bottom
            // Positions
            *mLockPtr++ = offsets[2].x + p->mPosition.x;
            *mLockPtr++ = offsets[2].y + p->mPosition.y;
            *mLockPtr++ = offsets[2].z + p->mPosition.z;
            // Colour
            // Convert float* to RGBA*
            pCol = static_cast<RGBA*>(static_cast<void*>(mLockPtr));
            *pCol++ = colour;
            // Update lock pointer
            mLockPtr = static_cast<float*>(static_cast<void*>(pCol));
            // Texture coords
            *mLockPtr++ = r.left;
            *mLockPtr++ = r.bottom;

            // Right-bottom
            // Positions
            *mLockPtr++ = offsets[3].x + p->mPosition.x;
            *mLockPtr++ = offsets[3].y + p->mPosition.y;
            *mLockPtr++ = offsets[3].z + p->mPosition.z;
            // Colour
            // Convert float* to RGBA*
            pCol = static_cast<RGBA*>(static_cast<void*>(mLockPtr));
            *pCol++ = colour;
            // Update lock pointer
            mLockPtr = static_cast<float*>(static_cast<void*>(pCol));
            // Texture coords
            *mLockPtr++ = r.right;
            *mLockPtr++ = r.bottom;
        }
        else if (mRotationType == BBR_VERTEX)
        {
            // TODO: Cache axis when billboard type is BBT_POINT or BBT_PERPENDICULAR_COMMON
            Vector3 axis = (offsets[3] - offsets[0]).crossProduct(offsets[2] - offsets[1]).normalisedCopy();

            Quaternion rotation(p->mRotation, axis);
            Vector3 pt;

            // Left-top
            // Positions
            pt = rotation * offsets[0];
            *mLockPtr++ = pt.x + p->mPosition.x;
            *mLockPtr++ = pt.y + p->mPosition.y;
            *mLockPtr++ = pt.z + p->mPosition.z;
            // Colour
            // Convert float* to RGBA*
            pCol = static_cast<RGBA*>(static_cast<void*>(mLockPtr));
            *pCol++ = colour;
            // Update lock pointer
            mLockPtr = static_cast<float*>(static_cast<void*>(pCol));
            // Texture coords
            *mLockPtr++ = r.left;
            *mLockPtr++ = r.top;

            // Right-top
            // Positions
            pt = rotation * offsets[1];
            *mLockPtr++ = pt.x + p->mPosition.x;
            *mLockPtr++ = pt.y + p->mPosition.y;
            *mLockPtr++ = pt.z + p->mPosition.z;
            // Colour
            // Convert float* to RGBA*
            pCol = static_cast<RGBA*>(static_cast<void*>(mLockPtr));
            *pCol++ = colour;
            // Update lock pointer
            mLockPtr = static_cast<float*>(static_cast<void*>(pCol));
            // Texture coords
            *mLockPtr++ = r.right;
            *mLockPtr++ = r.top;

            // Left-bottom
            // Positions
            pt = rotation * offsets[2];
            *mLockPtr++ = pt.x + p->mPosition.x;
            *mLockPtr++ = pt.y + p->mPosition.y;
            *mLockPtr++ = pt.z + p->mPosition.z;
            // Colour
            // Convert float* to RGBA*
            pCol = static_cast<RGBA*>(static_cast<void*>(mLockPtr));
            *pCol++ = colour;
            // Update lock pointer
            mLockPtr = static_cast<float*>(static_cast<void*>(pCol));
            // Texture coords
            *mLockPtr++ = r.left;
            *mLockPtr++ = r.bottom;

            // Right-bottom
            // Positions
            pt = rotation * offsets[3];
            *mLockPtr++ = pt.x + p->mPosition.x;
            *mLockPtr++ = pt.y + p->mPosition.y;
            *mLockPtr++ = pt.z + p->mPosition.z;
            // Colour
            // Convert float* to RGBA*
            pCol = static_cast<RGBA*>(static_cast<void*>(mLockPtr));
            *pCol++ = colour;
            // Update lock pointer
            mLockPtr = static_cast<float*>(static_cast<void*>(pCol));
            // Texture coords
            *mLockPtr++ = r.right;
            *mLockPtr++ = r.bottom;
        }
        else
        {
            const Real      cos_rot(Math::Cos(p->mRotation));
            const Real      sin_rot(Math::Sin(p->mRotation));

            float width = (r.right - r.left) / 2;
            float height = (r.bottom - r.top) / 2;
            float mid_u = r.left + width;
            float mid_v = r.top + height;

            float cos_rot_w = cos_rot * width;
            float cos_rot_h = cos_rot * height;
            float sin_rot_w = sin_rot * width;
            float sin_rot_h = sin_rot * height;

            // Left-top
            // Positions
            *mLockPtr++ = offsets[0].x + p->mPosition.x;
            *mLockPtr++ = offsets[0].y + p->mPosition.y;
            *mLockPtr++ = offsets[0].z + p->mPosition.z;
            // Colour
            // Convert float* to RGBA*
            pCol = static_cast<RGBA*>(static_cast<void*>(mLockPtr));
            *pCol++ = colour;
            // Update lock pointer
            mLockPtr = static_cast<float*>(static_cast<void*>(pCol));
            // Texture coords
            *mLockPtr++ = mid_u - cos_rot_w + sin_rot_h;
            *mLockPtr++ = mid_v - sin_rot_w - cos_rot_h;

            // Right-top
            // Positions
            *mLockPtr++ = offsets[1].x + p->mPosition.x;
            *mLockPtr++ = offsets[1].y + p->mPosition.y;
            *mLockPtr++ = offsets[1].z + p->mPosition.z;
            // Colour
            // Convert float* to RGBA*
            pCol = static_cast<RGBA*>(static_cast<void*>(mLockPtr));
            *pCol++ = colour;
            // Update lock pointer
            mLockPtr = static_cast<float*>(static_cast<void*>(pCol));
            // Texture coords
            *mLockPtr++ = mid_u + cos_rot_w + sin_rot_h;
            *mLockPtr++ = mid_v + sin_rot_w - cos_rot_h;

            // Left-bottom
            // Positions
            *mLockPtr++ = offsets[2].x + p->mPosition.x;
            *mLockPtr++ = offsets[2].y + p->mPosition.y;
            *mLockPtr++ = offsets[2].z + p->mPosition.z;
            // Colour
            // Convert float* to RGBA*
            pCol = static_cast<RGBA*>(static_cast<void*>(mLockPtr));
            *pCol++ = colour;
            // Update lock pointer
            mLockPtr = static_cast<float*>(static_cast<void*>(pCol));
            // Texture coords
            *mLockPtr++ = mid_u - cos_rot_w - sin_rot_h;
            *mLockPtr++ = mid_v - sin_rot_w + cos_rot_h;

            // Right-bottom
            // Positions
            *mLockPtr++ = offsets[3].x + p->mPosition.x;
            *mLockPtr++ = offsets[3].y + p->mPosition.y;
            *mLockPtr++ = offsets[3].z + p->mPosition.z;
            // Colour
            // Convert float* to RGBA*
            pCol = static_cast<RGBA*>(static_cast<void*>(mLockPtr));
            *pCol++ = colour;
            // Update lock pointer
            mLockPtr = static_cast<float*>(static_cast<void*>(pCol));
            // Texture coords
            *mLockPtr++ = mid_u + cos_rot_w - sin_rot_h;
            *mLockPtr++ = mid_v + sin_rot_w + cos_rot_h;
        }
    }

    //-----------------------------------------------------------------------
    const String& BillboardSet::getMovableType(void) const
    {
        return BillboardSetFactory::FACTORY_TYPE_NAME;
    }
    //-----------------------------------------------------------------------
    Real BillboardSet::getSquaredViewDepth(const Camera* const cam) const
    {
        assert(mParent);
        return mParent->getSquaredViewDepth(cam);
    }
   


    void BillboardSet::setTextureCoords(const std::vector<FloatRect>& coords)
    {
        if (coords.empty()) {
            setTextureStacksAndSlices(1, 1);
            return;
        }

        mTextureCoords = coords;
    }

    void BillboardSet::setTextureStacksAndSlices(uchar stacks, uchar slices)
    {
        if (stacks == 0) stacks = 1;
        if (slices == 0) slices = 1;
        //  clear out any previous allocation (as vectors may not shrink)
        TextureCoordSets().swap(mTextureCoords);
        //  make room
        mTextureCoords.resize((size_t)stacks * slices);
        unsigned int coordIndex = 0;
        //  spread the U and V coordinates across the rects
        for (uint32 v = 0; v < stacks; ++v) {
            //  (float)X / X is guaranteed to be == 1.0f for X up to 8 million, so
            //  our range of 1..256 is quite enough to guarantee perfect coverage.
            float top = (float)v / (float)stacks;
            float bottom = ((float)v + 1) / (float)stacks;
            for (uint32 u = 0; u < slices; ++u) {
                Ogre::FloatRect& r = mTextureCoords[coordIndex];
                r.left = (float)u / (float)slices;
                r.bottom = bottom;
                r.right = ((float)u + 1) / (float)slices;
                r.top = top;
                ++coordIndex;
            }
        }
        assert(coordIndex == (size_t)stacks * slices);
    }
    
    //-----------------------------------------------------------------------
    void BillboardSet::setPointRenderingEnabled(bool enabled)
    {
      
         enabled = false;
        

        if (enabled != mPointRendering)
        {
            mPointRendering = enabled;
            // Different buffer structure (1 or 4 verts per billboard)
            _destroyBuffers();
        }
    }

    //-----------------------------------------------------------------------
    void BillboardSet::setAutoUpdate(bool autoUpdate)
    {
        // Case auto update buffers changed we have to destroy the current buffers
        // since their usage will be different.
        if (autoUpdate != mAutoUpdate)
        {
            mAutoUpdate = autoUpdate;
            _destroyBuffers();
        }
    }

    //-----------------------------------------------------------------------
    //-----------------------------------------------------------------------
    String BillboardSetFactory::FACTORY_TYPE_NAME = "BillboardSet";
    //-----------------------------------------------------------------------
    const String& BillboardSetFactory::getType(void) const
    {
        return FACTORY_TYPE_NAME;
    }
    //-----------------------------------------------------------------------
    MoveObject* BillboardSetFactory::createInstanceImpl(const String& name,
        const NameValuePairList* params)
    {
        // may have parameters
        bool externalData = false;
        unsigned int poolSize = 0;

        if (params != 0)
        {
            NameValuePairList::const_iterator ni = params->find("poolSize");
            if (ni != params->end())
            {
                poolSize = StringConverter::parseUnsignedInt(ni->second);
            }
            ni = params->find("externalData");
            if (ni != params->end())
            {
                externalData = StringConverter::parseBool(ni->second);
            }

        }

        if (poolSize > 0)
        {
            return OGRE_NEW BillboardSet(name, poolSize, externalData);
        }
        else
        {
            return OGRE_NEW BillboardSet(name);
        }

    }
}
