#pragma once

#include "as-types.hpp"

namespace as
{

constexpr real_t PI = real_t(3.14159265358979323846);
constexpr real_t DEG_TO_RAD = PI / real_t(180.0);
constexpr real_t RAD_TO_DEG = real_t(180.0) / PI;

template<typename T>
constexpr T lerp(T t, T v0, T v1);

template<typename T>
constexpr T smooth_step(T t, T v0, T v1);

template<typename T>
constexpr T max(T v0, T v1);

template<typename T>
constexpr T min(T v0, T v1);

template<typename T>
constexpr T clamp(T t, T v0, T v1);

constexpr real_t deg_to_rad(real_t degrees);
constexpr real_t rad_to_deg(real_t radians);

bool equal(
    real_t a, real_t b,
    real_t max_diff = std::numeric_limits<real_t>::epsilon(),
    real_t max_rel_diff = std::numeric_limits<real_t>::epsilon());

} // namespace as

#include "as-math.inl"
