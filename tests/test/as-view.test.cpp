#include "catch-matchers.hpp"
#include "catch2/catch.hpp"

#include "as/as-math.hpp"
#include "as/as-view.hpp"

namespace unit_test
{

// types
using as::mat4;
using as::real;

// functions
using as::deg_to_rad;
using as::operator""_r;

static const real g_epsilon = 1e-6_r;

TEST_CASE("perspective_gl_rh", "[as_view]")
{
  using gsl::make_span;

  const real fov = deg_to_rad(90.0_r);
  const real aspect = real(16.0_r) / real(9.0_r);
  mat4 perspective_gl_rh = as::perspective_gl_rh(fov, aspect, 0.01_r, 1000.0_r);

  real reference[] = {0.562500_r, 0.000000_r, 0.000000_r,  0.000000_r,
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

  const real fov = deg_to_rad(90.0_r);
  const real aspect = real(16.0_r) / real(9.0_r);
  mat4 perspective_gl_lh = as::perspective_gl_lh(fov, aspect, 0.01_r, 1000.0_r);

  real reference[] = {0.562500_r, 0.000000_r, 0.000000_r,  0.000000_r,
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

  const real fov = deg_to_rad(90.0_r);
  const real aspect = real(16.0_r) / real(9.0_r);
  mat4 perspective_d3d_rh =
    as::perspective_d3d_rh(fov, aspect, 0.01_r, 1000.0_r);

  real reference[] = {0.562500_r, 0.000000_r, 0.000000_r,  0.000000_r,
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

  const real fov = deg_to_rad(90.0_r);
  const real aspect = real(16.0_r) / real(9.0_r);
  mat4 perspective_d3d_lh =
    as::perspective_d3d_lh(fov, aspect, 0.01_r, 1000.0_r);

  const real reference[] = {0.562500_r, 0.000000_r, 0.000000_r,  0.000000_r,
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

  const real fov = deg_to_rad(90.0_r);
  const real aspect = real(16.0_r) / real(9.0_r);
  mat4 perspective_vulkan_rh =
    as::perspective_vulkan_rh(fov, aspect, 0.01_r, 1000.0_r);

  const real reference[] = {0.562500_r, 0.000000_r,  0.000000_r,  0.000000_r,
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

  const real fov = deg_to_rad(90.0_r);
  const real aspect = real(16.0_r) / real(9.0_r);
  mat4 perspective_vulkan_lh =
    as::perspective_vulkan_lh(fov, aspect, 0.01_r, 1000.0_r);

  const real reference[] = {0.562500_r, 0.000000_r,  0.000000_r,  0.000000_r,
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

  mat4 ortho_gl_rh;
  ortho_gl_rh =
    as::ortho_gl_rh(-10.0_r, 10.0_r, -10.0_r, 10.0_r, 0.01_r, 1000.0_r);

  const real reference[] = {0.100000_r,  0.000000_r,  0.000000_r,  0.000000_r,
                            0.000000_r,  0.100000_r,  0.000000_r,  0.000000_r,
                            0.000000_r,  0.000000_r,  -0.002000_r, 0.000000_r,
                            -0.000000_r, -0.000000_r, -1.000020_r, 1.000000_r};

  CHECK_THAT(
    make_span(reference), make_elements_sub(ortho_gl_rh, 16).margin(g_epsilon));
}

TEST_CASE("ortho_gl_lh", "[as_view]")
{
  using gsl::make_span;

  mat4 ortho_gl_lh;
  ortho_gl_lh =
    as::ortho_gl_lh(-10.0_r, 10.0_r, -10.0_r, 10.0_r, 0.01_r, 1000.0_r);

  const real reference[] = {0.100000_r,  0.000000_r,  0.000000_r,  0.000000_r,
                            0.000000_r,  0.100000_r,  0.000000_r,  0.000000_r,
                            0.000000_r,  0.000000_r,  0.002000_r,  0.000000_r,
                            -0.000000_r, -0.000000_r, -1.000020_r, 1.000000_r};

  CHECK_THAT(
    make_span(reference), make_elements_sub(ortho_gl_lh, 16).margin(g_epsilon));
}

TEST_CASE("ortho_d3d_lh", "[as_view]")
{
  using gsl::make_span;

  mat4 ortho_d3d_lh;
  ortho_d3d_lh =
    as::ortho_d3d_lh(-10.0_r, 10.0_r, -10.0_r, 10.0_r, 0.01_r, 1000.0_r);

  const real reference[] = {0.100000_r,  0.000000_r,  0.000000_r,  0.000000_r,
                            0.000000_r,  0.100000_r,  0.000000_r,  0.000000_r,
                            0.000000_r,  0.000000_r,  0.001000_r,  0.000000_r,
                            -0.000000_r, -0.000000_r, -0.000010_r, 1.000000_r};

  CHECK_THAT(
    make_span(reference),
    make_elements_sub(ortho_d3d_lh, 16).margin(g_epsilon));
}

TEST_CASE("ortho_d3d_rh", "[as_view]")
{
  using gsl::make_span;

  mat4 ortho_d3d_rh;
  ortho_d3d_rh =
    as::ortho_d3d_rh(-10.0_r, 10.0_r, -10.0_r, 10.0_r, 0.01_r, 1000.0_r);

  const real reference[] = {0.100000_r,  0.000000_r,  0.000000_r,  0.000000_r,
                            0.000000_r,  0.100000_r,  0.000000_r,  0.000000_r,
                            0.000000_r,  0.000000_r,  -0.001000_r, 0.000000_r,
                            -0.000000_r, -0.000000_r, -0.000010_r, 1.000000_r};

  CHECK_THAT(
    make_span(reference),
    make_elements_sub(ortho_d3d_rh, 16).margin(g_epsilon));
}

TEST_CASE("ortho_vulkan_rh", "[as_view]")
{
  using gsl::make_span;

  mat4 ortho_vulkan_rh;
  ortho_vulkan_rh =
    as::ortho_vulkan_rh(-10.0_r, 10.0_r, -10.0_r, 10.0_r, 0.01_r, 1000.0_r);

  const real reference[] = {0.100000_r,  0.000000_r,  0.000000_r,  0.000000_r,
                            0.000000_r,  -0.100000_r, 0.000000_r,  0.000000_r,
                            0.000000_r,  0.000000_r,  -0.001000_r, 0.000000_r,
                            -0.000000_r, -0.000000_r, -0.000010_r, 1.000000_r};

  CHECK_THAT(
    make_span(reference),
    make_elements_sub(ortho_vulkan_rh, 16).margin(g_epsilon));
}

TEST_CASE("ortho_vulkan_lh", "[as_view]")
{
  using gsl::make_span;

  mat4 ortho_vulkan_lh;
  ortho_vulkan_lh =
    as::ortho_vulkan_lh(-10.0_r, 10.0_r, -10.0_r, 10.0_r, 0.01_r, 1000.0_r);

  const real reference[] = {0.100000_r,  0.000000_r,  0.000000_r,  0.000000_r,
                            0.000000_r,  -0.100000_r, 0.000000_r,  0.000000_r,
                            0.000000_r,  0.000000_r,  0.001000_r,  0.000000_r,
                            -0.000000_r, -0.000000_r, -0.000010_r, 1.000000_r};

  CHECK_THAT(
    make_span(reference),
    make_elements_sub(ortho_vulkan_lh, 16).margin(g_epsilon));
}

} // namespace unit_test
