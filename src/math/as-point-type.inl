namespace as
{

inline v2 operator-(const p2& lhs, const p2& rhs)
{
    return lhs.v - rhs.v;
}

inline p2 operator+(const p2& point, const v2& vec)
{
    return p2(point.v + vec);
}

inline void operator+=(p2& point, const v2& vec)
{
    point.v += vec;
}

inline p2 operator-(const p2& point, const v2& vec)
{
    return p2(point.v - vec);
}

inline void operator-=(p2& point, const v2& vec)
{
    point.v -= vec;
}

inline bool equal(const p2& lhs, const p2& rhs,
    const real epsilon /*= std::numeric_limits<real>::epsilon()*/)
{
    return as::vec::equal(lhs.v, rhs.v, epsilon);
}

inline v3 operator-(const p3& lhs, const p3& rhs)
{
    return lhs.v - rhs.v;
}

inline p3 operator+(const p3& point, const v3& vec)
{
    return p3(point.v + vec);
}

inline void operator+=(p3& point, const v3& vec)
{
    point.v += vec;
}

inline p3 operator-(const p3& point, const v3& vec)
{
    return p3(point.v - vec);
}

inline void operator-=(p3& point, const v3& vec)
{
    point.v -= vec;
}

inline bool equal(const p3& lhs, const p3& rhs,
    const real epsilon /*= std::numeric_limits<real>::epsilon()*/)
{
    return as::vec::equal(lhs.v, rhs.v, epsilon);
}

} // namespace as