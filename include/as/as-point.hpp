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
struct point2_t
{
  //! Type alias for ::real_t.
  using value_type = real_t;

  point2_t() noexcept = default;

  //! Constructs point2_t with `(xy_, xy_)`.
  constexpr explicit point2_t(real_t xy_);
  //! Constructs point2_t with `(xy_.x, xy_.y)`.
  constexpr explicit point2_t(const vec2_t& xy_);
  //! Constructs point2_t with `(x_, y_)`.
  constexpr point2_t(real_t x_, real_t y_);

  //! Returns a mutable reference to the value at the given index.
  //! \note Can only be called on a mutable lvalue object.
  //! \warning No bounds checking is performed.
  real_t& operator[](index_t i) &;
  //! Returns a const reference to the value at the given index.
  //! \note Can only be called on a const lvalue object.
  //! \warning No bounds checking is performed.
  const real_t& operator[](index_t i) const&;
  //! Returns a copy of the value at the given index.
  //! \note Can only be called on an rvalue object.
  //! \warning No bounds checking is performed.
  real_t operator[](index_t i) &&;

  //! Returns `2`.
  constexpr static index_t size();
  //! Returns `(0, 0)`.
  constexpr static point2_t zero();
  //! Returns `(x, 0)`.
  //! \param x Optional parameter for the length of the axis, defaults to 1.
  constexpr static point2_t axis_x(real_t x = 1.0_r);
  //! Returns `(0, y)`.
  //! \param y Optional parameter for the length of the axis, defaults to 1.
  constexpr static point2_t axis_y(real_t y = 1.0_r);

  //! Returns a copy of the underlying vec2_t.
  //! \note Can only be called on an rvalue object.
  constexpr vec2_t as_vec() &&;
  //! Returns a const reference to the underlying vec2_t.
  //! \note Can only be called on a const lvalue object.
  [[nodiscard]] constexpr const vec2_t& as_vec() const&;

private:
  //! Returns the result of the right hand point2_t subtracted from the left
  //! hand point2_t.
  friend constexpr const vec2_t operator-(
    const point2_t& lhs, const point2_t& rhs);
  //! Returns the result of a vec2_t added to a point2_t.
  friend constexpr const point2_t operator+(const point2_t& p, const vec2_t& v);
  //! Performs addition assignment of a point2_t and a vec2_t.
  friend constexpr point2_t& operator+=(point2_t& p, const vec2_t& v);
  //! Returns the result of a vec2_t subtracted from a point2_t.
  friend constexpr const point2_t operator-(const point2_t& p, const vec2_t& v);
  //! Performs subtraction assignment of a point2_t and a vec2_t.
  friend constexpr point2_t& operator-=(point2_t& p, const vec2_t& v);
  //! Returns the negation of a point2_t.
  friend const point2_t operator-(const point2_t& p);

  vec2_t v; //!< point2_t is implemented in terms of vec2_t.
};

//! Represents a three dimensional p.
//! A p provides many of the same operations as a vector but has a more
//! restrictive interface. It is geometrically very different from a vector and
//! can be used to increase type safety and prevent erroneous operations.
struct point3_t
{
  //! Type alias for ::real_t.
  using value_type = real_t;

  point3_t() noexcept = default;

  //! Constructs point3_t with `(xyz_, xyz_, xyz_)`.
  constexpr explicit point3_t(real_t xyz_);
  //! Constructs point3_t with `(v_.x, v_.y, v_.z)`.
  constexpr explicit point3_t(const vec3_t& v_);
  //! Constructs point3_t with `(x_, y_, z_)`.
  constexpr point3_t(real_t x_, real_t y_, real_t z_);
  //! Constructs point3_t with `(xy_.x, xy_.y, z_)`.
  constexpr point3_t(const vec2_t& xy_, real_t z_);

  //! Returns a mutable reference to the value at the given index.
  //! \note Can only be called on a mutable lvalue object.
  //! \warning No bounds checking is performed.
  real_t& operator[](index_t i) &;
  //! Returns a const reference to the value at the given index.
  //! \note Can only be called on a const lvalue object.
  //! \warning No bounds checking is performed.
  const real_t& operator[](index_t i) const&;
  //! Returns a copy of the value at the given index.
  //! \note Can only be called on an rvalue object.
  //! \warning No bounds checking is performed.
  real_t operator[](index_t i) &&;

  //! Returns `3`.
  constexpr static index_t size();

  //! Returns `(0, 0, 0)`.
  constexpr static point3_t zero();
  //! Returns `(x, 0, 0)`.
  //! \param x Optional parameter for the length of the axis, defaults to 1.
  constexpr static point3_t axis_x(real_t x = 1.0_r);
  //! Returns `(0, y, 0)`.
  //! \param y Optional parameter for the length of the axis, defaults to 1.
  constexpr static point3_t axis_y(real_t y = 1.0_r);
  //! Returns `(0, 0, z)`.
  //! \param z Optional parameter for the length of the axis, defaults to 1.
  constexpr static point3_t axis_z(real_t z = 1.0_r);

  //! Returns a copy of the underlying vec3_t.
  //! \note Can only be called on an rvalue object.
  constexpr vec3_t as_vec() &&;
  //! Returns a const reference to the underlying vec3_t.
  //! \note Can only be called on a const lvalue object.
  [[nodiscard]] constexpr const vec3_t& as_vec() const&;

private:
  //! Returns the result of the right hand point3_t subtracted from the left
  //! hand point3_t.
  friend constexpr const vec3_t operator-(
    const point3_t& lhs, const point3_t& rhs);
  //! Returns the result of a vec3_t added to a point3_t.
  friend constexpr const point3_t operator+(const point3_t& p, const vec3_t& v);
  //! Performs addition assignment of a point3_t and a vec3_t.
  friend constexpr point3_t& operator+=(point3_t& p, const vec3_t& v);
  //! Returns the result of a vec3_t subtracted from a point3_t.
  friend constexpr const point3_t operator-(const point3_t& p, const vec3_t& v);
  //! Performs subtraction assignment of a point3_t and a vec3_t.
  friend constexpr point3_t& operator-=(point3_t& p, const vec3_t& v);
  //! Returns the negation of a point3_t.
  friend constexpr const point3_t operator-(const point3_t& p);

  vec3_t v; //!< point3_t is implemented in terms of vec3_t.
};

} // namespace as

#include "as-point.inl"
