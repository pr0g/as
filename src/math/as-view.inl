namespace as
{

namespace view
{

// openGL default
inline m44 perspective_gl_rh(real fovy, real aspect, real n, real f)
{
    real e = 1.0f / tanr(fovy * 0.5f);

    return {
        e / aspect, 0.0f, 0.0f, 0.0f,
        0.0f, e, 0.0f, 0.0f,
        0.0f, 0.0f, -((f + n) / (f - n)), -1.0f,
        0.0f, 0.0f, -((2.0f * f * n) / (f - n)), 0.0f
    };
}

inline m44 perspective_gl_lh(real fovy, real aspect, real n, real f)
{
    real e = 1.0f / tanr(fovy * 0.5f);

    return {
        e / aspect, 0.0f, 0.0f, 0.0f,
        0.0f, e, 0.0f, 0.0f,
        0.0f, 0.0f, ((f + n) / (f - n)), 1.0f,
        0.0f, 0.0f, -((2.0f * f * n) / (f - n)), 0.0f
    };
}

// directX default
inline m44 perspective_d3d_lh(real fovy, real aspect, real n, real f)
{
    real e = 1.0f / tanr(fovy * 0.5f);

    return {
        e / aspect, 0.0f, 0.0f, 0.0f,
        0.0f, e, 0.0f, 0.0f,
        0.0f, 0.0f, f / (f - n), 1.0f,
        0.0f, 0.0f, -((f * n) / (f - n)), 0.0f
    };
}

inline m44 perspective_d3d_rh(real fovy, real aspect, real n, real f)
{
    real e = 1.0f / tanr(fovy * 0.5f);

    return {
        e / aspect, 0.0f, 0.0f, 0.0f,
        0.0f, e, 0.0f, 0.0f,
        0.0f, 0.0f, -f / (f - n), -1.0f,
        0.0f, 0.0f, -((f * n) / (f - n)), 0.0f
    };
}

// vulkan default
inline m44 perspective_vulkan_rh(real fovy, real aspect, real n, real f)
{
    // vulkan clip space has inverted Y and half z
    const m44 clip{
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, -1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.5f, 0.0f,
        0.0f, 0.0f, 0.5f, 1.0f
    };

    return clip * perspective_gl_rh(fovy, aspect, n, f);
}

inline m44 perspective_vulkan_lh(real fovy, real aspect, real n, real f)
{
    // vulkan clip space has inverted Y and half z
    const m44 clip{
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, -1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.5f, 0.0f,
        0.0f, 0.0f, 0.5f, 1.0f
    };

    return clip * perspective_gl_lh(fovy, aspect, n, f);
}

// openGL default
inline m44 ortho_gl_rh(real l, real r, real b, real t, real n, real f)
{
    const real x = 1.0f / (r - l);
    const real y = 1.0f / (t - b);
    const real z = 1.0f / (f - n);

    return {
        2.0f * x, 0.0f, 0.0f, 0.0f,
        0.0f, 2.0f * y, 0.0f, 0.0f,
        0.0f, 0.0f, -2.0f * z, 0.0f,
        -(l + r) * x, -(b + t) * y, -(n + f) * z, 1.0f
    };
}

// directx default
inline m44 ortho_d3d_lh(real l, real r, real b, real t, real n, real f)
{
    const real x = 1.0f / (r - l);
    const real y = 1.0f / (t - b);
    const real z = 1.0f / (f - n);

    return {
        2.0f * x, 0.0f, 0.0f, 0.0f,
        0.0f, 2.0f * y, 0.0f, 0.0f,
        0.0f, 0.0f, z, 0.0f,
        -(l + r) * x, -(b + t) * y, -n * z, 1.0f
    };
}

} // namespace view

} // namespace as