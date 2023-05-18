#include "OgreHeader.h"
#include "OGUtils.h"
#include "OGFlags.h"

#include <OgreMaterialManager.h>
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreCamera.h>
#include <OgreEntity.h>
#include <platform_log.h>
#include "OgreRenderable.h"
#include "OgreEntity.h"
#include "OGProjector.h"
#include "terrain.h"
#include "terrain_info.h"
#include "vertex_data.h"
#include "vertex_declaration.h"

namespace Orphigine {

    class ProjectorRenderable : public Ogre::Renderable
    {
    protected:
        Projector* mParent;

    public:
        VertexData* mVertexData = nullptr;
        Ogre::Matrix4 mProjectorMatrix;
    public:

        ProjectorRenderable(Projector* parent)
            : Renderable()
            , mParent(parent)
        {
            mVertexData = new VertexData;
            mVertexData->vertexCount = 6;
            auto decl = mVertexData->vertexDeclaration;
            decl->addElement(0, 0, 0, VET_FLOAT3, VES_POSITION);
            decl->addElement(0, 0, 3 * sizeof(Real), VET_COLOUR, VES_DIFFUSE);
            mVertexData->vertexSlotInfo.emplace_back();

            auto& back = mVertexData->vertexSlotInfo.back();
            back.createBuffer(16, mVertexData->vertexCount);
            
        }

        virtual VertexData* getVertexData()
        {
            return mVertexData;
        }

        virtual IndexData* getIndexData()
        {
            return nullptr;
        }

        virtual IndexDataView* getIndexView()
        {
            return nullptr;
        }

        void setVertexData(
            const std::vector<Ogre::Vector3> mTempPositions,
            size_t vertexStart, size_t vertexCount, unsigned int mColour)
        {
            auto& back = mVertexData->vertexSlotInfo.back();
            
            uint32_t numVerts = back.hardwareVertexBuffer->getNumVerts();

            if (numVerts < mTempPositions.size())
            {
                back.createBuffer(back.mVertexSize, mTempPositions.size());
            }
            mVertexData->vertexStart = vertexStart;
            mVertexData->vertexCount = vertexCount;

            float* pFloat = static_cast<float*>(back.hardwareVertexBuffer->lock());
            for (uint32_t i = 0; i < mTempPositions.size(); i++)
            {
                *pFloat++ = mTempPositions[i].x;
                *pFloat++ = mTempPositions[i].y;
                *pFloat++ = mTempPositions[i].z;
                unsigned int* pColour = (unsigned int*)pFloat;
                *pColour = mColour;
                pFloat++;
            }
            back.hardwareVertexBuffer->unlock();
        }
        virtual const std::shared_ptr<Material>& getMaterial() override
        {
            return mParent->_getPatchMaterial();
        }
    
        virtual const Ogre::Matrix4& getProjectorMatrix() override
        {
            float width = mParent->getOrthoWindowWidth();
            float height = mParent->getOrthoWindowHeight();
            const Ogre::Matrix4& view = mParent->getViewMatrix();
            const Ogre::Matrix4& proj = mParent->getProjectionMatrix();

            Real left = -width / 2.0f;
            Real right = width / 2.0f;
            Real top = height / 2.0f;
            Real bottom = -height / 2.0f;
            float zNear = mParent->getNearClipDistance();
            float zFar = mParent->getFarClipDistance();
            Ogre::Matrix4 aa =
                Ogre::Math::makeOrthoRH(left, right, bottom, top, zNear, zFar);
            Ogre::Vector3 eyePos(0, 200.0f, 0.0f);
            Ogre::Vector3 targetPos(0, 0, 0);
            Ogre::Vector3 up(1.0, 0.0, 0.0);
            Ogre::Matrix4 bb = Ogre::Math::makeLookAtRH(eyePos, targetPos, up);
        
            mProjectorMatrix = bb * aa;
            return mProjectorMatrix;
        }

        void getWorldTransforms(Ogre::Matrix4* xform) const
        {
            *xform = Ogre::Matrix4::IDENTITY;
        }
        //-----------------------------------------------------------------------
        /** Overridden - see Renderable. */
        const Ogre::Quaternion& getWorldOrientation(void) const
        {
            return Ogre::Quaternion::IDENTITY;
        }
        //-----------------------------------------------------------------------
        /** Overridden - see Renderable. */
        const Ogre::Vector3& getWorldPosition(void) const
        {
            return Ogre::Vector3::ZERO;
        }
        //-----------------------------------------------------------------------
        /** Overridden - see Renderable. */
        Ogre::Real getSquaredViewDepth(const Ogre::Camera* camera) const
        {
            Ogre::Node* n = mParent->getParentSceneNode();
            assert(n);
            return n->getSquaredViewDepth(camera);
        }

        //-----------------------------------------------------------------------
        /** Overridden - see Renderable. */
        const Ogre::PlaneList& getClipPlanes(void) const
        {
              return mParent->mClipPlanes;
        }
    };


	class RenderSysListener
	{
	public:
		RenderSysListener()
			: mProjector(0)
		{
		}

		void setProjector(Projector *proj)
		{
			mProjector = proj;
		}

		virtual void eventOccurred(const String& eventName, const NameValuePairList* parameters)
		{
			if (eventName == "DeviceRestored") {
				mProjector->setDirty(true);
			}
		}
	protected:
		Projector * mProjector;
	};
	//end
    //////////////////////////////////////////////////////////////////////////

    //-----------------------------------------------------------------------
    Projector::Projector(const String& name)
        : Ogre::Frustum()
        , mTerrain()
        , mTerrainGridLimit(256) 		
        , mQueryMask(~0)
        , mQueryTypeMask(~0)
        , mVertexLimit(4096)
        , mVertexBuffer()
        , mPatchMaterial()
        , mPatchMaterialName()
        , mPatchMaterialDirty()
        , mShowFrustum()
        , mEnableClipPlanes()
		, mColour(0xFFFFFFFF)
		, mForceUpdate(true)
		, mDirty(false)

		, m_bUsingProjScene(false)
    {
        // MovableObject name
        mName = name;

		// default type mask to everything except lights & fx (previous behaviour)
        mQueryTypeMask = ~(Ogre::SceneManager::FX_TYPE_MASK  | Ogre::SceneManager::LIGHT_TYPE_MASK);

        // default query mask set to decal target only
        mQueryMask = OQF_DECAL_TARGET;

		mSphereRadius = 100.0f;


    }
    //-----------------------------------------------------------------------
	Projector::~Projector()
	{
		
    }
    //-----------------------------------------------------------------------
    void Projector::_clearRenderables(void)
    {
      
    }
    //-----------------------------------------------------------------------
    void Projector::_freeRenderables(void)
    {
    }
    //-----------------------------------------------------------------------
    ProjectorRenderable* Projector::_allocRenderable(Ogre::Entity* entity)
    {
        if (mRenderables.empty())
        {
            mRenderables.push_back(new ProjectorRenderable(this));
        }

        return (ProjectorRenderable*)mRenderables.front();
    }
    //-----------------------------------------------------------------------
    void Projector::_addRenderable(Ogre::Entity* entity, size_t vertexStart, size_t vertexCount)
    {
        if (vertexCount > 0 && !m_bUsingProjScene)  // 如果不用ProjScene，那么才可以自己独立渲染，否则自己不独立渲染，而是交给ProjScene渲染
        {
            ProjectorRenderable* result = _allocRenderable(entity);
            result->setVertexData(mTempPositions, vertexStart, vertexCount, mColour);
        }
    }
    //-----------------------------------------------------------------------
    void Projector::setShowFrustum(bool showFrustum)
    {
        mShowFrustum = showFrustum;
    }
    //-----------------------------------------------------------------------
    bool Projector::getShowFrustum(void) const
    {
        return mShowFrustum;
    }
    //-----------------------------------------------------------------------
    void Projector::setEnableClipPlanes(bool enableClipPlanes)
    {
        mEnableClipPlanes = enableClipPlanes;
    }
    //-----------------------------------------------------------------------
    bool Projector::getEnableClipPlanes(void) const
    {
        return mEnableClipPlanes;
    }
    //-----------------------------------------------------------------------
    void Projector::setPatchMaterial(const String& materialName)
    {
        mPatchMaterialName = materialName;
        mPatchMaterialDirty = true;
    }
    //-----------------------------------------------------------------------
    const String& Projector::getPatchMaterialName(void) const
    {
        return mPatchMaterialName;
    }
    //-----------------------------------------------------------------------
    const Ogre::MaterialPtr& Projector::_getPatchMaterial(void)
    {
        _updateMaterial();
        return mPatchMaterial;
    }
    //-----------------------------------------------------------------------
    void Projector::setTerrain(Terrain* terrain)
    {
        mTerrain = terrain;
    }
    //-----------------------------------------------------------------------
    Terrain* Projector::getTerrain(void) const
    {
        return mTerrain;
    }
    //-----------------------------------------------------------------------
    void Projector::setTerrainGridLimit(int limit)
    {
        assert(limit > 0);
        mTerrainGridLimit = limit;
    }
    //-----------------------------------------------------------------------
    int Projector::getTerrainGridLimit(void) const
    {
        return mTerrainGridLimit;
    }
    //-----------------------------------------------------------------------
    void Projector::setVertexLimit(size_t limit)
    {
        mVertexLimit = limit;
    }
    //-----------------------------------------------------------------------
    size_t Projector::getVertexLimit(void) const
    {
        return mVertexLimit;
    }
    //-----------------------------------------------------------------------
    void Projector::setQueryMask(uint32 mask)
    {
        mQueryMask = mask;
    }
    //-----------------------------------------------------------------------
    uint32 Projector::getQueryMask(void) const
    {
        return mQueryMask;
    }
	//-----------------------------------------------------------------------
	void Projector::setQueryTypeMask(uint32 mask)
	{
		mQueryTypeMask = mask;
	}
	//-----------------------------------------------------------------------
	uint32 Projector::getQueryTypeMask(void) const
	{
		return mQueryTypeMask;
	}
    //-----------------------------------------------------------------------
    const String& Projector::getMovableType(void) const
    {
        return ProjectorFactory::FACTORY_TYPE_NAME;
    }
    //-----------------------------------------------------------------------
    bool Projector::_updateMaterial(void)
    {
        if (!mPatchMaterial)
        {
            if (!mPatchMaterialName.empty())
            {
                mPatchMaterial = createProjectiveMaterial(mPatchMaterialName, this);
            }
        }
        return true;
    }
    //-----------------------------------------------------------------------
    void Projector::_notifyCurrentCamera(Ogre::Camera* camera)
    {
        mCurrentCamera = camera;

		
		
    }

	void Projector::setVisible(bool visible)
    {
        mVisible = visible;
	}

	//-----------------------------------------------------------------------
	void Projector::setForceUpdate(bool forceUpdate)
	{
		mForceUpdate = forceUpdate;
	}	
    //-----------------------------------------------------------------------
	void Projector::_updateRenderQueue(Ogre::RenderQueue* queue)
	{
		

	}
	//-----------------------------------------------------------------------
    void Projector::_buildVertexBuffer(void)
    {
		
    }

    void Projector::update(float delta)
    {
        _updateVertexBuffer(false);
    }
	//-----------------------------------------------------------------------
    void Projector::_populateForTerrain(void)
    {
        if (!mTerrain)
        {
            mTempPositions.clear();
            float a = 100.0f;
            mTempPositions.push_back(Ogre::Vector3(-a, 0, -a));
            mTempPositions.push_back(Ogre::Vector3(a, 0, -a));
            mTempPositions.push_back(Ogre::Vector3(-a, 0, a));

            mTempPositions.push_back(Ogre::Vector3(-a, 0, a));
            mTempPositions.push_back(Ogre::Vector3(a, 0, -a));
            mTempPositions.push_back(Ogre::Vector3(a, 0, a));
            _addRenderable(NULL, 0, 6);
            return;
        }
            

        // Check vertex limit
        if (mTempPositions.size() >= mVertexLimit)
            return;

        auto data = mTerrain->getTerrainInfo();
        assert(data);

        Real fOldFar = getFarClipDistance();

        size_t vertexStart = mTempPositions.size();
        size_t vertexCount = data->isFrustumIntersectGround(
            this, mTerrainGridLimit, true, mTempPositions, nullptr);
        _addRenderable(NULL, vertexStart, vertexCount);
    }

	void Projector::calcAABB()
	{
		mAABB.setNull();
		const Ogre::Vector3* corners = getWorldSpaceCorners();
		for ( int i = 0; i < 8; i++ )
		{
			mAABB.merge(corners[i]);
		}
	}

	void Projector::_updateVertexBuffer(bool bUpdateAnyway)
	{
		const Ogre::Vector3& curPos = getParentSceneNode()->_getDerivedPosition();
		const Ogre::Quaternion& curOrient = getParentSceneNode()->_getDerivedOrientation();
		Real squaredLen = (mLastUpdatePos - curPos).squaredLength();
		const Real slRef = 50;  // 位置改变量超过这个阈值才发生更新。此阈值原先是0.5，未免太小了吧
		//只有水平方向的位置或者角度发生变化才需要重新构建vertexbuffer
		//设备重置……非特效光圈……位置改变……方向改变
		if (bUpdateAnyway || mDirty || mForceUpdate || (squaredLen > slRef) || 
            !curOrient.equals(mLastOrient, Ogre::Radian(0.02f)))
		{
			mLastUpdatePos = curPos;
			mLastOrient = curOrient;

			_freeRenderables();
			mTempPositions.clear();
			calcAABB();
			Real fHitY = 0.0f;
			bool bTerrainNeedProject = _populateForMovables(fHitY);
			static Real fOffset = 30.0f;
			//如果没有与行走面相交，仅仅投影到地形上
			if (fHitY == 0.0f)
			{
				fOffset = 300.0f;
			}
			else
			{
				//如果projector是阴影光圈或者选中光圈，需要把offset设的小一点
				if (mSphereRadius == 100.0f)
				{
					fOffset = 60.0f;
				}
				//如果projector是粒子系统投影到地面上
				else
				{
					fOffset = 300.0f;
				}
			}
			if (bTerrainNeedProject)
			{
				Real fOldFar = getFarClipDistance();
				Ogre::Vector3 frustumPos;
				frustumPos = getParentSceneNode()->_getDerivedPosition();
				Real fTerrainHeight = 0;
				if (mTerrain)
				{
					fTerrainHeight = mTerrain->getTerrainInfo()->getWorldIndexWorldHeight(frustumPos.x, frustumPos.z);
				}
				
				if (fHitY == 0.0f)
					setFarClipDistance(frustumPos.y - fTerrainHeight + fOffset);
				else
					setFarClipDistance(frustumPos.y - fHitY + fOffset);
				_populateForTerrain();
				setFarClipDistance(fOldFar);
			}
			if (mTempPositions.empty() || (mRenderables.empty() && !m_bUsingProjScene))
			{
				return;
			}

			_buildVertexBuffer();

			mDirty = false;
		}
	}

	void Projector::enableUsingProjScene(bool bEnable)
	{
		m_bUsingProjScene = bEnable;
	}

	bool Projector::uploadToProjScene()
	{
		
		
		return false;
	}
	
	void Projector::erasureFromProjScene()
	{
		
	}

    //-----------------------------------------------------------------------
    bool Projector::_populateForMovables(Real & fHitY)
	{
        return true;
	}
	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
	const String ProjectorFactory::FACTORY_TYPE_NAME = "Projector";
	//-----------------------------------------------------------------------
	const String& ProjectorFactory::getType(void) const
	{
		return FACTORY_TYPE_NAME;
	}
	//-----------------------------------------------------------------------
	Ogre::MoveObject* ProjectorFactory::createInstanceImpl(const String& name,
		const Ogre::NameValuePairList* params)
	{
		return new Projector(name);
	}
	//-----------------------------------------------------------------------
    void ProjectorFactory::destroyInstance(Ogre::MoveObject* obj)
	{
		delete obj;
	}
}
