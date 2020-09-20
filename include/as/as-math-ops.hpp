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

//! Creates a vector from a pointer to an array of the same type.
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

//! Returns the length squared of the vector.
template<typename T, index_t d>
constexpr T length_sq(const vec_t<T, d>& vec);

//! Returns the length of the vector.
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

//! Returns a vector with the absolute value of each element of the input
//! vector.
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

//! Creates a vec_t<T, 2> from a fixed size array of the same type and
//! dimension.
template<typename T>
vec_t<T, 2> from_arr(const T (&data)[2]);

//! Creates a vec_t<T, 2> from a pointer to an array of the same type.
template<typename T>
vec_t<T, 2> from_ptr(const T* data);

//! Returns a vec_t<T, 2> with the first and second element of the vec_t<T, 3>.
template<typename T>
constexpr vec_t<T, 2> from_vec3(const vec_t<T, 3>& vec);

//! Returns a vec_t<T, 2> with the first and second element of the vec_t<T, 4>.
template<typename T>
constexpr vec_t<T, 2> from_vec4(const vec_t<T, 4>& vec);

//! Returns the signed area formed by two vectors.
//! \note This is similar to the cross product of two 3d vectors.
template<typename T>
constexpr T wedge(const vec_t<T, 2>& lhs, const vec_t<T, 2>& rhs);

} // namespace vec2

//! Encapsulates all vec_t<T, 3> related functionality.
namespace vec3
{

//! Creates a vec_t<T, 3> from a fixed size array of the same type and
//! dimension.
template<typename T>
vec_t<T, 3> from_arr(const T (&data)[3]);

//! Creates a vec_t<T, 3> from a pointer to an array of the same type.
template<typename T>
vec_t<T, 3> from_ptr(const T* data);

//! Returns a vec_t<T, 3> with the elements of the vec_t<T, 2> and an optional
//! third parameter (defaulted to zero).
template<typename T>
constexpr vec_t<T, 3> from_vec2(const vec_t<T, 2>& vec, T z = T(0.0));

//! Returns a vec_t<T, 3> with the first and second element of the vec_t<T, 4>.
template<typename T>
constexpr vec_t<T, 3> from_vec4(const vec_t<T, 4>& vec);

//! Returns a vec_t<T, 3> orthogonal to both input vectors.
//! \note If the two input vectors are perpendicular the result will be zero
//! (undefined).
//! \note The order of the input vectors is important. The sign of the resulting
//! vector will vary depending on the order.
template<typename T>
constexpr vec_t<T, 3> cross(const vec_t<T, 3>& lhs, const vec_t<T, 3>& rhs);

//! Sets the across and up axes for the given input vector so all axes remain
//! orthogonal to one another.
//! \note Across and up will be invalid if dir is equal to +/-world_up.
//! \note Expects a left-handed coordinate system.
template<typename T>
void right_and_up_lh(
  const vec_t<T, 3>& dir, vec_t<T, 3>& across, vec_t<T, 3>& up,
  const vec_t<T, 3>& world_up = vec_t<T, 3>::axis_y());

//! Sets the across and up axes for the given input vector so all axes remain
//! orthogonal to one another.
//! \note Across and up will be invalid if dir is equal to +/-world_up.
//! \note Expects a right-handed coordinate system.
template<typename T>
void right_and_up_rh(
  const vec_t<T, 3>& dir, vec_t<T, 3>& across, vec_t<T, 3>& up,
  const vec_t<T, 3>& world_up = vec_t<T, 3>::axis_y());

//! Returns an orthonormal basis for the given input vector.
//! \note This should be preferred to `right_and_up` variants.
template<typename T>
mat_t<T, 3> orthonormal_basis(const vec_t<T, 3>& u);

} // namespace vec3

//! Encapsulates all vec_t<T, 4> related functionality.
namespace vec4
{

//! Creates a vec_t<T, 4> from a fixed size array of the same type and
//! dimension.
template<typename T>
vec_t<T, 4> from_arr(const T (&data)[4]);

//! Creates a vec_t<T, 4> from a pointer to an array of the same type.
template<typename T>
vec_t<T, 4> from_ptr(const T* data);

//! Returns a vec_t<T, 4> with the elements of the vec_t<T, 2> and optional
//! remaining parameters (defaulted to zero).
template<typename T>
constexpr vec_t<T, 4> from_vec2(
  const vec_t<T, 2>& vec, T z = T(0.0), T w = T(0.0));

//! Returns a vec_t<T, 4> with the elements of the vec_t<T, 3> and an optional
//! fourth parameter (defaulted to zero).
template<typename T>
constexpr vec_t<T, 4> from_vec3(const vec_t<T, 3>& vec, T w = T(0.0));

//! Returns a vec4_t from a point3_t.
//! \note The fourth paramter of the vec4_t will be set to 1.
vec4_t from_point3(const point3_t& point);

} // namespace vec4

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
constexpr index_t mat_rc(index_t r, index_t c, index_t d);

//! Returns the nth row of the matrix.
//! \param mat The matrix to use.
//! \param r Row index.
template<typename T, index_t d>
vec_t<T, d> mat_row(const mat_t<T, d>& mat, index_t r);

//! Returns the nth column of the matrix.
//! \param mat The matrix to use.
//! \param c Column index.
template<typename T, index_t d>
vec_t<T, d> mat_col(const mat_t<T, d>& mat, index_t c);

//! Sets the nth row of the matrix.
//! \param mat The matrix to use.
//! \param r Row index.
//! \param row The vector to use.
template<typename T, index_t d>
constexpr void mat_row(mat_t<T, d>& mat, index_t r, const vec_t<T, d>& row);

//! Sets the nth column of the matrix.
//! \param mat The matrix to use.
//! \param c Column index.
//! \param col The vector to use.
template<typename T, index_t d>
constexpr void mat_col(mat_t<T, d>& mat, index_t c, const vec_t<T, d>& col);

//! Returns a pointer to the start of the matrix data.
template<typename T, index_t d>
T* mat_data(mat_t<T, d>& mat);

//! Returns a const pointer to the start of the matrix data.
template<typename T, index_t d>
const T* mat_const_data(const mat_t<T, d>& mat);

//! Creates a mat_t from a fixed size array of the same type and dimension.
template<typename T, index_t d>
mat_t<T, d> mat_from_arr(const T (&data)[d * d]);

//! Creates a mat_t from a pointer to an array of the same type.
template<typename T, index_t d>
mat_t<T, d> mat_from_ptr(const T* data);

//! Writes the values stored in the matrix to an array of the same type and
//! dimension.
template<typename T, index_t d>
void mat_to_arr(const mat_t<T, d>& mat, T (&data)[d * d]);

//! Returns if two matrices are the same as each other (within a certain
//! tolerance).
template<typename T, index_t d>
bool mat_equal(
  const mat_t<T, d>& lhs, const mat_t<T, d>& rhs,
  real_t epsilon = std::numeric_limits<real_t>::epsilon());

//! Returns the transpose of the matrix.
//! \note Rows and columns are swapped.
template<typename T, index_t d>
mat_t<T, d> mat_transpose(const mat_t<T, d>& mat);

//! Returns the determinant of the matrix.
//! \note This is the signed volume of the n-dimensional parallelepiped spanned
//! by the column or row vectors of the matrix.
template<typename T, index_t d>
T mat_determinant(const mat_t<T, d>& mat);

//! Returns the inverse of the matrix.
//! ```{.cpp}
//! // mat * inv(mat) = identity
//! ```
template<typename T, index_t d>
mat_t<T, d> mat_inverse(const mat_t<T, d>& mat);

//! Returns the result of two `mat_t` types multiplied together.
//! \note `lhs` is performed first, then `rhs`
//! ```{.cpp}
//! // Column major
//! result = rhs * lhs; // right to left
//! // Row major
//! result = lhs * rhs; // left ro right
//! ```
template<typename T, index_t d>
mat_t<T, d> mat_mul(const mat_t<T, d>& lhs, const mat_t<T, d>& rhs);

//! Performs a mapping from a row and column index to a single offset for
//! ::mat3_t. \param r Row index. \param c Column index.
constexpr index_t mat3_rc(index_t r, index_t c);

//! Returns the first row of the ::mat3_t.
template<typename T>
constexpr vec_t<T, 3> mat3_row0(const mat_t<T, 3>& mat);

//! Returns the second row of the ::mat3_t.
template<typename T>
constexpr vec_t<T, 3> mat3_row1(const mat_t<T, 3>& mat);

//! Returns the third row of the ::mat3_t.
template<typename T>
constexpr vec_t<T, 3> mat3_row2(const mat_t<T, 3>& mat);

//! Returns the first column of the ::mat3_t.
template<typename T>
constexpr vec_t<T, 3> mat3_col0(const mat_t<T, 3>& mat);

//! Returns the second column of the ::mat3_t.
template<typename T>
constexpr vec_t<T, 3> mat3_col1(const mat_t<T, 3>& mat);

//! Returns the third column of the ::mat3_t.
template<typename T>
constexpr vec_t<T, 3> mat3_col2(const mat_t<T, 3>& mat);

//! Sets the first row of the ::mat3_t.
template<typename T>
constexpr void mat3_row0(mat_t<T, 3>& mat, const vec_t<T, 3>& row);

//! Sets the second row of the ::mat3_t.
template<typename T>
constexpr void mat3_row1(mat_t<T, 3>& mat, const vec_t<T, 3>& row);

//! Sets the third row of the ::mat3_t.
template<typename T>
constexpr void mat3_row2(mat_t<T, 3>& mat, const vec_t<T, 3>& row);

//! Sets the first column of the ::mat3_t.
template<typename T>
constexpr void mat3_col0(mat_t<T, 3>& mat, const vec_t<T, 3>& col);

//! Sets the second column of the ::mat3_t.
template<typename T>
constexpr void mat3_col1(mat_t<T, 3>& mat, const vec_t<T, 3>& col);

//! Sets the third column of the ::mat3_t.
template<typename T>
constexpr void mat3_col2(mat_t<T, 3>& mat, const vec_t<T, 3>& col);

//! Returns the x basis vector for the ::mat3_t.
template<typename T>
constexpr vec_t<T, 3> mat3_basis_x(const mat_t<T, 3>& mat);

//! Returns the y basis vector for the ::mat3_t.
template<typename T>
constexpr vec_t<T, 3> mat3_basis_y(const mat_t<T, 3>& mat);

//! Returns the z basis vector for the ::mat3_t.
template<typename T>
constexpr vec_t<T, 3> mat3_basis_z(const mat_t<T, 3>& mat);

//! Sets the x basis vector for the ::mat3_t.
template<typename T>
constexpr void mat3_basis_x(mat_t<T, 3>& mat, const vec_t<T, 3>& basis);

//! Sets the y basis vector for the ::mat3_t.
template<typename T>
constexpr void mat3_basis_y(mat_t<T, 3>& mat, const vec_t<T, 3>& basis);

//! Sets the z basis vector for the ::mat3_t.
template<typename T>
constexpr void mat3_basis_z(mat_t<T, 3>& mat, const vec_t<T, 3>& basis);

//! Creates a mat_t<T, 3> from a fixed size array of the same type and
//! dimension.
template<typename T>
mat_t<T, 3> mat3_from_arr(const T (&data)[9]);

//! Creates a mat_t<T, 3> from a pointer to an array of the same type.
template<typename T>
mat_t<T, 3> mat3_from_ptr(const T* data);

//! Returns a mat_t<T, 3> from a mat_t<T, 4>.
//! \note The upper 3x3 part of the 4x4 matrix is returned.
template<typename T>
constexpr mat_t<T, 3> mat3_from_mat4(const mat_t<T, 4>& transform);

//! Returns a rotation about a given axis.
//! \param axis The axis of rotation.
//! \param radians The amount to rotate by in radians.
mat3_t mat3_rotation_axis(const vec3_t& axis, real_t radians);

//! Returns a rotation about `x`, then `y`, then `z`.
mat3_t mat3_rotation_xyz(real_t x, real_t y, real_t z);

//! Returns a rotation about `z`, then `x`, then `y`.
//! \note This is often useful for free-look cameras.
mat3_t mat3_rotation_zxy(real_t x, real_t y, real_t z);

//! Returns a rotation about the x axis.
mat3_t mat3_rotation_x(real_t radians);

//! Returns a rotation about the y axis.
mat3_t mat3_rotation_y(real_t radians);

//! Returns a rotation about the z axis.
mat3_t mat3_rotation_z(real_t radians);

//! Returns a uniform scale martix.
constexpr mat3_t mat3_scale(real_t scale);

//! Returns a (potentially) non-uniform scale martix.
constexpr mat3_t mat3_scale(real_t x, real_t y, real_t z);

//! Returns a (potentially) non-uniform scale martix.
constexpr mat3_t mat3_scale(const vec3_t& scale);

//! Returns a ::mat3_t from a quaternion.
constexpr mat3_t mat3_from_quat(const quat_t& quat);

//! Performs a mapping from a row and column index to a single offset for
//! ::mat4_t. \param r Row index. \param c Column index.
constexpr index_t mat4_rc(index_t r, index_t c);

//! Returns the first row of the ::mat4_t.
template<typename T>
constexpr vec_t<T, 4> mat4_row0(const mat_t<T, 4>& mat);

//! Returns the second row of the ::mat4_t.
template<typename T>
constexpr vec_t<T, 4> mat4_row1(const mat_t<T, 4>& mat);

//! Returns the third row of the ::mat4_t.
template<typename T>
constexpr vec_t<T, 4> mat4_row2(const mat_t<T, 4>& mat);

//! Returns the fourth row of the ::mat4_t.
template<typename T>
constexpr vec_t<T, 4> mat4_row3(const mat_t<T, 4>& mat);

//! Returns the first column of the ::mat4_t.
template<typename T>
constexpr vec_t<T, 4> mat4_col0(const mat_t<T, 4>& mat);

//! Returns the second column of the ::mat4_t.
template<typename T>
constexpr vec_t<T, 4> mat4_col1(const mat_t<T, 4>& mat);

//! Returns the third column of the ::mat4_t.
template<typename T>
constexpr vec_t<T, 4> mat4_col2(const mat_t<T, 4>& mat);

//! Returns the fourth column of the ::mat4_t.
template<typename T>
constexpr vec_t<T, 4> mat4_col3(const mat_t<T, 4>& mat);

//! Sets the first row of the ::mat4_t.
template<typename T>
constexpr void mat4_row0(const mat_t<T, 4>& mat, const vec_t<T, 4>& row);

//! Sets the second row of the ::mat4_t.
template<typename T>
constexpr void mat4_row1(const mat_t<T, 4>& mat, const vec_t<T, 4>& row);

//! Sets the third row of the ::mat4_t.
template<typename T>
constexpr void mat4_row2(const mat_t<T, 4>& mat, const vec_t<T, 4>& row);

//! Sets the fourth row of the ::mat4_t.
template<typename T>
constexpr void mat4_row3(const mat_t<T, 4>& mat, const vec_t<T, 4>& row);

//! Sets the first column of the ::mat4_t.
template<typename T>
constexpr void mat4_col0(const mat_t<T, 4>& mat, const vec_t<T, 4>& col);

//! Sets the second column of the ::mat4_t.
template<typename T>
constexpr void mat4_col1(const mat_t<T, 4>& mat, const vec_t<T, 4>& col);

//! Sets the third column of the ::mat4_t.
template<typename T>
constexpr void mat4_col2(const mat_t<T, 4>& mat, const vec_t<T, 4>& col);

//! Sets the fourth column of the ::mat4_t.
template<typename T>
constexpr void mat4_col3(const mat_t<T, 4>& mat, const vec_t<T, 4>& col);

//! Returns the x basis vector for the ::mat4_t.
//! \note The fourth (w) element of the vector will be `0`.
template<typename T>
constexpr vec_t<T, 4> mat4_basis_x(const mat_t<T, 4>& mat);

//! Returns the y basis vector for the ::mat4_t.
//! \note The fourth (w) element of the vector will be `0`.
template<typename T>
constexpr vec_t<T, 4> mat4_basis_y(const mat_t<T, 4>& mat);

//! Returns the z basis vector for the ::mat4_t.
//! \note The fourth (w) element of the vector will be `0`.
template<typename T>
constexpr vec_t<T, 4> mat4_basis_z(const mat_t<T, 4>& mat);

//! Returns the translation component of the ::mat4_t.
//! \note The fourth (w) element of the vector will be `1`.
template<typename T>
constexpr vec_t<T, 4> mat4_translation(const mat_t<T, 4>& mat);

//! Sets the x basis vector for the ::mat4_t.
template<typename T>
constexpr void mat4_basis_x(mat_t<T, 4>& mat, const vec_t<T, 4>& basis);

//! Sets the y basis vector for the ::mat4_t.
template<typename T>
constexpr void mat4_basis_y(mat_t<T, 4>& mat, const vec_t<T, 4>& basis);

//! Sets the z basis vector for the ::mat4_t.
template<typename T>
constexpr void mat4_basis_z(mat_t<T, 4>& mat, const vec_t<T, 4>& basis);

//! Sets the translation component for the ::mat4_t.
//! \note The vec4_t should usually have its fourth (w) component set to `1`.
template<typename T>
constexpr void mat4_translation(mat_t<T, 4>& mat, const vec_t<T, 4>& translation);

//! Creates a mat_t<T, 4> from a fixed size array of the same type and
//! dimension.
template<typename T>
mat_t<T, 4> mat4_from_arr(const T (&data)[16]);

//! Creates a mat_t<T, 3> from a pointer to an array of the same type.
template<typename T>
mat_t<T, 4> mat4_from_ptr(const T* data);

//! Returns a mat_t<T, 4> from a vec_t<T, 3>.
//! \note The upper 3x3 part of the 4x4 matrix is the identity.
template<typename T>
constexpr mat_t<T, 4> mat4_from_vec3(const vec_t<T, 3>& translation);

//! Returns a mat_t<T, 4> from a mat_t<T, 3>.
//! \note The translation part of the 4x4 matrix will be `(0, 0, 0, 1)`.
template<typename T>
constexpr mat_t<T, 4> mat4_from_mat3(const mat_t<T, 3>& rotation);

//! Returns a mat_t<T, 4> from a mat_t<T, 3> and a vec_t<T, 3>.
template<typename T>
constexpr mat_t<T, 4> mat4_from_mat3_vec3(
  const mat_t<T, 3>& rotation, const vec_t<T, 3>& translation);

//! Returns a mat_t<T, 4> from an affine_t.
//! \note The effect of the transformation will be the same, it is only the type
//! that changes.
constexpr mat4_t mat4_from_affine(const affine_t& affine);

//! Returns a shear transformation about the `x` axis in `y` and/or `z`.
template<typename T>
constexpr mat_t<T, 4> mat4_shear_x(T y, T z);

//! Returns a shear transformation about the `y` axis in `x` and/or `z`.
template<typename T>
constexpr mat_t<T, 4> mat4_shear_y(T x, T z);

//! Returns a shear transformation about the `z` axis in `x` and/or `y`.
template<typename T>
constexpr mat_t<T, 4> mat4_shear_z(T x, T y);

//! Returns if two point2_t types are the same as each other (within a certain
//! tolerance).
bool point_equal(
  const point2_t& lhs, const point2_t& rhs,
  real_t epsilon = std::numeric_limits<real_t>::epsilon());

//! Returns if two point3_t types are the same as each other (within a certain
//! tolerance).
bool point_equal(
  const point3_t& lhs, const point3_t& rhs,
  real_t epsilon = std::numeric_limits<real_t>::epsilon());

//! Returns the average position of an array of points.
//! \note This is provided as adding points together is not supported.
template<typename point_t>
point_t point_average(const point_t* points, index_t count);

//! Returns the average position of a parameter pack of points.
//! \note This is provided as adding points together is not supported.
template<typename... points_t>
auto point_average_fold(points_t&&... points);

//! Returns the dot product of two quaternions.
//! \note The corresponding scalar parts are multiplied together and then
//! summed.
constexpr real_t quat_dot(const quat_t& lhs, const quat_t& rhs);

//! Returns the length (magnitude) squared of the quaternion.
constexpr real_t quat_length_sq(const quat_t& quat);

//! Returns the length (magnitude) of the quaternion.
real_t quat_length(const quat_t& quat);

//! Returns the conjugate of the quaternion.
//! \note The sign of the imaginary parts are flipped.
//! \note Represents the same rotation as the initial quaternion in the reverse
//! direction.
constexpr quat_t quat_conjugate(const quat_t& quat);

//! Returns a quaternion representing a rotation about the given axis.
//! \param axis The axis of rotation.
//! \param radians The amount to rotate by in radians.
quat_t quat_rotation_axis(const vec3_t& axis, real_t radians);

//! Returns a rotation about z, then x, then y.
quat_t quat_rotation_zxy(real_t x, real_t y, real_t z);

//! Returns the input quaternion normalized.
quat_t quat_normalize(const quat_t& quat);

//! Returns the inverse of the quaternion.
//! \note This is the same as the conjugate if the quaternion is normalized
//! (unit length).
quat_t quat_inverse(const quat_t& quat);

//! Returns the input vector rotated by the given quaternion.
vec3_t quat_rotate(const quat_t& quat, const vec3_t& v);

//! Returns the result of a spherical interpolation between the two quaternions
//! by ratio `t`.
//! \note `t` should be in the range `[0-1]`.
quat_t quat_slerp(const quat_t& lhs, const quat_t& rhs, real_t t);

//! Converts a rotation matrix to a quaternion.
//! \note Ensure ::mat3_t is a valid rotation.
quat_t quat_from_mat3(const mat3_t& mat);

//! Writes the values stored in the affine_t to an array of the same type and
//! dimension.
//! \note affine_t uses a ::mat3_t and a ::vec3_t internally.
void quat_to_arr(const affine_t& affine, real_t (&data)[12]);

//! Creates an affine_t from a fixed size array of the same type and dimension.
//! \note affine_t uses a ::mat3_t and a ::vec3_t internally.
affine_t affine_from_arr(const real_t (&data)[12]);

//! Creates an affine_t from a pointer to an array of the same type.
//! \note Ensure that the array has at least 12 elements from where it is read.
affine_t affine_from_ptr(const real_t* data);

//! Returns an affine_t from a ::mat4_t.
//! \note Ensure that the ::mat4_t holds a valid affine transformation
//! (translation/scale/rotation) and not a non-affine transformation such as a
//! projection.
affine_t affine_from(const mat4_t& mat);

//! Returns an affine_t from a ::mat3_t.
//! \note Ensure that the ::mat3_t holds a valid affine transformation
//! (scale/rotation)
//! \note The translation portion of affine_t will be zero.
affine_t affine_from(const mat3_t& mat);

//! Returns an affine_t from a ::mat3_t and a ::vec3_t.
//! \note Ensure that the ::mat3_t holds a valid affine transformation
//! (scale/rotation)
affine_t affine_from(const mat3_t& mat, const vec3_t& vec);

//! Returns an affine_t from a ::vec3_t.
//! \note The rotation part will be initialized to the identity.
affine_t affine_from(const vec3_t& vec);

//! Returns an affine_t from a point3_t.
//! \note The rotation part will be initialized to the identity.
affine_t affine_from(const point3_t& point);

//! Returns the result of two affine_t types multiplied together.
//! \note `lhs` is performed first, then `rhs`
affine_t affine_mul(const affine_t& lhs, const affine_t& rhs);

//! Returns the inverse of the affine_t.
//! ```{.cpp}
//! // affine * inv(affine) = identity
//! ```
//! \note The inverse of affine_t is just the transpose of the rotation part,
//! so ensure it holds a valid affine transformation (axes are orthogonal).
affine_t affine_inverse(const affine_t& affine);

//! Returns the input direction transformed by the affine_t.
//! \note No translation occurs, just rotation.
vec3_t affine_transform_dir(const affine_t& affine, const vec3_t& direction);

//! Returns the input position transformed by the affine_t.
//! \note No rotation occurs, just translation.
vec3_t affine_transform_pos(const affine_t& affine, const vec3_t& position);

//! Returns the input position transformed by the affine_t.
//! \note No rotation occurs, just translation.
point3_t affine_transform_pos(const affine_t& affine, const point3_t& position);

//! Returns the input direction transformed by the inverse of the affine_t.
//! \note No translation occurs, just rotation.
vec3_t affine_inv_transform_dir(
  const affine_t& affine, const vec3_t& direction);

//! Returns the input position transformed by the inverse of the affine_t.
//! \note No rotation occurs, just translation.
vec3_t affine_inv_transform_pos(const affine_t& affine, const vec3_t& position);

//! Returns the input position transformed by the inverse of the affine_t.
//! \note No rotation occurs, just translation.
point3_t affine_inv_transform_pos(
  const affine_t& affine, const point3_t& position);

} // namespace as

#include "as-math-ops.inl"
