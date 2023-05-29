#ifndef __OGUtils_H__
#define __OGUtils_H__
#include "OgreColourValue.h"

namespace Orphigine {
Ogre::MeshPtr
createSphere(const String& name,
             const Real radius = 1, const int rings = 16, const int segments = 16,
             const bool normals = true,
             const int numTexCoordSets = 1,
             const bool inwards = false);

Ogre::MeshPtr
_OrphigineExport createCommonSphere(const String& namePrefix,
                   const Real radius = 1, const int rings = 16, const int segments = 16,
                   const bool normals = true,
                   const int numTexCoordSets = 1,
                   const bool inwards = false);

Ogre::MeshPtr
_OrphigineExport createCommonSphere(const Real radius = 1, const int rings = 16, const int segments = 16,
                   const bool normals = true,
                   const int numTexCoordSets = 1,
                   const bool inwards = false);

Ogre::MaterialPtr
_OrphigineExport createPureColourMaterial(const Ogre::ColourValue& colour);

Ogre::MaterialPtr
_OrphigineExport createColourMaterial(const Ogre::ColourValue& colour);

Ogre::MaterialPtr
_OrphigineExport createColourMaterial(const Ogre::ColourValue& colour, const Ogre::ColourValue& specular, Real shininess);

//////////////////////////////////////////////////////////////////////////

Ogre::MaterialPtr
createProjectiveMaterial(const String& materialTemplateName, const Ogre::Frustum* frustum);

void
fixupProjectiveMaterial(const Ogre::MaterialPtr& material, const Ogre::Frustum* frustum);

//////////////////////////////////////////////////////////////////////////

typedef std::list<Ogre::MoveObject*> ObjectList;

extern void
findAllAttachedObjects(Ogre::SceneNode* sn, ObjectList& objects);

extern void
destroyObject(Ogre::SceneManager* creator, Ogre::MoveObject* object);

extern void
destroyObjects(Ogre::SceneManager* creator, const ObjectList& objects);

extern void
cleanupSceneNode(Ogre::SceneNode* sn);

extern void
_OrphigineExport cleanupAndDestroySceneNode(Ogre::SceneNode* sn);

//////////////////////////////////////////////////////////////////////////

extern Ogre::AnimationState*
getAnimationStateSafely(Ogre::AnimationStateSet* animationStateSet, const String& name);

extern Ogre::AnimationState*
getAnimationStateSafely(Ogre::Entity* entity, const String& name);

extern Ogre::Animation*
getAnimationSafely(const Ogre::Skeleton* skeleton, const String& name);

extern Ogre::Animation*
getAnimationSafely(const Ogre::SkeletonPtr& skeleton, const String& name);

extern Ogre::Animation*
getAnimationSafely(const Ogre::Mesh* mesh, const String& name);

extern Ogre::Animation*
getAnimationSafely(const Ogre::MeshPtr& mesh, const String& name);

//////////////////////////////////////////////////////////////////////////

// Returns transformed bounding box which will skinning by the given skeleton.
extern Ogre::AxisAlignedBox
skinningTransformBoundingBox(const Ogre::AxisAlignedBox& boundingBox, const Ogre::Skeleton* skeleton);

// Returns transformed bounding box which will skinning by the given skeleton.
extern Ogre::AxisAlignedBox
skinningTransformBoundingBox(const Ogre::AxisAlignedBox& boundingBox, const Ogre::SkeletonPtr& skeleton);

// Returns a bounding box that includes all possible positions of bones in the given skeleton.
extern Ogre::AxisAlignedBox
getSkeletonBoundingBox(const Ogre::Skeleton* skeleton);

// Returns a bounding box that includes all possible positions of bones in the given skeleton.
extern Ogre::AxisAlignedBox
getSkeletonBoundingBox(const Ogre::SkeletonPtr& skeleton);

//////////////////////////////////////////////////////////////////////////

extern Ogre::MeshPtr
createNullMeshForSkeleton(const String& meshName, const Ogre::SkeletonPtr& skeleton);

extern Ogre::MeshPtr
createNullMeshForSkeleton(const Ogre::SkeletonPtr& skeleton);

//////////////////////////////////////////////////////////////////////////

extern bool
convertEntityToHardwareSkinning(Ogre::Entity* entity,std::vector<String>& DerivedMat);

extern Ogre::MaterialPtr
deriveHardwareSkinningMaterial( Ogre::SubEntity& subEntity );

typedef std::vector<Ogre::MaterialPtr> DerivedMaterialsList;

extern bool
deriveHardwareSkinningMaterial( Ogre::Entity& entity, DerivedMaterialsList& materials );

extern const Ogre::String&
deriveHardwareSkinningTransparentGpuProgram( const Ogre::String& gpuProgramName, int texunitNumber, bool hasFog );

}

#endif // __OGUtils_H__
