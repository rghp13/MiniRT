/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadratic_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimitriscr <dimitriscr@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 16:56:32 by rponsonn          #+#    #+#             */
/*   Updated: 2022/03/23 17:08:30 by dimitriscr       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	solve_quadratic(t_quadratic *qua)
{
	qua->delta = (qua->b * qua->b) - (4.0 * qua->a * qua->c);
	if (qua->delta < 0)
		return (0);
	else if (qua->delta == 0)
	{
		qua->t1 = -qua->b / (2 * qua->a);
		qua->t2 = -qua->b / (2 * qua->a);
		return (1);
	}
	else
	{
		qua->t1 = (-qua->b + sqrt(qua->delta)) / (2 * qua->a);
		qua->t2 = (-qua->b - sqrt(qua->delta)) / (2 * qua->a);
		return (2);
	}
}
