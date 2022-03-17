#include "../includes/minirt.h"

t_color	calculate_illumination(t_minirt *scene, t_hit_result *hit)
{
	t_ray		ray;
	t_vector3d	inter_cam_norm;
	double		angle;
	double		intensity;

	// ray.direction = normalize_vector(hit->obj_to_cam);
	// ray.origin = add_vec(hit->inter_point, multiply_vector(hit->normal, 0.1));
	// hit->obj_to_cam = subtract_vec(scene->light->pos, hit->inter_point);
	// hit->normal_cam_dot = dot_vector(normalize_vector(hit->obj_to_cam), normalize_vector(hit->normal));
	// return (vector_to_color(multiply_vector(add_vec(color_to_vector(hit->color_at_hit), multiply_vector(color_to_vector(scene->light->color), hit->normal_cam_dot)), scene->light->lum)));
	inter_cam_norm = normalize_vector(subtract_vec(scene->light->pos, hit->inter_point));
	angle = acos(dot_vector(hit->normal, inter_cam_norm));
	if (angle > 1.5708)
		return (make_color(0,0,0));
	else
	{
		intensity = scene->light->lum * (1.0 - (angle / 1.5708));
		return (make_color(hit->color_at_hit.r * intensity, hit->color_at_hit.g * intensity, hit->color_at_hit.b * intensity));
	}
}