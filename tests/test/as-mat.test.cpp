#include "as-helpers.test.hpp"
#include "catch-matchers.hpp"
#include "catch2/catch.hpp"

#include "as/as-math-ops.hpp"

namespace unit_test
{

// types
using as::affine;
using as::index;
using as::mat;
using as::mat3;
using as::mat3i;
using as::mat4;
using as::mat4i;
using as::quat;
using as::real;
using as::vec;
using as::vec3;
using as::vec4;

// functions
using as::radians;
using as::operator""_r;

const real g_epsilon = real(std::numeric_limits<float>::epsilon());

static_assert(std::is_trivial_v<mat3>);
static_assert(std::is_standard_layout_v<mat3>);
static_assert(std::is_pod_v<mat3>);

static_assert(std::is_trivial_v<mat4>);
static_assert(std::is_standard_layout_v<mat4>);
static_assert(std::is_pod_v<mat4>);

static_assert(std::is_trivial_v<mat<int, 5>>);
static_assert(std::is_standard_layout_v<mat<int, 5>>);
static_assert(std::is_pod_v<mat<int, 5>>);

TEST_CASE("mat_row_col_access_mat3", "[as_mat]")
{
  using gsl::make_span;

  // clang-format off
  mat3 m3 {
    1.0_r, 2.0_r, 3.0_r,
    4.0_r, 5.0_r, 6.0_r,
    7.0_r, 8.0_r, 9.0_r
  };
  // clang-format on

#ifdef AS_COL_MAJOR
  const real col0[] = {1.0_r, 2.0_r, 3.0_r};
  CHECK_THAT(make_span(col0), elements_are_span(as::mat3_col0(m3)));
  CHECK_THAT(make_span(col0), elements_are_span(as::mat_col(m3, 0)));
  const real col1[] = {4.0_r, 5.0_r, 6.0_r};
  CHECK_THAT(make_span(col1), elements_are_span(as::mat3_col1(m3)));
  CHECK_THAT(make_span(col1), elements_are_span(as::mat_col(m3, 1)));
  const real col2[] = {7.0_r, 8.0_r, 9.0_r};
  CHECK_THAT(make_span(col2), elements_are_span(as::mat3_col2(m3)));
  CHECK_THAT(make_span(col2), elements_are_span(as::mat_col(m3, 2)));

  const real row0[] = {1.0_r, 4.0_r, 7.0_r};
  CHECK_THAT(make_span(row0), elements_are_span(as::mat3_row0(m3)));
  CHECK_THAT(make_span(row0), elements_are_span(as::mat_row(m3, 0)));
  const real row1[] = {2.0_r, 5.0_r, 8.0_r};
  CHECK_THAT(make_span(row1), elements_are_span(as::mat3_row1(m3)));
  CHECK_THAT(make_span(row1), elements_are_span(as::mat_row(m3, 1)));
  const real row2[] = {3.0_r, 6.0_r, 9.0_r};
  CHECK_THAT(make_span(row2), elements_are_span(as::mat3_row2(m3)));
  CHECK_THAT(make_span(row2), elements_are_span(as::mat_row(m3, 2)));
#elif defined AS_ROW_MAJOR
  const real row0[] = {1.0_r, 2.0_r, 3.0_r};
  CHECK_THAT(make_span(row0), elements_are_span(as::mat3_row0(m3)));
  CHECK_THAT(make_span(row0), elements_are_span(as::mat_row(m3, 0)));
  const real row1[] = {4.0_r, 5.0_r, 6.0_r};
  CHECK_THAT(make_span(row1), elements_are_span(as::mat3_row1(m3)));
  CHECK_THAT(make_span(row1), elements_are_span(as::mat_row(m3, 1)));
  const real row2[] = {7.0_r, 8.0_r, 9.0_r};
  CHECK_THAT(make_span(row2), elements_are_span(as::mat3_row2(m3)));
  CHECK_THAT(make_span(row2), elements_are_span(as::mat_row(m3, 2)));

  const real col0[] = {1.0_r, 4.0_r, 7.0_r};
  CHECK_THAT(make_span(col0), elements_are_span(as::mat3_col0(m3)));
  CHECK_THAT(make_span(col0), elements_are_span(as::mat_col(m3, 0)));
  const real col1[] = {2.0_r, 5.0_r, 8.0_r};
  CHECK_THAT(make_span(col1), elements_are_span(as::mat3_col1(m3)));
  CHECK_THAT(make_span(col1), elements_are_span(as::mat_col(m3, 1)));
  const real col2[] = {3.0_r, 6.0_r, 9.0_r};
  CHECK_THAT(make_span(col2), elements_are_span(as::mat3_col2(m3)));
  CHECK_THAT(make_span(col2), elements_are_span(as::mat_col(m3, 2)));
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR

  // clang-format off
  real elems[] = {
    1.0_r, 2.0_r, 3.0_r,
    4.0_r, 5.0_r, 6.0_r,
    7.0_r, 8.0_r, 9.0_r
  };
  // clang-format on

  CHECK_THAT(make_span(elems), elements_are_span(m3));

  // clang-format off
  mat3 mat3_mult;
  mat3_mult = mat3(
    vec3(10.0_r, 20.0_r, 30.0_r),
    vec3(40.0_r, 50.0_r, 60.0_r),
    vec3(70.0_r, 80.0_r, 90.0_r));

  real mult_elems[] = {
    10.0_r, 20.0_r, 30.0_r,
    40.0_r, 50.0_r, 60.0_r,
    70.0_r, 80.0_r, 90.0_r
  };
  // clang-format on

  CHECK_THAT(make_span(mult_elems), elements_are_span(mat3_mult));
}

TEST_CASE("mat_row_col_mutate_mat3", "[as_mat]")
{
  using gsl::make_span;

  // clang-format off
  mat3 m3;
  m3 = mat3 {
    0.0_r, 0.0_r, 0.0_r,
    0.0_r, 0.0_r, 0.0_r,
    0.0_r, 0.0_r, 0.0_r
  };
  // clang-format on

#ifdef AS_COL_MAJOR
  const real col0[] = {1.0_r, 2.0_r, 3.0_r};
  const vec3 c0 = as::vec3_from_arr(col0);
  as::mat3_col0(m3, c0);
  CHECK_THAT(make_span(col0), elements_are_span(as::mat3_col0(m3)));
  as::mat_col(m3, 0, c0);
  CHECK_THAT(make_span(col0), elements_are_span(as::mat_col(m3, 0)));

  const real col1[] = {4.0_r, 5.0_r, 6.0_r};
  const vec3 c1 = as::vec3_from_arr(col1);
  as::mat3_col1(m3, c1);
  CHECK_THAT(make_span(col1), elements_are_span(as::mat3_col1(m3)));
  as::mat_col(m3, 1, c1);
  CHECK_THAT(make_span(col1), elements_are_span(as::mat_col(m3, 1)));

  const real col2[] = {7.0_r, 8.0_r, 9.0_r};
  const vec3 c2 = as::vec3_from_arr(col2);
  as::mat3_col2(m3, c2);
  CHECK_THAT(make_span(col2), elements_are_span(as::mat3_col2(m3)));
  as::mat_col(m3, 2, c2);
  CHECK_THAT(make_span(col2), elements_are_span(as::mat_col(m3, 2)));

  const real row0[] = {1.0_r, 4.0_r, 7.0_r};
  const vec3 r0 = as::vec3_from_arr(row0);
  as::mat3_row0(m3, r0);
  CHECK_THAT(make_span(row0), elements_are_span(as::mat3_row0(m3)));
  as::mat_row(m3, 0, r0);
  CHECK_THAT(make_span(row0), elements_are_span(as::mat_row(m3, 0)));

  const real row1[] = {2.0_r, 5.0_r, 8.0_r};
  const vec3 r1 = as::vec3_from_arr(row1);
  as::mat3_row1(m3, r1);
  CHECK_THAT(make_span(row1), elements_are_span(as::mat3_row1(m3)));
  as::mat_row(m3, 1, r1);
  CHECK_THAT(make_span(row1), elements_are_span(as::mat_row(m3, 1)));

  const real row2[] = {3.0_r, 6.0_r, 9.0_r};
  const vec3 r2 = as::vec3_from_arr(row2);
  as::mat3_row2(m3, r2);
  CHECK_THAT(make_span(row2), elements_are_span(as::mat3_row2(m3)));
  as::mat_row(m3, 2, r2);
  CHECK_THAT(make_span(row2), elements_are_span(as::mat_row(m3, 2)));
#elif defined AS_ROW_MAJOR
  const real row0[] = {1.0_r, 2.0_r, 3.0_r};
  const vec3 r0 = as::vec3_from_arr(row0);
  as::mat3_row0(m3, r0);
  CHECK_THAT(make_span(row0), elements_are_span(as::mat3_row0(m3)));
  as::mat_row(m3, 0, r0);
  CHECK_THAT(make_span(row0), elements_are_span(as::mat_row(m3, 0)));

  const real row1[] = {4.0_r, 5.0_r, 6.0_r};
  const vec3 r1 = as::vec3_from_arr(row1);
  as::mat3_row1(m3, r1);
  CHECK_THAT(make_span(row1), elements_are_span(as::mat3_row1(m3)));
  as::mat_row(m3, 1, r1);
  CHECK_THAT(make_span(row1), elements_are_span(as::mat_row(m3, 1)));

  const real row2[] = {7.0_r, 8.0_r, 9.0_r};
  const vec3 r2 = as::vec3_from_arr(row2);
  as::mat3_row2(m3, r2);
  CHECK_THAT(make_span(row2), elements_are_span(as::mat3_row2(m3)));
  as::mat_row(m3, 2, r2);
  CHECK_THAT(make_span(row2), elements_are_span(as::mat_row(m3, 2)));

  const real col0[] = {1.0_r, 4.0_r, 7.0_r};
  const vec3 c0 = as::vec3_from_arr(col0);
  as::mat3_col0(m3, c0);
  CHECK_THAT(make_span(col0), elements_are_span(as::mat3_col0(m3)));
  as::mat_col(m3, 0, c0);
  CHECK_THAT(make_span(col0), elements_are_span(as::mat_col(m3, 0)));

  const real col1[] = {2.0_r, 5.0_r, 9.0_r};
  const vec3 c1 = as::vec3_from_arr(col1);
  as::mat3_col1(m3, c1);
  CHECK_THAT(make_span(col1), elements_are_span(as::mat3_col1(m3)));
  as::mat_col(m3, 1, c1);
  CHECK_THAT(make_span(col1), elements_are_span(as::mat_col(m3, 1)));

  const real col2[] = {3.0_r, 6.0_r, 9.0_r};
  const vec3 c2 = as::vec3_from_arr(col2);
  as::mat3_col2(m3, c2);
  CHECK_THAT(make_span(col2), elements_are_span(as::mat3_col2(m3)));
  as::mat_col(m3, 2, c2);
  CHECK_THAT(make_span(col2), elements_are_span(as::mat_col(m3, 2)));
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

TEST_CASE("mat_row_col_access_mat4", "[as_mat]")
{
  using gsl::make_span;

  // clang-format off
  mat4 m4 {
    1.0_r, 2.0_r, 3.0_r, 4.0_r,
    5.0_r, 6.0_r, 7.0_r, 8.0_r,
    9.0_r, 10.0_r, 11.0_r, 12.0_r,
    13.0_r, 14.0_r, 15.0_r, 16.0_r
  };
  // clang-format on

#ifdef AS_COL_MAJOR
  const real col0[] = {1.0_r, 2.0_r, 3.0_r, 4.0_r};
  CHECK_THAT(make_span(col0), elements_are_span(as::mat4_col0(m4)));
  CHECK_THAT(make_span(col0), elements_are_span(as::mat_col(m4, 0)));
  const real col1[] = {5.0_r, 6.0_r, 7.0_r, 8.0_r};
  CHECK_THAT(make_span(col1), elements_are_span(as::mat4_col1(m4)));
  CHECK_THAT(make_span(col1), elements_are_span(as::mat_col(m4, 1)));
  const real col2[] = {9.0_r, 10.0_r, 11.0_r, 12.0_r};
  CHECK_THAT(make_span(col2), elements_are_span(as::mat4_col2(m4)));
  CHECK_THAT(make_span(col2), elements_are_span(as::mat_col(m4, 2)));
  const real col3[] = {13.0_r, 14.0_r, 15.0_r, 16.0_r};
  CHECK_THAT(make_span(col3), elements_are_span(as::mat4_col3(m4)));
  CHECK_THAT(make_span(col3), elements_are_span(as::mat_col(m4, 3)));

  const real row0[] = {1.0_r, 5.0_r, 9.0_r, 13.0_r};
  CHECK_THAT(make_span(row0), elements_are_span(as::mat4_row0(m4)));
  CHECK_THAT(make_span(row0), elements_are_span(as::mat_row(m4, 0)));
  const real row1[] = {2.0_r, 6.0_r, 10.0_r, 14.0_r};
  CHECK_THAT(make_span(row1), elements_are_span(as::mat4_row1(m4)));
  CHECK_THAT(make_span(row1), elements_are_span(as::mat_row(m4, 1)));
  const real row2[] = {3.0_r, 7.0_r, 11.0_r, 15.0_r};
  CHECK_THAT(make_span(row2), elements_are_span(as::mat4_row2(m4)));
  CHECK_THAT(make_span(row2), elements_are_span(as::mat_row(m4, 2)));
  const real row3[] = {4.0_r, 8.0_r, 12.0_r, 16.0_r};
  CHECK_THAT(make_span(row3), elements_are_span(as::mat4_row3(m4)));
  CHECK_THAT(make_span(row3), elements_are_span(as::mat_row(m4, 3)));
#elif defined AS_ROW_MAJOR
  const real row0[] = {1.0_r, 2.0_r, 3.0_r, 4.0_r};
  CHECK_THAT(make_span(row0), elements_are_span(as::mat4_row0(m4)));
  CHECK_THAT(make_span(row0), elements_are_span(as::mat_row(m4, 0)));
  const real row1[] = {5.0_r, 6.0_r, 7.0_r, 8.0_r};
  CHECK_THAT(make_span(row1), elements_are_span(as::mat4_row1(m4)));
  CHECK_THAT(make_span(row1), elements_are_span(as::mat_row(m4, 1)));
  const real row2[] = {9.0_r, 10.0_r, 11.0_r, 12.0_r};
  CHECK_THAT(make_span(row2), elements_are_span(as::mat4_row2(m4)));
  CHECK_THAT(make_span(row2), elements_are_span(as::mat_row(m4, 2)));
  const real row3[] = {13.0_r, 14.0_r, 15.0_r, 16.0_r};
  CHECK_THAT(make_span(row3), elements_are_span(as::mat4_row3(m4)));
  CHECK_THAT(make_span(row3), elements_are_span(as::mat_row(m4, 3)));

  const real col0[] = {1.0_r, 5.0_r, 9.0_r, 13.0_r};
  CHECK_THAT(make_span(col0), elements_are_span(as::mat4_col0(m4)));
  CHECK_THAT(make_span(col0), elements_are_span(as::mat_col(m4, 0)));
  const real col1[] = {2.0_r, 6.0_r, 10.0_r, 14.0_r};
  CHECK_THAT(make_span(col1), elements_are_span(as::mat4_col1(m4)));
  CHECK_THAT(make_span(col1), elements_are_span(as::mat_col(m4, 1)));
  const real col2[] = {3.0_r, 7.0_r, 11.0_r, 15.0_r};
  CHECK_THAT(make_span(col2), elements_are_span(as::mat4_col2(m4)));
  CHECK_THAT(make_span(col2), elements_are_span(as::mat_col(m4, 2)));
  const real col3[] = {4.0_r, 8.0_r, 12.0_r, 16.0_r};
  CHECK_THAT(make_span(col3), elements_are_span(as::mat4_col3(m4)));
  CHECK_THAT(make_span(col3), elements_are_span(as::mat_col(m4, 3)));
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR

  // clang-format off
  real elems[] = {
    1.0_r,  2.0_r,  3.0_r,  4.0_r,
    5.0_r,  6.0_r,  7.0_r,  8.0_r,
    9.0_r,  10.0_r, 11.0_r, 12.0_r,
    13.0_r, 14.0_r, 15.0_r, 16.0_r
  };
  // clang-format on

  CHECK_THAT(make_span(elems), elements_are_span(m4));

  // clang-format off
  mat4 mat4_mult;
  mat4_mult = mat4(
    vec4(10.0_r,  20.0_r,  30.0_r,  40.0_r),
    vec4(50.0_r,  60.0_r,  70.0_r,  80.0_r),
    vec4(90.0_r,  100.0_r, 110.0_r, 120.0_r),
    vec4(130.0_r, 140.0_r, 150.0_r, 160.0_r)
  );

  real mult_elems[] = {
      10.0_r,  20.0_r,  30.0_r,  40.0_r,
      50.0_r,  60.0_r,  70.0_r,  80.0_r,
      90.0_r,  100.0_r, 110.0_r, 120.0_r,
      130.0_r, 140.0_r, 150.0_r, 160.0_r
  };
  // clang-format on

  CHECK_THAT(make_span(mult_elems), elements_are_span(mat4_mult));
}

TEST_CASE("mat_row_col_mutate_mat4", "[as_mat]")
{
  using gsl::make_span;

  // clang-format off
  mat4 m4;
  m4 = mat4 {
    0.0_r, 0.0_r, 0.0_r, 0.0_r,
    0.0_r, 0.0_r, 0.0_r, 0.0_r,
    0.0_r, 0.0_r, 0.0_r, 0.0_r,
    0.0_r, 0.0_r, 0.0_r, 0.0_r
  };
  // clang-format on

#ifdef AS_COL_MAJOR
  const real col0[] = {1.0_r, 2.0_r, 3.0_r, 4.0_r};
  const vec4 c0 = as::vec4_from_arr(col0);
  as::mat4_col0(m4, c0);
  CHECK_THAT(make_span(col0), elements_are_span(as::mat4_col0(m4)));
  as::mat_col(m4, 0, c0);
  CHECK_THAT(make_span(col0), elements_are_span(as::mat_col(m4, 0)));
  CHECK(col0[0] == Approx(as::mat_col(m4, 0)[0]).epsilon(g_epsilon));

  const real col1[] = {5.0_r, 6.0_r, 7.0_r, 8.0_r};
  const vec4 c1 = as::vec4_from_arr(col1);
  as::mat4_col1(m4, c1);
  CHECK_THAT(make_span(col1), elements_are_span(as::mat4_col1(m4)));
  as::mat_col(m4, 1, c1);
  CHECK_THAT(make_span(col1), elements_are_span(as::mat_col(m4, 1)));
  CHECK(col1[1] == Approx(as::mat_col(m4, 1)[1]).epsilon(g_epsilon));

  const real col2[] = {9.0_r, 10.0_r, 11.0_r, 12.0_r};
  const vec4 c2 = as::vec4_from_arr(col2);
  as::mat4_col2(m4, c2);
  CHECK_THAT(make_span(col2), elements_are_span(as::mat4_col2(m4)));
  as::mat_col(m4, 2, c2);
  CHECK_THAT(make_span(col2), elements_are_span(as::mat_col(m4, 2)));
  CHECK(col2[2] == Approx(as::mat_col(m4, 2)[2]).epsilon(g_epsilon));

  const real col3[] = {13.0_r, 14.0_r, 15.0_r, 16.0_r};
  const vec4 c3 = as::vec4_from_arr(col3);
  as::mat4_col3(m4, c3);
  CHECK_THAT(make_span(col3), elements_are_span(as::mat4_col3(m4)));
  as::mat_col(m4, 3, c3);
  CHECK_THAT(make_span(col3), elements_are_span(as::mat_col(m4, 3)));
  CHECK(col3[3] == Approx(as::mat_col(m4, 3)[3]).epsilon(g_epsilon));

  const real row0[] = {1.0_r, 5.0_r, 9.0_r, 13.0_r};
  const vec4 r0 = as::vec4_from_arr(row0);
  as::mat4_row0(m4, r0);
  CHECK_THAT(make_span(row0), elements_are_span(as::mat4_row0(m4)));
  as::mat_row(m4, 0, r0);
  CHECK_THAT(make_span(row0), elements_are_span(as::mat_row(m4, 0)));
  CHECK(row0[0] == Approx(as::mat_row(m4, 0)[0]).epsilon(g_epsilon));

  const real row1[] = {2.0_r, 6.0_r, 10.0_r, 14.0_r};
  const vec4 r1 = as::vec4_from_arr(row1);
  as::mat4_row1(m4, r1);
  CHECK_THAT(make_span(row1), elements_are_span(as::mat4_row1(m4)));
  as::mat_row(m4, 1, r1);
  CHECK_THAT(make_span(row1), elements_are_span(as::mat_row(m4, 1)));
  CHECK(row1[1] == Approx(as::mat_row(m4, 1)[1]).epsilon(g_epsilon));

  const real row2[] = {3.0_r, 7.0_r, 11.0_r, 15.0_r};
  const vec4 r2 = as::vec4_from_arr(row2);
  as::mat4_row2(m4, r2);
  CHECK_THAT(make_span(row2), elements_are_span(as::mat4_row2(m4)));
  as::mat_row(m4, 2, r2);
  CHECK_THAT(make_span(row2), elements_are_span(as::mat_row(m4, 2)));
  CHECK(row2[2] == Approx(as::mat_row(m4, 2)[2]).epsilon(g_epsilon));

  const real row3[] = {4.0_r, 8.0_r, 12.0_r, 16.0_r};
  const vec4 r3 = as::vec4_from_arr(row3);
  as::mat4_row3(m4, r3);
  CHECK_THAT(make_span(row3), elements_are_span(as::mat4_row3(m4)));
  as::mat_row(m4, 3, r3);
  CHECK_THAT(make_span(row3), elements_are_span(as::mat_row(m4, 3)));
  CHECK(row3[3] == Approx(as::mat_row(m4, 3)[3]).epsilon(g_epsilon));
#elif defined AS_ROW_MAJOR
  const real row0[] = {1.0_r, 2.0_r, 3.0_r, 4.0_r};
  const vec4 c0 = as::vec4_from_arr(row0);
  as::mat4_row0(m4, c0);
  CHECK_THAT(make_span(row0), elements_are_span(as::mat4_row0(m4)));
  as::mat_row(m4, 0, c0);
  CHECK(row0[0] == Approx(as::mat_row(m4, 0)[0]).epsilon(g_epsilon));

  const real row1[] = {5.0_r, 6.0_r, 7.0_r, 8.0_r};
  const vec4 c1 = as::vec4_from_arr(row1);
  as::mat4_row1(m4, c1);
  CHECK_THAT(make_span(row1), elements_are_span(as::mat4_row1(m4)));
  as::mat_row(m4, 1, c1);
  CHECK_THAT(make_span(row1), elements_are_span(as::mat_row(m4, 1)));
  CHECK(row1[1] == Approx(as::mat_row(m4, 1)[1]).epsilon(g_epsilon));

  const real row2[] = {9.0_r, 10.0_r, 11.0_r, 12.0_r};
  const vec4 c2 = as::vec4_from_arr(row2);
  as::mat4_row2(m4, c2);
  CHECK_THAT(make_span(row2), elements_are_span(as::mat4_row2(m4)));
  as::mat_row(m4, 2, c2);
  CHECK_THAT(make_span(row2), elements_are_span(as::mat_row(m4, 2)));
  CHECK(row2[2] == Approx(as::mat_row(m4, 2)[2]).epsilon(g_epsilon));

  const real row3[] = {13.0_r, 14.0_r, 15.0_r, 16.0_r};
  const vec4 c3 = as::vec4_from_arr(row3);
  as::mat4_row3(m4, c3);
  CHECK_THAT(make_span(row3), elements_are_span(as::mat4_row3(m4)));
  as::mat_row(m4, 3, c3);
  CHECK_THAT(make_span(row3), elements_are_span(as::mat_row(m4, 3)));
  CHECK(row3[3] == Approx(as::mat_row(m4, 3)[3]).epsilon(g_epsilon));

  const real col0[] = {1.0_r, 5.0_r, 9.0_r, 13.0_r};
  const vec4 r0 = as::vec4_from_arr(col0);
  as::mat4_col0(m4, r0);
  CHECK_THAT(make_span(col0), elements_are_span(as::mat4_col0(m4)));
  as::mat_col(m4, 0, r0);
  CHECK_THAT(make_span(col0), elements_are_span(as::mat_col(m4, 0)));
  CHECK(col0[0] == Approx(as::mat_col(m4, 0)[0]).epsilon(g_epsilon));

  const real col1[] = {2.0_r, 6.0_r, 10.0_r, 14.0_r};
  const vec4 r1 = as::vec4_from_arr(col1);
  as::mat4_col1(m4, r1);
  CHECK_THAT(make_span(col1), elements_are_span(as::mat4_col1(m4)));
  as::mat_col(m4, 1, r1);
  CHECK_THAT(make_span(col1), elements_are_span(as::mat_col(m4, 1)));
  CHECK(col1[1] == Approx(as::mat_col(m4, 1)[1]).epsilon(g_epsilon));

  const real col2[] = {3.0_r, 7.0_r, 11.0_r, 15.0_r};
  const vec4 r2 = as::vec4_from_arr(col2);
  as::mat4_col2(m4, r2);
  CHECK_THAT(make_span(col2), elements_are_span(as::mat4_col2(m4)));
  as::mat_col(m4, 2, r2);
  CHECK_THAT(make_span(col2), elements_are_span(as::mat_col(m4, 2)));
  CHECK(col2[2] == Approx(as::mat_col(m4, 2)[2]).epsilon(g_epsilon));

  const real col3[] = {4.0_r, 8.0_r, 12.0_r, 16.0_r};
  const vec4 r3 = as::vec4_from_arr(col3);
  as::mat4_col3(m4, r3);
  CHECK_THAT(make_span(col3), elements_are_span(as::mat4_col3(m4)));
  as::mat_col(m4, 3, r3);
  CHECK_THAT(make_span(col3), elements_are_span(as::mat_col(m4, 3)));
  CHECK(col3[3] == Approx(as::mat_col(m4, 3)[3]).epsilon(g_epsilon));
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

TEST_CASE("mat_mat4_from_mat3_and_vec3", "[as_mat]")
{
  using gsl::make_span;

  // clang-format off
  mat3 m3 {
    1.0_r, 2.0_r, 3.0_r,
    4.0_r, 5.0_r, 6.0_r,
    7.0_r, 8.0_r, 9.0_r
  };
  // clang-format on

  vec3 v3{10.0_r, 11.0_r, 12.0_r};

  // clang-format off
  const real mat3_and_vec3[] = {
    1.0_r,  2.0_r,  3.0_r,  0.0_r,
    4.0_r,  5.0_r,  6.0_r,  0.0_r,
    7.0_r,  8.0_r,  9.0_r,  0.0_r,
    10.0_r, 11.0_r, 12.0_r, 1.0_r
  };
  // clang-format on

  {
    mat4 m4;
    m4 = mat4{m3, v3};

    CHECK_THAT(make_span(mat3_and_vec3), elements_are_span(m4));
  }

  {
    mat4 m4;
    m4 = as::mat4_from_mat3_vec3(m3, v3);

    CHECK_THAT(make_span(mat3_and_vec3), elements_are_span(m4));
  }

  {
    mat4 m4;
    m4 = as::mat4_from_mat3(m3);

    // clang-format off
    const real mat3_and_zero[] = {
      1.0_r, 2.0_r, 3.0_r, 0.0_r,
      4.0_r, 5.0_r, 6.0_r, 0.0_r,
      7.0_r, 8.0_r, 9.0_r, 0.0_r,
      0.0_r, 0.0_r, 0.0_r, 1.0_r
    };
    // clang-format on

    CHECK_THAT(make_span(mat3_and_zero), elements_are_span(m4));
  }

  {
    mat4 m4;
    m4 = as::mat4_from_vec3(vec3{10.0_r, 20.0_r, 30.0_r});

    // clang-format off
    const real zero_and_vec3[] = {
      1.0_r, 0.0_r, 0.0_r, 0.0_r,
      0.0_r, 1.0_r, 0.0_r, 0.0_r,
      0.0_r, 0.0_r, 1.0_r, 0.0_r,
      10.0_r, 20.0_r, 30.0_r, 1.0_r
    };
    // clang-format on

    CHECK_THAT(make_span(zero_and_vec3), elements_are_span(m4));
  }
}

TEST_CASE("const_elem_access_mat_const", "[as_mat]")
{
  using gsl::make_span;

  // clang-format off
  const mat<real, 5> m5(
    1.0_r, 2.0_r, 3.0_r, 4.0_r, 5.0_r,
    6.0_r, 7.0_r, 8.0_r, 9.0_r, 10.0_r,
    11.0_r, 12.0_r, 13.0_r, 15.0_r, 15.0_r,
    16.0_r, 17.0_r, 18.0_r, 19.0_r, 20.0_r,
    21.0_r, 22.0_r, 23.0_r, 24.0_r, 25.0_r);

  const real mat_arr[] = {
    m5[0], m5[1], m5[2], m5[3], m5[4],
    m5[5], m5[6], m5[7], m5[8], m5[9],
    m5[10], m5[11], m5[12], m5[13], m5[14],
    m5[15], m5[16], m5[17], m5[18], m5[19],
    m5[20], m5[21], m5[22], m5[23], m5[24]
  };
  // clang-format on

  CHECK_THAT(make_span(mat_arr), elements_are_span(m5));
}

TEST_CASE("elem_access_mat", "[as_mat]")
{
  using gsl::make_span;

  // clang-format off
  mat<real, 5> m5(
    1.0_r, 2.0_r, 3.0_r, 4.0_r, 5.0_r,
    6.0_r, 7.0_r, 8.0_r, 9.0_r, 10.0_r,
    11.0_r, 12.0_r, 13.0_r, 15.0_r, 15.0_r,
    16.0_r, 17.0_r, 18.0_r, 19.0_r, 20.0_r,
    21.0_r, 22.0_r, 23.0_r, 24.0_r, 25.0_r
  );
  // clang-format on

  m5[15] = 100.0_r;
  m5[20] = 200.0_r;

  // clang-format off
  const real mat_arr[] = {
    m5[0], m5[1], m5[2], m5[3], m5[4],
    m5[5], m5[6], m5[7], m5[8], m5[9],
    m5[10], m5[11], m5[12], m5[13], m5[14],
    100.0_r, m5[16], m5[17], m5[18], m5[19],
    200.0_r, m5[21], m5[22], m5[23], m5[24]
  };
  // clang-format on

  CHECK_THAT(make_span(mat_arr), elements_are_span(m5));
}

TEST_CASE("elem_access_mat4_const", "[as_mat]")
{
  using gsl::make_span;

  // clang-format off
  const mat4 m4(
    1.0_r, 2.0_r, 3.0_r, 4.0_r,
    5.0_r, 6.0_r, 7.0_r, 8.0_r,
    9.0_r, 10.0_r, 11.0_r, 12.0_r,
    13.0_r, 14.0_r, 15.0_r, 16.0_r
  );

  const real mat_arr[] = {
    1.0_r, 2.0_r, 3.0_r, 4.0_r,
    5.0_r, 6.0_r, 7.0_r, 8.0_r,
    9.0_r, 10.0_r, 11.0_r, 12.0_r,
    13.0_r, 14.0_r, 15.0_r, 16.0_r,
  };
  // clang-format on

  const real mat4_8 = m4[8];
  CHECK(mat4_8 == Approx(mat_arr[8]).epsilon(g_epsilon));
  CHECK(mat4_8 == Approx(9.0_r).epsilon(g_epsilon));

  CHECK_THAT(make_span(mat_arr), elements_are_span(m4));
}

TEST_CASE("rvalue_elem_access_mat2_3_4", "[as_mat]")
{
  using gsl::make_span;

  auto make_mat2 = []() { return mat<real, 2>{5.0_r, 10.0_r, 15.0_r, 20.0_r}; };
  CHECK(make_mat2()[0] == Approx(5.0_r).epsilon(g_epsilon));
  CHECK(make_mat2()[1] == Approx(10.0_r).epsilon(g_epsilon));
  CHECK(make_mat2()[2] == Approx(15.0_r).epsilon(g_epsilon));
  CHECK(make_mat2()[3] == Approx(20.0_r).epsilon(g_epsilon));

  // clang-format off
  auto make_mat3 = []() {
    return mat3{
      1.0_r, 2.0_r, 3.0_r,
      4.0_r, 5.0_r, 6.0_r,
      7.0_r, 8.0_r, 9.0_r
    };
  };
  // clang-format on

  CHECK(make_mat3()[4] == Approx(5.0_r).epsilon(g_epsilon));

  // clang-format off
  auto make_mat4 = [](){
    return mat4 {
      1.0_r, 2.0_r, 3.0_r, 4.0_r,
      5.0_r, 6.0_r, 7.0_r, 8.0_r,
      9.0_r, 10.0_r, 11.0_r, 12.0_r,
      13.0_r, 14.0_r, 15.0_r, 16.0_r
    };
  };
  // clang-format on

  CHECK(make_mat4()[7] == Approx(8.0_r).epsilon(g_epsilon));
  CHECK(make_mat4()[15] == Approx(16.0_r).epsilon(g_epsilon));
}

TEST_CASE("mat_dimensions_are_valid", "[as_mat]")
{
  index mat3_rows;
  mat3_rows = mat3::rows();
  CHECK(mat3_rows == 3);

  index mat3_cols;
  mat3_cols = mat3::cols();
  CHECK(mat3_cols == 3);

  index mat3_dim;
  mat3_dim = mat3::dim();
  CHECK(mat3_dim == 3);

  index mat3_size;
  mat3_size = mat3::size();
  CHECK(mat3_size == 9);

  index mat4_rows;
  mat4_rows = mat4::rows();
  CHECK(mat4_rows == 4);

  index mat4_cols;
  mat4_cols = mat4::cols();
  CHECK(mat4_cols == 4);

  index mat4_dim;
  mat4_dim = mat4::dim();
  CHECK(mat4_dim == 4);

  index mat4_size;
  mat4_size = mat4::size();
  CHECK(mat4_size == 16);

  using mat5 = mat<real, 5>;

  index mat5_rows;
  mat5_rows = mat5::rows();
  CHECK(mat5_rows == 5);

  index mat5_cols;
  mat5_cols = mat5::cols();
  CHECK(mat5_cols == 5);

  index mat5_dim;
  mat5_dim = mat5::dim();
  CHECK(mat5_dim == 5);

  index mat5_size;
  mat5_size = mat5::size();
  CHECK(mat5_size == 25);
}

TEST_CASE("multiply_same_size", "[as_mat]")
{
  using gsl::make_span;

  // clang-format off
  const mat3 mat3_a {
    1.0_r, 2.0_r, 3.0_r,
    4.0_r, 5.0_r, 6.0_r,
    7.0_r, 8.0_r, 9.0_r
  };

  const mat3 mat3_b {
    9.0_r, 8.0_r, 7.0_r,
    6.0_r, 5.0_r, 4.0_r,
    3.0_r, 2.0_r, 1.0_r
  };

  const real mat_arr[] = {
    30.0_r, 24.0_r, 18.0_r,
    84.0_r, 69.0_r, 54.0_r,
    138.0_r, 114.0_r, 90.0_r
  };
  // clang-format on

  mat3 result;
#ifdef AS_ROW_MAJOR
  result = mat3_a * mat3_b;
#elif defined AS_COL_MAJOR
  result = mat3_b * mat3_a;
#endif

  CHECK_THAT(make_span(mat_arr), elements_are_span(result));
}

TEST_CASE("multiply_mul", "[as_mat]")
{
  using gsl::make_span;

  mat3 rotate_x = as::mat3_rotation_x(radians(30.0_r));
  mat3 rotate_y = as::mat3_rotation_y(radians(30.0_r));
  mat3 rotate_z = as::mat3_rotation_z(radians(30.0_r));

  mat3 result_mul;
  result_mul = as::mat_mul(as::mat_mul(rotate_x, rotate_y), rotate_z);

  mat3 result;
#ifdef AS_ROW_MAJOR
  result = rotate_x * rotate_y * rotate_z;
#elif defined AS_COL_MAJOR
  result = rotate_z * rotate_y * rotate_x;
#endif

  real result_arr[9];
  as::mat_to_arr(result, result_arr);

  CHECK_THAT(make_span(result_arr), elements_are_span(result_mul));
  CHECK(as::mat_near(result_mul, result));
}

TEST_CASE("near_mat", "[as_mat]")
{
  // clang-format off
  const mat4 mat_a = as::mat4{
    1.0_r,  2.0_r,  3.0_r,  4.0_r,
    5.0_r,  6.0_r,  7.0_r,  8.0_r,
    9.0_r,  10.0_r, 11.0_r, 12.0_r,
    13.0_r, 14.0_r, 15.0_r, 16.0_r
  };
  // clang-format on

  const mat4 mat_a_again = mat_a;

  CHECK(as::mat_near(mat_a, mat_a_again));
}

TEST_CASE("not_near_mat", "[as_mat]")
{
  // clang-format off
  const mat4 mat_a = as::mat4{
    1.0_r,  2.0_r,  3.0_r,  4.0_r,
    5.0_r,  6.0_r,  7.0_r,  8.0_r,
    9.0_r,  10.0_r, 11.0_r, 12.0_r,
    13.0_r, 14.0_r, 15.0_r, 16.0_r
  };

  const mat4 mat_b = as::mat4{
    3.0_r,  3.0_r,  2.0_r,  1.0_r,
    8.0_r,  7.0_r,  6.0_r,  5.0_r,
    12.0_r, 11.0_r, 10.0_r, 9.0_r,
    16.0_r, 15.0_r, 14.0_r, 13.0_r
  };
  // clang-format on

  CHECK(!as::mat_near(mat_a, mat_b));
}

TEST_CASE("multiply_vector", "[as_mat]")
{
  using gsl::make_span;

  // clang-format off
  const mat3 m {
    1.0_r, 2.0_r, 3.0_r,
    4.0_r, 5.0_r, 6.0_r,
    7.0_r, 8.0_r, 9.0_r
  };
  // clang-format on

  const vec3 v{11.0_r, 12.0_r, 13.0_r};

  vec3 result;
#ifdef AS_ROW_MAJOR
  result = v * m;
#elif defined AS_COL_MAJOR
  result = m * v;
#endif // AS_ROW_MAJOR ? AS_COL_MAJOR

  const real vec_arr[] = {150.0_r, 186.0_r, 222.0_r};
  CHECK_THAT(make_span(vec_arr), elements_are_span(result));
}

TEST_CASE("multiply_scalar", "[as_mat]")
{
  using gsl::make_span;

  // clang-format off
  const mat3 m3 {
    1.0_r, 2.0_r, 3.0_r,
    4.0_r, 5.0_r, 6.0_r,
    7.0_r, 8.0_r, 9.0_r
  };
  // clang-format on

  mat3 result33 = m3 * 2.0_r;

  // clang-format off
  const real mat3_arr[] = {
    2.0_r, 4.0_r, 6.0_r,
    8.0_r, 10.0_r, 12.0_r,
    14.0_r, 16.0_r, 18.0_r
  };
  // clang-format on

  CHECK_THAT(make_span(mat3_arr), elements_are_span(result33));

  // clang-format off
  const mat4 m4 {
    2.0_r, 4.0_r, 6.0_r, 8.0_r,
    10.0_r, 12.0_r, 14.0_r, 16.0_r,
    18.0_r, 20.0_r, 22.0_r, 24.0_r,
    26.0_r, 28.0_r, 30.0_r, 32.0_r
  };

  const mat4 result4 = m4 * 2.0_r;

  const real mat4_arr[] = {
    4.0_r, 8.0_r, 12.0_r, 16.0_r,
    20.0_r, 24.0_r, 28.0_r, 32.0_r,
    36.0_r, 40.0_r, 44.0_r, 48.0_r,
    52.0_r, 56.0_r, 60.0_r, 64.0_r
  };
  // clang-format on

  CHECK_THAT(make_span(mat4_arr), elements_are_span(result4));
}

TEST_CASE("mat_from_arr", "[as_mat]")
{
  using gsl::make_span;

  {
    // clang-format off
    real elems[] = {
      1.0_r,  2.0_r,  3.0_r,  4.0_r,
      5.0_r,  6.0_r,  7.0_r,  8.0_r,
      9.0_r,  10.0_r, 11.0_r, 12.0_r,
      13.0_r, 14.0_r, 15.0_r, 16.0_r
    };
    // clang-format on

    const mat4 mat4_a = as::mat_from_arr<real, 4>(elems);
    CHECK_THAT(make_span(elems), elements_are_span(mat4_a));

    const mat4 mat4_b = as::mat4_from_arr(elems);
    CHECK_THAT(make_span(elems), elements_are_span(mat4_b));

    // clang-format off
    int64_t elems_long[] = {
      1,  2,  3,  4,
      5,  6,  7,  8,
      9,  10, 11, 12,
      13, 14, 15, 16
    };
    // clang-format on

    const as::mat4l mat4_c = as::mat4_from_arr(elems_long);
    CHECK_THAT(make_span(elems_long), elements_are_span(mat4_c));
  }

  {
    // clang-format off
    real elems[] = {
      1.0_r, 2.0_r, 3.0_r,
      4.0_r, 5.0_r, 6.0_r,
      7.0_r, 8.0_r, 9.0_r
    };
    // clang-format on

    const mat3 mat3_a = as::mat_from_arr<real, 3>(elems);
    CHECK_THAT(make_span(elems), elements_are_span(mat3_a));

    const mat3 mat3_b = as::mat3_from_arr(elems);
    CHECK_THAT(make_span(elems), elements_are_span(mat3_b));
  }
}

TEST_CASE("mat_from_ptr", "[as_mat]")
{
  using gsl::make_span;

  {
    // clang-format off
    real elems[] = {
      1.0_r, 2.0_r, 3.0_r, 4.0_r,
      5.0_r, 6.0_r, 7.0_r, 8.0_r,
      9.0_r, 10.0_r, 11.0_r, 12.0_r,
      13.0_r, 14.0_r, 15.0_r, 16.0_r
    };
    // clang-format on

    const mat4 mat4_a = as::mat_from_ptr<real, 4>(elems);
    CHECK_THAT(make_span(elems), elements_are_span(mat4_a));

    const mat4 mat4_b = as::mat4_from_ptr(elems);
    CHECK_THAT(make_span(elems), elements_are_span(mat4_b));

    // clang-format off
    int64_t elems_long[] = {
      1, 2, 3, 4,
      5, 6, 7, 8,
      9, 10, 11, 12,
      13, 14, 15, 16
    };
    // clang-format on

    const as::mat4l mat4_c = as::mat4_from_ptr(elems_long);
    CHECK_THAT(make_span(elems_long), elements_are_span(mat4_c));
  }

  {
    // clang-format off
    real elems[] = {
      1.0_r, 2.0_r, 3.0_r,
      4.0_r, 5.0_r, 6.0_r,
      7.0_r, 8.0_r, 9.0_r
    };
    // clang-format on

    const mat3 mat3_a = as::mat_from_ptr<real, 3>(elems);
    CHECK_THAT(make_span(elems), elements_are_span(mat3_a));

    const mat3 mat3_b = as::mat3_from_ptr(elems);
    CHECK_THAT(make_span(elems), elements_are_span(mat3_b));
  }
}

TEST_CASE("mat_to_arr", "[as_mat]")
{
  using gsl::make_span;

  // clang-format off
  const mat3 m3 {
    1.0_r, 2.0_r, 3.0_r,
    4.0_r, 5.0_r, 6.0_r,
    7.0_r, 8.0_r, 9.0_r
  };
  // clang-format on

  real mat3_arr[9];
  as::mat_to_arr(m3, mat3_arr);

  CHECK_THAT(make_span(mat3_arr), elements_are_span(m3));
}

TEST_CASE("mat_transpose", "[as_mat]")
{
  using gsl::make_span;

  {
    // clang-format off
    const mat3 m3 {
      1.0_r, 2.0_r, 3.0_r,
      4.0_r, 5.0_r, 6.0_r,
      7.0_r, 8.0_r, 9.0_r
    };

    const mat3 mat3_transposed = as::mat_transpose(m3);

    const real mat3_transposed_ref[] {
        1.0_r, 4.0_r, 7.0_r,
        2.0_r, 5.0_r, 8.0_r,
        3.0_r, 6.0_r, 9.0_r
    };
    // clang-format on

    CHECK_THAT(
      make_span(mat3_transposed_ref), elements_are_span(mat3_transposed));
  }

  {
    // clang-format off
    const mat4 m4 = {
      1.0_r, 2.0_r, 3.0_r, 4.0_r,
      5.0_r, 6.0_r, 7.0_r, 8.0_r,
      9.0_r, 10.0_r, 11.0_r, 12.0_r,
      13.0_r, 14.0_r, 15.0_r, 16.0_r
    };

    const mat4 mat4_transposed = as::mat_transpose(m4);

    const real mat4_transposed_reference[] {
      1.0_r, 5.0_r, 9.0_r, 13.0_r,
      2.0_r, 6.0_r, 10.0_r, 14.0_r,
      3.0_r, 7.0_r, 11.0_r, 15.0_r,
      4.0_r, 8.0_r, 12.0_r, 16.0_r
    };
    // clang-format on

    CHECK_THAT(
      make_span(mat4_transposed_reference), elements_are_span(mat4_transposed));
  }
}

TEST_CASE("mat_identity", "[as_mat]")
{
  using gsl::make_span;

  {
    mat3 mat3_identity;
    mat3_identity = mat3::identity();

    // clang-format off
    const real mat3_identity_ref[] {
      1.0_r, 0.0_r, 0.0_r,
      0.0_r, 1.0_r, 0.0_r,
      0.0_r, 0.0_r, 1.0_r
    };
    // clang-format on

    CHECK_THAT(make_span(mat3_identity_ref), elements_are_span(mat3_identity));
  }

  {
    mat4 mat4_identity;
    mat4_identity = mat4::identity();

    // clang-format off
    const real mat4_identity_ref[] {
      1.0_r, 0.0_r, 0.0_r, 0.0_r,
      0.0_r, 1.0_r, 0.0_r, 0.0_r,
      0.0_r, 0.0_r, 1.0_r, 0.0_r,
      0.0_r, 0.0_r, 0.0_r, 1.0_r
    };
    // clang-format on

    CHECK_THAT(make_span(mat4_identity_ref), elements_are_span(mat4_identity));
  }

  {
    using mat5 = mat<real, 5>;

    mat5 mat5_identity;
    mat5_identity = mat5::identity();

    // clang-format off
    const real mat5_identity_ref[] {
      1.0_r, 0.0_r, 0.0_r, 0.0_r, 0.0_r,
      0.0_r, 1.0_r, 0.0_r, 0.0_r, 0.0_r,
      0.0_r, 0.0_r, 1.0_r, 0.0_r, 0.0_r,
      0.0_r, 0.0_r, 0.0_r, 1.0_r, 0.0_r,
      0.0_r, 0.0_r, 0.0_r, 0.0_r, 1.0_r
    };
    // clang-format on

    CHECK_THAT(make_span(mat5_identity_ref), elements_are_span(mat5_identity));
  }
}

TEST_CASE("mat_inverse", "[as_mat]")
{
  using gsl::make_span;

  {
    using mat2 = mat<real, 2>;

    // clang-format off
    const mat2 m2 {
      1.0_r, 2.0_r,
      3.0_r, 4.0_r
    };
    // clang-format on

    const mat2 mat2_inverse = as::mat_inverse(m2);
    const real mat2_inverse_ref[]{-2.0_r, 1.0_r, 3.0_r / 2.0_r, -1.0_r / 2.0_r};

    CHECK_THAT(make_span(mat2_inverse_ref), elements_are_span(mat2_inverse));
  }

  {
    // clang-format off
    const mat3 m3 {
      1.0_r, 2.0_r, 3.0_r,
      4.0_r, 5.0_r, 6.0_r,
      7.0_r, 2.0_r, 9.0_r
    };
    // clang-format on

    const mat3 mat3_inverse = as::mat_inverse(m3);

    // clang-format off
    const real mat3_inverse_ref[] {
      -11.0_r/12.0_r, 1.0_r/3.0_r, 1.0_r/12.0_r,
      -1.0_r/6.0_r, 1.0_r/3.0_r, -1.0_r/6.0_r,
      3.0_r/4.0_r, -1.0_r/3.0_r, 1.0_r/12.0_r
    };
    // clang-format on

    CHECK_THAT(make_span(mat3_inverse_ref), elements_are_span(mat3_inverse));
  }

  {
    // clang-format off
    const mat4 m4 = {
      1.0_r, 3.0_r, 5.0_r, 9.0_r,
      1.0_r, 3.0_r, 1.0_r, 7.0_r,
      4.0_r, 3.0_r, 9.0_r, 7.0_r,
      5.0_r, 2.0_r, 0.0_r, 9.0_r
    };
    // clang-format on

    const mat4 mat4_inverse = as::mat_inverse(m4);

    // clang-format off
    const real mat4_inverse_reference[] {
      -13.0_r/47.0_r, 2.0_r/47.0_r, 7.0_r/47.0_r, 6.0_r/47.0_r,
      -5.0_r/8.0_r, 7.0_r/8.0_r, 1.0_r/4.0_r, -1.0_r/4.0_r,
      39.0_r/376.0_r, -53.0_r/376.0_r, 13.0_r/188.0_r, -9.0_r/188.0_r,
      55.0_r/188.0_r, -41.0_r/188.0_r, -13.0_r/94.0_r, 9.0_r/94.0_r
    };
    // clang-format on

    CHECK_THAT(
      make_span(mat4_inverse_reference), elements_are_span(mat4_inverse));
  }
}

TEST_CASE("mat_scale", "[as_mat]")
{
  using gsl::make_span;

  mat3 scale;
  scale = as::mat3_scale(vec3{1.0_r, 2.0_r, 3.0_r});

  // clang-format off
  const real mat3_scale_reference[] {
    1.0_r, 0.0_r, 0.0_r,
    0.0_r, 2.0_r, 0.0_r,
    0.0_r, 0.0_r, 3.0_r
  };
  // clang-format on

  CHECK_THAT(make_span(mat3_scale_reference), elements_are_span(scale));

  mat3 uniform_scale;
  uniform_scale = as::mat3_scale(5.0_r);

  // clang-format off
  const real mat3_uniform_scale_reference[] {
    5.0_r, 0.0_r, 0.0_r,
    0.0_r, 5.0_r, 0.0_r,
    0.0_r, 0.0_r, 5.0_r
  };
  // clang-format on

  CHECK_THAT(
    make_span(mat3_uniform_scale_reference), elements_are_span(uniform_scale));
}

TEST_CASE("mat3_from_mat4", "[as_mat]")
{
  using gsl::make_span;

  mat4 m4;
  m4 = mat4::identity();

  mat3 m3;
  m3 = as::mat3_from_mat4(m4);

  // clang-format off
  const real mat3_identity_ref[] {
    1.0_r, 0.0_r, 0.0_r,
    0.0_r, 1.0_r, 0.0_r,
    0.0_r, 0.0_r, 1.0_r
  };
  // clang-format on

  CHECK_THAT(make_span(mat3_identity_ref), elements_are_span(m3));
}

TEST_CASE("mat3_rotation_axis", "[as_mat]")
{
  using gsl::make_span;

  {
    mat3 rotation_axis =
      as::mat3_rotation_axis(vec3::axis_x(), radians(90.0_r));
    real result_reference[] = {0.0_r, -1.0_r, 0.0_r};

    vec3 result;
#ifdef AS_ROW_MAJOR
    result = vec3::axis_z() * rotation_axis;
#elif defined AS_COL_MAJOR
    result = rotation_axis * vec3::axis_z();
#endif // AS_ROW_MAJOR ? AS_COL_MAJOR

    // note - checking against 0.0_r requires margin
    CHECK_THAT(
      make_span(result_reference), elements_are_span(result).margin(g_epsilon));
  }

  {
    mat3 rotation_axis =
      as::mat3_rotation_axis(vec3::axis_y(), radians(90.0_r));
    real result_reference[] = {0.0_r, 0.0_r, -1.0_r};

    vec3 result;
#ifdef AS_ROW_MAJOR
    result = vec3::axis_x() * rotation_axis;
#elif defined AS_COL_MAJOR
    result = rotation_axis * vec3::axis_x();
#endif // AS_ROW_MAJOR ? AS_COL_MAJOR

    // note - checking against 0.0_r requires margin
    CHECK_THAT(
      make_span(result_reference), elements_are_span(result).margin(g_epsilon));
  }
}

TEST_CASE("mat3_rotate_xyz", "[as_mat]")
{
  using gsl::make_span;

  {
    mat3 rotation_axis =
      as::mat3_rotation_xyz(radians(45.0_r), radians(90.0_r), radians(45.0_r));
    real result_reference[] = {0.0_r, 1.0_r, 0.0_r};

    vec3 result;
#ifdef AS_ROW_MAJOR
    result = vec3::axis_y() * rotation_axis;
#elif defined AS_COL_MAJOR
    result = rotation_axis * vec3::axis_y();
#endif // AS_ROW_MAJOR ? AS_COL_MAJOR

    // note - checking against 0.0_r requires margin
    CHECK_THAT(
      make_span(result_reference), elements_are_span(result).margin(g_epsilon));
  }

  {
    mat3 rotation_axis = as::mat3_rotation_xyz(
      radians(-180.0_r), radians(90.0_r), radians(-90.0_r));
    real result_reference[] = {0.0_r, 1.0_r, 0.0_r};

    vec3 result;
#ifdef AS_ROW_MAJOR
    result = vec3::axis_z() * rotation_axis;
#elif defined AS_COL_MAJOR
    result = rotation_axis * vec3::axis_z();
#endif // AS_ROW_MAJOR ? AS_COL_MAJOR

    // note - checking against 0.0_r requires margin
    CHECK_THAT(
      make_span(result_reference), elements_are_span(result).margin(g_epsilon));
  }
}

TEST_CASE("mat3_rotate_zxy", "[as_mat]")
{
  using gsl::make_span;

  {
    mat3 rotation_axis =
      as::mat3_rotation_zxy(radians(90.0_r), radians(90.0_r), radians(0.0_r));
    real result_reference_y[] = {1.0_r, 0.0_r, 0.0_r};
    real result_reference_z[] = {0.0_r, -1.0_r, 0.0_r};

    vec3 result_y;
    vec3 result_z;
#ifdef AS_ROW_MAJOR
    result_y = vec3::axis_y() * rotation_axis;
    result_z = vec3::axis_z() * rotation_axis;
#elif defined AS_COL_MAJOR
    result_y = rotation_axis * vec3::axis_y();
    result_z = rotation_axis * vec3::axis_z();
#endif // AS_ROW_MAJOR ? AS_COL_MAJOR

    // note - checking against 0.0_r requires margin
    CHECK_THAT(
      make_span(result_reference_y),
      elements_are_span(result_y).margin(g_epsilon));

    CHECK_THAT(
      make_span(result_reference_z),
      elements_are_span(result_z).margin(g_epsilon));
  }

  {
    mat3 rotation_axis =
      as::mat3_rotation_zxy(radians(0.0_r), radians(-90.0_r), radians(-90.0_r));
    real result_reference_x[] = {0.0_r, -1.0_r, 0.0_r};
    real result_reference_y[] = {0.0_r, 0.0_r, 1.0_r};

    vec3 result_x;
    vec3 result_y;
#ifdef AS_ROW_MAJOR
    result_x = vec3::axis_x() * rotation_axis;
    result_y = vec3::axis_y() * rotation_axis;
#elif defined AS_COL_MAJOR
    result_x = rotation_axis * vec3::axis_x();
    result_y = rotation_axis * vec3::axis_y();
#endif // AS_ROW_MAJOR ? AS_COL_MAJOR

    // note - checking against 0.0_r requires margin
    CHECK_THAT(
      make_span(result_reference_x),
      elements_are_span(result_x).margin(g_epsilon));

    CHECK_THAT(
      make_span(result_reference_y),
      elements_are_span(result_y).margin(g_epsilon));
  }
}

TEST_CASE("mat3_from_quat", "[as_mat]")
{
  using gsl::make_span;

  {
    mat3 rotation_axis_mat =
      as::mat3_rotation_zxy(radians(90.0_r), radians(90.0_r), radians(0.0_r));
    quat rotation_axis_quat =
      as::quat_rotation_zxy(radians(90.0_r), radians(90.0_r), radians(0.0_r));

    mat3 rotation_axis_mat_from_quat;
    rotation_axis_mat_from_quat = as::mat3_from_quat(rotation_axis_quat);

    real expected[9];
    as::mat_to_arr(rotation_axis_mat_from_quat, expected);

    // note - checking against 0.0 requires margin
    CHECK_THAT(
      make_span(expected),
      elements_are_span(rotation_axis_mat).margin(g_epsilon));
  }
}

TEST_CASE("mat3_from_affine", "[as_mat]")
{
  using gsl::make_span;

  mat3 rotation =
    mat3(2.0_r, 4.0_r, 6.0_r, 8.0_r, 10.0_r, 12.0_r, 14.0_r, 16.0_r, 18.0_r);

  affine a = affine(rotation, vec3::zero());

  mat3 result = mat3_from_affine(a);

  real expected[9];
  as::mat_to_arr(result, expected);

  CHECK_THAT(
    make_span(expected), elements_are_span(rotation).margin(g_epsilon));
}

TEST_CASE("mat4_from_affine", "[as_mat]")
{
  using gsl::make_span;

  {
    affine a(
      as::mat3(
        2.0_r, 4.0_r, 6.0_r, 8.0_r, 10.0_r, 12.0_r, 14.0_r, 16.0_r, 18.0_r),
      as::vec3(1.0_r, 2.0_r, 3.0_r));

    as::mat4 m4;
    m4 = as::mat4_from_affine(a);

    real expected[16] = {2.0_r,  4.0_r, 6.0_r,  0.0_r,  8.0_r,  10.0_r,
                         12.0_r, 0.0_r, 14.0_r, 16.0_r, 18.0_r, 0.0_r,
                         1.0_r,  2.0_r, 3.0_r,  1.0_r};

    // note - checking against 0.0 requires margin
    CHECK_THAT(make_span(expected), elements_are_span(m4).margin(g_epsilon));
  }
}

TEST_CASE("mat3_rotate_x_y_z_separate", "[as_mat]")
{
  using gsl::make_span;

  {
    mat3 axis_x = as::mat3_rotation_x(radians(45.0_r));
    mat3 axis_y = as::mat3_rotation_y(radians(90.0_r));
    mat3 axis_z = as::mat3_rotation_z(radians(45.0_r));

    real result_reference[] = {0.0_r, 1.0_r, 0.0_r};

    vec3 result;
#ifdef AS_ROW_MAJOR
    result = vec3::axis_y() * axis_x * axis_y * axis_z;
#elif defined AS_COL_MAJOR
    result = axis_z * axis_y * axis_x * vec3::axis_y();
#endif // AS_ROW_MAJOR ? AS_COL_MAJOR

    // note - checking against 0.0_r requires margin
    CHECK_THAT(
      make_span(result_reference), elements_are_span(result).margin(g_epsilon));
  }

  {
    mat3 axis_x = as::mat3_rotation_x(radians(-180.0_r));
    mat3 axis_y = as::mat3_rotation_y(radians(90.0_r));
    mat3 axis_z = as::mat3_rotation_z(radians(-90.0_r));

    real result_reference[] = {0.0_r, 1.0_r, 0.0_r};

    vec3 result;
#ifdef AS_ROW_MAJOR
    result = vec3::axis_z() * axis_x * axis_y * axis_z;
#elif defined AS_COL_MAJOR
    result = axis_z * axis_y * axis_x * vec3::axis_z();
#endif // AS_ROW_MAJOR ? AS_COL_MAJOR

    // note - checking against 0.0_r requires margin
    CHECK_THAT(
      make_span(result_reference), elements_are_span(result).margin(g_epsilon));
  }
}

TEST_CASE("row_col_access", "[as_mat]")
{
  {
    index offset;
    offset = as::mat_rc(0, 0, 2);
    CHECK(offset == 0);
  }

  {
    index offset;
    offset = as::mat3_rc(1, 1);
    CHECK(offset == 4);
  }

  {
    index offset;
    offset = as::mat4_rc(2, 2);
    CHECK(offset == 10);
  }

  {
    index offset;
    offset = as::mat_rc(3, 2, 4);
#ifdef AS_COL_MAJOR
    CHECK(offset == 11);
#elif defined AS_ROW_MAJOR
    CHECK(offset == 14);
#endif
  }
}

TEST_CASE("mat4_shear", "[as_mat]")
{
  using gsl::make_span;

  {
    mat4 shear_about_x;
    shear_about_x = as::mat4_shear_x(1.0_r, 0.0_r);

    const vec3 position(1.0_r, 0.0_r, 0.0_r);

    vec3 result;
    result =
      as::affine_transform_pos(as::affine_from_mat4(shear_about_x), position);

    CHECK_THAT(arr(1.0_r, 1.0_r, 0.0_r), elements_are_array(result));
  }

  {
    mat4 shear_about_x;
    shear_about_x = as::mat4_shear_x(0.0_r, 1.0_r);

    const vec3 position{1.0_r, 0.0_r, 0.0_r};

    vec3 result;
    result =
      as::affine_transform_pos(as::affine_from_mat4(shear_about_x), position);

    CHECK_THAT(arr(1.0_r, 0.0_r, 1.0_r), elements_are_array(result));
  }

  {
    mat4 shear_about_y;
    shear_about_y = as::mat4_shear_y(1.0_r, 0.0_r);

    const vec3 position{1.0_r, 1.0_r, 0.0_r};

    vec3 result;
    result =
      as::affine_transform_pos(as::affine_from_mat4(shear_about_y), position);

    CHECK_THAT(arr(2.0_r, 1.0_r, 0.0_r), elements_are_array(result));
  }

  {
    mat4 shear_about_y;
    shear_about_y = as::mat4_shear_y(0.0_r, 1.0_r);

    const vec3 position{1.0_r, 1.0_r, 0.0_r};

    vec3 result;
    result =
      as::affine_transform_pos(as::affine_from_mat4(shear_about_y), position);

    CHECK_THAT(arr(1.0_r, 1.0_r, 1.0_r), elements_are_array(result));
  }

  {
    mat4 shear_about_z;
    shear_about_z = as::mat4_shear_z(1.0_r, 0.0_r);

    const vec3 position{0.0_r, 0.0_r, 1.0_r};

    vec3 result;
    result =
      as::affine_transform_pos(as::affine_from_mat4(shear_about_z), position);

    CHECK_THAT(arr(1.0_r, 0.0_r, 1.0_r), elements_are_array(result));
  }

  {
    mat4 shear_about_z;
    shear_about_z = as::mat4_shear_z(0.0_r, 1.0_r);

    const vec3 position{1.0_r, 0.0_r, 1.0_r};

    vec3 result;
    result =
      as::affine_transform_pos(as::affine_from_mat4(shear_about_z), position);

    CHECK_THAT(arr(1.0_r, 1.0_r, 1.0_r), elements_are_array(result));
  }
}

TEST_CASE("mat_basis_access_mat3", "[as_mat]")
{
  using gsl::make_span;

  // clang-format off
  mat3 m3 {
    1.0_r, 2.0_r, 3.0_r,
    4.0_r, 5.0_r, 6.0_r,
    7.0_r, 8.0_r, 9.0_r
  };
  // clang-format on

  const real basis_x[] = {1.0_r, 2.0_r, 3.0_r};
  CHECK_THAT(make_span(basis_x), elements_are_span(as::mat3_basis_x(m3)));
  const real basis_y[] = {4.0_r, 5.0_r, 6.0_r};
  CHECK_THAT(make_span(basis_y), elements_are_span(as::mat3_basis_y(m3)));
  const real basis_z[] = {7.0_r, 8.0_r, 9.0_r};
  CHECK_THAT(make_span(basis_z), elements_are_span(as::mat3_basis_z(m3)));
}

TEST_CASE("mat_dimension_access_mat4", "[as_mat]")
{
  using gsl::make_span;

  // clang-format off
  mat4 m4 {
    1.0_r,  2.0_r,  3.0_r,  4.0_r,
    4.0_r,  5.0_r,  6.0_r,  7.0_r,
    7.0_r,  8.0_r,  9.0_r,  8.0_r,
    10.0_r, 11.0_r, 12.0_r, 9.0_r
  };
  // clang-format on

  CHECK_THAT(
    arr(1.0_r, 2.0_r, 3.0_r, 4.0_r),
    elements_are_array(as::mat4_dimension0(m4)));
  CHECK_THAT(
    arr(4.0_r, 5.0_r, 6.0_r, 7.0_r),
    elements_are_span(as::mat4_dimension1(m4)));
  CHECK_THAT(
    arr(7.0_r, 8.0_r, 9.0_r, 8.0_r),
    elements_are_span(as::mat4_dimension2(m4)));
  CHECK_THAT(
    make_span(arr(10.0_r, 11.0_r, 12.0_r, 9.0_r)),
    elements_are_span(as::mat4_dimension3(m4)));
}

TEST_CASE("mat_basis_access_mat4", "[as_mat]")
{
  using gsl::make_span;

  // clang-format off
  mat4 m4 {
    1.0_r,  2.0_r,  3.0_r,  4.0_r,
    4.0_r,  5.0_r,  6.0_r,  7.0_r,
    7.0_r,  8.0_r,  9.0_r,  8.0_r,
    10.0_r, 11.0_r, 12.0_r, 9.0_r
  };
  // clang-format on

  CHECK_THAT(
    arr(1.0_r, 2.0_r, 3.0_r), elements_are_array(as::mat4_basis_x(m4)));
  CHECK_THAT(arr(4.0_r, 5.0_r, 6.0_r), elements_are_span(as::mat4_basis_y(m4)));
  CHECK_THAT(arr(7.0_r, 8.0_r, 9.0_r), elements_are_span(as::mat4_basis_z(m4)));
  CHECK_THAT(
    make_span(arr(10.0_r, 11.0_r, 12.0_r)),
    elements_are_span(as::mat4_translation(m4)));
}

TEST_CASE("mat_basis_mutate_mat3", "[as_mat]")
{
  using gsl::make_span;

  mat3 m3{};

  const real basis_x[] = {1.0_r, 2.0_r, 3.0_r};
  const vec3 x = as::vec3_from_arr(basis_x);
  as::mat3_basis_x(m3, x);
  CHECK_THAT(make_span(basis_x), elements_are_span(as::mat3_basis_x(m3)));

  const real basis_y[] = {4.0_r, 5.0_r, 6.0_r};
  const vec3 y = as::vec3_from_arr(basis_y);
  as::mat3_basis_y(m3, y);
  CHECK_THAT(make_span(basis_y), elements_are_span(as::mat3_basis_y(m3)));

  const real basis_z[] = {7.0_r, 8.0_r, 9.0_r};
  const vec3 z = as::vec3_from_arr(basis_z);
  as::mat3_basis_z(m3, z);
  CHECK_THAT(make_span(basis_z), elements_are_span(as::mat3_basis_z(m3)));
}

TEST_CASE("mat_dimension_mutate_mat4", "[as_mat]")
{
  using gsl::make_span;

  mat4 m4{};

  const real basis_x[] = {1.0_r, 2.0_r, 3.0_r, 4.0_r};
  const vec4 x = as::vec4_from_arr(basis_x);
  as::mat4_dimension0(m4, x);
  CHECK_THAT(make_span(basis_x), elements_are_span(as::mat4_dimension0(m4)));

  const real basis_y[] = {4.0_r, 5.0_r, 6.0_r, 7.0_r};
  const vec4 y = as::vec4_from_arr(basis_y);
  as::mat4_dimension1(m4, y);
  CHECK_THAT(make_span(basis_y), elements_are_span(as::mat4_dimension1(m4)));

  const real basis_z[] = {7.0_r, 8.0_r, 9.0_r, 10.0_r};
  const vec4 z = as::vec4_from_arr(basis_z);
  as::mat4_dimension2(m4, z);
  CHECK_THAT(make_span(basis_z), elements_are_span(as::mat4_dimension2(m4)));

  const real translation[] = {10.0_r, 11.0_r, 12.0_r, 9.0_r};
  const vec4 t = as::vec4_from_arr(translation);
  as::mat4_dimension3(m4, t);
  CHECK_THAT(
    make_span(translation), elements_are_span(as::mat4_dimension3(m4)));
}

TEST_CASE("mat_basis_mutate_mat4", "[as_mat]")
{
  using gsl::make_span;

  // clang-format off
  mat4 m4 {
    1.0_r,  2.0_r,  3.0_r,  4.0_r,
    4.0_r,  5.0_r,  6.0_r,  7.0_r,
    7.0_r,  8.0_r,  9.0_r,  8.0_r,
    10.0_r, 11.0_r, 12.0_r, 9.0_r
  };
  // clang-format on

  const auto basis_x = vec3(14.0_r, 16.0_r, 18.0_r);
  as::mat4_basis_x(m4, basis_x);
  CHECK_THAT(
    vec4_from_vec3(basis_x, 0.0_r), elements_are(as::mat4_dimension0(m4)));

  const auto basis_y = vec3(22.0_r, 23.0_r, 23.0_r);
  as::mat4_basis_y(m4, basis_y);
  CHECK_THAT(
    vec4_from_vec3(basis_y, 0.0_r), elements_are(as::mat4_dimension1(m4)));

  const auto basis_z = vec3(32.0_r, 34.0_r, 36.0_r);
  as::mat4_basis_z(m4, basis_z);
  CHECK_THAT(
    vec4_from_vec3(basis_z, 0.0_r), elements_are(as::mat4_dimension2(m4)));

  const auto translation = vec3(8.0_r, 6.0_r, 4.0_r);
  as::mat4_translation(m4, translation);
  CHECK_THAT(
    vec4_from_vec3(translation, 1.0_r), elements_are(as::mat4_dimension3(m4)));
}

TEST_CASE("mat_data", "[as_mat]")
{
  mat4 mat = mat4::identity();
  real* matp = mat_data(mat);
  CHECK(*matp == Approx(1.0_r).epsilon(g_epsilon));
  CHECK(*(matp + 5) == Approx(1.0_r).epsilon(g_epsilon));
  CHECK(*(matp + 10) == Approx(1.0_r).epsilon(g_epsilon));
  CHECK(*(matp + 15) == Approx(1.0_r).epsilon(g_epsilon));
}

TEST_CASE("mat_range_iteration_mat3", "[as_mat]")
{
  {
    const real expected[]{1.0_r, 2.0_r, 3.0_r, 4.0_r, 5.0_r,
                          6.0_r, 7.0_r, 8.0_r, 9.0_r};

    // clang-format off
    const mat3 mat {
      1.0_r, 2.0_r, 3.0_r,
      4.0_r, 5.0_r, 6.0_r,
      7.0_r, 8.0_r, 9.0_r
    };
    // clang-format on

    as::index i = 0;
    for (const auto& elem : mat) {
      CHECK(elem == Approx(expected[i++]).epsilon(g_epsilon));
    }
    CHECK(i == 9);
  }

  {
    const real expected[]{2.0_r,  4.0_r,  6.0_r,  8.0_r, 10.0_r,
                          12.0_r, 14.0_r, 16.0_r, 18.0_r};

    // clang-format off
    mat3 mat {
      1.0_r, 2.0_r, 3.0_r,
      4.0_r, 5.0_r, 6.0_r,
      7.0_r, 8.0_r, 9.0_r
    };
    // clang-format on

    as::index i = 0;
    for (auto& elem : mat) {
      elem *= 2.0_r;
      CHECK(elem == Approx(expected[i++]).epsilon(g_epsilon));
    }
    CHECK(i == 9);
  }

  {
    const mat3 expected{2.0_r, 3.0_r, 4.0_r, 5.0_r, 6.0_r,
                        7.0_r, 8.0_r, 9.0_r, 10.0_r};

    // clang-format off
    mat3 m {
      1.0_r, 2.0_r, 3.0_r,
      4.0_r, 5.0_r, 6.0_r,
      7.0_r, 8.0_r, 9.0_r
    };
    // clang-format on

    mat3 next_mat;
    std::transform(cbegin(m), cend(m), begin(next_mat), [](const real elem) {
      return elem + 1;
    });

    CHECK_THAT(expected, elements_are(next_mat));
  }
}

TEST_CASE("mat_equal", "[as_mat]")
{
  {
    // clang-format off
    mat4i m4i_lhs{1,  2,  3,  4,
                  5,  6,  7,  8,
                  9,  10, 11, 12,
                  13, 14, 15, 16};
    mat4i m4i_rhs{1,  2,  3,  4,
                  5,  6,  7,  8,
                  9,  10, 11, 12,
                  13, 14, 15, 16};
    // clang-format on

    CHECK(m4i_lhs == m4i_rhs);
  }

  {
    // clang-format off
    mat3i m3i_lhs{1,  2,  4,
                  5,  6,  7,
                  9,  10, 1};
    mat3i m3i_rhs{1,  2,  4,
                  5,  6,  7,
                  1,  10, 1};
    // clang-format on

    CHECK(m3i_lhs != m3i_rhs);
  }
}

} // namespace unit_test

// explicit instantiations (for coverage)

// types
template struct as::mat<as::real, 2>;
template struct as::mat<as::real, 3>;
template struct as::mat<as::real, 4>;
template struct as::mat<as::real, 5>;

#ifdef __GNUC__
// constructor
template as::mat<as::real, 5>::mat(
  as::real, as::real, as::real, as::real, as::real, as::real, as::real,
  as::real, as::real, as::real, as::real, as::real, as::real, as::real,
  as::real, as::real, as::real, as::real, as::real, as::real, as::real,
  as::real, as::real, as::real, as::real) noexcept;
#endif // __GNUC__

// matrix multiply
template const as::mat<as::real, 3> as::operator*(
  const as::mat<as::real, 3>&, const as::mat<as::real, 3>&);
template const as::mat<as::real, 4> as::operator*(
  const as::mat<as::real, 4>&, const as::mat<as::real, 4>&);

// vector multiply
#if defined AS_ROW_MAJOR
template const as::vec<as::real, 3> as::operator*(
  const as::vec<as::real, 3>&, const as::mat<as::real, 3>&);
template const as::vec<as::real, 4> as::operator*(
  const as::vec<as::real, 4>&, const as::mat<as::real, 4>&);
#elif defined AS_COL_MAJOR
template const as::vec<as::real, 3> as::operator*(
  const as::mat<as::real, 3>&, const as::vec<as::real, 3>&);
template const as::vec<as::real, 4> as::operator*(
  const as::mat<as::real, 4>&, const as::vec<as::real, 4>&);
#endif // AS_ROW_MAJOR ? AS_COL_MAJOR

// scalar multiply
template const as::mat<as::real, 3> as::operator*(
  const as::mat<as::real, 3>&, as::real scalar);
template const as::mat<as::real, 4> as::operator*(
  const as::mat<as::real, 4>&, as::real scalar);
template as::mat<as::real, 3>& as::operator*=(
  as::mat<as::real, 3>&, as::real scalar);
template as::mat<as::real, 4>& as::operator*=(
  as::mat<as::real, 4>&, as::real scalar);
template bool as::operator==(
  const as::mat<int32_t, 4>& lhs, const as::mat<int32_t, 4>& rhs);
template bool as::operator!=(
  const as::mat<int32_t, 4>& lhs, const as::mat<int32_t, 4>& rhs);

template as::real* as::mat_data(as::mat<as::real, 5>&);
template const as::real* as::mat_const_data(const as::mat<as::real, 5>&);
