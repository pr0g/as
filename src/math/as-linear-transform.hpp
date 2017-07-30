#pragma once

#include "src/core/as-types.hpp"

#include "as-mat.hpp"
#include "as-mat3.hpp"
#include "as-mat4.hpp"
#include "as-vec.hpp"

namespace as
{

struct LinearTransform
{
    LinearTransform() {}
    LinearTransform(m33 rotation, v3 position) : rotation(rotation), position(position) {}

    m33 rotation;
    v3 position;

    AS_INLINE v3 transformDirection(const v3& direction);
    AS_INLINE v3 transformPosition(const v3& position);
    AS_INLINE v3 transformInverseDirection(const v3& direction);
    AS_INLINE v3 transformInversePosition(const v3& position);

//	AS_INLINE const v3& forward() const { return rotation.v.v_2; }
//	AS_INLINE const v3& right() const { return rotation.v.v_0; }
//	AS_INLINE const v3& up() const { return rotation.v.v_1; }
};

AS_INLINE m44 convertTom44(const LinearTransform& linearTransform)
{
    m44 temp;
    // temp.right = v4(linearTransform.right(), 0.0f);
    // temp.up = v4(linearTransform.up(), 0.0f);
    // temp.forward = v4(linearTransform.forward(), 0.0f);
    // temp.position = v4(linearTransform.position, 1.0f);
    return temp;
}

#if defined AS_COL_MAJOR
AS_INLINE v3 operator*(const LinearTransform& transform, const v3& vec)
{
    v3 result = transform.rotation * vec;
    return result + transform.position;
}
#elif defined AS_ROW_MAJOR
AS_INLINE v3 operator*(const v3& vec, const LinearTransform& transform)
{
    v3 result = vec * transform.rotation;
    return result + transform.position;
}
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR

AS_INLINE v3 LinearTransform::transformDirection(const v3& direction)
{
#if defined AS_COL_MAJOR
    return rotation * direction;
#elif defined AS_ROW_MAJOR
    return direction * rotation;
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

AS_INLINE v3 LinearTransform::transformPosition(const v3& position_)
{
#if defined AS_COL_MAJOR
    return rotation * position_ + position;
#elif defined AS_ROW_MAJOR
    return position_ * rotation + position;
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

AS_INLINE v3 LinearTransform::transformInverseDirection(const v3& direction)
{
    m33 invRotation = as::inverse(rotation);
#if defined AS_COL_MAJOR
    return invRotation * direction;
#elif defined AS_ROW_MAJOR
    return direction * invRotation;
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

AS_INLINE v3 LinearTransform::transformInversePosition(const v3& position_)
{
    m33 invRotation = as::inverse(rotation);
#if defined AS_COL_MAJOR
    return invRotation * (position_ - position);
#elif defined AS_ROW_MAJOR
    return (position_ - position) * invRotation;
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

}