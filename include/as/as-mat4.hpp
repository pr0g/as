//! \file
//! as-mat3

#pragma once

#include "as-mat.hpp"
#include "as-mat3.hpp"

namespace as
{

//! Partial template specialization of \ref mat_t for a four dimensional matrix.
template<typename T>
struct mat_t<T, 4>
{
  //! Type alias for template parameter `T`.
  using value_type = T;

  mat_t() noexcept = default;

  //! Constructs a mat_t<T, 4> from individual elements of type `T`.
  // clang-format off
    constexpr mat_t(
        T x0, T y0, T z0, T w0,
        T x1, T y1, T z1, T w1,
        T x2, T y2, T z2, T w2,
        T x3, T y3, T z3, T w3);
  // clang-format on

  //! Constructs mat_t<T, 4> from a mat_t<T, 3> and vec_t<T, 3>.
  constexpr mat_t(const mat_t<T, 3>& mat, const vec_t<T, 3>& pos);

#ifdef AS_ROW_MAJOR
  //! Constructs a mat_t<T, 4> from four row vectors of type `<T,4>`.
  //! \note This signature is only available when `AS_ROW_MAJOR` is defined.
  constexpr mat_t(
    const vec_t<T, 4>& row0, const vec_t<T, 4>& row1, const vec_t<T, 4>& row2,
    const vec_t<T, 4>& row3);
#elif defined AS_COL_MAJOR
  //! Constructs a mat_t<T, 4> from four column vectors of type `<T,4>`.
  //! \note This signature is only available when `AS_COL_MAJOR` is defined.
  constexpr mat_t(
    const vec_t<T, 4>& col0, const vec_t<T, 4>& col1, const vec_t<T, 4>& col2,
    const vec_t<T, 4>& col3);
#endif // AS_ROW_MAJOR ? AS_COL_MAJOR

  //! Returns a mutable reference to the value at the given index.
  //! \note Can only be called on a mutable lvalue object.
  //! \warning No bounds checking is performed.
  constexpr T& operator[](index_t i) &;
  //! Returns a const reference to the value at the given index.
  //! \note Can only be called on a const lvalue object.
  //! \warning No bounds checking is performed.
  constexpr const T& operator[](index_t i) const&;
  //! Returns a copy of the value at the given index.
  //! \note Can only be called on an rvalue object.
  //! \warning No bounds checking is performed.
  constexpr const T operator[](index_t i) &&;

  //! Returns `4`, the dimension of the matrix.
  constexpr static index_t dim();
  //! Returns `4`, the number of columns in the matrix.
  constexpr static index_t cols();
  //! Returns `4`, the number of rows in the matrix.
  constexpr static index_t rows();
  //! Returns `16`, the number of elements in the matrix.
  constexpr static index_t size();

  //! Returns the identity matrix.
  constexpr static mat_t<T, 4> identity();

private:
  T elem_rc[size()]; //!< Elements of the matrix.
};

//! Type alias for a four dimensional matrix of type ::real_t.
using mat4_t = mat_t<real_t, 4>;
//! Type alias for a four dimensional matrix of type `float`.
using mat4f_t = mat_t<float, 4>;
//! Type alias for a four dimensional matrix of type `double`.
using mat4d_t = mat_t<double, 4>;
//! Type alias for a four dimensional matrix of type `int32_t`.
using mat4i_t = mat_t<int32_t, 4>;
//! Type alias for a four dimensional matrix of type `int64_t`.
using mat4l_t = mat_t<int64_t, 4>;

} // namespace as

#include "as-mat4.inl"
