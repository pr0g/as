#pragma once

#include "as-mat.hpp"
#include "as-mat3.hpp"

namespace as
{

using mat44_t = mat_t<real_t, 4, 4>;

template<> struct mat_t<real_t, 4, 4>
{
    real_t elem_rc[4][4];
    static const size_t size = 4 * 4;

#ifdef AS_ROW_MAJOR
    vec4_t row(size_t i) const { return vec4_t(elem_rc[i][0], elem_rc[i][1], elem_rc[i][2], elem_rc[i][3]); }
    vec4_t row0() const { return vec4_t(elem_rc[0][0], elem_rc[0][1], elem_rc[0][2], elem_rc[0][3]); }
    vec4_t row1() const { return vec4_t(elem_rc[1][0], elem_rc[1][1], elem_rc[1][2], elem_rc[1][3]); }
    vec4_t row2() const { return vec4_t(elem_rc[2][0], elem_rc[2][1], elem_rc[2][2], elem_rc[2][3]); }
    vec4_t row3() const { return vec4_t(elem_rc[3][0], elem_rc[3][1], elem_rc[3][2], elem_rc[3][3]); }

    void row(size_t i, const vec4_t& row) { elem_rc[i][0] = row.x; elem_rc[i][1] = row.y; elem_rc[i][2] = row.z; elem_rc[i][3] = row.w; }
    void row0(const vec4_t& row) { elem_rc[0][0] = row.x; elem_rc[0][1] = row.y; elem_rc[0][2] = row.z; elem_rc[0][3] = row.w; }
    void row1(const vec4_t& row) { elem_rc[1][0] = row.x; elem_rc[1][1] = row.y; elem_rc[1][2] = row.z; elem_rc[1][3] = row.w; }
    void row2(const vec4_t& row) { elem_rc[2][0] = row.x; elem_rc[2][1] = row.y; elem_rc[2][2] = row.z; elem_rc[2][3] = row.w; }
    void row3(const vec4_t& row) { elem_rc[3][0] = row.x; elem_rc[3][1] = row.y; elem_rc[3][2] = row.z; elem_rc[3][3] = row.w; }

    vec4_t col(size_t i) const { return vec4_t(elem_rc[0][i], elem_rc[1][i], elem_rc[2][i], elem_rc[3][i]); }
    vec4_t col0() const { return vec4_t(elem_rc[0][0], elem_rc[1][0], elem_rc[2][0], elem_rc[3][0]); }
    vec4_t col1() const { return vec4_t(elem_rc[0][1], elem_rc[1][1], elem_rc[2][1], elem_rc[3][1]); }
    vec4_t col2() const { return vec4_t(elem_rc[0][2], elem_rc[1][2], elem_rc[2][2], elem_rc[3][2]); }
    vec4_t col3() const { return vec4_t(elem_rc[0][3], elem_rc[1][3], elem_rc[2][3], elem_rc[3][3]); }

    void col(size_t i, const vec4_t& col) { elem_rc[0][i] = col.x; elem_rc[1][i] = col.y; elem_rc[2][i] = col.z; elem_rc[3][i] = col.w; }
    void col0(const vec4_t& col) { elem_rc[0][0] = col.x; elem_rc[1][0] = col.y; elem_rc[2][0] = col.z; elem_rc[3][0] = col.w; }
    void col1(const vec4_t& col) { elem_rc[0][1] = col.x; elem_rc[1][1] = col.y; elem_rc[2][1] = col.z; elem_rc[3][1] = col.w; }
    void col2(const vec4_t& col) { elem_rc[0][2] = col.x; elem_rc[1][2] = col.y; elem_rc[2][2] = col.z; elem_rc[3][2] = col.w; }
    void col3(const vec4_t& col) { elem_rc[0][3] = col.x; elem_rc[1][3] = col.y; elem_rc[2][3] = col.z; elem_rc[3][3] = col.w; }
#elif defined AS_COL_MAJOR
    vec4_t col(size_t i) const { return vec4_t(elem_rc[i][0], elem_rc[i][1], elem_rc[i][2], elem_rc[i][3]); }
    vec4_t col0() const { return vec4_t(elem_rc[0][0], elem_rc[0][1], elem_rc[0][2], elem_rc[0][3]); }
    vec4_t col1() const { return vec4_t(elem_rc[1][0], elem_rc[1][1], elem_rc[1][2], elem_rc[1][3]); }
    vec4_t col2() const { return vec4_t(elem_rc[2][0], elem_rc[2][1], elem_rc[2][2], elem_rc[2][3]); }
    vec4_t col3() const { return vec4_t(elem_rc[3][0], elem_rc[3][1], elem_rc[3][2], elem_rc[3][3]); }

    void col(size_t i, const vec4_t& col) { elem_rc[i][0] = col.x; elem_rc[i][1] = col.y; elem_rc[i][2] = col.z; elem_rc[i][3] = col.w; }
    void col0(const vec4_t& col) { elem_rc[0][0] = col.x; elem_rc[0][1] = col.y; elem_rc[0][2] = col.z; elem_rc[0][3] = col.w; }
    void col1(const vec4_t& col) { elem_rc[1][0] = col.x; elem_rc[1][1] = col.y; elem_rc[1][2] = col.z; elem_rc[1][3] = col.w; }
    void col2(const vec4_t& col) { elem_rc[2][0] = col.x; elem_rc[2][1] = col.y; elem_rc[2][2] = col.z; elem_rc[2][3] = col.w; }
    void col3(const vec4_t& col) { elem_rc[3][0] = col.x; elem_rc[3][1] = col.y; elem_rc[3][2] = col.z; elem_rc[3][3] = col.w; }

    vec4_t row(size_t i) const { return vec4_t(elem_rc[0][i], elem_rc[1][i], elem_rc[2][i], elem_rc[3][i]); }
    vec4_t row0() const { return vec4_t(elem_rc[0][0], elem_rc[1][0], elem_rc[2][0], elem_rc[3][0]); }
    vec4_t row1() const { return vec4_t(elem_rc[0][1], elem_rc[1][1], elem_rc[2][1], elem_rc[3][1]); }
    vec4_t row2() const { return vec4_t(elem_rc[0][2], elem_rc[1][2], elem_rc[2][2], elem_rc[3][2]); }
    vec4_t row3() const { return vec4_t(elem_rc[0][3], elem_rc[1][3], elem_rc[2][3], elem_rc[3][3]); }

    void row(size_t i, const vec4_t& row) { elem_rc[0][i] = row.x; elem_rc[1][i] = row.y; elem_rc[2][i] = row.z; elem_rc[3][i] = row.w; }
    void row0(const vec4_t& row) { elem_rc[0][0] = row.x; elem_rc[1][0] = row.y; elem_rc[2][0] = row.z; elem_rc[3][0] = row.w; }
    void row1(const vec4_t& row) { elem_rc[0][1] = row.x; elem_rc[1][1] = row.y; elem_rc[2][1] = row.z; elem_rc[3][1] = row.w; }
    void row2(const vec4_t& row) { elem_rc[0][2] = row.x; elem_rc[1][2] = row.y; elem_rc[2][2] = row.z; elem_rc[3][2] = row.w; }
    void row3(const vec4_t& row) { elem_rc[0][3] = row.x; elem_rc[1][3] = row.y; elem_rc[2][3] = row.z; elem_rc[3][3] = row.w; }
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
        real_t x0, real_t y0, real_t z0, real_t w0,
        real_t x1, real_t y1, real_t z1, real_t w1,
        real_t x2, real_t y2, real_t z2, real_t w2,
        real_t x3, real_t y3, real_t z3, real_t w3)
            : elem_rc {
                { x0, y0, z0, w0 },
                { x1, y1, z1, w1 },
                { x2, y2, z2, w2 },
                { x3, y3, z3, w3 }
            } {}

#ifdef AS_ROW_MAJOR
    constexpr mat_t(
        const vec4_t& row0, const vec4_t& row1, const vec4_t& row2, const vec4_t& row3)
        : elem_rc {
            { row0.x, row0.y, row0.z, row0.w },
            { row1.x, row1.y, row1.z, row1.w },
            { row2.x, row2.y, row2.z, row2.w },
            { row3.x, row3.y, row3.z, row3.w }
        } {}
#elif defined AS_COL_MAJOR
    constexpr mat_t(
        const vec4_t& col0, const vec4_t& col1, const vec4_t& col2, const vec4_t& col3)
        : elem_rc {
            { col0.x, col0.y, col0.z, col0.w },
            { col1.x, col1.y, col1.z, col1.w },
            { col2.x, col2.y, col2.z, col2.w },
            { col3.x, col3.y, col3.z, col3.w }
        } {}
#endif

    constexpr mat_t(const mat33_t& mat, const vec3_t& pos)
        : elem_rc {
            { mat.elem_rc[0][0], mat.elem_rc[0][1], mat.elem_rc[0][2], 0.0f },
            { mat.elem_rc[1][0], mat.elem_rc[1][1], mat.elem_rc[1][2], 0.0f },
            { mat.elem_rc[2][0], mat.elem_rc[2][1], mat.elem_rc[2][2], 0.0f },
            { pos.x, pos.y, pos.z, 1.0f }
        } {}
};

} // namespace as