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
#include <scene/resources/packed_scene.h>
#include <scene/resources/resource_format_text.h>
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

static void register_scene_types()
{
    SceneStringNames::create();
    OS::get_singleton()->yield();
    Node::init_node_hrcr();

    static Ref<ResourceFormatLoaderText> resource_loader_text;

    /*static Ref<ResourceFormatLoaderCompressedTexture2D> resource_loader_stream_texture;
    static Ref<ResourceFormatLoaderCompressedTextureLayered> resource_loader_texture_layered;
    static Ref<ResourceFormatLoaderCompressedTexture3D> resource_loader_texture_3d;*/

    resource_loader_text.instantiate();
    ResourceLoader::add_resource_format_loader(resource_loader_text, true);
}

void loadGodotProject(const String& projectDir)
{
    if (globals == nullptr)
    {
        register_core_types();
        register_scene_types();
        globals = memnew(ProjectSettings);
        memnew(PackedData);
        Main();

        
    }

    Error ret = globals->setup(projectDir, String(), false, false);
    if ( ret == OK)
    {
        String game_path = GLOBAL_GET("application/run/main_scene");

        Ref<PackedScene> scenedata = ResourceLoader::load(game_path);

        int kk = 0;
    }
    else
    {
        assert_invariant(false);
    }
}