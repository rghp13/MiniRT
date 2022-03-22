/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponsonn <rponsonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 16:51:55 by rponsonn          #+#    #+#             */
/*   Updated: 2022/03/22 16:55:38 by rponsonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	sphere_parse(char **split, t_minirt *scene)
{
	int			i;
	t_sphere	*sphere;

	i = 0;
	if (!split[0] || !split[1] || !split[2] || !split[3] || split[4])
		return (1);
	sphere = ft_calloc(1, sizeof(t_sphere));
	if (!sphere)
		return (1);
	if (parse_vector(split[1], &sphere->pos))
		i = 1;
	if (parse_positive_double(split[2], &sphere->diameter))
		i = 1;
	if (parse_color(split[3], &sphere->color))
		i = 1;
	if (i)
		return (void_free(sphere, 1));
	if (scene->sphere)
		sphere_add_last(scene, sphere);
	else
		scene->sphere = sphere;
	return (0);
}

void	sphere_add_last(t_minirt *scene, t_sphere *sphere)
{
	t_sphere	*hold;

	hold = scene->sphere;
	while (hold->next)
		hold = hold->next;
	hold->next = sphere;
}
