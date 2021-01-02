namespace as
{

template<typename subscriptable_t>
subscript_iterator_type<subscriptable_t>::subscript_iterator_type(
  subscriptable_t& subscriptable_, index index_)
  : i(index_), subscriptable(subscriptable_) {}

template<typename subscriptable_t>
bool subscript_iterator_type<subscriptable_t>::operator!=(
  const subscript_iterator_type<subscriptable_t>& sub_it) const
{
  return sub_it.i != i;
}

template<typename subscriptable_t>
subscript_iterator_type<subscriptable_t>&
subscript_iterator_type<subscriptable_t>::operator++()
{
  ++i;
  return *this;
}

} // namespace as
