namespace as
{

template<typename T, size_t n>
size_t v_size(Vec<T, n>&)
{
    return n;
}

template<typename T, size_t n>
const T* v_const_data(const Vec<T, n>& vec)
{
    return vec.elem;
}

template<typename T, size_t n>
T* v_data(Vec<T, n>& vec)
{
    return vec.elem;
}

template<typename T, size_t n>
constexpr Vec<T, n> v_from_arr(const T(&data)[n])
{
    Vec<T, n> result;
    std::copy(std::begin(data), std::end(data), result.elem);
    return result;
}

template<typename T, size_t n>
constexpr Vec<T, n> v_from_ptr(const T* data)
{
    Vec<T, n> result;
    std::copy(data, data + n, result.elem);
    return result;
}

template<typename T, size_t n>
T v_dot(const Vec<T, n>& lhs, const Vec<T, n>& rhs)
{
    T result = 0;
    for (size_t i = 0; i < n; ++i) {
        result += lhs[i] * rhs[i];
    }
    return result;
}

template<typename T, size_t n>
T v_length_squared(const Vec<T, n>& vec)
{
    T result = 0;
    for (size_t i = 0; i < n; ++i) {
        result += vec[i] * vec[i];
    }
    return result;
}

template<typename T, size_t n>
T v_length(const Vec<T, n>& vec)
{
    return sqrt(v_length_squared(vec));
}

template<typename T, size_t n>
Vec<T, n> v_normalize(const Vec<T, n>& vec)
{
    return vec / v_length(vec);
}

template<typename T, size_t n>
T v_normalize_return_length(const Vec<T, n>& vec, Vec<T, n>& out)
{
    T len = v_length(vec);
    out = vec / len;
    return len;
}

template<typename T, size_t n>
bool v_equal(const Vec<T, n>& lhs, const Vec<T, n>& rhs, real epsilon /*= std::numeric_limits<real>::epsilon()*/)
{
    bool eq = true;
    for (size_t i = 0; i < n; ++i) {
        eq &= as::equal(lhs[i], rhs[i], epsilon, epsilon);
        if (!eq) { break; }
    }
    return eq;
}

template<typename T, size_t n>
Vec<T, n> v_min(const Vec<T, n>& lhs, const Vec<T, n>& rhs)
{
    Vec<T, n> result;
    for (size_t i = 0; i < n; ++i) {
        result[ i ] = as::min(lhs[i], rhs[i]);
    }
    return result;
}

template<typename T, size_t n>
T v_min_elem(const Vec<T, n>& vec)
{
    T val = vec[0];
    for (size_t i = 1; i < n; ++i) {
        val = as::min(val, vec[i]);
    }
    return val;
}

template<typename T, size_t n>
Vec<T, n> v_max(const Vec<T, n>& lhs, const Vec<T, n>& rhs)
{
    Vec<T, n> result;
    for (size_t i = 0; i < n; ++i) {
        result[ i ] = as::max(lhs[i], rhs[i]);
    }
    return result;
}

template<typename T, size_t n>
T v_max_elem(const Vec<T, n>& vec)
{
    T val = vec[0];
    for (size_t i = 1; i < n; ++i) {
        val = as::max(val, vec[i]);
    }
    return val;
}

template<typename T, size_t n>
Vec<T, n> v_abs(const Vec<T, n>& vec)
{
    Vec<T, n> result;
    for (size_t i = 0; i < n; ++i) {
        result[ i ] = absr(vec[i]);
    }
    return result;
}

template<typename T, size_t n>
Vec<T, n> v_clamp(const Vec<T, n>& vec, const Vec<T, n>& min, const Vec<T, n>& max)
{
    Vec<T, n> result;
    for (size_t i = 0; i < n; ++i) {
        result[ i ] = as::clamp( vec[ i ], min[ i ], max[ i ] );
    }
    return result;
}

template<typename T, size_t n>
Vec<T, n> v_saturate(const Vec<T, n>& vec)
{
    Vec<T, n> result;
    for (size_t i = 0; i < n; ++i) {
        result[ i ] = as::clamp( vec[ i ], 0.0f, 1.0f );
    }
    return result;
}

template<typename T, size_t n>
Vec<T, n> v_lerp(T t, const Vec<T, n>& v0, const Vec<T, n>& v1)
{
    Vec<T, n> result;
    for (size_t i = 0; i < n; ++i) {
        result[ i ] = as::lerp(t, v0[i], v1[i]);
    }
    return result;
}

template<typename T, size_t n>
Vec<T, n> v_select(const Vec<T, n>& v0, const Vec<T, n>& v1, bool select0)
{
    return select0 ? v0 : v1;
}

constexpr inline v2 v2_from_ptr(const real* data)
{
    return v_from_ptr<real, 2>(data);
}

constexpr inline v2 v2_from_arr(const real(&data)[2])
{
    return v_from_arr(data);
}

constexpr v3 v3_from_ptr(const real* data)
{
    return v_from_ptr<real, 3>(data);
}

constexpr v3 v3_from_arr(const real(&data)[3])
{
    return v_from_arr(data);
}

constexpr v4 v4_from_ptr(const real* data)
{
    return v_from_ptr<real, 4>(data);
}

constexpr v4 v4_from_arr(const real(&data)[4])
{
    return v_from_arr(data);
}

real v2_wedge(const v2& lhs, const v2& rhs)
{
    return lhs.x * rhs.y - lhs.y * rhs.x;
}

v3 v3_cross(const v3& lhs, const v3& rhs)
{
    return {
        lhs.y * rhs.z - lhs.z * rhs.y,
        lhs.z * rhs.x - lhs.x * rhs.z,
        lhs.x * rhs.y - lhs.y * rhs.x
    };
}

// note: will not work if dir == +/-world_up
void v3_right_and_up_lh(const v3& dir, v3& across, v3& up, const v3& world_up /*= v3_y*/)
{
    AS_ASSERT_DESC(!v_equal(dir, world_up), "dir and world_up are equal");

    across = v3_cross(dir, world_up);
    up = v_normalize(v3_cross(across, dir));
    across = v_normalize(v3_cross(up, dir));
}

// note: will not work if dir == +/-world_up
void v3_right_and_up_rh(const v3& dir, v3& across, v3& up, const v3& world_up /*= v3_y*/)
{
    AS_ASSERT_DESC(!v_equal(dir, world_up), "dir and world_up are equal");

    across = v3_cross(dir, world_up);
    up = v_normalize(v3_cross(across, dir));
    across = v_normalize(v3_cross(dir, up));
}

template<typename T, size_t r, size_t c>
inline T* m_data(const Mat<T, r, c>& mat)
{
    return mat.elem;
}

template<typename T, size_t r, size_t c>
inline const T* m_const_data(const Mat<T, r, c>& mat)
{
    return mat.elem;
}

template<typename T, size_t r, size_t c>
constexpr inline Mat<T, r, c> m_from_arr(const T(&data)[r * c])
{
    Mat<T, r, c> result;
    std::copy(std::begin(data), std::end(data), result.elem);
    return result;
}

template<typename T, size_t r, size_t c>
constexpr inline Mat<T, r, c> m_from_ptr(const T* data)
{
    Mat<T, r, c> result;
    std::copy(data, data + r * c, result.elem);
    return result;
}

template<typename T, size_t r, size_t c>
inline Mat<T, r, c> m_transpose(const Mat<T, r, c>& mat)
{
    Mat<T, r, c> result;
    for (size_t rowIndex = 0; rowIndex < r; ++rowIndex) {
        for (size_t colIndex = 0; colIndex < c; ++colIndex) {
            result[colIndex * r + rowIndex] = mat[rowIndex * c + colIndex];
        }
    }
    return result;
}

template<typename T, size_t rc>
constexpr inline Mat<T, rc, rc> m_identity()
{
    Mat<T, rc, rc> identity;
    size_t size = rc * rc;
    std::fill(std::begin(identity.elem), std::end(identity.elem), 0.0f);
    for (size_t i = 0; i < size; i += rc + 1) {
        identity.elem[i] = 1.0f;
    }
    return identity;
}

namespace internal
{

template<size_t> struct int2type {};

template<typename T>
inline T m_minor(const Mat<T, 2, 2>& mat)
{
    return mat[0] * mat[3] - mat[2] * mat[1];
}

// where col and row are the rows to ignore
template<typename T, size_t rc>
inline Mat<T, rc - 1, rc - 1> m_sub_matrix(const Mat<T, rc, rc>& mat, size_t col, size_t row)
{
    Mat<T, rc - 1, rc - 1> result = m_identity<T, rc - 1>();
    size_t i = 0;
    for (size_t r = 0; r < rc; ++r) {
        for (size_t c = 0; c < rc; ++c) {
            if (r == row || c == col)
                continue;
            result[i++] = mat[r * rc + c];
        }
    }
    return result;
}

template<typename T, size_t rc, size_t I>
T m_determinant_impl(const Mat<T, rc, rc>& mat, int2type<I>)
{
    T sign{ 1 };
    T result = 0;
    for (size_t i = 0; i < rc; ++i) {
        T minor = m_determinant_impl(m_sub_matrix(mat, i, 0), int2type<I - 1>{});
        result += (mat[i] * minor) * sign;
        sign *= T{ -1 };
    }
    return result;
}

template<typename T>
T m_determinant_impl(const Mat<T, 2, 2>& mat, int2type<2>)
{
    return m_minor(mat);
};

template<typename T, size_t rc, size_t I>
inline Mat<T, rc, rc> m_minor_impl(const Mat<T, rc, rc>& mat, int2type<I>)
{
    Mat<T, rc, rc> result;
    T outerSign = T{ 1 };
    for (size_t i = 0; i < rc; ++i) {
        T innerSign = outerSign;
        for (size_t j = 0; j < rc; ++j) {
            T minor = m_determinant_impl<T>(internal::m_sub_matrix(mat, j, i), int2type<rc - 1>{});
            result[j + i * rc] = minor * innerSign;
            innerSign *= T{ -1 };
        }
        outerSign *= T{ -1 };
    }
    return result;
}

} // namespace internal

template<typename T, size_t rc>
inline T m_determinant(const Mat<T, rc, rc>& mat)
{
    return internal::m_determinant_impl(mat, internal::int2type<rc>{});
}

template<typename T, size_t rc>
inline Mat<T, rc, rc> m_inverse(const Mat<T, rc, rc>& mat)
{
    Mat<T, rc, rc> result;

    result = internal::m_minor_impl(mat, internal::int2type<rc>{});
    result = m_transpose(result);
    result *= 1.0f / m_determinant(mat);

    return result;
}

template<typename T, size_t rc>
inline Mat<T, rc, rc> m_gj_inverse(const Mat<T, rc, rc>& mat)
{
    Mat<T, rc, rc> currentMat = mat;
    Mat<T, rc, rc> result = identity<T, rc>();

    size_t currentLine = 0;
    for (size_t i = 0; i < rc; ++i) {
        T diagonal = currentMat[(rc * i) + i];
        T diagonalRecip = T{ 1 } / diagonal;

        for (size_t j = rc * i; j < rc + (rc * i); ++j) {
            currentMat[j] *= diagonalRecip;
            result[j] *= diagonalRecip;
        }

        for (size_t row = 0; row < rc; ++row) {
            if (row == currentLine)
                continue;
            T next = currentMat[currentLine + row * rc];
            for (size_t col = 0; col < rc; ++col) {
                size_t index = rc * row + col;
                currentMat[index] -= (next * currentMat[rc * currentLine + col]);
                result[index] -= (next * result[rc * currentLine + col]);
            }
        }

        ++currentLine;
    }

    return result;
}

constexpr m33 m33_from_ptr(const real* data)
{
    return as::m_from_ptr<real, 3, 3>(data);
}

constexpr m33 m33_from_arr(const real(&data)[9])
{
    return as::m_from_arr<real, 3, 3>(data);
}

constexpr m33 m33_axis_angle(const v3& axis, real radians)
{
    return {
        cosr(radians) + ((axis.x * axis.x) * (1.0f - cosr(radians))),
        (axis.y * axis.x * (1.0f - cosr(radians))) + (axis.z * sinr(radians)),
        (axis.z * axis.x * (1.0f - cosr(radians))) - (axis.y * sinr(radians)),
        (axis.x * axis.y) * (1.0f - cosr(radians)) - (axis.z * sinr(radians)),
        cosr(radians) + ((axis.y * axis.y) * (1.0f - cosr(radians))),
        (axis.z * axis.y * (1.0f - cosr(radians))) + (axis.x * sinr(radians)),
        (axis.x * axis.z * (1.0f - cosr(radians))) + (axis.y * sinr(radians)),
        (axis.y * axis.z * (1.0f - cosr(radians))) - (axis.x * sinr(radians)),
        cosr(radians) + ((axis.z * axis.z) * (1.0f - cosr(radians)))
    };
}

constexpr m33 m33_rotation_xyz(real x, real y, real z)
{
    return {
        cosr(y) * cosr(z),
        cosr(y) * sinr(z),
        -sinr(y),
        (sinr(x) * sinr(y) * cosr(z)) - (cosr(x) * sinr(z)),
        (sinr(x) * sinr(y) * sinr(z)) + (cosr(x) * cosr(z)),
        sinr(x) * cosr(y),
        (cosr(x) * sinr(y) * cosr(z)) + (sinr(x) * sinr(z)),
        (cosr(x) * sinr(y) * sinr(z)) - (sinr(x) * cosr(z)),
        cosr(x) * cosr(y)
    };
}

constexpr m33 m33_rotation_zxy(real x, real y, real z)
{
    return {
        cosr(z) * cosr(y) + sinr(x) * sinr(y) * sinr(z),
        sinr(z) * cosr(x),
        -sinr(y) * cosr(z) + sinr(z) * sinr(x) * cosr(y),
        -sinr(z) * cosr(y) + cosr(z) * sinr(x) * sinr(y),
        cosr(z) * cosr(x),
        -sinr(z) * -sinr(y) + cosr(z) * sinr(x) * cosr(y),
        cosr(x) * sinr(y),
        -sinr(x),
        cosr(x) * cosr(y),
    };
}

constexpr m33 m33_rotation_x(real radians)
{
    return {
        1.0f, 0.0f, 0.0f,
        0.0f, cosr(radians), sinr(radians),
        0.0f, -sinr(radians), cosr(radians)
    };
}

constexpr m33 m33_rotation_y(real radians)
{
    return {
        cosr(radians), 0.0f, -sinr(radians),
        0.0f, 1.0f, 0.0f,
        sinr(radians), 0.0f, cosr(radians)
    };
}

constexpr m33 m33_rotation_z(real radians)
{
    return {
        cosr(radians), sinr(radians), 0.0f,
        -sinr(radians), cosr(radians), 0.0f,
        0.0f, 0.0f, 1.0f
    };
}

constexpr inline m33 m33_from_m44(const m44& transform)
{
    return {
        transform.x0, transform.x1, transform.x2,
        transform.y0, transform.y1, transform.y2,
        transform.z0, transform.z1, transform.z2
    };
}

constexpr inline m44 m44_from_ptr(const real* data)
{
    return as::m_from_ptr<real, 4, 4>(data);
}

constexpr inline m44 m44_from_arr(const real(&data)[16])
{
    return as::m_from_arr<real, 4, 4>(data);
}

constexpr inline m44 m44_from_v3(const v3& translation)
{
    return { v4_axis_x(), v4_axis_y(), v4_axis_z(),{ translation, 1.0f } };
}

constexpr inline m44 m44_from_m33(const m33& rotation)
{
    return { rotation, v3_zero() };
}

constexpr inline m44 m44_from_m33_v3(const m33& rotation, const v3& translation)
{
    return { rotation, translation };
}

inline bool p_equal(const p2& lhs, const p2& rhs,
    const real epsilon /*= std::numeric_limits<real>::epsilon()*/)
{
    return as::v_equal(lhs.v, rhs.v, epsilon);
}

inline bool p_equal(const p3& lhs, const p3& rhs,
    const real epsilon /*= std::numeric_limits<real>::epsilon()*/)
{
    return as::v_equal(lhs.v, rhs.v, epsilon);
}

constexpr inline real q_dot(const quat& a, const quat& b)
{
    return a.r * b.r + a.i * b.i + a.j * b.j + a.k * b.k;
}

constexpr inline real q_length_squared(const quat& a)
{
    return q_dot(a, a);
}

inline real q_length(const quat& a)
{
    return std::sqrt(q_length_squared(a));
}

inline quat q_normalize(const quat& a)
{
    return a / q_length(a);
}

constexpr inline quat q_conjugate(const quat& a)
{
    return { a.r, -a.i, -a.j, -a.k };
}

inline quat q_inverse(const quat& a)
{
    return q_conjugate(a) / q_length_squared(a);
}

inline v3 q_rotate(const quat& q, const v3& v)
{
    const quat quat_result = q * quat{ 0.0f, v.x, v.y, v.z } *q_conjugate(q);
    return { quat_result.i, quat_result.j, quat_result.k };
}

inline quat q_axis_angle(const v3& axis, real radians)
{
    return { cosr(0.5f * radians), axis * sinr(0.5f * radians) };
}

inline quat q_rotation_zxy(real x, real y, real z)
{
    return quat{ cosr(0.5f * y), 0.0f, sinr(0.5f * y), 0.0f } *
        quat{ cosr(0.5f * x), sinr(0.5f * x), 0.0f, 0.0f } *
        quat{ cosr(0.5f * z), 0.0f, 0.0f, sinr(0.5f * z) };
}

inline quat q_slerp(const quat& a, const quat& b, real u)
{
    const real theta = acosr(q_dot(a, b));
    return (a * sinr((1.0f - u) * theta) + b * sinr(u * theta)) / sinr(theta);
}

} // namespace as