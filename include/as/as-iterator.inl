namespace as
{

template<typename subscriptable_t, bool is_const>
AS_API subscript_iterator_type<subscriptable_t, is_const>::
  subscript_iterator_type(subscriptable_t& subscriptable_, index index_)
  : i(index_), subscriptable(subscriptable_)
{
}

template<typename subscriptable_t, bool is_const>
AS_API bool subscript_iterator_type<subscriptable_t, is_const>::operator==(
  const subscript_iterator_type<subscriptable_t, is_const>& sub_it) const
{
  return sub_it.i == i;
}

template<typename subscriptable_t, bool is_const>
AS_API bool subscript_iterator_type<subscriptable_t, is_const>::operator!=(
  const subscript_iterator_type<subscriptable_t, is_const>& sub_it) const
{
  return !operator==(sub_it);
}

template<typename subscriptable_t, bool is_const>
AS_API subscript_iterator_type<subscriptable_t, is_const>&
subscript_iterator_type<subscriptable_t, is_const>::operator++()
{
  ++i;
  return *this;
}

template<typename subscriptable_t, bool is_const>
AS_API subscript_iterator_type<subscriptable_t, is_const>
subscript_iterator_type<subscriptable_t, is_const>::operator++(int)
{
  auto temp(*this);
  ++i;
  return temp;
}

template<typename subscriptable_t, bool is_const>
AS_API subscript_iterator_type<subscriptable_t, is_const>&
subscript_iterator_type<subscriptable_t, is_const>::operator--()
{
  --i;
  return *this;
}

template<typename subscriptable_t, bool is_const>
AS_API subscript_iterator_type<subscriptable_t, is_const>
subscript_iterator_type<subscriptable_t, is_const>::operator--(int)
{
  auto temp(*this);
  --i;
  return temp;
}

template<typename subscriptable_t, bool is_const>
AS_API subscript_iterator_type<subscriptable_t, is_const>&
subscript_iterator_type<subscriptable_t, is_const>::operator+=(
  const difference_type& movement)
{
  i += movement;
  return *this;
}

template<typename subscriptable_t, bool is_const>
AS_API subscript_iterator_type<subscriptable_t, is_const>&
subscript_iterator_type<subscriptable_t, is_const>::operator-=(
  const difference_type& movement)
{
  i -= movement;
  return *this;
}

template<typename subscriptable_t, bool is_const>
AS_API subscript_iterator_type<subscriptable_t, is_const>
subscript_iterator_type<subscriptable_t, is_const>::operator+(
  const difference_type& movement)
{
  auto temp(*this);
  temp += movement;
  return temp;
}

template<typename subscriptable_t, bool is_const>
AS_API subscript_iterator_type<subscriptable_t, is_const>
subscript_iterator_type<subscriptable_t, is_const>::operator-(
  const difference_type& movement)
{
  auto temp(*this);
  temp -= movement;
  return temp;
}

template<typename subscriptable_t, bool is_const>
AS_API
  typename subscript_iterator_type<subscriptable_t, is_const>::difference_type
  subscript_iterator_type<subscriptable_t, is_const>::operator-(
    const subscript_iterator_type& sub_it) const
{
  return i - sub_it.i;
}

template<typename subscriptable_t, bool is_const>
AS_API bool subscript_iterator_type<subscriptable_t, is_const>::operator<(
  const subscript_iterator_type& sub_it) const
{
  return i < sub_it.i;
}

template<typename subscriptable_t, bool is_const>
AS_API bool subscript_iterator_type<subscriptable_t, is_const>::operator>(
  const subscript_iterator_type& sub_it) const
{
  return i > sub_it.i;
}

template<typename subscriptable_t, bool is_const>
AS_API bool subscript_iterator_type<subscriptable_t, is_const>::operator<=(
  const subscript_iterator_type& sub_it) const
{
  return !(*this > sub_it);
}

template<typename subscriptable_t, bool is_const>
AS_API bool subscript_iterator_type<subscriptable_t, is_const>::operator>=(
  const subscript_iterator_type& sub_it) const
{
  return !(*this < sub_it);
}

} // namespace as
