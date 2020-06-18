#include "catch-matchers.hpp"
#include "catch2/catch.hpp"

#include "as/as-math-ops.hpp"

namespace unit_test
{

// types
using as::affine_t;
using as::mat3_t;
using as::point3_t;
using as::real_t;
using as::vec3_t;

// functions
using as::deg_to_rad;
using as::operator""_r;

// namespaces
namespace affine = as::affine;
namespace mat3 = as::mat3;

// use float epsilon for comparisons
const real_t g_epsilon = real_t(std::numeric_limits<float>::epsilon());

TEST_CASE("affine_constructor", "[as_affine]")
{
    affine_t affine;
    mat3_t rotation = mat3::rotation_x(deg_to_rad(90.0_r));
    point3_t position = point3_t{0.0_r, 2.0_r, 2.0_r};
    affine = affine_t(rotation, position);

    CHECK(affine.position.v.x == Approx(position.v.x).margin(g_epsilon));
    CHECK(affine.position.v.y == Approx(position.v.y).margin(g_epsilon));
    CHECK(affine.position.v.z == Approx(position.v.z).margin(g_epsilon));
}

TEST_CASE("affine_transform_dir", "[as_affine]")
{
    const affine_t affine{
        mat3::rotation_y(deg_to_rad(90.0_r)), point3_t{5.0_r, 0.0_r, 0.0_r}};

    const vec3_t result =
        affine::transform_dir(affine, vec3_t{1.0_r, 0.0_r, 0.0_r});

    CHECK(result.x == Approx(0.0_r).margin(g_epsilon));
    CHECK(result.y == Approx(0.0_r).margin(g_epsilon));
    CHECK(result.z == Approx(-1.0_r).margin(g_epsilon));
}

TEST_CASE("affine_inv_transform_pos", "[as_affine]")
{
    {
        const affine_t affine =
            affine_t(mat3_t::identity(), point3_t{5.0_r, 0.0_r, 0.0_r});

        const point3_t result =
            affine::inv_transform_pos(affine, point3_t{6.0_r, 0.0_r, 0.0_r});

        CHECK(result.v.x == Approx(1.0_r).margin(g_epsilon));
        CHECK(result.v.y == Approx(0.0_r).margin(g_epsilon));
        CHECK(result.v.z == Approx(0.0_r).margin(g_epsilon));
    }

    {
        const affine_t affine = affine_t(
            mat3::rotation_z(deg_to_rad(90.0_r)), point3_t{0.0_r, 10.0_r, 0.0_r});

        const point3_t result =
            affine::inv_transform_pos(affine, point3_t{5.0_r, 0.0_r, 0.0_r});

        CHECK(result.v.x == Approx(-10.0_r).margin(g_epsilon));
        CHECK(result.v.y == Approx(-5.0_r).margin(g_epsilon));
        CHECK(result.v.z == Approx(0.0_r).margin(g_epsilon));
    }
}

TEST_CASE("affine_transform_pos", "[as_affine]")
{
    const affine_t affine = affine_t(
        mat3::rotation_y(deg_to_rad(90.0_r)), point3_t{5.0_r, 0.0_r, 0.0_r});

    const point3_t result =
        affine::transform_pos(affine, point3_t{1.0_r, 0.0_r, 0.0_r});

    CHECK(result.v.x == Approx(5.0_r).margin(g_epsilon));
    CHECK(result.v.y == Approx(0.0_r).margin(g_epsilon));
    CHECK(result.v.z == Approx(-1.0_r).margin(g_epsilon));
}

TEST_CASE("affine_inv_transform_dir", "[as_affine]")
{
    {
        const affine_t affine =
            affine_t(mat3_t::identity(), point3_t{5.0_r, 0.0_r, 0.0_r});

        const vec3_t result =
            affine::inv_transform_dir(affine, vec3_t{6.0_r, 0.0_r, 0.0_r});

        CHECK(result.x == Approx(6.0_r).margin(g_epsilon));
        CHECK(result.y == Approx(0.0_r).margin(g_epsilon));
        CHECK(result.z == Approx(0.0_r).margin(g_epsilon));
    }

    {
        const affine_t affine = affine_t(
            mat3::rotation_z(deg_to_rad(90.0_r)), point3_t{0.0_r, 10.0_r, 0.0_r});

        const vec3_t result =
            affine::inv_transform_dir(affine, vec3_t{5.0_r, 0.0_r, 0.0_r});

        const real_t local_epsilon = 1.0e-6_r;
        CHECK(result.x == Approx(0.0_r).margin(local_epsilon));
        CHECK(result.y == Approx(-5.0_r).margin(local_epsilon));
        CHECK(result.z == Approx(0.0_r).margin(local_epsilon));
    }
}

} // namespace unit_test
