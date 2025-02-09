/* WARNING, THIS FILE WAS GENERATED, DO NOT EDIT */
#ifndef SORT_GLSL_GEN_H_RD
#define SORT_GLSL_GEN_H_RD

#include "servers/rendering/renderer_rd/shader_rd.h"

class SortShaderRD : public ShaderRD {

public:

	SortShaderRD() {

		static const char _compute_code[] = {
R"<!>(
#version 450

#VERSION_DEFINES


























#define SORT_SIZE 512
#define NUM_THREADS (SORT_SIZE / 2)
#define INVERSION (16 * 2 + 8 * 3)
#define ITERATIONS 1

layout(local_size_x = NUM_THREADS, local_size_y = 1, local_size_z = 1) in;

#ifndef MODE_SORT_STEP

shared vec2 g_LDS[SORT_SIZE];

#endif

layout(set = 1, binding = 0, std430) restrict buffer SortBuffer {
	vec2 data[];
}
sort_buffer;

layout(push_constant, std430) uniform Params {
	uint total_elements;
	uint pad[3];
	ivec4 job_params;
}
params;

void main() {
#ifdef MODE_SORT_BLOCK

	uvec3 Gid = gl_WorkGroupID;
	uvec3 DTid = gl_GlobalInvocationID;
	uvec3 GTid = gl_LocalInvocationID;
	uint GI = gl_LocalInvocationIndex;

	int GlobalBaseIndex = int((Gid.x * SORT_SIZE) + GTid.x);
	int LocalBaseIndex = int(GI);
	int numElementsInThreadGroup = int(min(SORT_SIZE, params.total_elements - (Gid.x * SORT_SIZE)));

	

	int i;
	for (i = 0; i < 2 * ITERATIONS; ++i) {
		if (GI + i * NUM_THREADS < numElementsInThreadGroup)
			g_LDS[LocalBaseIndex + i * NUM_THREADS] = sort_buffer.data[GlobalBaseIndex + i * NUM_THREADS];
	}

	groupMemoryBarrier();
	barrier();

	
	for (int nMergeSize = 2; nMergeSize <= SORT_SIZE; nMergeSize = nMergeSize * 2) {
		for (int nMergeSubSize = nMergeSize >> 1; nMergeSubSize > 0; nMergeSubSize = nMergeSubSize >> 1) {
			for (i = 0; i < ITERATIONS; ++i) {
				int tmp_index = int(GI + NUM_THREADS * i);
				int index_low = tmp_index & (nMergeSubSize - 1);
				int index_high = 2 * (tmp_index - index_low);
				int index = index_high + index_low;

				int nSwapElem = nMergeSubSize == nMergeSize >> 1 ? index_high + (2 * nMergeSubSize - 1) - index_low : index_high + nMergeSubSize + index_low;
				if (nSwapElem < numElementsInThreadGroup) {
					vec2 a = g_LDS[index];
					vec2 b = g_LDS[nSwapElem];

					if (a.x > b.x) {
						g_LDS[index] = b;
						g_LDS[nSwapElem] = a;
					}
				}
				groupMemoryBarrier();
				barrier();
			}
		}
	}

	
	for (i = 0; i < 2 * ITERATIONS; ++i) {
		if (GI + i * NUM_THREADS < numElementsInThreadGroup) {
			sort_buffer.data[GlobalBaseIndex + i * NUM_THREADS] = g_LDS[LocalBaseIndex + i * NUM_THREADS];
		}
	}

#endif

#ifdef MODE_SORT_STEP

	uvec3 Gid = gl_WorkGroupID;
	uvec3 GTid = gl_LocalInvocationID;

	ivec4 tgp;

	tgp.x = int(Gid.x) * 256;
	tgp.y = 0;
	tgp.z = int(params.total_elements);
	tgp.w = min(512, max(0, tgp.z - int(Gid.x) * 512));

	uint localID = int(tgp.x) + GTid.x; 

	uint index_low = localID & (params.job_params.x - 1);
	uint index_high = 2 * (localID - index_low);

	uint index = tgp.y + index_high + index_low;
	uint nSwapElem = tgp.y + index_high + params.job_params.y + params.job_params.z * index_low;

	if (nSwapElem < tgp.y + tgp.z) {
		vec2 a = sort_buffer.data[index];
		vec2 b = sort_buffer.data[nSwapElem];

		if (a.x > b.x) {
			sort_buffer.data[index] = b;
			sort_buffer.data[nSwapElem] = a;
		}
	}

#endif

#ifdef MODE_SORT_INNER

	uvec3 Gid = gl_WorkGroupID;
	uvec3 DTid = gl_GlobalInvocationID;
	uvec3 GTid = gl_LocalInvocationID;
	uint GI = gl_LocalInvocationIndex;

	ivec4 tgp;

	tgp.x = int(Gid.x * 256);
	tgp.y = 0;
	tgp.z = int(params.total_elements.x);
	tgp.w = int(min(512, max(0, params.total_elements - Gid.x * 512)));

	int GlobalBaseIndex = int(tgp.y + tgp.x * 2 + GTid.x);
	int LocalBaseIndex = int(GI);
	int i;

	
	for (i = 0; i < 2; ++i) {
		if (GI + i * NUM_THREADS < tgp.w)
			g_LDS[LocalBaseIndex + i * NUM_THREADS] = sort_buffer.data[GlobalBaseIndex + i * NUM_THREADS];
	}

	groupMemoryBarrier();
	barrier();

	
	for (int nMergeSubSize = SORT_SIZE >> 1; nMergeSubSize > 0; nMergeSubSize = nMergeSubSize >> 1) {
		int tmp_index = int(GI);
		int index_low = tmp_index & (nMergeSubSize - 1);
		int index_high = 2 * (tmp_index - index_low);
		int index = index_high + index_low;

		int nSwapElem = index_high + nMergeSubSize + index_low;

		if (nSwapElem < tgp.w) {
			vec2 a = g_LDS[index];
			vec2 b = g_LDS[nSwapElem];

			if (a.x > b.x) {
				g_LDS[index] = b;
				g_LDS[nSwapElem] = a;
			}
		}
		groupMemoryBarrier();
		barrier();
	}

	
	for (i = 0; i < 2; ++i) {
		if (GI + i * NUM_THREADS < tgp.w) {
			sort_buffer.data[GlobalBaseIndex + i * NUM_THREADS] = g_LDS[LocalBaseIndex + i * NUM_THREADS];
		}
	}

#endif
}
)<!>"
		};
		setup(nullptr, nullptr, _compute_code, "SortShaderRD");
	}
};

#endif
