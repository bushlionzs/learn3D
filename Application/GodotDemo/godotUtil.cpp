#include <OgreHeader.h>
#include "godotUtil.h"
#include <core/config/project_settings.h>
#include <core/string/string_name.h>
#include <platform/windows/os_windows.h>
#include <core/os/memory.h>
#include <core/io/file_access_pack.h>
#include <core/io/missing_resource.h>
#include <core/input/shortcut.h>
static ProjectSettings* globals = nullptr;

class Main
{
public:
        Main()
    {
            OS::get_singleton()->initialize();
    }
};
void register_core_types()
{
    StringName::setup();
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
}

void loadGodotProject(const String& projectDir)
{
    if (globals == nullptr)
    {
        register_core_types();
        globals = memnew(ProjectSettings);
        memnew(PackedData);
        Main();

        
    }

    Error ret = globals->setup(projectDir, String(), false, false);
    if ( ret == OK)
    {
        int kk = 0;
    }
    else
    {
        int kk = 0;
    }
}