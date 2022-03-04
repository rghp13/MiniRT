#include "../includes/minirt.h"

int	reset_rotation(t_rotation *rot)
{
	rot->x = 0;
	rot->y = 0;
	rot->z = 0;
	return (0);
}