#include "../includes/minirt.h"

int	sphere_intersect(t_sphere *sphere, t_ray ray, t_hit_result *hr)
{
	t_quadratic	qua;

	ray.direction = normalize_vector(ray.direction);
	ray.origin = transform_translate(ray.origin, \
	-sphere->pos.x, -sphere->pos.y, -sphere->pos.z);
	qua.a = 1.0;
	qua.b = 2.0 * dot_vector(ray.origin, ray.direction);
	qua.c = dot_vector(ray.origin, ray.origin) - (pow(sphere->diameter / 2, 2));
	if (!solve_quadratic(&qua))
		return (0);
	if (qua.t1 < 0 && qua.t2 < 0)
		return (0);
	if (qua.t1 < qua.t2 || (qua.t1 > 0 && qua.t2 < 0))
		hr->t = qua.t1;
	else
		hr->t = qua.t2;
	hr->inter_point = transform_translate(add_vec(ray.origin, \
	multiply_vector(ray.direction, hr->t)), \
	sphere->pos.x, sphere->pos.y, sphere->pos.z);
	hr->normal = sphere_normal(sphere, hr->inter_point);
	hr->color_at_hit = sphere->color;
	return (1);
}

t_vector3d	sphere_normal(t_sphere *sphere, t_vector3d vec)
{
	return (normalize_vector(subtract_vec(vec, sphere->pos)));
}
