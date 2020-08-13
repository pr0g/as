#pragma once

#include <iterator>
#include <numeric>
#include <tuple>

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

template<typename T, index_t d>
constexpr index_t size(const vec_t<T, d>& vec);

template<typename T, index_t d>
vec_t<T, d> from_arr(const T (&data)[d]);

template<typename T, index_t d>
vec_t<T, d> from_ptr(const T* data);

template<typename T, index_t d>
void to_arr(const vec_t<T, d>& vec, T (&data)[d]);

template<typename T, index_t d>
constexpr T dot(const vec_t<T, d>& lhs, const vec_t<T, d>& rhs);

template<>
constexpr real_t dot(const vec3_t& lhs, const vec3_t& rhs);

template<typename T, index_t d>
constexpr T length_sq(const vec_t<T, d>& vec);

template<typename T, index_t d>
T length(const vec_t<T, d>& vec);

template<typename T, index_t d>
vec_t<T, d> normalize(const vec_t<T, d>& vec);

template<typename T, index_t d>
std::tuple<vec_t<T, d>, T> normalize_with_length(const vec_t<T, d>& vec);

template<typename T, index_t d>
bool equal(
    const vec_t<T, d>& lhs, const vec_t<T, d>& rhs,
    real_t epsilon = std::numeric_limits<real_t>::epsilon());

template<typename T, index_t d>
vec_t<T, d> min(const vec_t<T, d>& lhs, const vec_t<T, d>& rhs);

template<typename T, index_t d>
constexpr T min_elem(const vec_t<T, d>& vec);

template<typename T, index_t d>
vec_t<T, d> max(const vec_t<T, d>& lhs, const vec_t<T, d>& rhs);

template<typename T, index_t d>
constexpr T max_elem(const vec_t<T, d>& vec);

template<typename T, index_t d>
vec_t<T, d> abs(const vec_t<T, d>& vec);

template<typename T, index_t d>
vec_t<T, d> clamp(
    const vec_t<T, d>& vec, const vec_t<T, d>& min, const vec_t<T, d>& max);

template<typename T, index_t d>
vec_t<T, d> saturate(const vec_t<T, d>& vec);

template<typename T, index_t d>
vec_t<T, d> lerp(T t, const vec_t<T, d>& v0, const vec_t<T, d>& v1);

template<typename T, index_t d>
constexpr vec_t<T, d> select(
    const vec_t<T, d>& v0, const vec_t<T, d>& v1, bool select0);

template<typename T, index_t d>
vec_t<T, d> floor(const vec_t<T, d>& vec);

template<typename T, index_t d>
vec_t<T, d> ceil(const vec_t<T, d>& vec);

template<typename T, index_t d>
vec_t<T, d> round(const vec_t<T, d>& vec);

template<typename T, index_t d>
vec_t<T, d> snap(const vec_t<T, d>& vec, T step);

} // namespace vec

namespace vec2
{

template<typename T>
vec_t<T, 2> from_arr(const T (&data)[2]);

template<typename T>
vec_t<T, 2> from_ptr(const T* data);

template<typename T>
constexpr vec_t<T, 2> from_vec3(const vec_t<T, 3>& vec);

template<typename T>
constexpr vec_t<T, 2> from_vec4(const vec_t<T, 4>& vec);

template<typename T>
constexpr T wedge(const vec_t<T, 2>& lhs, const vec_t<T, 2>& rhs);

} // namespace vec2

namespace vec3
{

template<typename T>
vec_t<T, 3> from_arr(const T (&data)[3]);

template<typename T>
vec_t<T, 3> from_ptr(const T* data);

template<typename T>
constexpr vec_t<T, 3> from_vec2(const vec_t<T, 2>& vec, T z = T(0.0));

template<typename T>
constexpr vec_t<T, 3> from_vec4(const vec_t<T, 4>& vec);

template<typename T>
constexpr vec_t<T, 3> cross(const vec_t<T, 3>& lhs, const vec_t<T, 3>& rhs);

// note: will not work if dir == +/-world_up
template<typename T>
void right_and_up_lh(
    const vec_t<T, 3>& dir, vec_t<T, 3>& across, vec_t<T, 3>& up,
    const vec_t<T, 3>& world_up = vec_t<T, 3>::axis_y());

// note: will not work if dir == +/-world_up
template<typename T>
void right_and_up_rh(
    const vec_t<T, 3>& dir, vec_t<T, 3>& across, vec_t<T, 3>& up,
    const vec_t<T, 3>& world_up = vec_t<T, 3>::axis_y());

} // namespace vec3

namespace vec4
{

template<typename T>
vec_t<T, 4> from_arr(const T (&data)[4]);

template<typename T>
vec_t<T, 4> from_ptr(const T* data);

template<typename T>
constexpr vec_t<T, 4> from_vec2(
    const vec_t<T, 2>& vec, T z = T(0.0), T w = T(0.0));

template<typename T>
constexpr vec_t<T, 4> from_vec3(const vec_t<T, 3>& vec, T w = T(0.0));

vec4_t from_point3(const point3_t& point);

} // namespace vec4

namespace mat
{

constexpr index_t rc(index_t r, index_t c, index_t d);

template<typename T, index_t d>
vec_t<T, d> row(const mat_t<T, d>& mat, index_t r);

template<typename T, index_t d>
vec_t<T, d> col(const mat_t<T, d>& mat, index_t c);

template<typename T, index_t d>
constexpr void row(mat_t<T, d>& mat, index_t r, const vec_t<T, d>& row);

template<typename T, index_t d>
constexpr void col(mat_t<T, d>& mat, index_t c, const vec_t<T, d>& col);

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
bool equal(
    const mat_t<T, d>& lhs, const mat_t<T, d>& rhs,
    real_t epsilon = std::numeric_limits<real_t>::epsilon());

template<typename T, index_t d>
mat_t<T, d> transpose(const mat_t<T, d>& mat);

template<typename T, index_t d>
T determinant(const mat_t<T, d>& mat);

template<typename T, index_t d>
mat_t<T, d> inverse(const mat_t<T, d>& mat);

template<typename T, index_t d>
mat_t<T, d> gj_inverse(const mat_t<T, d>& mat);

// lhs is performed first, then rhs
// col major - result = rhs * lhs;
// row major - result = lhs * rhs;
template<typename T, index_t d>
mat_t<T, d> mul(const mat_t<T, d>& lhs, const mat_t<T, d>& rhs);

} // namespace mat

namespace mat3
{

constexpr index_t rc(index_t r, index_t c);

template<typename T>
constexpr vec_t<T, 3> row0(const mat_t<T, 3>& mat);

template<typename T>
constexpr vec_t<T, 3> row1(const mat_t<T, 3>& mat);

template<typename T>
constexpr vec_t<T, 3> row2(const mat_t<T, 3>& mat);

template<typename T>
constexpr vec_t<T, 3> col0(const mat_t<T, 3>& mat);

template<typename T>
constexpr vec_t<T, 3> col1(const mat_t<T, 3>& mat);

template<typename T>
constexpr vec_t<T, 3> col2(const mat_t<T, 3>& mat);

template<typename T>
constexpr void row0(mat_t<T, 3>& mat, const vec_t<T, 3>& row);

template<typename T>
constexpr void row1(mat_t<T, 3>& mat, const vec_t<T, 3>& row);

template<typename T>
constexpr void row2(mat_t<T, 3>& mat, const vec_t<T, 3>& row);

template<typename T>
constexpr void col0(mat_t<T, 3>& mat, const vec_t<T, 3>& col);

template<typename T>
constexpr void col1(mat_t<T, 3>& mat, const vec_t<T, 3>& col);

template<typename T>
constexpr void col2(mat_t<T, 3>& mat, const vec_t<T, 3>& col);

template<typename T>
constexpr vec_t<T, 3> basis_x(const mat_t<T, 3>& mat);

template<typename T>
constexpr vec_t<T, 3> basis_y(const mat_t<T, 3>& mat);

template<typename T>
constexpr vec_t<T, 3> basis_z(const mat_t<T, 3>& mat);

template<typename T>
constexpr void basis_x(mat_t<T, 3>& mat, const vec_t<T, 3>& basis);

template<typename T>
constexpr void basis_y(mat_t<T, 3>& mat, const vec_t<T, 3>& basis);

template<typename T>
constexpr void basis_z(mat_t<T, 3>& mat, const vec_t<T, 3>& basis);

template<typename T>
mat_t<T, 3> from_arr(const T (&data)[9]);

template<typename T>
mat_t<T, 3> from_ptr(const T* data);

template<typename T>
constexpr mat_t<T, 3> from_mat4(const mat_t<T, 4>& transform);

mat3_t axis_angle(const vec3_t& axis, real_t radians);

mat3_t rotation_xyz(real_t x, real_t y, real_t z);

mat3_t rotation_zxy(real_t x, real_t y, real_t z);

mat3_t rotation_x(real_t radians);

mat3_t rotation_y(real_t radians);

mat3_t rotation_z(real_t radians);

constexpr mat3_t scale(real_t scale);

constexpr mat3_t scale(const vec3_t& scale);

constexpr mat3_t from_quat(const quat_t& quat);

} // namespace mat3

namespace mat4
{

constexpr index_t rc(index_t r, index_t c);

template<typename T>
constexpr vec_t<T, 4> row0(const mat_t<T, 4>& mat);

template<typename T>
constexpr vec_t<T, 4> row1(const mat_t<T, 4>& mat);

template<typename T>
constexpr vec_t<T, 4> row2(const mat_t<T, 4>& mat);

template<typename T>
constexpr vec_t<T, 4> row3(const mat_t<T, 4>& mat);

template<typename T>
constexpr vec_t<T, 4> col0(const mat_t<T, 4>& mat);

template<typename T>
constexpr vec_t<T, 4> col1(const mat_t<T, 4>& mat);

template<typename T>
constexpr vec_t<T, 4> col2(const mat_t<T, 4>& mat);

template<typename T>
constexpr vec_t<T, 4> col3(const mat_t<T, 4>& mat);

template<typename T>
constexpr void row0(const mat_t<T, 4>& mat, const vec_t<T, 4>& row);

template<typename T>
constexpr void row1(const mat_t<T, 4>& mat, const vec_t<T, 4>& row);

template<typename T>
constexpr void row2(const mat_t<T, 4>& mat, const vec_t<T, 4>& row);

template<typename T>
constexpr void row3(const mat_t<T, 4>& mat, const vec_t<T, 4>& row);

template<typename T>
constexpr void col0(const mat_t<T, 4>& mat, const vec_t<T, 4>& col);

template<typename T>
constexpr void col1(const mat_t<T, 4>& mat, const vec_t<T, 4>& col);

template<typename T>
constexpr void col2(const mat_t<T, 4>& mat, const vec_t<T, 4>& col);

template<typename T>
constexpr void col3(const mat_t<T, 4>& mat, const vec_t<T, 4>& col);

template<typename T>
constexpr vec_t<T, 4> basis_x(const mat_t<T, 4>& mat);

template<typename T>
constexpr vec_t<T, 4> basis_y(const mat_t<T, 4>& mat);

template<typename T>
constexpr vec_t<T, 4> basis_z(const mat_t<T, 4>& mat);

template<typename T>
constexpr vec_t<T, 4> translation(const mat_t<T, 4>& mat);

template<typename T>
constexpr void basis_x(mat_t<T, 4>& mat, const vec_t<T, 4>& basis);

template<typename T>
constexpr void basis_y(mat_t<T, 4>& mat, const vec_t<T, 4>& basis);

template<typename T>
constexpr void basis_z(mat_t<T, 4>& mat, const vec_t<T, 4>& basis);

template<typename T>
constexpr void translation(mat_t<T, 4>& mat, const vec_t<T, 4>& translation);

template<typename T>
mat_t<T, 4> from_arr(const T (&data)[16]);

template<typename T>
mat_t<T, 4> from_ptr(const T* data);

template<typename T>
constexpr mat_t<T, 4> from_vec3(const vec_t<T, 3>& translation);

template<typename T>
constexpr mat_t<T, 4> from_mat3(const mat_t<T, 3>& rotation);

template<typename T>
constexpr mat_t<T, 4> from_mat3_vec3(
    const mat_t<T, 3>& rotation, const vec_t<T, 3>& translation);

constexpr mat4_t from_affine(const affine_t& affine);

template<typename T>
constexpr mat_t<T, 4> shear_x(T y, T z);

template<typename T>
constexpr mat_t<T, 4> shear_y(T x, T z);

template<typename T>
constexpr mat_t<T, 4> shear_z(T x, T y);

} // namespace mat4

namespace point
{

bool equal(
    const point2_t& lhs, const point2_t& rhs,
    real_t epsilon = std::numeric_limits<real_t>::epsilon());

bool equal(
    const point3_t& lhs, const point3_t& rhs,
    real_t epsilon = std::numeric_limits<real_t>::epsilon());

template<typename point_t>
point_t average(const point_t* points, index_t count);

template<typename... points_t>
auto average_fold(points_t&&... points);

} // namespace point

namespace quat
{

constexpr real_t dot(const quat_t& lhs, const quat_t& rhs);

constexpr real_t length_sq(const quat_t& quat);

constexpr quat_t conjugate(const quat_t& quat);

quat_t axis_angle(const vec3_t& axis, real_t radians);

quat_t rotation_zxy(real_t x, real_t y, real_t z);

real_t length(const quat_t& quat);

quat_t normalize(const quat_t& quat);

quat_t inverse(const quat_t& quat);

vec3_t rotate(const quat_t& quat, const vec3_t& v);

quat_t slerp(const quat_t& lhs, const quat_t& rhs, real_t t);

quat_t from_mat3(const mat3_t& mat);

} // namespace quat

namespace affine
{

void to_arr(const affine_t& affine, real_t (&data)[12]);

affine_t from_arr(const real_t (&data)[12]);

affine_t from_ptr(const real_t* data);

affine_t from_mat4(const mat4_t& mat);

affine_t from_mat3(const mat3_t& mat);

affine_t from_point3(const point3_t& point);

affine_t mul(const affine_t& lhs, const affine_t& rhs);

affine_t inverse(const affine_t& affine);

vec3_t transform_dir(const affine_t& affine, const vec3_t& direction);

point3_t transform_pos(const affine_t& affine, const point3_t& position);

vec3_t inv_transform_dir(const affine_t& affine, const vec3_t& direction);

point3_t inv_transform_pos(const affine_t& affine, const point3_t& position);

} // namespace affine

} // namespace as

#include "as-math-ops.inl"
