#include "../includes/minirt.h"

int	basic_tracer(t_minirt *scene)
{
	t_pixel		pixel;
	t_ray		ray;
	double		t;
	t_vector3d	N;
	t_vector3d	P;
	t_vector3d	L;
	double		dt;

	pixel.x = 0;
	pixel.y = 0;
	pixel.color = make_color(255, 255, 255);
	while (pixel.y < YSIZE)
	{
		pixel.x = 0;
		while (pixel.x < XSIZE)
		{
			ray.origin = make_vector(pixel.x, pixel.y, 0);
			ray.direction = make_vector(0, 0, 1);
			pixel.color = make_color(0, 0, 0);
			if (sphere_intersect(scene->sphere, ray, &t))
			{
				P = add_vec(ray.origin, multiply_vector(ray.direction, t));
				L = subtract_vec(scene->light->pos, P);
				N = get_normal(scene->sphere, P);
				dt = dot_vector(normalize_vector(L), normalize_vector(N));
				pixel.color = vector_to_color(multiply_vector(add_vec(color_to_vector(scene->sphere->color), multiply_vector(color_to_vector(scene->light->color), dt)), scene->light->lum));
			}
			mlx_draw_pixel(&scene->mlxref.imgref, pixel);
			pixel.x++;
		}
		pixel.y++;
	}
	return (0);
}