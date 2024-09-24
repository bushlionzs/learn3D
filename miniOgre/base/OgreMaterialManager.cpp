#include "OgreHeader.h"
#include "OgreMaterialManager.h"
#include "renderSystem.h"
#include "OgreResourceManager.h"
#include "OgreRoot.h"

template<> Ogre::MaterialManager* Ogre::Singleton<Ogre::MaterialManager>::msSingleton = 0;
namespace Ogre {

	String MaterialManager::DEFAULT_SCHEME_NAME = "__default__";
	MaterialManager::MaterialManager()
	{
	}

	MaterialManager::~MaterialManager()
	{

	}

	std::shared_ptr<Material>& MaterialManager::getDefaultMaterial()
	{
		if (!mDefaultMaterail)
		{
			mDefaultMaterail = getByName(DEFAULT_SCHEME_NAME);
		}
		return mDefaultMaterail;
	}

	std::shared_ptr<Material> MaterialManager::create(const std::string& name, bool pbr)
	{
		auto it = mMaterialMap.find(name);
		if (it != mMaterialMap.end())
		{
			assert(false);
		}

		std::shared_ptr<Material> p = std::make_shared<Material>(name, pbr);
		mMaterialMap[name] = p;
		return p;
	}

	bool MaterialManager::remove(const std::string& name)
	{
		return false;
	}
	bool MaterialManager::remove(uint64_t handle)
	{
		return false;
	}

	std::shared_ptr<Material> MaterialManager::getByName(const std::string& name, const std::string& group) const
	{
		auto it = mMaterialMap.find(name);
		if (it != mMaterialMap.end())
		{
			return it->second;
		}

		WARNING_LOG("fail to load material:%s", name.c_str());
		return std::shared_ptr<Material>();
	}

	bool MaterialManager::unloadUnreferencedResource(const String& name)
	{
		return true;
	}

}