#pragma once

#include "as-mat.hpp"

namespace as
{

using mat33_t = mat_t<real_t, 3, 3>;

template<> struct mat_t<real_t, 3, 3>
{
    real_t elem_rc[3][3];
    static const size_t size = 3 * 3;

#ifdef AS_ROW_MAJOR
    vec3_t row(size_t i) const { return vec3_t(elem_rc[i][0], elem_rc[i][1], elem_rc[i][2]); }
    vec3_t row0() const { return vec3_t(elem_rc[0][0], elem_rc[0][1], elem_rc[0][2]); }
    vec3_t row1() const { return vec3_t(elem_rc[1][0], elem_rc[1][1], elem_rc[1][2]); }
    vec3_t row2() const { return vec3_t(elem_rc[2][0], elem_rc[2][1], elem_rc[2][2]); }

    void row(size_t i, const vec3_t& row) { elem_rc[i][0] = row.x; elem_rc[i][1] = row.y; elem_rc[i][2] = row.z; }
    void row0(const vec3_t& row) { elem_rc[0][0] = row.x; elem_rc[0][1] = row.y, elem_rc[0][2] = row.z; }
    void row1(const vec3_t& row) { elem_rc[1][0] = row.x; elem_rc[1][1] = row.y, elem_rc[1][2] = row.z; }
    void row2(const vec3_t& row) { elem_rc[2][0] = row.x; elem_rc[2][1] = row.y, elem_rc[2][2] = row.z; }

    vec3_t col(size_t i) const { return vec3_t(elem_rc[0][i], elem_rc[1][i], elem_rc[2][i]); }
    vec3_t col0() const { return vec3_t(elem_rc[0][0], elem_rc[1][0], elem_rc[2][0]); }
    vec3_t col1() const { return vec3_t(elem_rc[0][1], elem_rc[1][1], elem_rc[2][1]); }
    vec3_t col2() const { return vec3_t(elem_rc[0][2], elem_rc[1][2], elem_rc[2][2]); }

    void col(size_t i, const vec3_t& col) { elem_rc[0][i] = col.x; elem_rc[1][i] = col.y; elem_rc[2][i] = col.z; }
    void col0(const vec3_t& col) { elem_rc[0][0] = col.x; elem_rc[1][0] = col.y; elem_rc[2][0] = col.z; }
    void col1(const vec3_t& col) { elem_rc[0][1] = col.x; elem_rc[1][1] = col.y; elem_rc[2][1] = col.z; }
    void col2(const vec3_t& col) { elem_rc[0][2] = col.x; elem_rc[1][2] = col.y; elem_rc[2][2] = col.z; }
#elif defined AS_COL_MAJOR
    vec3_t col(size_t i) const { return vec3_t(elem_rc[i][0], elem_rc[i][1], elem_rc[i][2]); }
    vec3_t col0() const { return vec3_t(elem_rc[0][0], elem_rc[0][1], elem_rc[0][2]); }
    vec3_t col1() const { return vec3_t(elem_rc[1][0], elem_rc[1][1], elem_rc[1][2]); }
    vec3_t col2() const { return vec3_t(elem_rc[2][0], elem_rc[2][1], elem_rc[2][2]); }

    void col(size_t i, const vec3_t& col) { elem_rc[i][0] = col.x; elem_rc[i][1] = col.y; elem_rc[i][2] = col.z; }
    void col0(const vec3_t& col) { elem_rc[0][0] = col.x; elem_rc[0][1] = col.y; elem_rc[0][2] = col.z; }
    void col1(const vec3_t& col) { elem_rc[1][0] = col.x; elem_rc[1][1] = col.y; elem_rc[1][2] = col.z; }
    void col2(const vec3_t& col) { elem_rc[2][0] = col.x; elem_rc[2][1] = col.y; elem_rc[2][2] = col.z; }

    vec3_t row(size_t i) const { return vec3_t(elem_rc[0][i], elem_rc[1][i], elem_rc[2][i]); }
    vec3_t row0() const { return vec3_t(elem_rc[0][0], elem_rc[1][0], elem_rc[2][0]); }
    vec3_t row1() const { return vec3_t(elem_rc[0][1], elem_rc[1][1], elem_rc[2][1]); }
    vec3_t row2() const { return vec3_t(elem_rc[0][2], elem_rc[1][2], elem_rc[2][2]); }

    void row(size_t i, const vec3_t& row) { elem_rc[0][i] = row.x; elem_rc[1][i] = row.y; elem_rc[2][i] = row.z; }
    void row0(const vec3_t& row) { elem_rc[0][0] = row.x; elem_rc[1][0] = row.y; elem_rc[2][0] = row.z; }
    void row1(const vec3_t& row) { elem_rc[0][1] = row.x; elem_rc[1][1] = row.y; elem_rc[2][1] = row.z; }
    void row2(const vec3_t& row) { elem_rc[0][2] = row.x; elem_rc[1][2] = row.y; elem_rc[2][2] = row.z; }
#endif

    constexpr real_t* elems() { return &elem_rc[0][0]; }
    constexpr const real_t* elems() const { return &elem_rc[0][0]; }

    constexpr real_t& operator[](size_t i) { return elems()[i]; }
    constexpr real_t operator[](size_t i) const { return elems()[i]; }

    mat_t() = default;
    mat_t(const mat_t& mat) = default;
    mat_t& operator=(const mat_t& mat) = default;
    mat_t(mat_t&& mat) noexcept = default;
    mat_t& operator=(mat_t&& mat) noexcept = default;
    ~mat_t() = default;

    constexpr mat_t(
        real_t x0, real_t y0, real_t z0,
        real_t x1, real_t y1, real_t z1,
        real_t x2, real_t y2, real_t z2)
            : elem_rc {
                { x0, y0, z0 },
                { x1, y1, z1 },
                { x2, y2, z2 }
            } {}

#ifdef AS_ROW_MAJOR
    constexpr mat_t(
        const vec3_t& row0, const vec3_t& row1, const vec3_t& row2)
        : elem_rc {
            { row0.x, row0.y, row0.z },
            { row1.x, row1.y, row1.z },
            { row2.x, row2.y, row2.z }
        } {}
#elif defined AS_COL_MAJOR
    constexpr mat_t(
        const vec3_t& col0, const vec3_t& col1, const vec3_t& col2)
        : elem_rc {
            { col0.x, col0.y, col0.z },
            { col1.x, col1.y, col1.z },
            { col2.x, col2.y, col2.z }
        } {}
#endif
};

} // namespace as