#include "../includes/minirt.h"

int	find_closest_sphere(t_minirt *scene, t_ray ray, t_hit_result *closest)
{
	int				found;
	t_hit_result	hit;
	t_sphere		*current;

	found = 0;
	current = scene->sphere;
	closest->t = __DBL_MAX__;
	while (current)
	{
		if (sphere_intersect(current, ray, &hit))
		{
			if (hit.t < closest->t)
			{
				*closest = hit;
				found = 1;
			}
		}
		current = current->next;
	}
	return (found);
}

int	find_closest_plane(t_minirt *scene, t_ray ray, t_hit_result *closest)
{
	int				found;
	t_hit_result	hit;
	t_plane			*current;

	found = 0;
	current = scene->plane;
	closest->t = __DBL_MAX__;
	while (current)
	{
		if (plane_intersect(current, ray, &hit))
		{
			if (hit.t < closest->t)
			{
				*closest = hit;
				found = 1;
			}
		}
		current = current->next;
	}
	return (found);
}

int	find_closest_cylinder(t_minirt *scene, t_ray ray, t_hit_result *closest)
{
	int				found;
	t_hit_result	hit;
	t_cylinder		*current;

	found = 0;
	current = scene->cylinder;
	closest->t = __DBL_MAX__;
	while (current)
	{
		if (cylinder_intersect(current, ray, &hit))
		{
			if (hit.t < closest->t)
			{
				*closest = hit;
				found = 1;
			}
		}
		current = current->next;
	}
	return (found);
}

int	find_closest_intersection(t_minirt *scene, \
t_ray ray, t_hit_result *closest_hit)
{
	t_hit_result	closest_sphere;
	t_hit_result	closest_plane;
	t_hit_result	closest_cylinder;

	if (!find_closest_sphere(scene, ray, &closest_sphere))
		closest_sphere.t = __DBL_MAX__;
	if (!find_closest_plane(scene, ray, &closest_plane))
		closest_plane.t = __DBL_MAX__;
	if (!find_closest_cylinder(scene, ray, &closest_cylinder))
		closest_cylinder.t = __DBL_MAX__;
	if (closest_sphere.t < closest_cylinder.t && closest_sphere.t \
	< closest_plane.t && closest_sphere.t > 0)
		*closest_hit = closest_sphere;
	else if (closest_cylinder.t < closest_plane.t && closest_cylinder.t > 0)
		*closest_hit = closest_cylinder;
	else if (closest_plane.t > 0)
		*closest_hit = closest_plane;
	else
		return (0);
	if (closest_hit->t == __DBL_MAX__)
		return (0);
	return (1);
}
