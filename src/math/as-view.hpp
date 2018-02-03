#pragma once

#include "as-mat4.hpp"

namespace as
{
namespace view
{

inline m44 perspective_gl_rh(real fovy, real aspect, real n, real f);
inline m44 perspective_gl_lh(real fovy, real aspect, real n, real f);
inline m44 perspective_d3d_lh(real fovy, real aspect, real n, real f);
inline m44 perspective_d3d_rh(real fovy, real aspect, real n, real f);
inline m44 perspective_vulkan_rh(real fovy, real aspect, real n, real f);
inline m44 perspective_vulkan_lh(real fovy, real aspect, real n, real f);

inline m44 ortho_gl_rh(real l, real r, real b, real t, real n, real f);
inline m44 ortho_d3d_lh(real l, real r, real b, real t, real n, real f);

} // namespace view

} // namespace as

#include "as-view.inl"