namespace as
{

namespace view
{

// openGL default
inline mat4_t perspective_gl_rh(const real_t fovy, const real_t aspect, const real_t n, const real_t f)
{
    const real_t e = 1.0f / tanr(fovy * 0.5f);

    return {
        e / aspect, 0.0f, 0.0f, 0.0f,
        0.0f, e, 0.0f, 0.0f,
        0.0f, 0.0f, -((f + n) / (f - n)), -1.0f,
        0.0f, 0.0f, -((2.0f * f * n) / (f - n)), 0.0f
    };
}

inline mat4_t perspective_gl_lh(const real_t fovy, const real_t aspect, const real_t n, const real_t f)
{
    const real_t e = 1.0f / tanr(fovy * 0.5f);

    return {
        e / aspect, 0.0f, 0.0f, 0.0f,
        0.0f, e, 0.0f, 0.0f,
        0.0f, 0.0f, ((f + n) / (f - n)), 1.0f,
        0.0f, 0.0f, -((2.0f * f * n) / (f - n)), 0.0f
    };
}

inline mat4_t perspective_d3d_rh(const real_t fovy, const real_t aspect, const real_t n, const real_t f)
{
    const real_t e = 1.0f / tanr(fovy * 0.5f);

    return {
        e / aspect, 0.0f, 0.0f, 0.0f,
        0.0f, e, 0.0f, 0.0f,
        0.0f, 0.0f, -f / (f - n), -1.0f,
        0.0f, 0.0f, -((f * n) / (f - n)), 0.0f
    };
}

// directX default
inline mat4_t perspective_d3d_lh(const real_t fovy, const real_t aspect, const real_t n, const real_t f)
{
    const real_t e = 1.0f / tanr(fovy * 0.5f);

    return {
        e / aspect, 0.0f, 0.0f, 0.0f,
        0.0f, e, 0.0f, 0.0f,
        0.0f, 0.0f, f / (f - n), 1.0f,
        0.0f, 0.0f, -((f * n) / (f - n)), 0.0f
    };
}

// vulkan default
inline mat4_t perspective_vulkan_rh(const real_t fovy, const real_t aspect, const real_t n, const real_t f)
{
    // vulkan clip space has inverted Y and half z
    const mat4_t clip{
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, -1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.5f, 0.0f,
        0.0f, 0.0f, 0.5f, 1.0f
    };

#if defined AS_COL_MAJOR
    return clip * perspective_gl_rh(fovy, aspect, n, f);
#elif defined AS_ROW_MAJOR
    return perspective_gl_rh(fovy, aspect, n, f) * clip;
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

inline mat4_t perspective_vulkan_lh(const real_t fovy, const real_t aspect, const real_t n, const real_t f)
{
    // vulkan clip space has inverted Y and half z
    const mat4_t clip{
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, -1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.5f, 0.0f,
        0.0f, 0.0f, 0.5f, 1.0f
    };

#if defined AS_COL_MAJOR
    return clip * perspective_gl_lh(fovy, aspect, n, f);
#elif defined AS_ROW_MAJOR
    return perspective_gl_lh(fovy, aspect, n, f) * clip;
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

// openGL default
inline mat4_t ortho_gl_rh(const real_t l, const real_t r, const real_t b, const real_t t, const real_t n, const real_t f)
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
inline mat4_t ortho_d3d_lh(const real_t l, const real_t r, const real_t b, const real_t t, const real_t n, const real_t f)
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
