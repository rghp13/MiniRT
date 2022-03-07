#include "minirt.h"

int parse_vector(const char *str, t_vector3d *vector)
{
	char	**hold;
	int		i;

	i = 0;
	hold = ft_split(str, ',');
	if (hold == NULL || valid_vector_check(hold))
	{
		ft_free_all_split(hold);
		return (1);
	}
	vector->x = ft_atof(hold[0]);
	vector->y = ft_atof(hold[1]);
	vector->z = ft_atof(hold[2]);
	ft_free_all_split(hold);
	return (0);
}

int	valid_vector_check(char **split)
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
			if (!(ft_isdigit(split[i][c]) || split[i][0] == '-'))
				return (1);
			c++;
		}
		c = 0;
		i++;
	}
	return (0);
}

int	rot_range(t_vector3d *rotation)
{
	if (rotation->x > 1.0 || rotation->x < -1.0)
		return (1);
	else if (rotation->y > 1.0 || rotation->y < -1.0)
		return (1);
	else if (rotation->z > 1.0 || rotation->z < -1.0)
		return (1);
	else
		return (0);
}

int	fov_range(double num)
{
	if (num > 1.0 || num < 0.0)
		return (1);
	return (0);
}
