#include "OgreHeader.h"
#include "OgreResourceManager.h"
#include "myutils.h"
#include "file_stream.h"
#include "OgreMemoryStream.h"
#include "OgreMesh.h"
#include "m3d_loader.h"
#include "ogre_loader.h"
#include "gltf_loader.h"
#include "ResourceParserManager.h"
#include "OgreScriptLoader.h"
#include "renderSystem.h"
#include "OgreRoot.h"
#include "platform_file_system.h"


namespace Ogre {
    template<> ResourceManager* Ogre::Singleton<ResourceManager>::msSingleton = 0;
    ResourceManager::ResourceManager()
    {
        registerMeshSerializer();
    }

    ResourceManager::~ResourceManager()
    {

    }

    void ResourceManager::addDirectory(
        const String& dir, 
        const String& group,
        bool recursive)
    {
        String full = CPlatformFileSystem::GetInstance()->getFullPath(dir);
        if (recursive)
        {
            mDirectorySetRecursive.insert(full);
            
        }
        else
        {
            mDirectorySet.insert(full);
        }
        
    }

    void ResourceManager::loadAllResource()
    {
        for (auto& it : mDirectorySet)
        {
            readDir(it, false);
        }

        for (auto& it : mDirectorySetRecursive)
        {
            readDir(it, true);
        }

        String suffix;
        for (auto& res : mResourceMap)
        {
            size_t npos = res.second->_fullname.find_last_of('.');
            if (npos != String::npos)
            {
                suffix = res.second->_fullname.substr(npos);

                ScriptLoader* loader = ResourceParserManager::getSingleton().getLoader(suffix);
                if (loader)
                {
                    loader->addResourceInfo(res.second);
                }
            }
        }

        ResourceParserManager::getSingleton().parserAll();

        Ogre::Root::getSingleton().getRenderSystem()->_resourceLoaded();
    }

    ResourceInfo* ResourceManager::getResource(const std::string& name, const String& group)
    {
        auto it = mResourceMap.find(name);

        if (it != mResourceMap.end())
        {
            return it->second;
        }
        return nullptr;
    }

    void ResourceManager::readDir(const std::string& dir, bool recursive)
    {
        WIN32_FIND_DATAA FindData;
        char namebuf[1024];
        sprintf(namebuf, "%s\\*.*", dir.c_str());
        HANDLE handle = FindFirstFile(namebuf, &FindData);

        ResourceInfo res;
        while (FindNextFile(handle, &FindData))
        {
            if (FindData.cFileName[0] == '.')
                continue;


            res._fullname = dir;
            res._fullname += "\\";
            res._fullname += FindData.cFileName;

            if (FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {
                if (recursive)
                {
                    std::string subdir = res._fullname;
                    readDir(subdir, true);
                }
                
                continue;
            }

            ResourceInfo* resInfo = new ResourceInfo;
            *resInfo = res;
            auto i = mResourceMap.emplace(std::pair<std::string, ResourceInfo*>(FindData.cFileName, resInfo));
            assert(i.second);
        }
    }

    std::shared_ptr<Mesh> ResourceManager::loadMeshFromFile(
        const std::string& name, const String& group)
    {
        std::string suffix = getSuffix(name);

        auto itor = mMeshMap.find(suffix);

        if (itor == mMeshMap.end())
        {
            return std::shared_ptr<Mesh>();
        }

        if (!hasResource(name, group))
        {
            WARNING_LOG("fail to load mesh:%s", name.c_str());
            return std::shared_ptr<Mesh>();
        }
        std::shared_ptr<DataStream> stream = openResource(name, group);




        std::shared_ptr<Mesh> mesh = itor->second->loadMeshFromFile(stream);

        if (mesh)
        {
            mesh->buildHardBuffer();
        }

        return mesh;
    }

    void ResourceManager::registerMeshSerializer()
    {
        mMeshMap[".m3d"] = new M3dLoader;
        mMeshMap[".mesh"] = new OgreMeshLoader;
        mMeshMap[".gltf"] = new GltfLoader;
        mMeshMap[".glb"] = new GltfLoader;
    }

    std::shared_ptr<DataStream> ResourceManager::openResource(
        const String& name, const String& group)
    {
        ResourceInfo* res = ResourceManager::getSingletonPtr()->getResource(name);

        assert(res != nullptr);

        return std::shared_ptr<DataStream>(new MemoryDataStream(res));
    }

    bool ResourceManager::hasResource(const String& name, const String& group)
    {
        ResourceInfo* res = ResourceManager::getSingletonPtr()->getResource(name);

        return res != nullptr;
    }

    bool ResourceManager::_addResource(
        const String& name,
        ResourceInfo* res,
        const String& group)
    {
        auto itor = mResourceMap.find(name);
        if (itor != mResourceMap.end())
        {
            OGRE_EXCEPT(Exception::ERR_INTERNAL_ERROR, "resource already exist!");
            return false;
        }

        mResourceMap[name] = res;
        return true;
    }
}
