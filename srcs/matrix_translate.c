#include "../includes/minirt.h"

t_vector3d	transform_t_translate(t_vector3d vec, t_vector3d t_vec)
{
	vec.x = vec.x + t_vec.x;
	vec.y = vec.y + t_vec.y;
	vec.z = vec.z + t_vec.z;
	return (vec);
}

t_vector3d	transform_translate(t_vector3d vec, \
double t_x, double t_y, double t_z)
{
	vec.x = vec.x + t_x;
	vec.y = vec.y + t_y;
	vec.z = vec.z + t_z;
	return (vec);
}

t_vector3d	transform_uniform_translate(t_vector3d vec, double t)
{
	vec.x = vec.x + t;
	vec.y = vec.y + t;
	vec.z = vec.z + t;
	return (vec);
}
