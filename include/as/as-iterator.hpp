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
  std::reference_wrapper<subscriptable_t> subscriptable;

public:
  using iterator_category = std::random_access_iterator_tag;
  using value_type = typename subscriptable_t::value_type;
  using difference_type = ptrdiff_t;
  using pointer = typename subscriptable_t::value_type*;
  using reference = typename subscriptable_t::value_type&;

  explicit subscript_iterator_type(
    subscriptable_t& subscriptable_, index index_ = 0);

  bool operator==(const subscript_iterator_type& sub_it) const;
  bool operator!=(const subscript_iterator_type& sub_it) const;
  subscript_iterator_type operator+(const difference_type& movement);
  subscript_iterator_type operator-(const difference_type& movement);
  subscript_iterator_type& operator+=(const difference_type& movement);
  subscript_iterator_type& operator-=(const difference_type& movement);
  subscript_iterator_type& operator++();
  subscript_iterator_type operator++(int);
  subscript_iterator_type& operator--();
  subscript_iterator_type operator--(int);
  difference_type operator-(const subscript_iterator_type& sub_it) const;
  bool operator<(const subscript_iterator_type& sub_it) const;
  bool operator>(const subscript_iterator_type& sub_it) const;
  bool operator<=(const subscript_iterator_type& sub_it) const;
  bool operator>=(const subscript_iterator_type& sub_it) const;

  template<typename = std::enable_if_t<std::is_const_v<subscriptable_t>>>
  const typename subscriptable_t::value_type& operator*() const
  {
    return subscriptable.get()[i];
  }

  template<typename = std::enable_if_t<!std::is_const_v<subscriptable_t>>>
  typename subscriptable_t::value_type& operator*()
  {
    return subscriptable.get()[i];
  }
};

template<typename subscriptable_t>
using subscript_iterator = subscript_iterator_type<subscriptable_t>;

template<typename subscriptable_t>
using subscript_const_iterator = subscript_iterator_type<const subscriptable_t>;

} // namespace as

#include "as-iterator.inl"
