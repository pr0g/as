namespace as
{

constexpr u8 operator "" _u8(u64 v) noexcept
{
    return static_cast<u8>(v);
}

constexpr u16 operator "" _u16(u64 v) noexcept
{
    return static_cast<u16>(v);
}

constexpr s8 operator "" _s8(u64 v) noexcept
{
    return static_cast<s8>(v);
}

constexpr s16 operator "" _s16(u64 v) noexcept
{
    return static_cast<s16>(v);
}

} // namespace as
