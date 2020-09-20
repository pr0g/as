//! \file
//! as-view

#pragma once

#include "as-math-ops.hpp"

namespace as
{

//! Returns a mat4 representing a perspective projection matrix.
//! \note Uses OpenGL NDC space (-1, 1) and a right handed coordinate system.
//! \note This is the OpenGL default.
//! \param fovy The vertical field of view.
//! \param aspect The aspect ratio to use for the projection.
//! \param n The near plane of the clipping volume.
//! \param f The far plane of the clipping volume.
mat4 perspective_gl_rh(real fovy, real aspect, real n, real f);

//! Returns a mat4 representing a perspective projection matrix.
//! \note Uses OpenGL NDC space (-1, 1) and a left handed coordinate system.
//! \param fovy The vertical field of view.
//! \param aspect The aspect ratio to use for the projection.
//! \param n The near plane of the clipping volume.
//! \param f The far plane of the clipping volume.
mat4 perspective_gl_lh(real fovy, real aspect, real n, real f);

//! Returns a mat4 representing a perspective projection matrix.
//! \note Uses Direct3D NDC space (0, 1) and a right handed coordinate system.
//! \param fovy The vertical field of view.
//! \param aspect The aspect ratio to use for the projection.
//! \param n The near plane of the clipping volume.
//! \param f The far plane of the clipping volume.
mat4 perspective_d3d_rh(real fovy, real aspect, real n, real f);

//! Returns a mat4 representing a perspective projection matrix.
//! \note Uses Direct3D NDC space (0, 1) and a left handed coordinate system.
//! \note This is the Direct3D default.
//! \param fovy The vertical field of view.
//! \param aspect The aspect ratio to use for the projection.
//! \param n The near plane of the clipping volume.
//! \param f The far plane of the clipping volume.
mat4 perspective_d3d_lh(real fovy, real aspect, real n, real f);

//! Returns a mat4 representing a perspective projection matrix.
//! \note Uses Vulkan NDC space (0, 1) and a right handed coordinate system.
//! \note This is the Vulkan default.
//! \param fovy The vertical field of view.
//! \param aspect The aspect ratio to use for the projection.
//! \param n The near plane of the clipping volume.
//! \param f The far plane of the clipping volume.
mat4 perspective_vulkan_rh(real fovy, real aspect, real n, real f);

//! Returns a mat4 representing a perspective projection matrix.
//! \note Uses Vulkan NDC space (0, 1) and a left handed coordinate system.
//! \param fovy The vertical field of view.
//! \param aspect The aspect ratio to use for the projection.
//! \param n The near plane of the clipping volume.
//! \param f The far plane of the clipping volume.
mat4 perspective_vulkan_lh(real fovy, real aspect, real n, real f);

//! Returns a mat4 representing an orthographic projection matrix.
//! \note Uses OpenGL NDC space (-1, 1) and a right handed coordinate system.
//! \note This is the OpenGL default.
//! \param l The leftmost extent of the clipping volume.
//! \param r The rightmost extent of the clipping volume.
//! \param b The bottommost extent of the clipping volume.
//! \param t The topmost extent of the clipping volume.
//! \param n The near plane of the clipping volume.
//! \param f The far plane of the clipping volume.
constexpr mat4 ortho_gl_rh(real l, real r, real b, real t, real n, real f);

//! Returns a mat4 representing an orthographic projection matrix.
//! \note Uses OpenGL NDC space (-1, 1) and a left handed coordinate system.
//! \param l The leftmost extent of the clipping volume.
//! \param r The rightmost extent of the clipping volume.
//! \param b The bottommost extent of the clipping volume.
//! \param t The topmost extent of the clipping volume.
//! \param n The near plane of the clipping volume.
//! \param f The far plane of the clipping volume.
constexpr mat4 ortho_gl_lh(real l, real r, real b, real t, real n, real f);

//! Returns a mat4 representing an orthographic projection matrix.
//! \note Uses Direct3D NDC space (0, 1) and a right handed coordinate system.
//! \param l The leftmost extent of the clipping volume.
//! \param r The rightmost extent of the clipping volume.
//! \param b The bottommost extent of the clipping volume.
//! \param t The topmost extent of the clipping volume.
//! \param n The near plane of the clipping volume.
//! \param f The far plane of the clipping volume.
constexpr mat4 ortho_d3d_rh(real l, real r, real b, real t, real n, real f);

//! Returns a mat4 representing an orthographic projection matrix.
//! \note Uses Direct3D NDC space (0, 1) and a right left coordinate system.
//! \note This is the Direct3D default.
//! \param l The leftmost extent of the clipping volume.
//! \param r The rightmost extent of the clipping volume.
//! \param b The bottommost extent of the clipping volume.
//! \param t The topmost extent of the clipping volume.
//! \param n The near plane of the clipping volume.
//! \param f The far plane of the clipping volume.
constexpr mat4 ortho_d3d_lh(real l, real r, real b, real t, real n, real f);

//! Returns a mat4 representing an orthographic projection matrix.
//! \note Uses Vulkan NDC space (0, 1) and a right handed coordinate system.
//! \note This is the Vulkan default.
//! \param l The leftmost extent of the clipping volume.
//! \param r The rightmost extent of the clipping volume.
//! \param b The bottommost extent of the clipping volume.
//! \param t The topmost extent of the clipping volume.
//! \param n The near plane of the clipping volume.
//! \param f The far plane of the clipping volume.
mat4 ortho_vulkan_rh(real l, real r, real b, real t, real n, real f);

//! Returns a mat4 representing an orthographic projection matrix.
//! \note Uses Vulkan NDC space (0, 1) and a left handed coordinate system.
//! \param l The leftmost extent of the clipping volume.
//! \param r The rightmost extent of the clipping volume.
//! \param b The bottommost extent of the clipping volume.
//! \param t The topmost extent of the clipping volume.
//! \param n The near plane of the clipping volume.
//! \param f The far plane of the clipping volume.
mat4 ortho_vulkan_lh(real l, real r, real b, real t, real n, real f);

} // namespace as

#include "as-view.inl"
