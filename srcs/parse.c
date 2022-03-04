#include "../includes/minirt.h"

int	parse(int argc, char **argv, t_minirt *scene)
{
	int	fd;

	if (check_valid_file(argv[1]))
		return (print_error(ER2, 1));
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (print_error(ER3, 1));
}
