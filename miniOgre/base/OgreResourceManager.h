#pragma once

#include "OgreSingleton.h"
#include "OgreTexture.h"
#include "OgreResourceLoader.h"
#include "OgreScriptLoader.h"

class ModelLoader;

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

        ResourceInfo* getResourceInfo(const String& name, const String& group = BLANKSTRING);

        std::shared_ptr<DataStream> openResource(
            const String& name, const String& group = BLANKSTRING);

        bool hasResource(const String& name, const String& group = BLANKSTRING);

        void addResource(MeshLoadDesc* pMeshDesc, SyncToken* token);

        void addResource(TextureLoadDesc* pTextureDesc, SyncToken* token);
        bool _addResource(
            const String& name, 
            ResourceInfo* res, 
            bool forceUpdate = false,
            const String& group = BLANKSTRING);

        utils::JobSystem& getJobSystem()
        {
            return mJobSystem;
        }
        virtual void _notifyResourceLoaded(Resource* res) {}

        /** Notify this manager that a resource which it manages has been
            unloaded.
        */
        virtual void _notifyResourceUnloaded(Resource* res) {}

        virtual void _notifyResourceTouched(Resource* res) {}
    private:
        void readDir(const String& dir, bool recursive);

    private:
        std::unordered_map<std::string, ResourceInfo*> mResourceMap;

        std::unordered_set<std::string> mDirectorySet;
        std::unordered_set<std::string> mDirectorySetRecursive;
        utils::JobSystem mJobSystem;
    };
}