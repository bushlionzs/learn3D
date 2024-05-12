/*
 * Copyright (C) 2019 The Android Open Source Project
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

#include "filament/RenderTarget.h"

#include "filament/FEngine.h"




#include <utils/Panic.h>
#include <filament/RenderTargetBase.h>


namespace filament {

using namespace backend;

struct RenderTarget::BuilderDetails {
    FRenderTarget::Attachment mAttachments[FRenderTarget::ATTACHMENT_COUNT] = {};
    uint32_t mWidth{};
    uint32_t mHeight{};
    uint8_t mSamples = 1;   // currently not settable in the public facing API
};

using BuilderType = RenderTarget;
BuilderType::Builder::Builder() noexcept = default;
BuilderType::Builder::~Builder() noexcept = default;
BuilderType::Builder::Builder(BuilderType::Builder const& rhs) noexcept = default;
BuilderType::Builder::Builder(BuilderType::Builder&& rhs) noexcept = default;
BuilderType::Builder& BuilderType::Builder::operator=(BuilderType::Builder const& rhs) noexcept = default;
BuilderType::Builder& BuilderType::Builder::operator=(BuilderType::Builder&& rhs) noexcept = default;

RenderTarget::Builder& RenderTarget::Builder::texture(AttachmentPoint pt, Texture* texture) noexcept {
    //mImpl->mAttachments[(size_t)pt].texture = downcast(texture);
    return *this;
}

RenderTarget::Builder& RenderTarget::Builder::mipLevel(AttachmentPoint pt, uint8_t level) noexcept {
    mImpl->mAttachments[(size_t)pt].mipLevel = level;
    return *this;
}

RenderTarget::Builder& RenderTarget::Builder::face(AttachmentPoint pt, CubemapFace face) noexcept {
    mImpl->mAttachments[(size_t)pt].face = face;
    return *this;
}

RenderTarget::Builder& RenderTarget::Builder::layer(AttachmentPoint pt, uint32_t layer) noexcept {
    mImpl->mAttachments[(size_t)pt].layer = layer;
    return *this;
}

RenderTarget* RenderTarget::Builder::build(Engine& engine) {
    using backend::TextureUsage;
    const FRenderTarget::Attachment& color = mImpl->mAttachments[(size_t)AttachmentPoint::COLOR0];
    const FRenderTarget::Attachment& depth = mImpl->mAttachments[(size_t)AttachmentPoint::DEPTH];

    if (color.texture) {
 
    }

    if (depth.texture) {
  
    }

    const size_t maxDrawBuffers = downcast(engine).getDriverApi().getMaxDrawBuffers();
    for (size_t i = maxDrawBuffers; i < MAX_SUPPORTED_COLOR_ATTACHMENTS_COUNT; i++) {
        ASSERT_PRECONDITION(!mImpl->mAttachments[i].texture,
                "Only %u color attachments are supported, but COLOR%u attachment is set",
                maxDrawBuffers, i);
    }
    
    uint32_t minWidth = std::numeric_limits<uint32_t>::max();
    uint32_t maxWidth = 0;
    uint32_t minHeight = std::numeric_limits<uint32_t>::max();
    uint32_t maxHeight = 0;
    for (auto const& attachment : mImpl->mAttachments) {
        if (attachment.texture) {
            
        }
    }

    ASSERT_PRECONDITION(minWidth == maxWidth && minHeight == maxHeight,
            "All attachments dimensions must match");

    mImpl->mWidth  = minWidth;
    mImpl->mHeight = minHeight;
    return downcast(engine).createRenderTarget(*this);
}

// ------------------------------------------------------------------------------------------------

FRenderTarget::FRenderTarget(FEngine& engine, const RenderTarget::Builder& builder)
    : mSupportedColorAttachmentsCount(engine.getDriverApi().getMaxDrawBuffers()) {

    
}

void FRenderTarget::terminate(FEngine& engine) {
    FEngine::DriverApi& driver = engine.getDriverApi();
    driver.destroyRenderTarget(mHandle);
}

bool FRenderTarget::hasSampleableDepth() const noexcept {
    return false;
}

} // namespace filament
