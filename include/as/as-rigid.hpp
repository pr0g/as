//! \file
//! `as-rigid`

#pragma once

#include "as-quat.hpp"
#include "as-vec.hpp"

namespace as
{

//! Represents a \ref rigid motion (proper rigid transformation).
//! A geometric transformation that includes only rotation and translation.
template<typename T>
struct rigid_t
{
  rigid_t() noexcept = default;

  //! Constructs a rigid with `(quat::identity(), translation_)`
  constexpr explicit rigid_t(const vec<T, 3>& translation_);
  //! Constructs a rigid with `(rotation_, translation_)`
  //! \note \p translation_ defaults to zero.
  constexpr explicit rigid_t(
    const quat& rotation_, const vec<T, 3>& translation_ = vec<T, 3>::zero());

  //! Returns an identity rigid (identity transform).
  constexpr static rigid_t identity();

  //! Returns `7`.
  constexpr static index size();

  quat rotation; //!< The rotation applied by this transformation.
  vec<T, 3> translation; //!< The translation applied by this transformation.
};

//! Type alias for a rigid of type ::real.
using rigid = rigid_t<real>;
//! Type alias for a rigid of type float.
using rigidf = rigid_t<float>;
//! Type alias for a rigid of type float.
using rigidd = rigid_t<double>;

} // namespace as

#include "as-rigid.inl"
