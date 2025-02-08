/* THIS FILE IS GENERATED DO NOT EDIT */
#ifndef GDVIRTUAL_GEN_H
#define GDVIRTUAL_GEN_H

#include "core/object/script_instance.h"

#ifdef TOOLS_ENABLED
#define GDVIRTUAL_TRACK(m_virtual, m_initialized)\
	if (_get_extension()->reloadable) {\
		VirtualMethodTracker *tracker = memnew(VirtualMethodTracker);\
		tracker->method = (void **)&m_virtual;\
		tracker->initialized = &m_initialized;\
		tracker->next = virtual_method_list;\
		virtual_method_list = tracker;\
	}
#else
#define GDVIRTUAL_TRACK(m_virtual, m_initialized)
#endif

/* 0 Arguments */

#define GDVIRTUAL0(m_name)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call() {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			_script_instance->callp(_gdvirtual_##m_name##_sn, nullptr, 0, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, nullptr, nullptr);\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), nullptr, nullptr);\
			}\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL;\
		return method_info;\
	}

#define GDVIRTUAL0R(m_ret, m_name)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_ret &r_ret) {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant ret = _script_instance->callp(_gdvirtual_##m_name##_sn, nullptr, 0, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				r_ret = VariantCaster<m_ret>::cast(ret);\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_ret>::EncodeT ret;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, nullptr, &ret);\
				r_ret = (m_ret)ret;\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), nullptr, &ret);\
				r_ret = (m_ret)ret;\
			}\
			return true;\
		}\
		(void)r_ret;\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL;\
		method_info.return_val = GetTypeInfo<m_ret>::get_class_info();\
		method_info.return_val_metadata = GetTypeInfo<m_ret>::METADATA;\
		return method_info;\
	}

#define GDVIRTUAL0C(m_name)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			_script_instance->callp(_gdvirtual_##m_name##_sn, nullptr, 0, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, nullptr, nullptr);\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), nullptr, nullptr);\
			}\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL | METHOD_FLAG_CONST;\
		return method_info;\
	}

#define GDVIRTUAL0RC(m_ret, m_name)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_ret &r_ret) const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant ret = _script_instance->callp(_gdvirtual_##m_name##_sn, nullptr, 0, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				r_ret = VariantCaster<m_ret>::cast(ret);\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_ret>::EncodeT ret;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, nullptr, &ret);\
				r_ret = (m_ret)ret;\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), nullptr, &ret);\
				r_ret = (m_ret)ret;\
			}\
			return true;\
		}\
		(void)r_ret;\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL | METHOD_FLAG_CONST;\
		method_info.return_val = GetTypeInfo<m_ret>::get_class_info();\
		method_info.return_val_metadata = GetTypeInfo<m_ret>::METADATA;\
		return method_info;\
	}

#define GDVIRTUAL0_REQUIRED(m_name)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call() {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			_script_instance->callp(_gdvirtual_##m_name##_sn, nullptr, 0, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, nullptr, nullptr);\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), nullptr, nullptr);\
			}\
			return true;\
		}\
		ERR_PRINT_ONCE("Required virtual method " + get_class() + "::" + #m_name + " must be overridden before calling.");\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL | METHOD_FLAG_VIRTUAL_REQUIRED;\
		return method_info;\
	}

#define GDVIRTUAL0R_REQUIRED(m_ret, m_name)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_ret &r_ret) {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant ret = _script_instance->callp(_gdvirtual_##m_name##_sn, nullptr, 0, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				r_ret = VariantCaster<m_ret>::cast(ret);\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_ret>::EncodeT ret;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, nullptr, &ret);\
				r_ret = (m_ret)ret;\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), nullptr, &ret);\
				r_ret = (m_ret)ret;\
			}\
			return true;\
		}\
		ERR_PRINT_ONCE("Required virtual method " + get_class() + "::" + #m_name + " must be overridden before calling.");\
		(void)r_ret;\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL | METHOD_FLAG_VIRTUAL_REQUIRED;\
		method_info.return_val = GetTypeInfo<m_ret>::get_class_info();\
		method_info.return_val_metadata = GetTypeInfo<m_ret>::METADATA;\
		return method_info;\
	}

#define GDVIRTUAL0C_REQUIRED(m_name)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			_script_instance->callp(_gdvirtual_##m_name##_sn, nullptr, 0, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, nullptr, nullptr);\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), nullptr, nullptr);\
			}\
			return true;\
		}\
		ERR_PRINT_ONCE("Required virtual method " + get_class() + "::" + #m_name + " must be overridden before calling.");\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL | METHOD_FLAG_CONST | METHOD_FLAG_VIRTUAL_REQUIRED;\
		return method_info;\
	}

#define GDVIRTUAL0RC_REQUIRED(m_ret, m_name)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_ret &r_ret) const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant ret = _script_instance->callp(_gdvirtual_##m_name##_sn, nullptr, 0, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				r_ret = VariantCaster<m_ret>::cast(ret);\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_ret>::EncodeT ret;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, nullptr, &ret);\
				r_ret = (m_ret)ret;\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), nullptr, &ret);\
				r_ret = (m_ret)ret;\
			}\
			return true;\
		}\
		ERR_PRINT_ONCE("Required virtual method " + get_class() + "::" + #m_name + " must be overridden before calling.");\
		(void)r_ret;\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL | METHOD_FLAG_CONST | METHOD_FLAG_VIRTUAL_REQUIRED;\
		method_info.return_val = GetTypeInfo<m_ret>::get_class_info();\
		method_info.return_val_metadata = GetTypeInfo<m_ret>::METADATA;\
		return method_info;\
	}

/* 1 Arguments */

#define GDVIRTUAL1(m_name, m_type1)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1) {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant vargs[1] = { Variant(arg1) };\
			const Variant *vargptrs[1] = { &vargs[0] };\
			_script_instance->callp(_gdvirtual_##m_name##_sn, (const Variant **)vargptrs, 1, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_type1>::EncodeT argval1 = (PtrToArg<m_type1>::EncodeT)arg1;\
			GDExtensionConstTypePtr argptrs[1] = { &argval1 };\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), nullptr);\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), nullptr);\
			}\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL;\
		method_info.arguments.push_back(GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type1>::METADATA);\
		return method_info;\
	}

#define GDVIRTUAL1R(m_ret, m_name, m_type1)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1, m_ret &r_ret) {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant vargs[1] = { Variant(arg1) };\
			const Variant *vargptrs[1] = { &vargs[0] };\
			Variant ret = _script_instance->callp(_gdvirtual_##m_name##_sn, (const Variant **)vargptrs, 1, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				r_ret = VariantCaster<m_ret>::cast(ret);\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_type1>::EncodeT argval1 = (PtrToArg<m_type1>::EncodeT)arg1;\
			GDExtensionConstTypePtr argptrs[1] = { &argval1 };\
			PtrToArg<m_ret>::EncodeT ret;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), &ret);\
				r_ret = (m_ret)ret;\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), &ret);\
				r_ret = (m_ret)ret;\
			}\
			return true;\
		}\
		(void)r_ret;\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL;\
		method_info.return_val = GetTypeInfo<m_ret>::get_class_info();\
		method_info.return_val_metadata = GetTypeInfo<m_ret>::METADATA;\
		method_info.arguments.push_back(GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type1>::METADATA);\
		return method_info;\
	}

#define GDVIRTUAL1C(m_name, m_type1)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1) const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant vargs[1] = { Variant(arg1) };\
			const Variant *vargptrs[1] = { &vargs[0] };\
			_script_instance->callp(_gdvirtual_##m_name##_sn, (const Variant **)vargptrs, 1, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_type1>::EncodeT argval1 = (PtrToArg<m_type1>::EncodeT)arg1;\
			GDExtensionConstTypePtr argptrs[1] = { &argval1 };\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), nullptr);\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), nullptr);\
			}\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL | METHOD_FLAG_CONST;\
		method_info.arguments.push_back(GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type1>::METADATA);\
		return method_info;\
	}

#define GDVIRTUAL1RC(m_ret, m_name, m_type1)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1, m_ret &r_ret) const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant vargs[1] = { Variant(arg1) };\
			const Variant *vargptrs[1] = { &vargs[0] };\
			Variant ret = _script_instance->callp(_gdvirtual_##m_name##_sn, (const Variant **)vargptrs, 1, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				r_ret = VariantCaster<m_ret>::cast(ret);\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_type1>::EncodeT argval1 = (PtrToArg<m_type1>::EncodeT)arg1;\
			GDExtensionConstTypePtr argptrs[1] = { &argval1 };\
			PtrToArg<m_ret>::EncodeT ret;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), &ret);\
				r_ret = (m_ret)ret;\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), &ret);\
				r_ret = (m_ret)ret;\
			}\
			return true;\
		}\
		(void)r_ret;\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL | METHOD_FLAG_CONST;\
		method_info.return_val = GetTypeInfo<m_ret>::get_class_info();\
		method_info.return_val_metadata = GetTypeInfo<m_ret>::METADATA;\
		method_info.arguments.push_back(GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type1>::METADATA);\
		return method_info;\
	}

#define GDVIRTUAL1_REQUIRED(m_name, m_type1)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1) {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant vargs[1] = { Variant(arg1) };\
			const Variant *vargptrs[1] = { &vargs[0] };\
			_script_instance->callp(_gdvirtual_##m_name##_sn, (const Variant **)vargptrs, 1, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_type1>::EncodeT argval1 = (PtrToArg<m_type1>::EncodeT)arg1;\
			GDExtensionConstTypePtr argptrs[1] = { &argval1 };\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), nullptr);\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), nullptr);\
			}\
			return true;\
		}\
		ERR_PRINT_ONCE("Required virtual method " + get_class() + "::" + #m_name + " must be overridden before calling.");\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL | METHOD_FLAG_VIRTUAL_REQUIRED;\
		method_info.arguments.push_back(GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type1>::METADATA);\
		return method_info;\
	}

#define GDVIRTUAL1R_REQUIRED(m_ret, m_name, m_type1)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1, m_ret &r_ret) {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant vargs[1] = { Variant(arg1) };\
			const Variant *vargptrs[1] = { &vargs[0] };\
			Variant ret = _script_instance->callp(_gdvirtual_##m_name##_sn, (const Variant **)vargptrs, 1, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				r_ret = VariantCaster<m_ret>::cast(ret);\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_type1>::EncodeT argval1 = (PtrToArg<m_type1>::EncodeT)arg1;\
			GDExtensionConstTypePtr argptrs[1] = { &argval1 };\
			PtrToArg<m_ret>::EncodeT ret;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), &ret);\
				r_ret = (m_ret)ret;\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), &ret);\
				r_ret = (m_ret)ret;\
			}\
			return true;\
		}\
		ERR_PRINT_ONCE("Required virtual method " + get_class() + "::" + #m_name + " must be overridden before calling.");\
		(void)r_ret;\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL | METHOD_FLAG_VIRTUAL_REQUIRED;\
		method_info.return_val = GetTypeInfo<m_ret>::get_class_info();\
		method_info.return_val_metadata = GetTypeInfo<m_ret>::METADATA;\
		method_info.arguments.push_back(GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type1>::METADATA);\
		return method_info;\
	}

#define GDVIRTUAL1C_REQUIRED(m_name, m_type1)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1) const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant vargs[1] = { Variant(arg1) };\
			const Variant *vargptrs[1] = { &vargs[0] };\
			_script_instance->callp(_gdvirtual_##m_name##_sn, (const Variant **)vargptrs, 1, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_type1>::EncodeT argval1 = (PtrToArg<m_type1>::EncodeT)arg1;\
			GDExtensionConstTypePtr argptrs[1] = { &argval1 };\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), nullptr);\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), nullptr);\
			}\
			return true;\
		}\
		ERR_PRINT_ONCE("Required virtual method " + get_class() + "::" + #m_name + " must be overridden before calling.");\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL | METHOD_FLAG_CONST | METHOD_FLAG_VIRTUAL_REQUIRED;\
		method_info.arguments.push_back(GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type1>::METADATA);\
		return method_info;\
	}

#define GDVIRTUAL1RC_REQUIRED(m_ret, m_name, m_type1)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1, m_ret &r_ret) const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant vargs[1] = { Variant(arg1) };\
			const Variant *vargptrs[1] = { &vargs[0] };\
			Variant ret = _script_instance->callp(_gdvirtual_##m_name##_sn, (const Variant **)vargptrs, 1, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				r_ret = VariantCaster<m_ret>::cast(ret);\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_type1>::EncodeT argval1 = (PtrToArg<m_type1>::EncodeT)arg1;\
			GDExtensionConstTypePtr argptrs[1] = { &argval1 };\
			PtrToArg<m_ret>::EncodeT ret;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), &ret);\
				r_ret = (m_ret)ret;\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), &ret);\
				r_ret = (m_ret)ret;\
			}\
			return true;\
		}\
		ERR_PRINT_ONCE("Required virtual method " + get_class() + "::" + #m_name + " must be overridden before calling.");\
		(void)r_ret;\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL | METHOD_FLAG_CONST | METHOD_FLAG_VIRTUAL_REQUIRED;\
		method_info.return_val = GetTypeInfo<m_ret>::get_class_info();\
		method_info.return_val_metadata = GetTypeInfo<m_ret>::METADATA;\
		method_info.arguments.push_back(GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type1>::METADATA);\
		return method_info;\
	}

/* 2 Arguments */

#define GDVIRTUAL2(m_name, m_type1, m_type2)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1, m_type2 arg2) {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant vargs[2] = { Variant(arg1), Variant(arg2) };\
			const Variant *vargptrs[2] = { &vargs[0], &vargs[1] };\
			_script_instance->callp(_gdvirtual_##m_name##_sn, (const Variant **)vargptrs, 2, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_type1>::EncodeT argval1 = (PtrToArg<m_type1>::EncodeT)arg1;\
			PtrToArg<m_type2>::EncodeT argval2 = (PtrToArg<m_type2>::EncodeT)arg2;\
			GDExtensionConstTypePtr argptrs[2] = { &argval1, &argval2 };\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), nullptr);\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), nullptr);\
			}\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL;\
		method_info.arguments.push_back(GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type1>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type2>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type2>::METADATA);\
		return method_info;\
	}

#define GDVIRTUAL2R(m_ret, m_name, m_type1, m_type2)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1, m_type2 arg2, m_ret &r_ret) {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant vargs[2] = { Variant(arg1), Variant(arg2) };\
			const Variant *vargptrs[2] = { &vargs[0], &vargs[1] };\
			Variant ret = _script_instance->callp(_gdvirtual_##m_name##_sn, (const Variant **)vargptrs, 2, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				r_ret = VariantCaster<m_ret>::cast(ret);\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_type1>::EncodeT argval1 = (PtrToArg<m_type1>::EncodeT)arg1;\
			PtrToArg<m_type2>::EncodeT argval2 = (PtrToArg<m_type2>::EncodeT)arg2;\
			GDExtensionConstTypePtr argptrs[2] = { &argval1, &argval2 };\
			PtrToArg<m_ret>::EncodeT ret;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), &ret);\
				r_ret = (m_ret)ret;\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), &ret);\
				r_ret = (m_ret)ret;\
			}\
			return true;\
		}\
		(void)r_ret;\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL;\
		method_info.return_val = GetTypeInfo<m_ret>::get_class_info();\
		method_info.return_val_metadata = GetTypeInfo<m_ret>::METADATA;\
		method_info.arguments.push_back(GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type1>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type2>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type2>::METADATA);\
		return method_info;\
	}

#define GDVIRTUAL2C(m_name, m_type1, m_type2)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1, m_type2 arg2) const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant vargs[2] = { Variant(arg1), Variant(arg2) };\
			const Variant *vargptrs[2] = { &vargs[0], &vargs[1] };\
			_script_instance->callp(_gdvirtual_##m_name##_sn, (const Variant **)vargptrs, 2, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_type1>::EncodeT argval1 = (PtrToArg<m_type1>::EncodeT)arg1;\
			PtrToArg<m_type2>::EncodeT argval2 = (PtrToArg<m_type2>::EncodeT)arg2;\
			GDExtensionConstTypePtr argptrs[2] = { &argval1, &argval2 };\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), nullptr);\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), nullptr);\
			}\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL | METHOD_FLAG_CONST;\
		method_info.arguments.push_back(GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type1>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type2>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type2>::METADATA);\
		return method_info;\
	}

#define GDVIRTUAL2RC(m_ret, m_name, m_type1, m_type2)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1, m_type2 arg2, m_ret &r_ret) const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant vargs[2] = { Variant(arg1), Variant(arg2) };\
			const Variant *vargptrs[2] = { &vargs[0], &vargs[1] };\
			Variant ret = _script_instance->callp(_gdvirtual_##m_name##_sn, (const Variant **)vargptrs, 2, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				r_ret = VariantCaster<m_ret>::cast(ret);\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_type1>::EncodeT argval1 = (PtrToArg<m_type1>::EncodeT)arg1;\
			PtrToArg<m_type2>::EncodeT argval2 = (PtrToArg<m_type2>::EncodeT)arg2;\
			GDExtensionConstTypePtr argptrs[2] = { &argval1, &argval2 };\
			PtrToArg<m_ret>::EncodeT ret;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), &ret);\
				r_ret = (m_ret)ret;\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), &ret);\
				r_ret = (m_ret)ret;\
			}\
			return true;\
		}\
		(void)r_ret;\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL | METHOD_FLAG_CONST;\
		method_info.return_val = GetTypeInfo<m_ret>::get_class_info();\
		method_info.return_val_metadata = GetTypeInfo<m_ret>::METADATA;\
		method_info.arguments.push_back(GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type1>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type2>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type2>::METADATA);\
		return method_info;\
	}

#define GDVIRTUAL2_REQUIRED(m_name, m_type1, m_type2)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1, m_type2 arg2) {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant vargs[2] = { Variant(arg1), Variant(arg2) };\
			const Variant *vargptrs[2] = { &vargs[0], &vargs[1] };\
			_script_instance->callp(_gdvirtual_##m_name##_sn, (const Variant **)vargptrs, 2, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_type1>::EncodeT argval1 = (PtrToArg<m_type1>::EncodeT)arg1;\
			PtrToArg<m_type2>::EncodeT argval2 = (PtrToArg<m_type2>::EncodeT)arg2;\
			GDExtensionConstTypePtr argptrs[2] = { &argval1, &argval2 };\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), nullptr);\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), nullptr);\
			}\
			return true;\
		}\
		ERR_PRINT_ONCE("Required virtual method " + get_class() + "::" + #m_name + " must be overridden before calling.");\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL | METHOD_FLAG_VIRTUAL_REQUIRED;\
		method_info.arguments.push_back(GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type1>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type2>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type2>::METADATA);\
		return method_info;\
	}

#define GDVIRTUAL2R_REQUIRED(m_ret, m_name, m_type1, m_type2)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1, m_type2 arg2, m_ret &r_ret) {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant vargs[2] = { Variant(arg1), Variant(arg2) };\
			const Variant *vargptrs[2] = { &vargs[0], &vargs[1] };\
			Variant ret = _script_instance->callp(_gdvirtual_##m_name##_sn, (const Variant **)vargptrs, 2, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				r_ret = VariantCaster<m_ret>::cast(ret);\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_type1>::EncodeT argval1 = (PtrToArg<m_type1>::EncodeT)arg1;\
			PtrToArg<m_type2>::EncodeT argval2 = (PtrToArg<m_type2>::EncodeT)arg2;\
			GDExtensionConstTypePtr argptrs[2] = { &argval1, &argval2 };\
			PtrToArg<m_ret>::EncodeT ret;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), &ret);\
				r_ret = (m_ret)ret;\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), &ret);\
				r_ret = (m_ret)ret;\
			}\
			return true;\
		}\
		ERR_PRINT_ONCE("Required virtual method " + get_class() + "::" + #m_name + " must be overridden before calling.");\
		(void)r_ret;\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL | METHOD_FLAG_VIRTUAL_REQUIRED;\
		method_info.return_val = GetTypeInfo<m_ret>::get_class_info();\
		method_info.return_val_metadata = GetTypeInfo<m_ret>::METADATA;\
		method_info.arguments.push_back(GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type1>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type2>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type2>::METADATA);\
		return method_info;\
	}

#define GDVIRTUAL2C_REQUIRED(m_name, m_type1, m_type2)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1, m_type2 arg2) const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant vargs[2] = { Variant(arg1), Variant(arg2) };\
			const Variant *vargptrs[2] = { &vargs[0], &vargs[1] };\
			_script_instance->callp(_gdvirtual_##m_name##_sn, (const Variant **)vargptrs, 2, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_type1>::EncodeT argval1 = (PtrToArg<m_type1>::EncodeT)arg1;\
			PtrToArg<m_type2>::EncodeT argval2 = (PtrToArg<m_type2>::EncodeT)arg2;\
			GDExtensionConstTypePtr argptrs[2] = { &argval1, &argval2 };\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), nullptr);\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), nullptr);\
			}\
			return true;\
		}\
		ERR_PRINT_ONCE("Required virtual method " + get_class() + "::" + #m_name + " must be overridden before calling.");\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL | METHOD_FLAG_CONST | METHOD_FLAG_VIRTUAL_REQUIRED;\
		method_info.arguments.push_back(GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type1>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type2>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type2>::METADATA);\
		return method_info;\
	}

#define GDVIRTUAL2RC_REQUIRED(m_ret, m_name, m_type1, m_type2)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1, m_type2 arg2, m_ret &r_ret) const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant vargs[2] = { Variant(arg1), Variant(arg2) };\
			const Variant *vargptrs[2] = { &vargs[0], &vargs[1] };\
			Variant ret = _script_instance->callp(_gdvirtual_##m_name##_sn, (const Variant **)vargptrs, 2, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				r_ret = VariantCaster<m_ret>::cast(ret);\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_type1>::EncodeT argval1 = (PtrToArg<m_type1>::EncodeT)arg1;\
			PtrToArg<m_type2>::EncodeT argval2 = (PtrToArg<m_type2>::EncodeT)arg2;\
			GDExtensionConstTypePtr argptrs[2] = { &argval1, &argval2 };\
			PtrToArg<m_ret>::EncodeT ret;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), &ret);\
				r_ret = (m_ret)ret;\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), &ret);\
				r_ret = (m_ret)ret;\
			}\
			return true;\
		}\
		ERR_PRINT_ONCE("Required virtual method " + get_class() + "::" + #m_name + " must be overridden before calling.");\
		(void)r_ret;\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL | METHOD_FLAG_CONST | METHOD_FLAG_VIRTUAL_REQUIRED;\
		method_info.return_val = GetTypeInfo<m_ret>::get_class_info();\
		method_info.return_val_metadata = GetTypeInfo<m_ret>::METADATA;\
		method_info.arguments.push_back(GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type1>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type2>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type2>::METADATA);\
		return method_info;\
	}

/* 3 Arguments */

#define GDVIRTUAL3(m_name, m_type1, m_type2, m_type3)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1, m_type2 arg2, m_type3 arg3) {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant vargs[3] = { Variant(arg1), Variant(arg2), Variant(arg3) };\
			const Variant *vargptrs[3] = { &vargs[0], &vargs[1], &vargs[2] };\
			_script_instance->callp(_gdvirtual_##m_name##_sn, (const Variant **)vargptrs, 3, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_type1>::EncodeT argval1 = (PtrToArg<m_type1>::EncodeT)arg1;\
			PtrToArg<m_type2>::EncodeT argval2 = (PtrToArg<m_type2>::EncodeT)arg2;\
			PtrToArg<m_type3>::EncodeT argval3 = (PtrToArg<m_type3>::EncodeT)arg3;\
			GDExtensionConstTypePtr argptrs[3] = { &argval1, &argval2, &argval3 };\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), nullptr);\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), nullptr);\
			}\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL;\
		method_info.arguments.push_back(GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type1>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type2>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type2>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type3>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type3>::METADATA);\
		return method_info;\
	}

#define GDVIRTUAL3R(m_ret, m_name, m_type1, m_type2, m_type3)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_ret &r_ret) {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant vargs[3] = { Variant(arg1), Variant(arg2), Variant(arg3) };\
			const Variant *vargptrs[3] = { &vargs[0], &vargs[1], &vargs[2] };\
			Variant ret = _script_instance->callp(_gdvirtual_##m_name##_sn, (const Variant **)vargptrs, 3, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				r_ret = VariantCaster<m_ret>::cast(ret);\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_type1>::EncodeT argval1 = (PtrToArg<m_type1>::EncodeT)arg1;\
			PtrToArg<m_type2>::EncodeT argval2 = (PtrToArg<m_type2>::EncodeT)arg2;\
			PtrToArg<m_type3>::EncodeT argval3 = (PtrToArg<m_type3>::EncodeT)arg3;\
			GDExtensionConstTypePtr argptrs[3] = { &argval1, &argval2, &argval3 };\
			PtrToArg<m_ret>::EncodeT ret;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), &ret);\
				r_ret = (m_ret)ret;\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), &ret);\
				r_ret = (m_ret)ret;\
			}\
			return true;\
		}\
		(void)r_ret;\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL;\
		method_info.return_val = GetTypeInfo<m_ret>::get_class_info();\
		method_info.return_val_metadata = GetTypeInfo<m_ret>::METADATA;\
		method_info.arguments.push_back(GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type1>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type2>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type2>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type3>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type3>::METADATA);\
		return method_info;\
	}

#define GDVIRTUAL3C(m_name, m_type1, m_type2, m_type3)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1, m_type2 arg2, m_type3 arg3) const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant vargs[3] = { Variant(arg1), Variant(arg2), Variant(arg3) };\
			const Variant *vargptrs[3] = { &vargs[0], &vargs[1], &vargs[2] };\
			_script_instance->callp(_gdvirtual_##m_name##_sn, (const Variant **)vargptrs, 3, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_type1>::EncodeT argval1 = (PtrToArg<m_type1>::EncodeT)arg1;\
			PtrToArg<m_type2>::EncodeT argval2 = (PtrToArg<m_type2>::EncodeT)arg2;\
			PtrToArg<m_type3>::EncodeT argval3 = (PtrToArg<m_type3>::EncodeT)arg3;\
			GDExtensionConstTypePtr argptrs[3] = { &argval1, &argval2, &argval3 };\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), nullptr);\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), nullptr);\
			}\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL | METHOD_FLAG_CONST;\
		method_info.arguments.push_back(GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type1>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type2>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type2>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type3>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type3>::METADATA);\
		return method_info;\
	}

#define GDVIRTUAL3RC(m_ret, m_name, m_type1, m_type2, m_type3)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_ret &r_ret) const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant vargs[3] = { Variant(arg1), Variant(arg2), Variant(arg3) };\
			const Variant *vargptrs[3] = { &vargs[0], &vargs[1], &vargs[2] };\
			Variant ret = _script_instance->callp(_gdvirtual_##m_name##_sn, (const Variant **)vargptrs, 3, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				r_ret = VariantCaster<m_ret>::cast(ret);\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_type1>::EncodeT argval1 = (PtrToArg<m_type1>::EncodeT)arg1;\
			PtrToArg<m_type2>::EncodeT argval2 = (PtrToArg<m_type2>::EncodeT)arg2;\
			PtrToArg<m_type3>::EncodeT argval3 = (PtrToArg<m_type3>::EncodeT)arg3;\
			GDExtensionConstTypePtr argptrs[3] = { &argval1, &argval2, &argval3 };\
			PtrToArg<m_ret>::EncodeT ret;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), &ret);\
				r_ret = (m_ret)ret;\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), &ret);\
				r_ret = (m_ret)ret;\
			}\
			return true;\
		}\
		(void)r_ret;\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL | METHOD_FLAG_CONST;\
		method_info.return_val = GetTypeInfo<m_ret>::get_class_info();\
		method_info.return_val_metadata = GetTypeInfo<m_ret>::METADATA;\
		method_info.arguments.push_back(GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type1>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type2>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type2>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type3>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type3>::METADATA);\
		return method_info;\
	}

#define GDVIRTUAL3_REQUIRED(m_name, m_type1, m_type2, m_type3)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1, m_type2 arg2, m_type3 arg3) {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant vargs[3] = { Variant(arg1), Variant(arg2), Variant(arg3) };\
			const Variant *vargptrs[3] = { &vargs[0], &vargs[1], &vargs[2] };\
			_script_instance->callp(_gdvirtual_##m_name##_sn, (const Variant **)vargptrs, 3, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_type1>::EncodeT argval1 = (PtrToArg<m_type1>::EncodeT)arg1;\
			PtrToArg<m_type2>::EncodeT argval2 = (PtrToArg<m_type2>::EncodeT)arg2;\
			PtrToArg<m_type3>::EncodeT argval3 = (PtrToArg<m_type3>::EncodeT)arg3;\
			GDExtensionConstTypePtr argptrs[3] = { &argval1, &argval2, &argval3 };\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), nullptr);\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), nullptr);\
			}\
			return true;\
		}\
		ERR_PRINT_ONCE("Required virtual method " + get_class() + "::" + #m_name + " must be overridden before calling.");\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL | METHOD_FLAG_VIRTUAL_REQUIRED;\
		method_info.arguments.push_back(GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type1>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type2>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type2>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type3>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type3>::METADATA);\
		return method_info;\
	}

#define GDVIRTUAL3R_REQUIRED(m_ret, m_name, m_type1, m_type2, m_type3)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_ret &r_ret) {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant vargs[3] = { Variant(arg1), Variant(arg2), Variant(arg3) };\
			const Variant *vargptrs[3] = { &vargs[0], &vargs[1], &vargs[2] };\
			Variant ret = _script_instance->callp(_gdvirtual_##m_name##_sn, (const Variant **)vargptrs, 3, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				r_ret = VariantCaster<m_ret>::cast(ret);\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_type1>::EncodeT argval1 = (PtrToArg<m_type1>::EncodeT)arg1;\
			PtrToArg<m_type2>::EncodeT argval2 = (PtrToArg<m_type2>::EncodeT)arg2;\
			PtrToArg<m_type3>::EncodeT argval3 = (PtrToArg<m_type3>::EncodeT)arg3;\
			GDExtensionConstTypePtr argptrs[3] = { &argval1, &argval2, &argval3 };\
			PtrToArg<m_ret>::EncodeT ret;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), &ret);\
				r_ret = (m_ret)ret;\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), &ret);\
				r_ret = (m_ret)ret;\
			}\
			return true;\
		}\
		ERR_PRINT_ONCE("Required virtual method " + get_class() + "::" + #m_name + " must be overridden before calling.");\
		(void)r_ret;\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL | METHOD_FLAG_VIRTUAL_REQUIRED;\
		method_info.return_val = GetTypeInfo<m_ret>::get_class_info();\
		method_info.return_val_metadata = GetTypeInfo<m_ret>::METADATA;\
		method_info.arguments.push_back(GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type1>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type2>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type2>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type3>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type3>::METADATA);\
		return method_info;\
	}

#define GDVIRTUAL3C_REQUIRED(m_name, m_type1, m_type2, m_type3)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1, m_type2 arg2, m_type3 arg3) const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant vargs[3] = { Variant(arg1), Variant(arg2), Variant(arg3) };\
			const Variant *vargptrs[3] = { &vargs[0], &vargs[1], &vargs[2] };\
			_script_instance->callp(_gdvirtual_##m_name##_sn, (const Variant **)vargptrs, 3, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_type1>::EncodeT argval1 = (PtrToArg<m_type1>::EncodeT)arg1;\
			PtrToArg<m_type2>::EncodeT argval2 = (PtrToArg<m_type2>::EncodeT)arg2;\
			PtrToArg<m_type3>::EncodeT argval3 = (PtrToArg<m_type3>::EncodeT)arg3;\
			GDExtensionConstTypePtr argptrs[3] = { &argval1, &argval2, &argval3 };\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), nullptr);\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), nullptr);\
			}\
			return true;\
		}\
		ERR_PRINT_ONCE("Required virtual method " + get_class() + "::" + #m_name + " must be overridden before calling.");\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL | METHOD_FLAG_CONST | METHOD_FLAG_VIRTUAL_REQUIRED;\
		method_info.arguments.push_back(GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type1>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type2>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type2>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type3>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type3>::METADATA);\
		return method_info;\
	}

#define GDVIRTUAL3RC_REQUIRED(m_ret, m_name, m_type1, m_type2, m_type3)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_ret &r_ret) const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant vargs[3] = { Variant(arg1), Variant(arg2), Variant(arg3) };\
			const Variant *vargptrs[3] = { &vargs[0], &vargs[1], &vargs[2] };\
			Variant ret = _script_instance->callp(_gdvirtual_##m_name##_sn, (const Variant **)vargptrs, 3, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				r_ret = VariantCaster<m_ret>::cast(ret);\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_type1>::EncodeT argval1 = (PtrToArg<m_type1>::EncodeT)arg1;\
			PtrToArg<m_type2>::EncodeT argval2 = (PtrToArg<m_type2>::EncodeT)arg2;\
			PtrToArg<m_type3>::EncodeT argval3 = (PtrToArg<m_type3>::EncodeT)arg3;\
			GDExtensionConstTypePtr argptrs[3] = { &argval1, &argval2, &argval3 };\
			PtrToArg<m_ret>::EncodeT ret;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), &ret);\
				r_ret = (m_ret)ret;\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), &ret);\
				r_ret = (m_ret)ret;\
			}\
			return true;\
		}\
		ERR_PRINT_ONCE("Required virtual method " + get_class() + "::" + #m_name + " must be overridden before calling.");\
		(void)r_ret;\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL | METHOD_FLAG_CONST | METHOD_FLAG_VIRTUAL_REQUIRED;\
		method_info.return_val = GetTypeInfo<m_ret>::get_class_info();\
		method_info.return_val_metadata = GetTypeInfo<m_ret>::METADATA;\
		method_info.arguments.push_back(GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type1>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type2>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type2>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type3>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type3>::METADATA);\
		return method_info;\
	}

/* 4 Arguments */

#define GDVIRTUAL4(m_name, m_type1, m_type2, m_type3, m_type4)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4) {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant vargs[4] = { Variant(arg1), Variant(arg2), Variant(arg3), Variant(arg4) };\
			const Variant *vargptrs[4] = { &vargs[0], &vargs[1], &vargs[2], &vargs[3] };\
			_script_instance->callp(_gdvirtual_##m_name##_sn, (const Variant **)vargptrs, 4, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_type1>::EncodeT argval1 = (PtrToArg<m_type1>::EncodeT)arg1;\
			PtrToArg<m_type2>::EncodeT argval2 = (PtrToArg<m_type2>::EncodeT)arg2;\
			PtrToArg<m_type3>::EncodeT argval3 = (PtrToArg<m_type3>::EncodeT)arg3;\
			PtrToArg<m_type4>::EncodeT argval4 = (PtrToArg<m_type4>::EncodeT)arg4;\
			GDExtensionConstTypePtr argptrs[4] = { &argval1, &argval2, &argval3, &argval4 };\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), nullptr);\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), nullptr);\
			}\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL;\
		method_info.arguments.push_back(GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type1>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type2>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type2>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type3>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type3>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type4>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type4>::METADATA);\
		return method_info;\
	}

#define GDVIRTUAL4R(m_ret, m_name, m_type1, m_type2, m_type3, m_type4)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_ret &r_ret) {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant vargs[4] = { Variant(arg1), Variant(arg2), Variant(arg3), Variant(arg4) };\
			const Variant *vargptrs[4] = { &vargs[0], &vargs[1], &vargs[2], &vargs[3] };\
			Variant ret = _script_instance->callp(_gdvirtual_##m_name##_sn, (const Variant **)vargptrs, 4, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				r_ret = VariantCaster<m_ret>::cast(ret);\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_type1>::EncodeT argval1 = (PtrToArg<m_type1>::EncodeT)arg1;\
			PtrToArg<m_type2>::EncodeT argval2 = (PtrToArg<m_type2>::EncodeT)arg2;\
			PtrToArg<m_type3>::EncodeT argval3 = (PtrToArg<m_type3>::EncodeT)arg3;\
			PtrToArg<m_type4>::EncodeT argval4 = (PtrToArg<m_type4>::EncodeT)arg4;\
			GDExtensionConstTypePtr argptrs[4] = { &argval1, &argval2, &argval3, &argval4 };\
			PtrToArg<m_ret>::EncodeT ret;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), &ret);\
				r_ret = (m_ret)ret;\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), &ret);\
				r_ret = (m_ret)ret;\
			}\
			return true;\
		}\
		(void)r_ret;\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL;\
		method_info.return_val = GetTypeInfo<m_ret>::get_class_info();\
		method_info.return_val_metadata = GetTypeInfo<m_ret>::METADATA;\
		method_info.arguments.push_back(GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type1>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type2>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type2>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type3>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type3>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type4>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type4>::METADATA);\
		return method_info;\
	}

#define GDVIRTUAL4C(m_name, m_type1, m_type2, m_type3, m_type4)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4) const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant vargs[4] = { Variant(arg1), Variant(arg2), Variant(arg3), Variant(arg4) };\
			const Variant *vargptrs[4] = { &vargs[0], &vargs[1], &vargs[2], &vargs[3] };\
			_script_instance->callp(_gdvirtual_##m_name##_sn, (const Variant **)vargptrs, 4, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_type1>::EncodeT argval1 = (PtrToArg<m_type1>::EncodeT)arg1;\
			PtrToArg<m_type2>::EncodeT argval2 = (PtrToArg<m_type2>::EncodeT)arg2;\
			PtrToArg<m_type3>::EncodeT argval3 = (PtrToArg<m_type3>::EncodeT)arg3;\
			PtrToArg<m_type4>::EncodeT argval4 = (PtrToArg<m_type4>::EncodeT)arg4;\
			GDExtensionConstTypePtr argptrs[4] = { &argval1, &argval2, &argval3, &argval4 };\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), nullptr);\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), nullptr);\
			}\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL | METHOD_FLAG_CONST;\
		method_info.arguments.push_back(GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type1>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type2>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type2>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type3>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type3>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type4>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type4>::METADATA);\
		return method_info;\
	}

#define GDVIRTUAL4RC(m_ret, m_name, m_type1, m_type2, m_type3, m_type4)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_ret &r_ret) const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant vargs[4] = { Variant(arg1), Variant(arg2), Variant(arg3), Variant(arg4) };\
			const Variant *vargptrs[4] = { &vargs[0], &vargs[1], &vargs[2], &vargs[3] };\
			Variant ret = _script_instance->callp(_gdvirtual_##m_name##_sn, (const Variant **)vargptrs, 4, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				r_ret = VariantCaster<m_ret>::cast(ret);\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_type1>::EncodeT argval1 = (PtrToArg<m_type1>::EncodeT)arg1;\
			PtrToArg<m_type2>::EncodeT argval2 = (PtrToArg<m_type2>::EncodeT)arg2;\
			PtrToArg<m_type3>::EncodeT argval3 = (PtrToArg<m_type3>::EncodeT)arg3;\
			PtrToArg<m_type4>::EncodeT argval4 = (PtrToArg<m_type4>::EncodeT)arg4;\
			GDExtensionConstTypePtr argptrs[4] = { &argval1, &argval2, &argval3, &argval4 };\
			PtrToArg<m_ret>::EncodeT ret;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), &ret);\
				r_ret = (m_ret)ret;\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), &ret);\
				r_ret = (m_ret)ret;\
			}\
			return true;\
		}\
		(void)r_ret;\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL | METHOD_FLAG_CONST;\
		method_info.return_val = GetTypeInfo<m_ret>::get_class_info();\
		method_info.return_val_metadata = GetTypeInfo<m_ret>::METADATA;\
		method_info.arguments.push_back(GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type1>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type2>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type2>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type3>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type3>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type4>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type4>::METADATA);\
		return method_info;\
	}

#define GDVIRTUAL4_REQUIRED(m_name, m_type1, m_type2, m_type3, m_type4)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4) {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant vargs[4] = { Variant(arg1), Variant(arg2), Variant(arg3), Variant(arg4) };\
			const Variant *vargptrs[4] = { &vargs[0], &vargs[1], &vargs[2], &vargs[3] };\
			_script_instance->callp(_gdvirtual_##m_name##_sn, (const Variant **)vargptrs, 4, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_type1>::EncodeT argval1 = (PtrToArg<m_type1>::EncodeT)arg1;\
			PtrToArg<m_type2>::EncodeT argval2 = (PtrToArg<m_type2>::EncodeT)arg2;\
			PtrToArg<m_type3>::EncodeT argval3 = (PtrToArg<m_type3>::EncodeT)arg3;\
			PtrToArg<m_type4>::EncodeT argval4 = (PtrToArg<m_type4>::EncodeT)arg4;\
			GDExtensionConstTypePtr argptrs[4] = { &argval1, &argval2, &argval3, &argval4 };\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), nullptr);\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), nullptr);\
			}\
			return true;\
		}\
		ERR_PRINT_ONCE("Required virtual method " + get_class() + "::" + #m_name + " must be overridden before calling.");\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL | METHOD_FLAG_VIRTUAL_REQUIRED;\
		method_info.arguments.push_back(GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type1>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type2>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type2>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type3>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type3>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type4>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type4>::METADATA);\
		return method_info;\
	}

#define GDVIRTUAL4R_REQUIRED(m_ret, m_name, m_type1, m_type2, m_type3, m_type4)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_ret &r_ret) {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant vargs[4] = { Variant(arg1), Variant(arg2), Variant(arg3), Variant(arg4) };\
			const Variant *vargptrs[4] = { &vargs[0], &vargs[1], &vargs[2], &vargs[3] };\
			Variant ret = _script_instance->callp(_gdvirtual_##m_name##_sn, (const Variant **)vargptrs, 4, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				r_ret = VariantCaster<m_ret>::cast(ret);\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_type1>::EncodeT argval1 = (PtrToArg<m_type1>::EncodeT)arg1;\
			PtrToArg<m_type2>::EncodeT argval2 = (PtrToArg<m_type2>::EncodeT)arg2;\
			PtrToArg<m_type3>::EncodeT argval3 = (PtrToArg<m_type3>::EncodeT)arg3;\
			PtrToArg<m_type4>::EncodeT argval4 = (PtrToArg<m_type4>::EncodeT)arg4;\
			GDExtensionConstTypePtr argptrs[4] = { &argval1, &argval2, &argval3, &argval4 };\
			PtrToArg<m_ret>::EncodeT ret;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), &ret);\
				r_ret = (m_ret)ret;\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), &ret);\
				r_ret = (m_ret)ret;\
			}\
			return true;\
		}\
		ERR_PRINT_ONCE("Required virtual method " + get_class() + "::" + #m_name + " must be overridden before calling.");\
		(void)r_ret;\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL | METHOD_FLAG_VIRTUAL_REQUIRED;\
		method_info.return_val = GetTypeInfo<m_ret>::get_class_info();\
		method_info.return_val_metadata = GetTypeInfo<m_ret>::METADATA;\
		method_info.arguments.push_back(GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type1>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type2>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type2>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type3>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type3>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type4>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type4>::METADATA);\
		return method_info;\
	}

#define GDVIRTUAL4C_REQUIRED(m_name, m_type1, m_type2, m_type3, m_type4)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4) const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant vargs[4] = { Variant(arg1), Variant(arg2), Variant(arg3), Variant(arg4) };\
			const Variant *vargptrs[4] = { &vargs[0], &vargs[1], &vargs[2], &vargs[3] };\
			_script_instance->callp(_gdvirtual_##m_name##_sn, (const Variant **)vargptrs, 4, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_type1>::EncodeT argval1 = (PtrToArg<m_type1>::EncodeT)arg1;\
			PtrToArg<m_type2>::EncodeT argval2 = (PtrToArg<m_type2>::EncodeT)arg2;\
			PtrToArg<m_type3>::EncodeT argval3 = (PtrToArg<m_type3>::EncodeT)arg3;\
			PtrToArg<m_type4>::EncodeT argval4 = (PtrToArg<m_type4>::EncodeT)arg4;\
			GDExtensionConstTypePtr argptrs[4] = { &argval1, &argval2, &argval3, &argval4 };\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), nullptr);\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), nullptr);\
			}\
			return true;\
		}\
		ERR_PRINT_ONCE("Required virtual method " + get_class() + "::" + #m_name + " must be overridden before calling.");\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL | METHOD_FLAG_CONST | METHOD_FLAG_VIRTUAL_REQUIRED;\
		method_info.arguments.push_back(GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type1>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type2>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type2>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type3>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type3>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type4>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type4>::METADATA);\
		return method_info;\
	}

#define GDVIRTUAL4RC_REQUIRED(m_ret, m_name, m_type1, m_type2, m_type3, m_type4)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_ret &r_ret) const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant vargs[4] = { Variant(arg1), Variant(arg2), Variant(arg3), Variant(arg4) };\
			const Variant *vargptrs[4] = { &vargs[0], &vargs[1], &vargs[2], &vargs[3] };\
			Variant ret = _script_instance->callp(_gdvirtual_##m_name##_sn, (const Variant **)vargptrs, 4, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				r_ret = VariantCaster<m_ret>::cast(ret);\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_type1>::EncodeT argval1 = (PtrToArg<m_type1>::EncodeT)arg1;\
			PtrToArg<m_type2>::EncodeT argval2 = (PtrToArg<m_type2>::EncodeT)arg2;\
			PtrToArg<m_type3>::EncodeT argval3 = (PtrToArg<m_type3>::EncodeT)arg3;\
			PtrToArg<m_type4>::EncodeT argval4 = (PtrToArg<m_type4>::EncodeT)arg4;\
			GDExtensionConstTypePtr argptrs[4] = { &argval1, &argval2, &argval3, &argval4 };\
			PtrToArg<m_ret>::EncodeT ret;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), &ret);\
				r_ret = (m_ret)ret;\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), &ret);\
				r_ret = (m_ret)ret;\
			}\
			return true;\
		}\
		ERR_PRINT_ONCE("Required virtual method " + get_class() + "::" + #m_name + " must be overridden before calling.");\
		(void)r_ret;\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL | METHOD_FLAG_CONST | METHOD_FLAG_VIRTUAL_REQUIRED;\
		method_info.return_val = GetTypeInfo<m_ret>::get_class_info();\
		method_info.return_val_metadata = GetTypeInfo<m_ret>::METADATA;\
		method_info.arguments.push_back(GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type1>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type2>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type2>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type3>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type3>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type4>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type4>::METADATA);\
		return method_info;\
	}

/* 5 Arguments */

#define GDVIRTUAL5(m_name, m_type1, m_type2, m_type3, m_type4, m_type5)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5) {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant vargs[5] = { Variant(arg1), Variant(arg2), Variant(arg3), Variant(arg4), Variant(arg5) };\
			const Variant *vargptrs[5] = { &vargs[0], &vargs[1], &vargs[2], &vargs[3], &vargs[4] };\
			_script_instance->callp(_gdvirtual_##m_name##_sn, (const Variant **)vargptrs, 5, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_type1>::EncodeT argval1 = (PtrToArg<m_type1>::EncodeT)arg1;\
			PtrToArg<m_type2>::EncodeT argval2 = (PtrToArg<m_type2>::EncodeT)arg2;\
			PtrToArg<m_type3>::EncodeT argval3 = (PtrToArg<m_type3>::EncodeT)arg3;\
			PtrToArg<m_type4>::EncodeT argval4 = (PtrToArg<m_type4>::EncodeT)arg4;\
			PtrToArg<m_type5>::EncodeT argval5 = (PtrToArg<m_type5>::EncodeT)arg5;\
			GDExtensionConstTypePtr argptrs[5] = { &argval1, &argval2, &argval3, &argval4, &argval5 };\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), nullptr);\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), nullptr);\
			}\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL;\
		method_info.arguments.push_back(GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type1>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type2>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type2>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type3>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type3>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type4>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type4>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type5>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type5>::METADATA);\
		return method_info;\
	}

#define GDVIRTUAL5R(m_ret, m_name, m_type1, m_type2, m_type3, m_type4, m_type5)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_ret &r_ret) {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant vargs[5] = { Variant(arg1), Variant(arg2), Variant(arg3), Variant(arg4), Variant(arg5) };\
			const Variant *vargptrs[5] = { &vargs[0], &vargs[1], &vargs[2], &vargs[3], &vargs[4] };\
			Variant ret = _script_instance->callp(_gdvirtual_##m_name##_sn, (const Variant **)vargptrs, 5, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				r_ret = VariantCaster<m_ret>::cast(ret);\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_type1>::EncodeT argval1 = (PtrToArg<m_type1>::EncodeT)arg1;\
			PtrToArg<m_type2>::EncodeT argval2 = (PtrToArg<m_type2>::EncodeT)arg2;\
			PtrToArg<m_type3>::EncodeT argval3 = (PtrToArg<m_type3>::EncodeT)arg3;\
			PtrToArg<m_type4>::EncodeT argval4 = (PtrToArg<m_type4>::EncodeT)arg4;\
			PtrToArg<m_type5>::EncodeT argval5 = (PtrToArg<m_type5>::EncodeT)arg5;\
			GDExtensionConstTypePtr argptrs[5] = { &argval1, &argval2, &argval3, &argval4, &argval5 };\
			PtrToArg<m_ret>::EncodeT ret;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), &ret);\
				r_ret = (m_ret)ret;\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), &ret);\
				r_ret = (m_ret)ret;\
			}\
			return true;\
		}\
		(void)r_ret;\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL;\
		method_info.return_val = GetTypeInfo<m_ret>::get_class_info();\
		method_info.return_val_metadata = GetTypeInfo<m_ret>::METADATA;\
		method_info.arguments.push_back(GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type1>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type2>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type2>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type3>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type3>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type4>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type4>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type5>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type5>::METADATA);\
		return method_info;\
	}

#define GDVIRTUAL5C(m_name, m_type1, m_type2, m_type3, m_type4, m_type5)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5) const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant vargs[5] = { Variant(arg1), Variant(arg2), Variant(arg3), Variant(arg4), Variant(arg5) };\
			const Variant *vargptrs[5] = { &vargs[0], &vargs[1], &vargs[2], &vargs[3], &vargs[4] };\
			_script_instance->callp(_gdvirtual_##m_name##_sn, (const Variant **)vargptrs, 5, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_type1>::EncodeT argval1 = (PtrToArg<m_type1>::EncodeT)arg1;\
			PtrToArg<m_type2>::EncodeT argval2 = (PtrToArg<m_type2>::EncodeT)arg2;\
			PtrToArg<m_type3>::EncodeT argval3 = (PtrToArg<m_type3>::EncodeT)arg3;\
			PtrToArg<m_type4>::EncodeT argval4 = (PtrToArg<m_type4>::EncodeT)arg4;\
			PtrToArg<m_type5>::EncodeT argval5 = (PtrToArg<m_type5>::EncodeT)arg5;\
			GDExtensionConstTypePtr argptrs[5] = { &argval1, &argval2, &argval3, &argval4, &argval5 };\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), nullptr);\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), nullptr);\
			}\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL | METHOD_FLAG_CONST;\
		method_info.arguments.push_back(GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type1>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type2>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type2>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type3>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type3>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type4>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type4>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type5>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type5>::METADATA);\
		return method_info;\
	}

#define GDVIRTUAL5RC(m_ret, m_name, m_type1, m_type2, m_type3, m_type4, m_type5)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_ret &r_ret) const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant vargs[5] = { Variant(arg1), Variant(arg2), Variant(arg3), Variant(arg4), Variant(arg5) };\
			const Variant *vargptrs[5] = { &vargs[0], &vargs[1], &vargs[2], &vargs[3], &vargs[4] };\
			Variant ret = _script_instance->callp(_gdvirtual_##m_name##_sn, (const Variant **)vargptrs, 5, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				r_ret = VariantCaster<m_ret>::cast(ret);\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_type1>::EncodeT argval1 = (PtrToArg<m_type1>::EncodeT)arg1;\
			PtrToArg<m_type2>::EncodeT argval2 = (PtrToArg<m_type2>::EncodeT)arg2;\
			PtrToArg<m_type3>::EncodeT argval3 = (PtrToArg<m_type3>::EncodeT)arg3;\
			PtrToArg<m_type4>::EncodeT argval4 = (PtrToArg<m_type4>::EncodeT)arg4;\
			PtrToArg<m_type5>::EncodeT argval5 = (PtrToArg<m_type5>::EncodeT)arg5;\
			GDExtensionConstTypePtr argptrs[5] = { &argval1, &argval2, &argval3, &argval4, &argval5 };\
			PtrToArg<m_ret>::EncodeT ret;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), &ret);\
				r_ret = (m_ret)ret;\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), &ret);\
				r_ret = (m_ret)ret;\
			}\
			return true;\
		}\
		(void)r_ret;\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL | METHOD_FLAG_CONST;\
		method_info.return_val = GetTypeInfo<m_ret>::get_class_info();\
		method_info.return_val_metadata = GetTypeInfo<m_ret>::METADATA;\
		method_info.arguments.push_back(GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type1>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type2>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type2>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type3>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type3>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type4>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type4>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type5>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type5>::METADATA);\
		return method_info;\
	}

#define GDVIRTUAL5_REQUIRED(m_name, m_type1, m_type2, m_type3, m_type4, m_type5)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5) {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant vargs[5] = { Variant(arg1), Variant(arg2), Variant(arg3), Variant(arg4), Variant(arg5) };\
			const Variant *vargptrs[5] = { &vargs[0], &vargs[1], &vargs[2], &vargs[3], &vargs[4] };\
			_script_instance->callp(_gdvirtual_##m_name##_sn, (const Variant **)vargptrs, 5, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_type1>::EncodeT argval1 = (PtrToArg<m_type1>::EncodeT)arg1;\
			PtrToArg<m_type2>::EncodeT argval2 = (PtrToArg<m_type2>::EncodeT)arg2;\
			PtrToArg<m_type3>::EncodeT argval3 = (PtrToArg<m_type3>::EncodeT)arg3;\
			PtrToArg<m_type4>::EncodeT argval4 = (PtrToArg<m_type4>::EncodeT)arg4;\
			PtrToArg<m_type5>::EncodeT argval5 = (PtrToArg<m_type5>::EncodeT)arg5;\
			GDExtensionConstTypePtr argptrs[5] = { &argval1, &argval2, &argval3, &argval4, &argval5 };\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), nullptr);\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), nullptr);\
			}\
			return true;\
		}\
		ERR_PRINT_ONCE("Required virtual method " + get_class() + "::" + #m_name + " must be overridden before calling.");\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL | METHOD_FLAG_VIRTUAL_REQUIRED;\
		method_info.arguments.push_back(GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type1>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type2>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type2>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type3>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type3>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type4>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type4>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type5>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type5>::METADATA);\
		return method_info;\
	}

#define GDVIRTUAL5R_REQUIRED(m_ret, m_name, m_type1, m_type2, m_type3, m_type4, m_type5)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_ret &r_ret) {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant vargs[5] = { Variant(arg1), Variant(arg2), Variant(arg3), Variant(arg4), Variant(arg5) };\
			const Variant *vargptrs[5] = { &vargs[0], &vargs[1], &vargs[2], &vargs[3], &vargs[4] };\
			Variant ret = _script_instance->callp(_gdvirtual_##m_name##_sn, (const Variant **)vargptrs, 5, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				r_ret = VariantCaster<m_ret>::cast(ret);\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_type1>::EncodeT argval1 = (PtrToArg<m_type1>::EncodeT)arg1;\
			PtrToArg<m_type2>::EncodeT argval2 = (PtrToArg<m_type2>::EncodeT)arg2;\
			PtrToArg<m_type3>::EncodeT argval3 = (PtrToArg<m_type3>::EncodeT)arg3;\
			PtrToArg<m_type4>::EncodeT argval4 = (PtrToArg<m_type4>::EncodeT)arg4;\
			PtrToArg<m_type5>::EncodeT argval5 = (PtrToArg<m_type5>::EncodeT)arg5;\
			GDExtensionConstTypePtr argptrs[5] = { &argval1, &argval2, &argval3, &argval4, &argval5 };\
			PtrToArg<m_ret>::EncodeT ret;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), &ret);\
				r_ret = (m_ret)ret;\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), &ret);\
				r_ret = (m_ret)ret;\
			}\
			return true;\
		}\
		ERR_PRINT_ONCE("Required virtual method " + get_class() + "::" + #m_name + " must be overridden before calling.");\
		(void)r_ret;\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL | METHOD_FLAG_VIRTUAL_REQUIRED;\
		method_info.return_val = GetTypeInfo<m_ret>::get_class_info();\
		method_info.return_val_metadata = GetTypeInfo<m_ret>::METADATA;\
		method_info.arguments.push_back(GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type1>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type2>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type2>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type3>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type3>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type4>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type4>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type5>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type5>::METADATA);\
		return method_info;\
	}

#define GDVIRTUAL5C_REQUIRED(m_name, m_type1, m_type2, m_type3, m_type4, m_type5)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5) const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant vargs[5] = { Variant(arg1), Variant(arg2), Variant(arg3), Variant(arg4), Variant(arg5) };\
			const Variant *vargptrs[5] = { &vargs[0], &vargs[1], &vargs[2], &vargs[3], &vargs[4] };\
			_script_instance->callp(_gdvirtual_##m_name##_sn, (const Variant **)vargptrs, 5, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_type1>::EncodeT argval1 = (PtrToArg<m_type1>::EncodeT)arg1;\
			PtrToArg<m_type2>::EncodeT argval2 = (PtrToArg<m_type2>::EncodeT)arg2;\
			PtrToArg<m_type3>::EncodeT argval3 = (PtrToArg<m_type3>::EncodeT)arg3;\
			PtrToArg<m_type4>::EncodeT argval4 = (PtrToArg<m_type4>::EncodeT)arg4;\
			PtrToArg<m_type5>::EncodeT argval5 = (PtrToArg<m_type5>::EncodeT)arg5;\
			GDExtensionConstTypePtr argptrs[5] = { &argval1, &argval2, &argval3, &argval4, &argval5 };\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), nullptr);\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), nullptr);\
			}\
			return true;\
		}\
		ERR_PRINT_ONCE("Required virtual method " + get_class() + "::" + #m_name + " must be overridden before calling.");\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL | METHOD_FLAG_CONST | METHOD_FLAG_VIRTUAL_REQUIRED;\
		method_info.arguments.push_back(GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type1>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type2>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type2>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type3>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type3>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type4>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type4>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type5>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type5>::METADATA);\
		return method_info;\
	}

#define GDVIRTUAL5RC_REQUIRED(m_ret, m_name, m_type1, m_type2, m_type3, m_type4, m_type5)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_ret &r_ret) const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant vargs[5] = { Variant(arg1), Variant(arg2), Variant(arg3), Variant(arg4), Variant(arg5) };\
			const Variant *vargptrs[5] = { &vargs[0], &vargs[1], &vargs[2], &vargs[3], &vargs[4] };\
			Variant ret = _script_instance->callp(_gdvirtual_##m_name##_sn, (const Variant **)vargptrs, 5, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				r_ret = VariantCaster<m_ret>::cast(ret);\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_type1>::EncodeT argval1 = (PtrToArg<m_type1>::EncodeT)arg1;\
			PtrToArg<m_type2>::EncodeT argval2 = (PtrToArg<m_type2>::EncodeT)arg2;\
			PtrToArg<m_type3>::EncodeT argval3 = (PtrToArg<m_type3>::EncodeT)arg3;\
			PtrToArg<m_type4>::EncodeT argval4 = (PtrToArg<m_type4>::EncodeT)arg4;\
			PtrToArg<m_type5>::EncodeT argval5 = (PtrToArg<m_type5>::EncodeT)arg5;\
			GDExtensionConstTypePtr argptrs[5] = { &argval1, &argval2, &argval3, &argval4, &argval5 };\
			PtrToArg<m_ret>::EncodeT ret;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), &ret);\
				r_ret = (m_ret)ret;\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), &ret);\
				r_ret = (m_ret)ret;\
			}\
			return true;\
		}\
		ERR_PRINT_ONCE("Required virtual method " + get_class() + "::" + #m_name + " must be overridden before calling.");\
		(void)r_ret;\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL | METHOD_FLAG_CONST | METHOD_FLAG_VIRTUAL_REQUIRED;\
		method_info.return_val = GetTypeInfo<m_ret>::get_class_info();\
		method_info.return_val_metadata = GetTypeInfo<m_ret>::METADATA;\
		method_info.arguments.push_back(GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type1>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type2>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type2>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type3>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type3>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type4>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type4>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type5>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type5>::METADATA);\
		return method_info;\
	}

/* 6 Arguments */

#define GDVIRTUAL6(m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6) {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant vargs[6] = { Variant(arg1), Variant(arg2), Variant(arg3), Variant(arg4), Variant(arg5), Variant(arg6) };\
			const Variant *vargptrs[6] = { &vargs[0], &vargs[1], &vargs[2], &vargs[3], &vargs[4], &vargs[5] };\
			_script_instance->callp(_gdvirtual_##m_name##_sn, (const Variant **)vargptrs, 6, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_type1>::EncodeT argval1 = (PtrToArg<m_type1>::EncodeT)arg1;\
			PtrToArg<m_type2>::EncodeT argval2 = (PtrToArg<m_type2>::EncodeT)arg2;\
			PtrToArg<m_type3>::EncodeT argval3 = (PtrToArg<m_type3>::EncodeT)arg3;\
			PtrToArg<m_type4>::EncodeT argval4 = (PtrToArg<m_type4>::EncodeT)arg4;\
			PtrToArg<m_type5>::EncodeT argval5 = (PtrToArg<m_type5>::EncodeT)arg5;\
			PtrToArg<m_type6>::EncodeT argval6 = (PtrToArg<m_type6>::EncodeT)arg6;\
			GDExtensionConstTypePtr argptrs[6] = { &argval1, &argval2, &argval3, &argval4, &argval5, &argval6 };\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), nullptr);\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), nullptr);\
			}\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL;\
		method_info.arguments.push_back(GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type1>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type2>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type2>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type3>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type3>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type4>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type4>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type5>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type5>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type6>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type6>::METADATA);\
		return method_info;\
	}

#define GDVIRTUAL6R(m_ret, m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_ret &r_ret) {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant vargs[6] = { Variant(arg1), Variant(arg2), Variant(arg3), Variant(arg4), Variant(arg5), Variant(arg6) };\
			const Variant *vargptrs[6] = { &vargs[0], &vargs[1], &vargs[2], &vargs[3], &vargs[4], &vargs[5] };\
			Variant ret = _script_instance->callp(_gdvirtual_##m_name##_sn, (const Variant **)vargptrs, 6, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				r_ret = VariantCaster<m_ret>::cast(ret);\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_type1>::EncodeT argval1 = (PtrToArg<m_type1>::EncodeT)arg1;\
			PtrToArg<m_type2>::EncodeT argval2 = (PtrToArg<m_type2>::EncodeT)arg2;\
			PtrToArg<m_type3>::EncodeT argval3 = (PtrToArg<m_type3>::EncodeT)arg3;\
			PtrToArg<m_type4>::EncodeT argval4 = (PtrToArg<m_type4>::EncodeT)arg4;\
			PtrToArg<m_type5>::EncodeT argval5 = (PtrToArg<m_type5>::EncodeT)arg5;\
			PtrToArg<m_type6>::EncodeT argval6 = (PtrToArg<m_type6>::EncodeT)arg6;\
			GDExtensionConstTypePtr argptrs[6] = { &argval1, &argval2, &argval3, &argval4, &argval5, &argval6 };\
			PtrToArg<m_ret>::EncodeT ret;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), &ret);\
				r_ret = (m_ret)ret;\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), &ret);\
				r_ret = (m_ret)ret;\
			}\
			return true;\
		}\
		(void)r_ret;\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL;\
		method_info.return_val = GetTypeInfo<m_ret>::get_class_info();\
		method_info.return_val_metadata = GetTypeInfo<m_ret>::METADATA;\
		method_info.arguments.push_back(GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type1>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type2>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type2>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type3>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type3>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type4>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type4>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type5>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type5>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type6>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type6>::METADATA);\
		return method_info;\
	}

#define GDVIRTUAL6C(m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6) const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant vargs[6] = { Variant(arg1), Variant(arg2), Variant(arg3), Variant(arg4), Variant(arg5), Variant(arg6) };\
			const Variant *vargptrs[6] = { &vargs[0], &vargs[1], &vargs[2], &vargs[3], &vargs[4], &vargs[5] };\
			_script_instance->callp(_gdvirtual_##m_name##_sn, (const Variant **)vargptrs, 6, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_type1>::EncodeT argval1 = (PtrToArg<m_type1>::EncodeT)arg1;\
			PtrToArg<m_type2>::EncodeT argval2 = (PtrToArg<m_type2>::EncodeT)arg2;\
			PtrToArg<m_type3>::EncodeT argval3 = (PtrToArg<m_type3>::EncodeT)arg3;\
			PtrToArg<m_type4>::EncodeT argval4 = (PtrToArg<m_type4>::EncodeT)arg4;\
			PtrToArg<m_type5>::EncodeT argval5 = (PtrToArg<m_type5>::EncodeT)arg5;\
			PtrToArg<m_type6>::EncodeT argval6 = (PtrToArg<m_type6>::EncodeT)arg6;\
			GDExtensionConstTypePtr argptrs[6] = { &argval1, &argval2, &argval3, &argval4, &argval5, &argval6 };\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), nullptr);\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), nullptr);\
			}\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL | METHOD_FLAG_CONST;\
		method_info.arguments.push_back(GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type1>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type2>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type2>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type3>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type3>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type4>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type4>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type5>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type5>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type6>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type6>::METADATA);\
		return method_info;\
	}

#define GDVIRTUAL6RC(m_ret, m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_ret &r_ret) const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant vargs[6] = { Variant(arg1), Variant(arg2), Variant(arg3), Variant(arg4), Variant(arg5), Variant(arg6) };\
			const Variant *vargptrs[6] = { &vargs[0], &vargs[1], &vargs[2], &vargs[3], &vargs[4], &vargs[5] };\
			Variant ret = _script_instance->callp(_gdvirtual_##m_name##_sn, (const Variant **)vargptrs, 6, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				r_ret = VariantCaster<m_ret>::cast(ret);\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_type1>::EncodeT argval1 = (PtrToArg<m_type1>::EncodeT)arg1;\
			PtrToArg<m_type2>::EncodeT argval2 = (PtrToArg<m_type2>::EncodeT)arg2;\
			PtrToArg<m_type3>::EncodeT argval3 = (PtrToArg<m_type3>::EncodeT)arg3;\
			PtrToArg<m_type4>::EncodeT argval4 = (PtrToArg<m_type4>::EncodeT)arg4;\
			PtrToArg<m_type5>::EncodeT argval5 = (PtrToArg<m_type5>::EncodeT)arg5;\
			PtrToArg<m_type6>::EncodeT argval6 = (PtrToArg<m_type6>::EncodeT)arg6;\
			GDExtensionConstTypePtr argptrs[6] = { &argval1, &argval2, &argval3, &argval4, &argval5, &argval6 };\
			PtrToArg<m_ret>::EncodeT ret;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), &ret);\
				r_ret = (m_ret)ret;\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), &ret);\
				r_ret = (m_ret)ret;\
			}\
			return true;\
		}\
		(void)r_ret;\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL | METHOD_FLAG_CONST;\
		method_info.return_val = GetTypeInfo<m_ret>::get_class_info();\
		method_info.return_val_metadata = GetTypeInfo<m_ret>::METADATA;\
		method_info.arguments.push_back(GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type1>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type2>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type2>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type3>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type3>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type4>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type4>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type5>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type5>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type6>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type6>::METADATA);\
		return method_info;\
	}

#define GDVIRTUAL6_REQUIRED(m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6) {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant vargs[6] = { Variant(arg1), Variant(arg2), Variant(arg3), Variant(arg4), Variant(arg5), Variant(arg6) };\
			const Variant *vargptrs[6] = { &vargs[0], &vargs[1], &vargs[2], &vargs[3], &vargs[4], &vargs[5] };\
			_script_instance->callp(_gdvirtual_##m_name##_sn, (const Variant **)vargptrs, 6, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_type1>::EncodeT argval1 = (PtrToArg<m_type1>::EncodeT)arg1;\
			PtrToArg<m_type2>::EncodeT argval2 = (PtrToArg<m_type2>::EncodeT)arg2;\
			PtrToArg<m_type3>::EncodeT argval3 = (PtrToArg<m_type3>::EncodeT)arg3;\
			PtrToArg<m_type4>::EncodeT argval4 = (PtrToArg<m_type4>::EncodeT)arg4;\
			PtrToArg<m_type5>::EncodeT argval5 = (PtrToArg<m_type5>::EncodeT)arg5;\
			PtrToArg<m_type6>::EncodeT argval6 = (PtrToArg<m_type6>::EncodeT)arg6;\
			GDExtensionConstTypePtr argptrs[6] = { &argval1, &argval2, &argval3, &argval4, &argval5, &argval6 };\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), nullptr);\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), nullptr);\
			}\
			return true;\
		}\
		ERR_PRINT_ONCE("Required virtual method " + get_class() + "::" + #m_name + " must be overridden before calling.");\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL | METHOD_FLAG_VIRTUAL_REQUIRED;\
		method_info.arguments.push_back(GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type1>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type2>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type2>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type3>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type3>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type4>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type4>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type5>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type5>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type6>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type6>::METADATA);\
		return method_info;\
	}

#define GDVIRTUAL6R_REQUIRED(m_ret, m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_ret &r_ret) {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant vargs[6] = { Variant(arg1), Variant(arg2), Variant(arg3), Variant(arg4), Variant(arg5), Variant(arg6) };\
			const Variant *vargptrs[6] = { &vargs[0], &vargs[1], &vargs[2], &vargs[3], &vargs[4], &vargs[5] };\
			Variant ret = _script_instance->callp(_gdvirtual_##m_name##_sn, (const Variant **)vargptrs, 6, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				r_ret = VariantCaster<m_ret>::cast(ret);\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_type1>::EncodeT argval1 = (PtrToArg<m_type1>::EncodeT)arg1;\
			PtrToArg<m_type2>::EncodeT argval2 = (PtrToArg<m_type2>::EncodeT)arg2;\
			PtrToArg<m_type3>::EncodeT argval3 = (PtrToArg<m_type3>::EncodeT)arg3;\
			PtrToArg<m_type4>::EncodeT argval4 = (PtrToArg<m_type4>::EncodeT)arg4;\
			PtrToArg<m_type5>::EncodeT argval5 = (PtrToArg<m_type5>::EncodeT)arg5;\
			PtrToArg<m_type6>::EncodeT argval6 = (PtrToArg<m_type6>::EncodeT)arg6;\
			GDExtensionConstTypePtr argptrs[6] = { &argval1, &argval2, &argval3, &argval4, &argval5, &argval6 };\
			PtrToArg<m_ret>::EncodeT ret;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), &ret);\
				r_ret = (m_ret)ret;\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), &ret);\
				r_ret = (m_ret)ret;\
			}\
			return true;\
		}\
		ERR_PRINT_ONCE("Required virtual method " + get_class() + "::" + #m_name + " must be overridden before calling.");\
		(void)r_ret;\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL | METHOD_FLAG_VIRTUAL_REQUIRED;\
		method_info.return_val = GetTypeInfo<m_ret>::get_class_info();\
		method_info.return_val_metadata = GetTypeInfo<m_ret>::METADATA;\
		method_info.arguments.push_back(GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type1>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type2>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type2>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type3>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type3>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type4>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type4>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type5>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type5>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type6>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type6>::METADATA);\
		return method_info;\
	}

#define GDVIRTUAL6C_REQUIRED(m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6) const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant vargs[6] = { Variant(arg1), Variant(arg2), Variant(arg3), Variant(arg4), Variant(arg5), Variant(arg6) };\
			const Variant *vargptrs[6] = { &vargs[0], &vargs[1], &vargs[2], &vargs[3], &vargs[4], &vargs[5] };\
			_script_instance->callp(_gdvirtual_##m_name##_sn, (const Variant **)vargptrs, 6, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_type1>::EncodeT argval1 = (PtrToArg<m_type1>::EncodeT)arg1;\
			PtrToArg<m_type2>::EncodeT argval2 = (PtrToArg<m_type2>::EncodeT)arg2;\
			PtrToArg<m_type3>::EncodeT argval3 = (PtrToArg<m_type3>::EncodeT)arg3;\
			PtrToArg<m_type4>::EncodeT argval4 = (PtrToArg<m_type4>::EncodeT)arg4;\
			PtrToArg<m_type5>::EncodeT argval5 = (PtrToArg<m_type5>::EncodeT)arg5;\
			PtrToArg<m_type6>::EncodeT argval6 = (PtrToArg<m_type6>::EncodeT)arg6;\
			GDExtensionConstTypePtr argptrs[6] = { &argval1, &argval2, &argval3, &argval4, &argval5, &argval6 };\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), nullptr);\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), nullptr);\
			}\
			return true;\
		}\
		ERR_PRINT_ONCE("Required virtual method " + get_class() + "::" + #m_name + " must be overridden before calling.");\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL | METHOD_FLAG_CONST | METHOD_FLAG_VIRTUAL_REQUIRED;\
		method_info.arguments.push_back(GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type1>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type2>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type2>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type3>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type3>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type4>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type4>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type5>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type5>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type6>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type6>::METADATA);\
		return method_info;\
	}

#define GDVIRTUAL6RC_REQUIRED(m_ret, m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_ret &r_ret) const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant vargs[6] = { Variant(arg1), Variant(arg2), Variant(arg3), Variant(arg4), Variant(arg5), Variant(arg6) };\
			const Variant *vargptrs[6] = { &vargs[0], &vargs[1], &vargs[2], &vargs[3], &vargs[4], &vargs[5] };\
			Variant ret = _script_instance->callp(_gdvirtual_##m_name##_sn, (const Variant **)vargptrs, 6, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				r_ret = VariantCaster<m_ret>::cast(ret);\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_type1>::EncodeT argval1 = (PtrToArg<m_type1>::EncodeT)arg1;\
			PtrToArg<m_type2>::EncodeT argval2 = (PtrToArg<m_type2>::EncodeT)arg2;\
			PtrToArg<m_type3>::EncodeT argval3 = (PtrToArg<m_type3>::EncodeT)arg3;\
			PtrToArg<m_type4>::EncodeT argval4 = (PtrToArg<m_type4>::EncodeT)arg4;\
			PtrToArg<m_type5>::EncodeT argval5 = (PtrToArg<m_type5>::EncodeT)arg5;\
			PtrToArg<m_type6>::EncodeT argval6 = (PtrToArg<m_type6>::EncodeT)arg6;\
			GDExtensionConstTypePtr argptrs[6] = { &argval1, &argval2, &argval3, &argval4, &argval5, &argval6 };\
			PtrToArg<m_ret>::EncodeT ret;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), &ret);\
				r_ret = (m_ret)ret;\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), &ret);\
				r_ret = (m_ret)ret;\
			}\
			return true;\
		}\
		ERR_PRINT_ONCE("Required virtual method " + get_class() + "::" + #m_name + " must be overridden before calling.");\
		(void)r_ret;\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL | METHOD_FLAG_CONST | METHOD_FLAG_VIRTUAL_REQUIRED;\
		method_info.return_val = GetTypeInfo<m_ret>::get_class_info();\
		method_info.return_val_metadata = GetTypeInfo<m_ret>::METADATA;\
		method_info.arguments.push_back(GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type1>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type2>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type2>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type3>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type3>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type4>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type4>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type5>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type5>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type6>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type6>::METADATA);\
		return method_info;\
	}

/* 7 Arguments */

#define GDVIRTUAL7(m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7) {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant vargs[7] = { Variant(arg1), Variant(arg2), Variant(arg3), Variant(arg4), Variant(arg5), Variant(arg6), Variant(arg7) };\
			const Variant *vargptrs[7] = { &vargs[0], &vargs[1], &vargs[2], &vargs[3], &vargs[4], &vargs[5], &vargs[6] };\
			_script_instance->callp(_gdvirtual_##m_name##_sn, (const Variant **)vargptrs, 7, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_type1>::EncodeT argval1 = (PtrToArg<m_type1>::EncodeT)arg1;\
			PtrToArg<m_type2>::EncodeT argval2 = (PtrToArg<m_type2>::EncodeT)arg2;\
			PtrToArg<m_type3>::EncodeT argval3 = (PtrToArg<m_type3>::EncodeT)arg3;\
			PtrToArg<m_type4>::EncodeT argval4 = (PtrToArg<m_type4>::EncodeT)arg4;\
			PtrToArg<m_type5>::EncodeT argval5 = (PtrToArg<m_type5>::EncodeT)arg5;\
			PtrToArg<m_type6>::EncodeT argval6 = (PtrToArg<m_type6>::EncodeT)arg6;\
			PtrToArg<m_type7>::EncodeT argval7 = (PtrToArg<m_type7>::EncodeT)arg7;\
			GDExtensionConstTypePtr argptrs[7] = { &argval1, &argval2, &argval3, &argval4, &argval5, &argval6, &argval7 };\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), nullptr);\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), nullptr);\
			}\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL;\
		method_info.arguments.push_back(GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type1>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type2>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type2>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type3>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type3>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type4>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type4>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type5>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type5>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type6>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type6>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type7>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type7>::METADATA);\
		return method_info;\
	}

#define GDVIRTUAL7R(m_ret, m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_ret &r_ret) {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant vargs[7] = { Variant(arg1), Variant(arg2), Variant(arg3), Variant(arg4), Variant(arg5), Variant(arg6), Variant(arg7) };\
			const Variant *vargptrs[7] = { &vargs[0], &vargs[1], &vargs[2], &vargs[3], &vargs[4], &vargs[5], &vargs[6] };\
			Variant ret = _script_instance->callp(_gdvirtual_##m_name##_sn, (const Variant **)vargptrs, 7, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				r_ret = VariantCaster<m_ret>::cast(ret);\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_type1>::EncodeT argval1 = (PtrToArg<m_type1>::EncodeT)arg1;\
			PtrToArg<m_type2>::EncodeT argval2 = (PtrToArg<m_type2>::EncodeT)arg2;\
			PtrToArg<m_type3>::EncodeT argval3 = (PtrToArg<m_type3>::EncodeT)arg3;\
			PtrToArg<m_type4>::EncodeT argval4 = (PtrToArg<m_type4>::EncodeT)arg4;\
			PtrToArg<m_type5>::EncodeT argval5 = (PtrToArg<m_type5>::EncodeT)arg5;\
			PtrToArg<m_type6>::EncodeT argval6 = (PtrToArg<m_type6>::EncodeT)arg6;\
			PtrToArg<m_type7>::EncodeT argval7 = (PtrToArg<m_type7>::EncodeT)arg7;\
			GDExtensionConstTypePtr argptrs[7] = { &argval1, &argval2, &argval3, &argval4, &argval5, &argval6, &argval7 };\
			PtrToArg<m_ret>::EncodeT ret;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), &ret);\
				r_ret = (m_ret)ret;\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), &ret);\
				r_ret = (m_ret)ret;\
			}\
			return true;\
		}\
		(void)r_ret;\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL;\
		method_info.return_val = GetTypeInfo<m_ret>::get_class_info();\
		method_info.return_val_metadata = GetTypeInfo<m_ret>::METADATA;\
		method_info.arguments.push_back(GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type1>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type2>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type2>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type3>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type3>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type4>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type4>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type5>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type5>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type6>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type6>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type7>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type7>::METADATA);\
		return method_info;\
	}

#define GDVIRTUAL7C(m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7) const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant vargs[7] = { Variant(arg1), Variant(arg2), Variant(arg3), Variant(arg4), Variant(arg5), Variant(arg6), Variant(arg7) };\
			const Variant *vargptrs[7] = { &vargs[0], &vargs[1], &vargs[2], &vargs[3], &vargs[4], &vargs[5], &vargs[6] };\
			_script_instance->callp(_gdvirtual_##m_name##_sn, (const Variant **)vargptrs, 7, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_type1>::EncodeT argval1 = (PtrToArg<m_type1>::EncodeT)arg1;\
			PtrToArg<m_type2>::EncodeT argval2 = (PtrToArg<m_type2>::EncodeT)arg2;\
			PtrToArg<m_type3>::EncodeT argval3 = (PtrToArg<m_type3>::EncodeT)arg3;\
			PtrToArg<m_type4>::EncodeT argval4 = (PtrToArg<m_type4>::EncodeT)arg4;\
			PtrToArg<m_type5>::EncodeT argval5 = (PtrToArg<m_type5>::EncodeT)arg5;\
			PtrToArg<m_type6>::EncodeT argval6 = (PtrToArg<m_type6>::EncodeT)arg6;\
			PtrToArg<m_type7>::EncodeT argval7 = (PtrToArg<m_type7>::EncodeT)arg7;\
			GDExtensionConstTypePtr argptrs[7] = { &argval1, &argval2, &argval3, &argval4, &argval5, &argval6, &argval7 };\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), nullptr);\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), nullptr);\
			}\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL | METHOD_FLAG_CONST;\
		method_info.arguments.push_back(GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type1>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type2>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type2>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type3>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type3>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type4>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type4>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type5>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type5>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type6>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type6>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type7>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type7>::METADATA);\
		return method_info;\
	}

#define GDVIRTUAL7RC(m_ret, m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_ret &r_ret) const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant vargs[7] = { Variant(arg1), Variant(arg2), Variant(arg3), Variant(arg4), Variant(arg5), Variant(arg6), Variant(arg7) };\
			const Variant *vargptrs[7] = { &vargs[0], &vargs[1], &vargs[2], &vargs[3], &vargs[4], &vargs[5], &vargs[6] };\
			Variant ret = _script_instance->callp(_gdvirtual_##m_name##_sn, (const Variant **)vargptrs, 7, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				r_ret = VariantCaster<m_ret>::cast(ret);\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_type1>::EncodeT argval1 = (PtrToArg<m_type1>::EncodeT)arg1;\
			PtrToArg<m_type2>::EncodeT argval2 = (PtrToArg<m_type2>::EncodeT)arg2;\
			PtrToArg<m_type3>::EncodeT argval3 = (PtrToArg<m_type3>::EncodeT)arg3;\
			PtrToArg<m_type4>::EncodeT argval4 = (PtrToArg<m_type4>::EncodeT)arg4;\
			PtrToArg<m_type5>::EncodeT argval5 = (PtrToArg<m_type5>::EncodeT)arg5;\
			PtrToArg<m_type6>::EncodeT argval6 = (PtrToArg<m_type6>::EncodeT)arg6;\
			PtrToArg<m_type7>::EncodeT argval7 = (PtrToArg<m_type7>::EncodeT)arg7;\
			GDExtensionConstTypePtr argptrs[7] = { &argval1, &argval2, &argval3, &argval4, &argval5, &argval6, &argval7 };\
			PtrToArg<m_ret>::EncodeT ret;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), &ret);\
				r_ret = (m_ret)ret;\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), &ret);\
				r_ret = (m_ret)ret;\
			}\
			return true;\
		}\
		(void)r_ret;\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL | METHOD_FLAG_CONST;\
		method_info.return_val = GetTypeInfo<m_ret>::get_class_info();\
		method_info.return_val_metadata = GetTypeInfo<m_ret>::METADATA;\
		method_info.arguments.push_back(GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type1>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type2>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type2>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type3>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type3>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type4>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type4>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type5>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type5>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type6>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type6>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type7>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type7>::METADATA);\
		return method_info;\
	}

#define GDVIRTUAL7_REQUIRED(m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7) {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant vargs[7] = { Variant(arg1), Variant(arg2), Variant(arg3), Variant(arg4), Variant(arg5), Variant(arg6), Variant(arg7) };\
			const Variant *vargptrs[7] = { &vargs[0], &vargs[1], &vargs[2], &vargs[3], &vargs[4], &vargs[5], &vargs[6] };\
			_script_instance->callp(_gdvirtual_##m_name##_sn, (const Variant **)vargptrs, 7, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_type1>::EncodeT argval1 = (PtrToArg<m_type1>::EncodeT)arg1;\
			PtrToArg<m_type2>::EncodeT argval2 = (PtrToArg<m_type2>::EncodeT)arg2;\
			PtrToArg<m_type3>::EncodeT argval3 = (PtrToArg<m_type3>::EncodeT)arg3;\
			PtrToArg<m_type4>::EncodeT argval4 = (PtrToArg<m_type4>::EncodeT)arg4;\
			PtrToArg<m_type5>::EncodeT argval5 = (PtrToArg<m_type5>::EncodeT)arg5;\
			PtrToArg<m_type6>::EncodeT argval6 = (PtrToArg<m_type6>::EncodeT)arg6;\
			PtrToArg<m_type7>::EncodeT argval7 = (PtrToArg<m_type7>::EncodeT)arg7;\
			GDExtensionConstTypePtr argptrs[7] = { &argval1, &argval2, &argval3, &argval4, &argval5, &argval6, &argval7 };\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), nullptr);\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), nullptr);\
			}\
			return true;\
		}\
		ERR_PRINT_ONCE("Required virtual method " + get_class() + "::" + #m_name + " must be overridden before calling.");\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL | METHOD_FLAG_VIRTUAL_REQUIRED;\
		method_info.arguments.push_back(GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type1>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type2>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type2>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type3>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type3>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type4>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type4>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type5>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type5>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type6>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type6>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type7>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type7>::METADATA);\
		return method_info;\
	}

#define GDVIRTUAL7R_REQUIRED(m_ret, m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_ret &r_ret) {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant vargs[7] = { Variant(arg1), Variant(arg2), Variant(arg3), Variant(arg4), Variant(arg5), Variant(arg6), Variant(arg7) };\
			const Variant *vargptrs[7] = { &vargs[0], &vargs[1], &vargs[2], &vargs[3], &vargs[4], &vargs[5], &vargs[6] };\
			Variant ret = _script_instance->callp(_gdvirtual_##m_name##_sn, (const Variant **)vargptrs, 7, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				r_ret = VariantCaster<m_ret>::cast(ret);\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_type1>::EncodeT argval1 = (PtrToArg<m_type1>::EncodeT)arg1;\
			PtrToArg<m_type2>::EncodeT argval2 = (PtrToArg<m_type2>::EncodeT)arg2;\
			PtrToArg<m_type3>::EncodeT argval3 = (PtrToArg<m_type3>::EncodeT)arg3;\
			PtrToArg<m_type4>::EncodeT argval4 = (PtrToArg<m_type4>::EncodeT)arg4;\
			PtrToArg<m_type5>::EncodeT argval5 = (PtrToArg<m_type5>::EncodeT)arg5;\
			PtrToArg<m_type6>::EncodeT argval6 = (PtrToArg<m_type6>::EncodeT)arg6;\
			PtrToArg<m_type7>::EncodeT argval7 = (PtrToArg<m_type7>::EncodeT)arg7;\
			GDExtensionConstTypePtr argptrs[7] = { &argval1, &argval2, &argval3, &argval4, &argval5, &argval6, &argval7 };\
			PtrToArg<m_ret>::EncodeT ret;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), &ret);\
				r_ret = (m_ret)ret;\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), &ret);\
				r_ret = (m_ret)ret;\
			}\
			return true;\
		}\
		ERR_PRINT_ONCE("Required virtual method " + get_class() + "::" + #m_name + " must be overridden before calling.");\
		(void)r_ret;\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL | METHOD_FLAG_VIRTUAL_REQUIRED;\
		method_info.return_val = GetTypeInfo<m_ret>::get_class_info();\
		method_info.return_val_metadata = GetTypeInfo<m_ret>::METADATA;\
		method_info.arguments.push_back(GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type1>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type2>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type2>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type3>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type3>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type4>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type4>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type5>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type5>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type6>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type6>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type7>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type7>::METADATA);\
		return method_info;\
	}

#define GDVIRTUAL7C_REQUIRED(m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7) const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant vargs[7] = { Variant(arg1), Variant(arg2), Variant(arg3), Variant(arg4), Variant(arg5), Variant(arg6), Variant(arg7) };\
			const Variant *vargptrs[7] = { &vargs[0], &vargs[1], &vargs[2], &vargs[3], &vargs[4], &vargs[5], &vargs[6] };\
			_script_instance->callp(_gdvirtual_##m_name##_sn, (const Variant **)vargptrs, 7, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_type1>::EncodeT argval1 = (PtrToArg<m_type1>::EncodeT)arg1;\
			PtrToArg<m_type2>::EncodeT argval2 = (PtrToArg<m_type2>::EncodeT)arg2;\
			PtrToArg<m_type3>::EncodeT argval3 = (PtrToArg<m_type3>::EncodeT)arg3;\
			PtrToArg<m_type4>::EncodeT argval4 = (PtrToArg<m_type4>::EncodeT)arg4;\
			PtrToArg<m_type5>::EncodeT argval5 = (PtrToArg<m_type5>::EncodeT)arg5;\
			PtrToArg<m_type6>::EncodeT argval6 = (PtrToArg<m_type6>::EncodeT)arg6;\
			PtrToArg<m_type7>::EncodeT argval7 = (PtrToArg<m_type7>::EncodeT)arg7;\
			GDExtensionConstTypePtr argptrs[7] = { &argval1, &argval2, &argval3, &argval4, &argval5, &argval6, &argval7 };\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), nullptr);\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), nullptr);\
			}\
			return true;\
		}\
		ERR_PRINT_ONCE("Required virtual method " + get_class() + "::" + #m_name + " must be overridden before calling.");\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL | METHOD_FLAG_CONST | METHOD_FLAG_VIRTUAL_REQUIRED;\
		method_info.arguments.push_back(GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type1>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type2>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type2>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type3>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type3>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type4>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type4>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type5>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type5>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type6>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type6>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type7>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type7>::METADATA);\
		return method_info;\
	}

#define GDVIRTUAL7RC_REQUIRED(m_ret, m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_ret &r_ret) const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant vargs[7] = { Variant(arg1), Variant(arg2), Variant(arg3), Variant(arg4), Variant(arg5), Variant(arg6), Variant(arg7) };\
			const Variant *vargptrs[7] = { &vargs[0], &vargs[1], &vargs[2], &vargs[3], &vargs[4], &vargs[5], &vargs[6] };\
			Variant ret = _script_instance->callp(_gdvirtual_##m_name##_sn, (const Variant **)vargptrs, 7, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				r_ret = VariantCaster<m_ret>::cast(ret);\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_type1>::EncodeT argval1 = (PtrToArg<m_type1>::EncodeT)arg1;\
			PtrToArg<m_type2>::EncodeT argval2 = (PtrToArg<m_type2>::EncodeT)arg2;\
			PtrToArg<m_type3>::EncodeT argval3 = (PtrToArg<m_type3>::EncodeT)arg3;\
			PtrToArg<m_type4>::EncodeT argval4 = (PtrToArg<m_type4>::EncodeT)arg4;\
			PtrToArg<m_type5>::EncodeT argval5 = (PtrToArg<m_type5>::EncodeT)arg5;\
			PtrToArg<m_type6>::EncodeT argval6 = (PtrToArg<m_type6>::EncodeT)arg6;\
			PtrToArg<m_type7>::EncodeT argval7 = (PtrToArg<m_type7>::EncodeT)arg7;\
			GDExtensionConstTypePtr argptrs[7] = { &argval1, &argval2, &argval3, &argval4, &argval5, &argval6, &argval7 };\
			PtrToArg<m_ret>::EncodeT ret;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), &ret);\
				r_ret = (m_ret)ret;\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), &ret);\
				r_ret = (m_ret)ret;\
			}\
			return true;\
		}\
		ERR_PRINT_ONCE("Required virtual method " + get_class() + "::" + #m_name + " must be overridden before calling.");\
		(void)r_ret;\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL | METHOD_FLAG_CONST | METHOD_FLAG_VIRTUAL_REQUIRED;\
		method_info.return_val = GetTypeInfo<m_ret>::get_class_info();\
		method_info.return_val_metadata = GetTypeInfo<m_ret>::METADATA;\
		method_info.arguments.push_back(GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type1>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type2>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type2>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type3>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type3>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type4>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type4>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type5>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type5>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type6>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type6>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type7>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type7>::METADATA);\
		return method_info;\
	}

/* 8 Arguments */

#define GDVIRTUAL8(m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8) {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant vargs[8] = { Variant(arg1), Variant(arg2), Variant(arg3), Variant(arg4), Variant(arg5), Variant(arg6), Variant(arg7), Variant(arg8) };\
			const Variant *vargptrs[8] = { &vargs[0], &vargs[1], &vargs[2], &vargs[3], &vargs[4], &vargs[5], &vargs[6], &vargs[7] };\
			_script_instance->callp(_gdvirtual_##m_name##_sn, (const Variant **)vargptrs, 8, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_type1>::EncodeT argval1 = (PtrToArg<m_type1>::EncodeT)arg1;\
			PtrToArg<m_type2>::EncodeT argval2 = (PtrToArg<m_type2>::EncodeT)arg2;\
			PtrToArg<m_type3>::EncodeT argval3 = (PtrToArg<m_type3>::EncodeT)arg3;\
			PtrToArg<m_type4>::EncodeT argval4 = (PtrToArg<m_type4>::EncodeT)arg4;\
			PtrToArg<m_type5>::EncodeT argval5 = (PtrToArg<m_type5>::EncodeT)arg5;\
			PtrToArg<m_type6>::EncodeT argval6 = (PtrToArg<m_type6>::EncodeT)arg6;\
			PtrToArg<m_type7>::EncodeT argval7 = (PtrToArg<m_type7>::EncodeT)arg7;\
			PtrToArg<m_type8>::EncodeT argval8 = (PtrToArg<m_type8>::EncodeT)arg8;\
			GDExtensionConstTypePtr argptrs[8] = { &argval1, &argval2, &argval3, &argval4, &argval5, &argval6, &argval7, &argval8 };\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), nullptr);\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), nullptr);\
			}\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL;\
		method_info.arguments.push_back(GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type1>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type2>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type2>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type3>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type3>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type4>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type4>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type5>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type5>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type6>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type6>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type7>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type7>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type8>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type8>::METADATA);\
		return method_info;\
	}

#define GDVIRTUAL8R(m_ret, m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8, m_ret &r_ret) {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant vargs[8] = { Variant(arg1), Variant(arg2), Variant(arg3), Variant(arg4), Variant(arg5), Variant(arg6), Variant(arg7), Variant(arg8) };\
			const Variant *vargptrs[8] = { &vargs[0], &vargs[1], &vargs[2], &vargs[3], &vargs[4], &vargs[5], &vargs[6], &vargs[7] };\
			Variant ret = _script_instance->callp(_gdvirtual_##m_name##_sn, (const Variant **)vargptrs, 8, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				r_ret = VariantCaster<m_ret>::cast(ret);\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_type1>::EncodeT argval1 = (PtrToArg<m_type1>::EncodeT)arg1;\
			PtrToArg<m_type2>::EncodeT argval2 = (PtrToArg<m_type2>::EncodeT)arg2;\
			PtrToArg<m_type3>::EncodeT argval3 = (PtrToArg<m_type3>::EncodeT)arg3;\
			PtrToArg<m_type4>::EncodeT argval4 = (PtrToArg<m_type4>::EncodeT)arg4;\
			PtrToArg<m_type5>::EncodeT argval5 = (PtrToArg<m_type5>::EncodeT)arg5;\
			PtrToArg<m_type6>::EncodeT argval6 = (PtrToArg<m_type6>::EncodeT)arg6;\
			PtrToArg<m_type7>::EncodeT argval7 = (PtrToArg<m_type7>::EncodeT)arg7;\
			PtrToArg<m_type8>::EncodeT argval8 = (PtrToArg<m_type8>::EncodeT)arg8;\
			GDExtensionConstTypePtr argptrs[8] = { &argval1, &argval2, &argval3, &argval4, &argval5, &argval6, &argval7, &argval8 };\
			PtrToArg<m_ret>::EncodeT ret;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), &ret);\
				r_ret = (m_ret)ret;\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), &ret);\
				r_ret = (m_ret)ret;\
			}\
			return true;\
		}\
		(void)r_ret;\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL;\
		method_info.return_val = GetTypeInfo<m_ret>::get_class_info();\
		method_info.return_val_metadata = GetTypeInfo<m_ret>::METADATA;\
		method_info.arguments.push_back(GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type1>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type2>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type2>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type3>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type3>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type4>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type4>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type5>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type5>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type6>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type6>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type7>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type7>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type8>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type8>::METADATA);\
		return method_info;\
	}

#define GDVIRTUAL8C(m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8) const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant vargs[8] = { Variant(arg1), Variant(arg2), Variant(arg3), Variant(arg4), Variant(arg5), Variant(arg6), Variant(arg7), Variant(arg8) };\
			const Variant *vargptrs[8] = { &vargs[0], &vargs[1], &vargs[2], &vargs[3], &vargs[4], &vargs[5], &vargs[6], &vargs[7] };\
			_script_instance->callp(_gdvirtual_##m_name##_sn, (const Variant **)vargptrs, 8, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_type1>::EncodeT argval1 = (PtrToArg<m_type1>::EncodeT)arg1;\
			PtrToArg<m_type2>::EncodeT argval2 = (PtrToArg<m_type2>::EncodeT)arg2;\
			PtrToArg<m_type3>::EncodeT argval3 = (PtrToArg<m_type3>::EncodeT)arg3;\
			PtrToArg<m_type4>::EncodeT argval4 = (PtrToArg<m_type4>::EncodeT)arg4;\
			PtrToArg<m_type5>::EncodeT argval5 = (PtrToArg<m_type5>::EncodeT)arg5;\
			PtrToArg<m_type6>::EncodeT argval6 = (PtrToArg<m_type6>::EncodeT)arg6;\
			PtrToArg<m_type7>::EncodeT argval7 = (PtrToArg<m_type7>::EncodeT)arg7;\
			PtrToArg<m_type8>::EncodeT argval8 = (PtrToArg<m_type8>::EncodeT)arg8;\
			GDExtensionConstTypePtr argptrs[8] = { &argval1, &argval2, &argval3, &argval4, &argval5, &argval6, &argval7, &argval8 };\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), nullptr);\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), nullptr);\
			}\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL | METHOD_FLAG_CONST;\
		method_info.arguments.push_back(GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type1>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type2>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type2>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type3>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type3>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type4>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type4>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type5>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type5>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type6>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type6>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type7>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type7>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type8>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type8>::METADATA);\
		return method_info;\
	}

#define GDVIRTUAL8RC(m_ret, m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8, m_ret &r_ret) const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant vargs[8] = { Variant(arg1), Variant(arg2), Variant(arg3), Variant(arg4), Variant(arg5), Variant(arg6), Variant(arg7), Variant(arg8) };\
			const Variant *vargptrs[8] = { &vargs[0], &vargs[1], &vargs[2], &vargs[3], &vargs[4], &vargs[5], &vargs[6], &vargs[7] };\
			Variant ret = _script_instance->callp(_gdvirtual_##m_name##_sn, (const Variant **)vargptrs, 8, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				r_ret = VariantCaster<m_ret>::cast(ret);\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_type1>::EncodeT argval1 = (PtrToArg<m_type1>::EncodeT)arg1;\
			PtrToArg<m_type2>::EncodeT argval2 = (PtrToArg<m_type2>::EncodeT)arg2;\
			PtrToArg<m_type3>::EncodeT argval3 = (PtrToArg<m_type3>::EncodeT)arg3;\
			PtrToArg<m_type4>::EncodeT argval4 = (PtrToArg<m_type4>::EncodeT)arg4;\
			PtrToArg<m_type5>::EncodeT argval5 = (PtrToArg<m_type5>::EncodeT)arg5;\
			PtrToArg<m_type6>::EncodeT argval6 = (PtrToArg<m_type6>::EncodeT)arg6;\
			PtrToArg<m_type7>::EncodeT argval7 = (PtrToArg<m_type7>::EncodeT)arg7;\
			PtrToArg<m_type8>::EncodeT argval8 = (PtrToArg<m_type8>::EncodeT)arg8;\
			GDExtensionConstTypePtr argptrs[8] = { &argval1, &argval2, &argval3, &argval4, &argval5, &argval6, &argval7, &argval8 };\
			PtrToArg<m_ret>::EncodeT ret;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), &ret);\
				r_ret = (m_ret)ret;\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), &ret);\
				r_ret = (m_ret)ret;\
			}\
			return true;\
		}\
		(void)r_ret;\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL | METHOD_FLAG_CONST;\
		method_info.return_val = GetTypeInfo<m_ret>::get_class_info();\
		method_info.return_val_metadata = GetTypeInfo<m_ret>::METADATA;\
		method_info.arguments.push_back(GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type1>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type2>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type2>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type3>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type3>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type4>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type4>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type5>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type5>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type6>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type6>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type7>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type7>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type8>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type8>::METADATA);\
		return method_info;\
	}

#define GDVIRTUAL8_REQUIRED(m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8) {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant vargs[8] = { Variant(arg1), Variant(arg2), Variant(arg3), Variant(arg4), Variant(arg5), Variant(arg6), Variant(arg7), Variant(arg8) };\
			const Variant *vargptrs[8] = { &vargs[0], &vargs[1], &vargs[2], &vargs[3], &vargs[4], &vargs[5], &vargs[6], &vargs[7] };\
			_script_instance->callp(_gdvirtual_##m_name##_sn, (const Variant **)vargptrs, 8, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_type1>::EncodeT argval1 = (PtrToArg<m_type1>::EncodeT)arg1;\
			PtrToArg<m_type2>::EncodeT argval2 = (PtrToArg<m_type2>::EncodeT)arg2;\
			PtrToArg<m_type3>::EncodeT argval3 = (PtrToArg<m_type3>::EncodeT)arg3;\
			PtrToArg<m_type4>::EncodeT argval4 = (PtrToArg<m_type4>::EncodeT)arg4;\
			PtrToArg<m_type5>::EncodeT argval5 = (PtrToArg<m_type5>::EncodeT)arg5;\
			PtrToArg<m_type6>::EncodeT argval6 = (PtrToArg<m_type6>::EncodeT)arg6;\
			PtrToArg<m_type7>::EncodeT argval7 = (PtrToArg<m_type7>::EncodeT)arg7;\
			PtrToArg<m_type8>::EncodeT argval8 = (PtrToArg<m_type8>::EncodeT)arg8;\
			GDExtensionConstTypePtr argptrs[8] = { &argval1, &argval2, &argval3, &argval4, &argval5, &argval6, &argval7, &argval8 };\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), nullptr);\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), nullptr);\
			}\
			return true;\
		}\
		ERR_PRINT_ONCE("Required virtual method " + get_class() + "::" + #m_name + " must be overridden before calling.");\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL | METHOD_FLAG_VIRTUAL_REQUIRED;\
		method_info.arguments.push_back(GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type1>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type2>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type2>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type3>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type3>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type4>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type4>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type5>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type5>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type6>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type6>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type7>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type7>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type8>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type8>::METADATA);\
		return method_info;\
	}

#define GDVIRTUAL8R_REQUIRED(m_ret, m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8, m_ret &r_ret) {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant vargs[8] = { Variant(arg1), Variant(arg2), Variant(arg3), Variant(arg4), Variant(arg5), Variant(arg6), Variant(arg7), Variant(arg8) };\
			const Variant *vargptrs[8] = { &vargs[0], &vargs[1], &vargs[2], &vargs[3], &vargs[4], &vargs[5], &vargs[6], &vargs[7] };\
			Variant ret = _script_instance->callp(_gdvirtual_##m_name##_sn, (const Variant **)vargptrs, 8, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				r_ret = VariantCaster<m_ret>::cast(ret);\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_type1>::EncodeT argval1 = (PtrToArg<m_type1>::EncodeT)arg1;\
			PtrToArg<m_type2>::EncodeT argval2 = (PtrToArg<m_type2>::EncodeT)arg2;\
			PtrToArg<m_type3>::EncodeT argval3 = (PtrToArg<m_type3>::EncodeT)arg3;\
			PtrToArg<m_type4>::EncodeT argval4 = (PtrToArg<m_type4>::EncodeT)arg4;\
			PtrToArg<m_type5>::EncodeT argval5 = (PtrToArg<m_type5>::EncodeT)arg5;\
			PtrToArg<m_type6>::EncodeT argval6 = (PtrToArg<m_type6>::EncodeT)arg6;\
			PtrToArg<m_type7>::EncodeT argval7 = (PtrToArg<m_type7>::EncodeT)arg7;\
			PtrToArg<m_type8>::EncodeT argval8 = (PtrToArg<m_type8>::EncodeT)arg8;\
			GDExtensionConstTypePtr argptrs[8] = { &argval1, &argval2, &argval3, &argval4, &argval5, &argval6, &argval7, &argval8 };\
			PtrToArg<m_ret>::EncodeT ret;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), &ret);\
				r_ret = (m_ret)ret;\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), &ret);\
				r_ret = (m_ret)ret;\
			}\
			return true;\
		}\
		ERR_PRINT_ONCE("Required virtual method " + get_class() + "::" + #m_name + " must be overridden before calling.");\
		(void)r_ret;\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL | METHOD_FLAG_VIRTUAL_REQUIRED;\
		method_info.return_val = GetTypeInfo<m_ret>::get_class_info();\
		method_info.return_val_metadata = GetTypeInfo<m_ret>::METADATA;\
		method_info.arguments.push_back(GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type1>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type2>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type2>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type3>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type3>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type4>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type4>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type5>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type5>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type6>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type6>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type7>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type7>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type8>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type8>::METADATA);\
		return method_info;\
	}

#define GDVIRTUAL8C_REQUIRED(m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8) const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant vargs[8] = { Variant(arg1), Variant(arg2), Variant(arg3), Variant(arg4), Variant(arg5), Variant(arg6), Variant(arg7), Variant(arg8) };\
			const Variant *vargptrs[8] = { &vargs[0], &vargs[1], &vargs[2], &vargs[3], &vargs[4], &vargs[5], &vargs[6], &vargs[7] };\
			_script_instance->callp(_gdvirtual_##m_name##_sn, (const Variant **)vargptrs, 8, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_type1>::EncodeT argval1 = (PtrToArg<m_type1>::EncodeT)arg1;\
			PtrToArg<m_type2>::EncodeT argval2 = (PtrToArg<m_type2>::EncodeT)arg2;\
			PtrToArg<m_type3>::EncodeT argval3 = (PtrToArg<m_type3>::EncodeT)arg3;\
			PtrToArg<m_type4>::EncodeT argval4 = (PtrToArg<m_type4>::EncodeT)arg4;\
			PtrToArg<m_type5>::EncodeT argval5 = (PtrToArg<m_type5>::EncodeT)arg5;\
			PtrToArg<m_type6>::EncodeT argval6 = (PtrToArg<m_type6>::EncodeT)arg6;\
			PtrToArg<m_type7>::EncodeT argval7 = (PtrToArg<m_type7>::EncodeT)arg7;\
			PtrToArg<m_type8>::EncodeT argval8 = (PtrToArg<m_type8>::EncodeT)arg8;\
			GDExtensionConstTypePtr argptrs[8] = { &argval1, &argval2, &argval3, &argval4, &argval5, &argval6, &argval7, &argval8 };\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), nullptr);\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), nullptr);\
			}\
			return true;\
		}\
		ERR_PRINT_ONCE("Required virtual method " + get_class() + "::" + #m_name + " must be overridden before calling.");\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL | METHOD_FLAG_CONST | METHOD_FLAG_VIRTUAL_REQUIRED;\
		method_info.arguments.push_back(GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type1>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type2>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type2>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type3>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type3>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type4>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type4>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type5>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type5>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type6>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type6>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type7>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type7>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type8>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type8>::METADATA);\
		return method_info;\
	}

#define GDVIRTUAL8RC_REQUIRED(m_ret, m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8, m_ret &r_ret) const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant vargs[8] = { Variant(arg1), Variant(arg2), Variant(arg3), Variant(arg4), Variant(arg5), Variant(arg6), Variant(arg7), Variant(arg8) };\
			const Variant *vargptrs[8] = { &vargs[0], &vargs[1], &vargs[2], &vargs[3], &vargs[4], &vargs[5], &vargs[6], &vargs[7] };\
			Variant ret = _script_instance->callp(_gdvirtual_##m_name##_sn, (const Variant **)vargptrs, 8, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				r_ret = VariantCaster<m_ret>::cast(ret);\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_type1>::EncodeT argval1 = (PtrToArg<m_type1>::EncodeT)arg1;\
			PtrToArg<m_type2>::EncodeT argval2 = (PtrToArg<m_type2>::EncodeT)arg2;\
			PtrToArg<m_type3>::EncodeT argval3 = (PtrToArg<m_type3>::EncodeT)arg3;\
			PtrToArg<m_type4>::EncodeT argval4 = (PtrToArg<m_type4>::EncodeT)arg4;\
			PtrToArg<m_type5>::EncodeT argval5 = (PtrToArg<m_type5>::EncodeT)arg5;\
			PtrToArg<m_type6>::EncodeT argval6 = (PtrToArg<m_type6>::EncodeT)arg6;\
			PtrToArg<m_type7>::EncodeT argval7 = (PtrToArg<m_type7>::EncodeT)arg7;\
			PtrToArg<m_type8>::EncodeT argval8 = (PtrToArg<m_type8>::EncodeT)arg8;\
			GDExtensionConstTypePtr argptrs[8] = { &argval1, &argval2, &argval3, &argval4, &argval5, &argval6, &argval7, &argval8 };\
			PtrToArg<m_ret>::EncodeT ret;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), &ret);\
				r_ret = (m_ret)ret;\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), &ret);\
				r_ret = (m_ret)ret;\
			}\
			return true;\
		}\
		ERR_PRINT_ONCE("Required virtual method " + get_class() + "::" + #m_name + " must be overridden before calling.");\
		(void)r_ret;\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL | METHOD_FLAG_CONST | METHOD_FLAG_VIRTUAL_REQUIRED;\
		method_info.return_val = GetTypeInfo<m_ret>::get_class_info();\
		method_info.return_val_metadata = GetTypeInfo<m_ret>::METADATA;\
		method_info.arguments.push_back(GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type1>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type2>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type2>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type3>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type3>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type4>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type4>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type5>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type5>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type6>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type6>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type7>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type7>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type8>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type8>::METADATA);\
		return method_info;\
	}

/* 9 Arguments */

#define GDVIRTUAL9(m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8, m_type9)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8, m_type9 arg9) {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant vargs[9] = { Variant(arg1), Variant(arg2), Variant(arg3), Variant(arg4), Variant(arg5), Variant(arg6), Variant(arg7), Variant(arg8), Variant(arg9) };\
			const Variant *vargptrs[9] = { &vargs[0], &vargs[1], &vargs[2], &vargs[3], &vargs[4], &vargs[5], &vargs[6], &vargs[7], &vargs[8] };\
			_script_instance->callp(_gdvirtual_##m_name##_sn, (const Variant **)vargptrs, 9, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_type1>::EncodeT argval1 = (PtrToArg<m_type1>::EncodeT)arg1;\
			PtrToArg<m_type2>::EncodeT argval2 = (PtrToArg<m_type2>::EncodeT)arg2;\
			PtrToArg<m_type3>::EncodeT argval3 = (PtrToArg<m_type3>::EncodeT)arg3;\
			PtrToArg<m_type4>::EncodeT argval4 = (PtrToArg<m_type4>::EncodeT)arg4;\
			PtrToArg<m_type5>::EncodeT argval5 = (PtrToArg<m_type5>::EncodeT)arg5;\
			PtrToArg<m_type6>::EncodeT argval6 = (PtrToArg<m_type6>::EncodeT)arg6;\
			PtrToArg<m_type7>::EncodeT argval7 = (PtrToArg<m_type7>::EncodeT)arg7;\
			PtrToArg<m_type8>::EncodeT argval8 = (PtrToArg<m_type8>::EncodeT)arg8;\
			PtrToArg<m_type9>::EncodeT argval9 = (PtrToArg<m_type9>::EncodeT)arg9;\
			GDExtensionConstTypePtr argptrs[9] = { &argval1, &argval2, &argval3, &argval4, &argval5, &argval6, &argval7, &argval8, &argval9 };\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), nullptr);\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), nullptr);\
			}\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL;\
		method_info.arguments.push_back(GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type1>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type2>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type2>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type3>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type3>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type4>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type4>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type5>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type5>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type6>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type6>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type7>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type7>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type8>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type8>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type9>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type9>::METADATA);\
		return method_info;\
	}

#define GDVIRTUAL9R(m_ret, m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8, m_type9)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8, m_type9 arg9, m_ret &r_ret) {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant vargs[9] = { Variant(arg1), Variant(arg2), Variant(arg3), Variant(arg4), Variant(arg5), Variant(arg6), Variant(arg7), Variant(arg8), Variant(arg9) };\
			const Variant *vargptrs[9] = { &vargs[0], &vargs[1], &vargs[2], &vargs[3], &vargs[4], &vargs[5], &vargs[6], &vargs[7], &vargs[8] };\
			Variant ret = _script_instance->callp(_gdvirtual_##m_name##_sn, (const Variant **)vargptrs, 9, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				r_ret = VariantCaster<m_ret>::cast(ret);\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_type1>::EncodeT argval1 = (PtrToArg<m_type1>::EncodeT)arg1;\
			PtrToArg<m_type2>::EncodeT argval2 = (PtrToArg<m_type2>::EncodeT)arg2;\
			PtrToArg<m_type3>::EncodeT argval3 = (PtrToArg<m_type3>::EncodeT)arg3;\
			PtrToArg<m_type4>::EncodeT argval4 = (PtrToArg<m_type4>::EncodeT)arg4;\
			PtrToArg<m_type5>::EncodeT argval5 = (PtrToArg<m_type5>::EncodeT)arg5;\
			PtrToArg<m_type6>::EncodeT argval6 = (PtrToArg<m_type6>::EncodeT)arg6;\
			PtrToArg<m_type7>::EncodeT argval7 = (PtrToArg<m_type7>::EncodeT)arg7;\
			PtrToArg<m_type8>::EncodeT argval8 = (PtrToArg<m_type8>::EncodeT)arg8;\
			PtrToArg<m_type9>::EncodeT argval9 = (PtrToArg<m_type9>::EncodeT)arg9;\
			GDExtensionConstTypePtr argptrs[9] = { &argval1, &argval2, &argval3, &argval4, &argval5, &argval6, &argval7, &argval8, &argval9 };\
			PtrToArg<m_ret>::EncodeT ret;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), &ret);\
				r_ret = (m_ret)ret;\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), &ret);\
				r_ret = (m_ret)ret;\
			}\
			return true;\
		}\
		(void)r_ret;\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL;\
		method_info.return_val = GetTypeInfo<m_ret>::get_class_info();\
		method_info.return_val_metadata = GetTypeInfo<m_ret>::METADATA;\
		method_info.arguments.push_back(GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type1>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type2>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type2>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type3>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type3>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type4>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type4>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type5>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type5>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type6>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type6>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type7>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type7>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type8>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type8>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type9>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type9>::METADATA);\
		return method_info;\
	}

#define GDVIRTUAL9C(m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8, m_type9)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8, m_type9 arg9) const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant vargs[9] = { Variant(arg1), Variant(arg2), Variant(arg3), Variant(arg4), Variant(arg5), Variant(arg6), Variant(arg7), Variant(arg8), Variant(arg9) };\
			const Variant *vargptrs[9] = { &vargs[0], &vargs[1], &vargs[2], &vargs[3], &vargs[4], &vargs[5], &vargs[6], &vargs[7], &vargs[8] };\
			_script_instance->callp(_gdvirtual_##m_name##_sn, (const Variant **)vargptrs, 9, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_type1>::EncodeT argval1 = (PtrToArg<m_type1>::EncodeT)arg1;\
			PtrToArg<m_type2>::EncodeT argval2 = (PtrToArg<m_type2>::EncodeT)arg2;\
			PtrToArg<m_type3>::EncodeT argval3 = (PtrToArg<m_type3>::EncodeT)arg3;\
			PtrToArg<m_type4>::EncodeT argval4 = (PtrToArg<m_type4>::EncodeT)arg4;\
			PtrToArg<m_type5>::EncodeT argval5 = (PtrToArg<m_type5>::EncodeT)arg5;\
			PtrToArg<m_type6>::EncodeT argval6 = (PtrToArg<m_type6>::EncodeT)arg6;\
			PtrToArg<m_type7>::EncodeT argval7 = (PtrToArg<m_type7>::EncodeT)arg7;\
			PtrToArg<m_type8>::EncodeT argval8 = (PtrToArg<m_type8>::EncodeT)arg8;\
			PtrToArg<m_type9>::EncodeT argval9 = (PtrToArg<m_type9>::EncodeT)arg9;\
			GDExtensionConstTypePtr argptrs[9] = { &argval1, &argval2, &argval3, &argval4, &argval5, &argval6, &argval7, &argval8, &argval9 };\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), nullptr);\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), nullptr);\
			}\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL | METHOD_FLAG_CONST;\
		method_info.arguments.push_back(GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type1>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type2>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type2>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type3>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type3>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type4>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type4>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type5>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type5>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type6>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type6>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type7>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type7>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type8>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type8>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type9>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type9>::METADATA);\
		return method_info;\
	}

#define GDVIRTUAL9RC(m_ret, m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8, m_type9)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8, m_type9 arg9, m_ret &r_ret) const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant vargs[9] = { Variant(arg1), Variant(arg2), Variant(arg3), Variant(arg4), Variant(arg5), Variant(arg6), Variant(arg7), Variant(arg8), Variant(arg9) };\
			const Variant *vargptrs[9] = { &vargs[0], &vargs[1], &vargs[2], &vargs[3], &vargs[4], &vargs[5], &vargs[6], &vargs[7], &vargs[8] };\
			Variant ret = _script_instance->callp(_gdvirtual_##m_name##_sn, (const Variant **)vargptrs, 9, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				r_ret = VariantCaster<m_ret>::cast(ret);\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_type1>::EncodeT argval1 = (PtrToArg<m_type1>::EncodeT)arg1;\
			PtrToArg<m_type2>::EncodeT argval2 = (PtrToArg<m_type2>::EncodeT)arg2;\
			PtrToArg<m_type3>::EncodeT argval3 = (PtrToArg<m_type3>::EncodeT)arg3;\
			PtrToArg<m_type4>::EncodeT argval4 = (PtrToArg<m_type4>::EncodeT)arg4;\
			PtrToArg<m_type5>::EncodeT argval5 = (PtrToArg<m_type5>::EncodeT)arg5;\
			PtrToArg<m_type6>::EncodeT argval6 = (PtrToArg<m_type6>::EncodeT)arg6;\
			PtrToArg<m_type7>::EncodeT argval7 = (PtrToArg<m_type7>::EncodeT)arg7;\
			PtrToArg<m_type8>::EncodeT argval8 = (PtrToArg<m_type8>::EncodeT)arg8;\
			PtrToArg<m_type9>::EncodeT argval9 = (PtrToArg<m_type9>::EncodeT)arg9;\
			GDExtensionConstTypePtr argptrs[9] = { &argval1, &argval2, &argval3, &argval4, &argval5, &argval6, &argval7, &argval8, &argval9 };\
			PtrToArg<m_ret>::EncodeT ret;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), &ret);\
				r_ret = (m_ret)ret;\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), &ret);\
				r_ret = (m_ret)ret;\
			}\
			return true;\
		}\
		(void)r_ret;\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL | METHOD_FLAG_CONST;\
		method_info.return_val = GetTypeInfo<m_ret>::get_class_info();\
		method_info.return_val_metadata = GetTypeInfo<m_ret>::METADATA;\
		method_info.arguments.push_back(GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type1>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type2>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type2>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type3>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type3>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type4>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type4>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type5>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type5>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type6>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type6>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type7>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type7>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type8>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type8>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type9>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type9>::METADATA);\
		return method_info;\
	}

#define GDVIRTUAL9_REQUIRED(m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8, m_type9)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8, m_type9 arg9) {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant vargs[9] = { Variant(arg1), Variant(arg2), Variant(arg3), Variant(arg4), Variant(arg5), Variant(arg6), Variant(arg7), Variant(arg8), Variant(arg9) };\
			const Variant *vargptrs[9] = { &vargs[0], &vargs[1], &vargs[2], &vargs[3], &vargs[4], &vargs[5], &vargs[6], &vargs[7], &vargs[8] };\
			_script_instance->callp(_gdvirtual_##m_name##_sn, (const Variant **)vargptrs, 9, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_type1>::EncodeT argval1 = (PtrToArg<m_type1>::EncodeT)arg1;\
			PtrToArg<m_type2>::EncodeT argval2 = (PtrToArg<m_type2>::EncodeT)arg2;\
			PtrToArg<m_type3>::EncodeT argval3 = (PtrToArg<m_type3>::EncodeT)arg3;\
			PtrToArg<m_type4>::EncodeT argval4 = (PtrToArg<m_type4>::EncodeT)arg4;\
			PtrToArg<m_type5>::EncodeT argval5 = (PtrToArg<m_type5>::EncodeT)arg5;\
			PtrToArg<m_type6>::EncodeT argval6 = (PtrToArg<m_type6>::EncodeT)arg6;\
			PtrToArg<m_type7>::EncodeT argval7 = (PtrToArg<m_type7>::EncodeT)arg7;\
			PtrToArg<m_type8>::EncodeT argval8 = (PtrToArg<m_type8>::EncodeT)arg8;\
			PtrToArg<m_type9>::EncodeT argval9 = (PtrToArg<m_type9>::EncodeT)arg9;\
			GDExtensionConstTypePtr argptrs[9] = { &argval1, &argval2, &argval3, &argval4, &argval5, &argval6, &argval7, &argval8, &argval9 };\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), nullptr);\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), nullptr);\
			}\
			return true;\
		}\
		ERR_PRINT_ONCE("Required virtual method " + get_class() + "::" + #m_name + " must be overridden before calling.");\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL | METHOD_FLAG_VIRTUAL_REQUIRED;\
		method_info.arguments.push_back(GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type1>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type2>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type2>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type3>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type3>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type4>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type4>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type5>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type5>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type6>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type6>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type7>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type7>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type8>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type8>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type9>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type9>::METADATA);\
		return method_info;\
	}

#define GDVIRTUAL9R_REQUIRED(m_ret, m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8, m_type9)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8, m_type9 arg9, m_ret &r_ret) {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant vargs[9] = { Variant(arg1), Variant(arg2), Variant(arg3), Variant(arg4), Variant(arg5), Variant(arg6), Variant(arg7), Variant(arg8), Variant(arg9) };\
			const Variant *vargptrs[9] = { &vargs[0], &vargs[1], &vargs[2], &vargs[3], &vargs[4], &vargs[5], &vargs[6], &vargs[7], &vargs[8] };\
			Variant ret = _script_instance->callp(_gdvirtual_##m_name##_sn, (const Variant **)vargptrs, 9, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				r_ret = VariantCaster<m_ret>::cast(ret);\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_type1>::EncodeT argval1 = (PtrToArg<m_type1>::EncodeT)arg1;\
			PtrToArg<m_type2>::EncodeT argval2 = (PtrToArg<m_type2>::EncodeT)arg2;\
			PtrToArg<m_type3>::EncodeT argval3 = (PtrToArg<m_type3>::EncodeT)arg3;\
			PtrToArg<m_type4>::EncodeT argval4 = (PtrToArg<m_type4>::EncodeT)arg4;\
			PtrToArg<m_type5>::EncodeT argval5 = (PtrToArg<m_type5>::EncodeT)arg5;\
			PtrToArg<m_type6>::EncodeT argval6 = (PtrToArg<m_type6>::EncodeT)arg6;\
			PtrToArg<m_type7>::EncodeT argval7 = (PtrToArg<m_type7>::EncodeT)arg7;\
			PtrToArg<m_type8>::EncodeT argval8 = (PtrToArg<m_type8>::EncodeT)arg8;\
			PtrToArg<m_type9>::EncodeT argval9 = (PtrToArg<m_type9>::EncodeT)arg9;\
			GDExtensionConstTypePtr argptrs[9] = { &argval1, &argval2, &argval3, &argval4, &argval5, &argval6, &argval7, &argval8, &argval9 };\
			PtrToArg<m_ret>::EncodeT ret;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), &ret);\
				r_ret = (m_ret)ret;\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), &ret);\
				r_ret = (m_ret)ret;\
			}\
			return true;\
		}\
		ERR_PRINT_ONCE("Required virtual method " + get_class() + "::" + #m_name + " must be overridden before calling.");\
		(void)r_ret;\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL | METHOD_FLAG_VIRTUAL_REQUIRED;\
		method_info.return_val = GetTypeInfo<m_ret>::get_class_info();\
		method_info.return_val_metadata = GetTypeInfo<m_ret>::METADATA;\
		method_info.arguments.push_back(GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type1>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type2>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type2>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type3>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type3>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type4>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type4>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type5>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type5>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type6>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type6>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type7>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type7>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type8>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type8>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type9>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type9>::METADATA);\
		return method_info;\
	}

#define GDVIRTUAL9C_REQUIRED(m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8, m_type9)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8, m_type9 arg9) const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant vargs[9] = { Variant(arg1), Variant(arg2), Variant(arg3), Variant(arg4), Variant(arg5), Variant(arg6), Variant(arg7), Variant(arg8), Variant(arg9) };\
			const Variant *vargptrs[9] = { &vargs[0], &vargs[1], &vargs[2], &vargs[3], &vargs[4], &vargs[5], &vargs[6], &vargs[7], &vargs[8] };\
			_script_instance->callp(_gdvirtual_##m_name##_sn, (const Variant **)vargptrs, 9, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_type1>::EncodeT argval1 = (PtrToArg<m_type1>::EncodeT)arg1;\
			PtrToArg<m_type2>::EncodeT argval2 = (PtrToArg<m_type2>::EncodeT)arg2;\
			PtrToArg<m_type3>::EncodeT argval3 = (PtrToArg<m_type3>::EncodeT)arg3;\
			PtrToArg<m_type4>::EncodeT argval4 = (PtrToArg<m_type4>::EncodeT)arg4;\
			PtrToArg<m_type5>::EncodeT argval5 = (PtrToArg<m_type5>::EncodeT)arg5;\
			PtrToArg<m_type6>::EncodeT argval6 = (PtrToArg<m_type6>::EncodeT)arg6;\
			PtrToArg<m_type7>::EncodeT argval7 = (PtrToArg<m_type7>::EncodeT)arg7;\
			PtrToArg<m_type8>::EncodeT argval8 = (PtrToArg<m_type8>::EncodeT)arg8;\
			PtrToArg<m_type9>::EncodeT argval9 = (PtrToArg<m_type9>::EncodeT)arg9;\
			GDExtensionConstTypePtr argptrs[9] = { &argval1, &argval2, &argval3, &argval4, &argval5, &argval6, &argval7, &argval8, &argval9 };\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), nullptr);\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), nullptr);\
			}\
			return true;\
		}\
		ERR_PRINT_ONCE("Required virtual method " + get_class() + "::" + #m_name + " must be overridden before calling.");\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL | METHOD_FLAG_CONST | METHOD_FLAG_VIRTUAL_REQUIRED;\
		method_info.arguments.push_back(GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type1>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type2>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type2>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type3>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type3>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type4>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type4>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type5>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type5>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type6>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type6>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type7>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type7>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type8>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type8>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type9>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type9>::METADATA);\
		return method_info;\
	}

#define GDVIRTUAL9RC_REQUIRED(m_ret, m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8, m_type9)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8, m_type9 arg9, m_ret &r_ret) const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant vargs[9] = { Variant(arg1), Variant(arg2), Variant(arg3), Variant(arg4), Variant(arg5), Variant(arg6), Variant(arg7), Variant(arg8), Variant(arg9) };\
			const Variant *vargptrs[9] = { &vargs[0], &vargs[1], &vargs[2], &vargs[3], &vargs[4], &vargs[5], &vargs[6], &vargs[7], &vargs[8] };\
			Variant ret = _script_instance->callp(_gdvirtual_##m_name##_sn, (const Variant **)vargptrs, 9, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				r_ret = VariantCaster<m_ret>::cast(ret);\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_type1>::EncodeT argval1 = (PtrToArg<m_type1>::EncodeT)arg1;\
			PtrToArg<m_type2>::EncodeT argval2 = (PtrToArg<m_type2>::EncodeT)arg2;\
			PtrToArg<m_type3>::EncodeT argval3 = (PtrToArg<m_type3>::EncodeT)arg3;\
			PtrToArg<m_type4>::EncodeT argval4 = (PtrToArg<m_type4>::EncodeT)arg4;\
			PtrToArg<m_type5>::EncodeT argval5 = (PtrToArg<m_type5>::EncodeT)arg5;\
			PtrToArg<m_type6>::EncodeT argval6 = (PtrToArg<m_type6>::EncodeT)arg6;\
			PtrToArg<m_type7>::EncodeT argval7 = (PtrToArg<m_type7>::EncodeT)arg7;\
			PtrToArg<m_type8>::EncodeT argval8 = (PtrToArg<m_type8>::EncodeT)arg8;\
			PtrToArg<m_type9>::EncodeT argval9 = (PtrToArg<m_type9>::EncodeT)arg9;\
			GDExtensionConstTypePtr argptrs[9] = { &argval1, &argval2, &argval3, &argval4, &argval5, &argval6, &argval7, &argval8, &argval9 };\
			PtrToArg<m_ret>::EncodeT ret;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), &ret);\
				r_ret = (m_ret)ret;\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), &ret);\
				r_ret = (m_ret)ret;\
			}\
			return true;\
		}\
		ERR_PRINT_ONCE("Required virtual method " + get_class() + "::" + #m_name + " must be overridden before calling.");\
		(void)r_ret;\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL | METHOD_FLAG_CONST | METHOD_FLAG_VIRTUAL_REQUIRED;\
		method_info.return_val = GetTypeInfo<m_ret>::get_class_info();\
		method_info.return_val_metadata = GetTypeInfo<m_ret>::METADATA;\
		method_info.arguments.push_back(GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type1>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type2>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type2>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type3>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type3>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type4>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type4>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type5>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type5>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type6>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type6>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type7>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type7>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type8>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type8>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type9>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type9>::METADATA);\
		return method_info;\
	}

/* 10 Arguments */

#define GDVIRTUAL10(m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8, m_type9, m_type10)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8, m_type9 arg9, m_type10 arg10) {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant vargs[10] = { Variant(arg1), Variant(arg2), Variant(arg3), Variant(arg4), Variant(arg5), Variant(arg6), Variant(arg7), Variant(arg8), Variant(arg9), Variant(arg10) };\
			const Variant *vargptrs[10] = { &vargs[0], &vargs[1], &vargs[2], &vargs[3], &vargs[4], &vargs[5], &vargs[6], &vargs[7], &vargs[8], &vargs[9] };\
			_script_instance->callp(_gdvirtual_##m_name##_sn, (const Variant **)vargptrs, 10, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_type1>::EncodeT argval1 = (PtrToArg<m_type1>::EncodeT)arg1;\
			PtrToArg<m_type2>::EncodeT argval2 = (PtrToArg<m_type2>::EncodeT)arg2;\
			PtrToArg<m_type3>::EncodeT argval3 = (PtrToArg<m_type3>::EncodeT)arg3;\
			PtrToArg<m_type4>::EncodeT argval4 = (PtrToArg<m_type4>::EncodeT)arg4;\
			PtrToArg<m_type5>::EncodeT argval5 = (PtrToArg<m_type5>::EncodeT)arg5;\
			PtrToArg<m_type6>::EncodeT argval6 = (PtrToArg<m_type6>::EncodeT)arg6;\
			PtrToArg<m_type7>::EncodeT argval7 = (PtrToArg<m_type7>::EncodeT)arg7;\
			PtrToArg<m_type8>::EncodeT argval8 = (PtrToArg<m_type8>::EncodeT)arg8;\
			PtrToArg<m_type9>::EncodeT argval9 = (PtrToArg<m_type9>::EncodeT)arg9;\
			PtrToArg<m_type10>::EncodeT argval10 = (PtrToArg<m_type10>::EncodeT)arg10;\
			GDExtensionConstTypePtr argptrs[10] = { &argval1, &argval2, &argval3, &argval4, &argval5, &argval6, &argval7, &argval8, &argval9, &argval10 };\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), nullptr);\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), nullptr);\
			}\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL;\
		method_info.arguments.push_back(GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type1>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type2>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type2>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type3>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type3>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type4>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type4>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type5>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type5>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type6>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type6>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type7>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type7>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type8>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type8>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type9>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type9>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type10>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type10>::METADATA);\
		return method_info;\
	}

#define GDVIRTUAL10R(m_ret, m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8, m_type9, m_type10)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8, m_type9 arg9, m_type10 arg10, m_ret &r_ret) {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant vargs[10] = { Variant(arg1), Variant(arg2), Variant(arg3), Variant(arg4), Variant(arg5), Variant(arg6), Variant(arg7), Variant(arg8), Variant(arg9), Variant(arg10) };\
			const Variant *vargptrs[10] = { &vargs[0], &vargs[1], &vargs[2], &vargs[3], &vargs[4], &vargs[5], &vargs[6], &vargs[7], &vargs[8], &vargs[9] };\
			Variant ret = _script_instance->callp(_gdvirtual_##m_name##_sn, (const Variant **)vargptrs, 10, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				r_ret = VariantCaster<m_ret>::cast(ret);\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_type1>::EncodeT argval1 = (PtrToArg<m_type1>::EncodeT)arg1;\
			PtrToArg<m_type2>::EncodeT argval2 = (PtrToArg<m_type2>::EncodeT)arg2;\
			PtrToArg<m_type3>::EncodeT argval3 = (PtrToArg<m_type3>::EncodeT)arg3;\
			PtrToArg<m_type4>::EncodeT argval4 = (PtrToArg<m_type4>::EncodeT)arg4;\
			PtrToArg<m_type5>::EncodeT argval5 = (PtrToArg<m_type5>::EncodeT)arg5;\
			PtrToArg<m_type6>::EncodeT argval6 = (PtrToArg<m_type6>::EncodeT)arg6;\
			PtrToArg<m_type7>::EncodeT argval7 = (PtrToArg<m_type7>::EncodeT)arg7;\
			PtrToArg<m_type8>::EncodeT argval8 = (PtrToArg<m_type8>::EncodeT)arg8;\
			PtrToArg<m_type9>::EncodeT argval9 = (PtrToArg<m_type9>::EncodeT)arg9;\
			PtrToArg<m_type10>::EncodeT argval10 = (PtrToArg<m_type10>::EncodeT)arg10;\
			GDExtensionConstTypePtr argptrs[10] = { &argval1, &argval2, &argval3, &argval4, &argval5, &argval6, &argval7, &argval8, &argval9, &argval10 };\
			PtrToArg<m_ret>::EncodeT ret;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), &ret);\
				r_ret = (m_ret)ret;\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), &ret);\
				r_ret = (m_ret)ret;\
			}\
			return true;\
		}\
		(void)r_ret;\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL;\
		method_info.return_val = GetTypeInfo<m_ret>::get_class_info();\
		method_info.return_val_metadata = GetTypeInfo<m_ret>::METADATA;\
		method_info.arguments.push_back(GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type1>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type2>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type2>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type3>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type3>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type4>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type4>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type5>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type5>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type6>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type6>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type7>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type7>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type8>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type8>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type9>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type9>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type10>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type10>::METADATA);\
		return method_info;\
	}

#define GDVIRTUAL10C(m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8, m_type9, m_type10)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8, m_type9 arg9, m_type10 arg10) const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant vargs[10] = { Variant(arg1), Variant(arg2), Variant(arg3), Variant(arg4), Variant(arg5), Variant(arg6), Variant(arg7), Variant(arg8), Variant(arg9), Variant(arg10) };\
			const Variant *vargptrs[10] = { &vargs[0], &vargs[1], &vargs[2], &vargs[3], &vargs[4], &vargs[5], &vargs[6], &vargs[7], &vargs[8], &vargs[9] };\
			_script_instance->callp(_gdvirtual_##m_name##_sn, (const Variant **)vargptrs, 10, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_type1>::EncodeT argval1 = (PtrToArg<m_type1>::EncodeT)arg1;\
			PtrToArg<m_type2>::EncodeT argval2 = (PtrToArg<m_type2>::EncodeT)arg2;\
			PtrToArg<m_type3>::EncodeT argval3 = (PtrToArg<m_type3>::EncodeT)arg3;\
			PtrToArg<m_type4>::EncodeT argval4 = (PtrToArg<m_type4>::EncodeT)arg4;\
			PtrToArg<m_type5>::EncodeT argval5 = (PtrToArg<m_type5>::EncodeT)arg5;\
			PtrToArg<m_type6>::EncodeT argval6 = (PtrToArg<m_type6>::EncodeT)arg6;\
			PtrToArg<m_type7>::EncodeT argval7 = (PtrToArg<m_type7>::EncodeT)arg7;\
			PtrToArg<m_type8>::EncodeT argval8 = (PtrToArg<m_type8>::EncodeT)arg8;\
			PtrToArg<m_type9>::EncodeT argval9 = (PtrToArg<m_type9>::EncodeT)arg9;\
			PtrToArg<m_type10>::EncodeT argval10 = (PtrToArg<m_type10>::EncodeT)arg10;\
			GDExtensionConstTypePtr argptrs[10] = { &argval1, &argval2, &argval3, &argval4, &argval5, &argval6, &argval7, &argval8, &argval9, &argval10 };\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), nullptr);\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), nullptr);\
			}\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL | METHOD_FLAG_CONST;\
		method_info.arguments.push_back(GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type1>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type2>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type2>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type3>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type3>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type4>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type4>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type5>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type5>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type6>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type6>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type7>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type7>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type8>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type8>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type9>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type9>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type10>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type10>::METADATA);\
		return method_info;\
	}

#define GDVIRTUAL10RC(m_ret, m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8, m_type9, m_type10)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8, m_type9 arg9, m_type10 arg10, m_ret &r_ret) const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant vargs[10] = { Variant(arg1), Variant(arg2), Variant(arg3), Variant(arg4), Variant(arg5), Variant(arg6), Variant(arg7), Variant(arg8), Variant(arg9), Variant(arg10) };\
			const Variant *vargptrs[10] = { &vargs[0], &vargs[1], &vargs[2], &vargs[3], &vargs[4], &vargs[5], &vargs[6], &vargs[7], &vargs[8], &vargs[9] };\
			Variant ret = _script_instance->callp(_gdvirtual_##m_name##_sn, (const Variant **)vargptrs, 10, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				r_ret = VariantCaster<m_ret>::cast(ret);\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_type1>::EncodeT argval1 = (PtrToArg<m_type1>::EncodeT)arg1;\
			PtrToArg<m_type2>::EncodeT argval2 = (PtrToArg<m_type2>::EncodeT)arg2;\
			PtrToArg<m_type3>::EncodeT argval3 = (PtrToArg<m_type3>::EncodeT)arg3;\
			PtrToArg<m_type4>::EncodeT argval4 = (PtrToArg<m_type4>::EncodeT)arg4;\
			PtrToArg<m_type5>::EncodeT argval5 = (PtrToArg<m_type5>::EncodeT)arg5;\
			PtrToArg<m_type6>::EncodeT argval6 = (PtrToArg<m_type6>::EncodeT)arg6;\
			PtrToArg<m_type7>::EncodeT argval7 = (PtrToArg<m_type7>::EncodeT)arg7;\
			PtrToArg<m_type8>::EncodeT argval8 = (PtrToArg<m_type8>::EncodeT)arg8;\
			PtrToArg<m_type9>::EncodeT argval9 = (PtrToArg<m_type9>::EncodeT)arg9;\
			PtrToArg<m_type10>::EncodeT argval10 = (PtrToArg<m_type10>::EncodeT)arg10;\
			GDExtensionConstTypePtr argptrs[10] = { &argval1, &argval2, &argval3, &argval4, &argval5, &argval6, &argval7, &argval8, &argval9, &argval10 };\
			PtrToArg<m_ret>::EncodeT ret;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), &ret);\
				r_ret = (m_ret)ret;\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), &ret);\
				r_ret = (m_ret)ret;\
			}\
			return true;\
		}\
		(void)r_ret;\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL | METHOD_FLAG_CONST;\
		method_info.return_val = GetTypeInfo<m_ret>::get_class_info();\
		method_info.return_val_metadata = GetTypeInfo<m_ret>::METADATA;\
		method_info.arguments.push_back(GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type1>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type2>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type2>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type3>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type3>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type4>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type4>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type5>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type5>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type6>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type6>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type7>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type7>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type8>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type8>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type9>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type9>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type10>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type10>::METADATA);\
		return method_info;\
	}

#define GDVIRTUAL10_REQUIRED(m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8, m_type9, m_type10)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8, m_type9 arg9, m_type10 arg10) {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant vargs[10] = { Variant(arg1), Variant(arg2), Variant(arg3), Variant(arg4), Variant(arg5), Variant(arg6), Variant(arg7), Variant(arg8), Variant(arg9), Variant(arg10) };\
			const Variant *vargptrs[10] = { &vargs[0], &vargs[1], &vargs[2], &vargs[3], &vargs[4], &vargs[5], &vargs[6], &vargs[7], &vargs[8], &vargs[9] };\
			_script_instance->callp(_gdvirtual_##m_name##_sn, (const Variant **)vargptrs, 10, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_type1>::EncodeT argval1 = (PtrToArg<m_type1>::EncodeT)arg1;\
			PtrToArg<m_type2>::EncodeT argval2 = (PtrToArg<m_type2>::EncodeT)arg2;\
			PtrToArg<m_type3>::EncodeT argval3 = (PtrToArg<m_type3>::EncodeT)arg3;\
			PtrToArg<m_type4>::EncodeT argval4 = (PtrToArg<m_type4>::EncodeT)arg4;\
			PtrToArg<m_type5>::EncodeT argval5 = (PtrToArg<m_type5>::EncodeT)arg5;\
			PtrToArg<m_type6>::EncodeT argval6 = (PtrToArg<m_type6>::EncodeT)arg6;\
			PtrToArg<m_type7>::EncodeT argval7 = (PtrToArg<m_type7>::EncodeT)arg7;\
			PtrToArg<m_type8>::EncodeT argval8 = (PtrToArg<m_type8>::EncodeT)arg8;\
			PtrToArg<m_type9>::EncodeT argval9 = (PtrToArg<m_type9>::EncodeT)arg9;\
			PtrToArg<m_type10>::EncodeT argval10 = (PtrToArg<m_type10>::EncodeT)arg10;\
			GDExtensionConstTypePtr argptrs[10] = { &argval1, &argval2, &argval3, &argval4, &argval5, &argval6, &argval7, &argval8, &argval9, &argval10 };\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), nullptr);\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), nullptr);\
			}\
			return true;\
		}\
		ERR_PRINT_ONCE("Required virtual method " + get_class() + "::" + #m_name + " must be overridden before calling.");\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL | METHOD_FLAG_VIRTUAL_REQUIRED;\
		method_info.arguments.push_back(GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type1>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type2>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type2>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type3>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type3>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type4>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type4>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type5>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type5>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type6>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type6>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type7>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type7>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type8>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type8>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type9>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type9>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type10>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type10>::METADATA);\
		return method_info;\
	}

#define GDVIRTUAL10R_REQUIRED(m_ret, m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8, m_type9, m_type10)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8, m_type9 arg9, m_type10 arg10, m_ret &r_ret) {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant vargs[10] = { Variant(arg1), Variant(arg2), Variant(arg3), Variant(arg4), Variant(arg5), Variant(arg6), Variant(arg7), Variant(arg8), Variant(arg9), Variant(arg10) };\
			const Variant *vargptrs[10] = { &vargs[0], &vargs[1], &vargs[2], &vargs[3], &vargs[4], &vargs[5], &vargs[6], &vargs[7], &vargs[8], &vargs[9] };\
			Variant ret = _script_instance->callp(_gdvirtual_##m_name##_sn, (const Variant **)vargptrs, 10, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				r_ret = VariantCaster<m_ret>::cast(ret);\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_type1>::EncodeT argval1 = (PtrToArg<m_type1>::EncodeT)arg1;\
			PtrToArg<m_type2>::EncodeT argval2 = (PtrToArg<m_type2>::EncodeT)arg2;\
			PtrToArg<m_type3>::EncodeT argval3 = (PtrToArg<m_type3>::EncodeT)arg3;\
			PtrToArg<m_type4>::EncodeT argval4 = (PtrToArg<m_type4>::EncodeT)arg4;\
			PtrToArg<m_type5>::EncodeT argval5 = (PtrToArg<m_type5>::EncodeT)arg5;\
			PtrToArg<m_type6>::EncodeT argval6 = (PtrToArg<m_type6>::EncodeT)arg6;\
			PtrToArg<m_type7>::EncodeT argval7 = (PtrToArg<m_type7>::EncodeT)arg7;\
			PtrToArg<m_type8>::EncodeT argval8 = (PtrToArg<m_type8>::EncodeT)arg8;\
			PtrToArg<m_type9>::EncodeT argval9 = (PtrToArg<m_type9>::EncodeT)arg9;\
			PtrToArg<m_type10>::EncodeT argval10 = (PtrToArg<m_type10>::EncodeT)arg10;\
			GDExtensionConstTypePtr argptrs[10] = { &argval1, &argval2, &argval3, &argval4, &argval5, &argval6, &argval7, &argval8, &argval9, &argval10 };\
			PtrToArg<m_ret>::EncodeT ret;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), &ret);\
				r_ret = (m_ret)ret;\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), &ret);\
				r_ret = (m_ret)ret;\
			}\
			return true;\
		}\
		ERR_PRINT_ONCE("Required virtual method " + get_class() + "::" + #m_name + " must be overridden before calling.");\
		(void)r_ret;\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL | METHOD_FLAG_VIRTUAL_REQUIRED;\
		method_info.return_val = GetTypeInfo<m_ret>::get_class_info();\
		method_info.return_val_metadata = GetTypeInfo<m_ret>::METADATA;\
		method_info.arguments.push_back(GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type1>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type2>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type2>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type3>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type3>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type4>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type4>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type5>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type5>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type6>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type6>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type7>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type7>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type8>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type8>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type9>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type9>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type10>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type10>::METADATA);\
		return method_info;\
	}

#define GDVIRTUAL10C_REQUIRED(m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8, m_type9, m_type10)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8, m_type9 arg9, m_type10 arg10) const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant vargs[10] = { Variant(arg1), Variant(arg2), Variant(arg3), Variant(arg4), Variant(arg5), Variant(arg6), Variant(arg7), Variant(arg8), Variant(arg9), Variant(arg10) };\
			const Variant *vargptrs[10] = { &vargs[0], &vargs[1], &vargs[2], &vargs[3], &vargs[4], &vargs[5], &vargs[6], &vargs[7], &vargs[8], &vargs[9] };\
			_script_instance->callp(_gdvirtual_##m_name##_sn, (const Variant **)vargptrs, 10, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_type1>::EncodeT argval1 = (PtrToArg<m_type1>::EncodeT)arg1;\
			PtrToArg<m_type2>::EncodeT argval2 = (PtrToArg<m_type2>::EncodeT)arg2;\
			PtrToArg<m_type3>::EncodeT argval3 = (PtrToArg<m_type3>::EncodeT)arg3;\
			PtrToArg<m_type4>::EncodeT argval4 = (PtrToArg<m_type4>::EncodeT)arg4;\
			PtrToArg<m_type5>::EncodeT argval5 = (PtrToArg<m_type5>::EncodeT)arg5;\
			PtrToArg<m_type6>::EncodeT argval6 = (PtrToArg<m_type6>::EncodeT)arg6;\
			PtrToArg<m_type7>::EncodeT argval7 = (PtrToArg<m_type7>::EncodeT)arg7;\
			PtrToArg<m_type8>::EncodeT argval8 = (PtrToArg<m_type8>::EncodeT)arg8;\
			PtrToArg<m_type9>::EncodeT argval9 = (PtrToArg<m_type9>::EncodeT)arg9;\
			PtrToArg<m_type10>::EncodeT argval10 = (PtrToArg<m_type10>::EncodeT)arg10;\
			GDExtensionConstTypePtr argptrs[10] = { &argval1, &argval2, &argval3, &argval4, &argval5, &argval6, &argval7, &argval8, &argval9, &argval10 };\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), nullptr);\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), nullptr);\
			}\
			return true;\
		}\
		ERR_PRINT_ONCE("Required virtual method " + get_class() + "::" + #m_name + " must be overridden before calling.");\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL | METHOD_FLAG_CONST | METHOD_FLAG_VIRTUAL_REQUIRED;\
		method_info.arguments.push_back(GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type1>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type2>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type2>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type3>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type3>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type4>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type4>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type5>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type5>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type6>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type6>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type7>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type7>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type8>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type8>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type9>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type9>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type10>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type10>::METADATA);\
		return method_info;\
	}

#define GDVIRTUAL10RC_REQUIRED(m_ret, m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8, m_type9, m_type10)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8, m_type9 arg9, m_type10 arg10, m_ret &r_ret) const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant vargs[10] = { Variant(arg1), Variant(arg2), Variant(arg3), Variant(arg4), Variant(arg5), Variant(arg6), Variant(arg7), Variant(arg8), Variant(arg9), Variant(arg10) };\
			const Variant *vargptrs[10] = { &vargs[0], &vargs[1], &vargs[2], &vargs[3], &vargs[4], &vargs[5], &vargs[6], &vargs[7], &vargs[8], &vargs[9] };\
			Variant ret = _script_instance->callp(_gdvirtual_##m_name##_sn, (const Variant **)vargptrs, 10, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				r_ret = VariantCaster<m_ret>::cast(ret);\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_type1>::EncodeT argval1 = (PtrToArg<m_type1>::EncodeT)arg1;\
			PtrToArg<m_type2>::EncodeT argval2 = (PtrToArg<m_type2>::EncodeT)arg2;\
			PtrToArg<m_type3>::EncodeT argval3 = (PtrToArg<m_type3>::EncodeT)arg3;\
			PtrToArg<m_type4>::EncodeT argval4 = (PtrToArg<m_type4>::EncodeT)arg4;\
			PtrToArg<m_type5>::EncodeT argval5 = (PtrToArg<m_type5>::EncodeT)arg5;\
			PtrToArg<m_type6>::EncodeT argval6 = (PtrToArg<m_type6>::EncodeT)arg6;\
			PtrToArg<m_type7>::EncodeT argval7 = (PtrToArg<m_type7>::EncodeT)arg7;\
			PtrToArg<m_type8>::EncodeT argval8 = (PtrToArg<m_type8>::EncodeT)arg8;\
			PtrToArg<m_type9>::EncodeT argval9 = (PtrToArg<m_type9>::EncodeT)arg9;\
			PtrToArg<m_type10>::EncodeT argval10 = (PtrToArg<m_type10>::EncodeT)arg10;\
			GDExtensionConstTypePtr argptrs[10] = { &argval1, &argval2, &argval3, &argval4, &argval5, &argval6, &argval7, &argval8, &argval9, &argval10 };\
			PtrToArg<m_ret>::EncodeT ret;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), &ret);\
				r_ret = (m_ret)ret;\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), &ret);\
				r_ret = (m_ret)ret;\
			}\
			return true;\
		}\
		ERR_PRINT_ONCE("Required virtual method " + get_class() + "::" + #m_name + " must be overridden before calling.");\
		(void)r_ret;\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL | METHOD_FLAG_CONST | METHOD_FLAG_VIRTUAL_REQUIRED;\
		method_info.return_val = GetTypeInfo<m_ret>::get_class_info();\
		method_info.return_val_metadata = GetTypeInfo<m_ret>::METADATA;\
		method_info.arguments.push_back(GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type1>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type2>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type2>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type3>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type3>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type4>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type4>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type5>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type5>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type6>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type6>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type7>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type7>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type8>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type8>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type9>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type9>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type10>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type10>::METADATA);\
		return method_info;\
	}

/* 11 Arguments */

#define GDVIRTUAL11(m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8, m_type9, m_type10, m_type11)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8, m_type9 arg9, m_type10 arg10, m_type11 arg11) {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant vargs[11] = { Variant(arg1), Variant(arg2), Variant(arg3), Variant(arg4), Variant(arg5), Variant(arg6), Variant(arg7), Variant(arg8), Variant(arg9), Variant(arg10), Variant(arg11) };\
			const Variant *vargptrs[11] = { &vargs[0], &vargs[1], &vargs[2], &vargs[3], &vargs[4], &vargs[5], &vargs[6], &vargs[7], &vargs[8], &vargs[9], &vargs[10] };\
			_script_instance->callp(_gdvirtual_##m_name##_sn, (const Variant **)vargptrs, 11, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_type1>::EncodeT argval1 = (PtrToArg<m_type1>::EncodeT)arg1;\
			PtrToArg<m_type2>::EncodeT argval2 = (PtrToArg<m_type2>::EncodeT)arg2;\
			PtrToArg<m_type3>::EncodeT argval3 = (PtrToArg<m_type3>::EncodeT)arg3;\
			PtrToArg<m_type4>::EncodeT argval4 = (PtrToArg<m_type4>::EncodeT)arg4;\
			PtrToArg<m_type5>::EncodeT argval5 = (PtrToArg<m_type5>::EncodeT)arg5;\
			PtrToArg<m_type6>::EncodeT argval6 = (PtrToArg<m_type6>::EncodeT)arg6;\
			PtrToArg<m_type7>::EncodeT argval7 = (PtrToArg<m_type7>::EncodeT)arg7;\
			PtrToArg<m_type8>::EncodeT argval8 = (PtrToArg<m_type8>::EncodeT)arg8;\
			PtrToArg<m_type9>::EncodeT argval9 = (PtrToArg<m_type9>::EncodeT)arg9;\
			PtrToArg<m_type10>::EncodeT argval10 = (PtrToArg<m_type10>::EncodeT)arg10;\
			PtrToArg<m_type11>::EncodeT argval11 = (PtrToArg<m_type11>::EncodeT)arg11;\
			GDExtensionConstTypePtr argptrs[11] = { &argval1, &argval2, &argval3, &argval4, &argval5, &argval6, &argval7, &argval8, &argval9, &argval10, &argval11 };\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), nullptr);\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), nullptr);\
			}\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL;\
		method_info.arguments.push_back(GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type1>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type2>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type2>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type3>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type3>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type4>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type4>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type5>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type5>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type6>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type6>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type7>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type7>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type8>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type8>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type9>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type9>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type10>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type10>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type11>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type11>::METADATA);\
		return method_info;\
	}

#define GDVIRTUAL11R(m_ret, m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8, m_type9, m_type10, m_type11)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8, m_type9 arg9, m_type10 arg10, m_type11 arg11, m_ret &r_ret) {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant vargs[11] = { Variant(arg1), Variant(arg2), Variant(arg3), Variant(arg4), Variant(arg5), Variant(arg6), Variant(arg7), Variant(arg8), Variant(arg9), Variant(arg10), Variant(arg11) };\
			const Variant *vargptrs[11] = { &vargs[0], &vargs[1], &vargs[2], &vargs[3], &vargs[4], &vargs[5], &vargs[6], &vargs[7], &vargs[8], &vargs[9], &vargs[10] };\
			Variant ret = _script_instance->callp(_gdvirtual_##m_name##_sn, (const Variant **)vargptrs, 11, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				r_ret = VariantCaster<m_ret>::cast(ret);\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_type1>::EncodeT argval1 = (PtrToArg<m_type1>::EncodeT)arg1;\
			PtrToArg<m_type2>::EncodeT argval2 = (PtrToArg<m_type2>::EncodeT)arg2;\
			PtrToArg<m_type3>::EncodeT argval3 = (PtrToArg<m_type3>::EncodeT)arg3;\
			PtrToArg<m_type4>::EncodeT argval4 = (PtrToArg<m_type4>::EncodeT)arg4;\
			PtrToArg<m_type5>::EncodeT argval5 = (PtrToArg<m_type5>::EncodeT)arg5;\
			PtrToArg<m_type6>::EncodeT argval6 = (PtrToArg<m_type6>::EncodeT)arg6;\
			PtrToArg<m_type7>::EncodeT argval7 = (PtrToArg<m_type7>::EncodeT)arg7;\
			PtrToArg<m_type8>::EncodeT argval8 = (PtrToArg<m_type8>::EncodeT)arg8;\
			PtrToArg<m_type9>::EncodeT argval9 = (PtrToArg<m_type9>::EncodeT)arg9;\
			PtrToArg<m_type10>::EncodeT argval10 = (PtrToArg<m_type10>::EncodeT)arg10;\
			PtrToArg<m_type11>::EncodeT argval11 = (PtrToArg<m_type11>::EncodeT)arg11;\
			GDExtensionConstTypePtr argptrs[11] = { &argval1, &argval2, &argval3, &argval4, &argval5, &argval6, &argval7, &argval8, &argval9, &argval10, &argval11 };\
			PtrToArg<m_ret>::EncodeT ret;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), &ret);\
				r_ret = (m_ret)ret;\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), &ret);\
				r_ret = (m_ret)ret;\
			}\
			return true;\
		}\
		(void)r_ret;\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL;\
		method_info.return_val = GetTypeInfo<m_ret>::get_class_info();\
		method_info.return_val_metadata = GetTypeInfo<m_ret>::METADATA;\
		method_info.arguments.push_back(GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type1>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type2>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type2>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type3>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type3>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type4>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type4>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type5>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type5>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type6>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type6>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type7>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type7>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type8>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type8>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type9>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type9>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type10>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type10>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type11>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type11>::METADATA);\
		return method_info;\
	}

#define GDVIRTUAL11C(m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8, m_type9, m_type10, m_type11)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8, m_type9 arg9, m_type10 arg10, m_type11 arg11) const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant vargs[11] = { Variant(arg1), Variant(arg2), Variant(arg3), Variant(arg4), Variant(arg5), Variant(arg6), Variant(arg7), Variant(arg8), Variant(arg9), Variant(arg10), Variant(arg11) };\
			const Variant *vargptrs[11] = { &vargs[0], &vargs[1], &vargs[2], &vargs[3], &vargs[4], &vargs[5], &vargs[6], &vargs[7], &vargs[8], &vargs[9], &vargs[10] };\
			_script_instance->callp(_gdvirtual_##m_name##_sn, (const Variant **)vargptrs, 11, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_type1>::EncodeT argval1 = (PtrToArg<m_type1>::EncodeT)arg1;\
			PtrToArg<m_type2>::EncodeT argval2 = (PtrToArg<m_type2>::EncodeT)arg2;\
			PtrToArg<m_type3>::EncodeT argval3 = (PtrToArg<m_type3>::EncodeT)arg3;\
			PtrToArg<m_type4>::EncodeT argval4 = (PtrToArg<m_type4>::EncodeT)arg4;\
			PtrToArg<m_type5>::EncodeT argval5 = (PtrToArg<m_type5>::EncodeT)arg5;\
			PtrToArg<m_type6>::EncodeT argval6 = (PtrToArg<m_type6>::EncodeT)arg6;\
			PtrToArg<m_type7>::EncodeT argval7 = (PtrToArg<m_type7>::EncodeT)arg7;\
			PtrToArg<m_type8>::EncodeT argval8 = (PtrToArg<m_type8>::EncodeT)arg8;\
			PtrToArg<m_type9>::EncodeT argval9 = (PtrToArg<m_type9>::EncodeT)arg9;\
			PtrToArg<m_type10>::EncodeT argval10 = (PtrToArg<m_type10>::EncodeT)arg10;\
			PtrToArg<m_type11>::EncodeT argval11 = (PtrToArg<m_type11>::EncodeT)arg11;\
			GDExtensionConstTypePtr argptrs[11] = { &argval1, &argval2, &argval3, &argval4, &argval5, &argval6, &argval7, &argval8, &argval9, &argval10, &argval11 };\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), nullptr);\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), nullptr);\
			}\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL | METHOD_FLAG_CONST;\
		method_info.arguments.push_back(GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type1>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type2>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type2>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type3>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type3>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type4>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type4>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type5>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type5>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type6>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type6>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type7>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type7>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type8>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type8>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type9>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type9>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type10>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type10>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type11>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type11>::METADATA);\
		return method_info;\
	}

#define GDVIRTUAL11RC(m_ret, m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8, m_type9, m_type10, m_type11)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8, m_type9 arg9, m_type10 arg10, m_type11 arg11, m_ret &r_ret) const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant vargs[11] = { Variant(arg1), Variant(arg2), Variant(arg3), Variant(arg4), Variant(arg5), Variant(arg6), Variant(arg7), Variant(arg8), Variant(arg9), Variant(arg10), Variant(arg11) };\
			const Variant *vargptrs[11] = { &vargs[0], &vargs[1], &vargs[2], &vargs[3], &vargs[4], &vargs[5], &vargs[6], &vargs[7], &vargs[8], &vargs[9], &vargs[10] };\
			Variant ret = _script_instance->callp(_gdvirtual_##m_name##_sn, (const Variant **)vargptrs, 11, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				r_ret = VariantCaster<m_ret>::cast(ret);\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_type1>::EncodeT argval1 = (PtrToArg<m_type1>::EncodeT)arg1;\
			PtrToArg<m_type2>::EncodeT argval2 = (PtrToArg<m_type2>::EncodeT)arg2;\
			PtrToArg<m_type3>::EncodeT argval3 = (PtrToArg<m_type3>::EncodeT)arg3;\
			PtrToArg<m_type4>::EncodeT argval4 = (PtrToArg<m_type4>::EncodeT)arg4;\
			PtrToArg<m_type5>::EncodeT argval5 = (PtrToArg<m_type5>::EncodeT)arg5;\
			PtrToArg<m_type6>::EncodeT argval6 = (PtrToArg<m_type6>::EncodeT)arg6;\
			PtrToArg<m_type7>::EncodeT argval7 = (PtrToArg<m_type7>::EncodeT)arg7;\
			PtrToArg<m_type8>::EncodeT argval8 = (PtrToArg<m_type8>::EncodeT)arg8;\
			PtrToArg<m_type9>::EncodeT argval9 = (PtrToArg<m_type9>::EncodeT)arg9;\
			PtrToArg<m_type10>::EncodeT argval10 = (PtrToArg<m_type10>::EncodeT)arg10;\
			PtrToArg<m_type11>::EncodeT argval11 = (PtrToArg<m_type11>::EncodeT)arg11;\
			GDExtensionConstTypePtr argptrs[11] = { &argval1, &argval2, &argval3, &argval4, &argval5, &argval6, &argval7, &argval8, &argval9, &argval10, &argval11 };\
			PtrToArg<m_ret>::EncodeT ret;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), &ret);\
				r_ret = (m_ret)ret;\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), &ret);\
				r_ret = (m_ret)ret;\
			}\
			return true;\
		}\
		(void)r_ret;\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL | METHOD_FLAG_CONST;\
		method_info.return_val = GetTypeInfo<m_ret>::get_class_info();\
		method_info.return_val_metadata = GetTypeInfo<m_ret>::METADATA;\
		method_info.arguments.push_back(GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type1>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type2>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type2>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type3>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type3>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type4>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type4>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type5>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type5>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type6>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type6>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type7>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type7>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type8>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type8>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type9>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type9>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type10>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type10>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type11>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type11>::METADATA);\
		return method_info;\
	}

#define GDVIRTUAL11_REQUIRED(m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8, m_type9, m_type10, m_type11)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8, m_type9 arg9, m_type10 arg10, m_type11 arg11) {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant vargs[11] = { Variant(arg1), Variant(arg2), Variant(arg3), Variant(arg4), Variant(arg5), Variant(arg6), Variant(arg7), Variant(arg8), Variant(arg9), Variant(arg10), Variant(arg11) };\
			const Variant *vargptrs[11] = { &vargs[0], &vargs[1], &vargs[2], &vargs[3], &vargs[4], &vargs[5], &vargs[6], &vargs[7], &vargs[8], &vargs[9], &vargs[10] };\
			_script_instance->callp(_gdvirtual_##m_name##_sn, (const Variant **)vargptrs, 11, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_type1>::EncodeT argval1 = (PtrToArg<m_type1>::EncodeT)arg1;\
			PtrToArg<m_type2>::EncodeT argval2 = (PtrToArg<m_type2>::EncodeT)arg2;\
			PtrToArg<m_type3>::EncodeT argval3 = (PtrToArg<m_type3>::EncodeT)arg3;\
			PtrToArg<m_type4>::EncodeT argval4 = (PtrToArg<m_type4>::EncodeT)arg4;\
			PtrToArg<m_type5>::EncodeT argval5 = (PtrToArg<m_type5>::EncodeT)arg5;\
			PtrToArg<m_type6>::EncodeT argval6 = (PtrToArg<m_type6>::EncodeT)arg6;\
			PtrToArg<m_type7>::EncodeT argval7 = (PtrToArg<m_type7>::EncodeT)arg7;\
			PtrToArg<m_type8>::EncodeT argval8 = (PtrToArg<m_type8>::EncodeT)arg8;\
			PtrToArg<m_type9>::EncodeT argval9 = (PtrToArg<m_type9>::EncodeT)arg9;\
			PtrToArg<m_type10>::EncodeT argval10 = (PtrToArg<m_type10>::EncodeT)arg10;\
			PtrToArg<m_type11>::EncodeT argval11 = (PtrToArg<m_type11>::EncodeT)arg11;\
			GDExtensionConstTypePtr argptrs[11] = { &argval1, &argval2, &argval3, &argval4, &argval5, &argval6, &argval7, &argval8, &argval9, &argval10, &argval11 };\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), nullptr);\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), nullptr);\
			}\
			return true;\
		}\
		ERR_PRINT_ONCE("Required virtual method " + get_class() + "::" + #m_name + " must be overridden before calling.");\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL | METHOD_FLAG_VIRTUAL_REQUIRED;\
		method_info.arguments.push_back(GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type1>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type2>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type2>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type3>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type3>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type4>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type4>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type5>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type5>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type6>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type6>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type7>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type7>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type8>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type8>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type9>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type9>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type10>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type10>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type11>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type11>::METADATA);\
		return method_info;\
	}

#define GDVIRTUAL11R_REQUIRED(m_ret, m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8, m_type9, m_type10, m_type11)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8, m_type9 arg9, m_type10 arg10, m_type11 arg11, m_ret &r_ret) {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant vargs[11] = { Variant(arg1), Variant(arg2), Variant(arg3), Variant(arg4), Variant(arg5), Variant(arg6), Variant(arg7), Variant(arg8), Variant(arg9), Variant(arg10), Variant(arg11) };\
			const Variant *vargptrs[11] = { &vargs[0], &vargs[1], &vargs[2], &vargs[3], &vargs[4], &vargs[5], &vargs[6], &vargs[7], &vargs[8], &vargs[9], &vargs[10] };\
			Variant ret = _script_instance->callp(_gdvirtual_##m_name##_sn, (const Variant **)vargptrs, 11, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				r_ret = VariantCaster<m_ret>::cast(ret);\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_type1>::EncodeT argval1 = (PtrToArg<m_type1>::EncodeT)arg1;\
			PtrToArg<m_type2>::EncodeT argval2 = (PtrToArg<m_type2>::EncodeT)arg2;\
			PtrToArg<m_type3>::EncodeT argval3 = (PtrToArg<m_type3>::EncodeT)arg3;\
			PtrToArg<m_type4>::EncodeT argval4 = (PtrToArg<m_type4>::EncodeT)arg4;\
			PtrToArg<m_type5>::EncodeT argval5 = (PtrToArg<m_type5>::EncodeT)arg5;\
			PtrToArg<m_type6>::EncodeT argval6 = (PtrToArg<m_type6>::EncodeT)arg6;\
			PtrToArg<m_type7>::EncodeT argval7 = (PtrToArg<m_type7>::EncodeT)arg7;\
			PtrToArg<m_type8>::EncodeT argval8 = (PtrToArg<m_type8>::EncodeT)arg8;\
			PtrToArg<m_type9>::EncodeT argval9 = (PtrToArg<m_type9>::EncodeT)arg9;\
			PtrToArg<m_type10>::EncodeT argval10 = (PtrToArg<m_type10>::EncodeT)arg10;\
			PtrToArg<m_type11>::EncodeT argval11 = (PtrToArg<m_type11>::EncodeT)arg11;\
			GDExtensionConstTypePtr argptrs[11] = { &argval1, &argval2, &argval3, &argval4, &argval5, &argval6, &argval7, &argval8, &argval9, &argval10, &argval11 };\
			PtrToArg<m_ret>::EncodeT ret;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), &ret);\
				r_ret = (m_ret)ret;\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), &ret);\
				r_ret = (m_ret)ret;\
			}\
			return true;\
		}\
		ERR_PRINT_ONCE("Required virtual method " + get_class() + "::" + #m_name + " must be overridden before calling.");\
		(void)r_ret;\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL | METHOD_FLAG_VIRTUAL_REQUIRED;\
		method_info.return_val = GetTypeInfo<m_ret>::get_class_info();\
		method_info.return_val_metadata = GetTypeInfo<m_ret>::METADATA;\
		method_info.arguments.push_back(GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type1>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type2>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type2>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type3>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type3>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type4>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type4>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type5>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type5>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type6>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type6>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type7>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type7>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type8>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type8>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type9>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type9>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type10>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type10>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type11>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type11>::METADATA);\
		return method_info;\
	}

#define GDVIRTUAL11C_REQUIRED(m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8, m_type9, m_type10, m_type11)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8, m_type9 arg9, m_type10 arg10, m_type11 arg11) const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant vargs[11] = { Variant(arg1), Variant(arg2), Variant(arg3), Variant(arg4), Variant(arg5), Variant(arg6), Variant(arg7), Variant(arg8), Variant(arg9), Variant(arg10), Variant(arg11) };\
			const Variant *vargptrs[11] = { &vargs[0], &vargs[1], &vargs[2], &vargs[3], &vargs[4], &vargs[5], &vargs[6], &vargs[7], &vargs[8], &vargs[9], &vargs[10] };\
			_script_instance->callp(_gdvirtual_##m_name##_sn, (const Variant **)vargptrs, 11, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_type1>::EncodeT argval1 = (PtrToArg<m_type1>::EncodeT)arg1;\
			PtrToArg<m_type2>::EncodeT argval2 = (PtrToArg<m_type2>::EncodeT)arg2;\
			PtrToArg<m_type3>::EncodeT argval3 = (PtrToArg<m_type3>::EncodeT)arg3;\
			PtrToArg<m_type4>::EncodeT argval4 = (PtrToArg<m_type4>::EncodeT)arg4;\
			PtrToArg<m_type5>::EncodeT argval5 = (PtrToArg<m_type5>::EncodeT)arg5;\
			PtrToArg<m_type6>::EncodeT argval6 = (PtrToArg<m_type6>::EncodeT)arg6;\
			PtrToArg<m_type7>::EncodeT argval7 = (PtrToArg<m_type7>::EncodeT)arg7;\
			PtrToArg<m_type8>::EncodeT argval8 = (PtrToArg<m_type8>::EncodeT)arg8;\
			PtrToArg<m_type9>::EncodeT argval9 = (PtrToArg<m_type9>::EncodeT)arg9;\
			PtrToArg<m_type10>::EncodeT argval10 = (PtrToArg<m_type10>::EncodeT)arg10;\
			PtrToArg<m_type11>::EncodeT argval11 = (PtrToArg<m_type11>::EncodeT)arg11;\
			GDExtensionConstTypePtr argptrs[11] = { &argval1, &argval2, &argval3, &argval4, &argval5, &argval6, &argval7, &argval8, &argval9, &argval10, &argval11 };\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), nullptr);\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), nullptr);\
			}\
			return true;\
		}\
		ERR_PRINT_ONCE("Required virtual method " + get_class() + "::" + #m_name + " must be overridden before calling.");\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL | METHOD_FLAG_CONST | METHOD_FLAG_VIRTUAL_REQUIRED;\
		method_info.arguments.push_back(GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type1>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type2>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type2>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type3>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type3>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type4>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type4>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type5>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type5>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type6>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type6>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type7>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type7>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type8>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type8>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type9>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type9>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type10>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type10>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type11>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type11>::METADATA);\
		return method_info;\
	}

#define GDVIRTUAL11RC_REQUIRED(m_ret, m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8, m_type9, m_type10, m_type11)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8, m_type9 arg9, m_type10 arg10, m_type11 arg11, m_ret &r_ret) const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant vargs[11] = { Variant(arg1), Variant(arg2), Variant(arg3), Variant(arg4), Variant(arg5), Variant(arg6), Variant(arg7), Variant(arg8), Variant(arg9), Variant(arg10), Variant(arg11) };\
			const Variant *vargptrs[11] = { &vargs[0], &vargs[1], &vargs[2], &vargs[3], &vargs[4], &vargs[5], &vargs[6], &vargs[7], &vargs[8], &vargs[9], &vargs[10] };\
			Variant ret = _script_instance->callp(_gdvirtual_##m_name##_sn, (const Variant **)vargptrs, 11, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				r_ret = VariantCaster<m_ret>::cast(ret);\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_type1>::EncodeT argval1 = (PtrToArg<m_type1>::EncodeT)arg1;\
			PtrToArg<m_type2>::EncodeT argval2 = (PtrToArg<m_type2>::EncodeT)arg2;\
			PtrToArg<m_type3>::EncodeT argval3 = (PtrToArg<m_type3>::EncodeT)arg3;\
			PtrToArg<m_type4>::EncodeT argval4 = (PtrToArg<m_type4>::EncodeT)arg4;\
			PtrToArg<m_type5>::EncodeT argval5 = (PtrToArg<m_type5>::EncodeT)arg5;\
			PtrToArg<m_type6>::EncodeT argval6 = (PtrToArg<m_type6>::EncodeT)arg6;\
			PtrToArg<m_type7>::EncodeT argval7 = (PtrToArg<m_type7>::EncodeT)arg7;\
			PtrToArg<m_type8>::EncodeT argval8 = (PtrToArg<m_type8>::EncodeT)arg8;\
			PtrToArg<m_type9>::EncodeT argval9 = (PtrToArg<m_type9>::EncodeT)arg9;\
			PtrToArg<m_type10>::EncodeT argval10 = (PtrToArg<m_type10>::EncodeT)arg10;\
			PtrToArg<m_type11>::EncodeT argval11 = (PtrToArg<m_type11>::EncodeT)arg11;\
			GDExtensionConstTypePtr argptrs[11] = { &argval1, &argval2, &argval3, &argval4, &argval5, &argval6, &argval7, &argval8, &argval9, &argval10, &argval11 };\
			PtrToArg<m_ret>::EncodeT ret;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), &ret);\
				r_ret = (m_ret)ret;\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), &ret);\
				r_ret = (m_ret)ret;\
			}\
			return true;\
		}\
		ERR_PRINT_ONCE("Required virtual method " + get_class() + "::" + #m_name + " must be overridden before calling.");\
		(void)r_ret;\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL | METHOD_FLAG_CONST | METHOD_FLAG_VIRTUAL_REQUIRED;\
		method_info.return_val = GetTypeInfo<m_ret>::get_class_info();\
		method_info.return_val_metadata = GetTypeInfo<m_ret>::METADATA;\
		method_info.arguments.push_back(GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type1>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type2>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type2>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type3>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type3>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type4>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type4>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type5>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type5>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type6>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type6>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type7>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type7>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type8>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type8>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type9>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type9>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type10>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type10>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type11>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type11>::METADATA);\
		return method_info;\
	}

/* 12 Arguments */

#define GDVIRTUAL12(m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8, m_type9, m_type10, m_type11, m_type12)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8, m_type9 arg9, m_type10 arg10, m_type11 arg11, m_type12 arg12) {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant vargs[12] = { Variant(arg1), Variant(arg2), Variant(arg3), Variant(arg4), Variant(arg5), Variant(arg6), Variant(arg7), Variant(arg8), Variant(arg9), Variant(arg10), Variant(arg11), Variant(arg12) };\
			const Variant *vargptrs[12] = { &vargs[0], &vargs[1], &vargs[2], &vargs[3], &vargs[4], &vargs[5], &vargs[6], &vargs[7], &vargs[8], &vargs[9], &vargs[10], &vargs[11] };\
			_script_instance->callp(_gdvirtual_##m_name##_sn, (const Variant **)vargptrs, 12, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_type1>::EncodeT argval1 = (PtrToArg<m_type1>::EncodeT)arg1;\
			PtrToArg<m_type2>::EncodeT argval2 = (PtrToArg<m_type2>::EncodeT)arg2;\
			PtrToArg<m_type3>::EncodeT argval3 = (PtrToArg<m_type3>::EncodeT)arg3;\
			PtrToArg<m_type4>::EncodeT argval4 = (PtrToArg<m_type4>::EncodeT)arg4;\
			PtrToArg<m_type5>::EncodeT argval5 = (PtrToArg<m_type5>::EncodeT)arg5;\
			PtrToArg<m_type6>::EncodeT argval6 = (PtrToArg<m_type6>::EncodeT)arg6;\
			PtrToArg<m_type7>::EncodeT argval7 = (PtrToArg<m_type7>::EncodeT)arg7;\
			PtrToArg<m_type8>::EncodeT argval8 = (PtrToArg<m_type8>::EncodeT)arg8;\
			PtrToArg<m_type9>::EncodeT argval9 = (PtrToArg<m_type9>::EncodeT)arg9;\
			PtrToArg<m_type10>::EncodeT argval10 = (PtrToArg<m_type10>::EncodeT)arg10;\
			PtrToArg<m_type11>::EncodeT argval11 = (PtrToArg<m_type11>::EncodeT)arg11;\
			PtrToArg<m_type12>::EncodeT argval12 = (PtrToArg<m_type12>::EncodeT)arg12;\
			GDExtensionConstTypePtr argptrs[12] = { &argval1, &argval2, &argval3, &argval4, &argval5, &argval6, &argval7, &argval8, &argval9, &argval10, &argval11, &argval12 };\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), nullptr);\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), nullptr);\
			}\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL;\
		method_info.arguments.push_back(GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type1>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type2>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type2>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type3>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type3>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type4>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type4>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type5>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type5>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type6>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type6>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type7>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type7>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type8>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type8>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type9>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type9>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type10>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type10>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type11>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type11>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type12>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type12>::METADATA);\
		return method_info;\
	}

#define GDVIRTUAL12R(m_ret, m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8, m_type9, m_type10, m_type11, m_type12)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8, m_type9 arg9, m_type10 arg10, m_type11 arg11, m_type12 arg12, m_ret &r_ret) {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant vargs[12] = { Variant(arg1), Variant(arg2), Variant(arg3), Variant(arg4), Variant(arg5), Variant(arg6), Variant(arg7), Variant(arg8), Variant(arg9), Variant(arg10), Variant(arg11), Variant(arg12) };\
			const Variant *vargptrs[12] = { &vargs[0], &vargs[1], &vargs[2], &vargs[3], &vargs[4], &vargs[5], &vargs[6], &vargs[7], &vargs[8], &vargs[9], &vargs[10], &vargs[11] };\
			Variant ret = _script_instance->callp(_gdvirtual_##m_name##_sn, (const Variant **)vargptrs, 12, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				r_ret = VariantCaster<m_ret>::cast(ret);\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_type1>::EncodeT argval1 = (PtrToArg<m_type1>::EncodeT)arg1;\
			PtrToArg<m_type2>::EncodeT argval2 = (PtrToArg<m_type2>::EncodeT)arg2;\
			PtrToArg<m_type3>::EncodeT argval3 = (PtrToArg<m_type3>::EncodeT)arg3;\
			PtrToArg<m_type4>::EncodeT argval4 = (PtrToArg<m_type4>::EncodeT)arg4;\
			PtrToArg<m_type5>::EncodeT argval5 = (PtrToArg<m_type5>::EncodeT)arg5;\
			PtrToArg<m_type6>::EncodeT argval6 = (PtrToArg<m_type6>::EncodeT)arg6;\
			PtrToArg<m_type7>::EncodeT argval7 = (PtrToArg<m_type7>::EncodeT)arg7;\
			PtrToArg<m_type8>::EncodeT argval8 = (PtrToArg<m_type8>::EncodeT)arg8;\
			PtrToArg<m_type9>::EncodeT argval9 = (PtrToArg<m_type9>::EncodeT)arg9;\
			PtrToArg<m_type10>::EncodeT argval10 = (PtrToArg<m_type10>::EncodeT)arg10;\
			PtrToArg<m_type11>::EncodeT argval11 = (PtrToArg<m_type11>::EncodeT)arg11;\
			PtrToArg<m_type12>::EncodeT argval12 = (PtrToArg<m_type12>::EncodeT)arg12;\
			GDExtensionConstTypePtr argptrs[12] = { &argval1, &argval2, &argval3, &argval4, &argval5, &argval6, &argval7, &argval8, &argval9, &argval10, &argval11, &argval12 };\
			PtrToArg<m_ret>::EncodeT ret;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), &ret);\
				r_ret = (m_ret)ret;\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), &ret);\
				r_ret = (m_ret)ret;\
			}\
			return true;\
		}\
		(void)r_ret;\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL;\
		method_info.return_val = GetTypeInfo<m_ret>::get_class_info();\
		method_info.return_val_metadata = GetTypeInfo<m_ret>::METADATA;\
		method_info.arguments.push_back(GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type1>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type2>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type2>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type3>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type3>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type4>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type4>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type5>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type5>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type6>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type6>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type7>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type7>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type8>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type8>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type9>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type9>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type10>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type10>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type11>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type11>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type12>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type12>::METADATA);\
		return method_info;\
	}

#define GDVIRTUAL12C(m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8, m_type9, m_type10, m_type11, m_type12)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8, m_type9 arg9, m_type10 arg10, m_type11 arg11, m_type12 arg12) const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant vargs[12] = { Variant(arg1), Variant(arg2), Variant(arg3), Variant(arg4), Variant(arg5), Variant(arg6), Variant(arg7), Variant(arg8), Variant(arg9), Variant(arg10), Variant(arg11), Variant(arg12) };\
			const Variant *vargptrs[12] = { &vargs[0], &vargs[1], &vargs[2], &vargs[3], &vargs[4], &vargs[5], &vargs[6], &vargs[7], &vargs[8], &vargs[9], &vargs[10], &vargs[11] };\
			_script_instance->callp(_gdvirtual_##m_name##_sn, (const Variant **)vargptrs, 12, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_type1>::EncodeT argval1 = (PtrToArg<m_type1>::EncodeT)arg1;\
			PtrToArg<m_type2>::EncodeT argval2 = (PtrToArg<m_type2>::EncodeT)arg2;\
			PtrToArg<m_type3>::EncodeT argval3 = (PtrToArg<m_type3>::EncodeT)arg3;\
			PtrToArg<m_type4>::EncodeT argval4 = (PtrToArg<m_type4>::EncodeT)arg4;\
			PtrToArg<m_type5>::EncodeT argval5 = (PtrToArg<m_type5>::EncodeT)arg5;\
			PtrToArg<m_type6>::EncodeT argval6 = (PtrToArg<m_type6>::EncodeT)arg6;\
			PtrToArg<m_type7>::EncodeT argval7 = (PtrToArg<m_type7>::EncodeT)arg7;\
			PtrToArg<m_type8>::EncodeT argval8 = (PtrToArg<m_type8>::EncodeT)arg8;\
			PtrToArg<m_type9>::EncodeT argval9 = (PtrToArg<m_type9>::EncodeT)arg9;\
			PtrToArg<m_type10>::EncodeT argval10 = (PtrToArg<m_type10>::EncodeT)arg10;\
			PtrToArg<m_type11>::EncodeT argval11 = (PtrToArg<m_type11>::EncodeT)arg11;\
			PtrToArg<m_type12>::EncodeT argval12 = (PtrToArg<m_type12>::EncodeT)arg12;\
			GDExtensionConstTypePtr argptrs[12] = { &argval1, &argval2, &argval3, &argval4, &argval5, &argval6, &argval7, &argval8, &argval9, &argval10, &argval11, &argval12 };\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), nullptr);\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), nullptr);\
			}\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL | METHOD_FLAG_CONST;\
		method_info.arguments.push_back(GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type1>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type2>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type2>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type3>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type3>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type4>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type4>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type5>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type5>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type6>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type6>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type7>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type7>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type8>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type8>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type9>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type9>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type10>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type10>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type11>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type11>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type12>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type12>::METADATA);\
		return method_info;\
	}

#define GDVIRTUAL12RC(m_ret, m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8, m_type9, m_type10, m_type11, m_type12)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8, m_type9 arg9, m_type10 arg10, m_type11 arg11, m_type12 arg12, m_ret &r_ret) const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant vargs[12] = { Variant(arg1), Variant(arg2), Variant(arg3), Variant(arg4), Variant(arg5), Variant(arg6), Variant(arg7), Variant(arg8), Variant(arg9), Variant(arg10), Variant(arg11), Variant(arg12) };\
			const Variant *vargptrs[12] = { &vargs[0], &vargs[1], &vargs[2], &vargs[3], &vargs[4], &vargs[5], &vargs[6], &vargs[7], &vargs[8], &vargs[9], &vargs[10], &vargs[11] };\
			Variant ret = _script_instance->callp(_gdvirtual_##m_name##_sn, (const Variant **)vargptrs, 12, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				r_ret = VariantCaster<m_ret>::cast(ret);\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_type1>::EncodeT argval1 = (PtrToArg<m_type1>::EncodeT)arg1;\
			PtrToArg<m_type2>::EncodeT argval2 = (PtrToArg<m_type2>::EncodeT)arg2;\
			PtrToArg<m_type3>::EncodeT argval3 = (PtrToArg<m_type3>::EncodeT)arg3;\
			PtrToArg<m_type4>::EncodeT argval4 = (PtrToArg<m_type4>::EncodeT)arg4;\
			PtrToArg<m_type5>::EncodeT argval5 = (PtrToArg<m_type5>::EncodeT)arg5;\
			PtrToArg<m_type6>::EncodeT argval6 = (PtrToArg<m_type6>::EncodeT)arg6;\
			PtrToArg<m_type7>::EncodeT argval7 = (PtrToArg<m_type7>::EncodeT)arg7;\
			PtrToArg<m_type8>::EncodeT argval8 = (PtrToArg<m_type8>::EncodeT)arg8;\
			PtrToArg<m_type9>::EncodeT argval9 = (PtrToArg<m_type9>::EncodeT)arg9;\
			PtrToArg<m_type10>::EncodeT argval10 = (PtrToArg<m_type10>::EncodeT)arg10;\
			PtrToArg<m_type11>::EncodeT argval11 = (PtrToArg<m_type11>::EncodeT)arg11;\
			PtrToArg<m_type12>::EncodeT argval12 = (PtrToArg<m_type12>::EncodeT)arg12;\
			GDExtensionConstTypePtr argptrs[12] = { &argval1, &argval2, &argval3, &argval4, &argval5, &argval6, &argval7, &argval8, &argval9, &argval10, &argval11, &argval12 };\
			PtrToArg<m_ret>::EncodeT ret;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), &ret);\
				r_ret = (m_ret)ret;\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), &ret);\
				r_ret = (m_ret)ret;\
			}\
			return true;\
		}\
		(void)r_ret;\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL | METHOD_FLAG_CONST;\
		method_info.return_val = GetTypeInfo<m_ret>::get_class_info();\
		method_info.return_val_metadata = GetTypeInfo<m_ret>::METADATA;\
		method_info.arguments.push_back(GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type1>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type2>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type2>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type3>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type3>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type4>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type4>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type5>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type5>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type6>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type6>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type7>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type7>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type8>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type8>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type9>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type9>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type10>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type10>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type11>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type11>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type12>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type12>::METADATA);\
		return method_info;\
	}

#define GDVIRTUAL12_REQUIRED(m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8, m_type9, m_type10, m_type11, m_type12)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8, m_type9 arg9, m_type10 arg10, m_type11 arg11, m_type12 arg12) {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant vargs[12] = { Variant(arg1), Variant(arg2), Variant(arg3), Variant(arg4), Variant(arg5), Variant(arg6), Variant(arg7), Variant(arg8), Variant(arg9), Variant(arg10), Variant(arg11), Variant(arg12) };\
			const Variant *vargptrs[12] = { &vargs[0], &vargs[1], &vargs[2], &vargs[3], &vargs[4], &vargs[5], &vargs[6], &vargs[7], &vargs[8], &vargs[9], &vargs[10], &vargs[11] };\
			_script_instance->callp(_gdvirtual_##m_name##_sn, (const Variant **)vargptrs, 12, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_type1>::EncodeT argval1 = (PtrToArg<m_type1>::EncodeT)arg1;\
			PtrToArg<m_type2>::EncodeT argval2 = (PtrToArg<m_type2>::EncodeT)arg2;\
			PtrToArg<m_type3>::EncodeT argval3 = (PtrToArg<m_type3>::EncodeT)arg3;\
			PtrToArg<m_type4>::EncodeT argval4 = (PtrToArg<m_type4>::EncodeT)arg4;\
			PtrToArg<m_type5>::EncodeT argval5 = (PtrToArg<m_type5>::EncodeT)arg5;\
			PtrToArg<m_type6>::EncodeT argval6 = (PtrToArg<m_type6>::EncodeT)arg6;\
			PtrToArg<m_type7>::EncodeT argval7 = (PtrToArg<m_type7>::EncodeT)arg7;\
			PtrToArg<m_type8>::EncodeT argval8 = (PtrToArg<m_type8>::EncodeT)arg8;\
			PtrToArg<m_type9>::EncodeT argval9 = (PtrToArg<m_type9>::EncodeT)arg9;\
			PtrToArg<m_type10>::EncodeT argval10 = (PtrToArg<m_type10>::EncodeT)arg10;\
			PtrToArg<m_type11>::EncodeT argval11 = (PtrToArg<m_type11>::EncodeT)arg11;\
			PtrToArg<m_type12>::EncodeT argval12 = (PtrToArg<m_type12>::EncodeT)arg12;\
			GDExtensionConstTypePtr argptrs[12] = { &argval1, &argval2, &argval3, &argval4, &argval5, &argval6, &argval7, &argval8, &argval9, &argval10, &argval11, &argval12 };\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), nullptr);\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), nullptr);\
			}\
			return true;\
		}\
		ERR_PRINT_ONCE("Required virtual method " + get_class() + "::" + #m_name + " must be overridden before calling.");\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL | METHOD_FLAG_VIRTUAL_REQUIRED;\
		method_info.arguments.push_back(GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type1>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type2>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type2>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type3>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type3>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type4>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type4>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type5>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type5>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type6>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type6>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type7>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type7>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type8>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type8>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type9>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type9>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type10>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type10>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type11>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type11>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type12>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type12>::METADATA);\
		return method_info;\
	}

#define GDVIRTUAL12R_REQUIRED(m_ret, m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8, m_type9, m_type10, m_type11, m_type12)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8, m_type9 arg9, m_type10 arg10, m_type11 arg11, m_type12 arg12, m_ret &r_ret) {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant vargs[12] = { Variant(arg1), Variant(arg2), Variant(arg3), Variant(arg4), Variant(arg5), Variant(arg6), Variant(arg7), Variant(arg8), Variant(arg9), Variant(arg10), Variant(arg11), Variant(arg12) };\
			const Variant *vargptrs[12] = { &vargs[0], &vargs[1], &vargs[2], &vargs[3], &vargs[4], &vargs[5], &vargs[6], &vargs[7], &vargs[8], &vargs[9], &vargs[10], &vargs[11] };\
			Variant ret = _script_instance->callp(_gdvirtual_##m_name##_sn, (const Variant **)vargptrs, 12, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				r_ret = VariantCaster<m_ret>::cast(ret);\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_type1>::EncodeT argval1 = (PtrToArg<m_type1>::EncodeT)arg1;\
			PtrToArg<m_type2>::EncodeT argval2 = (PtrToArg<m_type2>::EncodeT)arg2;\
			PtrToArg<m_type3>::EncodeT argval3 = (PtrToArg<m_type3>::EncodeT)arg3;\
			PtrToArg<m_type4>::EncodeT argval4 = (PtrToArg<m_type4>::EncodeT)arg4;\
			PtrToArg<m_type5>::EncodeT argval5 = (PtrToArg<m_type5>::EncodeT)arg5;\
			PtrToArg<m_type6>::EncodeT argval6 = (PtrToArg<m_type6>::EncodeT)arg6;\
			PtrToArg<m_type7>::EncodeT argval7 = (PtrToArg<m_type7>::EncodeT)arg7;\
			PtrToArg<m_type8>::EncodeT argval8 = (PtrToArg<m_type8>::EncodeT)arg8;\
			PtrToArg<m_type9>::EncodeT argval9 = (PtrToArg<m_type9>::EncodeT)arg9;\
			PtrToArg<m_type10>::EncodeT argval10 = (PtrToArg<m_type10>::EncodeT)arg10;\
			PtrToArg<m_type11>::EncodeT argval11 = (PtrToArg<m_type11>::EncodeT)arg11;\
			PtrToArg<m_type12>::EncodeT argval12 = (PtrToArg<m_type12>::EncodeT)arg12;\
			GDExtensionConstTypePtr argptrs[12] = { &argval1, &argval2, &argval3, &argval4, &argval5, &argval6, &argval7, &argval8, &argval9, &argval10, &argval11, &argval12 };\
			PtrToArg<m_ret>::EncodeT ret;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), &ret);\
				r_ret = (m_ret)ret;\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), &ret);\
				r_ret = (m_ret)ret;\
			}\
			return true;\
		}\
		ERR_PRINT_ONCE("Required virtual method " + get_class() + "::" + #m_name + " must be overridden before calling.");\
		(void)r_ret;\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL | METHOD_FLAG_VIRTUAL_REQUIRED;\
		method_info.return_val = GetTypeInfo<m_ret>::get_class_info();\
		method_info.return_val_metadata = GetTypeInfo<m_ret>::METADATA;\
		method_info.arguments.push_back(GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type1>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type2>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type2>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type3>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type3>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type4>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type4>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type5>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type5>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type6>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type6>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type7>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type7>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type8>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type8>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type9>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type9>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type10>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type10>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type11>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type11>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type12>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type12>::METADATA);\
		return method_info;\
	}

#define GDVIRTUAL12C_REQUIRED(m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8, m_type9, m_type10, m_type11, m_type12)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8, m_type9 arg9, m_type10 arg10, m_type11 arg11, m_type12 arg12) const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant vargs[12] = { Variant(arg1), Variant(arg2), Variant(arg3), Variant(arg4), Variant(arg5), Variant(arg6), Variant(arg7), Variant(arg8), Variant(arg9), Variant(arg10), Variant(arg11), Variant(arg12) };\
			const Variant *vargptrs[12] = { &vargs[0], &vargs[1], &vargs[2], &vargs[3], &vargs[4], &vargs[5], &vargs[6], &vargs[7], &vargs[8], &vargs[9], &vargs[10], &vargs[11] };\
			_script_instance->callp(_gdvirtual_##m_name##_sn, (const Variant **)vargptrs, 12, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_type1>::EncodeT argval1 = (PtrToArg<m_type1>::EncodeT)arg1;\
			PtrToArg<m_type2>::EncodeT argval2 = (PtrToArg<m_type2>::EncodeT)arg2;\
			PtrToArg<m_type3>::EncodeT argval3 = (PtrToArg<m_type3>::EncodeT)arg3;\
			PtrToArg<m_type4>::EncodeT argval4 = (PtrToArg<m_type4>::EncodeT)arg4;\
			PtrToArg<m_type5>::EncodeT argval5 = (PtrToArg<m_type5>::EncodeT)arg5;\
			PtrToArg<m_type6>::EncodeT argval6 = (PtrToArg<m_type6>::EncodeT)arg6;\
			PtrToArg<m_type7>::EncodeT argval7 = (PtrToArg<m_type7>::EncodeT)arg7;\
			PtrToArg<m_type8>::EncodeT argval8 = (PtrToArg<m_type8>::EncodeT)arg8;\
			PtrToArg<m_type9>::EncodeT argval9 = (PtrToArg<m_type9>::EncodeT)arg9;\
			PtrToArg<m_type10>::EncodeT argval10 = (PtrToArg<m_type10>::EncodeT)arg10;\
			PtrToArg<m_type11>::EncodeT argval11 = (PtrToArg<m_type11>::EncodeT)arg11;\
			PtrToArg<m_type12>::EncodeT argval12 = (PtrToArg<m_type12>::EncodeT)arg12;\
			GDExtensionConstTypePtr argptrs[12] = { &argval1, &argval2, &argval3, &argval4, &argval5, &argval6, &argval7, &argval8, &argval9, &argval10, &argval11, &argval12 };\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), nullptr);\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), nullptr);\
			}\
			return true;\
		}\
		ERR_PRINT_ONCE("Required virtual method " + get_class() + "::" + #m_name + " must be overridden before calling.");\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL | METHOD_FLAG_CONST | METHOD_FLAG_VIRTUAL_REQUIRED;\
		method_info.arguments.push_back(GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type1>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type2>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type2>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type3>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type3>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type4>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type4>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type5>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type5>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type6>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type6>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type7>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type7>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type8>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type8>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type9>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type9>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type10>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type10>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type11>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type11>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type12>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type12>::METADATA);\
		return method_info;\
	}

#define GDVIRTUAL12RC_REQUIRED(m_ret, m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8, m_type9, m_type10, m_type11, m_type12)\
	StringName _gdvirtual_##m_name##_sn = #m_name;\
	mutable bool _gdvirtual_##m_name##_initialized = false;\
	mutable void *_gdvirtual_##m_name = nullptr;\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_call(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8, m_type9 arg9, m_type10 arg10, m_type11 arg11, m_type12 arg12, m_ret &r_ret) const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance) {\
			Callable::CallError ce;\
			Variant vargs[12] = { Variant(arg1), Variant(arg2), Variant(arg3), Variant(arg4), Variant(arg5), Variant(arg6), Variant(arg7), Variant(arg8), Variant(arg9), Variant(arg10), Variant(arg11), Variant(arg12) };\
			const Variant *vargptrs[12] = { &vargs[0], &vargs[1], &vargs[2], &vargs[3], &vargs[4], &vargs[5], &vargs[6], &vargs[7], &vargs[8], &vargs[9], &vargs[10], &vargs[11] };\
			Variant ret = _script_instance->callp(_gdvirtual_##m_name##_sn, (const Variant **)vargptrs, 12, ce);\
			if (ce.error == Callable::CallError::CALL_OK) {\
				r_ret = VariantCaster<m_ret>::cast(ret);\
				return true;\
			}\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			PtrToArg<m_type1>::EncodeT argval1 = (PtrToArg<m_type1>::EncodeT)arg1;\
			PtrToArg<m_type2>::EncodeT argval2 = (PtrToArg<m_type2>::EncodeT)arg2;\
			PtrToArg<m_type3>::EncodeT argval3 = (PtrToArg<m_type3>::EncodeT)arg3;\
			PtrToArg<m_type4>::EncodeT argval4 = (PtrToArg<m_type4>::EncodeT)arg4;\
			PtrToArg<m_type5>::EncodeT argval5 = (PtrToArg<m_type5>::EncodeT)arg5;\
			PtrToArg<m_type6>::EncodeT argval6 = (PtrToArg<m_type6>::EncodeT)arg6;\
			PtrToArg<m_type7>::EncodeT argval7 = (PtrToArg<m_type7>::EncodeT)arg7;\
			PtrToArg<m_type8>::EncodeT argval8 = (PtrToArg<m_type8>::EncodeT)arg8;\
			PtrToArg<m_type9>::EncodeT argval9 = (PtrToArg<m_type9>::EncodeT)arg9;\
			PtrToArg<m_type10>::EncodeT argval10 = (PtrToArg<m_type10>::EncodeT)arg10;\
			PtrToArg<m_type11>::EncodeT argval11 = (PtrToArg<m_type11>::EncodeT)arg11;\
			PtrToArg<m_type12>::EncodeT argval12 = (PtrToArg<m_type12>::EncodeT)arg12;\
			GDExtensionConstTypePtr argptrs[12] = { &argval1, &argval2, &argval3, &argval4, &argval5, &argval6, &argval7, &argval8, &argval9, &argval10, &argval11, &argval12 };\
			PtrToArg<m_ret>::EncodeT ret;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_get_extension()->call_virtual_with_data(_get_extension_instance(), &_gdvirtual_##m_name##_sn, _gdvirtual_##m_name, reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), &ret);\
				r_ret = (m_ret)ret;\
			} else {\
				((GDExtensionClassCallVirtual)_gdvirtual_##m_name)(_get_extension_instance(), reinterpret_cast<GDExtensionConstTypePtr *>(argptrs), &ret);\
				r_ret = (m_ret)ret;\
			}\
			return true;\
		}\
		ERR_PRINT_ONCE("Required virtual method " + get_class() + "::" + #m_name + " must be overridden before calling.");\
		(void)r_ret;\
		return false;\
	}\
	_FORCE_INLINE_ bool _gdvirtual_##m_name##_overridden() const {\
		ScriptInstance *_script_instance = ((Object *)(this))->get_script_instance();\
		if (_script_instance && _script_instance->has_method(_gdvirtual_##m_name##_sn)) {\
			return true;\
		}\
		if (unlikely(_get_extension() && !_gdvirtual_##m_name##_initialized)) {\
			_gdvirtual_##m_name = nullptr;\
			if (_get_extension()->get_virtual_call_data && _get_extension()->call_virtual_with_data) {\
				_gdvirtual_##m_name = _get_extension()->get_virtual_call_data(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			} else if (_get_extension()->get_virtual) {\
				_gdvirtual_##m_name = (void *)_get_extension()->get_virtual(_get_extension()->class_userdata, &_gdvirtual_##m_name##_sn);\
			}\
			GDVIRTUAL_TRACK(_gdvirtual_##m_name, _gdvirtual_##m_name##_initialized);\
			_gdvirtual_##m_name##_initialized = true;\
		}\
		if (_gdvirtual_##m_name) {\
			return true;\
		}\
		return false;\
	}\
	_FORCE_INLINE_ static MethodInfo _gdvirtual_##m_name##_get_method_info() {\
		MethodInfo method_info;\
		method_info.name = #m_name;\
		method_info.flags = METHOD_FLAG_VIRTUAL | METHOD_FLAG_CONST | METHOD_FLAG_VIRTUAL_REQUIRED;\
		method_info.return_val = GetTypeInfo<m_ret>::get_class_info();\
		method_info.return_val_metadata = GetTypeInfo<m_ret>::METADATA;\
		method_info.arguments.push_back(GetTypeInfo<m_type1>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type1>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type2>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type2>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type3>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type3>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type4>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type4>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type5>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type5>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type6>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type6>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type7>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type7>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type8>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type8>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type9>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type9>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type10>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type10>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type11>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type11>::METADATA);\
		method_info.arguments.push_back(GetTypeInfo<m_type12>::get_class_info());\
		method_info.arguments_metadata.push_back(GetTypeInfo<m_type12>::METADATA);\
		return method_info;\
	}

#endif // GDVIRTUAL_GEN_H
