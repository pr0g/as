#pragma once

#include "as-vec.hpp"
#include "as-mat3.hpp"
#include "as-mat4.hpp"
#include "as-point.hpp"
#include "as-quat.hpp"

namespace as
{

namespace vec
{

template<typename T, size_t n>
inline size_t size(vec_t<T, n>& vec);

template<typename T, size_t n>
inline T* data(vec_t<T, n>& vec);

template<typename T, size_t n>
inline const T* const_data(const vec_t<T, n>& vec);

template<typename T, size_t n>
inline vec_t<T, n> from_arr(const T(&data)[n]);

template<typename T, size_t n>
inline vec_t<T, n> from_ptr(const T* data);

template<typename T, size_t n>
inline T dot(const vec_t<T, n>& lhs, const vec_t<T, n>& rhs);

template<typename T, size_t n>
inline T length_squared(const vec_t<T, n>& vec);

template<typename T, size_t n>
inline T length(const vec_t<T, n>& vec);

template<typename T, size_t n>
inline vec_t<T, n> normalize(const vec_t<T, n>& vec);

template<typename T, size_t n>
inline T normalize_return_length(const vec_t<T, n>& vec, vec_t<T, n>& out);

template<typename T, size_t n>
inline bool equal(const vec_t<T, n>& lhs, const vec_t<T, n>& rhs, real_t epsilon = std::numeric_limits<real_t>::epsilon());

template<typename T, size_t n>
inline vec_t<T, n> min(const vec_t<T, n>& lhs, const vec_t<T, n>& rhs);

template<typename T, size_t n>
inline T min_elem(const vec_t<T, n>& vec);

template<typename T, size_t n>
inline vec_t<T, n> max(const vec_t<T, n>& lhs, const vec_t<T, n>& rhs);

template<typename T, size_t n>
inline T max_elem(const vec_t<T, n>& vec);

template<typename T, size_t n>
inline vec_t<T, n> abs(const vec_t<T, n>& vec);

template<typename T, size_t n>
inline vec_t<T, n> clamp(const vec_t<T, n>& vec, const vec_t<T, n>& min, const vec_t<T, n>& max);

template<typename T, size_t n>
inline vec_t<T, n> saturate(const vec_t<T, n>& vec);

template<typename T, size_t n>
inline vec_t<T, n> lerp(T t, const vec_t<T, n>& v0, const vec_t<T, n>& v1);

template<typename T, size_t n>
inline vec_t<T, n> select(const vec_t<T, n>& v0, const vec_t<T, n>& v1, bool select0);

}

namespace vec2
{

constexpr inline vec2_t axis_x() { return { 1.0f, 0.0f }; }
constexpr inline vec2_t axis_y() { return { 0.0f, 1.0f }; }
constexpr inline vec2_t zero() { return { 0.0f, 0.0f }; }
constexpr inline vec2_t one() { return { 1.0f, 1.0f }; }
constexpr inline vec2_t max() { return { REAL_MAX, REAL_MAX }; }
constexpr inline vec2_t min() { return { REAL_MIN, REAL_MIN }; }
inline vec2_t from_ptr(const real_t* data);
inline vec2_t from_arr(const real_t(&data)[2]);

inline real_t wedge(const vec2_t& lhs, const vec2_t& rhs);

}

namespace vec3
{

constexpr inline vec3_t axis_x() { return { 1.0f, 0.0f, 0.0f }; }
constexpr inline vec3_t axis_y() { return { 0.0f, 1.0f, 0.0f }; }
constexpr inline vec3_t axis_z() { return { 0.0f, 0.0f, 1.0f }; }
constexpr inline vec3_t zero() { return { 0.0f, 0.0f, 0.0f }; }
constexpr inline vec3_t one() { return { 1.0f, 1.0f, 1.0f }; }
constexpr inline vec3_t max() { return { REAL_MAX, REAL_MAX, REAL_MAX }; }
constexpr inline vec3_t min() { return { REAL_MIN, REAL_MIN, REAL_MIN }; }
inline vec3_t from_ptr(const real_t* data);
inline vec3_t from_arr(const real_t(&data)[3]);

inline vec3_t cross(const vec3_t& lhs, const vec3_t& rhs);

// note: will not work if dir == +/-world_up
inline void right_and_up_lh(const vec3_t& dir, vec3_t& across, vec3_t& up, const vec3_t& world_up = axis_y());

// note: will not work if dir == +/-world_up
inline void right_and_up_rh(const vec3_t& dir, vec3_t& across, vec3_t& up, const vec3_t& world_up = axis_y());

}

namespace vec4
{

constexpr inline vec4_t axis_x() { return { 1.0f, 0.0f, 0.0f, 0.0f }; }
constexpr inline vec4_t axis_y() { return { 0.0f, 1.0f, 0.0f, 0.0f }; }
constexpr inline vec4_t axis_z() { return { 0.0f, 0.0f, 1.0f, 0.0f }; }
constexpr inline vec4_t axis_w() { return { 0.0f, 0.0f, 0.0f, 1.0f }; }
constexpr inline vec4_t zero() { return { 0.0f, 0.0f, 0.0f, 0.0f }; }
constexpr inline vec4_t one() { return { 1.0f, 1.0f, 1.0f, 1.0f }; }
constexpr inline vec4_t max() { return { REAL_MAX, REAL_MAX, REAL_MAX, REAL_MAX }; }
constexpr inline vec4_t min() { return { REAL_MIN, REAL_MIN, REAL_MIN, REAL_MIN }; }
inline vec4_t from_ptr(const real_t* data);
inline vec4_t from_arr(const real_t(&data)[4]);

}

namespace mat
{

template<typename T, size_t r, size_t c>
inline T* data(const mat_t<T, r, c>& mat);

template<typename T, size_t r, size_t c>
inline const T* const_data(const mat_t<T, r, c>& mat);

template<typename T, size_t r, size_t c>
inline mat_t<T, r, c> from_arr(const T(&data)[r * c]);

template<typename T, size_t r, size_t c>
inline mat_t<T, r, c> from_ptr(const T* data);

template<typename T, size_t r, size_t c>
inline mat_t<T, r, c> transpose(const mat_t<T, r, c>& mat);

template<typename T, size_t cr>
constexpr inline mat_t<T, cr, cr> identity();

template<typename T, size_t cr>
inline T determinant(const mat_t<T, cr, cr>& mat);

template<typename T, size_t cr>
inline mat_t<T, cr, cr> inverse(const mat_t<T, cr, cr>& mat);

template<typename T, size_t cr>
inline mat_t<T, cr, cr> gj_inverse(const mat_t<T, cr, cr>& mat);

}

namespace mat33
{

constexpr inline size_t rows() { return 3; }
constexpr inline size_t cols() { return 3; }

constexpr inline mat33_t identity();

inline mat33_t from_ptr(const real_t* data);
inline mat33_t from_arr(const real_t(&data)[9]);
constexpr inline mat33_t from_mat44(const mat44_t& transform);

inline mat33_t axis_angle(const vec3_t& axis, real_t radians);
inline mat33_t rotation_xyz(real_t x, real_t y, real_t z);
inline mat33_t rotation_zxy(real_t x, real_t y, real_t z);
inline mat33_t rotation_x(real_t radians);
inline mat33_t rotation_y(real_t radians);
inline mat33_t rotation_z(real_t radians);

}

namespace mat44
{

constexpr size_t rows() { return 4; }
constexpr size_t cols() { return 4; }

constexpr inline mat44_t identity();

inline mat44_t from_ptr(const real_t* data);
inline mat44_t from_arr(const real_t(&data)[16]);

constexpr inline mat44_t from_vec3(const vec3_t& translation);
constexpr inline mat44_t from_mat33(const mat33_t& rotation);
constexpr inline mat44_t from_mat33_vec3(const mat33_t& rotation, const vec3_t& translation);

}

namespace point
{

inline bool equal(const point2_t& lhs, const point2_t& rhs,
    real_t epsilon = std::numeric_limits<real_t>::epsilon());

inline bool equal(const point3_t& lhs, const point3_t& rhs,
    real_t epsilon = std::numeric_limits<real_t>::epsilon());

}

namespace quat
{

constexpr inline quat_t identity() { return { 1.0f, 0.0f, 0.0f, 0.0f }; }

constexpr inline real_t dot(const quat_t& a, const quat_t& b);
constexpr inline real_t length_squared(const quat_t& a);
constexpr inline quat_t conjugate(const quat_t& a);

inline quat_t axis_angle(const vec3_t& axis, real_t radians);
inline quat_t rotation_zxy(real_t x, real_t y, real_t z);
inline real_t length(const quat_t& a);
inline quat_t normalize(const quat_t& a);
inline quat_t inverse(const quat_t& a);
inline vec3_t rotate(const quat_t& q, const vec3_t& v);
inline quat_t slerp(const quat_t& a, const quat_t& b, real_t u);

}

} // namespace as

#include "as-math-type-ops.inl"