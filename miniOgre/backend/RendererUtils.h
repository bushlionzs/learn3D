/*
 * Copyright (C) 2022 The Android Open Source Project
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

#ifndef TNT_FILAMENT_DETAILS_RENDERERUTILS_H
#define TNT_FILAMENT_DETAILS_RENDERERUTILS_H


#include "fg/FrameGraphId.h"
#include "fg/FrameGraphTexture.h"
#include <backend/DriverEnums.h>
#include <backend/PixelBufferDescriptor.h>
#include <backend/Viewport.h>
#include <backend/Engine.h>
#include <math/vec4.h>

#include <stdint.h>

#include <utility>

namespace filament {

class FRenderTarget;
class FrameGraph;
class FrameGraph;
class FView;
class RendererUtils {
public:

    struct ColorPassConfig {
        // Rendering viewport (e.g. scaled down viewport from dynamic resolution)
        filament::Viewport physicalViewport;
        // Logical viewport (e.g. left-bottom non-zero when we have guard bands), origin
        // relative to physicalViewport
        filament::Viewport logicalViewport;
        // dynamic resolution scale
        math::float2 scale;
        // HDR format
        backend::TextureFormat hdrFormat;
        // MSAA sample count
        uint8_t msaa;
        // Clear flags
        backend::TargetBufferFlags clearFlags;
        // Clear color
        math::float4 clearColor = {};
        // Clear stencil
        uint8_t clearStencil = 0u;
        // Lod offset for the SSR passes
        float ssrLodOffset;
        // Contact shadow enabled?
        bool hasContactShadows;
        // Screen space reflections enabled
        bool hasScreenSpaceReflectionsOrRefractions;
        // Use a depth format with a stencil component.
        bool enabledStencilBuffer;
        // whether the screenspace reflections history buffer is initialized
        bool screenSpaceReflectionHistoryNotReady;
    };

    static FrameGraphId<FrameGraphTexture> colorPass(
            FrameGraph& fg, const char* name, FEngine& engine, FView const& view,
            FrameGraphTexture::Descriptor const& colorBufferDesc,
            ColorPassConfig const& config) noexcept;

};

} // namespace filament

#endif // TNT_FILAMENT_DETAILS_RENDERERUTILS_H