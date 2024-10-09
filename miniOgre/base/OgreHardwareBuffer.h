#pragma once
#include <DriverBase.h>
namespace Ogre {
    enum HardwareBufferUsage : uint8_t
    {
        /** Memory mappable on host and cached
         * @par Usage
         * results of some computations, e.g. screen capture
         */
        HBU_GPU_TO_CPU = 1,
        /** CPU (system) memory
         * This is the least optimal buffer setting.
         * @par Usage
         * Staging copy of resources used as transfer source.
         */
         HBU_CPU_ONLY = 2,
         /** Indicates the application will never read the contents of the buffer back,
         it will only ever write data. Locking a buffer with this flag will ALWAYS
         return a pointer to new, blank memory rather than the memory associated
         with the contents of the buffer; this avoids DMA stalls because you can
         write to a new memory area while the previous one is being used.

         However, you may read from it¡¯s shadow buffer if you set one up
         */
         HBU_DETAIL_WRITE_ONLY = 4,
         /** Device-local GPU (video) memory. No need to be mappable on host.
          * This is the optimal buffer usage setting.
          * @par Usage
          * Resources transferred from host once (immutable) - e.g. most textures, vertex buffers
          */
          HBU_GPU_ONLY = HBU_GPU_TO_CPU | HBU_DETAIL_WRITE_ONLY,
          /** Mappable on host and preferably fast to access by GPU.
           * @par Usage
           * Resources written frequently by host (dynamic) - e.g. uniform buffers updated every frame
           */
           HBU_CPU_TO_GPU = HBU_CPU_ONLY | HBU_DETAIL_WRITE_ONLY,
    };
    class HardwareBuffer
    {
    public:
    public:
        enum BufferType
        {
            VERTEX_BUFFER,
            INDEX_BUFFER,
            CONSTANT_BUFFER
        };

        typedef uint8_t Usage;

        

        /// Rather use HardwareBufferUsage
        enum UsageEnum
        {
            /// same as #HBU_GPU_TO_CPU
            HBU_STATIC = HBU_GPU_TO_CPU,
            /// same as #HBU_CPU_ONLY
            HBU_DYNAMIC = HBU_CPU_ONLY,
            /// @deprecated use #HBU_DETAIL_WRITE_ONLY
            HBU_WRITE_ONLY = HBU_DETAIL_WRITE_ONLY,
            /// @deprecated do not use
            HBU_DISCARDABLE = 8,
            /// same as #HBU_GPU_ONLY
            HBU_STATIC_WRITE_ONLY = HBU_GPU_ONLY,
            /// same as #HBU_CPU_TO_GPU
            HBU_DYNAMIC_WRITE_ONLY = HBU_CPU_TO_GPU,
            /// @deprecated do not use
            HBU_DYNAMIC_WRITE_ONLY_DISCARDABLE = HBU_CPU_TO_GPU,
        };

        enum LockOptions : uint8_t
        {
            HBL_NORMAL,
            HBL_DISCARD,
            HBL_READ_ONLY,
            HBL_NO_OVERWRITE,
            HBL_WRITE_ONLY
        };
    public:
        HardwareBuffer();
        virtual ~HardwareBuffer();

        virtual void* lockimpl(size_t offset, size_t length, LockOptions options)
        {
            return nullptr;
        }
        void* lock(LockOptions options = HBL_WRITE_ONLY)
        {
            return lockimpl(0, mSizeInBytes, options);
        }
        virtual void unlock() = 0;

        virtual void bind(int32_t slot, void* cb) const {};

        virtual void writeData(size_t offset, size_t length, const void* pSource,
        bool discardWholeBuffer = false) {}

        bool isLocked()
        {
            return mIsLocked;
        }

        size_t getSizeInBytes(void) const
        {
            return mSizeInBytes;
        }

        size_t getVertexSize() const
        {
            return mVertexSize;
        }

        int32_t getNumVerts() const
        {
            return mNumVerts;
        }
    protected:
        Usage mUsage;
        uint32_t mSizeInBytes = 0;
        int32_t mVertexSize = 0;
        int32_t mNumVerts = 0;
        std::unique_ptr<HardwareBuffer> mShadowBuffer;
        bool mShadowUpdated = false;
        bool mIsLocked = false;
    };

    class HardwareBufferLockGuard
    {
    public:
        HardwareBufferLockGuard(HardwareBuffer* p)
            :pBuf(p)
        {
            pData = pBuf->lock(HardwareBuffer::HBL_WRITE_ONLY);
        }
        ~HardwareBufferLockGuard()
        {
            pBuf->unlock();
        }
        void* data()
        {
            return pData;
        }
    private:

        HardwareBuffer* pBuf;
        void* pData;
    };

    class BufferHandleLockGuard
    {
    public:
        BufferHandleLockGuard(Handle<HwBufferObject> bufferHandle);
        ~BufferHandleLockGuard();

        void* data();
    private:
        Handle<HwBufferObject> mBufferHandle;
        void* mBufferData;
    };
}