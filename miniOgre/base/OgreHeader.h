#pragma once
#include <WinSock2.h>
#include <windows.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <stdint.h>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <deque>
#include <limits>
#include<cstddef>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<ctime>
#include<cuchar>    
#include<cwchar>
#include <algorithm>
#include <array>
#include <assert.h>


typedef uint16_t ushort;
typedef uint64_t uint64;
typedef uint32_t uint32;
typedef int32_t int32;
typedef uint16_t uint16;
typedef int16_t int16;
typedef uint8_t uint8;
typedef int8_t int8;
typedef float Real;
typedef unsigned char uchar;
typedef unsigned long ulong;
typedef std::string String;

#include "OgreException.h"
#define ReleaseCOM(x) { if(x){ x->Release(); x = 0; } }

namespace filament
{
    class Engine;
    class IndexBuffer;
    class VertexBuffer;
    class Texture;

}

using namespace filament;

namespace Ogre
{
    class Degree;
    class Quaternion;
    class Radian;
    class Ray;
    class Plane;
    class Sphere;
    class AxisAlignedBox;
    class Affine3;
    class Matrix3;
    class Matrix4;
    class Vector2;
    class Vector3;
    class Vector4;
    class RenderWindow;
    class ParticleSystem;
    class DataStream;
    class MemoryDataStream;
    class Serializer;
    class Material;
    class Renderable;
    class Node;
    class SceneNode;
    class SceneManager;
    class ICamera;
    class Camera;
    class MoveObject;
    class Light;
    class RenderQueue;
    class Skeleton;
    class Animation;
    class Bone;
    class Resource;
    class HardwareVertexBuffer;
    class HardwarePixelBuffer;
    class Archive;
    class Mesh;
    class SubMesh;
    class Entity;
    class SubEntity;
    class AnimationState;
    class AnimationStateSet;
    class Frustum;
    class MovablePlane;
    class ManualResourceLoader;
    class ResourceManager;
    class RibbonTrail;
    class OgreTexture;
    class RenderTarget;
    class Viewport;
    class RenderTargetListener;
    class Timer;
    class DepthBuffer;
    class SkeletonInstance;
    class FrameListener;
    class CImage;
    class BillboardSet;
    class Timer;
    class ScriptLoader;
    struct FileInfo;
    typedef std::pair<bool, Real> RayTestResult;
    typedef std::shared_ptr<Ogre::DataStream> DataStreamPtr;
    typedef std::shared_ptr<Ogre::Material> MaterialPtr;
    typedef std::shared_ptr<Ogre::Skeleton> SkeletonPtr;
    typedef std::shared_ptr<Ogre::Mesh> MeshPtr;
    typedef std::shared_ptr<Ogre::OgreTexture> TexturePtr;
    typedef std::shared_ptr<MemoryDataStream> MemoryDataStreamPtr;
    typedef std::shared_ptr<Ogre::HardwareVertexBuffer> HardwareVertexBufferSharedPtr;
    typedef std::vector<std::string> StringVector;
    typedef std::shared_ptr<StringVector> StringVectorPtr;
    typedef std::set<std::string> OStringSet;
    typedef std::shared_ptr<Resource> ResourcePtr;
    typedef std::map <std::string, ResourcePtr> OResourcePtrMap;
    typedef std::vector<FileInfo> FileInfoList;
    typedef std::shared_ptr<FileInfoList> FileInfoListPtr;
    typedef std::shared_ptr<HardwarePixelBuffer> HardwarePixelBufferPtr;
    enum AnimationType
    {
        AT_FULL,
        AT_FROZE,
        AT_DISABLE,
    };
    typedef float Real;
    typedef std::string String;
}

#define DECL_MALLOC 
#define OGRE_ARCHITECTURE_64 2
#define OGRE_ARCH_TYPE OGRE_ARCHITECTURE_64
#define OGRE_MEMORY_ALLOCATOR_STD 1
#define OGRE_MEMORY_ALLOCATOR OGRE_MEMORY_ALLOCATOR_STD
#define OGRE_COMPILER_MSVC 1
#define OGRE_COMPILER OGRE_COMPILER_MSVC
#define OGRE_SIMD_ALIGNMENT  16
#define RESTRICT_ALIAS __restrict

#include "OgreMemoryAllocatorConfig.h"
#include "OgreMath.h"
#include "OgreVector2.h"
#include "OgreVector3.h"
#include "OgreVector4.h"
#include "OgreMatrix3.h"
#include "OgreMatrix4.h"
#include "OgreAxisAlignedBox.h"
#include "OgreQuaternion.h"
#include "OgrePlane.h"
#include "OgreSphere.h"
#include "OgreRay.h"
#include "OgreMemoryStream.h"
#include "platform_log.h"




typedef std::map<String, String> NameValuePairList;
const String BLANKSTRING;

#define _OrphigineExport
#define DECLARE_SCRIPT_RESOURCE
#define OGRE_AUTO_MUTEX
#define OGRE_LOCK_AUTO_MUTEX
#define OGRE_MUTEX(...)
#define OGRE_LOCK_MUTEX(...)

#define OGRE_CHECK(expr, data) if(!expr)OGRE_EXCEPT(Ogre::Exception::ERR_INTERNAL_ERROR, data)

using namespace Ogre;

