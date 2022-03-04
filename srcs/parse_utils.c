#include "minirt.h"

int print_error(char *str, int ret)
{
	ft_putendl_fd(str, STDERR_FILENO);
	return (ret);
}
