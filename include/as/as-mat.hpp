//! \file
//! as-mat

#pragma once

#include <algorithm>
#include <type_traits>

#include "as-vec.hpp"

namespace as
{

// A static_assert to check the library matrix convention has been set
// correctly.
#if (!defined(AS_COL_MAJOR) && !defined(AS_ROW_MAJOR))
static_assert(false, "Must define AS_COL_MAJOR or AS_ROW_MAJOR");
#elif (defined(AS_COL_MAJOR) && defined(AS_ROW_MAJOR))
static_assert(false, "Must define only AS_COL_MAJOR or AS_ROW_MAJOR");
#endif // AS_ROW_MAJOR ? AS_COL_MAJOR

//! A matrix class template parameterized by type and dimension.
template<typename T, index d>
struct mat
{
  //! Type alias for template parameter `T`.
  using value_type = T;

  mat() noexcept = default;

  template<typename...>
  struct typelist
  {
  };

  //! A variadic template constructor that accepts the same number of elements
  //! as the size of the matrix.
  //! \note Passing the wrong number of elements will result in a compile
  //! error.
  template<
    typename... Args, typename = std::enable_if_t<!std::is_same<
                        typelist<mat>, typelist<std::decay_t<Args>...>>::value>>
  constexpr mat(Args... args) noexcept : elem_rc{std::forward<Args>(args)...}
  {
    static_assert(
      sizeof...(args) == size(), "Incorrect number of arguments for dimension");
  }

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

  //! Returns the dimension of the matrix.
  //! \note This is equal to to the number of rows or columns.
  constexpr static index dim();
  //! Returns the number of columns in the matrix.
  constexpr static index cols();
  //! Returns the number of rows in the matrix.
  constexpr static index rows();
  //! Returns the number of elements in the matrix.
  //! \note This is equal to `rows() * cols()` or `dim() * dim()`.
  constexpr static index size();

  //! Returns the identity matrix.
  static mat<T, d> identity();

private:
  T elem_rc[size()]; //!< Elements of the matrix.
};

//! Returns the result of `lhs * rhs`.
//! \note Matrix multiplication order is determined by `AS_ROW_MAJOR` or
//! `AS_COL_MAJOR` being defined.
template<typename T, index d>
const mat<T, d> operator*(const mat<T, d>& lhs, const mat<T, d>& rhs);

template<typename T, index d>
#ifdef AS_ROW_MAJOR
//! Pre-multiplies the vector by the matrix and returns the result.
//! \note This signature is only available when `AS_ROW_MAJOR` is defined.
const vec<T, d> operator*(const vec<T, d>& v, const mat<T, d>& m);
#elif defined AS_COL_MAJOR
//! Post-multiplies the vector by the matrix and returns the result.
//! \note This signature is only available when `AS_COL_MAJOR` is defined.
const vec<T, d> operator*(const mat<T, d>& m, const vec<T, d>& v);
#endif // AS_ROW_MAJOR ? AS_COL_MAJOR

//! Returns a new matrix with each element multiplied by a scalar.
template<typename T, index d>
constexpr const mat<T, d> operator*(const mat<T, d>& m, T scalar);

//! Performs a multiplication assignment of a matrix and a scalar.
template<typename T, index d>
constexpr mat<T, d>& operator*=(mat<T, d>& m, T scalar);

} // namespace as

#include "as-mat.inl"
