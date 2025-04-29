/*
-----------------------------------------------------------------------------
This source file is part of OGRE
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
THE SOFTWARE.
-----------------------------------------------------------------------------
*/
#pragma once
// Common stuff

#include <map>


#if OGRE_CPU == OGRE_CPU_X86
    #include <xmmintrin.h>
    #include <emmintrin.h>
#elif OGRE_CPU == OGRE_CPU_ARM && OGRE_USE_SIMD
    #include <arm_neon.h>
#endif

#if defined ( OGRE_GCC_VISIBILITY )
#   pragma GCC visibility push(default)
#endif

#if defined ( OGRE_GCC_VISIBILITY )
#   pragma GCC visibility pop
#endif



class VertexDeclaration;
namespace Ogre {
    

    /// Fast general hashing algorithm
    inline uint32_t FastHash (const char * data, int len, uint32_t hashSoFar = 0) {
        assert_invariant(false);
        /*uint32 ret;
        MurmurHash3_x86_32(data, len, hashSoFar, &ret);
        return ret;*/
        return 0;
    }
    /// Combine hashes with same style as boost::hash_combine
    template <typename T>
    uint32_t HashCombine (uint32_t hashSoFar, const T& data)
    {
        return FastHash((const char*)&data, sizeof(T), hashSoFar);
    }

    template <typename T>
    class BitField {
        int64_t value = 0;

    public:
        __forceinline BitField<T>& set_flag(T p_flag) {
            value |= (int64_t)p_flag;
            return *this;
        }
        __forceinline bool has_flag(T p_flag) const { return value & (int64_t)p_flag; }
        __forceinline bool is_empty() const { return value == 0; }
        __forceinline void clear_flag(T p_flag) { value &= ~(int64_t)p_flag; }
        __forceinline void clear() { value = 0; }
        __forceinline constexpr BitField() = default;
        __forceinline constexpr BitField(int64_t p_value) { value = p_value; }
        __forceinline constexpr BitField(T p_value) { value = (int64_t)p_value; }
        __forceinline operator int64_t() const { return value; }
       // __forceinline operator Variant() const { return value; }
        __forceinline BitField<T> operator^(const BitField<T>& p_b) const { return BitField<T>(value ^ p_b.value); }
    };

    enum ImageType : uint8_t {
        ImageType_UnSupported,
        ImageType_PNG,
        ImageType_JPG,
        ImageType_DDS,
        ImageType_BLP,
        ImageType_KTX,
        ImageType_TIF,
        ImageType_TGA
    };

    enum VertexPass
    {
        VpNormal,
        VpShadow,
        NumVertexPass
    };

    enum PrePassMode
    {
        /// This is a normal pass.
        PrePassNone,
        /// This is a depth pre-pass. Note: Implementations may write
        /// to colour too for hybrid deferred & forward rendering.
        PrePassCreate,
        /// This pass will be using the results of a previous pre-pass
        PrePassUse
    };

    enum OperationType
    {
        /// A list of points, 1 vertex per point
        OT_POINT_LIST = 1,
        /// A list of lines, 2 vertices per line
        OT_LINE_LIST = 2,
        /// A strip of connected lines, 1 vertex per line plus 1 start vertex
        OT_LINE_STRIP = 3,
        /// A list of triangles, 3 vertices per triangle
        OT_TRIANGLE_LIST = 4,
        /// A strip of triangles, 3 vertices for the first triangle, and 1 per triangle after that
        OT_TRIANGLE_STRIP = 5,
        /// A fan of triangles, 3 vertices for the first triangle, and 1 per triangle after that
        OT_TRIANGLE_FAN = 6
    };
    /** Comparison functions used for the depth/stencil buffer operations and 
        others. */
    enum CompareFunction
    {
        CMPF_ALWAYS_FAIL,
        CMPF_ALWAYS_PASS,
        CMPF_LESS,
        CMPF_LESS_EQUAL,
        CMPF_EQUAL,
        CMPF_NOT_EQUAL,
        CMPF_GREATER_EQUAL,
        CMPF_GREATER,
        NUM_COMPARE_FUNCTIONS,
    };

    /// Enum describing the various actions which can be taken on the stencil buffer
    enum StencilOperation
    {
        /// Leave the stencil buffer unchanged
        SOP_KEEP,
        /// Set the stencil value to zero
        SOP_ZERO,
        /// Set the stencil value to the reference value
        SOP_REPLACE,
        /// Increase the stencil value by 1, clamping at the maximum value
        SOP_INCREMENT,
        /// Decrease the stencil value by 1, clamping at 0
        SOP_DECREMENT,
        /// Increase the stencil value by 1, wrapping back to 0 when incrementing the maximum value
        SOP_INCREMENT_WRAP,
        /// Decrease the stencil value by 1, wrapping when decrementing 0
        SOP_DECREMENT_WRAP,
        /// Invert the bits of the stencil buffer
        SOP_INVERT
    };


    /** Texture addressing modes - default is TAM_WRAP.
    */
    enum TextureAddressingMode : uint8_t
    {
        /// %Any value beyond 1.0 wraps back to 0.0. %Texture is repeated.
        TAM_WRAP,
        /// %Texture flips every boundary, meaning texture is mirrored every 1.0 u or v
        TAM_MIRROR,
        /// Values beyond 1.0 are clamped to 1.0. %Texture ¡¯streaks¡¯ beyond 1.0 since last line
        /// of pixels is used across the rest of the address space. Useful for textures which
        /// need exact coverage from 0.0 to 1.0 without the ¡¯fuzzy edge¡¯ wrap gives when
        /// combined with filtering.
        TAM_CLAMP,
        /// %Texture coordinates outside the range [0.0, 1.0] are set to the border colour.
        TAM_BORDER,
        /// Unknown
        TAM_UNKNOWN = 99
    };

    struct StencilStateOp
    {
        StencilOperation stencilFailOp;
        StencilOperation stencilPassOp;
        StencilOperation stencilDepthFailOp;
        CompareFunction compareOp;

        StencilStateOp() :
            stencilFailOp( SOP_KEEP ),
            stencilPassOp( SOP_KEEP ),
            stencilDepthFailOp( SOP_KEEP ),
            compareOp( CMPF_ALWAYS_FAIL ) {}

        bool operator < ( const StencilStateOp &other ) const
        {
            if(   this->stencilFailOp < other.stencilFailOp  ) return true;
            if( !(this->stencilFailOp < other.stencilFailOp) ) return false;

            if(   this->stencilPassOp < other.stencilPassOp  ) return true;
            if( !(this->stencilPassOp < other.stencilPassOp) ) return false;

            if(   this->stencilDepthFailOp < other.stencilDepthFailOp  ) return true;
            if( !(this->stencilDepthFailOp < other.stencilDepthFailOp) ) return false;

            if(   this->compareOp < other.compareOp  ) return true;
            //if( !(this->compareOp < other.compareOp) ) return false;

            return false;
        }

        bool operator != ( const StencilStateOp &other ) const
        {
            return this->stencilFailOp != other.stencilFailOp ||
                   this->stencilPassOp != other.stencilPassOp ||
                   this->stencilDepthFailOp != other.stencilDepthFailOp ||
                   this->compareOp != other.compareOp;
        }
    };

    ///@see HlmsPso regarding padding.
    struct StencilParams
    {
        bool            enabled;
        uint8           readMask;
        uint8           writeMask;
        uint8           padding;
        StencilStateOp  stencilFront;
        StencilStateOp  stencilBack;

        StencilParams() :
            enabled( false ),
            readMask( 0xFF ),
            writeMask( 0xFF ),
            padding( 0 ) {}

        bool operator < ( const StencilParams &other ) const
        {
            if(   this->enabled < other.enabled  ) return true;
            if( !(this->enabled < other.enabled) ) return false;

            if(   this->readMask < other.readMask  ) return true;
            if( !(this->readMask < other.readMask) ) return false;

            if(   this->stencilFront < other.stencilFront  ) return true;
            if( !(this->stencilFront < other.stencilFront) ) return false;

            if(   this->stencilBack < other.stencilBack  ) return true;
            //if( !(this->stencilBack < other.stencilBack) ) return false;

            return false;
        }

        bool operator != ( const StencilParams &other ) const
        {
            return this->enabled != other.enabled ||
                   this->readMask != other.readMask ||
                   this->writeMask != other.writeMask ||
                   this->stencilFront != other.stencilFront ||
                   this->stencilBack != other.stencilBack;
        }
    };

    /** High-level filtering options providing shortcuts to settings the
        minification, magnification and mip filters. */
    enum TextureFilterOptions
    {
        /// Equal to: min=FO_POINT, mag=FO_POINT, mip=FO_NONE
        TFO_NONE,
        /// Equal to: min=FO_LINEAR, mag=FO_LINEAR, mip=FO_POINT
        TFO_BILINEAR,
        /// Equal to: min=FO_LINEAR, mag=FO_LINEAR, mip=FO_LINEAR
        TFO_TRILINEAR,
        /// Equal to: min=FO_ANISOTROPIC, max=FO_ANISOTROPIC, mip=FO_LINEAR
        TFO_ANISOTROPIC
    };

    enum FilterType
    {
        /// The filter used when shrinking a texture
        FT_MIN,
        /// The filter used when magnifying a texture
        FT_MAG,
        /// The filter used when determining the mipmap
        FT_MIP
    };
    /** Filtering options for textures / mipmaps. */
    enum FilterOptions
    {
        /// No filtering, used for FT_MIP to turn off mipmapping
        FO_NONE,
        /// Use the closest pixel
        FO_POINT,
        /// Average of a 2x2 pixel area, denotes bilinear for MIN and MAG, trilinear for MIP
        FO_LINEAR,
        /// Similar to FO_LINEAR, but compensates for the angle of the texture plane
        FO_ANISOTROPIC
    };

    /** Light shading modes. DEPRECATED */
    enum ShadeOptions
    {
        SO_FLAT,
        SO_GOURAUD,
        SO_PHONG
    };

    /** Fog modes. */
    enum FogMode
    {
        /// No fog. Duh.
        FOG_NONE,
        /// Fog density increases  exponentially from the camera (fog = 1/e^(distance * density))
        FOG_EXP,
        /// Fog density increases at the square of FOG_EXP, i.e. even quicker (fog = 1/e^(distance * density)^2)
        FOG_EXP2,
        /// Fog density increases linearly between the start and end distances
        FOG_LINEAR
    };

    
    enum CullingMode
    {
        /// Hardware never culls triangles and renders everything it receives.
        CULL_MODE_NONE = 0,
        /// Hardware culls triangles whose vertices are listed clockwise in the view (default).
        CULL_MODE_FRONT = 1,
        /// Hardware culls triangles whose vertices are listed anticlockwise in the view.
        CULL_MODE_BACK = 2
    };

    /** Enumerates the wave types usable with the Ogre engine. */
    enum WaveformType
    {
        /// Standard sine wave which smoothly changes from low to high and back again.
        WFT_SINE,
        /// An angular wave with a constant increase / decrease speed with pointed peaks.
        WFT_TRIANGLE,
        /// Half of the time is spent at the min, half at the max with instant transition between.
        WFT_SQUARE,
        /// Gradual steady increase from min to max over the period with an instant return to min at the end.
        WFT_SAWTOOTH,
        /// Gradual steady decrease from max to min over the period, with an instant return to max at the end.
        WFT_INVERSE_SAWTOOTH,
        /// Pulse Width Modulation. Works like WFT_SQUARE, except the high to low transition is controlled by duty cycle. 
        /// With a duty cycle of 50% (0.5) will give the same output as WFT_SQUARE.
        WFT_PWM
    };

    /** The polygon mode to use when rasterising. */
    enum PolygonMode
    {
        /// Only points are rendered.
        PM_POINTS = 1,
        /// Wireframe models are rendered.
        PM_WIREFRAME = 2,
        /// Solid polygons are rendered.
        PM_SOLID = 3
    };

    enum MaterialFlagBits
    {
        MATERIAL_FLAG_NONE = 0,
        MATERIAL_FLAG_TWO_SIDED = (1 << 0),
        MATERIAL_FLAG_ALPHA_TESTED = (1 << 1),
        MATERIAL_FLAG_TRANSPARENT = (1 << 2),
        MATERIAL_FLAG_DOUBLE_VOXEL_SIZE = (1 << 3),
        MATERIAL_FLAG_ALL = MATERIAL_FLAG_TWO_SIDED | MATERIAL_FLAG_ALPHA_TESTED | MATERIAL_FLAG_DOUBLE_VOXEL_SIZE
    };

    /** An enumeration describing which material properties should track the vertex colours */
    typedef int TrackVertexColourType;
    enum TrackVertexColourEnum {
        TVC_NONE        = 0x0,
        TVC_AMBIENT     = 0x1,        
        TVC_DIFFUSE     = 0x2,
        TVC_SPECULAR    = 0x4,
        TVC_EMISSIVE    = 0x8
    };

    /** Sort mode for billboard-set and particle-system */
    enum SortMode
    {
        /** Sort by direction of the camera */
        SM_DIRECTION,
        /** Sort by distance from the camera */
        SM_DISTANCE
    };

    /** Defines the frame buffer types. */
    enum FrameBufferType {
        FBT_COLOUR  = 0x1,
        FBT_DEPTH   = 0x2,
        FBT_STENCIL = 0x4
    };
	
	/** Defines the colour buffer types. */
    enum ColourBufferType
    {
      CBT_BACK = 0x0,
      CBT_BACK_LEFT,
      CBT_BACK_RIGHT
    };
	
	/** Defines the stereo mode types. */
    enum StereoModeType
    {
      SMT_NONE = 0x0,
      SMT_FRAME_SEQUENTIAL
    };

    enum IndexType
    {
        INDEX_TYPE_UINT32 = 0,
        INDEX_TYPE_UINT16,
    };

    enum ShaderType
    {
        VertexShader,
        PixelShader,
        GeometryShader,
        ComputeShader,
        RayGenShader,
        MissShader,
        AnyHitShader,
        ClosestHitShader,
    };

    enum CubeType
    {
        CubeType_Irradiance  = 0,
        CubeType_Prefiltered = 1,
    };

    enum ResourceState {
        ResourceState_None,
        LOADING, // resource is loading.
        READY,    // resource is loaded completely.
    };

    enum CameraMoveType
    {
        CameraMoveType_FirstPerson = 0,
        CameraMoveType_LookAt = 1,

    };

    typedef enum QueueType
    {
        QUEUE_TYPE_GRAPHICS = 0,
        QUEUE_TYPE_TRANSFER,
        QUEUE_TYPE_COMPUTE,
        MAX_QUEUE_TYPE
    } QueueType;

    enum TextureBindType
    {
        TextureBindType_Image = 0,
        TextureBindType_Combined_Image_Sampler,
        TextureBindType_RW_Image
    };
    /** Flags for the Instance Manager when calculating ideal number of instances per batch */
    enum InstanceManagerFlags
    {
        /** Forces an amount of instances per batch low enough so that vertices * numInst < 65535
            since usually improves performance. In HW instanced techniques, this flag is ignored
        */
        IM_USE16BIT     = 0x0001,

        /** The num. of instances is adjusted so that as few pixels as possible are wasted
            in the vertex texture */
        IM_VTFBESTFIT   = 0x0002,

        /** Use a limited number of skeleton animations shared among all instances. 
        Update only that limited amount of animations in the vertex texture.*/
        IM_VTFBONEMATRIXLOOKUP = 0x0004,

        IM_USEBONEDUALQUATERNIONS = 0x0008,

        /** Use one weight per vertex when recommended (i.e. VTF). */
        IM_USEONEWEIGHT = 0x0010,

        /** All techniques are forced to one weight per vertex. */
        IM_FORCEONEWEIGHT = 0x0020,

        IM_USEALL       = IM_USE16BIT|IM_VTFBESTFIT|IM_USEONEWEIGHT
    };

    /** The types of NodeMemoryManager & ObjectMemoryManagers
    @remarks
        By default all objects are dynamic. Static objects can save a lot of performance on CPU side
        (and sometimes GPU side, for example with some instancing techniques) by telling the engine
        they won't be changing often.
    @par
        What it means for Nodes:
            Nodes created with SCENE_STATIC won't update their derived position/rotation/scale every
            frame.
            This means that modifying (eg) a static node position won't actually take effect until
            SceneManager::notifyStaticDirty( mySceneNode ) is called or some other similar call.

            If the static scene node is child of a dynamic parent node, modifying the dynamic node
            will not cause the static one to notice the change until explicitly notifying the
            SceneManager that the child node should be updated.

            If a static scene node is child of another static scene node, explicitly notifying the
            SceneManager of the parent's change automatically causes the child to be updated as well

            Having a dynamic node to be child of a static node is perfectly pausible and encouraged,
            for example a moving pendulum hanging from a static clock.
            Having a static node being child of a dynamic node doesn't make much sense, and is probably
            a bug (unless the parent is the root node).
    @par
        What it means for Entities (and InstancedEntities, etc)
            Static entities are scheduled for culling and rendering like dynamic ones, but won't update
            their world AABB bounds (even if their scene node they're attached to changes)
            
            Static entities will update their aabb if user calls
            SceneManager::notifyStaticDirty( myEntity ) or the static node they're attached to was also
            flagged as dirty. Note that updating the node's position doesn't flag the node as dirty
            (it's not implicit) and hence the entity won't be updated either.
            
            Static entities can only be attached to static nodes, and dynamic entities can only be
            attached to dynamic nodes.
    @par    
        Note that on most cases, changing a single static entity or node (or creating more) can cause
        a lot of other static objects to be scheduled to update, so don't do it often, and do it all
        in the same frame. An example is doing it at startup (i.e. during loading time)
    @par
        Entities & Nodes can switch between dynamic & static at runtime. However InstancedEntities can't.
        You need to destroy the InstancedEntity and create a new one if you wish to switch (which, by
        the way, isn't expensive because batches preallocate the instances)
        InstancedEntities with different SceneMemoryMgrTypes will never share the same batch.
    */
    enum SceneMemoryMgrTypes
    {
        SCENE_DYNAMIC = 0,
        SCENE_STATIC,
        NUM_SCENE_MEMORY_MANAGER_TYPES
    };
    
    /** A hashed vector.
    */
    template <typename T>
    class HashedVector
    {
    public:
        typedef std::vector<T, STLAllocator<T, GeneralAllocPolicy> > VectorImpl;
    protected:
        VectorImpl mList;
        mutable uint32 mListHash;
        mutable bool mListHashDirty;

        void addToHash(const T& newPtr) const
        {
            mListHash = FastHash((const char*)&newPtr, sizeof(T), mListHash);
        }
        void recalcHash() const
        {
            mListHash = 0;
            for (const_iterator i = mList.begin(); i != mList.end(); ++i)
                addToHash(*i);
            mListHashDirty = false;
            
        }

    public:
        typedef typename VectorImpl::value_type value_type;
        typedef typename VectorImpl::pointer pointer;
        typedef typename VectorImpl::reference reference;
        typedef typename VectorImpl::const_reference const_reference;
        typedef typename VectorImpl::size_type size_type;
        typedef typename VectorImpl::difference_type difference_type;
        typedef typename VectorImpl::iterator iterator;
        typedef typename VectorImpl::const_iterator const_iterator;
        typedef typename VectorImpl::reverse_iterator reverse_iterator;
        typedef typename VectorImpl::const_reverse_iterator const_reverse_iterator;

        void dirtyHash()
        {
            mListHashDirty = true;
        }
        bool isHashDirty() const
        {
            return mListHashDirty;
        }

        iterator begin() 
        { 
            // we have to assume that hash needs recalculating on non-const
            dirtyHash();
            return mList.begin(); 
        }
        iterator end() { return mList.end(); }
        const_iterator begin() const { return mList.begin(); }
        const_iterator end() const { return mList.end(); }
        reverse_iterator rbegin() 
        { 
            // we have to assume that hash needs recalculating on non-const
            dirtyHash();
            return mList.rbegin(); 
        }
        reverse_iterator rend() { return mList.rend(); }
        const_reverse_iterator rbegin() const { return mList.rbegin(); }
        const_reverse_iterator rend() const { return mList.rend(); }
        size_type size() const { return mList.size(); }
        size_type max_size() const { return mList.max_size(); }
        size_type capacity() const { return mList.capacity(); }
        bool empty() const { return mList.empty(); }
        reference operator[](size_type n) 
        { 
            // we have to assume that hash needs recalculating on non-const
            dirtyHash();
            return mList[n]; 
        }
        const_reference operator[](size_type n) const { return mList[n]; }
        reference at(size_type n) 
        { 
            // we have to assume that hash needs recalculating on non-const
            dirtyHash();
            return mList.const_iterator(n); 
        }
        const_reference at(size_type n) const { return mList.at(n); }
        HashedVector() : mListHash(0), mListHashDirty(false) {}
        HashedVector(size_type n) : mList(n), mListHash(0), mListHashDirty(n > 0) {}
        HashedVector(size_type n, const T& t) : mList(n, t), mListHash(0), mListHashDirty(n > 0) {}
        HashedVector(const HashedVector<T>& rhs) 
            : mList(rhs.mList), mListHash(rhs.mListHash), mListHashDirty(rhs.mListHashDirty) {}

        template <class InputIterator>
        HashedVector(InputIterator a, InputIterator b)
            : mList(a, b), mListHash(0), mListHashDirty(false)
        {
            dirtyHash();
        }

        ~HashedVector() {}
        HashedVector<T>& operator=(const HashedVector<T>& rhs)
        {
            mList = rhs.mList;
            mListHash = rhs.mListHash;
            mListHashDirty = rhs.mListHashDirty;
            return *this;
        }

        void reserve(size_t t) { mList.reserve(t); }
        reference front() 
        { 
            // we have to assume that hash needs recalculating on non-const
            dirtyHash();
            return mList.front(); 
        }
        const_reference front() const { return mList.front(); }
        reference back()  
        { 
            // we have to assume that hash needs recalculating on non-const
            dirtyHash();
            return mList.back(); 
        }
        const_reference back() const { return mList.back(); }
        void push_back(const T& t)
        { 
            mList.push_back(t);
            // Quick progressive hash add
            if (!isHashDirty())
                addToHash(t);
        }
        void pop_back()
        {
            mList.pop_back();
            dirtyHash();
        }
        void swap(HashedVector<T>& rhs)
        {
            mList.swap(rhs.mList);
            dirtyHash();
        }
        iterator insert(iterator pos, const T& t)
        {
            bool recalc = (pos != end());
            iterator ret = mList.insert(pos, t);
            if (recalc)
                dirtyHash();
            else
                addToHash(t);
            return ret;
        }

        template <class InputIterator>
        void insert(iterator pos,
            InputIterator f, InputIterator l)
        {
            mList.insert(pos, f, l);
            dirtyHash();
        }

        void insert(iterator pos, size_type n, const T& x)
        {
            mList.insert(pos, n, x);
            dirtyHash();
        }

        iterator erase(iterator pos)
        {
            iterator ret = mList.erase(pos);
            dirtyHash();
            return ret;
        }
        iterator erase(iterator first, iterator last)
        {
            iterator ret = mList.erase(first, last);
            dirtyHash();
            return ret;
        }
        void clear()
        {
            mList.clear();
            mListHash = 0;
            mListHashDirty = false;
        }

        void resize(size_type n, const T& t = T())
        {
            bool recalc = false;
            if (n != size())
                recalc = true;

            mList.resize(n, t);
            if (recalc)
                dirtyHash();
        }

        bool operator==(const HashedVector<T>& b)
        { return mListHash == b.mListHash; }

        bool operator<(const HashedVector<T>& b)
        { return mListHash < b.mListHash; }


        /// Get the hash value
        uint32 getHash() const 
        { 
            if (isHashDirty())
                recalcHash();

            return mListHash; 
        }
    public:



    };

    typedef std::vector<Light*> LightArray;

    /// Used as the light list, sorted
    struct LightClosest
    {
        Light       *light;
        /// Index to SceneManager::mGlobalLightList.
        /// globalIndex may be == SceneManager::mGlobalLightList.size() if
        /// it holds a static light (see CompositorShadowNode::setLightFixedToShadowMap)
        /// that is not currently in camera.
        size_t      globalIndex; //Index to SceneManager::mGlobalLightList
        Real        distance;
        bool        isStatic;
        bool        isDirty;

        LightClosest() :
            light( 0 ),globalIndex( 0 ),distance( 0.0f ),
            isStatic( false ), isDirty( false ) {}
        LightClosest( Light *_light, size_t _globalIndex, Real _distance ) :
            light( _light ), globalIndex( _globalIndex ), distance( _distance ),
            isStatic( false ), isDirty( false ) {}

        inline bool operator < ( const LightClosest &right ) const
        {
            /*Shouldn't be necessary. distance is insanely low (big negative number)
            if( light->getType() == Light::LT_DIRECTIONAL &&
                right.light->getType() != Light::LT_DIRECTIONAL )
            {
                return true;
            }
            else if( light->getType() != Light::LT_DIRECTIONAL &&
                     right.light->getType() == Light::LT_DIRECTIONAL )
            {
                return false;
            }*/
            return distance < right.distance;
        }
    };
    /// Holds all lights in SoA after being culled over all frustums
    struct LightListInfo
    {
        LightArray                      lights;
        ///Copy from lights[i]->getVisibilityFlags(), this copy avoids one level of indirection
        uint32  * RESTRICT_ALIAS        visibilityMask;
        Sphere  * RESTRICT_ALIAS        boundingSphere;

        LightListInfo() : visibilityMask(0), boundingSphere(0) {}
        ~LightListInfo()
        {
            OGRE_FREE_SIMD( visibilityMask, MEMCATEGORY_SCENE_CONTROL );
            OGRE_FREE_SIMD( boundingSphere, MEMCATEGORY_SCENE_CONTROL );
        }
    };
    typedef HashedVector<LightClosest> LightList;
    typedef std::vector<LightClosest> LightClosestVec;
    typedef std::vector<LightClosest> LightClosestArray;


    typedef std::map<String, bool> UnaryOptionList;
    typedef std::map<String, String> BinaryOptionList;

    /// Name / value parameter pair (first = name, second = value)
    typedef std::map<String, String> NameValuePairList;

    /// Alias / Texture name pair (first = alias, second = texture name)
    typedef std::map<String, String> AliasTextureNamePairList;

        template< typename T > struct TRect
        {
          T left, top, right, bottom;
          TRect() : left(0), top(0), right(0), bottom(0) {}
          TRect( T const & l, T const & t, T const & r, T const & b )
            : left( l ), top( t ), right( r ), bottom( b )
          {
          }
          TRect( TRect const & o )
            : left( o.left ), top( o.top ), right( o.right ), bottom( o.bottom )
          {
          }
          TRect & operator=( TRect const & o )
          {
            left = o.left;
            top = o.top;
            right = o.right;
            bottom = o.bottom;
            return *this;
          }
          T width() const
          {
            return right - left;
          }
          T height() const
          {
            return bottom - top;
          }
          bool isNull() const
          {
              return width() == 0 || height() == 0;
          }
          void setNull()
          {
              left = right = top = bottom = 0;
          }
          TRect & merge(const TRect& rhs)
          {
              if (isNull())
              {
                  *this = rhs;
              }
              else if (!rhs.isNull())
              {
                  left = std::min(left, rhs.left);
                  right = std::max(right, rhs.right);
                  top = std::min(top, rhs.top);
                  bottom = std::max(bottom, rhs.bottom);
              }

              return *this;

          }
          TRect intersect(const TRect& rhs) const
          {
              TRect ret;
              if (isNull() || rhs.isNull())
              {
                  // empty
                  return ret;
              }
              else
              {
                  ret.left = std::max(left, rhs.left);
                  ret.right = std::min(right, rhs.right);
                  ret.top = std::max(top, rhs.top);
                  ret.bottom = std::min(bottom, rhs.bottom);
              }

              if (ret.left > ret.right || ret.top > ret.bottom)
              {
                  // no intersection, return empty
                  ret.left = ret.top = ret.right = ret.bottom = 0;
              }

              return ret;

          }

        };
        template<typename T>
        std::ostream& operator<<(std::ostream& o, const TRect<T>& r)
        {
            o << "TRect<>(l:" << r.left << ", t:" << r.top << ", r:" << r.right << ", b:" << r.bottom << ")";
            return o;
        }

        /** Structure used to define a rectangle in a 2-D floating point space.
        */
        typedef TRect<float> FloatRect;

        /** Structure used to define a rectangle in a 2-D floating point space, 
            subject to double / single floating point settings.
        */
        typedef TRect<Real> RealRect;

        /** Structure used to define a rectangle in a 2-D integer space.
        */
        typedef TRect< long > Rect;

        /** Structure used to define a box in a 3-D integer space.
            Note that the left, top, and front edges are included but the right, 
            bottom and back ones are not.
         */
        struct Box
        {
            uint32 left, top, right, bottom, front, back;
            /// Parameterless constructor for setting the members manually
            Box()
                : left(0), top(0), right(1), bottom(1), front(0), back(1)
            {
            }
            /** Define a box from left, top, right and bottom coordinates
                This box will have depth one (front=0 and back=1).
                @param  l   x value of left edge
                @param  t   y value of top edge
                @param  r   x value of right edge
                @param  b   y value of bottom edge
                @note Note that the left, top, and front edges are included 
                    but the right, bottom and back ones are not.
            */
            Box( uint32 l, uint32 t, uint32 r, uint32 b ):
                left(l),
                top(t),   
                right(r),
                bottom(b),
                front(0),
                back(1)
            {
                assert_invariant(right >= left && bottom >= top && back >= front);
            }
            /** Define a box from left, top, front, right, bottom and back
                coordinates.
                @param  l   x value of left edge
                @param  t   y value of top edge
                @param  ff  z value of front edge
                @param  r   x value of right edge
                @param  b   y value of bottom edge
                @param  bb  z value of back edge
                @note Note that the left, top, and front edges are included 
                    but the right, bottom and back ones are not.
            */
            Box( uint32 l, uint32 t, uint32 ff, uint32 r, uint32 b, uint32 bb ):
                left(l),
                top(t),   
                right(r),
                bottom(b),
                front(ff),
                back(bb)
            {
                assert_invariant(right >= left && bottom >= top && back >= front);
            }
            
            explicit Box(const Vector3i& size)
                : left(0), top(0), right(size.x), bottom(size.y), front(0), back(size.z)
            {
            }

            /// Return true if the other box is a part of this one
            bool contains(const Box &def) const
            {
                return (def.left >= left && def.top >= top && def.front >= front &&
                    def.right <= right && def.bottom <= bottom && def.back <= back);
            }
            
            /// Get the width of this box
            uint32 getWidth() const { return right-left; }
            /// Get the height of this box
            uint32 getHeight() const { return bottom-top; }
            /// Get the depth of this box
            uint32 getDepth() const { return back-front; }
        };

    
    
    /** Locate command-line options of the unary form '-blah' and of the
        binary form '-blah foo', passing back the index of the next non-option.
    @param numargs, argv The standard parameters passed to the main method
    @param unaryOptList Map of unary options (i.e. those that do not require a parameter).
        Should be pre-populated with, for example '-e' in the key and false in the 
        value. Options which are found will be set to true on return.
    @param binOptList Map of binary options (i.e. those that require a parameter
        e.g. '-e afile.txt').
        Should be pre-populated with, for example '-e' and the default setting. 
        Options which are found will have the value updated.
    */
    int  findCommandLineOpts(int numargs, char** argv, UnaryOptionList& unaryOptList, 
        BinaryOptionList& binOptList);

    /// Generic result of clipping
    enum ClipResult
    {
        /// Nothing was clipped
        CLIPPED_NONE = 0,
        /// Partially clipped
        CLIPPED_SOME = 1, 
        /// Everything was clipped away
        CLIPPED_ALL = 2
    };

    enum TextureLayout {
        TEXTURE_LAYOUT_UNDEFINED,
        TEXTURE_LAYOUT_STORAGE_OPTIMAL,
        TEXTURE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
        TEXTURE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL,
        TEXTURE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL,
        TEXTURE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
        TEXTURE_LAYOUT_COPY_SRC_OPTIMAL,
        TEXTURE_LAYOUT_COPY_DST_OPTIMAL,
        TEXTURE_LAYOUT_RESOLVE_SRC_OPTIMAL,
        TEXTURE_LAYOUT_RESOLVE_DST_OPTIMAL,
        TEXTURE_LAYOUT_VRS_ATTACHMENT_OPTIMAL,
        TEXTURE_LAYOUT_MAX
    };

    /// Render window creation parameters.
    struct RenderWindowDescription
    {
        String              name;
        unsigned int        width;
        unsigned int        height;
        bool                useFullScreen;
        NameValuePairList   miscParams;
    };

    struct ImageSubresourceLayer
    {
        uint32_t aspectMask;
        uint32_t mipLevel;
        uint32_t baseArrayLayer;
        uint32_t layerCount;
    };

    typedef struct Extent3D {
        uint32_t    width;
        uint32_t    height;
        uint32_t    depth;
    } Extent3D;

    struct ImageCopyDesc
    {
        ImageSubresourceLayer srcSubresource;
        Ogre::Vector3i srcOffset;
        ImageSubresourceLayer dstSubresource;
        Ogre::Vector3i dstOffset;
        Extent3D extent;
    };

    struct ImageCopyBufferDesc
    {
        uint64_t bufferOffset;
        ImageSubresourceLayer textureSubresources;
        Ogre::Vector3i textureOffset;
        Ogre::Vector3i textureRegionSize;
        TextureLayout textureLayout;
    };

    struct FamilyInfo
    {
        uint32_t graphicsQueueFamilyIndex;
        uint32_t transferQueueFamilyIndex;
        uint32_t transferQueueCount;
    };

    struct SwapChainInfo
    {
        Ogre::OgreTexture* color;
        Ogre::OgreTexture* depth;
        uint32_t imageIndex;
    };

   

    struct ShaderDesc
    {
        std::string vertexBin;
        std::string fragBin;
        std::string computeBin;
        std::string name;

        VertexDeclaration* decl;
    };

    enum PRIMITIVE_TOPOLOGY_TYPE : uint8_t
    {
        PRIMITIVE_TOPOLOGY_UNDEFINED = 0,
        PRIMITIVE_TOPOLOGY_POINTLIST = 1,
        PRIMITIVE_TOPOLOGY_LINELIST = 2,
        PRIMITIVE_TOPOLOGY_LINESTRIP = 3,
        PRIMITIVE_TOPOLOGY_TRIANGLELIST = 4,
        PRIMITIVE_TOPOLOGY_TRIANGLESTRIP = 5
    };

    enum LogicOperation : uint8_t {
        LOGIC_OP_CLEAR,
        LOGIC_OP_AND,
        LOGIC_OP_AND_REVERSE,
        LOGIC_OP_COPY,
        LOGIC_OP_AND_INVERTED,
        LOGIC_OP_NO_OP,
        LOGIC_OP_XOR,
        LOGIC_OP_OR,
        LOGIC_OP_NOR,
        LOGIC_OP_EQUIVALENT,
        LOGIC_OP_INVERT,
        LOGIC_OP_OR_REVERSE,
        LOGIC_OP_COPY_INVERTED,
        LOGIC_OP_OR_INVERTED,
        LOGIC_OP_NAND,
        LOGIC_OP_SET,
        LOGIC_OP_MAX
    };

    enum  BlendOperation: uint8_t {
        BLEND_OP_ADD,
        BLEND_OP_SUBTRACT,
        BLEND_OP_REVERSE_SUBTRACT,
        BLEND_OP_MINIMUM,
        BLEND_OP_MAXIMUM, // Yes, this one is an actual operator.
        BLEND_OP_MAX
    };

    enum  BlendFunction : uint8_t {
        BLEND_FACTOR_ZERO,
        BLEND_FACTOR_ONE,
        BLEND_FACTOR_SRC_COLOR,
        BLEND_FACTOR_ONE_MINUS_SRC_COLOR,
        BLEND_FACTOR_DST_COLOR,
        BLEND_FACTOR_ONE_MINUS_DST_COLOR,
        BLEND_FACTOR_SRC_ALPHA,
        BLEND_FACTOR_ONE_MINUS_SRC_ALPHA,
        BLEND_FACTOR_DST_ALPHA,
        BLEND_FACTOR_ONE_MINUS_DST_ALPHA,
        BLEND_FACTOR_CONSTANT_COLOR,
        BLEND_FACTOR_ONE_MINUS_CONSTANT_COLOR,
        BLEND_FACTOR_CONSTANT_ALPHA,
        BLEND_FACTOR_ONE_MINUS_CONSTANT_ALPHA,
        BLEND_FACTOR_SRC_ALPHA_SATURATE,
        BLEND_FACTOR_SRC1_COLOR,
        BLEND_FACTOR_ONE_MINUS_SRC1_COLOR,
        BLEND_FACTOR_SRC1_ALPHA,
        BLEND_FACTOR_ONE_MINUS_SRC1_ALPHA,
        BLEND_FACTOR_MAX
    };

    struct RasterizationStateInfo {
        bool depthClampEnable= false;
        bool discardPrimitives = false;
        bool wireframe = false;
        CullingMode cullMode = CULL_MODE_NONE;
        //PolygonFrontFace front_face = POLYGON_FRONT_FACE_CLOCKWISE;
        bool depthBiasEnable = false;
        float depthBiasConstantFactor = 0.0f;
        float depthBiasClamp = 0.0f;
        float depthBiasSlopeFactor = 0.0f;
        float lineWidth = 1.0f;
        uint32_t patchControlPoints = 1;
    };

    struct MultisampleStateInfo {
        uint32_t sampleCount = 1;
        bool enable_sample_shading = false;
        float min_sample_shading = 0.0f;
        std::vector<uint32_t> sample_mask;
        bool enable_alpha_to_coverage = false;
        bool enable_alpha_to_one = false;
    };

    struct DepthStencilStateInfo {
        bool depthTestEnable = false;
        bool depthWriteEnable = false;
        CompareFunction depthCompareOp = CMPF_ALWAYS_PASS;
        bool enable_depth_range = false;
        float depth_range_min = 0;
        float depth_range_max = 0;
        bool enable_stencil = false;
    };

    struct Attachment {
        bool enable_blend = false;
        BlendFunction blendFunctionSrcRGB = BLEND_FACTOR_ZERO;
        BlendFunction blendFunctionDstRGB = BLEND_FACTOR_ZERO;
        BlendOperation blendEquationRGB = BLEND_OP_ADD;
        BlendFunction blendFunctionSrcAlpha = BLEND_FACTOR_ZERO;
        BlendFunction blendFunctionDstAlpha = BLEND_FACTOR_ZERO;
        BlendOperation blendEquationAlpha = BLEND_OP_ADD;
        bool write_r = true;
        bool write_g = true;
        bool write_b = true;
        bool write_a = true;
    };
    struct ColorBlendStateInfo{
        bool enable_logic_op = false;
        LogicOperation logic_op = LOGIC_OP_CLEAR;
        std::vector<Attachment> attachments;
    };

    struct RenderTargetInfo
    {
        uint8_t renderTargetCount;
        uint16_t pixelFormat[8];
    };

    struct PipelineCreateInfo
    {
        VertexDeclaration* decl;
        PRIMITIVE_TOPOLOGY_TYPE topology;
        RasterizationStateInfo rasterizationState;
        MultisampleStateInfo multisampleState;
        DepthStencilStateInfo depthStencilState;
        ColorBlendStateInfo colorBlendState;
        RenderTargetInfo renderTarget;
    };

    struct CreateWindowDesc
    {
        uint32_t width;
        uint32_t height;
        bool srgb;
        char windowHandle[128];
    };

    enum BackendResourceState
    {
        RESOURCE_STATE_UNDEFINED = 0,
        RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER = 0x1,
        RESOURCE_STATE_INDEX_BUFFER = 0x2,
        RESOURCE_STATE_RENDER_TARGET = 0x4,
        RESOURCE_STATE_UNORDERED_ACCESS = 0x8,
        RESOURCE_STATE_DEPTH_WRITE = 0x10,
        RESOURCE_STATE_DEPTH_READ = 0x20,
        RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE = 0x40,
        RESOURCE_STATE_PIXEL_SHADER_RESOURCE = 0x80,
        RESOURCE_STATE_SHADER_RESOURCE = 0x40 | 0x80,
        RESOURCE_STATE_STREAM_OUT = 0x100,
        RESOURCE_STATE_INDIRECT_ARGUMENT = 0x200,
        RESOURCE_STATE_COPY_DEST = 0x400,
        RESOURCE_STATE_COPY_SOURCE = 0x800,
        RESOURCE_STATE_GENERIC_READ = (((((0x1 | 0x2) | 0x40) | 0x80) | 0x200) | 0x800),
        RESOURCE_STATE_PRESENT = 0x1000,
        RESOURCE_STATE_COMMON = 0x2000,
        RESOURCE_STATE_ACCELERATION_STRUCTURE_READ = 0x4000,
        RESOURCE_STATE_ACCELERATION_STRUCTURE_WRITE = 0x8000,
    };

    //! Buffer object binding type
    enum  BufferObjectBinding
    {
        BufferObjectBinding_None = 0,
        BufferObjectBinding_Vertex = 1,
        BufferObjectBinding_Index = BufferObjectBinding_Vertex << 1,
        BufferObjectBinding_Uniform = BufferObjectBinding_Index << 1,
        BufferObjectBinding_Buffer = BufferObjectBinding_Uniform << 1,
        BufferObjectBinding_Storge = BufferObjectBinding_Buffer << 1,
        BufferObjectBinding_InDirectBuffer = BufferObjectBinding_Storge << 1,
        BufferObjectBinding_AccelerationStructure = (BufferObjectBinding_InDirectBuffer << 1),
    };

    typedef enum ResourceMemoryUsage
    {
        /// No intended memory usage specified.
        RESOURCE_MEMORY_USAGE_UNKNOWN = 0,
        /// Memory will be used on device only, no need to be mapped on host.
        RESOURCE_MEMORY_USAGE_GPU_ONLY = 1,
        /// Memory will be mapped on host. Could be used for transfer to device.
        RESOURCE_MEMORY_USAGE_CPU_ONLY = 2,
        /// Memory will be used for frequent (dynamic) updates from host and reads on device.
        RESOURCE_MEMORY_USAGE_CPU_TO_GPU = 3,
        /// Memory will be used for writing on device and readback on host.
        RESOURCE_MEMORY_USAGE_GPU_TO_CPU = 4,
        RESOURCE_MEMORY_USAGE_COUNT,
        RESOURCE_MEMORY_USAGE_MAX_ENUM = 0x7FFFFFFF
    } ResourceMemoryUsage;

    typedef enum DescriptorType
    {
        DESCRIPTOR_TYPE_UNDEFINED = 0,
        DESCRIPTOR_TYPE_SAMPLER = 0x01,
        // SRV Read only texture
        DESCRIPTOR_TYPE_TEXTURE = (DESCRIPTOR_TYPE_SAMPLER << 1),
        DESCRIPTOR_TYPE_TEXTURE_SAMPLER = (DESCRIPTOR_TYPE_TEXTURE << 1),
        /// UAV Texture
        DESCRIPTOR_TYPE_RW_TEXTURE = (DESCRIPTOR_TYPE_TEXTURE_SAMPLER << 1),
        // SRV Read only buffer
        DESCRIPTOR_TYPE_BUFFER = (DESCRIPTOR_TYPE_RW_TEXTURE << 1),
        DESCRIPTOR_TYPE_BUFFER_RAW = (DESCRIPTOR_TYPE_BUFFER | (DESCRIPTOR_TYPE_BUFFER << 1)),
        DESCRIPTOR_TYPE_BUFFER_VIEW = DESCRIPTOR_TYPE_BUFFER << 2,
        /// UAV Buffer
        DESCRIPTOR_TYPE_RW_BUFFER = (DESCRIPTOR_TYPE_BUFFER_VIEW << 1),
        DESCRIPTOR_TYPE_RW_BUFFER_RAW = (DESCRIPTOR_TYPE_RW_BUFFER | (DESCRIPTOR_TYPE_RW_BUFFER << 1)),
        /// Uniform buffer
        DESCRIPTOR_TYPE_UNIFORM_BUFFER = (DESCRIPTOR_TYPE_RW_BUFFER << 2),
        /// Push constant / Root constant
        DESCRIPTOR_TYPE_ROOT_CONSTANT = (DESCRIPTOR_TYPE_UNIFORM_BUFFER << 1),
        /// IA
        DESCRIPTOR_TYPE_VERTEX_BUFFER = (DESCRIPTOR_TYPE_ROOT_CONSTANT << 1),
        DESCRIPTOR_TYPE_INDEX_BUFFER = (DESCRIPTOR_TYPE_VERTEX_BUFFER << 1),
        DESCRIPTOR_TYPE_INDIRECT_BUFFER = (DESCRIPTOR_TYPE_INDEX_BUFFER << 1),
        /// Cubemap SRV
        DESCRIPTOR_TYPE_TEXTURE_CUBE = (DESCRIPTOR_TYPE_TEXTURE | (DESCRIPTOR_TYPE_INDIRECT_BUFFER << 1)),
        /// RTV / DSV per mip slice
        DESCRIPTOR_TYPE_RENDER_TARGET_MIP_SLICES = (DESCRIPTOR_TYPE_INDIRECT_BUFFER << 2),
        /// RTV / DSV per array slice
        DESCRIPTOR_TYPE_RENDER_TARGET_ARRAY_SLICES = (DESCRIPTOR_TYPE_RENDER_TARGET_MIP_SLICES << 1),
        /// RTV / DSV per depth slice
        DESCRIPTOR_TYPE_RENDER_TARGET_DEPTH_SLICES = (DESCRIPTOR_TYPE_RENDER_TARGET_ARRAY_SLICES << 1),
        DESCRIPTOR_TYPE_INDIRECT_COMMAND_BUFFER = (DESCRIPTOR_TYPE_RENDER_TARGET_DEPTH_SLICES << 1),
        /// Raytracing acceleration structure
        DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE = (DESCRIPTOR_TYPE_INDIRECT_COMMAND_BUFFER << 1),
    } DescriptorType;

    typedef struct BufferDesc
    {
        /// Size of the buffer (in bytes)
        uint64_t             mSize;
        /// Index of the first element accessible by the SRV/UAV (applicable to BUFFER_USAGE_STORAGE_SRV, BUFFER_USAGE_STORAGE_UAV)
        uint32_t             mFirstElement;
        /// Number of elements in the buffer (applicable to BUFFER_USAGE_STORAGE_SRV, BUFFER_USAGE_STORAGE_UAV)
        uint32_t             mElementCount;
        /// Size of each element (in bytes) in the buffer (applicable to BUFFER_USAGE_STORAGE_SRV, BUFFER_USAGE_STORAGE_UAV)
        uint32_t             mStructStride;
        /// Alignment
        uint32_t             mAlignment;
        /// Debug name used in gpu profile
        const char* pName;
        ResourceMemoryUsage  mMemoryUsage;
        /// Creation flags of the buffer
        uint32_t  bufferCreationFlags; //BufferCreationFlags
        /// What type of queue the buffer is owned by
        QueueType            mQueueType;
        /// What state will the buffer get created in
        BackendResourceState        mStartState;
        //TinyImageFormat      mFormat;
        /// Flags specifying the suitable usage of this buffer (Uniform buffer, Vertex Buffer, Index Buffer,...)
        DescriptorType       mDescriptors;

        BufferObjectBinding mBindingType;

        bool raw;

    } BufferDesc;

    enum VertexElementType
    {
        VET_FLOAT1 = 0,
        VET_FLOAT2 = 1,
        VET_FLOAT3 = 2,
        VET_FLOAT4 = 3,

        VET_SHORT1 = 5,  ///< @deprecated (see #VertexElementType note)
        VET_SHORT2 = 6,
        VET_SHORT3 = 7,  ///< @deprecated (see #VertexElementType note)
        VET_SHORT4 = 8,
        VET_UBYTE4 = 9,
        _DETAIL_SWAP_RB = 10,

        // the following are not universally supported on all hardware:
        VET_DOUBLE1 = 12,
        VET_DOUBLE2 = 13,
        VET_DOUBLE3 = 14,
        VET_DOUBLE4 = 15,
        VET_USHORT1 = 16,  ///< @deprecated (see #VertexElementType note)
        VET_USHORT2 = 17,
        VET_USHORT3 = 18,  ///< @deprecated (see #VertexElementType note)
        VET_USHORT4 = 19,
        VET_INT1 = 20,
        VET_INT2 = 21,
        VET_INT3 = 22,
        VET_INT4 = 23,
        VET_UINT1 = 24,
        VET_UINT2 = 25,
        VET_UINT3 = 26,
        VET_UINT4 = 27,
        VET_BYTE4 = 28,  ///< signed bytes
        VET_BYTE4_NORM = 29,   ///< signed bytes (normalized to -1..1)
        VET_UBYTE4_NORM = 30,  ///< unsigned bytes (normalized to 0..1)
        VET_SHORT2_NORM = 31,  ///< signed shorts (normalized to -1..1)
        VET_SHORT4_NORM = 32,
        VET_USHORT2_NORM = 33, ///< unsigned shorts (normalized to 0..1)
        VET_USHORT4_NORM = 34,
        VET_INT_10_10_10_2_NORM = 35, ///< signed int (normalized to 0..1)
        VET_COLOUR = VET_UBYTE4_NORM,  ///< @deprecated use VET_UBYTE4_NORM
        VET_COLOUR_ARGB = VET_UBYTE4_NORM,  ///< @deprecated use VET_UBYTE4_NORM
        VET_COLOUR_ABGR = VET_UBYTE4_NORM,  ///< @deprecated use VET_UBYTE4_NORM
    };

   

    enum VertexElementSemantic {
        /// Position, typically VET_FLOAT3
        VES_POSITION = 1,
        /// Blending weights
        VES_BLEND_WEIGHTS = 2,
        /// Blending indices
        VES_BLEND_INDICES = 3,
        /// Normal, typically VET_FLOAT3
        VES_NORMAL = 4,
        /// Colour, typically VET_UBYTE4
        VES_COLOUR = 5,
        /// Secondary colour. Generally free for custom data. Means specular with OpenGL FFP.
        VES_COLOUR2 = 6,
        /// Texture coordinates, typically VET_FLOAT2
        VES_TEXTURE_COORDINATES = 7,
        /// Binormal (Y axis if normal is Z)
        VES_BINORMAL = 8,
        /// Tangent (X axis if normal is Z)
        VES_TANGENT = 9,
        /// The  number of VertexElementSemantic elements (note - the first value VES_POSITION is 1) 
        VES_COUNT = 9,
        /// @deprecated use VES_COLOUR
        VES_DIFFUSE = VES_COLOUR,
        /// @deprecated use VES_COLOUR2
        VES_SPECULAR = VES_COLOUR2
    };


#define DIFFUSE_TEXTURE "diffuse_texture"
#define NORMAL_TEXTURE "normal_texture"
#define SPECULAR_TEXTURE "specular_texure"
#define EMISSIVE_TEXTURE "emissive_texture"
#define OPACITY_TEXTURE "opacity_texture"

    typedef struct BufferBarrier
    {
        filament::backend::Handle<filament::backend::HwBufferObject> buffer;
        BitField<BackendResourceState> mCurrentState;
        BitField<BackendResourceState> mNewState;
        uint8_t       mBeginOnly : 1;
        uint8_t       mEndOnly : 1;
    } BufferBarrier;

    typedef struct TextureBarrier
    {
        OgreTexture* pTexture;
        BitField<BackendResourceState> mCurrentState;
        BitField<BackendResourceState> mNewState;
        uint8_t       mBeginOnly : 1;
        uint8_t       mEndOnly : 1;
        uint8_t       mAcquire : 1;
        uint8_t       mRelease : 1;
        uint8_t       mQueueType : 5;
        /// Specifiy whether following barrier targets particular subresource
        uint8_t       mSubresourceBarrier : 1;
        /// Following values are ignored if mSubresourceBarrier is false
        uint8_t       mMipLevel : 7;
        uint16_t      mArrayLayer;
    } TextureBarrier;

    typedef struct RenderTargetBarrier
    {
        Ogre::RenderTarget* pRenderTarget;
        uint32_t mCurrentState;//BackendResourceState
        uint32_t mNewState;//BackendResourceState
        uint8_t       mBeginOnly : 1;
        uint8_t       mEndOnly : 1;
        uint8_t       mAcquire : 1;
        uint8_t       mRelease : 1;
        uint8_t       mQueueType : 5;
        /// Specifiy whether following barrier targets particular subresource
        uint8_t       mSubresourceBarrier : 1;
        /// Following values are ignored if mSubresourceBarrier is false
        uint8_t       mMipLevel : 7;
        uint16_t      mArrayLayer;
    } RenderTargetBarrier;

    struct AccelerationStructure;

    struct BufferView
    {
        filament::backend::Handle<filament::backend::HwBufferObject> buffer;
        uint32_t offset;
    };

    typedef struct DescriptorData
    {
        const char* pName;
        uint32_t    mCount:16;
        uint32_t    mLevel : 8;
        uint32_t    mArrayElement : 8;
        uint32_t     mDstBinding;
        Ogre::DescriptorType descriptorType;
        union
        {
            const OgreTexture** ppTextures;
            const filament::backend::Handle<filament::backend::HwBufferObject>* ppBuffers;
            BufferView* pBufferView;
            const filament::backend::Handle<filament::backend::HwSampler>* ppSamplers;
            AccelerationStructure* pAS;
        };
       
    } DescriptorData;


    typedef struct DescriptorInfo
    {
        const char* pName;
        uint32_t mType;
        uint32_t mDim : 4;
        uint32_t mRootDescriptor : 1;
        uint32_t mStaticSampler : 1;
        uint32_t mSet : 3;
        uint32_t mSetIndex : 23;
        uint32_t mSize;
        uint32_t mRootIndex;
    } DescriptorInfo;

    struct TransformMatrix {
        float    matrix[3][4];
    };

    struct PushConstantContext
    {
        uint32_t size;
    };

    enum TextureAspect {
        TEXTURE_ASPECT_COLOR = 0,
        TEXTURE_ASPECT_DEPTH = 1,
        TEXTURE_ASPECT_STENCIL = 2,
        TEXTURE_ASPECT_MAX
    };

    enum TextureAspectBits {
        TEXTURE_ASPECT_COLOR_BIT = (1 << TEXTURE_ASPECT_COLOR),
        TEXTURE_ASPECT_DEPTH_BIT = (1 << TEXTURE_ASPECT_DEPTH),
        TEXTURE_ASPECT_STENCIL_BIT = (1 << TEXTURE_ASPECT_STENCIL),
    };

    struct TextureSubresourceRange {
        BitField<TextureAspectBits> aspect;
        uint32_t base_mipmap = 0;
        uint32_t mipmap_count = 0;
        uint32_t base_layer = 0;
        uint32_t layer_count = 0;
    };

    enum TextureUsageBits {
        TEXTURE_USAGE_SAMPLING_BIT = (1 << 0),
        TEXTURE_USAGE_COLOR_ATTACHMENT_BIT = (1 << 1),
        TEXTURE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT = (1 << 2),
        TEXTURE_USAGE_STORAGE_BIT = (1 << 3),
        TEXTURE_USAGE_STORAGE_ATOMIC_BIT = (1 << 4),
        TEXTURE_USAGE_CPU_READ_BIT = (1 << 5),
        TEXTURE_USAGE_CAN_UPDATE_BIT = (1 << 6),
        TEXTURE_USAGE_CAN_COPY_FROM_BIT = (1 << 7),
        TEXTURE_USAGE_CAN_COPY_TO_BIT = (1 << 8),
        TEXTURE_USAGE_INPUT_ATTACHMENT_BIT = (1 << 9),
        TEXTURE_USAGE_VRS_ATTACHMENT_BIT = (1 << 10),
    };

    enum Limit {
        LIMIT_MAX_BOUND_UNIFORM_SETS,
        LIMIT_MAX_FRAMEBUFFER_COLOR_ATTACHMENTS,
        LIMIT_MAX_TEXTURES_PER_UNIFORM_SET,
        LIMIT_MAX_SAMPLERS_PER_UNIFORM_SET,
        LIMIT_MAX_STORAGE_BUFFERS_PER_UNIFORM_SET,
        LIMIT_MAX_STORAGE_IMAGES_PER_UNIFORM_SET,
        LIMIT_MAX_UNIFORM_BUFFERS_PER_UNIFORM_SET,
        LIMIT_MAX_DRAW_INDEXED_INDEX,
        LIMIT_MAX_FRAMEBUFFER_HEIGHT,
        LIMIT_MAX_FRAMEBUFFER_WIDTH,
        LIMIT_MAX_TEXTURE_ARRAY_LAYERS,
        LIMIT_MAX_TEXTURE_SIZE_1D,
        LIMIT_MAX_TEXTURE_SIZE_2D,
        LIMIT_MAX_TEXTURE_SIZE_3D,
        LIMIT_MAX_TEXTURE_SIZE_CUBE,
        LIMIT_MAX_TEXTURES_PER_SHADER_STAGE,
        LIMIT_MAX_SAMPLERS_PER_SHADER_STAGE,
        LIMIT_MAX_STORAGE_BUFFERS_PER_SHADER_STAGE,
        LIMIT_MAX_STORAGE_IMAGES_PER_SHADER_STAGE,
        LIMIT_MAX_UNIFORM_BUFFERS_PER_SHADER_STAGE,
        LIMIT_MAX_PUSH_CONSTANT_SIZE,
        LIMIT_MAX_UNIFORM_BUFFER_SIZE,
        LIMIT_MAX_VERTEX_INPUT_ATTRIBUTE_OFFSET,
        LIMIT_MAX_VERTEX_INPUT_ATTRIBUTES,
        LIMIT_MAX_VERTEX_INPUT_BINDINGS,
        LIMIT_MAX_VERTEX_INPUT_BINDING_STRIDE,
        LIMIT_MIN_UNIFORM_BUFFER_OFFSET_ALIGNMENT,
        LIMIT_MAX_COMPUTE_SHARED_MEMORY_SIZE,
        LIMIT_MAX_COMPUTE_WORKGROUP_COUNT_X,
        LIMIT_MAX_COMPUTE_WORKGROUP_COUNT_Y,
        LIMIT_MAX_COMPUTE_WORKGROUP_COUNT_Z,
        LIMIT_MAX_COMPUTE_WORKGROUP_INVOCATIONS,
        LIMIT_MAX_COMPUTE_WORKGROUP_SIZE_X,
        LIMIT_MAX_COMPUTE_WORKGROUP_SIZE_Y,
        LIMIT_MAX_COMPUTE_WORKGROUP_SIZE_Z,
        LIMIT_MAX_VIEWPORT_DIMENSIONS_X,
        LIMIT_MAX_VIEWPORT_DIMENSIONS_Y,
        LIMIT_SUBGROUP_SIZE,
        LIMIT_SUBGROUP_MIN_SIZE,
        LIMIT_SUBGROUP_MAX_SIZE,
        LIMIT_SUBGROUP_IN_SHADERS, // Set flags using SHADER_STAGE_VERTEX_BIT, SHADER_STAGE_FRAGMENT_BIT, etc.
        LIMIT_SUBGROUP_OPERATIONS,
        LIMIT_VRS_TEXEL_WIDTH,
        LIMIT_VRS_TEXEL_HEIGHT,
        LIMIT_VRS_MAX_FRAGMENT_WIDTH,
        LIMIT_VRS_MAX_FRAGMENT_HEIGHT,
    };
    /// Render window creation parameters container.
    typedef std::vector<RenderWindowDescription> RenderWindowDescriptionList;

    /** @} */
    /** @} */

    /** Used for efficient removal in std::vector and std::deque (like an std::list)
        However it assumes the order of elements in container is not important or
        something external to the container holds the index of an element in it
        (but still should be kept deterministically across machines)
        Basically it swaps the iterator with the last iterator, and pops back
        Returns the next iterator
    */
    template<typename T>
    typename T::iterator efficientVectorRemove( T& container, typename T::iterator& iterator )
    {
        const size_t idx = iterator - container.begin();
        *iterator = container.back();
        container.pop_back();

        return container.begin() + idx;
    }

    /// Aligns the input 'offset' to the next multiple of 'alignment'.
    /// Alignment can be any value except 0. Some examples:
    ///
    /// alignToNextMultiple( 0, 4 ) = 0;
    /// alignToNextMultiple( 1, 4 ) = 4;
    /// alignToNextMultiple( 2, 4 ) = 4;
    /// alignToNextMultiple( 3, 4 ) = 4;
    /// alignToNextMultiple( 4, 4 ) = 4;
    /// alignToNextMultiple( 5, 4 ) = 8;
    ///
    /// alignToNextMultiple( 0, 3 ) = 0;
    /// alignToNextMultiple( 1, 3 ) = 3;
    inline size_t alignToNextMultiple( size_t offset, size_t alignment )
    {
        return ( (offset + alignment - 1) / alignment ) * alignment;
    }

#if OGRE_CPU == OGRE_CPU_X86
    //VS 2012 translates this to a single maxss/maxpd instruction! :)
    //(plus some memory loading if arguments weren't loaded)
    inline float min( const float &left, const float &right )
    {
        float retVal;
        _mm_store_ss( &retVal, _mm_min_ss( _mm_set_ss( left ), _mm_set_ss( right ) ) );
        return retVal;
    }
    inline float max( const float &left, const float &right )
    {
        float retVal;
        _mm_store_ss( &retVal, _mm_max_ss( _mm_set_ss( left ), _mm_set_ss( right ) ) );
        return retVal;
    }
    inline double min( const double &left, const double &right )
    {
        double retVal;
        _mm_store_sd( &retVal, _mm_min_sd( _mm_set_sd( left ), _mm_set_sd( right ) ) );
        return retVal;
    }
    inline double max( const double &left, const double &right )
    {
        double retVal;
        _mm_store_sd( &retVal, _mm_max_sd( _mm_set_sd( left ), _mm_set_sd( right ) ) );
        return retVal;
    }
#else
    //At least VS 2012 translates this to conditional moves. Using
    //"const float" instead of "const float&" and becomes a jump
    inline const float& min( const float &a, const float &b )
    {
        return a < b ? a : b;
    }

    inline const float& max( const float &a, const float &b )
    {
        return a > b ? a : b;
    }

    inline const double& min( const double &a, const double &b )
    {
        return a < b ? a : b;
    }

    inline const double& max( const double &a, const double &b )
    {
        return a > b ? a : b;
    }
#endif
}

