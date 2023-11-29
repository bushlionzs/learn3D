#ifdef _MSC_VER
    // for _Printf_format_string_ and compiler needs add /analyze options
    #include <sal.h>
#else
    #define _Printf_format_string_
#endif

#ifdef __GNUC__
    #define DY_NETWORK_PRINTF_FORMAT(format_param, dots_param) __attribute__((format(printf, format_param, dots_param)))
    #define DY_NETWORK_LIKELY(x) __builtin_expect(!!(x), 1)
    #define DY_NETWORK_UNLIKELY(x) __builtin_expect(!!(x), 0)
#else
    #define DY_NETWORK_PRINTF_FORMAT(format_param, dots_param)
    #define DY_NETWORK_LIKELY(x) (x)
    #define DY_NETWORK_UNLIKELY(x) (x)
#endif
