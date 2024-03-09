#include "OgreHeader.h"
#include "OgreSkeletonManager.h"
#include "OgreResourceManager.h"
#include "myutils.h"
#include "OgreSkeleton.h"
#include "ogre_skeleton_serializer.h"


namespace Ogre {
	template<> SkeletonManager* Ogre::Singleton<SkeletonManager>::msSingleton = 0;
	SkeletonManager::SkeletonManager()
	{

	}

	SkeletonManager::~SkeletonManager()
	{

	}

	std::shared_ptr<Skeleton> SkeletonManager::load(const std::string& name)
	{
		auto itor = mSkeletonMap.find(name);
		if (itor != mSkeletonMap.end())
		{
			return itor->second;
		}

		if (!ResourceManager::getSingletonPtr()->hasResource(name))
		{
			WARNING_LOG("fail to load skeleton:%s", name.c_str());
			return std::shared_ptr<Skeleton>();
		}

		std::shared_ptr<DataStream> stream =
			ResourceManager::getSingletonPtr()->openResource(name);

		std::shared_ptr<Skeleton> skeleton = std::make_shared<Skeleton>(name);

		mSkeletonMap[name] = skeleton;
		OgreSkeletonSerializerImpl serializer;

		serializer.importSkeleton(stream, skeleton.get());
		return skeleton;
	}

	std::shared_ptr<Skeleton> SkeletonManager::create(const std::string& name)
	{
		auto itor = mSkeletonMap.find(name);
		if (itor != mSkeletonMap.end())
		{
			assert(false);
			return std::shared_ptr<Skeleton>();
		}

		std::shared_ptr<Skeleton> skeleton(new Skeleton(name));
		mSkeletonMap[name] = skeleton;
		return skeleton;
	}

	void SkeletonManager::remove(const std::string& name)
	{

	}
}