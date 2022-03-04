#include "../includes/minirt.h"

int	reset_position(t_position *pos)
{
	pos->x = 0;
	pos->y = 0;
	pos->z = 0;
	return (0);
}