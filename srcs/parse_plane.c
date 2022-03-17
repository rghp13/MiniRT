#include "minirt.h"

int	plane_parse(char **split, t_minirt *scene)
{
	int		i;
	t_plane	*plane;

	i = 0;
	if (!split[0] || !split[1] || !split[2] || !split[3] || split[4])
		return (1);
	plane = ft_calloc(1, sizeof(t_plane));
	if (!plane)
		return (1);
	if (parse_vector(split[1], &plane->pos))
		i = 1;
	if (parse_vector(split[2], &plane->rot))
		i = 1;
	if (parse_color(split[3], &plane->color))
		i = 1;
	if (i || rot_range(&plane->rot))
		return (void_free(plane, 1));
	plane->rot = normalize_vector(plane->rot);
	if (scene->plane)
		plane_add_last(scene, plane);
	else
		scene->plane = plane;
	return (0);
}

void	plane_add_last(t_minirt *scene, t_plane *plane)
{
	t_plane	*hold;

	hold = scene->plane;
	while (hold->next)
		hold = hold->next;
	hold->next = plane;
}
