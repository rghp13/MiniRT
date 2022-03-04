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

t_minirt	init_scene_struct()
{
	t_minirt scene;

	init_mlx_win_img (&scene.mlxref);
	scene.ambient.color = 0;
	scene.ambient.ratio = 0;
	scene.camera.fov = 0;
	reset_position(&scene.camera.pos);
	reset_rotation(&scene.camera.rot);
	scene.light = NULL;
	scene.sphere = NULL;
	scene.plane = NULL;
	scene.cylinder = NULL;
	scene.cone = NULL;
	return (scene);
}

int	main(void)
{
	t_minirt	scene;

	scene = init_scene_struct(); //initialization
	//parsing and filling of struct
	//calculations and filling of image with pixel data
	my_mlx_pixel_put(&scene.mlxref.imgref, 400, 300, 0x00FF0000); //this will dissapear
	mlx_put_image_to_window(scene.mlxref.mlx, scene.mlxref.win, scene.mlxref.imgref.img, 0, 0);//display image
	mlx_key_hook(scene.mlxref.win, key_hook, &scene);//assign key to exit
	mlx_loop(scene.mlxref.mlx);//loop
	//free
	//exit
}
