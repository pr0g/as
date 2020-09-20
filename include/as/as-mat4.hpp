//! \file
//! as-mat3

#pragma once

#include "as-mat.hpp"
#include "as-mat3.hpp"

namespace as
{

//! Partial template specialization of \ref mat for a four dimensional matrix.
template<typename T>
struct mat<T, 4>
{
  //! Type alias for template parameter `T`.
  using value_type = T;

  mat() noexcept = default;

  //! Constructs a mat<T, 4> from individual elements of type `T`.
  // clang-format off
    constexpr mat(
        T x0, T y0, T z0, T w0,
        T x1, T y1, T z1, T w1,
        T x2, T y2, T z2, T w2,
        T x3, T y3, T z3, T w3);
  // clang-format on

  //! Constructs mat<T, 4> from a mat<T, 3> and vec<T, 3>.
  constexpr mat(const mat<T, 3>& m, const vec<T, 3>& pos);

#ifdef AS_ROW_MAJOR
  //! Constructs a mat<T, 4> from four row vectors of type `<T,4>`.
  //! \note This signature is only available when `AS_ROW_MAJOR` is defined.
  constexpr mat(
    const vec<T, 4>& row0, const vec<T, 4>& row1, const vec<T, 4>& row2,
    const vec<T, 4>& row3);
#elif defined AS_COL_MAJOR
  //! Constructs a mat<T, 4> from four column vectors of type `<T,4>`.
  //! \note This signature is only available when `AS_COL_MAJOR` is defined.
  constexpr mat(
    const vec<T, 4>& col0, const vec<T, 4>& col1, const vec<T, 4>& col2,
    const vec<T, 4>& col3);
#endif // AS_ROW_MAJOR ? AS_COL_MAJOR

  //! Returns a mutable reference to the value at the given index.
  //! \note Can only be called on a mutable lvalue object.
  //! \warning No bounds checking is performed.
  constexpr T& operator[](index i) &;
  //! Returns a const reference to the value at the given index.
  //! \note Can only be called on a const lvalue object.
  //! \warning No bounds checking is performed.
  constexpr const T& operator[](index i) const&;
  //! Returns a copy of the value at the given index.
  //! \note Can only be called on an rvalue object.
  //! \warning No bounds checking is performed.
  constexpr const T operator[](index i) &&;

  //! Returns `4`, the dimension of the matrix.
  constexpr static index dim();
  //! Returns `4`, the number of columns in the matrix.
  constexpr static index cols();
  //! Returns `4`, the number of rows in the matrix.
  constexpr static index rows();
  //! Returns `16`, the number of elements in the matrix.
  constexpr static index size();

  //! Returns the identity matrix.
  constexpr static mat<T, 4> identity();

private:
  T elem_rc[size()]; //!< Elements of the matrix.
};

//! Type alias for a four dimensional matrix of type ::real.
using mat4 = mat<real, 4>;
//! Type alias for a four dimensional matrix of type `float`.
using mat4f = mat<float, 4>;
//! Type alias for a four dimensional matrix of type `double`.
using mat4d = mat<double, 4>;
//! Type alias for a four dimensional matrix of type `int32_t`.
using mat4i = mat<int32_t, 4>;
//! Type alias for a four dimensional matrix of type `int64_t`.
using mat4l = mat<int64_t, 4>;

} // namespace as

#include "as-mat4.inl"
