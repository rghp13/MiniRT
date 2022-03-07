#include "../includes/minirt.h"

int	cylinder_intersect(t_cylinder *cylinder, t_ray ray, double *t)
{
	t_vector3d	u;
	t_vector3d	v;
	double		a;
	double		b;
	double		c;

	v = multiply_vector(cylinder->rot, dot_vector(ray.direction, cylinder->rot));
	v = subtract_vec(ray.direction, v);
	u = multiply_vector(cylinder->rot, dot_vector(subtract_vec(ray.origin, cylinder->pos), cylinder->rot));
	u = subtract_vec(subtract_vec(ray.origin, cylinder->pos), u);
	a = dot_vector(v, v);
	b = 2 * dot_vector(v, u);
	c = dot_vector(u, u) - (cylinder->diameter / 2 * cylinder->diameter / 2);
	*t = (-b - sqrt(pow(b, 2) - 4 * a * c)) / (2 * a);
	if (t < 0)
		return (0);
	return(1);
}

t_vector3d	cylinder_normal(t_cylinder *cylinder, t_vector3d vec)
{
	return (divide_vector(subtract_vec(vec, cylinder->pos), cylinder->diameter / 2));
}
