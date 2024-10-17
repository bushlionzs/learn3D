#version 450 core
#extension GL_GOOGLE_include_directive : require

layout (set = 0, binding = 0)  buffer indirectDrawArgs
{
	uint indirectDrawArgs_data[];
};


struct VBConstants
{
	uint indexOffset;
	uint pad_0;
	uint pad_1;
	uint pad_2;
};

layout(set = 0, binding = 2) uniform VBConstantBuffer
{
    VBConstants vbConstant[2];
};


void ClearIndirectDrawArgsBuffers(const uint dispatchThreadIdX)
{
	if(dispatchThreadIdX == 0)
	{
         for (uint view = 0; view <  5 ; ++view)
         {
            for (uint geom = 0; geom <  2 ; ++geom)
            {
               indirectDrawArgs_data[ (((((view) * 2 ) + (geom)) * 8 ) + (0)) ] = 0;
               indirectDrawArgs_data[ (((((view) * 2 ) + (geom)) * 8 ) + (1)) ] = 1;
               indirectDrawArgs_data[ (((((view) * 2 ) + (geom)) * 8 ) + (2)) ] = vbConstant[geom].indexOffset  ;
               indirectDrawArgs_data[ (((((view) * 2 ) + (geom)) * 8 ) + (3)) ] = 0;
               indirectDrawArgs_data[ (((((view) * 2 ) + (geom)) * 8 ) + (4)) ] = 0;
            }
         }
    }
}

layout (local_size_x = 1, local_size_y = 1, local_size_z = 1) in;
void main()
{
    const uvec3 threadID = uvec3(gl_GlobalInvocationID);
	ClearIndirectDrawArgsBuffers(threadID.x);
}