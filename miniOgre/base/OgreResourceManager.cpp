#include "OgreHeader.h"
#include <windows.h>
#include "OgreResourceManager.h"
#include "myutils.h"
#include "OgreMemoryStream.h"
#include "ResourceParserManager.h"
#include "OgreScriptLoader.h"
#include "renderSystem.h"
#include "OgreRoot.h"
#include "platform_file_system.h"
#include "OgreMeshManager.h"
#include "OgreTextureManager.h"

namespace Ogre {
    template<> ResourceManager* Ogre::Singleton<ResourceManager>::msSingleton = 0;
    const String ResourceManager::DEFAULT_RESOURCE_GROUP_NAME;
    ResourceManager::ResourceManager()
        :mJobSystem(10)
    {
        
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
            readDir(full, true);
            
        }
        else
        {
            readDir(full, false);
        }
        
    }

    void ResourceManager::loadAllResource()
    {
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
    }

    ResourceInfo* ResourceManager::getResourceInfo(const std::string& name, const String& group)
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
            assert_invariant(i.second);
        }
    }

    std::shared_ptr<DataStream> ResourceManager::openResource(
        const String& name, const String& group)
    {
        ResourceInfo* res = ResourceManager::getSingletonPtr()->getResourceInfo(name);

        if (res == nullptr)
        {
            WARNING_LOG("fail to load file:%s", name.c_str());
            return std::shared_ptr<DataStream>();
        }

        return std::shared_ptr<DataStream>(new MemoryDataStream(res));
    }

    bool ResourceManager::hasResource(const String& name, const String& group)
    {
        ResourceInfo* res = ResourceManager::getSingletonPtr()->getResourceInfo(name);

        return res != nullptr;
    }

    void ResourceManager::addResource(MeshLoadDesc* pMeshDesc, SyncToken* token)
    {
        auto loadfunc = [](MeshLoadDesc* pMeshDesc) {
            auto mesh = MeshManager::getSingleton().load(pMeshDesc->pFileName);
            pMeshDesc->pMesh = mesh.get();
            };
        if (token)
        {
            auto* loadJob = utils::jobs::createJob(mJobSystem, token->rootJob, loadfunc, pMeshDesc);
            mJobSystem.run(loadJob);
        }
        else
        {
            loadfunc(pMeshDesc);
        }
    }

    void ResourceManager::addResource(TextureLoadDesc* pTextureDesc, SyncToken* token)
    {
        auto loadfunc = [](TextureLoadDesc* pTextureDesc) {
            auto tex = TextureManager::getSingleton().load(pTextureDesc->pFileName, pTextureDesc->tp);
            pTextureDesc->pTexture = tex.get();
            };
        if (token)
        {
            auto* loadJob = utils::jobs::createJob(mJobSystem, token->rootJob, loadfunc, pTextureDesc);
            mJobSystem.run(loadJob);
        }
        else
        {
            loadfunc(pTextureDesc);
        }
    }

    bool ResourceManager::_addResource(
        const String& name,
        ResourceInfo* res,
        bool forceUpdate,
        const String& group)
    {
        auto itor = mResourceMap.find(name);
        if (itor != mResourceMap.end())
        {
            //OGRE_EXCEPT(Exception::ERR_INTERNAL_ERROR, "resource already exist!");
            if(!forceUpdate)
                return false;
            delete itor->second;
            itor->second = res;
            return true;
        }

        mResourceMap[name] = res;
        return true;
    }
}
