namespace as
{

AS_API constexpr affine_t::affine_t(
    const mat3_t& rotation_, const point3_t& position_)
    : rotation(rotation_), position(position_)
{
}

} // namespace as
