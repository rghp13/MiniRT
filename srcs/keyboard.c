/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponsonn <rponsonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 16:45:33 by rponsonn          #+#    #+#             */
/*   Updated: 2022/03/22 18:31:00 by rponsonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	key_hook(int key, t_minirt *scene)
{
	if (key == KEY_ESCAPE)
		exit_cleanly(scene, 0);
	return (0);
}
