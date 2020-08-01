namespace as
{

namespace vec
{

template<typename T, index_t n>
AS_API constexpr index_t size(const vec_t<T, n>& /*unused*/)
{
    return n;
}

template<typename T, index_t n>
AS_API vec_t<T, n> from_arr(const T (&data)[n])
{
    return from_ptr<T, n>(&data[0]);
}

template<typename T, index_t n>
AS_API vec_t<T, n> from_ptr(const T* data)
{
    vec_t<T, n> result;
    for (index_t i = 0; i < n; ++i) {
        result[i] = data[i];
    }

    return result;
}

template<typename T, index_t n>
AS_API void to_arr(const vec_t<T, n>& vec, T (&data)[n])
{
    for (index_t i = 0; i < n; ++i) {
        data[i] = vec[i];
    }
}

template<typename T, index_t n>
AS_API constexpr T dot(const vec_t<T, n>& lhs, const vec_t<T, n>& rhs)
{
    T result{0};
    for (index_t i = 0; i < n; ++i) {
        result += lhs[i] * rhs[i];
    }

    return result;
}

template<>
AS_API constexpr real_t dot(const vec3_t& lhs, const vec3_t& rhs)
{
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

template<typename T, index_t n>
AS_API constexpr T length_sq(const vec_t<T, n>& vec)
{
    return dot(vec, vec);
}

template<typename T, index_t n>
AS_API T length(const vec_t<T, n>& vec)
{
    return std::sqrt(length_sq(vec));
}

template<typename T, index_t n>
AS_API vec_t<T, n> normalize(const vec_t<T, n>& vec)
{
    return vec / length(vec);
}

template<typename T, index_t n>
AS_API std::tuple<vec_t<T, n>, T> normalize_with_length(const vec_t<T, n>& vec)
{
    const T len = length(vec);
    return std::make_tuple(vec / len, len);
}

template<typename T, index_t n>
AS_API bool equal(
    const vec_t<T, n>& lhs, const vec_t<T, n>& rhs,
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
AS_API vec_t<T, n> min(const vec_t<T, n>& lhs, const vec_t<T, n>& rhs)
{
    vec_t<T, n> result;
    for (index_t i = 0; i < n; ++i) {
        result[i] = as::min(lhs[i], rhs[i]);
    }

    return result;
}

template<typename T, index_t n>
AS_API constexpr T min_elem(const vec_t<T, n>& vec)
{
    T val = vec[0];
    for (index_t i = 1; i < n; ++i) {
        val = as::min(val, vec[i]);
    }

    return val;
}

template<typename T, index_t n>
AS_API vec_t<T, n> max(const vec_t<T, n>& lhs, const vec_t<T, n>& rhs)
{
    vec_t<T, n> result;
    for (index_t i = 0; i < n; ++i) {
        result[i] = as::max(lhs[i], rhs[i]);
    }

    return result;
}

template<typename T, index_t n>
AS_API constexpr T max_elem(const vec_t<T, n>& vec)
{
    T val = vec[0];
    for (index_t i = 1; i < n; ++i) {
        val = as::max(val, vec[i]);
    }

    return val;
}

template<typename T, index_t n>
AS_API vec_t<T, n> abs(const vec_t<T, n>& vec)
{
    vec_t<T, n> result;
    for (index_t i = 0; i < n; ++i) {
        result[i] = std::abs(vec[i]);
    }

    return result;
}

template<typename T, index_t n>
AS_API vec_t<T, n> clamp(
    const vec_t<T, n>& vec, const vec_t<T, n>& min, const vec_t<T, n>& max)
{
    vec_t<T, n> result;
    for (index_t i = 0; i < n; ++i) {
        result[i] = as::clamp(vec[i], min[i], max[i]);
    }

    return result;
}

template<typename T, index_t n>
AS_API vec_t<T, n> saturate(const vec_t<T, n>& vec)
{
    vec_t<T, n> result;
    for (index_t i = 0; i < n; ++i) {
        result[i] = as::clamp(vec[i], T(0.0), T(1.0));
    }

    return result;
}

template<typename T, index_t n>
AS_API vec_t<T, n> lerp(T t, const vec_t<T, n>& v0, const vec_t<T, n>& v1)
{
    vec_t<T, n> result;
    for (index_t i = 0; i < n; ++i) {
        result[i] = as::lerp(t, v0[i], v1[i]);
    }

    return result;
}

template<typename T, index_t n>
AS_API constexpr vec_t<T, n> select(
    const vec_t<T, n>& v0, const vec_t<T, n>& v1, bool select0)
{
    return select0 ? v0 : v1;
}

template<typename T, index_t n>
AS_API vec_t<T, n> floor(const vec_t<T, n>& vec)
{
    vec_t<T, n> result;
    for (index_t i = 0; i < n; ++i) {
        result[i] = std::floor(vec[i]);
    }

    return result;
}

template<typename T, index_t n>
AS_API vec_t<T, n> ceil(const vec_t<T, n>& vec)
{
    vec_t<T, n> result;
    for (index_t i = 0; i < n; ++i) {
        result[i] = std::ceil(vec[i]);
    }

    return result;
}

template<typename T, index_t n>
AS_API vec_t<T, n> round(const vec_t<T, n>& vec)
{
    vec_t<T, n> result;
    for (index_t i = 0; i < n; ++i) {
        result[i] = std::round(vec[i]);
    }

    return result;
}

} // namespace vec

namespace vec2
{

template<typename T>
AS_API inline vec_t<T, 2> from_ptr(const T* data)
{
    return vec::from_ptr<T, 2>(data);
}

template<typename T>
AS_API inline vec_t<T, 2> from_arr(const T (&data)[2])
{
    return vec::from_arr(data);
}

template<typename T>
AS_API constexpr vec_t<T, 2> from_vec3(const vec_t<T, 3>& vec)
{
    return {vec.x, vec.y};
}

template<typename T>
AS_API constexpr vec_t<T, 2> from_vec4(const vec_t<T, 4>& vec)
{
    return {vec.x, vec.y};
}

template<typename T>
AS_API constexpr T wedge(const vec_t<T, 2>& lhs, const vec_t<T, 2>& rhs)
{
    return lhs.x * rhs.y - lhs.y * rhs.x;
}

} // namespace vec2

namespace vec3
{

template<typename T>
AS_API vec_t<T, 3> from_ptr(const T* data)
{
    return vec::from_ptr<T, 3>(data);
}

template<typename T>
AS_API vec_t<T, 3> from_arr(const T (&data)[3])
{
    return vec::from_arr(data);
}

template<typename T>
AS_API constexpr vec_t<T, 3> from_vec2(const vec_t<T, 2>& vec, const T z)
{
    return {vec.x, vec.y, z};
}

template<typename T>
AS_API constexpr vec_t<T, 3> from_vec4(const vec_t<T, 4>& vec)
{
    return {vec.x, vec.y, vec.z};
}

template<typename T>
AS_API constexpr vec_t<T, 3> cross(
    const vec_t<T, 3>& lhs, const vec_t<T, 3>& rhs)
{
    // clang-format off
    return {lhs.y * rhs.z - lhs.z * rhs.y,
            lhs.z * rhs.x - lhs.x * rhs.z,
            lhs.x * rhs.y - lhs.y * rhs.x};
    // clang-format on
}

template<typename T>
AS_API void right_and_up_lh(
    const vec_t<T, 3>& dir, vec_t<T, 3>& across, vec_t<T, 3>& up,
    const vec_t<T, 3>& world_up)
{
    across = cross(dir, world_up);
    up = vec::normalize(cross(across, dir));
    across = vec::normalize(cross(up, dir));
}

template<typename T>
AS_API void right_and_up_rh(
    const vec_t<T, 3>& dir, vec_t<T, 3>& across, vec_t<T, 3>& up,
    const vec_t<T, 3>& world_up)
{
    across = cross(dir, world_up);
    up = vec::normalize(cross(across, dir));
    across = vec::normalize(cross(dir, up));
}

} // namespace vec3

namespace vec4
{

template<typename T>
AS_API vec_t<T, 4> from_ptr(const T* data)
{
    return vec::from_ptr<T, 4>(data);
}

template<typename T>
AS_API vec_t<T, 4> from_arr(const T (&data)[4])
{
    return vec::from_arr(data);
}

template<typename T>
AS_API constexpr vec_t<T, 4> from_vec2(
    const vec_t<T, 2>& vec, const T z, const T w)
{
    return {vec.x, vec.y, z, w};
}

template<typename T>
AS_API constexpr vec_t<T, 4> from_vec3(const vec_t<T, 3>& vec, T w)
{
    return {vec.x, vec.y, vec.z, w};
}

AS_API inline vec4_t from_point3(const point3_t& point)
{
    return {point[0], point[1], point[2], 1.0_r};
}

} // namespace vec4

namespace mat
{

AS_API constexpr index_t rc(index_t r, index_t c, index_t d)
{
#ifdef AS_COL_MAJOR
    return c * d + r;
#elif defined AS_ROW_MAJOR
    return r * d + c;
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

template<typename T, index_t d>
AS_API vec_t<T, d> row(const mat_t<T, d>& mat, index_t r)
{
    vec_t<T, d> vec;
    for (index_t c = 0; c < d; ++c) {
        vec[c] = mat[mat::rc(r, c, d)];
    }

    return vec;
}

template<typename T, index_t d>
AS_API vec_t<T, d> col(const mat_t<T, d>& mat, index_t c)
{
    vec_t<T, d> vec;
    for (index_t r = 0; r < d; ++r) {
        vec[r] = mat[mat::rc(r, c, d)];
    }

    return vec;
}

template<typename T, index_t d>
AS_API constexpr void row(mat_t<T, d>& mat, index_t r, const vec_t<T, d>& row)
{
    for (index_t c = 0; c < d; ++c) {
        mat[mat::rc(r, c, d)] = row[c];
    }
}

template<typename T, index_t d>
AS_API constexpr void col(mat_t<T, d>& mat, index_t c, const vec_t<T, d>& col)
{
    for (index_t r = 0; r < d; ++r) {
        mat[mat::rc(r, c, d)] = col[r];
    }
}

template<typename T, index_t d>
AS_API mat_t<T, d> from_arr(const T (&data)[d * d])
{
    return from_ptr<T, d>(data);
}

template<typename T, index_t d>
AS_API mat_t<T, d> from_ptr(const T* data)
{
    mat_t<T, d> result;
    for (index_t i = 0; i < d * d; ++i) {
        result[i] = data[i];
    }

    return result;
}

template<typename T, index_t d>
AS_API void to_arr(const mat_t<T, d>& mat, T (&data)[d * d])
{
    for (index_t i = 0; i < d * d; ++i) {
        data[i] = mat[i];
    }
}

template<typename T, index_t d>
AS_API bool equal(
    const mat_t<T, d>& lhs, const mat_t<T, d>& rhs,
    const real_t epsilon /* = std::numeric_limits<real_t>::epsilon() */)
{
    for (index_t i = 0; i < mat_t<T, d>::size(); ++i) {
        if (!as::equal(lhs[i], rhs[i], epsilon, epsilon)) {
            return false;
        }
    }

    return true;
}

template<typename T, index_t d>
AS_API mat_t<T, d> transpose(const mat_t<T, d>& mat)
{
    mat_t<T, d> result;
    for (index_t ci = 0; ci < d; ++ci) {
        for (index_t ri = 0; ri < d; ++ri) {
            result[ci * d + ri] = mat[ri * d + ci];
        }
    }

    return result;
}

namespace internal
{

template<index_t>
struct int2type
{
};

// where col and row are the rows to ignore
template<typename T, index_t d>
AS_API mat_t<T, d - 1> sub_matrix(
    const mat_t<T, d>& mat, const index_t r, const index_t c)
{
    mat_t<T, d - 1> result = identity<T, d - 1>();

    index_t i = 0;
    for (index_t ci = 0; ci < d; ++ci) {
        for (index_t ri = 0; ri < d; ++ri) {
            if (ri == r || ci == c) {
                continue;
            }

            result[i++] = mat[ci * d + ri];
        }
    }

    return result;
}

#pragma push_macro("minor")
#undef minor

template<typename T>
AS_API T minor(const mat_t<T, 2>& mat)
{
    return mat[0] * mat[3] - mat[2] * mat[1];
}

template<typename T, index_t d, index_t I>
AS_API T determinant_impl(const mat_t<T, d>& mat, int2type<I> /*unused*/)
{
    T sign{1.0};
    T result{0.0};

    for (index_t i = 0; i < d; ++i) {
        const T minor_det =
            determinant_impl(sub_matrix(mat, i, 0), int2type<I - 1>{});
        result += (mat[i] * minor_det) * sign;
        sign *= T{-1.0};
    }

    return result;
}

template<typename T>
AS_API T determinant_impl(const mat_t<T, 2>& mat, int2type<2> /*unused*/)
{
    return minor(mat);
}

#pragma pop_macro("minor")

template<typename T, index_t d, index_t I>
AS_API mat_t<T, d> minor_impl(const mat_t<T, d>& mat, int2type<I> /*unused*/)
{
    mat_t<T, d> result;
    T outer_sign = T{1.0};

    for (index_t c = 0; c < d; ++c) {
        T inner_sign{outer_sign};
        for (index_t r = 0; r < d; ++r) {
            const T minor_det = determinant_impl<T>(
                internal::sub_matrix(mat, r, c), int2type<d - 1>{});
            result[c * d + r] = minor_det * inner_sign;
            inner_sign *= T{-1.0};
        }

        outer_sign *= T{-1.0};
    }

    return result;
}

} // namespace internal

template<typename T, index_t d>
AS_API T determinant(const mat_t<T, d>& mat)
{
    return internal::determinant_impl(mat, internal::int2type<d>{});
}

template<typename T, index_t d>
AS_API mat_t<T, d> inverse(const mat_t<T, d>& mat)
{
    mat_t<T, d> result;

    result = internal::minor_impl(mat, internal::int2type<d>{});
    result = transpose(result);
    result *= T(1.0) / determinant(mat);

    return result;
}

template<typename T>
AS_API mat_t<T, 2> inverse(const mat_t<T, 2>& mat)
{
    // clang-format off
    return mat_t<T, 2>{mat[3], -mat[1],
                       -mat[2], mat[0]}
         * (T(1.0) / determinant(mat));
    // clang-format on
}

template<typename T, index_t d>
AS_API mat_t<T, d> gj_inverse(const mat_t<T, d>& mat)
{
    mat_t<T, d> curr_mat = mat;
    mat_t<T, d> result = identity<T, d>();

    index_t current_line = 0;
    for (index_t i = 0; i < d; ++i) {
        T diagonal = curr_mat[(d * i) + i];
        T diagonal_recip = T{1} / diagonal;

        for (index_t j = d * i; j < d + (d * i); ++j) {
            curr_mat[j] *= diagonal_recip;
            result[j] *= diagonal_recip;
        }

        for (index_t r = 0; r < d; ++r) {
            if (r == current_line) {
                continue;
            }

            T next = curr_mat[current_line + r * d];

            for (index_t c = 0; c < d; ++c) {
                index_t index_t = d * r + c;
                curr_mat[index_t] -= (next * curr_mat[d * current_line + c]);
                result[index_t] -= (next * result[d * current_line + c]);
            }
        }

        ++current_line;
    }

    return result;
}

template<typename T, index_t d>
AS_API mat_t<T, d> mul(const mat_t<T, d>& lhs, const mat_t<T, d>& rhs)
{
#ifdef AS_COL_MAJOR
    return rhs * lhs;
#elif defined AS_ROW_MAJOR
    return lhs * rhs;
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

} // namespace mat

namespace mat3
{

AS_API constexpr index_t rc(const index_t r, const index_t c)
{
    return mat::rc(r, c, 3);
}

template<typename T>
AS_API constexpr vec_t<T, 3> row0(const mat_t<T, 3>& mat)
{
    return mat::row(mat, 0);
}

template<typename T>
AS_API constexpr vec_t<T, 3> row1(const mat_t<T, 3>& mat)
{
    return mat::row(mat, 1);
}

template<typename T>
AS_API constexpr vec_t<T, 3> row2(const mat_t<T, 3>& mat)
{
    return mat::row(mat, 2);
}

template<typename T>
AS_API constexpr vec_t<T, 3> col0(const mat_t<T, 3>& mat)
{
    return mat::col(mat, 0);
}

template<typename T>
AS_API constexpr vec_t<T, 3> col1(const mat_t<T, 3>& mat)
{
    return mat::col(mat, 1);
}

template<typename T>
AS_API constexpr vec_t<T, 3> col2(const mat_t<T, 3>& mat)
{
    return mat::col(mat, 2);
}

template<typename T>
AS_API constexpr void row0(mat_t<T, 3>& mat, const vec_t<T, 3>& row)
{
    mat::row(mat, 0, row);
}

template<typename T>
AS_API constexpr void row1(mat_t<T, 3>& mat, const vec_t<T, 3>& row)
{
    mat::row(mat, 1, row);
}

template<typename T>
AS_API constexpr void row2(mat_t<T, 3>& mat, const vec_t<T, 3>& row)
{
    mat::row(mat, 2, row);
}

template<typename T>
AS_API constexpr void col0(mat_t<T, 3>& mat, const vec_t<T, 3>& col)
{
    mat::col(mat, 0, col);
}

template<typename T>
AS_API constexpr void col1(mat_t<T, 3>& mat, const vec_t<T, 3>& col)
{
    mat::col(mat, 1, col);
}

template<typename T>
AS_API constexpr void col2(mat_t<T, 3>& mat, const vec_t<T, 3>& col)
{
    mat::col(mat, 2, col);
}

template<typename T>
AS_API constexpr vec_t<T, 3> basis_x(const mat_t<T, 3>& mat)
{
#ifdef AS_COL_MAJOR
    return col0(mat);
#elif defined AS_ROW_MAJOR
    return row0(mat);
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

template<typename T>
AS_API constexpr vec_t<T, 3> basis_y(const mat_t<T, 3>& mat)
{
#ifdef AS_COL_MAJOR
    return col1(mat);
#elif defined AS_ROW_MAJOR
    return row1(mat);
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

template<typename T>
AS_API constexpr vec_t<T, 3> basis_z(const mat_t<T, 3>& mat)
{
#ifdef AS_COL_MAJOR
    return col2(mat);
#elif defined AS_ROW_MAJOR
    return row2(mat);
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

template<typename T>
AS_API constexpr void basis_x(mat_t<T, 3>& mat, const vec_t<T, 3>& basis)
{
#ifdef AS_COL_MAJOR
    return col0(mat, basis);
#elif defined AS_ROW_MAJOR
    return row0(mat, basis);
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

template<typename T>
AS_API constexpr void basis_y(mat_t<T, 3>& mat, const vec_t<T, 3>& basis)
{
#ifdef AS_COL_MAJOR
    return col1(mat, basis);
#elif defined AS_ROW_MAJOR
    return row1(mat, basis);
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

template<typename T>
AS_API constexpr void basis_z(mat_t<T, 3>& mat, const vec_t<T, 3>& basis)
{
#ifdef AS_COL_MAJOR
    return col2(mat, basis);
#elif defined AS_ROW_MAJOR
    return row2(mat, basis);
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

template<typename T>
AS_API mat_t<T, 3> from_ptr(const T* data)
{
    return mat::from_ptr<T, 3>(data);
}

template<typename T>
AS_API mat_t<T, 3> from_arr(const T (&data)[9])
{
    return mat::from_arr<T, 3>(data);
}

template<typename T>
AS_API constexpr mat_t<T, 3> from_mat4(const mat_t<T, 4>& transform)
{
    // clang-format off
    return {transform[0], transform[1], transform[2],
            transform[4], transform[5], transform[6],
            transform[8], transform[9], transform[10]};
    // clang-format on
}

AS_API inline mat3_t axis_angle(const vec3_t& axis, const real_t radians)
{
    const real_t cosr_radians = std::cos(radians);
    const real_t sinr_radians = std::sin(radians);
    const real_t one = 1.0_r;

    return {
        cosr_radians + ((axis.x * axis.x) * (one - cosr_radians)),
        (axis.y * axis.x * (one - cosr_radians)) + (axis.z * sinr_radians),
        (axis.z * axis.x * (one - cosr_radians)) - (axis.y * sinr_radians),
        (axis.x * axis.y * (one - cosr_radians)) - (axis.z * sinr_radians),
        cosr_radians + ((axis.y * axis.y) * (one - cosr_radians)),
        (axis.z * axis.y * (one - cosr_radians)) + (axis.x * sinr_radians),
        (axis.x * axis.z * (one - cosr_radians)) + (axis.y * sinr_radians),
        (axis.y * axis.z * (one - cosr_radians)) - (axis.x * sinr_radians),
        cosr_radians + ((axis.z * axis.z) * (one - cosr_radians))};
}

AS_API inline mat3_t rotation_xyz(
    const real_t x, const real_t y, const real_t z)
{
    const real_t cosr_x = std::cos(x);
    const real_t cosr_y = std::cos(y);
    const real_t cosr_z = std::cos(z);
    const real_t sinr_x = std::sin(x);
    const real_t sinr_y = std::sin(y);
    const real_t sinr_z = std::sin(z);

    return {
        cosr_y * cosr_z,
        cosr_y * sinr_z,
        -sinr_y,
        (sinr_x * sinr_y * cosr_z) - (cosr_x * sinr_z),
        (sinr_x * sinr_y * sinr_z) + (cosr_x * cosr_z),
        sinr_x * cosr_y,
        (cosr_x * sinr_y * cosr_z) + (sinr_x * sinr_z),
        (cosr_x * sinr_y * sinr_z) - (sinr_x * cosr_z),
        cosr_x * cosr_y};
}

AS_API inline mat3_t rotation_zxy(
    const real_t x, const real_t y, const real_t z)
{
    const real_t cosr_x = std::cos(x);
    const real_t cosr_y = std::cos(y);
    const real_t cosr_z = std::cos(z);
    const real_t sinr_x = std::sin(x);
    const real_t sinr_y = std::sin(y);
    const real_t sinr_z = std::sin(z);

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

AS_API inline mat3_t rotation_x(const real_t radians)
{
    // clang-format off
    return {1.0_r, 0.0_r,              0.0_r,
            0.0_r, std::cos(radians),  std::sin(radians),
            0.0_r, -std::sin(radians), std::cos(radians)};
    // clang-format on
}

AS_API inline mat3_t rotation_y(const real_t radians)
{
    // clang-format off
    return {std::cos(radians), 0.0_r, -std::sin(radians),
            0.0_r,             1.0_r, 0.0_r,
            std::sin(radians), 0.0_r, std::cos(radians)};
    // clang-format on
}

AS_API inline mat3_t rotation_z(const real_t radians)
{
    // clang-format off
    return {std::cos(radians),  std::sin(radians), 0.0_r,
            -std::sin(radians), std::cos(radians), 0.0_r,
            0.0_r,              0.0_r,             1.0_r};
    // clang-format on
}

AS_API constexpr mat3_t scale(const real_t scale)
{
    return mat3::scale(vec3_t{scale});
}

AS_API constexpr mat3_t scale(const vec3_t& scale)
{
    // clang-format off
    return {scale.x, 0.0_r,   0.0_r,
            0.0_r,   scale.y, 0.0_r,
            0.0_r,   0.0_r,   scale.z};
    // clang-format on
}

// ref: Essential Mathematics for Games & Interactive Applications: A
// Programmers Guide section 5.5.7
AS_API constexpr mat3_t from_quat(const quat_t& quat)
{
    const real_t s{
        2.0_r
        / (quat.x * quat.x + quat.y * quat.y + quat.z * quat.z
           + quat.w * quat.w)};

    const real_t xs{s * quat.x};
    const real_t ys{s * quat.y};
    const real_t zs{s * quat.z};
    const real_t wx{quat.w * xs};
    const real_t wy{quat.w * ys};
    const real_t wz{quat.w * zs};
    const real_t xx{quat.x * xs};
    const real_t xy{quat.x * ys};
    const real_t xz{quat.x * zs};
    const real_t yy{quat.y * ys};
    const real_t yz{quat.y * zs};
    const real_t zz{quat.z * zs};

    return {1.0_r - (yy + zz), xy + wz,           xz - wy,
            xy - wz,           1.0_r - (xx + zz), yz + wx,
            xz + wy,           yz - wx,           1.0_r - (xx + yy)};
}

} // namespace mat3

namespace mat4
{

AS_API constexpr index_t rc(const index_t r, const index_t c)
{
    return mat::rc(r, c, 4);
}

template<typename T>
AS_API constexpr vec_t<T, 4> row0(const mat_t<T, 4>& mat)
{
    return mat::row(mat, 0);
}

template<typename T>
AS_API constexpr vec_t<T, 4> row1(const mat_t<T, 4>& mat)
{
    return mat::row(mat, 1);
}

template<typename T>
AS_API constexpr vec_t<T, 4> row2(const mat_t<T, 4>& mat)
{
    return mat::row(mat, 2);
}

template<typename T>
AS_API constexpr vec_t<T, 4> row3(const mat_t<T, 4>& mat)
{
    return mat::row(mat, 3);
}

template<typename T>
AS_API constexpr vec_t<T, 4> col0(const mat_t<T, 4>& mat)
{
    return mat::col(mat, 0);
}

template<typename T>
AS_API constexpr vec_t<T, 4> col1(const mat_t<T, 4>& mat)
{
    return mat::col(mat, 1);
}

template<typename T>
AS_API constexpr vec_t<T, 4> col2(const mat_t<T, 4>& mat)
{
    return mat::col(mat, 2);
}

template<typename T>
AS_API constexpr vec_t<T, 4> col3(const mat_t<T, 4>& mat)
{
    return mat::col(mat, 3);
}

template<typename T>
AS_API constexpr void row0(mat_t<T, 4>& mat, const vec_t<T, 4>& row)
{
    mat::row(mat, 0, row);
}

template<typename T>
AS_API constexpr void row1(mat_t<T, 4>& mat, const vec_t<T, 4>& row)
{
    mat::row(mat, 1, row);
}

template<typename T>
AS_API constexpr void row2(mat_t<T, 4>& mat, const vec_t<T, 4>& row)
{
    mat::row(mat, 2, row);
}

template<typename T>
AS_API constexpr void row3(mat_t<T, 4>& mat, const vec_t<T, 4>& row)
{
    mat::row(mat, 3, row);
}

template<typename T>
AS_API constexpr void col0(mat_t<T, 4>& mat, const vec_t<T, 4>& col)
{
    mat::col(mat, 0, col);
}

template<typename T>
AS_API constexpr void col1(mat_t<T, 4>& mat, const vec_t<T, 4>& col)
{
    mat::col(mat, 1, col);
}

template<typename T>
AS_API constexpr void col2(mat_t<T, 4>& mat, const vec_t<T, 4>& col)
{
    mat::col(mat, 2, col);
}

template<typename T>
AS_API constexpr void col3(mat_t<T, 4>& mat, const vec_t<T, 4>& col)
{
    mat::col(mat, 3, col);
}

template<typename T>
AS_API constexpr vec_t<T, 4> basis_x(const mat_t<T, 4>& mat)
{
#ifdef AS_COL_MAJOR
    return col0(mat);
#elif defined AS_ROW_MAJOR
    return row0(mat);
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

template<typename T>
AS_API constexpr vec_t<T, 4> basis_y(const mat_t<T, 4>& mat)
{
#ifdef AS_COL_MAJOR
    return col1(mat);
#elif defined AS_ROW_MAJOR
    return row1(mat);
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

template<typename T>
AS_API constexpr vec_t<T, 4> basis_z(const mat_t<T, 4>& mat)
{
#ifdef AS_COL_MAJOR
    return col2(mat);
#elif defined AS_ROW_MAJOR
    return row2(mat);
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

template<typename T>
AS_API constexpr vec_t<T, 4> translation(const mat_t<T, 4>& mat)
{
#ifdef AS_COL_MAJOR
    return col3(mat);
#elif defined AS_ROW_MAJOR
    return row3(mat);
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

template<typename T>
AS_API constexpr void basis_x(mat_t<T, 4>& mat, const vec_t<T, 4>& basis)
{
#ifdef AS_COL_MAJOR
    return col0(mat, basis);
#elif defined AS_ROW_MAJOR
    return row0(mat, basis);
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

template<typename T>
AS_API constexpr void basis_y(mat_t<T, 4>& mat, const vec_t<T, 4>& basis)
{
#ifdef AS_COL_MAJOR
    return col1(mat, basis);
#elif defined AS_ROW_MAJOR
    return row1(mat, basis);
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

template<typename T>
AS_API constexpr void basis_z(mat_t<T, 4>& mat, const vec_t<T, 4>& basis)
{
#ifdef AS_COL_MAJOR
    return col2(mat, basis);
#elif defined AS_ROW_MAJOR
    return row2(mat, basis);
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

template<typename T>
AS_API constexpr void translation(
    mat_t<T, 4>& mat, const vec_t<T, 4>& translation)
{
#ifdef AS_COL_MAJOR
    return col3(mat, translation);
#elif defined AS_ROW_MAJOR
    return row3(mat, translation);
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

template<typename T>
AS_API mat_t<T, 4> from_ptr(const T* data)
{
    return mat::from_ptr<T, 4>(data);
}

template<typename T>
AS_API mat_t<T, 4> from_arr(const T (&data)[16])
{
    return mat::from_arr<T, 4>(data);
}

template<typename T>
AS_API constexpr mat_t<T, 4> from_vec3(const vec_t<T, 3>& translation)
{
    return {mat_t<T, 3>::identity(), translation};
}

template<typename T>
AS_API constexpr mat_t<T, 4> from_mat3(const mat_t<T, 3>& rotation)
{
    return {rotation, vec_t<T, 3>::zero()};
}

template<typename T>
AS_API constexpr mat_t<T, 4> from_mat3_vec3(
    const mat_t<T, 3>& rotation, const vec_t<T, 3>& translation)
{
    return {rotation, translation};
}

AS_API constexpr mat4_t from_affine(const affine_t& affine)
{
    return from_mat3_vec3(affine.rotation, affine.position.as_vec3());
}

template<typename T>
AS_API constexpr mat_t<T, 4> shear_x(const T y, const T z)
{
    // clang-format off
    return {T(1.0), y,      z,      T(0.0),
            T(0.0), T(1.0), T(0.0), T(0.0),
            T(0.0), T(0.0), T(1.0), T(0.0),
            T(0.0), T(0.0), T(0.0), T(1.0)};
    // clang-format on
}

template<typename T>
AS_API constexpr mat_t<T, 4> shear_y(const T x, const T z)
{
    // clang-format off
    return {T(1.0), T(0.0), T(0.0), T(0.0),
            x,      T(1.0), z,      T(0.0),
            T(0.0), T(0.0), T(1.0), T(0.0),
            T(0.0), T(0.0), T(0.0), T(1.0)};
    // clang-format on
}

template<typename T>
AS_API constexpr mat_t<T, 4> shear_z(const T x, const T y)
{
    // clang-format off
    return {T(1.0), T(0.0), T(0.0), T(0.0),
            T(0.0), T(1.0), T(0.0), T(0.0),
            x,      y,      T(1.0), T(0.0),
            T(0.0), T(0.0), T(0.0), T(1.0)};
    // clang-format on
}

} // namespace mat4

namespace point
{

AS_API inline bool equal(
    const point2_t& lhs, const point2_t& rhs,
    const real_t epsilon /*= std::numeric_limits<real_t>::epsilon()*/)
{
    return vec::equal(lhs.as_vec2(), rhs.as_vec2(), epsilon);
}

AS_API inline bool equal(
    const point3_t& lhs, const point3_t& rhs,
    const real_t epsilon /*= std::numeric_limits<real_t>::epsilon()*/)
{
    return vec::equal(lhs.as_vec3(), rhs.as_vec3(), epsilon);
}

} // namespace point

namespace quat
{

AS_API constexpr real_t dot(const quat_t& lhs, const quat_t& rhs)
{
    return lhs.w * rhs.w + lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

AS_API constexpr real_t length_sq(const quat_t& quat)
{
    return dot(quat, quat);
}

AS_API inline real_t length(const quat_t& quat)
{
    return std::sqrt(length_sq(quat));
}

AS_API inline quat_t normalize(const quat_t& quat)
{
    return quat / length(quat);
}

AS_API constexpr quat_t conjugate(const quat_t& quat)
{
    return {quat.w, -quat.x, -quat.y, -quat.z};
}

AS_API inline quat_t inverse(const quat_t& quat)
{
    return conjugate(quat) / length_sq(quat);
}

AS_API inline vec3_t rotate(const quat_t& quat, const vec3_t& v)
{
    const quat_t quat_result =
        quat * quat_t{0.0_r, v.x, v.y, v.z} * conjugate(quat);
    return {quat_result.x, quat_result.y, quat_result.z};
}

AS_API inline quat_t axis_angle(const vec3_t& axis, const real_t radians)
{
    return {std::cos(0.5_r * radians), axis * std::sin(0.5_r * radians)};
}

AS_API inline quat_t rotation_zxy(
    const real_t x, const real_t y, const real_t z)
{
    const auto half = 0.5_r;
    return quat_t{std::cos(half * y), 0.0_r, std::sin(half * y), 0.0_r}
         * quat_t{std::cos(half * x), std::sin(half * x), 0.0_r, 0.0_r}
         * quat_t{std::cos(half * z), 0.0_r, 0.0_r, std::sin(half * z)};
}

AS_API inline quat_t slerp(const quat_t& lhs, const quat_t& rhs, const real_t t)
{
    const real_t theta = std::acos(dot(lhs, rhs));
    return (lhs * std::sin((1.0_r - t) * theta) + rhs * std::sin(t * theta))
         / std::sin(theta);
}

// ref: euclidean space
// http://www.euclideanspace.com/maths/geometry/rotations/conversions/matrixToQuaternion/index.htm
AS_API inline quat_t from_mat3(const mat3_t& mat)
{
    quat_t q;

    const auto index = [](const index_t r, const index_t c) {
        return c * mat3_t::dim() + r;
    };

    const real_t trace = mat[index(0, 0)] + mat[index(1, 1)] + mat[index(2, 2)];

    if (trace > 0.0_r) {
        real_t s = 0.5_r / std::sqrt(trace + 1.0_r);
        q.w = 0.25_r / s;
        q.x = (mat[index(2, 1)] - mat[index(1, 2)]) * s;
        q.y = (mat[index(0, 2)] - mat[index(2, 0)]) * s;
        q.z = (mat[index(1, 0)] - mat[index(0, 1)]) * s;
    } else {
        if (mat[index(0, 0)] > mat[index(1, 1)]
            && mat[index(0, 0)] > mat[index(2, 2)]) {
            real_t s = 2.0_r
                     * std::sqrt(
                           1.0_r + mat[index(0, 0)] - mat[index(1, 1)]
                           - mat[index(2, 2)]);
            q.w = (mat[index(2, 1)] - mat[index(1, 2)]) / s;
            q.x = 0.25_r * s;
            q.y = (mat[index(0, 1)] + mat[index(1, 0)]) / s;
            q.z = (mat[index(0, 2)] + mat[index(2, 0)]) / s;
        } else if (mat[index(1, 1)] > mat[index(2, 2)]) {
            real_t s = 2.0_r
                     * std::sqrt(
                           1.0_r + mat[index(1, 1)] - mat[index(0, 0)]
                           - mat[index(2, 2)]);
            q.w = (mat[index(0, 2)] - mat[index(2, 0)]) / s;
            q.x = (mat[index(0, 1)] + mat[index(1, 0)]) / s;
            q.y = 0.25_r * s;
            q.z = (mat[index(1, 2)] + mat[index(2, 1)]) / s;
        } else {
            real_t s = 2.0_r
                     * std::sqrt(
                           1.0_r + mat[index(2, 2)] - mat[index(0, 0)]
                           - mat[index(1, 1)]);
            q.w = (mat[index(1, 0)] - mat[index(0, 1)]) / s;
            q.x = (mat[index(0, 2)] + mat[index(2, 0)]) / s;
            q.y = (mat[index(1, 2)] + mat[index(2, 1)]) / s;
            q.z = 0.25_r * s;
        }
    }

    return q;
}

} // namespace quat

namespace affine
{

AS_API inline void to_arr(const affine_t& affine, real_t (&data)[12])
{
    for (index_t i = 0; i < affine.rotation.size(); ++i) {
        data[i] = affine.rotation[i];
    }

    for (index_t i = 0; i < affine.position.size(); ++i) {
        data[affine.rotation.size() + i] = affine.position[i];
    }
}

AS_API inline affine_t from_arr(const real_t (&data)[12])
{
    return from_ptr(data);
}

AS_API inline affine_t from_ptr(const real_t* data)
{
    affine_t result;

    constexpr auto mat_size = mat3_t::size();
    for (index_t i = 0; i < mat_size; ++i) {
        result.rotation[i] = data[i];
    }

    constexpr auto vec_size = vec3_t::size();
    for (index_t i = 0; i < vec_size; ++i) {
        result.position[i] = data[result.rotation.size() + i];
    }

    return result;
}

AS_API inline affine_t from_mat4(const mat4_t& mat)
{
    return affine_t{
        mat3::from_mat4(mat),
        point3_t{vec3::from_vec4(mat4::translation(mat))}};
}

AS_API inline affine_t from_mat3(const mat3_t& mat)
{
    return affine_t{mat, point3_t::zero()};
}

AS_API inline affine_t from_point3(const point3_t& point)
{
    return affine_t(point);
}

AS_API inline affine_t mul(const affine_t& lhs, const affine_t& rhs)
{
    return affine_t{
        mat::mul(lhs.rotation, rhs.rotation), transform_pos(rhs, lhs.position)};
}

AS_API inline affine_t inverse(const affine_t& affine)
{
    const as::mat3_t inv_rot = as::mat::transpose(affine.rotation);
    const as::point3_t inv_pos =
        as::affine::transform_pos(as::affine_t{inv_rot}, -affine.position);
    return as::affine_t{inv_rot, inv_pos};
}

AS_API inline vec3_t transform_dir(
    const affine_t& affine, const vec3_t& direction)
{
#ifdef AS_COL_MAJOR
    return affine.rotation * direction;
#elif defined AS_ROW_MAJOR
    return direction * affine.rotation;
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

AS_API inline point3_t transform_pos(
    const affine_t& affine, const point3_t& position)
{
#ifdef AS_COL_MAJOR
    return point3_t{affine.rotation * position.as_vec3()}
         + affine.position.as_vec3();
#elif defined AS_ROW_MAJOR
    return point3_t{position.as_vec3() * affine.rotation}
         + affine.position.as_vec3();
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

AS_API inline vec3_t inv_transform_dir(
    const affine_t& affine, const vec3_t& direction)
{
    const mat3_t inv_rotation = as::mat::inverse(affine.rotation);
#ifdef AS_COL_MAJOR
    return inv_rotation * direction;
#elif defined AS_ROW_MAJOR
    return direction * inv_rotation;
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

AS_API inline point3_t inv_transform_pos(
    const affine_t& affine, const point3_t& position)
{
    const mat3_t inv_rotation = as::mat::inverse(affine.rotation);
#ifdef AS_COL_MAJOR
    return point3_t{inv_rotation * (position - affine.position)};
#elif defined AS_ROW_MAJOR
    return point3_t{(position - affine.position) * inv_rotation};
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

} // namespace affine

} // namespace as
