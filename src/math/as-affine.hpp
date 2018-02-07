#pragma once

#include "src/math/as-math-type-ops.hpp"

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

    constexpr affine_t(const mat33_t& rotation, const vec3_t& position)
        : rotation(rotation), position(position) {}

    mat33_t rotation;
    vec3_t position;

    inline vec3_t transform_dir(const vec3_t& direction);
    inline vec3_t transform_pos(const vec3_t& position);
    inline vec3_t inv_transform_dir(const vec3_t& direction);
    inline vec3_t inv_transform_pos(const vec3_t& position);
};

} // namespace as

#include "as-affine.inl"