#pragma once

#include <iterator>

#include "as-affine.hpp"
#include "as-mat3.hpp"
#include "as-mat4.hpp"
#include "as-point.hpp"
#include "as-quat.hpp"
#include "as-vec.hpp"

namespace as
{

namespace vec
{

template<typename T, index_t n>
index_t size(const vec_t<T, n>& vec);

template<typename T, index_t n>
vec_t<T, n> from_arr(const T (&data)[n]);

template<typename T, index_t n>
vec_t<T, n> from_ptr(const T* data);

template<typename T, index_t n>
void to_arr(const vec_t<T, n>& vec, T (&data)[n]);

template<typename T, index_t n>
T dot(const vec_t<T, n>& lhs, const vec_t<T, n>& rhs);

template<>
real_t dot(const vec3_t& lhs, const vec3_t& rhs);

template<typename T, index_t n>
T length_sq(const vec_t<T, n>& vec);

template<typename T, index_t n>
T length(const vec_t<T, n>& vec);

template<typename T, index_t n>
vec_t<T, n> normalize(const vec_t<T, n>& vec);

template<typename T, index_t n>
T normalize_return_length(const vec_t<T, n>& vec, vec_t<T, n>& out);

template<typename T, index_t n>
bool equal(
    const vec_t<T, n>& lhs, const vec_t<T, n>& rhs,
    real_t epsilon = std::numeric_limits<real_t>::epsilon());

template<typename T, index_t n>
vec_t<T, n> min(const vec_t<T, n>& lhs, const vec_t<T, n>& rhs);

template<typename T, index_t n>
T min_elem(const vec_t<T, n>& vec);

template<typename T, index_t n>
vec_t<T, n> max(const vec_t<T, n>& lhs, const vec_t<T, n>& rhs);

template<typename T, index_t n>
T max_elem(const vec_t<T, n>& vec);

template<typename T, index_t n>
vec_t<T, n> abs(const vec_t<T, n>& vec);

template<typename T, index_t n>
vec_t<T, n> clamp(
    const vec_t<T, n>& vec, const vec_t<T, n>& min, const vec_t<T, n>& max);

template<typename T, index_t n>
vec_t<T, n> saturate(const vec_t<T, n>& vec);

template<typename T, index_t n>
vec_t<T, n> lerp(T t, const vec_t<T, n>& v0, const vec_t<T, n>& v1);

template<typename T, index_t n>
vec_t<T, n> select(const vec_t<T, n>& v0, const vec_t<T, n>& v1, bool select0);

} // namespace vec

namespace vec2
{

constexpr vec2_t axis_x();
constexpr vec2_t axis_y();
constexpr vec2_t zero();
constexpr vec2_t one();
constexpr vec2_t max();
constexpr vec2_t min();
vec2_t from_ptr(const real_t* data);
vec2_t from_arr(const real_t (&data)[2]);

real_t wedge(const vec2_t& lhs, const vec2_t& rhs);

} // namespace vec2

namespace vec3
{

constexpr vec3_t axis_x();
constexpr vec3_t axis_y();
constexpr vec3_t axis_z();
constexpr vec3_t zero();
constexpr vec3_t one();
constexpr vec3_t max();
constexpr vec3_t min();
vec3_t from_ptr(const real_t* data);
vec3_t from_arr(const real_t (&data)[3]);

vec3_t cross(const vec3_t& lhs, const vec3_t& rhs);

// note: will not work if dir == +/-world_up
void right_and_up_lh(
    const vec3_t& dir, vec3_t& across, vec3_t& up,
    const vec3_t& world_up = axis_y());

// note: will not work if dir == +/-world_up
void right_and_up_rh(
    const vec3_t& dir, vec3_t& across, vec3_t& up,
    const vec3_t& world_up = axis_y());

} // namespace vec3

namespace vec4
{

constexpr vec4_t axis_x();
constexpr vec4_t axis_y();
constexpr vec4_t axis_z();
constexpr vec4_t axis_w();
constexpr vec4_t zero();
constexpr vec4_t one();
constexpr vec4_t max();
constexpr vec4_t min();
vec4_t from_ptr(const real_t* data);
vec4_t from_arr(const real_t (&data)[4]);

} // namespace vec4

namespace mat
{

template<typename T, index_t d>
T* data(mat_t<T, d>& mat);

template<typename T, index_t d>
const T* const_data(const mat_t<T, d>& mat);

template<typename T, index_t d>
mat_t<T, d> from_arr(const T (&data)[d * d]);

template<typename T, index_t d>
mat_t<T, d> from_ptr(const T* data);

template<typename T, index_t d>
void to_arr(const mat_t<T, d>& mat, T (&data)[d]);

template<typename T, index_t d>
mat_t<T, d> transpose(const mat_t<T, d>& mat);

template<typename T, index_t d>
constexpr mat_t<T, d> identity();

template<typename T, index_t d>
T determinant(const mat_t<T, d>& mat);

template<typename T, index_t d>
mat_t<T, d> inverse(const mat_t<T, d>& mat);

template<typename T, index_t d>
mat_t<T, d> gj_inverse(const mat_t<T, d>& mat);

} // namespace mat

namespace mat3
{

constexpr index_t rows();
constexpr index_t cols();

constexpr mat3_t identity();

mat3_t from_ptr(const real_t* data);
mat3_t from_arr(const real_t (&data)[9]);
constexpr mat3_t from_mat4(const mat4_t& transform);

mat3_t axis_angle(const vec3_t& axis, real_t radians);
mat3_t rotation_xyz(real_t x, real_t y, real_t z);
mat3_t rotation_zxy(real_t x, real_t y, real_t z);
mat3_t rotation_x(real_t radians);
mat3_t rotation_y(real_t radians);
mat3_t rotation_z(real_t radians);
mat3_t scale(real_t scale);
mat3_t scale(const vec3_t& scale);

} // namespace mat3

namespace mat4
{

constexpr index_t rows();
constexpr index_t cols();

constexpr mat4_t identity();

mat4_t from_ptr(const real_t* data);
mat4_t from_arr(const real_t (&data)[16]);

constexpr mat4_t from_vec3(const vec3_t& translation);
constexpr mat4_t from_mat3(const mat3_t& rotation);
constexpr mat4_t from_mat3_vec3(
    const mat3_t& rotation, const vec3_t& translation);

} // namespace mat4

namespace point
{

bool equal(
    const point2_t& lhs, const point2_t& rhs,
    real_t epsilon = std::numeric_limits<real_t>::epsilon());

bool equal(
    const point3_t& lhs, const point3_t& rhs,
    real_t epsilon = std::numeric_limits<real_t>::epsilon());

} // namespace point

namespace quat
{

constexpr quat_t identity();

constexpr real_t dot(const quat_t& a, const quat_t& b);
constexpr real_t length_sq(const quat_t& a);
constexpr quat_t conjugate(const quat_t& a);

quat_t axis_angle(const vec3_t& axis, real_t radians);
quat_t rotation_zxy(real_t x, real_t y, real_t z);
real_t length(const quat_t& a);
quat_t normalize(const quat_t& a);
quat_t inverse(const quat_t& a);
vec3_t rotate(const quat_t& q, const vec3_t& v);
quat_t slerp(const quat_t& a, const quat_t& b, real_t t);

} // namespace quat

namespace affine
{

vec3_t transform_dir(const affine_t& affine, const vec3_t& direction);
point3_t transform_pos(const affine_t& affine, const point3_t& position);
vec3_t inv_transform_dir(const affine_t& affine, const vec3_t& direction);
point3_t inv_transform_pos(const affine_t& affine, const point3_t& position);

} // namespace affine

} // namespace as

#include "as-math-ops.inl"
