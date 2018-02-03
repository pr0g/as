namespace as
{

constexpr m33 m33::from_ptr(const real* data)
{
    return as::mat::from_ptr<real, 3, 3>(data);
}

constexpr m33 m33::from_arr(const real(&data)[9])
{
    return as::mat::from_arr<real, 3, 3>(data);
}

constexpr m33 m33::axis_angle(const v3& axis, real radians)
{
    return {
        cosr(radians) + ((axis.x * axis.x) * (1.0f - cosr(radians))),
        (axis.y * axis.x * (1.0f - cosr(radians))) + (axis.z * sinr(radians)),
        (axis.z * axis.x * (1.0f - cosr(radians))) - (axis.y * sinr(radians)),
        (axis.x * axis.y) * (1.0f - cosr(radians)) - (axis.z * sinr(radians)),
        cosr(radians) + ((axis.y * axis.y) * (1.0f - cosr(radians))),
        (axis.z * axis.y * (1.0f - cosr(radians))) + (axis.x * sinr(radians)),
        (axis.x * axis.z * (1.0f - cosr(radians))) + (axis.y * sinr(radians)),
        (axis.y * axis.z * (1.0f - cosr(radians))) - (axis.x * sinr(radians)),
        cosr(radians) + ((axis.z * axis.z) * (1.0f - cosr(radians)))
    };
}

constexpr m33 m33::rotation_xyz(real x, real y, real z)
{
    return {
        cosr(y) * cosr(z),
        cosr(y) * sinr(z),
        -sinr(y),
        (sinr(x) * sinr(y) * cosr(z)) - (cosr(x) * sinr(z)),
        (sinr(x) * sinr(y) * sinr(z)) + (cosr(x) * cosr(z)),
        sinr(x) * cosr(y),
        (cosr(x) * sinr(y) * cosr(z)) + (sinr(x) * sinr(z)),
        (cosr(x) * sinr(y) * sinr(z)) - (sinr(x) * cosr(z)),
        cosr(x) * cosr(y)
    };
}

constexpr m33 m33::rotation_zxy(real x, real y, real z)
{
    return {
        cosr(z) * cosr(y) + sinr(x) * sinr(y) * sinr(z),
        sinr(z) * cosr(x),
        -sinr(y) * cosr(z) + sinr(z) * sinr(x) * cosr(y),
        -sinr(z) * cosr(y) + cosr(z) * sinr(x) * sinr(y),
        cosr(z) * cosr(x),
        -sinr(z) * -sinr(y) + cosr(z) * sinr(x) * cosr(y),
        cosr(x) * sinr(y),
        -sinr(x),
        cosr(x) * cosr(y),
    };
}

constexpr m33 m33::rotation_x(real radians)
{
    return {
        1.0f, 0.0f, 0.0f,
        0.0f, cosr(radians), sinr(radians),
        0.0f, -sinr(radians), cosr(radians)
    };
}

constexpr m33 m33::rotation_y(real radians)
{
    return {
        cosr(radians), 0.0f, -sinr(radians),
        0.0f, 1.0f, 0.0f,
        sinr(radians), 0.0f, cosr(radians)
    };
}

constexpr m33 m33::rotation_z(real radians)
{
    return {
        cosr(radians), sinr(radians), 0.0f,
        -sinr(radians), cosr(radians), 0.0f,
        0.0f, 0.0f, 1.0f
    };
}

} // namespace as