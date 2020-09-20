//! \file
//! as-point

#pragma once

#include "as-math.hpp"
#include "as-vec.hpp"

namespace as
{

//! Represents a two dimensional p.
//! A p provides many of the same operations as a vector but has a more
//! restrictive interface. It is geometrically very different from a vector and
//! can be used to increase type safety and prevent erroneous operations.
struct point2
{
  //! Type alias for ::real.
  using value_type = real;

  point2() noexcept = default;

  //! Constructs point2 with `(xy_, xy_)`.
  constexpr explicit point2(real xy_);
  //! Constructs point2 with `(xy_.x, xy_.y)`.
  constexpr explicit point2(const vec2& xy_);
  //! Constructs point2 with `(x_, y_)`.
  constexpr point2(real x_, real y_);

  //! Returns a mutable reference to the value at the given index.
  //! \note Can only be called on a mutable lvalue object.
  //! \warning No bounds checking is performed.
  real& operator[](index i) &;
  //! Returns a const reference to the value at the given index.
  //! \note Can only be called on a const lvalue object.
  //! \warning No bounds checking is performed.
  const real& operator[](index i) const&;
  //! Returns a copy of the value at the given index.
  //! \note Can only be called on an rvalue object.
  //! \warning No bounds checking is performed.
  real operator[](index i) &&;

  //! Returns `2`.
  constexpr static index size();
  //! Returns `(0, 0)`.
  constexpr static point2 zero();
  //! Returns `(x, 0)`.
  //! \param x Optional parameter for the length of the axis, defaults to 1.
  constexpr static point2 axis_x(real x = 1.0_r);
  //! Returns `(0, y)`.
  //! \param y Optional parameter for the length of the axis, defaults to 1.
  constexpr static point2 axis_y(real y = 1.0_r);

  //! Returns a copy of the underlying vec2.
  //! \note Can only be called on an rvalue object.
  constexpr vec2 as_vec() &&;
  //! Returns a const reference to the underlying vec2.
  //! \note Can only be called on a const lvalue object.
  [[nodiscard]] constexpr const vec2& as_vec() const&;

private:
  //! Returns the result of the right hand point2 subtracted from the left
  //! hand point2.
  friend constexpr const vec2 operator-(const point2& lhs, const point2& rhs);
  //! Returns the result of a vec2 added to a point2.
  friend constexpr const point2 operator+(const point2& p, const vec2& v);
  //! Performs addition assignment of a point2 and a vec2.
  friend constexpr point2& operator+=(point2& p, const vec2& v);
  //! Returns the result of a vec2 subtracted from a point2.
  friend constexpr const point2 operator-(const point2& p, const vec2& v);
  //! Performs subtraction assignment of a point2 and a vec2.
  friend constexpr point2& operator-=(point2& p, const vec2& v);
  //! Returns the negation of a point2.
  friend const point2 operator-(const point2& p);

  vec2 v; //!< point2 is implemented in terms of vec2.
};

//! Represents a three dimensional p.
//! A p provides many of the same operations as a vector but has a more
//! restrictive interface. It is geometrically very different from a vector and
//! can be used to increase type safety and prevent erroneous operations.
struct point3
{
  //! Type alias for ::real.
  using value_type = real;

  point3() noexcept = default;

  //! Constructs point3 with `(xyz_, xyz_, xyz_)`.
  constexpr explicit point3(real xyz_);
  //! Constructs point3 with `(v_.x, v_.y, v_.z)`.
  constexpr explicit point3(const vec3& v_);
  //! Constructs point3 with `(x_, y_, z_)`.
  constexpr point3(real x_, real y_, real z_);
  //! Constructs point3 with `(xy_.x, xy_.y, z_)`.
  constexpr point3(const vec2& xy_, real z_);

  //! Returns a mutable reference to the value at the given index.
  //! \note Can only be called on a mutable lvalue object.
  //! \warning No bounds checking is performed.
  real& operator[](index i) &;
  //! Returns a const reference to the value at the given index.
  //! \note Can only be called on a const lvalue object.
  //! \warning No bounds checking is performed.
  const real& operator[](index i) const&;
  //! Returns a copy of the value at the given index.
  //! \note Can only be called on an rvalue object.
  //! \warning No bounds checking is performed.
  real operator[](index i) &&;

  //! Returns `3`.
  constexpr static index size();

  //! Returns `(0, 0, 0)`.
  constexpr static point3 zero();
  //! Returns `(x, 0, 0)`.
  //! \param x Optional parameter for the length of the axis, defaults to 1.
  constexpr static point3 axis_x(real x = 1.0_r);
  //! Returns `(0, y, 0)`.
  //! \param y Optional parameter for the length of the axis, defaults to 1.
  constexpr static point3 axis_y(real y = 1.0_r);
  //! Returns `(0, 0, z)`.
  //! \param z Optional parameter for the length of the axis, defaults to 1.
  constexpr static point3 axis_z(real z = 1.0_r);

  //! Returns a copy of the underlying vec3.
  //! \note Can only be called on an rvalue object.
  constexpr vec3 as_vec() &&;
  //! Returns a const reference to the underlying vec3.
  //! \note Can only be called on a const lvalue object.
  [[nodiscard]] constexpr const vec3& as_vec() const&;

private:
  //! Returns the result of the right hand point3 subtracted from the left
  //! hand point3.
  friend constexpr const vec3 operator-(const point3& lhs, const point3& rhs);
  //! Returns the result of a vec3 added to a point3.
  friend constexpr const point3 operator+(const point3& p, const vec3& v);
  //! Performs addition assignment of a point3 and a vec3.
  friend constexpr point3& operator+=(point3& p, const vec3& v);
  //! Returns the result of a vec3 subtracted from a point3.
  friend constexpr const point3 operator-(const point3& p, const vec3& v);
  //! Performs subtraction assignment of a point3 and a vec3.
  friend constexpr point3& operator-=(point3& p, const vec3& v);
  //! Returns the negation of a point3.
  friend constexpr const point3 operator-(const point3& p);

  vec3 v; //!< point3 is implemented in terms of vec3.
};

} // namespace as

#include "as-point.inl"
