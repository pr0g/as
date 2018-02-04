#pragma once

#include "src/math/as-math-type-ops.hpp"

namespace as
{

struct affine
{
    affine() = default;
    affine(const affine&) = default;
    affine& operator=(const affine&) = default;
    affine(affine&&) noexcept = default;
    affine& operator=(affine&&) noexcept = default;
    ~affine() = default;

    constexpr affine(const m33& rotation, const v3& position)
        : rotation(rotation), position(position) {}

    m33 rotation;
    v3 position;

    inline v3 transform_dir(const v3& direction);
    inline v3 transform_pos(const v3& position);
    inline v3 inv_transform_dir(const v3& direction);
    inline v3 inv_transform_pos(const v3& position);
};

} // namespace as

#include "as-affine.inl"