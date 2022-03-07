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