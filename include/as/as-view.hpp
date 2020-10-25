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

//! Takes a position in world space and transforms it to screen coordinates.
//! \param world_position The position in world space.
//! \param projection The camera projection matrix.
//! \param view The camera view matrix (stored as an affine transformation due
//! to axis orthogonality).
//! \param screen_dimension The size of the screen/viewport.
vec2i world_to_screen(
  const vec3& world_position, const mat4& projection, const affine& view,
  const vec2i& screen_dimension);

//! Takes a position in screen space and returns it in world space aligned to
//! the near clip plane of the camera.
//! \param screen_position The position in screen space.
//! \param projection The camera projection matrix.
//! \param view The camera view matrix (stored as an affine transformation due
//! to axis orthogonality).
//! \param screen_dimension The size of the screen/viewport.
vec3 screen_to_world(
  const vec2i& screen_position, const mat4& projection, const affine& view,
  const vec2i& screen_dimension);

//! Returns a vec2 `(real, real)` from two `int32_t`s.
constexpr vec2 vec2_from_ints(int32_t x, int32_t y);

//! Returns a vec2 `(real, real)` from a vec2i.
constexpr vec2 vec2_from_vec2i(const vec2i& v);

//! Returns a vec2i `(int32_t, int32_t)` from two reals.
constexpr vec2i vec2i_from_reals(real x, real y);

//! Returns a vec2i `(int32_t, int32_t)` from a vec2.
constexpr vec2i vec2i_from_vec2(const vec2& v);

} // namespace as

#include "as-view.inl"
