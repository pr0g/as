#pragma once

#include <algorithm>
#include <type_traits>

#include "src/core/as-types.hpp"
#include "src/math/as-vec.hpp"

namespace as
{

// static assert to check library matrix convention has been set correctly
#if (!defined(AS_COL_MAJOR) && !defined(AS_ROW_MAJOR))
    static_assert(false, "Must define AS_COL_MAJOR or AS_ROW_MAJOR");
#elif (defined(AS_COL_MAJOR) && defined(AS_ROW_MAJOR))
    static_assert(false, "Must define only AS_COL_MAJOR or AS_ROW_MAJOR");
#endif // AS_ROW_MAJOR ? AS_COL_MAJOR

template<typename T, size_t r, size_t c>
struct mat_t
{
    T elem_rc[r][c];
    static const size_t size = r * c;

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

    template<typename...> struct typelist;
    template<typename... Args, typename = std::enable_if_t<!std::is_same<typelist<mat_t>, typelist<std::decay_t<Args>...>>::value>>
    mat_t(Args&&... args) noexcept : elem_rc { std::forward<Args>(args)... } {}
};

template <typename T, size_t r, size_t c>
inline mat_t<T, r, c> operator*(const mat_t<T, r, c>& lhs, const mat_t<T, r, c>& rhs);

template<typename T, size_t r, size_t c, size_t n>
#if defined AS_ROW_MAJOR
inline vec_t<T, n> operator*(const vec_t<T, n> v, const mat_t<T, r, c>& mat);
#elif defined AS_COL_MAJOR
inline vec_t<T, n> operator*(const mat_t<T, r, c>& mat, const vec_t<T, n> v);
#endif // AS_ROW_MAJOR ? AS_COL_MAJOR

template<typename T, size_t r, size_t c>
inline mat_t<T, r, c> operator*(const mat_t<T, r, c>& mat, T scalar);

template<typename T, size_t r, size_t c>
inline void operator*=(mat_t<T, r, c>& mat, T scalar);

} // namespace as

#include "as-mat.inl"