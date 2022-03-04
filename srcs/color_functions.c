#include "../includes/minirt.h"

t_color clamp_color(t_color color)
{
	if (color.r > 255)
		color.r = 255;
	else if (color.r < 0)
		color.r = 0;
	if (color.g > 255)
		color.g = 255;
	else if (color.g < 0)
		color.g = 0;
	if (color.b > 255)
		color.b = 255;
	else if (color.b < 0)
		color.b = 0;
	return (color);
}

int	int_color(t_color color)
{
	return (color.r << 16 | color.g << 8 | color.b);
}

t_color	make_color(int r, int g, int b)
{
	t_color	ret_col;

	ret_col.r = r;
	ret_col.g = g;
	ret_col.b = b;
	ret_col = clamp_color(ret_col);
	return (ret_col);
}