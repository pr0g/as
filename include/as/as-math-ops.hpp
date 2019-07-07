#pragma once

#include "as-vec.hpp"
#include "as-mat3.hpp"
#include "as-mat4.hpp"
#include "as-point.hpp"
#include "as-quat.hpp"
#include "as-affine.hpp"

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

template<>
inline real_t dot(const vec3_t& lhs, const vec3_t& rhs);

template<typename T, size_t n>
inline T length_sq(const vec_t<T, n>& vec);

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

} // namespace vec

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

} // namespace vec2

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

} // namespace vec3

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

} // namespace vec4

namespace mat
{

template<typename T, size_t d>
inline T* data(const mat_t<T, d>& mat);

template<typename T, size_t d>
inline const T* const_data(const mat_t<T, d>& mat);

template<typename T, size_t d>
inline mat_t<T, d> from_arr(const T(&data)[d * d]);

template<typename T, size_t d>
inline mat_t<T, d> from_ptr(const T* data);

template<typename T, size_t d>
inline mat_t<T, d> transpose(const mat_t<T, d>& mat);

template<typename T, size_t d>
constexpr inline mat_t<T, d> identity();

template<typename T, size_t d>
inline T determinant(const mat_t<T, d>& mat);

template<typename T, size_t d>
inline mat_t<T, d> inverse(const mat_t<T, d>& mat);

template<typename T, size_t d>
inline mat_t<T, d> gj_inverse(const mat_t<T, d>& mat);

} // namespace mat

namespace mat33
{

constexpr inline size_t rows() { return 3; }
constexpr inline size_t cols() { return 3; }

constexpr inline mat3_t identity();

inline mat3_t from_ptr(const real_t* data);
inline mat3_t from_arr(const real_t(&data)[9]);
constexpr inline mat3_t from_mat44(const mat4_t& transform);

inline mat3_t axis_angle(const vec3_t& axis, real_t radians);
inline mat3_t rotation_xyz(real_t x, real_t y, real_t z);
inline mat3_t rotation_zxy(real_t x, real_t y, real_t z);
inline mat3_t rotation_x(real_t radians);
inline mat3_t rotation_y(real_t radians);
inline mat3_t rotation_z(real_t radians);
inline mat3_t scale(real_t scale);
inline mat3_t scale(const vec3_t& scale);

} // namespace mat33

namespace mat44
{

constexpr size_t rows() { return 4; }
constexpr size_t cols() { return 4; }

constexpr inline mat4_t identity();

inline mat4_t from_ptr(const real_t* data);
inline mat4_t from_arr(const real_t(&data)[16]);

constexpr inline mat4_t from_vec3(const vec3_t& translation);
constexpr inline mat4_t from_mat33(const mat3_t& rotation);
constexpr inline mat4_t from_mat33_vec3(const mat3_t& rotation, const vec3_t& translation);

} // namespace mat44

namespace point
{

inline bool equal(const point2_t& lhs, const point2_t& rhs,
    real_t epsilon = std::numeric_limits<real_t>::epsilon());

inline bool equal(const point3_t& lhs, const point3_t& rhs,
    real_t epsilon = std::numeric_limits<real_t>::epsilon());

} // namespace point

namespace quat
{

constexpr inline quat_t identity() { return { 1.0f, 0.0f, 0.0f, 0.0f }; }

constexpr inline real_t dot(const quat_t& a, const quat_t& b);
constexpr inline real_t length_sq(const quat_t& a);
constexpr inline quat_t conjugate(const quat_t& a);

inline quat_t axis_angle(const vec3_t& axis, real_t radians);
inline quat_t rotation_zxy(real_t x, real_t y, real_t z);
inline real_t length(const quat_t& a);
inline quat_t normalize(const quat_t& a);
inline quat_t inverse(const quat_t& a);
inline vec3_t rotate(const quat_t& q, const vec3_t& v);
inline quat_t slerp(const quat_t& a, const quat_t& b, real_t u);

} // namespace quat

namespace affine
{

inline vec3_t transform_dir(const affine_t& affine, const vec3_t& direction);
inline vec3_t transform_pos(const affine_t& affine, const vec3_t& position);
inline vec3_t inv_transform_dir(const affine_t& affine, const vec3_t& direction);
inline vec3_t inv_transform_pos(const affine_t& affine, const vec3_t& position);

} // namespace affine

} // namespace as

#include "as-math-ops.inl"
