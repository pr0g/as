//! \file
//! as-mat3

#pragma once

#include "as-mat.hpp"

namespace as
{

template<typename T>
struct mat_t<T, 3>
{
    using value_type = T;

    mat_t() noexcept = default;

    // clang-format off
    constexpr mat_t(
        T x0, T y0, T z0,
        T x1, T y1, T z1,
        T x2, T y2, T z2);
    // clang-format on

#ifdef AS_ROW_MAJOR
    constexpr mat_t(
        const vec_t<T, 3>& row0, const vec_t<T, 3>& row1,
        const vec_t<T, 3>& row2);
#elif defined AS_COL_MAJOR
    constexpr mat_t(
        const vec_t<T, 3>& col0, const vec_t<T, 3>& col1,
        const vec_t<T, 3>& col2);
#endif // AS_ROW_MAJOR ? AS_COL_MAJOR

    constexpr T& operator[](index_t i) &;
    constexpr const T& operator[](index_t i) const&;
    constexpr const T operator[](index_t i) &&;

    constexpr static index_t dim();
    constexpr static index_t cols();
    constexpr static index_t rows();
    constexpr static index_t size();
    constexpr static mat_t<T, 3> identity();

private:
    T elem_rc[size()];
};

using mat3_t = mat_t<real_t, 3>;
using mat3f_t = mat_t<float, 3>;
using mat3d_t = mat_t<double, 3>;
using mat3i_t = mat_t<int32_t, 3>;
using mat3l_t = mat_t<int64_t, 3>;

} // namespace as

#include "as-mat3.inl"
