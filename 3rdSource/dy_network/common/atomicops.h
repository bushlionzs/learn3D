#ifndef _ATOMICOPS_H_INCLUDED
#define _ATOMICOPS_H_INCLUDED

#include <stdint.h>

typedef int32_t Atomic32;

// Atomic32 atomic_load_acquire(volatile Atomic32 *ptr);
// void atomic_store_release(volatile Atomic32 *ptr, Atomic32 value);
// Atomic32 atomic_compare_and_swap(volatile Atomic32 *ptr, Atomic32 old_value, Atomic32 new_value);

#ifdef _WIN32 // msvc
#include <intrin.h>



inline Atomic32 atomic_load_acquire(volatile Atomic32 *ptr)
{
    Atomic32 value = *ptr;
    return value;
}

inline void atomic_store_release(volatile Atomic32 *ptr, Atomic32 value)
{
    *ptr = value;
}

inline Atomic32 atomic_compare_and_swap(volatile Atomic32 *ptr,
                                        Atomic32 old_value,
                                        Atomic32 new_value)
{
    long result = _InterlockedCompareExchange(
        reinterpret_cast<volatile long*>(ptr),
        static_cast<long>(new_value),
        static_cast<long>(old_value));
    return static_cast<Atomic32>(result);
}

#else   // gcc

inline void memory_barrier()
{
    __sync_synchronize();
}

inline Atomic32 atomic_load_acquire(volatile Atomic32 *ptr)
{
    Atomic32 value = *ptr;
    memory_barrier();
    return value;
}

inline void atomic_store_release(volatile Atomic32 *ptr, Atomic32 value)
{
    memory_barrier();
    *ptr = value;
}

inline Atomic32 atomic_compare_and_swap(volatile Atomic32 *ptr,
                                        Atomic32 old_value,
                                        Atomic32 new_value)
{
    return __sync_val_compare_and_swap(ptr, old_value, new_value);
}

#endif


#endif // !_ATOMICOPS_H_INCLUDED