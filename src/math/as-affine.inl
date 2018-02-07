namespace as
{

#if defined AS_COL_MAJOR
vec3_t operator*(const affine_t& transform, const vec3_t& vec)
{
    return transform.rotation * vec + transform.position;
}
#elif defined AS_ROW_MAJOR
vec3_t operator*(const vec3_t& vec, const affine_t& transform)
{
    return vec * transform.rotation + transform.position;
}
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR

vec3_t affine_t::transform_dir(const vec3_t& direction)
{
#if defined AS_COL_MAJOR
    return rotation * direction;
#elif defined AS_ROW_MAJOR
    return direction * rotation;
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

vec3_t affine_t::transform_pos(const vec3_t& position_)
{
#if defined AS_COL_MAJOR
    return rotation * position_ + position;
#elif defined AS_ROW_MAJOR
    return position_ * rotation + position;
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

vec3_t affine_t::inv_transform_dir(const vec3_t& direction)
{
    const mat33_t invRotation = as::mat::inverse(rotation);
#if defined AS_COL_MAJOR
    return invRotation * direction;
#elif defined AS_ROW_MAJOR
    return direction * invRotation;
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

vec3_t affine_t::inv_transform_pos(const vec3_t& position_)
{
    const mat33_t invRotation = as::mat::inverse(rotation);
#if defined AS_COL_MAJOR
    return invRotation * (position_ - position);
#elif defined AS_ROW_MAJOR
    return (position_ - position) * invRotation;
#endif // AS_COL_MAJOR ? AS_ROW_MAJOR
}

}