namespace as
{

namespace view
{

// openGL default
inline mat44_t perspective_gl_rh(real_t fovy, real_t aspect, real_t n, real_t f)
{
    real_t e = 1.0f / tanr(fovy * 0.5f);

    return {
        e / aspect, 0.0f, 0.0f, 0.0f,
        0.0f, e, 0.0f, 0.0f,
        0.0f, 0.0f, -((f + n) / (f - n)), -1.0f,
        0.0f, 0.0f, -((2.0f * f * n) / (f - n)), 0.0f
    };
}

inline mat44_t perspective_gl_lh(real_t fovy, real_t aspect, real_t n, real_t f)
{
    real_t e = 1.0f / tanr(fovy * 0.5f);

    return {
        e / aspect, 0.0f, 0.0f, 0.0f,
        0.0f, e, 0.0f, 0.0f,
        0.0f, 0.0f, ((f + n) / (f - n)), 1.0f,
        0.0f, 0.0f, -((2.0f * f * n) / (f - n)), 0.0f
    };
}

// directX default
inline mat44_t perspective_d3d_lh(real_t fovy, real_t aspect, real_t n, real_t f)
{
    real_t e = 1.0f / tanr(fovy * 0.5f);

    return {
        e / aspect, 0.0f, 0.0f, 0.0f,
        0.0f, e, 0.0f, 0.0f,
        0.0f, 0.0f, f / (f - n), 1.0f,
        0.0f, 0.0f, -((f * n) / (f - n)), 0.0f
    };
}

inline mat44_t perspective_d3d_rh(real_t fovy, real_t aspect, real_t n, real_t f)
{
    real_t e = 1.0f / tanr(fovy * 0.5f);

    return {
        e / aspect, 0.0f, 0.0f, 0.0f,
        0.0f, e, 0.0f, 0.0f,
        0.0f, 0.0f, -f / (f - n), -1.0f,
        0.0f, 0.0f, -((f * n) / (f - n)), 0.0f
    };
}

// vulkan default
inline mat44_t perspective_vulkan_rh(real_t fovy, real_t aspect, real_t n, real_t f)
{
    // vulkan clip space has inverted Y and half z
    const mat44_t clip{
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, -1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.5f, 0.0f,
        0.0f, 0.0f, 0.5f, 1.0f
    };

    return clip * perspective_gl_rh(fovy, aspect, n, f);
}

inline mat44_t perspective_vulkan_lh(real_t fovy, real_t aspect, real_t n, real_t f)
{
    // vulkan clip space has inverted Y and half z
    const mat44_t clip{
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, -1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.5f, 0.0f,
        0.0f, 0.0f, 0.5f, 1.0f
    };

    return clip * perspective_gl_lh(fovy, aspect, n, f);
}

// openGL default
inline mat44_t ortho_gl_rh(real_t l, real_t r, real_t b, real_t t, real_t n, real_t f)
{
    const real_t x = 1.0f / (r - l);
    const real_t y = 1.0f / (t - b);
    const real_t z = 1.0f / (f - n);

    return {
        2.0f * x, 0.0f, 0.0f, 0.0f,
        0.0f, 2.0f * y, 0.0f, 0.0f,
        0.0f, 0.0f, -2.0f * z, 0.0f,
        -(l + r) * x, -(b + t) * y, -(n + f) * z, 1.0f
    };
}

// directx default
inline mat44_t ortho_d3d_lh(real_t l, real_t r, real_t b, real_t t, real_t n, real_t f)
{
    const real_t x = 1.0f / (r - l);
    const real_t y = 1.0f / (t - b);
    const real_t z = 1.0f / (f - n);

    return {
        2.0f * x, 0.0f, 0.0f, 0.0f,
        0.0f, 2.0f * y, 0.0f, 0.0f,
        0.0f, 0.0f, z, 0.0f,
        -(l + r) * x, -(b + t) * y, -n * z, 1.0f
    };
}

} // namespace view

} // namespace as