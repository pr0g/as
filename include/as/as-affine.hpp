//! \file
//! as-affine

#pragma once

#include "as-mat3.hpp"
#include "as-point.hpp"

namespace as
{

//! Represents an affine transformation.
//! A geometric transformation that preserves lines and parrellism.
struct affine_t
{
    affine_t() = default;

    //! Constructs affine_t with `(mat3_t::identity(), translation_)`
    constexpr explicit affine_t(const vec3_t& translation_);
    //! Constructs affine_t with `(rotation_, translation_)`
    //! \note \p translation_ defaults to zero.
    constexpr explicit affine_t(
        const mat3_t& rotation_,
        const vec3_t& translation_ = as::vec3_t::zero());

    mat3_t rotation; //!< The rotation applied by this transformation.
    vec3_t translation; //!< The translation applied by this transformation.
};

} // namespace as

#include "as-affine.inl"
