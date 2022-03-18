#include "../includes/minirt.h"

t_color	light_plus_ambiant(t_color color, double intensity, t_alight ambiant)
{
	t_color	ret_col;
	
	ret_col = make_color(\
	(color.r * intensity) + (ambiant.color.r * ambiant.ratio), \
	(color.g * intensity) + (ambiant.color.g * ambiant.ratio), \
	(color.b * intensity) + (ambiant.color.g * ambiant.ratio));
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
	t_ray		ray;
	t_vector3d	inter_cam_norm;
	double		angle;
	double		intensity;

	inter_cam_norm = normalize_vector(subtract_vec(scene->light->pos, hit->inter_point));
	angle = acos(dot_vector(hit->normal, inter_cam_norm));
	if (angle > 1.5708)
		return (light_plus_ambiant(hit->color_at_hit, 0, *scene->ambient));
	else
	{
		intensity = scene->light->lum * (1.0 - (angle / 1.5708));
		return (light_plus_ambiant(hit->color_at_hit, intensity, *scene->ambient));
	}
}