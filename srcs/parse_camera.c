/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponsonn <rponsonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 16:49:26 by rponsonn          #+#    #+#             */
/*   Updated: 2022/03/22 16:49:27 by rponsonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	camera_parse(char **split, t_minirt *scene)
{
	int			i;
	t_camera	*camera;

	i = 0;
	if (scene->camera)
		return (print_error(ER8, 1));
	if (!split[0] || !split[1] || !split[2] || !split[3] || split[4])
		return (1);
	camera = ft_calloc(1, sizeof(t_camera));
	if (camera == NULL)
		return (1);
	if (parse_vector(split[1], &camera->pos))
		i = 1;
	if (parse_vector(split[2], &camera->rot))
		i = 1;
	if (parse_positive_double(split[3], &camera->fov))
		i = 1;
	if (i || rot_range(&camera->rot) || fov_range(camera->fov))
	{
		free(camera);
		return (print_error(ER9, 1));
	}
	camera->rot = normalize_vector(camera->rot);
	scene->camera = camera;
	return (0);
}
