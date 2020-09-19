namespace as
{

AS_API constexpr affine_t::affine_t(const vec3_t& translation_)
  : rotation(mat3_t::identity()), translation(translation_)
{
}

AS_API constexpr affine_t::affine_t(
  const mat3_t& rotation_, const vec3_t& translation_)
  : rotation(rotation_), translation(translation_)
{
}

} // namespace as
