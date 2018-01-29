#pragma once

#include "as-mat.hpp"

namespace as
{

using m33 = Mat<real, 3, 3>;

#ifdef _MSC_VER
__pragma(warning(push))
__pragma(warning(disable:4201))
#endif

template<> struct Mat<real, 3, 3>
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

    size_t rows() const { return 3; }
    size_t cols() const { return 3; }
};

#ifdef _MSC_VER
__pragma(warning(pop))
#endif

const m33 m33_id = identity<real, 3>();

AS_INLINE m33 make_m33_from(const real* data)
{
    return make_from<real, 3, 3>(data);
}

AS_INLINE m33 axis_angle_rotation(v3 axis, real radians)
{
    m33 result;
    result[0] = cosr(radians) + ((axis.x * axis.x) * (1.0f - cosr(radians)));
    result[1] = (axis.y * axis.x * (1.0f - cosr(radians))) + (axis.z * sinr(radians));
    result[2] = (axis.z * axis.x * (1.0f - cosr(radians))) - (axis.y * sinr(radians));
    result[3] = (axis.x * axis.y) * (1.0f - cosr(radians)) - (axis.z * sinr(radians));
    result[4] = cosr(radians) + ((axis.y * axis.y) * (1.0f - cosr(radians)));
    result[5] = (axis.z * axis.y * (1.0f - cosr(radians))) + (axis.x * sinr(radians));
    result[6] = (axis.x * axis.z * (1.0f - cosr(radians))) + (axis.y * sinr(radians));
    result[7] = (axis.y * axis.z * (1.0f - cosr(radians))) - (axis.x * sinr(radians));
    result[8] = cosr(radians) + ((axis.z * axis.z) * (1.0f - cosr(radians)));
    return result;
}

AS_INLINE m33 make_rotation_xyz(real x, real y, real z)
{
    m33 result;
    result[0] =  cosr(y) * cosr(z);
    result[1] =  cosr(y) * sinr(z);
    result[2] = -sinr(y);
    result[3] = (sinr(x) * sinr(y) * cosr(z)) - (cosr(x) * sinr(z));
    result[4] = (sinr(x) * sinr(y) * sinr(z)) + (cosr(x) * cosr(z));
    result[5] =  sinr(x) * cosr(y);
    result[6] = (cosr(x) * sinr(y) * cosr(z)) + (sinr(x) * sinr(z));
    result[7] = (cosr(x) * sinr(y) * sinr(z)) - (sinr(x) * cosr(z));
    result[8] =  cosr(x) * cosr(y);
    return result;
}

AS_INLINE m33 make_rotation_zxy(real x, real y, real z)
{
    m33 result;
    result[0] =  cosr(z) * cosr(y) + sinr(x) * sinr(y) * sinr(z);
    result[1] =  sinr(z) * cosr(x);
    result[2] = -sinr(y) * cosr(z) + sinr(z) * sinr(x) * cosr(y);
    result[3] = -sinr(z) * cosr(y) + cosr(z) * sinr(x) * sinr(y);
    result[4] =  cosr(z) * cosr(x);
    result[5] = -sinr(z) * -sinr(y) + cosr(z) * sinr(x) * cosr(y);
    result[6] =  cosr(x) * sinr(y);
    result[7] = -sinr(x);
    result[8] =  cosr(x) * cosr(y);
    return result;
}

AS_INLINE m33 make_rotation_x(real radians)
{
    m33 result = {};
    result[0] = 1.0f;
    result[4] = cosr(radians);
    result[5] = sinr(radians);
    result[7] = -sinr(radians);
    result[8] = cosr(radians);
    return result;
}

AS_INLINE m33 make_rotation_y(real radians)
{
    m33 result = {};
    result[0] = cosr(radians);
    result[2] = -sinr(radians);
    result[4] = 1.0f;
    result[6] = sinr(radians);
    result[8] = cosr(radians);
    return result;
}

AS_INLINE m33 make_rotation_z(real radians)
{
    m33 result = {};
    result[0] = cosr(radians);
    result[1] = sinr(radians);
    result[3] = -sinr(radians);
    result[4] = cosr(radians);
    result[8] = 1.0f;
    return result;
}

}