#pragma once

#include <algorithm>
#include <type_traits>

#include "src/core/as-types.hpp"
#include "src/math/as-vec-type.hpp"

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
    union
    {
        T elem[r * c];
        T elem_rc[r][c];
        Vec<T, r> vec[c];
    };

    constexpr T& operator[](size_t i) { return elem[i]; }
    constexpr const T& operator[](size_t i) const { return elem[i]; }

    Mat() = default;
    Mat(const Mat& mat) = default;
    Mat& operator=(const Mat& mat) = default;
    Mat(Mat&& mat) noexcept = default;
    Mat& operator=(Mat&& mat) noexcept = default;
    ~Mat() = default;

    template<typename...> struct typelist;
    template<typename... Args, typename = std::enable_if_t<!std::is_same<typelist<Mat>, typelist<std::decay_t<Args>...>>::value>>
    Mat(Args&&... args) noexcept : elem { std::forward<Args>(args)... } {}
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

namespace mat
{

template<typename T, size_t r, size_t c>
inline T* data(const Mat<T, r, c>& mat);

template<typename T, size_t r, size_t c>
inline const T* const_data(const Mat<T, r, c>& mat);

template<typename T, size_t r, size_t c>
inline Mat<T, r, c> from_arr(const T(&data)[r * c]);

template<typename T, size_t r, size_t c>
inline Mat<T, r, c> from_ptr(const T* data);

template<typename T, size_t r, size_t c>
inline Mat<T, r, c> transpose(const Mat<T, r, c>& mat);

template<typename T, size_t cr>
inline Mat<T, cr, cr> identity();

template<typename T, size_t cr>
inline T determinant(const Mat<T, cr, cr>& mat);

template<typename T, size_t cr>
inline Mat<T, cr, cr> inverse(const Mat<T, cr, cr>& mat);

template<typename T, size_t cr>
inline Mat<T, cr, cr> gj_inverse(const Mat<T, cr, cr>& mat);

} // namespace mat

} // namespace as

#include "as-mat-type.inl"