/**************************************************************************/
/*  rendering_device_driver.cpp                                           */
/**************************************************************************/
/*                         This file is part of:                          */
/*                             GODOT ENGINE                               */
/*                        https://godotengine.org                         */
/**************************************************************************/
/* Copyright (c) 2014-present Godot Engine contributors (see AUTHORS.md). */
/* Copyright (c) 2007-2014 Juan Linietsky, Ariel Manzur.                  */
/*                                                                        */
/* Permission is hereby granted, free of charge, to any person obtaining  */
/* a copy of this software and associated documentation files (the        */
/* "Software"), to deal in the Software without restriction, including    */
/* without limitation the rights to use, copy, modify, merge, publish,    */
/* distribute, sublicense, and/or sell copies of the Software, and to     */
/* permit persons to whom the Software is furnished to do so, subject to  */
/* the following conditions:                                              */
/*                                                                        */
/* The above copyright notice and this permission notice shall be         */
/* included in all copies or substantial portions of the Software.        */
/*                                                                        */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,        */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF     */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. */
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY   */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,   */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE      */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                 */
/**************************************************************************/

#include "rendering_device_driver.h"


/****************/
/**** SHADER ****/
/****************/

Error RenderingDeviceDriver::_reflect_spirv(VectorView<ShaderStageSPIRVData> p_spirv, ShaderReflection &r_reflection) {
	r_reflection = {};

	for (uint32_t i = 0; i < p_spirv.size(); i++) {
		ShaderStage stage = p_spirv[i].shader_stage;
		ShaderStage stage_flag = (ShaderStage)(1 << p_spirv[i].shader_stage);

		if (p_spirv[i].shader_stage == SHADER_STAGE_COMPUTE) {
			r_reflection.is_compute = true;
			ERR_FAIL_COND_V_MSG(p_spirv.size() != 1, FAILED,
					"Compute shaders can only receive one stage, dedicated to compute.");
		}
		ERR_FAIL_COND_V_MSG(r_reflection.stages.has_flag(stage_flag), FAILED,
				"Stage " + String(SHADER_STAGE_NAMES[p_spirv[i].shader_stage]) + " submitted more than once.");

		

		r_reflection.stages.set_flag(stage_flag);
	}

	return OK;
}

/**************/
/**** MISC ****/
/**************/

uint64_t RenderingDeviceDriver::api_trait_get(ApiTrait p_trait) {
	// Sensible canonical defaults.
	switch (p_trait) {
		case API_TRAIT_HONORS_PIPELINE_BARRIERS:
			return 1;
		case API_TRAIT_SHADER_CHANGE_INVALIDATION:
			return SHADER_CHANGE_INVALIDATION_ALL_BOUND_UNIFORM_SETS;
		case API_TRAIT_TEXTURE_TRANSFER_ALIGNMENT:
			return 1;
		case API_TRAIT_TEXTURE_DATA_ROW_PITCH_STEP:
			return 1;
		case API_TRAIT_SECONDARY_VIEWPORT_SCISSOR:
			return 1;
		case API_TRAIT_CLEARS_WITH_COPY_ENGINE:
			return true;
		default:
			ERR_FAIL_V(0);
	}
}

/******************/

RenderingDeviceDriver::~RenderingDeviceDriver() {}
