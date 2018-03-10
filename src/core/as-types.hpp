#pragma once

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif // _WIN32

#ifdef __GNUC__
#include <csignal>
#endif // __GNUC__

#include <cstdint>
#include <cmath>
#include <cfloat>

namespace as
{

// typedefs
typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef float f32;
typedef double f64;

typedef uint8_t byte;

// static assert to check library floating point precision has been set correctly
#if (!defined(AS_PRECISION_FLOAT) && !defined(AS_PRECISION_DOUBLE))
    static_assert(false, "Must define AS_PRECISION_FLOAT or AS_PRECISION_DOUBLE");
#elif (defined(AS_PRECISION_FLOAT) && defined(AS_PRECISION_DOUBLE))
    static_assert(false, "Must define only AS_PRECISION_FLOAT or AS_PRECISION_DOUBLE");
#endif // // AS_PRECISION_FLOAT ? AS_PRECISION_DOUBLE

#ifdef AS_PRECISION_FLOAT
typedef float real_t;
#define cosr cosf
#define sinr sinf
#define tanr tanf
#define acosr acosf
#define asinr asinf
#define atanr atanf
#define absr fabsf
#define sqrtr sqrtf
#define REAL_EPSILON FLT_EPSILON
#define REAL_MAX FLT_MAX
#define REAL_MIN FLT_MIN
#elif defined AS_PRECISION_DOUBLE
typedef double real_t;
#define cosr cos
#define sinr sin
#define tanr tan
#define acosr acos
#define asinr asin
#define atanr atan
#define absr fabs
#define sqrtr sqrt
#define REAL_EPSILON DBL_EPSILON
#define REAL_MAX DBL_MAX
#define REAL_MIN DBL_MIN
#endif

#ifdef _MSC_VER
__pragma(warning(push))
__pragma(warning(disable: 4251))
#endif // _MSC_VER

#ifdef AS_FUNCDLL_EXPORT
#ifdef _MSC_VER
    #define AS_FUNCDLL_API __declspec(dllexport)
#elif defined __GNUC__
    #define AS_FUNCDLL_API __attribute__ ((visibility("default")))
#endif
#else
#ifdef _MSC_VER
    #define AS_FUNCDLL_API __declspec(dllimport)
#elif defined __GNUC__ 
    #define AS_FUNCDLL_API __attribute__ ((visibility ("hidden")))
#endif
#endif

#define AS_MULTILINE_MACRO_BEGIN do {
#define AS_MULTILINE_MACRO_END \
    } while((void)0,0)

//(void)sizeof(x); // Does not work on VS 2010+
#define AS_UNUSED(x) AS_MULTILINE_MACRO_BEGIN \
    (void)(x); \
    AS_MULTILINE_MACRO_END

#ifdef _MSC_VER
#define AS_BREAK() AS_MULTILINE_MACRO_BEGIN \
    __debugbreak(); \
AS_MULTILINE_MACRO_END
#elif defined __GNUC__
#define AS_BREAK() AS_MULTILINE_MACRO_BEGIN \
    raise(SIGABRT); \
AS_MULTILINE_MACRO_END
#endif

#define AS_DISABLE_OPTIMIZATIONS #pragma optimize("", off)
#ifdef _MSC_VER
#define AS_NOINLINE __declspec(noinline)
#elif defined __GNUC__
#define AS_NOINLINE __attribute__ ((__noinline__))
#endif

#define AS_TOSTRING(x) #x

// Type-safe compile time array size
template <typename T, int N> char(&dim_helper(T(&)[N]))[N];
#define AS_DIM(x) (sizeof(dim_helper(x)))

#ifdef _MSC_VER
#define AS_FORCE_INLINE __forceinline
#elif defined __GNUC__
#define AS_FORCE_INLINE inline __attribute__((__always_inline__))
#endif

#ifdef _MSC_VER
#define AS_ENABLE_UNUSED __pragma(warning(push)) \
                         __pragma(warning(disable:4100))

#define AS_DISABLE_UNUSED __pragma(warning(pop))
#endif // _MSC_VER

// Logging - Log to Visual Studio Output Window (DEBUG) or Console (CONSOLE)
#define AS_LOG_DEBUG
//#define AS_LOG_CONSOLE

} // namespace as

#ifdef _MSC_VER
__pragma(warning(pop))
#endif