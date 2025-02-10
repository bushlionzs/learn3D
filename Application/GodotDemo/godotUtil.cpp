#include <OgreHeader.h>
#include "godotUtil.h"
#include <core/config/project_settings.h>
#include <core/string/string_name.h>
#include <platform/windows/os_windows.h>
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
#include <scene/resources/3d/sky_material.h>
#include <scene/main/canvas_layer.h>
#include <scene/resources/3d/box_shape_3d.h>
#include <scene/resources/3d/concave_polygon_shape_3d.h>
#include <scene/resources/3d/capsule_shape_3d.h>

#include <scene/resources/packed_scene.h>
#include <scene/resources/resource_format_text.h>
#include <scene/resources/compressed_texture.h>
#include <scene/resources/3d/primitive_meshes.h>
#include <servers/rendering/rendering_server_default.h>
#include <servers/rendering/renderer_rd/renderer_compositor_rd.h>
#include <servers/rendering/shader_types.h>
#include <servers/physics_server_2d.h>
#include <servers/physics_server_3d_dummy.h>
#include <servers/physics_server_2d_dummy.h>
#include <modules/register_module_types.h>
#include "rendering_context_driver_null.h"
#include <core/config/engine.h>
static ProjectSettings* globals = nullptr;

class Main
{
public:
        Main()
    {
            OS::get_singleton()->initialize();
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
static void register_scene_types()
{
    SceneStringNames::create();
    OS::get_singleton()->yield();
    Node::init_node_hrcr();

    

    static Ref<ResourceFormatLoaderCompressedTexture2D> resource_loader_stream_texture;
    static Ref<ResourceFormatLoaderCompressedTextureLayered> resource_loader_texture_layered;
    static Ref<ResourceFormatLoaderCompressedTexture3D> resource_loader_texture_3d;
    resource_loader_stream_texture.instantiate();
    ResourceLoader::add_resource_format_loader(resource_loader_texture_layered, true);
    resource_loader_texture_layered.instantiate();
    ResourceLoader::add_resource_format_loader(resource_loader_texture_layered, true);
    resource_loader_texture_3d.instantiate();
    ResourceLoader::add_resource_format_loader(resource_loader_texture_3d, true);
    resource_loader_text.instantiate();
    ResourceLoader::add_resource_format_loader(resource_loader_text, true);
    memnew(ShaderTypes);
    auto rendering_device = memnew(RenderingDevice);
    static RenderingContextDriverNULL renderingContext;
    rendering_device->initialize(&renderingContext);

    auto rendering_server = memnew(RenderingServerDefault);

    RendererCompositorRD::make_current();
    rendering_server->init();
    rendering_server->set_render_loop_enabled(false);

    BaseMaterial3D::init_shaders();
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
void visitNode(Node* scene);
void loadGodotProject(const String& projectDir)
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
    
    Error ret = globals->setup(projectDir, String(), false, false);
    if ( ret == OK)
    {
        String aa = "D:\\godotProject\\Abandoned-Spaceship-Godot-Demo\\models\\objects\\barrel.tscn";
        //resource_loader_text->load(aa, aa);
        String game_path = GLOBAL_GET("application/run/main_scene");

        Ref<PackedScene> scenedata = ResourceLoader::load(game_path);

        Node* scene = scenedata->instantiate();
        visitNode(scene);
    }
    else
    {
        assert_invariant(false);
    }
}

void visitNode(Node* scene)
{
    auto name = scene->get_name();
    int count = scene->get_child_count();
    for (int i = 0; i < count; i++)
    {
        Node* subNode = scene->get_child(i);

        auto subName = subNode->get_name();
        int kk = 0;
    }
}