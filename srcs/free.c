/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponsonn <rponsonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 16:44:29 by rponsonn          #+#    #+#             */
/*   Updated: 2022/03/22 18:30:43 by rponsonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	exit_cleanly(t_minirt *scene, int status)
{
	if (scene->ambient)
		free(scene->ambient);
	if (scene->camera)
		free(scene->camera);
	light_free(scene->light);
	sphere_free(scene->sphere);
	plane_free(scene->plane);
	cylinder_free(scene->cylinder);
	if (scene->mlxref.mlx)
	{
		mlx_destroy_window(scene->mlxref.mlx, scene->mlxref.win);
		mlx_destroy_image(scene->mlxref.mlx, scene->mlxref.imgref.img);
		mlx_destroy_display(scene->mlxref.mlx);
		free(scene->mlxref.mlx);
	}
	exit(status);
}

void	light_free(t_light *light)
{
	t_light	*hold;

	while (light)
	{
		hold = light->next;
		free(light);
		light = hold;
	}
}

void	sphere_free(t_sphere *sphere)
{
	t_sphere	*hold;

	while (sphere)
	{
		hold = sphere->next;
		free(sphere);
		sphere = hold;
	}
}

void	plane_free(t_plane *plane)
{
	t_plane	*hold;

	while (plane)
	{
		hold = plane->next;
		free(plane);
		plane = hold;
	}
}

void	cylinder_free(t_cylinder *cylinder)
{
	t_cylinder	*hold;

	while (cylinder)
	{
		hold = cylinder->next;
		free(cylinder);
		cylinder = hold;
	}
}
