#include "OgreHeader.h"
#include "OGUtils.h"
#include "OGResources.h"
#include <iomanip>
#include <OgreMeshManager.h>
#include <OgreMaterialManager.h>
#include <OgreFrustum.h>
#include <OgreHardwareBufferManager.h>
#include <OgreSubMesh.h>
#include <OgreRoot.h>
#include <OgreEntity.h>
#include <OgreParticleSystemManager.h>
#include "OgreMaterialManager.h"
#include <OgreBone.h>
#include <OgreAnimation.h>
#include <OgreSubEntity.h>
#include <algorithm>
#include "OgreSceneManager.h"
#include "OgreAnimationState.h"
#include "OgreSkeleton.h"
#include "OgreBone.h"
#include "animation_track.h"
#include "keyframe.h"
#include "OgreTextureUnit.h"

namespace Ogre {

	//extern "C" void installScorpioPlugin(void) throw();
    bool convertEntityToHardwareSkinning(Entity* entity,
        size_t maxSimultaneousLights,
        std::vector<String>& DerivedMat)
    {
        return true;
    }

}


namespace Orphigine {

using namespace Ogre;



MaterialPtr
createPureColourMaterial(const ColourValue& colour)
{
    RGBA rgba = colour.getAsRGBA();

    std::stringstream str;
    str << "PureColour" << std::hex << std::setfill('0') << std::setw(8) << rgba;
    String name = str.str();

    auto res = MaterialManager::getSingleton().getByName(name);
    if (res)
        return std::dynamic_pointer_cast<Material>(res);

    MaterialPtr material = MaterialManager::getSingleton().create(name);
    material->setAmbient(0, 0, 0);
    material->setDiffuse(0, 0, 0, colour.a);
    material->setSelfIllumination(colour);
    material->setFog(true, FOG_NONE);
    if (colour.a != 1)
        material->setSceneBlending(SBT_TRANSPARENT_ALPHA);
    return material;
}

MaterialPtr
createColourMaterial(const ColourValue& colour)
{
    if (colour == ColourValue::White)
        return MaterialManager::getSingleton().getByName("BaseWhite");

    RGBA rgba = colour.getAsRGBA();

    std::stringstream str;
    str << "Colour_" << std::hex << std::setfill('0') << std::setw(8) << rgba;
    String name = str.str();

    auto res = MaterialManager::getSingleton().getByName(name);
    if (res)
        return res;

    MaterialPtr material = MaterialManager::getSingleton().create(name);
    material->setAmbient(colour);
    material->setDiffuse(colour);
    if (colour.a != 1)
        material->setSceneBlending(SBT_TRANSPARENT_ALPHA);
    return material;
}

MaterialPtr
createColourMaterial(const ColourValue& colour, const ColourValue& specular, Real shininess)
{
    if (shininess == 0 || specular == ColourValue::Black)
        return createColourMaterial(colour);

    RGBA rgba = colour.getAsRGBA();
    RGBA rgbaSpecular = specular.getAsRGBA();


    std::stringstream str;
    str << "Colour_" << std::hex << std::setfill('0')
        << std::setw(8) << rgba
        << std::setw(0) << '_'
        << std::setw(8) << rgbaSpecular
        << std::setw(0) << '_' << shininess;
    String name = str.str();

    auto res = MaterialManager::getSingleton().getByName(name);
    if (res)
        return res;

    MaterialPtr material = MaterialManager::getSingleton().create(name);
    material->setAmbient(colour);
    material->setDiffuse(colour);
    material->setSpecular(specular);
    material->setShininess(shininess);
    if (colour.a != 1)
        material->setSceneBlending(SBT_TRANSPARENT_ALPHA);
    return material;
}

//////////////////////////////////////////////////////////////////////////

MaterialPtr
createProjectiveMaterial(const String& materialTemplateName, const Frustum* frustum)
{
    if (materialTemplateName.empty())
    {
        OGRE_EXCEPT(Exception::ERR_INVALIDPARAMS,
            "You must give a material template name for create projective material.",
            "createProjectiveMaterial");
    }

    // Build the material from template
    MaterialPtr material = MaterialManager::getSingleton().getByName(materialTemplateName);
    if (!material)
    {
        OGRE_EXCEPT(Exception::ERR_ITEM_NOT_FOUND,
            "Can't found material with name " + materialTemplateName +
            "Have you forgotten to define it in a  .material script?",
            "createProjectiveMaterial");
    }

    material = material->clone(material->getName() + "/Projectived/" + frustum->getName());
    fixupProjectiveMaterial(material, frustum);

    return material;
}

void
fixupProjectiveMaterial(const MaterialPtr& material, const Frustum* frustum)
{
    std::vector<std::shared_ptr<TextureUnit>>& tus = material->getAllTexureUnit();

    for (auto itor = tus.begin(); itor != tus.end(); itor++)
    {
        (*itor)->setProjectiveTexturing(true, frustum);
    }
}

//////////////////////////////////////////////////////////////////////////

typedef std::list<MoveObject*> ObjectList;


static void addAttachedObject(MoveObject* object, ObjectList& objects);

template <class Iterator>
static inline void
addAttachedObjects(Iterator it, ObjectList& objects)
{
    while (it.hasMoreElements())
    {
        MoveObject* object = it.getNext();
        addAttachedObject(object, objects);
    }
}

static void
addAttachedObject(MoveObject* object, ObjectList& objects)
{
    objects.push_back(object);

    if (object->getMovableType() == "Entity")
    {
        Entity* entity = static_cast<Entity*>(object);

        const Ogre::Entity::ChildObjectList& childs = entity->getAttachedObjects();

        for (auto it = childs.begin(); it != childs.end(); it++)
        {
            addAttachedObject(*it, objects);
        }
    }
}

void
findAllAttachedObjects(SceneNode* sn, ObjectList& objects)
{
    const Ogre::SceneNode::ObjectMap& objs = sn->getAttachedObjects();

    for (auto it = objs.begin(); it != objs.end(); it++)
    {
        addAttachedObject(it->second, objects);
    }

    const Ogre::SceneNode::ChildNodeMap& childs = sn->getChildren();

    for (auto it = childs.begin(); it != childs.end(); it++)
    {
        SceneNode* child = (SceneNode*)(*it);
        findAllAttachedObjects(child, objects);
    }
}

void
destroyObject(SceneManager* creator, MoveObject* object)
{
    const String& type = object->getMovableType();
    const String& name = object->getName();

    if (type == "Entity")
    {
        creator->destroyEntity(name);
    }
    else if (type == "Camera")
    {
        creator->destroyCamera(name);
    }
    else if (type == "Light")
    {
        creator->destroyLight(name);
    }
    else if (type == "BillboardSet")
    {
        creator->removeBillboardSet(name);
    }
    else if (type == "StaticGeometry")
    {
        creator->destroyStaticGeometry(name);
    }
    else if (type == "ParticleSystem")
    {
        creator->destroyParticleSystem(name);
    }
    else
    {
        OGRE_EXCEPT(Exception::ERR_INTERNAL_ERROR,
            "Unknown object type " + type,
            "destroyObject");
    }
}

void
destroyObjects(SceneManager* creator, const ObjectList& objects)
{
    for (ObjectList::const_iterator it = objects.begin(); it != objects.end(); ++it)
    {
        destroyObject(creator, *it);
    }
}

void
cleanupSceneNode(SceneNode* sn)
{
    ObjectList objects;
    findAllAttachedObjects(sn, objects);
    sn->removeAndDestroyAllChildren();

    destroyObjects(sn->getCreator(), objects);
}

void
cleanupAndDestroySceneNode(SceneNode* sn)
{
    cleanupSceneNode(sn);
    sn->getCreator()->destroySceneNode(sn);
}

//////////////////////////////////////////////////////////////////////////

AnimationState*
getAnimationStateSafely(AnimationStateSet* animationStateSet, const String& name)
{
    if (animationStateSet)
    {
        if (animationStateSet->hasAnimationState(name))
            return animationStateSet->getAnimationState(name);

    }

    return NULL;
}

AnimationState*
getAnimationStateSafely(Entity* entity, const String& name)
{
    assert(entity);
    return getAnimationStateSafely(entity->getAllAnimationStates(), name);
}

Animation*
getAnimationSafely(const Skeleton* skeleton, const String& name)
{
    return skeleton ? skeleton->_getAnimationImpl(name, nullptr) : 0;
}

Animation*
getAnimationSafely(const SkeletonPtr& skeleton, const String& name)
{
    return getAnimationSafely(skeleton.get(), name);
}

Animation*
getAnimationSafely(const Mesh* mesh, const String& name)
{
    return mesh ? getAnimationSafely(mesh->getSkeleton(), name) : 0;
}

Animation*
getAnimationSafely(const MeshPtr& mesh, const String& name)
{
    return getAnimationSafely(mesh.get(), name);
}

//////////////////////////////////////////////////////////////////////////

static AxisAlignedBox
_getSkeletonBoundingBox(const Skeleton* _skeleton, bool deltaOnly)
{
    Skeleton* skeleton = const_cast<Skeleton*>(_skeleton);
    assert(skeleton);

    AxisAlignedBox boundingBox;

    // calculate bone initial positions
    std::map<Bone*, Vector3> boneInitialPositions;

    skeleton->reset();
    int boneCount = skeleton->getNumBones();
    for(int32_t i = 0 ; i< boneCount; i++)
    {
        Bone* bone = skeleton->getBone(i);
        const Vector3& pos = bone->_getDerivedPosition();
        if (deltaOnly)
        {
            boneInitialPositions[bone] = pos;
        }
        else
        {
            boundingBox.merge(pos);
        }
    }

    // create animation state set
    AnimationStateSet animationStateSet;
    skeleton->_initAnimationState(&animationStateSet);

    // for each animation
    const AnimationStateMap& aniMap = animationStateSet.getAnimationStates();
    for(auto& ele:aniMap)
    {
        AnimationState* as = ele.second;

        typedef std::set<Real> RealSet;
        typedef ConstVectorIterator<RealSet> ConstRealSetIterator;

        // collect key frame times
        RealSet keyFrameTimes;
        Animation* animation = skeleton->getAnimation(as->getAnimationName());
        const Ogre::Animation::NodeTrackList& nodetracks =  animation->_getNodeTrackList();
        auto nti = nodetracks.begin();
        while (nti != nodetracks.end())
        {
            AnimationTrack* nt = nti->second;
            nti++;
            for (ushort i = 0; i < nt->getNumKeyFrames(); ++i)
            {
                KeyFrame* tkf = nt->getNodeKeyFrame(i);
                keyFrameTimes.insert(tkf->getTimePos());
            }
        }

        // collect bounds of the animation
        as->setEnabled(true);
        ConstRealSetIterator kfti(keyFrameTimes.begin(), keyFrameTimes.end());
        while (kfti.hasMoreElements())
        {
            // Applies the time position
            as->setTimePosition(kfti.getNext());
            skeleton->setAnimationState(animationStateSet);
            int32_t boneCount = skeleton->getNumBones();
            for(int32_t i = 0; i < boneCount; i++)
            {
                Bone* bone = skeleton->getBone(i);
                const Vector3& pos = bone->_getDerivedPosition();
                if (deltaOnly)
                {
                    boundingBox.merge(pos - boneInitialPositions[bone]);
                }
                else
                {
                    boundingBox.merge(pos);
                }
            }
        }
        as->setEnabled(false);
    }

    // reset skeleton
    skeleton->reset();

    return boundingBox;
}

AxisAlignedBox
skinningTransformBoundingBox(const AxisAlignedBox& boundingBox, const Skeleton* skeleton)
{
    if (boundingBox.isNull())
        return boundingBox;

    AxisAlignedBox deltaBoundingBox = _getSkeletonBoundingBox(skeleton, true);
    if (deltaBoundingBox.isNull())
        return boundingBox;

    AxisAlignedBox newBoundingBox(boundingBox);
    newBoundingBox.merge(boundingBox.getMinimum() + deltaBoundingBox.getMinimum());
    newBoundingBox.merge(boundingBox.getMaximum() + deltaBoundingBox.getMaximum());
    return newBoundingBox;
}

AxisAlignedBox
skinningTransformBoundingBox(const AxisAlignedBox& boundingBox, const SkeletonPtr& skeleton)
{
    return skinningTransformBoundingBox(boundingBox, skeleton.get());
}

AxisAlignedBox
getSkeletonBoundingBox(const Skeleton* skeleton)
{
    return _getSkeletonBoundingBox(skeleton, false);
}

AxisAlignedBox
getSkeletonBoundingBox(const SkeletonPtr& skeleton)
{
    return getSkeletonBoundingBox(skeleton.get());
}




//////////////////////////////////////////////////////////////////////////

typedef bool ConvertEntityToHardwareSkinningFunc(Ogre::Entity* entity, size_t maxSimultaneousLights);

static bool convertEntityToHardwareSkinning_Noop(Ogre::Entity* entity, size_t maxSimultaneousLights);

static bool convertEntityToHardwareSkinning_Noop(Ogre::Entity* entity, size_t maxSimultaneousLights)
{
    return false;
}

extern bool convertEntityToHardwareSkinning(Ogre::Entity* entity,std::vector<String>& DerivedMat)
{
	return Ogre::convertEntityToHardwareSkinning(entity, 3,DerivedMat);

}

class HardwareSkinningGpuProgramParameters
{
public:
	ushort mBlendMatrixCount;
	ushort mMaxBlendWeight;
	ushort mTexCoordCount;
	ushort mTexUnitCount;

	bool mEnableLighting;
	bool mAmbientLighting;
	bool mSpecularLighting;
	bool mVertexFog;
	bool mOmitLastBlendWeight;
	bool mProjectiveTexture;

	HardwareSkinningGpuProgramParameters( ushort blendMatrixCount = 0, ushort maxBlendWeight = 1, ushort texcoordNumber = 1, ushort texunitNumber = 1, bool vertexFog = true, 
		bool enableLighting = false, bool ambientLighting = true, bool specularLighting = false, bool omitLastBlendWeight = true, bool projectiveTexture = false );

	static bool parse( const String& name, HardwareSkinningGpuProgramParameters* pGpuProgramParameters = NULL );
	const String& toString( ) const;

	void enableLighting( bool enable );

protected:
	const String& getGpuProgramSyntaxCode( ) const;

	bool deriveBlendMatrixMaxNumber( ) const;
	uint32 getRegisterNumberPerLight( ) const;

	String derivePreprocessorDefines( ) const;

	mutable uint32 mDerivedBlendMatrixCount;
	mutable uint32 mDerivedSupportLightCount;

	static const uint32 msMinSupportLightCount;
	static const uint32 msMaxSupportLightCount;

	const static String msPatternPrefix;
	static String msPattern;

	static const char msZero;
};

const String HardwareSkinningGpuProgramParameters::msPatternPrefix = "HardwareSkinningGpuProgram";
String HardwareSkinningGpuProgramParameters::msPattern = HardwareSkinningGpuProgramParameters::msPatternPrefix + "%%%%%";

const char HardwareSkinningGpuProgramParameters::msZero = '0';

const uint32 HardwareSkinningGpuProgramParameters::msMinSupportLightCount = 2;
const uint32 HardwareSkinningGpuProgramParameters::msMaxSupportLightCount = 8;

HardwareSkinningGpuProgramParameters::HardwareSkinningGpuProgramParameters( ushort blendMatrixCount, ushort maxBlendWeight, ushort texcoordNumber, ushort texunitNumber, 
	bool vertexFog, bool enableLighting, bool ambientLighting, bool specularLighting, bool omitLastBlendWeight, bool projectiveTexture )
{
	mBlendMatrixCount = blendMatrixCount;
	mMaxBlendWeight = maxBlendWeight;
	mTexCoordCount = texcoordNumber;
	mTexUnitCount = texunitNumber;

	mEnableLighting = enableLighting;
	mAmbientLighting = ambientLighting;
	mSpecularLighting = specularLighting;
	mVertexFog = vertexFog;
	mOmitLastBlendWeight = omitLastBlendWeight;
	mProjectiveTexture = projectiveTexture;

	mDerivedBlendMatrixCount = 0;
	mDerivedSupportLightCount = 0;
}

bool HardwareSkinningGpuProgramParameters::parse( const String& name, HardwareSkinningGpuProgramParameters* pGpuProgramParameters )
{
	if ( name.length( ) < msPattern.length( ) )
		return false;

	if ( pGpuProgramParameters == NULL )
		return true;

	size_t index = msPatternPrefix.length( );

	pGpuProgramParameters->mTexCoordCount = name[index++] - msZero;
	pGpuProgramParameters->mTexUnitCount = name[index++] - msZero;
	pGpuProgramParameters->mMaxBlendWeight = name[index++] - msZero;
	pGpuProgramParameters->mVertexFog = ( (name[index++] - msZero) != 0 );
	pGpuProgramParameters->mDerivedSupportLightCount = name[index++] - msZero;

	return true;
}

const String& HardwareSkinningGpuProgramParameters::toString( ) const
{
	size_t index = msPatternPrefix.length( );

	msPattern[index++] = msZero + mTexCoordCount;
	msPattern[index++] = msZero + mTexUnitCount;
	msPattern[index++] = msZero + mMaxBlendWeight;
	msPattern[index++] = mVertexFog ? '1' : '0';
	msPattern[index++] = msZero + mDerivedSupportLightCount;

	return msPattern;
}

void HardwareSkinningGpuProgramParameters::enableLighting( bool enable )
{
	mEnableLighting = enable;
	mDerivedSupportLightCount = 0;
}

Ogre::MaterialPtr
deriveHardwareSkinningMaterial(Ogre::SubEntity& subEntity)
{
    return Ogre::MaterialPtr();
}
bool deriveHardwareSkinningMaterial(Ogre::Entity& entity,
    DerivedMaterialsList& materials)
{
    return false;
}

Ogre::MeshPtr
createNullMeshForSkeleton(const String& meshName,
    const Ogre::SkeletonPtr& skeleton)
{
    MeshManager& mm = MeshManager::getSingleton();

    MeshPtr mesh = mm.getByName(meshName);
    if (!mesh)
    {
        if (meshName == skeleton->getName())
        {
            mesh = mm.createManual(meshName);
        }
        else
        {
            mesh = mm.createManual(meshName);
        }

        mesh->load();
    }

    return mesh;
}

Ogre::MeshPtr
createNullMeshForSkeleton(const Ogre::SkeletonPtr& skeleton)
{
    auto mesh = MeshManager::getSingleton().createManual(skeleton->getName());

    mesh->setSkeletonName(skeleton->getName());

    return mesh;
}




}
