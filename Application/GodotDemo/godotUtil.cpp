#include "godotUtil.h"
#include <core/config/project_settings.h>
#include <core/string/string_name.h>
#include <core/os/memory.h>
#include <core/io/file_access_pack.h>
#include <core/io/missing_resource.h>
#include <core/input/shortcut.h>
#include <core/io/resource_loader.h>
#include <core/io/translation_loader_po.h>
#include <core/io/resource_format_binary.h>
#include <core/io/resource_importer.h>
#include <core/io/image_loader.h>
#include <core/io/resource_uid.h>

#include <scene/3d/node_3d.h>
#include <scene/3d/camera_3d.h>
#include <scene/3d/lightmap_gi.h>
#include <scene/3d/reflection_probe.h>
#include <scene/3d/world_environment.h>
#include <scene/3d/mesh_instance_3d.h>
#include <scene/3d/physics/static_body_3d.h>
#include <scene/3d/physics/collision_object_3d.h>
#include <scene/3d/physics/collision_shape_3d.h>
#include <scene/3d/physics/collision_polygon_3d.h>
#include <scene/3d/physics/character_body_3d.h>
#include <scene/3d/gpu_particles_3d.h>
#include <scene/resources/3d/sky_material.h>
#include <scene/main/canvas_layer.h>
#include <scene/resources/3d/box_shape_3d.h>
#include <scene/resources/3d/concave_polygon_shape_3d.h>
#include <scene/resources/3d/capsule_shape_3d.h>

#include <scene/resources/packed_scene.h>
#include <scene/resources/resource_format_text.h>
#include <scene/resources/compressed_texture.h>
#include <scene/resources/gradient_texture.h>
#include <scene/resources/curve_texture.h>
#include <scene/resources/3d/primitive_meshes.h>
#include <scene/resources/particle_process_material.h>
#include <scene/gui/video_stream_player.h>
#include <scene/main/viewport.h>
#include <servers/rendering/rendering_server_default.h>
#include <servers/rendering/renderer_rd/renderer_compositor_rd.h>
#include <servers/rendering/shader_types.h>
#include <servers/physics_server_2d.h>
#include <servers/physics_server_3d_dummy.h>
#include <servers/physics_server_2d_dummy.h>
#include <servers/navigation_server_3d_dummy.h>
#include <servers/text/text_server_dummy.h>
#include <modules/register_module_types.h>
#include "rendering_context_driver_null.h"
#include <core/config/engine.h>
#include <editor/project_manager.h>
#include <editor/progress_dialog.h>
#include <platform/windows/os_windows.h>
#include <OgreHeader.h>
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreMeshManager.h>
#include <OgreVertexData.h>
#include <OgreIndexData.h>
#include <OgreVertexDeclaration.h>
#include <OgreEntity.h>
#include <OgreSubEntity.h>
#include <OgreMaterialManager.h>
#include <myutils.h>
static ProjectSettings* globals = nullptr;
static Input* input = nullptr;
class Main
{
private:
    String text_driver = "";
    int text_driver_idx = -1;
    
public:
        Main()
    {
            OS::get_singleton()->initialize();
            auto tsman = memnew(TextServerManager);
            if (tsman) {
                Ref<TextServerDummy> ts;
                ts.instantiate();
                tsman->add_interface(ts);
            }

            input = memnew(Input);
            OS::get_singleton()->initialize_joypads();

            text_driver = GLOBAL_GET("internationalization/rendering/text_driver");

            uint32_t count = TextServerManager::get_singleton()->get_interface_count();
            for (int i = 0; i < count; i++) {
                if (TextServerManager::get_singleton()->get_interface(i)->get_name() == text_driver) {
                    text_driver_idx = i;
                    break;
                }
            }

            if (text_driver_idx < 0) {
                /* If not selected, use one with the most features available. */
                int max_features = 0;
                for (int i = 0; i < TextServerManager::get_singleton()->get_interface_count(); i++) {
                    uint32_t features = TextServerManager::get_singleton()->get_interface(i)->get_features();
                    int feature_number = 0;
                    while (features) {
                        feature_number += features & 1;
                        features >>= 1;
                    }
                    if (feature_number >= max_features) {
                        max_features = feature_number;
                        text_driver_idx = i;
                    }
                }
            }

            if (text_driver_idx >= 0) {
                Ref<TextServer> ts = TextServerManager::get_singleton()->get_interface(text_driver_idx);
                TextServerManager::get_singleton()->set_primary_interface(ts);
                if (ts->has_feature(TextServer::FEATURE_USE_SUPPORT_DATA)) {
                    ts->load_support_data("res://" + ts->get_support_data_filename());
                }
            }
            else {
                assert_invariant(false);
            }

            auto navigation_server_3d = memnew(NavigationServer3DDummy);

            navigation_server_3d->init();
    }
};
static void register_core_types()
{
    StringName::setup();
    Variant::register_types();
    CoreStringNames::create();
    GDREGISTER_CLASS(Object);
    GDREGISTER_CLASS(RefCounted);
    GDREGISTER_CLASS(WeakRef);
    GDREGISTER_CLASS(Resource);
  
    GDREGISTER_VIRTUAL_CLASS(MissingResource);
    GDREGISTER_CLASS(Image);

    GDREGISTER_CLASS(Shortcut);
    GDREGISTER_ABSTRACT_CLASS(InputEvent);
    GDREGISTER_ABSTRACT_CLASS(InputEventWithModifiers);
    GDREGISTER_ABSTRACT_CLASS(InputEventFromWindow);
    GDREGISTER_CLASS(InputEventKey);
    GDREGISTER_CLASS(InputEventShortcut);
    GDREGISTER_ABSTRACT_CLASS(InputEventMouse);
    GDREGISTER_CLASS(InputEventMouseButton);
    GDREGISTER_CLASS(InputEventMouseMotion);
    GDREGISTER_CLASS(InputEventJoypadButton);
    GDREGISTER_CLASS(InputEventJoypadMotion);
    GDREGISTER_CLASS(InputEventScreenDrag);
    GDREGISTER_CLASS(InputEventScreenTouch);
    GDREGISTER_CLASS(InputEventAction);
    GDREGISTER_ABSTRACT_CLASS(InputEventGesture);
    GDREGISTER_CLASS(InputEventMagnifyGesture);
    GDREGISTER_CLASS(InputEventPanGesture);
    GDREGISTER_CLASS(InputEventMIDI);

    GDREGISTER_CLASS(Gradient);
    GDREGISTER_CLASS(GradientTexture1D);
    GDREGISTER_CLASS(GradientTexture2D);

    GDREGISTER_CLASS(Curve);
    GDREGISTER_CLASS(CurveTexture);
    GDREGISTER_CLASS(ParticleProcessMaterial);

    static OS_Windows os(nullptr);
    memnew(WorkerThreadPool);
    memnew(ResourceUID);
  
    static Ref<TranslationLoaderPO> resource_format_po;
    static Ref<ResourceFormatLoaderBinary> resource_loader_binary;
    static Ref<ResourceFormatLoaderImage> resource_format_image;
    static Ref<ResourceFormatImporter> resource_format_importer;
    ResourceLoader::initialize();

    resource_format_po.instantiate();
    ResourceLoader::add_resource_format_loader(resource_format_po);

    resource_loader_binary.instantiate();
    ResourceLoader::add_resource_format_loader(resource_loader_binary);

    resource_format_importer.instantiate();
    ResourceLoader::add_resource_format_loader(resource_format_importer);

    resource_format_image.instantiate();
    ResourceLoader::add_resource_format_loader(resource_format_image);
}
static Ref<ResourceFormatLoaderText> resource_loader_text;

static bool has_server_feature_callback(const String& p_feature) {
    if (RenderingServer::get_singleton()) {
        if (RenderingServer::get_singleton()->has_os_feature(p_feature)) {
            return true;
        }
    }

    return false;
}
static void register_scene_types()
{
    SceneStringNames::create();
    OS::get_singleton()->yield();
    Node::init_node_hrcr();

    

    static Ref<ResourceFormatLoaderCompressedTexture2D> resource_loader_stream_texture;
    static Ref<ResourceFormatLoaderCompressedTextureLayered> resource_loader_texture_layered;
    static Ref<ResourceFormatLoaderCompressedTexture3D> resource_loader_texture_3d;
    static Ref<ResourceFormatLoaderShader> resource_loader_shader;
    resource_loader_stream_texture.instantiate();
    ResourceLoader::add_resource_format_loader(resource_loader_stream_texture, true);
    resource_loader_texture_layered.instantiate();
    ResourceLoader::add_resource_format_loader(resource_loader_texture_layered, true);
    resource_loader_texture_3d.instantiate();
    ResourceLoader::add_resource_format_loader(resource_loader_texture_3d, true);
    resource_loader_text.instantiate();
    ResourceLoader::add_resource_format_loader(resource_loader_text, true);
    resource_loader_shader.instantiate();
    ResourceLoader::add_resource_format_loader(resource_loader_shader, true);
    memnew(ShaderTypes);
    auto rendering_device = memnew(RenderingDevice);
    static RenderingContextDriverNULL renderingContext;
    rendering_device->initialize(&renderingContext);
    memnew(MessageQueue);
    auto rendering_server = memnew(RenderingServerDefault);

    RendererCompositorRD::make_current();
    rendering_server->init();
    rendering_server->set_render_loop_enabled(false);
    OS::get_singleton()->set_has_server_feature_callback(has_server_feature_callback);
    BaseMaterial3D::init_shaders();
    ParticleProcessMaterial::init_shaders();
    GDREGISTER_CLASS(Object);
    GDREGISTER_VIRTUAL_CLASS(Resource);
    GDREGISTER_CLASS(Node3D);
    GDREGISTER_CLASS(WorldEnvironment);
    GDREGISTER_CLASS(Environment);
    GDREGISTER_ABSTRACT_CLASS(SceneState);
    GDREGISTER_CLASS(PackedScene);
    GDREGISTER_CLASS(Camera3D);
    GDREGISTER_CLASS(VisualInstance3D);
    GDREGISTER_CLASS(LightmapGI);
    GDREGISTER_CLASS(LightmapGIData);
    GDREGISTER_CLASS(ReflectionProbe);
    GDREGISTER_CLASS(MeshInstance3D);
    GDREGISTER_CLASS(OmniLight3D);
    GDREGISTER_CLASS(SpotLight3D);
    GDREGISTER_CLASS(CanvasLayer);

    GDREGISTER_VIRTUAL_CLASS(Mesh);
    GDREGISTER_CLASS(ArrayMesh);
    GDREGISTER_CLASS(QuadMesh);

    GDREGISTER_VIRTUAL_CLASS(Material);
    GDREGISTER_CLASS(ProceduralSkyMaterial);
    GDREGISTER_CLASS(ShaderMaterial);

    GDREGISTER_CLASS(GPUParticles3D);
    GDREGISTER_CLASS(Sky);

    GDREGISTER_CLASS(BoxShape3D);
    GDREGISTER_CLASS(ConcavePolygonShape3D);
    GDREGISTER_CLASS(CapsuleShape3D);
    GDREGISTER_CLASS(StandardMaterial3D);
    GDREGISTER_CLASS(StaticBody3D);
    GDREGISTER_CLASS(CollisionShape3D);
    GDREGISTER_CLASS(CharacterBody3D);

    GDREGISTER_CLASS(Shader);

    GDREGISTER_CLASS(DirectionalLight3D);
    
    GDREGISTER_ABSTRACT_CLASS(Viewport);
    GDREGISTER_CLASS(SubViewport);
    GDREGISTER_CLASS(ViewportTexture);

    GDREGISTER_CLASS(VideoStreamPlayer);
    GDREGISTER_VIRTUAL_CLASS(VideoStreamPlayback);
    GDREGISTER_VIRTUAL_CLASS(VideoStream);
}
static void initialize_physics() 
{
    memnew(PhysicsServer3DManager);
    memnew(PhysicsServer2DManager);
#ifndef _3D_DISABLED
    /// 3D Physics Server
    auto physics_server_3d = PhysicsServer3DManager::get_singleton()->new_server(
        GLOBAL_GET(PhysicsServer3DManager::setting_property_name));
    if (!physics_server_3d) {
        // Physics server not found, Use the default physics
        physics_server_3d = PhysicsServer3DManager::get_singleton()->new_default_server();
    }

    if (!physics_server_3d) {
        WARN_PRINT(vformat("Falling back to dummy PhysicsServer3D; 3D physics functionality will be disabled. If this is intended, set the %s project setting to Dummy.", PhysicsServer3DManager::setting_property_name));
        physics_server_3d = memnew(PhysicsServer3DDummy);
    }
    // Should be impossible, but make sure it's not null.
    ERR_FAIL_NULL_MSG(physics_server_3d, "Failed to initialize PhysicsServer3D.");
    physics_server_3d->init();
#endif // _3D_DISABLED

    // 2D Physics server
    auto physics_server_2d = PhysicsServer2DManager::get_singleton()->new_server(
        GLOBAL_GET(PhysicsServer2DManager::get_singleton()->setting_property_name));
    if (!physics_server_2d) {
        // Physics server not found, Use the default physics
        physics_server_2d = PhysicsServer2DManager::get_singleton()->new_default_server();
    }
    if (!physics_server_2d) {
        WARN_PRINT(vformat("Falling back to dummy PhysicsServer2D; 2D physics functionality will be disabled. If this is intended, set the %s project setting to Dummy.", PhysicsServer2DManager::setting_property_name));
        physics_server_2d = memnew(PhysicsServer2DDummy);
    }
    // Should be impossible, but make sure it's not null.
    ERR_FAIL_NULL_MSG(physics_server_2d, "Failed to initialize PhysicsServer2D.");
    physics_server_2d->init();
}

std::string convert_stringname_to_ascii(const String& name) {

    PackedByteArray ascii_bytes = name.to_ascii_buffer();

    std::string std_str;
    std_str.assign((const char*)ascii_bytes.ptr(), ascii_bytes.size());
    return std_str;
}

void visitNode(Node* scene, Ogre::SceneNode* sceneNode, GodotContext& context);
Node* findNode(Node* godotNode, const char* name);

void godotInit()
{
    if (globals == nullptr)
    {
        memnew(Engine);

        register_core_types();
        globals = memnew(ProjectSettings);

        memnew(PackedData);
        register_scene_types();
        initialize_physics();
        initialize_modules(MODULE_INITIALIZATION_LEVEL_SERVERS);
        Main();

       
    }
}

void loadGodotProject(const String& projectDir, GodotContext& context)
{
    godotInit();
    Error ret = globals->setup(projectDir, String(), false, false);
    if ( ret == OK)
    {
        String game_path = GLOBAL_GET("application/run/main_scene");
        //game_path = "res://Scenes/Environment/space_craft_hangar.tscn";
        //game_path = "res://Models/Outside/Tree.tscn";
        Ref<PackedScene> scenedata = ResourceLoader::load(game_path);

        Node* scene = scenedata->instantiate();
        std::string sceneNodeName = convert_stringname_to_ascii(scene->get_name());
        Ogre::SceneNode* root = context.sceneManager->getRoot()->createChildSceneNode(sceneNodeName);

        Node* node = findNode(scene, "SpaceCraftHangar");
        visitNode(node, root, context);
    }
    else
    {
        assert_invariant(false);
    }
}

struct GodotVertex
{
    Ogre::Vector3 vertex;
    Ogre::Vector3 normal;
    Ogre::Vector4 tangent;
    Ogre::Vector2 uv;
};


void updateMaterial(Ref<StandardMaterial3D> standard_mat, Ogre::Material* ogreMat)
{
    PbrMaterialConstanceBuffer& matInfo = ogreMat->getPbrMatInfo();
    Ogre::TextureProperty texProperty;
    String texName;
    std::string ogreTexName;
    Ref<Texture2D> albedo_texture =
        standard_mat->get_texture(StandardMaterial3D::TEXTURE_ALBEDO);
    if (albedo_texture.is_valid())
    {
        texName = albedo_texture->get_path();
        ogreTexName = getShortFilename(convert_stringname_to_ascii(texName));
        texProperty._pbrType = Ogre::TextureTypePbr_Albedo;
        ogreMat->addTexture(ogreTexName, &texProperty);
        matInfo.hasAlbedoMap = 1;
    }


    Ref<Texture2D> normal_texture =
        standard_mat->get_texture(StandardMaterial3D::TEXTURE_NORMAL);
    if (normal_texture.is_valid())
    {
        texName = normal_texture->get_path();
        ogreTexName = getShortFilename(convert_stringname_to_ascii(texName));
        texProperty._pbrType = Ogre::TextureTypePbr_NormalMap;
        ogreMat->addTexture(ogreTexName, &texProperty);
        matInfo.hasNormalMap = 1;
    }


    Ref<Texture2D> roughness_texture =
        standard_mat->get_texture(StandardMaterial3D::TEXTURE_ROUGHNESS);
    if (normal_texture.is_valid())
    {
        texName = roughness_texture->get_path();
        ogreTexName = getShortFilename(convert_stringname_to_ascii(texName));
        texProperty._pbrType = Ogre::TextureTypePbr_Roughness;
        ogreMat->addTexture(ogreTexName, &texProperty);
        matInfo.hasRoughNessMap = 1;
    }
}

void updateMaterial(Ref<ShaderMaterial> shader_mat, Ogre::Material* ogreMat)
{
    PbrMaterialConstanceBuffer& matInfo = ogreMat->getPbrMatInfo();
    Ogre::TextureProperty texProperty;
    String texName;
    std::string ogreTexName;
    Variant albedo_texture_variant = shader_mat->get_shader_parameter("albedo_tex");
    if (albedo_texture_variant.get_type() == Variant::OBJECT)
    {
        Ref<Texture2D> albedo_texture = albedo_texture_variant;
        texName = albedo_texture->get_path();
        ogreTexName = getShortFilename(convert_stringname_to_ascii(texName));
        texProperty._pbrType = Ogre::TextureTypePbr_Albedo;
        ogreMat->addTexture(ogreTexName, &texProperty);
        matInfo.hasAlbedoMap = 1;
    }

    Variant normal_texture_variant = shader_mat->get_shader_parameter("normal_tex");
    if (normal_texture_variant.get_type() == Variant::OBJECT) 
    {
        Ref<Texture2D> normal_texture = normal_texture_variant;
        texName = normal_texture->get_path();
        ogreTexName = getShortFilename(convert_stringname_to_ascii(texName));
        texProperty._pbrType = Ogre::TextureTypePbr_NormalMap;
        ogreMat->addTexture(ogreTexName, &texProperty);
        matInfo.hasNormalMap = 1;
    }

    Variant roughness_scale_variant = shader_mat->get_shader_parameter("roughness_scale");
    if (roughness_scale_variant.get_type() == Variant::FLOAT)
    {
        float roughness = roughness_scale_variant;
        matInfo.metallicRoughnessValues[1] *= roughness;
    }

    Variant color_variant = shader_mat->get_shader_parameter("paint_color");
    if (color_variant.get_type() == Variant::COLOR)
    {
        Color v = color_variant;
        matInfo.baseColorFactor[0] = v.r;
        matInfo.baseColorFactor[1] = v.g;
        matInfo.baseColorFactor[2] = v.b;
        matInfo.baseColorFactor[3] = v.a;
    }

}

Node* findNode(Node* godotNode, const char* name)
{
    StringName sName = godotNode->get_name();
    std::string aa = convert_stringname_to_ascii(sName);
    if (aa == name)
    {
        return godotNode;
    }

    int count = godotNode->get_child_count();
    for (int i = 0; i < count; i++)
    {
        Node* node = findNode(godotNode->get_child(i), name);
        if (node)
        {
            return node;
        }
    }

    return nullptr;
}

void visitNode(Node* godotNode, Ogre::SceneNode* sceneNode, GodotContext& context)
{
    auto name = sceneNode->getName();
    int count = godotNode->get_child_count();

    const String& className = godotNode->get_class();
    StringName sName = godotNode->get_name();
    std::string aa = convert_stringname_to_ascii(sName);

    if (className == "MeshInstance3D")
    {
        static int xx = 0;
        printf("MeshInstance3D:[%d]%s\n", ++xx, aa.c_str());
        if (aa == "Ship_bumper")
        {
            int kk = 0;
        }
        MeshInstance3D* meshInstance3d = Object::cast_to<MeshInstance3D>(godotNode);
        
        Ref<Mesh> mesh = meshInstance3d->get_mesh();

        if (mesh.is_valid())
        {
            const String& meshName = mesh->get_name();

            std::string ogreMeshName = convert_stringname_to_ascii(meshName);

            if (!Ogre::MeshManager::getSingleton().hasMesh(ogreMeshName))
            {
                std::shared_ptr<Ogre::Mesh>ogreMesh = std::make_shared<Ogre::Mesh>(ogreMeshName);

                Ogre::MeshManager::getSingleton().addMesh(ogreMeshName, ogreMesh);
                int surfaceCount = mesh->get_surface_count();

                for (int i = 0; i < surfaceCount; i++)
                {
                    Ogre::SubMesh* subMesh = ogreMesh->addSubMesh(false, false);
                    Array surface_data = mesh->surface_get_arrays(i);
                    int arraySize = surface_data.size();

                    PackedVector2Array uv_coords = surface_data[Mesh::ARRAY_TEX_UV];
                    PackedVector3Array vertices = surface_data[Mesh::ARRAY_VERTEX];
                    PackedVector3Array normals = surface_data[Mesh::ARRAY_NORMAL];
                    PackedVector3Array tangents = surface_data[Mesh::ARRAY_TANGENT];
                    Variant indices_variant   = surface_data[Mesh::ARRAY_INDEX];

                    if (indices_variant.get_type() != Variant::Type::PACKED_INT32_ARRAY)
                    {
                        int kk = 0;
                    }


                    PackedInt32Array indices = indices_variant;
                    
                    uint32_t uv_size = uv_coords.size();
                    uint32_t vertexCount = vertices.size();
                    uint32_t normalCount = normals.size();



                    VertexData* vertexData = subMesh->getVertexData();
                    IndexData* indexData = subMesh->getIndexData();

                    std::vector<GodotVertex> vertexList(vertexCount);

                    for (uint32_t j = 0; j < vertexCount; j++)
                    {
                        vertexList[j].vertex.x = vertices[j].x;
                        vertexList[j].vertex.y = vertices[j].y;
                        vertexList[j].vertex.z = vertices[j].z;

                        if (!normals.is_empty())
                        {
                            vertexList[j].normal.x = normals[j].x;
                            vertexList[j].normal.y = normals[j].y;
                            vertexList[j].normal.z = normals[j].z;
                        }
                        

                        if (!uv_coords.is_empty())
                        {
                            vertexList[j].uv.x = uv_coords[j].x;
                            vertexList[j].uv.y = uv_coords[j].y;
                        }
                        
                    }
                    vertexData->addBindBuffer(sizeof(GodotVertex), vertexCount);
                    vertexData->writeBindBufferData(0, (const char*)vertexList.data(), sizeof(GodotVertex) * vertexCount);
                    vertexData->addElement(0, 0, 0, Ogre::VET_FLOAT3, Ogre::VES_POSITION);
                    vertexData->addElement(0, 0, 12, Ogre::VET_FLOAT3, Ogre::VES_NORMAL);
                    vertexData->addElement(0, 0, 24, Ogre::VET_FLOAT4, Ogre::VES_TANGENT);
                    vertexData->addElement(0, 0, 40, Ogre::VET_FLOAT2, Ogre::VES_TEXTURE_COORDINATES);
                    indexData->createBuffer(4, indices.size());
                    indexData->writeData((const char*)indices.ptr(), 4 * indices.size());

                    subMesh->addIndexs(indices.size(), 0, 0);
                    //
                    Ref<Material> mat = mesh->surface_get_material(i);

                    if (mat.is_null())
                    {
                        std::shared_ptr<Ogre::Material> ogreMat = Ogre::MaterialManager::getSingleton().getByName("BaseWhite");
                        subMesh->setMaterial(ogreMat);
                        continue;
                    }
                    
                    Ref<StandardMaterial3D> standard_mat = Object::cast_to<StandardMaterial3D>(mat.ptr());
                    Ref<ShaderMaterial> shader_mat = Object::cast_to<ShaderMaterial>(mat.ptr());
                    String matName = mat->get_path();
                    
                    std::string ogreMatName = convert_stringname_to_ascii(matName);

                    if (!Ogre::MaterialManager::getSingleton().hasMaterial(ogreMatName))
                    {
                        std::shared_ptr<Ogre::Material> ogreMat = 
                            Ogre::MaterialManager::getSingleton().create(ogreMatName, true);

                        ShaderInfo& shaderInfo = ogreMat->getShaderInfo();
                        shaderInfo.shaderName = "pbr";
                        shaderInfo.shaderMacros.push_back(std::pair<std::string, std::string>("PBR", "1"));
                        shaderInfo.shaderMacros.push_back(std::pair<std::string, std::string>("USE_IBL", "1"));
                        
                        if (standard_mat.is_valid())
                        {
                            updateMaterial(standard_mat, ogreMat.get());
                        }

                        if (shader_mat.is_valid())
                        {
                            updateMaterial(shader_mat, ogreMat.get());
                        }
                        if (true)
                        {
                            Ogre::TextureProperty texProperty;
                            texProperty._pbrType = Ogre::TextureTypePbr_BRDF_LUT;
                            ogreMat->addTexture(context.brdfTexName, &texProperty);

                            texProperty._pbrType = Ogre::TextureTypePbr_IBL_Diffuse;
                            ogreMat->addTexture(context.irradianceTexName, &texProperty);

                            texProperty._pbrType = Ogre::TextureTypePbr_IBL_Specular;
                            ogreMat->addTexture(context.prefilteredTexName, &texProperty);

                            
                        }
                        
                    }

                    std::shared_ptr<Ogre::Material> ogreMat = Ogre::MaterialManager::getSingleton().getByName(ogreMatName);
                    subMesh->setMaterial(ogreMat);
                }
            }
            
            std::shared_ptr<Ogre::Mesh> ogreMesh = Ogre::MeshManager::getSingleton().getByName(ogreMeshName);

            const StringName& instanceName = meshInstance3d->get_name();

            std::string entityName = convert_stringname_to_ascii(instanceName);

            Ogre::Entity* entity = new Ogre::Entity(entityName, ogreMesh.get());

            sceneNode->attachObject(entity);
        }
    }
    
    Node3D* node3d = Object::cast_to<Node3D>(godotNode);
    if (node3d)
    {
        Vector3 local_position = node3d->get_position();
        Vector3 local_scale = node3d->get_scale();
        Basis local_basis = node3d->get_transform().basis;
        Quaternion local_quat = local_basis.get_rotation_quaternion();

        sceneNode->setPosition(Ogre::Vector3(local_position.x, local_position.y, local_position.z));
        sceneNode->setScale(Ogre::Vector3(local_scale.x, local_scale.y, local_scale.z));
        Ogre::Quaternion ogreQuat;
        ogreQuat.x = local_quat.x;
        ogreQuat.y = local_quat.y;
        ogreQuat.z = local_quat.z;
        ogreQuat.w = local_quat.w;
        sceneNode->setOrientation(ogreQuat);
    }
    
    
    for (int i = 0; i < count; i++)
    {
        Node* subNode = godotNode->get_child(i);
        const StringName& name = subNode->get_name();
        std::string sceneNodeName = convert_stringname_to_ascii(name);
        printf("node name:%s\n", sceneNodeName.c_str());
        Ogre::SceneNode* subSceneNode = sceneNode->createChildSceneNode(sceneNodeName);
        visitNode(subNode, subSceneNode, context);
    }
}


void godotProjectSetting()
{
    ProjectManager* pmanager = memnew(ProjectManager());
    ProgressDialog* progress_dialog = memnew(ProgressDialog);
    pmanager->add_child(progress_dialog);
}