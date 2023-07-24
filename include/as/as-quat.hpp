//! \file
//! `as-quat`

#pragma once

#include "as-vec.hpp"

namespace as
{

//! A quaternion used to store rotation/orientation in (_w_, __v__) format.
template<typename T>
struct quat_t
{
  //! Type alias for T
  using value_type = T;

  quat_t() noexcept = default;

  //! Constructs quat with `(w_, x_, y_, z_)`.
  constexpr quat_t(T w_, T x_, T y_, T z_);
  //! Constructs quat with `(w_, xyz_.x, xyz_.y, xyz_.z)`.
  constexpr quat_t(T w_, const vec3& xyz_);

  //! Returns quaternion identity `(1.0, 0.0, 0.0, 0.0)`
  constexpr static quat_t identity();

  //! Returns `4`.
  constexpr static index size();

  //! Returns a mutable reference to the value at the given index.
  //! \note Can only be called on a mutable lvalue object.
  //! \warning No bounds checking is performed.
  T& operator[](index i) &;
  //! Returns a const reference to the value at the given index.
  //! \note Can only be called on a const lvalue object.
  //! \warning No bounds checking is performed.
  const T& operator[](index i) const&;
  //! Returns a copy of the value at the given index.
  //! \note Can only be called on an rvalue object.
  //! \warning No bounds checking is performed.
  T operator[](index i) &&;

  T w; //!< Scalar part.
  T x; //!< X component of vector part x _i_.
  T y; //!< Y component of vector part y _j_.
  T z; //!< Z component of vector part z _k_.

private:
  static T quat_t::*elem[4];
};

template<typename T>
T quat_t<T>::*quat_t<T>::elem[4] = {
  &quat_t<T>::w, &quat_t<T>::x, &quat_t<T>::y, &quat_t<T>::z};

//! Type alias for a rigid of type ::real.
using quat = quat_t<real>;
//! Type alias for a rigid of type float.
using quatf = quat_t<float>;
//! Type alias for a rigid of type float.
using quatd = quat_t<double>;

//! Returns the result of concatenating two quaternions by multiplying them
//! together.
//! \note The quaternion on the right of the expression `rhs` will be applied
//! first, followed by `lhs`.
template<typename T>
constexpr const quat_t<T> operator*(const quat_t<T>& lhs, const quat_t<T>& rhs);

//! Performs multiplication assignment of two quaternions.
template<typename T>
constexpr quat_t<T>& operator*=(quat_t<T>& lhs, const quat_t<T>& rhs);

//! Returns the sum of two quaternions.
template<typename T>
constexpr const quat_t<T> operator+(const quat_t<T>& lhs, const quat_t<T>& rhs);

//! Performs addition assignment of two quaternions.
template<typename T>
constexpr quat_t<T>& operator+=(quat_t<T>& lhs, const quat_t<T>& rhs);

//! Returns the result of `rhs` subtracted from `lhs`.
template<typename T>
constexpr const quat_t<T> operator-(const quat_t<T>& lhs, const quat_t<T>& rhs);

//! Performs subtraction assignment of two quaternions.
template<typename T>
constexpr quat_t<T>& operator-=(quat_t<T>& lhs, const quat_t<T>& rhs);

//! Returns the negation of `quat_t<T>`.
template<typename T>
constexpr const quat_t<T> operator-(const quat_t<T>& q);

//! Returns a quat_t<T> divided by a scalar quantity.
template<typename T>
constexpr const quat_t<T> operator/(const quat_t<T>& lhs, T rhs);

//! Returns a quat_t<T> multiplied by a scalar quantity.
template<typename T>
constexpr const quat_t<T> operator*(const quat_t<T>& lhs, T rhs);

//! Returns a quat_t<T> multiplied by a scalar quantity (overload).
template<typename T>
constexpr const quat_t<T> operator*(T lhs, const quat_t<T>& rhs);

//! Returns an iterator to the beginning of the quaternion.
template<typename T>
subscript_iterator<quat_t<T>> begin(quat_t<T>& q);

//! Returns an iterator to the end of the quaternion.
template<typename T>
subscript_iterator<quat_t<T>> end(quat_t<T>& q);

//! Returns an iterator to the beginning of the quaternion.
//! \note `const` overload
template<typename T>
subscript_const_iterator<quat_t<T>> begin(const quat_t<T>& q);

//! Returns an iterator to the end of the quaternion.
//! \note `const` overload
template<typename T>
subscript_const_iterator<quat_t<T>> end(const quat_t<T>& q);

//! Returns a const iterator to the beginning of the quaternion.
template<typename T>
subscript_const_iterator<quat_t<T>> cbegin(const quat_t<T>& q);

//! Returns a const iterator to the end of the quaternion.
template<typename T>
subscript_const_iterator<quat_t<T>> cend(const quat_t<T>& q);

} // namespace as

#include "as-quat.inl"
