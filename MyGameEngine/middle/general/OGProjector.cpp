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

namespace Orphigine {

    class ProjectorRenderable : public Ogre::Renderable
    {
    protected:
        Projector* mParent;

    public:
        Ogre::Entity* mEntity;
       // Ogre::RenderOperation mRenderOp;

    public:
        
        //-----------------------------------------------------------------------
        /** Overridden - see Renderable. */
        const Ogre::MaterialPtr& getMaterial(void) const
        {
            return mParent->mPatchMaterial;
        }
       
        //-----------------------------------------------------------------------
        /** Overridden - see Renderable. */
        void getWorldTransforms(Ogre::Matrix4* xform) const
        {
            if (mEntity)
            {
                *xform = mEntity->_getParentNodeFullTransform();
            }
            else
            {
                *xform = Ogre::Matrix4::IDENTITY;
            }
        }
        //-----------------------------------------------------------------------
        /** Overridden - see Renderable. */
        const Ogre::Quaternion& getWorldOrientation(void) const
        {
            if (mEntity)
            {
                return mEntity->getParentSceneNode()->_getDerivedOrientation();
            }
            else
            {
                return Ogre::Quaternion::IDENTITY;
            }
        }
        //-----------------------------------------------------------------------
        /** Overridden - see Renderable. */
        const Ogre::Vector3& getWorldPosition(void) const
        {
            if (mEntity)
            {
                return mEntity->getParentSceneNode()->_getDerivedPosition();
            }
            else
            {
                return Ogre::Vector3::ZERO;
            }
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
        , mRenderables()
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
        _freeRenderables();

        for (ProjectorRenderableList::const_iterator it = mFreeRenderables.begin(); it != mFreeRenderables.end(); ++it)
        {
            delete *it;
        }
        mFreeRenderables.clear();
    }
    //-----------------------------------------------------------------------
    void Projector::_freeRenderables(void)
    {
        
    }
    //-----------------------------------------------------------------------
    ProjectorRenderable* Projector::_allocRenderable(Ogre::Entity* entity)
    {
        return nullptr;
    }
    //-----------------------------------------------------------------------
    void Projector::_addRenderable(Ogre::Entity* entity, size_t vertexStart, size_t vertexCount)
    {
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
        return false;
    }
    //-----------------------------------------------------------------------
    void Projector::_notifyCurrentCamera(Ogre::Camera* camera)
    {
        mCurrentCamera = camera;

		
		
    }

	void Projector::setVisible(bool visible)
	{
	

		
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
	//-----------------------------------------------------------------------
    void Projector::_populateForTerrain(void)
    {
        if (!mTerrain)
            return;

        
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


	bool Projector::_populateForMovables(Real & fHitY)
	{
        return true;
	}

	void Projector::_updateVertexBuffer(bool bUpdateAnyway)
	{
		
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
    /*void Projector::_populateForMovables(void)
    {
        // Shortcut to ignore all movables
        if (!mQueryMask || !mQueryTypeMask)
            return;

        // Check vertex limit
        if (mTempPositions.size() >= mVertexLimit)
            return;

        Ogre::SceneNode* sn = this->getParentSceneNode(); assert(sn);
        Ogre::SceneManager* sm = sn->getCreator(); assert(sm);

        Ogre::PlaneBoundedVolumeListSceneQuery* query = sm->createPlaneBoundedVolumeQuery(Ogre::PlaneBoundedVolumeList());

        {
            Ogre::PlaneBoundedVolumeList volumes;
            Ogre::PlaneBoundedVolume volume;
            const Ogre::Plane* frustumPlanes;

            // Pre-allocate spaces
            volume.planes.reserve(6 * 2);

            // Inject our clip planes
            frustumPlanes = this->getFrustumPlanes();
            volume.planes.insert(volume.planes.end(), frustumPlanes, frustumPlanes + 6);

            // Setup renderable clip planes if need
            if (mEnableClipPlanes)
            {
                mClipPlanes = volume.planes;
            }

            // Inject camera's clip planes
            frustumPlanes = mCurrentCamera->getFrustumPlanes();
            volume.planes.insert(volume.planes.end(), frustumPlanes, frustumPlanes + 6);

            // Construct volumes and query
            volumes.push_back(volume);
            query->setVolumes(volumes);
        }

        // Cache the view-projection matrix
        Ogre::Matrix4 viewProjMatrix = this->getProjectionMatrix() * this->getViewMatrix();
        CollisionModelManager& cmm = CollisionModelManager::getSingleton();

        // TODO: Optimize usage of the following variables
        Opcode::PlanesCollider planesCollider;
        Opcode::PlanesCache planesCache;
        IceMaths::Plane clipPlanes[6];

		query->setQueryMask(mQueryMask);
        query->setQueryTypeMask(mQueryTypeMask);
        Ogre::SceneQueryResult& result = query->execute();
        for (Ogre::SceneQueryResultMovableList::const_iterator it = result.movables.begin(); it != result.movables.end(); ++it)
        {
            Ogre::MovableObject* movable = *it;
            if (!(movable->_notifyCurrentCamera(mCurrentCamera), movable->isVisible()))
                continue;

            if (movable->getMovableType() == Ogre::EntityFactory::FACTORY_TYPE_NAME)
            {
                Ogre::Entity* entity = static_cast<Ogre::Entity*>(movable);
                if (!entity->hasSkeleton() && !entity->hasVertexAnimation())
                {
                    // Static entity

                    const Ogre::MeshPtr& mesh = entity->getMesh();
                    // Get world matrix
                    Ogre::Matrix4 worldMatrix = entity->_getParentNodeFullTransform();
                    // Compute world-view-projection matrix
                    Ogre::Matrix4 worldViewProjMatrix = viewProjMatrix * worldMatrix;
                    // Get the collision mode
                    CollisionModelPtr collisionModel = cmm.getCollisionModel(mesh);

                    // Setup clip planes in model space, NB: Opcode use negative side as inside
                    clipPlanes[Ogre::FRUSTUM_PLANE_LEFT].Set(
                        - worldViewProjMatrix[0][0] - worldViewProjMatrix[3][0],
                        - worldViewProjMatrix[0][1] - worldViewProjMatrix[3][1],
                        - worldViewProjMatrix[0][2] - worldViewProjMatrix[3][2],
                        - worldViewProjMatrix[0][3] - worldViewProjMatrix[3][3]);
                    clipPlanes[Ogre::FRUSTUM_PLANE_RIGHT].Set(
                        + worldViewProjMatrix[0][0] - worldViewProjMatrix[3][0],
                        + worldViewProjMatrix[0][1] - worldViewProjMatrix[3][1],
                        + worldViewProjMatrix[0][2] - worldViewProjMatrix[3][2],
                        + worldViewProjMatrix[0][3] - worldViewProjMatrix[3][3]);
                    clipPlanes[Ogre::FRUSTUM_PLANE_BOTTOM].Set(
                        - worldViewProjMatrix[1][0] - worldViewProjMatrix[3][0],
                        - worldViewProjMatrix[1][1] - worldViewProjMatrix[3][1],
                        - worldViewProjMatrix[1][2] - worldViewProjMatrix[3][2],
                        - worldViewProjMatrix[1][3] - worldViewProjMatrix[3][3]);
                    clipPlanes[Ogre::FRUSTUM_PLANE_TOP].Set(
                        + worldViewProjMatrix[1][0] - worldViewProjMatrix[3][0],
                        + worldViewProjMatrix[1][1] - worldViewProjMatrix[3][1],
                        + worldViewProjMatrix[1][2] - worldViewProjMatrix[3][2],
                        + worldViewProjMatrix[1][3] - worldViewProjMatrix[3][3]);
                    clipPlanes[Ogre::FRUSTUM_PLANE_NEAR].Set(
                        - worldViewProjMatrix[2][0] - worldViewProjMatrix[3][0],
                        - worldViewProjMatrix[2][1] - worldViewProjMatrix[3][1],
                        - worldViewProjMatrix[2][2] - worldViewProjMatrix[3][2],
                        - worldViewProjMatrix[2][3] - worldViewProjMatrix[3][3]);
                    clipPlanes[Ogre::FRUSTUM_PLANE_FAR].Set(
                        + worldViewProjMatrix[2][0] - worldViewProjMatrix[3][0],
                        + worldViewProjMatrix[2][1] - worldViewProjMatrix[3][1],
                        + worldViewProjMatrix[2][2] - worldViewProjMatrix[3][2],
                        + worldViewProjMatrix[2][3] - worldViewProjMatrix[3][3]);

                    // collide check
                    if (!planesCollider.Collide(planesCache, clipPlanes, 6, collisionModel->getOpcodeModel(), NULL))
                        continue;

                    const udword* triangles = planesCollider.GetTouchedPrimitives();
                    udword numTriangles = planesCollider.GetNbTouchedPrimitives();
                    if (!triangles || !numTriangles)
                        continue;

                    // Get the view vector base on projection type
                    Ogre::Vector4 vv;
                    Ogre::Matrix4 eyeToModel = (this->getViewMatrix() * worldMatrix).inverse();
                    if (this->getProjectionType() == Ogre::PT_PERSPECTIVE)
                    {
                        // Use view position as view vector
                        vv[0] = eyeToModel[0][3];
                        vv[1] = eyeToModel[1][3];
                        vv[2] = eyeToModel[2][3];
                        vv[3] = eyeToModel[3][3];
                    }
                    else
                    {
                        // Use view direction as view vector
                        vv[0] = eyeToModel[0][2];
                        vv[1] = eyeToModel[1][2];
                        vv[2] = eyeToModel[2][2];
                        vv[3] = eyeToModel[3][2];
                    }

                    const std::vector<Ogre::Vector4>& faceNormals = collisionModel->getFaceNormals();
                    const std::vector<Ogre::Vector3>& vertices = collisionModel->getVertices();
                    const std::vector<size_t>& indices = collisionModel->getIndices();
                    size_t vertexStart = mTempPositions.size();
                    size_t vertexCount = 0;

                    // Reserve memory avoid allocate overhead
                    mTempPositions.reserve(vertexStart + numTriangles * 3);

                    for (udword i = 0; i < numTriangles; ++i)
                    {
                        udword triangleIndex = triangles[i];
                        const Ogre::Vector4& faceNormal = faceNormals[triangleIndex];

                        // Check the triangle is projector facing
                        if (faceNormal.dotProduct(vv) > 0)
                        {
                            mTempPositions.push_back(vertices[indices[triangleIndex*3 + 0]]);
                            mTempPositions.push_back(vertices[indices[triangleIndex*3 + 1]]);
                            mTempPositions.push_back(vertices[indices[triangleIndex*3 + 2]]);
                            vertexCount += 3;
                        }
                    }

                    // Check vertex limit
                    assert(vertexStart <= mVertexLimit);
                    if (mVertexLimit <= vertexStart)
                        break;  // Just for safely

                    // Check overrun
                    bool overrun = vertexStart + vertexCount > mVertexLimit;
                    if (overrun)
                    {
                        // discard overrun vertices
                        vertexCount = (mVertexLimit - vertexStart) / 3 * 3;
                        mTempPositions.resize(vertexStart + vertexCount);
                    }

                    _addRenderable(entity, vertexStart, vertexCount);

                    // No more process because vertices overrun
                    if (overrun)
                        break;
                }
                else
                {
                    // Animation entity
                    // TODO:
                }
            }
        }

        sm->destroyQuery(query);
    }*/
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
