#pragma once

#include <algorithm>
#include <type_traits>

#include "src/core/as-types.hpp"
#include "src/math/as-vec.hpp"

namespace as
{

#ifdef _MSC_VER
__pragma(warning(push))
__pragma(warning(disable:4201))
#endif // _MSC_VER

// static assert to check library matrix convention has been set correctly
#if (!defined(AS_COL_MAJOR) && !defined(AS_ROW_MAJOR))
    static_assert(false, "Must define AS_COL_MAJOR or AS_ROW_MAJOR");
#elif (defined(AS_COL_MAJOR) && defined(AS_ROW_MAJOR))
    static_assert(false, "Must define only AS_COL_MAJOR or AS_ROW_MAJOR");
#endif // AS_ROW_MAJOR ? AS_COL_MAJOR

template<typename T, size_t r, size_t c>
struct Mat
{
    constexpr T& operator[](size_t i) { return elem[i]; }
    constexpr const T& operator[](size_t i) const { return elem[i]; }

    T* elems() { return elem; }
    const T* elems() const { return elem; }

    Mat() = default;
    Mat(const Mat& mat) = default;
    Mat& operator=(const Mat& mat) = default;
    Mat(Mat&& mat) noexcept = default;
    Mat& operator=(Mat&& mat) noexcept = default;
    ~Mat() = default;

    template<typename...> struct typelist;
    template<typename... Args, typename = std::enable_if_t<!std::is_same<typelist<Mat>, typelist<std::decay_t<Args>...>>::value>>
    Mat(Args&&... args) noexcept : elem { std::forward<Args>(args)... } {}

private:
    T elem[r * c];
};

#ifdef _MSC_VER
__pragma(warning(pop))
#endif // _MSC_VER

template <typename T, size_t r, size_t c>
inline Mat<T, r, c> operator*(const Mat<T, r, c>& lhs, const Mat<T, r, c>& rhs);

template<typename T, size_t r, size_t c, size_t n>
#if defined AS_ROW_MAJOR
inline Vec<T, n> operator*(const Vec<T, n> v, const Mat<T, r, c>& mat)
#elif defined AS_COL_MAJOR
inline Vec<T, n> operator*(const Mat<T, r, c>& mat, const Vec<T, n> v);
#endif // AS_ROW_MAJOR ? AS_COL_MAJOR

template<typename T, size_t r, size_t c>
inline Mat<T, r, c> operator*(const Mat<T, r, c>& mat, T scalar);

template<typename T, size_t r, size_t c>
inline void operator*=(Mat<T, r, c>& mat, T scalar);

} // namespace as

#include "as-mat.inl"