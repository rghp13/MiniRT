#include "../includes/minirt.h"

void	mlx_draw_pixel(t_img *img, t_pixel pixel)
{
	char	*dst;

	if (pixel.x > 0 && pixel.y > 0 && pixel.x < XSIZE && pixel.y < YSIZE)
	{
		dst = img->addr + ((int)pixel.y * img->line_length + \
		(int)pixel.x * (img->bits_per_pixel / 8));
		*(unsigned int *)dst = int_color(pixel.color);
	}
}
