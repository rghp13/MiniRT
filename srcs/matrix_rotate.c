#include "../includes/minirt.h"

t_vector3d	x_axis_rotation(t_vector3d vec, double theta)
{
	t_vector3d	result;

	theta = theta * (M_PI / 180);
	result.y = (vec.y * cos(theta)) + (vec.z * (sin(theta) * -1));
	result.z = (vec.y * sin(theta)) + (vec.z * cos(theta));
	result.x = vec.x;
	return (result);
}

t_vector3d	y_axis_rotation(t_vector3d vec, double theta)
{
	t_vector3d	result;

	theta = theta * (M_PI / 180);
	result.x = (vec.x * cos(theta)) + (vec.z * sin(theta));
	result.z = (vec.x * (sin(theta) * -1)) + (vec.z * cos(theta));
	result.y = vec.y;
	return (result);
}

t_vector3d	z_axis_rotation(t_vector3d vec, double theta)
{
	t_vector3d	result;

	theta = theta * (M_PI / 180);
	result.x = (vec.x * cos(theta)) + (vec.y * (sin(theta) * -1));
	result.y = (vec.x * sin(theta)) + (vec.y * cos(theta));
	result.z = vec.z;
	return (result);
}

t_vector3d	transform_t_rotate(t_vector3d vec, t_vector3d rotation)
{
	vec = z_axis_rotation(vec, rotation.z);
	vec = y_axis_rotation(vec, rotation.y);
	vec = x_axis_rotation(vec, rotation.x);
	return (vec);
}

t_vector3d	transform_rotate(t_vector3d vec, double r_x, double r_y, double r_z)
{
	vec = z_axis_rotation(vec, r_z);
	vec = y_axis_rotation(vec, r_y);
	vec = x_axis_rotation(vec, r_x);
	return (vec);
}
