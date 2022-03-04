#include "../includes/minirt.h"

void	exit_cleanly(t_minirt *scene, int status)
{
	(void)scene;//this needs to free everythin malloced in the struct
	exit(status);
}