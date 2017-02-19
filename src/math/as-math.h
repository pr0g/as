#pragma once

#include <ASframework/Types/AsTypes.h>

// To get rid of stupid global namespace min and max
// (Probably brought in by a lib at this point - need
// rebuild with NOMINMAX - TODO)
#ifdef min
#undef min
#endif
#ifdef max
#undef max
#endif

namespace as
{

const float PI = 3.14159265f;
const float DEG_TO_RAD = PI / 180.0f;
const float RAD_TO_DEG = 180.0f / PI;

template<typename T>
AS_INLINE T lerp(T v0, T v1, T t)
{
	return (1 - t) * v0 + t * v1;
}

template<typename T>
AS_INLINE T smooth_step(T v0, T v1, T t)
{
	T val = (t * t) * ((T)3 - (T)2 * t);
	return lerp(v0, v1, val);
}

template<typename T>
AS_INLINE T max(T v0, T v1)
{
	return v0 > v1 ? v0 : v1;
}

template<typename T>
AS_INLINE T min(T v0, T v1)
{
	return v0 < v1 ? v0 : v1;
}

template<typename T>
AS_INLINE T clamp(T v0, T v1, T t)
{
	return t <= v0 ? v0 : t >= v1 ? v1 : t;
}

AS_INLINE float degToRad(float degrees)
{
	return degrees * DEG_TO_RAD;
}

AS_INLINE double degToRad(double degrees)
{
	return degrees * (double)DEG_TO_RAD;
}

AS_INLINE float radToDeg(float radians)
{
	return radians * RAD_TO_DEG;
}

AS_INLINE double radToDeg(double radians)
{
	return radians * (double)RAD_TO_DEG;
}

}