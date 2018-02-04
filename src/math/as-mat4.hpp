#pragma once

#include "as-mat.hpp"
#include "as-mat3.hpp"

namespace as
{

using m44 = mat::Mat<real, 4, 4>;

#ifdef _MSC_VER
__pragma(warning(push))
__pragma(warning(disable:4201))
#endif

template<> struct mat::Mat<real, 4, 4>
{
    union
    {
        real elem[4 * 4];
        real elem_rc[4][4];
        struct { real x0; real y0; real z0; real w0;
                 real x1; real y1; real z1; real w1;
                 real x2; real y2; real z2; real w2;
                 real x3; real y3; real z3; real w3; };
    };

#ifdef AS_ROW_MAJOR
    v4 row(size_t i) const { return v4(elem_rc[i][0], elem_rc[i][1], elem_rc[i][2], elem_rc[i][3]); }
    v4 row0() const { return v4(elem_rc[0][0], elem_rc[0][1], elem_rc[0][2], elem_rc[0][3]); }
    v4 row1() const { return v4(elem_rc[1][0], elem_rc[1][1], elem_rc[1][2], elem_rc[1][3]); }
    v4 row2() const { return v4(elem_rc[2][0], elem_rc[2][1], elem_rc[2][2], elem_rc[2][3]); }
    v4 row3() const { return v4(elem_rc[3][0], elem_rc[3][1], elem_rc[3][2], elem_rc[3][3]); }

    v4 col(size_t i) { return v4(elem_rc[0][i], elem_rc[1][i], elem_rc[2][i], elem_rc[3][i]); }
    v4 col0() const { return v4(elem_rc[0][0], elem_rc[1][0], elem_rc[2][0], elem_rc[3][0]); }
    v4 col1() const { return v4(elem_rc[0][1], elem_rc[1][1], elem_rc[2][1], elem_rc[3][1]); }
    v4 col2() const { return v4(elem_rc[0][2], elem_rc[1][2], elem_rc[2][2], elem_rc[3][2]); }
    v4 col3() const { return v4(elem_rc[3][0], elem_rc[3][1], elem_rc[3][2], elem_rc[3][3]); }
#elif defined AS_COL_MAJOR
    v4 col(size_t i) const { return v4(elem_rc[i][0], elem_rc[i][1], elem_rc[i][2], elem_rc[i][3]); }
    v4 col0() const { return v4(elem_rc[0][0], elem_rc[0][1], elem_rc[0][2], elem_rc[0][3]); }
    v4 col1() const { return v4(elem_rc[1][0], elem_rc[1][1], elem_rc[1][2], elem_rc[1][3]); }
    v4 col2() const { return v4(elem_rc[2][0], elem_rc[2][1], elem_rc[2][2], elem_rc[2][3]); }
    v4 col3() const { return v4(elem_rc[3][0], elem_rc[3][1], elem_rc[3][2], elem_rc[3][3]); }

    v4 row(size_t i) { return v4(elem_rc[0][i], elem_rc[1][i], elem_rc[2][i], elem_rc[3][i]); }
    v4 row0() const { return v4(elem_rc[0][0], elem_rc[1][0], elem_rc[2][0], elem_rc[3][0]); }
    v4 row1() const { return v4(elem_rc[0][1], elem_rc[1][1], elem_rc[2][1], elem_rc[3][1]); }
    v4 row2() const { return v4(elem_rc[0][2], elem_rc[1][2], elem_rc[2][2], elem_rc[3][2]); }
    v4 row3() const { return v4(elem_rc[3][0], elem_rc[3][1], elem_rc[3][2], elem_rc[3][3]); }
#endif

    constexpr real& operator[](size_t i) { return elem[i]; }
    constexpr const real& operator[](size_t i) const { return elem[i]; }

    Mat() = default;
    Mat(const Mat& mat) = default;
    Mat& operator=(const Mat& mat) = default;
    Mat(Mat&& mat) noexcept = default;
    Mat& operator=(Mat&& mat) noexcept = default;
    ~Mat() = default;

    constexpr Mat(
        real x0, real y0, real z0, real w0,
        real x1, real y1, real z1, real w1,
        real x2, real y2, real z2, real w2,
        real x3, real y3, real z3, real w3)
        : x0(x0), y0(y0), z0(z0), w0(w0),
          x1(x1), y1(y1), z1(z1), w1(w1),
          x2(x2), y2(y2), z2(z2), w2(w2),
          x3(x3), y3(y3), z3(z3), w3(w3) {}

#ifdef AS_ROW_MAJOR
    constexpr Mat(
        const v4& row0, const v4& row1, const v4& row2, const v4& row3)
        : x0(row0.x), y0(row0.y), z0(row0.z), w0(row0.w),
          x1(row1.x), y1(row1.y), z1(row1.z), w1(row1.w),
          x2(row2.x), y2(row2.y), z2(row2.z), w2(row2.w),
          x3(row3.x), y3(row3.y), z3(row3.z), w3(row3.w) {}
#elif defined AS_COL_MAJOR
    constexpr Mat(
        const v4& col0, const v4& col1, const v4& col2, const v4& col3)
        : x0(col0.x), y0(col0.y), z0(col0.z), w0(col0.w),
          x1(col1.x), y1(col1.y), z1(col1.z), w1(col1.w),
          x2(col2.x), y2(col2.y), z2(col2.z), w2(col2.w),
          x3(col3.x), y3(col3.y), z3(col3.z), w3(col3.w) {}
#endif

    constexpr Mat(const m33& mat, const v3& pos)
        : x0(mat.x0), y0(mat.y0), z0(mat.z0), w0(0.0f),
          x1(mat.x1), y1(mat.y1), z1(mat.z1), w1(0.0f),
          x2(mat.x2), y2(mat.y2), z2(mat.z2), w2(0.0f),
          x3(pos.x),  y3(pos.y),  z3(pos.z),  w3(1.0f) {}

    constexpr static size_t rows() { return 4; }
    constexpr static size_t cols() { return 4; }

    constexpr static Mat identity() { return mat::identity<real, 4>(); }

    constexpr inline static Mat from_ptr(const real* data);
    constexpr inline static Mat from_arr(const real(&data)[16]);
    constexpr inline static m44 from_v3(const v3& translation);
    constexpr inline static m44 from_m33(const m33& rotation);
    constexpr inline static m44 from_m33_v3(const m33& rotation, const v3& translation);
};

#ifdef _MSC_VER
__pragma(warning(pop))
#endif

} // namespace as

#include "as-mat4.inl"