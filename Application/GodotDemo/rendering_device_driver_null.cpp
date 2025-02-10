#include "rendering_device_driver_null.h"

Error RenderingDeviceDriverNULL::initialize(uint32_t p_device_index, uint32_t p_frame_count)
{
	return OK;
}

RenderingDeviceDriver::BufferID RenderingDeviceDriverNULL::buffer_create(
	uint64_t p_size, BitField<BufferUsageBits> p_usage, MemoryAllocationType p_allocation_type)
{
	return RenderingDeviceDriver::BufferID();
}

bool RenderingDeviceDriverNULL::buffer_set_texel_format(BufferID p_buffer, DataFormat p_format)
{
	return true;
}

void RenderingDeviceDriverNULL::buffer_free(BufferID p_buffer)
{

}

uint64_t RenderingDeviceDriverNULL::buffer_get_allocation_size(BufferID p_buffer)
{
	return 0;
}

uint8_t* RenderingDeviceDriverNULL::buffer_map(BufferID p_buffer)
{
	return nullptr;
}

void RenderingDeviceDriverNULL::buffer_unmap(BufferID p_buffer)
{

}

RenderingDeviceDriver::TextureID RenderingDeviceDriverNULL::texture_create(
	const TextureFormat& p_format, const TextureView& p_view)
{
	return RenderingDeviceDriver::TextureID();
}

RenderingDeviceDriver::TextureID RenderingDeviceDriverNULL::texture_create_from_extension(
	uint64_t p_native_texture, TextureType p_type,
	DataFormat p_format, uint32_t p_array_layers, bool p_depth_stencil)
{
	return RenderingDeviceDriver::TextureID();
}

RenderingDeviceDriver::TextureID RenderingDeviceDriverNULL::texture_create_shared(TextureID p_original_texture, const TextureView& p_view)
{
	return RenderingDeviceDriver::TextureID();
}

RenderingDeviceDriver::TextureID RenderingDeviceDriverNULL::texture_create_shared_from_slice
(TextureID p_original_texture, const TextureView& p_view,
	TextureSliceType p_slice_type, uint32_t p_layer,
	uint32_t p_layers, uint32_t p_mipmap, uint32_t p_mipmaps)
{
	return RenderingDeviceDriver::TextureID();
}

void RenderingDeviceDriverNULL::texture_free(TextureID p_texture)
{

}

uint64_t RenderingDeviceDriverNULL::texture_get_allocation_size(TextureID p_texture)
{
	return 0;
}

void RenderingDeviceDriverNULL::texture_get_copyable_layout(TextureID p_texture,
	const TextureSubresource& p_subresource, TextureCopyableLayout* r_layout)
{

}

uint8_t* RenderingDeviceDriverNULL::texture_map(RenderingDeviceDriver::TextureID p_texture, const RenderingDeviceDriver::TextureSubresource& p_subresource)
{
	return nullptr;
}

void RenderingDeviceDriverNULL::texture_unmap(TextureID p_texture)
{

}

BitField<RenderingDeviceDriver::TextureUsageBits> RenderingDeviceDriverNULL::texture_get_usages_supported_by_format(
	DataFormat p_format, bool p_cpu_readable)
{
	return BitField<RenderingDeviceDriver::TextureUsageBits>(0xffffffff);
}
bool RenderingDeviceDriverNULL::texture_can_make_shared_with_format(TextureID p_texture, DataFormat p_format, bool& r_raw_reinterpretation)
{
	return true;
}

RenderingDeviceDriver::SamplerID RenderingDeviceDriverNULL::sampler_create(const RenderingDeviceDriver::SamplerState& p_state)
{
	return RenderingDeviceDriver::SamplerID();
}

void RenderingDeviceDriverNULL::sampler_free(SamplerID p_sampler)
{

}

bool RenderingDeviceDriverNULL::sampler_is_format_supported_for_filter(DataFormat p_format, SamplerFilter p_filter)
{
	return true;
}

RenderingDeviceDriver::VertexFormatID RenderingDeviceDriverNULL::vertex_format_create(
	VectorView<VertexAttribute> p_vertex_attribs)
{
	return RenderingDeviceDriver::VertexFormatID();
}

void RenderingDeviceDriverNULL::vertex_format_free(VertexFormatID p_vertex_format)
{

}

void RenderingDeviceDriverNULL::command_pipeline_barrier(
	CommandBufferID p_cmd_buffer,
	BitField<PipelineStageBits> p_src_stages,
	BitField<PipelineStageBits> p_dst_stages,
	VectorView<MemoryBarrier> p_memory_barriers,
	VectorView<BufferBarrier> p_buffer_barriers,
	VectorView<TextureBarrier> p_texture_barriers)
{

}

RenderingDeviceDriver::FenceID RenderingDeviceDriverNULL::fence_create()
{
	return RenderingDeviceDriver::FenceID();
}

Error RenderingDeviceDriverNULL::fence_wait(FenceID p_fence)
{
	return OK;
}

void RenderingDeviceDriverNULL::fence_free(FenceID p_fence)
{

}

RenderingDeviceDriver::SemaphoreID RenderingDeviceDriverNULL::semaphore_create()
{
	return RenderingDeviceDriver::SemaphoreID();
}

void RenderingDeviceDriverNULL::semaphore_free(SemaphoreID p_semaphore)
{

}

RenderingDeviceDriver::CommandQueueFamilyID RenderingDeviceDriverNULL::command_queue_family_get(
	BitField<CommandQueueFamilyBits> p_cmd_queue_family_bits, RenderingContextDriver::SurfaceID p_surface)
{
	return RenderingDeviceDriver::CommandQueueFamilyID();
}

RenderingDeviceDriver::CommandQueueID RenderingDeviceDriverNULL::command_queue_create(
	CommandQueueFamilyID p_cmd_queue_family, bool p_identify_as_main_queue)
{
	return RenderingDeviceDriver::CommandQueueID();
}

Error RenderingDeviceDriverNULL::command_queue_execute_and_present(
	CommandQueueID p_cmd_queue, VectorView<SemaphoreID> p_wait_semaphores,
	VectorView<CommandBufferID> p_cmd_buffers, VectorView<SemaphoreID> p_cmd_semaphores,
	FenceID p_cmd_fence, VectorView<SwapChainID> p_swap_chains)
{
	return OK;
}

void RenderingDeviceDriverNULL::command_queue_free(CommandQueueID p_cmd_queue)
{

}

RenderingDeviceDriver::CommandPoolID RenderingDeviceDriverNULL::command_pool_create(
	CommandQueueFamilyID p_cmd_queue_family, CommandBufferType p_cmd_buffer_type)
{
	return RenderingDeviceDriver::CommandPoolID();
}

void RenderingDeviceDriverNULL::command_pool_free(CommandPoolID p_cmd_pool)
{

}

RenderingDeviceDriver::CommandBufferID RenderingDeviceDriverNULL::command_buffer_create(CommandPoolID p_cmd_pool)
{
	return RenderingDeviceDriver::CommandBufferID();
}

bool RenderingDeviceDriverNULL::command_buffer_begin(CommandBufferID p_cmd_buffer)
{
	return true;
}

bool RenderingDeviceDriverNULL::command_buffer_begin_secondary(
	CommandBufferID p_cmd_buffer, RenderPassID p_render_pass, uint32_t p_subpass, FramebufferID p_framebuffer)
{
	return true;
}

void RenderingDeviceDriverNULL::command_buffer_end(CommandBufferID p_cmd_buffer)
{

}

void RenderingDeviceDriverNULL::command_buffer_execute_secondary(
	CommandBufferID p_cmd_buffer, VectorView<CommandBufferID> p_secondary_cmd_buffers)
{

}

RenderingDeviceDriver::SwapChainID RenderingDeviceDriverNULL::swap_chain_create(RenderingContextDriver::SurfaceID p_surface)
{
	return RenderingDeviceDriver::SwapChainID();
}

Error RenderingDeviceDriverNULL::swap_chain_resize(
	CommandQueueID p_cmd_queue, SwapChainID p_swap_chain, uint32_t p_desired_framebuffer_count)
{
	return OK;
}

RenderingDeviceDriver::FramebufferID RenderingDeviceDriverNULL::swap_chain_acquire_framebuffer(
	CommandQueueID p_cmd_queue, SwapChainID p_swap_chain, bool& r_resize_required)
{
	return RenderingDeviceDriver::FramebufferID();
}

RenderingDeviceDriver::RenderPassID RenderingDeviceDriverNULL::swap_chain_get_render_pass(SwapChainID p_swap_chain)
{
	return RenderingDeviceDriver::RenderPassID();
}

RenderingDeviceDriver::DataFormat RenderingDeviceDriverNULL::swap_chain_get_format(SwapChainID p_swap_chain)
{
	return DATA_FORMAT_R8G8B8_UNORM;
}

void RenderingDeviceDriverNULL::swap_chain_free(SwapChainID p_swap_chain)
{

}

RenderingDeviceDriverNULL::FramebufferID RenderingDeviceDriverNULL::framebuffer_create(
	RenderingDeviceDriver::RenderPassID p_render_pass, VectorView<RenderingDeviceDriver::TextureID> p_attachments,
	uint32_t p_width, uint32_t p_height)
{
	return RenderingDeviceDriverNULL::FramebufferID();
}

void RenderingDeviceDriverNULL::framebuffer_free(FramebufferID p_framebuffer)
{

}

String RenderingDeviceDriverNULL::shader_get_binary_cache_key()
{
	return String();
}

Vector<uint8_t> RenderingDeviceDriverNULL::shader_compile_binary_from_spirv(
	VectorView<RenderingDeviceDriver::ShaderStageSPIRVData> p_spirv, const String& p_shader_name)
{
	return Vector<uint8_t>();
}

RenderingDeviceDriver::ShaderID RenderingDeviceDriverNULL::shader_create_from_bytecode(
	const Vector<uint8_t>& p_shader_binary, RenderingDeviceDriver::ShaderDescription& r_shader_desc, String& r_name)
{
	return RenderingDeviceDriver::ShaderID();
}

void RenderingDeviceDriverNULL::shader_free(RenderingDeviceDriver::ShaderID p_shader)
{

}

void RenderingDeviceDriverNULL::shader_destroy_modules(ShaderID p_shader)
{

}

RenderingDeviceDriver::UniformSetID RenderingDeviceDriverNULL::uniform_set_create(
	VectorView<BoundUniform> p_uniforms, ShaderID p_shader, uint32_t p_set_index)
{
	return RenderingDeviceDriver::UniformSetID();
}

void RenderingDeviceDriverNULL::uniform_set_free(UniformSetID p_uniform_set)
{

}

void RenderingDeviceDriverNULL::command_uniform_set_prepare_for_use(
	CommandBufferID p_cmd_buffer, UniformSetID p_uniform_set, ShaderID p_shader, uint32_t p_set_index)
{

}

void RenderingDeviceDriverNULL::command_clear_buffer(CommandBufferID p_cmd_buffer,
	BufferID p_buffer, uint64_t p_offset, uint64_t p_size)
{

}

void RenderingDeviceDriverNULL::command_copy_buffer(
	CommandBufferID p_cmd_buffer, BufferID p_src_buffer, BufferID p_dst_buffer, VectorView<BufferCopyRegion> p_regions)
{

}

void RenderingDeviceDriverNULL::command_copy_texture(CommandBufferID p_cmd_buffer,
	TextureID p_src_texture, TextureLayout p_src_texture_layout, TextureID p_dst_texture,
	TextureLayout p_dst_texture_layout, VectorView<TextureCopyRegion> p_regions)
{

}

void RenderingDeviceDriverNULL::command_resolve_texture(
	CommandBufferID p_cmd_buffer, TextureID p_src_texture,
	TextureLayout p_src_texture_layout, uint32_t p_src_layer, uint32_t p_src_mipmap,
	TextureID p_dst_texture, TextureLayout p_dst_texture_layout, uint32_t p_dst_layer, uint32_t p_dst_mipmap)
{

}

void RenderingDeviceDriverNULL::command_clear_color_texture(
	CommandBufferID p_cmd_buffer, TextureID p_texture,
	TextureLayout p_texture_layout, const Color& p_color,
	const TextureSubresourceRange& p_subresources)
{

}

void RenderingDeviceDriverNULL::command_copy_buffer_to_texture(
	CommandBufferID p_cmd_buffer, BufferID p_src_buffer, TextureID p_dst_texture,
	TextureLayout p_dst_texture_layout, VectorView<BufferTextureCopyRegion> p_regions)
{

}

void RenderingDeviceDriverNULL::command_copy_texture_to_buffer(
	CommandBufferID p_cmd_buffer, TextureID p_src_texture,
	TextureLayout p_src_texture_layout, BufferID p_dst_buffer, VectorView<BufferTextureCopyRegion> p_regions)
{

}

void RenderingDeviceDriverNULL::pipeline_free(PipelineID p_pipeline)
{

}

void RenderingDeviceDriverNULL::command_bind_push_constants(
	CommandBufferID p_cmd_buffer, ShaderID p_shader, uint32_t p_first_index, VectorView<uint32_t> p_data)
{

}

bool RenderingDeviceDriverNULL::pipeline_cache_create(const Vector<uint8_t>& p_data)
{
	return true;
}

void RenderingDeviceDriverNULL::pipeline_cache_free()
{

}

size_t RenderingDeviceDriverNULL::pipeline_cache_query_size()
{
	return 1000;
}

Vector<uint8_t> RenderingDeviceDriverNULL::pipeline_cache_serialize()
{
	return Vector<uint8_t>();
}

RenderingDeviceDriver::RenderPassID RenderingDeviceDriverNULL::render_pass_create(
	VectorView<Attachment> p_attachments, VectorView<Subpass> p_subpasses,
	VectorView<SubpassDependency> p_subpass_dependencies, uint32_t p_view_count)
{
	return RenderingDeviceDriver::RenderPassID();
}

void RenderingDeviceDriverNULL::render_pass_free(RenderPassID p_render_pass)
{

}

void RenderingDeviceDriverNULL::command_begin_render_pass(
	CommandBufferID p_cmd_buffer,
	RenderPassID p_render_pass,
	FramebufferID p_framebuffer,
	CommandBufferType p_cmd_buffer_type,
	const Rect2i& p_rect, VectorView<RenderPassClearValue> p_clear_values)
{

}

void RenderingDeviceDriverNULL::command_end_render_pass(CommandBufferID p_cmd_buffer)
{

}

void RenderingDeviceDriverNULL::command_next_render_subpass(
	CommandBufferID p_cmd_buffer, CommandBufferType p_cmd_buffer_type)
{

}

void RenderingDeviceDriverNULL::command_render_set_viewport(
	CommandBufferID p_cmd_buffer, VectorView<Rect2i> p_viewports)
{

}

void RenderingDeviceDriverNULL::command_render_set_scissor(
	CommandBufferID p_cmd_buffer, VectorView<Rect2i> p_scissors)
{

}

void RenderingDeviceDriverNULL::command_render_clear_attachments(
	CommandBufferID p_cmd_buffer, VectorView<AttachmentClear> p_attachment_clears, VectorView<Rect2i> p_rects)
{

}

void RenderingDeviceDriverNULL::command_bind_render_pipeline(CommandBufferID p_cmd_buffer, PipelineID p_pipeline)
{

}

void RenderingDeviceDriverNULL::command_bind_render_uniform_set(
	CommandBufferID p_cmd_buffer, UniformSetID p_uniform_set, ShaderID p_shader, uint32_t p_set_index)
{

}

void RenderingDeviceDriverNULL::command_render_draw(
	CommandBufferID p_cmd_buffer,
	uint32_t p_vertex_count,
	uint32_t p_instance_count,
	uint32_t p_base_vertex,
	uint32_t p_first_instance)
{

}

void RenderingDeviceDriverNULL::command_render_draw_indexed(
	CommandBufferID p_cmd_buffer,
	uint32_t p_index_count,
	uint32_t p_instance_count,
	uint32_t p_first_index, int32_t p_vertex_offset, uint32_t p_first_instance)
{

}

void RenderingDeviceDriverNULL::command_render_draw_indexed_indirect(
	CommandBufferID p_cmd_buffer, BufferID p_indirect_buffer,
	uint64_t p_offset, uint32_t p_draw_count, uint32_t p_stride)
{

}

void RenderingDeviceDriverNULL::command_render_draw_indexed_indirect_count(
	CommandBufferID p_cmd_buffer, BufferID p_indirect_buffer,
	uint64_t p_offset, BufferID p_count_buffer, uint64_t p_count_buffer_offset,
	uint32_t p_max_draw_count, uint32_t p_stride)
{

}

void RenderingDeviceDriverNULL::command_render_draw_indirect(
	CommandBufferID p_cmd_buffer, BufferID p_indirect_buffer,
	uint64_t p_offset, uint32_t p_draw_count, uint32_t p_stride)
{

}

void RenderingDeviceDriverNULL::command_render_draw_indirect_count(
	CommandBufferID p_cmd_buffer, BufferID p_indirect_buffer,
	uint64_t p_offset, BufferID p_count_buffer, uint64_t p_count_buffer_offset,
	uint32_t p_max_draw_count, uint32_t p_stride)
{

}

void RenderingDeviceDriverNULL::command_render_bind_vertex_buffers(
	CommandBufferID p_cmd_buffer, uint32_t p_binding_count,
	const BufferID* p_buffers, const uint64_t* p_offsets)
{

}

void RenderingDeviceDriverNULL::command_render_bind_index_buffer(
	CommandBufferID p_cmd_buffer, BufferID p_buffer,
	IndexBufferFormat p_format, uint64_t p_offset)
{

}

void RenderingDeviceDriverNULL::command_render_set_blend_constants(
	CommandBufferID p_cmd_buffer, const Color& p_constants)
{

}

void RenderingDeviceDriverNULL::command_render_set_line_width(CommandBufferID p_cmd_buffer, float p_width)
{

}

RenderingDeviceDriver::PipelineID RenderingDeviceDriverNULL::render_pipeline_create(
	ShaderID p_shader,
	VertexFormatID p_vertex_format,
	RenderPrimitive p_render_primitive,
	PipelineRasterizationState p_rasterization_state,
	PipelineMultisampleState p_multisample_state,
	PipelineDepthStencilState p_depth_stencil_state,
	PipelineColorBlendState p_blend_state,
	VectorView<int32_t> p_color_attachments,
	BitField<PipelineDynamicStateFlags> p_dynamic_state,
	RenderPassID p_render_pass,
	uint32_t p_render_subpass,
	VectorView<PipelineSpecializationConstant> p_specialization_constants)
{
	return RenderingDeviceDriver::PipelineID();
}

void RenderingDeviceDriverNULL::command_bind_compute_pipeline(CommandBufferID p_cmd_buffer, PipelineID p_pipeline)
{

}

void RenderingDeviceDriverNULL::command_bind_compute_uniform_set(
	CommandBufferID p_cmd_buffer, UniformSetID p_uniform_set, ShaderID p_shader, uint32_t p_set_index)
{

}

void RenderingDeviceDriverNULL::command_compute_dispatch(
	CommandBufferID p_cmd_buffer, uint32_t p_x_groups, uint32_t p_y_groups, uint32_t p_z_groups)
{

}

void RenderingDeviceDriverNULL::command_compute_dispatch_indirect(
	CommandBufferID p_cmd_buffer, BufferID p_indirect_buffer, uint64_t p_offset)
{

}

RenderingDeviceDriver::PipelineID RenderingDeviceDriverNULL::compute_pipeline_create(
	ShaderID p_shader, VectorView<PipelineSpecializationConstant> p_specialization_constants)
{
	return RenderingDeviceDriver::PipelineID();
}

RenderingDeviceDriver::QueryPoolID RenderingDeviceDriverNULL::timestamp_query_pool_create(uint32_t p_query_count)
{
	return RenderingDeviceDriver::QueryPoolID();
}

void RenderingDeviceDriverNULL::timestamp_query_pool_free(QueryPoolID p_pool_id)
{

}

void RenderingDeviceDriverNULL::timestamp_query_pool_get_results(
	QueryPoolID p_pool_id, uint32_t p_query_count, uint64_t* r_results)
{

}

uint64_t RenderingDeviceDriverNULL::timestamp_query_result_to_time(uint64_t p_result)
{
	return 0;
}

void RenderingDeviceDriverNULL::command_timestamp_query_pool_reset(
	CommandBufferID p_cmd_buffer, QueryPoolID p_pool_id, uint32_t p_query_count)
{

}

void RenderingDeviceDriverNULL::command_timestamp_write(
	CommandBufferID p_cmd_buffer, QueryPoolID p_pool_id, uint32_t p_index)
{

}

void RenderingDeviceDriverNULL::command_begin_label(
	CommandBufferID p_cmd_buffer, const char* p_label_name, const Color& p_color)
{

}

void RenderingDeviceDriverNULL::command_end_label(CommandBufferID p_cmd_buffer)
{

}

void RenderingDeviceDriverNULL::command_insert_breadcrumb(CommandBufferID p_cmd_buffer, uint32_t p_data)
{

}

void RenderingDeviceDriverNULL::begin_segment(uint32_t p_frame_index, uint32_t p_frames_drawn)
{

}

void RenderingDeviceDriverNULL::end_segment()
{

}

void RenderingDeviceDriverNULL::set_object_name(ObjectType p_type, ID p_driver_id, const String& p_name)
{

}

uint64_t RenderingDeviceDriverNULL::get_resource_native_handle(DriverResource p_type, ID p_driver_id)
{
	return 0;
}

uint64_t RenderingDeviceDriverNULL::get_total_memory_used()
{
	return 0;
}

uint64_t RenderingDeviceDriverNULL::limit_get(Limit p_limit)
{
	return 0;
}

uint64_t RenderingDeviceDriverNULL::api_trait_get(ApiTrait p_trait)
{
	return 0;
}

bool RenderingDeviceDriverNULL::has_feature(Features p_feature)
{
	return true;
}

const RenderingDeviceDriver::MultiviewCapabilities& RenderingDeviceDriverNULL::get_multiview_capabilities()
{
	return mMultiviewCapabilities;
}

String RenderingDeviceDriverNULL::get_api_name()const
{
	return String("Null");
}

String RenderingDeviceDriverNULL::get_api_version()const
{
	return String("1.0");
}

String RenderingDeviceDriverNULL::get_pipeline_cache_uuid()const
{
	return String("xxxx");
}

const RenderingDeviceDriver::Capabilities& RenderingDeviceDriverNULL::get_capabilities() const
{
	return mCapabilities;
}

bool RenderingDeviceDriverNULL::is_composite_alpha_supported(RenderingDeviceDriver::CommandQueueID p_queue) const
{
	return true;
}

RenderingDeviceDriverNULL::RenderingDeviceDriverNULL(RenderingContextDriverNULL* p_context_driver)
{

}

RenderingDeviceDriverNULL::~RenderingDeviceDriverNULL()
{

}