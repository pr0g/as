#pragma once

#include "as-mat.hpp"
#include "as-mat3.hpp"

namespace as
{

template<typename T>
struct mat_t<T, 4>
{
    T elem_rc[4][4];

    static constexpr size_t size = 4 * 4;
    using type = T;

#ifdef AS_ROW_MAJOR
    vec_t<T, 4> row(size_t i) const {
        return vec_t<T, 4>{
            elem_rc[i][0], elem_rc[i][1],
            elem_rc[i][2], elem_rc[i][3]
        };
    }

    const vec_t<T, 4> row0() const { return row(0); }
    const vec_t<T, 4> row1() const { return row(1); }
    const vec_t<T, 4> row2() const { return row(2); }
    const vec_t<T, 4> row3() const { return row(3); }

    void row(size_t i, const vec_t<T, 4>& row) {
        elem_rc[i][0] = row.x; elem_rc[i][1] = row.y;
        elem_rc[i][2] = row.z; elem_rc[i][3] = row.w;
    }

    void row0(const vec_t<T, 4>& row_) { row(0, row_); }
    void row1(const vec_t<T, 4>& row_) { row(1, row_); }
    void row2(const vec_t<T, 4>& row_) { row(2, row_); }
    void row3(const vec_t<T, 4>& row_) { row(3, row_); }

    vec_t<T, 4> col(size_t i) const {
        return vec_t<T, 4>{
            elem_rc[0][i], elem_rc[1][i],
            elem_rc[2][i], elem_rc[3][i]
        };
    }

    const vec_t<T, 4> col0() const { return col(0); }
    const vec_t<T, 4> col1() const { return col(1); }
    const vec_t<T, 4> col2() const { return col(2); }
    const vec_t<T, 4> col3() const { return col(3); }

    void col(size_t i, const vec_t<T, 4>& col) {
        elem_rc[0][i] = col.x; elem_rc[1][i] = col.y;
        elem_rc[2][i] = col.z; elem_rc[3][i] = col.w;
    }

    void col0(const vec_t<T, 4>& col_) { col(0, col_); }
    void col1(const vec_t<T, 4>& col_) { col(1, col_); }
    void col2(const vec_t<T, 4>& col_) { col(2, col_); }
    void col3(const vec_t<T, 4>& col_) { col(3, col_); }
#elif defined AS_COL_MAJOR
    vec_t<T, 4> col(size_t i) const {
        return vec_t<T, 4>{
            elem_rc[i][0], elem_rc[i][1],
            elem_rc[i][2], elem_rc[i][3]
        };
    }

    const vec_t<T, 4> col0() const { return col(0); }
    const vec_t<T, 4> col1() const { return col(1); }
    const vec_t<T, 4> col2() const { return col(2); }
    const vec_t<T, 4> col3() const { return col(3); }

    void col(size_t i, const vec_t<T, 4>& col) {
        elem_rc[i][0] = col.x; elem_rc[i][1] = col.y;
        elem_rc[i][2] = col.z; elem_rc[i][3] = col.w;
    }

    void col0(const vec_t<T, 4>& col_) { col(0, col_); }
    void col1(const vec_t<T, 4>& col_) { col(1, col_); }
    void col2(const vec_t<T, 4>& col_) { col(2, col_); }
    void col3(const vec_t<T, 4>& col_) { col(3, col_); }

    vec_t<T, 4> row(size_t i) const {
        return vec_t<T, 4>{
            elem_rc[0][i], elem_rc[1][i],
            elem_rc[2][i], elem_rc[3][i]
        };
    }

    const vec_t<T, 4> row0() const { return row(0); }
    const vec_t<T, 4> row1() const { return row(1); }
    const vec_t<T, 4> row2() const { return row(2); }
    const vec_t<T, 4> row3() const { return row(3); }

    void row(size_t i, const vec_t<T, 4>& row) {
        elem_rc[0][i] = row.x; elem_rc[1][i] = row.y;
        elem_rc[2][i] = row.z; elem_rc[3][i] = row.w;
    }

    void row0(const vec_t<T, 4>& row_) { row(0, row_); }
    void row1(const vec_t<T, 4>& row_) { row(1, row_); }
    void row2(const vec_t<T, 4>& row_) { row(2, row_); }
    void row3(const vec_t<T, 4>& row_) { row(3, row_); }
#endif

    constexpr T& operator[](size_t i) & { return *(&elem_rc[0][0] + i); }
    constexpr const T& operator[](size_t i) const& { return *(&elem_rc[0][0] + i); }
    constexpr const T operator[](size_t i) && { return *(&elem_rc[0][0] + i); }

    mat_t() noexcept = default;
    mat_t(const mat_t&) noexcept = default;
    mat_t& operator=(const mat_t&) noexcept = default;
    mat_t(mat_t&&) noexcept = default;
    mat_t& operator=(mat_t&&) noexcept = default;
    ~mat_t() = default;

    constexpr mat_t(
        T x0, T y0, T z0, T w0,
        T x1, T y1, T z1, T w1,
        T x2, T y2, T z2, T w2,
        T x3, T y3, T z3, T w3)
            : elem_rc {
                { x0, y0, z0, w0 },
                { x1, y1, z1, w1 },
                { x2, y2, z2, w2 },
                { x3, y3, z3, w3 }
            } {}

#ifdef AS_ROW_MAJOR
    constexpr mat_t(
        const vec_t<T, 4>& row0, const vec_t<T, 4>& row1,
        const vec_t<T, 4>& row2, const vec_t<T, 4>& row3)
        : elem_rc {
            { row0.x, row0.y, row0.z, row0.w },
            { row1.x, row1.y, row1.z, row1.w },
            { row2.x, row2.y, row2.z, row2.w },
            { row3.x, row3.y, row3.z, row3.w }
        } {}
#elif defined AS_COL_MAJOR
    constexpr mat_t(
        const vec_t<T, 4>& col0, const vec_t<T, 4>& col1,
        const vec_t<T, 4>& col2, const vec_t<T, 4>& col3)
        : elem_rc {
            { col0.x, col0.y, col0.z, col0.w },
            { col1.x, col1.y, col1.z, col1.w },
            { col2.x, col2.y, col2.z, col2.w },
            { col3.x, col3.y, col3.z, col3.w }
        } {}
#endif

    constexpr mat_t(const mat_t<T, 3>& mat_, const vec_t<T, 3>& pos_)
        : elem_rc {
            { mat_.elem_rc[0][0], mat_.elem_rc[0][1], mat_.elem_rc[0][2], 0.0f },
            { mat_.elem_rc[1][0], mat_.elem_rc[1][1], mat_.elem_rc[1][2], 0.0f },
            { mat_.elem_rc[2][0], mat_.elem_rc[2][1], mat_.elem_rc[2][2], 0.0f },
            { pos_.x, pos_.y, pos_.z, 1.0f }
        } {}
};

using mat4_t = mat_t<real_t, 4>;
using mat4f_t = mat_t<float, 4>;
using mat4d_t = mat_t<double, 4>;
using mat4i_t = mat_t<int32_t, 4>;
using mat4l_t = mat_t<int64_t, 4>;

} // namespace as
