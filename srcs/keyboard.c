#include "../includes/minirt.h"

int	key_hook(int key, t_minirt *scene)
{
	if (key == KEY_ESCAPE)
		exit_cleanly(scene, 0);
	return (0);
}
