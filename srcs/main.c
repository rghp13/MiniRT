/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponsonn <rponsonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 16:38:54 by rponsonn          #+#    #+#             */
/*   Updated: 2022/03/22 17:41:22 by rponsonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	init_mlx_win_img(t_mlx_base *mlxref)
{
	mlxref->mlx = mlx_init();
	if (mlxref->mlx == NULL)
		return (1);
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

	if (init_mlx_win_img (&scene.mlxref))
		exit(print_error(ER11, 1));
	scene.ambient = NULL;
	scene.camera = NULL;
	scene.light = NULL;
	scene.sphere = NULL;
	scene.plane = NULL;
	scene.cylinder = NULL;
	scene.cone = NULL;
	return (scene);
}

int	main(int argc, char **argv)
{
	t_minirt	scene;

	if (argc != 2)
		return (1);
	scene = init_scene_struct();
	mlx_key_hook(scene.mlxref.win, key_hook, &scene);
	mlx_hook(scene.mlxref.win, 17, 1L << 2, mouse_hook, &scene);
	if (parse(argv, &scene) || !scene.ambient || !scene.camera || !scene.light)
		exit_cleanly(&scene, 1);
	basic_tracer(&scene);
	mlx_put_image_to_window(scene.mlxref.mlx, scene.mlxref.win, \
	scene.mlxref.imgref.img, 0, 0);
	mlx_loop(scene.mlxref.mlx);
}
