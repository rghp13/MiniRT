#include "../includes/minirt.h"

int	sphere_intersect(t_sphere *sphere, t_ray ray, t_hit_result *hr)
{
	t_quadratic	qua;

	qua.oc = subtract_vec(ray.origin, sphere->pos);
	qua.a = dot_vector(ray.direction, ray.direction);
	qua.b = 2.0 * dot_vector(qua.oc, ray.direction);
	qua.c = dot_vector(qua.oc, qua.oc) - ((sphere->diameter / 2) * (sphere->diameter / 2));
	if (!solve_quadratic(&qua))
		return (0);
	if (qua.t1 < 0 && qua.t2 < 0)
		return (0);
	if (qua.t1 < qua.t2 || (qua.t1 > 0 && qua.t2 < 0))
		hr->t = qua.t1;
	else
		hr->t = qua.t2;
	hr->inter_point = add_vec(ray.origin, multiply_vector(ray.direction, hr->t));
	hr->normal = sphere_normal(sphere, hr->inter_point);
	hr->color_at_hit = sphere->color;
	return(1);
}

t_vector3d	sphere_normal(t_sphere *sphere, t_vector3d vec)
{
	t_vector3d	normal;

	normal = normalize_vector(divide_vector(subtract_vec(vec, sphere->pos), sphere->diameter / 2));
	if (dot_vector(normal, vec) > 0)
		return (multiply_vector(normal, -1));
	return (normal);
}
