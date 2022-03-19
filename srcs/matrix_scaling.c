#include "../includes/minirt.h"

t_vector3d	transform_t_scale(t_vector3d point, t_vector3d scale)
{
	point.x = point.x * scale.x;
	point.y = point.y * scale.y;
	point.z = point.z * scale.z;
	return (point);
}

t_vector3d	transform_scale(t_vector3d point, \
double s_x, double s_y, double s_z)
{
	point.x = point.x * s_x;
	point.y = point.y * s_y;
	point.z = point.z * s_z;
	return (point);
}

t_vector3d	transform_uniform_scale(t_vector3d point, double s)
{
	point.x = point.x * s;
	point.y = point.y * s;
	point.z = point.z * s;
	return (point);
}
