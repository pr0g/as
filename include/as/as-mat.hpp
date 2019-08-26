#pragma once

#include <algorithm>
#include <type_traits>

#include "as-vec.hpp"

namespace as
{

// static assert to check library matrix convention has been set correctly
#if (!defined(AS_COL_MAJOR) && !defined(AS_ROW_MAJOR))
static_assert(false, "Must define AS_COL_MAJOR or AS_ROW_MAJOR");
#elif (defined(AS_COL_MAJOR) && defined(AS_ROW_MAJOR))
static_assert(false, "Must define only AS_COL_MAJOR or AS_ROW_MAJOR");
#endif // AS_ROW_MAJOR ? AS_COL_MAJOR

namespace mat
{

AS_API index_t rc(index_t r, index_t c, index_t d);

} // namespace mat

template<typename T, index_t d>
struct mat_t
{
    constexpr static index_t dim() { return d; }
    constexpr static index_t size() { return d * d; }

    using value_type = T;

    T elem_rc[size()];

    constexpr T& operator[](index_t i) & { return elem_rc[i]; }
    constexpr const T& operator[](index_t i) const& { return elem_rc[i]; }
    constexpr const T operator[](index_t i) && { return elem_rc[i]; }

    mat_t() noexcept = default;
    mat_t(const mat_t&) noexcept = default;
    mat_t& operator=(const mat_t&) noexcept = default;
    mat_t(mat_t&&) noexcept = default;
    mat_t& operator=(mat_t&&) noexcept = default;
    ~mat_t() = default;

    template<typename...> struct typelist {};
    template<
        typename... Args,
        typename = std::enable_if_t<
            !std::is_same<typelist<mat_t>,
                typelist<std::decay_t<Args>...>>::value>>
    mat_t(Args... args) noexcept : elem_rc { std::forward<Args>(args)... }
    {
        static_assert(sizeof ...(args) == size(), "Not enough arguments for dimension");
    }
};

template <typename T, index_t d>
AS_API const mat_t<T, d> operator*(const mat_t<T, d>& lhs, const mat_t<T, d>& rhs);

template<typename T, index_t d>
#if defined AS_ROW_MAJOR
AS_API const vec_t<T, d> operator*(const vec_t<T, d>& v, const mat_t<T, d>& mat);
#elif defined AS_COL_MAJOR
AS_API const vec_t<T, d> operator*(const mat_t<T, d>& mat, const vec_t<T, d>& v);
#endif // AS_ROW_MAJOR ? AS_COL_MAJOR

template<typename T, index_t d>
AS_API const mat_t<T, d> operator*(const mat_t<T, d>& mat, T scalar);

template<typename T, index_t d>
AS_API mat_t<T, d>& operator*=(mat_t<T, d>& mat, T scalar);

} // namespace as

#include "as-mat.inl"
