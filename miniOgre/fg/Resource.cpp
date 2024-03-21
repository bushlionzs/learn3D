/*
 * Copyright (C) 2021 The Android Open Source Project
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

#include "Handle.h"
#include "Resource.h"

#include "PassNode.h"
#include "ResourceNode.h"



namespace filament {

VirtualResource::~VirtualResource() noexcept = default;

UTILS_ALWAYS_INLINE
void VirtualResource::addOutgoingEdge(ResourceNode* node, ResourceEdgeBase* edge) noexcept {
    node->addOutgoingEdge(edge);
}

UTILS_ALWAYS_INLINE
void VirtualResource::setIncomingEdge(ResourceNode* node, ResourceEdgeBase* edge) noexcept {
    node->setIncomingEdge(edge);
}

UTILS_ALWAYS_INLINE
DependencyGraph::Node* VirtualResource::toDependencyGraphNode(ResourceNode* node) noexcept {
    // this can't go to the header file, because it would add a dependency on ResourceNode.h,
    // which we prefer to avoid
    return node;
}

UTILS_ALWAYS_INLINE
DependencyGraph::Node* VirtualResource::toDependencyGraphNode(PassNode* node) noexcept {
    // this can't go to the header file, because it would add a dependency on PassNode.h
    // which we prefer to avoid
    return node;
}

UTILS_ALWAYS_INLINE
ResourceEdgeBase* VirtualResource::getReaderEdgeForPass(
        ResourceNode* resourceNode, PassNode* passNode) noexcept {
    // this can't go to the header file, because it would add a dependency on PassNode.h
    // which we prefer to avoid
    return resourceNode->getReaderEdgeForPass(passNode);
}

UTILS_ALWAYS_INLINE
ResourceEdgeBase* VirtualResource::getWriterEdgeForPass(
        ResourceNode* resourceNode, PassNode* passNode) noexcept {
    // this can't go to the header file, because it would add a dependency on PassNode.h
    // which we prefer to avoid
    return resourceNode->getWriterEdgeForPass(passNode);
}

void VirtualResource::neededByPass(PassNode* pNode) noexcept {
    refcount++;
    // figure out which is the first pass to need this resource
    first = first ? first : pNode;
    // figure out which is the last pass to need this resource
    last = pNode;

    // also extend the lifetime of our parent resource if any
    if (parent != this) {
        parent->neededByPass(pNode);
    }
}

// ------------------------------------------------------------------------------------------------

ImportedRenderTarget::~ImportedRenderTarget() noexcept = default;

ImportedRenderTarget::ImportedRenderTarget(char const* resourceName,
        FrameGraphTexture::Descriptor const& mainAttachmentDesc,
        FrameGraphRenderPass::ImportDescriptor const& importedDesc,
    backend::Handle<Ogre::RenderTarget> target)
        : ImportedResource<FrameGraphTexture>(resourceName, mainAttachmentDesc,
                usageFromAttachmentsFlags(importedDesc.attachments), {}),
          target(target), importedDesc(importedDesc) {
}

UTILS_NOINLINE
void ImportedRenderTarget::assertConnect(FrameGraphTexture::Usage u) {
    constexpr auto ANY_ATTACHMENT = FrameGraphTexture::Usage::COLOR_ATTACHMENT |
        FrameGraphTexture::Usage::DEPTH_ATTACHMENT |
        FrameGraphTexture::Usage::STENCIL_ATTACHMENT;

    ASSERT_PRECONDITION(none(u & ~ANY_ATTACHMENT),
        "Imported render target resource \"%s\" can only be used as an attachment (usage=%s)",
        name, utils::to_string(u).c_str());
}

bool ImportedRenderTarget::connect(DependencyGraph& graph, PassNode* passNode,
        ResourceNode* resourceNode, backend::TextureUsage u) {
    // pass Node to resource Node edge (a write to)
    assertConnect(u);
    return Resource::connect(graph, passNode, resourceNode, u);
}

bool ImportedRenderTarget::connect(DependencyGraph& graph, ResourceNode* resourceNode,
        PassNode* passNode, backend::TextureUsage u) {
    // resource Node to pass Node edge (a read from)
    assertConnect(u);
    return Resource::connect(graph, resourceNode, passNode, u);
}

FrameGraphTexture::Usage ImportedRenderTarget::usageFromAttachmentsFlags(
        backend::TargetBufferFlags attachments) noexcept {

    if (any(attachments & backend::TargetBufferFlags::COLOR_ALL))
        return FrameGraphTexture::Usage::COLOR_ATTACHMENT;

    if ((attachments & backend::TargetBufferFlags::DEPTH_AND_STENCIL) == backend::TargetBufferFlags::DEPTH_AND_STENCIL)
        return FrameGraphTexture::Usage::DEPTH_ATTACHMENT | FrameGraphTexture::Usage::STENCIL_ATTACHMENT;

    if (any(attachments & backend::TargetBufferFlags::DEPTH))
        return FrameGraphTexture::Usage::DEPTH_ATTACHMENT;

    if (any(attachments & backend::TargetBufferFlags::STENCIL))
        return FrameGraphTexture::Usage::STENCIL_ATTACHMENT;

    // we shouldn't be here
    return FrameGraphTexture::Usage::COLOR_ATTACHMENT;
}

// ------------------------------------------------------------------------------------------------

template class Resource<FrameGraphTexture>;
template class ImportedResource<FrameGraphTexture>;

} // namespace filament
