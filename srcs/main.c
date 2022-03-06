#include "../includes/minirt.h"

int	init_mlx_win_img(t_mlx_base *mlxref)
{
	mlxref->mlx = mlx_init();
	mlxref->win = mlx_new_window(mlxref->mlx, XSIZE, YSIZE, "miniRT");
	mlxref->imgref.img = mlx_new_image(mlxref->mlx, XSIZE, YSIZE);
	mlxref->imgref.addr = mlx_get_data_addr(mlxref->imgref.img, \
	&mlxref->imgref.bits_per_pixel, &mlxref->imgref.line_length, \
	&mlxref->imgref.endian);
	return (0);
}

t_minirt	init_scene_struct(void)
{
	t_minirt	scene;

	init_mlx_win_img (&scene.mlxref);
	scene.ambient = NULL;
	scene.camera = NULL;
	scene.light = NULL;
	scene.sphere = NULL;
	scene.plane = NULL;
	scene.cylinder = NULL;
	scene.cone = NULL;
	return (scene);
}

int	temp_parse(t_minirt *scene)
{
	scene->ambient = ft_calloc(1, sizeof(t_alight));
	scene->camera = ft_calloc(1, sizeof(t_camera));
	scene->light = ft_calloc(1, sizeof(t_light));
	scene->sphere = ft_calloc(1, sizeof(t_sphere));
	scene->plane = ft_calloc(1, sizeof(t_plane));
	scene->cylinder = ft_calloc(1, sizeof(t_cylinder));
	if (scene->ambient == NULL || scene->camera == NULL || scene->light == NULL || scene->sphere == NULL || scene->plane == NULL || scene->cylinder == NULL)
		return (1);
	scene->ambient->color = make_color(255, 255, 255);
	scene->ambient->ratio = 0.5;
	scene->camera->fov = 70.0;
	scene->camera->pos = make_vector(0, 0, 0);
	scene->camera->rot = make_vector(0, 0, 0);
	scene->light->color = make_color(255, 255, 255);
	scene->light->lum = 1;
	scene->light->pos = make_vector(0, 0, 0);
	scene->sphere->pos = make_vector(0, 0, 300);
	scene->sphere->color = make_color(0, 255, 0);
	scene->sphere->diameter = 150;
	scene->plane->color = make_color(0, 255, 0);
	scene->plane->pos.y = 10.0;
	scene->cylinder->color = make_color(0, 0, 255);
	scene->cylinder->diameter = 3.0;
	scene->cylinder->height = 4.0;
	scene->cylinder->pos.z = 10.0;
	return (0);
}

int	main(int argc, char **argv)
{
	t_minirt	scene;

	if (argc != 2)
		return (1);
	scene = init_scene_struct(); //initialization
	if (temp_parse(&scene))
		return (1);
	//parsing and filling of struct
	basic_tracer(&scene);//calculations and filling of image with pixel data
	printf("done\n");
	mlx_put_image_to_window(scene.mlxref.mlx, scene.mlxref.win, scene.mlxref.imgref.img, 0, 0);//display image
	mlx_key_hook(scene.mlxref.win, key_hook, &scene);//assign key to exit
	mlx_loop(scene.mlxref.mlx);//loop
	//free
	//exit
}
