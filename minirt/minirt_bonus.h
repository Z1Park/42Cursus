/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 12:43:36 by jpark2            #+#    #+#             */
/*   Updated: 2023/03/09 11:16:20 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_BONUS_H
# define MINIRT_BONUS_H
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include "mlx.h"
# include "libft.h"
# include "get_next_line.h"

# define DBL_EPSL	0.0000001
# define ALIAS		10

enum e_hook
{
	ON_KEYDOWN		= 2,
	ON_KEYUP		= 3,
	ON_MOUSEDOWN	= 4,
	ON_MOUSEUP		= 5,
	ON_MOUSEMOVE	= 6,
	ON_DESTROY		= 17
};

typedef enum e_parse
{
	PARSE_AMBIENT		= 1,
	PARSE_CAMERA		= 2,
	PARSE_BACKGROUND	= 4,
	PARSE_REFLECTION	= 8,
}	t_parse;

typedef enum e_handle_key
{
	K_ESC = 53
}	t_handle_key;

typedef enum e_obj
{
	OBJ_SPHERE,
	OBJ_PLANE,
	OBJ_CYLINDER,
	OBJ_CONE,
}	t_obj;

typedef enum e_ref
{
	REFLECT_PHONG,
	REFLECT_FULL_PHONG,
	REFLECT_RAY_TRACING,
}	t_ref;

typedef enum e_material
{
	GLASS	= 0,
	MIRROR	= 1,
	METAL	= 3,
	WOOD	= 10,
}	t_material;

typedef struct s_vec
{
	double	x;
	double	y;
	double	z;
}	t_vec;

typedef struct s_spco
{
	double	radius;
	double	theta;
	double	pie;
}	t_spco;

typedef struct s_view
{
	double	aspect_ratio;
	int		img_width;
	int		img_height;
	double	focal_length;
}	t_view;

typedef struct s_camera
{
	double	aspect_ratio;
	double	viewport_height;
	double	viewport_width;
	double	theta;
	double	lens_radius;
	int		img_width;
	int		img_height;
	t_vec	origin;
	t_vec	horizon;
	t_vec	vert;
	t_vec	left_bot;
	t_vec	u;
	t_vec	v;
	t_vec	w;
}	t_camera;

typedef struct s_ray
{
	t_vec	dir;
	t_vec	org;
}	t_ray;

typedef struct s_texture
{
	void	*img;
	char	*addr;
	int		bpp;
	int		size_line;
	int		endn;
	int		width;
	int		height;
}	t_texture;

typedef struct s_surface
{
	t_material	mat;
	t_vec		color;
	t_texture	texture;
	t_texture	bump;
}	t_surface;

typedef struct s_hit_record
{
	t_obj		obj_type;
	t_vec		p;
	t_vec		normal;
	double		t;
	double		u;
	double		v;
	int			front_face;
	t_surface	surface;
}	t_hit_record;

typedef struct s_sphere
{
	t_vec		center;
	double		radius;
	t_surface	surface;
}	t_sphere;

typedef struct s_plane
{
	t_vec		point;
	t_vec		normal;
	t_surface	surface;
}	t_plane;

typedef struct s_cylinder
{
	t_vec		center;
	t_vec		normal;
	double		diameter;
	double		height;
	t_surface	surface;
}	t_cylinder;

typedef struct s_cone
{
	t_vec		center;
	t_vec		normal;
	double		cosine;
	double		height;
	t_surface	surface;
}	t_cone;

typedef struct s_light
{
	t_vec			point;
	double			brightness;
	t_vec			color;
	struct s_light	*next;
}	t_light;

typedef struct s_obj_list
{
	void				*obj;
	t_obj				obj_type;
	struct s_obj_list	*next;
}	t_obj_list;

typedef struct s_mlx_arg
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bpp;
	int			size_line;
	int			endn;
	t_parse		parse_flag;
	t_camera	cam;
	t_vec		cam_dir;
	t_vec		ambient;
	t_surface	background;
	t_ref		ref_type;
	t_ray		ray;
	t_light		*lights;
	t_obj_list	*obj_list;
}	t_mlx_arg;

void			free_argument(t_mlx_arg *mlx_arg);
void			error_exit(char *str);

/* control.c */
void			cntl_map(t_mlx_arg *mlx_arg);

/* fileio.c */
int				check_filename(char *filename);
void			argument_init(t_mlx_arg *mlx_arg);
void			file_parse(t_mlx_arg *mlx_arg, char *filename);

/* vector_operation.c */
t_vec			vec(double x, double y, double z);
t_vec			vec_plus(t_vec vec1, t_vec vec2);
t_vec			vec_diff(t_vec vec1, t_vec vec2);
t_vec			vec_mul(t_vec vec, double t);
t_vec			vec_div(t_vec vec, double t);

/* vector_operation2.c */
t_vec			vec_mul2(t_vec v1, t_vec v2);
t_vec			vec_neg(t_vec v1);
t_vec			vec_reflect(t_vec v, t_vec normal);
t_vec			vec_refract(t_vec unit_vec, t_vec normal, double eta_ratio);
int				vec_cmp(t_vec v1, t_vec v2);

/* vector.c */
t_vec			vec_unit(t_vec v);
double			vec_scalar(t_vec vec);
double			vec_dot(t_vec vec1, t_vec vec2);
t_vec			vec_cross(t_vec vec1, t_vec vec2);
double			get_cosine(t_vec vec1, t_vec vec2);

/* color.c */
t_vec			calc_gradation(t_vec color, double ratio, \
								t_vec light, double t);
t_vec			set_background_color(t_mlx_arg *mlx_arg, double u, double v);
t_vec			ray_color(t_ray r, t_mlx_arg *mlx_arg, int depth);
int				write_color(t_vec *color, int num);
double			color_resize(double color);

/* sphere.c */
double			sphere_hit(t_sphere sphere, t_ray ray);
int				rec_sp_hit(t_sphere sp, t_ray ray, \
							double t_max, t_hit_record *rec);

/* utils.c */
int				ft_error_atoi(const char *str);
double			ft_atod(char *s);
double			clamp(double x, double min, double max);

/* utils2.c */
void			argv_free(char **argv);
int				get_argv_size(char **argv);
double			light_attenuation(double brightness, double distance);
t_vec			string_to_vec(char *s);
double			degrees_to_radians(double degrees);

/* ray_utils.c */
void			set_face_normal(t_ray ray, t_hit_record *rec);
t_vec			ray_at(t_ray *ray, double t);

/* random_utils.c */
double			rand_double(void);
double			rand_minmax(double min, double max);
t_vec			rand_in_unit_disk(void);
t_vec			rand_in_unit_sphere(void);
t_vec			random_unit_vec(void);

/* setting.c */
void			set_ambient(t_mlx_arg *mlx_arg, char **argv);
void			add_background(t_mlx_arg *mlx_arg, char **argv);
void			set_camera(t_mlx_arg *mlx_arg, char **argv);
void			set_reflection_type(t_mlx_arg *mlx_arg, char **argv);

/* setting2.c */
void			add_light(t_mlx_arg *mlx_arg, char **argv);
t_material		get_material_type(char *str);

/* object.c */
t_obj_list		*add_object(t_mlx_arg *mlx_arg, t_obj obj_type);
void			add_sphere(t_mlx_arg *mlx_arg, char **argv);
void			add_plane(t_mlx_arg *mlx_arg, char **argv);
void			add_cylinder(t_mlx_arg *mlx_arg, char **argv);
void			add_cone(t_mlx_arg *mlx_arg, char **argv);

/* phong_lighting.c */
t_vec			phong_lighting(t_mlx_arg *mlx_arg, t_hit_record *rec);

/* ray.c */
int				shortest_hit(t_mlx_arg *mlx_arg, t_ray ray, t_hit_record *rec);

/* ray_casting.c */
void			ray_casting(t_mlx_arg *mlx_arg);

/* shadow.c */
int				shadow_check(t_mlx_arg *mlx_arg, t_vec surf, t_vec dir);

/* scatter.c */
int				scatter_lamb(t_ray r, t_hit_record *rec, \
								t_vec *color, t_ray *sct);
int				scatter_metal(t_ray r, t_hit_record *rec, \
								t_vec *color, t_ray *sct);
int				scatter_glass(t_ray r, t_hit_record *rec, \
								t_vec *color, t_ray *sct);

/* texture.c */
t_vec			check_texture(double u, double v);
void			check_color_pattern(t_mlx_arg *mlx_arg, \
									t_surface *surf, char *s);
t_vec			get_texture(t_hit_record *rec, double u, double v);

/* cone.c */
double			cone_hit(t_cone cone, t_ray ray);
t_vec			cone_normal_vec(t_vec p, t_cone cone);
int				rec_cone_hit(t_cone cone, t_ray ray, \
							double t_max, t_hit_record *rec);

/* cylinder.c */
double			cylinder_hit(t_cylinder cylinder, t_ray ray);
t_vec			cylinder_normal_vec(t_vec p, t_cylinder cy);
int				rec_cy_hit(t_cylinder cy, t_ray ray, \
							double t_max, t_hit_record *rec);

/* plane.c */
double			plane_hit(t_plane plane, t_ray ray);
t_vec			plane_normal_vec(t_ray ray, t_plane plane, double t);
int				rec_plane_hit(t_plane plane, t_ray ray, \
								double t_max, t_hit_record *rec);

/* bump.c */
void			set_normal(t_hit_record *rec, int x, int y);

/* color_utils.c */
int				get_r(int trgb);
int				get_g(int trgb);
int				get_b(int trgb);
unsigned int	get_pixel(t_texture texture, int x, int y);
void			put_pixel(t_mlx_arg *mlx_arg, int x, int y, int color);

#endif
