/*
 * Copyright (C) 2023 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "VulkanSpirvUtils.h"

#include <utils/compiler.h>   // UTILS_UNUSED_IN_RELEASE, UTILS_FALLTHROUGH
#include <utils/debug.h>      // assert_invariant
#include <utils/FixedCapacityVector.h>


#include <unordered_map>
#include <variant>
#include <vector>

namespace filament::backend {

namespace {

// This function transforms an OpSpecConstant instruction into just a OpConstant instruction.
// Additionally, it will adjust the value of the constant as given by the program.
void getTransformedConstantInst(SpecConstantValue* value, uint32_t* inst) {

   
}

} // anonymous namespace

void workaroundSpecConstant(Program::ShaderBlob const& blob,
        utils::FixedCapacityVector<Program::SpecializationConstant> const& specConstants,
        std::vector<uint32_t>& output) {
   
}

std::tuple<uint32_t,uint32_t, uint32_t> getProgramBindings(Program::ShaderBlob const& blob) {
    std::unordered_map<uint32_t, uint32_t> targetToSet, targetToBinding;

   
    return {0, 0, 0};
}

} // namespace filament::backend
