namespace as
{

template<typename T>
AS_API constexpr rigid_t<T>::rigid_t(const vec<T, 3>& translation_)
  : rotation(quat::identity()), translation(translation_)
{
}

template<typename T>
AS_API constexpr rigid_t<T>::rigid_t(
  const quat& rotation_, const vec<T, 3>& translation_)
  : rotation(rotation_), translation(translation_)
{
}

template<typename T>
AS_API constexpr rigid_t<T> rigid_t<T>::identity()
{
  return rigid(quat::identity(), vec<T, 3>::zero());
}

template<typename T>
AS_API constexpr index rigid_t<T>::size()
{
  return 7;
}

} // namespace as
