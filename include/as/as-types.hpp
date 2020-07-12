#pragma once

#include <cfloat>
#include <cmath>
#include <cstdint>

namespace as
{

// aliases for built-in data types
using index_t = ptrdiff_t;

// static assert to check library floating point precision has been set
// correctly
#if (!defined(AS_PRECISION_FLOAT) && !defined(AS_PRECISION_DOUBLE))
static_assert(false, "Must define AS_PRECISION_FLOAT or AS_PRECISION_DOUBLE");
#elif (defined(AS_PRECISION_FLOAT) && defined(AS_PRECISION_DOUBLE))
static_assert(
    false, "Must define only AS_PRECISION_FLOAT or AS_PRECISION_DOUBLE");
#endif // AS_PRECISION_FLOAT ? AS_PRECISION_DOUBLE

// aliases for float or double types and functions
#ifdef AS_PRECISION_FLOAT
using real_t = float;
constexpr float operator"" _r(long double val)
{
    return float(val);
}
#elif defined AS_PRECISION_DOUBLE
using real_t = double;
constexpr double operator"" _r(long double val)
{
    return double(val);
}
#endif // AS_PRECISION_FLOAT ? AS_PRECISION_DOUBLE

// from Google's Chromium project - compile time array size
#define AS_DIM(x)                                                              \
    ((sizeof(x) / sizeof(0 [x])) / ((size_t)(!(sizeof(x) % sizeof(0 [x])))))

#ifdef _MSC_VER
#define AS_NOINLINE __declspec(noinline)
#elif defined __GNUC__
#define AS_NOINLINE __attribute__((__noinline__))
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
