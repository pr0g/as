#pragma once

#include "as-mat.hpp"

namespace as
{

using m33 = mat::Mat<real, 3, 3>;

#ifdef _MSC_VER
__pragma(warning(push))
__pragma(warning(disable:4201))
#endif

template<> struct mat::Mat<real, 3, 3>
{
    union
    {
        real elem[3 * 3];
        real elem_rc[3][3];
        struct { real x0; real y0; real z0;
                 real x1; real y1; real z1;
                 real x2; real y2; real z2; };
    };

#ifdef AS_ROW_MAJOR
    v3 row(size_t i) { return v3(elem_rc[i][0], elem_rc[i][1], elem_rc[i][2]); }
    v3 row0() const { return v3(elem_rc[0][0], elem_rc[0][1], elem_rc[0][2]); }
    v3 row1() const { return v3(elem_rc[1][0], elem_rc[1][1], elem_rc[1][2]); }
    v3 row2() const { return v3(elem_rc[2][0], elem_rc[2][1], elem_rc[2][2]); }

    v3 col(size_t i) { return v3(elem_rc[0][i], elem_rc[1][i], elem_rc[2][i]); }
    v3 col0() const { return v3(elem_rc[0][0], elem_rc[1][0], elem_rc[2][0]); }
    v3 col1() const { return v3(elem_rc[0][1], elem_rc[1][1], elem_rc[2][1]); }
    v3 col2() const { return v3(elem_rc[0][2], elem_rc[1][2], elem_rc[2][2]); }
#elif defined AS_COL_MAJOR
    v3 col(size_t i) { return v3(elem_rc[i][0], elem_rc[i][1], elem_rc[i][2]); }
    v3 col0() const { return v3(elem_rc[0][0], elem_rc[0][1], elem_rc[0][2]); }
    v3 col1() const { return v3(elem_rc[1][0], elem_rc[1][1], elem_rc[1][2]); }
    v3 col2() const { return v3(elem_rc[2][0], elem_rc[2][1], elem_rc[2][2]); }

    v3 row(size_t i) { return v3(elem_rc[0][i], elem_rc[1][i], elem_rc[2][i]); }
    v3 row0() const { return v3(elem_rc[0][0], elem_rc[1][0], elem_rc[2][0]); }
    v3 row1() const { return v3(elem_rc[0][1], elem_rc[1][1], elem_rc[2][1]); }
    v3 row2() const { return v3(elem_rc[0][2], elem_rc[1][2], elem_rc[2][2]); }
#endif

    constexpr real& operator[](size_t i) { return elem[i]; }
    constexpr real operator[](size_t i) const { return elem[i]; }

    Mat() = default;
    Mat(const Mat& mat) = default;
    Mat& operator=(const Mat& mat) = default;
    Mat(Mat&& mat) noexcept = default;
    Mat& operator=(Mat&& mat) noexcept = default;
    ~Mat() = default;

    constexpr Mat(
        real x0, real y0, real z0,
        real x1, real y1, real z1,
        real x2, real y2, real z2)
        : x0(x0), y0(y0), z0(z0),
          x1(x1), y1(y1), z1(z1),
          x2(x2), y2(y2), z2(z2) {}

#ifdef AS_ROW_MAJOR
    constexpr Mat(
        const v3& row0, const v3& row1, const v3& row2)
        : x0(row0.x), y0(row0.y), z0(row0.z),
          x1(row1.x), y1(row1.y), z1(row1.z),
          x2(row2.x), y2(row2.y), z2(row2.z) {}
#elif defined AS_COL_MAJOR
    constexpr Mat(
        const v3& col0, const v3& col1, const v3& col2)
        : x0(col0.x), y0(col0.y), z0(col0.z),
          x1(col1.x), y1(col1.y), z1(col1.z),
          x2(col2.x), y2(col2.y), z2(col2.z) {}
#endif

    constexpr static size_t rows() { return 3; }
    constexpr static size_t cols() { return 3; }

    constexpr static Mat identity() { return mat::identity<real, 3>(); }

    constexpr inline static Mat from_ptr(const real* data);
    constexpr inline static Mat from_arr(const real(&data)[9]);
    
    constexpr inline static Mat axis_angle(const v3& axis, real radians);
    constexpr inline static Mat rotation_xyz(real x, real y, real z);
    constexpr inline static Mat rotation_zxy(real x, real y, real z);
    constexpr inline static Mat rotation_x(real radians);
    constexpr inline static Mat rotation_y(real radians);
    constexpr inline static Mat rotation_z(real radians);
};

#ifdef _MSC_VER
__pragma(warning(pop))
#endif

} // namespace as

#include "as-mat3.inl"