#pragma once

#include "OgreSingleton.h"
#include "texture.h"

class ModelLoader;

#include "OgreScriptLoader.h"

namespace Ogre {

    class ResourceManager : public Ogre::Singleton<ResourceManager>
    {
    public:

        static const String DEFAULT_RESOURCE_GROUP_NAME;
        ResourceManager();
        ~ResourceManager();

        void addDirectory(
            const String& dir, 
            const String& group = BLANKSTRING, 
            bool recursive = true);
        void loadAllResource();

        ResourceInfo* getResource(const String& name, const String& group = BLANKSTRING);

        std::shared_ptr<DataStream> openResource(
            const String& name, const String& group = BLANKSTRING);

        bool hasResource(const String& name, const String& group = BLANKSTRING);
        std::shared_ptr<Mesh> loadMeshFromFile(
            const std::string& name, 
            const String& group = BLANKSTRING);

        bool _addResource(
            const String& name, 
            ResourceInfo* res, 
            bool forceUpdate = false,
            const String& group = BLANKSTRING);
        virtual void _notifyResourceLoaded(Resource* res) {}

        /** Notify this manager that a resource which it manages has been
            unloaded.
        */
        virtual void _notifyResourceUnloaded(Resource* res) {}

        virtual void _notifyResourceTouched(Resource* res) {}
    private:
        void readDir(const String& dir, bool recursive);

        void registerMeshSerializer();
    private:
        std::unordered_map<std::string, ResourceInfo*> mResourceMap;

        std::unordered_set<std::string> mDirectorySet;
        std::unordered_set<std::string> mDirectorySetRecursive;
        std::unordered_map<std::string, ModelLoader*> mMeshMap;
    };
}