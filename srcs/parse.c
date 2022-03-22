/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponsonn <rponsonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 16:56:15 by rponsonn          #+#    #+#             */
/*   Updated: 2022/03/22 16:56:16 by rponsonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse(char **argv, t_minirt *scene)
{
	int		fd;
	char	*hold;
	int		i;

	i = 0;
	if (prepare_file(argv, &fd, scene))
		return (1);
	while (1)
	{
		hold = get_next_line(fd);
		if (!hold)
			break ;
		remove_nl(hold);
		if (scan_text(hold, scene, 0))
		{
			free(hold);
			close(fd);
			return (1);
		}
		free(hold);
		i++;
	}
	return (close(fd));
}

int	scan_text(const char *str, t_minirt *scene, int ret)
{
	char	**split;

	if (empty_line(str) == 0)
		return (0);
	split = ft_split(str, ' ');
	if (split == NULL || split[0] == NULL || split[0][0] == '\n')
		return (ft_free_all_split(split));
	if (ft_stringcomp(split[0], "A") == 0)
		ret |= ambient_parse(split, scene);
	else if (ft_stringcomp(split[0], "C") == 0)
		ret |= camera_parse(split, scene);
	else if (ft_stringcomp(split[0], "L") == 0)
		ret |= light_parse(split, scene);
	else if (ft_stringcomp(split[0], "sp") == 0)
		ret |= sphere_parse(split, scene);
	else if (ft_stringcomp(split[0], "pl") == 0)
		ret |= plane_parse(split, scene);
	else if (ft_stringcomp(split[0], "cy") == 0)
		ret |= cylinder_parse(split, scene);
	else
		ret |= print_error(ER4, 1);
	ft_free_all_split(split);
	return (ret);
}

/*
**Checks that text is a valid .rt file, opens correctly and can be read;
*/
int	prepare_file(char **argv, int *fd, t_minirt *scene)
{
	(void)scene;
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
