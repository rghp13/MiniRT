/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advanced_vector_math.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimitriscr <dimitriscr@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 16:42:52 by rponsonn          #+#    #+#             */
/*   Updated: 2022/03/22 20:35:34 by dimitriscr       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_vector3d	normalize_vector(t_vector3d v1)
{
	double		mg;
	t_vector3d	res_vec;

	mg = sqrt((v1.x * v1.x) + (v1.y * v1.y) + (v1.z * v1.z));
	res_vec.x = v1.x / mg;
	res_vec.y = v1.y / mg;
	res_vec.z = v1.z / mg;
	return (res_vec);
}

t_vector3d	cross_vector(t_vector3d v1, t_vector3d v2)
{
	t_vector3d	ret_vec;

	ret_vec.x = (v1.y * v2.z) - (v1.z * v2.y);
	ret_vec.y = (v1.z * v2.x) - (v1.x * v2.z);
	ret_vec.z = (v1.x * v2.y) - (v1.y * v2.x);
	return (ret_vec);
}

double	dot_vector(t_vector3d v1, t_vector3d v2)
{
	return ((v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z));
}

double	vector_magnitude(t_vector3d vec)
{
	return (sqrt(pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2)));
}
