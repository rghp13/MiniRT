/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponsonn <rponsonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 16:49:41 by rponsonn          #+#    #+#             */
/*   Updated: 2022/03/22 16:49:42 by rponsonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	cylinder_parse(char **spl, t_minirt *scene)
{
	int			i;
	t_cylinder	*cyl;

	i = 0;
	if (!spl[1] || !spl[2] || !spl[3] || !spl[4] || !spl[5] || spl[6])
		return (1);
	cyl = ft_calloc(1, sizeof(t_cylinder));
	if (!cyl)
		return (1);
	if (parse_vector(spl[1], &cyl->pos) || parse_vector(spl[2], &cyl->rot))
		i = 1;
	if (parse_positive_double(spl[3], &cyl->diameter))
		i = 1;
	if (parse_positive_double(spl[4], &cyl->height))
		i = 1;
	if (parse_color(spl[5], &cyl->color))
		i = 1;
	if (i || rot_range(&cyl->rot))
		return (void_free(cyl, 1));
	cyl->rot = normalize_vector(cyl->rot);
	if (scene->cylinder)
		cylinder_add_last(scene, cyl);
	else
		scene->cylinder = cyl;
	return (0);
}

void	cylinder_add_last(t_minirt *scene, t_cylinder *cyl)
{
	t_cylinder	*hold;

	hold = scene->cylinder;
	while (hold->next)
		hold = hold->next;
	hold->next = cyl;
}
