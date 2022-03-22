/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponsonn <rponsonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 16:50:41 by rponsonn          #+#    #+#             */
/*   Updated: 2022/03/22 16:50:42 by rponsonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	light_parse(char **split, t_minirt *scene)
{
	int		i;
	t_light	*light;

	i = 0;
	if (!split[0] || !split[1] || !split[2] || !split[3] || split[4])
		return (1);
	light = ft_calloc(1, sizeof(t_light));
	if (!light)
		return (1);
	if (parse_vector(split[1], &light->pos))
		i = 1;
	if (parse_positive_double(split[2], &light->lum))
		i = 1;
	if (parse_color(split[3], &light->color))
		i = 1;
	if (i || light->lum > 1.0 || light->lum < 0.0)
		return (void_free(light, 1));
	if (scene->light == NULL)
		scene->light = light;
	else
		light_add_last(scene, light);
	return (0);
}

void	light_add_last(t_minirt *scene, t_light *light)
{
	t_light	*hold;

	hold = scene->light;
	while (hold->next)
		hold = hold->next;
	hold->next = light;
}
