namespace as
{

template<typename T>
AS_API constexpr affine_t<T>::affine_t(const vec<T, 3>& translation_)
  : rotation(mat3::identity()), translation(translation_)
{
}

template<typename T>
AS_API constexpr affine_t<T>::affine_t(
  const mat<T, 3>& rotation_, const vec<T, 3>& translation_)
  : rotation(rotation_), translation(translation_)
{
}

template<typename T>
AS_API constexpr affine_t<T> affine_t<T>::identity()
{
  return affine_t(mat<T, 3>::identity(), vec<T, 3>::zero());
}

template<typename T>
AS_API constexpr index affine_t<T>::size()
{
  return 12;
}

} // namespace as
