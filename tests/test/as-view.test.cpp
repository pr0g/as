#include "catch2/catch.hpp"
#include "catch-matchers.hpp"

#include "as/as-math.hpp"
#include "as/as-view.hpp"

namespace unit_test
{

// types
using as::mat_t;
using as::mat3_t;
using as::mat4_t;
using as::index_t;
using as::real_t;
using as::vec_t;
using as::vec3_t;
using as::vec4_t;

// functions
using as::deg_to_rad;

// namespaces
namespace mat = as::mat;
namespace mat3 = as::mat3;
namespace mat4 = as::mat4;
namespace view = as::view;

static const float g_epsilon = 1e-6f;

TEST_CASE("perspective_gl_rh", "[as-view]")
{
    using gsl::make_span;

    const real_t fov = deg_to_rad(90.0f);
    const real_t aspect = real_t(16.0f) / real_t(9.0f);
    mat4_t perspective_gl_rh = view::perspective_gl_rh(fov, aspect, 0.01f, 1000.0f);

    real_t reference[] = {
        0.562500f, 0.000000f, 0.000000f, 0.000000f,
        0.000000f, 1.000000f, 0.000000f, 0.000000f,
        0.000000f, 0.000000f, -1.000020f, -1.000000f,
        0.000000f, 0.000000f, -0.020000f, 0.000000f
    };

    CHECK_THAT(
        make_span(reference),
        make_elements_sub(perspective_gl_rh, 16).margin(g_epsilon));
}

TEST_CASE("perspective_gl_lh", "[as-view]")
{
    using gsl::make_span;

    const real_t fov = deg_to_rad(90.0f);
    const real_t aspect = real_t(16.0f) / real_t(9.0f);
    mat4_t perspective_gl_lh = view::perspective_gl_lh(fov, aspect, 0.01f, 1000.0f);

    real_t reference[] = {
        0.562500f, 0.000000f, 0.000000f, 0.000000f,
        0.000000f, 1.000000f, 0.000000f, 0.000000f,
        0.000000f, 0.000000f, 1.000020f, 1.000000f,
        0.000000f, 0.000000f, -0.020000f, 0.000000f
    };

    CHECK_THAT(
        make_span(reference),
        make_elements_sub(perspective_gl_lh, 16).margin(g_epsilon));
}

TEST_CASE("perspective_d3d_rh", "[as-view]")
{
    using gsl::make_span;

    const real_t fov = deg_to_rad(90.0f);
    const real_t aspect = real_t(16.0f) / real_t(9.0f);
    mat4_t perspective_d3d_rh =
        view::perspective_d3d_rh(fov, aspect, 0.01f, 1000.0f);

    real_t reference[] = {
        0.562500f, 0.000000f, 0.000000f, 0.000000f,
        0.000000f, 1.000000f, 0.000000f, 0.000000f,
        0.000000f, 0.000000f, -1.000010f, -1.000000f,
        0.000000f, 0.000000f, -0.010000f, 0.000000f
    };

    CHECK_THAT(
        make_span(reference),
        make_elements_sub(perspective_d3d_rh, 16).margin(g_epsilon));
}

TEST_CASE("perspective_d3d_lh", "[as-view]")
{
    using gsl::make_span;

    const real_t fov = deg_to_rad(90.0f);
    const real_t aspect = real_t(16.0f) / real_t(9.0f);
    mat4_t perspective_d3d_lh =
        view::perspective_d3d_lh(fov, aspect, 0.01f, 1000.0f);

    const real_t reference[] = {
        0.562500f, 0.000000f, 0.000000f, 0.000000f,
        0.000000f, 1.000000f, 0.000000f, 0.000000f,
        0.000000f, 0.000000f, 1.000010f, 1.000000f,
        0.000000f, 0.000000f, -0.010000f, 0.000000f
    };

    CHECK_THAT(
        make_span(reference),
        make_elements_sub(perspective_d3d_lh, 16).margin(g_epsilon));
}

TEST_CASE("perspective_vulkan_rh", "[as-view]")
{
    using gsl::make_span;

    const real_t fov = deg_to_rad(90.0f);
    const real_t aspect = real_t(16.0f) / real_t(9.0f);
    mat4_t perspective_vulkan_rh =
        view::perspective_vulkan_rh(fov, aspect, 0.01f, 1000.0f);

    const real_t reference[] = {
        0.562500f, 0.000000f, 0.000000f, 0.000000f,
        0.000000f, -1.000000f, 0.000000f, 0.000000f,
        0.000000f, 0.000000f, -1.000010f, -1.000000f,
        0.000000f, 0.000000f, -0.010000f, 0.000000f
    };

    CHECK_THAT(
        make_span(reference),
        make_elements_sub(perspective_vulkan_rh, 16).margin(g_epsilon));
}

TEST_CASE("perspective_vulkan_lh", "[as-view]")
{
    using gsl::make_span;

    const real_t fov = deg_to_rad(90.0f);
    const real_t aspect = real_t(16.0f) / real_t(9.0f);
    mat4_t perspective_vulkan_lh =
        view::perspective_vulkan_lh(fov, aspect, 0.01f, 1000.0f);

    const real_t reference[] = {
        0.562500f, 0.000000f, 0.000000f, 0.000000f,
        0.000000f, -1.000000f, 0.000000f, 0.000000f,
        0.000000f, 0.000000f, 1.000010f, 1.000000f,
        0.000000f, 0.000000f, -0.010000f, 0.000000f
    };

    CHECK_THAT(
        make_span(reference),
        make_elements_sub(perspective_vulkan_lh, 16).margin(g_epsilon));
}

TEST_CASE("ortho_gl_rh", "[as-view]")
{
    using gsl::make_span;

    mat4_t ortho_gl_rh =
        view::ortho_gl_rh(-10.0f, 10.0f, -10.0f, 10.0f, 0.01f, 1000.0f);

    const real_t reference[] = {
        0.100000f, 0.000000f, 0.000000f, 0.000000f,
        0.000000f, 0.100000f, 0.000000f, 0.000000f,
        0.000000f, 0.000000f, -0.002000f, 0.000000f,
        -0.000000f, -0.000000f, -1.000020f, 1.000000f
    };

    CHECK_THAT(
        make_span(reference),
        make_elements_sub(ortho_gl_rh, 16).margin(g_epsilon));
}

TEST_CASE("ortho_d3d_lh", "[as-view]")
{
    using gsl::make_span;

    mat4_t ortho_d3d_lh =
        view::ortho_d3d_lh(-10.0f, 10.0f, -10.0f, 10.0f, 0.01f, 1000.0f);

    const real_t reference[] = {
        0.100000f, 0.000000f, 0.000000f, 0.000000f,
        0.000000f, 0.100000f, 0.000000f, 0.000000f,
        0.000000f, 0.000000f, 0.001000f, 0.000000f,
        -0.000000f, -0.000000f, -0.000010f, 1.000000f
    };

    CHECK_THAT(
        make_span(reference),
        make_elements_sub(ortho_d3d_lh, 16).margin(g_epsilon));
}

} // namespace unit_test
