// Copyright 2015-2021 Crytek GmbH / Crytek Group. All rights reserved.

#pragma once

#include "CrySchematyc/FundamentalTypes.h"
#include "CrySchematyc/Env/EnvElementBase.h"
#include "CrySchematyc/Env/Elements/IEnvFunction.h"
#include "CrySchematyc/Reflection/TypeDesc.h"
#include "CrySchematyc/Runtime/RuntimeParamMap.h"
#include "CrySchematyc/Utils/Assert.h"
#include "CrySchematyc/Utils/Any.h"
#include "CrySchematyc/Utils/AnyArray.h"
#include "CrySchematyc/Utils/EnumFlags.h"
#include "CrySchematyc/Utils/StringUtils.h"
#include "CrySchematyc/Utils/TypeName.h"

#define SCHEMATYC_MAKE_ENV_FUNCTION(functionPtr, guid, name) Schematyc::EnvFunction::MakeShared(functionPtr, guid, name, SCHEMATYC_SOURCE_FILE_INFO)

namespace Schematyc
{

// Forward declare interfaces.
struct IEnvAction;
struct IEnvComponent;

namespace EnvFunctionUtils
{

struct SBinding;

enum class EParamFlags
{
	AvailableInput  = BIT(0), // Parameter can be bound to input.
	BoundToInput    = BIT(1), // Parameter is bound to input.
	AvailableOutput = BIT(2), // Parameter can be bound to output.
	BoundToOutput   = BIT(3)  // Parameter is bound to output.
};

typedef CEnumFlags<EParamFlags> ParamFlags;

template <typename RETURN_TYPE>
using StubWrapperPtr = RETURN_TYPE(*)(const SBinding&, CRuntimeParamMap& params, void* pObject);
using StubPtr = StubWrapperPtr<void>;


template<typename TYPE> struct SParamTraits
{
	static const bool IsSupported = !std::is_pointer<TYPE>::value;
	static const bool IsConst = std::is_const<typename std::remove_reference<TYPE>::type>::value;
	static const bool IsReference = std::is_reference<TYPE>::value;
	static const bool IsInput = !IsReference || IsConst;

	using UnqualifiedType = typename std::decay<TYPE>::type;
	using ProxyType = 
		typename std::conditional<!IsReference, 
			const TYPE&,
			TYPE
		>::type;
};

struct SParamBinding
{
	inline SParamBinding()
		: idx(InvalidIdx)
		, id(InvalidId)
		, pArrayTypeDesc(nullptr)
	{}

	ParamFlags             flags;
	uint32                 idx;
	uint32                 id;
	string                 name;
	string                 description;
	CAnyValuePtr           pData;
	const CCommonTypeDesc* pArrayTypeDesc;
};

struct SBinding
{
	inline SBinding()
		: flags(EEnvFunctionFlags::None)
		, pObjectTypeDesc(nullptr)
	{}

	uint8   pFunction[sizeof(void*) * 4];
	StubPtr pStub;
						    
	EnvFunctionFlags                flags;
	const CCommonTypeDesc*          pObjectTypeDesc;
	DynArray<SParamBinding, uint32> params;
	DynArray<uint32, uint32>        inputs;
	DynArray<uint32, uint32>        outputs;
};

namespace detail
{
	template <typename...TYPES>
	struct SimpleTypeList
	{};

	template <typename TYPE>
	struct SParamInitializer
	{
		static_assert(sizeof(TYPE) == -1, "Internal initializer called without SimpleTypeList<>");
	};

	template <>
	struct SParamInitializer<SimpleTypeList<>>
	{
		// No parameters
		static void Initialize(SBinding& binding, int index) {}
	};

	template <typename TYPE>
	struct SParamInitializer<SimpleTypeList<TYPE>>
	{
		static void Initialize(SBinding& binding, int index)
		{
			typedef SParamTraits<TYPE> Traits;

			static_assert(Traits::IsSupported, "Parameter type is not supported!");
			static_assert(std::is_default_constructible<typename Traits::UnqualifiedType>::value, "Parameter type must provide default constructor!");

			SParamBinding paramBinding;
			paramBinding.pData = CAnyValue::MakeShared(typename Traits::UnqualifiedType());

			if (Traits::IsInput)
			{
				paramBinding.flags = EParamFlags::AvailableInput;
			}
			else
			{
				paramBinding.flags = EParamFlags::AvailableOutput;
			}

			binding.params.push_back(paramBinding);
		}
	};

	template <typename HEAD, typename...REST>
	struct SParamInitializer<SimpleTypeList<HEAD, REST...>> : SParamInitializer<SimpleTypeList<REST...>>
	{
		using HeadInit = SParamInitializer<SimpleTypeList<HEAD>>;
		using RecurseInit = SParamInitializer<SimpleTypeList<REST...>>;

		static void Initialize(SBinding& binding, int index)
		{
			HeadInit::Initialize(binding, index);
			RecurseInit::Initialize(binding, ++index);
		}
	};
} // detail

template <typename T>
inline void InitReturnParam(SBinding& binding)
{
	typedef SParamTraits<T> Traits;

	static_assert(Traits::IsSupported, "Parameter type is not supported");
	static_assert(std::is_default_constructible<typename Traits::UnqualifiedType>::value, "Parameter type must provide default constructor!");

	SParamBinding paramBinding;
	paramBinding.flags = EParamFlags::AvailableOutput;
	paramBinding.pData = CAnyValue::MakeShared(typename Traits::UnqualifiedType());

	binding.params.push_back(paramBinding);
}

template <>
inline void InitReturnParam<void>(SBinding& binding)
{
	binding.params.emplace_back();
}

template <typename RETURN_TYPE, typename...TYPES>
struct SParamInitializer : detail::SParamInitializer<detail::SimpleTypeList<TYPES...>>
{
	using Initializer = detail::SParamInitializer<detail::SimpleTypeList<TYPES...>>;

	static const int  ParamCount = sizeof...(TYPES) + 1;

	static void Initialize(SBinding& binding)
	{
		binding.params.reserve(ParamCount + 1);

		InitReturnParam<RETURN_TYPE>(binding);

		Initializer::Initialize(binding, 1);
	}
};

inline void BindInput(SBinding& binding, uint32 paramIdx, uint32 id, const char* szName, const char* szDescription, const CAnyValuePtr& pData)
{
	// #SchematycTODO : Make sure id is unique and name is valid!!!

	SCHEMATYC_CORE_ASSERT_FATAL(szName);

	SParamBinding& param = binding.params.at(paramIdx);
	SCHEMATYC_CORE_ASSERT_FATAL(param.flags.Check(EParamFlags::AvailableInput));

	param.flags.Remove({ EParamFlags::AvailableInput, EParamFlags::AvailableOutput });
	param.flags.Add(EParamFlags::BoundToInput);

	param.idx = binding.inputs.size();
	param.id = id;
	param.name = szName;
	param.description = szDescription;

	if (pData)
	{
		param.pData = pData;
	}

	binding.inputs.push_back(paramIdx);
}

inline void BindInputArrayType(SBinding& binding, uint32 paramIdx, uint32 id, const char* szName, const char* szDescription, const CCommonTypeDesc& valueTypeDesc)
{
	// #SchematycTODO : Make sure id is unique and name is valid!!!

	SCHEMATYC_CORE_ASSERT_FATAL(szName);

	SParamBinding& param = binding.params.at(paramIdx);
	SCHEMATYC_CORE_ASSERT_FATAL(param.flags.Check(EParamFlags::AvailableInput));

	param.flags.Remove({ EParamFlags::AvailableInput, EParamFlags::AvailableOutput });
	param.flags.Add(EParamFlags::BoundToInput);

	param.idx = binding.inputs.size();
	param.id = id;
	param.name = szName;
	param.description = szDescription;
	param.pArrayTypeDesc = &valueTypeDesc;

	binding.inputs.push_back(paramIdx);
}

inline void BindOutput(SBinding& binding, uint32 paramIdx, uint32 id, const char* szName, const char* szDescription)
{
	// #SchematycTODO : Make sure id is unique and name is valid!!!

	SCHEMATYC_CORE_ASSERT_FATAL(szName);

	SParamBinding& param = binding.params.at(paramIdx);
	SCHEMATYC_CORE_ASSERT_FATAL(param.flags.Check(EParamFlags::AvailableOutput));

	param.flags.Remove({ EParamFlags::AvailableInput, EParamFlags::AvailableOutput });
	param.flags.Add(EParamFlags::BoundToOutput);

	param.idx = binding.outputs.size();
	param.id = id;
	param.name = szName;
	param.description = szDescription;

	binding.outputs.push_back(paramIdx);
}

inline bool ValidateBinding(const SBinding& binding)
{
	for (uint32 paramIdx = 0; paramIdx < static_cast<uint32>(binding.params.size()); ++paramIdx)
	{
		if (binding.params.at(paramIdx).flags.CheckAny({ EParamFlags::AvailableInput, EParamFlags::AvailableOutput }))
		{
			return false;
		}
	}
	return true;
}

template<typename TYPE> struct SParamReader
{
	using Traits     = SParamTraits<TYPE>;
	using ReturnType = typename Traits::ProxyType;
	using CastType   = typename Traits::UnqualifiedType;

	static inline ReturnType ReadParam(const SBinding& binding, uint32 paramIdx, CRuntimeParamMap& params)
	{
		const SParamBinding& param = binding.params.at(paramIdx);
		return DynamicCast<CastType>(*GetParam(param, params));
	}

private:
	template <bool IS_INPUT = Traits::IsInput, typename std::enable_if<IS_INPUT>::type* = nullptr>
	static inline CAnyConstPtr GetParam(const SParamBinding& paramBinding, CRuntimeParamMap& params)
	{
		SCHEMATYC_CORE_ASSERT_FATAL(paramBinding.flags.Check(EParamFlags::BoundToInput));
		return params.GetInput(CUniqueId::FromUInt32(paramBinding.id));
	}

	template <bool IS_OUTPUT = !Traits::IsInput, typename std::enable_if<IS_OUTPUT>::type* = nullptr>
	static inline CAnyPtr GetParam(const SParamBinding& paramBinding, CRuntimeParamMap& params)
	{
		SCHEMATYC_CORE_ASSERT_FATAL(paramBinding.flags.Check(EParamFlags::BoundToOutput));
		return params.GetOutput(CUniqueId::FromUInt32(paramBinding.id));
	}
};

template<> struct SParamReader<CAnyArrayPtr>
{
	using ReturnType = CAnyArrayPtr;

	static inline CAnyArrayPtr ReadParam(const SBinding& binding, uint32 paramIdx, CRuntimeParamMap& params)
	{
		const SParamBinding& param = binding.params.at(paramIdx);
		SCHEMATYC_CORE_ASSERT_FATAL(param.flags.Check(EParamFlags::BoundToInput));
		CAnyConstPtr pInput = params.GetInput(CUniqueId::FromUInt32(param.id));
		return pInput ? DynamicCast<CAnyArrayPtr>(*pInput) : CAnyArrayPtr();
	}
};

template<typename TYPE> 
inline typename SParamReader<TYPE>::ReturnType ReadParam(const SBinding& binding, uint32 paramIdx, CRuntimeParamMap& params)
{
	return SParamReader<TYPE>::ReadParam(binding, paramIdx, params);
}

template<typename RETURN_TYPE>
inline void ExecuteStub(const SBinding& binding, CRuntimeParamMap& params, void* pObject, StubWrapperPtr<RETURN_TYPE> pStub)
{
	const SParamBinding& param = binding.params[0];
	SCHEMATYC_CORE_ASSERT_FATAL(param.flags.Check(EParamFlags::BoundToOutput));
	DynamicCast<typename SParamTraits<RETURN_TYPE>::UnqualifiedType>(*params.GetOutput(CUniqueId::FromUInt32(param.id))) = pStub(binding, params, pObject);
}

template<>
inline void ExecuteStub<void>(const SBinding& binding, CRuntimeParamMap& params, void* pObject, StubWrapperPtr<void> pStub)
{
	pStub(binding, params, pObject);
}

template<typename FUNCTION_PTR_TYPE> struct SBinder
{
	static const bool IsSupported = false;
};

// PARAM0 (*)(PARAMS...)
template<typename PARAM0, typename...PARAMS>
struct SBinder<PARAM0(*)(PARAMS...)>
{
	static constexpr auto seq = std::make_index_sequence<sizeof...(PARAMS)>{};
	typedef PARAM0(*FunctionPtr)(PARAMS...);

	static inline void Bind(SBinding& binding, FunctionPtr pFunction)
	{
		static_assert(sizeof(FunctionPtr) <= sizeof(binding.pFunction), "Function pointer exceeds maximum size!");

		memcpy(binding.pFunction, &pFunction, sizeof(FunctionPtr));

		binding.pStub = &SBinder::Stub;

		SParamInitializer<PARAM0, PARAMS...>::Initialize(binding);
	}

	static void Stub(const SBinding& binding, CRuntimeParamMap& params, void* pObject)
	{
		ExecuteStub<PARAM0>(binding, params, pObject, &SBinder::StubWrapper);
	}

	static PARAM0 StubWrapper(const SBinding& binding, CRuntimeParamMap& params, void* pObject)
	{
		return SBinder::Executor(binding, params, pObject, seq);
	}

	template <size_t... Is>
	static PARAM0 Executor(const SBinding& binding, CRuntimeParamMap& params, void* pObject, std::index_sequence<Is...>)
	{
		FunctionPtr pFunction = *reinterpret_cast<const FunctionPtr*>(binding.pFunction);
		return (*pFunction)(ReadParam<PARAMS>(binding, Is + 1, params)...);
	}

	static const bool IsSupported = true;
};

// PARAM0 (OBJECT::*)(PARAMS...)
template<typename OBJECT, typename PARAM0, typename...PARAMS>
struct SBinder<PARAM0(OBJECT::*)(PARAMS...)>
{
	static constexpr auto seq = std::make_index_sequence<sizeof...(PARAMS)>{};
	typedef PARAM0(OBJECT::* FunctionPtr)(PARAMS...);

	static inline void Bind(SBinding& binding, FunctionPtr pFunction)
	{
		static_assert(sizeof(FunctionPtr) <= sizeof(binding.pFunction), "Function pointer exceeds maximum size!");

		memcpy(binding.pFunction, &pFunction, sizeof(FunctionPtr));

		binding.pStub = &SBinder::Stub;
		binding.flags = EEnvFunctionFlags::Member;
		binding.pObjectTypeDesc = &GetTypeDesc<OBJECT>();

		SParamInitializer<PARAM0, PARAMS...>::Initialize(binding);
	}

	static void Stub(const SBinding& binding, CRuntimeParamMap& params, void* pObject)
	{
		ExecuteStub<PARAM0>(binding, params, pObject, &SBinder::StubWrapper);
	}

	static PARAM0 StubWrapper(const SBinding& binding, CRuntimeParamMap& params, void* pObject)
	{
		return SBinder::Executor(binding, params, pObject, seq);
	}

	template <size_t... Is>
	static PARAM0 Executor(const SBinding& binding, CRuntimeParamMap& params, void* pObject, std::index_sequence<Is...>)
	{
		FunctionPtr pFunction = *reinterpret_cast<const FunctionPtr*>(binding.pFunction);
		return (static_cast<OBJECT*>(pObject)->*pFunction)(ReadParam<PARAMS>(binding, Is + 1, params)...);
	}

	static const bool IsSupported = true;
};

// PARAM0 (OBJECT::*)(PARAMS...) const
template<typename OBJECT, typename PARAM0, typename...PARAMS>
struct SBinder<PARAM0(OBJECT::*)(PARAMS...) const>
{
	static constexpr auto seq = std::make_index_sequence<sizeof...(PARAMS)>{};
	typedef PARAM0(OBJECT::* FunctionPtr)(PARAMS...) const;

	static inline void Bind(SBinding& binding, FunctionPtr pFunction)
	{
		static_assert(sizeof(FunctionPtr) <= sizeof(binding.pFunction), "Function pointer exceeds maximum size!");

		memcpy(binding.pFunction, &pFunction, sizeof(FunctionPtr));

		binding.pStub = &SBinder::Stub;
		binding.flags = { EEnvFunctionFlags::Member, EEnvFunctionFlags::Const };
		binding.pObjectTypeDesc = &GetTypeDesc<OBJECT>();

		SParamInitializer<PARAM0, PARAMS...>::Initialize(binding);
	}

	static void Stub(const SBinding& binding, CRuntimeParamMap& params, void* pObject)
	{
		ExecuteStub<PARAM0>(binding, params, pObject, &SBinder::StubWrapper);
	}

	static PARAM0 StubWrapper(const SBinding& binding, CRuntimeParamMap& params, void* pObject)
	{
		return SBinder::Executor(binding, params, pObject, seq);
	}

	template <size_t... Is>
	static PARAM0 Executor(const SBinding& binding, CRuntimeParamMap& params, void* pObject, std::index_sequence<Is...>)
	{
		FunctionPtr pFunction = *reinterpret_cast<const FunctionPtr*>(binding.pFunction);
		return (static_cast<const OBJECT*>(pObject)->*pFunction)(ReadParam<PARAMS>(binding, Is + 1, params)...);
	}

	static const bool IsSupported = true;
};

} // EnvFunctionUtils

class CEnvFunction : public CEnvElementBase<IEnvFunction>
{
public:

	template<typename FUNCTION_PTR_TYPE> inline CEnvFunction(FUNCTION_PTR_TYPE pFunction, const CryGUID& guid, const char* szName, const SSourceFileInfo& sourceFileInfo)
		: CEnvElementBase(guid, szName, sourceFileInfo)
	{
		typedef EnvFunctionUtils::SBinder<FUNCTION_PTR_TYPE> FunctionBinder;

		static_assert(FunctionBinder::IsSupported, "Unsupported function signature!");

		FunctionBinder::Bind(m_binding, pFunction);
	}

	// IEnvElement

	virtual bool IsValidScope(IEnvElement& scope) const override
	{
		switch (scope.GetType())
		{
		case EEnvElementType::Module:
		case EEnvElementType::DataType:
		case EEnvElementType::Class:
		case EEnvElementType::Component:
		case EEnvElementType::Action:
			{
				return true;
			}
		default:
			{
				return false;
			}
		}
	}

	// ~IEnvElement

	// IEnvFunction

	virtual bool Validate() const override
	{
		return EnvFunctionUtils::ValidateBinding(m_binding);
	}

	virtual EnvFunctionFlags GetFunctionFlags() const override
	{
		return m_binding.flags;
	}

	virtual const CCommonTypeDesc* GetObjectTypeDesc() const override
	{
		return m_binding.pObjectTypeDesc;
	}

	virtual uint32 GetInputCount() const override
	{
		return m_binding.inputs.size();
	}

	virtual uint32 GetInputId(uint32 inputIdx) const override
	{
		return inputIdx < m_binding.inputs.size() ? m_binding.params.at(m_binding.inputs.at(inputIdx)).id : InvalidId;
	}

	virtual const char* GetInputName(uint32 inputIdx) const override
	{
		return inputIdx < m_binding.inputs.size() ? m_binding.params.at(m_binding.inputs.at(inputIdx)).name.c_str() : "";
	}

	virtual const char* GetInputDescription(uint32 inputIdx) const override
	{
		return inputIdx < m_binding.inputs.size() ? m_binding.params.at(m_binding.inputs.at(inputIdx)).description.c_str() : "";
	}

	virtual CAnyConstPtr GetInputData(uint32 inputIdx) const override
	{
		return inputIdx < m_binding.inputs.size() ? m_binding.params.at(m_binding.inputs.at(inputIdx)).pData.get() : nullptr;
	}

	virtual const CCommonTypeDesc* GetInputArrayType(uint32 inputIdx) const override
	{
		return inputIdx < m_binding.inputs.size() ? m_binding.params.at(m_binding.inputs.at(inputIdx)).pArrayTypeDesc : nullptr;
	}

	virtual uint32 GetOutputCount() const override
	{
		return m_binding.outputs.size();
	}

	virtual uint32 GetOutputId(uint32 outputIdx) const override
	{
		return outputIdx < m_binding.outputs.size() ? m_binding.params.at(m_binding.outputs.at(outputIdx)).id : InvalidId;
	}

	virtual const char* GetOutputName(uint32 outputIdx) const override
	{
		return outputIdx < m_binding.outputs.size() ? m_binding.params.at(m_binding.outputs.at(outputIdx)).name.c_str() : "";
	}

	virtual const char* GetOutputDescription(uint32 outputIdx) const override
	{
		return outputIdx < m_binding.outputs.size() ? m_binding.params.at(m_binding.outputs.at(outputIdx)).description.c_str() : "";
	}

	virtual CAnyConstPtr GetOutputData(uint32 outputIdx) const override
	{
		return outputIdx < m_binding.outputs.size() ? m_binding.params.at(m_binding.outputs.at(outputIdx)).pData.get() : nullptr;
	}

	virtual void Execute(CRuntimeParamMap& params, void* pObject) const override
	{
		if (m_binding.pStub)
		{
			(*m_binding.pStub)(m_binding, params, pObject);
		}
	}

	// ~IEnvFunction

	inline void SetFlags(EnvFunctionFlags flags)
	{
		const EnvFunctionFlags filter = { EEnvFunctionFlags::Pure, EEnvFunctionFlags::Construction };
		m_binding.flags.SetWithFilter(flags, filter);
	}

	inline void BindInput(uint32 paramIdx, uint32 id, const char* szName, const char* szDescription = nullptr)
	{
		EnvFunctionUtils::BindInput(m_binding, paramIdx, id, szName, szDescription, CAnyValuePtr());
	}

	template<typename TYPE> inline void BindInputArrayType(uint32 paramIdx, uint32 id, const char* szName, const char* szDescription = nullptr, const TYPE& value = TYPE())
	{
		EnvFunctionUtils::BindInputArrayType(m_binding, paramIdx, id, szName, szDescription, GetTypeDesc<TYPE>());
	}

	template<typename TYPE> inline void BindInput(uint32 paramIdx, uint32 id, const char* szName, const char* szDescription, const TYPE& value)
	{
		EnvFunctionUtils::BindInput(m_binding, paramIdx, id, szName, szDescription, CAnyValue::MakeShared(static_cast<const TYPE&>(value)));
	}

	inline void BindOutput(uint32 paramIdx, uint32 id, const char* szName, const char* szDescription = nullptr)
	{
		EnvFunctionUtils::BindOutput(m_binding, paramIdx, id, szName, szDescription);
	}

private:

	EnvFunctionUtils::SBinding m_binding;
};

namespace EnvFunction
{

template<typename FUNCTION_PTR_TYPE> inline std::shared_ptr<CEnvFunction> MakeShared(FUNCTION_PTR_TYPE pFunction, const CryGUID& guid, const char* szName, const SSourceFileInfo& sourceFileInfo)
{
	return std::make_shared<CEnvFunction>(pFunction, guid, szName, sourceFileInfo);
}

} // EnvFunction
} // Schematyc
