#ifndef __OGResources_H__
#define __OGResources_H__

namespace Orphigine {

extern const String _OrphigineExport GRAMMAR_RESOURCE_GROUP_NAME;
extern const String _OrphigineExport EDITOR_RESOURCE_GROUP_NAME;

extern const String _OrphigineExport SCENE_SCHEMA_NAME;
extern const String _OrphigineExport TERRAIN_SCHEMA_NAME;

//extern const String _OrphigineExport DEFAULT_RESOURCE_GROUP_NAME;
extern const String _OrphigineExport BRUSH_RESOURCE_GROUP_NAME;

extern const String _OrphigineExport AUTO_ANIMATION_NAME;

class FakeManualResourceLoader
{
public:
    void loadResource(Ogre::Resource* resource)
    {
        // do nothing
    }
};

extern FakeManualResourceLoader gsFakeManualResourceLoader;

extern bool
_OrphigineExport splitResourceName(const String& name, String& resourceName, String& groupName);

//extern bool
//findCorrelativeResource(String& resourceName, String& groupName,
//                        const String& baseResourceName, const String& baseGroupName);

extern Ogre::ResourcePtr
loadCorrelativeResource(const String& resourceName, const String& groupName,
                        const String& baseResourceName, const String& baseGroupName);

extern Ogre::MeshPtr
_OrphigineExport loadMesh(const String& meshName, const String& groupName,
                    const String& baseResourceName, const String& baseGroupName);

}

#endif // __OGResources_H__
