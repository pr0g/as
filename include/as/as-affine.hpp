//! \file
//! as-affine

#pragma once

#include "as-mat3.hpp"
#include "as-vec.hpp"

namespace as
{

//! Represents an affine transformation.
//! A geometric transformation that preserves lines and parrellism.
struct affine
{
  affine() noexcept = default;

  //! Constructs an affine with `(mat3::identity(), translation_)`
  constexpr explicit affine(const vec3& translation_);
  //! Constructs an affine with `(rotation_, translation_)`
  //! \note \p translation_ defaults to zero.
  constexpr explicit affine(
    const mat3& rotation_, const vec3& translation_ = vec3::zero());

  mat3 rotation; //!< The rotation applied by this transformation.
  vec3 translation; //!< The translation applied by this transformation.
};

} // namespace as

#include "as-affine.inl"
