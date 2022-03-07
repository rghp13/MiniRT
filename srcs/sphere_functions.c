#include "../includes/minirt.h"

int	sphere_intersect(t_sphere *sphere, t_ray ray, double *t)
{
	t_vector3d	oc;
	double		a;
	double		b;
	double		c;
	double		disc;

	oc = subtract_vec(ray.origin, sphere->pos);
	a = dot_vector(ray.direction, ray.direction);
	b = 2.0 * dot_vector(oc, ray.direction);
	c = dot_vector(oc, oc) - ((sphere->diameter / 2) * (sphere->diameter / 2));
	disc = b * b - (4 * a * c);
	if (disc < 0)
		return (0);
	*t = (-b - sqrt(disc)) / (2.0*a);
	return(1);
}

t_vector3d	sphere_normal(t_sphere *sphere, t_vector3d vec)
{
	t_vector3d	normal;

	normal = divide_vector(subtract_vec(vec, sphere->pos), sphere->diameter / 2);
	if (dot_vector(normal, vec) > 0)
		return (multiply_vector(normal, -1));
	return (normal);
}
