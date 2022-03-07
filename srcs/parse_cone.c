#include "minirt.h"

int	cone_parse(char **spl, t_minirt *scene)
{
	int		i;
	t_cone	*cone;

	i = 0;
	if (!spl[1] || !spl[2] || !spl[3] || !spl[4] || spl[5])
		return (1);
	cone = ft_calloc(1, sizeof(t_cone));
	if (!cone)
		return (1);
	if (parse_vector(spl[1], &cone->pos) || parse_vector(spl[2], &cone->rot))
		i = 1;
	if (parse_positive_double(spl[3], &cone->angle))
		i = 1;
	if (parse_color(spl[4], &cone->color))
		i = 1;
	if (i || rot_range(&cone->rot))
	{
		free(cone);
		return (1);
	}
	if (scene->cone)
		cone_add_last(scene, cone);
	else
		scene->cone = cone;
	return (0);
}

void	cone_add_last(t_minirt *scene, t_cone *cone)
{
	t_cone	*hold;

	hold = scene->cone;
	while (hold->next)
		hold = hold->next;
	hold->next = cone;
}
