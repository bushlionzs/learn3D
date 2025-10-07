shader sceneGeometryPass
{
    shader_unit
	 {
		shader_type directx
		vertex_shader scenePass.hlsl VS
		frag_shader scenePass.hlsl PS
	 }
	 
	 shader_unit
	 {
		shader_type vulkan
		vertex_shader scenePass.hlsl VS
		frag_shader  scenePass.hlsl PS 
	 }
}

shader vctShadowPass
{
   shader_unit
	 {
		shader_type directx
		vertex_shader shadowMapping.hlsl VS
		frag_shader  shadowMapping.hlsl PS 
	 }
	 
	 shader_unit
	 {
		shader_type vulkan
		vertex_shader shadowMapping.hlsl VS
		frag_shader  shadowMapping.hlsl PS 
	 }
}

shader forwardScenePass
{
    shader_unit
	 {
		shader_type directx
		vertex_shader forwardScenePass.hlsl VS
		frag_shader forwardScenePass.hlsl PS
	 }
	 
	 shader_unit
	 {
		shader_type vulkan
		vertex_shader forwardScenePass.hlsl VS
		frag_shader  forwardScenePass.hlsl PS 
	 }
}

shader voxelizationPass
{
   shader_unit
	 {
		shader_type directx
		vertex_shader VoxelConeTracingVoxelization.hlsl VSMain
		geometry_shader VoxelConeTracingVoxelization.hlsl GSMain
		frag_shader VoxelConeTracingVoxelization.hlsl PSMain
	 }
	 
	 shader_unit
	 {
		shader_type vulkan
		vertex_shader VoxelConeTracingVoxelization.hlsl VSMain
		geometry_shader VoxelConeTracingVoxelization.hlsl GSMain
		frag_shader VoxelConeTracingVoxelization.hlsl PSMain
	 }
}

shader mipmapPreparePass

{
    shader_unit
	 {
		shader_type directx
		compute_shader VoxelConeTracingAnisoMipmapPrepareCS.hlsl CSMain
	 }
	 
	 shader_unit
	 {
		shader_type vulkan
		compute_shader VoxelConeTracingAnisoMipmapPrepareCS.hlsl CSMain
	 }
}

shader mipmapMainPass
{
    shader_unit
	 {
		shader_type directx
		compute_shader VoxelConeTracingAnisoMipmapMainCS.hlsl CSMain
	 }
	 
	 shader_unit
	 {
		shader_type vulkan
		compute_shader VoxelConeTracingAnisoMipmapMainCS.hlsl CSMain
	 }
}

shader tracingConePass
{
    shader_unit
	 {
		shader_type directx
		compute_shader VoxelConeTracingCS.hlsl CSMain
	 }
	 
	 shader_unit
	 {
		shader_type vulkan
		compute_shader VoxelConeTracingCS.hlsl CSMain
	 }
}

shader vctLightingPass
{
    shader_unit
	 {
		shader_type directx
		vertex_shader VCTLighting.hlsl VSMain
		frag_shader  VCTLighting.hlsl PSMain 
	 }
	 
	 shader_unit
	 {
		shader_type vulkan
		vertex_shader VCTLighting.hlsl VSMain
		frag_shader  VCTLighting.hlsl PSMain 
	 }
}

//vxgi

shader clearVoxelPass
{
    shader_unit
	 {
		shader_type directx
		compute_shader clear6FacesClipmapImage3D.hlsl CSMain
	 }
	 
	 shader_unit
	 {
		shader_type vulkan
		compute_shader clear6FacesClipmapImage3D.hlsl CSMain
	 }
}




//ddgi
shader VctLighting
{
    shader_unit
	 {
		shader_type directx
		vertex_shader VCTLighting.hlsl VSMain
		frag_shader VCTLighting.hlsl PSMain
	 }
	 
	 shader_unit
	 {
		shader_type vulkan
		vertex_shader VCTLighting.hlsl VSMain
		frag_shader VCTLighting.hlsl PSMain
	 }
}

shader downsampleOpacity
{
   shader_unit
	 {
		shader_type directx
	 }
	 
	 shader_unit
	 {
		shader_type vulkan
		compute_shader downsampleOpacity.comp main 
	 }
}

shader downsample3DImage
{
   shader_unit
	 {
		shader_type directx
	 }
	 
	 shader_unit
	 {
		shader_type vulkan
		compute_shader downsample3DImage.comp main 
	 }
}

shader injectLight
{
    shader_unit
	 {
		shader_type directx
		vertex_shader projector.hlsl VS
		frag_shader projector.hlsl PS
	 }
	 
	 shader_unit
	 {
		shader_type vulkan
		vertex_shader injectLightByConservativeVoxelization.vert main
		geometry_shader injectLightByConservativeVoxelization.geom main
		frag_shader  injectLightByConservativeVoxelization.frag main 
	 }
}

shader injectLightByMSAA
{
    shader_unit
	 {
		shader_type directx
		vertex_shader projector.hlsl VS
		frag_shader projector.hlsl PS
	 }
	 
	 shader_unit
	 {
		shader_type vulkan
		vertex_shader injectLightByMSAAVoxelization.vert main
		geometry_shader injectLightByMSAAVoxelization.geom main
		frag_shader  injectLightByMSAAVoxelization.frag main 
	 }
}

shader copyAlpha6Faces
{
   shader_unit
	 {
		shader_type directx
	 }
	 
	 shader_unit
	 {
		shader_type vulkan
		compute_shader copyAlpha6Faces.comp main 
	 }
}

shader copyWrappedBorder
{
   shader_unit
	 {
		shader_type directx
	 }
	 
	 shader_unit
	 {
		shader_type vulkan
		compute_shader copyWrappedBorder.comp main 
	 }
}

shader finalLightingPass
{
    shader_unit
	 {
		shader_type directx
		vertex_shader projector.hlsl VS
		frag_shader projector.hlsl PS
	 }
	 
	 shader_unit
	 {
		shader_type vulkan
		vertex_shader finalLightingPass.vert main
		frag_shader  finalLightingPass.frag main 
	 }
}

shader ProbeBlendingCS
{
     shader_unit
	 {
		shader_type directx
		compute_shader ProbeBlendingCS.hlsl DDGIProbeBlendingCS 
	 }
	 
	 shader_unit
	 {
		shader_type vulkan
		compute_shader ProbeBlendingCS.hlsl DDGIProbeBlendingCS 
	 }
}

shader ProbeRelocationUpdateCS
{
     shader_unit
	 {
		shader_type directx
		compute_shader ProbeRelocationCS.hlsl DDGIProbeRelocationCS 
	 }
	 
	 shader_unit
	 {
		shader_type vulkan
		compute_shader ProbeRelocationCS.hlsl DDGIProbeRelocationCS 
	 }
}

shader ProbeRelocationResetCS
{
     shader_unit
	 {
		shader_type directx
		compute_shader ProbeRelocationCS.hlsl DDGIProbeRelocationResetCS 
	 }
	 
	 shader_unit
	 {
		shader_type vulkan
		compute_shader ProbeRelocationCS.hlsl DDGIProbeRelocationResetCS 
	 }
}

shader ProbeClassificationUpdateCS
{
     shader_unit
	 {
		shader_type directx
		compute_shader ProbeClassificationCS.hlsl DDGIProbeClassificationCS 
	 }
	 
	 shader_unit
	 {
		shader_type vulkan
		compute_shader ProbeClassificationCS.hlsl DDGIProbeClassificationCS 
	 }
}

shader ProbeClassificationResetCS
{
     shader_unit
	 {
		shader_type directx
		compute_shader ProbeClassificationCS.hlsl DDGIProbeClassificationResetCS 
	 }
	 
	 shader_unit
	 {
		shader_type vulkan
		compute_shader ProbeClassificationCS.hlsl DDGIProbeClassificationResetCS 
	 }
}

shader ProbeVariabilityReductionCS
{
     shader_unit
	 {
		shader_type directx
		compute_shader ReductionCS.hlsl DDGIReductionCS 
	 }
	 
	 shader_unit
	 {
		shader_type vulkan
		compute_shader ReductionCS.hlsl DDGIReductionCS 
	 }
}

shader ProbeExtraReductionCS
{
     shader_unit
	 {
		shader_type directx
		compute_shader ReductionCS.hlsl DDGIExtraReductionCS 
	 }
	 
	 shader_unit
	 {
		shader_type vulkan
		compute_shader ReductionCS.hlsl DDGIExtraReductionCS 
	 }
}

shader IndirectCS
{
     shader_unit
	 {
		shader_type directx
		compute_shader IndirectCS.hlsl CS 
	 }
	 
	 shader_unit
	 {
		shader_type vulkan
		compute_shader IndirectCS.hlsl CS 
	 }
}

shader CompositePass
{
    shader_unit
	 {
		shader_type directx
		vertex_shader Composite.hlsl VS
		frag_shader Composite.hlsl PS
	 }
	 
	 shader_unit
	 {
		shader_type vulkan
		vertex_shader Composite.hlsl VS
		frag_shader  Composite.hlsl PS 
	 }
}
