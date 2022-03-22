/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rponsonn <rponsonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 16:52:18 by rponsonn          #+#    #+#             */
/*   Updated: 2022/03/22 16:54:35 by rponsonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	split_count(char **split)
{
	int	i;

	i = 0;
	if (split == NULL)
		return (-1);
	while (split[i])
		i++;
	return (i);
}

int	valid_color_check(char **split)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (split[i])
		i++;
	if (i != 3)
		return (1);
	i = 0;
	while (split[i])
	{
		while (split[i][c])
		{
			if (!ft_isdigit(split[i][c]))
				return (1);
			c++;
		}
		c = 0;
		i++;
	}
	return (0);
}

int	remove_nl(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			str[i] = '\0';
		i++;
	}
	return (0);
}

int	parse_positive_double(char *str, double *num)
{
	int	i;
	int	check;

	i = -1;
	check = 0;
	if (str == NULL || num == NULL)
		return (1);
	while (str[++i])
	{
		if (str[i] == '.')
			check++;
		if (!(ft_isdigit(str[i]) || str[i] == '.'))
			return (1);
	}
	if (check > 1)
		return (1);
	*num = ft_atof(str);
	if (*num < 0.0)
		return (1);
	return (0);
}

int	parse_color(char *str, t_color *color)
{
	int		i;
	char	**split;

	i = 0;
	split = ft_split(str, ',');
	if (split == NULL || valid_color_check(split))
	{
		ft_free_all_split(split);
		return (1);
	}
	color->r = ft_atof(split[0]);
	color->g = ft_atof(split[1]);
	color->b = ft_atof(split[2]);
	ft_free_all_split(split);
	if (color->r > 255 || color->r < 0 || color->g > 255 || color->g < 0 || \
	color->b > 255 || color->b < 0)
		return (1);
	return (0);
}
