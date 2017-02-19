#pragma once

#include <ASframework/Types/AsTypes.h>
#include <ASframework/Maths/AsMat.h>
#include <ASframework/Maths/AsVec.h>

namespace as
{

struct LinearTransform
{
	LinearTransform() {}
	LinearTransform(m33 rotation, v3 position) : rotation_(rotation), position_(position) {}

	m33 rotation_;
	v3 position_;

	AS_INLINE v3 transformDirection(const v3& direction);
	AS_INLINE v3 transformPosition(const v3& position);
	AS_INLINE v3 transformInverseDirection(const v3& direction);
	AS_INLINE v3 transformInversePosition(const v3& position);

	AS_INLINE const v3& forward() const { return rotation_.forward; }
	AS_INLINE const v3& right() const { return rotation_.right; }
	AS_INLINE const v3& up() const { return rotation_.up; }
};

AS_INLINE m44 convertTom44(const LinearTransform& linearTransform)
{
	m44 temp;
	temp.right = make_v4(linearTransform.right(), 0.0f);
	temp.up = make_v4(linearTransform.up(), 0.0f);
	temp.forward = make_v4(linearTransform.forward(), 0.0f);
	temp.position = make_v4(linearTransform.position_, 1.0f);
	return temp;
}

AS_INLINE v3 operator*(const LinearTransform& transform, const v3& vec)
{
	v3 result = transform.rotation_ * vec;
	return result + transform.position_;
}

AS_INLINE v3 operator*(const v3& vec, const LinearTransform& transform)
{
	v3 result = vec * transform.rotation_;
	return result + transform.position_;
}

AS_INLINE v3 LinearTransform::transformDirection(const v3& direction)
{
#if defined AS_COL_MAJOR
	return rotation_ * direction;
#elif defined AS_ROW_MAJOR
	return direction * rotation_;
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

AS_INLINE v3 LinearTransform::transformPosition(const v3& position)
{
#if defined AS_COL_MAJOR
	return rotation_ * position + position_;
#elif defined AS_ROW_MAJOR
	return position * rotation_ + position_;
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

AS_INLINE v3 LinearTransform::transformInverseDirection(const v3& direction)
{
	m33 invRotation = as::inverse(rotation_);
#if defined AS_COL_MAJOR
	return invRotation * direction;
#elif defined AS_ROW_MAJOR
	return direction * invRotation;
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

AS_INLINE v3 LinearTransform::transformInversePosition(const v3& position)
{
	m33 invRotation = as::inverse(rotation_);
#if defined AS_COL_MAJOR
	return invRotation * (position - position_);
#elif defined AS_ROW_MAJOR
	return (position - position_) * invRotation;
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

}