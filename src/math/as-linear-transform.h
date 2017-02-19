#pragma once

#include <ASframework/Types/AsTypes.h>
#include <ASframework/Maths/AsMat.h>
#include <ASframework/Maths/AsVec.h>

namespace as
{

struct LinearTransform
{
	LinearTransform() {}
	LinearTransform(float33 rotation, float3 position) : rotation_(rotation), position_(position) {}

	float33 rotation_;
	float3 position_;

	AS_INLINE float3 transformDirection(const float3& direction);
	AS_INLINE float3 transformPosition(const float3& position);
	AS_INLINE float3 transformInverseDirection(const float3& direction);
	AS_INLINE float3 transformInversePosition(const float3& position);

	AS_INLINE const float3& forward() const { return rotation_.forward; }
	AS_INLINE const float3& right() const { return rotation_.right; }
	AS_INLINE const float3& up() const { return rotation_.up; }
};

AS_INLINE float44 convertToFloat44(const LinearTransform& linearTransform)
{
	float44 temp;
	temp.right = make_float4(linearTransform.right(), 0.0f);
	temp.up = make_float4(linearTransform.up(), 0.0f);
	temp.forward = make_float4(linearTransform.forward(), 0.0f);
	temp.position = make_float4(linearTransform.position_, 1.0f);
	return temp;
}

AS_INLINE float3 operator*(const LinearTransform& transform, const float3& vec)
{
	float3 result = transform.rotation_ * vec;
	return result + transform.position_;
}

AS_INLINE float3 operator*(const float3& vec, const LinearTransform& transform)
{
	float3 result = vec * transform.rotation_;
	return result + transform.position_;
}

AS_INLINE float3 LinearTransform::transformDirection(const float3& direction)
{
#if defined AS_COL_MAJOR
	return rotation_ * direction;
#elif defined AS_ROW_MAJOR
	return direction * rotation_;
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

AS_INLINE float3 LinearTransform::transformPosition(const float3& position)
{
#if defined AS_COL_MAJOR
	return rotation_ * position + position_;
#elif defined AS_ROW_MAJOR
	return position * rotation_ + position_;
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

AS_INLINE float3 LinearTransform::transformInverseDirection(const float3& direction)
{
	float33 invRotation = as::inverse(rotation_);
#if defined AS_COL_MAJOR
	return invRotation * direction;
#elif defined AS_ROW_MAJOR
	return direction * invRotation;
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

AS_INLINE float3 LinearTransform::transformInversePosition(const float3& position)
{
	float33 invRotation = as::inverse(rotation_);
#if defined AS_COL_MAJOR
	return invRotation * (position - position_);
#elif defined AS_ROW_MAJOR
	return (position - position_) * invRotation;
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

}