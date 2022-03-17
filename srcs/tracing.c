#include "../includes/minirt.h"

t_ray	generate_ray(t_minirt *scene, t_pixel pixel)
{
	t_ray		ray;
	t_vector3d	pixeloffset;
	double		focal_length;

	ray.origin = scene->camera->pos;
	focal_length = (XSIZE / 2) / tan((scene->camera->fov / 2) * (M_PI / 180));
	pixeloffset = make_vector(pixel.x - (XSIZE / 2), pixel.y - (YSIZE / 2), focal_length);
	ray.direction = normalize_vector(add_vec(multiply_vector(scene->camera->rot, focal_length), pixeloffset));
	return (ray);
}

int	basic_tracer(t_minirt *scene)
{
	t_pixel			pixel;
	t_ray			ray;
	t_hit_result	hit;

	pixel.x = 0;
	pixel.y = 0;
	hit.t = 0;
	while (pixel.y < YSIZE)
	{
		pixel.x = 0;
		while (pixel.x < XSIZE)
		{
			ray = generate_ray(scene, pixel);
			pixel.color = make_color(80, 80, 80);
			if (find_closest_intersection(scene, ray, &hit))
			{
				pixel.color = calculate_illumination(scene, &hit);
				//pixel.color = hit.color_at_hit;
			}
			mlx_draw_pixel(&scene->mlxref.imgref, pixel);
			pixel.x++;
		}
		pixel.y++;
	}
	return (0);
}
