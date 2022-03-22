/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponsonn <rponsonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 16:48:35 by rponsonn          #+#    #+#             */
/*   Updated: 2022/03/22 16:49:22 by rponsonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ambient_parse(char **split, t_minirt *scene)
{
	int			i;
	t_alight	*light;

	i = 0;
	if (scene->ambient)
		return (print_error(ER7, 1));
	if (!split[0] || !split[1] || !split[2] || split[3])
		return (1);
	light = ft_calloc(1, sizeof(t_alight));
	if (light == NULL)
		return (1);
	if (parse_positive_double(split[1], &light->ratio))
		i = 1;
	if (parse_color(split[2], &light->color))
		i = 1;
	if (i || (light->ratio > 1.0 || light->ratio < 0.0))
	{
		free(light);
		return (1);
	}
	scene->ambient = light;
	return (0);
}
