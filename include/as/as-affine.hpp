//! \file
//! as-affine

#pragma once

#include "as-mat3.hpp"
#include "as-point.hpp"

namespace as
{

//! Represents an a transformation.
//! A geometric transformation that preserves lines and parrellism.
struct affine
{
  affine() noexcept = default;

  //! Constructs affine with `(mat3::identity(), translation_)`
  constexpr explicit affine(const vec3& translation_);
  //! Constructs affine with `(rotation_, translation_)`
  //! \note \p translation_ defaults to zero.
  constexpr explicit affine(
    const mat3& rotation_, const vec3& translation_ = as::vec3::zero());

  mat3 rotation; //!< The rotation applied by this transformation.
  vec3 translation; //!< The translation applied by this transformation.
};

} // namespace as

#include "as-affine.inl"
