#include "../includes/minirt.h"

int	plane_intersect(t_plane *plane, t_ray ray, double *t)
{
	t_vector3d	oc;
	double		disc;

	disc = dot_vector(plane->rot, ray.direction);
	if (disc < 0)
		return (0);
	oc = subtract_vec(plane->pos, ray.origin);
	*t = dot_vector(oc, plane->rot) / disc;
	if (t < 0)
		return (0);
	return(1);
}

t_vector3d	plane_normal(t_plane *plane, t_vector3d vec)
{
	if (dot_vector(plane->rot, vec) > 0)
		return (multiply_vector(plane->rot, -1));
	return (plane->rot);
}
