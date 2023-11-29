#ifndef _FUNCTION_VIEW_H_INCLUDED
#define _FUNCTION_VIEW_H_INCLUDED

#include <type_traits>

template<typename T>
class FunctionView;

template<typename R, typename ... Args>
class FunctionView<R(Args...)> final
{
public:
    template <
        typename F,
        typename std::enable_if<

        !std::is_function<typename std::remove_pointer<
        typename std::remove_reference<F>::type>::type>::value &&

        !std::is_same<std::nullptr_t,
        typename std::remove_cv<F>::type>::value &&

        !std::is_same<FunctionView,
        typename std::remove_cv<typename std::remove_reference<
        F>::type>::type>::value>::type* = nullptr>
    FunctionView(F&& f)
        : _call(CallVoidPtr<typename std::remove_reference<F>::type>)
    {
        _f.void_ptr = &f;
    }

    template <
        typename F,
        typename std::enable_if<std::is_function<typename std::remove_pointer<
        typename std::remove_reference<F>::type>::type>::value>::type* = nullptr>
    FunctionView(F&& f)
        : _call(f ? CallFunPtr<typename std::remove_pointer<F>::type> : nullptr)
    {
        _f.fun_ptr = reinterpret_cast<void(*)()>(f);
    }

    template <typename F,
        typename std::enable_if<std::is_same<
        std::nullptr_t,
        typename std::remove_cv<F>::type>::value>::type* = nullptr>
    FunctionView(F&& f) {}

    FunctionView() = default;

    R operator()(Args... args) const
    {
        return _call(_f, std::forward<Args>(args)...);
    }

    explicit operator bool() const { return !!_call; }

private:
    union VoidUnion
    {
        void* void_ptr;
        void(*fun_ptr)();
    };

    template <typename F>
    static R CallVoidPtr(VoidUnion vu, Args... args)
    {
        return (*static_cast<F*>(vu.void_ptr))(std::forward<Args>(args)...);
    }
    template <typename F>
    static R CallFunPtr(VoidUnion vu, Args... args)
    {
        return (reinterpret_cast<typename std::add_pointer<F>::type>(vu.fun_ptr))(
            std::forward<Args>(args)...);
    }

    VoidUnion _f;

    R(*_call)(VoidUnion, Args...) = nullptr;
};


#endif // !_FUNCTION_VIEW_H_INCLUDED
