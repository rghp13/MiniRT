#include "../includes/minirt.h"

int	plane_intersect(t_plane *plane, t_ray ray, t_hit_result *hr)
{
	t_vector3d	oc;
	double		disc;

	disc = dot_vector(plane->rot, ray.direction);
	if (disc < 0)
		return (0);
	oc = subtract_vec(plane->pos, ray.origin);
	hr->t = dot_vector(oc, plane->rot) / disc;
	if (hr->t < 0)
		return (0);
	hr->inter_point = add_vec(ray.origin, multiply_vector(ray.direction, hr->t));
	hr->normal = plane_normal(plane, hr->inter_point);
	hr->color_at_hit = plane->color;
	return(1);
}

t_vector3d	plane_normal(t_plane *plane, t_vector3d vec)
{
	if (dot_vector(plane->rot, vec) > 0)
		return (multiply_vector(plane->rot, -1));
	return (plane->rot);
}
