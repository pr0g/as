//! \file
//! `as-view`

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
mat4 perspective_opengl_rh(real fovy, real aspect, real n, real f);

//! Returns a mat4 representing a perspective projection matrix.
//! \note Uses OpenGL NDC space (-1, 1) and a left handed coordinate system.
//! \param fovy The vertical field of view.
//! \param aspect The aspect ratio to use for the projection.
//! \param n The near plane of the clipping volume.
//! \param f The far plane of the clipping volume.
mat4 perspective_opengl_lh(real fovy, real aspect, real n, real f);

//! Returns a mat4 representing a perspective projection matrix.
//! \note Uses Direct3D NDC space (0, 1) and a right handed coordinate system.
//! \param fovy The vertical field of view.
//! \param aspect The aspect ratio to use for the projection.
//! \param n The near plane of the clipping volume.
//! \param f The far plane of the clipping volume.
mat4 perspective_direct3d_rh(real fovy, real aspect, real n, real f);

//! Returns a mat4 representing a perspective projection matrix.
//! \note Uses Direct3D NDC space (0, 1) and a left handed coordinate system.
//! \note This is the Direct3D default.
//! \param fovy The vertical field of view.
//! \param aspect The aspect ratio to use for the projection.
//! \param n The near plane of the clipping volume.
//! \param f The far plane of the clipping volume.
mat4 perspective_direct3d_lh(real fovy, real aspect, real n, real f);

//! Returns a mat4 representing a perspective projection matrix.
//! \note Uses Metal NDC space (0, 1) and a right handed coordinate system.
//! \note The Metal projection matrix calculation is equivalent to Direct3D.
inline const auto perspective_metal_rh = perspective_direct3d_rh;

//! Returns a mat4 representing a perspective projection matrix.
//! \note Uses Metal NDC space (0, 1) and a left handed coordinate system.
//! \note The Metal projection matrix calculation is equivalent to Direct3D.
inline const auto perspective_metal_lh = perspective_direct3d_lh;

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

//! Takes a perspective projection matrix which maps depth values to the range
//! (0, 1) and returns a matrix which maps them to the range (1, 0) - inverse z.
mat4 reverse_z(const mat4& perspective_projection);

//! Takes a perspective projection matrix with a depth range of -1 to 1 (OpenGL
//! default) and returns a matrix with the depth range mapped to 0 to 1.
//! \note The -1 to 1 range is sometimes referred to as 'closed unit ball',
//! hence the name 'unit_range' used here.
mat4 normalize_unit_range(const mat4& perspective_projection);

//! Takes a projection matrix (orthographic or perspective) and flips the y
//! axis.
//! \note The effect is to flip the image upside down, useful if the
//! graphics API has y grow top down instead of bottom up.
mat4 invert_y(const mat4& projection);

//! Returns a mat4 representing an orthographic projection matrix.
//! \note Uses OpenGL NDC space (-1, 1) and a right handed coordinate system.
//! \note This is the OpenGL default.
//! \param l The leftmost extent of the clipping volume.
//! \param r The rightmost extent of the clipping volume.
//! \param b The bottommost extent of the clipping volume.
//! \param t The topmost extent of the clipping volume.
//! \param n The near plane of the clipping volume.
//! \param f The far plane of the clipping volume.
constexpr mat4 ortho_opengl_rh(real l, real r, real b, real t, real n, real f);

//! Returns a mat4 representing an orthographic projection matrix.
//! \note Uses OpenGL NDC space (-1, 1) and a left handed coordinate system.
//! \param l The leftmost extent of the clipping volume.
//! \param r The rightmost extent of the clipping volume.
//! \param b The bottommost extent of the clipping volume.
//! \param t The topmost extent of the clipping volume.
//! \param n The near plane of the clipping volume.
//! \param f The far plane of the clipping volume.
constexpr mat4 ortho_opengl_lh(real l, real r, real b, real t, real n, real f);

//! Returns a mat4 representing an orthographic projection matrix.
//! \note Uses Direct3D NDC space (0, 1) and a right handed coordinate system.
//! \param l The leftmost extent of the clipping volume.
//! \param r The rightmost extent of the clipping volume.
//! \param b The bottommost extent of the clipping volume.
//! \param t The topmost extent of the clipping volume.
//! \param n The near plane of the clipping volume.
//! \param f The far plane of the clipping volume.
constexpr mat4 ortho_direct3d_rh(
  real l, real r, real b, real t, real n, real f);

//! Returns a mat4 representing an orthographic projection matrix.
//! \note Uses Direct3D NDC space (0, 1) and a right left coordinate system.
//! \note This is the Direct3D default.
//! \param l The leftmost extent of the clipping volume.
//! \param r The rightmost extent of the clipping volume.
//! \param b The bottommost extent of the clipping volume.
//! \param t The topmost extent of the clipping volume.
//! \param n The near plane of the clipping volume.
//! \param f The far plane of the clipping volume.
constexpr mat4 ortho_direct3d_lh(
  real l, real r, real b, real t, real n, real f);

//! Returns a mat4 representing an orthographic projection matrix.
//! \note Uses Metal NDC space (0, 1) and a right handed coordinate system.
//! \note The Metal projection matrix calculation is equivalent to Direct3D.
inline const auto ortho_metal_rh = ortho_direct3d_rh;

//! Returns a mat4 representing an orthographic projection matrix.
//! \note Uses Metal NDC space (0, 1) and a left handed coordinate system.
//! \note The Metal projection matrix calculation is equivalent to Direct3D.
inline const auto ortho_metal_lh = ortho_direct3d_lh;

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
