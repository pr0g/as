#pragma once

#include "src/core/as-types.hpp"

namespace as
{

constexpr real PI = 3.14159265358979323846f;
constexpr real DEG_TO_RAD = PI / 180.0f;
constexpr real RAD_TO_DEG = 180.0f / PI;

template<typename T>
inline T lerp(T t, T v0, T v1);

template<typename T>
inline T smooth_step(T t, T v0, T v1);

template<typename T>
inline T max(T v0, T v1);

template<typename T>
inline T min(T v0, T v1);

template<typename T>
inline T clamp(T t, T v0, T v1);

inline real deg_to_rad(real degrees);
inline real rad_to_deg(real radians);

inline bool equal(
    real a, real b,
    real max_diff = std::numeric_limits<real>::epsilon(),
    real max_rel_diff = std::numeric_limits<real>::epsilon());

} // namespace as

#include "as-math.inl"