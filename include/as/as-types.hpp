//! \file
//! as-types

#pragma once

#include <cfloat>
#include <cmath>
#include <cstdint>

//! \mainpage `as` linear algebra math library
//! \section overview as tries to combine the best of C and C++

//! `as` linear algebra math library.
namespace as
{

//! Alias for `ptrdiff_t` (signed integer).
//! \note Used primarily for loop counters
using index_t = ptrdiff_t;

// static assert to check library floating p precision has been set
// correctly
#if (!defined(AS_PRECISION_FLOAT) && !defined(AS_PRECISION_DOUBLE))
static_assert(false, "Must define AS_PRECISION_FLOAT or AS_PRECISION_DOUBLE");
#elif (defined(AS_PRECISION_FLOAT) && defined(AS_PRECISION_DOUBLE))
static_assert(
  false, "Must define only AS_PRECISION_FLOAT or AS_PRECISION_DOUBLE");
#endif // AS_PRECISION_FLOAT ? AS_PRECISION_DOUBLE

#ifdef AS_PRECISION_FLOAT
//! An alias for `float` if `AS_PRECISION_FLOAT` is defined.
using real_t = float;
//! A user-defined literal to be used for ::real_t.
//! \note Returns `float` when `AS_PRECISION_FLOAT` is defined.
//! \note Useful when using literals where precision is customizable.
constexpr float operator"" _r(long double val)
{
  return float(val);
}
#endif // AS_PRECISION_FLOAT

#ifdef AS_PRECISION_DOUBLE
//! An alias for `double` if `AS_PRECISION_DOUBLE` is defined.
using real_t = double;
//! A user-defined literal to be used for ::real_t.
//! \note Returns `double` when `AS_PRECISION_DOUBLE` is defined.
//! \note Useful when using literals where precision is customizable.
constexpr double operator"" _r(long double val)
{
  return double(val);
}
#endif // AS_PRECISION_DOUBLE

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
