#pragma once

#include "as-mat.hpp"
#include "as-mat3.hpp"

namespace as
{

template<typename T>
struct mat_t<T, 4>
{
    using value_type = T;

    mat_t() noexcept = default;

    // clang-format off
    constexpr mat_t(
        T x0, T y0, T z0, T w0,
        T x1, T y1, T z1, T w1,
        T x2, T y2, T z2, T w2,
        T x3, T y3, T z3, T w3);
    // clang-format on

    constexpr mat_t(const mat_t<T, 3>& mat, const vec_t<T, 3>& pos);

#ifdef AS_ROW_MAJOR
    constexpr mat_t(
        const vec_t<T, 4>& row0, const vec_t<T, 4>& row1,
        const vec_t<T, 4>& row2, const vec_t<T, 4>& row3);
#elif defined AS_COL_MAJOR
    constexpr mat_t(
        const vec_t<T, 4>& col0, const vec_t<T, 4>& col1,
        const vec_t<T, 4>& col2, const vec_t<T, 4>& col3);
#endif // AS_ROW_MAJOR ? AS_COL_MAJOR

    constexpr T& operator[](index_t i) &;
    constexpr const T& operator[](index_t i) const&;
    constexpr const T operator[](index_t i) &&;

    constexpr static index_t dim();
    constexpr static index_t cols();
    constexpr static index_t rows();
    constexpr static index_t size();
    constexpr static mat_t<T, 4> identity();

private:
    T elem_rc[size()];
};

using mat4_t = mat_t<real_t, 4>;
using mat4f_t = mat_t<float, 4>;
using mat4d_t = mat_t<double, 4>;
using mat4i_t = mat_t<int32_t, 4>;
using mat4l_t = mat_t<int64_t, 4>;

} // namespace as

#include "as-mat4.inl"
