// Copyright 2016-2021 Crytek GmbH / Crytek Group. All rights reserved.

// #SchematycTODO : Separate into two classes: CAnyArray and CAnyArrayPtr!!!
// #SchematycTODO : Implement comparison operators?
// #SchematycTODO : Do we need to worry about data alignment?
// #SchematycTODO : Implement move semantics?

#pragma once

#include <CrySerialization/DynArray.h>
#include <CrySerialization/Forward.h>

#include "CrySchematyc/Reflection/TypeDesc.h"
#include "CrySchematyc/Utils/Any.h"
#include "CrySchematyc/Utils/Assert.h"
#include "CrySchematyc/Utils/IString.h"

namespace Schematyc
{

class CAnyArray
{
public:

	inline CAnyArray(const CCommonTypeDesc& typeDesc)
		: m_typeDesc(typeDesc)
		, m_capacity(0)
		, m_size(0)
		, m_pBegin(nullptr)
	{}

	inline CAnyArray(const CAnyArray& rhs)
		: m_typeDesc(rhs.m_typeDesc)
		, m_capacity(0)
		, m_size(0)
		, m_pBegin(nullptr)
	{
		Reserve(rhs.m_capacity);
		CopyConstruct(rhs.m_pBegin, rhs.m_size, m_pBegin);
	}

	inline ~CAnyArray()
	{
		if (m_pBegin)
		{
			Destruct(m_pBegin, m_size);
			CryModuleFree(m_pBegin);
		}
	}

	inline size_t GetSize() const
	{
		return m_size;
	}

	inline uint32 GetCapacity() const
	{
		return m_capacity;
	}

	inline void Reserve(uint32 capacity)
	{
		if (capacity > m_capacity)
		{
			const uint32 minCapacity = 8;
			const uint32 growthFactor = 2;
			capacity = std::max({ minCapacity, capacity, capacity * growthFactor });
			
			uint8* pBegin = static_cast<uint8*>(CryModuleMalloc(capacity * m_typeDesc.GetSize()));
			Move(m_pBegin, m_size, pBegin);
			CryModuleFree(m_pBegin);

			m_pBegin = pBegin;
			m_capacity = capacity;
		}
	}

	inline void PushBack(const CAnyConstRef& value)
	{
		CRY_ASSERT(value.GetTypeDesc() == m_typeDesc, "Mixing types in CAnyArray!");
		if (value.GetTypeDesc() == m_typeDesc)
		{
			Reserve(GetSize() + 1);

			STypeOperators::CopyConstruct copyConstruct = m_typeDesc.GetOperators().copyConstruct;
			SCHEMATYC_CORE_ASSERT(copyConstruct);

			(*copyConstruct)(m_pBegin + (m_size * m_typeDesc.GetSize()), value.GetValue());

			++m_size;
		}
	}

	inline void PopBack()
	{
		if (m_size == 0)
			return;

		STypeOperators::Destruct destruct = m_typeDesc.GetOperators().destruct;
		SCHEMATYC_CORE_ASSERT(destruct);

		(*destruct)(m_pBegin + ((m_size-1) * m_typeDesc.GetSize()));

		--m_size;
	}

	inline void RemoveByIdx(uint32 idx)
	{
		if (idx >= m_size)
			return;

		if (idx == (m_size - 1))
		{
			PopBack();
		}
		else
		{
			// #SchematycTODO : Remove elements rather than destroying and re-constructing?

			STypeOperators::Destruct destruct = m_typeDesc.GetOperators().destruct;
			SCHEMATYC_CORE_ASSERT(destruct);

			STypeOperators::CopyConstruct copyConstruct = m_typeDesc.GetOperators().copyConstruct;
			SCHEMATYC_CORE_ASSERT(copyConstruct);

			const size_t stride = m_typeDesc.GetSize();
			for (size_t i = idx; i < m_size-1; i++)
			{
				uint8* pCur = m_pBegin + (idx * stride);
				uint8* pNext = pCur + stride;

				(*destruct)(pCur);
				(*copyConstruct)(pCur, pNext);
			}

			--m_size;
		}
	}

	inline void RemoveByValue(const CAnyConstRef& value)
	{
		CRY_ASSERT(value.GetTypeDesc() == m_typeDesc, "Mixing types in CAnyArray!");
		if (value.GetTypeDesc() == m_typeDesc)
		{
			STypeOperators::Equals equals = m_typeDesc.GetOperators().equals;
			SCHEMATYC_CORE_ASSERT(equals);

			for (uint32 idx = 0, size = GetSize(); idx < size; )
			{
				if ((*equals)((*this)[idx].GetValue(), value.GetValue()))
				{
					RemoveByIdx(idx);
					--size;
				}
				else
				{
					++idx;
				}
			}
		}
	}

	inline void Clear()
	{
		Destruct(m_pBegin, m_size);
	}

	inline void ToString(IString& output) const
	{
		output.assign("{ ");

		STypeOperators::ToString toString = m_typeDesc.GetOperators().toString;
		if (toString)
		{
			for (uint32 idx = 0; idx < m_size; ++idx)
			{
				CStackString temp;
				(*toString)(temp, (*this)[idx].GetValue());
				output.append(temp.c_str());
				output.append(", ");
			}
			output.TrimRight(", ");
		}

		output.append(" }");
	}

	inline CAnyRef operator[](uint32 idx)
	{
		return CAnyRef(m_typeDesc, m_pBegin + (idx * m_typeDesc.GetSize()));
	}

	inline CAnyConstRef operator[](uint32 idx) const
	{
		return CAnyConstRef(m_typeDesc, m_pBegin + (idx * m_typeDesc.GetSize()));
	}

	//inline CAnyArray& operator = (const CAnyArray& rhs);
	//inline bool operator == (const CAnyArray& rhs) const
	//inline bool operator != (const CAnyArray& rhs) const

	static inline void ReflectType(CTypeDesc<CAnyArray>& desc)
	{
		desc.SetGUID("f6af4221-8344-49e9-9ef8-5f7e8144aa57"_cry_guid);
		desc.SetToStringOperator<&CAnyArray::ToString>();
	}

private:

	void CopyConstruct(const uint8* pSrc, const size_t size, uint8* pDst)
	{
		STypeOperators::CopyConstruct copyConstruct = m_typeDesc.GetOperators().copyConstruct;
		SCHEMATYC_CORE_ASSERT(copyConstruct);

		for (size_t idx = 0; idx < size; ++idx)
		{
			(*copyConstruct)(pDst + (idx * m_typeDesc.GetSize()), pSrc + (idx * m_typeDesc.GetSize()));
			++m_size;
		}
	}

	void Move(uint8* pSrc, size_t size, uint8* pDst) const
	{
		STypeOperators::CopyConstruct copyConstruct = m_typeDesc.GetOperators().copyConstruct;
		SCHEMATYC_CORE_ASSERT(copyConstruct);

		STypeOperators::Destruct destruct = m_typeDesc.GetOperators().destruct;
		SCHEMATYC_CORE_ASSERT(destruct);

		for (size_t idx = 0; idx < size; idx++)
		{
			(*copyConstruct)(pDst + (idx * m_typeDesc.GetSize()), pSrc + (idx * m_typeDesc.GetSize()));
			(*destruct)(pSrc + (idx * m_typeDesc.GetSize()));
		}
	}

	void Destruct(uint8* pBegin, size_t size)
	{
		STypeOperators::Destruct destruct = m_typeDesc.GetOperators().destruct;
		SCHEMATYC_CORE_ASSERT(destruct);

		for (size_t idx = 0; idx < size; ++idx)
		{
			(*destruct)(pBegin + (idx * m_typeDesc.GetSize()));
		}

		m_size = 0;
	}

private:

	const CCommonTypeDesc& m_typeDesc;   // #SchematycTODO : Rather than storing type info could we just store size, copyConstruct and destruct?
	uint32                 m_capacity;
	size_t                 m_size;
	uint8*                 m_pBegin;
};

class CAnyArrayPtr // #SchematycTODO : Create more generic pointer class for storing all types of value on scratchpad? Or just use CAnyPtr?
{
public:

	inline CAnyArrayPtr(CAnyArray* pArray = nullptr)
		: m_pArray(pArray)
	{}

	inline CAnyArrayPtr(const CAnyArrayPtr& rhs)
		: m_pArray(rhs.m_pArray)
	{}

	explicit inline operator bool() const
	{
		return m_pArray != nullptr;
	}

	inline CAnyArray* operator->()
	{
		return m_pArray;
	}

	inline const CAnyArray* operator->() const
	{
		return m_pArray;
	}

	inline CAnyArray& operator*()
	{
		SCHEMATYC_CORE_ASSERT(m_pArray);
		return *m_pArray;
	}

	inline const CAnyArray& operator*() const
	{
		SCHEMATYC_CORE_ASSERT(m_pArray);
		return *m_pArray;
	}

	CAnyArrayPtr& operator=(const CAnyArrayPtr& rhs)
	{
		m_pArray = rhs.m_pArray;
		return *this;
	}

	static inline void ReflectType(CTypeDesc<CAnyArrayPtr>& desc)
	{
		desc.SetGUID("9500b20f-4264-4a09-a7ec-6c8136113369"_cry_guid);
	}

private:

	CAnyArray* m_pArray;
};

}   // Schematyc
