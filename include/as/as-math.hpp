//! \file
//! `as-math`

#pragma once

#include "as-types.hpp"

#include <algorithm>

namespace as
{

//! Mathematical constant Pi to 21 significant digits.
constexpr real k_pi = 3.14159265358979323846_r;

//! Mathematical constant 2 * Pi to 21 significant digits.
constexpr real k_two_pi = 6.28318530717958647692_r;

//! Mathematical constant 1/2 * Pi to 21 significant digits.
constexpr real k_half_pi = 1.57079632679489655800_r;

//! Mathematical constant Tau to 21 significant digits (equivalent to 2 * Pi).
constexpr real k_tau = k_two_pi;

//! Returns a linearly interpolated value between `begin` and `end`.
//! \param begin The value to interpolate from.
//! \param end The value to interpolate to.
//! \param t The amount of interpolation between `begin` and `end`. Must be in
//! the range `[0-1]`.
template<typename T, typename V>
constexpr V mix(V begin, V end, T t);

//! Returns a value in the range `[0-1]` from a value between `begin` and `end`.
//! \param begin The value at the beginning of the range.
//! \param end The value at the end of the range.
//! \param value The value between begin and end.
template<typename T>
constexpr real inverse_mix(T begin, T end, T value);

//! Returns the result of Hermite interpolation between `begin` and `end`.
//! \note `smooth_step` is not second-order continuous at either `t=0` or `t=1`.
//! \param t The amount of interpolation between `begin` and `end`. Must be in
//! the range `[0-1]`.
template<typename T>
constexpr T smooth_step(T t);

//! Returns the result of Hermite interpolation between `begin` and `end`.
//! \note `smoother_step` is second-order continuous at both `t=0` and `t=1`.
//! \param t The amount of interpolation between `begin` and `end`. Must be in
//! the range `[0-1]`.
template<typename T>
constexpr T smoother_step(T t);

//! Returns `1.0` when `x` is positive, `-1.0` when `x` is negative and `0.0`
//! when `x` is zero.
template<typename T>
constexpr T sign(T x);

//! Returns the fractional part of `x` (equivalent to `x - floor(x)`).
//! \note Be careful with negative numbers - this function preserves the
//! behavior of shading languages and will return `0.9` when `-0.1` is passed.
//! Use ::fract_abs or ::fract_abs_signed for more intuitive behavior.
template<typename T>
constexpr T fract(T x);

//! Returns the fractional part of `x` (equivalent to `x - floor(x)`) but first
//! calculates the absolute value of `x`.
//! \note Use this function for `-0.3` to return `0.3` not `0.7` as ::fract
//! does.
template<typename T>
constexpr T fract_abs(T x);

//! Returns the fractional part of `x` (equivalent to `x - floor(x)`) but first
//! calculates the absolute value of `x` and then preserves the original sign.
//! \note Use this function for `-0.3` to return `-0.3` not `0.7` (as ::fract
//! does) or `0.3` (as ::fract_abs does).
template<typename T>
constexpr T fract_abs_signed(T x);

//! Returns the larger of the two values.
//! https://en.cppreference.com/w/cpp/algorithm/max
using std::max;

//! Returns the smaller of the two values.
//! https://en.cppreference.com/w/cpp/algorithm/min
using std::min;

//! Clamps the input between two values.
//! https://en.cppreference.com/w/cpp/algorithm/clamp
using std::clamp;

//! Returns the absolute value of the input.
//! https://en.cppreference.com/w/cpp/numeric/math/abs
using std::abs;

//! Returns the closest `step` value to `in`.
//! \param in The value to snap.
//! \param step The step size to snap to.
//! \remark `snap(in = 0.8, step = 0.5) = 1.0 // snap up`
//! \remark `snap(in = 0.6, step = 0.5) = 0.5 // snap down`
//! \remark `snap(in = 1.2, step = 0.5) = 1.0 // snap down`
template<typename T>
constexpr T snap(T in, T step);

//! Returns the value in degrees as radians.
template<typename T>
constexpr T radians(T degrees);

//! Returns the value in radians as degrees.
template<typename T>
constexpr T degrees(T radians);

//! Returns if `a` and `b` are almost equal (within a given tolerance/epsilon).
//! \param a The first value to compare.
//! \param b The second value to compare.
//! \param max_diff The epsilon value to use for values very close to zero.
//! \param max_rel_diff The epsilon value to use for all other values.
//! `max_rel_diff` will be scaled by the largest of the two values.
bool real_near(
  real a, real b, real max_diff = std::numeric_limits<float>::epsilon(),
  real max_rel_diff = std::numeric_limits<float>::epsilon());

} // namespace as

#include "as-math.inl"
