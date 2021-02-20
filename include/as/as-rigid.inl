namespace as
{

AS_API constexpr rigid::rigid(const vec3& translation_)
  : rotation(quat::identity()), translation(translation_)
{
}

AS_API constexpr rigid::rigid(const quat& rotation_, const vec3& translation_)
  : rotation(rotation_), translation(translation_)
{
}

AS_API constexpr rigid rigid::identity()
{
  return rigid(quat::identity(), vec3::zero());
}

} // namespace as
