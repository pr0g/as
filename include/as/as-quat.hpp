//! \file
//! as-quat

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

  real w; //!< Scalar part.
  real x; //!< X component of vector part x _i_.
  real y; //!< Y component of vector part y _j_.
  real z; //!< Z component of vector part z _k_.
};

//! Returns the result of concatenating two quaternions by multiplying them
//! together.
//! \note The quaternion on the right of the expression `rhs` will be applied
//! first, followed by `lhs`.
constexpr const quat operator*(const quat& lhs, const quat& rhs);
//! Performs multiplication assignment of two quaternions.
constexpr quat& operator*=(quat& lhs, const quat& rhs);
//! Returns the sum of two quaternions.
constexpr const quat operator+(const quat& lhs, const quat& rhs);
//! Returns the result of `rhs` subtracted from `lhs`.
constexpr const quat operator-(const quat& lhs, const quat& rhs);
//! Returns the negation of `quat`.
constexpr const quat operator-(const quat& q);
//! Returns a quat divided by a scalar quantity.
constexpr const quat operator/(const quat& lhs, real rhs);
//! Returns a quat multiplied by a scalar quantity.
constexpr const quat operator*(const quat& lhs, real rhs);

} // namespace as

#include "as-quat.inl"
