//! \file
//! as-iterator

#pragma once

#include <type_traits>

#include "as-types.hpp"

namespace as
{

template<typename subscriptable_t>
class subscript_iterator_type
{
  index i;
  subscriptable_t& subscriptable;
public:
  explicit subscript_iterator_type(subscriptable_t& subscriptable_, index index_);

  bool operator!=(const subscript_iterator_type& sub_it) const;
  subscript_iterator_type& operator++();

  template<typename = std::enable_if_t<std::is_const_v<subscriptable_t>>>
  const typename subscriptable_t::value_type& operator*() const {
    return subscriptable[i];
  }

  template<typename = std::enable_if_t<!std::is_const_v<subscriptable_t>>>
  typename subscriptable_t::value_type& operator*() {
    return subscriptable[i];
  }
};

template<typename subscriptable_t>
using subscript_iterator = subscript_iterator_type<subscriptable_t>;

template<typename subscriptable_t>
using subscript_const_iterator = subscript_iterator_type<const subscriptable_t>;

} // namespace as

#include "as-iterator.inl"
