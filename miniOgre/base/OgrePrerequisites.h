/*-------------------------------------------------------------------------
This source file is a part of OGRE
(Object-oriented Graphics Rendering Engine)

For the latest info, see http://www.ogre3d.org/

Copyright (c) 2000-2014 Torus Knot Software Ltd
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE
-------------------------------------------------------------------------*/
#ifndef __OgrePrerequisites_H__
#define __OgrePrerequisites_H__

// Platform-specific stuff
#include <deque>
#include "OgreMemorySTLAllocator.h"
#include "OgreMemoryAllocatorConfig.h"

// configure memory tracking
#if OGRE_DEBUG_MODE 
#   if OGRE_MEMORY_TRACKER_DEBUG_MODE
#       define OGRE_MEMORY_TRACKER 1
#   else
#       define OGRE_MEMORY_TRACKER 0
#   endif
#else
#   if OGRE_MEMORY_TRACKER_RELEASE_MODE
#       define OGRE_MEMORY_TRACKER 1
#   else
#       define OGRE_MEMORY_TRACKER 0
#   endif
#endif

namespace Ogre {
    // Define ogre version
    #define OGRE_VERSION_MAJOR 2
    #define OGRE_VERSION_MINOR 1
    #define OGRE_VERSION_PATCH 0
    #define OGRE_VERSION_SUFFIX ""
    #define OGRE_VERSION_NAME "Baldur"

    #define OGRE_VERSION    ((OGRE_VERSION_MAJOR << 16) | (OGRE_VERSION_MINOR << 8) | OGRE_VERSION_PATCH)

    // define the real number values to be used
    // default to use 'float' unless precompiler option set
    #if OGRE_DOUBLE_PRECISION == 1
        /** Software floating point type.
        @note Not valid as a pointer to GPU buffers / parameters
        */
        typedef double Real;
        typedef uint64 RealAsUint;
    #else
        /** Software floating point type.
        @note Not valid as a pointer to GPU buffers / parameters
        */
        typedef float Real;
        typedef uint32 RealAsUint;
    #endif

    #if OGRE_COMPILER == OGRE_COMPILER_GNUC && OGRE_COMP_VER >= 310 && !defined(STLPORT)
    #   if OGRE_COMP_VER >= 430
    #       if __cplusplus >= 201103L
    #           define OGRE_HASH_NAMESPACE ::std
    #       else
    #           define OGRE_HASH_NAMESPACE ::std::tr1
    #       endif
    #       define OGRE_HASHMAP_NAME unordered_map
    #       define OGRE_HASHMULTIMAP_NAME unordered_multimap
    #       define OGRE_HASHSET_NAME unordered_set
    #       define OGRE_HASHMULTISET_NAME unordered_multiset
    #    else
    #       define OGRE_HASH_NAMESPACE ::__gnu_cxx
    #       define OGRE_HASHMAP_NAME hash_map
    #       define OGRE_HASHMULTIMAP_NAME hash_multimap
    #       define OGRE_HASHSET_NAME hash_set
    #       define OGRE_HASHMULTISET_NAME hash_multiset
    #    endif
    #elif OGRE_COMPILER == OGRE_COMPILER_CLANG
    #       define OGRE_HASHMAP_NAME unordered_map
    #       define OGRE_HASHMULTIMAP_NAME unordered_multimap
    #       define OGRE_HASHSET_NAME unordered_set
    #       define OGRE_HASHMULTISET_NAME unordered_multiset
    #    if defined(_LIBCPP_VERSION) || __cplusplus >= 201103L
    #       define OGRE_HASH_NAMESPACE ::std
    #    else
    #       define OGRE_HASH_NAMESPACE ::std::tr1
    #    endif
    #else
    #   if OGRE_COMPILER == OGRE_COMPILER_MSVC && !defined(_STLP_MSVC)
    #       define OGRE_HASHMAP_NAME unordered_map
    #       define OGRE_HASHMULTIMAP_NAME unordered_multimap
    #       define OGRE_HASHSET_NAME unordered_set
    #       define OGRE_HASHMULTISET_NAME unordered_multiset
    #       if _MSC_VER >= 1900 // VC++ 2015
    #           define OGRE_HASH_NAMESPACE ::std
    #       elif _MSC_FULL_VER >= 150030729 // VC++ 9.0/2008 SP1+
    #           define OGRE_HASH_NAMESPACE ::std::tr1
    #       elif OGRE_THREAD_PROVIDER == 1
    #           define OGRE_HASH_NAMESPACE ::boost
    #       endif
    #   else
    #       define OGRE_HASH_NAMESPACE ::std
    #       define OGRE_HASHMAP_NAME unordered_map
    #       define OGRE_HASHMULTIMAP_NAME unordered_multimap
    #       define OGRE_HASHSET_NAME unordered_set
    #       define OGRE_HASHMULTISET_NAME unordered_multiset
    #   endif
    #endif

    /** In order to avoid finger-aches :)
    */
    typedef unsigned char uchar;
    typedef unsigned short ushort;
    typedef unsigned int uint;
    typedef unsigned long ulong;

    #if __cplusplus >= 201103L
    #define register
    #endif
// Pre-declare classes
// Allows use of pointers in header files without including individual .h
// so decreases dependencies between files
}

/* Include all the standard header *after* all the configuration
settings have been made.
*/
//#include "OgreStdHeaders.h"
//#include "OgreMemoryAllocatorConfig.h"


namespace Ogre
{
#if OGRE_STRING_USE_CUSTOM_MEMORY_ALLOCATOR
    #if OGRE_WCHAR_T_STRINGS
        typedef std::basic_string<wchar_t, std::char_traits<wchar_t>, STLAllocator<wchar_t,GeneralAllocPolicy > >   _StringBase;
    #else
        typedef std::basic_string<char, std::char_traits<char>, STLAllocator<char,GeneralAllocPolicy > >    _StringBase;
    #endif

    #if OGRE_WCHAR_T_STRINGS
        typedef std::basic_stringstream<wchar_t,std::char_traits<wchar_t>,STLAllocator<wchar_t,GeneralAllocPolicy >> _StringStreamBase;
    #else
        typedef std::basic_stringstream<char,std::char_traits<char>,STLAllocator<char,GeneralAllocPolicy > > _StringStreamBase;
    #endif

    #define StdStringT(T) std::basic_string<T, std::char_traits<T>, std::allocator<T> > 
    #define CustomMemoryStringT(T) std::basic_string<T, std::char_traits<T>, STLAllocator<T,GeneralAllocPolicy> >   

    template<typename T>
    bool operator <(const CustomMemoryStringT(T)& l,const StdStringT(T)& o)
    {
        return l.compare(0,l.length(),o.c_str(),o.length())<0;
    }
    template<typename T>
    bool operator <(const StdStringT(T)& l,const CustomMemoryStringT(T)& o)
    {
        return l.compare(0,l.length(),o.c_str(),o.length())<0;
    }
    template<typename T>
    bool operator <=(const CustomMemoryStringT(T)& l,const StdStringT(T)& o)
    {
        return l.compare(0,l.length(),o.c_str(),o.length())<=0;
    }
    template<typename T>
    bool operator <=(const StdStringT(T)& l,const CustomMemoryStringT(T)& o)
    {
        return l.compare(0,l.length(),o.c_str(),o.length())<=0;
    }
    template<typename T>
    bool operator >(const CustomMemoryStringT(T)& l,const StdStringT(T)& o)
    {
        return l.compare(0,l.length(),o.c_str(),o.length())>0;
    }
    template<typename T>
    bool operator >(const StdStringT(T)& l,const CustomMemoryStringT(T)& o)
    {
        return l.compare(0,l.length(),o.c_str(),o.length())>0;
    }
    template<typename T>
    bool operator >=(const CustomMemoryStringT(T)& l,const StdStringT(T)& o)
    {
        return l.compare(0,l.length(),o.c_str(),o.length())>=0;
    }
    template<typename T>
    bool operator >=(const StdStringT(T)& l,const CustomMemoryStringT(T)& o)
    {
        return l.compare(0,l.length(),o.c_str(),o.length())>=0;
    }

    template<typename T>
    bool operator ==(const CustomMemoryStringT(T)& l,const StdStringT(T)& o)
    {
        return l.compare(0,l.length(),o.c_str(),o.length())==0;
    }
    template<typename T>
    bool operator ==(const StdStringT(T)& l,const CustomMemoryStringT(T)& o)
    {
        return l.compare(0,l.length(),o.c_str(),o.length())==0;
    }

    template<typename T>
    bool operator !=(const CustomMemoryStringT(T)& l,const StdStringT(T)& o)
    {
        return l.compare(0,l.length(),o.c_str(),o.length())!=0;
    }
    template<typename T>
    bool operator !=(const StdStringT(T)& l,const CustomMemoryStringT(T)& o)
    {
        return l.compare(0,l.length(),o.c_str(),o.length())!=0;
    }

    template<typename T>
    CustomMemoryStringT(T) operator +=(const CustomMemoryStringT(T)& l,const StdStringT(T)& o)
    {
        return CustomMemoryStringT(T)(l)+=o.c_str();
    }
    template<typename T>
    CustomMemoryStringT(T) operator +=(const StdStringT(T)& l,const CustomMemoryStringT(T)& o)
    {
        return CustomMemoryStringT(T)(l.c_str())+=o.c_str();
    }

    template<typename T>
    CustomMemoryStringT(T) operator +(const CustomMemoryStringT(T)& l,const StdStringT(T)& o)
    {
        return CustomMemoryStringT(T)(l)+=o.c_str();
    }

    template<typename T>
    CustomMemoryStringT(T) operator +(const StdStringT(T)& l,const CustomMemoryStringT(T)& o)
    {
        return CustomMemoryStringT(T)(l.c_str())+=o.c_str();
    }

    template<typename T>
    CustomMemoryStringT(T) operator +(const T* l,const CustomMemoryStringT(T)& o)
    {
        return CustomMemoryStringT(T)(l)+=o;
    }

    #undef StdStringT
    #undef CustomMemoryStringT

#else
    #if OGRE_WCHAR_T_STRINGS
        typedef std::wstring _StringBase;
    #else
        typedef std::string _StringBase;
    #endif

    #if OGRE_WCHAR_T_STRINGS
        typedef std::basic_stringstream<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t> > _StringStreamBase;
    #else
        typedef std::basic_stringstream<char,std::char_traits<char>,std::allocator<char> > _StringStreamBase;
    #endif

#endif

    typedef _StringBase String;
    typedef _StringStreamBase StringStream;
    typedef StringStream stringstream;

}

#if OGRE_STRING_USE_CUSTOM_MEMORY_ALLOCATOR 
namespace std 
{
#if (OGRE_COMPILER == OGRE_COMPILER_GNUC && OGRE_COMP_VER >= 430) || OGRE_COMPILER == OGRE_COMPILER_CLANG && !defined(STLPORT) && __cplusplus < 201103L
    namespace tr1
    {
#endif
    template <> struct hash<Ogre::String>
    {
    public :
        size_t operator()(const Ogre::String &str ) const
        {
            size_t _Val = 2166136261U;
            size_t _First = 0;
            size_t _Last = str.size();
            size_t _Stride = 1 + _Last / 10;

            for(; _First < _Last; _First += _Stride)
                _Val = 16777619U * _Val ^ (size_t)str[_First];
            return (_Val);
        }
    };
#if (OGRE_COMPILER == OGRE_COMPILER_GNUC && OGRE_COMP_VER >= 430) || OGRE_COMPILER == OGRE_COMPILER_CLANG && !defined(STLPORT) && __cplusplus < 201103L
    }
#endif
}
#endif

//for stl container
namespace Ogre
{ 
    template <typename T, typename A = STLAllocator<T, GeneralAllocPolicy> > 
    struct deque 
    { 
#if OGRE_CONTAINERS_USE_CUSTOM_MEMORY_ALLOCATOR
        typedef typename std::deque<T, A> type;    
        typedef typename std::deque<T, A>::iterator iterator;
        typedef typename std::deque<T, A>::const_iterator const_iterator;
#else
        typedef typename std::deque<T> type;
        typedef typename std::deque<T>::iterator iterator;
        typedef typename std::deque<T>::const_iterator const_iterator;
#endif
    }; 

    template <typename T, typename A = STLAllocator<T, GeneralAllocPolicy> > 
    struct vector 
    { 
#if OGRE_CONTAINERS_USE_CUSTOM_MEMORY_ALLOCATOR
        typedef typename std::vector<T, A> type;
        typedef typename std::vector<T, A>::iterator iterator;
        typedef typename std::vector<T, A>::const_iterator const_iterator;
#else
        typedef typename std::vector<T> type;
        typedef typename std::vector<T>::iterator iterator;
        typedef typename std::vector<T>::const_iterator const_iterator;
#endif
    }; 

    template <typename T, typename A = STLAllocator<T, GeneralAllocPolicy> > 
    struct list 
    { 
#if OGRE_CONTAINERS_USE_CUSTOM_MEMORY_ALLOCATOR
        typedef typename std::list<T, A> type;
        typedef typename std::list<T, A>::iterator iterator;
        typedef typename std::list<T, A>::const_iterator const_iterator;
#else
        typedef typename std::list<T> type;
        typedef typename std::list<T>::iterator iterator;
        typedef typename std::list<T>::const_iterator const_iterator;
#endif
    }; 

    template <typename T, typename P = std::less<T>, typename A = STLAllocator<T, GeneralAllocPolicy> > 
    struct set 
    { 
#if OGRE_CONTAINERS_USE_CUSTOM_MEMORY_ALLOCATOR
        typedef typename std::set<T, P, A> type;
        typedef typename std::set<T, P, A>::iterator iterator;
        typedef typename std::set<T, P, A>::const_iterator const_iterator;
#else
        typedef typename std::set<T, P> type;
        typedef typename std::set<T, P>::iterator iterator;
        typedef typename std::set<T, P>::const_iterator const_iterator;
#endif
    }; 

    template <typename K, typename V, typename P = std::less<K>, typename A = STLAllocator<std::pair<const K, V>, GeneralAllocPolicy> > 
    struct map 
    { 
#if OGRE_CONTAINERS_USE_CUSTOM_MEMORY_ALLOCATOR
        typedef typename std::map<K, V, P, A> type;
        typedef typename std::map<K, V, P, A>::iterator iterator;
        typedef typename std::map<K, V, P, A>::const_iterator const_iterator;
#else
        typedef typename std::map<K, V, P> type;
        typedef typename std::map<K, V, P>::iterator iterator;
        typedef typename std::map<K, V, P>::const_iterator const_iterator;
#endif
    }; 

    template <typename K, typename V, typename P = std::less<K>, typename A = STLAllocator<std::pair<const K, V>, GeneralAllocPolicy> > 
    struct multimap 
    { 
#if OGRE_CONTAINERS_USE_CUSTOM_MEMORY_ALLOCATOR
        typedef typename std::multimap<K, V, P, A> type;
        typedef typename std::multimap<K, V, P, A>::iterator iterator;
        typedef typename std::multimap<K, V, P, A>::const_iterator const_iterator;
#else
        typedef typename std::multimap<K, V, P> type;
        typedef typename std::multimap<K, V, P>::iterator iterator;
        typedef typename std::multimap<K, V, P>::const_iterator const_iterator;
#endif
    }; 

    template <typename K, typename V, typename H = OGRE_HASH_NAMESPACE::hash<K>, typename E = std::equal_to<K>, typename A = STLAllocator<std::pair<const K, V>, GeneralAllocPolicy> >
    struct unordered_map
    { 
#if OGRE_CONTAINERS_USE_CUSTOM_MEMORY_ALLOCATOR
        typedef typename OGRE_HASH_NAMESPACE::OGRE_HASHMAP_NAME<K, V, H, E, A> type;
#else
        typedef typename OGRE_HASH_NAMESPACE::OGRE_HASHMAP_NAME<K, V, H, E> type;
#endif
        typedef typename type::iterator iterator;
        typedef typename type::const_iterator const_iterator;
    };

    template <typename K, typename V, typename H = OGRE_HASH_NAMESPACE::hash<K>, typename E = std::equal_to<K>, typename A = STLAllocator<std::pair<const K, V>, GeneralAllocPolicy> >
    struct unordered_multimap
    { 
#if OGRE_CONTAINERS_USE_CUSTOM_MEMORY_ALLOCATOR
        typedef typename OGRE_HASH_NAMESPACE::OGRE_HASHMULTIMAP_NAME<K, V, H, E, A> type;
#else
        typedef typename OGRE_HASH_NAMESPACE::OGRE_HASHMULTIMAP_NAME<K, V, H, E> type;
#endif
        typedef typename type::iterator iterator;
        typedef typename type::const_iterator const_iterator;
    };

    template <typename K, typename H = OGRE_HASH_NAMESPACE::hash<K>, typename E = std::equal_to<K>, typename A = STLAllocator<K, GeneralAllocPolicy> >
    struct unordered_set
    { 
#if OGRE_CONTAINERS_USE_CUSTOM_MEMORY_ALLOCATOR
        typedef typename OGRE_HASH_NAMESPACE::OGRE_HASHSET_NAME<K, H, E, A> type;
#else
        typedef typename OGRE_HASH_NAMESPACE::OGRE_HASHSET_NAME<K, H, E> type;
#endif
        typedef typename type::iterator iterator;
        typedef typename type::const_iterator const_iterator;
    };

    template <typename K, typename H = OGRE_HASH_NAMESPACE::hash<K>, typename E = std::equal_to<K>, typename A = STLAllocator<K, GeneralAllocPolicy> >
    struct unordered_multiset
    { 
#if OGRE_CONTAINERS_USE_CUSTOM_MEMORY_ALLOCATOR
        typedef typename OGRE_HASH_NAMESPACE::OGRE_HASHMULTISET_NAME<K, H, E, A> type;
#else
        typedef typename OGRE_HASH_NAMESPACE::OGRE_HASHMULTISET_NAME<K, H, E> type;
#endif
        typedef typename type::iterator iterator;
        typedef typename type::const_iterator const_iterator;
    };

} // Ogre


#endif // __OgrePrerequisites_H__


