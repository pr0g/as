namespace as
{

namespace view
{

// openGL default
AS_API inline mat4_t perspective_gl_rh(
    const real_t fovy, const real_t aspect, const real_t n, const real_t f)
{
    const real_t e = 1.0_r / std::tan(fovy * 0.5_r);

    // clang-format off
    return {
        e / aspect, 0.0_r,  0.0_r,                        0.0_r,
        0.0_r,      e,      0.0_r,                        0.0_r,
        0.0_r,      0.0_r,  -((f + n) / (f - n)),         -1.0_r,
        0.0_r,      0.0_r,  -((2.0_r * f * n) / (f - n)), 0.0_r
    };
    // clang-format on
}

AS_API inline mat4_t perspective_gl_lh(
    const real_t fovy, const real_t aspect, const real_t n, const real_t f)
{
    const real_t e = 1.0_r / std::tan(fovy * 0.5_r);

    // clang-format off
    return {
        e / aspect, 0.0_r, 0.0_r,                        0.0_r,
        0.0_r,      e,     0.0_r,                        0.0_r,
        0.0_r,      0.0_r, ((f + n) / (f - n)),          1.0_r,
        0.0_r,      0.0_r, -((2.0_r * f * n) / (f - n)), 0.0_r
    };
    // clang-format on
}

AS_API inline mat4_t perspective_d3d_rh(
    const real_t fovy, const real_t aspect, const real_t n, const real_t f)
{
    const real_t e = 1.0_r / std::tan(fovy * 0.5_r);

    // clang-format off
    return {
        e / aspect, 0.0_r,  0.0_r,                0.0_r,
        0.0_r,      e,      0.0_r,                0.0_r,
        0.0_r,      0.0_r,  -f / (f - n),         -1.0_r,
        0.0_r,      0.0_r,  -((f * n) / (f - n)), 0.0_r
    };
    // clang-format on
}

AS_API inline mat4_t perspective_d3d_lh(
    const real_t fovy, const real_t aspect, const real_t n, const real_t f)
{
    const real_t e = 1.0_r / std::tan(fovy * 0.5_r);

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
constexpr mat4_t vulkan_clip{
    1.0_r, 0.0_r,  0.0_r, 0.0_r,
    0.0_r, -1.0_r, 0.0_r, 0.0_r,
    0.0_r, 0.0_r,  0.5_r, 0.0_r,
    0.0_r, 0.0_r,  0.5_r, 1.0_r
};
// clang-format on

// vulkan default
AS_API inline mat4_t perspective_vulkan_rh(
    const real_t fovy, const real_t aspect, const real_t n, const real_t f)
{
    return mat::mul(perspective_gl_rh(fovy, aspect, n, f), vulkan_clip);
}

AS_API inline mat4_t perspective_vulkan_lh(
    const real_t fovy, const real_t aspect, const real_t n, const real_t f)
{
    return mat::mul(perspective_gl_lh(fovy, aspect, n, f), vulkan_clip);
}

AS_API constexpr mat4_t ortho_gl_rh(
    const real_t l, const real_t r, const real_t b, const real_t t,
    const real_t n, const real_t f)
{
    const real_t x = 1.0_r / (r - l);
    const real_t y = 1.0_r / (t - b);
    const real_t z = 1.0_r / (f - n);

    // clang-format off
    return {
        2.0_r * x,    0.0_r,        0.0_r,        0.0_r,
        0.0_r,        2.0_r * y,    0.0_r,        0.0_r,
        0.0_r,        0.0_r,        -2.0_r * z,   0.0_r,
        -(l + r) * x, -(b + t) * y, -(n + f) * z, 1.0_r
    };
    // clang-format on
}

AS_API constexpr mat4_t ortho_gl_lh(
    const real_t l, const real_t r, const real_t b, const real_t t,
    const real_t n, const real_t f)
{
    const real_t x = 1.0_r / (r - l);
    const real_t y = 1.0_r / (t - b);
    const real_t z = 1.0_r / (f - n);

    // clang-format off
    return {
        2.0_r * x,    0.0_r,        0.0_r,        0.0_r,
        0.0_r,        2.0_r * y,    0.0_r,        0.0_r,
        0.0_r,        0.0_r,        2.0_r * z,    0.0_r,
        -(l + r) * x, -(b + t) * y, -(n + f) * z, 1.0_r
    };
    // clang-format on
}

AS_API constexpr mat4_t ortho_d3d_rh(
    const real_t l, const real_t r, const real_t b, const real_t t,
    const real_t n, const real_t f)
{
    const real_t x = 1.0_r / (r - l);
    const real_t y = 1.0_r / (t - b);
    const real_t z = 1.0_r / (f - n);

    // clang-format off
    return {
        2.0_r * x,    0.0_r,        0.0_r,  0.0_r,
        0.0_r,        2.0_r * y,    0.0_r,  0.0_r,
        0.0_r,        0.0_r,        -z,     0.0_r,
        -(l + r) * x, -(b + t) * y, -n * z, 1.0_r
    };
    // clang-format on
}

AS_API constexpr mat4_t ortho_d3d_lh(
    const real_t l, const real_t r, const real_t b, const real_t t,
    const real_t n, const real_t f)
{
    const real_t x = 1.0_r / (r - l);
    const real_t y = 1.0_r / (t - b);
    const real_t z = 1.0_r / (f - n);

    // clang-format off
    return {
        2.0_r * x,    0.0_r,        0.0_r,  0.0_r,
        0.0_r,        2.0_r * y,    0.0_r,  0.0_r,
        0.0_r,        0.0_r,        z,      0.0_r,
        -(l + r) * x, -(b + t) * y, -n * z, 1.0_r
    };
    // clang-format on
}

AS_API inline mat4_t ortho_vulkan_rh(
    real_t l, real_t r, real_t b, real_t t, real_t n, real_t f)
{
    return mat::mul(ortho_gl_rh(l, r, b, t, n, f), vulkan_clip);
}

AS_API inline mat4_t ortho_vulkan_lh(
    real_t l, real_t r, real_t b, real_t t, real_t n, real_t f)
{
    return mat::mul(ortho_gl_lh(l, r, b, t, n, f), vulkan_clip);
}

} // namespace view

} // namespace as
