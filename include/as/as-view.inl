namespace as
{

AS_API inline mat4 perspective_gl_rh(
  const real fovy, const real aspect, const real n, const real f)
{
  const real e = 1.0_r / std::tan(fovy * 0.5_r);

  // clang-format off
  return {e / aspect, 0.0_r, 0.0_r,                     0.0_r,
          0.0_r,      e,     0.0_r,                     0.0_r,
          0.0_r,      0.0_r, (f + n) / (n - f),        -1.0_r,
          0.0_r,      0.0_r, (2.0_r * f * n) / (n - f), 0.0_r};
  // clang-format on
}

AS_API inline mat4 perspective_gl_lh(
  const real fovy, const real aspect, const real n, const real f)
{
  const real e = 1.0_r / std::tan(fovy * 0.5_r);

  // clang-format off
  return {e / aspect, 0.0_r, 0.0_r,                     0.0_r,
          0.0_r,      e,     0.0_r,                     0.0_r,
          0.0_r,      0.0_r, (f + n) / (f - n),        1.0_r,
          0.0_r,      0.0_r, (2.0_r * f * n) / (n - f), 0.0_r};
  // clang-format on
}

AS_API inline mat4 perspective_d3d_rh(
  const real fovy, const real aspect, const real n, const real f)
{
  const real e = 1.0_r / std::tan(fovy * 0.5_r);

  // clang-format off
  return {e / aspect, 0.0_r, 0.0_r,             0.0_r,
          0.0_r,      e,     0.0_r,             0.0_r,
          0.0_r,      0.0_r, f / (n - f),      -1.0_r,
          0.0_r,      0.0_r, (f * n) / (n - f), 0.0_r};
  // clang-format on
}

AS_API inline mat4 perspective_d3d_lh(
  const real fovy, const real aspect, const real n, const real f)
{
  const real e = 1.0_r / std::tan(fovy * 0.5_r);

  // clang-format off
  return {e / aspect, 0.0_r, 0.0_r,             0.0_r,
          0.0_r,      e,     0.0_r,             0.0_r,
          0.0_r,      0.0_r, f / (f - n),      1.0_r,
          0.0_r,      0.0_r, (f * n) / (n - f), 0.0_r};
  // clang-format on
}

// clang-format off
// vulkan clip space has inverted Y and half z
constexpr mat4 vulkan_clip {1.0_r, 0.0_r,  0.0_r, 0.0_r,
                            0.0_r, -1.0_r, 0.0_r, 0.0_r,
                            0.0_r, 0.0_r,  0.5_r, 0.0_r,
                            0.0_r, 0.0_r,  0.5_r, 1.0_r};
// clang-format on

AS_API inline mat4 perspective_vulkan_rh(
  const real fovy, const real aspect, const real n, const real f)
{
  return as::mat_mul(perspective_gl_rh(fovy, aspect, n, f), vulkan_clip);
}

AS_API inline mat4 perspective_vulkan_lh(
  const real fovy, const real aspect, const real n, const real f)
{
  return as::mat_mul(perspective_gl_lh(fovy, aspect, n, f), vulkan_clip);
}

AS_API inline mat4 reverse_z(const mat4& perspective_projection)
{
  // clang-format off
  constexpr mat4 reverse_z {1.0_r, 0.0_r, 0.0_r,  0.0_r,
                            0.0_r, 1.0_r, 0.0_r,  0.0_r,
                            0.0_r, 0.0_r, -1.0_r, 0.0_r,
                            0.0_r, 0.0_r, 1.0_r,  1.0_r};
  // clang-format on
  return as::mat_mul(perspective_projection, reverse_z);
}

AS_API inline mat4 normalize_unit_range(const mat4& perspective_projection)
{
    // clang-format off
    constexpr mat4 normalize_range {1.0_r, 0.0_r, 0.0_r, 0.0_r,
                                    0.0_r, 1.0_r, 0.0_r, 0.0_r,
                                    0.0_r, 0.0_r, 0.5_r, 0.0_r,
                                    0.0_r, 0.0_r, 0.5_r, 1.0_r};
    // clang-format on
    return as::mat_mul(perspective_projection, normalize_range);
}

AS_API constexpr mat4 ortho_gl_rh(
  const real l, const real r, const real b, const real t, const real n,
  const real f)
{
  const real x = 1.0_r / (r - l);
  const real y = 1.0_r / (t - b);
  const real z = 1.0_r / (f - n);

  // clang-format off
  return {2.0_r * x,    0.0_r,        0.0_r,        0.0_r,
          0.0_r,        2.0_r * y,    0.0_r,        0.0_r,
          0.0_r,        0.0_r,        -2.0_r * z,   0.0_r,
          -(l + r) * x, -(b + t) * y, -(n + f) * z, 1.0_r};
  // clang-format on
}

AS_API constexpr mat4 ortho_gl_lh(
  const real l, const real r, const real b, const real t, const real n,
  const real f)
{
  const real x = 1.0_r / (r - l);
  const real y = 1.0_r / (t - b);
  const real z = 1.0_r / (f - n);

  // clang-format off
  return {2.0_r * x,    0.0_r,        0.0_r,        0.0_r,
          0.0_r,        2.0_r * y,    0.0_r,        0.0_r,
          0.0_r,        0.0_r,        2.0_r * z,    0.0_r,
          -(l + r) * x, -(b + t) * y, -(n + f) * z, 1.0_r};
  // clang-format on
}

AS_API constexpr mat4 ortho_d3d_rh(
  const real l, const real r, const real b, const real t, const real n,
  const real f)
{
  const real x = 1.0_r / (r - l);
  const real y = 1.0_r / (t - b);
  const real z = 1.0_r / (f - n);

  // clang-format off
  return {2.0_r * x,    0.0_r,        0.0_r,  0.0_r,
          0.0_r,        2.0_r * y,    0.0_r,  0.0_r,
          0.0_r,        0.0_r,        -z,     0.0_r,
          -(l + r) * x, -(b + t) * y, -n * z, 1.0_r};
  // clang-format on
}

AS_API constexpr mat4 ortho_d3d_lh(
  const real l, const real r, const real b, const real t, const real n,
  const real f)
{
  const real x = 1.0_r / (r - l);
  const real y = 1.0_r / (t - b);
  const real z = 1.0_r / (f - n);

  // clang-format off
  return {2.0_r * x,    0.0_r,        0.0_r,  0.0_r,
          0.0_r,        2.0_r * y,    0.0_r,  0.0_r,
          0.0_r,        0.0_r,        z,      0.0_r,
          -(l + r) * x, -(b + t) * y, -n * z, 1.0_r};
  // clang-format on
}

AS_API inline mat4 ortho_vulkan_rh(
  real l, real r, real b, real t, real n, real f)
{
  return as::mat_mul(ortho_gl_rh(l, r, b, t, n, f), vulkan_clip);
}

AS_API inline mat4 ortho_vulkan_lh(
  real l, real r, real b, real t, real n, real f)
{
  return as::mat_mul(ortho_gl_lh(l, r, b, t, n, f), vulkan_clip);
}

AS_API inline vec2i world_to_screen(
  const vec3& world_position, const mat4& projection, const affine& view,
  const vec2i& screen_dimension)
{
  const vec4 clip = mat_mul(
    vec4_from_vec3(world_position, 1.0_r),
    mat_mul(mat4_from_affine(view), projection));
  const vec3 ndc = vec3_from_vec4(clip / clip.w);
  const vec2 screen = (vec2_from_vec3(ndc) + vec2::one()) * 0.5_r;
  return vec2i(
    vec2i::value_type(
      std::round(screen.x * vec2::value_type(screen_dimension.x))),
    vec2i::value_type(
      std::round((1.0_r - screen.y) * vec2::value_type(screen_dimension.y))));
}

AS_API inline vec3 screen_to_world(
  const vec2i& screen_position, const mat4& projection, const affine& view,
  const vec2i& screen_dimension)
{
  const vec2 normalized_screen =
    vec2_from_ints(screen_position.x, screen_dimension.y - screen_position.y)
    / vec2_from_vec2i(screen_dimension);
  const vec2 ndc = (normalized_screen * 2.0_r) - vec2::one();
  vec4 world_position = mat_mul(
    vec4(ndc.x, ndc.y, -1.0_r, 1.0_r),
    mat_mul(mat_inverse(projection), mat4_from_affine(affine_inverse(view))));
  world_position /= world_position.w;
  return vec3_from_vec4(world_position);
}

AS_API constexpr vec2 vec2_from_ints(const int32_t x, const int32_t y)
{
  return {vec2::value_type(x), vec2::value_type(y)};
}

AS_API constexpr vec2 vec2_from_vec2i(const as::vec2i& v)
{
  return vec2_from_ints(v.x, v.y);
}

AS_API constexpr vec2i vec2i_from_reals(const real x, const real y)
{
  return {vec2i::value_type(x), vec2i::value_type(y)};
}

AS_API constexpr vec2i vec2i_from_vec2(const vec2& v)
{
  return vec2i_from_reals(v.x, v.y);
}

} // namespace as
