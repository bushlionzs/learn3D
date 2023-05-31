#ifndef __OBJECT_INDEX_H__
#define __OBJECT_INDEX_H__

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <platform_mutex.h>
#include <scoped_lock.h>

template<typename T>
class CObjectMgr
{
public:
	CObjectMgr( uint8_t bit )
	{
		if( bit > 24 )
			bit = 24;
		if( bit < 8 )
			bit = 8;
		_max_index_count = 1 << bit;
		_index_mask = _max_index_count - 1;
		_index_array = (T**)malloc(_max_index_count*sizeof(T*));
		memset( _index_array , 0 , sizeof(T*) * _max_index_count );
		_next_alloc_index = 1;
		_magic = 0;
		_magic_bit = bit;
		_magic_mask = 1 << (32-bit);
	}
	
	~CObjectMgr()
	{
		free(_index_array);
	}
	
	uint32_t alloc_and_set(T* object)
	{
        //ScopedLock<PlatformMutex> lock(_mutex);
		uint32_t index = _find_free_index();
		if( index == 0 )
			return 0;
		uint32_t handle = ( _magic << _magic_bit ) | index;
		_magic++;
		_magic |= _magic_mask;
		_index_array[index] = object;
		return handle;
	}
	
	T* get_object(uint32_t handle)
	{
		uint32_t index = handle & _index_mask;
        //ScopedLock<PlatformMutex> lock(_mutex);
		T* object = _index_array[index];
		if( 0 == object )
			return 0;
		return object;
	}
	
	T* release_object( uint32_t handle )
	{
		uint32_t index = handle & _index_mask;
        //ScopedLock<PlatformMutex> lock(_mutex);
		T* object = _index_array[index];
		if( 0 == object )
			return 0;
		_index_array[index] = 0;
		return object;
	}
private:
	uint32_t _find_free_index()
	{
		for( uint32_t i = _next_alloc_index; i < _max_index_count; i++ )
		{
			if( _index_array[i] == 0 )
            {   
                _next_alloc_index = i + 1;
                if (_next_alloc_index > _max_index_count)
                {
                    _next_alloc_index = 1;
                }
				return i;
            }
		}
		for( uint32_t i = 1; i < _next_alloc_index-1; i++ )
		{
			if( _index_array[i] == 0 )
				return i;
		}
		return 0;
	}
private:
	uint32_t _max_index_count;
	uint32_t _magic_bit;
	uint32_t _magic;
	uint32_t _magic_mask;
	uint32_t _index_mask;
	T** _index_array;
	uint32_t _next_alloc_index;
    PlatformMutex _mutex;
};
#endif //__OBJECT_INDEX_H__
