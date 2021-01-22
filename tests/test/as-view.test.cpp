#include "as-helpers.test.hpp"
#include "catch-matchers.hpp"
#include "catch2/catch_all.hpp"

#include "as/as-math.hpp"
#include "as/as-view.hpp"

namespace unit_test
{

// types
using as::affine;
using as::mat4;
using as::real;
using as::vec2;
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
    elements_are_span(perspective_gl_rh).margin(g_epsilon));
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
    elements_are_span(perspective_gl_lh).margin(g_epsilon));
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
    elements_are_span(perspective_d3d_rh).margin(g_epsilon));
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
    elements_are_span(perspective_d3d_lh).margin(g_epsilon));
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
    elements_are_span(perspective_vulkan_rh).margin(g_epsilon));
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
    elements_are_span(perspective_vulkan_lh).margin(g_epsilon));
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
    make_span(reference), elements_are_span(ortho_gl_rh).margin(g_epsilon));
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
    make_span(reference), elements_are_span(ortho_gl_lh).margin(g_epsilon));
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
    make_span(reference), elements_are_span(ortho_d3d_lh).margin(g_epsilon));
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
    make_span(reference), elements_are_span(ortho_d3d_rh).margin(g_epsilon));
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
    make_span(reference), elements_are_span(ortho_vulkan_rh).margin(g_epsilon));
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
    make_span(reference), elements_are_span(ortho_vulkan_lh).margin(g_epsilon));
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

TEST_CASE("screen_to_world_to_screen", "[as_view]")
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

    CHECK_THAT(arr(400, 300), elements_are_array(returned_screen_position));
  }

  {
    const auto expected_screen_position = vec2i(0, 0);
    const auto returned_screen_position = screen_to_world_to_screen(
      expected_screen_position, perspective_gl_rh, affine(vec3::zero()),
      screen_dimension);

    CHECK_THAT(arr(0, 0), elements_are_array(returned_screen_position));
  }

  {
    const auto expected_screen_position = vec2i(800, 600);
    const auto returned_screen_position = screen_to_world_to_screen(
      expected_screen_position, perspective_gl_rh, affine(vec3::zero()),
      screen_dimension);

    CHECK_THAT(arr(800, 600), elements_are_array(returned_screen_position));
  }

  {
    const auto expected_screen_position = vec2i(327, 589);
    const auto returned_screen_position = screen_to_world_to_screen(
      expected_screen_position, perspective_gl_rh, affine(vec3::zero()),
      screen_dimension);

    CHECK_THAT(arr(327, 589), elements_are_array(returned_screen_position));
  }

  {
    const auto expected_screen_position = vec2i(15, 45);
    const auto returned_screen_position = screen_to_world_to_screen(
      expected_screen_position, perspective_gl_rh, affine(vec3::zero()),
      screen_dimension);

    CHECK_THAT(arr(15, 45), elements_are_array(returned_screen_position));
  }

  {
    const auto expected_screen_position = vec2i(78, 127);
    const auto returned_screen_position = screen_to_world_to_screen(
      expected_screen_position, perspective_gl_rh,
      affine(as::mat3_rotation_y(radians(-90.0_r)), vec3::axis_z(10.0_r)),
      screen_dimension);

    CHECK_THAT(arr(78, 127), elements_are_array(returned_screen_position));
  }
}

TEST_CASE("world_to_screen_to_world", "[as_view]")
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
      expected_world_position,
      elements_are(returned_world_position).margin(g_epsilon));
  }

  {
    const mat4 perspective_d3d_lh =
      as::perspective_d3d_lh(fov, aspect, 0.01_r, 1000.0_r);

    const auto expected_world_position = vec3(10.0_r, 0.0_r, 0.0_r);
    const auto returned_world_position = world_to_screen_to_world(
      expected_world_position, perspective_d3d_lh,
      affine(as::mat3_rotation_y(radians(-90.0_r))), screen_dimension);

    CHECK_THAT(
      expected_world_position,
      elements_are(returned_world_position).margin(g_epsilon));
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
      expected_world_position,
      elements_are(returned_world_position).margin(g_epsilon));
  }

  {
    const mat4 perspective_vulkan_rh =
      as::perspective_vulkan_rh(fov, aspect, 0.01_r, 1000.0_r);

    const auto expected_world_position = vec3(0.0_r, -10.0_r, 0.0_r);
    const auto returned_world_position = world_to_screen_to_world(
      expected_world_position, perspective_vulkan_rh,
      affine(as::mat3_rotation_x(radians(90.0_r)), vec3::axis_z(5.0_r)),
      screen_dimension);

    CHECK_THAT(
      expected_world_position,
      elements_are(returned_world_position).margin(g_epsilon));
  }
}

TEST_CASE("screen_to_world_near_clip", "[as_view]")
{
  const real fov = radians(90.0_r);
  const real aspect = 16.0_r / 9.0_r;
  const vec2i screen_dimension = vec2i(1024, 768);
  const mat4 perspective_gl_lh =
    as::perspective_gl_lh(fov, aspect, 0.01_r, 1000.0_r);

  {
    const auto returned_world_position = as::screen_to_world(
      vec2i(512, 384), perspective_gl_lh, affine(vec3::zero()),
      screen_dimension);

    CHECK_THAT(
      arr(0.0_r, 0.0_r, 0.01_r), elements_are_array(returned_world_position));
  }
}

TEST_CASE("vec2_to_vec2i_conversions", "[as_view]")
{
  {
    auto v = vec2(1.0_r, 2.0_r);
    vec2i vi;
    vi = as::vec2i_from_vec2(v);
    CHECK_THAT(arr(1, 2), elements_are_array(vi));
  }

  {
    vec2i vi;
    vi = as::vec2i_from_reals(3.0_r, 6.0_r);
    CHECK_THAT(arr(3, 6), elements_are_array(vi));
  }

  {
    auto vi = vec2i(4, 5);
    vec2 v;
    v = as::vec2_from_vec2i(vi);
    CHECK_THAT(arr(4.0_r, 5.0_r), elements_are_array(v));
  }

  {
    vec2 v;
    v = as::vec2_from_ints(6, 7);
    CHECK_THAT(arr(6.0_r, 7.0_r), elements_are_array(v));
  }
}

} // namespace unit_test
