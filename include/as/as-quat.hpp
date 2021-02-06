//! \file
//! `as-quat`

#pragma once

#include "as-vec.hpp"

namespace as
{

//! A quaternion used to store rotation/orientation in (_w_, __v__) format.
struct quat
{
  //! Type alias for ::real.
  using value_type = real;

  quat() noexcept = default;

  //! Constructs quat with `(w_, x_, y_, z_)`.
  constexpr quat(real w_, real x_, real y_, real z_);
  //! Constructs quat with `(w_, xyz_.x, xyz_.y, xyz_.z)`.
  constexpr quat(real w_, const vec3& xyz_);

  //! Returns quaternion identity `(1.0, 0.0, 0.0, 0.0)`
  constexpr static quat identity();

  //! Returns `4`.
  constexpr static index size();

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

  real w; //!< Scalar part.
  real x; //!< X component of vector part x _i_.
  real y; //!< Y component of vector part y _j_.
  real z; //!< Z component of vector part z _k_.

private:
  static real quat::*elem[4];
};

inline real quat::*quat::elem[4] = {&quat::w, &quat::x, &quat::y, &quat::z};

//! Returns the result of concatenating two quaternions by multiplying them
//! together.
//! \note The quaternion on the right of the expression `rhs` will be applied
//! first, followed by `lhs`.
constexpr const quat operator*(const quat& lhs, const quat& rhs);

//! Performs multiplication assignment of two quaternions.
constexpr quat& operator*=(quat& lhs, const quat& rhs);

//! Returns the sum of two quaternions.
constexpr const quat operator+(const quat& lhs, const quat& rhs);

//! Performs addition assignment of two quaternions.
constexpr quat& operator+=(quat& lhs, const quat& rhs);

//! Returns the result of `rhs` subtracted from `lhs`.
constexpr const quat operator-(const quat& lhs, const quat& rhs);

//! Performs subtraction assignment of two quaternions.
constexpr quat& operator-=(quat& lhs, const quat& rhs);

//! Returns the negation of `quat`.
constexpr const quat operator-(const quat& q);

//! Returns a quat divided by a scalar quantity.
constexpr const quat operator/(const quat& lhs, real rhs);

//! Returns a quat multiplied by a scalar quantity.
constexpr const quat operator*(const quat& lhs, real rhs);

//! Returns a quat multiplied by a scalar quantity (overload).
constexpr const quat operator*(real lhs, const quat& rhs);

//! Returns an iterator to the beginning of the quaternion.
subscript_iterator<quat> begin(quat& q);

//! Returns an iterator to the end of the quaternion.
subscript_iterator<quat> end(quat& q);

//! Returns an iterator to the beginning of the quaternion.
//! \note `const` overload
subscript_const_iterator<quat> begin(const quat& q);

//! Returns an iterator to the end of the quaternion.
//! \note `const` overload
subscript_const_iterator<quat> end(const quat& q);

//! Returns a const iterator to the beginning of the quaternion.
subscript_const_iterator<quat> cbegin(const quat& q);

//! Returns a const iterator to the end of the quaternion.
subscript_const_iterator<quat> cend(const quat& q);

} // namespace as

#include "as-quat.inl"
