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
