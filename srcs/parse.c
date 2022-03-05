#include "minirt.h"

int	parse(char **argv, t_minirt *scene)
{
	int		fd;
	char	*hold;

	if (prepare_file(argv, &fd, scene))
		return (1);
	while (1)
	{
		hold = get_next_line(fd);
		if (!hold)
			break ;
		scan_text(hold, scene);
		free(hold);
	}
	return (0);
}

int	scan_text(const char *str, t_minirt *scene)
{
	char	**split;

	if (check_valid_content(str))
		return (print_error(ER6, 1));
	if (empty_line(str) == 0)
		return;
	split = ft_split(str, ' ');
	if (split == NULL || split[0] == NULL || split[0][0] == '\n')
		return (ft_free_all_split(split));
	if (ft_stringcomp(split[0], "A") == 0)
		ambient_parse(split, scene);
	else if (ft_stringcomp(split[0], "C") == 0)
		camera_parse(split, scene);
	else if (ft_stringcomp(split[0], "L") == 0)
		light_parse(split, scene);
	else if (ft_stringcomp(split[0], "sp") == 0)
		sphere_parse(split, scene);
	else if (ft_stringcomp(split[0], "pl") == 0)
		plane_parse(split, scene);
	else if (ft_stringcomp(split[0], "cy") == 0)
		cylinder_parse(split, scene);
	else if (ft_strincomp(split[0], "co") == 0)
		cone_parse(split, scene);
	else
		scene->parsing_error = print_error(ER4, 1);
	ft_free_all_split(split);
	return (0);
}

/*
**Checks that text is a valid .rt file, opens correctly and can be read;
*/
int	prepare_file(char **argv, int *fd, t_minirt *scene)
{
	char *str;
	int i;

	if (check_valid_file(argv[1]))
		return (print_error(ER2, 1));
	*fd = open(argv[1], O_RDONLY);
	if (*fd < 0)
		return (print_error(ER3, 1));
	if (read(*fd, NULL, 0))
	{
		close(*fd);
		perror("minirt");
		return (1);
	}
	return (0);
}
