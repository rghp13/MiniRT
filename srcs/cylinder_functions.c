#include "../includes/minirt.h"

int	cylinder_intersect(t_cylinder *cylinder, t_ray ray, t_hit_result *hr)
{
	t_vector3d	temp_pos;
	double		a;
	double		b;
	double		c;
	double		delta;

	ray.origin = transform_translate(ray.origin, -cylinder->pos.x, -cylinder->pos.y, -cylinder->pos.z);
	ray.origin = transform_rotate(ray.origin, 20, 10, 0);
	ray.direction = transform_rotate(ray.direction, 20, 10, 0);
	//ray.direction = transform_translate(ray.direction, -cylinder->pos.x, -cylinder->pos.y, -cylinder->pos.z);
	temp_pos = make_vector(0, 0, 0);
	//temp_pos = cylinder->pos;
	ray.direction = normalize_vector(ray.direction);
	a = (ray.direction.x * ray.direction.x) + (ray.direction.z * ray.direction.z);
	b = ray.direction.x * (ray.origin.x - temp_pos.x) + ray.direction.z * (ray.origin.z - temp_pos.z);
	c = pow(ray.origin.x - temp_pos.x, 2) + pow(ray.origin.z - temp_pos.z, 2) - pow(cylinder->diameter / 2, 2);
	delta = b * b - a * c;
	if (delta > 0)
	{
		hr->t = -b - sqrt(delta) / (a);
		if (hr->t <= 0)
			hr->t = -b + sqrt(delta) / (a);
		if (fabs(add_vec(ray.origin, multiply_vector(ray.direction, hr->t)).y - temp_pos.y) > cylinder->height / 2)
			return (0);
		return (1);
	}
	return (0);
}

t_vector3d	cylinder_normal(t_cylinder *cylinder, t_vector3d vec)
{
	t_vector3d	normal;

	normal = make_vector(vec.x - cylinder->pos.x, vec.y - vec.y, vec.z - cylinder->pos.z);
	normal = transform_t_rotate(normal, cylinder->rot);
	normal = normalize_vector(normal);
	return (normal);
}
