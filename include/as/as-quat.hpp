//! \file
//! as-quat

#pragma once

#include "as-vec.hpp"

namespace as
{

//! A quaternion used to store rotation/orientaton in (_w_, __v__) format.
struct quat_t
{
  //! Type alias for ::real_t.
  using value_type = real_t;

  quat_t() noexcept = default;

  //! Constructs quat_t with `(w_, x_, y_, z_)`.
  constexpr quat_t(real_t w_, real_t x_, real_t y_, real_t z_);
  //! Constructs quat_t with `(w_, xyz_.x, xyz_.y, xyz_.z)`.
  constexpr quat_t(real_t w_, const vec3_t& xyz_);

  //! Returns quaternion identity `(1.0, 0.0, 0.0, 0.0)`
  constexpr static quat_t identity();

  real_t w; //!< Scalar part.
  real_t x; //!< X component of vector part x _i_.
  real_t y; //!< Y component of vector part y _j_.
  real_t z; //!< Z component of vector part z _k_.
};

//! Returns the result of concatenating two quaternions by multiplying them
//! together.
//! \note The quaternion on the right of the expression `rhs` will be applied
//! first, followed by `lhs`.
constexpr const quat_t operator*(const quat_t& lhs, const quat_t& rhs);
//! Performs multiplication assignment of two quaternions.
constexpr quat_t& operator*=(quat_t& lhs, const quat_t& rhs);
//! Returns the sum of two quaternions.
constexpr const quat_t operator+(const quat_t& lhs, const quat_t& rhs);
//! Returns the result of `rhs` subtracted from `lhs`.
constexpr const quat_t operator-(const quat_t& lhs, const quat_t& rhs);
//! Returns the negation of `quat`.
constexpr const quat_t operator-(const quat_t& q);
//! Returns a quat_t divided by a scalar quantity.
constexpr const quat_t operator/(const quat_t& lhs, real_t rhs);
//! Returns a quat_t multiplied by a scalar quantity.
constexpr const quat_t operator*(const quat_t& lhs, real_t rhs);

} // namespace as

#include "as-quat.inl"
