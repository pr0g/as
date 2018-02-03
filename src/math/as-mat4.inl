namespace as
{

constexpr m44 m44::from_ptr(const real* data)
{
    return as::mat::from_ptr<real, 4, 4>(data);
}

constexpr m44 m44::from_arr(const real(&data)[16])
{
    return as::mat::from_arr<real, 4, 4>(data);
}

constexpr m44 m44::translation(const v3& translation)
{
    return { v4::axis_x(), v4::axis_y(), v4::axis_z(), { translation, 1.0f } };
}

constexpr m44 m44::rotation(const m33& rotation)
{
    return { rotation, v3::zero() };
}

constexpr inline static m44 transform(const m33& rotation, const v3& translation)
{
    return { rotation, translation };
}

} // namespace as