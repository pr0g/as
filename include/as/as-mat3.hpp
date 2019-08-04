#pragma once

#include "as-mat.hpp"

namespace as
{

template<typename T>
struct mat_t<T, 3>
{
    T elem_rc[3][3];

    static constexpr size_t size = 3 * 3;
    using type = T;

#ifdef AS_ROW_MAJOR
    vec_t<T, 3> row(size_t i) const {
        return vec_t<T, 3>{elem_rc[i][0], elem_rc[i][1], elem_rc[i][2]};
    }

    const vec_t<T, 3> row0() const { return row(0); }
    const vec_t<T, 3> row1() const { return row(1); }
    const vec_t<T, 3> row2() const { return row(2); }

    void row(size_t i, const vec_t<T, 3>& row) {
        elem_rc[i][0] = row.x; elem_rc[i][1] = row.y; elem_rc[i][2] = row.z;
    }

    void row0(const vec_t<T, 3>& row_) { row(0, row_); }
    void row1(const vec_t<T, 3>& row_) { row(1, row_); }
    void row2(const vec_t<T, 3>& row_) { row(2, row_); }

    vec_t<T, 3> col(size_t i) const {
        return vec_t<T, 3>{elem_rc[0][i], elem_rc[1][i], elem_rc[2][i]};
    }

    const vec_t<T, 3> col0() const { return col(0); }
    const vec_t<T, 3> col1() const { return col(1); }
    const vec_t<T, 3> col2() const { return col(2); }

    void col(size_t i, const vec_t<T, 3>& col) {
        elem_rc[0][i] = col.x; elem_rc[1][i] = col.y; elem_rc[2][i] = col.z;
    }

    void col0(const vec_t<T, 3>& col_) { col(0, col_); }
    void col1(const vec_t<T, 3>& col_) { col(1, col_); }
    void col2(const vec_t<T, 3>& col_) { col(2, col_); }
#elif defined AS_COL_MAJOR
    vec_t<T, 3> col(size_t i) const {
        return vec_t<T, 3>{elem_rc[i][0], elem_rc[i][1], elem_rc[i][2]};
    }

    const vec_t<T, 3> col0() const { return col(0); }
    const vec_t<T, 3> col1() const { return col(1); }
    const vec_t<T, 3> col2() const { return col(2); }

    void col(size_t i, const vec_t<T, 3>& col) {
        elem_rc[i][0] = col.x; elem_rc[i][1] = col.y; elem_rc[i][2] = col.z;
    }

    void col0(const vec_t<T, 3>& col_) { col(0, col_); }
    void col1(const vec_t<T, 3>& col_) { col(1, col_); }
    void col2(const vec_t<T, 3>& col_) { col(2, col_); }

    vec_t<T, 3> row(size_t i) const {
        return vec_t<T, 3>{elem_rc[0][i], elem_rc[1][i], elem_rc[2][i]};
    }

    const vec_t<T, 3> row0() const { return row(0); }
    const vec_t<T, 3> row1() const { return row(1); }
    const vec_t<T, 3> row2() const { return row(2); }

    void row(size_t i, const vec_t<T, 3>& row) {
        elem_rc[0][i] = row.x; elem_rc[1][i] = row.y; elem_rc[2][i] = row.z;
    }

    void row0(const vec_t<T, 3>& row_) { row(0, row_); }
    void row1(const vec_t<T, 3>& row_) { row(1, row_); }
    void row2(const vec_t<T, 3>& row_) { row(2, row_); }
#endif

    constexpr T& operator[](size_t i) & { return elem_rc[0][i]; }
    constexpr const T& operator[](size_t i) const& { return elem_rc[0][i]; }
    constexpr const T operator[](size_t i) && { return elem_rc[0][i]; }

    mat_t() noexcept = default;
    mat_t(const mat_t&) noexcept = default;
    mat_t& operator=(const mat_t&) noexcept = default;
    mat_t(mat_t&&) noexcept = default;
    mat_t& operator=(mat_t&&) noexcept = default;
    ~mat_t() = default;

    constexpr mat_t(
        T x0, T y0, T z0,
        T x1, T y1, T z1,
        T x2, T y2, T z2)
            : elem_rc {
                { x0, y0, z0 },
                { x1, y1, z1 },
                { x2, y2, z2 }
            } {}

#ifdef AS_ROW_MAJOR
    constexpr mat_t(
        const vec_t<T, 3>& row0, const vec_t<T, 3>& row1, const vec_t<T, 3>& row2)
        : elem_rc {
            { row0.x, row0.y, row0.z },
            { row1.x, row1.y, row1.z },
            { row2.x, row2.y, row2.z }
        } {}
#elif defined AS_COL_MAJOR
    constexpr mat_t(
        const vec_t<T, 3>& col0, const vec_t<T, 3>& col1, const vec_t<T, 3>& col2)
        : elem_rc {
            { col0.x, col0.y, col0.z },
            { col1.x, col1.y, col1.z },
            { col2.x, col2.y, col2.z }
        } {}
#endif
};

using mat3_t = mat_t<real_t, 3>;
using mat3f_t = mat_t<float, 3>;
using mat3d_t = mat_t<double, 3>;
using mat3i_t = mat_t<int32_t, 3>;
using mat3l_t = mat_t<int64_t, 3>;

} // namespace as
