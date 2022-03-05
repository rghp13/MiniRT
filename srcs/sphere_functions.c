#include "../includes/minirt.h"

int	sphere_intersect(t_sphere *sphere, t_ray ray, double *t)
{
	t_vector3d	oc;
	double		b;
	double		c;
	double		disk;

	oc = subtract_vec(ray.origin, sphere->pos);
	b = 2 * dot_vector(oc, ray.direction);
	c = dot_vector(oc, oc)  - (sphere->diameter / 2) * (sphere->diameter / 2);
	disk = b * b - 4 * c;
	if (disk < 0.0001)
		return (0);
	disk = sqrt(disk);
	if (-b - disk < -b - disk)
		*t = -b - disk;
	else
		*t = -b + disk;
	return (1);
}

t_vector3d	get_normal(t_sphere *sphere, t_vector3d vec)
{
	return (divide_vector(subtract_vec(vec, sphere->pos), sphere->diameter / 2));
}
