//! \file
//! as-math

#pragma once

#include "as-types.hpp"

#include <algorithm>

namespace as
{

//! Mathematical constant Pi to 21 significant digits.
constexpr real kPi = 3.14159265358979323846_r;

//! Returns a linearly interpolated value between `begin` and `end`.
//! \param t The amount of interpolation between `begin` and `end`. Must be in
//! the range `[0-1]`.
//! \param begin The value to interpolate from.
//! \param end The value to interpolate to.
template<typename T>
constexpr T mix(T begin, T end, T t);

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

//! Returns the larger of the two values.
//! https://en.cppreference.com/w/cpp/algorithm/max
using std::max;

//! Returns the smaller of the two values.
//! https://en.cppreference.com/w/cpp/algorithm/min
using std::min;

//! Clamps the input between two values.
//! https://en.cppreference.com/w/cpp/algorithm/clamp
using std::clamp;

//! Returns the closest `step` value to `in`.
//! \param in The value to snap.
//! \param step The step size to snap to.
//! \remark `snap(in = 0.8, step = 0.5) = 1.0 // snap up`
//! \remark `snap(in = 0.6, step = 0.5) = 0.5 // snap down`
//! \remark `snap(in = 1.2, step = 0.5) = 1.0 // snap down`
template<typename T>
constexpr T snap(T in, T step);

//! Returns the value in degrees as radians.
constexpr real radians(real degrees);

//! Returns the value in radians as degrees.
constexpr real degrees(real radians);

//! Returns if `a` and `b` are almost equal (within a given tolerance/epsilon).
//! \param a The first value to compare.
//! \param b The second value to compare.
//! \param max_diff The epsilon value to use for values very close to zero.
//! \param max_rel_diff The epsilon value to use for all other values.
//! `max_rel_diff` will be scaled by the largest of the two values.
bool almost_equal(
  real a, real b, real max_diff = std::numeric_limits<real>::epsilon(),
  real max_rel_diff = std::numeric_limits<real>::epsilon());

} // namespace as

#include "as-math.inl"
