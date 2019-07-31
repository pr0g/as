namespace as
{

inline const vec2_t operator-(const point2_t& lhs, const point2_t& rhs)
{
    return lhs.v - rhs.v;
}

inline const point2_t operator+(const point2_t& point, const vec2_t& vec)
{
    return point2_t(point.v + vec);
}

inline point2_t& operator+=(point2_t& point, const vec2_t& vec)
{
    point.v += vec;
    return point;
}

inline const point2_t operator-(const point2_t& point, const vec2_t& vec)
{
    return point2_t(point.v - vec);
}

inline point2_t& operator-=(point2_t& point, const vec2_t& vec)
{
    point.v -= vec;
    return point;
}

inline const vec3_t operator-(const point3_t& lhs, const point3_t& rhs)
{
    return lhs.v - rhs.v;
}

inline const point3_t operator+(const point3_t& point, const vec3_t& vec)
{
    return point3_t(point.v + vec);
}

inline point3_t& operator+=(point3_t& point, const vec3_t& vec)
{
    point.v += vec;
    return point;
}

inline const point3_t operator-(const point3_t& point, const vec3_t& vec)
{
    return point3_t(point.v - vec);
}

inline point3_t& operator-=(point3_t& point, const vec3_t& vec)
{
    point.v -= vec;
    return point;
}

} // namespace as
