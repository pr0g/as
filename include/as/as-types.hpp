#pragma once

#include <cstddef>
#include <cstdint>
#include <cmath>
#include <cfloat>

namespace as
{

// aliases for built-in data types
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
#endif // AS_PRECISION_FLOAT ? AS_PRECISION_DOUBLE

// aliases for float or double types and functions
#ifdef AS_PRECISION_FLOAT
using real_t = float;
#define cosr cosf
#define sinr sinf
#define tanr tanf
#define acosr acosf
#define asinr asinf
#define atanr atanf
#define fabsr fabsf
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
#define fabsr fabs
#define sqrtr sqrt
#define REAL_EPSILON DBL_EPSILON
#define REAL_MAX DBL_MAX
#define REAL_MIN DBL_MIN
#endif // AS_PRECISION_FLOAT ? AS_PRECISION_DOUBLE

// from Google's Chromium project - compile time array size
#define AS_DIM(x) ((sizeof(x) / sizeof(0[x])) / ((size_t)(!(sizeof(x) % sizeof(0[x])))))

#ifdef _MSC_VER
#define AS_NOINLINE __declspec(noinline)
#elif defined __GNUC__
#define AS_NOINLINE __attribute__ ((__noinline__))
#endif // _MSC_VER ? __GNUC__

#ifdef _MSC_VER
#define AS_FORCE_INLINE __forceinline
#elif defined __GNUC__
#define AS_FORCE_INLINE inline __attribute__((__always_inline__))
#endif // _MSC_VER ? __GNUC__

#ifdef _MSC_VER
#define AS_API
#elif defined __GNUC__ && defined AS_COVERAGE
#define AS_API __attribute__((__used__))
#elif defined __GNUC__
#define AS_API
#endif // _MSC_VER ? __GNUC__ && AS_COVERAGE

} // namespace as
