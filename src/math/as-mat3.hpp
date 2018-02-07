#pragma once

#include "as-mat.hpp"

namespace as
{

using mat33_t = Mat<real_t, 3, 3>;

#ifdef _MSC_VER
__pragma(warning(push))
__pragma(warning(disable:4201))
#endif

template<> struct Mat<real_t, 3, 3>
{
    union
    {
        real_t elem[3 * 3];
        real_t elem_rc[3][3];
        struct { real_t x0; real_t y0; real_t z0;
                 real_t x1; real_t y1; real_t z1;
                 real_t x2; real_t y2; real_t z2; };
    };

#ifdef AS_ROW_MAJOR
    vec3_t row(size_t i) { return vec3_t(elem_rc[i][0], elem_rc[i][1], elem_rc[i][2]); }
    vec3_t row0() const { return vec3_t(elem_rc[0][0], elem_rc[0][1], elem_rc[0][2]); }
    vec3_t row1() const { return vec3_t(elem_rc[1][0], elem_rc[1][1], elem_rc[1][2]); }
    vec3_t row2() const { return vec3_t(elem_rc[2][0], elem_rc[2][1], elem_rc[2][2]); }

    vec3_t col(size_t i) { return vec3_t(elem_rc[0][i], elem_rc[1][i], elem_rc[2][i]); }
    vec3_t col0() const { return vec3_t(elem_rc[0][0], elem_rc[1][0], elem_rc[2][0]); }
    vec3_t col1() const { return vec3_t(elem_rc[0][1], elem_rc[1][1], elem_rc[2][1]); }
    vec3_t col2() const { return vec3_t(elem_rc[0][2], elem_rc[1][2], elem_rc[2][2]); }
#elif defined AS_COL_MAJOR
    vec3_t col(size_t i) { return vec3_t(elem_rc[i][0], elem_rc[i][1], elem_rc[i][2]); }
    vec3_t col0() const { return vec3_t(elem_rc[0][0], elem_rc[0][1], elem_rc[0][2]); }
    vec3_t col1() const { return vec3_t(elem_rc[1][0], elem_rc[1][1], elem_rc[1][2]); }
    vec3_t col2() const { return vec3_t(elem_rc[2][0], elem_rc[2][1], elem_rc[2][2]); }

    vec3_t row(size_t i) { return vec3_t(elem_rc[0][i], elem_rc[1][i], elem_rc[2][i]); }
    vec3_t row0() const { return vec3_t(elem_rc[0][0], elem_rc[1][0], elem_rc[2][0]); }
    vec3_t row1() const { return vec3_t(elem_rc[0][1], elem_rc[1][1], elem_rc[2][1]); }
    vec3_t row2() const { return vec3_t(elem_rc[0][2], elem_rc[1][2], elem_rc[2][2]); }
#endif

    constexpr real_t& operator[](size_t i) { return elem[i]; }
    constexpr real_t operator[](size_t i) const { return elem[i]; }

    Mat() = default;
    Mat(const Mat& mat) = default;
    Mat& operator=(const Mat& mat) = default;
    Mat(Mat&& mat) noexcept = default;
    Mat& operator=(Mat&& mat) noexcept = default;
    ~Mat() = default;

    constexpr Mat(
        real_t x0, real_t y0, real_t z0,
        real_t x1, real_t y1, real_t z1,
        real_t x2, real_t y2, real_t z2)
        : x0(x0), y0(y0), z0(z0),
          x1(x1), y1(y1), z1(z1),
          x2(x2), y2(y2), z2(z2) {}

#ifdef AS_ROW_MAJOR
    constexpr Mat(
        const vec3_t& row0, const vec3_t& row1, const vec3_t& row2)
        : x0(row0.x), y0(row0.y), z0(row0.z),
          x1(row1.x), y1(row1.y), z1(row1.z),
          x2(row2.x), y2(row2.y), z2(row2.z) {}
#elif defined AS_COL_MAJOR
    constexpr Mat(
        const vec3_t& col0, const vec3_t& col1, const vec3_t& col2)
        : x0(col0.x), y0(col0.y), z0(col0.z),
          x1(col1.x), y1(col1.y), z1(col1.z),
          x2(col2.x), y2(col2.y), z2(col2.z) {}
#endif
};

#ifdef _MSC_VER
__pragma(warning(pop))
#endif

} // namespace as