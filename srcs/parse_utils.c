#include "minirt.h"

int	print_error(const char *str, int ret)
{
	ft_putendl_fd(str, STDERR_FILENO);
	return (ret);
}

int	check_valid_file(const char *filename)
{
	int	len;

	if (filename == NULL)
		return (1);
	len = ft_strlen(filename);
	if (filename[len - 1] == 't' && filename[len - 2] == 'r' && \
	filename[len -3] == '.')
		return (0);
	return (1);
}
//if not empty return 1
int	empty_line(const char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] == ' ' || str[i] == '\t'))
			return (1);
		i++;
	}
	return (0);
}
//verifies that only valid chars are in the text file
int	check_valid_content(const char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (approved_char(str[i]))
			continue ;
		if (str[i] == '-' || str[i] == ',' || str[i] == '.' || str[i] == ' ' || \
		str[i] == '\t' || str[i] == '\n')
			continue ;
		return (1);
	}
	return (0);
}

int	approved_char(const char str)
{
	if (str == 'A' || str == 'C' || str == 'L' || str == 's' || str == 'p' || \
	str == 'l' || str == 'c' || str == 'y')
		return (1);
	return (0);
}