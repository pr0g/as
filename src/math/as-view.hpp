#pragma once

#include "as-mat4.hpp"

namespace as
{

namespace view
{

inline mat44_t perspective_gl_rh(real_t fovy, real_t aspect, real_t n, real_t f);
inline mat44_t perspective_gl_lh(real_t fovy, real_t aspect, real_t n, real_t f);
inline mat44_t perspective_d3d_lh(real_t fovy, real_t aspect, real_t n, real_t f);
inline mat44_t perspective_d3d_rh(real_t fovy, real_t aspect, real_t n, real_t f);
inline mat44_t perspective_vulkan_rh(real_t fovy, real_t aspect, real_t n, real_t f);
inline mat44_t perspective_vulkan_lh(real_t fovy, real_t aspect, real_t n, real_t f);

inline mat44_t ortho_gl_rh(real_t l, real_t r, real_t b, real_t t, real_t n, real_t f);
inline mat44_t ortho_d3d_lh(real_t l, real_t r, real_t b, real_t t, real_t n, real_t f);

} // namespace view

} // namespace as

#include "as-view.inl"