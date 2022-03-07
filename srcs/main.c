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
void	print_parse(t_minirt *scene)
{
	t_light *li;
	t_sphere *sph;
	t_plane *pla;
	t_cylinder *cyl;
	t_cone *con;

	li = scene->light;
	sph = scene->sphere;
	pla = scene->plane;
	cyl = scene->cylinder;
	con = scene->cone;
	if (scene->ambient)
	{
		printf("AMBIENT LIGHT\n");
		printf("RATIO = %f\n", scene->ambient->ratio);
		printf("COLOR R = %d, G = %d, B = %d\n", scene->ambient->color.r, scene->ambient->color.g, scene->ambient->color.b);
	}
	if (scene->camera)
	{
		printf("CAMERA\n");
		printf("x = %f\ny = %f\nz = %f\n", scene->camera->pos.x, scene->camera->pos.y, scene->camera->pos.z);
		printf("x = %f\ny = %f\nz = %f\n", scene->camera->rot.x, scene->camera->rot.y, scene->camera->rot.z);
		printf("FOV = %f\n", scene->camera->fov);
	}
	while (li)
	{
		printf("LIGHT\n");
		printf("x = %f\ny = %f\nz = %f\n", li->pos.x, li->pos.y, li->pos.z);
		printf("LUM = %f\n", li->lum);
		printf("COLOR R = %d, G = %d, B = %d\n", li->color.r, li->color.g, li->color.b);
		li = li->next;
	}
	while (sph)
	{
		printf("SPHERE\n");
		printf("x = %f\ny = %f\nz = %f\n", sph->pos.x, sph->pos.y, sph->pos.z);
		printf("Diameter = %f\n", sph->diameter);
		printf("COLOR R = %d, G = %d, B = %d\n", sph->color.r, sph->color.g, sph->color.b);
		sph = sph->next;
	}
	while (pla)
	{
		printf("PLANE\n");
		printf("x = %f\ny = %f\nz = %f\n", pla->pos.x, pla->pos.y, pla->pos.z);
		printf("x = %f\ny = %f\nz = %f\n", pla->rot.x, pla->rot.y, pla->rot.z);
		printf("COLOR R = %d, G = %d, B = %d\n", pla->color.r, pla->color.g, pla->color.b);
		pla = pla->next;
	}
	while (cyl)
	{
		printf("CYLINDER\n");
		printf("x = %f\ny = %f\nz = %f\n", cyl->pos.x, cyl->pos.y, cyl->pos.z);
		printf("x = %f\ny = %f\nz = %f\n", cyl->rot.x, cyl->rot.y, cyl->rot.z);
		printf("Diameter %f\n", cyl->diameter);
		printf("Height %f\n", cyl->height);
		printf("COLOR R = %d, G = %d, B = %d\n", cyl->color.r, cyl->color.g, cyl->color.b);
		cyl = cyl->next;
	}
	while (con)
	{
		printf("CONE\n");
		printf("x = %f\ny = %f\nz = %f\n", con->pos.x, con->pos.y, con->pos.z);
		printf("x = %f\ny = %f\nz = %f\n", con->rot.x, con->rot.y, con->rot.z);
		printf("Angle %f\n", con->angle);
		printf("COLOR R = %d, G = %d, B = %d\n", con->color.r, con->color.g, con->color.b);
		con = con->next;
	}
	//exit_cleanly(scene, 0);
}

int	main(int argc, char **argv)
{
	t_minirt	scene;

	if (argc != 2)
		return (1);
	scene = init_scene_struct();
	//if (temp_parse(&scene))
	//	return (1);
	if (parse(argv, &scene) || !scene.ambient || !scene.camera || !scene.light)
		exit_cleanly(&scene, 1);
	print_parse(&scene);
	basic_tracer(&scene);//calculations and filling of image with pixel data
	printf("done\n");
	mlx_put_image_to_window(scene.mlxref.mlx, scene.mlxref.win, scene.mlxref.imgref.img, 0, 0);//display image
	mlx_key_hook(scene.mlxref.win, key_hook, &scene);//assign key to exit
	mlx_loop(scene.mlxref.mlx);//loop
	//free
	//exit
}
