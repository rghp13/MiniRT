/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponsonn <rponsonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 16:43:53 by rponsonn          #+#    #+#             */
/*   Updated: 2022/03/22 16:43:54 by rponsonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_vector3d	cylinder_normal(t_cylinder *cylinder, t_vector3d vec)
{
	t_vector3d	normal;

	(void)cylinder;
	normal = make_vector(vec.x, 0, vec.z);
	return (normalize_vector(normal));
}

t_vector3d	cap_normal(double side)
{
	if (side > 0)
		return (make_vector(0, 1, 0));
	else
		return (make_vector(0, -1, 0));
}

int	cap_intersect(t_cylinder *cylinder, t_ray ray, \
t_hit_result *hr, double side)
{
	double		denom;
	t_vector3d	oc;

	denom = dot_vector(normalize_vector(make_vector(0, -side, 0)) \
	, ray.direction);
	if (denom > 0)
	{
		oc = subtract_vec(make_vector(0, side, 0), ray.origin);
		hr->t = dot_vector(oc, normalize_vector(make_vector(0, -side, 0))) \
		/ denom;
		hr->inter_point = add_vec(ray.origin, \
		multiply_vector(ray.direction, hr->t));
		hr->normal = cap_normal(side);
		hr->color_at_hit = cylinder->color;
		if (hr->t >= 0)
		{
			oc = subtract_vec(hr->inter_point, make_vector(0, side, 0));
			denom = dot_vector(oc, oc);
			*hr = local_to_world(*hr, cylinder->pos, cylinder->rot);
			return (sqrt(denom) <= cylinder->diameter / 2);
		}
	}
	return (0);
}

int	body_intersect(t_cylinder *cylinder, t_ray ray, t_hit_result *hr)
{
	t_quadratic	qua;

	qua.a = pow(ray.direction.x, 2.0) + pow(ray.direction.z, 2.0);
	qua.b = 2.0 * ((ray.direction.x * ray.origin.x) \
	+ (ray.direction.z * ray.origin.z));
	qua.c = pow(ray.origin.x, 2.0) \
	+ pow(ray.origin.z, 2.0) - pow(cylinder->diameter / 2, 2);
	if (!solve_quadratic(&qua) && qua.t1 < 0 && qua.t2 < 0)
		return (0);
	if (qua.t1 < qua.t2 || (qua.t1 > 0 && qua.t2 < 0))
		hr->t = qua.t1;
	else
		hr->t = qua.t2;
	hr->inter_point = add_vec(ray.origin, \
	multiply_vector(ray.direction, hr->t));
	hr->normal = cylinder_normal(cylinder, hr->inter_point);
	hr->color_at_hit = cylinder->color;
	if (hr->inter_point.y >= -cylinder->height / 2 \
	&& hr->inter_point.y <= cylinder->height / 2)
	{
		*hr = local_to_world(*hr, cylinder->pos, cylinder->rot);
		return (1);
	}
	return (0);
}

int	cylinder_intersect(t_cylinder *cylinder, t_ray ray, t_hit_result *hr)
{
	int				hit[3];
	t_hit_result	hit_body;
	t_hit_result	hit_top;
	t_hit_result	hit_bottom;

	ray = world_to_local(ray, cylinder->pos, cylinder->rot);
	hit[0] = body_intersect(cylinder, ray, &hit_body);
	hit[1] = cap_intersect(cylinder, ray, &hit_top, cylinder->height / 2);
	hit[2] = cap_intersect(cylinder, ray, &hit_bottom, -cylinder->height / 2);
	if (!hit[0] && !hit[1] && !hit[2])
		return (0);
	if (hit[0])
	{
		*hr = hit_body;
		if (hit[1] && hit_top.t < hr->t)
			*hr = hit_top;
		if (hit[2] && hit_bottom.t < hr->t)
			*hr = hit_bottom;
		return (1);
	}
	if (hit[1] && (hit_top.t < hit_bottom.t || !hit[2]))
		*hr = hit_top;
	else if (hit[2])
		*hr = hit_bottom;
	return (1);
}
