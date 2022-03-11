#include "../includes/minirt.h"

int	cylinder_intersect(t_cylinder *cylinder, t_ray ray, t_hit_result *hr)
{
	t_quadratic	qua;

	qua.a = pow(ray.direction.x, 2.0) + pow(ray.direction.z, 2.0);
	qua.b = 2.0 * ((ray.direction.x * ray.origin.x) + (ray.direction.z * ray.origin.z));
	qua.c = pow(ray.origin.x, 2.0) + pow(ray.origin.z, 2.0) - 1;
	if (!solve_quadratic(&qua))
		return (0);
	if (qua.t1 < 0 && qua.t2 < 0)
		return (0);
	if (qua.t1 < qua.t2 || (qua.t1 > 0 && qua.t2 < 0))
		hr->t = qua.t1;
	else
		hr->t = qua.t2;
	hr->inter_point = add_vec(ray.origin, multiply_vector(ray.direction, hr->t));
	hr->normal = cylinder_normal(cylinder, hr->inter_point);
	hr->color_at_hit = cylinder->color;
	return (1);
}

t_vector3d	cylinder_normal(t_cylinder *cylinder, t_vector3d vec)
{
	t_vector3d	normal;

	normal = make_vector(vec.x, 0, vec.z);
	return (normalize_vector(normal));
}
