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

    AS_API constexpr affine_t(
        const mat3_t& rotation_, const point3_t& position_)
        : rotation(rotation_), position(position_) {}

    mat3_t rotation;
    point3_t position;
};

} // namespace as
