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
	pixel.color = make_color(0, 0, 0);
	while (pixel.y < YSIZE)
	{
		pixel.x = 0;
		while (pixel.x < XSIZE)
		{
			ray = generate_ray(scene, pixel);
			pixel.color = make_color(pixel.x / 3, pixel.y / 2, 255);
			if (sphere_intersect(scene->sphere, ray, &hit))
			{
				hit.inter_point = add_vec(ray.origin, multiply_vector(ray.direction, hit.t));
				hit.obj_to_cam = subtract_vec(scene->light->pos, hit.inter_point);
				hit.normal = sphere_normal(scene->sphere, hit.inter_point);
				hit.normal_cam_dot = dot_vector(normalize_vector(hit.obj_to_cam), normalize_vector(hit.normal));
				pixel.color = vector_to_color(multiply_vector(add_vec(color_to_vector(scene->sphere->color), multiply_vector(color_to_vector(scene->light->color), hit.normal_cam_dot)), scene->light->lum));
			}
			mlx_draw_pixel(&scene->mlxref.imgref, pixel);
			pixel.x++;
		}
		pixel.y++;
	}
	return (0);
}

int	test(t_minirt *scene)
{
	t_pixel		pixel;
	t_ray		ray;

	pixel.x = 0;
	pixel.y = 0;
	while (pixel.y < YSIZE)
	{
		pixel.x = 0;
		while (pixel.x < XSIZE)
		{
			ray = generate_ray(scene, pixel);
			printf("%d %d: (%f, %f, %f) going towards (%f, %f, %f)\n", pixel.x, pixel.y, ray.origin.x, ray.origin.y, ray.origin.z, ray.direction.x, ray.direction.y, ray.direction.z);
			pixel.x++;
		}
		printf("\n\n\n");
		pixel.y++;
	}
	return(0);
}