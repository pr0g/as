#include "catch-matchers.hpp"
#include "catch2/catch.hpp"

#include "as/as-math-ops.hpp"

namespace unit_test
{

// types
using as::affine_t;
using as::mat3_t;
using as::mat4_t;
using as::point3_t;
using as::real_t;
using as::vec3_t;

// functions
using as::deg_to_rad;
using as::operator""_r;

// namespaces
namespace affine = as::affine;
namespace mat = as::mat;
namespace mat3 = as::mat3;
namespace mat4 = as::mat4;
namespace vec = as::vec;
namespace vec3 = as::vec3;

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
            mat3::rotation_z(deg_to_rad(90.0_r)),
            point3_t{0.0_r, 10.0_r, 0.0_r});

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
            mat3::rotation_z(deg_to_rad(90.0_r)),
            point3_t{0.0_r, 10.0_r, 0.0_r});

        const vec3_t result =
            affine::inv_transform_dir(affine, vec3_t{5.0_r, 0.0_r, 0.0_r});

        const real_t local_epsilon = 1.0e-6_r;
        CHECK(result.x == Approx(0.0_r).margin(local_epsilon));
        CHECK(result.y == Approx(-5.0_r).margin(local_epsilon));
        CHECK(result.z == Approx(0.0_r).margin(local_epsilon));
    }
}

TEST_CASE("affine_to_arr", "[as_affine]")
{
    using gsl::make_span;

    affine_t affine{
        mat3_t{1.0_r, 2.0_r, 3.0_r, 4.0_r, 5.0_r, 6.0_r, 7.0_r, 8.0_r, 9.0_r},
        point3_t{10.0f, 20.0f, 30.0f}};

    real_t expected_affine[12];
    affine::to_arr(affine, expected_affine);

    CHECK_THAT(
        make_span(expected_affine, 9), make_elements_sub(affine.rotation, 9));
    CHECK_THAT(
        make_span(&expected_affine[9], 3),
        make_elements_sub(affine.position.v, 3));
}

TEST_CASE("affine_from_arr", "[as_affine]")
{
    using gsl::make_span;

    real_t affine_arr[] = {1.0_r, 2.0_r, 3.0_r, 4.0_r, 5.0_r, 6.0_r,
                           7.0_r, 8.0_r, 9.0_r, 10.0f, 20.0f, 30.0f};

    affine_t affine;
    affine = affine::from_arr(affine_arr);

    CHECK_THAT(make_span(affine_arr, 9), make_elements_sub(affine.rotation, 9));
    CHECK_THAT(
        make_span(&affine_arr[9], 3), make_elements_sub(affine.position.v, 3));
}

TEST_CASE("affine_concatenation", "[as_affine]")
{
    using gsl::make_span;

    mat4_t mat_a = mat4::from_mat3_vec3(
        mat3::rotation_x(deg_to_rad(45.0_r)), vec3_t::axis_x(5.0_r));

    mat4_t mat_b = mat4::from_mat3_vec3(
        mat3::rotation_y(deg_to_rad(90.0_r)), vec3_t::axis_y(10.0_r));

    mat4_t mat_c = mat4::from_mat3_vec3(
        mat3::rotation_y(deg_to_rad(180.0_r)), vec3_t::axis_z(20.0_r));

    mat4_t mat_result;
    mat_result = mat::mul(mat::mul(mat_a, mat_b), mat_c);

    affine_t affine_a = affine::from_mat4(mat_a);
    affine_t affine_b = affine::from_mat4(mat_b);
    affine_t affine_c = affine::from_mat4(mat_c);

    affine_t affine_result;
    affine_result = affine::mul(affine::mul(affine_a, affine_b), affine_c);

    real_t expected_orientation[9];
    mat::to_arr(affine_result.rotation, expected_orientation);

    real_t expected_position[3];
    vec::to_arr(affine_result.position.v, expected_position);

    CHECK_THAT(
        make_span(expected_orientation),
        make_elements_sub(mat3::from_mat4(mat_result), 9));

    CHECK_THAT(
        make_span(expected_position),
        make_elements_sub(vec3::from_vec4(mat4::translation(mat_result)), 3));
}

} // namespace unit_test
