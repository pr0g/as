#pragma once

#ifdef __GNUC__
#include <csignal>
#endif // __GNUC__

#include <cstddef>
#include <cstdint>
#include <cmath>
#include <cfloat>

namespace as
{

// aliases
using s8 = int8_t;
using s16 = int16_t;
using s32 = int32_t;
using s64 = int64_t;
using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;
using f32 = float;
using f64 = double;

// static assert to check library floating point precision has been set correctly
#if (!defined(AS_PRECISION_FLOAT) && !defined(AS_PRECISION_DOUBLE))
    static_assert(false, "Must define AS_PRECISION_FLOAT or AS_PRECISION_DOUBLE");
#elif (defined(AS_PRECISION_FLOAT) && defined(AS_PRECISION_DOUBLE))
    static_assert(false, "Must define only AS_PRECISION_FLOAT or AS_PRECISION_DOUBLE");
#endif // // AS_PRECISION_FLOAT ? AS_PRECISION_DOUBLE

#ifdef AS_PRECISION_FLOAT
using real_t = float;
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
using real_t = double;
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

// from Google's Chromium project - compile time array size
#define AS_DIM(x) ((sizeof(x) / sizeof(0[x])) / ((size_t)(!(sizeof(x) % sizeof(0[x])))))

#ifdef _MSC_VER
#define AS_FORCE_INLINE __forceinline
#elif defined __GNUC__
#define AS_FORCE_INLINE inline __attribute__((__always_inline__))
#endif

} // namespace as