#pragma once

#include "as-mat.hpp"

namespace as
{

template<typename T>
struct mat_t<T, 3, 3>
{
    T elem_rc[3][3];
    static constexpr size_t size = 3 * 3;

#ifdef AS_ROW_MAJOR
    vec_t<T, 3> row(size_t i) const { return vec_t<T, 3>(elem_rc[i][0], elem_rc[i][1], elem_rc[i][2]); }
    vec_t<T, 3> row0() const { return vec_t<T, 3>(elem_rc[0][0], elem_rc[0][1], elem_rc[0][2]); }
    vec_t<T, 3> row1() const { return vec_t<T, 3>(elem_rc[1][0], elem_rc[1][1], elem_rc[1][2]); }
    vec_t<T, 3> row2() const { return vec_t<T, 3>(elem_rc[2][0], elem_rc[2][1], elem_rc[2][2]); }

    void row(size_t i, const vec_t<T, 3>& row) { elem_rc[i][0] = row.x; elem_rc[i][1] = row.y; elem_rc[i][2] = row.z; }
    void row0(const vec_t<T, 3>& row) { elem_rc[0][0] = row.x; elem_rc[0][1] = row.y, elem_rc[0][2] = row.z; }
    void row1(const vec_t<T, 3>& row) { elem_rc[1][0] = row.x; elem_rc[1][1] = row.y, elem_rc[1][2] = row.z; }
    void row2(const vec_t<T, 3>& row) { elem_rc[2][0] = row.x; elem_rc[2][1] = row.y, elem_rc[2][2] = row.z; }

    vec_t<T, 3> col(size_t i) const { return vec_t<T, 3>(elem_rc[0][i], elem_rc[1][i], elem_rc[2][i]); }
    vec_t<T, 3> col0() const { return vec_t<T, 3>(elem_rc[0][0], elem_rc[1][0], elem_rc[2][0]); }
    vec_t<T, 3> col1() const { return vec_t<T, 3>(elem_rc[0][1], elem_rc[1][1], elem_rc[2][1]); }
    vec_t<T, 3> col2() const { return vec_t<T, 3>(elem_rc[0][2], elem_rc[1][2], elem_rc[2][2]); }

    void col(size_t i, const vec_t<T, 3>& col) { elem_rc[0][i] = col.x; elem_rc[1][i] = col.y; elem_rc[2][i] = col.z; }
    void col0(const vec_t<T, 3>& col) { elem_rc[0][0] = col.x; elem_rc[1][0] = col.y; elem_rc[2][0] = col.z; }
    void col1(const vec_t<T, 3>& col) { elem_rc[0][1] = col.x; elem_rc[1][1] = col.y; elem_rc[2][1] = col.z; }
    void col2(const vec_t<T, 3>& col) { elem_rc[0][2] = col.x; elem_rc[1][2] = col.y; elem_rc[2][2] = col.z; }
#elif defined AS_COL_MAJOR
    vec_t<T, 3> col(size_t i) const { return vec_t<T, 3>(elem_rc[i][0], elem_rc[i][1], elem_rc[i][2]); }
    vec_t<T, 3> col0() const { return vec_t<T, 3>(elem_rc[0][0], elem_rc[0][1], elem_rc[0][2]); }
    vec_t<T, 3> col1() const { return vec_t<T, 3>(elem_rc[1][0], elem_rc[1][1], elem_rc[1][2]); }
    vec_t<T, 3> col2() const { return vec_t<T, 3>(elem_rc[2][0], elem_rc[2][1], elem_rc[2][2]); }

    void col(size_t i, const vec_t<T, 3>& col) { elem_rc[i][0] = col.x; elem_rc[i][1] = col.y; elem_rc[i][2] = col.z; }
    void col0(const vec_t<T, 3>& col) { elem_rc[0][0] = col.x; elem_rc[0][1] = col.y; elem_rc[0][2] = col.z; }
    void col1(const vec_t<T, 3>& col) { elem_rc[1][0] = col.x; elem_rc[1][1] = col.y; elem_rc[1][2] = col.z; }
    void col2(const vec_t<T, 3>& col) { elem_rc[2][0] = col.x; elem_rc[2][1] = col.y; elem_rc[2][2] = col.z; }

    vec_t<T, 3> row(size_t i) const { return vec_t<T, 3>(elem_rc[0][i], elem_rc[1][i], elem_rc[2][i]); }
    vec_t<T, 3> row0() const { return vec_t<T, 3>(elem_rc[0][0], elem_rc[1][0], elem_rc[2][0]); }
    vec_t<T, 3> row1() const { return vec_t<T, 3>(elem_rc[0][1], elem_rc[1][1], elem_rc[2][1]); }
    vec_t<T, 3> row2() const { return vec_t<T, 3>(elem_rc[0][2], elem_rc[1][2], elem_rc[2][2]); }

    void row(size_t i, const vec_t<T, 3>& row) { elem_rc[0][i] = row.x; elem_rc[1][i] = row.y; elem_rc[2][i] = row.z; }
    void row0(const vec_t<T, 3>& row) { elem_rc[0][0] = row.x; elem_rc[1][0] = row.y; elem_rc[2][0] = row.z; }
    void row1(const vec_t<T, 3>& row) { elem_rc[0][1] = row.x; elem_rc[1][1] = row.y; elem_rc[2][1] = row.z; }
    void row2(const vec_t<T, 3>& row) { elem_rc[0][2] = row.x; elem_rc[1][2] = row.y; elem_rc[2][2] = row.z; }
#endif

    constexpr T* elems() { return &elem_rc[0][0]; }
    constexpr const T* elems() const { return &elem_rc[0][0]; }

    constexpr T& operator[](size_t i) { return elems()[i]; }
    constexpr T operator[](size_t i) const { return elems()[i]; }

    mat_t() = default;
    mat_t(const mat_t& mat) = default;
    mat_t& operator=(const mat_t& mat) = default;
    mat_t(mat_t&& mat) noexcept = default;
    mat_t& operator=(mat_t&& mat) noexcept = default;
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

using mat33_t = mat_t<real_t, 3, 3>;
using mat33f_t = mat_t<float, 3, 3>;
using mat33d_t = mat_t<double, 3, 3>;
using mat33i_t = mat_t<int32_t, 3, 3>;
using mat33l_t = mat_t<int64_t, 3, 3>;

} // namespace as
