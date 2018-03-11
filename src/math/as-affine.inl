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

}