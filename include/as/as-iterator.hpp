//! \file
//! as-iterator

#pragma once

#include <type_traits>

#include "as-types.hpp"

namespace as
{

template<typename subscriptable_t, bool is_const>
class subscript_iterator_type
{
  std::conditional_t<is_const, const subscriptable_t*, subscriptable_t*>
    subscriptable;
  index i;

public:
  using iterator_category = std::random_access_iterator_tag;
  using value_type = typename subscriptable_t::value_type;
  using difference_type = ptrdiff_t;
  using reference = typename std::conditional_t<
    is_const, const typename subscriptable_t::value_type&,
    typename subscriptable_t::value_type&>;
  using pointer = typename std::conditional_t<
    is_const, const typename subscriptable_t::value_type*,
    typename subscriptable_t::value_type*>;

  explicit subscript_iterator_type(
    std::conditional_t<is_const, const subscriptable_t&, subscriptable_t&>
      subscriptable_,
    index index_ = 0);
  subscript_iterator_type(const subscript_iterator_type&) = default;
  subscript_iterator_type& operator=(const subscript_iterator_type&) = default;

  template<bool now_const, typename = std::enable_if_t<is_const && !now_const>>
  subscript_iterator_type(
    const subscript_iterator_type<subscriptable_t, now_const>& rhs)
    : subscriptable(rhs.subscriptable), i(rhs.i)
  {
  }

  template<bool now_const, typename = std::enable_if_t<is_const && !now_const>>
  subscript_iterator_type& operator=(
    const subscript_iterator_type<subscriptable_t, now_const>& rhs)
  {
    subscriptable = rhs.subscriptable;
    i = rhs.i;
    return *this;
  }

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

  const reference operator*() const
  {
    return (*subscriptable)[i];
  }

  template<bool now_const = is_const>
  std::enable_if_t<!now_const, reference> operator*()
  {
    return (*subscriptable)[i];
  }

  friend std::conditional_t<
    !is_const, subscript_iterator_type<subscriptable_t, true>, void>;
};

template<typename subscriptable_t>
using subscript_iterator = subscript_iterator_type<subscriptable_t, false>;

template<typename subscriptable_t>
using subscript_const_iterator = subscript_iterator_type<subscriptable_t, true>;

} // namespace as

#include "as-iterator.inl"
