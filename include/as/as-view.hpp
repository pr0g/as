//! \file
//! as-view

#pragma once

#include "as-math-ops.hpp"

namespace as
{

//! Encapsulates all projection operations.
namespace view
{

//! Returns a mat4_t representing a perspective projection matrix.
//! \note Uses OpenGL NDC space (-1, 1) and a right handed coordinate system.
//! \note This is the OpenGL default.
//! \param fovy The vertical field of view.
//! \param aspect The aspect ratio to use for the projection.
//! \param n The near plane of the clipping volume.
//! \param f The far plane of the clipping volume.
mat4_t perspective_gl_rh(real_t fovy, real_t aspect, real_t n, real_t f);

//! Returns a mat4_t representing a perspective projection matrix.
//! \note Uses OpenGL NDC space (-1, 1) and a left handed coordinate system.
//! \param fovy The vertical field of view.
//! \param aspect The aspect ratio to use for the projection.
//! \param n The near plane of the clipping volume.
//! \param f The far plane of the clipping volume.
mat4_t perspective_gl_lh(real_t fovy, real_t aspect, real_t n, real_t f);

//! Returns a mat4_t representing a perspective projection matrix.
//! \note Uses Direct3D NDC space (0, 1) and a right handed coordinate system.
//! \param fovy The vertical field of view.
//! \param aspect The aspect ratio to use for the projection.
//! \param n The near plane of the clipping volume.
//! \param f The far plane of the clipping volume.
mat4_t perspective_d3d_rh(real_t fovy, real_t aspect, real_t n, real_t f);

//! Returns a mat4_t representing a perspective projection matrix.
//! \note Uses Direct3D NDC space (0, 1) and a left handed coordinate system.
//! \note This is the Direct3D default.
//! \param fovy The vertical field of view.
//! \param aspect The aspect ratio to use for the projection.
//! \param n The near plane of the clipping volume.
//! \param f The far plane of the clipping volume.
mat4_t perspective_d3d_lh(real_t fovy, real_t aspect, real_t n, real_t f);

//! Returns a mat4_t representing a perspective projection matrix.
//! \note Uses Vulkan NDC space (0, 1) and a right handed coordinate system.
//! \note This is the Vulkan default.
//! \param fovy The vertical field of view.
//! \param aspect The aspect ratio to use for the projection.
//! \param n The near plane of the clipping volume.
//! \param f The far plane of the clipping volume.
mat4_t perspective_vulkan_rh(real_t fovy, real_t aspect, real_t n, real_t f);

//! Returns a mat4_t representing a perspective projection matrix.
//! \note Uses Vulkan NDC space (0, 1) and a left handed coordinate system.
//! \param fovy The vertical field of view.
//! \param aspect The aspect ratio to use for the projection.
//! \param n The near plane of the clipping volume.
//! \param f The far plane of the clipping volume.
mat4_t perspective_vulkan_lh(real_t fovy, real_t aspect, real_t n, real_t f);

//! Returns a mat4_t representing an orthographic projection matrix.
//! \note Uses OpenGL NDC space (-1, 1) and a right handed coordinate system.
//! \note This is the OpenGL default.
//! \param l The leftmost extent of the clipping volume.
//! \param r The rightmost extent of the clipping volume.
//! \param b The bottommost extent of the clipping volume.
//! \param t The topmost extent of the clipping volume.
//! \param n The near plane of the clipping volume.
//! \param f The far plane of the clipping volume.
constexpr mat4_t ortho_gl_rh(
    real_t l, real_t r, real_t b, real_t t, real_t n, real_t f);

//! Returns a mat4_t representing an orthographic projection matrix.
//! \note Uses OpenGL NDC space (-1, 1) and a left handed coordinate system.
//! \param l The leftmost extent of the clipping volume.
//! \param r The rightmost extent of the clipping volume.
//! \param b The bottommost extent of the clipping volume.
//! \param t The topmost extent of the clipping volume.
//! \param n The near plane of the clipping volume.
//! \param f The far plane of the clipping volume.
constexpr mat4_t ortho_gl_lh(
    real_t l, real_t r, real_t b, real_t t, real_t n, real_t f);

//! Returns a mat4_t representing an orthographic projection matrix.
//! \note Uses Direct3D NDC space (0, 1) and a right handed coordinate system.
//! \param l The leftmost extent of the clipping volume.
//! \param r The rightmost extent of the clipping volume.
//! \param b The bottommost extent of the clipping volume.
//! \param t The topmost extent of the clipping volume.
//! \param n The near plane of the clipping volume.
//! \param f The far plane of the clipping volume.
constexpr mat4_t ortho_d3d_rh(
    real_t l, real_t r, real_t b, real_t t, real_t n, real_t f);

//! Returns a mat4_t representing an orthographic projection matrix.
//! \note Uses Direct3D NDC space (0, 1) and a right left coordinate system.
//! \note This is the Direct3D default.
//! \param l The leftmost extent of the clipping volume.
//! \param r The rightmost extent of the clipping volume.
//! \param b The bottommost extent of the clipping volume.
//! \param t The topmost extent of the clipping volume.
//! \param n The near plane of the clipping volume.
//! \param f The far plane of the clipping volume.
constexpr mat4_t ortho_d3d_lh(
    real_t l, real_t r, real_t b, real_t t, real_t n, real_t f);

//! Returns a mat4_t representing an orthographic projection matrix.
//! \note Uses Vulkan NDC space (0, 1) and a right handed coordinate system.
//! \note This is the Vulkan default.
//! \param l The leftmost extent of the clipping volume.
//! \param r The rightmost extent of the clipping volume.
//! \param b The bottommost extent of the clipping volume.
//! \param t The topmost extent of the clipping volume.
//! \param n The near plane of the clipping volume.
//! \param f The far plane of the clipping volume.
mat4_t ortho_vulkan_rh(
    real_t l, real_t r, real_t b, real_t t, real_t n, real_t f);

//! Returns a mat4_t representing an orthographic projection matrix.
//! \note Uses Vulkan NDC space (0, 1) and a left handed coordinate system.
//! \param l The leftmost extent of the clipping volume.
//! \param r The rightmost extent of the clipping volume.
//! \param b The bottommost extent of the clipping volume.
//! \param t The topmost extent of the clipping volume.
//! \param n The near plane of the clipping volume.
//! \param f The far plane of the clipping volume.
mat4_t ortho_vulkan_lh(
    real_t l, real_t r, real_t b, real_t t, real_t n, real_t f);

} // namespace view

} // namespace as

#include "as-view.inl"
