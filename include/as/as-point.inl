namespace as
{

const vec2_t operator-(const point2_t& lhs, const point2_t& rhs)
{
    return lhs.v - rhs.v;
}

const point2_t operator+(const point2_t& point, const vec2_t& vec)
{
    return point2_t(point.v + vec);
}

point2_t& operator+=(point2_t& point, const vec2_t& vec)
{
    point.v += vec;
    return point;
}

const point2_t operator-(const point2_t& point, const vec2_t& vec)
{
    return point2_t(point.v - vec);
}

point2_t& operator-=(point2_t& point, const vec2_t& vec)
{
    point.v -= vec;
    return point;
}

const vec3_t operator-(const point3_t& lhs, const point3_t& rhs)
{
    return lhs.v - rhs.v;
}

const point3_t operator+(const point3_t& point, const vec3_t& vec)
{
    return point3_t(point.v + vec);
}

point3_t& operator+=(point3_t& point, const vec3_t& vec)
{
    point.v += vec;
    return point;
}

const point3_t operator-(const point3_t& point, const vec3_t& vec)
{
    return point3_t(point.v - vec);
}

point3_t& operator-=(point3_t& point, const vec3_t& vec)
{
    point.v -= vec;
    return point;
}

} // namespace as
