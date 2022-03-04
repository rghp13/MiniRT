#ifndef MINIRT_H
# define MINIRT_H
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include "libft.h"
# include "../minilibx-linux/mlx.h"

typedef struct s_position
{
	double	x;
	double	y;
	double	z;
}				t_position;
typedef struct s_orientation
{
	double	x;
	double	y;
	double	z;
}				t_orientation;
typedef struct s_alight
{
	double		ratio;
	u_int32_t	color;
}				t_alight;
typedef struct s_camera
{
	t_position		pos;
	t_orientation	ori;
	double			fov;
}					t_camera;
typedef struct s_light
{
	t_position	pos;
	double		lum;
	u_int32_t	color;
}				t_light;
typedef struct s_sphere
{
	t_position		pos;
	double			diameter;
	u_int32_t		color;
	struct s_sphere	*next;
}					t_sphere;
typedef struct s_plane
{
	t_position		pos;
	t_orientation	ori;
	u_int32_t		color;
	struct s_plane	*next;
}					t_plane;
typedef struct s_cylinder
{
	t_position		pos;
	t_orientation	ori;
	double			diameter;
	double			height;
	u_int32_t		color;
}					t_cylinder;
typedef struct s_cone
{
	t_position		pos;
	t_orientation	ori;
	double			angle;
	struct s_cone	*next;
}					t_cone;
typedef struct s_minirt
{
	t_alight	*ambient;
	t_camera	*camera;
	t_light		*light;
	t_sphere	*sphere;
	t_plane		*plane;
	t_cylinder	*cylinder;
	t_cone		*cone;
}				t_minirt;

#endif