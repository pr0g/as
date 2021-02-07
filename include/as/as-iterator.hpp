//! \file
//! `as-iterator`

#pragma once

#include <iterator>
#include <type_traits>

#include "as-types.hpp"

namespace as
{

//! Provides an iterator that can be used in any context where the subscrript
//! operator (`[]`) is implemented for the type.
//! \note This type should never be used directly, instead ::subscript_iterator
//! and ::subscript_const_iterator should be used depending on the usage
//! requirements.
template<typename subscriptable_t, bool is_const>
class subscript_iterator_type
{
  std::conditional_t<is_const, const subscriptable_t*, subscriptable_t*>
    subscriptable; //!< A pointer to the subscriptable type.
  index i; //!< The current offset into the subscriptable type.

public:
  //! \name Type aliases
  //! Required aliases provided by the iterator type.
  //!@{
  /** The kind of iterator (see https://en.cppreference.com/w/cpp/iterator
   * and https://en.cppreference.com/w/cpp/iterator/iterator_tags for more
   * details). */
  using iterator_category = std::random_access_iterator_tag;
  /** The type of the element the iterator can point to. */
  using value_type = typename subscriptable_t::value_type;
  /** Type to express the result of subtracting one iterator from another. */
  using difference_type = ptrdiff_t;
  /** The type of a reference to an element the iterator can point to. */
  using reference = typename std::conditional_t<
    is_const, const typename subscriptable_t::value_type&,
    typename subscriptable_t::value_type&>;
  /** The type of a pointer to an element the iterator can point to. */
  using pointer = typename std::conditional_t<
    is_const, const typename subscriptable_t::value_type*,
    typename subscriptable_t::value_type*>;
  //!@}

  //! Default constructor.
  subscript_iterator_type() = default;
  //! Custom constructor accepting a `subscriptable_t` and a current `index`.
  //! \note Whether `subscriptable_t` is `const` or not is determined by the
  //! `subscript_iterator_type` template argument `is_const`.
  explicit subscript_iterator_type(
    std::conditional_t<is_const, const subscriptable_t&, subscriptable_t&>
      subscriptable_,
    index index_ = 0);
  //! Default copy constructor.
  subscript_iterator_type(const subscript_iterator_type&) = default;
  //! Default assignment operator.
  subscript_iterator_type& operator=(const subscript_iterator_type&) = default;
  //! Converting constructor to permit conversion from a non-`const` iterator to
  //! a `const` iterator.
  //! \note Mote details on this topic can be found here:
  //! https://quuxplusone.github.io/blog/2018/12/01/const-iterator-antipatterns/
  template<bool now_const, typename = std::enable_if_t<is_const && !now_const>>
  subscript_iterator_type(
    const subscript_iterator_type<subscriptable_t, now_const>& rhs)
    : subscriptable(rhs.subscriptable), i(rhs.i)
  {
  }
  //! Converting assignment operator to permit conversion from a non-`const`
  //! iterator to a `const` iterator.
  template<bool now_const, typename = std::enable_if_t<is_const && !now_const>>
  subscript_iterator_type& operator=(
    const subscript_iterator_type<subscriptable_t, now_const>& rhs)
  {
    subscriptable = rhs.subscriptable;
    i = rhs.i;
    return *this;
  }

  //! \name Iterator operations.
  //! Member functions required for subscript_iterator_type to act as a
  //! random access iterator.
  //!@{
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
  //!@}

  //! Dereference operator to access a `const` reference.
  const reference operator*() const { return (*subscriptable)[i]; }

  //! Dereference operator to access a non-`const` reference.
  //! \note The member function is only present on a subscript_iterator_type
  //! whose `is_const` template argument is `false`.
  template<bool now_const = is_const>
  std::enable_if_t<!now_const, reference> operator*()
  {
    return (*subscriptable)[i];
  }

  //! Non-`const` subscript_iterator_type friend declaration.
  //! \note Make the non-`const` subscript_iterator_type a friend of the
  //! `const` subscript_iterator_type to allow access to private members in
  //! the converting constructor.
  friend std::conditional_t<
    !is_const, subscript_iterator_type<subscriptable_t, true>, void>;
};

//! Type alias for non-`const` subscript_iterator_type.
template<typename subscriptable_t>
using subscript_iterator = subscript_iterator_type<subscriptable_t, false>;

//! Type alias for `const` subscript_iterator_type.
template<typename subscriptable_t>
using subscript_const_iterator = subscript_iterator_type<subscriptable_t, true>;

} // namespace as

#include "as-iterator.inl"
