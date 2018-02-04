#pragma once

#include "src/math/as-mat3.hpp"
#include "src/math/as-mat4.hpp"

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

    v3 transform_dir(const v3& direction);
    v3 transform_pos(const v3& position);
    v3 inv_transform_dir(const v3& direction);
    v3 inv_transform_pos(const v3& position);
};

#if defined AS_COL_MAJOR
v3 operator*(const affine& transform, const v3& vec)
{
    return transform.rotation * vec + transform.position;
}
#elif defined AS_ROW_MAJOR
v3 operator*(const v3& vec, const affine& transform)
{
    return vec * transform.rotation + transform.position;
}
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR

v3 affine::transform_dir(const v3& direction)
{
#if defined AS_COL_MAJOR
    return rotation * direction;
#elif defined AS_ROW_MAJOR
    return direction * rotation;
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

v3 affine::transform_pos(const v3& position_)
{
#if defined AS_COL_MAJOR
    return rotation * position_ + position;
#elif defined AS_ROW_MAJOR
    return position_ * rotation + position;
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

v3 affine::inv_transform_dir(const v3& direction)
{
    const m33 invRotation = as::mat::inverse(rotation);
#if defined AS_COL_MAJOR
    return invRotation * direction;
#elif defined AS_ROW_MAJOR
    return direction * invRotation;
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

v3 affine::inv_transform_pos(const v3& position_)
{
    const m33 invRotation = as::mat::inverse(rotation);
#if defined AS_COL_MAJOR
    return invRotation * (position_ - position);
#elif defined AS_ROW_MAJOR
    return (position_ - position) * invRotation;
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

}