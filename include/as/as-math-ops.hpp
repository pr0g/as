//! \file
//! `as-math-ops`

#pragma once

#include <algorithm>
#include <iterator>
#include <numeric>
#include <tuple>

#include "as-affine.hpp"
#include "as-mat3.hpp"
#include "as-mat4.hpp"
#include "as-math.hpp"
#include "as-quat.hpp"
#include "as-rigid.hpp"
#include "as-vec.hpp"

namespace as
{

//! Creates a vector from a fixed size array of the same type and dimension.
template<typename T, index d>
vec<T, d> vec_from_arr(const T (&data)[d]);

//! Creates a vector from a pointer to an array of the same type.
//! \warning Be very careful when using this function. Ensure that the array
//! used to initialize the vector is at least as big as the size of the vector.
//! Undefined behaviour may be invoked by reading memory out of bounds if not.
template<typename T, index d>
vec<T, d> vec_from_ptr(const T* data);

//! Creates a vector from an existing vector with a new type (O - other).
//! ```{.cpp}
//! as::vec3d v3d = {1.0, 2.0, 3.0};
//! as::vec3f v3f = vec_from_vec<float>(v3d);
//! ```
template<typename T, typename O, as::index d>
as::vec<T, d> vec_from_vec(const as::vec<O, d>& v);

//! Writes the values stored in the vector to an array of the same type and
//! dimension.
template<typename T, index d>
void vec_to_arr(const vec<T, d>& v, T (&data)[d]);

//! Returns a pointer to the start of the vector data.
template<typename T, index d>
T* vec_data(vec<T, d>& v);

//! Returns a pointer to the start of the  vector data (const/immutable).
template<typename T, index d>
const T* vec_const_data(const vec<T, d>& v);

//! Returns the dot product of two vectors.
//! \note Result is equivalent to: `|lhs| * |rhs| * cos(θ)`
//! \note Result is positive for acute angles, negative for obtuse angles and
//! zero for right angles (vectors that are perpendicular/orthogonal).
template<typename T, index d>
constexpr real vec_dot(const vec<T, d>& lhs, const vec<T, d>& rhs);

//! Returns the dot product of two vector twos.
template<>
constexpr real vec_dot(const vec2& lhs, const vec2& rhs);

//! Returns the dot product of two vector threes.
template<>
constexpr real vec_dot(const vec3& lhs, const vec3& rhs);

//! Returns the length squared of the vector.
template<typename T, index d>
constexpr real vec_length_sq(const vec<T, d>& v);

//! Returns the length of the vector.
template<typename T, index d>
real vec_length(const vec<T, d>& v);

//! Returns the distance between two vectors.
template<typename T, index d>
real vec_distance(const vec<T, d>& lhs, const vec<T, d>& rhs);

//! Returns the input vector with unit length.
template<typename T, index d>
vec<real, d> vec_normalize(const vec<T, d>& v);

//! Returns the normalized vector (unit length) along with the length of the
//! input vector.
//! \note This can be useful to use instead of having to call `normalize` and
//! `length` separately (reduces repeated work).
template<typename T, index d>
std::tuple<vec<real, d>, real> vec_normalize_and_length(const vec<T, d>& v);

//! Returns if two vectors are the same as each other (within a certain
//! tolerance).
//! \param max_diff The epsilon value to use for values very close to zero.
//! \param max_rel_diff The epsilon value to use for all other values.
//! `max_rel_diff` will be scaled by the largest of the two values.
template<typename T, index d>
bool vec_near(
  const vec<T, d>& lhs, const vec<T, d>& rhs,
  real max_diff = std::numeric_limits<float>::epsilon(),
  real max_rel_diff = std::numeric_limits<float>::epsilon());

//! Performs a `min` on each element of the two vectors, returning the
//! smallest value at each element.
//! ```{.cpp}
//! min((2, 4, 6), (3, 8, 1)) = (2, 4, 1)
//! ```
template<typename T, index d>
vec<T, d> vec_min(const vec<T, d>& lhs, const vec<T, d>& rhs);

//! Performs a `min` on each element of the vector with `rhs`, returning the
//! smallest value at each element.
//! ```{.cpp}
//! min((2, 4, 6), 3) = (2, 3, 3)
//! ```
template<typename T, index d>
vec<T, d> vec_min(const vec<T, d>& lhs, T rhs);

//! Returns the smallest element in the vector.
template<typename T, index d>
constexpr T vec_min_elem(const vec<T, d>& v);

//! Performs a `max` on each element of the two vectors, returning the
//! largest value at each element.
//! ```{.cpp}
//! max((2, 4, 6), (3, 8, 1)) = (3, 8, 6)
//! ```
template<typename T, index d>
vec<T, d> vec_max(const vec<T, d>& lhs, const vec<T, d>& rhs);

//! Performs a `max` on each element of the vector with `rhs`, returning the
//! largest value at each element.
//! ```{.cpp}
//! max((2, 4, 6), 3) = (3, 4, 6)
//! ```
template<typename T, index d>
vec<T, d> vec_max(const vec<T, d>& lhs, T rhs);

//! Returns the largest element in the vector.
template<typename T, index d>
constexpr T vec_max_elem(const vec<T, d>& v);

//! Returns a vector with the absolute value of each element of the input
//! vector.
//! ```{.cpp}
//! abs((-1, 5, -3)) = (1, 5, 3)
//! ```
template<typename T, index d>
vec<T, d> vec_abs(const vec<T, d>& v);

//! Returns a vector where each element falls within the range `min` and `max`.
template<typename T, index d>
vec<T, d> vec_clamp(
  const vec<T, d>& v, const vec<T, d>& min, const vec<T, d>& max);

//! Returns a vector with each element clamped within the `0-1` range.
template<typename T, index d>
vec<T, d> vec_saturate(const vec<T, d>& v);

//! Returns a linearly interpolated vector between `begin` and `end`.
//! \param t The amount of interpolation between `begin` and `end`. Must be in
//! the range `[0-1]`.
//! \param begin The vector to interpolate from.
//! \param end The vector to interpolate to.
template<typename T, index d>
vec<T, d> vec_mix(const vec<T, d>& begin, const vec<T, d>& end, real t);

//! Template specialization of vec_mix for vec2.
template<>
constexpr vec2 vec_mix(const vec2& begin, const vec2& end, real t);

//! Template specialization of vec_mix for vec3.
template<>
constexpr vec3 vec_mix(const vec3& begin, const vec3& end, real t);

//! Returns `v0` if `select0` is true, otherwise `v1`.
template<typename T, index d>
constexpr vec<T, d> vec_select(
  const vec<T, d>& v0, const vec<T, d>& v1, bool select0);

//! Returns a vector with each element being rounded down to the nearest whole
//! number.
template<typename T, index d>
vec<T, d> vec_floor(const vec<T, d>& v);

//! Returns a vector with each element being rounded up to the nearest whole
//! number.
template<typename T, index d>
vec<T, d> vec_ceil(const vec<T, d>& v);

//! Returns a vector with each element being rounded toward to the nearest whole
//! number.
//! \note Halfway values are rounded up.
template<typename T, index d>
vec<T, d> vec_round(const vec<T, d>& v);

//! Returns a vector with each element rounded to the nearest step value.
template<typename T, index d>
vec<T, d> vec_snap(const vec<T, d>& v, T step);

//! Returns a vector with each element converted from degrees to radians.
template<typename T, index d>
vec<T, d> vec_radians(const vec<T, d>& degrees);

//! Returns a vector with each element converted from radians to degrees.
template<typename T, index d>
vec<T, d> vec_degrees(const vec<T, d>& radians);

//! Creates a vec<T, 2> from a fixed size array of the same type and
//! dimension.
template<typename T>
vec<T, 2> vec2_from_arr(const T (&data)[2]);

//! Creates a vec<T, 2> from a pointer to an array of the same type.
template<typename T>
vec<T, 2> vec2_from_ptr(const T* data);

//! Returns a vec<T, 2> with the first and second element of the vec<T, 3>.
template<typename T>
constexpr vec<T, 2> vec2_from_vec3(const vec<T, 3>& v);

//! Returns a vec<T, 2> with the first and second element of the vec<T, 4>.
template<typename T>
constexpr vec<T, 2> vec2_from_vec4(const vec<T, 4>& v);

//! Returns the signed area formed by two vectors.
//! \note This is similar to the cross product of two 3d vectors.
template<typename T>
constexpr T vec2_wedge(const vec<T, 2>& lhs, const vec<T, 2>& rhs);

//! Returns the vector orthogonal/perpendicular to v (clockwise).
template<typename T>
constexpr vec<T, 2> vec2_orthogonal_cw(const vec<T, 2>& v);

//! Returns the vector orthogonal/perpendicular to v (counter clockwise).
template<typename T>
constexpr vec<T, 2> vec2_orthogonal_ccw(const vec<T, 2>& v);

//! Creates a vec<T, 3> from a fixed size array of the same type and
//! dimension.
template<typename T>
vec<T, 3> vec3_from_arr(const T (&data)[3]);

//! Creates a vec<T, 3> from a pointer to an array of the same type.
template<typename T>
vec<T, 3> vec3_from_ptr(const T* data);

//! Returns a vec<T, 3> with the elements of the vec<T, 2> and an optional
//! third parameter (defaulted to zero).
template<typename T>
constexpr vec<T, 3> vec3_from_vec2(const vec<T, 2>& v, T z = T(0.0));

//! Returns a vec<T, 3> with the first and second element of the vec<T, 4>.
template<typename T>
constexpr vec<T, 3> vec3_from_vec4(const vec<T, 4>& v);

//! Returns a vec<T, 3> orthogonal to both input vectors.
//! \note If the two input vectors are perpendicular the result will be zero
//! (undefined).
//! \note The order of the input vectors is important. The sign of the resulting
//! vector will vary depending on the order.
template<typename T>
constexpr vec<T, 3> vec3_cross(const vec<T, 3>& lhs, const vec<T, 3>& rhs);

//! Returns the reflection of vector `l` about the normal `n`.
//! \param l Incoming light direction.
//! \param n Surface normal.
template<typename T>
vec<T, 3> vec3_reflect(const vec<T, 3>& l, const vec<T, 3>& n);

//! Sets the across and up axes for the given input vector so all axes remain
//! orthogonal to one another.
//! \note Across and up will be invalid if dir is equal to +/-world_up.
//! \note Expects a left-handed coordinate system.
template<typename T>
void vec3_right_and_up_lh(
  const vec<T, 3>& dir, vec<T, 3>& across, vec<T, 3>& up,
  const vec<T, 3>& world_up = vec<T, 3>::axis_y());

//! Sets the across and up axes for the given input vector so all axes remain
//! orthogonal to one another.
//! \note Across and up will be invalid if dir is equal to +/-world_up.
//! \note Expects a right-handed coordinate system.
template<typename T>
void vec3_right_and_up_rh(
  const vec<T, 3>& dir, vec<T, 3>& across, vec<T, 3>& up,
  const vec<T, 3>& world_up = vec<T, 3>::axis_y());

//! Returns a vector orthogonal to u.
template<typename T>
vec<T, 3> vec3_orthogonal(const vec<T, 3>& u);

//! Returns an orthonormal basis for the given input vector.
//! \note This should be preferred to `right_and_up` variants.
template<typename T>
mat<T, 3> orthonormal_basis(const vec<T, 3>& u);

//! Creates a vec<T, 4> from a fixed size array of the same type and
//! dimension.
template<typename T>
vec<T, 4> vec4_from_arr(const T (&data)[4]);

//! Creates a vec<T, 4> from a pointer to an array of the same type.
template<typename T>
vec<T, 4> vec4_from_ptr(const T* data);

//! Returns a vec<T, 4> with the elements of the vec<T, 2> and optional
//! remaining parameters (defaulted to zero).
template<typename T>
constexpr vec<T, 4> vec4_from_vec2(
  const vec<T, 2>& v, T z = T(0.0), T w = T(0.0));

//! Returns a vec<T, 4> with the elements of the vec<T, 3> and an optional
//! fourth parameter (defaulted to zero).
template<typename T>
constexpr vec<T, 4> vec4_from_vec3(const vec<T, 3>& v, T w = T(0.0));

//! Returns a vec<T, 4> with the xyz components of `v` and w as `1.0`.
template<typename T>
constexpr vec<T, 4> vec4_translation(const vec<T, 3>& v);

//! Returns a vec<T, 4> with the xyz components of `v` and w as `0.0`.
template<typename T>
constexpr vec<T, 4> vec4_direction(const vec<T, 3>& v);

//! Returns the average of an array of vectors.
template<typename T, index d>
vec<T, d> vec_average(const vec<T, d>* vectors, index count);

//! Returns the average of a parameter pack of vectors.
template<typename... vectors>
auto vec_average_fold(vectors&&... vecs);

//! Returns the nth row of the matrix.
//! \param m The matrix to use.
//! \param r Row index.
template<typename T, index d>
vec<T, d> mat_row(const mat<T, d>& m, index r);

//! Returns the nth column of the matrix.
//! \param m The matrix to use.
//! \param c Column index.
template<typename T, index d>
vec<T, d> mat_col(const mat<T, d>& m, index c);

//! Sets the nth row of the matrix.
//! \param m The matrix to use.
//! \param r Row index.
//! \param row The vector to use.
template<typename T, index d>
constexpr void mat_row(mat<T, d>& m, index r, const vec<T, d>& row);

//! Sets the nth column of the matrix.
//! \param m The matrix to use.
//! \param c Column index.
//! \param col The vector to use.
template<typename T, index d>
constexpr void mat_col(mat<T, d>& m, index c, const vec<T, d>& col);

//! Returns a pointer to the start of the matrix data.
template<typename T, index d>
T* mat_data(mat<T, d>& m);

//! Returns a pointer to the start of the  matrix data (const/immutable).
template<typename T, index d>
const T* mat_const_data(const mat<T, d>& m);

//! Creates a mat from a fixed size array of the same type and dimension.
template<typename T, index d>
mat<T, d> mat_from_arr(const T (&data)[d * d]);

//! Creates a mat from a pointer to an array of the same type.
template<typename T, index d>
mat<T, d> mat_from_ptr(const T* data);

//! Creates a matrix from an existing matrix with a new type (O - other).
//! ```{.cpp}
//! as::mat3d m3d = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};
//! as::mat3f m3f = mat_from_mat<float>(m3d);
//! ```
template<typename T, typename O, as::index d>
as::mat<T, d> mat_from_mat(const as::mat<O, d>& m);

//! Writes the values stored in the matrix to an array of the same type and
//! dimension.
template<typename T, index d>
void mat_to_arr(const mat<T, d>& m, T (&data)[d * d]);

//! Returns if two matrices are the same as each other (within a certain
//! tolerance).
//! \param max_diff The epsilon value to use for values very close to zero.
//! \param max_rel_diff The epsilon value to use for all other values.
//! `max_rel_diff` will be scaled by the largest of the two values.
template<typename T, index d>
bool mat_near(
  const mat<T, d>& lhs, const mat<T, d>& rhs,
  real max_diff = std::numeric_limits<float>::epsilon(),
  real max_rel_diff = std::numeric_limits<float>::epsilon());

//! Returns the transpose of the matrix.
//! \note Rows and columns are swapped.
template<typename T, index d>
mat<T, d> mat_transpose(const mat<T, d>& m);

//! Returns the determinant of the matrix.
//! \note This is the signed volume of the n-dimensional parallelepiped spanned
//! by the column or row vectors of the matrix.
template<typename T, index d>
T mat_determinant(const mat<T, d>& m);

//! Returns the inverse of the matrix.
//! ```{.cpp}
//! // m * inv(m) = identity
//! ```
template<typename T, index d>
mat<T, d> mat_inverse(const mat<T, d>& m);

//! Returns the result of two `mat` types multiplied together.
//! \note `lhs` is performed first, then `rhs`
//! ```{.cpp}
//! // Column major
//! result = rhs * lhs; // right to left
//! // Row major
//! result = lhs * rhs; // left to right
//! ```
template<typename T, index d>
mat<T, d> mat_mul(const mat<T, d>& lhs, const mat<T, d>& rhs);

//! Returns the result of transforming the vector `v` by `m`.
//! ```{.cpp}
//! // Column major
//! result = m * v; // right to left
//! // Row major
//! result = v * m; // left to right
//! ```
template<typename T, index d>
vec<T, d> mat_mul(const vec<T, d>& v, const mat<T, d>& m);

//! Returns the first row of the ::mat3.
template<typename T>
constexpr vec<T, 3> mat3_row0(const mat<T, 3>& m);

//! Returns the second row of the ::mat3.
template<typename T>
constexpr vec<T, 3> mat3_row1(const mat<T, 3>& m);

//! Returns the third row of the ::mat3.
template<typename T>
constexpr vec<T, 3> mat3_row2(const mat<T, 3>& m);

//! Returns the first column of the ::mat3.
template<typename T>
constexpr vec<T, 3> mat3_col0(const mat<T, 3>& m);

//! Returns the second column of the ::mat3.
template<typename T>
constexpr vec<T, 3> mat3_col1(const mat<T, 3>& m);

//! Returns the third column of the ::mat3.
template<typename T>
constexpr vec<T, 3> mat3_col2(const mat<T, 3>& m);

//! Sets the first row of the ::mat3.
template<typename T>
constexpr void mat3_row0(mat<T, 3>& m, const vec<T, 3>& row);

//! Sets the second row of the ::mat3.
template<typename T>
constexpr void mat3_row1(mat<T, 3>& m, const vec<T, 3>& row);

//! Sets the third row of the ::mat3.
template<typename T>
constexpr void mat3_row2(mat<T, 3>& m, const vec<T, 3>& row);

//! Sets the first column of the ::mat3.
template<typename T>
constexpr void mat3_col0(mat<T, 3>& m, const vec<T, 3>& col);

//! Sets the second column of the ::mat3.
template<typename T>
constexpr void mat3_col1(mat<T, 3>& m, const vec<T, 3>& col);

//! Sets the third column of the ::mat3.
template<typename T>
constexpr void mat3_col2(mat<T, 3>& m, const vec<T, 3>& col);

//! Returns the x basis vector of the ::mat3.
template<typename T>
constexpr vec<T, 3> mat3_basis_x(const mat<T, 3>& m);

//! Returns the y basis vector of the ::mat3.
template<typename T>
constexpr vec<T, 3> mat3_basis_y(const mat<T, 3>& m);

//! Returns the z basis vector of the ::mat3.
template<typename T>
constexpr vec<T, 3> mat3_basis_z(const mat<T, 3>& m);

//! Sets the x basis vector of the ::mat3.
template<typename T>
constexpr void mat3_basis_x(mat<T, 3>& m, const vec<T, 3>& basis);

//! Sets the y basis vector of the ::mat3.
template<typename T>
constexpr void mat3_basis_y(mat<T, 3>& m, const vec<T, 3>& basis);

//! Sets the z basis vector of the ::mat3.
template<typename T>
constexpr void mat3_basis_z(mat<T, 3>& m, const vec<T, 3>& basis);

//! Creates a mat<T, 3> from a fixed size array of the same type and
//! dimension.
template<typename T>
mat<T, 3> mat3_from_arr(const T (&data)[9]);

//! Creates a mat<T, 3> from a pointer to an array of the same type.
template<typename T>
mat<T, 3> mat3_from_ptr(const T* data);

//! Returns a mat<T, 3> from a mat<T, 4>.
//! \note The upper 3x3 part of the 4x4 matrix is returned.
template<typename T>
constexpr mat<T, 3> mat3_from_mat4(const mat<T, 4>& transform);

//! Returns a mat<T, 3> from an \ref affine.
template<typename T>
constexpr mat<T, 3> mat3_from_affine(const affine_t<T>& a);

//! Returns a rotation about a given axis.
//! \param axis The axis of rotation.
//! \param radians The amount to rotate by in radians.
template<typename T>
mat<T, 3> mat3_rotation_axis(const vec<T, 3>& axis, T radians);

//! Returns a rotation about `x`, then `y`, then `z`.
template<typename T>
mat<T, 3> mat3_rotation_xyz(T x, T y, T z);

//! Returns a rotation about `x`, then `y`, then `z` of vector `xyz`.
template<typename T>
mat<T, 3> mat3_rotation_xyz(const vec<T, 3>& xyz);

//! Returns a rotation about `z`, then `x`, then `y`.
//! Each rotation occurs about the world frame (global axes), not the local
//! frame. Each time a new rotation is introduced from the left, it has no
//! concern for the current local frame, it always rotates in terms of the
//! world frame.
//! \note This is often useful for free-look/fps cameras.
template<typename T>
mat<T, 3> mat3_rotation_zxy(T x, T y, T z);

//! Returns a rotation about `z`, then `x`, then `y` of vector `xyz`.
template<typename T>
mat<T, 3> mat3_rotation_zxy(const vec<T, 3>& xyz);

//! Returns a rotation about the x axis.
template<typename T>
mat<T, 3> mat3_rotation_x(T radians);

//! Returns a rotation about the y axis.
template<typename T>
mat<T, 3> mat3_rotation_y(T radians);

//! Returns a rotation about the z axis.
template<typename T>
mat<T, 3> mat3_rotation_z(T radians);

//! Returns a uniform scale matrix.
template<typename T>
constexpr mat<T, 3> mat3_scale(T scale);

//! Returns a (potentially) non-uniform scale matrix.
template<typename T>
constexpr mat<T, 3> mat3_scale(T x, T y, T z);

//! Returns a (potentially) non-uniform scale matrix.
template<typename T>
constexpr mat<T, 3> mat3_scale(const vec<T, 3>& scale);

//! Returns a ::mat3 from a quaternion.
template<typename T>
constexpr mat<T, 3> mat3_from_quat(const quat_t<T>& q);

//! Returns the first row of the ::mat4.
template<typename T>
constexpr vec<T, 4> mat4_row0(const mat<T, 4>& m);

//! Returns the second row of the ::mat4.
template<typename T>
constexpr vec<T, 4> mat4_row1(const mat<T, 4>& m);

//! Returns the third row of the ::mat4.
template<typename T>
constexpr vec<T, 4> mat4_row2(const mat<T, 4>& m);

//! Returns the fourth row of the ::mat4.
template<typename T>
constexpr vec<T, 4> mat4_row3(const mat<T, 4>& m);

//! Returns the first column of the ::mat4.
template<typename T>
constexpr vec<T, 4> mat4_col0(const mat<T, 4>& m);

//! Returns the second column of the ::mat4.
template<typename T>
constexpr vec<T, 4> mat4_col1(const mat<T, 4>& m);

//! Returns the third column of the ::mat4.
template<typename T>
constexpr vec<T, 4> mat4_col2(const mat<T, 4>& m);

//! Returns the fourth column of the ::mat4.
template<typename T>
constexpr vec<T, 4> mat4_col3(const mat<T, 4>& m);

//! Sets the first row of the ::mat4.
template<typename T>
constexpr void mat4_row0(mat<T, 4>& m, const vec<T, 4>& row);

//! Sets the second row of the ::mat4.
template<typename T>
constexpr void mat4_row1(mat<T, 4>& m, const vec<T, 4>& row);

//! Sets the third row of the ::mat4.
template<typename T>
constexpr void mat4_row2(mat<T, 4>& m, const vec<T, 4>& row);

//! Sets the fourth row of the ::mat4.
template<typename T>
constexpr void mat4_row3(mat<T, 4>& m, const vec<T, 4>& row);

//! Sets the first column of the ::mat4.
template<typename T>
constexpr void mat4_col0(mat<T, 4>& m, const vec<T, 4>& col);

//! Sets the second column of the ::mat4.
template<typename T>
constexpr void mat4_col1(mat<T, 4>& m, const vec<T, 4>& col);

//! Sets the third column of the ::mat4.
template<typename T>
constexpr void mat4_col2(mat<T, 4>& m, const vec<T, 4>& col);

//! Sets the fourth column of the ::mat4.
template<typename T>
constexpr void mat4_col3(mat<T, 4>& m, const vec<T, 4>& col);

//! Returns the first vector of the ::mat4.
//! \note This is either the first row or column depending on
//! AS_COL_MAJOR or AS_ROW_MAJOR being defined.
template<typename T>
constexpr vec<T, 4> mat4_dimension0(const mat<T, 4>& m);

//! Returns the second vector of the ::mat4.
//! \note This is either the first row or column depending on
//! AS_COL_MAJOR or AS_ROW_MAJOR being defined.
template<typename T>
constexpr vec<T, 4> mat4_dimension1(const mat<T, 4>& m);

//! Returns the third vector of the ::mat4.
//! \note This is either the first row or column depending on
//! AS_COL_MAJOR or AS_ROW_MAJOR being defined.
template<typename T>
constexpr vec<T, 4> mat4_dimension2(const mat<T, 4>& m);

//! Returns the fourth vector of the ::mat4.
//! \note This is either the first row or column depending on
//! AS_COL_MAJOR or AS_ROW_MAJOR being defined.
template<typename T>
constexpr vec<T, 4> mat4_dimension3(const mat<T, 4>& m);

//! Sets the first vector of the ::mat4.
//! \note This is either the first row or column depending on
//! AS_COL_MAJOR or AS_ROW_MAJOR being defined.
template<typename T>
constexpr void mat4_dimension0(mat<T, 4>& m, const vec<T, 4>& v);

//! Sets the second vector of the ::mat4.
//! \note This is either the first row or column depending on
//! AS_COL_MAJOR or AS_ROW_MAJOR being defined.
template<typename T>
constexpr void mat4_dimension1(mat<T, 4>& m, const vec<T, 4>& v);

//! Sets the third vector of the ::mat4.
//! \note This is either the first row or column depending on
//! AS_COL_MAJOR or AS_ROW_MAJOR being defined.
template<typename T>
constexpr void mat4_dimension2(mat<T, 4>& m, const vec<T, 4>& v);

//! Sets the fourth vector of the ::mat4.
//! \note This is either the first row or column depending on
//! AS_COL_MAJOR or AS_ROW_MAJOR being defined.
template<typename T>
constexpr void mat4_dimension3(mat<T, 4>& m, const vec<T, 4>& v);

//! Returns the x basis vector of the ::mat4.
template<typename T>
constexpr vec<T, 3> mat4_basis_x(const mat<T, 4>& m);

//! Returns the y basis vector of the ::mat4.
template<typename T>
constexpr vec<T, 3> mat4_basis_y(const mat<T, 4>& m);

//! Returns the z basis vector of the ::mat4.
template<typename T>
constexpr vec<T, 3> mat4_basis_z(const mat<T, 4>& m);

//! Returns the translation component of the ::mat4.
template<typename T>
constexpr vec<T, 3> mat4_translation(const mat<T, 4>& m);

//! Sets the x basis vector of the ::mat4.
//! \note The fourth component of the matrix vector will be set to 0.
template<typename T>
constexpr void mat4_basis_x(mat<T, 4>& m, const vec<T, 3>& basis);

//! Sets the y basis vector of the ::mat4.
//! \note The fourth component of the matrix vector will be set to 0.
template<typename T>
constexpr void mat4_basis_y(mat<T, 4>& m, const vec<T, 3>& basis);

//! Sets the z basis vector of the ::mat4.
//! \note The fourth component of the matrix vector will be set to 0.
template<typename T>
constexpr void mat4_basis_z(mat<T, 4>& m, const vec<T, 3>& basis);

//! Sets the translation vector of the ::mat4.
//! \note The fourth component of the matrix vector will be set to 1.
template<typename T>
constexpr void mat4_translation(mat<T, 4>& m, const vec<T, 3>& translation);

//! Creates a mat<T, 4> from a fixed size array of the same type and
//! dimension.
template<typename T>
mat<T, 4> mat4_from_arr(const T (&data)[16]);

//! Creates a mat<T, 3> from a pointer to an array of the same type.
template<typename T>
mat<T, 4> mat4_from_ptr(const T* data);

//! Returns a mat<T, 4> from a vec<T, 3>.
//! \note The upper 3x3 part of the 4x4 matrix is the identity.
template<typename T>
constexpr mat<T, 4> mat4_from_vec3(const vec<T, 3>& translation);

//! Returns a mat<T, 4> from a mat<T, 3>.
//! \note The translation part of the 4x4 matrix will be `(0, 0, 0, 1)`.
template<typename T>
constexpr mat<T, 4> mat4_from_mat3(const mat<T, 3>& rotation);

//! Returns a mat<T, 4> from a mat<T, 3> and a vec<T, 3>.
template<typename T>
constexpr mat<T, 4> mat4_from_mat3_vec3(
  const mat<T, 3>& rotation, const vec<T, 3>& translation);

//! Returns a mat<T, 4> from an \ref affine.
//! \note The effect of the transformation will be the same, it is only the type
//! that changes.
template<typename T>
constexpr mat<T, 4> mat4_from_affine(const affine_t<T>& a);

//! Returns a mat<T, 4> from a \ref rigid.
//! \note The effect of the transformation will be the same, it is only the type
//! that changes.
template<typename T>
constexpr mat<T, 4> mat4_from_rigid(const rigid_t<T>& r);

//! Returns a shear transformation about the `x` axis in `y` and/or `z`.
template<typename T>
constexpr mat<T, 4> mat4_shear_x(T y, T z);

//! Returns a shear transformation about the `y` axis in `x` and/or `z`.
template<typename T>
constexpr mat<T, 4> mat4_shear_y(T x, T z);

//! Returns a shear transformation about the `z` axis in `x` and/or `y`.
template<typename T>
constexpr mat<T, 4> mat4_shear_z(T x, T y);

//! Returns if two quaternions are within a certain tolerance of one another.
template<typename T>
bool quat_near(
  const quat_t<T>& q0, const quat_t<T>& q1,
  real max_diff = std::numeric_limits<float>::epsilon(),
  real max_rel_diff = std::numeric_limits<float>::epsilon());

//! Returns the dot product of two quaternions.
//! \note The corresponding scalar parts are multiplied together and then
//! summed.
template<typename T>
constexpr T quat_dot(const quat_t<T>& lhs, const quat_t<T>& rhs);

//! Returns the length (magnitude) squared of the quaternion.
template<typename T>
constexpr T quat_length_sq(const quat_t<T>& q);

//! Returns the length (magnitude) of the quaternion.
template<typename T>
T quat_length(const quat_t<T>& q);

//! Returns the conjugate of the quaternion.
//! \note The sign of the imaginary parts are flipped.
//! \note Represents the same rotation as the initial quaternion in the reverse
//! direction.
template<typename T>
constexpr quat_t<T> quat_conjugate(const quat_t<T>& q);

//! Returns a quaternion representing a rotation about the given axis.
//! \param axis The axis of rotation.
//! \param radians The amount to rotate by in radians.
template<typename T>
quat_t<T> quat_rotation_axis(const vec<T, 3>& axis, T radians);

//! Returns a rotation about the x axis.
template<typename T>
quat_t<T> quat_rotation_x(T radians);

//! Returns a rotation about the y axis.
template<typename T>
quat_t<T> quat_rotation_y(T radians);

//! Returns a rotation about the z axis.
template<typename T>
quat_t<T> quat_rotation_z(T radians);

//! Returns a rotation about x, then y, then z.
template<typename T>
quat_t<T> quat_rotation_xyz(T x, T y, T z);

//! Returns a rotation about x, then y, then z of vector `xyz`.
template<typename T>
quat_t<T> quat_rotation_xyz(const vec<T, 3>& xyz);

//! Returns a rotation about z, then x, then y.
template<typename T>
quat_t<T> quat_rotation_zxy(T x, T y, T z);

//! Returns a rotation about z, then x, then y of vector `xyz`.
template<typename T>
quat_t<T> quat_rotation_zxy(const vec<T, 3>& xyz);

//! Returns the input quaternion normalized.
template<typename T>
quat_t<T> quat_normalize(const quat_t<T>& q);

//! Returns the inverse of the quaternion.
//! \note This is the same as the conjugate if the quaternion is normalized
//! (unit length).
template<typename T>
quat_t<T> quat_inverse(const quat_t<T>& q);

//! Returns the input vector rotated by the given quaternion.
template<typename T>
vec<T, 3> quat_rotate(const quat_t<T>& q, const vec<T, 3>& v);

//! Returns the result of a linear interpolation between the two quaternions
//! by ratio `t`.
//! \note `t` should be in the range `[0-1]`.
template<typename T>
quat_t<T> quat_nlerp(const quat_t<T>& q0, const quat_t<T>& q1, T t);

//! Returns the result of a spherical interpolation between the two quaternions
//! by ratio `t`.
//! \note `t` should be in the range `[0-1]`.
template<typename T>
quat_t<T> quat_slerp(const quat_t<T>& q0, const quat_t<T>& q1, T t);

//! Converts a rotation matrix to a quaternion.
//! \note Ensure ::mat3 is a valid rotation. It must be 'special orthogonal'
//! (pure rotation without reflection).
template<typename T>
quat_t<T> quat_from_mat3(const mat<T, 3>& m);

//! Writes the values stored in the \ref quat to an array of the same type
//! and dimension.
template<typename T>
void quat_to_arr(const quat_t<T>& q, T (&data)[quat_t<T>::size()]);

//! Writes the values stored in the \ref affine to an array of the same type
//! and dimension.
//! \note affine uses a ::mat3 and a ::vec3 internally.
template<typename T>
void affine_to_arr(const affine_t<T>& a, T (&data)[affine_t<T>::size()]);

//! Creates an \ref affine from a fixed size array of the same type and
//! dimension.
//! \note affine uses a ::mat3 and a ::vec3 internally.
template<typename T>
affine_t<T> affine_from_arr(const T (&data)[affine_t<T>::size()]);

//! Creates an \ref affine from a pointer to an array of the same type.
//! \note Ensure that the array has at least 12 elements from where it is read.
template<typename T>
affine_t<T> affine_from_ptr(const T* data);

//! Returns an \ref affine from a ::mat4.
//! \note Ensure that the ::mat4 holds a valid a transformation
//! (translation/scale/rotation) and not a non-affine transformation such as a
//! projection.
template<typename T>
affine_t<T> affine_from_mat4(const mat<T, 4>& m);

//! Returns an \ref affine from a ::mat3.
//! \note Ensure that the ::mat3 holds a valid a transformation
//! (scale/rotation)
//! \note The translation portion of affine will be zero.
template<typename T>
affine_t<T> affine_from_mat3(const mat<T, 3>& m);

//! Returns an \ref affine from a ::mat3 and a ::vec3.
//! \note Ensure that the ::mat3 holds a valid a transformation
//! (scale/rotation)
template<typename T>
affine_t<T> affine_from_mat3_vec3(const mat<T, 3>& m, const vec<T, 3>& v);

//! Returns an \ref affine from a ::vec3.
//! \note The rotation part will be initialized to the identity.
template<typename T>
affine_t<T> affine_from_vec3(const vec<T, 3>& v);

//! Returns an \ref affine from a \ref rigid.
template<typename T>
affine_t<T> affine_from_rigid(const rigid_t<T>& r);

//! Returns the result of two \ref affine types multiplied together.
//! \note `lhs` is performed first, then `rhs`
template<typename T>
affine_t<T> affine_mul(const affine_t<T>& lhs, const affine_t<T>& rhs);

//! Returns the inverse of the \ref affine.
//! ```{.cpp}
//! // a * inv(a) = identity
//! ```
//! \note A full inverse is performed as the rotation part may also contain
//! scale.
//! Ensure it holds a valid a rotation (axes are orthogonal).
template<typename T>
affine_t<T> affine_inverse(const affine_t<T>& a);

//! Returns if two affine transformations are the same as each other (within
//! a certain tolerance).
template<typename T>
bool affine_near(
  const affine_t<T>& lhs, const affine_t<T>& rhs,
  real max_diff = std::numeric_limits<float>::epsilon(),
  real max_rel_diff = std::numeric_limits<float>::epsilon());

//! Returns the input direction transformed by the \ref affine.
template<typename T>
vec<T, 3> affine_transform_dir(
  const affine_t<T>& a, const vec<T, 3>& direction);

//! Returns the input position transformed by the \ref affine.
template<typename T>
vec<T, 3> affine_transform_pos(const affine_t<T>& a, const vec<T, 3>& position);

//! Returns the input direction transformed by the inverse of the \ref affine.
template<typename T>
vec<T, 3> affine_inv_transform_dir(
  const affine_t<T>& a, const vec<T, 3>& direction);

//! Returns the input position transformed by the inverse of the \ref affine.
template<typename T>
vec<T, 3> affine_inv_transform_pos(
  const affine_t<T>& a, const vec<T, 3>& position);

//! Writes the values stored in the \ref rigid to an array of the same type
//! and dimension.
//! \note rigid uses a \ref quat and a ::vec3 internally.
template<typename T>
void rigid_to_arr(const rigid_t<T>& r, T (&data)[rigid_t<T>::size()]);

//! Creates a \ref rigid from a fixed size array of the same type and
//! dimension.
//! \note rigid uses a \ref quat and a ::vec3 internally.
template<typename T>
rigid_t<T> rigid_from_arr(const T (&data)[rigid_t<T>::size()]);

//! Creates a \ref rigid from a pointer to an array of the same type.
//! \note Ensure that the array has at least 7 elements from where it is read.
template<typename T>
rigid_t<T> rigid_from_ptr(const T* data);

//! Returns a \ref rigid from a ::mat4.
//! \note Ensure that the ::mat4 holds a valid a transformation
//! (translation/scale/rotation) and not a non-affine transformation such as a
//! projection.
template<typename T>
rigid_t<T> rigid_from_mat4(const mat<T, 4>& m);

//! Returns a \ref rigid from a \ref quat.
//! \note Ensure that the \ref quat holds a valid a transformation
//! (scale/rotation)
//! \note The translation portion of rigid will be zero.
template<typename T>
rigid_t<T> rigid_from_quat(const quat_t<T>& q);

//! Returns a \ref rigid from a \ref quat and a ::vec3.
//! \note Ensure that the \ref quat holds a valid a transformation
//! (scale/rotation)
template<typename T>
rigid_t<T> rigid_from_quat_vec3(const quat_t<T>& q, const vec<T, 3>& v);

//! Returns a \ref rigid from a ::vec3.
//! \note The rotation part will be initialized to the identity.
template<typename T>
rigid_t<T> rigid_from_vec3(const vec<T, 3>& v);

//! Returns a \ref rigid from an \ref affine.
//! \note The ::mat3 part of the \ref affine must be a valid rotation matrix.
template<typename T>
rigid_t<T> rigid_from_affine(const affine_t<T>& a);

//! Returns the result of two \ref rigid types multiplied together.
//! \note `lhs` is performed first, then `rhs`
template<typename T>
rigid_t<T> rigid_mul(const rigid_t<T>& lhs, const rigid_t<T>& rhs);

//! Returns the inverse of the \ref rigid.
//! ```{.cpp}
//! // r * inv(r) = identity
//! ```
template<typename T>
rigid_t<T> rigid_inverse(const rigid_t<T>& r);

//! Returns if two rigid transformations are the same as each other (within
//! a certain tolerance).
template<typename T>
bool rigid_near(
  const rigid_t<T>& lhs, const rigid_t<T>& rhs,
  real max_diff = std::numeric_limits<float>::epsilon(),
  real max_rel_diff = std::numeric_limits<float>::epsilon());

//! Returns the input direction transformed by the \ref rigid.
template<typename T>
vec<T, 3> rigid_transform_dir(const rigid_t<T>& r, const vec<T, 3>& direction);

//! Returns the input position transformed by the \ref rigid.
template<typename T>
vec<T, 3> rigid_transform_pos(const rigid_t<T>& r, const vec<T, 3>& position);

//! Returns the input direction transformed by the inverse of the \ref rigid.
template<typename T>
vec<T, 3> rigid_inv_transform_dir(
  const rigid_t<T>& r, const vec<T, 3>& direction);

//! Returns the input position transformed by the inverse of the \ref rigid.
template<typename T>
vec<T, 3> rigid_inv_transform_pos(
  const rigid_t<T>& r, const vec<T, 3>& position);

} // namespace as

#include "as-math-ops.inl"
