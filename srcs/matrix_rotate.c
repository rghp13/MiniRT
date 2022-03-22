/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_rotate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponsonn <rponsonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 16:47:41 by rponsonn          #+#    #+#             */
/*   Updated: 2022/03/22 16:47:42 by rponsonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_vector3d	x_axis_rotation(t_vector3d vec, double theta)
{
	t_vector3d	result;

	result.y = (vec.y * cos(theta)) + (vec.z * (sin(theta) * -1));
	result.z = (vec.y * sin(theta)) + (vec.z * cos(theta));
	result.x = vec.x;
	return (result);
}

t_vector3d	y_axis_rotation(t_vector3d vec, double theta)
{
	t_vector3d	result;

	result.x = (vec.x * cos(theta)) + (vec.z * sin(theta));
	result.z = (vec.x * (sin(theta) * -1)) + (vec.z * cos(theta));
	result.y = vec.y;
	return (result);
}

t_vector3d	z_axis_rotation(t_vector3d vec, double theta)
{
	t_vector3d	result;

	result.x = (vec.x * cos(theta)) + (vec.y * (sin(theta) * -1));
	result.y = (vec.x * sin(theta)) + (vec.y * cos(theta));
	result.z = vec.z;
	return (result);
}

t_vector3d	transform_t_rotate(t_vector3d vec, t_vector3d rotation)
{
	vec = x_axis_rotation(vec, -rotation.x);
	vec = y_axis_rotation(vec, -rotation.y + (90 * M_PI / 180));
	vec = z_axis_rotation(vec, -rotation.z);
	return (vec);
}

t_vector3d	transform_inverse_rotate(t_vector3d vec, t_vector3d rotation)
{
	vec = z_axis_rotation(vec, rotation.z);
	vec = y_axis_rotation(vec, rotation.y - (90 * M_PI / 180));
	vec = x_axis_rotation(vec, rotation.x);
	return (vec);
}
