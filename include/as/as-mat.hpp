//! \file
//! as-mat

#pragma once

#include <algorithm>
#include <type_traits>

#include "as-vec.hpp"

namespace as
{

// A static_assert to check the library matrix convention has been set correctly.
#if (!defined(AS_COL_MAJOR) && !defined(AS_ROW_MAJOR))
static_assert(false, "Must define AS_COL_MAJOR or AS_ROW_MAJOR");
#elif (defined(AS_COL_MAJOR) && defined(AS_ROW_MAJOR))
static_assert(false, "Must define only AS_COL_MAJOR or AS_ROW_MAJOR");
#endif // AS_ROW_MAJOR ? AS_COL_MAJOR

//! A matrix class template parameterized by type and dimension.
template<typename T, index_t d>
struct mat_t
{
    //! Type alias for template parameter `T`.
    using value_type = T;

    mat_t() noexcept = default;

    template<typename...>
    struct typelist
    {
    };

    //! A variadic template constructor that accepts the same number of elements
    //! as the size of the matrix.
    //! \note Passing the wrong number of elements will result in a compile
    //! error.
    template<
        typename... Args,
        typename = std::enable_if_t<!std::is_same<
            typelist<mat_t>, typelist<std::decay_t<Args>...>>::value>>
    constexpr mat_t(Args... args) noexcept
        : elem_rc{std::forward<Args>(args)...}
    {
        static_assert(
            sizeof...(args) == size(),
            "Incorrent number of arguments for dimension");
    }

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

    //! Returns the dimension of the matrix.
    //! \note This is equal to to the number of rows or columns.
    constexpr static index_t dim();
    //! Returns the number of columns in the matrix.
    constexpr static index_t cols();
    //! Returns the number of rows in the matrix.
    constexpr static index_t rows();
    //! Returns the number of elements in the matrix.
    //! \note This is equal to `rows() * cols()` or `dim() * dim()`.
    constexpr static index_t size();

    //! Returns the identity matrix.
    static mat_t<T, d> identity();

private:
    T elem_rc[size()]; //!< Elements of the matrix.
};

//! Returns the result of `lhs * rhs`.
//! \note Matrix multiplication order is determined by `AS_ROW_MAJOR` or
//! `AS_COL_MAJOR` being defined.
template<typename T, index_t d>
const mat_t<T, d> operator*(const mat_t<T, d>& lhs, const mat_t<T, d>& rhs);

template<typename T, index_t d>
#ifdef AS_ROW_MAJOR
//! Pre-multiplies the vector my the matrix and returns the result.
//! \note This signature is only available when `AS_ROW_MAJOR` is defined.
const vec_t<T, d> operator*(const vec_t<T, d>& vec, const mat_t<T, d>& mat);
#elif defined AS_COL_MAJOR
//! Post-multiplies the vector my the matrix and returns the result.
//! \note This signature is only available when `AS_COL_MAJOR` is defined.
const vec_t<T, d> operator*(const mat_t<T, d>& mat, const vec_t<T, d>& vec);
#endif // AS_ROW_MAJOR ? AS_COL_MAJOR

//! Returns a new matrix with each element multiplied by a scalar.
template<typename T, index_t d>
constexpr const mat_t<T, d> operator*(const mat_t<T, d>& mat, T scalar);

//! Performs a multiplication assignment of a matrix and a scalar.
template<typename T, index_t d>
constexpr mat_t<T, d>& operator*=(mat_t<T, d>& mat, T scalar);

} // namespace as

#include "as-mat.inl"
