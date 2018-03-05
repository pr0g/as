#pragma once

#include "as-mat.hpp"
#include "as-mat3.hpp"

namespace as
{

using mat44_t = Mat<real_t, 4, 4>;

template<> struct Mat<real_t, 4, 4>
{
    real_t elem_rc[4][4];

#ifdef AS_ROW_MAJOR
    vec4_t row(size_t i) const { return vec4_t(elem_rc[i][0], elem_rc[i][1], elem_rc[i][2], elem_rc[i][3]); }
    vec4_t row0() const { return vec4_t(elem_rc[0][0], elem_rc[0][1], elem_rc[0][2], elem_rc[0][3]); }
    vec4_t row1() const { return vec4_t(elem_rc[1][0], elem_rc[1][1], elem_rc[1][2], elem_rc[1][3]); }
    vec4_t row2() const { return vec4_t(elem_rc[2][0], elem_rc[2][1], elem_rc[2][2], elem_rc[2][3]); }
    vec4_t row3() const { return vec4_t(elem_rc[3][0], elem_rc[3][1], elem_rc[3][2], elem_rc[3][3]); }

    vec4_t col(size_t i) { return vec4_t(elem_rc[0][i], elem_rc[1][i], elem_rc[2][i], elem_rc[3][i]); }
    vec4_t col0() const { return vec4_t(elem_rc[0][0], elem_rc[1][0], elem_rc[2][0], elem_rc[3][0]); }
    vec4_t col1() const { return vec4_t(elem_rc[0][1], elem_rc[1][1], elem_rc[2][1], elem_rc[3][1]); }
    vec4_t col2() const { return vec4_t(elem_rc[0][2], elem_rc[1][2], elem_rc[2][2], elem_rc[3][2]); }
    vec4_t col3() const { return vec4_t(elem_rc[3][0], elem_rc[3][1], elem_rc[3][2], elem_rc[3][3]); }
#elif defined AS_COL_MAJOR
    vec4_t col(size_t i) const { return vec4_t(elem_rc[i][0], elem_rc[i][1], elem_rc[i][2], elem_rc[i][3]); }
    vec4_t col0() const { return vec4_t(elem_rc[0][0], elem_rc[0][1], elem_rc[0][2], elem_rc[0][3]); }
    vec4_t col1() const { return vec4_t(elem_rc[1][0], elem_rc[1][1], elem_rc[1][2], elem_rc[1][3]); }
    vec4_t col2() const { return vec4_t(elem_rc[2][0], elem_rc[2][1], elem_rc[2][2], elem_rc[2][3]); }
    vec4_t col3() const { return vec4_t(elem_rc[3][0], elem_rc[3][1], elem_rc[3][2], elem_rc[3][3]); }

    vec4_t row(size_t i) { return vec4_t(elem_rc[0][i], elem_rc[1][i], elem_rc[2][i], elem_rc[3][i]); }
    vec4_t row0() const { return vec4_t(elem_rc[0][0], elem_rc[1][0], elem_rc[2][0], elem_rc[3][0]); }
    vec4_t row1() const { return vec4_t(elem_rc[0][1], elem_rc[1][1], elem_rc[2][1], elem_rc[3][1]); }
    vec4_t row2() const { return vec4_t(elem_rc[0][2], elem_rc[1][2], elem_rc[2][2], elem_rc[3][2]); }
    vec4_t row3() const { return vec4_t(elem_rc[3][0], elem_rc[3][1], elem_rc[3][2], elem_rc[3][3]); }
#endif

    real_t* elems() { return &elem_rc[0][0]; }
    const real_t* elems() const { return &elem_rc[0][0]; }

    constexpr real_t& operator[](size_t i) { return *(elems() + i); }
    constexpr real_t operator[](size_t i) const { return *(elems() + i); }

    Mat() = default;
    Mat(const Mat& mat) = default;
    Mat& operator=(const Mat& mat) = default;
    Mat(Mat&& mat) noexcept = default;
    Mat& operator=(Mat&& mat) noexcept = default;
    ~Mat() = default;

    constexpr Mat(
        real_t x0, real_t y0, real_t z0, real_t w0,
        real_t x1, real_t y1, real_t z1, real_t w1,
        real_t x2, real_t y2, real_t z2, real_t w2,
        real_t x3, real_t y3, real_t z3, real_t w3)
            : elem_rc { 
                x0, y0, z0, w0,
                x1, y1, z1, w1,
                x2, y2, z2, w2,
                x3, y3, z3, w3 } {}

#ifdef AS_ROW_MAJOR
    constexpr Mat(
        const vec4_t& row0, const vec4_t& row1, const vec4_t& row2, const vec4_t& row3)
        : elem_rc {
            row0.x, row0.y, row0.z, row0.w,
            row1.x, row1.y, row1.z, row1.w,
            row2.x, row2.y, row2.z, row2.w,
            row3.x, row3.y, row3.z, row3.w } {}
#elif defined AS_COL_MAJOR
    constexpr Mat(
        const vec4_t& col0, const vec4_t& col1, const vec4_t& col2, const vec4_t& col3)
        : elem_rc {
            col0.x, col0.y, col0.z, col0.w,
            col1.x, col1.y, col1.z, col1.w,
            col2.x, col2.y, col2.z, col2.w,
            col3.x, col3.y, col3.z, col3.w } {}
#endif

    constexpr Mat(const mat33_t& mat, const vec3_t& pos)
        : elem_rc{
            mat.elem_rc[0][0], mat.elem_rc[0][1], mat.elem_rc[0][2], 0.0f,
            mat.elem_rc[1][0], mat.elem_rc[1][1], mat.elem_rc[1][2], 0.0f,
            mat.elem_rc[2][0], mat.elem_rc[2][1], mat.elem_rc[2][2], 0.0f,
            pos.x, pos.y, pos.z, 1.0f } {}
};

} // namespace as