#ifndef __OGCollisionModel_H__
#define __OGCollisionModel_H__


#include "OGOpcode.h"

#include <OgreVector3.h>
#include <OgreVector4.h>
#include "OgreResource.h"

// Forward declaration for Opcode to avoid header file dependency.
namespace Opcode
{
    class ModelComponent;
}

namespace Orphigine
{
    class CollisionModel;
    typedef std::shared_ptr<CollisionModel> CollisionModelPtr;

	class CollisionModel
    {
    protected:
        class Imp;
        Imp* mImp;

        std::vector<Ogre::Vector3> mVertices;
        std::vector<Ogre::Vector4> mFaceNormals;
        std::vector<size_t> mIndices;
        std::vector<size_t> mIndexOffsets;

        size_t mMemoryUsage;

    public:
        CollisionModel(void);
        ~CollisionModel();

        void addMesh(const Ogre::MeshPtr& mesh);
        void addEntity(const Ogre::Entity* entity);
        void reset(void);

        void build(bool dynamic);
        void destroy(void);

        const Opcode::Model& getOpcodeModel(void) const;

        const std::vector<Ogre::Vector3>& getVertices(void) const
        {
            return mVertices;
        }

        const std::vector<Ogre::Vector4>& getFaceNormals(void) const
        {
            return mFaceNormals;
        }

        const std::vector<size_t>& getIndices(void) const
        {
            return mIndices;
        }

        const std::vector<size_t>& getIndexOffsets(void) const
        {
            return mIndexOffsets;
        }

        size_t getMemoryUsage(void) const
        {
            return mMemoryUsage;
        }
    };
}

#endif __OGCollisionModel_H__
