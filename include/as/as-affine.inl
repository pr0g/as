namespace as
{

AS_API constexpr affine_t::affine_t(const point3_t& position_)
    : rotation(mat3_t::identity()), position(position_)
{
}

AS_API constexpr affine_t::affine_t(
    const mat3_t& rotation_, const point3_t& position_)
    : rotation(rotation_), position(position_)
{
}

} // namespace as
