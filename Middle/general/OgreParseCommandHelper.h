#pragma once

#include "ogrestringconverter.h"
#include "ogrestringinterface.h"
#include "lexical_cast_util.h"

template <class T>
inline Ogre::String
__ToOgreString(const T& v)
{
    return Ogre::StringConverter::toString(v);
}

template <>
inline Ogre::String
__ToOgreString<Ogre::String>(const Ogre::String& v)
{
    return v;
}

template <class T>
inline T
__FromOgreString(const Ogre::String& s)
{
    return lexical_cast<T>(s.c_str());
}

template <>
inline Ogre::String
__FromOgreString<Ogre::String>(const Ogre::String& s)
{
    return s;
}

template <>
inline bool
__FromOgreString<bool>(const Ogre::String& s)
{
    return Ogre::StringConverter::parseBool(s);
}

template <>
inline
Ogre::Vector3
__FromOgreString<Ogre::Vector3>(const Ogre::String& s)
{
	return Ogre::StringConverter::parseVector3(s);
}

template <> inline
Ogre::Quaternion
__FromOgreString<Ogre::Quaternion>(const Ogre::String& s)
{
	return Ogre::StringConverter::parseQuaternion(s);
}

template<> inline
Ogre::ColourValue
__FromOgreString<Ogre::ColourValue>(const Ogre::String& s)
{
	return Ogre::StringConverter::parseColourValue(s);
}

template <typename TClass, typename TType, TType TClass::*PtrToMember>
class MemeberValueCopyParamCommand : public Ogre::ParamCommand
{
public:
	virtual Ogre::String doGet(const void* target) const 
	{
		 const TClass* pObj = static_cast<const TClass*>(target);
		 return __ToOgreString(pObj->*PtrToMember);
	}

    virtual void doSet(void* target, const Ogre::String& val) 
	{
		 TClass* pObj = static_cast<TClass*>(target);
		 pObj->*PtrToMember = __FromOgreString<TType>(val);
	}

#if OGRE_STRING_INTERFACE_COPY
    virtual void doCopy(void* target, const void* source)
	{
		TClass* pTarget = static_cast<TClass*>(target);
		const TClass* pSource = static_cast<const TClass*>(source);
		pTarget->*PtrToMember = pSource->*PtrToMember;
	}
#endif
};


template <typename TClass, typename TType, TType TClass::*PtrToMember>
class MemeberValueChangeParamCommand : public Ogre::ParamCommand
{
public:
	virtual Ogre::String doGet(const void* target) const 
	{
		 const TClass* pObj = static_cast<const TClass*>(target);
		 return __ToOgreString(pObj->*PtrToMember);
	}

    virtual void doSet(void* target, const Ogre::String& val) 
	{
		 TClass* pObj = static_cast<TClass*>(target);
		 pObj->*PtrToMember = __FromOgreString<TType>(val);
		 pObj->OnParamChanged();
	}

#if OGRE_STRING_INTERFACE_COPY
    virtual void doCopy(void* target, const void* source)
	{
		TClass* pTarget = static_cast<TClass*>(target);
		const TClass* pSource = static_cast<const TClass*>(source);
		pTarget->*PtrToMember = pSource->*PtrToMember;
		pTarget->OnParamChanged();
	}
#endif
};
