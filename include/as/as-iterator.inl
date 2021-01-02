namespace as
{

template<typename subscriptable_t>
AS_API subscript_iterator_type<subscriptable_t>::subscript_iterator_type(
  subscriptable_t& subscriptable_, index index_)
  : i(index_), subscriptable(subscriptable_)
{
}

template<typename subscriptable_t>
AS_API bool subscript_iterator_type<subscriptable_t>::operator==(
  const subscript_iterator_type<subscriptable_t>& sub_it) const
{
  return sub_it.i == i;
}

template<typename subscriptable_t>
AS_API bool subscript_iterator_type<subscriptable_t>::operator!=(
  const subscript_iterator_type<subscriptable_t>& sub_it) const
{
  return !operator==(sub_it);
}

template<typename subscriptable_t>
AS_API subscript_iterator_type<subscriptable_t>& subscript_iterator_type<
  subscriptable_t>::operator++()
{
  ++i;
  return *this;
}

template<typename subscriptable_t>
AS_API subscript_iterator_type<subscriptable_t> subscript_iterator_type<
  subscriptable_t>::operator++(int)
{
  auto temp(*this);
  ++i;
  return temp;
}

template<typename subscriptable_t>
AS_API subscript_iterator_type<subscriptable_t>& subscript_iterator_type<
  subscriptable_t>::operator--()
{
  --i;
  return *this;
}

template<typename subscriptable_t>
AS_API subscript_iterator_type<subscriptable_t> subscript_iterator_type<
  subscriptable_t>::operator--(int)
{
  auto temp(*this);
  --i;
  return temp;
}

template<typename subscriptable_t>
AS_API subscript_iterator_type<subscriptable_t>& subscript_iterator_type<
  subscriptable_t>::operator+=(const difference_type& movement)
{
  i += movement;
  return *this;
}

template<typename subscriptable_t>
AS_API subscript_iterator_type<subscriptable_t>& subscript_iterator_type<
  subscriptable_t>::operator-=(const difference_type& movement)
{
  i -= movement;
  return *this;
}

template<typename subscriptable_t>
AS_API subscript_iterator_type<subscriptable_t> subscript_iterator_type<
  subscriptable_t>::operator+(const difference_type& movement)
{
  auto temp(*this);
  temp += movement;
  return temp;
}

template<typename subscriptable_t>
AS_API subscript_iterator_type<subscriptable_t> subscript_iterator_type<
  subscriptable_t>::operator-(const difference_type& movement)
{
  auto temp(*this);
  temp -= movement;
  return temp;
}

template<typename subscriptable_t>
AS_API typename subscript_iterator_type<subscriptable_t>::difference_type
subscript_iterator_type<subscriptable_t>::operator-(
  const subscript_iterator_type& sub_it) const
{
  return i - sub_it.i;
}

template<typename subscriptable_t>
AS_API bool subscript_iterator_type<subscriptable_t>::operator<(
  const subscript_iterator_type& sub_it) const
{
  return i < sub_it.i;
}

template<typename subscriptable_t>
AS_API bool subscript_iterator_type<subscriptable_t>::operator>(
  const subscript_iterator_type& sub_it) const
{
  return i > sub_it.i;
}

template<typename subscriptable_t>
AS_API bool subscript_iterator_type<subscriptable_t>::operator<=(
  const subscript_iterator_type& sub_it) const
{
  return !(*this > sub_it);
}

template<typename subscriptable_t>
AS_API bool subscript_iterator_type<subscriptable_t>::operator>=(
  const subscript_iterator_type& sub_it) const
{
  return !(*this < sub_it);
}

} // namespace as
