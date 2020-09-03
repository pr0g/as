//! \file
//! as-math-ops

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

//! Encapsulates all generic vec_t related functionality.
namespace vec
{

//! Returns the number of elements in the vector.
//! \note This is equivalent with `d`, the dimension.
template<typename T, index_t d>
constexpr index_t size(const vec_t<T, d>& vec);

//! Creates a vector from a fixed size array of the same type and dimension.
template<typename T, index_t d>
vec_t<T, d> from_arr(const T (&data)[d]);

//! Creates a vector from a pointer to the beginning of an array of the same
//! type.
//! \warning Be very careful when using this function. Ensure that the array
//! used to initialize the vector is at least as big as the size of the vector.
//! Undefined behaviour may be invoked by reading memory out of bounds if not.
template<typename T, index_t d>
vec_t<T, d> from_ptr(const T* data);

//! Writes the values stored in the vector to an array of the same type and
//! dimension.
template<typename T, index_t d>
void to_arr(const vec_t<T, d>& vec, T (&data)[d]);

//! Returns the dot product of two vectors.
//! \note Result is equivalent to: `|lhs| * |rhs| * cos(θ)`
//! \note Result is positive for acute angles, negative for obtuse angles and
//! zero for right angles (vectors that are perpendicular/orthogonal).
template<typename T, index_t d>
constexpr T dot(const vec_t<T, d>& lhs, const vec_t<T, d>& rhs);

//! Returns the dot product of two vector threes.
template<>
constexpr real_t dot(const vec3_t& lhs, const vec3_t& rhs);

//! Returns the length squared of a vector.
template<typename T, index_t d>
constexpr T length_sq(const vec_t<T, d>& vec);

//! Returns the length of a vector.
template<typename T, index_t d>
T length(const vec_t<T, d>& vec);

//! Returns the input vector with unit length.
template<typename T, index_t d>
vec_t<T, d> normalize(const vec_t<T, d>& vec);

//! Returns the normalized vector (unit length) along with the length of the
//! input vector.
//! \note This can be useful to use instead of having to call `normalize` and
//! `length` separately (reduces repeated work).
template<typename T, index_t d>
std::tuple<vec_t<T, d>, T> normalize_and_length(const vec_t<T, d>& vec);

//! Returns if two vectors are the same as each other (within a certain
//! tolerance).
template<typename T, index_t d>
bool equal(
    const vec_t<T, d>& lhs, const vec_t<T, d>& rhs,
    real_t epsilon = std::numeric_limits<real_t>::epsilon());

//! Performs a `min` on each element of the two vectors, returning the
//! smallest value at each element.
//! ```{.cpp}
//! min((2, 4, 6), (3, 8, 1)) = (2, 4, 1)
//! ```
template<typename T, index_t d>
vec_t<T, d> min(const vec_t<T, d>& lhs, const vec_t<T, d>& rhs);

//! Returns the smallest element in the vector.
template<typename T, index_t d>
constexpr T min_elem(const vec_t<T, d>& vec);

//! Performs a `max` on each element of the two vectors, returning the
//! largest value at each element.
//! ```{.cpp}
//! min((2, 4, 6), (3, 8, 1)) = (3, 8, 6)
//! ```
template<typename T, index_t d>
vec_t<T, d> max(const vec_t<T, d>& lhs, const vec_t<T, d>& rhs);

//! Returns the largest element in the vector.
template<typename T, index_t d>
constexpr T max_elem(const vec_t<T, d>& vec);

//! Returns a vector with the absolute value of each element of the input vector.
//! ```{.cpp}
//! abs((-1, 5, -3)) = (1, 5, 3)
//! ```
template<typename T, index_t d>
vec_t<T, d> abs(const vec_t<T, d>& vec);

//! Returns a vector where each element falls within the range `min` and `max`.
template<typename T, index_t d>
vec_t<T, d> clamp(
    const vec_t<T, d>& vec, const vec_t<T, d>& min, const vec_t<T, d>& max);

//! Returns a vector with each element clamped within the `0-1` range.
template<typename T, index_t d>
vec_t<T, d> saturate(const vec_t<T, d>& vec);

//! Returns a linearly interpolated vector between `begin` and `end`.
//! \param t The amount of interpolation between `begin` and `end`. Must be in
//! the range `[0-1]`.
//! \param begin The vector to interpolate from.
//! \param end The vector to interpolate to.
template<typename T, index_t d>
vec_t<T, d> lerp(T t, const vec_t<T, d>& begin, const vec_t<T, d>& end);

//! Returns `v0` if `select0` is true, otherwise `v1`.
template<typename T, index_t d>
constexpr vec_t<T, d> select(
    const vec_t<T, d>& v0, const vec_t<T, d>& v1, bool select0);

//! Returns a vector with each element being rounded down to the nearest whole
//! number.
template<typename T, index_t d>
vec_t<T, d> floor(const vec_t<T, d>& vec);

//! Returns a vector with each element being rounded up to the nearest whole
//! number.
template<typename T, index_t d>
vec_t<T, d> ceil(const vec_t<T, d>& vec);

//! Returns a vector with each element being rounded toward to the nearest whole
//! number.
//! \note Halfway values are rounded up.
template<typename T, index_t d>
vec_t<T, d> round(const vec_t<T, d>& vec);

//! Returns a vector with each element rounded to the nearest step value.
template<typename T, index_t d>
vec_t<T, d> snap(const vec_t<T, d>& vec, T step);

} // namespace vec

//! Encapsulates all vec_t<T, 2> related functionality.
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

//! Encapsulates all vec_t<T, 3> related functionality.
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

template<typename T>
mat_t<T, 3> orthonormal_basis(const vec_t<T, 3>& vec);

} // namespace vec3

//! Encapsulates all vec_t<T, 4> related functionality.
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

//! Encapsulates all generic mat_t related functionality.
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

//! Encapsulates all mat_t<T, 3> related functionality.
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

//! Encapsulates all mat_t<T, 4> related functionality.
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

//! Encapsulates all point2_t and point3_t related functionality.
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

//! Encapsulates all quat_t related functionality.
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

//! Encapsulates all affine_t related functionality.
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

vec3_t transform_pos(const affine_t& affine, const vec3_t& position);

point3_t transform_pos(const affine_t& affine, const point3_t& position);

vec3_t inv_transform_dir(const affine_t& affine, const vec3_t& direction);

vec3_t inv_transform_pos(const affine_t& affine, const vec3_t& position);

point3_t inv_transform_pos(const affine_t& affine, const point3_t& position);

} // namespace affine

} // namespace as

#include "as-math-ops.inl"
