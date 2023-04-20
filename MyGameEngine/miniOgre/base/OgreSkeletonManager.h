#pragma once

#include "OgreSingleton.h"

class RenderSystem;

namespace Ogre {
    class SkeletonManager : public Ogre::Singleton<SkeletonManager>
    {
    public:
        SkeletonManager();
        ~SkeletonManager();

        std::shared_ptr<Skeleton> load(const std::string& name);
        std::shared_ptr<Skeleton> create(const std::string& name);
        void remove(const std::string& name);
    private:
        std::unordered_map<std::string, std::shared_ptr<Skeleton>> mSkeletonMap;
    };
}