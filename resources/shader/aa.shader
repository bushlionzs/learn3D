shader basic
{
     shader_unit
	 {
		shader_type directx
		vertex_shader basic.hlsl VS
		frag_shader basic.hlsl PS
	 }
	 
	 shader_unit
	 {
		shader_type vulkan
		vertex_shader basic.vert.glsl main
		frag_shader basic.frag.glsl main
	 }
}

shader mygui
{
    shader_unit
	 {
		shader_type directx
		vertex_shader mygui.hlsl VS
		frag_shader mygui.hlsl PS
	 }
	 
	 shader_unit
	 {
		shader_type vulkan
		vertex_shader mygui.vert.glsl main
		frag_shader mygui.frag.glsl main
	 }
}

shader ogreparticle
{
     shader_unit
	 {
		shader_type directx
		vertex_shader ogreparticle.hlsl VS
		frag_shader ogreparticle.hlsl PS
	 }
	 
	 shader_unit
	 {
		shader_type vulkan
		vertex_shader ogreparticle.vert.glsl main
		frag_shader ogreparticle.frag.glsl main
	 }
}

shader ogresky
{
     shader_unit
	 {
		shader_type directx
		vertex_shader sky.hlsl VS
		frag_shader sky.hlsl PS
	 }
	 
	 shader_unit
	 {
		shader_type vulkan
		vertex_shader sky.vert.glsl main
		frag_shader sky.frag.glsl main
	 }
}

shader ogresimple
{
     shader_unit
	 {
		shader_type directx
		vertex_shader ogresimple.hlsl VS
		frag_shader ogresimple.hlsl PS
	 }
	 
	 shader_unit
	 {
		shader_type vulkan
		vertex_shader ogresimple.glsl main
		frag_shader ogresimple.glsl main
	 }
}

shader addblend
{
     shader_unit
	 {
		shader_type directx
		vertex_shader addblend.hlsl VS
		frag_shader addblend.hlsl PS
	 }
	 
	 shader_unit
	 {
		shader_type vulkan
		vertex_shader addblend.vert.glsl main
		frag_shader addblend.frag.glsl main
	 }
}

shader ogreblend
{
     shader_unit
	 {
		shader_type directx
		vertex_shader blend.hlsl VS
		frag_shader blend.hlsl PS
	 }
	 
	 shader_unit
	 {
		shader_type vulkan
		vertex_shader blend.vert.glsl main
		frag_shader blend.frag.glsl main
	 }
}


shader add
{
     shader_unit
	 {
		shader_type directx
		vertex_shader add.hlsl VS
		frag_shader add.hlsl PS
	 }
	 
	 shader_unit
	 {
		shader_type vulkan
		vertex_shader add.vert.glsl main
		frag_shader add.frag.glsl main
	 }
}

shader ogreterrain_onelayer
{
     shader_unit
	 {
		shader_type directx
		vertex_shader ogreterrain.hlsl onelayer_vs
		frag_shader ogreterrain.hlsl onelayer_ps
	 }
	 
	 shader_unit
	 {
		shader_type vulkan
		vertex_shader basic.vert.spv main
		frag_shader basic.frag.spv main
	 }
}

shader ogreterrain_onelayer_lightmap
{
     shader_unit
	 {
		shader_type directx
		vertex_shader ogreterrain.hlsl onelayer_lightmap_vs
		frag_shader ogreterrain.hlsl onelayer_lightmap_ps
	 }
	 
	 shader_unit
	 {
		shader_type vulkan
		vertex_shader basic.vert.spv main
		frag_shader basic.frag.spv main
	 }
}

shader ogreterrain_twolayer
{
     shader_unit
	 {
		shader_type directx
		vertex_shader ogreterrain.hlsl twolayer_vs
		frag_shader ogreterrain.hlsl twolayer_vs
	 }
	 
	 shader_unit
	 {
		shader_type vulkan
		vertex_shader basic.vert.spv main
		frag_shader basic.frag.spv main
	 }
}

shader ogreterrain_twolayer_lightmap
{
     shader_unit
	 {
		shader_type directx
		vertex_shader ogreterrain.hlsl twolayer_lightmap_vs
		frag_shader ogreterrain.hlsl twolayer_lightmap_ps
	 }
	 
	 shader_unit
	 {
		shader_type vulkan
		vertex_shader basic.vert.spv main
		frag_shader basic.frag.spv main
	 }
}

shader water
{
     shader_unit
	 {
		shader_type directx
		vertex_shader water.hlsl vs_main
		frag_shader water.hlsl ps_main
	 }
	 
	 shader_unit
	 {
		shader_type vulkan
		vertex_shader water.glsl vs
		frag_shader water.glsl ps
	 }
}

shader mipmap
{
    shader_unit
	 {
		shader_type directx
		vertex_shader mipmap.hlsl vs
		frag_shader mipmap.hlsl ps
	 }
	 
	 shader_unit
	 {
		shader_type vulkan
		vertex_shader mipmap.glsl vs
		frag_shader mipmap.glsl ps
	 }
}

shader shadow
{
    shader_unit
	 {
		shader_type directx
		vertex_shader shadow.hlsl vs
		frag_shader shadow.hlsl ps
	 }
	 
	 shader_unit
	 {
		shader_type vulkan
		vertex_shader shadow.glsl vs
		frag_shader shadow.glsl ps
	 }
}

shader shadows
{
    shader_unit
	 {
		shader_type directx
		vertex_shader shadows.hlsl vs
		frag_shader shadows.hlsl ps
	 }
	 
	 shader_unit
	 {
		shader_type vulkan
		vertex_shader shadow.glsl vs
		frag_shader shadow.glsl ps
	 }
}