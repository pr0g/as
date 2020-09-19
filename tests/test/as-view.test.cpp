#include "catch-matchers.hpp"
#include "catch2/catch.hpp"

#include "as/as-math.hpp"
#include "as/as-view.hpp"

namespace unit_test
{

// types
using as::mat4_t;
using as::real_t;

// functions
using as::deg_to_rad;
using as::operator""_r;

// namespaces
namespace view = as::view;

static const real_t g_epsilon = 1e-6_r;

TEST_CASE("perspective_gl_rh", "[as_view]")
{
  using gsl::make_span;

  const real_t fov = deg_to_rad(90.0_r);
  const real_t aspect = real_t(16.0_r) / real_t(9.0_r);
  mat4_t perspective_gl_rh =
    view::perspective_gl_rh(fov, aspect, 0.01_r, 1000.0_r);

  real_t reference[] = {0.562500_r, 0.000000_r, 0.000000_r,  0.000000_r,
                        0.000000_r, 1.000000_r, 0.000000_r,  0.000000_r,
                        0.000000_r, 0.000000_r, -1.000020_r, -1.000000_r,
                        0.000000_r, 0.000000_r, -0.020000_r, 0.000000_r};

  CHECK_THAT(
    make_span(reference),
    make_elements_sub(perspective_gl_rh, 16).margin(g_epsilon));
}

TEST_CASE("perspective_gl_lh", "[as_view]")
{
  using gsl::make_span;

  const real_t fov = deg_to_rad(90.0_r);
  const real_t aspect = real_t(16.0_r) / real_t(9.0_r);
  mat4_t perspective_gl_lh =
    view::perspective_gl_lh(fov, aspect, 0.01_r, 1000.0_r);

  real_t reference[] = {0.562500_r, 0.000000_r, 0.000000_r,  0.000000_r,
                        0.000000_r, 1.000000_r, 0.000000_r,  0.000000_r,
                        0.000000_r, 0.000000_r, 1.000020_r,  1.000000_r,
                        0.000000_r, 0.000000_r, -0.020000_r, 0.000000_r};

  CHECK_THAT(
    make_span(reference),
    make_elements_sub(perspective_gl_lh, 16).margin(g_epsilon));
}

TEST_CASE("perspective_d3d_rh", "[as_view]")
{
  using gsl::make_span;

  const real_t fov = deg_to_rad(90.0_r);
  const real_t aspect = real_t(16.0_r) / real_t(9.0_r);
  mat4_t perspective_d3d_rh =
    view::perspective_d3d_rh(fov, aspect, 0.01_r, 1000.0_r);

  real_t reference[] = {0.562500_r, 0.000000_r, 0.000000_r,  0.000000_r,
                        0.000000_r, 1.000000_r, 0.000000_r,  0.000000_r,
                        0.000000_r, 0.000000_r, -1.000010_r, -1.000000_r,
                        0.000000_r, 0.000000_r, -0.010000_r, 0.000000_r};

  CHECK_THAT(
    make_span(reference),
    make_elements_sub(perspective_d3d_rh, 16).margin(g_epsilon));
}

TEST_CASE("perspective_d3d_lh", "[as_view]")
{
  using gsl::make_span;

  const real_t fov = deg_to_rad(90.0_r);
  const real_t aspect = real_t(16.0_r) / real_t(9.0_r);
  mat4_t perspective_d3d_lh =
    view::perspective_d3d_lh(fov, aspect, 0.01_r, 1000.0_r);

  const real_t reference[] = {0.562500_r, 0.000000_r, 0.000000_r,  0.000000_r,
                              0.000000_r, 1.000000_r, 0.000000_r,  0.000000_r,
                              0.000000_r, 0.000000_r, 1.000010_r,  1.000000_r,
                              0.000000_r, 0.000000_r, -0.010000_r, 0.000000_r};

  CHECK_THAT(
    make_span(reference),
    make_elements_sub(perspective_d3d_lh, 16).margin(g_epsilon));
}

TEST_CASE("perspective_vulkan_rh", "[as_view]")
{
  using gsl::make_span;

  const real_t fov = deg_to_rad(90.0_r);
  const real_t aspect = real_t(16.0_r) / real_t(9.0_r);
  mat4_t perspective_vulkan_rh =
    view::perspective_vulkan_rh(fov, aspect, 0.01_r, 1000.0_r);

  const real_t reference[] = {0.562500_r, 0.000000_r,  0.000000_r,  0.000000_r,
                              0.000000_r, -1.000000_r, 0.000000_r,  0.000000_r,
                              0.000000_r, 0.000000_r,  -1.000010_r, -1.000000_r,
                              0.000000_r, 0.000000_r,  -0.010000_r, 0.000000_r};

  CHECK_THAT(
    make_span(reference),
    make_elements_sub(perspective_vulkan_rh, 16).margin(g_epsilon));
}

TEST_CASE("perspective_vulkan_lh", "[as_view]")
{
  using gsl::make_span;

  const real_t fov = deg_to_rad(90.0_r);
  const real_t aspect = real_t(16.0_r) / real_t(9.0_r);
  mat4_t perspective_vulkan_lh =
    view::perspective_vulkan_lh(fov, aspect, 0.01_r, 1000.0_r);

  const real_t reference[] = {0.562500_r, 0.000000_r,  0.000000_r,  0.000000_r,
                              0.000000_r, -1.000000_r, 0.000000_r,  0.000000_r,
                              0.000000_r, 0.000000_r,  1.000010_r,  1.000000_r,
                              0.000000_r, 0.000000_r,  -0.010000_r, 0.000000_r};

  CHECK_THAT(
    make_span(reference),
    make_elements_sub(perspective_vulkan_lh, 16).margin(g_epsilon));
}

TEST_CASE("ortho_gl_rh", "[as_view]")
{
  using gsl::make_span;

  mat4_t ortho_gl_rh;
  ortho_gl_rh =
    view::ortho_gl_rh(-10.0_r, 10.0_r, -10.0_r, 10.0_r, 0.01_r, 1000.0_r);

  const real_t reference[] = {
    0.100000_r,  0.000000_r,  0.000000_r,  0.000000_r, 0.000000_r,  0.100000_r,
    0.000000_r,  0.000000_r,  0.000000_r,  0.000000_r, -0.002000_r, 0.000000_r,
    -0.000000_r, -0.000000_r, -1.000020_r, 1.000000_r};

  CHECK_THAT(
    make_span(reference), make_elements_sub(ortho_gl_rh, 16).margin(g_epsilon));
}

TEST_CASE("ortho_gl_lh", "[as_view]")
{
  using gsl::make_span;

  mat4_t ortho_gl_lh;
  ortho_gl_lh =
    view::ortho_gl_lh(-10.0_r, 10.0_r, -10.0_r, 10.0_r, 0.01_r, 1000.0_r);

  const real_t reference[] = {
    0.100000_r,  0.000000_r,  0.000000_r,  0.000000_r, 0.000000_r, 0.100000_r,
    0.000000_r,  0.000000_r,  0.000000_r,  0.000000_r, 0.002000_r, 0.000000_r,
    -0.000000_r, -0.000000_r, -1.000020_r, 1.000000_r};

  CHECK_THAT(
    make_span(reference), make_elements_sub(ortho_gl_lh, 16).margin(g_epsilon));
}

TEST_CASE("ortho_d3d_lh", "[as_view]")
{
  using gsl::make_span;

  mat4_t ortho_d3d_lh;
  ortho_d3d_lh =
    view::ortho_d3d_lh(-10.0_r, 10.0_r, -10.0_r, 10.0_r, 0.01_r, 1000.0_r);

  const real_t reference[] = {
    0.100000_r,  0.000000_r,  0.000000_r,  0.000000_r, 0.000000_r, 0.100000_r,
    0.000000_r,  0.000000_r,  0.000000_r,  0.000000_r, 0.001000_r, 0.000000_r,
    -0.000000_r, -0.000000_r, -0.000010_r, 1.000000_r};

  CHECK_THAT(
    make_span(reference),
    make_elements_sub(ortho_d3d_lh, 16).margin(g_epsilon));
}

TEST_CASE("ortho_d3d_rh", "[as_view]")
{
  using gsl::make_span;

  mat4_t ortho_d3d_rh;
  ortho_d3d_rh =
    view::ortho_d3d_rh(-10.0_r, 10.0_r, -10.0_r, 10.0_r, 0.01_r, 1000.0_r);

  const real_t reference[] = {
    0.100000_r,  0.000000_r,  0.000000_r,  0.000000_r, 0.000000_r,  0.100000_r,
    0.000000_r,  0.000000_r,  0.000000_r,  0.000000_r, -0.001000_r, 0.000000_r,
    -0.000000_r, -0.000000_r, -0.000010_r, 1.000000_r};

  CHECK_THAT(
    make_span(reference),
    make_elements_sub(ortho_d3d_rh, 16).margin(g_epsilon));
}

TEST_CASE("ortho_vulkan_rh", "[as_view]")
{
  using gsl::make_span;

  mat4_t ortho_vulkan_rh;
  ortho_vulkan_rh =
    view::ortho_vulkan_rh(-10.0_r, 10.0_r, -10.0_r, 10.0_r, 0.01_r, 1000.0_r);

  const real_t reference[] = {
    0.100000_r,  0.000000_r,  0.000000_r,  0.000000_r, 0.000000_r,  -0.100000_r,
    0.000000_r,  0.000000_r,  0.000000_r,  0.000000_r, -0.001000_r, 0.000000_r,
    -0.000000_r, -0.000000_r, -0.000010_r, 1.000000_r};

  CHECK_THAT(
    make_span(reference),
    make_elements_sub(ortho_vulkan_rh, 16).margin(g_epsilon));
}

TEST_CASE("ortho_vulkan_lh", "[as_view]")
{
  using gsl::make_span;

  mat4_t ortho_vulkan_lh;
  ortho_vulkan_lh =
    view::ortho_vulkan_lh(-10.0_r, 10.0_r, -10.0_r, 10.0_r, 0.01_r, 1000.0_r);

  const real_t reference[] = {
    0.100000_r,  0.000000_r,  0.000000_r,  0.000000_r, 0.000000_r, -0.100000_r,
    0.000000_r,  0.000000_r,  0.000000_r,  0.000000_r, 0.001000_r, 0.000000_r,
    -0.000000_r, -0.000000_r, -0.000010_r, 1.000000_r};

  CHECK_THAT(
    make_span(reference),
    make_elements_sub(ortho_vulkan_lh, 16).margin(g_epsilon));
}

} // namespace unit_test
