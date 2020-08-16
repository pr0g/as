//! \file
//! as-math

#pragma once

#include "as-types.hpp"

namespace as
{

//! Mathematical constant Pi to 21 significant digits.
constexpr real_t kPi = 3.14159265358979323846_r;

//! Returns a linearly interpolated value between `begin` and `end`.
//! \param t The amount of interpolation between `begin` and `end`. Must be in
//! the range `[0-1]`.
//! \param begin The value to interpolate from.
//! \param end The value to interpolate to.
template<typename T>
constexpr T lerp(T t, T begin, T end);

//! Returns the result of Hermite interpolation between `begin` and `end`.
//! \note `smooth_step` is not second-order continuous at either `t=0` or `t=1`.
//! \param t The amount of interpolation between `begin` and `end`. Must be in
//! the range `[0-1]`.
//! \param begin The value to interpolate from.
//! \param end The value to interpolate to.
template<typename T>
constexpr T smooth_step(T t, T begin, T end);

//! Returns the result of Hermite interpolation between `begin` and `end`.
//! \note `smoother_step` is second-order continuous at both `t=0` and `t=1`.
//! \param t The amount of interpolation between `begin` and `end`. Must be in
//! the range `[0-1]`.
//! \param begin The value to interpolate from.
//! \param end The value to interpolate to.
template<typename T>
constexpr T smoother_step(T t, T begin, T end);

//! Returns the larger of the two values.
template<typename T>
constexpr T max(T v0, T v1);

//! Returns the smaller of the two values.
template<typename T>
constexpr T min(T v0, T v1);

//! Returns `low` if `in` is less than `low`, `high` if `in` is greater than
//! `high` and `in` otherwise.
//! \param in The value to clamp.
//! \param low The minimum value to clamp to.
//! \param high The maximum value to clamp to.
template<typename T>
constexpr T clamp(T in, T low, T high);

//! Returns the closest `step` value to `in`.
//! \param in The value to snap.
//! \param step The step size to snap to.
//! \remark `snap(in = 0.8, step = 0.5) = 1.0 // snap up`
//! \remark `snap(in = 0.6, step = 0.5) = 0.5 // snap down`
//! \remark `snap(in = 1.2, step = 0.5) = 1.0 // snap down`
template<typename T>
constexpr T snap(T in, T step);

//! Returns the value in radians as degrees.
constexpr real_t deg_to_rad(real_t degrees);

//! Returns the value in degrees as radians.
constexpr real_t rad_to_deg(real_t radians);

//! Returns if `a` and `b` are almost equal (within a given tolerance/epsilon).
//! \param a The first value to compare.
//! \param b The second value to compare.
//! \param max_diff The epsilon value to use for values very close to zero.
//! \param max_rel_diff The epsilon value to use for all other values.
//! `max_rel_diff` will be scaled by the largest of the two values.
bool almost_equal(
    real_t a, real_t b,
    real_t max_diff = std::numeric_limits<real_t>::epsilon(),
    real_t max_rel_diff = std::numeric_limits<real_t>::epsilon());

} // namespace as

#include "as-math.inl"
