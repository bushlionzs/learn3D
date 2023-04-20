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
		return std::shared_ptr<Material>();
	}

	std::shared_ptr<Shader> MaterialManager::buildShader(ShaderInfo& sinfo)
	{
		auto shader = Ogre::Root::getSingleton().getRenderSystem()->createShader(sinfo);
		return std::shared_ptr<Shader>(shader);
	}

	bool MaterialManager::unloadUnreferencedResource(const String& name)
	{
		return true;
	}

}