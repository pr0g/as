#pragma once

#include "as-mat.hpp"
#include "as-mat3.hpp"

namespace as
{

using mat44_t = Mat<real_t, 4, 4>;

#ifdef _MSC_VER
__pragma(warning(push))
__pragma(warning(disable:4201))
#endif

template<> struct Mat<real_t, 4, 4>
{
    union
    {
        real_t elem[4 * 4];
        real_t elem_rc[4][4];
        struct { real_t x0; real_t y0; real_t z0; real_t w0;
                 real_t x1; real_t y1; real_t z1; real_t w1;
                 real_t x2; real_t y2; real_t z2; real_t w2;
                 real_t x3; real_t y3; real_t z3; real_t w3; };
    };

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

    constexpr real_t& operator[](size_t i) { return elem[i]; }
    constexpr const real_t& operator[](size_t i) const { return elem[i]; }

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
        : x0(x0), y0(y0), z0(z0), w0(w0),
          x1(x1), y1(y1), z1(z1), w1(w1),
          x2(x2), y2(y2), z2(z2), w2(w2),
          x3(x3), y3(y3), z3(z3), w3(w3) {}

#ifdef AS_ROW_MAJOR
    constexpr Mat(
        const vec4_t& row0, const vec4_t& row1, const vec4_t& row2, const vec4_t& row3)
        : x0(row0.x), y0(row0.y), z0(row0.z), w0(row0.w),
          x1(row1.x), y1(row1.y), z1(row1.z), w1(row1.w),
          x2(row2.x), y2(row2.y), z2(row2.z), w2(row2.w),
          x3(row3.x), y3(row3.y), z3(row3.z), w3(row3.w) {}
#elif defined AS_COL_MAJOR
    constexpr Mat(
        const vec4_t& col0, const vec4_t& col1, const vec4_t& col2, const vec4_t& col3)
        : x0(col0.x), y0(col0.y), z0(col0.z), w0(col0.w),
          x1(col1.x), y1(col1.y), z1(col1.z), w1(col1.w),
          x2(col2.x), y2(col2.y), z2(col2.z), w2(col2.w),
          x3(col3.x), y3(col3.y), z3(col3.z), w3(col3.w) {}
#endif

    constexpr Mat(const mat33_t& mat, const vec3_t& pos)
        : x0(mat.x0), y0(mat.y0), z0(mat.z0), w0(0.0f),
          x1(mat.x1), y1(mat.y1), z1(mat.z1), w1(0.0f),
          x2(mat.x2), y2(mat.y2), z2(mat.z2), w2(0.0f),
          x3(pos.x),  y3(pos.y),  z3(pos.z),  w3(1.0f) {}
};

#ifdef _MSC_VER
__pragma(warning(pop))
#endif

} // namespace as