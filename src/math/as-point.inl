namespace as
{

inline vec2_t operator-(const point2_t& lhs, const point2_t& rhs)
{
    return lhs.v - rhs.v;
}

inline point2_t operator+(const point2_t& point, const vec2_t& vec)
{
    return point2_t(point.v + vec);
}

inline void operator+=(point2_t& point, const vec2_t& vec)
{
    point.v += vec;
}

inline point2_t operator-(const point2_t& point, const vec2_t& vec)
{
    return point2_t(point.v - vec);
}

inline void operator-=(point2_t& point, const vec2_t& vec)
{
    point.v -= vec;
}

inline vec3_t operator-(const point3_t& lhs, const point3_t& rhs)
{
    return lhs.v - rhs.v;
}

inline point3_t operator+(const point3_t& point, const vec3_t& vec)
{
    return point3_t(point.v + vec);
}

inline void operator+=(point3_t& point, const vec3_t& vec)
{
    point.v += vec;
}

inline point3_t operator-(const point3_t& point, const vec3_t& vec)
{
    return point3_t(point.v - vec);
}

inline void operator-=(point3_t& point, const vec3_t& vec)
{
    point.v -= vec;
}

} // namespace as