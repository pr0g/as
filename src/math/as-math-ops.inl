namespace as
{

namespace vec
{

template<typename T, size_t n>
size_t size(vec_t<T, n>&)
{
    return n;
}

template<typename T, size_t n>
const T* const_data(const vec_t<T, n>& vec)
{
    return vec.elems();
}

template<typename T, size_t n>
T* data(vec_t<T, n>& vec)
{
    return vec.elems();
}

template<typename T, size_t n>
vec_t<T, n> from_arr(const T(&data)[n])
{
    vec_t<T, n> result;
    std::copy(std::begin(data), std::end(data), result.elems());
    return result;
}

template<typename T, size_t n>
vec_t<T, n> from_ptr(const T* data)
{
    vec_t<T, n> result;
    std::copy(data, data + n, result.elems());
    return result;
}

template<typename T, size_t n>
T dot(const vec_t<T, n>& lhs, const vec_t<T, n>& rhs)
{
    T result = 0;
    for (size_t i = 0; i < n; ++i) {
        result += lhs[i] * rhs[i];
    }
    return result;
}

template<>
real_t dot(const vec3_t& lhs, const vec3_t& rhs)
{
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

template<typename T, size_t n>
T length_squared(const vec_t<T, n>& vec)
{
    T result = 0;
    for (size_t i = 0; i < n; ++i) {
        result += vec[i] * vec[i];
    }
    return result;
}

template<>
inline real_t length_squared(const vec3_t& vec)
{
    return dot(vec, vec);
}

template<typename T, size_t n>
T length(const vec_t<T, n>& vec)
{
    return sqrtr(length_squared(vec));
}

template<typename T, size_t n>
vec_t<T, n> normalize(const vec_t<T, n>& vec)
{
    return vec / length(vec);
}

template<typename T, size_t n>
T normalize_return_length(const vec_t<T, n>& vec, vec_t<T, n>& out)
{
    T len = length(vec);
    out = vec / len;
    return len;
}

template<typename T, size_t n>
bool equal(const vec_t<T, n>& lhs, const vec_t<T, n>& rhs,
    real_t epsilon /*= std::numeric_limits<real_t>::epsilon()*/)
{
    bool eq = true;
    for (size_t i = 0; i < n; ++i) {
        eq &= as::equal(lhs[i], rhs[i], epsilon, epsilon);
        if (!eq) { break; }
    }
    return eq;
}

template<typename T, size_t n>
vec_t<T, n> min(const vec_t<T, n>& lhs, const vec_t<T, n>& rhs)
{
    vec_t<T, n> result;
    for (size_t i = 0; i < n; ++i) {
        result[ i ] = as::min(lhs[i], rhs[i]);
    }
    return result;
}

template<typename T, size_t n>
T min_elem(const vec_t<T, n>& vec)
{
    T val = vec[0];
    for (size_t i = 1; i < n; ++i) {
        val = as::min(val, vec[i]);
    }
    return val;
}

template<typename T, size_t n>
vec_t<T, n> max(const vec_t<T, n>& lhs, const vec_t<T, n>& rhs)
{
    vec_t<T, n> result;
    for (size_t i = 0; i < n; ++i) {
        result[ i ] = as::max(lhs[i], rhs[i]);
    }
    return result;
}

template<typename T, size_t n>
T max_elem(const vec_t<T, n>& vec)
{
    T val = vec[0];
    for (size_t i = 1; i < n; ++i) {
        val = as::max(val, vec[i]);
    }
    return val;
}

template<typename T, size_t n>
vec_t<T, n> abs(const vec_t<T, n>& vec)
{
    vec_t<T, n> result;
    for (size_t i = 0; i < n; ++i) {
        result[ i ] = absr(vec[i]);
    }
    return result;
}

template<typename T, size_t n>
vec_t<T, n> clamp(const vec_t<T, n>& vec,
    const vec_t<T, n>& min, const vec_t<T, n>& max)
{
    vec_t<T, n> result;
    for (size_t i = 0; i < n; ++i) {
        result[ i ] = as::clamp( vec[ i ], min[ i ], max[ i ] );
    }
    return result;
}

template<typename T, size_t n>
vec_t<T, n> saturate(const vec_t<T, n>& vec)
{
    vec_t<T, n> result;
    for (size_t i = 0; i < n; ++i) {
        result[ i ] = as::clamp( vec[ i ], 0.0f, 1.0f );
    }
    return result;
}

template<typename T, size_t n>
vec_t<T, n> lerp(T t, const vec_t<T, n>& v0, const vec_t<T, n>& v1)
{
    vec_t<T, n> result;
    for (size_t i = 0; i < n; ++i) {
        result[ i ] = as::lerp(t, v0[i], v1[i]);
    }
    return result;
}

template<typename T, size_t n>
vec_t<T, n> select(const vec_t<T, n>& v0, const vec_t<T, n>& v1, bool select0)
{
    return select0 ? v0 : v1;
}

} // namespace vec

namespace vec2
{

vec2_t from_ptr(const real_t* data)
{
    return vec::from_ptr<real_t, 2>(data);
}

vec2_t from_arr(const real_t(&data)[2])
{
    return vec::from_arr(data);
}

real_t wedge(const vec2_t& lhs, const vec2_t& rhs)
{
    return lhs.x * rhs.y - lhs.y * rhs.x;
}

} // namespace vec2

namespace vec3
{

vec3_t from_ptr(const real_t* data)
{
    return vec::from_ptr<real_t, 3>(data);
}

vec3_t from_arr(const real_t(&data)[3])
{
    return vec::from_arr(data);
}

vec3_t cross(const vec3_t& lhs, const vec3_t& rhs)
{
    return {
        lhs.y * rhs.z - lhs.z * rhs.y,
        lhs.z * rhs.x - lhs.x * rhs.z,
        lhs.x * rhs.y - lhs.y * rhs.x
    };
}

// note: will not work if dir == +/-world_up
void right_and_up_lh(
    const vec3_t& dir, vec3_t& across, vec3_t& up, const vec3_t& world_up)
{
    across = cross(dir, world_up);
    up = vec::normalize(cross(across, dir));
    across = vec::normalize(cross(up, dir));
}

// note: will not work if dir == +/-world_up
void right_and_up_rh(
    const vec3_t& dir, vec3_t& across, vec3_t& up, const vec3_t& world_up)
{
    across = cross(dir, world_up);
    up = vec::normalize(cross(across, dir));
    across = vec::normalize(cross(dir, up));
}

} // namespace vec3

namespace vec4
{

vec4_t from_ptr(const real_t* data)
{
    return vec::from_ptr<real_t, 4>(data);
}

vec4_t from_arr(const real_t(&data)[4])
{
    return vec::from_arr(data);
}

} // namespace vec4

namespace mat
{

template<typename T, size_t r, size_t c>
T* data(const mat_t<T, r, c>& mat)
{
    return mat.elems();
}

template<typename T, size_t r, size_t c>
const T* const_data(const mat_t<T, r, c>& mat)
{
    return mat.elems();
}

template<typename T, size_t r, size_t c>
mat_t<T, r, c> from_arr(const T(&data)[r * c])
{
    mat_t<T, r, c> result;
    std::copy(std::begin(data), std::end(data), result.elems());
    return result;
}

template<typename T, size_t r, size_t c>
mat_t<T, r, c> from_ptr(const T* data)
{
    mat_t<T, r, c> result;
    std::copy(data, data + r * c, result.elems());
    return result;
}

template<typename T, size_t r, size_t c>
mat_t<T, r, c> transpose(const mat_t<T, r, c>& mat)
{
    mat_t<T, r, c> result;
    for (size_t rowIndex = 0; rowIndex < r; ++rowIndex) {
        for (size_t colIndex = 0; colIndex < c; ++colIndex) {
            result[colIndex * r + rowIndex] = mat[rowIndex * c + colIndex];
        }
    }
    return result;
}

template<typename T, size_t rc>
constexpr mat_t<T, rc, rc> identity()
{
    mat_t<T, rc, rc> identity{};
    const size_t size = rc * rc;
    for (size_t i = 0; i < size; i += rc + 1) {
        identity[i] = 1.0f;
    }
    return identity;
}

namespace internal
{

template<size_t> struct int2type {};

template<typename T>
T minor(const mat_t<T, 2, 2>& mat)
{
    return mat[0] * mat[3] - mat[2] * mat[1];
}

// where col and row are the rows to ignore
template<typename T, size_t rc>
mat_t<T, rc - 1, rc - 1> sub_matrix(
    const mat_t<T, rc, rc>& mat, size_t col, size_t row)
{
    mat_t<T, rc - 1, rc - 1> result = identity<T, rc - 1>();
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
T determinant_impl(const mat_t<T, rc, rc>& mat, int2type<I>)
{
    T sign{ 1 };
    T result = 0;
    for (size_t i = 0; i < rc; ++i) {
        T minor = determinant_impl(sub_matrix(mat, i, 0), int2type<I - 1>{});
        result += (mat[i] * minor) * sign;
        sign *= T{ -1 };
    }
    return result;
}

template<typename T>
T determinant_impl(const mat_t<T, 2, 2>& mat, int2type<2>)
{
    return minor(mat);
};

template<typename T, size_t rc, size_t I>
mat_t<T, rc, rc> minor_impl(const mat_t<T, rc, rc>& mat, int2type<I>)
{
    mat_t<T, rc, rc> result;
    T outerSign = T{ 1 };
    for (size_t i = 0; i < rc; ++i) {
        T innerSign = outerSign;
        for (size_t j = 0; j < rc; ++j) {
            T minor = determinant_impl<T>(
                internal::sub_matrix(mat, j, i),
                int2type<rc - 1>{});
            result[j + i * rc] = minor * innerSign;
            innerSign *= T{ -1 };
        }
        outerSign *= T{ -1 };
    }
    return result;
}

} // namespace internal

template<typename T, size_t rc>
T determinant(const mat_t<T, rc, rc>& mat)
{
    return internal::determinant_impl(mat, internal::int2type<rc>{});
}

template<typename T, size_t rc>
mat_t<T, rc, rc> inverse(const mat_t<T, rc, rc>& mat)
{
    mat_t<T, rc, rc> result;

    result = internal::minor_impl(mat, internal::int2type<rc>{});
    result = transpose(result);
    result *= 1.0f / determinant(mat);

    return result;
}

template<typename T, size_t rc>
mat_t<T, rc, rc> gj_inverse(const mat_t<T, rc, rc>& mat)
{
    mat_t<T, rc, rc> curr_mat = mat;
    mat_t<T, rc, rc> result = identity<T, rc>();

    size_t currentLine = 0;
    for (size_t i = 0; i < rc; ++i) {
        T diagonal = curr_mat[(rc * i) + i];
        T diagonal_recip = T{ 1 } / diagonal;

        for (size_t j = rc * i; j < rc + (rc * i); ++j) {
            curr_mat[j] *= diagonal_recip;
            result[j] *= diagonal_recip;
        }

        for (size_t row = 0; row < rc; ++row) {
            if (row == currentLine)
                continue;
            T next = curr_mat[currentLine + row * rc];
            for (size_t col = 0; col < rc; ++col) {
                size_t index = rc * row + col;
                curr_mat[index] -= (next * curr_mat[rc * currentLine + col]);
                result[index] -= (next * result[rc * currentLine + col]);
            }
        }

        ++currentLine;
    }

    return result;
}

} // namespace mat

namespace mat33
{

constexpr mat33_t identity()
{
    return mat::identity<real_t, 3>();
}

mat33_t from_ptr(const real_t* data)
{
    return mat::from_ptr<real_t, 3, 3>(data);
}

mat33_t from_arr(const real_t(&data)[9])
{
    return mat::from_arr<real_t, 3, 3>(data);
}

mat33_t axis_angle(const vec3_t& axis, real_t radians)
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

mat33_t rotation_xyz(real_t x, real_t y, real_t z)
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

mat33_t rotation_zxy(real_t x, real_t y, real_t z)
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

mat33_t rotation_x(real_t radians)
{
    return {
        1.0f, 0.0f, 0.0f,
        0.0f, cosr(radians), sinr(radians),
        0.0f, -sinr(radians), cosr(radians)
    };
}

mat33_t rotation_y(real_t radians)
{
    return {
        cosr(radians), 0.0f, -sinr(radians),
        0.0f, 1.0f, 0.0f,
        sinr(radians), 0.0f, cosr(radians)
    };
}

mat33_t rotation_z(real_t radians)
{
    return {
        cosr(radians), sinr(radians), 0.0f,
        -sinr(radians), cosr(radians), 0.0f,
        0.0f, 0.0f, 1.0f
    };
}

mat33_t scale(real_t scale)
{
    return {
        scale, 0.0f, 0.0f,
        0.0f, scale, 0.0f,
        0.0f, 0.0f, scale
    };
}

mat33_t scale(const vec3_t& scale)
{
    return {
        scale.x, 0.0f, 0.0f,
        0.0f, scale.y, 0.0f,
        0.0f, 0.0f, scale.z
    };
}

constexpr mat33_t from_mat44(const mat44_t& transform)
{
    return {
        transform.elem_rc[0][0], transform.elem_rc[0][1], transform.elem_rc[0][2],
        transform.elem_rc[1][0], transform.elem_rc[1][1], transform.elem_rc[1][2],
        transform.elem_rc[2][0], transform.elem_rc[2][1], transform.elem_rc[2][2],
    };
}

} // namespace mat33

namespace mat44
{

constexpr mat44_t identity()
{
    return mat::identity<real_t, 4>();
}

mat44_t from_ptr(const real_t* data)
{
    return mat::from_ptr<real_t, 4, 4>(data);
}

mat44_t from_arr(const real_t(&data)[16])
{
    return mat::from_arr<real_t, 4, 4>(data);
}

constexpr mat44_t from_vec3(const vec3_t& translation)
{
    return {
        vec4::axis_x(),
        vec4::axis_y(),
        vec4::axis_z(),
        { translation, 1.0f }
    };
}

constexpr mat44_t from_mat33(const mat33_t& rotation)
{
    return { rotation, vec3::zero() };
}

constexpr mat44_t from_mat33_vec3(
    const mat33_t& rotation, const vec3_t& translation)
{
    return { rotation, translation };
}

} // namespace mat44

namespace point
{

bool equal(const point2_t& lhs, const point2_t& rhs,
    const real_t epsilon /*= std::numeric_limits<real_t>::epsilon()*/)
{
    return vec::equal(lhs.v, rhs.v, epsilon);
}

bool equal(const point3_t& lhs, const point3_t& rhs,
    const real_t epsilon /*= std::numeric_limits<real_t>::epsilon()*/)
{
    return vec::equal(lhs.v, rhs.v, epsilon);
}

} // namespace point

namespace quat
{

constexpr real_t dot(const quat_t& a, const quat_t& b)
{
    return a.w * b.w + a.x * b.x + a.y * b.y + a.z * b.z;
}

constexpr real_t length_squared(const quat_t& a)
{
    return dot(a, a);
}

real_t length(const quat_t& a)
{
    return sqrtr(length_squared(a));
}

quat_t normalize(const quat_t& a)
{
    return a / length(a);
}

constexpr quat_t conjugate(const quat_t& a)
{
    return { a.w, -a.x, -a.y, -a.z };
}

quat_t inverse(const quat_t& a)
{
    return conjugate(a) / length_squared(a);
}

vec3_t rotate(const quat_t& q, const vec3_t& v)
{
    const quat_t quat_result = q * quat_t{ 0.0f, v.x, v.y, v.z } * conjugate(q);
    return { quat_result.x, quat_result.y, quat_result.z };
}

quat_t axis_angle(const vec3_t& axis, real_t radians)
{
    return { cosr(0.5f * radians), axis * sinr(0.5f * radians) };
}

quat_t rotation_zxy(real_t x, real_t y, real_t z)
{
    return quat_t{ cosr(0.5f * y), 0.0f, sinr(0.5f * y), 0.0f } *
        quat_t{ cosr(0.5f * x), sinr(0.5f * x), 0.0f, 0.0f } *
        quat_t{ cosr(0.5f * z), 0.0f, 0.0f, sinr(0.5f * z) };
}

quat_t slerp(const quat_t& a, const quat_t& b, real_t u)
{
    const real_t theta = acosr(dot(a, b));
    return (a * sinr((1.0f - u) * theta) + b * sinr(u * theta)) / sinr(theta);
}

} // namespace quat

namespace affine
{

vec3_t transform_dir(const affine_t& affine, const vec3_t& direction)
{
#if defined AS_COL_MAJOR
    return affine.rotation * direction;
#elif defined AS_ROW_MAJOR
    return direction * affine.rotation;
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

vec3_t transform_pos(const affine_t& affine, const vec3_t& position_)
{
#if defined AS_COL_MAJOR
    return affine.rotation * position_ + affine.position;
#elif defined AS_ROW_MAJOR
    return position_ * affine.rotation + affine.position;
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

vec3_t inv_transform_dir(const affine_t& affine, const vec3_t& direction)
{
    const mat33_t invRotation = as::mat::inverse(affine.rotation);
#if defined AS_COL_MAJOR
    return invRotation * direction;
#elif defined AS_ROW_MAJOR
    return direction * invRotation;
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

vec3_t inv_transform_pos(const affine_t& affine, const vec3_t& position_)
{
    const mat33_t invRotation = as::mat::inverse(affine.rotation);
#if defined AS_COL_MAJOR
    return invRotation * (position_ - affine.position);
#elif defined AS_ROW_MAJOR
    return (position_ - affine.position) * invRotation;
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

} // namespace affine

} // namespace as
