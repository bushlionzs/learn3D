#include "rendering_context_driver_null.h"
#include "rendering_device_driver_null.h"

RenderingContextDriverNULL::RenderingContextDriverNULL()
{

}

RenderingContextDriverNULL::~RenderingContextDriverNULL()
{

}

Error RenderingContextDriverNULL::initialize()
{
    return OK;
}

const RenderingContextDriver::Device& RenderingContextDriverNULL::device_get(uint32_t p_device_index) const
{
    return mDevice;
}

uint32_t RenderingContextDriverNULL::device_get_count() const
{
    return 1;
}

bool RenderingContextDriverNULL::device_supports_present(uint32_t p_device_index, SurfaceID p_surface) const
{
    return true;
}
RenderingDeviceDriver* RenderingContextDriverNULL::driver_create()
{
    return new RenderingDeviceDriverNULL(this);
}

void RenderingContextDriverNULL::driver_free(RenderingDeviceDriver* p_driver)
{
    delete p_driver;
}

RenderingContextDriver::SurfaceID RenderingContextDriverNULL::surface_create(const void* p_platform_data)
{
    return RenderingContextDriver::SurfaceID();
}

void RenderingContextDriverNULL::surface_set_size(
    RenderingContextDriver::SurfaceID p_surface, uint32_t p_width, uint32_t p_height)
{

}

void RenderingContextDriverNULL::surface_set_vsync_mode(RenderingContextDriver::SurfaceID p_surface, DisplayServer::VSyncMode p_vsync_mode)
{

}

DisplayServer::VSyncMode RenderingContextDriverNULL::surface_get_vsync_mode(RenderingContextDriver::SurfaceID p_surface) const
{
    return DisplayServer::VSYNC_DISABLED;
}

uint32_t RenderingContextDriverNULL::surface_get_width(RenderingContextDriver::SurfaceID p_surface) const
{
    return 100;
}

uint32_t RenderingContextDriverNULL::surface_get_height(RenderingContextDriver::SurfaceID p_surface) const
{
    return 100;
}
void RenderingContextDriverNULL::surface_set_needs_resize(RenderingContextDriver::SurfaceID p_surface, bool p_needs_resize)
{

}

bool RenderingContextDriverNULL::surface_get_needs_resize(RenderingContextDriver::SurfaceID p_surface) const
{
    return false;
}

void RenderingContextDriverNULL::surface_destroy(SurfaceID p_surface)
{

}

bool RenderingContextDriverNULL::is_debug_utils_enabled() const
{
    return false;
}