#pragma once

#include "as-types.hpp"

namespace as
{

constexpr real_t PI = 3.14159265358979323846f;
constexpr real_t DEG_TO_RAD = PI / 180.0f;
constexpr real_t RAD_TO_DEG = 180.0f / PI;

template<typename T>
AS_API T lerp(T t, T v0, T v1);

template<typename T>
AS_API T smooth_step(T t, T v0, T v1);

template<typename T>
AS_API T max(T v0, T v1);

template<typename T>
AS_API T min(T v0, T v1);

template<typename T>
AS_API T clamp(T t, T v0, T v1);

AS_API real_t deg_to_rad(real_t degrees);
AS_API real_t rad_to_deg(real_t radians);

AS_API bool equal(
    real_t a, real_t b,
    real_t max_diff = std::numeric_limits<real_t>::epsilon(),
    real_t max_rel_diff = std::numeric_limits<real_t>::epsilon());

} // namespace as

#include "as-math.inl"
