namespace as
{

AS_API constexpr affine::affine(const vec3& translation_)
  : rotation(mat3::identity()), translation(translation_)
{
}

AS_API constexpr affine::affine(const mat3& rotation_, const vec3& translation_)
  : rotation(rotation_), translation(translation_)
{
}

AS_API constexpr affine affine::identity()
{
  return affine(mat3::identity(), vec3::zero());
}

AS_API constexpr index affine::size()
{
  return 12;
}

} // namespace as
