#pragma once

#include "OgreSingleton.h"
#include "OgreMaterial.h"
#include "shader.h"
class RenderSystem;

namespace Ogre {
    class MaterialManager : public Ogre::Singleton<MaterialManager>
    {
    public:
        static String DEFAULT_SCHEME_NAME;
    public:
        MaterialManager();
        ~MaterialManager();
        std::shared_ptr<Material>& getDefaultMaterial();
        std::shared_ptr<Material> create(const std::string& name, bool pbr = false);
        bool remove(const std::string& name);
        bool remove(uint64_t handle);
        std::shared_ptr<Material> getByName(const std::string& name, const std::string& group = BLANKSTRING) const;

        std::shared_ptr<Shader> buildShader(ShaderInfo& sinfo);

        bool unloadUnreferencedResource(const String& name);
    private:
        std::unordered_map<std::string, std::shared_ptr<Material>> mMaterialMap;

        std::shared_ptr<Material> mDefaultMaterail;
    };
}