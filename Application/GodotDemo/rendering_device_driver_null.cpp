#include "rendering_device_driver_null.h"
#include <servers/rendering/rendering_device_commons.h>
#include "core/io/marshalls.h"
#include "OgreHeader.h"
#include "OgreCommon.h"
#include "OgreVertexDeclaration.h"
#include "renderSystem.h"
#include <algorithm>

Error RenderingDeviceDriverNULL::initialize(uint32_t p_device_index, uint32_t p_frame_count)
{
	mRenderSystem = Ogre::Root::getSingleton().getRenderSystem();

	mCapabilities.device_family = DEVICE_VULKAN;
	mCapabilities.version_major = 1;
	mCapabilities.version_minor = 4;
	return OK;
}

RenderingDeviceDriver::BufferID RenderingDeviceDriverNULL::buffer_create(
	uint64_t p_size, BitField<BufferUsageBits> p_usage, MemoryAllocationType p_allocation_type)
{
	Ogre::BufferDesc desc{};
	desc.mBindingType = Ogre::BufferObjectBinding_Buffer;
	desc.mMemoryUsage = Ogre::RESOURCE_MEMORY_USAGE_GPU_ONLY;
	if (p_allocation_type == MEMORY_ALLOCATION_TYPE_CPU)
	{
		desc.mMemoryUsage = Ogre::RESOURCE_MEMORY_USAGE_CPU_TO_GPU;
	}
	desc.bufferCreationFlags = 0;
	desc.mSize = p_size;
	std::string tmp = std::to_string(p_size);

	desc.pName = tmp.c_str();
	
	auto bufferHandle = mRenderSystem->createBufferObject(desc);

	return RenderingDeviceDriver::BufferID(bufferHandle.getId());
}

bool RenderingDeviceDriverNULL::buffer_set_texel_format(BufferID p_buffer, DataFormat p_format)
{
	return true;
}

void RenderingDeviceDriverNULL::buffer_free(BufferID p_buffer)
{
	filament::backend::Handle<filament::backend::HwBufferObject> bufferHandle(p_buffer.id);
	mRenderSystem->destroyBufferObject(bufferHandle);
}

uint64_t RenderingDeviceDriverNULL::buffer_get_allocation_size(BufferID p_buffer)
{
	filament::backend::Handle<filament::backend::HwBufferObject> bufferHandle(p_buffer.id);
	Ogre::BufferDesc desc;
	bool b = mRenderSystem->getBufferInfo(bufferHandle, desc);
	assert_invariant(b);
	return desc.mSize;
}

uint8_t* RenderingDeviceDriverNULL::buffer_map(BufferID p_buffer)
{
	filament::backend::Handle<filament::backend::HwBufferObject> bufferHandle(p_buffer.id);
	return mRenderSystem->bufferMap(bufferHandle);
}

void RenderingDeviceDriverNULL::buffer_unmap(BufferID p_buffer)
{
	filament::backend::Handle<filament::backend::HwBufferObject> bufferHandle(p_buffer.id);
	mRenderSystem->bufferUnmap(bufferHandle);
}

Ogre::PixelFormat mapPixelFormat(RenderingDeviceCommons::DataFormat format)
{
	switch (format)
	{
	case RenderingDeviceCommons::DATA_FORMAT_R8G8B8A8_UNORM:
		return Ogre::PixelFormat::PF_A8R8G8B8;
	case RenderingDeviceCommons::DATA_FORMAT_R8G8B8A8_UINT:
		return Ogre::PixelFormat::PF_R8G8B8A8_UINT;
	case RenderingDeviceCommons::DATA_FORMAT_D16_UNORM:
		return Ogre::PixelFormat::PF_DEPTH16;
	case RenderingDeviceCommons::DATA_FORMAT_R8_UNORM:
		return Ogre::PixelFormat::PF_R8;
	case RenderingDeviceCommons::DATA_FORMAT_R8_UINT:
		return Ogre::PixelFormat::PF_R8_UINT;
	case RenderingDeviceCommons::DATA_FORMAT_R32_SFLOAT:
		return Ogre::PixelFormat::PF_FLOAT32_R;
	case RenderingDeviceCommons::DATA_FORMAT_D32_SFLOAT:
		return Ogre::PixelFormat::PF_DEPTH32;
	default:
		assert_invariant(false);
	}

	return Ogre::PixelFormat::PF_A8R8G8B8;
}

Ogre::TextureType mapTextureType(RenderingDeviceCommons::TextureType texType)
{
	switch (texType)
	{
	case RenderingDeviceCommons::TEXTURE_TYPE_2D:
		return Ogre::TEX_TYPE_2D;
	case RenderingDeviceCommons::TEXTURE_TYPE_2D_ARRAY:
		return Ogre::TEX_TYPE_2D_ARRAY;
	case RenderingDeviceCommons::TEXTURE_TYPE_CUBE:
		return Ogre::TEX_TYPE_CUBE_MAP;
	case RenderingDeviceCommons::TEXTURE_TYPE_CUBE_ARRAY:
		return Ogre::TEX_TYPE_CUBE_MAP_ARRAY;
	case RenderingDeviceCommons::TEXTURE_TYPE_3D:
		return Ogre::TEX_TYPE_3D;
	default:
		assert_invariant(false);
	}
	return Ogre::TEX_TYPE_2D;
}
RenderingDeviceDriver::TextureID RenderingDeviceDriverNULL::texture_create(
	const TextureFormat& p_format, const TextureView& p_view)
{
	Ogre::TextureProperty texProperty;
	texProperty._width = p_format.width;
	texProperty._height = p_format.height;
	texProperty._depth = p_format.depth;
	texProperty._face = p_format.array_layers;
	texProperty._texType = mapTextureType(p_format.texture_type);
	texProperty._need_mipmap = p_format.mipmaps > 1;
	texProperty._tex_format = mapPixelFormat(p_format.format);
	texProperty._tex_usage = p_format.usage_bits;

	auto texHandle = mRenderSystem->createManualTexture("", &texProperty);

	return RenderingDeviceDriver::TextureID(texHandle);
}

RenderingDeviceDriver::TextureID RenderingDeviceDriverNULL::texture_create_from_extension(
	uint64_t p_native_texture, TextureType p_type,
	DataFormat p_format, uint32_t p_array_layers, bool p_depth_stencil)
{
	assert_invariant(false);
	return RenderingDeviceDriver::TextureID(1);
}

RenderingDeviceDriver::TextureID RenderingDeviceDriverNULL::texture_create_shared(TextureID p_original_texture, const TextureView& p_view)
{
	Ogre::OgreTexture* texture = (Ogre::OgreTexture*)p_original_texture.id;
	return RenderingDeviceDriver::TextureID(texture);
}

RenderingDeviceDriver::TextureID RenderingDeviceDriverNULL::texture_create_shared_from_slice
(TextureID p_original_texture, const TextureView& p_view,
	TextureSliceType p_slice_type, uint32_t p_layer,
	uint32_t p_layers, uint32_t p_mipmap, uint32_t p_mipmaps)
{
	Ogre::OgreTexture* tex = (Ogre::OgreTexture*)p_original_texture.id;
	return RenderingDeviceDriver::TextureID(tex);
}

void RenderingDeviceDriverNULL::texture_free(TextureID p_texture)
{

}

uint64_t RenderingDeviceDriverNULL::texture_get_allocation_size(TextureID p_texture)
{
	Ogre::OgreTexture* tex = (Ogre::OgreTexture*)p_texture.id;
	Ogre::TextureProperty* tp = tex->getTextureProperty();

	
	uint32_t size = Ogre::PixelUtil::getMemorySize(tp->_width, tp->_height, tp->_depth, tp->_tex_format);

	return size;
}

void RenderingDeviceDriverNULL::texture_get_copyable_layout(TextureID p_texture,
	const TextureSubresource& p_subresource, TextureCopyableLayout* r_layout)
{
	assert_invariant(false);
}

uint8_t* RenderingDeviceDriverNULL::texture_map(RenderingDeviceDriver::TextureID p_texture, const RenderingDeviceDriver::TextureSubresource& p_subresource)
{
	assert_invariant(false);
	return nullptr;
}

void RenderingDeviceDriverNULL::texture_unmap(TextureID p_texture)
{
	assert_invariant(false);
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
	filament::backend::SamplerParams params;
	params.filterMag = filament::backend::SamplerFilterType::LINEAR;
	params.filterMin = filament::backend::SamplerFilterType::LINEAR;
	params.mipMapMode = filament::backend::SamplerMipMapMode::MIPMAP_MODE_LINEAR;
	params.wrapS = filament::backend::SamplerWrapMode::REPEAT;
	params.wrapT = filament::backend::SamplerWrapMode::REPEAT;
	params.wrapR = filament::backend::SamplerWrapMode::REPEAT;
	params.compareMode = filament::backend::SamplerCompareMode::NONE;
	params.compareFunc = filament::backend::SamplerCompareFunc::N;
	params.anisotropyLog2 = 3;
	params.useComparison = 0;
	params.maxLod = 0;
	params.padding2 = 0;
	auto samplerHandle = mRenderSystem->createTextureSampler(params);

	return RenderingDeviceDriver::SamplerID(samplerHandle.getId());
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
	uint32_t size = p_vertex_attribs.size();
	std::vector<VertexAttribute>* attr = new std::vector<VertexAttribute>;
	attr->resize(size);
	for (uint32_t i = 0; i < size; i++)
	{
		attr->at(i) = p_vertex_attribs[i];
	}

	return RenderingDeviceDriver::VertexFormatID(attr);
}

void RenderingDeviceDriverNULL::vertex_format_free(VertexFormatID p_vertex_format)
{
	VertexAttribute* attr = (VertexAttribute*)p_vertex_format.id;
	delete[] attr;
}

 Ogre::BitField<Ogre::BackendResourceState> mapResourceState(const BitField<RenderingDeviceDriver::BarrierAccessBits>& bits)
{
	 Ogre::BitField<Ogre::BackendResourceState> value;
	if (bits.has_flag(RenderingDeviceDriver::BARRIER_ACCESS_INDEX_READ_BIT))
	{
		value.set_flag(Ogre::RESOURCE_STATE_INDEX_BUFFER);
	}

	if (bits.has_flag(RenderingDeviceDriver::BARRIER_ACCESS_VERTEX_ATTRIBUTE_READ_BIT))
	{
		value.set_flag(Ogre::RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER);
	}

	if (bits.has_flag(RenderingDeviceDriver::BARRIER_ACCESS_MEMORY_READ_BIT))
	{
		value.set_flag(Ogre::RESOURCE_STATE_GENERIC_READ);
	}

	if (bits.has_flag(RenderingDeviceDriver::BARRIER_ACCESS_COPY_READ_BIT))
	{
		value.set_flag(Ogre::RESOURCE_STATE_COPY_SOURCE);
	}

	if (bits.has_flag(RenderingDeviceDriver::BARRIER_ACCESS_COPY_WRITE_BIT))
	{
		value.set_flag(Ogre::RESOURCE_STATE_COPY_DEST);
	}
	if (bits.has_flag(RenderingDeviceDriver::BARRIER_ACCESS_COLOR_ATTACHMENT_READ_BIT))
	{
		value.set_flag(Ogre::RESOURCE_STATE_SHADER_RESOURCE);
	}

	if (bits.has_flag(RenderingDeviceDriver::BARRIER_ACCESS_RESOLVE_READ_BIT))
	{
		value.set_flag(Ogre::RESOURCE_STATE_PRESENT);
	}

	return value;
}

 Ogre::BitField<Ogre::BackendResourceState> mapResourceState(RenderingDeviceDriver::TextureLayout layout)
 {
	 switch (layout)
	 {
	 case RenderingDeviceDriver::TEXTURE_LAYOUT_UNDEFINED:
		 return Ogre::RESOURCE_STATE_UNDEFINED;
	 case RenderingDeviceDriver::TEXTURE_LAYOUT_STORAGE_OPTIMAL:
		 return Ogre::RESOURCE_STATE_UNORDERED_ACCESS;
	 case RenderingDeviceDriver::TEXTURE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL:
		 return Ogre::RESOURCE_STATE_RENDER_TARGET;
	 case RenderingDeviceDriver::TEXTURE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL:
		 return Ogre::RESOURCE_STATE_DEPTH_WRITE;
	 case RenderingDeviceDriver::TEXTURE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL:
		 return Ogre::RESOURCE_STATE_DEPTH_READ;
	 case RenderingDeviceDriver::TEXTURE_LAYOUT_SHADER_READ_ONLY_OPTIMAL:
		 return Ogre::RESOURCE_STATE_SHADER_RESOURCE;
	 case RenderingDeviceDriver::TEXTURE_LAYOUT_COPY_SRC_OPTIMAL:
		 return Ogre::RESOURCE_STATE_COPY_SOURCE;
	 case RenderingDeviceDriver::TEXTURE_LAYOUT_COPY_DST_OPTIMAL:
		 return Ogre::RESOURCE_STATE_COPY_DEST;
	 default:
		 assert_invariant(false);
		
	 }
	 return Ogre::RESOURCE_STATE_UNDEFINED;
 }

void RenderingDeviceDriverNULL::command_pipeline_barrier(
	CommandBufferID p_cmd_buffer,
	BitField<PipelineStageBits> p_src_stages,
	BitField<PipelineStageBits> p_dst_stages,
	VectorView<MemoryBarrier> p_memory_barriers,
	VectorView<BufferBarrier> p_buffer_barriers,
	VectorView<TextureBarrier> p_texture_barriers)
{

	std::vector<Ogre::BufferBarrier> bufferBarriers;
	bufferBarriers.resize(p_buffer_barriers.size());
	for (uint32_t i = 0; i < p_buffer_barriers.size(); i++)
	{
		bufferBarriers[i].buffer = filament::backend::Handle<filament::backend::HwBufferObject>(p_buffer_barriers[i].buffer.id);
		bufferBarriers[i].mCurrentState = mapResourceState(p_buffer_barriers[i].src_access);
		bufferBarriers[i].mNewState = mapResourceState(p_buffer_barriers[i].dst_access);
		bufferBarriers[i].mBeginOnly = 0;
		bufferBarriers[i].mEndOnly = 0;
	}
	std::vector<Ogre::TextureBarrier> texBarriers;
	texBarriers.resize(p_texture_barriers.size());
	for (uint32_t i = 0; i < p_texture_barriers.size(); i++)
	{
		texBarriers[i] = {};
		texBarriers[i].pTexture = (Ogre::OgreTexture*)(p_texture_barriers[i].texture.id);
		texBarriers[i].mCurrentState = mapResourceState(p_texture_barriers[i].prev_layout);
		texBarriers[i].mNewState = mapResourceState(p_texture_barriers[i].next_layout);
	}
	
	mRenderSystem->resourceBarrier(bufferBarriers.size(), bufferBarriers.data(), texBarriers.size(), texBarriers.data(), 0, nullptr);
}

RenderingDeviceDriver::FenceID RenderingDeviceDriverNULL::fence_create()
{
	auto fh = mRenderSystem->createFence();
	return RenderingDeviceDriver::FenceID(fh.getId());
}

Error RenderingDeviceDriverNULL::fence_wait(FenceID p_fence)
{
	filament::backend::Handle<filament::backend::HwFence> fh(p_fence.id);

	mRenderSystem->waitFence(fh);
	return OK;
}

void RenderingDeviceDriverNULL::fence_free(FenceID p_fence)
{

}

RenderingDeviceDriver::SemaphoreID RenderingDeviceDriverNULL::semaphore_create()
{
	auto sh = mRenderSystem->createSemaphore();
	return RenderingDeviceDriver::SemaphoreID(sh.getId());
}

void RenderingDeviceDriverNULL::semaphore_free(SemaphoreID p_semaphore)
{

}


RenderingDeviceDriver::CommandQueueFamilyID RenderingDeviceDriverNULL::command_queue_family_get(
	BitField<CommandQueueFamilyBits> p_cmd_queue_family_bits, RenderingContextDriver::SurfaceID p_surface)
{
	if (p_cmd_queue_family_bits.has_flag(COMMAND_QUEUE_FAMILY_GRAPHICS_BIT))
	{
		return RenderingDeviceDriver::CommandQueueFamilyID(Ogre::QueueType::QUEUE_TYPE_GRAPHICS + 1);
	}

	if (p_cmd_queue_family_bits.has_flag(COMMAND_QUEUE_FAMILY_COMPUTE_BIT))
	{
		assert_invariant(false);
	}

	if (p_cmd_queue_family_bits.has_flag(COMMAND_QUEUE_FAMILY_TRANSFER_BIT))
	{
		return RenderingDeviceDriver::CommandQueueFamilyID(Ogre::QueueType::QUEUE_TYPE_TRANSFER + 1);
	}

	return RenderingDeviceDriver::CommandQueueFamilyID();
}

RenderingDeviceDriver::CommandQueueID RenderingDeviceDriverNULL::command_queue_create(
	CommandQueueFamilyID p_cmd_queue_family, bool p_identify_as_main_queue)
{
	Ogre::QueueType type = (Ogre::QueueType)(p_cmd_queue_family.id - 1);
	auto cqh = mRenderSystem->createCommandQueue(type, 0);

	return RenderingDeviceDriver::CommandQueueID(cqh.getId());
}

Error RenderingDeviceDriverNULL::command_queue_execute_and_present(
	CommandQueueID p_cmd_queue, VectorView<SemaphoreID> p_wait_semaphores,
	VectorView<CommandBufferID> p_cmd_buffers, VectorView<SemaphoreID> p_cmd_semaphores,
	FenceID p_cmd_fence, VectorView<SwapChainID> p_swap_chains)
{
	filament::backend::Handle<filament::backend::HwCommandQueue> cqh(p_cmd_queue.id);

	std::vector<filament::backend::Handle<filament::backend::HwSemaphore>> wait_sphs;
	wait_sphs.resize(p_wait_semaphores.size());
	for (uint32_t i = 0; i < p_wait_semaphores.size(); i++)
	{
		wait_sphs[i] = filament::backend::Handle<filament::backend::HwSemaphore>(p_wait_semaphores[i].id);
	}
	std::vector< filament::backend::Handle<filament::backend::HwCommandBuffer>> cbhs;
	cbhs.resize(p_cmd_buffers.size());
	for (uint32_t i = 0; i < p_cmd_buffers.size(); i++)
	{
		cbhs[i] = filament::backend::Handle<filament::backend::HwCommandBuffer>(p_cmd_buffers[i].id);
	}

	std::vector<filament::backend::Handle<filament::backend::HwSemaphore>> cmd_sphs;
	cmd_sphs.resize(p_cmd_semaphores.size());
	for (uint32_t i = 0; i < p_cmd_semaphores.size(); i++)
	{
		cmd_sphs[i] = filament::backend::Handle<filament::backend::HwSemaphore>(p_cmd_semaphores[i].id);
	}
	filament::backend::Handle<filament::backend::HwFence> fh(p_cmd_fence.id);
	mRenderSystem->executeAndPresent(cqh, wait_sphs.data(), wait_sphs.size(),
		cbhs.data(), cbhs.size(), cmd_sphs.data(), cmd_sphs.size(), fh, nullptr, p_swap_chains.size());
	return OK;
}

void RenderingDeviceDriverNULL::command_queue_free(CommandQueueID p_cmd_queue)
{

}


RenderingDeviceDriver::CommandPoolID RenderingDeviceDriverNULL::command_pool_create(
	CommandQueueFamilyID p_cmd_queue_family, CommandBufferType p_cmd_buffer_type)
{
	return RenderingDeviceDriver::CommandPoolID(p_cmd_queue_family.id);
}

void RenderingDeviceDriverNULL::command_pool_free(CommandPoolID p_cmd_pool)
{

}

RenderingDeviceDriver::CommandBufferID RenderingDeviceDriverNULL::command_buffer_create(CommandPoolID p_cmd_pool)
{
	Ogre::QueueType type = (Ogre::QueueType)(p_cmd_pool.id - 1);
	auto cbh = mRenderSystem->createCommandBuffer(type);
	return RenderingDeviceDriver::CommandBufferID(cbh.getId());
}

bool RenderingDeviceDriverNULL::command_buffer_begin(CommandBufferID p_cmd_buffer)
{
	filament::backend::Handle<filament::backend::HwCommandBuffer> cbh(p_cmd_buffer.id);
	mRenderSystem->beginCommandBuffer(cbh);
	return true;
}

bool RenderingDeviceDriverNULL::command_buffer_begin_secondary(
	CommandBufferID p_cmd_buffer, RenderPassID p_render_pass, uint32_t p_subpass, FramebufferID p_framebuffer)
{
	assert_invariant(false);
	return true;
}

void RenderingDeviceDriverNULL::command_buffer_end(CommandBufferID p_cmd_buffer)
{
	filament::backend::Handle<filament::backend::HwCommandBuffer> cbh(p_cmd_buffer.id);
	mRenderSystem->endCommandBuffer(cbh);
}

void RenderingDeviceDriverNULL::command_buffer_execute_secondary(
	CommandBufferID p_cmd_buffer, VectorView<CommandBufferID> p_secondary_cmd_buffers)
{
	assert_invariant(false);
}

RenderingDeviceDriver::SwapChainID RenderingDeviceDriverNULL::swap_chain_create(RenderingContextDriver::SurfaceID p_surface)
{
	auto sch = mRenderSystem->createSwapChain();
	SwapChainPrivateInfo* info = new SwapChainPrivateInfo;
	info->sch = sch;
	auto& ogreConfig = Ogre::Root::getSingleton().getEngineConfig();
	for (uint32_t i = 0; i < ogreConfig.swapBufferCount; i++)
	{
		FrameBufferInfo* frameInfo = new FrameBufferInfo;
		frameInfo->isSwapChain = true;
		info->swapChainFrame.push_back(frameInfo);
	}
	return RenderingDeviceDriver::SwapChainID(info);
}

Error RenderingDeviceDriverNULL::swap_chain_resize(
	CommandQueueID p_cmd_queue, SwapChainID p_swap_chain, uint32_t p_desired_framebuffer_count)
{
	return OK;
}

RenderingDeviceDriver::FramebufferID RenderingDeviceDriverNULL::swap_chain_acquire_framebuffer(
	CommandQueueID p_cmd_queue, SwapChainID p_swap_chain, bool& r_resize_required)
{
	SwapChainPrivateInfo* info = (SwapChainPrivateInfo*)p_swap_chain.id;

	Ogre::SwapChainInfo swapChainInfo;
	mRenderSystem->swapChainAcquire(info->sch, swapChainInfo);
	FrameBufferInfo* frameInfo = info->swapChainFrame[swapChainInfo.imageIndex];
	frameInfo->textureList.clear();
	frameInfo->textureList.push_back(swapChainInfo.color);
	frameInfo->depth = swapChainInfo.depth;
	return RenderingDeviceDriver::FramebufferID(frameInfo);
}

RenderingDeviceDriver::RenderPassID RenderingDeviceDriverNULL::swap_chain_get_render_pass(SwapChainID p_swap_chain)
{
	return RenderingDeviceDriver::RenderPassID(1);
}

RenderingDeviceDriver::DataFormat RenderingDeviceDriverNULL::swap_chain_get_format(SwapChainID p_swap_chain)
{
	return DATA_FORMAT_R8G8B8A8_UNORM;
}

void RenderingDeviceDriverNULL::swap_chain_free(SwapChainID p_swap_chain)
{

}

RenderingDeviceDriverNULL::FramebufferID RenderingDeviceDriverNULL::framebuffer_create(
	RenderingDeviceDriver::RenderPassID p_render_pass, VectorView<RenderingDeviceDriver::TextureID> p_attachments,
	uint32_t p_width, uint32_t p_height)
{

	FrameBufferInfo* info = new FrameBufferInfo;
	info->width = p_width;
	info->height = p_height;
	for (uint32_t i = 0; i < p_attachments.size(); i++) 
	{
		Ogre::OgreTexture* tex = (Ogre::OgreTexture*)p_attachments[i].id;
		info->textureList.push_back(tex);
	}


	return RenderingDeviceDriverNULL::FramebufferID(info);
}

void RenderingDeviceDriverNULL::framebuffer_free(FramebufferID p_framebuffer)
{
	FrameBufferInfo* info = (FrameBufferInfo*)p_framebuffer.id;
	delete info;
}

String RenderingDeviceDriverNULL::shader_get_binary_cache_key()
{
	return String();
}

Vector<uint8_t> RenderingDeviceDriverNULL::shader_compile_binary_from_spirv(
	VectorView<RenderingDeviceDriver::ShaderStageSPIRVData> p_spirv, const String& p_shader_name)
{
	uint32_t size = p_spirv.size();
	if (size > 1)
	{
		int kk = 0;
	}
	ShaderReflection shader_refl;
	if (_reflect_spirv(p_spirv, shader_refl) != OK) {
		return Vector<uint8_t>();
	}

	Vector<uint8_t> ret;
	ShaderData binary_data;
	Vector<Vector<DataBinding>> uniforms; // Set bindings.
	Vector<SpecializationConstant> specialization_constants;
	binary_data.vertex_input_mask = shader_refl.vertex_input_mask;
	binary_data.fragment_output_mask = shader_refl.fragment_output_mask;
	binary_data.specialization_constants_count = shader_refl.specialization_constants.size();
	binary_data.is_compute = shader_refl.is_compute;
	binary_data.compute_local_size[0] = shader_refl.compute_local_size[0];
	binary_data.compute_local_size[1] = shader_refl.compute_local_size[1];
	binary_data.compute_local_size[2] = shader_refl.compute_local_size[2];
	binary_data.set_count = shader_refl.uniform_sets.size();
	binary_data.push_constant_size = shader_refl.push_constant_size;
	binary_data.stage_count = p_spirv.size();
	for (const Vector<ShaderUniform>& set_refl : shader_refl.uniform_sets) {
		Vector<DataBinding> set_bindings;
		for (const ShaderUniform& uniform_refl : set_refl) {
			DataBinding binding;
			binding.type = (uint32_t)uniform_refl.type;
			binding.binding = uniform_refl.binding;
			binding.stages = (uint32_t)uniform_refl.stages;
			binding.length = uniform_refl.length;
			binding.writable = (uint32_t)uniform_refl.writable;
			auto ascii = uniform_refl.name.ascii();
			assert_invariant(ascii.size() < sizeof(binding.name));
			strncpy(binding.name, ascii.ptr(), sizeof(binding.name));
			set_bindings.push_back(binding);
		}
		uniforms.push_back(set_bindings);
	}

	for (const ShaderSpecializationConstant& refl_sc : shader_refl.specialization_constants)
	{
		SpecializationConstant spec_constant;
		spec_constant.type = (uint32_t)refl_sc.type;
		spec_constant.constant_id = refl_sc.constant_id;
		spec_constant.int_value = refl_sc.int_value;
		spec_constant.stage_flags = (uint32_t)refl_sc.stages;
		specialization_constants.push_back(spec_constant);
	}

	uint32_t total_size = 0;
	total_size += sizeof(ShaderPrivateInfo);
	CharString shader_name_utf = p_shader_name.utf8();
	uint32_t shader_name_len = shader_name_utf.length();
	total_size += sizeof(uint32_t); //shader_name_len
	total_size += shader_name_len;

	total_size += sizeof(ShaderData);
	total_size += sizeof(uint32_t);
	total_size += sizeof(SpecializationConstant) * specialization_constants.size();


	total_size += sizeof(uint32_t);
	for (uint32_t i = 0; i < uniforms.size(); i++)
	{
		total_size += sizeof(uint32_t);
		total_size += sizeof(DataBinding) * uniforms[i].size();
	}
	
	if (binary_data.stage_count > 1)
	{
		int kk = 0;
	}
	for (uint32_t i = 0; i < binary_data.stage_count; i++)
	{
		total_size += sizeof(uint32_t); //stage
		total_size += sizeof(uint32_t); //spirv size
		total_size += p_spirv[i].spirv.size();
	}
	ret.resize(total_size);

	uint32_t offset = 0;
	uint8_t* binptr = ret.ptrw();
	binptr[0] = 'G';
	binptr[1] = 'S';
	binptr[2] = 'B';
	binptr[3] = 'D';
	offset += 4;
	encode_uint32(0, binptr + offset);
	offset += sizeof(uint32_t);
	encode_uint32(total_size, binptr + offset);
	offset += sizeof(uint32_t);
	encode_uint32(shader_name_len, binptr + offset);
	offset += sizeof(uint32_t);
	if (shader_name_len > 0) {
		memcpy(binptr + offset, shader_name_utf.ptr(), shader_name_len);
	}
	offset += shader_name_len;
	memcpy(binptr + offset, &binary_data, sizeof(binary_data));
	offset += sizeof(binary_data);

	for (uint32_t i = 0; i < binary_data.set_count; i++)
	{
		encode_uint32(uniforms[i].size(), binptr + offset);
		offset += sizeof(uint32_t);
		memcpy(binptr + offset, uniforms[i].ptr(), uniforms[i].size() * sizeof(DataBinding));
		offset += uniforms[i].size() * sizeof(DataBinding);
	}
	uint32_t specialization_size = sizeof(SpecializationConstant) * specialization_constants.size();
	memcpy(binptr + offset, specialization_constants.ptr(), specialization_size);
	offset += specialization_size;

	for (uint32_t i = 0; i < binary_data.stage_count; i++)
	{
		encode_uint32(p_spirv[i].shader_stage, binptr + offset);
		offset += sizeof(uint32_t);
		encode_uint32(p_spirv[i].spirv.size(), binptr + offset);
		offset += sizeof(uint32_t);
		memcpy(binptr + offset, p_spirv[i].spirv.ptr(), p_spirv[i].spirv.size());
		offset += p_spirv[i].spirv.size();
	}
	return ret;
}

RenderingDeviceDriver::ShaderID RenderingDeviceDriverNULL::shader_create_from_bytecode(
	const Vector<uint8_t>& p_shader_binary, 
	RenderingDeviceDriver::ShaderDescription& r_shader_desc, 
	String& r_name)
{

	Ogre::ShaderDesc desc;
	const uint8_t* binptr = p_shader_binary.ptr();
	uint32_t binsize = p_shader_binary.size();

	ERR_FAIL_COND_V(binptr[0] != 'G' || binptr[1] != 'S' || binptr[2] != 'B' || binptr[3] != 'D', ShaderID());

	uint32_t bin_version = decode_uint32(binptr + 4);
	uint32_t bin_data_size = decode_uint32(binptr + 8);
	uint32_t offset = 12;

	uint32_t shader_name_len = decode_uint32(binptr + offset);
	offset += sizeof(uint32_t);

	if (shader_name_len)
	{
		r_name.parse_utf8((const char*)(binptr + offset), shader_name_len);
		offset += shader_name_len;
	}
	
	ShaderData binary_data;
	std::vector<std::vector<DataBinding>> uniforms; // Set bindings.
	std::vector<SpecializationConstant> specialization_constants;
	memcpy(&binary_data, binptr + offset, sizeof(binary_data));
	offset += sizeof(binary_data);

	uniforms.resize(binary_data.set_count);
	for (uint32_t i = 0; i < binary_data.set_count; i++)
	{
		uint32_t binding_size = decode_uint32(binptr + offset);
		offset += sizeof(uint32_t);
		uniforms[i].resize(binding_size);
		memcpy(uniforms[i].data(), binptr + offset, binding_size * sizeof(DataBinding));
		offset += binding_size * sizeof(DataBinding);
	}
	specialization_constants.resize(binary_data.specialization_constants_count);
	uint32_t specialization_size = binary_data.specialization_constants_count * sizeof(SpecializationConstant);
	memcpy(specialization_constants.data(), binptr + offset, specialization_size);
	offset += specialization_size;
	r_shader_desc.push_constant_size = binary_data.push_constant_size;
	r_shader_desc.vertex_input_mask = binary_data.vertex_input_mask;
	r_shader_desc.fragment_output_mask = binary_data.fragment_output_mask;

	r_shader_desc.is_compute = binary_data.is_compute;
	r_shader_desc.compute_local_size[0] = binary_data.compute_local_size[0];
	r_shader_desc.compute_local_size[1] = binary_data.compute_local_size[1];
	r_shader_desc.compute_local_size[2] = binary_data.compute_local_size[2];
	r_shader_desc.uniform_sets.resize(binary_data.set_count);


	r_shader_desc.specialization_constants.resize(binary_data.specialization_constants_count);
	for (uint32_t i = 0; i < binary_data.specialization_constants_count; i++)
	{
		const SpecializationConstant& src_sc = specialization_constants[i];
		ShaderSpecializationConstant sc;
		sc.type = PipelineSpecializationConstantType(src_sc.type);
		sc.constant_id = src_sc.constant_id;
		sc.int_value = src_sc.int_value;
		sc.stages = src_sc.stage_flags;
		r_shader_desc.specialization_constants.write[i] = sc;
	}

	for (uint32_t i = 0; i < binary_data.set_count; i++)
	{
		DataBinding* binging_ptr = uniforms[i].data();
		uint32_t binding_count = uniforms[i].size();
		for (uint32 j = 0; j < binding_count; j++)
		{
			ShaderUniform info;
			info.type = UniformType(binging_ptr[j].type);
			info.writable = binging_ptr[j].writable;
			info.length = binging_ptr[j].length;
			info.binding = binging_ptr[j].binding;
			info.stages = binging_ptr[j].stages;
			r_shader_desc.uniform_sets.write[i].push_back(info);
		}
	}

	r_shader_desc.stages.resize(binary_data.stage_count);
	for (uint32_t i = 0; i < binary_data.stage_count; i++)
	{
		ShaderStage stage = (ShaderStage)decode_uint32(binptr + offset);
		offset += sizeof(uint32_t);
		uint32_t spirv_size = decode_uint32(binptr + offset);
		offset += sizeof(uint32_t);
		switch (stage)
		{
		case SHADER_STAGE_VERTEX:
			desc.vertexBin.resize(spirv_size);
			memcpy(desc.vertexBin.data(), binptr + offset, spirv_size);
			break;
		case SHADER_STAGE_FRAGMENT:
			desc.fragBin.resize(spirv_size);
			memcpy(desc.fragBin.data(), binptr + offset, spirv_size);
			break;
		case SHADER_STAGE_COMPUTE:
			desc.computeBin.resize(spirv_size);
			memcpy(desc.computeBin.data(), binptr + offset, spirv_size);
			break;
		}
		offset += spirv_size;
		r_shader_desc.stages.set(i, ShaderStage(stage));
	}
	
	desc.name = r_name.ascii().get_data();
	auto sh = mRenderSystem->createShader(desc);
	return RenderingDeviceDriver::ShaderID(sh.getId());
}

void RenderingDeviceDriverNULL::shader_free(RenderingDeviceDriver::ShaderID p_shader)
{

}

void RenderingDeviceDriverNULL::shader_destroy_modules(ShaderID p_shader)
{

}

Ogre::DescriptorType mapDescriptorType(RenderingDeviceCommons::UniformType type)
{
	switch (type)
	{
	case RenderingDeviceCommons::UNIFORM_TYPE_SAMPLER:
		return Ogre::DESCRIPTOR_TYPE_SAMPLER;
	case RenderingDeviceCommons::UNIFORM_TYPE_SAMPLER_WITH_TEXTURE:
		return Ogre::DESCRIPTOR_TYPE_TEXTURE_SAMPLER;
	case RenderingDeviceCommons::UNIFORM_TYPE_TEXTURE:
		return Ogre::DESCRIPTOR_TYPE_TEXTURE;
	case RenderingDeviceCommons::UNIFORM_TYPE_IMAGE:
		return Ogre::DESCRIPTOR_TYPE_RW_TEXTURE;
	case RenderingDeviceCommons::UNIFORM_TYPE_UNIFORM_BUFFER:
		return Ogre::DESCRIPTOR_TYPE_BUFFER;
	case RenderingDeviceCommons::UNIFORM_TYPE_STORAGE_BUFFER:
		return Ogre::DESCRIPTOR_TYPE_RW_BUFFER;
	default:
		assert_invariant(false);
		return Ogre::DESCRIPTOR_TYPE_BUFFER;
	}
}

RenderingDeviceDriver::UniformSetID RenderingDeviceDriverNULL::uniform_set_create(
	VectorView<BoundUniform> p_uniforms, ShaderID p_shader, uint32_t p_set_index)
{
	filament::backend::Handle<filament::backend::HwShader> sh(p_shader.id);
	auto dsh = mRenderSystem->createDescriptorSet(sh, p_set_index);

	Ogre::DescriptorData descriptorData[128];

	uint32_t size = p_uniforms.size();

	assert_invariant(size <= 128);
	std::vector< filament::backend::Handle<filament::backend::HwBufferObject>> buffers;
	std::vector<Ogre::OgreTexture*> textures;
	std::vector< filament::backend::Handle<filament::backend::HwSampler>> samplers;

	uint32_t capacity = std::max(size, (uint32_t)16);
	buffers.reserve(capacity);
	textures.reserve(capacity);
	samplers.reserve(capacity);
	for (uint32_t i = 0; i < size; i++)
	{
		const BoundUniform& uniform = p_uniforms[i];
		descriptorData[i].pName = nullptr;
		descriptorData[i].mDstBinding = uniform.binding;
		descriptorData[i].mCount = uniform.ids.size();
		descriptorData[i].mLevel = 0;
		descriptorData[i].descriptorType = mapDescriptorType(uniform.type);
		
		switch (descriptorData[i].descriptorType)
		{
		case Ogre::DESCRIPTOR_TYPE_BUFFER:
		case Ogre::DESCRIPTOR_TYPE_RW_BUFFER:
		{
			uint32_t offset = buffers.size();
			for (uint32_t j = 0; j < descriptorData[i].mCount; j++)
			{
				buffers.push_back(filament::backend::Handle<filament::backend::HwBufferObject>(uniform.ids[j].id));
			}
			descriptorData[i].ppBuffers = buffers.data() + offset;
		}
			
			break;
		case Ogre::DESCRIPTOR_TYPE_TEXTURE:
		case Ogre::DESCRIPTOR_TYPE_RW_TEXTURE:
		{
			uint32_t offset = textures.size();
			
			for (uint32_t j = 0; j < descriptorData[i].mCount; j++)
			{
				textures.push_back((Ogre::OgreTexture *)uniform.ids[j].id);
			}
			descriptorData[i].ppTextures = (const Ogre::OgreTexture**)(textures.data() + offset);
		}
		break;
		case Ogre::DESCRIPTOR_TYPE_TEXTURE_SAMPLER:
		{
			uint32_t offset = textures.size();
			uint32_t num_descriptors = uniform.ids.size() / 2;
			descriptorData[i].mCount = num_descriptors;
			for (uint32_t j = 0; j < num_descriptors; j++)
			{
				textures.push_back((Ogre::OgreTexture*)(uniform.ids[j*2+1].id));
			}
			descriptorData[i].ppTextures = (const Ogre::OgreTexture**)(textures.data() + offset);
		}
			
			break;
		case Ogre::DESCRIPTOR_TYPE_SAMPLER:
		{
			uint32_t offset = samplers.size();
			for (uint32_t j = 0; j < descriptorData[i].mCount; j++)
			{
				filament::backend::Handle<filament::backend::HwSampler> sph(uniform.ids[j].id);
				samplers.push_back(sph);
			}
			descriptorData[i].ppSamplers = samplers.data() + offset;
		}
			break;
		default:
			assert_invariant(false);
		}
	
		
	}
	
	mRenderSystem->updateDescriptorSet(dsh, size, descriptorData);
	return RenderingDeviceDriver::UniformSetID(dsh.getId());
}

void RenderingDeviceDriverNULL::uniform_set_free(UniformSetID p_uniform_set)
{

}

void RenderingDeviceDriverNULL::command_uniform_set_prepare_for_use(
	CommandBufferID p_cmd_buffer, UniformSetID p_uniform_set, ShaderID p_shader, uint32_t p_set_index)
{
	assert_invariant(false);
}

void RenderingDeviceDriverNULL::command_clear_buffer(CommandBufferID p_cmd_buffer,
	BufferID p_buffer, uint64_t p_offset, uint64_t p_size)
{
	filament::backend::Handle<filament::backend::HwBufferObject> boh(p_buffer.id);
	filament::backend::Handle<filament::backend::HwCommandBuffer> cbh(p_cmd_buffer.id);
	mRenderSystem->clearBufferObject(boh, cbh);
}

void RenderingDeviceDriverNULL::command_copy_buffer(
	CommandBufferID p_cmd_buffer, 
	BufferID p_src_buffer, 
	BufferID p_dst_buffer, VectorView<BufferCopyRegion> p_regions)
{
	filament::backend::Handle<filament::backend::HwCommandBuffer> cbh(p_cmd_buffer.id);

	filament::backend::Handle<filament::backend::HwBufferObject> src(p_src_buffer.id);
	filament::backend::Handle<filament::backend::HwBufferObject> dst(p_dst_buffer.id);

	uint32_t size = p_regions.size();
	assert_invariant(size == 1);
	for (uint32_t i = 0; i < p_regions.size(); i++)
	{
		BufferCopyRegion region = p_regions[i];
		mRenderSystem->copyBuffer(src, region.src_offset, dst, region.dst_offset, region.size, &cbh);
	}
	
}

void RenderingDeviceDriverNULL::command_copy_texture(CommandBufferID p_cmd_buffer,
	TextureID p_src_texture, TextureLayout p_src_texture_layout, TextureID p_dst_texture,
	TextureLayout p_dst_texture_layout, VectorView<TextureCopyRegion> p_regions)
{
	filament::backend::Handle<filament::backend::HwCommandBuffer> cbh(p_cmd_buffer.id);
	Ogre::OgreTexture* dst = (Ogre::OgreTexture*)p_dst_texture.id;
	Ogre::OgreTexture* src = (Ogre::OgreTexture*)p_src_texture.id;
	Ogre::ImageCopyDesc desc;

	uint32_t size = p_regions.size();
	assert_invariant(size == 1);
	for (uint32_t i = 0; i < size; i++)
	{
		TextureCopyRegion region = p_regions[i];
		desc.srcSubresource.aspectMask = region.src_subresources.aspect;
		desc.srcSubresource.baseArrayLayer = region.src_subresources.base_layer;
		desc.srcSubresource.layerCount = region.src_subresources.layer_count;
		desc.srcSubresource.mipLevel = region.src_subresources.mipmap;
		desc.dstSubresource.aspectMask = region.dst_subresources.aspect;
		desc.dstSubresource.baseArrayLayer = region.dst_subresources.base_layer;
		desc.dstSubresource.layerCount = region.dst_subresources.layer_count;
		desc.dstSubresource.mipLevel = region.dst_subresources.mipmap;
		desc.extent.width = region.size.x;
		desc.extent.height = region.size.y;
		desc.extent.depth = region.size.z;
		desc.srcOffset.x = region.src_offset.x;
		desc.srcOffset.y = region.src_offset.y;
		desc.srcOffset.z = region.src_offset.z;
		desc.dstOffset.x = region.dst_offset.x;
		desc.dstOffset.y = region.dst_offset.y;
		desc.dstOffset.z = region.dst_offset.z;
		mRenderSystem->copyImage(dst, src, desc);
	}
	
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
	filament::backend::Handle<filament::backend::HwCommandBuffer> cbh(p_cmd_buffer.id);
	Ogre::OgreTexture* tex = (Ogre::OgreTexture*)p_texture.id;
	Ogre::Vector4 color(p_color.r, p_color.g, p_color.b, p_color.a);
	Ogre::TextureSubresourceRange subresources;
	subresources.aspect = (int64_t)p_subresources.aspect;
	subresources.base_mipmap = p_subresources.base_mipmap;
	subresources.mipmap_count = p_subresources.mipmap_count;
	subresources.base_layer = p_subresources.base_layer;
	subresources.layer_count = p_subresources.layer_count;
	mRenderSystem->clearRenderTexture(tex, color, subresources);
}

void RenderingDeviceDriverNULL::command_copy_buffer_to_texture(
	CommandBufferID p_cmd_buffer, BufferID p_src_buffer, TextureID p_dst_texture,
	TextureLayout p_dst_texture_layout, VectorView<BufferTextureCopyRegion> p_regions)
{
	filament::backend::Handle<filament::backend::HwCommandBuffer> cbh(p_cmd_buffer.id);
	filament::backend::Handle<filament::backend::HwBufferObject> boh(p_src_buffer.id);
	Ogre::OgreTexture* tex = (Ogre::OgreTexture*)p_dst_texture.id;

	uint32_t size = p_regions.size();
	assert_invariant(size == 1);

	Ogre::ImageCopyBufferDesc desc;

	desc.bufferOffset = p_regions[0].buffer_offset;
	desc.textureOffset.x = p_regions[0].texture_offset.x;
	desc.textureOffset.y = p_regions[0].texture_offset.y;
	desc.textureOffset.z = p_regions[0].texture_offset.z;

	desc.textureRegionSize.x = p_regions[0].texture_region_size.x;
	desc.textureRegionSize.y = p_regions[0].texture_region_size.y;
	desc.textureRegionSize.z = p_regions[0].texture_region_size.z;

	desc.textureSubresources.aspectMask = p_regions[0].texture_subresources.aspect;
	desc.textureSubresources.mipLevel = p_regions[0].texture_subresources.mipmap;
	desc.textureSubresources.baseArrayLayer = p_regions[0].texture_subresources.base_layer;
	desc.textureSubresources.layerCount = p_regions[0].texture_subresources.layer_count;
	desc.textureLayout = (Ogre::TextureLayout)p_dst_texture_layout;
	mRenderSystem->copyBufferToTexture(cbh, boh, tex, desc);
}

void RenderingDeviceDriverNULL::command_copy_texture_to_buffer(
	CommandBufferID p_cmd_buffer, TextureID p_src_texture,
	TextureLayout p_src_texture_layout, BufferID p_dst_buffer, VectorView<BufferTextureCopyRegion> p_regions)
{
	assert_invariant(false);
}

void RenderingDeviceDriverNULL::pipeline_free(PipelineID p_pipeline)
{

}

void RenderingDeviceDriverNULL::command_bind_push_constants(
	CommandBufferID p_cmd_buffer, ShaderID p_shader, uint32_t p_dst_first_index, VectorView<uint32_t> p_data)
{
	filament::backend::Handle<filament::backend::HwCommandBuffer> cbh(p_cmd_buffer.id);
	filament::backend::Handle<filament::backend::HwShader> sh(p_shader.id);

	uint32_t offset = p_dst_first_index * sizeof(uint32_t);
	mRenderSystem->updatePushConstants(cbh, sh, offset, (const char*)p_data.ptr(), p_data.size() * sizeof(uint32_t));
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
	RenderPrivatePassInfo* info = new RenderPrivatePassInfo;
	for (uint32_t i = 0; i < p_attachments.size(); i++)
	{
		Ogre::PixelFormat format = mapPixelFormat(p_attachments[i].format);
		info->attachments.push_back(format);
	}
	info->subpassCount = p_subpasses.size();
	info->subpassDependenciesCount = p_subpass_dependencies.size();
	info->viewCount = p_view_count;
	return RenderingDeviceDriver::RenderPassID(info);
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
	FrameBufferInfo* frameBufferInfo = (FrameBufferInfo*)p_framebuffer.id;
	filament::backend::Handle<filament::backend::HwCommandBuffer> cbh(p_cmd_buffer.id);
	RenderPassInfo renderPassInfo;
	renderPassInfo.cbh = cbh;
	renderPassInfo.renderTargetCount = frameBufferInfo->textureList.size();
	for (uint32_t i = 0; i < renderPassInfo.renderTargetCount; i++)
	{
		renderPassInfo.renderTargets[0].target.texture = frameBufferInfo->textureList[i];
		renderPassInfo.renderTargets[0].isTexture = true;
		renderPassInfo.renderTargets[0].clearColour = { 0.0f, 0.0f, 0.0f, 0.0f };
	}
	
	renderPassInfo.depthTarget.target.texture = frameBufferInfo->depth;
	renderPassInfo.depthTarget.isTexture = true;
	renderPassInfo.depthTarget.clearValue = { 0.0f, 0.0f };
	mRenderSystem->beginRenderPass(renderPassInfo);
}

void RenderingDeviceDriverNULL::command_end_render_pass(CommandBufferID p_cmd_buffer)
{
	filament::backend::Handle<filament::backend::HwCommandBuffer> cbh(p_cmd_buffer.id);
	RenderPassInfo renderPassInfo;
	renderPassInfo.cbh = cbh;
	mRenderSystem->endRenderPass(renderPassInfo);
}

void RenderingDeviceDriverNULL::command_next_render_subpass(
	CommandBufferID p_cmd_buffer, CommandBufferType p_cmd_buffer_type)
{
	assert_invariant(false);
}

void RenderingDeviceDriverNULL::command_render_set_viewport(
	CommandBufferID p_cmd_buffer, VectorView<Rect2i> p_viewports)
{
	for (uint32_t i = 0; i < p_viewports.size(); i++)
	{
		float x = p_viewports[i].position.x;
		float y = p_viewports[i].position.y;
		float width = p_viewports[i].size.x;
		float height = p_viewports[i].size.y;
		float minDepth = 0.0f;
		float maxDepth = 1.0f;
		mRenderSystem->setViewport(x, y, width, height, minDepth, maxDepth);
	}
	
}

void RenderingDeviceDriverNULL::command_render_set_scissor(
	CommandBufferID p_cmd_buffer, VectorView<Rect2i> p_scissors)
{
	for (uint32_t i = 0; i < p_scissors.size(); i++)
	{
		float x = p_scissors[i].position.x;
		float y = p_scissors[i].position.y;
		float width = p_scissors[i].size.x;
		float height = p_scissors[i].size.y;
		mRenderSystem->setScissor(x, y, width, height);
	}
	
}

void RenderingDeviceDriverNULL::command_render_clear_attachments(
	CommandBufferID p_cmd_buffer, VectorView<AttachmentClear> p_attachment_clears, VectorView<Rect2i> p_rects)
{

}

void RenderingDeviceDriverNULL::command_bind_render_pipeline(CommandBufferID p_cmd_buffer, PipelineID p_pipeline)
{

}

void RenderingDeviceDriverNULL::command_bind_render_uniform_set(
	CommandBufferID p_cmd_buffer, 
	UniformSetID p_uniform_set, 
	ShaderID p_shader, 
	uint32_t p_set_index)
{
	filament::backend::Handle<filament::backend::HwDescriptorSet>dsh(p_uniform_set.id);
	filament::backend::Handle<filament::backend::HwShader> sh(p_shader.id);
}

void RenderingDeviceDriverNULL::command_render_draw(
	CommandBufferID p_cmd_buffer,
	uint32_t p_vertex_count,
	uint32_t p_instance_count,
	uint32_t p_base_vertex,
	uint32_t p_first_instance)
{
	filament::backend::Handle<filament::backend::HwCommandBuffer> cbh(p_cmd_buffer.id);
	mRenderSystem->draw(p_vertex_count, p_instance_count, p_base_vertex, p_first_instance, &cbh);
}

void RenderingDeviceDriverNULL::command_render_draw_indexed(
	CommandBufferID p_cmd_buffer,
	uint32_t p_index_count,
	uint32_t p_instance_count,
	uint32_t p_first_index, int32_t p_vertex_offset, uint32_t p_first_instance)
{
	filament::backend::Handle<filament::backend::HwCommandBuffer> cbh(p_cmd_buffer.id);
	mRenderSystem->drawIndexed(
		p_index_count, p_instance_count, p_first_index, p_vertex_offset, p_first_instance, &cbh);
}

void RenderingDeviceDriverNULL::command_render_draw_indexed_indirect(
	CommandBufferID p_cmd_buffer, BufferID p_indirect_buffer,
	uint64_t p_offset, uint32_t p_draw_count, uint32_t p_stride)
{
	filament::backend::Handle<filament::backend::HwCommandBuffer> cbh(p_cmd_buffer.id);
	filament::backend::Handle<filament::backend::HwBufferObject> dbh(p_indirect_buffer.id);
	mRenderSystem->drawIndexedIndirect(dbh, p_offset, p_draw_count, p_stride, &cbh);
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
	for (uint32_t i = 0; i < p_binding_count; i++)
	{
		filament::backend::Handle<filament::backend::HwBufferObject> bufHandle(p_buffers[i].id);

		mRenderSystem->bindVertexBuffer(bufHandle, 0, p_offsets[i]);
	}
}

void RenderingDeviceDriverNULL::command_render_bind_index_buffer(
	CommandBufferID p_cmd_buffer, BufferID p_buffer,
	IndexBufferFormat p_format, uint64_t p_offset)
{
	filament::backend::Handle<filament::backend::HwBufferObject> bufHandle(p_buffer.id);
	uint32_t indexSize = 4;
	if (p_format == INDEX_BUFFER_FORMAT_UINT16)
	{
		indexSize = 2;
	}
	mRenderSystem->bindIndexBuffer(bufHandle, indexSize, p_offset);
}

void RenderingDeviceDriverNULL::command_render_set_blend_constants(
	CommandBufferID p_cmd_buffer, const Color& p_constants)
{

}

void RenderingDeviceDriverNULL::command_render_set_line_width(CommandBufferID p_cmd_buffer, float p_width)
{

}

Ogre::CullingMode mapCullingMode(RenderingDeviceCommons::PolygonCullMode cullingMode)
{
	switch (cullingMode)
	{
	case RenderingDeviceCommons::POLYGON_CULL_DISABLED:
		return Ogre::CULL_MODE_NONE;
	case RenderingDeviceCommons::POLYGON_CULL_FRONT:
		return Ogre::CULL_MODE_FRONT;
	case RenderingDeviceCommons::POLYGON_CULL_BACK:
		return Ogre::CULL_MODE_BACK;
	default:
		assert_invariant(false);
		return Ogre::CULL_MODE_NONE;
	}
}
Ogre::CompareFunction mapDepthCompareOp(RenderingDeviceCommons::CompareOperator compare_operator)
{
	switch (compare_operator)
	{
	case RenderingDeviceCommons::COMPARE_OP_NEVER:
		return Ogre::CMPF_ALWAYS_FAIL;
	case RenderingDeviceCommons::COMPARE_OP_LESS:
		return Ogre::CMPF_LESS;
	case RenderingDeviceCommons::COMPARE_OP_EQUAL:
		return Ogre::CMPF_EQUAL;
	case RenderingDeviceCommons::COMPARE_OP_LESS_OR_EQUAL:
		return Ogre::CMPF_LESS_EQUAL;
	case RenderingDeviceCommons::COMPARE_OP_GREATER:
		return Ogre::CMPF_GREATER;
	case RenderingDeviceCommons::COMPARE_OP_NOT_EQUAL:
		return Ogre::CMPF_NOT_EQUAL;
	case RenderingDeviceCommons::COMPARE_OP_GREATER_OR_EQUAL:
		return Ogre::CMPF_GREATER_EQUAL;
	case RenderingDeviceCommons::COMPARE_OP_ALWAYS:
		return Ogre::CMPF_ALWAYS_PASS;
	default:
		assert_invariant(false);
		return Ogre::CMPF_ALWAYS_PASS;
	}
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
	filament::backend::Handle<filament::backend::HwShader> sh(p_shader.id);
	filament::backend::RasterState aa;
	Ogre::PipelineCreateInfo pipelineCreateInfo;
	VertexDeclaration decl;

	std::vector<VertexAttribute>* attrs = (std::vector<VertexAttribute>*)p_vertex_format.id;
	if (attrs)
	{
		uint32_t attr_size = attrs->size();
		if (attr_size > 1)
		{
			int kk = 0;
		}
		/*assert_invariant(attr_size == 1);
		for (uint32_t i = 0; i < attrs->size(); i++)
		{
			VertexAttribute& attr = attrs->at(i);
			decl.addElement(0, 0, attr.offset, Ogre::VET_FLOAT3, Ogre::VES_POSITION);
		}*/
	}
	
	pipelineCreateInfo.decl = nullptr;
	auto & rasterizationState = pipelineCreateInfo.rasterizationState;
	rasterizationState.cullMode = mapCullingMode(p_rasterization_state.cull_mode);
	rasterizationState.depthBiasClamp = p_rasterization_state.depth_bias_clamp;
	rasterizationState.depthBiasConstantFactor = p_rasterization_state.depth_bias_constant_factor;
	rasterizationState.depthBiasEnable = p_rasterization_state.depth_bias_enabled;
	rasterizationState.depthBiasSlopeFactor = p_rasterization_state.depth_bias_slope_factor;
	rasterizationState.depthClampEnable = p_rasterization_state.enable_depth_clamp;
	rasterizationState.discardPrimitives = p_rasterization_state.discard_primitives;
	rasterizationState.lineWidth = p_rasterization_state.line_width;
	rasterizationState.patchControlPoints = p_rasterization_state.patch_control_points;
	rasterizationState.wireframe = p_rasterization_state.wireframe;
	auto & depthStencilState = pipelineCreateInfo.depthStencilState;
	depthStencilState.depthCompareOp = mapDepthCompareOp(p_depth_stencil_state.depth_compare_operator);
	depthStencilState.depthTestEnable = p_depth_stencil_state.enable_depth_test;
	depthStencilState.depthWriteEnable = p_depth_stencil_state.enable_depth_write;
	depthStencilState.depth_range_max = p_depth_stencil_state.depth_range_max;
	depthStencilState.depth_range_min = p_depth_stencil_state.depth_range_min;
	depthStencilState.enable_depth_range = p_depth_stencil_state.enable_depth_range;
	depthStencilState.enable_stencil = p_depth_stencil_state.enable_stencil;

	auto & colorBlendState = pipelineCreateInfo.colorBlendState;
	colorBlendState.enable_logic_op = p_blend_state.enable_logic_op;
	colorBlendState.logic_op = (Ogre::LogicOperation)p_blend_state.logic_op;
	colorBlendState.attachments.resize(p_blend_state.attachments.size());
	for (uint32_t i = 0; i < p_blend_state.attachments.size(); i++)
	{
		colorBlendState.attachments[i].enable_blend = p_blend_state.attachments[i].enable_blend;
		colorBlendState.attachments[i].blendFunctionSrcRGB =
			(Ogre::BlendFunction)p_blend_state.attachments[i].src_color_blend_factor;
		colorBlendState.attachments[i].blendFunctionDstRGB =
			(Ogre::BlendFunction)p_blend_state.attachments[i].dst_color_blend_factor;
		colorBlendState.attachments[i].blendEquationRGB =
			(Ogre::BlendOperation) p_blend_state.attachments[i].color_blend_op;
		colorBlendState.attachments[i].blendFunctionSrcAlpha =
			(Ogre::BlendFunction)p_blend_state.attachments[i].src_alpha_blend_factor;
		colorBlendState.attachments[i].blendFunctionDstAlpha =
			(Ogre::BlendFunction)p_blend_state.attachments[i].dst_alpha_blend_factor;
		colorBlendState.attachments[i].blendEquationAlpha =
			(Ogre::BlendOperation)p_blend_state.attachments[i].alpha_blend_op;
	}
	auto & renderTarget = pipelineCreateInfo.renderTarget;
	renderTarget.renderTargetCount = p_color_attachments.size();

	auto ph = mRenderSystem->createPipeline(pipelineCreateInfo, sh);
	return RenderingDeviceDriver::PipelineID(ph.getId());
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
	filament::backend::Handle<filament::backend::HwShader> sh(p_shader.id);
	auto ph = mRenderSystem->createComputePipeline(sh);
	return RenderingDeviceDriver::PipelineID(ph.getId());
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
	Ogre::Vector3i color;
	color.x = p_color.r;
	color.y = p_color.g;
	color.z = p_color.b;
	mRenderSystem->pushGroupMarker(p_label_name, color);
}

void RenderingDeviceDriverNULL::command_end_label(CommandBufferID p_cmd_buffer)
{
	mRenderSystem->popGroupMarker();
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
	assert_invariant(false);
}

uint64_t RenderingDeviceDriverNULL::get_resource_native_handle(DriverResource p_type, ID p_driver_id)
{
	assert_invariant(false);
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
	return RenderingDeviceDriver::api_trait_get(p_trait);
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