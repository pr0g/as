namespace as
{

namespace vec
{

template<typename T, index_t d>
AS_API constexpr index_t size(const vec_t<T, d>& /*unused*/)
{
  return d;
}

template<typename T, index_t d>
AS_API vec_t<T, d> from_arr(const T (&data)[d])
{
  return from_ptr<T, d>(&data[0]);
}

template<typename T, index_t d>
AS_API vec_t<T, d> from_ptr(const T* data)
{
  vec_t<T, d> result;
  for (index_t i = 0; i < d; ++i) {
    result[i] = data[i];
  }

  return result;
}

template<typename T, index_t d>
AS_API void to_arr(const vec_t<T, d>& vec, T (&data)[d])
{
  for (index_t i = 0; i < d; ++i) {
    data[i] = vec[i];
  }
}

template<typename T, index_t d>
AS_API constexpr T dot(const vec_t<T, d>& lhs, const vec_t<T, d>& rhs)
{
  T result{0};
  for (index_t i = 0; i < d; ++i) {
    result += lhs[i] * rhs[i];
  }

  return result;
}

template<>
AS_API constexpr real_t dot(const vec3_t& lhs, const vec3_t& rhs)
{
  return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

template<typename T, index_t d>
AS_API constexpr T length_sq(const vec_t<T, d>& vec)
{
  return dot(vec, vec);
}

template<typename T, index_t d>
AS_API T length(const vec_t<T, d>& vec)
{
  return std::sqrt(length_sq(vec));
}

template<typename T, index_t d>
AS_API vec_t<T, d> normalize(const vec_t<T, d>& vec)
{
  return vec / length(vec);
}

template<typename T, index_t d>
AS_API std::tuple<vec_t<T, d>, T> normalize_and_length(const vec_t<T, d>& vec)
{
  const T len = length(vec);
  return std::make_tuple(vec / len, len);
}

template<typename T, index_t d>
AS_API bool equal(
  const vec_t<T, d>& lhs, const vec_t<T, d>& rhs,
  real_t epsilon /*= std::numeric_limits<real_t>::epsilon()*/)
{
  for (index_t i = 0; i < d; ++i) {
    if (!as::almost_equal(lhs[i], rhs[i], epsilon, epsilon)) {
      return false;
    }
  }

  return true;
}

template<typename T, index_t d>
AS_API vec_t<T, d> min(const vec_t<T, d>& lhs, const vec_t<T, d>& rhs)
{
  vec_t<T, d> result;
  for (index_t i = 0; i < d; ++i) {
    result[i] = as::min(lhs[i], rhs[i]);
  }

  return result;
}

template<typename T, index_t d>
AS_API constexpr T min_elem(const vec_t<T, d>& vec)
{
  T val = vec[0];
  for (index_t i = 1; i < d; ++i) {
    val = as::min(val, vec[i]);
  }

  return val;
}

template<typename T, index_t d>
AS_API vec_t<T, d> max(const vec_t<T, d>& lhs, const vec_t<T, d>& rhs)
{
  vec_t<T, d> result;
  for (index_t i = 0; i < d; ++i) {
    result[i] = as::max(lhs[i], rhs[i]);
  }

  return result;
}

template<typename T, index_t d>
AS_API constexpr T max_elem(const vec_t<T, d>& vec)
{
  T val = vec[0];
  for (index_t i = 1; i < d; ++i) {
    val = as::max(val, vec[i]);
  }

  return val;
}

template<typename T, index_t d>
AS_API vec_t<T, d> abs(const vec_t<T, d>& vec)
{
  vec_t<T, d> result;
  for (index_t i = 0; i < d; ++i) {
    result[i] = std::abs(vec[i]);
  }

  return result;
}

template<typename T, index_t d>
AS_API vec_t<T, d> clamp(
  const vec_t<T, d>& vec, const vec_t<T, d>& min, const vec_t<T, d>& max)
{
  vec_t<T, d> result;
  for (index_t i = 0; i < d; ++i) {
    result[i] = as::clamp(vec[i], min[i], max[i]);
  }

  return result;
}

template<typename T, index_t d>
AS_API vec_t<T, d> saturate(const vec_t<T, d>& vec)
{
  vec_t<T, d> result;
  for (index_t i = 0; i < d; ++i) {
    result[i] = as::clamp(vec[i], T(0.0), T(1.0));
  }

  return result;
}

template<typename T, index_t d>
AS_API vec_t<T, d> lerp(T t, const vec_t<T, d>& begin, const vec_t<T, d>& end)
{
  vec_t<T, d> result;
  for (index_t i = 0; i < d; ++i) {
    result[i] = as::lerp(t, begin[i], end[i]);
  }

  return result;
}

template<typename T, index_t d>
AS_API constexpr vec_t<T, d> select(
  const vec_t<T, d>& v0, const vec_t<T, d>& v1, bool select0)
{
  return select0 ? v0 : v1;
}

template<typename T, index_t d>
AS_API vec_t<T, d> floor(const vec_t<T, d>& vec)
{
  vec_t<T, d> result;
  for (index_t i = 0; i < d; ++i) {
    result[i] = std::floor(vec[i]);
  }

  return result;
}

template<typename T, index_t d>
AS_API vec_t<T, d> ceil(const vec_t<T, d>& vec)
{
  vec_t<T, d> result;
  for (index_t i = 0; i < d; ++i) {
    result[i] = std::ceil(vec[i]);
  }

  return result;
}

template<typename T, index_t d>
AS_API vec_t<T, d> round(const vec_t<T, d>& vec)
{
  vec_t<T, d> result;
  for (index_t i = 0; i < d; ++i) {
    result[i] = std::round(vec[i]);
  }

  return result;
}

template<typename T, index_t d>
AS_API vec_t<T, d> snap(const vec_t<T, d>& vec, const T step)
{
  vec_t<T, d> result;
  for (index_t i = 0; i < d; ++i) {
    result[i] = as::snap(vec[i], step);
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

// ref: John F. Hughes & Tomas Moller (1999) Building an Orthonormal
// Basis from a Unit Vector, Journal of Graphics Tools, 4:4, 33-35
template<typename T>
AS_API mat_t<T, 3> orthonormal_basis(const vec_t<T, 3>& u)
{
  const auto [x, y, z] = vec::abs(u);

  const vec_t<T, 3> v = vec::normalize([u, x = x, y = y, z = z] {
    if (x <= y && x <= z) {
      return vec_t<T, 3>(0.0_r, -u.z, u.y);
    }
    if (y <= x && y <= z) {
      return vec_t<T, 3>(-u.z, 0.0_r, u.x);
    }
    // z <= x && z <= y
    return vec_t<T, 3>(-u.y, u.x, 0.0_r);
  }());

  const vec_t<T, 3> w = cross(u, v);
  return mat_t<T, 3>(u, v, w);
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

AS_API constexpr index_t mat_rc(index_t r, index_t c, index_t d)
{
#ifdef AS_COL_MAJOR
  return c * d + r;
#elif defined AS_ROW_MAJOR
  return r * d + c;
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

template<typename T, index_t d>
AS_API vec_t<T, d> mat_row(const mat_t<T, d>& mat, index_t r)
{
  vec_t<T, d> vec;
  for (index_t c = 0; c < d; ++c) {
    vec[c] = mat[mat_rc(r, c, d)];
  }

  return vec;
}

template<typename T, index_t d>
AS_API vec_t<T, d> mat_col(const mat_t<T, d>& mat, index_t c)
{
  vec_t<T, d> vec;
  for (index_t r = 0; r < d; ++r) {
    vec[r] = mat[mat_rc(r, c, d)];
  }

  return vec;
}

template<typename T, index_t d>
AS_API constexpr void mat_row(mat_t<T, d>& mat, index_t r, const vec_t<T, d>& row)
{
  for (index_t c = 0; c < d; ++c) {
    mat[mat_rc(r, c, d)] = row[c];
  }
}

template<typename T, index_t d>
AS_API constexpr void mat_col(mat_t<T, d>& mat, index_t c, const vec_t<T, d>& col)
{
  for (index_t r = 0; r < d; ++r) {
    mat[mat_rc(r, c, d)] = col[r];
  }
}

template<typename T, index_t d>
AS_API mat_t<T, d> mat_from_arr(const T (&data)[d * d])
{
  return mat_from_ptr<T, d>(data);
}

template<typename T, index_t d>
AS_API mat_t<T, d> mat_from_ptr(const T* data)
{
  mat_t<T, d> result;
  for (index_t i = 0; i < d * d; ++i) {
    result[i] = data[i];
  }

  return result;
}

template<typename T, index_t d>
AS_API void mat_to_arr(const mat_t<T, d>& mat, T (&data)[d * d])
{
  for (index_t i = 0; i < d * d; ++i) {
    data[i] = mat[i];
  }
}

template<typename T, index_t d>
AS_API bool mat_equal(
  const mat_t<T, d>& lhs, const mat_t<T, d>& rhs,
  const real_t epsilon /* = std::numeric_limits<real_t>::epsilon() */)
{
  for (index_t i = 0; i < mat_t<T, d>::size(); ++i) {
    if (!as::almost_equal(lhs[i], rhs[i], epsilon, epsilon)) {
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
  mat_t<T, d - 1> result = mat_identity<T, d - 1>();

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
      const T minor_det =
        determinant_impl<T>(internal::sub_matrix(mat, r, c), int2type<d - 1>{});
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
                    -mat[2],  mat[0]}
        * (T(1.0) / determinant(mat));
  // clang-format on
}

template<typename T, index_t d>
AS_API mat_t<T, d> mat_mul(const mat_t<T, d>& lhs, const mat_t<T, d>& rhs)
{
#ifdef AS_COL_MAJOR
  return rhs * lhs;
#elif defined AS_ROW_MAJOR
  return lhs * rhs;
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

AS_API constexpr index_t mat3_rc(const index_t r, const index_t c)
{
  return mat_rc(r, c, 3);
}

template<typename T>
AS_API constexpr vec_t<T, 3> mat3_row0(const mat_t<T, 3>& mat)
{
  return mat_row(mat, 0);
}

template<typename T>
AS_API constexpr vec_t<T, 3> mat3_row1(const mat_t<T, 3>& mat)
{
  return mat_row(mat, 1);
}

template<typename T>
AS_API constexpr vec_t<T, 3> mat3_row2(const mat_t<T, 3>& mat)
{
  return mat_row(mat, 2);
}

template<typename T>
AS_API constexpr vec_t<T, 3> mat3_col0(const mat_t<T, 3>& mat)
{
  return mat_col(mat, 0);
}

template<typename T>
AS_API constexpr vec_t<T, 3> mat3_col1(const mat_t<T, 3>& mat)
{
  return mat_col(mat, 1);
}

template<typename T>
AS_API constexpr vec_t<T, 3> mat3_col2(const mat_t<T, 3>& mat)
{
  return mat_col(mat, 2);
}

template<typename T>
AS_API constexpr void mat3_row0(mat_t<T, 3>& mat, const vec_t<T, 3>& row)
{
  mat_row(mat, 0, row);
}

template<typename T>
AS_API constexpr void mat3_row1(mat_t<T, 3>& mat, const vec_t<T, 3>& row)
{
  mat_row(mat, 1, row);
}

template<typename T>
AS_API constexpr void mat3_row2(mat_t<T, 3>& mat, const vec_t<T, 3>& row)
{
  mat_row(mat, 2, row);
}

template<typename T>
AS_API constexpr void mat3_col0(mat_t<T, 3>& mat, const vec_t<T, 3>& col)
{
  mat_col(mat, 0, col);
}

template<typename T>
AS_API constexpr void mat3_col1(mat_t<T, 3>& mat, const vec_t<T, 3>& col)
{
  mat_col(mat, 1, col);
}

template<typename T>
AS_API constexpr void mat3_col2(mat_t<T, 3>& mat, const vec_t<T, 3>& col)
{
  mat_col(mat, 2, col);
}

template<typename T>
AS_API constexpr vec_t<T, 3> mat3_basis_x(const mat_t<T, 3>& mat)
{
#ifdef AS_COL_MAJOR
  return mat3_col0(mat);
#elif defined AS_ROW_MAJOR
  return mat3_row0(mat);
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

template<typename T>
AS_API constexpr vec_t<T, 3> mat3_basis_y(const mat_t<T, 3>& mat)
{
#ifdef AS_COL_MAJOR
  return mat3_col1(mat);
#elif defined AS_ROW_MAJOR
  return mat3_row1(mat);
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

template<typename T>
AS_API constexpr vec_t<T, 3> mat3_basis_z(const mat_t<T, 3>& mat)
{
#ifdef AS_COL_MAJOR
  return mat3_col2(mat);
#elif defined AS_ROW_MAJOR
  return mat3_row2(mat);
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

template<typename T>
AS_API constexpr void mat3_basis_x(mat_t<T, 3>& mat, const vec_t<T, 3>& basis)
{
#ifdef AS_COL_MAJOR
  return mat3_col0(mat, basis);
#elif defined AS_ROW_MAJOR
  return mat3_row0(mat, basis);
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

template<typename T>
AS_API constexpr void mat3_basis_y(mat_t<T, 3>& mat, const vec_t<T, 3>& basis)
{
#ifdef AS_COL_MAJOR
  return mat3_col1(mat, basis);
#elif defined AS_ROW_MAJOR
  return mat3_row1(mat, basis);
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

template<typename T>
AS_API constexpr void mat3_basis_z(mat_t<T, 3>& mat, const vec_t<T, 3>& basis)
{
#ifdef AS_COL_MAJOR
  return mat3_col2(mat, basis);
#elif defined AS_ROW_MAJOR
  return mat3_row2(mat, basis);
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

template<typename T>
AS_API mat_t<T, 3> mat3_from_ptr(const T* data)
{
  return mat_from_ptr<T, 3>(data);
}

template<typename T>
AS_API mat_t<T, 3> mat3_from_arr(const T (&data)[9])
{
  return mat_from_arr<T, 3>(data);
}

template<typename T>
AS_API constexpr mat_t<T, 3> mat3_from_mat4(const mat_t<T, 4>& transform)
{
  // clang-format off
  return {transform[0], transform[1], transform[2],
          transform[4], transform[5], transform[6],
          transform[8], transform[9], transform[10]};
  // clang-format on
}

AS_API inline mat3_t mat3_rotation_axis(
  const vec3_t& axis, const real_t radians)
{
  const real_t cos_radians = std::cos(radians);
  const real_t sin_radians = std::sin(radians);
  const real_t inv_cos_radians = 1.0_r - cos_radians;

  return {
    cos_radians + ((axis.x * axis.x) * inv_cos_radians),
    (axis.y * axis.x * inv_cos_radians) + (axis.z * sin_radians),
    (axis.z * axis.x * inv_cos_radians) - (axis.y * sin_radians),
    (axis.x * axis.y * inv_cos_radians) - (axis.z * sin_radians),
    cos_radians + ((axis.y * axis.y) * inv_cos_radians),
    (axis.z * axis.y * inv_cos_radians) + (axis.x * sin_radians),
    (axis.x * axis.z * inv_cos_radians) + (axis.y * sin_radians),
    (axis.y * axis.z * inv_cos_radians) - (axis.x * sin_radians),
    cos_radians + ((axis.z * axis.z) * inv_cos_radians)};
}

AS_API inline mat3_t mat3_rotation_xyz(
  const real_t x, const real_t y, const real_t z)
{
  const real_t cos_x = std::cos(x);
  const real_t cos_y = std::cos(y);
  const real_t cos_z = std::cos(z);
  const real_t sin_x = std::sin(x);
  const real_t sin_y = std::sin(y);
  const real_t sin_z = std::sin(z);

  return {
    cos_y * cos_z,
    cos_y * sin_z,
    -sin_y,
    (sin_x * sin_y * cos_z) - (cos_x * sin_z),
    (sin_x * sin_y * sin_z) + (cos_x * cos_z),
    sin_x * cos_y,
    (cos_x * sin_y * cos_z) + (sin_x * sin_z),
    (cos_x * sin_y * sin_z) - (sin_x * cos_z),
    cos_x * cos_y};
}

AS_API inline mat3_t mat3_rotation_zxy(
  const real_t x, const real_t y, const real_t z)
{
  const real_t cos_x = std::cos(x);
  const real_t cos_y = std::cos(y);
  const real_t cos_z = std::cos(z);
  const real_t sin_x = std::sin(x);
  const real_t sin_y = std::sin(y);
  const real_t sin_z = std::sin(z);

  return {
    cos_z * cos_y + sin_x * sin_y * sin_z,
    sin_z * cos_x,
    -sin_y * cos_z + sin_z * sin_x * cos_y,
    -sin_z * cos_y + cos_z * sin_x * sin_y,
    cos_z * cos_x,
    -sin_z * -sin_y + cos_z * sin_x * cos_y,
    cos_x * sin_y,
    -sin_x,
    cos_x * cos_y,
  };
}

AS_API inline mat3_t mat3_rotation_x(const real_t radians)
{
  const real_t cos_radians = std::cos(radians);
  const real_t sin_radians = std::sin(radians);

  // clang-format off
  return {1.0_r, 0.0_r,        0.0_r,
          0.0_r, cos_radians,  sin_radians,
          0.0_r, -sin_radians, cos_radians};
  // clang-format on
}

AS_API inline mat3_t mat3_rotation_y(const real_t radians)
{
  const real_t cos_radians = std::cos(radians);
  const real_t sin_radians = std::sin(radians);

  // clang-format off
  return {cos_radians, 0.0_r, -sin_radians,
          0.0_r,       1.0_r, 0.0_r,
          sin_radians, 0.0_r, cos_radians};
  // clang-format on
}

AS_API inline mat3_t mat3_rotation_z(const real_t radians)
{
  const real_t cos_radians = std::cos(radians);
  const real_t sin_radians = std::sin(radians);

  // clang-format off
  return {cos_radians,  sin_radians, 0.0_r,
          -sin_radians, cos_radians, 0.0_r,
          0.0_r,        0.0_r,       1.0_r};
  // clang-format on
}

AS_API constexpr mat3_t mat3_scale(const real_t scale)
{
  return mat3_scale(scale, scale, scale);
}

//! Returns a (potentially) non-uniform scale martix.
AS_API constexpr mat3_t mat3_scale(
  const real_t x, const real_t y, const real_t z)
{
  // clang-format off
  return {x,     0.0_r, 0.0_r,
          0.0_r, y,     0.0_r,
          0.0_r, 0.0_r, z};
  // clang-format on
}

AS_API constexpr mat3_t mat3_scale(const vec3_t& scale)
{
  return mat3_scale(scale.x, scale.y, scale.z);
}

// ref: Essential Mathematics for Games & Interactive Applications: A
// Programmers Guide section 5.5.7
AS_API constexpr mat3_t mat3_from_quat(const quat_t& quat)
{
  const real_t s{
    2.0_r
    / (quat.x * quat.x + quat.y * quat.y + quat.z * quat.z + quat.w * quat.w)};

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

AS_API constexpr index_t mat4_rc(const index_t r, const index_t c)
{
  return mat_rc(r, c, 4);
}

template<typename T>
AS_API constexpr vec_t<T, 4> mat4_row0(const mat_t<T, 4>& mat)
{
  return mat_row(mat, 0);
}

template<typename T>
AS_API constexpr vec_t<T, 4> mat4_row1(const mat_t<T, 4>& mat)
{
  return mat_row(mat, 1);
}

template<typename T>
AS_API constexpr vec_t<T, 4> mat4_row2(const mat_t<T, 4>& mat)
{
  return mat_row(mat, 2);
}

template<typename T>
AS_API constexpr vec_t<T, 4> mat4_row3(const mat_t<T, 4>& mat)
{
  return mat_row(mat, 3);
}

template<typename T>
AS_API constexpr vec_t<T, 4> mat4_col0(const mat_t<T, 4>& mat)
{
  return mat_col(mat, 0);
}

template<typename T>
AS_API constexpr vec_t<T, 4> mat4_col1(const mat_t<T, 4>& mat)
{
  return mat_col(mat, 1);
}

template<typename T>
AS_API constexpr vec_t<T, 4> mat4_col2(const mat_t<T, 4>& mat)
{
  return mat_col(mat, 2);
}

template<typename T>
AS_API constexpr vec_t<T, 4> mat4_col3(const mat_t<T, 4>& mat)
{
  return mat_col(mat, 3);
}

template<typename T>
AS_API constexpr void mat4_row0(mat_t<T, 4>& mat, const vec_t<T, 4>& row)
{
  mat_row(mat, 0, row);
}

template<typename T>
AS_API constexpr void mat4_row1(mat_t<T, 4>& mat, const vec_t<T, 4>& row)
{
  mat_row(mat, 1, row);
}

template<typename T>
AS_API constexpr void mat4_row2(mat_t<T, 4>& mat, const vec_t<T, 4>& row)
{
  mat_row(mat, 2, row);
}

template<typename T>
AS_API constexpr void mat4_row3(mat_t<T, 4>& mat, const vec_t<T, 4>& row)
{
  mat_row(mat, 3, row);
}

template<typename T>
AS_API constexpr void mat4_col0(mat_t<T, 4>& mat, const vec_t<T, 4>& col)
{
  mat_col(mat, 0, col);
}

template<typename T>
AS_API constexpr void mat4_col1(mat_t<T, 4>& mat, const vec_t<T, 4>& col)
{
  mat_col(mat, 1, col);
}

template<typename T>
AS_API constexpr void mat4_col2(mat_t<T, 4>& mat, const vec_t<T, 4>& col)
{
  mat_col(mat, 2, col);
}

template<typename T>
AS_API constexpr void mat4_col3(mat_t<T, 4>& mat, const vec_t<T, 4>& col)
{
  mat_col(mat, 3, col);
}

template<typename T>
AS_API constexpr vec_t<T, 4> mat4_basis_x(const mat_t<T, 4>& mat)
{
#ifdef AS_COL_MAJOR
  return mat4_col0(mat);
#elif defined AS_ROW_MAJOR
  return mat4_row0(mat);
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

template<typename T>
AS_API constexpr vec_t<T, 4> mat4_basis_y(const mat_t<T, 4>& mat)
{
#ifdef AS_COL_MAJOR
  return mat4_col1(mat);
#elif defined AS_ROW_MAJOR
  return mat4_row1(mat);
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

template<typename T>
AS_API constexpr vec_t<T, 4> mat4_basis_z(const mat_t<T, 4>& mat)
{
#ifdef AS_COL_MAJOR
  return mat4_col2(mat);
#elif defined AS_ROW_MAJOR
  return mat4_row2(mat);
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

template<typename T>
AS_API constexpr vec_t<T, 4> mat4_translation(const mat_t<T, 4>& mat)
{
#ifdef AS_COL_MAJOR
  return mat4_col3(mat);
#elif defined AS_ROW_MAJOR
  return mat4_row3(mat);
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

template<typename T>
AS_API constexpr void mat4_basis_x(mat_t<T, 4>& mat, const vec_t<T, 4>& basis)
{
#ifdef AS_COL_MAJOR
  return mat4_col0(mat, basis);
#elif defined AS_ROW_MAJOR
  return mat4_row0(mat, basis);
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

template<typename T>
AS_API constexpr void mat4_basis_y(mat_t<T, 4>& mat, const vec_t<T, 4>& basis)
{
#ifdef AS_COL_MAJOR
  return mat4_col1(mat, basis);
#elif defined AS_ROW_MAJOR
  return mat4_row1(mat, basis);
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

template<typename T>
AS_API constexpr void mat4_basis_z(mat_t<T, 4>& mat, const vec_t<T, 4>& basis)
{
#ifdef AS_COL_MAJOR
  return mat4_col2(mat, basis);
#elif defined AS_ROW_MAJOR
  return mat4_row2(mat, basis);
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

template<typename T>
AS_API constexpr void mat4_translation(
  mat_t<T, 4>& mat, const vec_t<T, 4>& translation)
{
#ifdef AS_COL_MAJOR
  return mat4_col3(mat, translation);
#elif defined AS_ROW_MAJOR
  return mat4_row3(mat, translation);
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

template<typename T>
AS_API mat_t<T, 4> mat4_from_ptr(const T* data)
{
  return mat_from_ptr<T, 4>(data);
}

template<typename T>
AS_API mat_t<T, 4> mat4_from_arr(const T (&data)[16])
{
  return mat_from_arr<T, 4>(data);
}

template<typename T>
AS_API constexpr mat_t<T, 4> mat4_from_vec3(const vec_t<T, 3>& translation)
{
  return {mat_t<T, 3>::identity(), translation};
}

template<typename T>
AS_API constexpr mat_t<T, 4> mat4_from_mat3(const mat_t<T, 3>& rotation)
{
  return {rotation, vec_t<T, 3>::zero()};
}

template<typename T>
AS_API constexpr mat_t<T, 4> from_mat3_vec3(
  const mat_t<T, 3>& rotation, const vec_t<T, 3>& translation)
{
  return {rotation, translation};
}

AS_API constexpr mat4_t mat4_from_affine(const affine_t& affine)
{
  return from_mat3_vec3(affine.rotation, affine.translation);
}

template<typename T>
AS_API constexpr mat_t<T, 4> mat4_shear_x(const T y, const T z)
{
  // clang-format off
  return {T(1.0), y,      z,      T(0.0),
          T(0.0), T(1.0), T(0.0), T(0.0),
          T(0.0), T(0.0), T(1.0), T(0.0),
          T(0.0), T(0.0), T(0.0), T(1.0)};
  // clang-format on
}

template<typename T>
AS_API constexpr mat_t<T, 4> mat4_shear_y(const T x, const T z)
{
  // clang-format off
  return {T(1.0), T(0.0), T(0.0), T(0.0),
          x,      T(1.0), z,      T(0.0),
          T(0.0), T(0.0), T(1.0), T(0.0),
          T(0.0), T(0.0), T(0.0), T(1.0)};
  // clang-format on
}

template<typename T>
AS_API constexpr mat_t<T, 4> mat4_shear_z(const T x, const T y)
{
  // clang-format off
  return {T(1.0), T(0.0), T(0.0), T(0.0),
          T(0.0), T(1.0), T(0.0), T(0.0),
          x,      y,      T(1.0), T(0.0),
          T(0.0), T(0.0), T(0.0), T(1.0)};
  // clang-format on
}

AS_API inline bool point_equal(
  const point2_t& lhs, const point2_t& rhs,
  const real_t epsilon /*= std::numeric_limits<real_t>::epsilon()*/)
{
  return vec::equal(lhs.as_vec(), rhs.as_vec(), epsilon);
}

AS_API inline bool point_equal(
  const point3_t& lhs, const point3_t& rhs,
  const real_t epsilon /*= std::numeric_limits<real_t>::epsilon()*/)
{
  return vec::equal(lhs.as_vec(), rhs.as_vec(), epsilon);
}

template<typename... points_t>
AS_API auto point_average_fold(points_t&&... points)
{
  return std::common_type_t<decltype(points)...>(
    (points.as_vec() + ...) / real_t(sizeof...(points)));
}

template<typename point_t>
AS_API point_t point_average(const point_t* points, const index_t count)
{
  return point_t(
    std::accumulate(
      points, points + count, point_t{},
      [](auto acc, const auto point) { return acc + point.as_vec(); })
      .as_vec()
    / real_t(count));
}

AS_API constexpr real_t quat_dot(const quat_t& lhs, const quat_t& rhs)
{
  return lhs.w * rhs.w + lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

AS_API constexpr real_t quat_length_sq(const quat_t& quat)
{
  return quat_dot(quat, quat);
}

AS_API inline real_t quat_length(const quat_t& quat)
{
  return std::sqrt(quat_length_sq(quat));
}

AS_API inline quat_t quat_normalize(const quat_t& quat)
{
  return quat / quat_length(quat);
}

AS_API constexpr quat_t quat_conjugate(const quat_t& quat)
{
  return {quat.w, -quat.x, -quat.y, -quat.z};
}

AS_API inline quat_t quat_inverse(const quat_t& quat)
{
  return quat_conjugate(quat) / quat_length_sq(quat);
}

AS_API inline vec3_t quat_rotate(const quat_t& quat, const vec3_t& v)
{
  const quat_t quat_result =
    quat * quat_t{0.0_r, v.x, v.y, v.z} * quat_conjugate(quat);
  return {quat_result.x, quat_result.y, quat_result.z};
}

AS_API inline quat_t quat_rotation_axis(
  const vec3_t& axis, const real_t radians)
{
  return {std::cos(0.5_r * radians), axis * std::sin(0.5_r * radians)};
}

AS_API inline quat_t quat_rotation_zxy(
  const real_t x, const real_t y, const real_t z)
{
  return quat_t{std::cos(0.5_r * y), 0.0_r, std::sin(0.5_r * y), 0.0_r}
       * quat_t{std::cos(0.5_r * x), std::sin(0.5_r * x), 0.0_r, 0.0_r}
       * quat_t{std::cos(0.5_r * z), 0.0_r, 0.0_r, std::sin(0.5_r * z)};
}

AS_API inline quat_t quat_slerp(
  const quat_t& lhs, const quat_t& rhs, const real_t t)
{
  const real_t theta = std::acos(quat_dot(lhs, rhs));
  return (lhs * std::sin((1.0_r - t) * theta) + rhs * std::sin(t * theta))
       / std::sin(theta);
}

// ref: euclidean space
// http://www.euclideanspace.com/maths/geometry/rotations/conversions/matrixToQuaternion/index.htm
AS_API inline quat_t quat_from_mat3(const mat3_t& mat)
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
    if (
      mat[index(0, 0)] > mat[index(1, 1)]
      && mat[index(0, 0)] > mat[index(2, 2)]) {
      real_t s =
        2.0_r
        * std::sqrt(
          1.0_r + mat[index(0, 0)] - mat[index(1, 1)] - mat[index(2, 2)]);
      q.w = (mat[index(2, 1)] - mat[index(1, 2)]) / s;
      q.x = 0.25_r * s;
      q.y = (mat[index(0, 1)] + mat[index(1, 0)]) / s;
      q.z = (mat[index(0, 2)] + mat[index(2, 0)]) / s;
    } else if (mat[index(1, 1)] > mat[index(2, 2)]) {
      real_t s =
        2.0_r
        * std::sqrt(
          1.0_r + mat[index(1, 1)] - mat[index(0, 0)] - mat[index(2, 2)]);
      q.w = (mat[index(0, 2)] - mat[index(2, 0)]) / s;
      q.x = (mat[index(0, 1)] + mat[index(1, 0)]) / s;
      q.y = 0.25_r * s;
      q.z = (mat[index(1, 2)] + mat[index(2, 1)]) / s;
    } else {
      real_t s =
        2.0_r
        * std::sqrt(
          1.0_r + mat[index(2, 2)] - mat[index(0, 0)] - mat[index(1, 1)]);
      q.w = (mat[index(1, 0)] - mat[index(0, 1)]) / s;
      q.x = (mat[index(0, 2)] + mat[index(2, 0)]) / s;
      q.y = (mat[index(1, 2)] + mat[index(2, 1)]) / s;
      q.z = 0.25_r * s;
    }
  }

  return q;
}

AS_API inline void affine_to_arr(const affine_t& affine, real_t (&data)[12])
{
  for (index_t i = 0; i < affine.rotation.size(); ++i) {
    data[i] = affine.rotation[i];
  }

  for (index_t i = 0; i < affine.translation.size(); ++i) {
    data[affine.rotation.size() + i] = affine.translation[i];
  }
}

AS_API inline affine_t affine_from_arr(const real_t (&data)[12])
{
  return affine_from_ptr(data);
}

AS_API inline affine_t affine_from_ptr(const real_t* data)
{
  affine_t result;

  constexpr auto mat_size = mat3_t::size();
  for (index_t i = 0; i < mat_size; ++i) {
    result.rotation[i] = data[i];
  }

  constexpr auto vec_size = vec3_t::size();
  for (index_t i = 0; i < vec_size; ++i) {
    result.translation[i] = data[result.rotation.size() + i];
  }

  return result;
}

AS_API inline affine_t affine_from(const mat4_t& mat)
{
  return affine_t(mat3_from_mat4(mat), vec3::from_vec4(mat4_translation(mat)));
}

AS_API inline affine_t affine_from(const mat3_t& mat)
{
  return affine_t(mat, vec3_t::zero());
}

AS_API inline affine_t affine_from(const mat3_t& mat, const vec3_t& vec)
{
  return affine_t(mat, vec);
}

AS_API inline affine_t affine_from(const vec3_t& vec)
{
  return affine_t(vec);
}

AS_API inline affine_t affine_from(const point3_t& point)
{
  return affine_t(point.as_vec());
}

AS_API inline affine_t affine_mul(const affine_t& lhs, const affine_t& rhs)
{
  return affine_t(
    mat_mul(lhs.rotation, rhs.rotation),
    affine_transform_pos(rhs, lhs.translation));
}

AS_API inline affine_t affine_inverse(const affine_t& affine)
{
  const mat3_t inv_rot = transpose(affine.rotation);
  const vec3_t inv_pos =
    affine_transform_pos(affine_t(inv_rot), -affine.translation);
  return affine_t(inv_rot, inv_pos);
}

AS_API inline vec3_t affine_transform_dir(
  const affine_t& affine, const vec3_t& direction)
{
#ifdef AS_COL_MAJOR
  return affine.rotation * direction;
#elif defined AS_ROW_MAJOR
  return direction * affine.rotation;
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

AS_API inline vec3_t affine_transform_pos(
  const affine_t& affine, const vec3_t& position)
{
#ifdef AS_COL_MAJOR
  return affine.rotation * position + affine.translation;
#elif defined AS_ROW_MAJOR
  return position * affine.rotation + affine.translation;
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

AS_API inline point3_t affine_transform_pos(
  const affine_t& affine, const point3_t& position)
{
  return point3_t(affine_transform_pos(affine, position.as_vec()));
}

AS_API inline vec3_t affine_inv_transform_dir(
  const affine_t& affine, const vec3_t& direction)
{
  const mat3_t inv_rotation = inverse(affine.rotation);
#ifdef AS_COL_MAJOR
  return inv_rotation * direction;
#elif defined AS_ROW_MAJOR
  return direction * inv_rotation;
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

AS_API inline vec3_t affine_inv_transform_pos(
  const affine_t& affine, const vec3_t& position)
{
  const mat3_t inv_rotation = inverse(affine.rotation);
#ifdef AS_COL_MAJOR
  return inv_rotation * (position - affine.translation);
#elif defined AS_ROW_MAJOR
  return (position - affine.translation) * inv_rotation;
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

AS_API inline point3_t affine_inv_transform_pos(
  const affine_t& affine, const point3_t& position)
{
  return point3_t(affine_inv_transform_pos(affine, position.as_vec()));
}

} // namespace as
