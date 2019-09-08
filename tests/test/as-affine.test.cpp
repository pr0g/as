#include "catch2/catch.hpp"
#include "catch-matchers.hpp"

#include "as/as-math-ops.hpp"

using namespace as;

// use float epsilon for comparisons
const real_t g_epsilon = std::numeric_limits<float>::epsilon();

TEST_CASE("affine_constructor", "[as_affine]")
{
    affine_t affine;
    mat3_t rotation = mat3::rotation_x(deg_to_rad(90.0f));
    point3_t position = point3_t{ 0.0f, 2.0f, 2.0f};
    affine = affine_t(rotation, position);

    CHECK(affine.position.v.x == Approx(position.v.x).margin(g_epsilon));
    CHECK(affine.position.v.y == Approx(position.v.y).margin(g_epsilon));
    CHECK(affine.position.v.z == Approx(position.v.z).margin(g_epsilon));
}

TEST_CASE("affine_transform_dir", "[as_affine]")
{
    const affine_t affine =
        affine_t(mat3::rotation_y(deg_to_rad(90.0f)), point3_t{ 5.0f, 0.0f, 0.0f });

    const vec3_t result = affine::transform_dir(affine, vec3_t{ 1.0f, 0.0f, 0.0f });

    CHECK(result.x == Approx(0.0f).margin(g_epsilon));
    CHECK(result.y == Approx(0.0f).margin(g_epsilon));
    CHECK(result.z == Approx(-1.0f).margin(g_epsilon));
}

TEST_CASE("affine_inv_transform_pos", "[as_affine]")
{
    {
        const affine_t affine =
            affine_t(mat3::identity(), point3_t{ 5.0f, 0.0f, 0.0f });

        const point3_t result = affine::inv_transform_pos(affine, point3_t{ 6.0f, 0.0f, 0.0f });

        CHECK(result.v.x == Approx(1.0f).margin(g_epsilon));
        CHECK(result.v.y == Approx(0.0f).margin(g_epsilon));
        CHECK(result.v.z == Approx(0.0f).margin(g_epsilon));
    }

    {
        const affine_t affine =
            affine_t(mat3::rotation_z(deg_to_rad(90.0f)), point3_t{ 0.0f, 10.0f, 0.0f });

        const point3_t result = affine::inv_transform_pos(affine, point3_t{ 5.0f, 0.0f, 0.0f });

        CHECK(result.v.x == Approx(-10.0f).margin(g_epsilon));
        CHECK(result.v.y == Approx(-5.0f).margin(g_epsilon));
        CHECK(result.v.z == Approx(0.0f).margin(g_epsilon));
    }
}

TEST_CASE("affine_transform_pos", "[as_affine]")
{
    const affine_t affine =
        affine_t(mat3::rotation_y(deg_to_rad(90.0f)), point3_t{ 5.0f, 0.0f, 0.0f });

    const point3_t result = affine::transform_pos(affine, point3_t{ 1.0f, 0.0f, 0.0f });

    CHECK(result.v.x == Approx(5.0f).margin(g_epsilon));
    CHECK(result.v.y == Approx(0.0f).margin(g_epsilon));
    CHECK(result.v.z == Approx(-1.0f).margin(g_epsilon));
}

TEST_CASE("affine_inv_transform_dir", "[as_affine]")
{
    {
        const affine_t affine =
            affine_t(mat3::identity(), point3_t{ 5.0f, 0.0f, 0.0f });

        const vec3_t result = affine::inv_transform_dir(affine, vec3_t{ 6.0f, 0.0f, 0.0f });

        CHECK(result.x == Approx(6.0f).margin(g_epsilon));
        CHECK(result.y == Approx(0.0f).margin(g_epsilon));
        CHECK(result.z == Approx(0.0f).margin(g_epsilon));
    }

    {
        const affine_t affine =
            affine_t(mat3::rotation_z(deg_to_rad(90.0f)), point3_t{ 0.0f, 10.0f, 0.0f });

        const vec3_t result = affine::inv_transform_dir(affine, vec3_t{ 5.0f, 0.0f, 0.0f });

        const float local_epsilon = 1.0e-6f;
        CHECK(result.x == Approx(0.0f).margin(local_epsilon));
        CHECK(result.y == Approx(-5.0f).margin(local_epsilon));
        CHECK(result.z == Approx(0.0f).margin(local_epsilon));
    }
}
