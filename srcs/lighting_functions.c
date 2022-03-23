/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimitriscr <dimitriscr@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 16:46:54 by rponsonn          #+#    #+#             */
/*   Updated: 2022/03/23 15:53:35 by dimitriscr       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	check_shadow(t_minirt *scene, t_hit_result hit)
{
	t_ray			ray;
	t_hit_result	hit2;

	ray.origin = add_vec(hit.inter_point, multiply_vector(hit.normal, 0.0001));
	ray.direction = normalize_vector(subtract_vec(scene->light->pos, \
hit.inter_point));
	if (find_closest_intersection(scene, ray, &hit2))
	{
		if (hit2.t < vector_magnitude(\
		subtract_vec(scene->light->pos, ray.origin)))
			return (1);
	}
	return (0);
}

t_color	light_plus_ambiant(t_color color, double intensity, t_alight ambiant)
{
	t_color	ret_col;

	ret_col = make_color(\
	(color.r * intensity) + (ambiant.color.r * ambiant.ratio), \
	(color.g * intensity) + (ambiant.color.g * ambiant.ratio), \
	(color.b * intensity) + (ambiant.color.b * ambiant.ratio));
	if (ret_col.r > color.r)
		ret_col.r = color.r;
	if (ret_col.g > color.g)
		ret_col.g = color.g;
	if (ret_col.b > color.b)
		ret_col.b = color.b;
	return (ret_col);
}

t_color	calculate_illumination(t_minirt *scene, t_hit_result *hit)
{
	t_vector3d	inter_cam_norm;
	double		angle;
	double		intensity;

	inter_cam_norm = normalize_vector(subtract_vec(scene->light->pos, \
	hit->inter_point));
	angle = acos(dot_vector(hit->normal, inter_cam_norm));
	if (angle > 1.5708 || check_shadow(scene, *hit))
		return (light_plus_ambiant(hit->color_at_hit, 0, *scene->ambient));
	else
	{
		intensity = scene->light->lum * (1.0 - (angle / 1.5708));
		return (light_plus_ambiant(hit->color_at_hit, intensity, \
		*scene->ambient));
	}
}
