#pragma once

#include "as-math-ops.hpp"

namespace as
{

struct affine_t
{
    affine_t() = default;
    affine_t(const affine_t&) = default;
    affine_t& operator=(const affine_t&) = default;
    affine_t(affine_t&&) noexcept = default;
    affine_t& operator=(affine_t&&) noexcept = default;
    ~affine_t() = default;

    constexpr affine_t(
        const mat33_t& rotation, const vec3_t& position)
        : rotation(rotation), position(position) {}

    mat33_t rotation;
    vec3_t position;
};

#if defined AS_COL_MAJOR
inline const vec3_t operator*(const affine_t& transform, const vec3_t& vec);
#elif defined AS_ROW_MAJOR
inline const vec3_t operator*(const vec3_t& vec, const affine_t& transform);
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR

} // namespace as

#include "as-affine.inl"
