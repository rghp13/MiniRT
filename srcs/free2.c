/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponsonn <rponsonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 16:44:38 by rponsonn          #+#    #+#             */
/*   Updated: 2022/03/22 18:30:49 by rponsonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	cone_free(t_cone *cone)
{
	t_cone	*hold;

	while (cone)
	{
		hold = cone->next;
		free(cone);
		cone = hold;
	}
}

int	mouse_hook(t_minirt *scene)
{
	exit_cleanly(scene, 0);
	return (0);
}

int	void_free(void *free_me, int ret)
{
	if (free_me)
		free(free_me);
	return (ret);
}
