//! \file
//! `as-types`

#pragma once

#include <cfloat>
#include <cmath>
#include <cstddef>
#include <cstdint>

//! \mainpage `as` - a header-only linear algebra math library written in C++
//! \section overview as
//! `as` is written in C++ and relies on templates to parameterize vectors and
//! matrices by both type and dimension. Template specializations exist for
//! common vector and matrix types such as `vec3` and `mat4`. Row or Column
//! major ordering must be determined by defining either `AS_COL_MAJOR` or
//! `AS_ROW_MAJOR`. The default type `real` must also be set by either defining
//! `AS_PRECISION_FLOAT` or `AS_PRECISION_DOUBLE`.

//! `as` - a header-only linear algebra math library written in C++.
namespace as
{

//! Alias for `ptrdiff_t` (signed integer).
//! \note Used primarily for loop counters
using index = ptrdiff_t;

// static assert to check library floating p precision has been set
// correctly
#if (!defined(AS_PRECISION_FLOAT) && !defined(AS_PRECISION_DOUBLE))
static_assert(false, "Must define AS_PRECISION_FLOAT or AS_PRECISION_DOUBLE");
#elif (defined(AS_PRECISION_FLOAT) && defined(AS_PRECISION_DOUBLE))
static_assert(
  false, "Must define only AS_PRECISION_FLOAT or AS_PRECISION_DOUBLE");
#endif // AS_PRECISION_FLOAT ? AS_PRECISION_DOUBLE

inline namespace literals
{

#ifdef AS_PRECISION_FLOAT
//! An alias for `float` if `AS_PRECISION_FLOAT` is defined.
using real = float;
//! A user-defined literal to be used for ::real.
//! \note Returns `float` when `AS_PRECISION_FLOAT` is defined.
//! \note Useful when using literals where precision is customizable.
constexpr float operator"" _r(const long double val)
{
  return float(val);
}
#endif // AS_PRECISION_FLOAT

#ifdef AS_PRECISION_DOUBLE
//! An alias for `double` if `AS_PRECISION_DOUBLE` is defined.
using real = double;
//! A user-defined literal to be used for ::real.
//! \note Returns `double` when `AS_PRECISION_DOUBLE` is defined.
//! \note Useful when using literals where precision is customizable.
constexpr double operator"" _r(const long double val)
{
  return double(val);
}
#endif // AS_PRECISION_DOUBLE

} // namespace literals

//! A utility function to convert a double to the type ::real is defined as.
//! \note If ::real is defined as `float`, some precision may be lost during
//! the conversion.
constexpr real to_real(const double val)
{
  return real(val);
}

//! A utility function to convert a float to the type ::real is defined as.
constexpr real to_real(const float val)
{
  return real(val);
}

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
