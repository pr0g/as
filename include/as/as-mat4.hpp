#pragma once

#include "as-mat.hpp"
#include "as-mat3.hpp"

namespace as
{

template<typename T>
struct mat_t<T, 4>
{
    using value_type = T;

    T elem_rc[size()];

    mat_t() noexcept = default;
    mat_t(const mat_t&) noexcept = default;
    mat_t& operator=(const mat_t&) noexcept = default;
    mat_t(mat_t&&) noexcept = default;
    mat_t& operator=(mat_t&&) noexcept = default;
    ~mat_t() = default;

    // clang-format off
    constexpr mat_t(
        T x0, T y0, T z0, T w0,
        T x1, T y1, T z1, T w1,
        T x2, T y2, T z2, T w2,
        T x3, T y3, T z3, T w3);
    // clang-format on

    constexpr mat_t(const mat_t<T, 3>& mat_, const vec_t<T, 3>& pos_);

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
    constexpr static index_t size();

    const vec_t<T, 4> row0() const;
    const vec_t<T, 4> row1() const;
    const vec_t<T, 4> row2() const;
    const vec_t<T, 4> row3() const;
    const vec_t<T, 4> col0() const;
    const vec_t<T, 4> col1() const;
    const vec_t<T, 4> col2() const;
    const vec_t<T, 4> col3() const;

    void row0(const vec_t<T, 4>& row_);
    void row1(const vec_t<T, 4>& row_);
    void row2(const vec_t<T, 4>& row_);
    void row3(const vec_t<T, 4>& row_);
    void col0(const vec_t<T, 4>& col_);
    void col1(const vec_t<T, 4>& col_);
    void col2(const vec_t<T, 4>& col_);
    void col3(const vec_t<T, 4>& col_);

    void row(index_t r, const vec_t<T, 4>& row);
    void col(index_t c, const vec_t<T, 4>& col);
    const vec_t<T, 4> row(index_t r) const;
    const vec_t<T, 4> col(index_t c) const;
};

using mat4_t = mat_t<real_t, 4>;
using mat4f_t = mat_t<float, 4>;
using mat4d_t = mat_t<double, 4>;
using mat4i_t = mat_t<int32_t, 4>;
using mat4l_t = mat_t<int64_t, 4>;

namespace mat4
{

index_t rc(index_t r, index_t c);

} // namespace mat4

} // namespace as

#include "as-mat4.inl"
