namespace as
{

namespace vec
{

template<typename T, index_t n>
index_t size(const vec_t<T, n>&)
{
    return n;
}

template<typename T, index_t n>
vec_t<T, n> from_arr(const T(&data)[n])
{
    return from_ptr<T, n>(&data[0]);
}

template<typename T, index_t n>
vec_t<T, n> from_ptr(const T* data)
{
    vec_t<T, n> result;

    for (index_t i = 0; i < n; ++i) {
        result[i] = data[i];
    }

    return result;
}

template<typename T, index_t n>
void to_arr(const vec_t<T, n>& vec, T(&data)[n])
{
    for (index_t i = 0; i < n; ++i) {
        data[i] = vec[i];
    }
}

template<typename T, index_t n>
T dot(const vec_t<T, n>& lhs, const vec_t<T, n>& rhs)
{
    T result { 0 };

    for (index_t i = 0; i < n; ++i) {
        result += lhs[i] * rhs[i];
    }

    return result;
}

template<>
inline real_t dot(const vec3_t& lhs, const vec3_t& rhs)
{
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

template<typename T, index_t n>
T length_sq(const vec_t<T, n>& vec)
{
    return dot(vec, vec);
}

template<typename T, index_t n>
T length(const vec_t<T, n>& vec)
{
    return sqrtr(length_sq(vec));
}

template<typename T, index_t n>
vec_t<T, n> normalize(const vec_t<T, n>& vec)
{
    return vec / length(vec);
}

template<typename T, index_t n>
T normalize_return_length(const vec_t<T, n>& vec, vec_t<T, n>& out)
{
    const T len = length(vec);
    out = vec / len;
    return len;
}

template<typename T, index_t n>
bool equal(const vec_t<T, n>& lhs, const vec_t<T, n>& rhs,
    real_t epsilon /*= std::numeric_limits<real_t>::epsilon()*/)
{
    for (index_t i = 0; i < n; ++i) {
        if (!as::equal(lhs[i], rhs[i], epsilon, epsilon)) {
            return false;
        }
    }

    return true;
}

template<typename T, index_t n>
vec_t<T, n> min(const vec_t<T, n>& lhs, const vec_t<T, n>& rhs)
{
    vec_t<T, n> result;

    for (index_t i = 0; i < n; ++i) {
        result[i] = as::min(lhs[i], rhs[i]);
    }

    return result;
}

template<typename T, index_t n>
T min_elem(const vec_t<T, n>& vec)
{
    T val = vec[0];

    for (index_t i = 1; i < n; ++i) {
        val = as::min(val, vec[i]);
    }

    return val;
}

template<typename T, index_t n>
vec_t<T, n> max(const vec_t<T, n>& lhs, const vec_t<T, n>& rhs)
{
    vec_t<T, n> result;

    for (index_t i = 0; i < n; ++i) {
        result[i] = as::max(lhs[i], rhs[i]);
    }

    return result;
}

template<typename T, index_t n>
T max_elem(const vec_t<T, n>& vec)
{
    T val = vec[0];

    for (index_t i = 1; i < n; ++i) {
        val = as::max(val, vec[i]);
    }

    return val;
}

template<typename T, index_t n>
vec_t<T, n> abs(const vec_t<T, n>& vec)
{
    vec_t<T, n> result;

    for (index_t i = 0; i < n; ++i) {
        result[i] = fabsr(vec[i]);
    }

    return result;
}

template<typename T, index_t n>
vec_t<T, n> clamp(const vec_t<T, n>& vec,
    const vec_t<T, n>& min, const vec_t<T, n>& max)
{
    vec_t<T, n> result;

    for (index_t i = 0; i < n; ++i) {
        result[i] = as::clamp(vec[i], min[i], max[i]);
    }

    return result;
}

template<typename T, index_t n>
vec_t<T, n> saturate(const vec_t<T, n>& vec)
{
    vec_t<T, n> result;

    for (index_t i = 0; i < n; ++i) {
        result[i] = as::clamp(vec[i], real_t(0.0), real_t(1.0));
    }

    return result;
}

template<typename T, index_t n>
vec_t<T, n> lerp(T t, const vec_t<T, n>& v0, const vec_t<T, n>& v1)
{
    vec_t<T, n> result;

    for (index_t i = 0; i < n; ++i) {
        result[i] = as::lerp(t, v0[i], v1[i]);
    }

    return result;
}

template<typename T, index_t n>
vec_t<T, n> select(const vec_t<T, n>& v0, const vec_t<T, n>& v1, bool select0)
{
    return select0 ? v0 : v1;
}

} // namespace vec

namespace vec2
{

inline vec2_t from_ptr(const real_t* data)
{
    return vec::from_ptr<real_t, 2>(data);
}

inline vec2_t from_arr(const real_t(&data)[2])
{
    return vec::from_arr(data);
}

inline real_t wedge(const vec2_t& lhs, const vec2_t& rhs)
{
    return lhs.x * rhs.y - lhs.y * rhs.x;
}

} // namespace vec2

namespace vec3
{

inline vec3_t from_ptr(const real_t* data)
{
    return vec::from_ptr<real_t, 3>(data);
}

inline vec3_t from_arr(const real_t(&data)[3])
{
    return vec::from_arr(data);
}

inline vec3_t cross(const vec3_t& lhs, const vec3_t& rhs)
{
    return {
        lhs.y * rhs.z - lhs.z * rhs.y,
        lhs.z * rhs.x - lhs.x * rhs.z,
        lhs.x * rhs.y - lhs.y * rhs.x
    };
}

// note: will not work if dir == +/-world_up
inline void right_and_up_lh(
    const vec3_t& dir, vec3_t& across, vec3_t& up, const vec3_t& world_up)
{
    across = cross(dir, world_up);
    up = vec::normalize(cross(across, dir));
    across = vec::normalize(cross(up, dir));
}

// note: will not work if dir == +/-world_up
inline void right_and_up_rh(
    const vec3_t& dir, vec3_t& across, vec3_t& up, const vec3_t& world_up)
{
    across = cross(dir, world_up);
    up = vec::normalize(cross(across, dir));
    across = vec::normalize(cross(dir, up));
}

} // namespace vec3

namespace vec4
{

inline vec4_t from_ptr(const real_t* data)
{
    return vec::from_ptr<real_t, 4>(data);
}

inline vec4_t from_arr(const real_t(&data)[4])
{
    return vec::from_arr(data);
}

} // namespace vec4

namespace mat
{

template<typename T, index_t d>
mat_t<T, d> from_arr(const T(&data)[d * d])
{
    return from_ptr<T, d>(&data[0]);
}

template<typename T, index_t d>
mat_t<T, d> from_ptr(const T* data)
{
    mat_t<T, d> result;

    for (index_t i = 0; i < d * d; ++i) {
        result[i] = data[i];
    }

    return result;
}

template<typename T, index_t d>
AS_API void to_arr(const mat_t<T, d>& mat, T(&data)[d * d])
{
    for (index_t i = 0; i < d * d; ++i) {
        data[i] = mat[i];
    }
}

template<typename T, index_t d>
mat_t<T, d> transpose(const mat_t<T, d>& mat)
{
    mat_t<T, d> result;

    for (index_t rowIndex = 0; rowIndex < d; ++rowIndex) {
        for (index_t colIndex = 0; colIndex < d; ++colIndex) {
            result[colIndex * d + rowIndex] = mat[rowIndex * d + colIndex];
        }
    }

    return result;
}

template<typename T, index_t d>
constexpr mat_t<T, d> identity()
{
    mat_t<T, d> identity{};

    for (index_t i = 0; i < mat_t<T, d>::size(); i += d + 1) {
        identity[i] = 1.0f;
    }

    return identity;
}

namespace internal
{

template<index_t> struct int2type {};

// where col and row are the rows to ignore
template<typename T, index_t d>
mat_t<T, d - 1> sub_matrix(
    const mat_t<T, d>& mat, const index_t col, const index_t row)
{
    mat_t<T, d - 1> result = identity<T, d - 1>();
    index_t i = 0;

    for (index_t r = 0; r < d; ++r) {
        for (index_t c = 0; c < d; ++c) {
            if (r == row || c == col) {
                continue;
            }

            result[i++] = mat[r * d + c];
        }
    }

    return result;
}

#pragma push_macro("minor")
#undef minor

template<typename T>
T minor(const mat_t<T, 2>& mat)
{
    return mat[0] * mat[3] - mat[2] * mat[1];
}

template<typename T, index_t d, index_t I>
T determinant_impl(const mat_t<T, d>& mat, int2type<I>)
{
    T sign { 1.0f };
    T result{ 0.0f };

    for (index_t i = 0; i < d; ++i) {
        T minor = determinant_impl(sub_matrix(mat, i, 0), int2type<I - 1> {});
        result += (mat[i] * minor) * sign;
        sign *= T { -1.0f };
    }

    return result;
}

template<typename T>
T determinant_impl(const mat_t<T, 2>& mat, int2type<2>)
{
    return minor(mat);
}

#pragma pop_macro("minor")

template<typename T, index_t d, index_t I>
mat_t<T, d> minor_impl(const mat_t<T, d>& mat, int2type<I>)
{
    mat_t<T, d> result;
    T outerSign = T { 1.0f };

    for (index_t i = 0; i < d; ++i) {
        T innerSign { outerSign };

        for (index_t j = 0; j < d; ++j) {
            T minor = determinant_impl<T>(
                    internal::sub_matrix(mat, j, i),
                    int2type<d - 1> {});
            result[j + i * d] = minor * innerSign;
            innerSign *= T{ -1.0f };
        }

        outerSign *= T { -1.0f };
    }

    return result;
}

} // namespace internal

template<typename T, index_t d>
T determinant(const mat_t<T, d>& mat)
{
    return internal::determinant_impl(mat, internal::int2type<d> {});
}

template<typename T, index_t d>
mat_t<T, d> inverse(const mat_t<T, d>& mat)
{
    mat_t<T, d> result;

    result = internal::minor_impl(mat, internal::int2type<d> {});
    result = transpose(result);
    result *= real_t(1.0f) / determinant(mat);

    return result;
}

template<typename T>
mat_t<T, 2> inverse(const mat_t<T, 2>& mat)
{
    return mat_t<T, 2> {
        mat[3], -mat[1],
        -mat[2], mat[0]
    } * (real_t(1.0f) / determinant(mat));
}

template<typename T, index_t d>
mat_t<T, d> gj_inverse(const mat_t<T, d>& mat)
{
    mat_t<T, d> curr_mat = mat;
    mat_t<T, d> result = identity<T, d>();

    index_t currentLine = 0;

    for (index_t i = 0; i < d; ++i) {
        T diagonal = curr_mat[(d * i) + i];
        T diagonal_recip = T{ 1 } / diagonal;

        for (index_t j = d * i; j < d + (d * i); ++j) {
            curr_mat[j] *= diagonal_recip;
            result[j] *= diagonal_recip;
        }

        for (index_t row = 0; row < d; ++row) {
            if (row == currentLine) {
                continue;
            }

            T next = curr_mat[currentLine + row * d];

            for (index_t col = 0; col < d; ++col) {
                index_t index_t = d * row + col;
                curr_mat[index_t] -= (next * curr_mat[d * currentLine + col]);
                result[index_t] -= (next * result[d * currentLine + col]);
            }
        }

        ++currentLine;
    }

    return result;
}

} // namespace mat

namespace mat3
{

constexpr mat3_t identity()
{
    return mat::identity<real_t, 3>();
}

inline mat3_t from_ptr(const real_t* data)
{
    return mat::from_ptr<real_t, 3>(data);
}

inline mat3_t from_arr(const real_t(&data)[9])
{
    return mat::from_arr<real_t, 3>(data);
}

inline mat3_t axis_angle(const vec3_t& axis, const real_t radians)
{
    const real_t cosr_radians = cosr(radians);
    const real_t sinr_radians = sinr(radians);

    return {
        cosr_radians + ((axis.x * axis.x) * (1.0f - cosr_radians)),
        (axis.y * axis.x * (1.0f - cosr_radians)) + (axis.z * sinr_radians),
        (axis.z * axis.x * (1.0f - cosr_radians)) - (axis.y * sinr_radians),
        (axis.x * axis.y * (1.0f - cosr_radians)) - (axis.z * sinr_radians),
        cosr_radians + ((axis.y * axis.y) * (1.0f - cosr_radians)),
        (axis.z * axis.y * (1.0f - cosr_radians)) + (axis.x * sinr_radians),
        (axis.x * axis.z * (1.0f - cosr_radians)) + (axis.y * sinr_radians),
        (axis.y * axis.z * (1.0f - cosr_radians)) - (axis.x * sinr_radians),
        cosr_radians + ((axis.z * axis.z) * (1.0f - cosr_radians))
    };
}

inline mat3_t rotation_xyz(const real_t x, const real_t y, const real_t z)
{
    const real_t cosr_x = cosr(x);
    const real_t cosr_y = cosr(y);
    const real_t cosr_z = cosr(z);
    const real_t sinr_x = sinr(x);
    const real_t sinr_y = sinr(y);
    const real_t sinr_z = sinr(z);

    return {
        cosr_y * cosr_z,
        cosr_y * sinr_z,
        -sinr_y,
        (sinr_x * sinr_y * cosr_z) - (cosr_x * sinr_z),
        (sinr_x * sinr_y * sinr_z) + (cosr_x * cosr_z),
        sinr_x * cosr_y,
        (cosr_x * sinr_y * cosr_z) + (sinr_x * sinr_z),
        (cosr_x * sinr_y * sinr_z) - (sinr_x * cosr_z),
        cosr_x * cosr_y
    };
}

inline mat3_t rotation_zxy(const real_t x, const real_t y, const real_t z)
{
    const real_t cosr_x = cosr(x);
    const real_t cosr_y = cosr(y);
    const real_t cosr_z = cosr(z);
    const real_t sinr_x = sinr(x);
    const real_t sinr_y = sinr(y);
    const real_t sinr_z = sinr(z);

    return {
        cosr_z * cosr_y + sinr_x * sinr_y * sinr_z,
        sinr_z * cosr_x,
        -sinr_y * cosr_z + sinr_z * sinr_x * cosr_y,
        -sinr_z * cosr_y + cosr_z * sinr_x * sinr_y,
        cosr_z * cosr_x,
        -sinr_z * -sinr_y + cosr_z * sinr_x * cosr_y,
        cosr_x * sinr_y,
        -sinr_x,
        cosr_x * cosr_y,
    };
}

inline mat3_t rotation_x(const real_t radians)
{
    return {
        1.0f, 0.0f, 0.0f,
        0.0f, cosr(radians), sinr(radians),
        0.0f, -sinr(radians), cosr(radians)
    };
}

inline mat3_t rotation_y(const real_t radians)
{
    return {
        cosr(radians), 0.0f, -sinr(radians),
        0.0f, 1.0f, 0.0f,
        sinr(radians), 0.0f, cosr(radians)
    };
}

inline mat3_t rotation_z(const real_t radians)
{
    return {
        cosr(radians), sinr(radians), 0.0f,
        -sinr(radians), cosr(radians), 0.0f,
        0.0f, 0.0f, 1.0f
    };
}

inline mat3_t scale(const real_t scale)
{
    return mat3::scale(vec3_t{ scale });
}

inline mat3_t scale(const vec3_t& scale)
{
    return {
        scale.x, 0.0f, 0.0f,
        0.0f, scale.y, 0.0f,
        0.0f, 0.0f, scale.z
    };
}

constexpr mat3_t from_mat4(const mat4_t& transform)
{
    return {
        transform[0], transform[1], transform[2],
        transform[4], transform[5], transform[6],
        transform[8], transform[9], transform[10],
    };
}

} // namespace mat3

namespace mat4
{

constexpr mat4_t identity()
{
    return mat::identity<real_t, 4>();
}

inline mat4_t from_ptr(const real_t* data)
{
    return mat::from_ptr<real_t, 4>(data);
}

inline mat4_t from_arr(const real_t(&data)[16])
{
    return mat::from_arr<real_t, 4>(data);
}

constexpr mat4_t from_vec3(const vec3_t& translation)
{
    return { as::mat3::identity(), translation };
}

constexpr mat4_t from_mat3(const mat3_t& rotation)
{
    return { rotation, vec3::zero() };
}

constexpr mat4_t from_mat3_vec3(
    const mat3_t& rotation, const vec3_t& translation)
{
    return { rotation, translation };
}

} // namespace mat4

namespace point
{

inline bool equal(const point2_t& lhs, const point2_t& rhs,
    const real_t epsilon /*= std::numeric_limits<real_t>::epsilon()*/)
{
    return vec::equal(lhs.v, rhs.v, epsilon);
}

inline bool equal(const point3_t& lhs, const point3_t& rhs,
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

constexpr real_t length_sq(const quat_t& a)
{
    return dot(a, a);
}

inline real_t length(const quat_t& a)
{
    return sqrtr(length_sq(a));
}

inline quat_t normalize(const quat_t& a)
{
    return a / length(a);
}

constexpr quat_t conjugate(const quat_t& a)
{
    return { a.w, -a.x, -a.y, -a.z };
}

inline quat_t inverse(const quat_t& a)
{
    return conjugate(a) / length_sq(a);
}

inline vec3_t rotate(const quat_t& q, const vec3_t& v)
{
    const quat_t quat_result = q * quat_t{ 0.0f, v.x, v.y, v.z } * conjugate(q);
    return { quat_result.x, quat_result.y, quat_result.z };
}

inline quat_t axis_angle(const vec3_t& axis, const real_t radians)
{
    return { cosr(0.5f * radians), axis * sinr(0.5f * radians) };
}

inline quat_t rotation_zxy(const real_t x, const real_t y, const real_t z)
{
    return quat_t{ cosr(0.5f * y), 0.0f, sinr(0.5f * y), 0.0f } *
        quat_t{ cosr(0.5f * x), sinr(0.5f * x), 0.0f, 0.0f } *
        quat_t{ cosr(0.5f * z), 0.0f, 0.0f, sinr(0.5f * z) };
}

inline quat_t slerp(const quat_t& a, const quat_t& b, const real_t t)
{
    const real_t theta = acosr(dot(a, b));
    return (a * sinr((1.0f - t) * theta) + b * sinr(t * theta)) / sinr(theta);
}

} // namespace quat

namespace affine
{

inline vec3_t transform_dir(const affine_t& affine, const vec3_t& direction)
{
#if defined AS_COL_MAJOR
    return affine.rotation * direction;
#elif defined AS_ROW_MAJOR
    return direction * affine.rotation;
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

inline point3_t transform_pos(const affine_t& affine, const point3_t& position)
{
#if defined AS_COL_MAJOR
    return point3_t { affine.rotation * position.v } + affine.position.v;
#elif defined AS_ROW_MAJOR
    return point3_t { position.v * affine.rotation } + affine.position.v;
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

inline vec3_t inv_transform_dir(const affine_t& affine, const vec3_t& direction)
{
    const mat3_t invRotation = as::mat::inverse(affine.rotation);
#if defined AS_COL_MAJOR
    return invRotation * direction;
#elif defined AS_ROW_MAJOR
    return direction * invRotation;
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

inline point3_t inv_transform_pos(const affine_t& affine, const point3_t& position)
{
    const mat3_t invRotation = as::mat::inverse(affine.rotation);
#if defined AS_COL_MAJOR
    return point3_t { invRotation * (position - affine.position) };
#elif defined AS_ROW_MAJOR
    return point3_t { (position - affine.position) * invRotation };
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

} // namespace affine

} // namespace as
