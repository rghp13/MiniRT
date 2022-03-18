#include "../includes/minirt.h"

t_vector3d	cylinder_normal(t_cylinder *cylinder, t_vector3d vec)
{
	t_vector3d	normal;

	normal = make_vector(vec.x, 0, vec.z);
	return (normalize_vector(normal));
}

t_vector3d	cap_normal(double side)
{
	t_vector3d	vec;
	
	if (side > 0)
		return (make_vector(0, 1, 0));
	else
		return (make_vector(0, -1, 0));
}

int	cap_intersect(t_cylinder *cylinder, t_ray ray, t_hit_result *hr, double side)
{
	double		denom;
	t_vector3d	oc;

	denom = dot_vector(normalize_vector(make_vector(0, -side, 0)), ray.direction);
	if (denom > 0)
	{
		oc = subtract_vec(make_vector(0, side, 0), ray.origin);
		hr->t = dot_vector(oc, normalize_vector(make_vector(0, -side, 0))) / denom;
		hr->inter_point = add_vec(ray.origin, multiply_vector(ray.direction, hr->t));
		hr->normal = cap_normal(side);
		hr->color_at_hit = cylinder->color;
		if (hr->t >= 0)
		{
			oc = subtract_vec(hr->inter_point, make_vector(0, side, 0));
			denom = dot_vector(oc, oc);
			hr->inter_point = transform_inverse_rotate(hr->inter_point, get_all_axis_rotation(cylinder->rot));
			hr->normal = transform_inverse_rotate(hr->normal, get_all_axis_rotation(cylinder->rot));
			hr->inter_point = transform_translate(hr->inter_point, cylinder->pos.x, cylinder->pos.y, cylinder->pos.z);
			return (sqrt(denom) <= cylinder->diameter / 2);
		}
	}
	return (0);
}

int	body_intersect(t_cylinder *cylinder, t_ray ray, t_hit_result *hr)
{
	t_quadratic	qua;
	double		r;

	qua.a = pow(ray.direction.x, 2.0) + pow(ray.direction.z, 2.0);
	qua.b = 2.0 * ((ray.direction.x * ray.origin.x) + (ray.direction.z * ray.origin.z));
	qua.c = pow(ray.origin.x, 2.0) + pow(ray.origin.z, 2.0) - pow(cylinder->diameter / 2, 2);
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
	if (hr->inter_point.y >= -cylinder->height / 2 && hr->inter_point.y <= cylinder->height / 2)
	{
		hr->inter_point = transform_inverse_rotate(hr->inter_point, get_all_axis_rotation(cylinder->rot));
		hr->normal = transform_inverse_rotate(hr->normal, get_all_axis_rotation(cylinder->rot));
		hr->inter_point = transform_translate(hr->inter_point, cylinder->pos.x, cylinder->pos.y, cylinder->pos.z);
		return (1);
	}
	return (0);
}

int	cylinder_intersect(t_cylinder *cylinder, t_ray ray, t_hit_result *hr)
{
	int				body;
	t_hit_result	hit_body;
	int				top;
	t_hit_result	hit_top;
	int				bottom;
	t_hit_result	hit_bottom;

	ray.origin = transform_translate(ray.origin, -cylinder->pos.x, -cylinder->pos.y, -cylinder->pos.z);
	ray.direction = transform_t_rotate(ray.direction, get_all_axis_rotation(cylinder->rot));
	ray.origin = transform_t_rotate(ray.origin, get_all_axis_rotation(cylinder->rot));
	body = body_intersect(cylinder, ray, &hit_body);
	top = cap_intersect(cylinder, ray, &hit_top, cylinder->height / 2);
	bottom = cap_intersect(cylinder, ray, &hit_bottom, -cylinder->height / 2);
	if (!body && !top && !bottom)
		return (0);
	if (body)
	{
		*hr = hit_body;
		if (top && hit_top.t < hr->t)
			*hr = hit_top;
		if (bottom && hit_bottom.t < hr->t)
			*hr = hit_bottom;
		return (1);
	}
	if (top && (hit_top.t < hit_bottom.t || !bottom))
		*hr = hit_top;
	else if (bottom)
		*hr = hit_bottom;
	return (1);
}
