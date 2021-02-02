namespace as
{

template<typename T, index d>
AS_API vec<T, d> vec_from_arr(const T (&data)[d])
{
  return vec_from_ptr<T, d>(&data[0]);
}

template<typename T, index d>
AS_API vec<T, d> vec_from_ptr(const T* data)
{
  vec<T, d> result;
  for (index i = 0; i < d; ++i) {
    result[i] = data[i];
  }

  return result;
}

template<typename T, index d>
AS_API void vec_to_arr(const vec<T, d>& v, T (&data)[d])
{
  for (index i = 0; i < d; ++i) {
    data[i] = v[i];
  }
}

template<typename T, index d>
AS_API T* vec_data(vec<T, d>& v)
{
  return const_cast<T*>(vec_const_data(static_cast<const vec<T, d>&>(v)));
}

template<typename T, index d>
AS_API const T* vec_const_data(const vec<T, d>& v)
{
  return &v[0];
}

template<typename T, index d>
AS_API constexpr T vec_dot(const vec<T, d>& lhs, const vec<T, d>& rhs)
{
  auto result = T(0.0);
  for (index i = 0; i < d; ++i) {
    result += lhs[i] * rhs[i];
  }

  return result;
}

template<>
AS_API constexpr real vec_dot(const vec2& lhs, const vec2& rhs)
{
  return lhs.x * rhs.x + lhs.y * rhs.y;
}

template<>
AS_API constexpr real vec_dot(const vec3& lhs, const vec3& rhs)
{
  return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

template<typename T, index d>
AS_API constexpr T vec_length_sq(const vec<T, d>& v)
{
  return vec_dot(v, v);
}

template<typename T, index d>
AS_API T vec_length(const vec<T, d>& v)
{
  return std::sqrt(vec_length_sq(v));
}

template<typename T, index d>
AS_API T vec_distance(const vec<T, d>& lhs, const vec<T, d>& rhs)
{
  return vec_length(rhs - lhs);
}

template<typename T, index d>
AS_API vec<T, d> vec_normalize(const vec<T, d>& v)
{
  return v / vec_length(v);
}

template<typename T, index d>
AS_API std::tuple<vec<T, d>, T> vec_normalize_and_length(const vec<T, d>& v)
{
  const T len = vec_length(v);
  return std::make_tuple(v / len, len);
}

template<typename T, index d>
AS_API bool vec_near(
  const vec<T, d>& lhs, const vec<T, d>& rhs,
  const real max_diff /*= std::numeric_limits<real>::epsilon()*/,
  const real max_rel_diff /*= std::numeric_limits<real>::epsilon()*/)
{
  for (index i = 0; i < d; ++i) {
    if (!real_near(lhs[i], rhs[i], max_diff, max_rel_diff)) {
      return false;
    }
  }

  return true;
}

template<typename T, index d>
AS_API vec<T, d> vec_min(const vec<T, d>& lhs, const vec<T, d>& rhs)
{
  vec<T, d> result;
  for (index i = 0; i < d; ++i) {
    result[i] = min(lhs[i], rhs[i]);
  }

  return result;
}

template<typename T, index d>
AS_API constexpr T vec_min_elem(const vec<T, d>& v)
{
  T val = v[0];
  for (index i = 1; i < d; ++i) {
    val = min(val, v[i]);
  }

  return val;
}

template<typename T, index d>
AS_API vec<T, d> vec_max(const vec<T, d>& lhs, const vec<T, d>& rhs)
{
  vec<T, d> result;
  for (index i = 0; i < d; ++i) {
    result[i] = max(lhs[i], rhs[i]);
  }

  return result;
}

template<typename T, index d>
AS_API constexpr T vec_max_elem(const vec<T, d>& v)
{
  T val = v[0];
  for (index i = 1; i < d; ++i) {
    val = max(val, v[i]);
  }

  return val;
}

template<typename T, index d>
AS_API vec<T, d> vec_abs(const vec<T, d>& v)
{
  vec<T, d> result;
  for (index i = 0; i < d; ++i) {
    result[i] = std::abs(v[i]);
  }

  return result;
}

template<typename T, index d>
AS_API vec<T, d> vec_clamp(
  const vec<T, d>& v, const vec<T, d>& min, const vec<T, d>& max)
{
  vec<T, d> result;
  for (index i = 0; i < d; ++i) {
    result[i] = clamp(v[i], min[i], max[i]);
  }

  return result;
}

template<typename T, index d>
AS_API vec<T, d> vec_saturate(const vec<T, d>& v)
{
  vec<T, d> result;
  for (index i = 0; i < d; ++i) {
    result[i] = clamp(v[i], T(0.0), T(1.0));
  }

  return result;
}

template<typename T, index d>
AS_API vec<T, d> vec_mix(
  const vec<T, d>& begin, const vec<T, d>& end, const T t)
{
  vec<T, d> result;
  for (index i = 0; i < d; ++i) {
    result[i] = mix(begin[i], end[i], t);
  }

  return result;
}

template<>
AS_API constexpr vec2 vec_mix(const vec2& begin, const vec2& end, const real t)
{
  return {mix(begin.x, end.x, t), mix(begin.y, end.y, t)};
}

template<>
AS_API constexpr vec3 vec_mix(const vec3& begin, const vec3& end, const real t)
{
  return {
    mix(begin.x, end.x, t), mix(begin.y, end.y, t), mix(begin.z, end.z, t)};
}

template<typename T, index d>
AS_API constexpr vec<T, d> vec_select(
  const vec<T, d>& v0, const vec<T, d>& v1, bool select0)
{
  return select0 ? v0 : v1;
}

template<typename T, index d>
AS_API vec<T, d> vec_floor(const vec<T, d>& v)
{
  vec<T, d> result;
  for (index i = 0; i < d; ++i) {
    result[i] = std::floor(v[i]);
  }

  return result;
}

template<typename T, index d>
AS_API vec<T, d> vec_ceil(const vec<T, d>& v)
{
  vec<T, d> result;
  for (index i = 0; i < d; ++i) {
    result[i] = std::ceil(v[i]);
  }

  return result;
}

template<typename T, index d>
AS_API vec<T, d> vec_round(const vec<T, d>& v)
{
  vec<T, d> result;
  for (index i = 0; i < d; ++i) {
    result[i] = std::round(v[i]);
  }

  return result;
}

template<typename T, index d>
AS_API vec<T, d> vec_snap(const vec<T, d>& v, const T step)
{
  vec<T, d> result;
  for (index i = 0; i < d; ++i) {
    result[i] = snap(v[i], step);
  }

  return result;
}

template<typename T>
AS_API inline vec<T, 2> vec2_from_ptr(const T* data)
{
  return vec_from_ptr<T, 2>(data);
}

template<typename T>
AS_API inline vec<T, 2> vec2_from_arr(const T (&data)[2])
{
  return vec_from_arr(data);
}

template<typename T>
AS_API constexpr vec<T, 2> vec2_from_vec3(const vec<T, 3>& v)
{
  return {v.x, v.y};
}

template<typename T>
AS_API constexpr vec<T, 2> vec2_from_vec4(const vec<T, 4>& v)
{
  return {v.x, v.y};
}

template<typename T>
AS_API constexpr T vec2_wedge(const vec<T, 2>& lhs, const vec<T, 2>& rhs)
{
  return lhs.x * rhs.y - lhs.y * rhs.x;
}

template<typename T>
AS_API vec<T, 3> vec3_from_ptr(const T* data)
{
  return vec_from_ptr<T, 3>(data);
}

template<typename T>
AS_API vec<T, 3> vec3_from_arr(const T (&data)[3])
{
  return vec_from_arr(data);
}

template<typename T>
AS_API constexpr vec<T, 3> vec3_from_vec2(const vec<T, 2>& v, const T z)
{
  return {v.x, v.y, z};
}

template<typename T>
AS_API constexpr vec<T, 3> vec3_from_vec4(const vec<T, 4>& v)
{
  return {v.x, v.y, v.z};
}

template<typename T>
AS_API constexpr vec<T, 3> vec3_cross(
  const vec<T, 3>& lhs, const vec<T, 3>& rhs)
{
  // clang-format off
  return {lhs.y * rhs.z - lhs.z * rhs.y,
          lhs.z * rhs.x - lhs.x * rhs.z,
          lhs.x * rhs.y - lhs.y * rhs.x};
  // clang-format on
}

template<typename T>
AS_API vec<T, 3> vec3_reflect(const vec<T, 3>& l, const vec<T, 3>& n)
{
  return l - n * T(2.0) * vec_dot(l, n);
}

template<typename T>
AS_API void vec3_right_and_up_lh(
  const vec<T, 3>& dir, vec<T, 3>& across, vec<T, 3>& up,
  const vec<T, 3>& world_up)
{
  across = vec3_cross(dir, world_up);
  up = vec_normalize(vec3_cross(across, dir));
  across = vec_normalize(vec3_cross(up, dir));
}

template<typename T>
AS_API void vec3_right_and_up_rh(
  const vec<T, 3>& dir, vec<T, 3>& across, vec<T, 3>& up,
  const vec<T, 3>& world_up)
{
  across = vec3_cross(dir, world_up);
  up = vec_normalize(vec3_cross(across, dir));
  across = vec_normalize(vec3_cross(dir, up));
}

template<typename T>
AS_API vec<T, 3> vec3_orthogonal(const vec<T, 3>& u)
{
  const auto [x, y, z] = vec_abs(u);

  return vec_normalize([u, x = x, y = y, z = z] {
    if (x <= y && x <= z) {
      return vec<T, 3>(0.0_r, -u.z, u.y);
    }
    if (y <= x && y <= z) {
      return vec<T, 3>(-u.z, 0.0_r, u.x);
    }
    // z <= x && z <= y
    return vec<T, 3>(-u.y, u.x, 0.0_r);
  }());
}

// ref: John F. Hughes & Tomas Moller (1999) Building an Orthonormal
// Basis from a Unit Vector, Journal of Graphics Tools, 4:4, 33-35
template<typename T>
AS_API mat<T, 3> orthonormal_basis(const vec<T, 3>& u)
{
  const vec<T, 3> v = vec3_orthogonal(u);
  const vec<T, 3> w = vec3_cross(u, v);
  return mat<T, 3>(u, v, w);
}

template<typename T>
AS_API vec<T, 4> vec4_from_ptr(const T* data)
{
  return vec_from_ptr<T, 4>(data);
}

template<typename T>
AS_API vec<T, 4> vec4_from_arr(const T (&data)[4])
{
  return vec_from_arr(data);
}

template<typename T>
AS_API constexpr vec<T, 4> vec4_from_vec2(
  const vec<T, 2>& v, const T z, const T w)
{
  return {v.x, v.y, z, w};
}

template<typename T>
AS_API constexpr vec<T, 4> vec4_from_vec3(const vec<T, 3>& v, const T w)
{
  return {v.x, v.y, v.z, w};
}

template<typename T>
AS_API constexpr vec<T, 4> vec4_translation(const vec<T, 3>& v)
{
  return vec4_from_vec3(v, T(1.0));
}

template<typename T>
AS_API constexpr vec<T, 4> vec4_direction(const vec<T, 3>& v)
{
  return vec4_from_vec3(v, T(0.0));
}

template<typename T, index d>
AS_API vec<T, d> vec_average(const vec<T, d>* vectors, const index count)
{
  return vec<T, d>(
    std::accumulate(
      vectors, vectors + count, vec<T, d>{},
      [](auto acc, const auto v) { return acc + v; })
    / real(count));
}

template<typename... vectors>
AS_API auto vec_average_fold(vectors&&... vecs)
{
  return std::common_type_t<decltype(vecs)...>(
    (vecs + ...) / real(sizeof...(vecs)));
}

AS_API constexpr index mat_rc(const index r, const index c, const index d)
{
#ifdef AS_COL_MAJOR
  return c * d + r;
#elif defined AS_ROW_MAJOR
  return r * d + c;
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

template<typename T, index d>
AS_API vec<T, d> mat_row(const mat<T, d>& m, const index r)
{
  vec<T, d> v;
  for (index c = 0; c < d; ++c) {
    v[c] = m[mat_rc(r, c, d)];
  }

  return v;
}

template<typename T, index d>
AS_API vec<T, d> mat_col(const mat<T, d>& m, const index c)
{
  vec<T, d> v;
  for (index r = 0; r < d; ++r) {
    v[r] = m[mat_rc(r, c, d)];
  }

  return v;
}

template<typename T, index d>
AS_API constexpr void mat_row(mat<T, d>& m, const index r, const vec<T, d>& row)
{
  for (index c = 0; c < d; ++c) {
    m[mat_rc(r, c, d)] = row[c];
  }
}

template<typename T, index d>
AS_API constexpr void mat_col(mat<T, d>& m, const index c, const vec<T, d>& col)
{
  for (index r = 0; r < d; ++r) {
    m[mat_rc(r, c, d)] = col[r];
  }
}

template<typename T, index d>
AS_API T* mat_data(mat<T, d>& m)
{
  return const_cast<T*>(mat_const_data(static_cast<const mat<T, d>&>(m)));
}

template<typename T, index d>
AS_API const T* mat_const_data(const mat<T, d>& m)
{
  return &m[0];
}

template<typename T, index d>
AS_API mat<T, d> mat_from_arr(const T (&data)[d * d])
{
  return mat_from_ptr<T, d>(data);
}

template<typename T, index d>
AS_API mat<T, d> mat_from_ptr(const T* data)
{
  mat<T, d> result;
  for (index i = 0; i < d * d; ++i) {
    result[i] = data[i];
  }

  return result;
}

template<typename T, index d>
AS_API void mat_to_arr(const mat<T, d>& m, T (&data)[d * d])
{
  for (index i = 0; i < d * d; ++i) {
    data[i] = m[i];
  }
}

template<typename T, index d>
AS_API bool mat_near(
  const mat<T, d>& lhs, const mat<T, d>& rhs,
  const real max_diff /*= std::numeric_limits<real>::epsilon()*/,
  const real max_rel_diff /*= std::numeric_limits<real>::epsilon()*/)
{
  for (index i = 0; i < mat<T, d>::size(); ++i) {
    if (!real_near(lhs[i], rhs[i], max_diff, max_rel_diff)) {
      return false;
    }
  }

  return true;
}

template<typename T, index d>
AS_API mat<T, d> mat_transpose(const mat<T, d>& m)
{
  mat<T, d> result;
  for (index ci = 0; ci < d; ++ci) {
    for (index ri = 0; ri < d; ++ri) {
      result[ci * d + ri] = m[ri * d + ci];
    }
  }

  return result;
}

namespace internal
{

template<index>
struct int2type
{
};

// where col and row are the rows to ignore
template<typename T, index d>
AS_API mat<T, d - 1> sub_matrix(
  const mat<T, d>& m, const index r, const index c)
{
  mat<T, d - 1> result = mat_identity<T, d - 1>();

  index i = 0;
  for (index ci = 0; ci < d; ++ci) {
    for (index ri = 0; ri < d; ++ri) {
      if (ri == r || ci == c) {
        continue;
      }

      result[i++] = m[ci * d + ri];
    }
  }

  return result;
}

#pragma push_macro("minor")
#undef minor

template<typename T>
AS_API T minor(const mat<T, 2>& m)
{
  return m[0] * m[3] - m[2] * m[1];
}

template<typename T, index d, index I>
AS_API T determinant_impl(const mat<T, d>& m, int2type<I> /*unused*/)
{
  T sign{1.0};
  T result{0.0};

  for (index i = 0; i < d; ++i) {
    const T minor_det =
      determinant_impl(sub_matrix(m, i, 0), int2type<I - 1>{});
    result += (m[i] * minor_det) * sign;
    sign *= T{-1.0};
  }

  return result;
}

template<typename T>
AS_API T determinant_impl(const mat<T, 2>& m, int2type<2> /*unused*/)
{
  return minor(m);
}

#pragma pop_macro("minor")

template<typename T, index d, index I>
AS_API mat<T, d> minor_impl(const mat<T, d>& m, int2type<I> /*unused*/)
{
  mat<T, d> result;
  T outer_sign = T{1.0};

  for (index c = 0; c < d; ++c) {
    T inner_sign{outer_sign};
    for (index r = 0; r < d; ++r) {
      const T minor_det =
        determinant_impl<T>(internal::sub_matrix(m, r, c), int2type<d - 1>{});
      result[c * d + r] = minor_det * inner_sign;
      inner_sign *= T{-1.0};
    }

    outer_sign *= T{-1.0};
  }

  return result;
}

} // namespace internal

template<typename T, index d>
AS_API T determinant(const mat<T, d>& m)
{
  return internal::determinant_impl(m, internal::int2type<d>{});
}

template<typename T, index d>
AS_API mat<T, d> mat_inverse(const mat<T, d>& m)
{
  mat<T, d> result;

  result = internal::minor_impl(m, internal::int2type<d>{});
  result = mat_transpose(result);
  result *= T(1.0) / determinant(m);

  return result;
}

template<typename T>
AS_API mat<T, 2> mat_inverse(const mat<T, 2>& m)
{
  // clang-format off
  return mat<T, 2>{m[3], -m[1],
                  -m[2],  m[0]}
        * (T(1.0) / determinant(m));
  // clang-format on
}

template<typename T, index d>
AS_API mat<T, d> mat_mul(const mat<T, d>& lhs, const mat<T, d>& rhs)
{
#ifdef AS_COL_MAJOR
  return rhs * lhs;
#elif defined AS_ROW_MAJOR
  return lhs * rhs;
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

template<typename T, index d>
AS_API vec<T, d> mat_mul(const vec<T, d>& v, const mat<T, d>& m)
{
#ifdef AS_COL_MAJOR
  return m * v;
#elif defined AS_ROW_MAJOR
  return v * m;
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

AS_API constexpr index mat3_rc(const index r, const index c)
{
  return mat_rc(r, c, 3);
}

template<typename T>
AS_API constexpr vec<T, 3> mat3_row0(const mat<T, 3>& m)
{
  return mat_row(m, 0);
}

template<typename T>
AS_API constexpr vec<T, 3> mat3_row1(const mat<T, 3>& m)
{
  return mat_row(m, 1);
}

template<typename T>
AS_API constexpr vec<T, 3> mat3_row2(const mat<T, 3>& m)
{
  return mat_row(m, 2);
}

template<typename T>
AS_API constexpr vec<T, 3> mat3_col0(const mat<T, 3>& m)
{
  return mat_col(m, 0);
}

template<typename T>
AS_API constexpr vec<T, 3> mat3_col1(const mat<T, 3>& m)
{
  return mat_col(m, 1);
}

template<typename T>
AS_API constexpr vec<T, 3> mat3_col2(const mat<T, 3>& m)
{
  return mat_col(m, 2);
}

template<typename T>
AS_API constexpr void mat3_row0(mat<T, 3>& m, const vec<T, 3>& row)
{
  mat_row(m, 0, row);
}

template<typename T>
AS_API constexpr void mat3_row1(mat<T, 3>& m, const vec<T, 3>& row)
{
  mat_row(m, 1, row);
}

template<typename T>
AS_API constexpr void mat3_row2(mat<T, 3>& m, const vec<T, 3>& row)
{
  mat_row(m, 2, row);
}

template<typename T>
AS_API constexpr void mat3_col0(mat<T, 3>& m, const vec<T, 3>& col)
{
  mat_col(m, 0, col);
}

template<typename T>
AS_API constexpr void mat3_col1(mat<T, 3>& m, const vec<T, 3>& col)
{
  mat_col(m, 1, col);
}

template<typename T>
AS_API constexpr void mat3_col2(mat<T, 3>& m, const vec<T, 3>& col)
{
  mat_col(m, 2, col);
}

template<typename T>
AS_API constexpr vec<T, 3> mat3_basis_x(const mat<T, 3>& m)
{
#ifdef AS_COL_MAJOR
  return mat3_col0(m);
#elif defined AS_ROW_MAJOR
  return mat3_row0(m);
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

template<typename T>
AS_API constexpr vec<T, 3> mat3_basis_y(const mat<T, 3>& m)
{
#ifdef AS_COL_MAJOR
  return mat3_col1(m);
#elif defined AS_ROW_MAJOR
  return mat3_row1(m);
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

template<typename T>
AS_API constexpr vec<T, 3> mat3_basis_z(const mat<T, 3>& m)
{
#ifdef AS_COL_MAJOR
  return mat3_col2(m);
#elif defined AS_ROW_MAJOR
  return mat3_row2(m);
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

template<typename T>
AS_API constexpr void mat3_basis_x(mat<T, 3>& m, const vec<T, 3>& basis)
{
#ifdef AS_COL_MAJOR
  return mat3_col0(m, basis);
#elif defined AS_ROW_MAJOR
  return mat3_row0(m, basis);
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

template<typename T>
AS_API constexpr void mat3_basis_y(mat<T, 3>& m, const vec<T, 3>& basis)
{
#ifdef AS_COL_MAJOR
  return mat3_col1(m, basis);
#elif defined AS_ROW_MAJOR
  return mat3_row1(m, basis);
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

template<typename T>
AS_API constexpr void mat3_basis_z(mat<T, 3>& m, const vec<T, 3>& basis)
{
#ifdef AS_COL_MAJOR
  return mat3_col2(m, basis);
#elif defined AS_ROW_MAJOR
  return mat3_row2(m, basis);
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

template<typename T>
AS_API mat<T, 3> mat3_from_ptr(const T* data)
{
  return mat_from_ptr<T, 3>(data);
}

template<typename T>
AS_API mat<T, 3> mat3_from_arr(const T (&data)[9])
{
  return mat_from_arr<T, 3>(data);
}

template<typename T>
AS_API constexpr mat<T, 3> mat3_from_mat4(const mat<T, 4>& transform)
{
  // clang-format off
  return {transform[0], transform[1], transform[2],
          transform[4], transform[5], transform[6],
          transform[8], transform[9], transform[10]};
  // clang-format on
}

AS_API constexpr mat3 mat3_from_affine(const affine& a)
{
  return a.rotation;
}

AS_API inline mat3 mat3_rotation_axis(const vec3& axis, const real radians)
{
  const real cos_radians = std::cos(radians);
  const real sin_radians = std::sin(radians);
  const real inv_cos_radians = 1.0_r - cos_radians;

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

AS_API inline mat3 mat3_rotation_xyz(const real x, const real y, const real z)
{
  const real cos_x = std::cos(x);
  const real cos_y = std::cos(y);
  const real cos_z = std::cos(z);
  const real sin_x = std::sin(x);
  const real sin_y = std::sin(y);
  const real sin_z = std::sin(z);

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

AS_API inline mat3 mat3_rotation_zxy(const real x, const real y, const real z)
{
  const real cos_x = std::cos(x);
  const real cos_y = std::cos(y);
  const real cos_z = std::cos(z);
  const real sin_x = std::sin(x);
  const real sin_y = std::sin(y);
  const real sin_z = std::sin(z);

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

AS_API inline mat3 mat3_rotation_x(const real radians)
{
  const real cos_radians = std::cos(radians);
  const real sin_radians = std::sin(radians);

  // clang-format off
  return {1.0_r, 0.0_r,        0.0_r,
          0.0_r, cos_radians,  sin_radians,
          0.0_r, -sin_radians, cos_radians};
  // clang-format on
}

AS_API inline mat3 mat3_rotation_y(const real radians)
{
  const real cos_radians = std::cos(radians);
  const real sin_radians = std::sin(radians);

  // clang-format off
  return {cos_radians, 0.0_r, -sin_radians,
          0.0_r,       1.0_r, 0.0_r,
          sin_radians, 0.0_r, cos_radians};
  // clang-format on
}

AS_API inline mat3 mat3_rotation_z(const real radians)
{
  const real cos_radians = std::cos(radians);
  const real sin_radians = std::sin(radians);

  // clang-format off
  return {cos_radians,  sin_radians, 0.0_r,
          -sin_radians, cos_radians, 0.0_r,
          0.0_r,        0.0_r,       1.0_r};
  // clang-format on
}

AS_API constexpr mat3 mat3_scale(const real scale)
{
  return mat3_scale(scale, scale, scale);
}

//! Returns a (potentially) non-uniform scale martix.
AS_API constexpr mat3 mat3_scale(const real x, const real y, const real z)
{
  // clang-format off
  return {x,     0.0_r, 0.0_r,
          0.0_r, y,     0.0_r,
          0.0_r, 0.0_r, z};
  // clang-format on
}

AS_API constexpr mat3 mat3_scale(const vec3& scale)
{
  return mat3_scale(scale.x, scale.y, scale.z);
}

// ref: Essential Mathematics for Games & Interactive Applications: A
// Programmers Guide section 5.5.7
AS_API constexpr mat3 mat3_from_quat(const quat& q)
{
  const real s{2.0_r / (q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w)};

  const real xs{s * q.x};
  const real ys{s * q.y};
  const real zs{s * q.z};
  const real wx{q.w * xs};
  const real wy{q.w * ys};
  const real wz{q.w * zs};
  const real xx{q.x * xs};
  const real xy{q.x * ys};
  const real xz{q.x * zs};
  const real yy{q.y * ys};
  const real yz{q.y * zs};
  const real zz{q.z * zs};

  return {1.0_r - (yy + zz), xy + wz,           xz - wy,
          xy - wz,           1.0_r - (xx + zz), yz + wx,
          xz + wy,           yz - wx,           1.0_r - (xx + yy)};
}

AS_API constexpr index mat4_rc(const index r, const index c)
{
  return mat_rc(r, c, 4);
}

template<typename T>
AS_API constexpr vec<T, 4> mat4_row0(const mat<T, 4>& m)
{
  return mat_row(m, 0);
}

template<typename T>
AS_API constexpr vec<T, 4> mat4_row1(const mat<T, 4>& m)
{
  return mat_row(m, 1);
}

template<typename T>
AS_API constexpr vec<T, 4> mat4_row2(const mat<T, 4>& m)
{
  return mat_row(m, 2);
}

template<typename T>
AS_API constexpr vec<T, 4> mat4_row3(const mat<T, 4>& m)
{
  return mat_row(m, 3);
}

template<typename T>
AS_API constexpr vec<T, 4> mat4_col0(const mat<T, 4>& m)
{
  return mat_col(m, 0);
}

template<typename T>
AS_API constexpr vec<T, 4> mat4_col1(const mat<T, 4>& m)
{
  return mat_col(m, 1);
}

template<typename T>
AS_API constexpr vec<T, 4> mat4_col2(const mat<T, 4>& m)
{
  return mat_col(m, 2);
}

template<typename T>
AS_API constexpr vec<T, 4> mat4_col3(const mat<T, 4>& m)
{
  return mat_col(m, 3);
}

template<typename T>
AS_API constexpr void mat4_row0(mat<T, 4>& m, const vec<T, 4>& row)
{
  mat_row(m, 0, row);
}

template<typename T>
AS_API constexpr void mat4_row1(mat<T, 4>& m, const vec<T, 4>& row)
{
  mat_row(m, 1, row);
}

template<typename T>
AS_API constexpr void mat4_row2(mat<T, 4>& m, const vec<T, 4>& row)
{
  mat_row(m, 2, row);
}

template<typename T>
AS_API constexpr void mat4_row3(mat<T, 4>& m, const vec<T, 4>& row)
{
  mat_row(m, 3, row);
}

template<typename T>
AS_API constexpr void mat4_col0(mat<T, 4>& m, const vec<T, 4>& col)
{
  mat_col(m, 0, col);
}

template<typename T>
AS_API constexpr void mat4_col1(mat<T, 4>& m, const vec<T, 4>& col)
{
  mat_col(m, 1, col);
}

template<typename T>
AS_API constexpr void mat4_col2(mat<T, 4>& m, const vec<T, 4>& col)
{
  mat_col(m, 2, col);
}

template<typename T>
AS_API constexpr void mat4_col3(mat<T, 4>& m, const vec<T, 4>& col)
{
  mat_col(m, 3, col);
}

template<typename T>
AS_API constexpr vec<T, 4> mat4_dimension0(const mat<T, 4>& m)
{
#ifdef AS_COL_MAJOR
  return mat4_col0(m);
#elif defined AS_ROW_MAJOR
  return mat4_row0(m);
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

template<typename T>
AS_API constexpr vec<T, 4> mat4_dimension1(const mat<T, 4>& m)
{
#ifdef AS_COL_MAJOR
  return mat4_col1(m);
#elif defined AS_ROW_MAJOR
  return mat4_row1(m);
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

template<typename T>
AS_API constexpr vec<T, 4> mat4_dimension2(const mat<T, 4>& m)
{
#ifdef AS_COL_MAJOR
  return mat4_col2(m);
#elif defined AS_ROW_MAJOR
  return mat4_row2(m);
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

template<typename T>
AS_API constexpr vec<T, 4> mat4_dimension3(const mat<T, 4>& m)
{
#ifdef AS_COL_MAJOR
  return mat4_col3(m);
#elif defined AS_ROW_MAJOR
  return mat4_row3(m);
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

template<typename T>
AS_API constexpr void mat4_dimension0(mat<T, 4>& m, const vec<T, 4>& v)
{
#ifdef AS_COL_MAJOR
  return mat4_col0(m, v);
#elif defined AS_ROW_MAJOR
  return mat4_row0(m, v);
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

template<typename T>
AS_API constexpr void mat4_dimension1(mat<T, 4>& m, const vec<T, 4>& v)
{
#ifdef AS_COL_MAJOR
  return mat4_col1(m, v);
#elif defined AS_ROW_MAJOR
  return mat4_row1(m, v);
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

template<typename T>
AS_API constexpr void mat4_dimension2(mat<T, 4>& m, const vec<T, 4>& v)
{
#ifdef AS_COL_MAJOR
  return mat4_col2(m, v);
#elif defined AS_ROW_MAJOR
  return mat4_row2(m, v);
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

template<typename T>
AS_API constexpr void mat4_dimension3(mat<T, 4>& m, const vec<T, 4>& v)
{
#ifdef AS_COL_MAJOR
  return mat4_col3(m, v);
#elif defined AS_ROW_MAJOR
  return mat4_row3(m, v);
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

template<typename T>
AS_API constexpr vec<T, 3> mat4_basis_x(const mat<T, 4>& m)
{
  return vec3_from_vec4(mat4_dimension0(m));
}

template<typename T>
AS_API constexpr vec<T, 3> mat4_basis_y(const mat<T, 4>& m)
{
  return vec3_from_vec4(mat4_dimension1(m));
}

template<typename T>
AS_API constexpr vec<T, 3> mat4_basis_z(const mat<T, 4>& m)
{
  return vec3_from_vec4(mat4_dimension2(m));
}

template<typename T>
AS_API constexpr vec<T, 3> mat4_translation(const mat<T, 4>& m)
{
  return vec3_from_vec4(mat4_dimension3(m));
}

template<typename T>
AS_API constexpr void mat4_basis_x(mat<T, 4>& m, const vec<T, 3>& basis)
{
  mat4_dimension0(m, vec<T, 4>(basis));
}

template<typename T>
AS_API constexpr void mat4_basis_y(mat<T, 4>& m, const vec<T, 3>& basis)
{
  mat4_dimension1(m, vec<T, 4>(basis));
}

template<typename T>
AS_API constexpr void mat4_basis_z(mat<T, 4>& m, const vec<T, 3>& basis)
{
  mat4_dimension2(m, vec<T, 4>(basis));
}

template<typename T>
AS_API constexpr void mat4_translation(
  mat<T, 4>& m, const vec<T, 3>& translation)
{
  mat4_dimension3(m, vec<T, 4>(translation, T(1.0)));
}

template<typename T>
AS_API mat<T, 4> mat4_from_ptr(const T* data)
{
  return mat_from_ptr<T, 4>(data);
}

template<typename T>
AS_API mat<T, 4> mat4_from_arr(const T (&data)[16])
{
  return mat_from_arr<T, 4>(data);
}

template<typename T>
AS_API constexpr mat<T, 4> mat4_from_vec3(const vec<T, 3>& translation)
{
  return {mat<T, 3>::identity(), translation};
}

template<typename T>
AS_API constexpr mat<T, 4> mat4_from_mat3(const mat<T, 3>& rotation)
{
  return {rotation, vec<T, 3>::zero()};
}

template<typename T>
AS_API constexpr mat<T, 4> mat4_from_mat3_vec3(
  const mat<T, 3>& rotation, const vec<T, 3>& translation)
{
  return {rotation, translation};
}

AS_API constexpr mat4 mat4_from_affine(const affine& a)
{
  return mat4_from_mat3_vec3(a.rotation, a.translation);
}

template<typename T>
AS_API constexpr mat<T, 4> mat4_shear_x(const T y, const T z)
{
  // clang-format off
  return {T(1.0), y,      z,      T(0.0),
          T(0.0), T(1.0), T(0.0), T(0.0),
          T(0.0), T(0.0), T(1.0), T(0.0),
          T(0.0), T(0.0), T(0.0), T(1.0)};
  // clang-format on
}

template<typename T>
AS_API constexpr mat<T, 4> mat4_shear_y(const T x, const T z)
{
  // clang-format off
  return {T(1.0), T(0.0), T(0.0), T(0.0),
          x,      T(1.0), z,      T(0.0),
          T(0.0), T(0.0), T(1.0), T(0.0),
          T(0.0), T(0.0), T(0.0), T(1.0)};
  // clang-format on
}

template<typename T>
AS_API constexpr mat<T, 4> mat4_shear_z(const T x, const T y)
{
  // clang-format off
  return {T(1.0), T(0.0), T(0.0), T(0.0),
          T(0.0), T(1.0), T(0.0), T(0.0),
          x,      y,      T(1.0), T(0.0),
          T(0.0), T(0.0), T(0.0), T(1.0)};
  // clang-format on
}

AS_API constexpr real quat_dot(const quat& lhs, const quat& rhs)
{
  return lhs.w * rhs.w + lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

AS_API constexpr real quat_length_sq(const quat& q)
{
  return quat_dot(q, q);
}

AS_API inline real quat_length(const quat& q)
{
  return std::sqrt(quat_length_sq(q));
}

AS_API inline quat quat_normalize(const quat& q)
{
  return q / quat_length(q);
}

AS_API constexpr quat quat_conjugate(const quat& q)
{
  return {q.w, -q.x, -q.y, -q.z};
}

AS_API inline quat quat_inverse(const quat& q)
{
  return quat_conjugate(q) / quat_length_sq(q);
}

AS_API inline vec3 quat_rotate(const quat& q, const vec3& v)
{
  const quat quat_result = q * quat{0.0_r, v.x, v.y, v.z} * quat_conjugate(q);
  return {quat_result.x, quat_result.y, quat_result.z};
}

AS_API inline quat quat_rotation_axis(const vec3& axis, const real radians)
{
  return {std::cos(0.5_r * radians), axis * std::sin(0.5_r * radians)};
}

AS_API inline quat quat_rotation_xyz(const real x, const real y, const real z)
{
  return quat{std::cos(0.5_r * z), 0.0_r, 0.0_r, std::sin(0.5_r * z)}
       * quat{std::cos(0.5_r * y), 0.0_r, std::sin(0.5_r * y), 0.0_r}
       * quat{std::cos(0.5_r * x), std::sin(0.5_r * x), 0.0_r, 0.0_r};
}

AS_API inline quat quat_rotation_zxy(const real x, const real y, const real z)
{
  return quat{std::cos(0.5_r * y), 0.0_r, std::sin(0.5_r * y), 0.0_r}
       * quat{std::cos(0.5_r * x), std::sin(0.5_r * x), 0.0_r, 0.0_r}
       * quat{std::cos(0.5_r * z), 0.0_r, 0.0_r, std::sin(0.5_r * z)};
}

AS_API inline quat quat_nlerp(const quat& q0, const quat& q1, const real t)
{
    return mix(q0, q1, t);
}

AS_API inline quat quat_slerp(const quat& q0, const quat& q1, const real t)
{
  const real dot = clamp(quat_dot(q0, q1), -1.0_r, 1.0_r);
  if (dot > 0.995_r) {
      return quat_nlerp(q0, q1, t);
  }
  const quat q1_s = dot < 0.0_r ? q1 * -1.0_r : q1;
  const real theta = std::acos(dot);
  const real sin_theta = std::sin(theta);
  return (q0 * std::sin((1.0_r - t) * theta) + q1_s * std::sin(t * theta))
          / sin_theta;
}

// ref: euclidean space
// http://www.euclideanspace.com/maths/geometry/rotations/conversions/matrixToQuaternion/index.htm
AS_API inline quat quat_from_mat3(const mat3& m)
{
  quat q;

  const auto rc = [](const index r, const index c) {
    return c * mat3::dim() + r;
  };

  const real trace = m[rc(0, 0)] + m[rc(1, 1)] + m[rc(2, 2)];

  if (trace > 0.0_r) {
    real s = 0.5_r / std::sqrt(trace + 1.0_r);
    q.w = 0.25_r / s;
    q.x = (m[rc(2, 1)] - m[rc(1, 2)]) * s;
    q.y = (m[rc(0, 2)] - m[rc(2, 0)]) * s;
    q.z = (m[rc(1, 0)] - m[rc(0, 1)]) * s;
  } else {
    if (m[rc(0, 0)] > m[rc(1, 1)] && m[rc(0, 0)] > m[rc(2, 2)]) {
      real s =
        2.0_r * std::sqrt(1.0_r + m[rc(0, 0)] - m[rc(1, 1)] - m[rc(2, 2)]);
      q.w = (m[rc(2, 1)] - m[rc(1, 2)]) / s;
      q.x = 0.25_r * s;
      q.y = (m[rc(0, 1)] + m[rc(1, 0)]) / s;
      q.z = (m[rc(0, 2)] + m[rc(2, 0)]) / s;
    } else if (m[rc(1, 1)] > m[rc(2, 2)]) {
      real s =
        2.0_r * std::sqrt(1.0_r + m[rc(1, 1)] - m[rc(0, 0)] - m[rc(2, 2)]);
      q.w = (m[rc(0, 2)] - m[rc(2, 0)]) / s;
      q.x = (m[rc(0, 1)] + m[rc(1, 0)]) / s;
      q.y = 0.25_r * s;
      q.z = (m[rc(1, 2)] + m[rc(2, 1)]) / s;
    } else {
      real s =
        2.0_r * std::sqrt(1.0_r + m[rc(2, 2)] - m[rc(0, 0)] - m[rc(1, 1)]);
      q.w = (m[rc(1, 0)] - m[rc(0, 1)]) / s;
      q.x = (m[rc(0, 2)] + m[rc(2, 0)]) / s;
      q.y = (m[rc(1, 2)] + m[rc(2, 1)]) / s;
      q.z = 0.25_r * s;
    }
  }

  return q;
}

AS_API inline void affine_to_arr(const affine& a, real (&data)[12])
{
  for (index i = 0; i < a.rotation.size(); ++i) {
    data[i] = a.rotation[i];
  }

  for (index i = 0; i < a.translation.size(); ++i) {
    data[a.rotation.size() + i] = a.translation[i];
  }
}

AS_API inline affine affine_from_arr(const real (&data)[12])
{
  return affine_from_ptr(data);
}

AS_API inline affine affine_from_ptr(const real* data)
{
  affine result;

  constexpr auto mat3_size = result.rotation.size();
  for (index i = 0; i < mat3_size; ++i) {
    result.rotation[i] = data[i];
  }

  constexpr auto vec3_size = result.translation.size();
  for (index i = 0; i < vec3_size; ++i) {
    result.translation[i] = data[mat3_size + i];
  }

  return result;
}

AS_API inline affine affine_from_mat4(const mat4& m)
{
  return affine(mat3_from_mat4(m), mat4_translation(m));
}

AS_API inline affine affine_from_mat3(const mat3& m)
{
  return affine(m, vec3::zero());
}

AS_API inline affine affine_from_mat3_vec3(const mat3& m, const vec3& v)
{
  return affine(m, v);
}

AS_API inline affine affine_from_vec3(const vec3& v)
{
  return affine(v);
}

AS_API inline affine affine_mul(const affine& lhs, const affine& rhs)
{
  return affine(
    mat_mul(lhs.rotation, rhs.rotation),
    affine_transform_pos(rhs, lhs.translation));
}

AS_API inline affine affine_inverse(const affine& a)
{
  const mat3 inv_rot = mat_transpose(a.rotation);
  const vec3 inv_pos = affine_transform_pos(affine(inv_rot), -a.translation);
  return affine(inv_rot, inv_pos);
}

AS_API inline vec3 affine_transform_dir(const affine& a, const vec3& direction)
{
#ifdef AS_COL_MAJOR
  return a.rotation * direction;
#elif defined AS_ROW_MAJOR
  return direction * a.rotation;
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

AS_API inline vec3 affine_transform_pos(const affine& a, const vec3& position)
{
#ifdef AS_COL_MAJOR
  return a.rotation * position + a.translation;
#elif defined AS_ROW_MAJOR
  return position * a.rotation + a.translation;
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

AS_API inline vec3 affine_inv_transform_dir(
  const affine& a, const vec3& direction)
{
  const mat3 inv_rotation = mat_inverse(a.rotation);
#ifdef AS_COL_MAJOR
  return inv_rotation * direction;
#elif defined AS_ROW_MAJOR
  return direction * inv_rotation;
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

AS_API inline vec3 affine_inv_transform_pos(
  const affine& a, const vec3& position)
{
  const mat3 inv_rotation = mat_inverse(a.rotation);
#ifdef AS_COL_MAJOR
  return inv_rotation * (position - a.translation);
#elif defined AS_ROW_MAJOR
  return (position - a.translation) * inv_rotation;
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

} // namespace as
