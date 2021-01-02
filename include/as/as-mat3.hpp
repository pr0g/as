//! \file
//! as-mat3

#pragma once

#include "as-mat.hpp"

namespace as
{

//! Partial template specialization of \ref mat for a three dimensional
//! matrix.
template<typename T>
struct mat<T, 3>
{
  //! Type alias for template parameter `T`.
  using value_type = T;

  mat() noexcept = default;

  //! Constructs a mat<T, 3> from individual elements of type `T`.
  // clang-format off
  constexpr mat(
    T x0, T y0, T z0,
    T x1, T y1, T z1,
    T x2, T y2, T z2);
  // clang-format on

#ifdef AS_ROW_MAJOR
  //! Constructs a mat<T, 3> from three row vectors of type `<T,3>`.
  //! \note This signature is only available when `AS_ROW_MAJOR` is defined.
  constexpr mat(
    const vec<T, 3>& row0, const vec<T, 3>& row1, const vec<T, 3>& row2);
#elif defined AS_COL_MAJOR
  //! Constructs a mat<T, 3> from three column vectors of type `<T,3>`.
  //! \note This signature is only available when `AS_COL_MAJOR` is defined.
  constexpr mat(
    const vec<T, 3>& col0, const vec<T, 3>& col1, const vec<T, 3>& col2);
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

  //! Returns `3`, the dimension of the matrix.
  constexpr static index dim();
  //! Returns `3`, the number of columns in the matrix.
  constexpr static index cols();
  //! Returns `3` the number of rows in the matrix.
  constexpr static index rows();
  //! Returns `9`, the number of elements in the matrix.
  constexpr static index size();

  //! Returns the identity matrix.
  constexpr static mat<T, 3> identity();

private:
  T elem_rc[size()]; //!< Elements of the matrix.
};

//! Type alias for a three dimensional matrix of type ::real.
using mat3 = mat<real, 3>;
//! Type alias for a three dimensional matrix of type `float`.
using mat3f = mat<float, 3>;
//! Type alias for a three dimensional matrix of type `double`.
using mat3d = mat<double, 3>;
//! Type alias for a three dimensional matrix of type `int32_t`.
using mat3i = mat<int32_t, 3>;
//! Type alias for a three dimensional matrix of type `int64_t`.
using mat3l = mat<int64_t, 3>;

} // namespace as

#include "as-mat3.inl"
