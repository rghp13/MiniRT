/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimitriscr <dimitriscr@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 16:34:22 by rponsonn          #+#    #+#             */
/*   Updated: 2022/03/22 20:36:01 by dimitriscr       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

/*
For the math to works, XSIZE has to be bigger than YSIZE
*/

# define XSIZE 1280
# define YSIZE 720
# define KEY_ESCAPE 65307
# define WHITE 0x00FFFFFF
# define ER1 "ERROR : MALLOC FAILURE "
# define ER2 "ERROR : INVALID FILETYPE "
# define ER3 "ERROR : FILE OPEN FAILURE "
# define ER4 "ERROR : PARSING ERROR DETECTED "
# define ER5 "ERROR : MISSING KEY COMPONENT "
# define ER6 "ERROR : ILLEGAL CHARS DETECTED "
# define ER7 "ERROR : AMBIENT LIGHTING ALREADY INIT "
# define ER8 "ERROR : CAMERA ALREADY INIT "
# define ER9 "ERROR : CAMERA PARSING "
# define ER10 "ERROR : ROTATION == 0.0 "

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
	int	b;
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

typedef struct s_quadratic {
	t_vector3d	oc;
	double		a;
	double		b;
	double		c;
	double		delta;
	double		t1;
	double		t2;
}				t_quadratic;

typedef struct s_ray {
	t_vector3d	origin;
	t_vector3d	direction;
}				t_ray;

typedef struct s_hit_result {
	double		t;
	t_vector3d	inter_point;
	t_vector3d	normal;
	t_vector3d	obj_to_cam;
	double		normal_cam_dot;
	t_color		color_at_hit;
}				t_hit_result;

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
//keyword co
typedef struct s_cone
{
	t_vector3d		pos;
	t_vector3d		rot;
	double			angle;
	t_color			color;
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
	int			parsing_error;
}				t_minirt;

/*
Matrix Functions (functions that apply matrix transformations to vectors)
*/
t_vector3d		transform_t_translate(t_vector3d vec, t_vector3d t_vec);
t_vector3d		transform_translate(t_vector3d vec, \
double t_x, double t_y, double t_z);
t_vector3d		transform_translate(t_vector3d vec, \
double t_x, double t_y, double t_z);
t_vector3d		x_axis_rotation(t_vector3d vec, double theta);
t_vector3d		y_axis_rotation(t_vector3d vec, double theta);
t_vector3d		z_axis_rotation(t_vector3d vec, double theta);
t_vector3d		transform_t_rotate(t_vector3d vec, t_vector3d rotation);
t_vector3d		transform_inverse_rotate(t_vector3d vec, t_vector3d rotation);
t_vector3d		transform_t_scale(t_vector3d point, t_vector3d scale);
t_vector3d		transform_scale(t_vector3d point, double s_x, \
double s_y, double s_z);
t_vector3d		transform_uniform_scale(t_vector3d point, double s);
t_vector3d		get_all_axis_rotation(t_vector3d rotation);
double			get_z_axis_rot(t_vector3d rotation);
double			get_y_axis_rot(t_vector3d rotation);
double			get_x_axis_rot(t_vector3d rotation);
/*
**Draw Functions (functions that change parts of the image)
*/
void			mlx_draw_pixel(t_img *img, t_pixel pixel);

/*
**Local/World Functions (functions that translate local and world space)
*/
t_ray			world_to_local(t_ray ray, t_vector3d pos, t_vector3d rot);
t_hit_result	local_to_world(t_hit_result hr, t_vector3d pos, t_vector3d rot);

/*
**Position Functions (functions that run on a position struct)
*/
int				reset_position(t_vector3d *pos);

/*
**Rotation Functions (functions that run on a rotation struct)
*/
int				reset_rotation(t_vector3d *rot);

/*
**Keyboard Functions (functions that relate to keys being pressed)
*/
int				key_hook(int key, t_minirt *scene);

/*
**Free Functions (functions that are related to freeing malloced memory)
*/
void			exit_cleanly(t_minirt *scene, int status);
void			light_free(t_light *light);
void			sphere_free(t_sphere *sphere);
void			plane_free(t_plane *plane);
void			cylinder_free(t_cylinder *cylinder);
void			cone_free(t_cone *cone);
int				mouse_hook(t_minirt *scene);
int				void_free(void *free_me, int ret);
/*
**Parse.c
*/
int				parse(char **argv, t_minirt *scene);
int				prepare_file(char **argv, int *fd, t_minirt *scene);
int				scan_text(const char *str, t_minirt *scene, int ret);
/*
**parse_utils.c
*/
int				print_error(const char *str, int ret);
int				check_valid_file(const char *filename);
int				empty_line(const char *str);
/*
**parse_utils2.c
*/
int				split_count(char **split);
int				valid_color_check(char **split);
int				remove_nl(char *str);
int				parse_positive_double(char *str, double *num);
int				parse_color(char *str, t_color *color);
/*
**parse_utils3.c
*/
int				parse_vector(const char *str, t_vector3d *vector);
int				valid_vector_check(char **split);
int				rot_range(t_vector3d *rotation);
int				fov_range(double num);
/*
**parse_ambient.c
*/
int				ambient_parse(char **split, t_minirt *scene);
/*
**parse_camera.c
*/
int				camera_parse(char **split, t_minirt *scene);
/*
**parse_cone.c
*/
int				cone_parse(char **split, t_minirt *scene);
void			cone_add_last(t_minirt *scene, t_cone *cone);
/*
**parse_cylinder.c
*/
int				cylinder_parse(char **split, t_minirt *scene);
void			cylinder_add_last(t_minirt *scene, t_cylinder *cyl);
/*
**parse_light.c
*/
int				light_parse(char **split, t_minirt *scene);
void			light_add_last(t_minirt *scene, t_light *light);
/*
**parse_plane.c
*/
int				plane_parse(char **split, t_minirt *scene);
void			plane_add_last(t_minirt *scene, t_plane *plane);
/*
**parse_sphere.c
*/
int				sphere_parse(char **split, t_minirt *scene);
void			sphere_add_last(t_minirt *scene, t_sphere *sphere);

/*
Simple Vector Math (functions that allow for simple manipulations of vectors)
*/
t_vector3d		make_vector(double x, double y, double z);
t_vector3d		add_vec(t_vector3d v1, t_vector3d v2);
t_vector3d		subtract_vec(t_vector3d v1, t_vector3d v2);
t_vector3d		multiply_vector(t_vector3d v1, double d);
t_vector3d		divide_vector(t_vector3d v1, double d);

/*
Advanced Vector Math (functions that allow for simple manipulations of vectors)
*/
t_vector3d		normalize_vector(t_vector3d v1);
t_vector3d		cross_vector(t_vector3d v1, t_vector3d v2);
double			dot_vector(t_vector3d v1, t_vector3d v2);
double			vector_magnitude(t_vector3d vec);

/*
Quadratic Functions (functions that help solve quadratics)
*/
int				solve_quadratic(t_quadratic *qua);

/*
Color Math (functions that allow for the manipulation of colors)
*/
t_color			clamp_color(t_color color);
t_color			make_color(int r, int g, int b);
int				int_color(t_color color);
t_vector3d		color_to_vector(t_color color);
t_color			vector_to_color(t_vector3d vector);

/*
Lighting Functions (functions that deal with illumination calculation)
*/
t_color			calculate_illumination(t_minirt *scene, t_hit_result *hit);

/*
Tracing Functions (functions that deal with the raytracing logic)
*/
int				basic_tracer(t_minirt *scene);
int				test(t_minirt *scene);

/*
Intersection Functions (functions that calculate hit data for objects)
*/
int				find_closest_intersection(t_minirt *scene, \
t_ray ray, t_hit_result *closest_hit);

/*
Sphere Functions (functions that handle math related to spheres)
*/
int				sphere_intersect(t_sphere *sphere, t_ray ray, t_hit_result *hr);
t_vector3d		sphere_normal(t_sphere *sphere, t_vector3d vec);

/*
plane Functions (functions that handle math related to planes)
*/
int				plane_intersect(t_plane *plane, t_ray ray, t_hit_result *hr);
t_vector3d		plane_normal(t_plane *plane, t_vector3d vec);

/*
Cylinder Functions (functions that handle math related to cylinders)
*/
int				cylinder_intersect(t_cylinder *cylinder, \
t_ray ray, t_hit_result *hr);
t_vector3d		cylinder_normal(t_cylinder *cylinder, t_vector3d vec);

#endif