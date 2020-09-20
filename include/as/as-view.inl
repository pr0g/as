namespace as
{

// openGL default
AS_API inline mat4 perspective_gl_rh(
  const real fovy, const real aspect, const real n, const real f)
{
  const real e = 1.0_r / std::tan(fovy * 0.5_r);

  // clang-format off
    return {
        e / aspect, 0.0_r,  0.0_r,                        0.0_r,
        0.0_r,      e,      0.0_r,                        0.0_r,
        0.0_r,      0.0_r,  -((f + n) / (f - n)),         -1.0_r,
        0.0_r,      0.0_r,  -((2.0_r * f * n) / (f - n)), 0.0_r
    };
  // clang-format on
}

AS_API inline mat4 perspective_gl_lh(
  const real fovy, const real aspect, const real n, const real f)
{
  const real e = 1.0_r / std::tan(fovy * 0.5_r);

  // clang-format off
    return {
        e / aspect, 0.0_r, 0.0_r,                        0.0_r,
        0.0_r,      e,     0.0_r,                        0.0_r,
        0.0_r,      0.0_r, ((f + n) / (f - n)),          1.0_r,
        0.0_r,      0.0_r, -((2.0_r * f * n) / (f - n)), 0.0_r
    };
  // clang-format on
}

AS_API inline mat4 perspective_d3d_rh(
  const real fovy, const real aspect, const real n, const real f)
{
  const real e = 1.0_r / std::tan(fovy * 0.5_r);

  // clang-format off
    return {
        e / aspect, 0.0_r,  0.0_r,                0.0_r,
        0.0_r,      e,      0.0_r,                0.0_r,
        0.0_r,      0.0_r,  -f / (f - n),         -1.0_r,
        0.0_r,      0.0_r,  -((f * n) / (f - n)), 0.0_r
    };
  // clang-format on
}

AS_API inline mat4 perspective_d3d_lh(
  const real fovy, const real aspect, const real n, const real f)
{
  const real e = 1.0_r / std::tan(fovy * 0.5_r);

  // clang-format off
    return {
        e / aspect, 0.0_r,  0.0_r,                0.0_r,
        0.0_r,      e,      0.0_r,                0.0_r,
        0.0_r,      0.0_r,  f / (f - n),          1.0_r,
        0.0_r,      0.0_r,  -((f * n) / (f - n)), 0.0_r
    };
  // clang-format on
}

// clang-format off
// vulkan clip space has inverted Y and half z
constexpr mat4 vulkan_clip{
    1.0_r, 0.0_r,  0.0_r, 0.0_r,
    0.0_r, -1.0_r, 0.0_r, 0.0_r,
    0.0_r, 0.0_r,  0.5_r, 0.0_r,
    0.0_r, 0.0_r,  0.5_r, 1.0_r
};
// clang-format on

// vulkan default
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

AS_API constexpr mat4 ortho_gl_rh(
  const real l, const real r, const real b, const real t, const real n,
  const real f)
{
  const real x = 1.0_r / (r - l);
  const real y = 1.0_r / (t - b);
  const real z = 1.0_r / (f - n);

  // clang-format off
    return {
        2.0_r * x,    0.0_r,        0.0_r,        0.0_r,
        0.0_r,        2.0_r * y,    0.0_r,        0.0_r,
        0.0_r,        0.0_r,        -2.0_r * z,   0.0_r,
        -(l + r) * x, -(b + t) * y, -(n + f) * z, 1.0_r
    };
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
    return {
        2.0_r * x,    0.0_r,        0.0_r,        0.0_r,
        0.0_r,        2.0_r * y,    0.0_r,        0.0_r,
        0.0_r,        0.0_r,        2.0_r * z,    0.0_r,
        -(l + r) * x, -(b + t) * y, -(n + f) * z, 1.0_r
    };
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
    return {
        2.0_r * x,    0.0_r,        0.0_r,  0.0_r,
        0.0_r,        2.0_r * y,    0.0_r,  0.0_r,
        0.0_r,        0.0_r,        -z,     0.0_r,
        -(l + r) * x, -(b + t) * y, -n * z, 1.0_r
    };
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
    return {
        2.0_r * x,    0.0_r,        0.0_r,  0.0_r,
        0.0_r,        2.0_r * y,    0.0_r,  0.0_r,
        0.0_r,        0.0_r,        z,      0.0_r,
        -(l + r) * x, -(b + t) * y, -n * z, 1.0_r
    };
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

} // namespace as
