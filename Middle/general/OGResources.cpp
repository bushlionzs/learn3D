#include "OgreHeader.h"
#include "OGResources.h"
#include <OgreMesh.h>
#include <OgreSkeleton.h>
#include <OgreMeshManager.h>
#include <OgreSkeletonManager.h>
#include <platform_log.h>
#include "OgreResourceManager.h"
#include "OgreString.h"

namespace Orphigine {

const String GRAMMAR_RESOURCE_GROUP_NAME = "Grammar";
const String EDITOR_RESOURCE_GROUP_NAME = "Orphigine Editor";

const String SCENE_SCHEMA_NAME = "OrphigineScene.xsd";
const String TERRAIN_SCHEMA_NAME = "OrphigineTerrain.xsd";

//const String BOOTSTRAP_RESOURCE_GROUP_NAME = "Bootstrap";
const String BRUSH_RESOURCE_GROUP_NAME = "Brushes";

const String AUTO_ANIMATION_NAME = "[auto]";

FakeManualResourceLoader gsFakeManualResourceLoader;

bool
splitResourceName(const String& name, String& resourceName, String& groupName)
{
    String::size_type pos = name.find_first_of(':');
    if (pos == String::npos)
    {
        resourceName = name;
        return false;
    }
    else
    {
        groupName = name.substr(0, pos);
        resourceName = name.substr(pos+1, String::npos);
        return true;
    }
}
/*
bool
findCorrelativeResource(String& resourceName, String& groupName,
                        const String& baseResourceName, const String& baseGroupName)
{
    Ogre::ResourceGroupManager& mgr = Ogre::ResourceGroupManager::getSingleton();

    String name, path;
    Ogre::StringUtil::splitFilename(resourceName, name, path);
    bool existsPath = !path.empty();

    // First, find in correlatived group and path if resource name doesn't exists path
    if (!existsPath)
    {
        Ogre::StringUtil::splitFilename(baseResourceName, name, path);
        if (!path.empty())
        {
            name = path + resourceName;
            if (mgr.resourceExists(baseGroupName, name))//----需要改进性能----[2009/07/27 dscky add]
            {
                resourceName = name;
                groupName = baseGroupName;
                return true;
            }
        }
    }

    // Second, find in correlatived group
    if (mgr.resourceExists(baseGroupName, resourceName))//----需要改进性能----[2009/07/27 dscky add]
    {
        groupName = baseGroupName;
        return true;
    }

    // Three, find in user given group
    if (!groupName.empty())
    {
        if (mgr.resourceExists(groupName, resourceName))//----需要改进性能----[2009/07/27 dscky add]
        {
            return true;
        }
    }

    // Four, find in global default group
    if (groupName != BOOTSTRAP_RESOURCE_GROUP_NAME)
    {
        if (mgr.resourceExists(BOOTSTRAP_RESOURCE_GROUP_NAME, resourceName))//----需要改进性能----[2009/07/27 dscky add]
        {
            groupName = DEFAULT_RESOURCE_GROUP_NAME;
            return true;
        }
    }

    return false;
}
*/

Ogre::ResourcePtr
tryLoadResource(Ogre::ResourceManager& resourceManager,
                 const String& resourceName, const String& groupName)
{
    return Ogre::ResourcePtr();
}

Ogre::ResourcePtr
loadCorrelativeResource(const String& resourceName, const String& groupName,
                        const String& baseResourceName, const String& baseGroupName,
                        Ogre::ResourceManager& resourceManager)
{
    Ogre::ResourcePtr res;

    String name, path;
    Ogre::StringUtil::splitFilename(resourceName, name, path);
    bool existsPath = !path.empty();

    // First, load in correlatived group and path if resource name doesn't exists path
    if (!existsPath)
    {
        Ogre::StringUtil::splitFilename(baseResourceName, name, path);
        if (!path.empty())
        {
            name = path + resourceName;
            res = tryLoadResource(resourceManager, name, baseGroupName);
            if (res)
                return res;
        }
    }

    // Second, load in correlatived group
    res = tryLoadResource(resourceManager, resourceName, baseGroupName);
    if (res)
        return res;

    // Three, load in user given group
    if (!groupName.empty())
    {
        res = tryLoadResource(resourceManager, resourceName, groupName);
        if (res)
            return res;
    }

  
    res = tryLoadResource(resourceManager, resourceName, groupName);
    return res;
}

Ogre::ResourcePtr
loadCorrelativeResource(const String& resourceName, const String& groupName,
    const String& baseResourceName, const String& baseGroupName)
{
    return Ogre::ResourcePtr();
}
Ogre::MeshPtr
loadMesh(const String& meshName, const String& groupName,
         const String& baseResourceName, const String& baseGroupName)
{
    // Load the mesh
    
    Ogre::MeshPtr mesh = MeshManager::getSingleton().load(meshName);

    if (!mesh)
    {
        OGRE_EXCEPT(Ogre::Exception::ERR_ITEM_NOT_FOUND,
            "Unable to load mesh " + meshName,
            "loadMesh");
    }

    // Try to resolve skeleton resource
    if (mesh->hasSkeleton() && !mesh->getSkeleton())
    {

        // resolve correlative with mesh
        Ogre::SkeletonPtr skeleton = std::dynamic_pointer_cast<Ogre::Skeleton>(loadCorrelativeResource(
            mesh->getSkeletonName(), groupName,
            mesh->getName(), mesh->getGroup()));

        if (!skeleton)
        {
            // resolve correlative with base resource
            skeleton = std::dynamic_pointer_cast<Ogre::Skeleton>(loadCorrelativeResource(
                mesh->getSkeletonName(), groupName,
                baseResourceName, baseGroupName));
        }

        if (!skeleton)
        {

			mesh->setSkeletonName("");
        }

		else
        // Set to the actual name
			mesh->setSkeletonName(skeleton->getName());
    }

    return mesh;
}

}
