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
AS_API constexpr real vec_dot(const vec<T, d>& lhs, const vec<T, d>& rhs)
{
  auto result = real(0.0);
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
AS_API constexpr real vec_length_sq(const vec<T, d>& v)
{
  return vec_dot(v, v);
}

template<typename T, index d>
AS_API real vec_length(const vec<T, d>& v)
{
  return std::sqrt(vec_length_sq(v));
}

template<typename T, index d>
AS_API real vec_distance(const vec<T, d>& lhs, const vec<T, d>& rhs)
{
  return vec_length(rhs - lhs);
}

template<typename T, index d>
AS_API vec<real, d> vec_normalize(const vec<T, d>& v)
{
  return v / vec_length(v);
}

template<typename T, index d>
AS_API std::tuple<vec<real, d>, real> vec_normalize_and_length(
  const vec<T, d>& v)
{
  const real len = vec_length(v);
  return std::make_tuple(v / len, len);
}

template<typename T, index d>
AS_API bool vec_near(
  const vec<T, d>& lhs, const vec<T, d>& rhs,
  const real max_diff /*= std::numeric_limits<float>::epsilon()*/,
  const real max_rel_diff /*= std::numeric_limits<float>::epsilon()*/)
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
AS_API vec<T, d> vec_min(const vec<T, d>& lhs, const T rhs)
{
  vec<T, d> result;
  for (index i = 0; i < d; ++i) {
    result[i] = min(lhs[i], rhs);
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
AS_API vec<T, d> vec_max(const vec<T, d>& lhs, const T rhs)
{
  vec<T, d> result;
  for (index i = 0; i < d; ++i) {
    result[i] = max(lhs[i], rhs);
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
    result[i] = abs(v[i]);
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
  const vec<T, d>& begin, const vec<T, d>& end, const real t)
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

template<typename T, index d>
AS_API vec<T, d> vec_radians(const vec<T, d>& degrees)
{
  vec<T, d> result;
  for (index i = 0; i < d; ++i) {
    result[i] = radians(degrees[i]);
  }
  return result;
}

template<typename T, index d>
AS_API vec<T, d> vec_degrees(const vec<T, d>& radians)
{
  vec<T, d> result;
  for (index i = 0; i < d; ++i) {
    result[i] = degrees(radians[i]);
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
AS_API constexpr vec<T, 2> vec2_orthogonal_cw(const vec<T, 2>& v)
{
  return {v.y, -v.x};
}

template<typename T>
AS_API constexpr vec<T, 2> vec2_orthogonal_ccw(const vec<T, 2>& v)
{
  return {-v.y, v.x};
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
      return vec<T, 3>(T(0.0), -u.z, u.y);
    }
    if (y <= x && y <= z) {
      return vec<T, 3>(-u.z, T(0.0), u.x);
    }
    // z <= x && z <= y
    return vec<T, 3>(-u.y, u.x, T(0.0));
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
  const real max_diff /*= std::numeric_limits<float>::epsilon()*/,
  const real max_rel_diff /*= std::numeric_limits<float>::epsilon()*/)
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
  auto result = T(0.0);
  auto current_sign = T(1.0);
  for (index i = 0; i < d; ++i) {
    const T minor_det =
      determinant_impl(sub_matrix(m, i, 0), int2type<I - 1>{});
    result += m[i] * minor_det * current_sign;
    current_sign *= T(-1.0);
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
  auto outer_sign = T(1.0);
  for (index c = 0; c < d; ++c) {
    auto inner_sign = outer_sign;
    for (index r = 0; r < d; ++r) {
      const T minor_det =
        determinant_impl<T>(internal::sub_matrix(m, r, c), int2type<d - 1>{});
      result[c * d + r] = minor_det * inner_sign;
      inner_sign *= T(-1.0);
    }
    outer_sign *= T(-1.0);
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

template<typename T>
AS_API constexpr mat<T, 3> mat3_from_affine(const affine_t<T>& a)
{
  return a.rotation;
}

template<typename T>
AS_API mat<T, 3> mat3_rotation_axis(const vec<T, 3>& axis, const T radians)
{
  const T cos_radians = std::cos(radians);
  const T sin_radians = std::sin(radians);
  const T inv_cos_radians = T(1.0) - cos_radians;
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

template<typename T>
AS_API mat<T, 3> mat3_rotation_xyz(const T x, const T y, const T z)
{
  const T cos_x = std::cos(x);
  const T cos_y = std::cos(y);
  const T cos_z = std::cos(z);
  const T sin_x = std::sin(x);
  const T sin_y = std::sin(y);
  const T sin_z = std::sin(z);
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

template<typename T>
AS_API mat<T, 3> mat3_rotation_xyz(const vec<T, 3>& xyz)
{
  return mat3_rotation_xyz(xyz.x, xyz.y, xyz.z);
}

template<typename T>
AS_API mat<T, 3> mat3_rotation_zxy(const T x, const T y, const T z)
{
  const T cos_x = std::cos(x);
  const T cos_y = std::cos(y);
  const T cos_z = std::cos(z);
  const T sin_x = std::sin(x);
  const T sin_y = std::sin(y);
  const T sin_z = std::sin(z);
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

template<typename T>
AS_API mat<T, 3> mat3_rotation_zxy(const vec<T, 3>& xyz)
{
  return mat3_rotation_zxy(xyz.x, xyz.y, xyz.z);
}

template<typename T>
AS_API mat<T, 3> mat3_rotation_x(const T radians)
{
  const T cos_radians = std::cos(radians);
  const T sin_radians = std::sin(radians);
  // clang-format off
  return {T(1.0), T(0.0),       T(0.0),
          T(0.0), cos_radians,  sin_radians,
          T(0.0), -sin_radians, cos_radians};
  // clang-format on
}

template<typename T>
AS_API mat<T, 3> mat3_rotation_y(const T radians)
{
  const T cos_radians = std::cos(radians);
  const T sin_radians = std::sin(radians);
  // clang-format off
  return {cos_radians, T(0.0), -sin_radians,
          T(0.0),      T(1.0), T(0.0),
          sin_radians, T(0.0), cos_radians};
  // clang-format on
}

template<typename T>
AS_API mat<T, 3> mat3_rotation_z(const T radians)
{
  const T cos_radians = std::cos(radians);
  const T sin_radians = std::sin(radians);
  // clang-format off
  return {cos_radians,  sin_radians, T(0.0),
          -sin_radians, cos_radians, T(0.0),
          T(0.0),       T(0.0),      T(1.0)};
  // clang-format on
}

template<typename T>
AS_API constexpr mat<T, 3> mat3_scale(const T scale)
{
  return mat3_scale(scale, scale, scale);
}

template<typename T>
AS_API constexpr mat<T, 3> mat3_scale(const T x, const T y, const T z)
{
  // clang-format off
  return {x,      T(0.0), T(0.0),
          T(0.0), y,      T(0.0),
          T(0.0), T(0.0), z};
  // clang-format on
}

template<typename T>
AS_API constexpr mat<T, 3> mat3_scale(const vec<T, 3>& scale)
{
  return mat3_scale(scale.x, scale.y, scale.z);
}

// ref: Essential Mathematics for Games & Interactive Applications: A
// Programmers Guide section 5.5.7
template<typename T>
AS_API constexpr mat<T, 3> mat3_from_quat(const quat_t<T>& q)
{
  const T s{T(2.0) / (q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w)};
  const T xs{s * q.x};
  const T ys{s * q.y};
  const T zs{s * q.z};
  const T wx{q.w * xs};
  const T wy{q.w * ys};
  const T wz{q.w * zs};
  const T xx{q.x * xs};
  const T xy{q.x * ys};
  const T xz{q.x * zs};
  const T yy{q.y * ys};
  const T yz{q.y * zs};
  const T zz{q.z * zs};

  return {T(1.0) - (yy + zz), xy + wz, xz - wy, xy - wz,
          T(1.0) - (xx + zz), yz + wx, xz + wy, yz - wx,
          T(1.0) - (xx + yy)};
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

template<typename T>
AS_API constexpr mat<T, 4> mat4_from_affine(const affine_t<T>& a)
{
  return mat4_from_mat3_vec3(a.rotation, a.translation);
}

template<typename T>
AS_API constexpr mat<T, 4> mat4_from_rigid(const rigid_t<T>& r)
{
  return mat4_from_mat3_vec3(mat3_from_quat(r.rotation), r.translation);
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

template<typename T>
AS_API bool quat_near(
  const quat_t<T>& q0, const quat_t<T>& q1,
  const real max_diff /*= std::numeric_limits<float>::epsilon()*/,
  const real max_rel_diff /*= std::numeric_limits<float>::epsilon()*/)
{
  return std::equal(
           begin(q0), end(q0), begin(q1),
           [max_diff, max_rel_diff](const auto& lhs, const auto& rhs) {
             return real_near(lhs, rhs, max_diff, max_rel_diff);
           })
      || std::equal(
           begin(q0), end(q0), begin(q1),
           [max_diff, max_rel_diff](const auto& lhs, const auto& rhs) {
             return real_near(lhs, -rhs, max_diff, max_rel_diff);
           });
}

template<typename T>
AS_API constexpr T quat_dot(const quat_t<T>& lhs, const quat_t<T>& rhs)
{
  return lhs.w * rhs.w + lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

template<typename T>
AS_API constexpr T quat_length_sq(const quat_t<T>& q)
{
  return quat_dot(q, q);
}

template<typename T>
AS_API T quat_length(const quat_t<T>& q)
{
  return std::sqrt(quat_length_sq(q));
}

template<typename T>
AS_API quat_t<T> quat_normalize(const quat_t<T>& q)
{
  return q / quat_length(q);
}

template<typename T>
AS_API constexpr quat_t<T> quat_conjugate(const quat_t<T>& q)
{
  return {q.w, -q.x, -q.y, -q.z};
}

template<typename T>
AS_API quat_t<T> quat_inverse(const quat_t<T>& q)
{
  return quat_conjugate(q) / quat_length_sq(q);
}

template<typename T>
AS_API vec<T, 3> quat_rotate(const quat_t<T>& q, const vec<T, 3>& v)
{
  const quat_t<T> quat_result =
    q * quat_t<T>{T(0.0), v.x, v.y, v.z} * quat_conjugate(q);
  return {quat_result.x, quat_result.y, quat_result.z};
}

template<typename T>
AS_API quat_t<T> quat_rotation_axis(const vec<T, 3>& axis, const T radians)
{
  return quat_normalize(
    quat_t<T>{std::cos(T(0.5) * radians), axis * std::sin(T(0.5) * radians)});
}

template<typename T>
AS_API quat_t<T> quat_rotation_x(const T radians)
{
  return quat_rotation_axis(vec<T, 3>::axis_x(), radians);
}

template<typename T>
AS_API quat_t<T> quat_rotation_y(const T radians)
{
  return quat_rotation_axis(vec<T, 3>::axis_y(), radians);
}

template<typename T>
AS_API quat_t<T> quat_rotation_z(const T radians)
{
  return quat_rotation_axis(vec<T, 3>::axis_z(), radians);
}

template<typename T>
AS_API quat_t<T> quat_rotation_xyz(const T x, const T y, const T z)
{
  return quat_t<T>{std::cos(T(0.5) * z), T(0.0), T(0.0), std::sin(T(0.5) * z)}
       * quat_t<T>{std::cos(T(0.5) * y), T(0.0), std::sin(T(0.5) * y), T(0.0)}
       * quat_t<T>{std::cos(T(0.5) * x), std::sin(T(0.5) * x), T(0.0), T(0.0)};
}

template<typename T>
AS_API quat_t<T> quat_rotation_xyz(const vec<T, 3>& xyz)
{
  return quat_rotation_xyz(xyz.x, xyz.y, xyz.z);
}

template<typename T>
AS_API quat_t<T> quat_rotation_zxy(const T x, const T y, const T z)
{
  return quat_t<T>{std::cos(T(0.5) * y), T(0.0), std::sin(T(0.5) * y), T(0.0)}
       * quat_t<T>{std::cos(T(0.5) * x), std::sin(T(0.5) * x), T(0.0), T(0.0)}
       * quat_t<T>{std::cos(T(0.5) * z), T(0.0), T(0.0), std::sin(T(0.5) * z)};
}

template<typename T>
AS_API quat_t<T> quat_rotation_zxy(const vec<T, 3>& xyz)
{
  return quat_rotation_zxy(xyz.x, xyz.y, xyz.z);
}

template<typename T>
AS_API quat_t<T> quat_nlerp(const quat_t<T>& q0, const quat_t<T>& q1, const T t)
{
  const quat_t<T> q1_s = quat_dot(q0, q1) < T(0.0) ? -q1 : q1;
  return quat_normalize(mix(q0, q1_s, t));
}

template<typename T>
AS_API inline quat_t<T> quat_slerp(
  const quat_t<T>& q0, const quat_t<T>& q1, const T t)
{
  const T dot = clamp(quat_dot(q0, q1), T(-1.0), T(1.0));
  const T abs_dot = std::abs(dot);
  const quat_t<T> q1_s = dot < T(0.0) ? -q1 : q1;
  if (abs_dot > T(0.9995)) {
    return quat_normalize(mix(q0, q1_s, t));
  }
  const T theta = std::acos(abs_dot);
  return (q0 * std::sin((T(1.0) - t) * theta) + q1_s * std::sin(t * theta))
       / std::sin(theta);
}

// ref: euclidean space
// http://www.euclideanspace.com/maths/geometry/rotations/conversions/matrixToQuaternion/index.htm
template<typename T>
AS_API quat_t<T> quat_from_mat3(const mat<T, 3>& m)
{
  quat_t<T> q;
  const auto rc = [](const index r, const index c) {
    return c * mat<T, 3>::dim() + r;
  };

  const T trace = m[rc(0, 0)] + m[rc(1, 1)] + m[rc(2, 2)];
  if (trace > T(0.0)) {
    T s = T(0.5) / std::sqrt(trace + T(1.0));
    q.w = T(0.25) / s;
    q.x = (m[rc(2, 1)] - m[rc(1, 2)]) * s;
    q.y = (m[rc(0, 2)] - m[rc(2, 0)]) * s;
    q.z = (m[rc(1, 0)] - m[rc(0, 1)]) * s;
  } else {
    if (m[rc(0, 0)] > m[rc(1, 1)] && m[rc(0, 0)] > m[rc(2, 2)]) {
      T s =
        T(2.0) * std::sqrt(T(1.0) + m[rc(0, 0)] - m[rc(1, 1)] - m[rc(2, 2)]);
      q.w = (m[rc(2, 1)] - m[rc(1, 2)]) / s;
      q.x = T(0.25) * s;
      q.y = (m[rc(0, 1)] + m[rc(1, 0)]) / s;
      q.z = (m[rc(0, 2)] + m[rc(2, 0)]) / s;
    } else if (m[rc(1, 1)] > m[rc(2, 2)]) {
      T s =
        T(2.0) * std::sqrt(T(1.0) + m[rc(1, 1)] - m[rc(0, 0)] - m[rc(2, 2)]);
      q.w = (m[rc(0, 2)] - m[rc(2, 0)]) / s;
      q.x = (m[rc(0, 1)] + m[rc(1, 0)]) / s;
      q.y = T(0.25) * s;
      q.z = (m[rc(1, 2)] + m[rc(2, 1)]) / s;
    } else {
      T s =
        T(2.0) * std::sqrt(T(1.0) + m[rc(2, 2)] - m[rc(0, 0)] - m[rc(1, 1)]);
      q.w = (m[rc(1, 0)] - m[rc(0, 1)]) / s;
      q.x = (m[rc(0, 2)] + m[rc(2, 0)]) / s;
      q.y = (m[rc(1, 2)] + m[rc(2, 1)]) / s;
      q.z = T(0.25) * s;
    }
  }
  return q;
}

template<typename T>
AS_API void quat_to_arr(const quat_t<T>& q, T (&data)[quat_t<T>::size()])
{
  for (index i = 0; i < q.size(); ++i) {
    data[i] = q[i];
  }
}

template<typename T>
AS_API void affine_to_arr(const affine_t<T>& a, T (&data)[affine_t<T>::size()])
{
  for (index i = 0; i < a.rotation.size(); ++i) {
    data[i] = a.rotation[i];
  }
  for (index i = 0; i < a.translation.size(); ++i) {
    data[a.rotation.size() + i] = a.translation[i];
  }
}

template<typename T>
AS_API affine_t<T> affine_from_arr(const T (&data)[affine_t<T>::size()])
{
  return affine_from_ptr(data);
}

template<typename T>
AS_API affine_t<T> affine_from_ptr(const T* data)
{
  affine_t<T> result;
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

template<typename T>
AS_API affine_t<T> affine_from_mat4(const mat<T, 4>& m)
{
  return affine_t<T>(mat3_from_mat4(m), mat4_translation(m));
}

template<typename T>
AS_API affine_t<T> affine_from_mat3(const mat<T, 3>& m)
{
  return affine_t<T>(m, vec<T, 3>::zero());
}

template<typename T>
AS_API affine_t<T> affine_from_mat3_vec3(const mat<T, 3>& m, const vec<T, 3>& v)
{
  return affine_t<T>(m, v);
}

template<typename T>
AS_API affine_t<T> affine_from_vec3(const vec<T, 3>& v)
{
  return affine_t<T>(v);
}

template<typename T>
AS_API inline affine_t<T> affine_from_rigid(const rigid_t<T>& r)
{
  return affine_t<T>(mat3_from_quat(r.rotation), r.translation);
}

template<typename T>
AS_API affine_t<T> affine_mul(const affine_t<T>& lhs, const affine_t<T>& rhs)
{
  return affine_t<T>(
    mat_mul(lhs.rotation, rhs.rotation),
    affine_transform_pos(rhs, lhs.translation));
}

template<typename T>
AS_API inline affine_t<T> affine_inverse(const affine_t<T>& a)
{
  const mat<T, 3> inv_rot = mat_inverse(a.rotation);
  const vec<T, 3> inv_pos =
    affine_transform_pos(affine_t<T>(inv_rot), -a.translation);
  return affine_t<T>(inv_rot, inv_pos);
}

template<typename T>
AS_API bool affine_near(
  const affine_t<T>& lhs, const affine_t<T>& rhs,
  const real max_diff /*= std::numeric_limits<float>::epsilon()*/,
  const real max_rel_diff /*= std::numeric_limits<float>::epsilon()*/)
{
  return vec_near(lhs.translation, rhs.translation, max_diff, max_rel_diff)
      && mat_near(lhs.rotation, rhs.rotation, max_diff, max_rel_diff);
}

template<typename T>
AS_API vec<T, 3> affine_transform_dir(
  const affine_t<T>& a, const vec<T, 3>& direction)
{
#ifdef AS_COL_MAJOR
  return a.rotation * direction;
#elif defined AS_ROW_MAJOR
  return direction * a.rotation;
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

template<typename T>
AS_API vec<T, 3> affine_transform_pos(
  const affine_t<T>& a, const vec<T, 3>& position)
{
#ifdef AS_COL_MAJOR
  return a.rotation * position + a.translation;
#elif defined AS_ROW_MAJOR
  return position * a.rotation + a.translation;
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

template<typename T>
AS_API vec<T, 3> affine_inv_transform_dir(
  const affine_t<T>& a, const vec<T, 3>& direction)
{
  const mat<T, 3> inv_rotation = mat_inverse(a.rotation);
#ifdef AS_COL_MAJOR
  return inv_rotation * direction;
#elif defined AS_ROW_MAJOR
  return direction * inv_rotation;
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

template<typename T>
AS_API vec<T, 3> affine_inv_transform_pos(
  const affine_t<T>& a, const vec<T, 3>& position)
{
  const mat<T, 3> inv_rotation = mat_inverse(a.rotation);
#ifdef AS_COL_MAJOR
  return inv_rotation * (position - a.translation);
#elif defined AS_ROW_MAJOR
  return (position - a.translation) * inv_rotation;
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

template<typename T>
AS_API inline void rigid_to_arr(
  const rigid_t<T>& r, T (&data)[rigid_t<T>::size()])
{
  for (index i = 0; i < r.rotation.size(); ++i) {
    data[i] = r.rotation[i];
  }
  for (index i = 0; i < r.translation.size(); ++i) {
    data[r.rotation.size() + i] = r.translation[i];
  }
}

template<typename T>
AS_API rigid_t<T> rigid_from_arr(const T (&data)[rigid_t<T>::size()])
{
  return rigid_from_ptr(data);
}

template<typename T>
AS_API rigid_t<T> rigid_from_ptr(const T* data)
{
  rigid_t<T> result;
  constexpr auto quat_size = result.rotation.size();
  for (index i = 0; i < quat_size; ++i) {
    result.rotation[i] = data[i];
  }
  constexpr auto vec3_size = result.translation.size();
  for (index i = 0; i < vec3_size; ++i) {
    result.translation[i] = data[quat_size + i];
  }
  return result;
}

template<typename T>
AS_API rigid_t<T> rigid_from_mat4(const mat<T, 4>& m)
{
  return rigid_t<T>(quat_from_mat3(mat3_from_mat4(m)), mat4_translation(m));
}

template<typename T>
AS_API rigid_t<T> rigid_from_quat(const quat_t<T>& q)
{
  return rigid_t<T>(q);
}

template<typename T>
AS_API rigid_t<T> rigid_from_quat_vec3(const quat_t<T>& q, const vec<T, 3>& v)
{
  return rigid_t<T>(q, v);
}

template<typename T>
AS_API rigid_t<T> rigid_from_vec3(const vec<T, 3>& v)
{
  return rigid_t<T>(v);
}

template<typename T>
AS_API rigid_t<T> rigid_from_affine(const affine_t<T>& a)
{
  return rigid_t<T>(quat_from_mat3(a.rotation), a.translation);
}

template<typename T>
AS_API rigid_t<T> rigid_mul(const rigid_t<T>& lhs, const rigid_t<T>& rhs)
{
  return rigid_t<T>(
    rhs.rotation * lhs.rotation, rigid_transform_pos(rhs, lhs.translation));
}

template<typename T>
AS_API rigid_t<T> rigid_inverse(const rigid_t<T>& r)
{
  const quat_t<T> inv_rot = quat_inverse(quat_normalize(r.rotation));
  const vec<T, 3> inv_pos =
    rigid_transform_pos(rigid_t<T>(inv_rot), -r.translation);
  return rigid_t<T>(inv_rot, inv_pos);
}

template<typename T>
AS_API bool rigid_near(
  const rigid_t<T>& lhs, const rigid_t<T>& rhs,
  const real max_diff /*= std::numeric_limits<float>::epsilon()*/,
  const real max_rel_diff /*= std::numeric_limits<float>::epsilon()*/)
{
  return vec_near(lhs.translation, rhs.translation, max_diff, max_rel_diff)
      && quat_near(lhs.rotation, rhs.rotation, max_diff, max_rel_diff);
}

template<typename T>
AS_API vec<T, 3> rigid_transform_dir(
  const rigid_t<T>& r, const vec<T, 3>& direction)
{
  return quat_rotate(r.rotation, direction);
}

template<typename T>
AS_API vec<T, 3> rigid_transform_pos(
  const rigid_t<T>& r, const vec<T, 3>& position)
{
  return quat_rotate(r.rotation, position) + r.translation;
}

template<typename T>
AS_API vec<T, 3> rigid_inv_transform_dir(
  const rigid_t<T>& r, const vec<T, 3>& direction)
{
  return quat_rotate(quat_inverse(r.rotation), direction);
}

template<typename T>
AS_API vec<T, 3> rigid_inv_transform_pos(
  const rigid_t<T>& r, const vec<T, 3>& position)
{
  return quat_rotate(quat_inverse(r.rotation), position - r.translation);
}

} // namespace as
