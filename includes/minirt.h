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

# define XSIZE 1280
# define YSIZE 720
# define KEY_ESCAPE 65307

typedef struct s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef struct s_mlx_base {
	void	*mlx;
	void	*win;
	t_img	imgref;
}				t_mlx_base;

typedef struct s_pixel {
	int		x;
	int		y;
	int		color;
}			t_pixel;

typedef struct s_position
{
	double	x;
	double	y;
	double	z;
}				t_position;

typedef struct s_rotation
{
	double	x;
	double	y;
	double	z;
}				t_rotation;

typedef struct s_alight
{
	double		ratio;
	u_int32_t	color;
}				t_alight;

typedef struct s_camera
{
	t_position		pos;
	t_rotation		rot;
	double			fov;
}					t_camera;

typedef struct s_light
{
	t_position		pos;
	double			lum;
	u_int32_t		color;
	struct s_light	*next;
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
	t_rotation		rot;
	u_int32_t		color;
	struct s_plane	*next;
}					t_plane;

typedef struct s_cylinder
{
	t_position			pos;
	t_rotation			rot;
	double				diameter;
	double				height;
	u_int32_t			color;
	struct s_cylinder	*next;
}					t_cylinder;

typedef struct s_cone
{
	t_position		pos;
	t_rotation		rot;
	double			angle;
	struct s_cone	*next;
}					t_cone;

typedef struct s_minirt
{
	t_mlx_base	mlxref;
	t_alight	ambient;
	t_camera	camera;
	t_light		*light;
	t_sphere	*sphere;
	t_plane		*plane;
	t_cylinder	*cylinder;
	t_cone		*cone;
}				t_minirt;

/*
Draw Functions (functions that change parts of the image)
*/
void	my_mlx_pixel_put(t_img *data, int x, int y, int color);
void	mlx_draw_pixel(t_img *img, t_pixel pixel);

/*
Position Functions (functions that run on a position struct)
*/
int		reset_position(t_position *pos);

/*
Rotation Functions (functions that run on a rotation struct)
*/
int		reset_rotation(t_rotation *rot);

/*
Keyboard Functions (functions that relate to keys being pressed)
*/
int		key_hook(int key, t_minirt *scene);

/*
Free Functions (functions that are related to freeing malloced memory)
*/
void	exit_cleanly(t_minirt *scene, int status);

#endif