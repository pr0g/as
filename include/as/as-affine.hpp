//! \file
//! `as-affine`

#pragma once

#include "as-mat3.hpp"
#include "as-vec.hpp"

namespace as
{

//! Represents an \ref affine transformation.
//! A geometric transformation that preserves lines and parallelism.
template<typename T>
struct affine_t
{
  affine_t() noexcept = default;

  //! Constructs an affine with `(mat3::identity(), translation_)`
  constexpr explicit affine_t(const vec<T, 3>& translation_);
  //! Constructs an affine with `(rotation_, translation_)`
  //! \note \p translation_ defaults to zero.
  constexpr explicit affine_t(
    const mat<T, 3>& rotation_,
    const vec<T, 3>& translation_ = vec<T, 3>::zero());

  //! Returns an identity affine (identity transform).
  constexpr static affine_t identity();

  //! Returns `12`.
  constexpr static index size();

  mat<T, 3> rotation; //!< The rotation applied by this transformation.
  vec<T, 3> translation; //!< The translation applied by this transformation.
};

//! Type alias for an affine of type ::real.
using affine = affine_t<real>;
//! Type alias for an affine of type float.
using affinef = affine_t<float>;
//! Type alias for an affine of type float.
using affined = affine_t<double>;

} // namespace as

#include "as-affine.inl"
