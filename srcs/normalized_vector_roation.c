/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalized_vector_roation.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponsonn <rponsonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 16:48:14 by rponsonn          #+#    #+#             */
/*   Updated: 2022/03/22 16:48:14 by rponsonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

double	get_x_axis_rot(t_vector3d rotation)
{
	double	rot;
	double	hypotenuse;

	hypotenuse = sqrt(pow(rotation.x, 2) + \
	pow(rotation.y, 2) + pow(rotation.z, 2));
	rot = acos(rotation.x / hypotenuse);
	return (rot);
}

double	get_y_axis_rot(t_vector3d rotation)
{
	double	rot;
	double	hypotenuse;

	hypotenuse = sqrt(pow(rotation.x, 2) + \
	pow(rotation.y, 2) + pow(rotation.z, 2));
	rot = acos(rotation.y / hypotenuse);
	return (rot);
}

double	get_z_axis_rot(t_vector3d rotation)
{
	double	rot;
	double	hypotenuse;

	hypotenuse = sqrt(pow(rotation.x, 2) + \
	pow(rotation.y, 2) + pow(rotation.z, 2));
	rot = acos(rotation.z / hypotenuse);
	return (rot);
}

t_vector3d	get_all_axis_rotation(t_vector3d rotation)
{
	t_vector3d	rot;

	rot.x = get_x_axis_rot(rotation);
	rot.y = get_y_axis_rot(rotation);
	rot.z = get_z_axis_rot(rotation);
	return (rot);
}
