#include "as-helpers.test.hpp"
#include "catch-matchers.hpp"
#include "catch2/catch.hpp"

#include "as/as-math.hpp"
#include "as/as-view.hpp"

namespace unit_test
{

// types
using as::affine;
using as::mat4;
using as::real;
using as::vec2i;
using as::vec3;

// functions
using as::radians;
using as::operator""_r;

static const real g_epsilon = 1e-6_r;

TEST_CASE("perspective_gl_rh", "[as_view]")
{
  using gsl::make_span;

  const real fov = radians(90.0_r);
  const real aspect = 16.0_r / 9.0_r;
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

  const real fov = radians(90.0_r);
  const real aspect = 16.0_r / 9.0_r;
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

  const real fov = radians(90.0_r);
  const real aspect = 16.0_r / 9.0_r;
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

  const real fov = radians(90.0_r);
  const real aspect = 16.0_r / 9.0_r;
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

  const real fov = radians(90.0_r);
  const real aspect = 16.0_r / 9.0_r;
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

  const real fov = radians(90.0_r);
  const real aspect = 16.0_r / 9.0_r;
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

static vec2i screen_to_world_to_screen(
  const vec2i& screen_position, const mat4& projection, const affine& view,
  const vec2i& screen_dimension)
{
  const auto world =
    screen_to_world(screen_position, projection, view, screen_dimension);
  return world_to_screen(world, projection, view, screen_dimension);
}

static vec3 world_to_screen_to_world(
  const vec3& world_position, const mat4& projection, const affine& view,
  const vec2i& screen_dimension)
{
  const auto screen =
    world_to_screen(world_position, projection, view, screen_dimension);
  const auto world_near =
    screen_to_world(screen, projection, view, screen_dimension);
  const auto view_position = affine_inverse(view).translation;
  const auto distance = vec_distance(world_position, view_position);
  return view_position + vec_normalize(world_near) * distance;
}

TEST_CASE("screen_to_world", "[as_view]")
{
  const real fov = radians(90.0_r);
  const real aspect = 16.0_r / 9.0_r;
  const vec2i screen_dimension = vec2i(800, 600);
  const mat4 perspective_gl_rh =
    as::perspective_gl_rh(fov, aspect, 0.01_r, 1000.0_r);

  {
    const auto expected_screen_position = vec2i(400, 300);
    const auto returned_screen_position = screen_to_world_to_screen(
      expected_screen_position, perspective_gl_rh, affine(vec3::zero()),
      screen_dimension);

    CHECK_THAT(arr(400, 300), make_elements_sub(returned_screen_position, 2));
  }

  {
    const auto expected_screen_position = vec2i(0, 0);
    const auto returned_screen_position = screen_to_world_to_screen(
      expected_screen_position, perspective_gl_rh, affine(vec3::zero()),
      screen_dimension);

    CHECK_THAT(arr(0, 0), make_elements_sub(returned_screen_position, 2));
  }

  {
    const auto expected_screen_position = vec2i(800, 600);
    const auto returned_screen_position = screen_to_world_to_screen(
      expected_screen_position, perspective_gl_rh, affine(vec3::zero()),
      screen_dimension);

    CHECK_THAT(arr(800, 600), make_elements_sub(returned_screen_position, 2));
  }

  {
    const auto expected_screen_position = vec2i(327, 589);
    const auto returned_screen_position = screen_to_world_to_screen(
      expected_screen_position, perspective_gl_rh, affine(vec3::zero()),
      screen_dimension);

    CHECK_THAT(arr(327, 589), make_elements_sub(returned_screen_position, 2));
  }

  {
    const auto expected_screen_position = vec2i(15, 45);
    const auto returned_screen_position = screen_to_world_to_screen(
      expected_screen_position, perspective_gl_rh, affine(vec3::zero()),
      screen_dimension);

    CHECK_THAT(arr(15, 45), make_elements_sub(returned_screen_position, 2));
  }

  {
    const auto expected_screen_position = vec2i(78, 127);
    const auto returned_screen_position = screen_to_world_to_screen(
      expected_screen_position, perspective_gl_rh,
      affine(as::mat3_rotation_y(radians(-90.0_r)), vec3::axis_z(10.0_r)),
      screen_dimension);

    CHECK_THAT(arr(78, 127), make_elements_sub(returned_screen_position, 2));
  }
}

TEST_CASE("world_to_screen", "[as_view]")
{
  const real fov = radians(90.0_r);
  const real aspect = 16.0_r / 9.0_r;
  const vec2i screen_dimension = vec2i(800, 600);

  {
    const mat4 perspective_gl_rh =
      as::perspective_gl_rh(fov, aspect, 0.01_r, 1000.0_r);

    const auto expected_world_position = vec3(0.0_r, 0.0_r, -10.0_r);
    const auto returned_world_position = world_to_screen_to_world(
      expected_world_position, perspective_gl_rh, affine(vec3::zero()),
      screen_dimension);

    CHECK_THAT(
      arr(
        expected_world_position.x, expected_world_position.y,
        expected_world_position.z),
      make_elements_sub(returned_world_position, 3).margin(g_epsilon));
  }

  {
    const mat4 perspective_d3d_lh =
      as::perspective_d3d_lh(fov, aspect, 0.01_r, 1000.0_r);

    const auto expected_world_position = vec3(10.0_r, 0.0_r, 0.0_r);
    const auto returned_world_position = world_to_screen_to_world(
      expected_world_position, perspective_d3d_lh,
      affine(as::mat3_rotation_y(radians(-90.0_r))), screen_dimension);

    CHECK_THAT(
      arr(
        expected_world_position.x, expected_world_position.y,
        expected_world_position.z),
      make_elements_sub(returned_world_position, 3).margin(g_epsilon));
  }

  {
    const mat4 perspective_d3d_lh =
      as::perspective_d3d_lh(fov, aspect, 0.01_r, 1000.0_r);

    const auto expected_world_position = vec3(-10.0_r, 0.0_r, 0.0_r);
    const auto returned_world_position = world_to_screen_to_world(
      expected_world_position, perspective_d3d_lh,
      affine(as::mat3_rotation_y(radians(-90.0_r)), vec3::axis_z(10.0_r)),
      screen_dimension);

    CHECK_THAT(
      arr(
        expected_world_position.x, expected_world_position.y,
        expected_world_position.z),
      make_elements_sub(returned_world_position, 3).margin(g_epsilon));
  }
}

} // namespace unit_test
