/*$T MapServer/Server/Base/HashMap.h GC 1.140 10/10/07 10:07:20 */


/*$6
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 */


#ifndef __HASH_MAP_H__
#define __HASH_MAP_H__

#include "TypeDefine.h"

#ifdef __LINUX__
#include <ext/hash_map>
#else
#include <hash_map>
#endif


// template <typename KEY,typename VALUE>
// class HashMap
// {
// public:
// 
// #ifdef __WINDOWS__
// 	typedef typename stdext::hash_map<KEY,VALUE>	IDTableHashMap;
// #else
// 	typedef typename __gnu_cxx::hash_map<KEY,VALUE>	IDTableHashMap;
// #endif
// 
// 	typedef typename IDTableHashMap::iterator IDTableIterator;
// 	typedef typename IDTableHashMap::value_type IDTableValue;
// 	
// 	HashMap()
// 	{
// 	}
// 
// 	~HashMap()
// 	{
// 	}
// 
// 	BOOL Add(KEY id, VALUE v)
// 	{
// 		__GUARD__ 
// 		m_IDTableHashMap.insert(typename IDTableValue(id, v));
// 		return TRUE;
// 		__UNGUARD__ 
// 		return FALSE;
// 	}
// 
// 	VALUE Get(KEY id)
// 	{
// 		__GUARD__ 
// 		typename IDTableIterator it = m_IDTableHashMap.find(id);
// 		if(it != m_IDTableHashMap.end()) 
// 			return it->second;
// 		return (VALUE)(0);
// 		__UNGUARD__ 
// 		return (VALUE)(0);
// 	}
// 
// 	BOOL GetValue(KEY id,VALUE& v)
// 	{
// 		__GUARD__ 
// 		typename IDTableIterator it = m_IDTableHashMap.find(id);
// 		if(it != m_IDTableHashMap.end())
// 		{
// 			v = it->second;
// 			return TRUE;
// 		}
// 		return FALSE;
// 		__UNGUARD__ 
// 		return FALSE;
// 	}
// 
// 	BOOL Remove(KEY id)
// 	{
// 		__GUARD__ 
// 		typename IDTableIterator it = m_IDTableHashMap.find(id);
// 		if(it != m_IDTableHashMap.end())
// 		{
// 			m_IDTableHashMap.erase(it);
// 			return TRUE;
// 		}
// 		return FALSE;
// 		__UNGUARD__ 
// 		return FALSE;	
// 	}
// 
// 	void Clear()
// 	{
// 		__GUARD__ 
// 		m_IDTableHashMap.clear();
// 		__UNGUARD__	
// 	}
// 
// 	void ClearAndDestroy()
// 	{
// 		__GUARD__ 
// 		typename IDTableIterator it = m_IDTableHashMap.begin();
// 		while(it != m_IDTableHashMap.end())
// 		{
// 			delete it->second;
// 			++it;
// 		}
// 
// 		m_IDTableHashMap.clear();
// 		__UNGUARD__	
// 	}
// 
// 	uint32 GetCount()
// 	{
// 		return(uint32) m_IDTableHashMap.size();
// 	}
// 
// 	IDTableIterator Begin()
// 	{
// 		m_CurrentIterator = m_IDTableHashMap.begin();
// 		return m_CurrentIterator;
// 	}
// 
// 	IDTableIterator End()
// 	{
// 		return m_IDTableHashMap.end();
// 	}
// 
// 
// private:
// 	IDTableHashMap m_IDTableHashMap;
// 	IDTableIterator m_CurrentIterator;
// };

#endif
