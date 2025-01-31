

shader pbr
{
     shader_unit
	 {
		shader_type directx
		vertex_shader pbr.hlsl VS
		frag_shader pbr.hlsl PS
	 }
	 
	 shader_unit
	 {
		shader_type vulkan
		vertex_shader pbr.hlsl VS
		frag_shader pbr.hlsl PS
	 }
}

shader prefilteredMap
{
    shader_unit
	 {
		shader_type directx
		vertex_shader filtercube.vert.glsl main
		frag_shader prefilterenvmap.frag.glsl main
	 }
	 
	 shader_unit
	 {
		shader_type vulkan
		vertex_shader filtercube.vert.glsl main
		frag_shader prefilterenvmap.frag.glsl main
	 }
}

shader irradianceMap
{
    shader_unit
	 {
		shader_type directx
		vertex_shader filtercube.vert.glsl main
		frag_shader irradiancecube.frag.glsl main
	 }
	 
	 shader_unit
	 {
		shader_type vulkan
		vertex_shader filtercube.vert.glsl main
		frag_shader irradiancecube.frag.glsl main
	 }
}

shader generateBRDFLUT
{
    shader_unit
	 {
		shader_type directx
		vertex_shader genbrdflut.vert.glsl main
		frag_shader genbrdflut.frag.glsl main
	 }
	 
	 shader_unit
	 {
		shader_type vulkan
		vertex_shader genbrdflut.vert.glsl main
		frag_shader genbrdflut.frag.glsl main
	 }
}

shader clearBuffer
{
    shader_unit
	 {
		shader_type directx
		compute_shader clearVisibilityBuffers.hlsl CS
	 }
	 
	 shader_unit
	 {
		shader_type vulkan
		//compute_shader clearVisibilityBuffers.glsl main
		compute_shader clearVisibilityBuffers.hlsl CS
	 }
}

shader filterTriangles
{
    shader_unit
	 {
		shader_type directx
		compute_shader filterTriangles.hlsl CS
	 }
	 
	 shader_unit
	 {
		shader_type vulkan
		//compute_shader filterTriangles.glsl main
		compute_shader filterTriangles.hlsl CS
	 }
}


shader meshDepth
{
    shader_unit
	 {
		shader_type directx
		vertex_shader meshDepthPass.hlsl VS
	 }
	 
	 shader_unit
	 {
		shader_type vulkan
		//vertex_shader meshDepthPass.glsl main
		vertex_shader meshDepthPass.hlsl VS
	 }
}

shader meshDepthAlpha
{
    shader_unit
	 {
		shader_type directx
		vertex_shader meshDepthPassAlpha.hlsl VS
		frag_shader  meshDepthPassAlpha.hlsl PS 
	 }
	 
	 shader_unit
	 {
		shader_type vulkan
		//vertex_shader meshDepthPassAlpha.glsl main
		//frag_shader  meshDepthPassAlpha.glsl main 
		vertex_shader meshDepthPassAlpha.hlsl VS
		frag_shader  meshDepthPassAlpha.hlsl PS 
	 }
}

shader visibilityBuffer
{
    shader_unit
	 {
		shader_type directx
		vertex_shader visibilityBufferPass.hlsl VS
		frag_shader  visibilityBufferPass.hlsl PS 
	 }
	 
	 shader_unit
	 {
		shader_type vulkan
		//vertex_shader visibilityBufferPass.glsl main
		//frag_shader  visibilityBufferPass.glsl main 
		vertex_shader visibilityBufferPass.hlsl VS
		frag_shader  visibilityBufferPass.hlsl PS 
	 }
}

shader visibilityBufferAlpha
{
    shader_unit
	 {
		shader_type directx
		vertex_shader visibilityBufferPassAlpha.hlsl VS
		frag_shader  visibilityBufferPassAlpha.hlsl PS 
	 }
	 
	 shader_unit
	 {
		shader_type vulkan
		//vertex_shader visibilityBufferPassAlpha.glsl main
		//frag_shader  visibilityBufferPassAlpha.glsl main 
		vertex_shader visibilityBufferPassAlpha.hlsl VS
		frag_shader  visibilityBufferPassAlpha.hlsl PS 
	 }
}

shader visibilityBufferShade
{
    shader_unit
	 {
		shader_type directx
		vertex_shader visibilityBufferShade.hlsl VS
		frag_shader  visibilityBufferShade.hlsl PS 
	 }
	 
	 shader_unit
	 {
		shader_type vulkan
		//vertex_shader visibilityBufferShade.glsl main
		//frag_shader  visibilityBufferShade.glsl main 
		
		vertex_shader visibilityBufferShade.hlsl VS
		frag_shader  visibilityBufferShade.hlsl PS 
	 }
}

shader presentShade
{
    shader_unit
	 {
		shader_type directx
		vertex_shader presentShade.hlsl VS
		frag_shader  presentShade.hlsl PS 
	 }
	 
	 shader_unit
	 {
		shader_type vulkan
		//vertex_shader presentShade.glsl main
		//frag_shader  presentShade.glsl main 
		
		vertex_shader presentShade.hlsl VS
		frag_shader  presentShade.hlsl PS 
	 }
}



shader testShader
{
    shader_unit
	 {
		shader_type directx
		vertex_shader test.glsl main
		frag_shader  test.glsl main 
		geometry_shader test.glsl main
	 }
	 
	 shader_unit
	 {
		shader_type vulkan
		vertex_shader test.glsl main
		frag_shader  test.glsl main 
		geometry_shader test.glsl main
	 }
}

shader RayQuery
{
    shader_unit
	 {
		shader_type directx 
		compute_shader rayQuery.comp.hlsl main
	 }
    shader_unit
	 {
		shader_type vulkan 
		compute_shader rayQuery.comp.glsl main
	 }
}

