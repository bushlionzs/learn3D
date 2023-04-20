#include "OgreHeader.h"
#include "VulkanObjectPool.h"

template<> VulkanObjectPool* Ogre::Singleton<VulkanObjectPool>::msSingleton = 0;

VulkanObjectPool::VulkanObjectPool()
{

}

VulkanObjectPool::~VulkanObjectPool()
{

}


void VulkanObjectPool::init(VulkanRenderSystem* vkrs)
{
    mObjectCB = std::make_unique<VulkanUploadBuffer<ObjectConstantBuffer>>(
        mObjectCountMax,
        true
        );

    mSkinnedCB = std::make_unique<VulkanUploadBuffer<SkinnedConstantBuffer>>(
        mSkinnedCountMax,
        true
        );

    for (uint32_t i = 1; i <= mObjectCountMax; i++)
    {
        mObjectIndexSet.insert(i);
    }

    for (uint32_t i = 1; i <= mSkinnedCountMax; i++)
    {
        mSkinnedCBSet.insert(i);
    }
}

VulkanObjectDesc VulkanObjectPool::allocObject(VulkanObjectType vkType)
{
	VulkanObjectDesc desc;
	desc._vkObjectType = vkType;

    if (vkType == VulkanObject_ObjectCB)
    {
        if (mObjectIndexSet.empty())
        {
            OGRE_EXCEPT(Exception::ERR_INTERNAL_ERROR, "alloc vulkan object failed");
        }

        desc._vkObjectIndex = *mObjectIndexSet.begin();
        mObjectIndexSet.erase(desc._vkObjectIndex);
    }
    else
    {
        if (mSkinnedCBSet.empty())
        {
            OGRE_EXCEPT(Exception::ERR_INTERNAL_ERROR, "alloc vulkan skinned object failed");
        }
        desc._vkObjectIndex = *mSkinnedCBSet.begin();
        mSkinnedCBSet.erase(desc._vkObjectIndex);
    }
	return desc;
}

void VulkanObjectPool::releaseObject(VulkanObjectDesc& desc)
{
    if (desc._vkObjectType == VulkanObject_ObjectCB)
    {
        if (mObjectIndexSet.count(desc._vkObjectIndex) ||
            desc._vkObjectIndex > mObjectCountMax)
        {
            OGRE_EXCEPT(Exception::ERR_INTERNAL_ERROR, "release exception object");
        }

        mObjectIndexSet.insert(desc._vkObjectIndex);
    }
    else
    {
        if (mSkinnedCBSet.count(desc._vkObjectIndex) ||
            desc._vkObjectIndex > mSkinnedCountMax)
        {
            OGRE_EXCEPT(Exception::ERR_INTERNAL_ERROR, "release exception skinned object");
        }

        mSkinnedCBSet.insert(desc._vkObjectIndex);
    }
}

VulkanBufferInfo VulkanObjectPool::getObjectInfo(VulkanObjectDesc& desc)
{
    VulkanBufferInfo vbInfo;
    if (desc._vkObjectType == VulkanObject_ObjectCB)
    {
        vbInfo._vulkanBuffer = mObjectCB->getVKBuffer();
        vbInfo._offset = (desc._vkObjectIndex - 1) * mObjectCB->getObjectSize();
    }
    else
    {
        vbInfo._vulkanBuffer = mSkinnedCB->getVKBuffer();
        vbInfo._offset = (desc._vkObjectIndex - 1) * mSkinnedCB->getObjectSize();
    }
    return vbInfo;
}

void VulkanObjectPool::updateObject(const VulkanObjectDesc& desc, const char* data, uint32_t size)
{
    if (desc._vkObjectType == VulkanObject_ObjectCB)
    {
        assert(desc._vkObjectIndex > 0 && desc._vkObjectIndex <= mObjectCountMax);
        mObjectCB->CopyData(desc._vkObjectIndex - 1, 
            data, size);
    }
    else
    {
        assert(desc._vkObjectIndex > 0 && desc._vkObjectIndex <= mSkinnedCountMax);
        mSkinnedCB->CopyData(desc._vkObjectIndex - 1,
            data, size);
    }
}