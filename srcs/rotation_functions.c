/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponsonn <rponsonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 16:56:38 by rponsonn          #+#    #+#             */
/*   Updated: 2022/03/22 16:56:39 by rponsonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	reset_rotation(t_vector3d *rot)
{
	rot->x = 0;
	rot->y = 0;
	rot->z = 0;
	return (0);
}
