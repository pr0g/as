#pragma once

#include "as-mat3.hpp"
#include "as-point.hpp"

namespace as
{

struct affine_t
{
    affine_t() = default;
    constexpr affine_t(const point3_t& position_);
    constexpr affine_t(
        const mat3_t& rotation_,
        const point3_t& position_ = as::point3_t::zero());

    mat3_t rotation;
    point3_t position;
};

} // namespace as

#include "as-affine.inl"
