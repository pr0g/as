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

template<typename T, size_t d>
struct mat_t
{
    T elem_rc[d][d];
    static constexpr size_t size = d * d;

    constexpr T& operator[](size_t i) { return elems()[i]; }
    constexpr const T& operator[](size_t i) const { return elems()[i]; }

    T* elems() { return &elem_rc[0][0]; }
    const T* elems() const { return &elem_rc[0][0]; }

    mat_t() = default;
    mat_t(const mat_t& mat) = default;
    mat_t& operator=(const mat_t& mat) = default;
    mat_t(mat_t&& mat) noexcept = default;
    mat_t& operator=(mat_t&& mat) noexcept = default;
    ~mat_t() = default;

    template<typename...> struct typelist {};
    template<
        typename... Args,
        typename = std::enable_if_t<
            !std::is_same<typelist<mat_t>,
            typelist<std::decay_t<Args>...>>::value>>
    mat_t(Args&&... args) noexcept : elem_rc { std::forward<Args>(args)... }
    {
        static_assert(sizeof ...(args) == size, "Not enough arguments for dimension");
    }
};

template <typename T, size_t d>
inline const mat_t<T, d> operator*(const mat_t<T, d>& lhs, const mat_t<T, d>& rhs);

template<typename T, size_t d>
#if defined AS_ROW_MAJOR
inline const vec_t<T, d> operator*(const vec_t<T, d>& v, const mat_t<T, d>& mat);
#elif defined AS_COL_MAJOR
inline const vec_t<T, d> operator*(const mat_t<T, d>& mat, const vec_t<T, d>& v);
#endif // AS_ROW_MAJOR ? AS_COL_MAJOR

template<typename T, size_t d>
inline const mat_t<T, d> operator*(const mat_t<T, d>& mat, T scalar);

template<typename T, size_t d>
inline mat_t<T, d>& operator*=(mat_t<T, d>& mat, T scalar);

} // namespace as

#include "as-mat.inl"
