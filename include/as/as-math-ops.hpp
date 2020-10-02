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

//! Returns the number of elements in the vector.
//! \note This is equivalent with `d`, the dimension.
template<typename T, index d>
constexpr index vec_size(const vec<T, d>& v);

//! Creates a vector from a fixed size array of the same type and dimension.
template<typename T, index d>
vec<T, d> vec_from_arr(const T (&data)[d]);

//! Creates a vector from a pointer to an array of the same type.
//! \warning Be very careful when using this function. Ensure that the array
//! used to initialize the vector is at least as big as the size of the vector.
//! Undefined behaviour may be invoked by reading memory out of bounds if not.
template<typename T, index d>
vec<T, d> vec_from_ptr(const T* data);

//! Writes the values stored in the vector to an array of the same type and
//! dimension.
template<typename T, index d>
void vec_to_arr(const vec<T, d>& v, T (&data)[d]);

//! Returns the dot product of two vectors.
//! \note Result is equivalent to: `|lhs| * |rhs| * cos(θ)`
//! \note Result is positive for acute angles, negative for obtuse angles and
//! zero for right angles (vectors that are perpendicular/orthogonal).
template<typename T, index d>
constexpr T vec_dot(const vec<T, d>& lhs, const vec<T, d>& rhs);

//! Returns the dot product of two vector threes.
template<>
constexpr real vec_dot(const vec3& lhs, const vec3& rhs);

//! Returns the length squared of the vector.
template<typename T, index d>
constexpr T vec_length_sq(const vec<T, d>& v);

//! Returns the length of the vector.
template<typename T, index d>
T vec_length(const vec<T, d>& v);

//! Returns the distance between two vectors.
template<typename T, index d>
T vec_distance(const vec<T, d>& lhs, const vec<T, d>& rhs);

//! Returns the input vector with unit length.
template<typename T, index d>
vec<T, d> vec_normalize(const vec<T, d>& v);

//! Returns the normalized vector (unit length) along with the length of the
//! input vector.
//! \note This can be useful to use instead of having to call `normalize` and
//! `length` separately (reduces repeated work).
template<typename T, index d>
std::tuple<vec<T, d>, T> vec_normalize_and_length(const vec<T, d>& v);

//! Returns if two vectors are the same as each other (within a certain
//! tolerance).
template<typename T, index d>
bool vec_equal(
  const vec<T, d>& lhs, const vec<T, d>& rhs,
  real epsilon = std::numeric_limits<real>::epsilon());

//! Performs a `min` on each element of the two vectors, returning the
//! smallest value at each element.
//! ```{.cpp}
//! min((2, 4, 6), (3, 8, 1)) = (2, 4, 1)
//! ```
template<typename T, index d>
vec<T, d> vec_min(const vec<T, d>& lhs, const vec<T, d>& rhs);

//! Returns the smallest element in the vector.
template<typename T, index d>
constexpr T vec_min_elem(const vec<T, d>& v);

//! Performs a `max` on each element of the two vectors, returning the
//! largest value at each element.
//! ```{.cpp}
//! min((2, 4, 6), (3, 8, 1)) = (3, 8, 6)
//! ```
template<typename T, index d>
vec<T, d> vec_max(const vec<T, d>& lhs, const vec<T, d>& rhs);

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
vec<T, d> vec_mix(const vec<T, d>& begin, const vec<T, d>& end, T t);

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

//! Returns a vec4 from a point3.
//! \note The fourth paramter of the vec4 will be set to 1.
vec4 vec4_from_point3(const point3& p);

//! Performs a mapping from a row and column index to a single offset.
//! \param r Row index.
//! \param c Column index.
//! \param d Dimension of the matrix.
//! \note The result returned will depend on if `AS_COL_MAJOR` or `AS_ROW_MAJOR`
//! is defined.
//! ```{.cpp}
//! // e.g. 4x4 matrix
//! rc(3, 2, 4) = 11 // column major
//! rc(3, 2, 4) = 14 // row major
//! ```
constexpr index mat_rc(index r, index c, index d);

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

//! Returns a const pointer to the start of the matrix data.
template<typename T, index d>
const T* mat_const_data(const mat<T, d>& m);

//! Creates a mat from a fixed size array of the same type and dimension.
template<typename T, index d>
mat<T, d> mat_from_arr(const T (&data)[d * d]);

//! Creates a mat from a pointer to an array of the same type.
template<typename T, index d>
mat<T, d> mat_from_ptr(const T* data);

//! Writes the values stored in the matrix to an array of the same type and
//! dimension.
template<typename T, index d>
void mat_to_arr(const mat<T, d>& m, T (&data)[d * d]);

//! Returns if two matrices are the same as each other (within a certain
//! tolerance).
template<typename T, index d>
bool mat_equal(
  const mat<T, d>& lhs, const mat<T, d>& rhs,
  real epsilon = std::numeric_limits<real>::epsilon());

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
//! result = lhs * rhs; // left ro right
//! ```
template<typename T, index d>
mat<T, d> mat_mul(const mat<T, d>& lhs, const mat<T, d>& rhs);

//! Performs a mapping from a row and column index to a single offset for
//! ::mat3. \param r Row index. \param c Column index.
constexpr index mat3_rc(index r, index c);

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

//! Returns the x basis vector for the ::mat3.
template<typename T>
constexpr vec<T, 3> mat3_basis_x(const mat<T, 3>& m);

//! Returns the y basis vector for the ::mat3.
template<typename T>
constexpr vec<T, 3> mat3_basis_y(const mat<T, 3>& m);

//! Returns the z basis vector for the ::mat3.
template<typename T>
constexpr vec<T, 3> mat3_basis_z(const mat<T, 3>& m);

//! Sets the x basis vector for the ::mat3.
template<typename T>
constexpr void mat3_basis_x(mat<T, 3>& m, const vec<T, 3>& basis);

//! Sets the y basis vector for the ::mat3.
template<typename T>
constexpr void mat3_basis_y(mat<T, 3>& m, const vec<T, 3>& basis);

//! Sets the z basis vector for the ::mat3.
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

//! Returns a mat<T, 3> from an ::affine.
constexpr mat3 mat3_from_affine(const affine& a);

//! Returns a rotation about a given axis.
//! \param axis The axis of rotation.
//! \param radians The amount to rotate by in radians.
mat3 mat3_rotation_axis(const vec3& axis, real radians);

//! Returns a rotation about `x`, then `y`, then `z`.
mat3 mat3_rotation_xyz(real x, real y, real z);

//! Returns a rotation about `z`, then `x`, then `y`.
//! \note This is often useful for free-look cameras.
mat3 mat3_rotation_zxy(real x, real y, real z);

//! Returns a rotation about the x axis.
mat3 mat3_rotation_x(real radians);

//! Returns a rotation about the y axis.
mat3 mat3_rotation_y(real radians);

//! Returns a rotation about the z axis.
mat3 mat3_rotation_z(real radians);

//! Returns a uniform scale martix.
constexpr mat3 mat3_scale(real scale);

//! Returns a (potentially) non-uniform scale martix.
constexpr mat3 mat3_scale(real x, real y, real z);

//! Returns a (potentially) non-uniform scale martix.
constexpr mat3 mat3_scale(const vec3& scale);

//! Returns a ::mat3 from a quaternion.
constexpr mat3 mat3_from_quat(const quat& q);

//! Performs a mapping from a row and column index to a single offset for
//! ::mat4. \param r Row index. \param c Column index.
constexpr index mat4_rc(index r, index c);

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
constexpr void mat4_row0(const mat<T, 4>& m, const vec<T, 4>& row);

//! Sets the second row of the ::mat4.
template<typename T>
constexpr void mat4_row1(const mat<T, 4>& m, const vec<T, 4>& row);

//! Sets the third row of the ::mat4.
template<typename T>
constexpr void mat4_row2(const mat<T, 4>& m, const vec<T, 4>& row);

//! Sets the fourth row of the ::mat4.
template<typename T>
constexpr void mat4_row3(const mat<T, 4>& m, const vec<T, 4>& row);

//! Sets the first column of the ::mat4.
template<typename T>
constexpr void mat4_col0(const mat<T, 4>& m, const vec<T, 4>& col);

//! Sets the second column of the ::mat4.
template<typename T>
constexpr void mat4_col1(const mat<T, 4>& m, const vec<T, 4>& col);

//! Sets the third column of the ::mat4.
template<typename T>
constexpr void mat4_col2(const mat<T, 4>& m, const vec<T, 4>& col);

//! Sets the fourth column of the ::mat4.
template<typename T>
constexpr void mat4_col3(const mat<T, 4>& m, const vec<T, 4>& col);

//! Returns the x basis vector for the ::mat4.
//! \note The fourth (w) element of the vector will be `0`.
template<typename T>
constexpr vec<T, 4> mat4_basis_x(const mat<T, 4>& m);

//! Returns the y basis vector for the ::mat4.
//! \note The fourth (w) element of the vector will be `0`.
template<typename T>
constexpr vec<T, 4> mat4_basis_y(const mat<T, 4>& m);

//! Returns the z basis vector for the ::mat4.
//! \note The fourth (w) element of the vector will be `0`.
template<typename T>
constexpr vec<T, 4> mat4_basis_z(const mat<T, 4>& m);

//! Returns the translation component of the ::mat4.
//! \note The fourth (w) element of the vector will be `1`.
template<typename T>
constexpr vec<T, 4> mat4_translation(const mat<T, 4>& m);

//! Sets the x basis vector for the ::mat4.
template<typename T>
constexpr void mat4_basis_x(mat<T, 4>& m, const vec<T, 4>& basis);

//! Sets the y basis vector for the ::mat4.
template<typename T>
constexpr void mat4_basis_y(mat<T, 4>& m, const vec<T, 4>& basis);

//! Sets the z basis vector for the ::mat4.
template<typename T>
constexpr void mat4_basis_z(mat<T, 4>& m, const vec<T, 4>& basis);

//! Sets the translation component for the ::mat4.
//! \note The vec4 should usually have its fourth (w) component set to `1`.
template<typename T>
constexpr void mat4_translation(mat<T, 4>& m, const vec<T, 4>& translation);

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

//! Returns a mat<T, 4> from an affine.
//! \note The effect of the transformation will be the same, it is only the type
//! that changes.
constexpr mat4 mat4_from_affine(const affine& a);

//! Returns a shear transformation about the `x` axis in `y` and/or `z`.
template<typename T>
constexpr mat<T, 4> mat4_shear_x(T y, T z);

//! Returns a shear transformation about the `y` axis in `x` and/or `z`.
template<typename T>
constexpr mat<T, 4> mat4_shear_y(T x, T z);

//! Returns a shear transformation about the `z` axis in `x` and/or `y`.
template<typename T>
constexpr mat<T, 4> mat4_shear_z(T x, T y);

//! Returns if two point2 types are the same as each other (within a certain
//! tolerance).
bool point_equal(
  const point2& lhs, const point2& rhs,
  real epsilon = std::numeric_limits<real>::epsilon());

//! Returns if two point3 types are the same as each other (within a certain
//! tolerance).
bool point_equal(
  const point3& lhs, const point3& rhs,
  real epsilon = std::numeric_limits<real>::epsilon());

//! Returns the average position of an array of points.
//! \note This is provided as adding points together is not supported.
template<typename point>
point point_average(const point* points, index count);

//! Returns the average position of a parameter pack of points.
//! \note This is provided as adding points together is not supported.
template<typename... points_t>
auto point_average_fold(points_t&&... points);

//! Returns the dot product of two quaternions.
//! \note The corresponding scalar parts are multiplied together and then
//! summed.
constexpr real quat_dot(const quat& lhs, const quat& rhs);

//! Returns the length (magnitude) squared of the quaternion.
constexpr real quat_length_sq(const quat& q);

//! Returns the length (magnitude) of the quaternion.
real quat_length(const quat& q);

//! Returns the conjugate of the quaternion.
//! \note The sign of the imaginary parts are flipped.
//! \note Represents the same rotation as the initial quaternion in the reverse
//! direction.
constexpr quat quat_conjugate(const quat& q);

//! Returns a quaternion representing a rotation about the given axis.
//! \param axis The axis of rotation.
//! \param radians The amount to rotate by in radians.
quat quat_rotation_axis(const vec3& axis, real radians);

//! Returns a rotation about x, then y, then z.
quat quat_rotation_xyz(real x, real y, real z);

//! Returns a rotation about z, then x, then y.
quat quat_rotation_zxy(real x, real y, real z);

//! Returns the input quaternion normalized.
quat quat_normalize(const quat& q);

//! Returns the inverse of the quaternion.
//! \note This is the same as the conjugate if the quaternion is normalized
//! (unit length).
quat quat_inverse(const quat& q);

//! Returns the input vector rotated by the given quaternion.
vec3 quat_rotate(const quat& q, const vec3& v);

//! Returns the result of a spherical interpolation between the two quaternions
//! by ratio `t`.
//! \note `t` should be in the range `[0-1]`.
quat quat_slerp(const quat& lhs, const quat& rhs, real t);

//! Converts a rotation matrix to a quaternion.
//! \note Ensure ::mat3 is a valid rotation.
quat quat_from_mat3(const mat3& m);

//! Writes the values stored in the affine to an array of the same type and
//! dimension.
//! \note affine uses a ::mat3 and a ::vec3 internally.
void quat_to_arr(const affine& a, real (&data)[12]);

//! Creates an affine from a fixed size array of the same type and dimension.
//! \note affine uses a ::mat3 and a ::vec3 internally.
affine affine_from_arr(const real (&data)[12]);

//! Creates an affine from a pointer to an array of the same type.
//! \note Ensure that the array has at least 12 elements from where it is read.
affine affine_from_ptr(const real* data);

//! Returns an affine from a ::mat4.
//! \note Ensure that the ::mat4 holds a valid a transformation
//! (translation/scale/rotation) and not a non-affine transformation such as a
//! projection.
affine affine_from_mat4(const mat4& m);

//! Returns an affine from a ::mat3.
//! \note Ensure that the ::mat3 holds a valid a transformation
//! (scale/rotation)
//! \note The translation portion of affine will be zero.
affine affine_from_mat3(const mat3& m);

//! Returns an affine from a ::mat3 and a ::vec3.
//! \note Ensure that the ::mat3 holds a valid a transformation
//! (scale/rotation)
affine affine_from_mat3_vec3(const mat3& m, const vec3& v);

//! Returns an affine from a ::vec3.
//! \note The rotation part will be initialized to the identity.
affine affine_from_vec3(const vec3& v);

//! Returns an affine from a point3.
//! \note The rotation part will be initialized to the identity.
affine affine_from_point3(const point3& p);

//! Returns the result of two affine types multiplied together.
//! \note `lhs` is performed first, then `rhs`
affine affine_mul(const affine& lhs, const affine& rhs);

//! Returns the inverse of the affine.
//! ```{.cpp}
//! // a * inv(a) = identity
//! ```
//! \note The inverse of affine is just the transpose of the rotation part,
//! so ensure it holds a valid a transformation (axes are orthogonal).
affine affine_inverse(const affine& a);

//! Returns the input direction transformed by the affine.
//! \note No translation occurs, just rotation.
vec3 affine_transform_dir(const affine& a, const vec3& direction);

//! Returns the input position transformed by the affine.
//! \note No rotation occurs, just translation.
vec3 affine_transform_pos(const affine& a, const vec3& position);

//! Returns the input position transformed by the affine.
//! \note No rotation occurs, just translation.
point3 affine_transform_pos(const affine& a, const point3& position);

//! Returns the input direction transformed by the inverse of the affine.
//! \note No translation occurs, just rotation.
vec3 affine_inv_transform_dir(const affine& a, const vec3& direction);

//! Returns the input position transformed by the inverse of the affine.
//! \note No rotation occurs, just translation.
vec3 affine_inv_transform_pos(const affine& a, const vec3& position);

//! Returns the input position transformed by the inverse of the affine.
//! \note No rotation occurs, just translation.
point3 affine_inv_transform_pos(const affine& a, const point3& position);

} // namespace as

#include "as-math-ops.inl"
