#include "minirt.h"

void	cone_free(t_cone *cone)
{
	t_cone	*hold;

	while (cone)
	{
		hold = cone->next;
		free(cone);
		cone = hold;
	}
}

int	mouse_hook(t_minirt *scene)
{
	mlx_destroy_window(scene->mlxref.mlx, scene->mlxref.win);
	free(scene->mlxref.mlx);
	exit_cleanly(scene, 0);
	return (0);
}

int	void_free(void *free_me, int ret)
{
	if (free_me)
		free(free_me);
	return (ret);
}