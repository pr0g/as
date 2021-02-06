//! \file
//! `as-rigid`

#pragma once

#include "as-quat.hpp"
#include "as-vec.hpp"

namespace as
{

//! Represents a \ref rigid motion (proper rigid transformation).
//! A geometric transformation that includes only rotation and translation.
struct rigid
{
  rigid() noexcept = default;

  //! Constructs a rigid with `(quat::identity(), translation_)`
  constexpr explicit rigid(const vec3& translation_);
  //! Constructs a rigid with `(rotation_, translation_)`
  //! \note \p translation_ defaults to zero.
  constexpr explicit rigid(
    const quat& rotation_, const vec3& translation_ = vec3::zero());

  quat rotation; //!< The rotation applied by this transformation.
  vec3 translation; //!< The translation applied by this transformation.
};

} // namespace as

#include "as-rigid.inl"
