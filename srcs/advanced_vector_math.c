#include "../includes/minirt.h"

t_vector3d	normalize_vector(t_vector3d v1)
{
	double		mg;
	t_vector3d	res_vec;

	mg = sqrt((v1.x * v1.x) + (v1.y * v1.y) + (v1.z * v1.z));
	res_vec.x = v1.x / mg;
	res_vec.y = v1.y / mg;
	res_vec.z = v1.z / mg;
	return (res_vec);
}

double	dot_vector(t_vector3d v1, t_vector3d v2)
{
	return ((v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z));
}
