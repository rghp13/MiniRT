#include "../includes/minirt.h"

int	cylinder_intersect(t_cylinder *cylinder, t_ray ray, double *t)
{
	double		a;
	double		b;
	double		c;
	double		delta;

	// ray.origin = transform_rotate(ray.origin, acos(-cylinder->rot.x), acos(-cylinder->rot.y), acos(-cylinder->rot.z));
	// ray.direction = transform_rotate(ray.direction, acos(-cylinder->rot.x), acos(-cylinder->rot.y), acos(-cylinder->rot.z));
	// ray.origin = transform_translate(ray.origin, -cylinder->pos.x, -cylinder->pos.y, -cylinder->pos.z);
	// ray.direction = transform_translate(ray.direction, -cylinder->pos.x, -cylinder->pos.y, -cylinder->pos.z);
	// cylinder->pos = make_vector(0, 0, 0);
	// cylinder->rot = make_vector(0, 0, 0);
	a = (ray.direction.x * ray.direction.x) + (ray.direction.z * ray.direction.z);
	b = ray.direction.x * (ray.origin.x - cylinder->pos.x) + ray.direction.z * (ray.origin.z - cylinder->pos.z);
	c = pow(ray.origin.x - cylinder->pos.x, 2) + pow(ray.origin.z - cylinder->pos.z, 2) - pow(cylinder->diameter / 2, 2);
	delta = b * b - a * c;
	if (delta > 0)
	{
		*t = -b - sqrt(delta) / (a);
		if (*t <= 0)
			*t = -b + sqrt(delta) / (a);
		if (fabs(add_vec(ray.origin, multiply_vector(ray.direction, *t)).y - cylinder->pos.y) > cylinder->height / 2)
			return (0);
		return (1);
	}
	return (0);
}

t_vector3d	cylinder_normal(t_cylinder *cylinder, t_vector3d vec)
{
	t_vector3d	normal;

	normal = make_vector(vec.x - cylinder->pos.x, vec.y - vec.y, vec.z - cylinder->pos.z);
	transform_t_rotate(normal, cylinder->rot);
	normalize_vector(normal);
	return (normal);
}
