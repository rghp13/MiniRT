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
# define WHITE 0x00FFFFFF
# define ER1 "ERROR : MALLOC FAILURE "
# define ER2 "ERROR : INVALID FILETYPE "
# define ER3 "ERROR : FILE OPEN FAILURE "
# define ER4 "ERROR : PARSING ERROR DETECTED "
# define ER5 "ERROR : MISSING KEY COMPONENT "

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

typedef struct s_color {
	int	r;
	int	g;
	int b;
}			t_color;

typedef struct s_pixel {
	int		x;
	int		y;
	t_color	color;
}			t_pixel;

typedef struct s_vector3d {
	double	x;
	double	y;
	double	z;
}				t_vector3d;

typedef	struct s_ray {
	t_vector3d	origin;
	t_vector3d	direction;
}				t_ray;

typedef struct s_alight
{
	double		ratio;
	t_color		color;
}				t_alight;

typedef struct s_camera
{
	t_vector3d		pos;
	t_vector3d		rot;
	double			fov;
}					t_camera;

typedef struct s_light
{
	t_vector3d		pos;
	double			lum;
	t_color			color;
	struct s_light	*next;
}				t_light;

typedef struct s_sphere
{
	t_vector3d		pos;
	double			diameter;
	t_color			color;
	struct s_sphere	*next;
}					t_sphere;

typedef struct s_plane
{
	t_vector3d		pos;
	t_vector3d		rot;
	t_color			color;
	struct s_plane	*next;
}					t_plane;

typedef struct s_cylinder
{
	t_vector3d			pos;
	t_vector3d			rot;
	double				diameter;
	double				height;
	t_color				color;
	struct s_cylinder	*next;
}					t_cylinder;

typedef struct s_cone
{
	t_vector3d		pos;
	t_vector3d		rot;
	double			angle;
	struct s_cone	*next;
}					t_cone;

typedef struct s_minirt
{
	t_mlx_base	mlxref;
	t_alight	*ambient;
	t_camera	*camera;
	t_light		*light;
	t_sphere	*sphere;
	t_plane		*plane;
	t_cylinder	*cylinder;
	t_cone		*cone;
}				t_minirt;

/*
Draw Functions (functions that change parts of the image)
*/
void		mlx_draw_pixel(t_img *img, t_pixel pixel);

/*
Position Functions (functions that run on a position struct)
*/
int			reset_position(t_vector3d *pos);

/*
Rotation Functions (functions that run on a rotation struct)
*/
int			reset_rotation(t_vector3d *rot);

/*
Keyboard Functions (functions that relate to keys being pressed)
*/
int			key_hook(int key, t_minirt *scene);

/*
Free Functions (functions that are related to freeing malloced memory)
*/
void		exit_cleanly(t_minirt *scene, int status);

/*
Simple Vector Math (functions that allow for simple manipulations of vectors)
*/
t_vector3d	make_vector(double x, double y, double z);
t_vector3d	add_vec(t_vector3d v1, t_vector3d v2);
t_vector3d	subtract_vec(t_vector3d v1, t_vector3d v2);
t_vector3d	multiply_vector(t_vector3d v1, double d);
t_vector3d	divide_vector(t_vector3d v1, double d);

/*
Advanced Vector Math (functions that allow for simple manipulations of vectors)
*/
t_vector3d	normalize_vector(t_vector3d v1);
double		dot_vector(t_vector3d v1, t_vector3d v2);

/*
Color Math (functions that allow for the manipulation of colors)
*/
t_color 	clamp_color(t_color color);
t_color		make_color(int r, int g, int b);
int			int_color(t_color color);
t_vector3d	color_to_vector(t_color color);
t_color		vector_to_color(t_vector3d vector);

/*
Tracing Functions (functions that deal with the raytracing logic)
*/
int			basic_tracer(t_minirt *scene);

/*
Sphere Functions (functions that handle math related to spheres)
*/
int			sphere_intersect(t_sphere *sphere, t_ray ray, double *t);
t_vector3d	get_normal(t_sphere *sphere, t_vector3d vec);

#endif