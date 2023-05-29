#ifndef _SINGLETON_H__
#define _SINGLETON_H__


#if OGRE_COMPILER == OGRE_COMPILER_MSVC
#   pragma warning (push)
#   pragma warning ( disable: 4661)
#endif

namespace Ogre {
   
template <typename T> class Singleton
{
private:
    /** @brief Explicit private copy constructor. This is a forbidden operation.*/
    Singleton(const Singleton<T>&);

    /** @brief Private operator= . This is a forbidden operation. */
    Singleton& operator=(const Singleton<T>&);

protected:
    static T* msSingleton;

public:
#if defined(__has_attribute)
#  if __has_attribute(no_sanitize)
    // The `static_cast` happens so early in the construction of the inheriting
    // classes that the `this` pointer is still detected as the super class
    // pointer. Therefore, disabling vptr checks.
    __attribute__((no_sanitize("vptr")))
#  endif
#endif
    Singleton(void)
    {
        assert(!msSingleton);
        msSingleton = static_cast<T*>(this);
    }
    ~Singleton(void)
    {
        assert(msSingleton);
        msSingleton = 0;
    }
    /// Get the singleton instance
    static T& getSingleton(void)
    {
        assert(msSingleton);
        return (*msSingleton);
    }
    /// @copydoc getSingleton
    static T* getSingletonPtr(void) { return msSingleton; }
    };
    /** @} */
    /** @} */

}
#if OGRE_COMPILER == OGRE_COMPILER_MSVC
#   pragma warning (pop)
#endif

#endif
