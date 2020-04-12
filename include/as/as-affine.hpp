#pragma once

#include "as-mat3.hpp"
#include "as-point.hpp"

namespace as
{

struct affine_t
{
    mat3_t rotation;
    point3_t position;

    affine_t() = default;
    affine_t(const affine_t&) = default;
    affine_t& operator=(const affine_t&) = default;
    affine_t(affine_t&&) noexcept = default;
    affine_t& operator=(affine_t&&) noexcept = default;
    ~affine_t() = default;

    constexpr affine_t(const mat3_t& rotation_, const point3_t& position_);
};

} // namespace as

#include "as-affine.inl"
