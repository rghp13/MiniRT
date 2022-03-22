/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_vector_math.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponsonn <rponsonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 16:56:45 by rponsonn          #+#    #+#             */
/*   Updated: 2022/03/22 16:57:11 by rponsonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_vector3d	make_vector(double x, double y, double z)
{
	t_vector3d	ret_vec;

	ret_vec.x = x;
	ret_vec.y = y;
	ret_vec.z = z;
	return (ret_vec);
}

t_vector3d	add_vec(t_vector3d v1, t_vector3d v2)
{
	t_vector3d	res_vec;

	res_vec.x = v1.x + v2.x;
	res_vec.y = v1.y + v2.y;
	res_vec.z = v1.z + v2.z;
	return (res_vec);
}

t_vector3d	subtract_vec(t_vector3d v1, t_vector3d v2)
{
	t_vector3d	res_vec;

	res_vec.x = v1.x - v2.x;
	res_vec.y = v1.y - v2.y;
	res_vec.z = v1.z - v2.z;
	return (res_vec);
}

t_vector3d	multiply_vector(t_vector3d v1, double d)
{
	t_vector3d	res_vec;

	res_vec.x = v1.x * d;
	res_vec.y = v1.y * d;
	res_vec.z = v1.z * d;
	return (res_vec);
}

t_vector3d	divide_vector(t_vector3d v1, double d)
{
	t_vector3d	res_vec;

	res_vec.x = v1.x / d;
	res_vec.y = v1.y / d;
	res_vec.z = v1.z / d;
	return (res_vec);
}
